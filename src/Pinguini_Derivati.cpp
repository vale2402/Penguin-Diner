/**
 * @file Pinguini_Derivati.cpp
 * @brief Implements specialized penguin client types and their behaviors.
 */
#include "../header/Pinguini_Derivati.hpp"

// ============================================================================
// Student Penguin Implementation
// ============================================================================

/**
 * @brief Constructs a student penguin customer
 */
Pinguin_Student::Pinguin_Student(const Cronometru_Rabdare &timer, const Comanda &cmd)
    : Client_Pinguin(timer, cmd, "Student") {
}

/**
 * @brief Creates a copy of this student penguin using Prototype pattern
 */
Client_Pinguin *Pinguin_Student::clone() const {
    return new Pinguin_Student(*this);
}

/**
 * @brief Applies 10% student discount and logs the price change
 */
void Pinguin_Student::primeste_reducere() const {
    double pret_vechi = comanda_client.getprodus_meniu().getpret();
    double pret_nou = pret_vechi * 0.90; // 10% reducere

    std::cout << " [Student] " << tip_pinguin << " " << ID_Pinguin
            << " prezinta carnetul de student.\n"
            << "  Pret initial: " << pret_vechi << " RON -> Pret cu reducere: " << pret_nou << " RON.\n";
}

/**
 * @brief Displays student-specific details with prefix
 */
void Pinguin_Student::afiseaza_detalii(std::ostream &os) const {
    os << "[Student] ";
    Client_Pinguin::afiseaza_detalii(os);
}

// ============================================================================
// Businessman Penguin Implementation
// ============================================================================

/**
 * @brief Constructs a businessman penguin customer with lower patience
 */
Pinguin_Afacerist::Pinguin_Afacerist(const Cronometru_Rabdare &timer, const Comanda &cmd)
    : Client_Pinguin(timer, cmd, "Afacerist") {
}

/**
 * @brief Creates a copy of this businessman penguin using Prototype pattern
 */
Client_Pinguin *Pinguin_Afacerist::clone() const {
    return new Pinguin_Afacerist(*this);
}

/**
 * @brief Reacts to waiting with doubled impatience (loses patience twice as fast)
 */
void Pinguin_Afacerist::do_reactioneaza_la_timp(float timp_scurs) {
    Client_Pinguin::do_reactioneaza_la_timp(timp_scurs * 2.0f);
}

/**
 * @brief Displays businessman-specific details with prefix
 */
void Pinguin_Afacerist::afiseaza_detalii(std::ostream &os) const {
    os << "[Afacerist] ";
    Client_Pinguin::afiseaza_detalii(os);
}

// ============================================================================
// Influencer Penguin Implementation
// ============================================================================

/**
 * @brief Constructs an influencer penguin customer with high patience
 */
Pinguin_Influencer::Pinguin_Influencer(const Cronometru_Rabdare &timer, const Comanda &cmd)
    : Client_Pinguin(timer, cmd, "Influencer") {
}

/**
 * @brief Creates a copy of this influencer penguin using Prototype pattern
 */
Client_Pinguin *Pinguin_Influencer::clone() const {
    return new Pinguin_Influencer(*this);
}

/**
 * @brief Reacts to waiting with halved impatience (loses patience half as fast)
 */
void Pinguin_Influencer::do_reactioneaza_la_timp(float timp_scurs) {
    Client_Pinguin::do_reactioneaza_la_timp(timp_scurs * 0.5f);
}

/**
 * @brief Displays influencer-specific details with prefix
 */
void Pinguin_Influencer::afiseaza_detalii(std::ostream &os) const {
    os << "[Influencer] ";
    Client_Pinguin::afiseaza_detalii(os);
}

// ============================================================================
// Rich Penguin Implementation
// ============================================================================

/**
 * @brief Constructs a rich penguin customer who tips generously
 */
Pinguin_Bogat::Pinguin_Bogat(const Cronometru_Rabdare &timer, const Comanda &cmd)
    : Client_Pinguin(timer, cmd, "Bogat") {
}

/**
 * @brief Creates a copy of this rich penguin using Prototype pattern
 */
Client_Pinguin *Pinguin_Bogat::clone() const {
    return new Pinguin_Bogat(*this);
}

/**
 * @brief Leaves a generous 25% tip and logs the payment breakdown
 */
void Pinguin_Bogat::lasa_bacsis_extra() const {
    double pret = comanda_client.getprodus_meniu().getpret();
    double bonus = pret * 0.25; // 25%
    double total = pret + bonus;

    std::cout << "[Bogat] " << tip_pinguin << " " << ID_Pinguin
            << " e generos! Lasa 25% bacsis.\n"
            << "  Nota: " << pret << " + " << bonus << " (Tip) = " << total << " RON.\n";
}

/**
 * @brief Displays rich penguin-specific details with prefix
 */
void Pinguin_Bogat::afiseaza_detalii(std::ostream &os) const {
    os << "[Bogatas] ";
    Client_Pinguin::afiseaza_detalii(os);
}
