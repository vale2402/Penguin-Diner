//
// Created by Valiv on 03/12/2025.
//

#ifndef OOP_CLIENT_PINGUIN_HPP
#define OOP_CLIENT_PINGUIN_HPP
#include <iostream>

#include "Comanda.hpp"
#include "Cronometru_Rabdare.hpp"


class Client_Pinguin {
protected:
    int ID_Pinguin;
    Cronometru_Rabdare cronometru;
    Comanda comanda_client;
    bool plecat_suparat;
    std::string tip_pinguin;
    static int contor_global_clienti;


    //Functii Virtuale
    virtual void do_reactioneaza_la_timp(float timp_scurs);

    virtual void afiseaza_detalii(std::ostream& os) const;
public:
    //Constructor
    Client_Pinguin(const Cronometru_Rabdare &cronometru, Comanda comanda_client, std::string tip = "Generic");

    //Destructor Virtual
    virtual ~Client_Pinguin();

    //Constructor de Copiere
    Client_Pinguin(const Client_Pinguin& other);

    //Operator de Atribuire
    Client_Pinguin& operator=(const Client_Pinguin& other);

    //Constructor Virtual (Clone)
    [[nodiscard]] virtual Client_Pinguin* clone() const = 0;

    //Interfata Non-Virtuala
    void actualizeaza_stare(float timp_scurs);

    //Functie normala
    void esteServit(float timpDeMancat, float rataScadereMancat);

    [[nodiscard]] bool a_plecat_suparat() const;

    friend std::ostream& operator<<(std::ostream& os, const Client_Pinguin& client);
};

#endif //OOP_CLIENT_PINGUIN_HPP