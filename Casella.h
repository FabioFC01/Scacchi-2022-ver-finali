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
		//riga e colonna senn� non sono validi
		//di default
		riga = -1;
		colonna = -1;
			
	}

	//costruttore con argomenti
	Casella(const int riga, const int col);




	//setRiga
	//ritorna true se la riga
	//� dentro la scacchiera
	bool setRiga(const int ri);

	//ritorna il valore della riga
	//da 0 a 7
	int getRiga() const {
		return riga;
	}


	//setColonna
	//ritorna true se la colonna
	//� dentro la scacchiera
	bool setColonna(const int col);


	//ritorna l'indice di colonna
	//da 0 a 7
	int getColonna() const {
		return colonna;
	}

	//metodo che controlla se questa casella � dentro
	//la scacchiera o fuori
	//molto importante specie perch� 
	//il valore di default � -1
	bool casellaValida() const;

	bool casellaValida(const int riga, const int col);






};



#endif