//
// Created by Valiv on 07/12/2025.
//

#include "Pinguini_Derivati.hpp"

// Implementare student
Pinguin_Student::Pinguin_Student(const Cronometru_Rabdare& timer, const Comanda& cmd)
    : Client_Pinguin(timer, cmd, "Student") {
}

Client_Pinguin* Pinguin_Student::clone() const {
    return new Pinguin_Student(*this);
}

void Pinguin_Student::primeste_reducere() const {
    double pret_vechi = comanda_client.getprodus_meniu().getpret();
    double pret_nou = pret_vechi * 0.90; // 10% reducere

    std::cout << " [Student] " << tip_pinguin << " " << ID_Pinguin
              << " prezinta carnetul de student.\n"
              << "  Pret initial: " << pret_vechi << " RON -> Pret cu reducere: " << pret_nou << " RON.\n";
}

void Pinguin_Student::do_reactioneaza_la_timp(float timp_scurs) {
    Client_Pinguin::do_reactioneaza_la_timp(timp_scurs);
}

void Pinguin_Student::afiseaza_detalii(std::ostream& os) const {
    os << "[Student] ";
    Client_Pinguin::afiseaza_detalii(os);
}


// Implementare afacerist
Pinguin_Afacerist::Pinguin_Afacerist(const Cronometru_Rabdare& timer, const Comanda& cmd)
    : Client_Pinguin(timer, cmd, "Afacerist") {
}

Client_Pinguin* Pinguin_Afacerist::clone() const {
    return new Pinguin_Afacerist(*this);
}

void Pinguin_Afacerist::do_reactioneaza_la_timp(float timp_scurs) {
    Client_Pinguin::do_reactioneaza_la_timp(timp_scurs * 2.0f);
}

void Pinguin_Afacerist::afiseaza_detalii(std::ostream& os) const {
    os << "[Afacerist] ";
    Client_Pinguin::afiseaza_detalii(os);
}


// Implementare influencer
Pinguin_Influencer::Pinguin_Influencer(const Cronometru_Rabdare& timer, const Comanda& cmd)
    : Client_Pinguin(timer, cmd, "Influencer") {
}

Client_Pinguin* Pinguin_Influencer::clone() const {
    return new Pinguin_Influencer(*this);
}

void Pinguin_Influencer::do_reactioneaza_la_timp(float timp_scurs) {
    Client_Pinguin::do_reactioneaza_la_timp(timp_scurs * 0.5f);
}

void Pinguin_Influencer::afiseaza_detalii(std::ostream& os) const {
    os << "[Influencer] ";
    Client_Pinguin::afiseaza_detalii(os);
}


// Implementare bogat
Pinguin_Bogat::Pinguin_Bogat(const Cronometru_Rabdare& timer, const Comanda& cmd)
    : Client_Pinguin(timer, cmd, "Bogat") {
}

Client_Pinguin* Pinguin_Bogat::clone() const {
    return new Pinguin_Bogat(*this);
}

void Pinguin_Bogat::do_reactioneaza_la_timp(float timp_scurs) {
    Client_Pinguin::do_reactioneaza_la_timp(timp_scurs);
}

void Pinguin_Bogat::lasa_bacsis_extra() const {
    double pret = comanda_client.getprodus_meniu().getpret();
    double bonus = pret * 0.25; // 25%
    double total = pret + bonus;

    std::cout << "[Bogat] " << tip_pinguin << " " << ID_Pinguin
              << " e generos! Lasa 25% bacsis.\n"
              << "  Nota: " << pret << " + " << bonus << " (Tip) = " << total << " RON.\n";
}

void Pinguin_Bogat::afiseaza_detalii(std::ostream& os) const {
    os << "[Bogatas] ";
    Client_Pinguin::afiseaza_detalii(os);
}