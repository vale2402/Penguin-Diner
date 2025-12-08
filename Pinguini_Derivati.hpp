#ifndef OOP_PINGUINI_DERIVATI_HPP
#define OOP_PINGUINI_DERIVATI_HPP

#include "Client_Pinguin.hpp"


// 1.Pinguinul Student
class Pinguin_Student : public Client_Pinguin {
public:
    Pinguin_Student(const Cronometru_Rabdare& timer, const Comanda& cmd);

    [[nodiscard]] Client_Pinguin* clone() const override;

    void primeste_reducere() const;

protected:
    void afiseaza_detalii(std::ostream& os) const override;
};


// 2.Pinguinul Afacerist (Grabit)
class Pinguin_Afacerist : public Client_Pinguin {
public:
    Pinguin_Afacerist(const Cronometru_Rabdare& timer, const Comanda& cmd);

    [[nodiscard]] Client_Pinguin* clone() const override;

protected:
    void do_reactioneaza_la_timp(float timp_scurs) override;
    void afiseaza_detalii(std::ostream& os) const override;
};

// 3.Pinguinul Influencer (Lent)
class Pinguin_Influencer : public Client_Pinguin {
public:
    Pinguin_Influencer(const Cronometru_Rabdare& timer, const Comanda& cmd);

    [[nodiscard]] Client_Pinguin* clone() const override;

protected:
    void do_reactioneaza_la_timp(float timp_scurs) override;
    void afiseaza_detalii(std::ostream& os) const override;
};

// 3.Pinguinul Bogat (Normal, dar plateste mai mult)
class Pinguin_Bogat : public Client_Pinguin {
public:
    Pinguin_Bogat(const Cronometru_Rabdare& timer, const Comanda& cmd);

    [[nodiscard]] Client_Pinguin* clone() const override;

    void lasa_bacsis_extra() const;

protected:
    void afiseaza_detalii(std::ostream& os) const override;
};

#endif //OOP_PINGUINI_DERIVATI_HPP