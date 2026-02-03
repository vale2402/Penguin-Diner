/**
 * @file PenguinFactory.cpp
 * @brief Implements the factory that creates penguin sprites with predefined assets.
 */
#include "../header/PenguinFactory.hpp"

/**
 * @brief Constructs the factory with access to texture resources
 */
PenguinFactory::PenguinFactory(AssetManager<sf::Texture> &_textures) : textures(_textures) {
}

/**
 * @brief Creates a penguin sprite of specified type at given position
 *
 * Selects appropriate texture based on type string, applies standard scaling
 * and origin settings, and positions the sprite.
 *
 * @return Pointer to newly allocated sprite (caller must manage memory)
 */
sf::Sprite *PenguinFactory::createPenguin(const std::string &type, float startX, float startY) const {
    auto *penguin = new sf::Sprite();

    if (type == "student") penguin->setTexture(textures.get("c_student"));
    else if (type == "afacerist") penguin->setTexture(textures.get("c_afacerist"));
    else if (type == "bogat") penguin->setTexture(textures.get("c_bogat"));
    else if (type == "influencer") penguin->setTexture(textures.get("c_influencer"));

    penguin->setScale(4.0f, 4.0f);
    penguin->setOrigin(16, 16);
    penguin->setPosition(startX, startY);

    return penguin;
}
