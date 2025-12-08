#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Produs_Meniu.hpp"
#include "Comanda.hpp"
#include "Cronometru_Rabdare.hpp"
#include "Client_Pinguin.hpp"
#include "Pinguini_Derivati.hpp"
#include "Restaurant.hpp"
#include "Exceptii.hpp"

using namespace std;

void citeste_meniu(vector<Produs_Meniu>& meniu) {
    ifstream fisier("meniu.txt");
    if (!fisier.is_open()) {
        throw runtime_error("Nu s-a putut deschide fisierul meniu.txt!");
    }

    string nume;
    double pret;
    int timp;

    while (fisier >> nume >> pret >> timp) {
        meniu.emplace_back(nume, pret, timp);
    }
    cout << "[System] Meniu incarcat cu succes din fisier!\n\n";
}

int main() {
    cout << "- PENGUIN DINER SIMULATOR -\n\n";

    try {
        vector<Produs_Meniu> lista_meniu;
        citeste_meniu(lista_meniu);

        Cronometru_Rabdare timer_check(5.0f, 1.0f);
        Comanda comanda_check(lista_meniu[0], 99);

        timer_check.adauga_rabdare(2.0f);
        if (!timer_check.expirat()) {
            cout << " Timer functional. Masa test: " << comanda_check.getnr_masa() << "\n";
        }

        if (!lista_meniu.empty()) {
            cout << lista_meniu[0].gettimp_preparare() << " " << lista_meniu[0].pret_cu_bacsis(0.1f) << "\n";
        }

        Restaurant dummy_rest(1);
        dummy_rest.aseaza_la_masa(0, new Pinguin_Student(timer_check, Comanda(lista_meniu[0], 99)));
        try { dummy_rest.serveste_client(0); } catch(...) {}

        Restaurant penguin_diner(4);

        cout << "\n- [1] Soseste Primul Client (Student) -\n";
        Client_Pinguin* student = new Pinguin_Student(
            Cronometru_Rabdare(30.0f, 1.0f),
            Comanda(lista_meniu[0], 1)
        );
        penguin_diner.primeste_client(student);


        cout << "\n- [2] Soseste Al Doilea Client (Afacerist) -\n";
        Client_Pinguin* afacerist = new Pinguin_Afacerist(
            Cronometru_Rabdare(20.0f, 1.0f),
            Comanda(lista_meniu[1], 2)
        );
        penguin_diner.primeste_client(afacerist);


        cout << "\n- [3] Starea Restaurantului -\n";
        cout << penguin_diner << endl;

        penguin_diner.aplica_promotie_studenti();


        cout << "Dupa 5 secunde... \n";
        penguin_diner.simuleaza_tura(5.0f);
        cout << penguin_diner << endl;


        cout << "\n- [4] Soseste Al Treilea Client (Influencer) -\n";
        Client_Pinguin* influencer = new Pinguin_Influencer(
            Cronometru_Rabdare(60.0f, 1.0f),
            Comanda(lista_meniu[2], 3)
        );

        cout << " Incercam sa asezam Influencerul la masa\n";
        penguin_diner.primeste_client(influencer);
        cout << " Influencerul a primit loc la masa.\n";

        cout << "\n- [In plus] Soseste Pinguinul Bogat (Al 4-lea) -\n";
        auto* bogatas = new Pinguin_Bogat(
            Cronometru_Rabdare(40.0f, 1.0f),
            Comanda(lista_meniu[0], 1)
        );
        bogatas->lasa_bacsis_extra();

        cout << " Incercam sa asezam Bogatasul la masa\n";
        penguin_diner.primeste_client(bogatas);

    }
    catch (const Eroare_Restaurant_Plin& e) {
        cerr << "\n[!] Exceptie de joc: " << e.what() << "\n";
        cerr << " Clientul a fost refuzat, memoria a fost curatata.\n";
    }
    catch (const exception& e) {
        cerr << "\n[!] Alta eroare critica: " << e.what() << "\n";
    }

    cout << "\n- Sfarsit simulare -\n";

    return 0;
}