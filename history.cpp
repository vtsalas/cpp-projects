#include <iostream>

using namespace std;

class BrowserHistory{
public:

    //Ο κατασκευαστής, πόσο χώρο θα χρειστούμε
    BrowserHistory(int max_pages) {
        capacity = max_pages;
        top = 0;
        urls = new string[capacity];
    }

    //καταστροφέας - distructor
    ~BrowserHistory(){
        delete[] urls;
    }

    //επίσκεψη σε νέα σελίδα, όταν γίνεται επίσκεψη κάνω Push δηλαδή βάζω ένα στοιχείο
    //στο stuck μου, δηλαδή σε αυτό το δυναμικό πίνακα και ταυτόχρονα αυξάνω το top.
    void visit(string new_url) {
        //κάνω αρχικά έναν έλεγχο, καθώς πρέπει το top να μην ξεπεράσει το capacity
        if(top == capacity) {
            cout << "You reached history limit! New url: " << new_url << " can't be saved" << endl;
            return;
        }
        urls[top] = new_url;
        top++;
        cout << "You visited page: " << new_url << endl;
    }

   void back() {
    // 1. Έλεγχος αν μπορούμε καν να κάνουμε back
    if (top == 0) {
        cout << "No last page!" << endl;
        return; 
    }
    
    // 2. Κάνουμε το βήμα πίσω
    top--; 
    
    // 3. Ελέγχουμε πού προσγειωθήκαμε!
    if (top == 0) {
        cout << "Return on home page (New Tab)." << endl;
    } else {
        // ΕΔΩ μπαίνει η δική σου, ολόσωστη διόρθωση!
        cout << "Return on page: " << urls[top - 1] << endl;
    }
}

    void printHistory() {
        cout << "------Browser History------" << endl;

        for(int i=0; i<top; i++){
            cout << i+1 << ") " << urls[i] << endl;
        }

        cout << "---------------------------" << endl;
    }


private:
    //Φτιάχνουμε ένα δείκτη που δείχνει στο πρώτο κουτί ενός πίνακα που θα φτιάξουμε
    //ο οποίος θα αποθηκεύει δυναμικά τα urls, όσα και αν του δώσουμε θα ξέρει πόσο χώρο 
    //θα χρειαστεί για να τα αποθηκεύσει, ο δείκτης θα του δείχνει στο πρώτο κουτί
    //και το πρόγραμμα μας θα συνεχίζει από μόνο του μετά.
    string* urls;

    //θα το χρησιμοποιήσουμε αργότερα για να έχουμε τον αριθμό που θα λάβουμε από τον χρήστη
    //ώστε να μπει στον δυναμικό μας πίνακα
    int capacity;

    //δείχνει πάντα στο τελευταίο στοιχείο που μπήκε στον πίνακα μας,
    //έτσι κάνει δύο δουλειές: 
    //1) μας λέει πόσα στοιχεία έχουμε βάλει στον πίνακα 
    //2) ποιο είναι το επόμενο στοιχείο
    //για να μην χρειάζεται να ψάχνουμε όλο τον πίνακα, φτιάχνουμε πρακτικά έναν μετρητή
    int top;

};

int main() {
    // Φτιάχνουμε ένα ιστορικό που χωράει το πολύ 5 σελίδες
    BrowserHistory myBrowser(1);

    myBrowser.visit("google.com");
    myBrowser.visit("youtube.com/c++_tutorial");
    myBrowser.visit("stackoverflow.com/pointers_help");
    
    myBrowser.printHistory();

    myBrowser.back(); // Πρέπει να μας γυρίσει στο youtube
    myBrowser.back(); // Πρέπει να μας γυρίσει στο google
    
    myBrowser.visit("github.com"); // Το top τώρα γράφει πάνω από το παλιό stackoverflow!

    myBrowser.printHistory();

    return 0;
}