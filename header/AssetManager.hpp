/**
 * @file AssetManager.hpp
 * @brief Generic resource manager template that loads and stores assets by name.
 *        Designed for SFML-like resources that provide loadFromFile().
 */
#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

/**
 * @class AssetManager
 * @brief Template class for managing and caching game assets (textures, fonts, etc.)
 *
 * This class provides a centralized resource management system that loads assets
 * from files and stores them by name for efficient retrieval. It works with any
 * type that implements a loadFromFile() method (e.g., SFML textures, fonts).
 *
 * @tparam T Type of asset to manage (must have a loadFromFile() method)
 */
template<typename T>
class AssetManager {
private:
    std::map<std::string, T> resurse; ///< Container storing assets by name

public:
    /**
     * @brief Default constructor
     */
    AssetManager() = default;

    /**
     * @brief Loads an asset from a file and stores it with a given name
     *
     * @param nume Name/key to associate with the loaded asset
     * @param cale_fisier Path to the file to load
     * @throws std::runtime_error if the file cannot be loaded
     */
    void load(const std::string &nume, const std::string &cale_fisier) {
        T resursa;
        if (resursa.loadFromFile(cale_fisier)) {
            resurse[nume] = resursa;
        } else {
            throw std::runtime_error("Eroare: Nu s-a putut incarca fisierul: " + cale_fisier);
        }
    }

    /**
     * @brief Retrieves a previously loaded asset by name
     *
     * @param nume Name/key of the asset to retrieve
     * @return Reference to the requested asset
     * @throws std::runtime_error if the asset with the given name doesn't exist
     */
    T &get(const std::string &nume) {
        if (!resurse.contains(nume)) {
            throw std::runtime_error("Eroare: Resursa nu exista: " + nume);
        }
        return resurse[nume];
    }
};

#endif
