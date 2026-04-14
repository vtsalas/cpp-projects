#include <iostream>
#include <stdexcept> //για να μπορεί να πετάξει το πρόγραμμα μου τα logic errors "out of range"
#include <iomanip>
using namespace std;

class ChessBoardArray{
protected:
    class Row{
    public:
    //σημαντικό! Οι αναφορές (&) και οι const μεταβλητές ΠΑΝΤΑ αρχικοποιούνται στην initializer list.
    //Γιατί; Γιατί μια αναφορά δεν μπορεί να "δείχνει" πουθενά προσωρινά — πρέπει να ξέρει από την αρχή σε τι δείχνει.  
        Row(ChessBoardArray &a, int i) : array(a), row(i) {} 

        int & operator [] (int i) const {
           return array.select(row, i);
        }
    
    private:
        int row; //ποια γραμμή είναι
        ChessBoardArray &array; //για να ξέρουμε ποιον πίνακα θέλουμε
    };

    class ConstRow{
    public:
        ConstRow(const ChessBoardArray &a, int i) : array(a), row(i) {}
        int operator [] (int i) const {
            return array.select(row, i);
        }

    private:
        int row;
        const ChessBoardArray &array;

    };

public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0) {
        s = size;
        b = base;

        //σημείωση! Εδώ το () μηδενίζει όλα τα στοιχεία της μνήμης που πάμε να δεσμεύσουμε, ώστε να μην έχουμε σκουπίδα
        data = new int[s*s/2](); 
    }
    ChessBoardArray(const ChessBoardArray &a) {
        s = a.s;
        b = a.b;

        data = new int[s*s/2]();

        for(int i = 0; i<(s*s/2); i++) {
            data[i] = a.data[i];
        }
    }

    ~ChessBoardArray() {
        delete[] data;
    }

    ChessBoardArray & operator = (const ChessBoardArray &a) {
        // Έλεγχος self-assignment (π.χ. a = a): αν ο τρέχων
        // αντικείμενο είναι το ίδιο με το a, δεν κάνουμε τίποτα.
        // Χωρίς αυτόν τον έλεγχο, θα διαγράφαμε τα δεδομένα μας
        // πριν τα αντιγράψουμε, με αποτέλεσμα crash!
        if(this != &a) {

            delete[] data;

            s = a.s;
            b = a.b;

            data = new int[s*s/2]();

            for(int i = 0; i<(s*s/2); i++) {
                 data[i] = a.data[i];
              }

        }
        return *this;
    }

    int & select(int i, int j) {
        int index = loc(i, j);
        return data[index];
    }

    int select(int i, int j) const {
        int index = loc(i, j);
        return data[index];
    }

    const Row operator [] (int i) {
        return Row(*this, i);
    }
    const ConstRow operator [] (int i) const {
        return ConstRow(*this, i);
    }

    friend ostream & operator << (ostream &out, const ChessBoardArray &a) {
        for(int i = a.b; i < a.b + a.s; i++) {
            for(int j = a.b; j < a.b + a.s; j++) {
                if((i + j) % 2 == 0)
                    out << setw(4) << a.select(i, j);  // λευκό
                else
                    out << setw(4) << 0;               // μαύρο
            }
            out << endl;
        }
    return out;
        
    }

private:
    int* data;
    unsigned int s; //size
    unsigned int b; //base

    unsigned int loc(int i, int j) const {
      if((i + j) % 2 != 0) throw out_of_range("black square");
      return (i - b) * (s / 2) + (j - b) / 2;  
    }
};

int main() {
    ChessBoardArray a(4, 1); // size 4x4, rows and columns numbered from 1
    a[3][1] = 42;
    a[4][4] = 17;
    try { a[2][1] = 7; }
    catch(out_of_range &e) { cout << "a[2][1] is black" << endl; }
    try { cout << a[1][2] << endl; }
    catch(out_of_range &e) { cout << "and so is a[1][2]" << endl; }
    cout << a;
}
