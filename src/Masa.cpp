/**
 * @file Masa.cpp
 * @brief Implements the table logic: seating, orders, and UI.
 */
#include "../header/Masa.hpp"
#include <iostream>
#include <cstdlib>
#include "../header/Pinguini_Derivati.hpp"

/**
 * @brief Constructs a table with texture and position
 */
Masa::Masa(const sf::Texture &texture, sf::Vector2f pos)
    : clientVisual(nullptr),
      clientLogic(nullptr),
      esteOcupata(false),
      asteaptaComanda(false),
      areMancare(false),
      afiseazaBani(false),
      tipProdus(-1) {
    sprite.setTexture(texture);
    sprite.setScale(3.5f, 2.5f);
    sprite.setOrigin(32.0f, 32.0f);
    sprite.setPosition(pos);
}

/**
 * @brief Gets the table sprite
 */
sf::Sprite &Masa::getSprite() { return sprite; }

/**
 * @brief Gets the visual sprite of seated customer
 */
sf::Sprite *Masa::getClientVisual() const { return clientVisual; }

/**
 * @brief Gets the logic object of seated customer
 */
Client_Pinguin *Masa::getClientLogic() const { return clientLogic; }

/**
 * @brief Checks if table is occupied
 */
bool Masa::isOcupata() const { return esteOcupata; }

/**
 * @brief Checks if customer is waiting to order
 */
bool Masa::isAsteaptaComanda() const { return asteaptaComanda; }

/**
 * @brief Checks if customer has food on table
 */
bool Masa::isAreMancare() const { return areMancare; }

/**
 * @brief Checks if table is showing payment
 */
bool Masa::isAfiseazaBani() const { return afiseazaBani; }

/**
 * @brief Gets the ordered product type
 */
int Masa::getTipProdus() const { return tipProdus; }

/**
 * @brief Seats a customer at this table
 */
void Masa::setClient(sf::Sprite *newClient, Client_Pinguin *newLogic) {
    clientVisual = newClient;
    clientLogic = newLogic;

    if (clientVisual) {
        clientVisual->setPosition(sprite.getPosition().x - 50.0f, sprite.getPosition().y + 20.0f);
        clientVisual->setScale(4.0f, 4.0f);
        esteOcupata = true;
        timer.restart();
    } else {
        esteOcupata = false;
        if (clientLogic) {
            delete clientLogic;
            clientLogic = nullptr;
        }
    }
}

/**
 * @brief Marks that customer's order has been taken
 */
void Masa::preiaComanda() { asteaptaComanda = false; }

/**
 * @brief Delivers food to the customer
 */
void Masa::primesteMancare(AssetManager<sf::Texture> &textures, int tip) {
    areMancare = true;
    timer.restart();

    plateSprite.setTexture(textures.get("farfurie"));
    plateSprite.setScale(2.5f, 2.5f);
    sf::FloatRect boundsP = plateSprite.getLocalBounds();
    plateSprite.setOrigin(boundsP.width / 2.0f, boundsP.height / 2.0f);
    plateSprite.setPosition(sprite.getPosition());

    if (tip == 0) foodSprite.setTexture(textures.get("item_peste"));
    else foodSprite.setTexture(textures.get("item_suc"));

    foodSprite.setScale(2.0f, 2.0f);
    sf::FloatRect boundsF = foodSprite.getLocalBounds();
    foodSprite.setOrigin(boundsF.width / 2.0f, boundsF.height / 2.0f);
    foodSprite.setPosition(plateSprite.getPosition().x, plateSprite.getPosition().y - 10.0f);

    if (clientLogic) {
        clientLogic->esteServit(5.0f, 0.0f);
    }
}

/**
 * @brief Updates table state each frame (ordering, eating, payment)
 */
void Masa::updateLogic(float dt, AssetManager<sf::Texture> &textures, int &baniTotal) {
    if (clientVisual != nullptr && clientLogic != nullptr) {
        clientLogic->actualizeaza_stare(dt);

        if (clientLogic->a_plecat_suparat()) {
            std::cout << "[Masa] Clientul a plecat suparat!\n";
            delete clientVisual;
            clientVisual = nullptr;
            delete clientLogic;
            clientLogic = nullptr;
            esteOcupata = false;
            asteaptaComanda = false;
            areMancare = false;
            return;
        }

        if (!asteaptaComanda && !areMancare) {
            if (timer.getElapsedTime().asSeconds() > 2.0f && tipProdus == -1) {
                asteaptaComanda = true;
                tipProdus = std::rand() % 2;

                bubbleSprite.setTexture(textures.get("bubble"));
                bubbleSprite.setScale(3.0f, 3.0f);
                bubbleSprite.setPosition(clientVisual->getPosition().x - 35.0f, clientVisual->getPosition().y - 120.0f);

                if (tipProdus == 0) foodSprite.setTexture(textures.get("item_peste"));
                else foodSprite.setTexture(textures.get("item_suc"));

                foodSprite.setOrigin(0, 0);
                foodSprite.setScale(1.7f, 1.7f);
                sf::FloatRect bounds = foodSprite.getLocalBounds();
                foodSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
                foodSprite.setPosition(bubbleSprite.getPosition().x + 80.0f, bubbleSprite.getPosition().y + 60.0f);
            }
        }

        if (areMancare) {
            if (timer.getElapsedTime().asSeconds() > 5.0f) {
                delete clientVisual;
                clientVisual = nullptr;
                areMancare = false;
                tipProdus = -1;
                esteOcupata = false;

                afiseazaBani = true;
                moneySprite.setTexture(textures.get("bani"));
                moneySprite.setScale(2.0f, 2.0f);
                moneySprite.setOrigin(moneySprite.getLocalBounds().width / 2.0f,
                                      moneySprite.getLocalBounds().height / 2.0f);
                moneySprite.setPosition(sprite.getPosition());
                timer.restart();
            }
        }
    }

    if (afiseazaBani) {
        if (timer.getElapsedTime().asSeconds() > 2.0f) {
            afiseazaBani = false;

            if (clientLogic) {
                int notaFinala = 50;

                if (auto *bogat = dynamic_cast<Pinguin_Bogat *>(clientLogic)) {
                    bogat->lasa_bacsis_extra();
                    notaFinala = 100;
                } else if (auto *student = dynamic_cast<Pinguin_Student *>(clientLogic)) {
                    student->primeste_reducere();
                    notaFinala = 30;
                } else if (dynamic_cast<Pinguin_Influencer *>(clientLogic)) {
                    notaFinala = 10;
                } else if (dynamic_cast<Pinguin_Afacerist *>(clientLogic)) {
                    notaFinala = 60;
                }

                baniTotal += notaFinala;
                std::cout << "[JOC] Incasat: " << notaFinala << "$\n";

                delete clientLogic;
                clientLogic = nullptr;
            }
        }
    }
}

/**
 * @brief Renders food, plates, and money on the table
 */
void Masa::drawItems(sf::RenderWindow &window) const {
    if (areMancare) {
        window.draw(plateSprite);
        window.draw(foodSprite);
    }
    if (afiseazaBani) { window.draw(moneySprite); }
}

/**
 * @brief Renders UI elements like speech bubbles
 */
void Masa::drawUI(sf::RenderWindow &window) const {
    if (clientVisual && asteaptaComanda) {
        window.draw(bubbleSprite);
        window.draw(foodSprite);
    }
}
