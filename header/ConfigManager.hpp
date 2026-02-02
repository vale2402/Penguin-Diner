/**
 * @file ConfigManager.hpp
 * @brief Declares a simple key-value configuration loader for gameplay parameters.
 */
#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <map>
#include <string>
#include <SFML/System/Vector2.hpp>

/**
 * @class ConfigManager
 * @brief Loads and manages configuration settings from a text file
 */
class ConfigManager {
private:
    std::map<std::string, float> settings; ///< Key-value pairs storing configuration parameters

public:
    /**
     * @brief Loads configuration from a file
     * @param filename Path to configuration file
     * @throws std::runtime_error if file cannot be opened
     */
    void loadFromFile(const std::string &filename);

    /**
     * @brief Retrieves a float value by key
     * @param key Configuration key
     * @return Float value, or 0.0f if key does not exist
     */
    float getFloat(const std::string &key) const;

    /**
     * @brief Retrieves a 2D vector by key prefix (e.g., "PREFIX_X" and "PREFIX_Y")
     * @param keyPrefix Key prefix (without "_X" or "_Y" suffix)
     * @return Vector with X and Y components from the configuration
     */
    sf::Vector2f getVector(const std::string &keyPrefix) const;
};

#endif
