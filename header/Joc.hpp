//
// Created by Valiv on 29/01/2026.
//

/**
 * @file Joc.hpp
 * @brief Declares the core game class responsible for running the main loop and scene.
 */
#ifndef JOC_HPP
#define JOC_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "AssetManager.hpp"
#include "ConfigManager.hpp"
#include "PenguinFactory.hpp"
#include "Masa.hpp"
#include "Client_Pinguin.hpp"

/**
 * @class Joc
 * @brief Main game controller managing the entire Penguin Diner simulation
 *
 * This class orchestrates all game systems including rendering, input handling,
 * customer spawning, order management, and game state. It manages the main game
 * loop and coordinates between visual sprites and logical entities.
 */
class Joc {
private:
    sf::RenderWindow window; ///< Main rendering window
    AssetManager<sf::Texture> textures; ///< Centralized texture manager

    sf::Font font; ///< Font used for UI text
    sf::Text textBani; ///< Text displaying current money

    ConfigManager &config; ///< Reference to configuration manager
    std::unique_ptr<PenguinFactory> penguinFactory; ///< Factory for creating penguin sprites

    sf::Sprite background; ///< Background image sprite
    sf::Sprite kitchen; ///< Kitchen area sprite
    sf::Sprite trashBin; ///< Trash bin sprite for discarding food
    sf::Sprite covor; ///< Carpet/mat sprite
    sf::Sprite penny; ///< Player character sprite

    std::vector<Masa> mese; ///< Vector of all tables in the restaurant
    std::vector<sf::Sprite *> coadaAsteptare; ///< Visual sprites for customers waiting in queue
    std::vector<Client_Pinguin *> coadaLogica; ///< Logic objects for customers in queue

    sf::Sprite *clientInMana = nullptr; ///< Pointer to customer sprite being carried
    Client_Pinguin *logicInMana = nullptr; ///< Pointer to logic object of carried customer
    int mancareInMana = -1; ///< Type of food being carried (-1 = none)
    sf::Sprite spriteMancareCarata; ///< Sprite for food being carried
    sf::Sprite spriteFarfurieCarata; ///< Sprite for plate being carried

    std::vector<int> comenziInLucru; ///< Orders currently being cooked
    std::vector<int> comenziPeTejghea; ///< Orders ready on the kitchen counter
    sf::Clock timerGatit; ///< Timer tracking cooking progress

    sf::Sprite spriteMancareTejghea; ///< Sprite for food on the kitchen counter
    sf::Sprite spriteFarfurieTejghea; ///< Sprite for plate on the kitchen counter

    sf::Clock ceasGlobal; ///< Global clock for delta time calculation
    sf::Vector2f targetPosition; ///< Target position for Penny to move to
    sf::Sprite *clientTinta = nullptr; ///< Target customer sprite for movement
    int indexMasaTinta = -1; ///< Target table index (-1 = none)
    bool mergeLaBucatarie = false; ///< Flag: Penny is moving to kitchen
    bool mergeLaGunoi = false; ///< Flag: Penny is moving to trash bin
    int bani = 0; ///< Current money accumulated
    float vitezaPenny; ///< Movement speed of Penny character

    bool rearanjareCoada = false; ///< Flag indicating queue needs rearranging
    sf::Clock timerCoada; ///< Timer for queue rearrangement animation
    sf::Clock timerSpawn; ///< Timer for customer spawning
    float timpUrmatorSpawn = 2.0f; ///< Time until next customer spawn

    /**
     * @brief Loads all game assets (textures, fonts) from files
     */
    void incarcaResurse();

    /**
     * @brief Initializes the game scene with all sprites and UI elements
     */
    void initializareScena();

    /**
     * @brief Processes user input events
     */
    void handleInput();

    /**
     * @brief Spawns a new customer and adds them to the waiting queue
     *
     * @throws Eroare_Restaurant_Plin if queue is at maximum capacity
     */
    void spawnClient();

    /**
     * @brief Processes mouse click events and determines appropriate actions
     *
     * @param pixelPos Pixel coordinates of the mouse click
     */
    void procesareClick(sf::Vector2i pixelPos);

    /**
     * @brief Updates all game logic based on elapsed time
     *
     * @param dt Delta time in seconds since last update
     */
    void update(float dt);

    /**
     * @brief Executes actions when Penny reaches her target destination
     *
     * Handles seating customers, picking up food, delivering orders, etc.
     *
     * @throws Eroare_Masa_Ocupata if trying to seat at occupied table
     * @throws Eroare_Actiune_Interzisa if trying invalid actions
     */
    void actiuniLaDestinatie();

    /**
     * @brief Renders all game objects to the window
     *
     * Implements depth sorting for proper visual layering.
     */
    void render();

public:
    /**
     * @brief Constructs a new game instance
     *
     * @param cfg Reference to configuration manager with game settings
     */
    explicit Joc(ConfigManager &cfg);

    /**
     * @brief Destructor cleaning up dynamically allocated resources
     */
    ~Joc();

    /**
     * @brief Starts and runs the main game loop until window is closed
     */
    void run();
};

#endif
