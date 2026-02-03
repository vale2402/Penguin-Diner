//
// Created by Valiv on 03/12/2025.
//

/**
 * @file Cronometru_Rabdare.hpp
 * @brief Declares a simple patience timer used to model waiting/consumption time.
 */
#ifndef OOP_CRONOMETRU_RABDARE_HPP
#define OOP_CRONOMETRU_RABDARE_HPP

#include <iostream>

/**
 * @class Cronometru_Rabdare
 * @brief Manages a countdown timer representing patience or activity duration
 *
 * This class implements a timer that decreases over time at a specified rate.
 * It's used to model customer patience while waiting for service or eating food.
 * The timer can be checked for expiration and can have time added back to it.
 */
class Cronometru_Rabdare {
private:
    float rabdare_actuala; ///< Current remaining patience/time value
    float rabdare_maxima; ///< Maximum patience/time value (used for capping additions)
    float rata_scadere; ///< Rate at which patience decreases per second

public:
    /**
     * @brief Constructs a new patience timer
     *
     * @param maxim Maximum and initial patience value
     * @param rata Rate at which patience decreases per second
     */
    Cronometru_Rabdare(float maxim, float rata);

    /**
     * @brief Updates the timer by reducing patience based on elapsed time
     *
     * @param timp_scurs Time elapsed since the last update in seconds
     * @return true if the timer expired during this update, false otherwise
     */
    bool actualizeaza(float timp_scurs);

    /**
     * @brief Adds time/patience back to the timer (capped at maximum)
     *
     * @param suma Amount of patience to add
     */
    //void adauga_rabdare(float suma);

    /**
     * @brief Checks if the patience timer has expired
     *
     * @return true if patience has reached zero, false otherwise
     */
    // [[nodiscard]] bool expirat() const;

    /**
     * @brief Stream insertion operator for displaying timer state
     *
     * @param os Output stream
     * @param timer Timer to display
     * @return Reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Cronometru_Rabdare &timer);
};

#endif //OOP_CRONOMETRU_RABDARE_HPP
