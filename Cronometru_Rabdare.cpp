//
// Created by Valiv on 03/12/2025.
//

#include "Cronometru_Rabdare.hpp"
#include <algorithm>

Cronometru_Rabdare::Cronometru_Rabdare(float maxim, float rata)
    : rabdare_actuala(maxim),
      rabdare_maxima(maxim),
      rata_scadere(rata) {}

bool Cronometru_Rabdare::actualizeaza(float timp_scurs) {
    if (rabdare_actuala > 0) {
        rabdare_actuala -= rata_scadere * timp_scurs;
        if (rabdare_actuala <= 0) {
            rabdare_actuala = 0;
            return true;
        }
    }
    return false;
}

void Cronometru_Rabdare::adauga_rabdare(float suma) {
    rabdare_actuala = std::min(rabdare_actuala + suma, rabdare_maxima);
}

bool Cronometru_Rabdare::expirat() const {
    return rabdare_actuala <= 0;
}

std::ostream& operator<<(std::ostream& os, const Cronometru_Rabdare& timer) {
    os << "Rabdare: [" << timer.rabdare_actuala << " / " << timer.rabdare_maxima << "]";
    return os;
}