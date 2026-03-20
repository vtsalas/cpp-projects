#include <iostream>
using namespace std;

void drawBoard(char board[3][3]);
bool checkWin(char board[3][3], char player);
bool checkDraw(char board[3][3]);


int main(){

    //Αρχικοποίηση του πίνακα 3Χ3 με κενά
    
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char currentPlayer = 'X'; //Ο παίκτης 1 ξεκινάει με το Χ

    bool gameWon = false;
    bool gameDraw = false;

    cout << "Welcome to Tic-Tac-Toe game!\n";

    while(!gameWon && !gameDraw){
        drawBoard(board);
        
        int row, col, r, c;
        
        cout << "Player " << currentPlayer << ", give row(1-3) and column(1-3) with space in between\n";
        cin >> row >> col;

        if(cin.fail()) {
            cin.clear(); // Επαναφέρει την cin σε κανονική λειτουργία
        }

        cin.ignore(10000, '\n');



        r = row - 1;
        c = col - 1;

        if(r>=0 && r<=2 && c>=0 && c<=2 && board[r][c] == ' '){
            board[r][c] = currentPlayer;
        }
        else {
            cout << "Invalid Move!";
            continue;
        } 

        if(checkWin(board, currentPlayer)){
            gameWon = true;
            drawBoard(board);
            cout << "Congratulations! Player " << currentPlayer << " has Won!\n";
            break;
        }

        if(checkDraw(board)){
            gameDraw = true;
            drawBoard(board);
            cout << "We have a Draw! Good Game!\n";
            break;
        }

        if(currentPlayer=='X') {
            currentPlayer = 'O';
        }
        else {
            currentPlayer = 'X';
        }

    }
    
    return 0;
}

void drawBoard(char board[3][3]) {
    cout << "\n";
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    cout << "\n";

}

bool checkWin(char board[3][3], char player){
    if(board[0][0]==player && board[0][1]==player && board[0][2]==player) return true;
    if(board[1][0]==player && board[1][1]==player && board[1][2]==player) return true;
    if(board[2][0]==player && board[2][1]==player && board[2][2]==player) return true;
    if(board[0][0]==player && board[1][0]==player && board[2][0]==player) return true;
    if(board[0][1]==player && board[1][1]==player && board[2][1]==player) return true;
    if(board[0][2]==player && board[1][2]==player && board[2][2]==player) return true;
    if(board[0][0]==player && board[1][1]==player && board[2][2]==player) return true;
    if(board[2][0]==player && board[1][1]==player && board[0][2]==player) return true;
    return false;
}

bool checkDraw(char board[3][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j] == ' ') return false;
        }
    }
    return true;
}