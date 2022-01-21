#include <iostream>
#include "ChessBoard.h"

using namespace std;

int main(int argc, char* argv[])
{
    //formazione scacchiera


    string temp = "";

    if (argc == 2) {
        temp = argv[1];
    }

    ChessBoard scacchi(temp);

    scacchi.stampa();

    scacchi.partita();
    

    cout << "fine programma" << endl;
    return 0;



}
