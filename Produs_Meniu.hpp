//
// Created by Valiv on 11/11/2025.
//

#ifndef OOP_PRODUS_MENIU_HPP
#define OOP_PRODUS_MENIU_HPP

#include <string>
#include <iostream>

class Produs_Meniu {
private:
    std::string nume_produs;
    double pret;
    int timp_preparare;

public:
    Produs_Meniu(std::string nume_produs, double pret, int timp_preparare);

    [[nodiscard]] const std::string& getnume_produs() const;
    [[nodiscard]] double getpret() const;
    [[nodiscard]] int gettimp_preparare() const;
    [[nodiscard]] double pret_cu_bacsis (float procent_bacsis) const;

    friend std::ostream& operator<<(std::ostream& os, const Produs_Meniu& art);
};

#endif //OOP_PRODUS_MENIU_HPP