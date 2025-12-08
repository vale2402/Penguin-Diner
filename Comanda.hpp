//
// Created by Valiv on 03/12/2025.
//

#ifndef OOP_COMANDA_HPP
#define OOP_COMANDA_HPP

#include "Produs_Meniu.hpp"

class Comanda {
private:
    Produs_Meniu produs_meniu;
    int nr_masa;
    bool stare_comanda;

public:
    Comanda(Produs_Meniu produs_meniu, int nr_masa);

    double finalizeaza_comanda();

    [[nodiscard]] const Produs_Meniu& getprodus_meniu() const;
    [[nodiscard]] int getnr_masa() const;
    [[nodiscard]] bool getstare_comanda() const;

    friend std::ostream& operator<<(std::ostream& os, const Comanda& comanda);
};

#endif //OOP_COMANDA_HPP