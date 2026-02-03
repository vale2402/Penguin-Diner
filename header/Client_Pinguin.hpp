//
// Created by Valiv on 03/12/2025.
//

/**
 * @file Client_Pinguin.hpp
 * @brief Declares the base penguin client class used for game logic and state handling.
 */
#ifndef OOP_CLIENT_PINGUIN_HPP
#define OOP_CLIENT_PINGUIN_HPP
#include <iostream>

#include "Comanda.hpp"
#include "Cronometru_Rabdare.hpp"

/**
 * @class Client_Pinguin
 * @brief Abstract base class representing a penguin customer in the restaurant
 *
 * This class manages customer state including patience timer, order status, and
 * reaction to waiting time. It uses the Prototype pattern (clone method) and
 * provides virtual methods for derived classes to customize behavior.
 */
class Client_Pinguin {
protected:
    int ID_Pinguin; ///< Unique identifier for this client
    Cronometru_Rabdare cronometru; ///< Patience timer tracking how long the client will wait
    Comanda comanda_client; ///< The client's food order
    bool plecat_suparat; ///< Flag indicating if the client left angry/unsatisfied
    std::string tip_pinguin; ///< Type/category of penguin (e.g., Student, Businessman)
    static int contor_global_clienti; ///< Global counter for assigning unique IDs

    /**
     * @brief Virtual method for derived classes to customize reaction to waiting time
     *
     * @param timp_scurs Elapsed time in seconds
     */
    virtual void do_reactioneaza_la_timp(float timp_scurs);

    /**
     * @brief Virtual method to display client details to an output stream
     *
     * @param os Output stream to write to
     */
    virtual void afiseaza_detalii(std::ostream &os) const;

public:
    /**
     * @brief Constructs a new penguin client
     *
     * @param cronometru Patience timer configuration
     * @param comanda_client Order placed by the client
     * @param tip Type/category of penguin client (default: "Generic")
     */
    Client_Pinguin(const Cronometru_Rabdare &cronometru, Comanda comanda_client, std::string tip = "Generic");

    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~Client_Pinguin();

    /**
     * @brief Copy constructor
     *
     * @param other Client to copy from
     */
    Client_Pinguin(const Client_Pinguin &other);

    /**
     * @brief Copy assignment operator
     *
     * @param other Client to assign from
     * @return Reference to this object
     */
    Client_Pinguin &operator=(const Client_Pinguin &other);

    /**
     * @brief Pure virtual clone method for the Prototype pattern
     *
     * @return Pointer to a newly allocated copy of this client
     */
    [[nodiscard]] virtual Client_Pinguin *clone() const = 0;

    /**
     * @brief Updates the client's state based on elapsed time
     *
     * @param timp_scurs Time elapsed since last update in seconds
     */
    void actualizeaza_stare(float timp_scurs);

    /**
     * @brief Marks the client as served and starts eating timer
     *
     * @param timpDeMancat Time required to finish eating in seconds
     * @param rataScadereMancat Rate at which eating patience decreases
     */
    void esteServit(float timpDeMancat, float rataScadereMancat);

    /**
     * @brief Checks if the client left angry
     *
     * @return true if client left unsatisfied, false otherwise
     */
    [[nodiscard]] bool a_plecat_suparat() const;

    /**
     * @brief Stream insertion operator for displaying client information
     *
     * @param os Output stream
     * @param client Client to display
     * @return Reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Client_Pinguin &client);
};

#endif //OOP_CLIENT_PINGUIN_HPP
