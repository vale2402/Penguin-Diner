//
// Created by Valiv on 07/12/2025.
//

#ifndef OOP_RESTAURANT_HPP
#define OOP_RESTAURANT_HPP

#include <vector>
#include <iostream>
#include "Client_Pinguin.hpp"

class Restaurant {
private:
    std::vector<Client_Pinguin*> mese;
    int capacitate_maxima;

public:
    //Constructor
    explicit Restaurant(int capacitate = 5);

    //Destructor
    ~Restaurant();
    //Copy Constructor
    Restaurant(const Restaurant& other);
    //Operator=
    Restaurant& operator=(Restaurant other);

    friend void swap(Restaurant& r1, Restaurant& r2) noexcept;

    void primeste_client(Client_Pinguin* client_nou);

    void simuleaza_tura(float timp_scurs) const;

    void aseaza_la_masa(int index, Client_Pinguin* client);

    void serveste_client(int index) const;

    void aplica_promotie_studenti() const;

    friend std::ostream& operator<<(std::ostream& os, const Restaurant& restaurant);
};

#endif //OOP_RESTAURANT_HPP