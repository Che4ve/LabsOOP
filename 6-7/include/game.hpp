#pragma once

#include <iostream>
#include <sstream>
#include <streambuf>
#include <vector>
#include <deque>
#include <chrono>
#include <termios.h>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <random>
#include <future>
#include <unistd.h> 

#include "npc.hpp"
#include "observer.hpp"

const char EMPTY_CELL = '.';
const char PLAYER_CELL = 'P';
const char ATTACK_CELL = '*';
const char ELF_CELL = 'E';
const char BEAR_CELL = 'B';
const char THIEF_CELL = 'T';

const char npcType2Char(NPCType type) {
    switch (type) {
        case ELF:   return ELF_CELL;
        case BEAR:  return BEAR_CELL;
        case THIEF: return THIEF_CELL;
        default:    return EMPTY_CELL;
    }
}

class Player {
    public:
        int x;
        int y;

        Player(int x, int y) : x(x), y(y) {}

        int handleInput(char input) {
            // Обработка ввода
            switch (input) {
                case 'w': case 'W':
                    y -= 1;
                    break;
                case 's': case 'S':
                    y += 1;
                    break;
                case 'a': case 'A':
                    x -= 1;
                    break;
                case 'd': case 'D':
                    x += 1;
                    break;
            }
            return 1;
        }
};

std::mutex pauseMutex;
std::condition_variable pauseCondition;

std::shared_mutex accessMutex;

std::mutex outputMutex;

class Game {
public:
    Game(int width, int height) : width(width), height(height), 
        _eventManager(), _isRunning(true) { 
        map.assign(height, std::vector<char>(width, EMPTY_CELL));
    }

    const std::vector<NPC*>& getNPCList() const { return _npc_list; }

    void updateNPCs() {
        for (NPC* npc : _npc_list) {
            if (!npc->isAlive()) {
                continue;
            }
            npc->x = std::clamp(npc->x, 0, width - 1);
            npc->y = std::clamp(npc->y, 0, height - 1);
            setElement(npc->x, npc->y, npcType2Char(npc->getType()));
        }
    }

    void clearNPCs() {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (isNpcCell(x, y)) {
                    setElement(x, y, EMPTY_CELL);
                }
            }
        }
    }

    void addNPC(NPC* npc) {
        _npc_list.push_back(npc);
    }

    Player* getPlayer() { return _player; }

    void removeNPC(NPC* targetNpc) {
        auto it = std::find_if(_npc_list.begin(), _npc_list.end(),
            [targetNpc](const NPC* npc)  { return targetNpc == npc; });
        _npc_list.erase(it);
    }

    void addPlayer(Player* player) {
        _player = player;
    }

    void updatePlayer() {
        if (_player != nullptr) {
            setElement(_player->x, _player->y, PLAYER_CELL);
        }
    }

    void clearPlayer() {
        if (_player != nullptr) {
            setElement(_player->x, _player->y, EMPTY_CELL);
        }
    }

    void drawMap() const {
        std::lock_guard<std::mutex> lock(outputMutex);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << map[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

    std::string getMenu() {
        std::string res;
        std::stringstream ss;
        ss << "  [w|a|s|d] Movement\n" 
           << "  [+] Add NPC\n"
           << "  [f] Switch Battle Mode\n"
           << "  [p] Print NPCs data\n"
           << "  [<] Load NPCs from file\n"
           << "  [>] Save NPCs to file\n"
           << "  [q] Stop\n";
        res = ss.str();
        return res;
    }

    bool isNpcCell(int x, int y) const { 
        char cell = getElement(x, y);
        switch (cell) {
            case ELF_CELL: case BEAR_CELL: case THIEF_CELL: return true;
        }
        return false;
    }

    char getElement(int x, int y) const { 
        std::shared_lock<std::shared_mutex> lock(accessMutex);
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return map[y][x];
        }
        return '\0';
    }

    void setElement(int x, int y, char element) {
        std::unique_lock<std::shared_mutex> lock(accessMutex);
        if (x >= 0 && x < width && y >= 0 && y < height) {
            map[y][x] = element;
        }
    }

    int getHeight() const { 
        std::shared_lock<std::shared_mutex> lock(accessMutex);
        return height; 
    }

    int getWidth() const { 
        std::shared_lock<std::shared_mutex> lock(accessMutex);
        return width; 
    }

    bool isRunning() const { 
        std::shared_lock<std::shared_mutex> lock(accessMutex); 
        return _isRunning; 
    }

    void stop() { 
        std::unique_lock<std::shared_mutex> lock(accessMutex);
        _isRunning = false; 
    }

    bool isPaused() const { 
        std::shared_lock<std::shared_mutex> lock(accessMutex);
        return _isPaused; 
    }

    void pause() { 
        std::unique_lock<std::shared_mutex> lock(accessMutex);
        _isPaused = true; 
    }

    void resume() { 
        std::unique_lock<std::shared_mutex> lock(accessMutex);
        _isPaused = false; 
        pauseCondition.notify_all();
    }

    InGameEventManager& getEventManager() { return _eventManager; }

    void drawLine(int x1, int y1, int x2, int y2, char cell) {
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            setElement(x1, y1, cell);
            if (x1 == x2 && y1 == y2) {
                break;
            }
            int err2 = 2 * err;
            if (err2 > -dy) {
                err -= dy;
                x1 += sx;
            }
            if (err2 < dx) {
                err += dx;
                y1 += sy;
            }
        }
    }

private:
    bool _isPaused{ true };
    bool _isRunning{ true };

    int width;
    int height;
    std::vector<std::vector<char>> map;
    std::vector<NPC*> _npc_list;
    Player* _player{ nullptr };
    InGameEventManager _eventManager;

};

class BattleThread {
public:
    BattleThread(NPC* attacker, NPC* target, Game &game) :
        _attacker(attacker), _target(target),
        _game(game), _eventManager(game.getEventManager()) {}

    void operator()() {
        int attackerRoll = rollDie();
        int defenderRoll = rollDie();
        if (attackerRoll > defenderRoll) {
            _attacker->attack(_target);
            _game.drawLine(_target->x, _target->y, 
                       _attacker->x, _attacker->y, '*');
            
            _game.setElement(_target->x, _target->y, '0');
            _notifyAboutKill();
        } else {
            _game.drawLine(_target->x, _target->y, 
                       _attacker->x, _attacker->y, ',');
        }
        
    }

private:
    int rollDie() {
        // create a C++11 random engine and seed with std::random_device
        // static to keep it alive between function calls
        static std::default_random_engine rng(std::random_device {} ());

        // create a C++11 static uniform distribution
        static std::uniform_int_distribution<> dist { };
        std::uniform_int_distribution<> dis{ 1, 6 };

        // generate a random die roll and return the value
        return dist(rng, decltype(dist)::param_type { 1, 6 });
    }

    void _notifyAboutKill() {
            std::stringstream logMessage;
            logMessage << _attacker->getName() << " killed " << _target->getName();
            _eventManager.createMessage(logMessage.str());
            _eventManager.notify();
    }

private:
    NPC* _attacker;
    NPC* _target;
    Game &_game;
    InGameEventManager &_eventManager;
};

class MovementThread {
public:
    MovementThread(Game &game) :
        _game(game), _eventManager(game.getEventManager()) {}

    void operator()() {
        NPCFightVisitor fightVisitor;
        std::thread fightAbilityThread(_fight, this); // Calculating attacks
        while (_game.isRunning()) { 
            {
            std::unique_lock<std::mutex> lock(pauseMutex);
            pauseCondition.wait(lock, [this] { return !_game.isPaused(); });

            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            for (NPC* attacker : _game.getNPCList()) {
                if (!attacker->isAlive()) {
                    continue;
                }
                // for (NPC* target : _game.getNPCList()) {
                //     if (!_isAbleToBattle(attacker, target)) {
                //         continue;
                //     }
                //     std::thread(BattleThread(attacker, target, _game)).detach();
                // }
                fightVisitor.visit(attacker); // NPC roaming
            }
            }
        }
        fightAbilityThread.detach();
    }

private:
    static void _fight(MovementThread* instance) {
        while (instance->_game.isRunning()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            if (instance->_game.isPaused()) {
                continue;
            }
            for (NPC* attacker : instance->_game.getNPCList()) {
                if (!attacker->isAlive()) {
                    continue;
                }
                for (NPC* target : instance->_game.getNPCList()) {
                    if (!instance->_isAbleToBattle(attacker, target)) {
                        continue;
                    }
                    std::thread(BattleThread(attacker, target, instance->_game)).join();
                }
            }
        }
    }

    bool _isAbleToBattle(NPC* attacker, NPC* target) {
        if (!attacker->isAlive() || !target->isAlive()) {
            return false;
        }
        if (attacker == target) {
            return false;
        }
        if (attacker->getDistance2(target) > attacker->getAttackRange()) {
            return false;
        } 
        if (!attacker->isCompatibleWith(target)) {
            return false;
        }

        return true;
    }

private:
    bool _isPaused{ false };
    Game &_game;
    InGameEventManager &_eventManager;

    std::mutex _mutex;
};

static struct termios stored_settings;

class GameThread {
public:
    GameThread(Game &game, PrintingListener &killfeed) : 
        _game(game), _killfeed(killfeed) {}

    void operator()() {
        _setKeypress();
        std::thread inputThread{&GameThread::_getInput, this};

        Player* player = _game.getPlayer();
        // Цикл игры
        while (_game.isRunning()) {
            isPaused = _game.isPaused();
            system("clear");  // Очистка терминала (Unix)

            {
                std::lock_guard<std::mutex> lock(outputMutex);
                _killfeed.printKillfeed();
            }

            _game.updateNPCs();
            _game.updatePlayer();

            _game.drawMap();

            _game.clearNPCs();
            _game.clearPlayer();

            {
                std::lock_guard<std::mutex> lock(outputMutex);
                std::cout << _game.getMenu() << std::endl;
            }
            // Обработка ввода
            {
                // Read user input
                std::lock_guard<std::mutex> lock(_inputMutex);
                char input = _userInput.load();
                
                if (input == 'q') {
                    _game.resume();
                    _game.stop();
                    break;
                }
                if (input == '+') {
                    std::thread(&GameThread::_IaddNPCLogic, this).join();
                }
                if (input == '<') {
                    std::thread(&GameThread::_IloadFromFileLogic, this).join();
                }
                if (input == '>') {
                    std::thread(&GameThread::_IsaveToFileLogic, this).join();
                }
                if (input == 'p') {
                    std::thread(&GameThread::_IshowNPCDataLogic, this).join();
                }
                if (input == 'f') {
                    if (_game.isPaused()) {
                        _game.resume();
                    } else {
                        _game.pause();
                    }
                }
                player->handleInput(input);
                _userInput = '\0';
            }
            
            // Задержка между тиками (в милисекундах)
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        inputThread.join();
        _resetKeypress();
    }

private:
    
    // Function to get input in a separate thread
    static void _getInput(GameThread* instance) {
        char c;

        for (;;) {
            {
                c = std::getchar();
                std::lock_guard<std::mutex> lock(instance->_inputMutex);
                instance->_userInput.store(c);
            }
            if (c == 'q') {
                break;
            }
        }
    }

    void _setKeypress(void) {
        struct termios new_settings;

        tcgetattr(0, &stored_settings);

        new_settings = stored_settings;

        new_settings.c_lflag &= ~ICANON; /* disable buffered i/o */
        new_settings.c_lflag &= 0 ? ECHO : ~ECHO; /* set echo mode */

        tcsetattr(0, TCSANOW, &new_settings);
        return;
    }
        
    void _resetKeypress(void) {
        tcsetattr(0, TCSANOW, &stored_settings);
        return;
    }

    void _prepareForInterface() {
        _game.pause();
        system("clear");
        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "Press any button to continue..." << std::endl;
        }
        fflush(stdin);
        system("clear");
        _resetKeypress();
    }

    void _prepareForGameplay() {
        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "Press any button to continue..." << std::endl;
        }
        _setKeypress();
        std::getchar();
        fflush(stdin);
    }

    void _IaddNPCLogic() {
        _prepareForInterface();

        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "Add NPC in the format '[type],[name],[x],[y]'\n"
                << "Where type is int: 0 - Elf, 1 - Bear, 2 - thief\n"
                << "Enter NPC: ";
        }

        std::string line;
        std::getline(std::cin, line);
        try {
            NPC* newNPC = deserialize(line);
            if (newNPC == nullptr) {
                std::cerr << "Invalid input." << std::endl;
            } else {
                std::lock_guard<std::mutex> lock(outputMutex);
                // Print NPC name (for verification)
                std::cout << newNPC->getName() << " added to the game." << std::endl;
                // Add the NPC to the game
                _game.addNPC(newNPC);
            }
        } catch (std::exception& e) {
            std::cerr << "Failed to add NPC. Invalid input." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        _prepareForGameplay();
    }

    void _IshowNPCDataLogic() {
        _prepareForInterface();
        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "NPC list:" << std::endl;
        }

        std::vector<NPC*> npcList = _game.getNPCList();
        std::vector<NPC*>::const_iterator it;
        for (it = npcList.begin(); it < npcList.end(); it++) {
            std::cout << it - npcList.begin() + 1 << ".\t" << **it << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        _prepareForGameplay();
    }

    void _IsaveToFileLogic() {
        _prepareForInterface();
        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "Enter file name: ";
        }
        std::string fileName;
        std::getline(std::cin, fileName);
        saveNPCsToFile(fileName, _game.getNPCList());
        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "Done!" << std::endl;
        }
        _prepareForGameplay();
    }

    void _IloadFromFileLogic() {
        _prepareForInterface();
        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "Enter file name: ";
        }
        std::string fileName;
        std::getline(std::cin, fileName);
        try {
            std::vector<NPC*> npcList{ loadNPCsFromFile(fileName) };
            for (NPC* npc : npcList) {
                _game.addNPC(npc);
            }
            {
                std::lock_guard<std::mutex> lock(outputMutex);
                std::cout << "NPCs are loaded to the game!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        _prepareForGameplay();
    }

public:
    bool isPaused{ true };

private:
    Game &_game;
    PrintingListener &_killfeed;
    std::atomic_char _userInput{ '\0' };
    std::string _inputStr;
    std::mutex _inputMutex;
    std::mutex _interfaceMutex;

};