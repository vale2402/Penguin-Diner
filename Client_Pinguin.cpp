//
// Created by Valiv on 03/12/2025.
//

#include "Client_Pinguin.hpp"


int Client_Pinguin::contor_global_clienti = 0;


//Constructor
Client_Pinguin::Client_Pinguin(const Cronometru_Rabdare &cronometru, Comanda comanda_client, std::string tip)
    : ID_Pinguin(++contor_global_clienti),
      cronometru(cronometru),
      comanda_client(std::move(comanda_client)),
      plecat_suparat(false),
      tip_pinguin(std::move(tip)) {
    std::cout << "Constructor Baza: S-a nascut un " << tip_pinguin << " (ID: " << ID_Pinguin << ")\n";
}

//Destructor Virtual
Client_Pinguin::~Client_Pinguin() {
    std::cout << "Destructor Baza: " << tip_pinguin << " " << ID_Pinguin << " pleaca acasa.\n";
}

//Copy Constructor
Client_Pinguin::Client_Pinguin(const Client_Pinguin& other)
    : ID_Pinguin(other.ID_Pinguin),
      cronometru(other.cronometru),
      comanda_client(other.comanda_client),
      plecat_suparat(other.plecat_suparat),
      tip_pinguin(other.tip_pinguin) {
    std::cout << "Copy Constructor Baza: Copiere " << other.ID_Pinguin << "\n";
}


//Operator=
Client_Pinguin& Client_Pinguin::operator=(const Client_Pinguin& other) {
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

//Non-Virtual Interface
void Client_Pinguin::actualizeaza_stare(float timp_scurs) {
    // Logica comuna: daca e suparat sau servit, nu facem nimic
    if (plecat_suparat || comanda_client.getstare_comanda()) {
        return;
    }
    do_reactioneaza_la_timp(timp_scurs);
}

//Comportamentul general
void Client_Pinguin::do_reactioneaza_la_timp(float timp_scurs) {
    if (cronometru.actualizeaza(timp_scurs)) {
        plecat_suparat = true;
        std::cout << "!!! " << tip_pinguin << " " << ID_Pinguin << " si-a pierdut rabdarea! !!!\n";
    }
}

void Client_Pinguin::esteServit(float timpDeMancat, float rataScadereMancat) {
    if (plecat_suparat) return;

    std::cout << "> " << tip_pinguin << " " << ID_Pinguin << " servit. Mnam mnam.\n";
    cronometru = Cronometru_Rabdare(timpDeMancat, rataScadereMancat);
    this->comanda_client.finalizeaza_comanda();
}

bool Client_Pinguin::a_plecat_suparat() const {
    return plecat_suparat;
}


void Client_Pinguin::afiseaza_detalii(std::ostream& os) const {
    os << "Client [" << tip_pinguin << "] ID: " << ID_Pinguin
       << " | Suparat: " << (plecat_suparat ? "DA" : "NU") << "\n"
       << "   " << cronometru << "\n"
       << "   " << comanda_client;
}

std::ostream& operator<<(std::ostream& os, const Client_Pinguin& client) {
    os << "-\n";
    client.afiseaza_detalii(os);
    os << "\n-\n";
    return os;
}