#ifndef Casella_h
#define Casella_h


//classe che identifica una singola casella
//sulla scacchiera
class Casella {
	//parte privata
private:
	//coordinate della casella
	int riga;
	int colonna;


public:
	//costruttore
	Casella() {
		//importante
		//quando si inizializza una nuova vasella
		//poi bisogna impostare i valori di 
		//riga e colonna sennò non sono validi
		//di default
		riga = -1;
		colonna = -1;
			
	}

	//costruttore con argomenti
	Casella(int riga,  int col);




	//setRiga
	//ritorna true se la riga
	//è dentro la scacchiera
	bool setRiga( int ri);

	//ritorna il valore della riga
	//da 0 a 7
	int getRiga() const {
		return riga;
	}


	//setColonna
	//ritorna true se la colonna
	//è dentro la scacchiera
	bool setColonna(int col);


	//ritorna l'indice di colonna
	//da 0 a 7
	int getColonna() const {
		return colonna;
	}

	//metodo che controlla se questa casella è dentro
	//la scacchiera o fuori
	bool casellaValida() const;

	//metodo che controlla se questa casella è dentro
	//la scacchiera o fuori (controlla gli argomenti)
	bool casellaValida(const int riga, const int col);






};



#endif