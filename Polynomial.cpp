#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

class Polynomial {
protected:
    class Term {
    protected:
        int exponent;
        int coefficient;
        Term* next;
        Term(int exp, int coeff, Term* n) : exponent(exp), coefficient(coeff), next(n) {}
        friend class Polynomial;
        friend Polynomial operator+(const Polynomial& p, const Polynomial& q);
        friend Polynomial operator*(const Polynomial& p, const Polynomial& q);
        friend ostream& operator<<(ostream& out, const Polynomial& p);
    };

public:
    Polynomial() {
        // TODO: αρχικοποίηση head
        head = nullptr;
    }

    Polynomial(const Polynomial& p) {
        // TODO: deep copy της λίστας του p
        Term* curr = p.head;
        Term* tail = nullptr;
        head = nullptr;

        while(curr != nullptr) {
            Term* newTerm = new Term(curr->exponent, curr->coefficient, nullptr);

            if(tail == nullptr) head = newTerm;
            else tail->next = newTerm;
            tail = newTerm;
            curr = curr->next;
        }
    }

    ~Polynomial() {
        Term* curr = head;

        while(curr != nullptr) {
            Term* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    Polynomial& operator=(const Polynomial& p) {
        if(this != &p) {
            Term* curr = head;

            while(curr != nullptr) {
                Term* next = curr->next;
                delete curr;
                curr = next;
            }
            Term* second_curr = p.head;
            Term* tail = nullptr;
            head = nullptr;

            while(second_curr != nullptr) {
                Term* newTerm = new Term(second_curr->exponent, second_curr->coefficient, nullptr);

                if(tail == nullptr) head = newTerm;
                else tail->next = newTerm;
                tail = newTerm;
                second_curr = second_curr->next;
            }
        }
        return *this;
    }

    void addTerm(int expon, int coeff) {

        if(coeff == 0) return;

        Term* curr = head;
        Term* prev = nullptr;

        while(curr != nullptr && curr->exponent > expon) {
            prev = curr;
            curr = curr->next;
        }
        if(curr != nullptr && curr->exponent == expon) {
            curr->coefficient += coeff;
            if(curr->coefficient == 0) {
                if(prev == nullptr) head = curr->next;
                else prev->next = curr->next;
                delete curr;
            }
        }
        else{
            Term* newTerm = new Term(expon, coeff, curr);
            if(prev == nullptr) head = newTerm;
            else prev->next = newTerm;
        }
    }

    double evaluate(double x) {
        Term* curr = head;
        double sum = 0.0;
        
        while(curr != nullptr) {
            sum += curr->coefficient * pow(x, curr->exponent);
            curr = curr->next;             
        }
        return sum;
    }

    friend Polynomial operator+(const Polynomial& p, const Polynomial& q) {

        Polynomial result;

        Term* curr = p.head;
        while(curr != nullptr) {
            result.addTerm(curr->exponent,curr->coefficient);
            curr = curr->next;
        }
        Term* src = q.head;
        while(src != nullptr) {
            result.addTerm(src->exponent, src->coefficient);
            src = src->next;
        }
        return result;
    }

    friend Polynomial operator*(const Polynomial& p, const Polynomial& q) {

        Polynomial result;
        Term* src = q.head;

        while(src != nullptr) {

            Term* curr = p.head;

            while(curr != nullptr) {
                result.addTerm(curr->exponent+src->exponent, curr->coefficient*src->coefficient);
                curr = curr->next;
            }
            src = src->next;
        }
        return result;
    }

    friend ostream& operator<<(ostream& out, const Polynomial& p) {

        if(p.head == nullptr) {
            out << "0";
            return out;
        }

        Term* curr = p.head;
        bool first = true;

        while(curr != nullptr) {
            if(!first) {
                if(curr->coefficient < 0) out << " - ";
                else out << " + ";
            }
            else {
                if(curr->coefficient < 0 ) out << "- ";
            }

            int absCoeff = abs(curr->coefficient);

            if(curr->exponent == 0) {
                out << absCoeff;
            }
            else if(curr->exponent == 1) {
                if(absCoeff == 1) out << "x";
                else out << absCoeff << "x";
            }
            else {
                if(absCoeff == 1) out << "x^" << curr->exponent;
                else out << absCoeff << "x^" << curr->exponent;
            }
            first = false;
            curr = curr->next;
        }
        return out;
    }
private:
    Term* head; // pointer στον πρώτο κόμβο της λίστας (nullptr αν το πολυώνυμο είναι μηδέν)

};

int main() {
    
    Polynomial p;
    p.addTerm(1, 3);   // 3x
    p.addTerm(2, 1);   // x^2
    p.addTerm(0, -1);  // -1

    Polynomial q(p);   // x^2 + 3x - 1
    q.addTerm(1, -3);  // -3x

    cout << "P(x) = " << p << endl;
    cout << "P(1) = " << p.evaluate(1) << endl;
    cout << "Q(x) = " << q << endl;
    cout << "Q(1) = " << q.evaluate(1) << endl;
    cout << "(P+Q)(x) = " << p+q << endl;
    cout << "(P*Q)(x) = " << p*q << endl;

}