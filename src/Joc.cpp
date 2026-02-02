/**
 * @file Joc.cpp
 * @brief Implements the core game loop, rendering, and interaction logic.
 */
#include "../header/Joc.hpp"
#include "../header/Utils.hpp"

#include "../header/Pinguini_Derivati.hpp"
#include "../header/Cronometru_Rabdare.hpp"
#include "../header/Comanda.hpp"
#include "../header/Produs_Meniu.hpp"
#include "../header/Exceptii.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

/**
 * @brief Helper function to find the closest access point around a table
 *
 * Tables have four access points (north, south, west, east). This function
 * finds which one is closest to Penny's current position.
 *
 * @param centruMasa Center position of the table
 * @param pozitiePenny Current position of Penny character
 * @return The closest access point coordinates
 */
sf::Vector2f gasestePunctAcces(sf::Vector2f centruMasa, sf::Vector2f pozitiePenny) {
    std::vector<sf::Vector2f> puncte = {
        {centruMasa.x, centruMasa.y + 55.0f},
        {centruMasa.x, centruMasa.y - 55.0f},
        {centruMasa.x - 110.0f, centruMasa.y},
        {centruMasa.x + 90.0f, centruMasa.y}
    };

    sf::Vector2f celMaiApropiat = puncte[0];
    float distMin = 100000.0f;

    for (const auto &p: puncte) {
        float d = calculDistanta(pozitiePenny, p);
        if (d < distMin) {
            distMin = d;
            celMaiApropiat = p;
        }
    }
    return celMaiApropiat;
}

/**
 * @brief Helper struct for depth-sorting visual objects
 *
 * Used to sort sprites by Y position for proper visual layering.
 */
struct ObiectVizual {
    sf::Sprite *s; ///< Pointer to sprite
    float y; ///< Y coordinate for sorting
};

/**
 * @brief Constructs the game, initializes window and loads all resources
 */
Joc::Joc(ConfigManager &cfg)
    : window(sf::VideoMode(800, 600), "Penguin Diner: Final"),
      config(cfg),
      vitezaPenny(0.0f) {
    window.setFramerateLimit(60);
    incarcaResurse();
    initializareScena();
}

/**
 * @brief Destructor cleaning up customer objects
 */
Joc::~Joc() {
    for (auto *c: coadaLogica) delete c;
    delete logicInMana;
}

/**
 * @brief Loads all game assets (textures and fonts) from files
 */
void Joc::incarcaResurse() {
    textures.load("background", "assets/background.png");
    textures.get("background").setSmooth(true);

    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "EROARE: Nu am gasit assets/arial.ttf! Textul nu va merge.\n";
    }

    std::vector<std::string> assets = {
        "penny", "masa", "kitchen", "covor", "farfurie", "bani",
        "c_student", "c_afacerist", "c_bogat", "c_influencer",
        "bubble", "item_peste", "item_suc", "gunoi"
    };

    for (const auto &asset: assets) {
        std::string path = "assets/";
        if (asset == "c_student") path += "pinguin_student.png";
        else if (asset == "c_afacerist") path += "pinguin_afacerist.png";
        else if (asset == "c_bogat") path += "pinguin_bogat.png";
        else if (asset == "c_influencer") path += "pinguin_influencer.png";
        else if (asset == "kitchen") path += "bucatarie.png";
        else path += asset + ".png";

        textures.load(asset, path);
        textures.get(asset).setSmooth(false);
    }
}

/**
 * @brief Initializes all game objects, sprites, and UI elements
 */
void Joc::initializareScena() {
    textBani.setFont(font);
    textBani.setCharacterSize(28);
    textBani.setFillColor(sf::Color::White);
    textBani.setOutlineColor(sf::Color::Black);
    textBani.setOutlineThickness(2.0f);
    textBani.setStyle(sf::Text::Bold);
    textBani.setPosition(20.0f, 20.0f);
    textBani.setString("Bani: $0");

    penguinFactory = std::make_unique<PenguinFactory>(textures);

    background.setTexture(textures.get("background"));
    float scaleX = 800.0f / background.getLocalBounds().width;
    float scaleY = 600.0f / background.getLocalBounds().height;
    background.setScale(scaleX, scaleY);

    kitchen.setTexture(textures.get("kitchen"));
    kitchen.setScale(6.0f, 6.0f);

    sf::Vector2f kPosOrig = config.getVector("KITCHEN");
    kitchen.setPosition(kPosOrig.x - 75.0f, kPosOrig.y - 90.0f);

    trashBin.setTexture(textures.get("gunoi"));
    trashBin.setScale(3.5f, 3.5f);
    trashBin.setPosition(kitchen.getPosition().x + (kitchen.getLocalBounds().width * 4.0f) + 490.0f,
                         kPosOrig.y + 100.0f);

    covor.setTexture(textures.get("covor"));
    covor.setScale(4.5f, 4.0f);
    covor.setPosition(config.getVector("COVOR"));

    penny.setTexture(textures.get("penny"));
    penny.setScale(4.0f, 4.0f);
    penny.setOrigin(16.0f, 16.0f);
    penny.setPosition(400.0f, 300.0f);
    targetPosition = penny.getPosition();

    vitezaPenny = config.getFloat("PENNY_SPEED");

    for (int i = 1; i <= 5; ++i) {
        std::string key = "TABLE_" + std::to_string(i);
        mese.emplace_back(textures.get("masa"), config.getVector(key));
    }

    spriteFarfurieCarata.setTexture(textures.get("farfurie"));
    spriteFarfurieCarata.setScale(2.0f, 2.0f);

    spriteFarfurieTejghea.setTexture(textures.get("farfurie"));
    spriteFarfurieTejghea.setScale(2.0f, 2.0f);

    spriteFarfurieTejghea.setPosition(kitchen.getPosition().x + 100.0f, kitchen.getPosition().y + 150.0f);

    timerSpawn.restart();
    timpUrmatorSpawn = static_cast<float>(std::rand() % 3000 + 1000) / 1000.0f;
}

/**
 * @brief Processes window events and user input
 */
void Joc::handleInput() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            procesareClick(sf::Mouse::getPosition(window));
        }
    }
}

/**
 * @brief Spawns a new random customer and adds them to the waiting queue
 */
void Joc::spawnClient() {
    if (static_cast<int>(coadaAsteptare.size()) < 4) {
        std::vector<std::string> tipuri = {"student", "afacerist", "bogat", "influencer"};
        int idx = std::rand() % static_cast<int>(tipuri.size());
        const std::string &tipAles = tipuri[idx];

        float startY = config.getFloat("START_COADA_Y");
        sf::Sprite *c = penguinFactory->createPenguin(tipAles, -60.0f, startY);

        Cronometru_Rabdare cronometru(60.0f, 1.0f);
        Produs_Meniu produs("Asteptare", 0.0, 0);
        Comanda comanda(produs, 0);

        Client_Pinguin *logic = nullptr;

        if (tipAles == "student") logic = new Pinguin_Student(cronometru, comanda);
        else if (tipAles == "afacerist") {
            Cronometru_Rabdare cronometruRapid(30.0f, 1.5f);
            logic = new Pinguin_Afacerist(cronometruRapid, comanda);
        } else if (tipAles == "bogat") logic = new Pinguin_Bogat(cronometru, comanda);
        else logic = new Pinguin_Influencer(cronometru, comanda);

        coadaAsteptare.push_back(c);
        coadaLogica.push_back(logic);

        rearanjareCoada = true;
        timerCoada.restart();
    } else {
        try {
            throw Eroare_Restaurant_Plin(4);
        } catch (const Eroare_Restaurant_Plin &e) {
            std::cout << "[INFO] " << e.what() << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "[CRITIC] Eroare neasteptata la spawn: " << e.what() << std::endl;
        }
    }
}

/**
 * @brief Processes mouse clicks to set movement targets and interactions
 */
void Joc::procesareClick(sf::Vector2i pixelPos) {
    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

    if (clientInMana != nullptr) {
        for (size_t i = 0; i < mese.size(); ++i) {
            if (mese[i].getSprite().getGlobalBounds().contains(mousePos)) {
                targetPosition = gasestePunctAcces(mese[i].getSprite().getPosition(), penny.getPosition());
                indexMasaTinta = static_cast<int>(i);
                mergeLaBucatarie = false;
                clientTinta = nullptr;
                mergeLaGunoi = false;
                return;
            }
        }
        return;
    }

    if (mancareInMana != -1) {
        for (size_t i = 0; i < mese.size(); ++i) {
            if (mese[i].getSprite().getGlobalBounds().contains(mousePos)) {
                targetPosition = gasestePunctAcces(mese[i].getSprite().getPosition(), penny.getPosition());
                indexMasaTinta = static_cast<int>(i);
                mergeLaBucatarie = false;
                clientTinta = nullptr;
                mergeLaGunoi = false;
                return;
            }
        }

        if (trashBin.getGlobalBounds().contains(mousePos)) {
            sf::Vector2f binPos = trashBin.getPosition();
            targetPosition = {binPos.x - 20.0f, binPos.y + 60.0f};

            mergeLaGunoi = true;
            mergeLaBucatarie = false;
            indexMasaTinta = -1;
            clientTinta = nullptr;
            return;
        }
        return;
    }

    bool amLocLaMasa = false;
    for (const auto &m: mese) {
        if (m.getClientVisual() == nullptr) {
            amLocLaMasa = true;
            break;
        }
    }

    if (amLocLaMasa) {
        for (auto *client: coadaAsteptare) {
            if (client->getGlobalBounds().contains(mousePos)) {
                targetPosition = client->getPosition();
                clientTinta = client;
                indexMasaTinta = -1;
                mergeLaBucatarie = false;
                mergeLaGunoi = false;
                return;
            }
        }
    }

    if (kitchen.getGlobalBounds().contains(mousePos)) {
        sf::Vector2f kPos = kitchen.getPosition();
        targetPosition = {kPos.x + 220.0f, kPos.y + 185.0f};

        mergeLaBucatarie = true;
        indexMasaTinta = -1;
        clientTinta = nullptr;
        mergeLaGunoi = false;
        return;
    }

    for (size_t i = 0; i < mese.size(); ++i) {
        if (mese[i].getSprite().getGlobalBounds().contains(mousePos)) {
            targetPosition = gasestePunctAcces(mese[i].getSprite().getPosition(), penny.getPosition());
            indexMasaTinta = static_cast<int>(i);
            mergeLaBucatarie = false;
            clientTinta = nullptr;
            mergeLaGunoi = false;
            return;
        }
    }
}

/**
 * @brief Updates all game logic including movement, timers, and customer state
 */
void Joc::update(float dt) {
    textBani.setString("Bani: $" + std::to_string(bani));

    if (static_cast<int>(coadaAsteptare.size()) < 4) {
        if (timerSpawn.getElapsedTime().asSeconds() > timpUrmatorSpawn) {
            spawnClient();
            timpUrmatorSpawn = static_cast<float>(std::rand() % 3000 + 2000) / 1000.0f;
            timerSpawn.restart();
        }
    }

    if (rearanjareCoada) {
        if (timerCoada.getElapsedTime().asSeconds() > 0.3f) {
            bool totiAuAjuns = true;
            float startX = config.getFloat("START_COADA_X");
            float startY = config.getFloat("START_COADA_Y");

            for (size_t i = 0; i < coadaAsteptare.size(); ++i) {
                float targetX = startX - static_cast<float>(i) * 55.0f;
                float currentX = coadaAsteptare[i]->getPosition().x;

                if (std::abs(currentX - targetX) > 4.0f) {
                    float directie = (targetX > currentX) ? 1.0f : -1.0f;
                    coadaAsteptare[i]->move(directie * 300.0f * dt, 0.0f);
                    totiAuAjuns = false;
                } else {
                    coadaAsteptare[i]->setPosition(targetX, startY);
                }
            }
            if (totiAuAjuns) rearanjareCoada = false;
        }
    }

    if (!comenziInLucru.empty()) {
        if (timerGatit.getElapsedTime().asSeconds() > 3.0f) {
            int mancareGata = comenziInLucru[0];
            comenziInLucru.erase(comenziInLucru.begin());
            comenziPeTejghea.push_back(mancareGata);
            timerGatit.restart();
        }
    } else {
        timerGatit.restart();
    }

    if (!comenziPeTejghea.empty()) {
        int mancareCurenta = comenziPeTejghea[0];
        if (mancareCurenta == 0) spriteMancareTejghea.setTexture(textures.get("item_peste"));
        else spriteMancareTejghea.setTexture(textures.get("item_suc"));

        spriteMancareTejghea.setScale(2.0f, 2.0f);
        float kX = kitchen.getPosition().x;
        float kY = kitchen.getPosition().y;
        spriteFarfurieTejghea.setPosition(kX + 100.0f, kY + 150.0f);
        spriteMancareTejghea.setPosition(spriteFarfurieTejghea.getPosition().x + 15.0f,
                                         spriteFarfurieTejghea.getPosition().y + 5.0f);
    }

    for (auto &i: mese) {
        i.updateLogic(dt, textures, bani);
    }

    sf::Vector2f posCurenta = penny.getPosition();
    if (calculDistanta(posCurenta, targetPosition) > 5.0f) {
        sf::Vector2f directie = (targetPosition - posCurenta) / calculDistanta(posCurenta, targetPosition);
        penny.move(directie * vitezaPenny * dt);
    } else {
        actiuniLaDestinatie();
    }

    if (clientInMana) {
        clientInMana->setPosition(penny.getPosition().x + 60.0f, penny.getPosition().y);
    }
    if (mancareInMana != -1) {
        if (mancareInMana == 0) spriteMancareCarata.setTexture(textures.get("item_peste"));
        else spriteMancareCarata.setTexture(textures.get("item_suc"));

        spriteMancareCarata.setScale(2.0f, 2.0f);
        spriteMancareCarata.setOrigin(0, 0);
        spriteFarfurieCarata.setOrigin(0, 0);
        spriteMancareCarata.setPosition(penny.getPosition().x + 25.0f, penny.getPosition().y - 20.0f);
        spriteFarfurieCarata.setPosition(penny.getPosition().x + 10.0f, penny.getPosition().y - 25.0f);
    }
}

/**
 * @brief Executes appropriate actions when Penny reaches her destination
 */
void Joc::actiuniLaDestinatie() {
    if (clientTinta != nullptr) {
        auto it = std::find(coadaAsteptare.begin(), coadaAsteptare.end(), clientTinta);
        int index = static_cast<int>(std::distance(coadaAsteptare.begin(), it));

        clientInMana = coadaAsteptare[index];
        logicInMana = coadaLogica[index];

        clientTinta = nullptr;
        coadaAsteptare.erase(it);
        coadaLogica.erase(coadaLogica.begin() + index);

        rearanjareCoada = true;
        timerCoada.restart();
        timerSpawn.restart();
    }

    if (mergeLaBucatarie) {
        if (!comenziPeTejghea.empty() && mancareInMana == -1) {
            mancareInMana = comenziPeTejghea[0];
            comenziPeTejghea.erase(comenziPeTejghea.begin());
        }
        mergeLaBucatarie = false;
    }

    if (mergeLaGunoi) {
        if (mancareInMana != -1) {
            std::cout << "[PENNY] Ajuns la cos. Mancare aruncata.\n";
            mancareInMana = -1;
        }
        mergeLaGunoi = false;
    }

    if (indexMasaTinta != -1) {
        Masa &m = mese[indexMasaTinta];

        if (clientInMana != nullptr) {
            try {
                if (m.isOcupata() || m.isAfiseazaBani()) {
                    throw Eroare_Masa_Ocupata(indexMasaTinta + 1);
                }

                m.setClient(clientInMana, logicInMana);
                clientInMana = nullptr;
                logicInMana = nullptr;
            } catch (const Eroare_Masa_Ocupata &e) {
                std::cerr << "[EXCEPTIE GAMEPLAY] " << e.what() << std::endl;
            } catch (const std::exception &e) {
                std::cerr << "[EROARE GENERICA] " << e.what() << std::endl;
            }
        } else if (m.isAsteaptaComanda() && mancareInMana == -1) {
            m.preiaComanda();
            comenziInLucru.push_back(m.getTipProdus());
        } else if (mancareInMana != -1) {
            try {
                if (m.getClientVisual() == nullptr) {
                    throw Eroare_Actiune_Interzisa("Masa este goala! Nu ai cui sa servesti.");
                }
                if (m.isAsteaptaComanda()) {
                    throw Eroare_Actiune_Interzisa("Clientul inca nu a dat comanda! Ia comanda intai.");
                }
                if (m.isAreMancare()) {
                    throw Eroare_Actiune_Interzisa("Clientul are deja mancare!");
                }
                if (m.getTipProdus() != mancareInMana) {
                    throw Eroare_Actiune_Interzisa("Produs gresit! Clientul a cerut altceva.");
                }

                m.primesteMancare(textures, mancareInMana);
                mancareInMana = -1;
            } catch (const Eroare_Joc &e) {
                std::cerr << "[EXCEPTIE SERVIRE] " << e.what() << std::endl;
            }
        }

        indexMasaTinta = -1;
    }
}

/**
 * @brief Renders all game objects with depth sorting
 */
void Joc::render() {
    window.clear(sf::Color::Black);
    window.draw(background);
    window.draw(covor);

    std::vector<ObiectVizual> lista;
    lista.push_back({&penny, penny.getPosition().y});
    lista.push_back({&kitchen, kitchen.getPosition().y});
    lista.push_back({&trashBin, trashBin.getPosition().y});

    for (auto *c: coadaAsteptare) lista.push_back({c, c->getPosition().y});
    for (auto &m: mese) {
        lista.push_back({&m.getSprite(), m.getSprite().getPosition().y});

        if (m.getClientVisual()) {
            lista.push_back({m.getClientVisual(), m.getClientVisual()->getPosition().y});
        }
    }

    std::sort(lista.begin(), lista.end(), [](const ObiectVizual &a, const ObiectVizual &b) {
        return a.y < b.y;
    });

    for (auto &obj: lista) {
        window.draw(*obj.s);
        if (obj.s == &penny) {
            if (clientInMana) window.draw(*clientInMana);
            if (mancareInMana != -1) {
                window.draw(spriteFarfurieCarata);
                window.draw(spriteMancareCarata);
            }
        }
        for (auto &m: mese) {
            if (obj.s == &m.getSprite()) {
                m.drawItems(window);
            }
        }
        if (obj.s == &kitchen) {
            int maxItems = std::min(static_cast<int>(comenziPeTejghea.size()), 3);
            for (int i = 0; i < maxItems; i++) {
                int tipMancare = comenziPeTejghea[i];
                float posX = (kitchen.getPosition().x + 200.0f) - (static_cast<float>(i) * 50.0f);
                float posY = kitchen.getPosition().y + 200.0f;

                spriteFarfurieTejghea.setPosition(posX, posY);
                window.draw(spriteFarfurieTejghea);

                if (tipMancare == 0) spriteMancareTejghea.setTexture(textures.get("item_peste"));
                else spriteMancareTejghea.setTexture(textures.get("item_suc"));

                spriteMancareTejghea.setOrigin(0, 0);
                spriteMancareTejghea.setScale(2.0f, 2.0f);
                spriteMancareTejghea.setPosition(posX + 15.0f, posY + 5.0f);
                window.draw(spriteMancareTejghea);
            }
        }
    }

    for (auto &m: mese) {
        m.drawUI(window);
    }

    window.draw(textBani);
    window.display();
}

/**
 * @brief Main game loop running until window is closed
 */
void Joc::run() {
    while (window.isOpen()) {
        float dt = ceasGlobal.restart().asSeconds();
        window.setTitle("Penguin Diner | OOP Project");
        handleInput();
        update(dt);
        render();
    }
}
