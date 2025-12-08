//
// Created by Valiv on 07/12/2025.
//

#ifndef OOP_EXCEPTII_HPP
#define OOP_EXCEPTII_HPP

#include <exception>
#include <string>

class Eroare_Joc : public std::exception {
protected:
    std::string mesaj;
public:
    explicit Eroare_Joc(std::string msg) : mesaj(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override { return mesaj.c_str(); }
};

//Exceptia 1: Logica de așezare la masă
class Eroare_Masa_Ocupata : public Eroare_Joc {
public:
    explicit Eroare_Masa_Ocupata(int index_masa)
        : Eroare_Joc("EROARE: Masa " + std::to_string(index_masa) + " este deja ocupata! Clientul trebuie sa astepte.") {}
};

//Exceptia 2: Logica de meniu
class Eroare_Produs_Indisponibil : public Eroare_Joc {
public:
    explicit Eroare_Produs_Indisponibil(const std::string& nume_produs)
        : Eroare_Joc("EROARE: Produsul '" + nume_produs + "' nu este in meniu!") {}
};

//Exceptia 3: Logica de stare a clientului
class Eroare_Actiune_Interzisa : public Eroare_Joc {
public:
    explicit Eroare_Actiune_Interzisa(const std::string& nume_client)
        : Eroare_Joc("ATENTIE: Nu poti interactiona cu " + nume_client + ". Clientul a plecat deja!") {}
};
// Exceptia 4: Restaurantul e complet plin
class Eroare_Restaurant_Plin : public Eroare_Joc {
public:
    explicit Eroare_Restaurant_Plin(int capacitate)
        : Eroare_Joc("CRITIC: Restaurantul a atins capacitatea maxima de " + std::to_string(capacitate) + " locuri!") {}
};

#endif //OOP_EXCEPTII_HPP