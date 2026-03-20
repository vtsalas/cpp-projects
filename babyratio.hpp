#ifndef CONTEST
#define BABYRATIO_HPP

class rational {
public:
    rational (int n, int d); // Ο Κατασκευαστής (Constructor)
    rational add (rational r);
    rational sub (rational r);
    rational mul (rational r);
    rational div (rational r);
    void print ();

private:
    int nom, den; // Αριθμητής (nom) και Παρονομαστής (den)
    static int gcd (int a, int b); // Μέγιστος Κοινός Διαιρέτης
};

#endif