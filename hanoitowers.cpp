#include <iostream>
using namespace std;

//n = το πλήθος των δίσκων
//fromRoad = ο δίσκος από τον οποίο ξεκινάω
//toRoad = ο δίσκος στον οποίο θέλω να πάω
//auxRoad = ο δίκσος που χρησιμοποιώ ως βοηθητικό

void hanoiTowers(int n, char fromRoad, char toRoad, char auxRoad);

int main(){
    int numDisks;

    cout << "**********Hanoi Towers**********\n";
    cout << "Give me number of disks: ";

    cin >> numDisks;
    
    cout << "The steps to solve the riddle are: " << endl;

    hanoiTowers(numDisks, 'A', 'C', 'B');


    return 0;
}

void hanoiTowers(int n, char fromRoad, char toRoad, char auxRoad) {
    if(n == 1) {
        cout << "Move disk " << n << " from " << fromRoad << " to " << toRoad << endl;
        return;
    }
    hanoiTowers(n-1, fromRoad, auxRoad, toRoad);

    cout << "Move disk " << n << " from " << fromRoad << " to " << toRoad << endl;

    hanoiTowers(n-1, auxRoad, toRoad, fromRoad);
}