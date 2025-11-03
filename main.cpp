#include <iostream>
#include <string>
#include <ostream>
#include <utility>
#include <algorithm>

using namespace std;

class Produs_Meniu {
private:
    std::string nume_produs;
    double pret;
    int timp_preparare;
public:
    Produs_Meniu(std::string nume_produs, double pret, int timp_preparare)
        : nume_produs(std::move(nume_produs)),
          pret(pret),
          timp_preparare(timp_preparare) {
    }

    [[nodiscard]] const std::string& getnume_produs() const {
        return nume_produs;
    }

    [[nodiscard]] double getpret() const {
        return pret;
    }

    [[nodiscard]] int gettimp_preparare() const {
        return timp_preparare;
    }

    [[nodiscard]] double pret_cu_bacsis (float procent_bacsis) const {
        if (procent_bacsis < 0.0f) {
            return pret;
        }
        return pret * (1.0 + procent_bacsis);
    }

    friend std::ostream& operator<<(std::ostream& os, const Produs_Meniu& art);
};

std::ostream& operator<<(std::ostream& os, const Produs_Meniu& art) {
    os << "Articol: " << art.nume_produs
       << " (Pret: " << art.pret
       << ", Timp: " << art.timp_preparare << "s)";
    return os;
}

class Cronometru_Rabdare {
private:
    float rabdare_actuala;
    float rabdare_maxima;
    float rata_scadere;
public:
    Cronometru_Rabdare(float maxim, float rata)
        :rabdare_actuala(maxim),
        rabdare_maxima(maxim),
        rata_scadere(rata) {
    }

    bool actualizeaza(float timp_scurs) {
        if (rabdare_actuala > 0) {
            rabdare_actuala -= rata_scadere * timp_scurs;
            if (rabdare_actuala <= 0) {
                rabdare_actuala = 0;
                return true;
            }
        }
        return false;
    }
    void adauga_rabdare(float suma) {
        rabdare_actuala = std::min(rabdare_actuala + suma, rabdare_maxima);
    }
    [[nodiscard]] bool expirat() const {
        return rabdare_actuala <= 0;
    }
    friend std::ostream& operator<<(std::ostream& os, const Cronometru_Rabdare& timer);
};

std::ostream& operator<<(std::ostream& os, const Cronometru_Rabdare& timer) {
    os << "Rabdare: [" << timer.rabdare_actuala << " / " << timer.rabdare_maxima << "]";
    return os;
}

class Comanda {
private:
    Produs_Meniu produs_meniu;
    int nr_masa;
    bool stare_comanda;
public:
    Comanda(Produs_Meniu produs_meniu, int nr_masa)
        : produs_meniu(std::move(produs_meniu)),
          nr_masa(nr_masa),
          stare_comanda(false){
    }

    double finalizeaza_comanda() {
        this->stare_comanda = true;
        return this->produs_meniu.getpret();
    }

    [[nodiscard]] const Produs_Meniu& getprodus_meniu() const {
        return produs_meniu;
    }

    [[nodiscard]] int getnr_masa() const {
        return nr_masa;
    }

    [[nodiscard]] bool getstare_comanda() const {
        return stare_comanda;
    }
    friend std::ostream& operator<<(std::ostream& os, const Comanda& comanda);
};
std::ostream& operator<<(std::ostream& os, const Comanda& comanda) {
    os << "Comanda pt Masa " << comanda.nr_masa
       << " | " << comanda.produs_meniu
       << " | Gata: " << (comanda.stare_comanda ? "Da" : "Nu");
    return os;
}

class Client_Pinguin {
private:
    int ID_Pinguin;
    Cronometru_Rabdare cronometru;
    Comanda comanda_client;
    bool plecat_suparat;
    static int contor_global_clienti;
public:
    Client_Pinguin(const Cronometru_Rabdare &cronometru, Comanda comanda_client)
        : ID_Pinguin(++contor_global_clienti),
          cronometru(cronometru),
          comanda_client(std::move(comanda_client)),
          plecat_suparat(false) {
        std::cout << "Constructor: Clientul " << ID_Pinguin << " s-a asezat.\n";
    }

    ~Client_Pinguin() {
        std::cout << "Destructor: Clientul " << ID_Pinguin << " paraseste restaurantul";
        if (plecat_suparat) {
            std::cout << " (suparat!).\n";
        } else {
            std::cout << " (fericit!).\n";
        }
    }

    Client_Pinguin(const Client_Pinguin& other)
        : ID_Pinguin(other.ID_Pinguin),
          cronometru(other.cronometru),
          comanda_client(other.comanda_client),
          plecat_suparat(other.plecat_suparat) {
        std::cout << "Constructor de COPIERE: Se cloneaza clientul " << other.ID_Pinguin << ".\n";
    }

    Client_Pinguin& operator=(const Client_Pinguin& other) {
        std::cout << "Operator de ATRIBUIRE (=): Clientul " << this->ID_Pinguin
                  << " devine " << other.ID_Pinguin << ".\n";
        if (this != &other) {
            ID_Pinguin = other.ID_Pinguin;
            cronometru = other.cronometru;
            comanda_client = other.comanda_client;
            plecat_suparat = other.plecat_suparat;
        }
        return *this;
    }

    void actualizeaza_stare(float timp_scurs) {
        if (plecat_suparat || comanda_client.getstare_comanda()) {
            return;
        }

        if (cronometru.actualizeaza(timp_scurs)) {
            plecat_suparat = true;
            std::cout << "! Clientul " << ID_Pinguin << " si-a pierdut rabdarea si pleaca! !!!\n";
        }
    }

    void esteServit(float timpDeMancat, float rataScadereMancat) {
        if (plecat_suparat) return;

        std::cout << "Clientul " << ID_Pinguin << " este servit. Incepe sa manance.\n";
        cronometru = Cronometru_Rabdare(timpDeMancat, rataScadereMancat);
        this->comanda_client.finalizeaza_comanda();
    }

    [[nodiscard]] bool a_plecat_suparat() const{
        return plecat_suparat;
    }
    friend std::ostream& operator<<(std::ostream& os, const Client_Pinguin& client);
};

int Client_Pinguin::contor_global_clienti = 0;

std::ostream& operator<<(std::ostream& os, const Client_Pinguin& client) {
    os << "\n";
    os << "Client: " << client.ID_Pinguin << " | Suparat: " << (client.plecat_suparat ? "DA" : "NU") << "\n";
    os << "   " << client.cronometru << "\n";
    os << "   " << client.comanda_client << "\n";
    os << "\n";
    return os;
}

void afiseazaStareaComenzii(const Comanda& comanda) {
    cout << "Stare: ";
    if (comanda.getstare_comanda()) {
        cout << "Gata" << endl;
    } else {
        cout << "In asteptare" << endl;
    }
}

int main() {
    cout << "===== START SIMULARE RESTAURANT  =====\n\n";

    cout << "1. Creare Meniu\n";
    Produs_Meniu peste("Peste", 25.5, 30);
    Produs_Meniu suc("Suc", 8.0, 10);

    cout << peste << endl;
    cout << suc << endl;

    cout << "Peste +10% bacsis: " << peste.pret_cu_bacsis(0.1f) << " \n";

    cout << "Detalii suc: " << suc.getnume_produs() << ", "
         << suc.getpret() << " , "
         << suc.gettimp_preparare() << "s\n\n";

    cout << "2. Testare Cronometru Separat\n";
    Cronometru_Rabdare timerTest(10.0f, 2.0f);
    cout << "Initial: " << timerTest << endl;

    timerTest.actualizeaza(3.0f);
    cout << "Dupa 3s: " << timerTest << endl;

    timerTest.adauga_rabdare(20.0f);
    cout << "Dupa boost: " << timerTest << endl;

    cout << "A expirat? " << (timerTest.expirat() ? "Da" : "Nu") << "\n\n";

    cout << "3. Testare Comanda Separat\n";
    Comanda comandaFinalizata(suc, 5);
    comandaFinalizata.finalizeaza_comanda();

    Comanda comandaInAsteptare(peste, 6);

    cout << "Test comanda finalizata: " << comandaFinalizata << endl;
    cout << "Test comanda in asteptare: " << comandaInAsteptare << endl;

    afiseazaStareaComenzii(comandaFinalizata);

    afiseazaStareaComenzii(comandaInAsteptare);

    cout << "Masa (Test 1): " << comandaFinalizata.getnr_masa() << endl;
    cout << "Produs (Test 2): " << comandaInAsteptare.getprodus_meniu().getnume_produs() << "\n\n";

    cout << "4. Soseste Clientul #1\n";
    Comanda comanda1(peste, 1);
    Cronometru_Rabdare timer1(30.0f, 2.0f);

    Client_Pinguin pingu1(timer1, comanda1);

    cout << pingu1;

    cout << ">> Simulam 10 secunde \n";
    pingu1.actualizeaza_stare(10.0f);
    cout << pingu1;

    cout << ">> Simulam inca 10 secunde (total 20s, ar trebui sa plece)\n";
    pingu1.actualizeaza_stare(10.0f);

    cout << "Verificare: A plecat suparat? " << (pingu1.a_plecat_suparat() ? "Da" : "Nu") << endl;
    cout << pingu1;

    cout << "5. Soseste Clientul #2\n";
    Comanda comanda2(suc, 2);
    Cronometru_Rabdare timer2(25.0f, 5.0f);

    Client_Pinguin pingu2(timer2, comanda2);
    cout << pingu2;

    cout << ">> Simulam 4 secunde \n";
    pingu2.actualizeaza_stare(4.0f);
    cout << pingu2;

    pingu2.esteServit(20.0f, 1.0f);
    cout << pingu2;

    cout << ">> Simulam 15 secunde (mănâncă)\n";
    pingu2.actualizeaza_stare(15.0f);
    cout << "Verificare: A plecat suparat? " << (pingu2.a_plecat_suparat() ? "Da" : "Nu") << endl;
    cout << pingu2;

    cout << "--- 6. Testare Regula celor Trei ---\n";

    cout << ">> Se creeaza pingu3 (copie dupa pingu1, cel suparat)\n";
    Client_Pinguin pingu3 = pingu1;
    cout << pingu3;

    cout << ">> Se creeaza pingu4 (dummy), apoi se atribuie pingu2 (cel fericit)\n";
    Client_Pinguin pingu4(timerTest, comandaInAsteptare);
    pingu4 = pingu2;
    cout << pingu4;

    cout << "\n===== FINAL SIMULARE (se apeleaza Destructorii) =====\n";

    return 0;
}
