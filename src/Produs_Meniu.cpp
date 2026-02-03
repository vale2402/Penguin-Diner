/**
 * @file Produs_Meniu.cpp
 * @brief Implements the menu product entity and helpers.
 */
#include "../header/Produs_Meniu.hpp"
#include <utility>

/**
 * @brief Constructs a menu product with name, price, and preparation time
 */
Produs_Meniu::Produs_Meniu(std::string nume_produs, double pret, int timp_preparare)
    : nume_produs(std::move(nume_produs)),
      pret(pret),
      timp_preparare(timp_preparare) {
}

/**
 * @brief Gets the product name
 *
 * @return Const reference to product name
 */
const std::string &Produs_Meniu::getnume_produs() const {
    return nume_produs;
}

/**
 * @brief Gets the product price
 *
 * @return Base price of the product
 */
double Produs_Meniu::getpret() const {
    return pret;
}

/**
 * @brief Gets the preparation time
 *
 * @return Preparation time in seconds
 */
// int Produs_Meniu::gettimp_preparare() const {
//     return timp_preparare;
// }

/**
 * @brief Calculates price with tip percentage added
 *
 * @param procent_bacsis Tip percentage (0.25 = 25%)
 * @return Total price including tip, or base price if percentage is negative
 */
// double Produs_Meniu::pret_cu_bacsis(float procent_bacsis) const {
//     if (procent_bacsis < 0.0f) {
//         return pret;
//     }
//     return pret * (1.0 + procent_bacsis);
// }

/**
 * @brief Outputs product details to stream
 */
std::ostream &operator<<(std::ostream &os, const Produs_Meniu &art) {
    os << "Articol: " << art.nume_produs
            << " (Pret: " << art.pret
            << ", Timp: " << art.timp_preparare << "s)";
    return os;
}
