//
// Created by Valiv on 11/11/2025.
//

#include "Produs_Meniu.hpp"
#include <utility>

Produs_Meniu::Produs_Meniu(std::string nume_produs, double pret, int timp_preparare)
    : nume_produs(std::move(nume_produs)),
      pret(pret),
      timp_preparare(timp_preparare) {}

const std::string& Produs_Meniu::getnume_produs() const {
    return nume_produs;
}

double Produs_Meniu::getpret() const {
    return pret;
}

int Produs_Meniu::gettimp_preparare() const {
    return timp_preparare;
}

double Produs_Meniu::pret_cu_bacsis(float procent_bacsis) const {
    if (procent_bacsis < 0.0f) {
        return pret;
    }
    return pret * (1.0 + procent_bacsis);
}

std::ostream& operator<<(std::ostream& os, const Produs_Meniu& art) {
    os << "Articol: " << art.nume_produs
       << " (Pret: " << art.pret
       << ", Timp: " << art.timp_preparare << "s)";
    return os;
}