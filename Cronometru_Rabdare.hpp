//
// Created by Valiv on 03/12/2025.
//

#ifndef OOP_CRONOMETRU_RABDARE_HPP
#define OOP_CRONOMETRU_RABDARE_HPP

#include <iostream>

class Cronometru_Rabdare {
private:
    float rabdare_actuala;
    float rabdare_maxima;
    float rata_scadere;

public:
    Cronometru_Rabdare(float maxim, float rata);

    bool actualizeaza(float timp_scurs);
    void adauga_rabdare(float suma);
    [[nodiscard]] bool expirat() const;

    friend std::ostream& operator<<(std::ostream& os, const Cronometru_Rabdare& timer);
};

#endif //OOP_CRONOMETRU_RABDARE_HPP