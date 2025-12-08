//
// Created by Valiv on 07/12/2025.
//

#include "Restaurant.hpp"
#include <algorithm>
#include "Exceptii.hpp"
#include "Pinguini_Derivati.hpp"

//Constructor
Restaurant::Restaurant(int capacitate) : capacitate_maxima(capacitate) {
    mese.reserve(capacitate);
}

//Destructor
Restaurant::~Restaurant() {
    std::cout << "[Restaurant] Se inchide, dam afara clientii.\n";
    for (auto* client : mese) {
        delete client;
    }
    mese.clear();
}

//Copy Constructor
Restaurant::Restaurant(const Restaurant& other)
    : capacitate_maxima(other.capacitate_maxima) {

    std::cout << "[Restaurant] Se deschide o franciza (Copiere)\n";

    for (const auto* client : other.mese) {
        mese.push_back(client->clone());
    }
}

void swap(Restaurant& r1, Restaurant& r2) noexcept {
    using std::swap;
    swap(r1.mese, r2.mese);
    swap(r1.capacitate_maxima, r2.capacitate_maxima);
}

//Operatorul de atribuire
Restaurant& Restaurant::operator=(Restaurant other) {
    std::cout << "[Restaurant] Preluare management (Operator=)\n";
    swap(*this, other);
    return *this;
}

//Adauga un client la o masa
void Restaurant::primeste_client(Client_Pinguin* client_nou) {
    if (static_cast<int>(mese.size()) >= capacitate_maxima) {
        delete client_nou;
        throw Eroare_Restaurant_Plin(capacitate_maxima);
    }
    mese.push_back(client_nou);
}

//Simuleaza trecerea timpului
void Restaurant::simuleaza_tura(float timp_scurs) const {
    for (auto* client : mese) {
        client->actualizeaza_stare(timp_scurs);
    }
}

void Restaurant::aseaza_la_masa(int index, Client_Pinguin* client) {
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

void Restaurant::serveste_client(int index) const {
    if (index < 0 || index >= static_cast<int>(mese.size())) {
        throw std::out_of_range("Nu exista client la masa " + std::to_string(index));
    }

    Client_Pinguin* c = mese[index];

    if (c->a_plecat_suparat()) {
        throw Eroare_Actiune_Interzisa("Client Suparat");
    }

    c->esteServit(20.0f, 1.0f);
}

void Restaurant::aplica_promotie_studenti() {
    std::cout << "\n[EVENT] Oferta Flash: 10% Reducere pentru toti studentii din restaurant!\n";

    bool gasit = false;
    for (auto* client : mese) {
        auto* student = dynamic_cast<Pinguin_Student*>(client);

        if (student != nullptr) {
            student->primeste_reducere();
            gasit = true;
        }
    }

    if (!gasit) {
        std::cout << " -> Nu sunt studenti in restaurant momentan.\n";
    }
    std::cout << "\n";
}

//Afiseaza starea restaurantului
std::ostream& operator<<(std::ostream& os, const Restaurant& restaurant) {
    os << "RESTAURANT PENGUIN DINER\n";
    os << "Capacitate: " << restaurant.mese.size() << "/" << restaurant.capacitate_maxima << "\n";
    os << "Clienti la mese:\n";
    if (restaurant.mese.empty()) {
        os << "  (Gol)\n";
    } else {
        for (const auto* client : restaurant.mese) {
            os << *client << "\n";
        }
    }
    os << "--\n";
    return os;
}

