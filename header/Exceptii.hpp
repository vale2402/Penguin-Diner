/**
 * @file Exceptii.hpp
 * @brief Custom exception hierarchy for game/restaurant logic errors.
 */
#ifndef OOP_EXCEPTII_HPP
#define OOP_EXCEPTII_HPP

#include <exception>
#include <string>

/**
 * @class Eroare_Joc
 * @brief Base exception class for game-related errors
 *
 * This is the parent class for all custom game exceptions, providing
 * a common interface for error handling in the restaurant simulation.
 */
class Eroare_Joc : public std::exception {
protected:
    std::string mesaj; ///< Error message describing the problem

public:
    /**
     * @brief Constructs a game error with a message
     *
     * @param msg Error message describing the problem
     */
    explicit Eroare_Joc(std::string msg) : mesaj(std::move(msg)) {
    }

    /**
     * @brief Returns the error message
     *
     * @return C-string containing the error message
     */
    [[nodiscard]] const char *what() const noexcept override { return mesaj.c_str(); }
};

/**
 * @class Eroare_Masa_Ocupata
 * @brief Exception thrown when attempting to seat a customer at an occupied table
 *
 * This exception is part of the table seating logic and indicates that
 * the selected table is already in use.
 */
class Eroare_Masa_Ocupata : public Eroare_Joc {
public:
    /**
     * @brief Constructs an occupied table error
     *
     * @param index_masa Index/number of the occupied table
     */
    explicit Eroare_Masa_Ocupata(int index_masa)
        : Eroare_Joc(
            "EROARE: Masa " + std::to_string(index_masa) + " este deja ocupata! Clientul trebuie sa astepte.") {
    }
};

/**
 * @class Eroare_Produs_Indisponibil
 * @brief Exception thrown when a menu product is unavailable or doesn't exist
 *
 * This exception handles menu validation errors when an order references
 * a product that isn't on the menu or has an invalid name.
 */
class Eroare_Produs_Indisponibil : public Eroare_Joc {
public:
    /**
     * @brief Constructs a product unavailability error
     *
     * @param nume_produs Name of the unavailable product
     */
    explicit Eroare_Produs_Indisponibil(const std::string &nume_produs)
        : Eroare_Joc("EROARE: Produsul '" + nume_produs + "' nu este in meniu!") {
    }
};

/**
 * @class Eroare_Actiune_Interzisa
 * @brief Exception thrown when attempting an invalid action on a customer
 *
 * This exception prevents actions on customers in invalid states, such as
 * serving food to a customer who has already left or hasn't ordered yet.
 */
class Eroare_Actiune_Interzisa : public Eroare_Joc {
public:
    /**
     * @brief Constructs an invalid action error
     *
     * @param nume_client Description of the customer or situation
     */
    explicit Eroare_Actiune_Interzisa(const std::string &nume_client)
        : Eroare_Joc("ATENTIE: Nu poti interactiona cu " + nume_client + ". Clientul a plecat deja!") {
    }
};

/**
 * @class Eroare_Restaurant_Plin
 * @brief Exception thrown when the restaurant has reached maximum capacity
 *
 * This critical exception prevents adding more customers when all tables
 * and waiting positions are occupied.
 */
class Eroare_Restaurant_Plin : public Eroare_Joc {
public:
    /**
     * @brief Constructs a restaurant full error
     *
     * @param capacitate Maximum capacity that has been reached
     */
    explicit Eroare_Restaurant_Plin(int capacitate)
        : Eroare_Joc("CRITIC: Restaurantul a atins capacitatea maxima de " + std::to_string(capacitate) + " locuri!") {
    }
};

#endif //OOP_EXCEPTII_HPP
