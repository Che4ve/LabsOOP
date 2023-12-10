#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <termios.h>
#include <thread>
#include <future>
#include <unistd.h> 

#include "./include/game.hpp"

static struct termios stored_settings;

void setKeypress(void)
{
    struct termios new_settings;

    tcgetattr(0,&stored_settings);

    new_settings = stored_settings;

    /* Disable canonical mode, and set buffer size to 1 byte */
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(0,TCSANOW,&new_settings);
    return;
}
     
void resetKeypress(void)
{
    tcsetattr(0,TCSANOW,&stored_settings);
    return;
}

// Function to get input in a separate thread
void getInput(std::atomic_char& input, std::mutex& inputMutex) {
    char c;
    while (std::cin >> c) {
        {
            std::lock_guard<std::mutex> lock(inputMutex);
            input = c;
        }
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    setKeypress();
    Game game(30, 20);
    const std::string logFileName = "log.txt";
    LoggingListener logger(logFileName, game.getEventManager());
    PrintingListener killfeed(game.getEventManager());
 
    Player player(1, 2);
    game.addPlayer(&player);

    std::vector<NPC*> npcList = loadNPCsFromFile("npclist.txt");

    for (NPC* npc : npcList) {
        game.addNPC(npc);
    }

    NPCFightVisitor fightVisitor;
    

    std::atomic_char userInput('\0');
    std::mutex inputMutex;

    // Start the input thread
    std::thread inputThread(getInput, std::ref(userInput), std::ref(inputMutex));

    bool isBattle = false;
    // Цикл игры
    while (true) {
        system("clear");  // Очистка терминала (Unix)
        killfeed.printKillfeed();
        
        game.clearNPCs();

        if (isBattle) {
            for (NPC* npc : npcList) {
                fightVisitor.visit(npc);
            }
        }
        
        game.performCombat();
        game.updateNPCs();

        //game.drawKillfeed();
        game.drawMap();
        std::cout << "  [w|a|s|d] Movement\n" 
                  << "  [+] Add NPC\n"
                  << "  [-] Remove NPC\n"
                  << "  [f] Switch Battle Mode\n"
                  << "  [p] Print NPC data\n"
                  << "  [s] Save NPCs to file\n"
                  << "  [q] Stop\n" << std::endl;

        // Обработка ввода
        game.clearPlayer();
        {
            // Read user input
            std::lock_guard<std::mutex> lock(inputMutex);
            char input = userInput.load();
            
            if (input == 'q') {
                fflush(stdin);
                break;
            }
            if (input == 'p') {
                isBattle = isBattle == true ? false : false;

            }
            if (input == 'f') {
                isBattle = isBattle == false ? true : false;
            }
            player.handleInput(input);
            userInput = '\0';
        }
        game.updatePlayer();
        // Задержка между тиками (в милисекундах)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    // Join the input thread
    inputThread.join();
    resetKeypress();
    return 0;
}
