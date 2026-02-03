/**
 * @file Client_Pinguin.cpp
 * @brief Implements the base penguin client behaviors and state transitions.
 */
#include "../header/Client_Pinguin.hpp"

/**
 * @brief Static counter for assigning unique IDs to customers
 */
int Client_Pinguin::contor_global_clienti = 0;

/**
 * @brief Constructs a penguin customer with timer, order, and type
 *
 * Assigns a unique ID from the global counter.
 */
Client_Pinguin::Client_Pinguin(const Cronometru_Rabdare &cronometru, Comanda comanda_client, std::string tip)
    : ID_Pinguin(++contor_global_clienti),
      cronometru(cronometru),
      comanda_client(std::move(comanda_client)),
      plecat_suparat(false),
      tip_pinguin(std::move(tip)) {
    std::cout << "Constructor Baza: S-a nascut un " << tip_pinguin << " (ID: " << ID_Pinguin << ")\n";
}

/**
 * @brief Virtual destructor for proper cleanup of derived classes
 */
Client_Pinguin::~Client_Pinguin() {
    std::cout << "Destructor Baza: " << tip_pinguin << " " << ID_Pinguin << " pleaca acasa.\n";
}

/**
 * @brief Copy constructor creating a duplicate customer
 */
Client_Pinguin::Client_Pinguin(const Client_Pinguin &other)
    : ID_Pinguin(other.ID_Pinguin),
      cronometru(other.cronometru),
      comanda_client(other.comanda_client),
      plecat_suparat(other.plecat_suparat),
      tip_pinguin(other.tip_pinguin) {
    std::cout << "Copy Constructor Baza: Copiere " << other.ID_Pinguin << "\n";
}

/**
 * @brief Copy assignment operator
 */
Client_Pinguin &Client_Pinguin::operator=(const Client_Pinguin &other) {
    if (this != &other) {
        ID_Pinguin = other.ID_Pinguin;
        cronometru = other.cronometru;
        comanda_client = other.comanda_client;
        plecat_suparat = other.plecat_suparat;
        tip_pinguin = other.tip_pinguin;
    }
    std::cout << "Operator= Baza\n";
    return *this;
}

/**
 * @brief Updates customer state based on elapsed time
 *
 * Skips update if customer has already left or order is completed.
 */
void Client_Pinguin::actualizeaza_stare(float timp_scurs) {
    if (plecat_suparat || comanda_client.getstare_comanda()) {
        return;
    }
    do_reactioneaza_la_timp(timp_scurs);
}

/**
 * @brief Base implementation of patience reaction
 *
 * Can be overridden by derived classes to modify patience decay behavior.
 */
void Client_Pinguin::do_reactioneaza_la_timp(float timp_scurs) {
    if (cronometru.actualizeaza(timp_scurs)) {
        plecat_suparat = true;
        std::cout << "!!! " << tip_pinguin << " " << ID_Pinguin << " si-a pierdut rabdarea! !!!\n";
    }
}

/**
 * @brief Marks customer as served and starts eating timer
 *
 * Resets the patience timer to track eating time instead of waiting time.
 */
void Client_Pinguin::esteServit(float timpDeMancat, float rataScadereMancat) {
    if (plecat_suparat) return;

    std::cout << "> " << tip_pinguin << " " << ID_Pinguin << " servit. Mnam mnam.\n";
    cronometru = Cronometru_Rabdare(timpDeMancat, rataScadereMancat);
    this->comanda_client.finalizeaza_comanda();
}

/**
 * @brief Checks if customer left angry/unsatisfied
 *
 * @return true if customer left without being served in time
 */
bool Client_Pinguin::a_plecat_suparat() const {
    return plecat_suparat;
}

/**
 * @brief Base implementation for displaying customer details
 *
 * Can be overridden by derived classes to add type-specific information.
 */
void Client_Pinguin::afiseaza_detalii(std::ostream &os) const {
    os << "Client [" << tip_pinguin << "] ID: " << ID_Pinguin
            << " | Suparat: " << (plecat_suparat ? "DA" : "NU") << "\n"
            << "   " << cronometru << "\n"
            << "   " << comanda_client;
}

/**
 * @brief Stream insertion operator for customer output
 */
std::ostream &operator<<(std::ostream &os, const Client_Pinguin &client) {
    os << "-\n";
    client.afiseaza_detalii(os);
    os << "\n-";
    return os;
}
