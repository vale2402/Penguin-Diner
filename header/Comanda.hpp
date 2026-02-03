/**
 * @file Comanda.hpp
 * @brief Declares the order entity containing a menu item, table number and status.
 */
#ifndef OOP_COMANDA_HPP
#define OOP_COMANDA_HPP

#include "Produs_Meniu.hpp"

/**
 * @class Comanda
 * @brief Represents a food order placed by a customer at a specific table
 *
 * This class encapsulates all information about an order: the menu item requested,
 * which table it's for, and whether the order has been completed/served.
 */
class Comanda {
private:
    Produs_Meniu produs_meniu; ///< Menu product ordered by the customer
    int nr_masa; ///< Table number where the order should be delivered
    bool stare_comanda; ///< Order status: false = pending, true = completed/served

public:
    /**
     * @brief Constructs a new order
     *
     * @param produs_meniu Menu product being ordered
     * @param nr_masa Table number for this order
     * @throws Eroare_Produs_Indisponibil if the product name is empty
     */
    Comanda(Produs_Meniu produs_meniu, int nr_masa);

    /**
     * @brief Marks the order as completed and returns its price
     *
     * @return Price of the ordered item
     */
    double finalizeaza_comanda();

    /**
     * @brief Gets the menu product in this order
     *
     * @return Const reference to the ordered product
     */
    [[nodiscard]] const Produs_Meniu &getprodus_meniu() const;

    /**
     * @brief Gets the table number for this order
     *
     * @return Table number
     */
    //[[nodiscard]] int getnr_masa() const;

    /**
     * @brief Gets the completion status of the order
     *
     * @return true if order is completed, false if still pending
     */
    [[nodiscard]] bool getstare_comanda() const;

    /**
     * @brief Stream insertion operator for displaying order information
     *
     * @param os Output stream
     * @param comanda Order to display
     * @return Reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Comanda &comanda);
};

#endif //OOP_COMANDA_HPP
