/**
 * @file Pinguini_Derivati.hpp
 * @brief Declares derived penguin client types with specialized behaviors and messages.
 */
#ifndef OOP_PINGUINI_DERIVATI_HPP
#define OOP_PINGUINI_DERIVATI_HPP

#include "Client_Pinguin.hpp"

/**
 * @class Pinguin_Student
 * @brief Student penguin customer with normal patience and discount benefits
 *
 * This customer type has standard patience but receives a 10% discount
 * when presenting a student ID card, paying less than other customers.
 */
class Pinguin_Student final : public Client_Pinguin {
public:
    /**
     * @brief Constructs a student penguin customer
     *
     * @param timer Patience timer configuration
     * @param cmd Order for this customer
     */
    Pinguin_Student(const Cronometru_Rabdare &timer, const Comanda &cmd);

    /**
     * @brief Creates a copy of this student penguin
     *
     * @return Pointer to newly allocated copy
     */
    [[nodiscard]] Client_Pinguin *clone() const override;

    /**
     * @brief Applies student discount and displays the price difference
     */
    void primeste_reducere() const;

protected:
    /**
     * @brief Displays student-specific details
     *
     * @param os Output stream to write to
     */
    void afiseaza_detalii(std::ostream &os) const override;
};

/**
 * @class Pinguin_Afacerist
 * @brief Businessman penguin customer with low patience and fast service expectations
 *
 * This customer type has significantly reduced patience (loses patience twice as fast)
 * and gets angry quickly if not served promptly. However, pays well for quick service.
 */
class Pinguin_Afacerist final : public Client_Pinguin {
public:
    /**
     * @brief Constructs a businessman penguin customer
     *
     * @param timer Patience timer configuration (should have higher decay rate)
     * @param cmd Order for this customer
     */
    Pinguin_Afacerist(const Cronometru_Rabdare &timer, const Comanda &cmd);

    /**
     * @brief Creates a copy of this businessman penguin
     *
     * @return Pointer to newly allocated copy
     */
    [[nodiscard]] Client_Pinguin *clone() const override;

protected:
    /**
     * @brief Reacts to waiting time with doubled impatience
     *
     * @param timp_scurs Elapsed time in seconds (doubled internally)
     */
    void do_reactioneaza_la_timp(float timp_scurs) override;

    /**
     * @brief Displays businessman-specific details
     *
     * @param os Output stream to write to
     */
    void afiseaza_detalii(std::ostream &os) const override;
};

/**
 * @class Pinguin_Influencer
 * @brief Influencer penguin customer with high patience and slow eating
 *
 * This customer type takes longer to get impatient (loses patience at half the normal rate),
 * often taking photos of food. However, leaves minimal tips.
 */
class Pinguin_Influencer final : public Client_Pinguin {
public:
    /**
     * @brief Constructs an influencer penguin customer
     *
     * @param timer Patience timer configuration
     * @param cmd Order for this customer
     */
    Pinguin_Influencer(const Cronometru_Rabdare &timer, const Comanda &cmd);

    /**
     * @brief Creates a copy of this influencer penguin
     *
     * @return Pointer to newly allocated copy
     */
    [[nodiscard]] Client_Pinguin *clone() const override;

protected:
    /**
     * @brief Reacts to waiting time with halved patience loss
     *
     * @param timp_scurs Elapsed time in seconds (halved internally)
     */
    void do_reactioneaza_la_timp(float timp_scurs) override;

    /**
     * @brief Displays influencer-specific details
     *
     * @param os Output stream to write to
     */
    void afiseaza_detalii(std::ostream &os) const override;
};

/**
 * @class Pinguin_Bogat
 * @brief Rich penguin customer with normal patience but generous tipping
 *
 * This customer type has standard patience but leaves a 25% tip,
 * making them the most profitable customer type.
 */
class Pinguin_Bogat final : public Client_Pinguin {
public:
    /**
     * @brief Constructs a rich penguin customer
     *
     * @param timer Patience timer configuration
     * @param cmd Order for this customer
     */
    Pinguin_Bogat(const Cronometru_Rabdare &timer, const Comanda &cmd);

    /**
     * @brief Creates a copy of this rich penguin
     *
     * @return Pointer to newly allocated copy
     */
    [[nodiscard]] Client_Pinguin *clone() const override;

    /**
     * @brief Leaves a generous 25% tip and displays the amount
     */
    void lasa_bacsis_extra() const;

protected:
    /**
     * @brief Displays rich penguin-specific details
     *
     * @param os Output stream to write to
     */
    void afiseaza_detalii(std::ostream &os) const override;
};

#endif //OOP_PINGUINI_DERIVATI_HPP
