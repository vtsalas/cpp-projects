#include <iostream>

using namespace std;

template <typename T>
class stack {
public:
    //constructor
    stack (int size) {
        num = size;
        n = 0;
        buffer = new T[num];
        }

    stack (const stack &s) {
        num = s.num;
        n = s.n;

        buffer = new T[n];

        for(int i=0; i<n; i++) {
            buffer[i] = s.buffer[i];
        }
    }
    
    ~stack () {
        delete[] buffer;
    }

    const stack & operator = (const stack &s) {
        if (this != &s) {
            
            delete[] buffer;

            num = s.num;
            n = s.n;

            buffer = new T[num];

            for (int i=0; i<n; i++) {
                buffer[i] = s.buffer[i];
            }

        }

        return *this;
    }

    bool empty () {
        return n == 0;
    }

    void push (const T &x) {
        buffer[n] = x;
        n++;
    }

    T pop () {
        n--;
        return buffer[n];
    }

    int size () {
        return n;
    }

    friend ostream & operator << (ostream &out, const stack &s) {
        out << "[";
    
        for (int i=0; i<s.n; i++) {
            out << s.buffer[i];
            if (i < s.n-1) {
                out << ", ";
            }
        }

        out << "]";
        return out;
    }

private:
    T *buffer;
    int num;
    int n;

};


#ifndef CONTEST
 int main () {
    // let’s play with integers...

    stack<int> s(10);
    cout << "s is empty: " << s << endl;

    s.push(42);
    cout << "s has one element: "  << s << endl;

    s.push(17);
    s.push(34);
    cout << "s has more elements: " << s << endl;

    cout << "How many? " << s.size() << endl;

    stack<int> t(5);
    t.push(7);
    cout << "t: " << t << endl;
    t = s;
    cout << "popping from s: " << s.pop() << endl;

    s.push(8);
    
    stack<int> a(s);
    t.push(99);
    a.push(77);
    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    cout << "a: " << a << endl;

    // now with doubles...
    stack<double> c(4);
    c.push(3.14);
    c.push(1.414);
    cout << "c contains doubles " << c << endl;

    // and with characters...
    stack<char> k(4);
    k.push('$');
    cout << "k contains a character: " << k << endl;
    }
#endif



