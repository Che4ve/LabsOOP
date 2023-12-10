#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <chrono>
#include <termios.h>
#include <thread>
#include <mutex>
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

class Game {
public:
    Game(int width, int height) : width(width), height(height), _eventManager() {
        map.assign(height, std::vector<char>(width, EMPTY_CELL));
    }

    void updateNPCs() {
        for (NPC* npc : _npc_list) {
            npc->x = std::clamp(npc->x, 0, width - 1);
            npc->y = std::clamp(npc->y, 0, height - 1);
            setElement(npc->x, npc->y, npcType2Char(npc->getType()));
        }
    }

    void clearNPCs() {
        for (NPC* npc : _npc_list) {
            setElement(npc->x, npc->y, EMPTY_CELL);
        }
    }

    void addNPC(NPC* npc) {
        _npc_list.push_back(npc);
    }

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
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << map[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

    char getElement(int x, int y) const { return map[x][y]; }

    void setElement(int x, int y, char element) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            map[y][x] = element;
        }
    }

    int getHeight() const { return height; }

    int getWidth() const { return width; }

    InGameEventManager& getEventManager() { return _eventManager; }

    void drawLine(int x1, int y1, int x2, int y2) {
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            setElement(x1, y1, ATTACK_CELL);
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

    void performCombat() {
        for (NPC* attacker : _npc_list) {
            for (NPC* target : _npc_list) {
                if (!attacker->isAlive() || !target->isAlive()) {
                    continue;
                }
                if (attacker != target) {
                    bool success = attacker->attack(target);
                    if (success) {
                        drawLine(attacker->x, attacker->y, target->x, target->y);
                        setElement(target->x, target->y, '0');
                        removeNPC(target);

                        std::stringstream logMessage;
                        logMessage << attacker->getName() << " killed " 
                                   << target->getName();
                        _eventManager.createMessage(logMessage.str());
                        _eventManager.notify();
                    }
                }
            }
        }
    }

private:
    int width;
    int height;
    std::vector<std::vector<char>> map;
    std::vector<NPC*> _npc_list;
    Player* _player{ nullptr };
    InGameEventManager _eventManager;

};


class BattleThread {
public:
    BattleThread(NPC* attacker, NPC* target) :
        _attacker(attacker), _target(target) {}

    void operator()() {
        int attackerRoll = rollDie();
        int defenderRoll = rollDie();
        if (attackerRoll > defenderRoll) {
            attacker->attack();
        }
    }

private:
    int rollDie() {
        std::random_device rd;
        std::mt19937 gen{ rd };
        std::uniform_int_distribution<> dis{ 1, 6 };
        return dis(gen);
    }

private:
    NPC* _attacker;
    NPC* _target;
};

class MovementThread {
public:
    MovementThread(std::vector<NPC*> npcs) : _npcs(npcs) {}

    void operator()() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            for (NPC* attacker : _npcs) {
                for (NPC* target : _npcs) {
                    if (!_isAbleToBattle(attacker, target)) {
                        continue;
                    }
                    std::thread battleThread(BattleThread(attacker, target));
                }
            }
        }
    }

private:
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

        return true;
    }

private:
    std::vector<NPC*> _npcs;
};
