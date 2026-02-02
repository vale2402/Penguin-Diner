/**
 * @file main.cpp
 * @brief Program entry point: loads configuration and runs the game loop.
 */
#include <iostream>
#include "header/ConfigManager.hpp"
#include "header/Joc.hpp"

/**
 * @brief Main entry point for the Penguin Diner game application.
 *
 * This function initializes the random number generator, loads configuration
 * settings from a file, creates a game instance, and starts the main game loop.
 *
 * @return 0 on successful execution, -1 if configuration loading or game initialization fails
 *
 * @throws std::exception Catches and logs configuration or game initialization errors
 */
int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    ConfigManager config;
    try {
        config.loadFromFile("settings.txt");
    } catch (const std::exception &e) {
        std::cerr << "Eroare Config: " << e.what() << std::endl;
        return -1;
    }

    try {
        Joc joc(config);
        joc.run();
    } catch (const std::exception &e) {
        std::cerr << "Eroare Joc: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
