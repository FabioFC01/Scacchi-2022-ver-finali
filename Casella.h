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
	Casella(const int riga, const int col) {
		//prova a settare la riga con l'arg. passato
		//se fallisci, imposta il valore -1
		if (!setRiga(riga)) { setRiga(-1); }
		//idem per la colonna
		if (!setColonna(col)) { setColonna(-1); }



	}




	//setRiga
	//ritorna true se la riga
	//è dentro la scacchiera
	bool setRiga(const int ri) {
		//controllo che la riga non sia
		//fuori dalla scacchiera
		if (ri < 0 || ri > 7) {
			return false;
		}
		riga = ri;
		return true;
	}

	//ritorna il valore della riga
	//da 0 a 7
	int getRiga() const {
		return riga;
	}


	//setColonna
	//ritorna true se la colonna
	//è dentro la scacchiera
	bool setColonna(const int col) {
		//controllo che la riga non sia
		//fuori dalla scacchiera
		if (col < 0 || col > 7) {
			return false;
		}
		colonna = col;
		return true;
	}


	//ritorna l'indice di colonna
	//da 0 a 7
	int getColonna() const {
		return colonna;
	}

	//metodo che controlla se questa casella è dentro
	//la scacchiera o fuori
	//molto importante specie perchè 
	//il valore di default è -1
	bool casellaValida() const {

		//se almeno uno dei due parametri è fuori ritorna false
		if (riga < 0 || riga > 7 || colonna < 0 || colonna > 7) {
			return false;
		}
		//altrimenti ritorna vero
		return true;

	}

	bool casellaValida(const int riga, const int col) {
		//se almeno uno dei due parametri è fuori ritorna false
		if (riga < 0 || riga > 7 || colonna < 0 || colonna > 7) {
			return false;
		}
		//altrimenti ritorna vero
		return true;
	}






};



#endif