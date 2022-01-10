#include "Casella.h"



//costruttore con argomenti
Casella::Casella(int riga, int col) {
	//prova a settare la riga con l'arg. passato
	//se fallisci, imposta il valore -1
	if (!setRiga(riga)) { setRiga(-1); }
	//idem per la colonna
	if (!setColonna(col)) { setColonna(-1); }



}

bool Casella::setRiga(int ri) {
	//controllo che la riga non sia
	//fuori dalla scacchiera
	if (ri < 0 || ri > 7) {
		return false;
	}
	riga = ri;
	return true;
}

//setColonna
	//ritorna true se la colonna
	//� dentro la scacchiera
bool Casella::setColonna(int col) {
	//controllo che la riga non sia
	//fuori dalla scacchiera
	if (col < 0 || col > 7) {
		return false;
	}
	colonna = col;
	return true;
}

//metodo che controlla se questa casella � dentro
	//la scacchiera o fuori
	//molto importante specie perch� 
	//il valore di default � -1
bool Casella::casellaValida() const {

	//se almeno uno dei due parametri � fuori ritorna false
	if (riga < 0 || riga > 7 || colonna < 0 || colonna > 7) {
		return false;
	}
	//altrimenti ritorna vero
	return true;

}

bool Casella::casellaValida(const int riga, const int col) {
	//se almeno uno dei due parametri � fuori ritorna false
	if (riga < 0 || riga > 7 || colonna < 0 || colonna > 7) {
		return false;
	}
	//altrimenti ritorna vero
	return true;
}