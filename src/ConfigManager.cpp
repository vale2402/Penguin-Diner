/**
 * @file ConfigManager.cpp
 * @brief Implements the configuration loader and accessors.
 */
#include "../header/ConfigManager.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

/**
 * @brief Loads configuration settings from a text file
 *
 * File format: each line contains a key and float value separated by whitespace.
 * Example: "PENNY_SPEED 200.0"
 *
 * @throws std::runtime_error if file cannot be opened
 */
void ConfigManager::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nu pot deschide fisierul de configurare: " + filename);
    }

    std::string key;
    float value;
    while (file >> key >> value) {
        settings[key] = value;
    }
    std::cout << "[CONFIG] Date incarcate din " << filename << "\n";
}

/**
 * @brief Retrieves a float value by key
 *
 * @return The float value, or 0.0f if key doesn't exist
 */
float ConfigManager::getFloat(const std::string &key) const {
    if (!settings.contains(key)) return 0.0f;
    return settings.at(key);
}

/**
 * @brief Retrieves a 2D vector by key prefix
 *
 * Looks up two keys: keyPrefix + "_X" and keyPrefix + "_Y"
 *
 * @return Vector with X and Y components from configuration
 */
sf::Vector2f ConfigManager::getVector(const std::string &keyPrefix) const {
    return {getFloat(keyPrefix + "_X"), getFloat(keyPrefix + "_Y")};
}
