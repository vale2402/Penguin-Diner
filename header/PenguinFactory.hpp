/**
 * @file PenguinFactory.hpp
 * @brief Declares a factory for creating penguin sprites with predefined textures and transforms.
 */
#ifndef PENGUIN_FACTORY_HPP
#define PENGUIN_FACTORY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "AssetManager.hpp"

/**
 * @class PenguinFactory
 * @brief Factory class for creating penguin customer sprites
 *
 * This class implements the Factory pattern to create penguin sprites
 * with appropriate textures and initial positioning based on penguin type.
 */
class PenguinFactory {
private:
    AssetManager<sf::Texture> &textures; ///< Reference to texture manager

public:
    /**
     * @brief Constructs a penguin factory with access to textures
     *
     * @param _textures Reference to the asset manager containing penguin textures
     */
    explicit PenguinFactory(AssetManager<sf::Texture> &_textures);

    /**
     * @brief Creates a new penguin sprite of the specified type
     *
     * @param type Type of penguin ("student", "afacerist", "bogat", "influencer")
     * @param startX Initial X position
     * @param startY Initial Y position
     * @return Pointer to newly allocated penguin sprite (caller owns the pointer)
     */
    [[nodiscard]] sf::Sprite *createPenguin(const std::string &type, float startX, float startY) const;
};

#endif
