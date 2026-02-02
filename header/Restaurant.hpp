/**
 * @file Restaurant.hpp
 * @brief Declares the Restaurant class managing clients, seating, and service logic.
 */
#ifndef OOP_RESTAURANT_HPP
#define OOP_RESTAURANT_HPP

#include <vector>
#include <iostream>
#include "Client_Pinguin.hpp"

/**
 * @class Restaurant
 * @brief Manages restaurant operations including customer seating and service
 *
 * This class handles the restaurant's customer management, including seating
 * customers at tables, serving them, running time-based simulations, and
 * applying special promotions. Implements the Rule of Three with proper
 * resource management.
 */
class Restaurant {
private:
    std::vector<Client_Pinguin *> mese; ///< Vector of pointers to seated customers
    int capacitate_maxima; ///< Maximum number of tables/seats

public:
    /**
     * @brief Constructs a restaurant with specified capacity
     *
     * @param capacitate Maximum number of customers that can be seated (default: 5)
     */
    explicit Restaurant(int capacitate = 5);

    /**
     * @brief Destructor that properly cleans up all customer objects
     */
    ~Restaurant();

    /**
     * @brief Copy constructor that performs deep copy of customers
     *
     * @param other Restaurant to copy from
     */
    Restaurant(const Restaurant &other);

    /**
     * @brief Copy assignment operator using copy-and-swap idiom
     *
     * @param other Restaurant to assign from (passed by value)
     * @return Reference to this object
     */
    Restaurant &operator=(Restaurant other);

    /**
     * @brief Swaps contents of two restaurants (used in copy-and-swap)
     *
     * @param r1 First restaurant
     * @param r2 Second restaurant
     */
    friend void swap(Restaurant &r1, Restaurant &r2) noexcept;

    /**
     * @brief Adds a new customer to the restaurant
     *
     * @param client_nou Pointer to customer to add
     * @throws Eroare_Restaurant_Plin if restaurant is at maximum capacity
     */
    void primeste_client(Client_Pinguin *client_nou);

    /**
     * @brief Simulates passage of time for all customers
     *
     * Updates patience timers and checks for customers leaving.
     *
     * @param timp_scurs Time elapsed in seconds
     */
    void simuleaza_tura(float timp_scurs) const;

    /**
     * @brief Seats a customer at a specific table index
     *
     * @param index Table number (0-based)
     * @param client Pointer to customer to seat
     * @throws std::out_of_range if index is invalid
     * @throws Eroare_Masa_Ocupata if restaurant is full
     */
    void aseaza_la_masa(int index, Client_Pinguin *client);

    /**
     * @brief Serves food to a customer at specified table
     *
     * @param index Table number where customer is seated
     * @throws std::out_of_range if index is invalid
     * @throws Eroare_Actiune_Interzisa if customer has already left angry
     */
    void serveste_client(int index) const;

    /**
     * @brief Applies student discount promotion to all student customers
     *
     * Uses dynamic_cast to identify student customers and applies discount.
     */
    void aplica_promotie_studenti() const;

    /**
     * @brief Stream insertion operator for displaying restaurant state
     *
     * @param os Output stream
     * @param restaurant Restaurant to display
     * @return Reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Restaurant &restaurant);
};

#endif //OOP_RESTAURANT_HPP
