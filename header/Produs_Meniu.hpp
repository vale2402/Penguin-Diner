/**
 * @file Produs_Meniu.hpp
 * @brief Declares the menu product (name, price, preparation time) used in orders.
 */
#ifndef OOP_PRODUS_MENIU_HPP
#define OOP_PRODUS_MENIU_HPP

#include <string>
#include <iostream>

/**
 * @class Produs_Meniu
 * @brief Represents a menu item with name, price, and preparation time
 *
 * This class encapsulates all information about a menu product that can be
 * ordered by customers, including pricing with optional tip calculations.
 */
class Produs_Meniu {
private:
    std::string nume_produs; ///< Name of the menu item
    double pret; ///< Base price of the item
    int timp_preparare; ///< Time required to prepare the item in seconds

public:
    /**
     * @brief Constructs a menu product
     *
     * @param nume_produs Name of the menu item
     * @param pret Price of the item
     * @param timp_preparare Preparation time in seconds
     */
    Produs_Meniu(std::string nume_produs, double pret, int timp_preparare);

    /**
     * @brief Gets the product name
     *
     * @return Const reference to the product name
     */
    [[nodiscard]] const std::string &getnume_produs() const;

    /**
     * @brief Gets the base price
     *
     * @return Product price
     */
    [[nodiscard]] double getpret() const;

    /**
     * @brief Gets the preparation time
     *
     * @return Preparation time in seconds
     */
    [[nodiscard]] int gettimp_preparare() const;

    /**
     * @brief Calculates price including a tip percentage
     *
     * @param procent_bacsis Tip percentage (e.g., 0.25 for 25%)
     * @return Total price including tip, or base price if percentage is negative
     */
    [[nodiscard]] double pret_cu_bacsis(float procent_bacsis) const;

    /**
     * @brief Stream insertion operator for displaying product information
     *
     * @param os Output stream
     * @param art Menu product to display
     * @return Reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Produs_Meniu &art);
};

#endif //OOP_PRODUS_MENIU_HPP
