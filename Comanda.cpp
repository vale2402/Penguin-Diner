//
// Created by Valiv on 03/12/2025.
//

#include "Comanda.hpp"
#include <utility>

#include "Exceptii.hpp"

Comanda::Comanda(Produs_Meniu produs_meniu, int nr_masa)
    : produs_meniu(std::move(produs_meniu)),
      nr_masa(nr_masa),
    stare_comanda(false){
    if (this->produs_meniu.getnume_produs().empty()) {
    throw Eroare_Produs_Indisponibil("Produs Necunoscut");
    }
}

double Comanda::finalizeaza_comanda() {
    this->stare_comanda = true;
    return this->produs_meniu.getpret();
}

const Produs_Meniu& Comanda::getprodus_meniu() const {
    return produs_meniu;
}

int Comanda::getnr_masa() const {
    return nr_masa;
}

bool Comanda::getstare_comanda() const {
    return stare_comanda;
}

std::ostream& operator<<(std::ostream& os, const Comanda& comanda) {
    os << "Comanda pt Masa " << comanda.nr_masa
       << " | " << comanda.produs_meniu
       << " | Gata: " << (comanda.stare_comanda ? "Da" : "Nu");
    return os;
}