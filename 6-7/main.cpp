#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <termios.h>
#include <thread>
#include <mutex>
#include <future>
#include <unistd.h> 

#include "./include/game.hpp"

constexpr int GAME_MAP_WIDTH  { 30 };
constexpr int GAME_MAP_HEIGHT { 20 };

const std::string logFileName { "log.txt" };

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Game game{ GAME_MAP_WIDTH, GAME_MAP_HEIGHT };

    LoggingListener logger{ logFileName, game.getEventManager() };
    PrintingListener killfeed{ game.getEventManager() };
 
    Player player{ 2, 2 };
    game.addPlayer(&player);

    GameThread gameThreadClassInstance{ game, killfeed };
    std::thread gameThread{ std::ref(gameThreadClassInstance) };

    MovementThread movementThreadClassInstance{ game };
    std::thread movementThread{ std::ref(movementThreadClassInstance) };

    movementThread.join();
    gameThread.join();
    return 0;
}
