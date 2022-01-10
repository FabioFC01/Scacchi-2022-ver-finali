#ifndef Mossa_h
#define Mossa_h

//per poter indicare le caselle di partenza
//e arrivo della mossa
#include "Casella.h"
#include "Pezzo.h"
#include "Player.h"




//classe che identifica una singola mossa
//e le sue varie caratteristiche
//molto utile per tutti i vari tipi di mosse
//strane che ci sono negli scacchi
class Mossa {

private:
	//giocatore che fa la mossa
	//Player giocatore;

	//le due caselle di partenza e arrivo 
	Casella partenza;
	Casella arrivo;




	//Pezzo mosso;

	//ammesso che ci sia
	//Pezzo catturato;









public:
	//costruttore
	Mossa(Casella &part, Casella &arr);

	Casella getCasellaPartenza() const {
		return partenza;
	}

	Casella getCasellaArrivo() const {
		return arrivo;
	}



};




#endif