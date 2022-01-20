#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


#include "Pezzo.h"

#include "Pedone.h"
#include "Re.h"
#include "Regina.h"
#include "Cavallo.h"
#include "Alfiere.h"
#include "Torre.h"



#include "Player.h"
#include "Mossa.h"
#include "Casella.h"

#include "Exception.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */



class ChessBoard {
	//classe con la scacchiera, gestione dei pezzi
	//e della partita


	/*
	* 
	* Configurazione iniziale scacchiera
	
	8 TCADRACT
	7 PPPPPPPP
	6
	5
	4
	3
	2 pppppppp
	1 tcadract
	  ABCDEFGH


	  dove
	  P pedone
	  T torre
	  C cavallo
	  A alfiere
	  D regina
	  R re


	  ---
	  MAIUSCOLE --- PEZZI NERI
	  minuscole --- pezzi bianchi

	  inizia il bianco





	
	
	*/

private:
	//scacchiera dove metteremo i pezzi segnati da lettere
	// utile per la stampa
	//          [ riga ]  [ colonna ]
	//char scacchiera_char[8][8];


	//scacchiera con i puntatori a superclasse
	//scacchiera[riga][colonna]
	Pezzo* scacchiera[8][8];


	//0 per partita giocatore - pc
	//1 per partita pc - pc
	bool tipoPartita;



	//valore booleano per capire di chi è il turno
	/*
	* turno = 0 significa che è il turno del nero
	* turno = 1 significa che è il turno del bianco
	* 
	* viene inizializzato con valore 1, in quanto per regolamento il primo a fare la mossa è il bianco
	
	*/
	bool turno;


	//valore booleano per capire se si è arrivati allo scacco matto
	//inizializzato a false, diventa true se si verifica la situazione di scacco matto
	bool scaccoMatto;


	//valore booleano che mi serve a capire se la partita è terminata
	bool partitaTerminata;

	enum stato { Attiva = 0, ScaccoMatto = 1, Stallo = 2, Patta = 3 };
	stato statoPartita;


	//vettori con i vari pezzi
	//std::vector<Pezzo*> giocBianco;
	//std::vector<Pezzo*> giocNero;


	Player giocBianco;
	Player giocNero;



	//limite massimo di mosse per una partita tra due pc
	const int maxMossePc = 800;


	//mappa per tenere memoria delle varie posizioni dei
	//pezzi nella scacchiera durante la partita
	std::map<string, int> mappa;




public:
	ChessBoard(string arg);	//costruttore



	void resetScacchiera();

	Pezzo* getPezzo(int rig, int col) const;




	//funzione di chiamata per il move
	bool call(Pezzo* pez, const Casella inizio, const Casella arrivo, const bool cattura);




	void sceltaPartita(string arg);


	/*
		metodo principale che gestisce la partita
	
	*/
	void partita(); 


	//metodo stampa
	void stampa() const;

	//metodo per tradurre la scacchiera in una stringa
	string scacchieraInStringa() const;
	

	//metodo per chiedere al giocatore umano l'input per la mossa
	Mossa input();

	//funzione che prende una mossa e ridà una stringa
	//con le coordinate in lettere e numeri
	string coordinateInTesto(Mossa m);


	//metodo per controllare che l'input per il movimento sia corretto
	//es. B1 C3 è un corretto comando, deve avere la coordinata di partenza
	//e quella di arrivo
	bool inputCorretto(const Mossa &prossimaMossa);


	//funzione che controlla tutto quello che c'è da controllare per
	//verificare la correttezza di tale mossa
	//se la mossa è corretta viene eseguito
	bool mossaFattibile(const Mossa& prossimaMossa);


	/*
	metodo che controlla se i pezzi avversari (rispetto a chi gioca quel turno)
	mettono sotto scacco il re

	ritorna true se il re di chi ha il turno ora è sotto scacco, false altrimenti

*/
	bool reSottoScacco();


	/*
		metodo per cambiare turno
		se viene chiamato quando nel turno del bianco
		il prossimo sarà il turno del nero
		e viceversa
	
	*/
	void cambiaTurno();


	/*
		metodo che controlla se un giocatore può fare
		almeno una mossa considerata regolare
		ritorna true se può farne almeno una,
		false altrimenti
	
	*/
	bool possoFareMosse();


	/*
		metodo che guarda di chi è il turno
		e che tipo di giocatore è quello che ha tale turno
		( cioè se è giocatore umano o pc)
		e fa una mossa sulla scacchiera
		Se il giocatore è umano chiede in input una mossa
		fino a quando è una mossa regolare (a quel punto la fa)
		Se il giocatore è pc cerca nella scacchiera un pezzo del suo colore
		e cerca di fare una mossa legale, sennò cerca altri pezzi e
		rifà lo stesso procedimento fino a quando riesce a fare una mossa legale

		ritorna un valore true se è stato spostato un pedone
		false altrimenti

		ritorna la mossa fatta
	*/
	Mossa faiMossa();


	//metodo per contare quanti pezzi ci sono nella scacchiera
	int contaPezzi();






	
	
	
};



#endif