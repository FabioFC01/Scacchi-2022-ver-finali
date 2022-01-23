// COCIANCICH FABIO - 2016268

#ifndef PEZZO_H
#define PEZZO_H


#include "Casella.h"
#include "Mossa.h"


#include <vector>



class Casella;

class Pezzo {
	//classe di un pezzo casuale
	//le classi del pedone, torre, regina ecc...
	//saranno classi derivate di classe Pezzo


	/*
	scacchiera

	8
	7
	6
	5
	4
	3
	2
	1
	    A B C D E F G H
	
	
	
	
	
	*/

private:

	/*
		nella classe Pezzo :
			riga sarà l'indice delle righe della matrice (da 0 a 7)
			colonna sarà la stessa cosa (da 0 a 7)


			es. B7 ---> riga (7-1) = 6
						colonna B --> 1


				A	0
				B	1
				C	2
				D	3
				E	4
				F	5
				G	6
				H	7

	
	*/
	

	//1 per i bianchi
	//0 per i neri
	bool colore;


	//simbolo char da stampare a video
	//che rappresenta il pezzo
	char simbolo;



public:
	//setta il colore
	//1 per i bianchi, 0 per i neri
	void setColore(const bool b);

	//1 per i bianchi, 0 per i neri
	bool getColore() const { return colore; }

	bool dentroScacchiera(const int rig, const int col) const;

	//metodi per i simboli dei pezzi
	//bianchi minuscoli, neri maiuscoli
	char getSimbolo() const { return simbolo; }
	void setSimbolo(const char c) { simbolo = c; }


	//metodo per dare le posizioni intermedie tra la casella di inizio e di fine
	//dello spostamento
	virtual std::vector<Casella> getCaselleIntermedie(const Casella inizio, const Casella fine) = 0;


	//metodo virtuale che, data una casella di partenza, dà un elenco di posizioni 
	//nelle quali il pezzo può spostarsi (considerando una scacchiera vuota)
	virtual std::vector<Casella> mossePezzo(const Casella inizio) = 0;


	//METODO MOVE
	//metodo più importante, quello per muovere il pezzo
	//deve fare il controllo che sia possibile far tale mossa
	// immaginando che il pezzo si muova in una scacchiera vuota
	 virtual bool move(const Casella inizio, const Casella arrivo, const bool cattura) = 0;
	





	 


};



#endif