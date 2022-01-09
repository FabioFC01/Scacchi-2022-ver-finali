#ifndef Player_h
#define Player_h

//classe che identifica un singolo giocatore
//pu� essere umano o un pc
class Player {
	//dati privati
private:
	//var. booleana
	//1 se il giocatore � bianco
	//0 se � nero
	bool bianco;


	//var. booleana per tipologia di giocatore
	//1 se � umano
	//0 se � pc
	bool umano;



	//metodi pubblici
public:
	//costruttore di default 
	//non usarlo
	Player () {
		bianco = false;
		umano = false;
	}


	//costruttore
	Player(const bool bianco_, const bool giocUmano ) {
		bianco = bianco_;
		umano = giocUmano;
	}




	//per settare il colore del giocatore, arg. bool deve essere
	//true se lo si vuole impostare il giocatore come bianco
	//false se lo si vuole impostare a nero
	void setBianco(const bool col) { bianco = col; }


	//ritorna valore booleano
	//true se il giocatore � bianco
	//false altrimenti
	bool coloreBianco() const { return bianco; }

	//----

	//metodo per impostare se il giocaore � umano o no
	//arg. true per umano
	//arg. false per pc
	void setUmano (const bool um) { umano = um; }


	/*
		ritorna true se il Player � umano
		false altrimenti
	*/
	bool getUmano() const { return umano; }



	//metodo per capire se il giocatore � umano
	//return true se lo �
	//false altrimenti
	bool giocatoreUmano() const { return umano; }





};



#endif