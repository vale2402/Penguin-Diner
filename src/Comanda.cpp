/**
 * @file Comanda.cpp
 * @brief Implements the order logic and stream output.
 */
#include "../header/Comanda.hpp"
#include <utility>

#include "../header/Exceptii.hpp"

/**
 * @brief Constructs an order for a specific table
 *
 * @throws Eroare_Produs_Indisponibil if product name is empty
 */
Comanda::Comanda(Produs_Meniu produs_meniu, int nr_masa)
    : produs_meniu(std::move(produs_meniu)),
      nr_masa(nr_masa),
      stare_comanda(false) {
    if (this->produs_meniu.getnume_produs().empty()) {
        throw Eroare_Produs_Indisponibil("Produs Necunoscut");
    }
}

/**
 * @brief Marks the order as completed/served
 *
 * @return The price of the completed order
 */
double Comanda::finalizeaza_comanda() {
    this->stare_comanda = true;
    return this->produs_meniu.getpret();
}

/**
 * @brief Gets the ordered menu product
 *
 * @return Const reference to the product
 */
const Produs_Meniu &Comanda::getprodus_meniu() const {
    return produs_meniu;
}

/**
 * @brief Gets the table number for this order
 *
 * @return Table number
 */
// int Comanda::getnr_masa() const {
//     return nr_masa;
// }

/**
 * @brief Gets the order completion status
 *
 * @return true if completed, false if pending
 */
bool Comanda::getstare_comanda() const {
    return stare_comanda;
}

/**
 * @brief Outputs order details to stream
 */
std::ostream &operator<<(std::ostream &os, const Comanda &comanda) {
    os << "Comanda pt Masa " << comanda.nr_masa
            << " | " << comanda.produs_meniu
            << " | Gata: " << (comanda.stare_comanda ? "Da" : "Nu");
    return os;
}
