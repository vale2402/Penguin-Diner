/**
 * @file Restaurant.cpp
 * @brief Implements the restaurant management logic: seating, service, and promotions.
 */
#include "../header/Restaurant.hpp"
#include <algorithm>
#include "../header/Exceptii.hpp"
#include "../header/Pinguini_Derivati.hpp"

/**
 * @brief Constructs a restaurant with specified capacity
 *
 * Reserves space in the vector for efficiency.
 */
Restaurant::Restaurant(int capacitate) : capacitate_maxima(capacitate) {
    mese.reserve(capacitate);
}

/**
 * @brief Destructor that properly deletes all customer objects
 *
 * Prevents memory leaks by deleting dynamically allocated customers.
 */
Restaurant::~Restaurant() {
    std::cout << "[Restaurant] Se inchide, dam afara clientii.\n";
    for (auto *client: mese) {
        delete client;
    }
    mese.clear();
}

/**
 * @brief Copy constructor performing deep copy of customers
 *
 * Uses the clone() method to create independent copies of all customers.
 */
Restaurant::Restaurant(const Restaurant &other)
    : capacitate_maxima(other.capacitate_maxima) {
    std::cout << "[Restaurant] Se deschide o franciza (Copiere)\n";

    for (const auto *client: other.mese) {
        mese.push_back(client->clone());
    }
}

/**
 * @brief Swaps contents of two restaurants efficiently
 *
 * Used by copy-and-swap idiom in assignment operator.
 */
void swap(Restaurant &r1, Restaurant &r2) noexcept {
    using std::swap;
    swap(r1.mese, r2.mese);
    swap(r1.capacitate_maxima, r2.capacitate_maxima);
}

/**
 * @brief Copy assignment operator using copy-and-swap idiom
 *
 * Provides strong exception guarantee.
 */
Restaurant &Restaurant::operator=(Restaurant other) {
    std::cout << "[Restaurant] Preluare management (Operator=)\n";
    swap(*this, other);
    return *this;
}

/**
 * @brief Adds a new customer to the restaurant
 *
 * @throws Eroare_Restaurant_Plin if restaurant is at maximum capacity
 */
void Restaurant::primeste_client(Client_Pinguin *client_nou) {
    if (static_cast<int>(mese.size()) >= capacitate_maxima) {
        delete client_nou;
        throw Eroare_Restaurant_Plin(capacitate_maxima);
    }
    mese.push_back(client_nou);
}

/**
 * @brief Simulates passage of time for all seated customers
 *
 * Updates patience timers and checks for customers leaving.
 */
void Restaurant::simuleaza_tura(float timp_scurs) const {
    for (auto *client: mese) {
        client->actualizeaza_stare(timp_scurs);
    }
}

/**
 * @brief Seats a customer at a specific table
 *
 * @throws std::out_of_range if index is invalid
 * @throws Eroare_Masa_Ocupata if restaurant is full
 */
void Restaurant::aseaza_la_masa(int index, Client_Pinguin *client) {
    if (index < 0 || index >= capacitate_maxima) {
        delete client;
        throw std::out_of_range("Index masa invalid");
    }
    if (static_cast<int>(mese.size()) >= capacitate_maxima) {
        delete client;
        throw Eroare_Masa_Ocupata(static_cast<int>(mese.size()) + 1);
    }
    mese.push_back(client);
}

/**
 * @brief Serves food to a customer at specified table
 *
 * @throws std::out_of_range if index is out of bounds
 * @throws Eroare_Actiune_Interzisa if customer has already left angry
 */
void Restaurant::serveste_client(int index) const {
    if (index < 0 || index >= static_cast<int>(mese.size())) {
        throw std::out_of_range("Nu exista client la masa " + std::to_string(index));
    }

    Client_Pinguin *c = mese[index];

    if (c->a_plecat_suparat()) {
        throw Eroare_Actiune_Interzisa("Client Suparat");
    }
    c->esteServit(20.0f, 1.0f);
}

/**
 * @brief Applies student discount promotion to all student customers
 *
 * Uses RTTI (dynamic_cast) to identify student customers specifically.
 */
void Restaurant::aplica_promotie_studenti() const {
    std::cout << "[Eveniment] Oferta: 10% Reducere pentru toti studentii din restaurant!\n";

    bool gasit = false;
    for (auto *client: mese) {
        if (const auto *student = dynamic_cast<Pinguin_Student *>(client); student != nullptr) {
            student->primeste_reducere();
            gasit = true;
        }
    }

    if (!gasit) {
        std::cout << " Nu sunt studenti in restaurant momentan.\n";
    }
    std::cout << "\n";
}

/**
 * @brief Outputs restaurant state to stream
 *
 * Shows capacity, current occupancy, and all seated customers.
 */
std::ostream &operator<<(std::ostream &os, const Restaurant &restaurant) {
    os << "Capacitate: " << restaurant.mese.size() << "/" << restaurant.capacitate_maxima << "\n";
    os << "Clienti la mese:\n";
    if (restaurant.mese.empty()) {
        os << "  (Gol)\n";
    } else {
        for (const auto *client: restaurant.mese) {
            os << *client;
        }
    }
    return os;
}
