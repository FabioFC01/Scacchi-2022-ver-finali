#include <iostream>
#include "ChessBoard.h"

using namespace std;

int main()
{
    
    //formazione scacchiera


    ChessBoard scacchi;

    scacchi.stampa();

    


    //scacchi.sceltaPartita();


    //ad es una delle due
    //scacchi.partita_1();


    scacchi.partita();
    

   




    cout << "fine programma" << endl;
    return 0;



}

//chess.cpp
/*
    matrice char [8] [8] --- per stampare a schermo

    pezzi contraddistinti da classi per gestire le loro caratteristiche

    riga---numero
    colonna --- lettera


    //es. torrre in A1 all'inizio
    int riga = 1;
    char colonna = A;

    riga++;


    --
    es.
    classe pedone, ed è l'oggetto pedone che si muove
    riga++;

    classe pedone, però è la classe scacchiera che lo muove
    pedone.setRiga(ecc...)






*/


/*
//gestione file

main.cpp --- main    --- gestisce argomenti da riga di comando

chess.cpp --- gestisce scacchiera e inizializza pezzi vari
chess.h -- relativo header


Pezzo.h --- header file della classe Pezzo
i vari pezzi saranno classi derivate della classe Pezzo

pedone.cpp
torre.cpp
cavaliere.cpp
alfiere.cpp
regina.cpp
re.cpp

pedone.h
torre.h
cavaliere.h
alfiere.h
regina.h
re.h






*/

/*
    in ogni classe di un pezzo

    dati sulla posizione
        riga
        colonna

    metodi per ottenere e modificare posizione


    //es alfiere
    bool metodo move(int riga, char colonna) {
        
        //controlla che la posizione data sia in diagonale 
        //e non occupata da uno dei suoi pezzi

        //se ciò è rispettato si può muovere e ritorna true
        //se non può farlo ritorna false




    }


    //chiamata del metodo move

    while (! pedone.move(posizione dove deve andare)) {
        //ritenta
    }

    //è riuscito a fare una mossa




*/


/*
replay.cpp

e sotto file


ogni mossa che facciamo la scriviamo nel log 

es
pedone da A2 a A3

A2 A3
A3 A4
A4 A5


xx



*/


//-------------------------------------------------------------------------------
//APPUNTI VARI
//https://www.codeproject.com/Articles/1214018/Chess-Console-Game-in-Cplusplus
// 
// 
// https://codereview.stackexchange.com/questions/173656/chess-game-in-c
// 
// 
// https://www.linkedin.com/pulse/writing-simple-chess-engine-c-baran-can-%C3%B6ner-cfa/
// 
// 
// mooolto interressante
// https://www.geeksforgeeks.org/design-a-chess-game/
// 
// https://inst.eecs.berkeley.edu/~cs162/sp07/Nachos/chess.shtml
// 
// 
// http://www.unife.it/scienze/informatica/insegnamenti/programmazione-e-laboratorio/materiale-didattico-anni-precedenti/materiale-didattico-a-a-2016-17/diapositive/160-argomenti-della-linea-di-comando
// 
// 
//link con idee carine da prendere direi