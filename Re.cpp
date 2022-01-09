#include "Re.h"

//costruttore
Re::Re(const bool color) {
	setColore(color);
	setCatturato(false);


	//bianco
	if (getColore()) {
		setSimbolo('r');
	}
	//nero
	else {
		setSimbolo('R');
	}

}

//metodo move
//serve per capire se può fare quella mossa (immaginando una scacchiera tutta vuota
//cattura = true se con questo spostamento posso catturare un pezzo avversario
bool Re::move(const Casella inizio, const Casella arrivo, const bool cattura) {

	int absSpostRighe = arrivo.getRiga() - inizio.getRiga(); //spostamento lungo le righe (in alto e in basso)
	int absSpostColonne = arrivo.getColonna() - inizio.getColonna(); //spostamento lungo le colonne (dx/sx)

	//rendiamo questi valori assoluti
	if (absSpostRighe < 0) { absSpostRighe *= -1; }
	if (absSpostColonne < 0) { absSpostColonne *= -1;}


	int rig = arrivo.getRiga();
	int col = arrivo.getColonna();

	//primo controllo da fare, se la posizione di arrivo è dentro la scacchiera
	if (!dentroScacchiera(rig, col)) {
		return false;
	}

	//il re ha comportamenti nel movimento indipendenti dal suo colore

	//il re può muoversi in tutte le direzioni adiacenti

	//movimento su / giù
	if (absSpostRighe == 1 && absSpostColonne == 0) { return true; }
	//movimenti diagonale (tutti e 4)
	if (absSpostRighe == 1 && absSpostColonne == 1) { return true; }
	//movimenti dx/sx
	if (absSpostRighe == 0 && absSpostColonne == 1) { return true; }

	//se non è nessuno di questi deve essere un movimento errato per forza
	return false;


}


//il re si muove soltanto nelle caselle adiacenti, quindi non bisogna controllare nulla
std::vector<Casella> Re::getCaselleIntermedie(const Casella inizio, const Casella fine) {

	return vector<Casella> ();

}

//metodo che da tutte le posizioni dove si può spostare il re data la casella di partenza
	//immaginando la scacchiera vuota
std::vector<Casella> Re::mossePezzo(const Casella inizio) {
	
	std::vector<Casella> cas;

	int rigaInizio = inizio.getRiga();
	int colonnaInizio = inizio.getColonna();

	//alto a dx
	Casella temp(rigaInizio + 1, colonnaInizio + 1);

	if (temp.setRiga(rigaInizio + 1) && temp.setColonna(colonnaInizio + 1)) {
		cas.push_back(temp);
	}

	//alto 
	temp.setColonna(colonnaInizio);
	if (temp.setRiga(rigaInizio + 1) && temp.setColonna(colonnaInizio)) {
		cas.push_back(temp);
	}

	//alto a sx
	temp.setColonna(colonnaInizio - 1);
	if (temp.setRiga(rigaInizio + 1) && temp.setColonna(colonnaInizio - 1)) {
		cas.push_back(temp);
	}

	//sx
	temp.setRiga(rigaInizio);
	if (temp.setRiga(rigaInizio) && temp.setColonna(colonnaInizio - 1)) {
		cas.push_back(temp);
	}

	//basso a sx
	temp.setRiga(rigaInizio - 1);
	if (temp.setRiga(rigaInizio - 1) && temp.setColonna(colonnaInizio - 1)) {
		cas.push_back(temp);
	}

	//basso
	temp.setColonna(colonnaInizio);
	if (temp.setRiga(rigaInizio - 1) && temp.setColonna(colonnaInizio)) {
		cas.push_back(temp);
	}

	//basso a dx
	temp.setColonna(colonnaInizio + 1);
	if (temp.setRiga(rigaInizio - 1) && temp.setColonna(colonnaInizio + 1)) {
		cas.push_back(temp);
	}

	//dx
	temp.setRiga(rigaInizio);
	if (temp.setRiga(rigaInizio) && temp.setColonna(colonnaInizio + 1)) {
		cas.push_back(temp);
	}

	//-----
	//ritorna
	return cas;





}