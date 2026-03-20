#include <iostream>
using namespace std;

//Αρχικά δηλώνω τις συναρτήσεις πριν την main για να ξέρει ο compiler ότι υπάρχουν

void showMenu();
void deposit(double &balance, double amount);
void withdraw(double &balance, double amount);

int main() {

    double balance = 1000.0; //Αρχικό υπόλοιπο λογαριασμού
    int choice; //Μεταβλητή για την επιλογή του χρήστη
    double amount; //Μεταβλητή για το ποσό ανάληψης ή κατάθεσης

    cout << "Welcome to Vasilis Bank!\n";

    do {
        showMenu();
        cout << "Select an action(1-4): ";
        cin >> choice;

           switch (choice)
           {
            case 1:
                cout << "Your Balance is: " << balance << endl;
             
                break;
            case 2:
                cout << "Put amount of deposit: ";
                cin >> amount;

                deposit(balance, amount);
           
                break;
            case 3:
                cout << "Put amount of withdraw: ";
                cin >> amount;

                withdraw(balance, amount);

                break;
            case 4:
                cout << "Thank you for choosing Vasilis Bank!\n";
                break;
           
            default:
                cout << "Error: Invalid action! Please try again\n";
            }

    } while(choice!=4);

    return 0;
}

void showMenu() {
    cout << "****************************\n";
    cout << "****** Starting Menu *******\n";
    cout << "1. Show Balance\n" << "2. Deposit\n" << "3. Withdraw\n" << "4. Close\n";
}

void deposit(double &balance, double amount) {
    balance += amount;

    cout << "Deposit was succesful!\n";

}

void withdraw(double &balance, double amount) {
    if(amount <= balance) {
        balance -= amount;
        cout << "Withdraw was succesful!\n";

    }
    else {
        cout << "Error: Not enough balance!\n";
    }
}