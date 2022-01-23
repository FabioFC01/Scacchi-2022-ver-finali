//PANOZZO ELISA SILENE

#include "Alfiere.h"
#include <iostream>
using namespace std;
Alfiere::Alfiere(const bool color) {
	setColore(color);

	//bianco
	if (getColore()) {
		setSimbolo('a');
	}
	//nero
	else {
		setSimbolo('A');
	}





}

bool Alfiere::move(const Casella inizio, const Casella arrivo, const bool cattura) {
	//alfiere si muove in diagonale

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


	//controlla che sia dentro la scacchiera la casella di arrivo
	if (!dentroScacchiera(rig, col)) {
		cout << "posizione non presente in scacchiera" << endl;
		return false;
	}

	//controlliamo che la mossa non sia nulla
	if (spostColonne == 0 && spostRighe == 0) {
		return false;
	}

	//mossa valida se absSpostRighe e absSpostCol hanno lo stesso valore
	if (absSpostCol == absSpostRighe) {
		return true;
	}

	//se sei arrivato qui la mossa non può essere valida
	return false;

	
}

std::vector<Casella> Alfiere::getCaselleIntermedie(const Casella inizio, const Casella fine)
{

	int spostRighe = fine.getRiga() - inizio.getRiga(); //spostamento lungo le righe (in alto e in basso)
	int spostColonne = fine.getColonna() - inizio.getColonna(); //spostamento lungo le colonne (dx/sx)

	int rig = fine.getRiga();
	int col = fine.getColonna();

	int absSpostRighe;
	int absSpostCol;

	if (spostRighe >= 0) { absSpostRighe = spostRighe; }
	else { absSpostRighe = spostRighe * (-1); }

	if (spostColonne >= 0) { absSpostCol = spostColonne; }
	else { absSpostCol = spostColonne * (-1); }

	//spostamento in diagonale tipo alfiere
	if (absSpostCol == absSpostRighe) {

		//coordinate di inizio e fine in int
		int rigArrivo = fine.getRiga();
		int rigPartenza = inizio.getRiga();

		int colArrivo = fine.getColonna();
		int colPartenza = inizio.getColonna();

		//valore uguale a 1 se le righe aumentano nello spostamento
		//-1 altrimenti
		int pendenzaRighe;

		if (spostRighe > 0) {
			pendenzaRighe = 1;
		}
		else {
			pendenzaRighe = -1;
		}

		//valore uguale a 1 se le righe aumentano nello spostamento
		//-1 altrimenti
		int pendenzaCol;
		if (spostColonne > 0) {
			pendenzaCol = 1;
		}
		else {
			pendenzaCol = -1;
		}


		//ciclo per mettere le caselle nel vector
		//indici che verranno modificati
		int r = rigPartenza;
		int c = colPartenza;

		//primo incremento degli indici
		//(questo perchè non voglio inserire la casella 
		//di partenza nel vector)
		r += pendenzaRighe;
		c += pendenzaCol;

		std::vector<Casella> cas;

		while ((r != rigArrivo) && (c != colArrivo)) {
			//inserimento della casella nel vector
			Casella temp(r, c);
			cas.push_back(temp);

			//incremento
			r += pendenzaRighe;
			c += pendenzaCol;

		}

		return cas;
	}

	//se sei qui il comando è errato
	return std::vector<Casella>();

	
}


//override del metodo mossePezzo
std::vector<Casella> Alfiere::mossePezzo(const Casella inizio) {

	std::vector<Casella> cas;

	//dati di partenza
	int rigaInizio = inizio.getRiga();
	int colonnaInizio = inizio.getColonna();

	//indice di spostamento (è un valore da aggiungere agli indici di riga e colonna)
	int spost = 1;


	//spostamento in alto a dx  (entrambi gli indici aumentano)
	Casella temp(rigaInizio + spost, colonnaInizio + spost);



	//finchè la casella è dentro la scacchiera
	while (temp.setColonna(colonnaInizio + spost) && temp.setRiga(rigaInizio + spost)) {
		//aggiunta al vector
		cas.push_back(temp);
		//incremento
		spost++;
		//nuova casella
		temp.setColonna(colonnaInizio + spost);
		temp.setRiga(rigaInizio + spost);

	}

	//spostamento in alto a sx  (riga aumenta, colonna diminuisce)
	spost = 1;
	temp.setColonna(colonnaInizio - spost);
	temp.setRiga(rigaInizio + spost);

	while (temp.setColonna(colonnaInizio - spost) && temp.setRiga(rigaInizio + spost)) {
		//aggiunta al vector
		cas.push_back(temp);
		//incremento
		spost++;
		//nuova casella
		temp.setColonna(colonnaInizio - spost);
		temp.setRiga(rigaInizio + spost);

	}

	//spostamento in basso a sx (entrambi gli indici diminuiscono)
	spost = 1;
	temp.setColonna(colonnaInizio - spost);
	temp.setRiga(rigaInizio - spost);

	while (temp.setColonna(colonnaInizio - spost) && temp.setRiga(rigaInizio - spost)) {
		//aggiunta al vector
		cas.push_back(temp);
		//incremento
		spost++;
		//nuova casella
		temp.setColonna(colonnaInizio - spost);
		temp.setRiga(rigaInizio - spost);

	}

	//spostamento in basso a dx (riga diminuisce, colonna aumenta)
	spost = 1;
	temp.setColonna(colonnaInizio + spost);
	temp.setRiga(rigaInizio - spost);

	while (temp.setColonna(colonnaInizio + spost) && temp.setRiga(rigaInizio - spost)) {
		//aggiunta al vector
		cas.push_back(temp);
		//incremento
		spost++;
		//nuova casella
		temp.setColonna(colonnaInizio + spost);
		temp.setRiga(rigaInizio - spost);

	}

	//ritorna il vector con le varie posizioni
	return cas;



}
