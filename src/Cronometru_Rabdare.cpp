/**
 * @file Cronometru_Rabdare.cpp
 * @brief Implements the patience timer logic.
 */
#include "../header/Cronometru_Rabdare.hpp"
#include <algorithm>

/**
 * @brief Constructs a patience timer with maximum value and decay rate
 */
Cronometru_Rabdare::Cronometru_Rabdare(float maxim, float rata)
    : rabdare_actuala(maxim),
      rabdare_maxima(maxim),
      rata_scadere(rata) {
}

/**
 * @brief Updates the timer, decreasing patience based on elapsed time
 *
 * @return true if patience just expired during this update, false otherwise
 */
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

/**
 * @brief Adds patience back to the timer, capped at maximum
 */
void Cronometru_Rabdare::adauga_rabdare(float suma) {
    rabdare_actuala = std::min(rabdare_actuala + suma, rabdare_maxima);
}

/**
 * @brief Checks if patience has run out
 *
 * @return true if patience is zero or below
 */
bool Cronometru_Rabdare::expirat() const {
    return rabdare_actuala <= 0;
}

/**
 * @brief Outputs timer state to stream in readable format
 */
std::ostream &operator<<(std::ostream &os, const Cronometru_Rabdare &timer) {
    os << "Rabdare: [" << timer.rabdare_actuala << " / " << timer.rabdare_maxima << "]";
    return os;
}
