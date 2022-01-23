//COCIANCICH FABIO - 2016268

#include "Regina.h"

//costruttore
Regina::Regina(const bool color) {
	setColore(color);

	//bianco
	if (getColore()) {
		setSimbolo('d');
	}
	//nero
	else {
		setSimbolo('D');
	}


}

//metodo move
//serve per capire se può fare quella mossa (immaginando una scacchiera tutta vuota
//cattura = true se con questo spostamento posso catturare un pezzo avversario
bool Regina::move(const Casella inizio, const Casella arrivo, const bool cattura) {

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




	//primo controllo da fare, se la posizione di arrivo è dentro la scacchiera
	if (!dentroScacchiera(rig, col)) {
		return false;
	}

	//regina può fare tre tipi di mosse 
		//si muove nelle 8 caselle attorno a lei, tipo il re
		//si muove in diagonale, come l'alfiere
		//si muove in alto, basso, sx, dx, come la torre

	//controlliamo che non voglia fare una mossa dove rimane fermo
	if (spostRighe == 0 && spostColonne == 0) {
		//non puoi fare una mossa fasulla dove rimani fermo
		return false;
	}


	//controlliamo se cerca di muoversi nelle 8 posizioni adiacenti alla sua
	//come il re
	//movimento su / giù
	if (absSpostRighe == 1 && absSpostCol == 0) { return true; }
	//movimenti diagonale (tutti e 4)
	if (absSpostRighe == 1 && absSpostCol == 1) { return true; }
	//movimenti dx/sx
	if (absSpostRighe == 0 && absSpostCol == 1) { return true; }


	//controlliamo se cerca di muoversi in diagonale, come l'alfiere
	if (absSpostCol == absSpostRighe) {
		return true;
	}

	//cerchiamo se vuole muoversi in alto, basso, dx, sx, come la torre
	// 
	//spostamento in alto e in basso
	if (spostColonne == 0 && spostRighe != 0) {
		return true;
	}
	//spostamento a sx/dx
	if (spostColonne != 0 && spostRighe == 0) {
		return true;
	}


	//se sei arrivato qui non è nessuna delle mosse precedenti
	return false;

}


std::vector<Casella> Regina::getCaselleIntermedie(const Casella inizio, const Casella fine) {

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


	//----

	//se fa i movimenti nelle caselle adiacenti come il re
	//non bisogna controllare nulla

	if ((absSpostRighe == 1 && absSpostCol == 0) || (absSpostRighe == 1 && absSpostCol == 1) || (absSpostRighe == 0 && absSpostCol == 1)) {
		return std::vector<Casella>();
	}

	//movimenti da torre , lungo una sola coordinata

	//regina si sposta lungo una riga (cioè un movimento sx/dx)
	if (spostColonne != 0 && spostRighe == 0) {

		//indice della riga nella quale si muove
		int riga = rig;

		//indici delle colonne dove la regina vuole partire e arrivare
		int colPartenza = inizio.getColonna();
		int colArrivo = fine.getColonna();

		
		int colMinore;
		int colMaggiore;

		if (colPartenza < colArrivo) {
			colMinore = colPartenza;
			colMaggiore = colArrivo;
		}
		else {
			colMinore = colArrivo;
			colMaggiore = colPartenza;
		}

		//creo il vettore con le varie caselle
		std::vector<Casella> cas;

		//lo riempio
		for (int j = colMinore + 1; j < colMaggiore; j++) {
			Casella temp(riga, j);
			cas.push_back(temp);
		}

		return cas;

	}


	//spostamento in alto/basso
	if (spostColonne == 0 && spostRighe != 0) {
		//indice colonna (rimane costante nel movimento)
		int colonna = col;

		//indici delle righe dove la regina vuole partire e arrivare
		int rigPartenza = inizio.getRiga();
		int rigArrivo = fine.getRiga();

		int rigMinore;
		int rigMaggiore;

		if (rigPartenza < rigArrivo) {
			rigMinore = rigPartenza;
			rigMaggiore = rigArrivo;
		}
		else {
			rigMinore = rigArrivo;
			rigMaggiore = rigPartenza;
		}

		//creo il vettore con le varie caselle
		std::vector<Casella> cas;

		for (int j = rigMinore + 1; j < rigMaggiore; j++) {
			Casella temp(j, colonna);
			cas.push_back(temp);
		}

		return cas;

	}

	//spostamento in diagonale tipo alfiere
	if (absSpostCol == absSpostRighe) {

		//coordinate di inizio e fine in int
		int rigArrivo = fine.getRiga();
		int rigPartenza = inizio.getRiga();

		int colArrivo = fine.getColonna();
		int colPartenza = inizio.getColonna();

		//-------------

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



//metodo che ridà tutte le posizioni dove la regina si può muovere, contando una scacchiera vuota
std::vector<Casella> Regina::mossePezzo(const Casella inizio) {
	
	std::vector<Casella> cas;

	//dati di partenza
	int rigaInizio = inizio.getRiga();
	int colonnaInizio = inizio.getColonna();


	//SPOSTAMENTO DA ALFIERE

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


	//-----------------------------------
	//SPOSTAMENTI TIPO TORRE


	//dati di partenza
	rigaInizio = inizio.getRiga();
	colonnaInizio = inizio.getColonna();

	spost = 1;

	//movimento verso l'alto
	temp.setRiga(rigaInizio + spost);
	temp.setColonna(colonnaInizio);

	//finchè la casella è dentro la scacchiera
	while (temp.setColonna(colonnaInizio) && temp.setRiga(rigaInizio + spost)) {
		//aggiunta al vector
		cas.push_back(temp);
		//incremento
		spost++;
		//nuova casella
		temp.setColonna(colonnaInizio);
		temp.setRiga(rigaInizio + spost);
	}



	//movimento verso il basso
	spost = 1;
	temp.setColonna(colonnaInizio);
	temp.setRiga(rigaInizio - spost);

	while (temp.setColonna(colonnaInizio) && temp.setRiga(rigaInizio - spost)) {
		//aggiunta al vector
		cas.push_back(temp);
		//incremento
		spost++;
		//nuova casella
		temp.setColonna(colonnaInizio);
		temp.setRiga(rigaInizio - spost);
	}


	//movimento verso destra
	spost = 1;
	temp.setRiga(rigaInizio);
	temp.setColonna(colonnaInizio + spost);

	while (temp.setColonna(colonnaInizio + spost) && temp.setRiga(rigaInizio)) {
		//aggiunta al vector
		cas.push_back(temp);
		//incremento
		spost++;
		//nuova casella
		temp.setColonna(colonnaInizio + spost);
		temp.setRiga(rigaInizio);
	}

	//movimento verso sinistra
	spost = 1;
	temp.setRiga(rigaInizio);
	temp.setColonna(colonnaInizio - spost);

	while (temp.setColonna(colonnaInizio - spost) && temp.setRiga(rigaInizio)) {
		//aggiunta al vector
		cas.push_back(temp);
		//incremento
		spost++;
		//nuova casella
		temp.setColonna(colonnaInizio - spost);
		temp.setRiga(rigaInizio);
	}


	//movimenti finiti
	return cas;


}
