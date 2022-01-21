#include "Cavallo.h"

//costruttore
Cavallo::Cavallo(const bool color) {
	setColore(color);


	//bianco
	if (getColore()) {
		setSimbolo('c');
	}
	//nero
	else {
		setSimbolo('C');
	}
}


//metodo move
bool Cavallo::move(const Casella inizio, const Casella arrivo, const bool cattura) {
	//il cavallo ha la seguente mossa:
	/*
	
	
*	bianchi minuscoli
* 
*   0 
	1   c c
	2  c   c
	3    C
	4  c   c
	5   c c
	6 
	7 
	  01234567
	  ABCDEFGH

	  neri
	
	
	*/

	/*
		rispetto alla posizione di partenza si fa una L 
		con un lato di 2 e l'altro di 1

		varie possibilità :
			
			1 in alto, 2 a sx/dx
			2 in alto, 1 a sx/dx

			1 in basso, 2 a sx/dx
			2 in basso, 1 a sx/dx

			che si riassumono in:

			absSpostRighe 1  ,  absSpostCol 2
			absSpostRighe 2  ,  absSpostCol 1

			a patto di stare dentro la scacchiera

	
	*/

	int spostRighe = arrivo.getRiga() - inizio.getRiga(); //spostamento lungo le righe (in alto e in basso)
	int spostColonne = arrivo.getColonna() - inizio.getColonna(); //spostamento lungo le colonne (dx/sx)

	int rig = arrivo.getRiga();
	int col = arrivo.getColonna();

	int absSpostRighe;
	int absSpostCol;

	if (spostRighe >= 0) { absSpostRighe = spostRighe; }
	else { absSpostRighe = spostRighe * (-1); }

	if (spostColonne >= 0) { absSpostCol = spostColonne; }
	else { absSpostCol = spostColonne * (-1); }


	//controlliamo che la posizione di arrivo sia dentro la scacchiera
	if (!dentroScacchiera(rig, col)) {
		return false;
	}

	//controlliamo le varie mosse possibili
	if (absSpostRighe == 1 && absSpostCol == 2) {
		return true;
	}
	if (absSpostRighe == 2 && absSpostCol == 1) {
		return true;
	}

	//a questo punto la mossa deve essere sbagliata
	return false;




}


//il cavallo non deve controllare nulla, quindi ritorna un vettore vuoto
std::vector<Casella> Cavallo::getCaselleIntermedie(const Casella inizio, const Casella fine)
{
	return std::vector<Casella> ();

}

//metodo che da tutte le posizioni dove si può spostare il cavallo data la casella di partenza
	//immaginando la scacchiera vuota
std::vector<Casella> Cavallo::mossePezzo(const Casella inizio) {

	std::vector<Casella> cas;

	//dati di partenza
	int rigaInizio = inizio.getRiga();
	int colonnaInizio = inizio.getColonna();

	//ci sono 8 movimenti possibili

	//1
	Casella temp(rigaInizio + 2, colonnaInizio + 1);
	if (temp.setRiga(rigaInizio + 2) &&  temp.setColonna(colonnaInizio + 1)) {
		cas.push_back(temp);
	}

	//2
	temp.setRiga(rigaInizio + 2);
	temp.setColonna(colonnaInizio - 1);
	if (temp.setRiga(rigaInizio + 2) && temp.setColonna(colonnaInizio - 1)) {
		cas.push_back(temp);
	}

	//3
	temp.setRiga(rigaInizio + 1);
	temp.setColonna(colonnaInizio + 2);
	if (temp.setRiga(rigaInizio + 1) && temp.setColonna(colonnaInizio + 2)) {
		cas.push_back(temp);
	}

	//4
	temp.setRiga(rigaInizio + 1);
	temp.setColonna(colonnaInizio - 2);
	if (temp.setRiga(rigaInizio + 1) && temp.setColonna(colonnaInizio - 2)) {
		cas.push_back(temp);
	}

	//5
	temp.setRiga(rigaInizio - 1);
	temp.setColonna(colonnaInizio + 2);
	if (temp.setRiga(rigaInizio - 1) && temp.setColonna(colonnaInizio + 2)) {
		cas.push_back(temp);
	}

	//6
	temp.setRiga(rigaInizio - 1);
	temp.setColonna(colonnaInizio - 2);
	if (temp.setRiga(rigaInizio - 1) && temp.setColonna(colonnaInizio - 2)) {
		cas.push_back(temp);
	}

	//7
	temp.setRiga(rigaInizio - 2);
	temp.setColonna(colonnaInizio + 1);
	if (temp.setRiga(rigaInizio - 2) && temp.setColonna(colonnaInizio + 1)) {
		cas.push_back(temp);
	}

	//8
	temp.setRiga(rigaInizio - 2);
	temp.setColonna(colonnaInizio - 1);
	if (temp.setRiga(rigaInizio - 2) && temp.setColonna(colonnaInizio - 1)) {
		cas.push_back(temp);
	}


	//ritorna il vettore
	return cas;



}
