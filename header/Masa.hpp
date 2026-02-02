/**
 * @file Masa.hpp
 * @brief Declares the Masa (table) class managing seating, orders, and UI elements.
 */
#ifndef MASA_HPP
#define MASA_HPP

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Client_Pinguin.hpp"

/**
 * @class Masa
 * @brief Represents a table in the restaurant managing customer seating and service
 *
 * This class handles all table-related logic including customer seating, order taking,
 * food delivery, eating time, payment, and visual representation of these states.
 */
class Masa {
private:
    sf::Sprite sprite; ///< Visual representation of the table
    sf::Sprite *clientVisual = nullptr; ///< Pointer to seated customer's visual sprite
    Client_Pinguin *clientLogic = nullptr; ///< Pointer to seated customer's logic object

    bool esteOcupata = false; ///< Flag: table has a seated customer
    bool asteaptaComanda = false; ///< Flag: customer is ready to order
    bool areMancare = false; ///< Flag: customer has been served food
    bool afiseazaBani = false; ///< Flag: customer finished eating, showing payment
    int tipProdus = -1; ///< Type of food ordered (-1 = none, 0 = fish, 1 = juice)

    sf::Sprite bubbleSprite; ///< Speech bubble for showing customer's order
    sf::Sprite foodSprite; ///< Sprite for food on table or in speech bubble
    sf::Sprite plateSprite; ///< Sprite for plate on table
    sf::Sprite moneySprite; ///< Sprite for money/payment after eating
    sf::Clock timer; ///< Timer for state transitions (ordering, eating, payment)

public:
    /**
     * @brief Constructs a new table at specified position
     *
     * @param texture Texture for the table sprite
     * @param pos Position to place the table
     */
    Masa(const sf::Texture &texture, sf::Vector2f pos);

    /**
     * @brief Gets the table's sprite for rendering and collision detection
     *
     * @return Reference to the table sprite
     */
    sf::Sprite &getSprite();

    /**
     * @brief Gets the visual sprite of the seated customer
     *
     * @return Pointer to customer sprite, or nullptr if table is empty
     */
    sf::Sprite *getClientVisual() const;

    /**
     * @brief Gets the logic object of the seated customer
     *
     * @return Pointer to customer logic object, or nullptr if table is empty
     */
    Client_Pinguin *getClientLogic() const;

    /**
     * @brief Checks if table has a seated customer
     *
     * @return true if occupied, false if empty
     */
    bool isOcupata() const;

    /**
     * @brief Checks if customer is waiting to place an order
     *
     * @return true if customer is ready to order
     */
    bool isAsteaptaComanda() const;

    /**
     * @brief Checks if customer has been served food
     *
     * @return true if food is on the table
     */
    bool isAreMancare() const;

    /**
     * @brief Checks if table is showing payment (customer finished eating)
     *
     * @return true if displaying money sprite
     */
    bool isAfiseazaBani() const;

    /**
     * @brief Gets the type of food ordered by the customer
     *
     * @return Product type (0 = fish, 1 = juice, -1 = none)
     */
    int getTipProdus() const;

    /**
     * @brief Seats a customer at this table
     *
     * @param newClient Visual sprite of the customer
     * @param newLogic Logic object of the customer
     */
    void setClient(sf::Sprite *newClient, Client_Pinguin *newLogic);

    /**
     * @brief Marks that the customer's order has been taken
     */
    void preiaComanda();

    /**
     * @brief Delivers food to the customer at this table
     *
     * @param textures Asset manager for loading food/plate textures
     * @param tip Type of food being delivered (0 = fish, 1 = juice)
     */
    void primesteMancare(AssetManager<sf::Texture> &textures, int tip);

    /**
     * @brief Updates table state logic each frame
     *
     * Handles ordering countdown, eating countdown, payment display, and customer removal.
     *
     * @param dt Delta time in seconds
     * @param textures Asset manager for loading UI sprites
     * @param baniTotal Reference to total money counter to add payment to
     */
    void updateLogic(float dt, AssetManager<sf::Texture> &textures, int &baniTotal);

    /**
     * @brief Renders food, plates, and money on the table
     *
     * @param window Render window to draw to
     */
    void drawItems(sf::RenderWindow &window) const;

    /**
     * @brief Renders UI elements (speech bubbles, order indicators)
     *
     * @param window Render window to draw to
     */
    void drawUI(sf::RenderWindow &window) const;
};

#endif
