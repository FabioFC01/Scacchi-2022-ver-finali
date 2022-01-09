#include "Pedone.h"


//costruttore della classe pedonei
Pedone::Pedone( const bool color) {
	
	//inizializziamo la var. booleana a true
	primaMossa = true;


	//chiamo i metodi della classe Pezzo
	//per inizializzare il colore
	setColore(color);

	setCatturato(false);



	//bianco
	if (getColore()) {
		setSimbolo('p');
	}
	//nero
	else {
		setSimbolo('P');
	}

	



}

//il pedone solitamente si muove andando lungo le righe e non cambia colonna
//i pedoni bianchi si muovono in ordine crescente di righe,
//i neri in ordine decrescente di righe

//rig e col designano le coordinate di arrivo
//cattura = true se con questo spostamento posso catturare un pezzo avversario
bool Pedone::move(const Casella inizio, const Casella arrivo, const bool cattura) {

	int spostRighe = arrivo.getRiga() - inizio.getRiga(); //spostamento lungo le righe (in alto e in basso)
	int spostColonne = arrivo.getColonna() - inizio.getColonna(); //spostamento lungo le colonne (dx/sx)

	int rig = arrivo.getRiga();
	int col = arrivo.getColonna();

	//primo controllo da fare, se la posizione di arrivo � dentro la scacchiera
	if (! dentroScacchiera(rig, col)) {
		return false;
	}

	//se � pedone bianco
	if (getColore()) {
		//se non ha ancora fatto la prima mossa pu� spostarsi di due in avanti (se non c'� nessuno da mangiare)
		if (primaMossa && (spostRighe == 2 || spostRighe == 1 ) && (spostColonne == 0)  &&  (cattura == false) ) {

			//spostamento lungo le righe
			primaMossa = false;

			return true;	//successo, puoi muoverti

		}
		//se lo spostamento lungo le righe � di uno in alto
		if (spostRighe == 1 && spostColonne == 0 && (cattura == false) ) {
			
			return true;
		}
		//le due mosse laterali che si possono fare solo se puoi catturare un pezzo avversario
		if (cattura && ((spostRighe==1 && spostColonne == 1) || (spostRighe == 1 && spostColonne == -1)) ) {
			
			if (primaMossa) { primaMossa = false; }

			return true;

		}
		else {
			
			
			return false;
		}
	}
	//se � pedone nero
	else {
		//se non ha ancora fatto la prima mossa pu� spostarsi di due in avanti (se non c'� nessuno da catturare)
		if (primaMossa && (spostRighe == -2 || spostRighe == -1) && spostColonne == 0  && (cattura == false) ) {
			primaMossa = false;

			return true;	//successo
		}
		//mossa di 1 in avanti (se non c'� nessuno da catturare)
		if (spostRighe == -1 && spostColonne == 0  && (cattura == false)) {
			return true;
		}
		//le due mosse laterali che si possono fare solo se puoi catturare un pezzo avversario
		if (cattura && ((spostRighe == -1 && spostColonne == 1) || (spostRighe == -1 && spostColonne == -1))) {
			

			if (primaMossa) { primaMossa = false; }

			return true;

		}

		else {
			return false;
		}

	}


	return true;
}


std::vector<Casella> Pedone::getCaselleIntermedie(const Casella inizio, const Casella fine) {

	//l'unico caso nel quale c'� una casella da controllare � quando fa la prima mossa
	//e fa un salto di due in avanti, in tutti gli altri casi si ritorna un vector vuoto

	int spostRighe = fine.getRiga() - inizio.getRiga(); //spostamento lungo le righe (in alto e in basso)
	int spostColonne = fine.getColonna() - inizio.getColonna(); //spostamento lungo le colonne (dx/sx)

	//valore assoluto di spostamento di indici di riga
	int absSpostRighe;

	if (spostRighe > 0) { absSpostRighe = spostRighe; }
	else { absSpostRighe = spostRighe * (-1); }
	

	//se si tratta di uno spostamento di due in alto/basso (dipende dal colore del pezzo)
	if (absSpostRighe == 2 && spostColonne == 0) {

		//valore che sar� uguale a 1 se il pedone si sta muovendo verso l'alto
		//sar� uguale a -1 se si star� muovendo verso il basso
		int alto_basso = 0;

		//se il movimento � verso l'alto
		if (spostRighe > 0) {
			alto_basso = 1;
		}
		//se il movimento � verso il basso
		else {
			alto_basso = -1;
		}

		//questa � la casella che viene saltata in uno spostamento di 2 in avanti 
		//del pedone
		Casella temp(inizio.getRiga() + alto_basso, inizio.getColonna() );

		std::vector<Casella> cas;
		
		cas.push_back(temp);

		return cas;



	}











	//crea vettore a caso
	return std::vector<Casella> ();

	

}


//metodo che da tutte le posizioni dove si pu� spostare il cavallo data la casella di partenza
	//immaginando la scacchiera vuota
std::vector<Casella> Pedone::mossePezzo(const Casella inizio) {

	std::vector<Casella> cas;

	int rigaInizio = inizio.getRiga();
	int colonnaInizio = inizio.getColonna();

	Casella temp(-1, -1);

	//se � bianco
	if (getColore()) {

		//due posizioni in avanti
		if (primaMossa) {
			temp.setRiga(rigaInizio + 2);
			temp.setColonna(colonnaInizio);
			if (temp.setRiga(rigaInizio + 2) && temp.setColonna(colonnaInizio)) {
				cas.push_back(temp);
			}
		}

		//1 in avanti
		temp.setRiga(rigaInizio + 1);
		temp.setColonna(colonnaInizio);
		if (temp.setRiga(rigaInizio + 1) && temp.setColonna(colonnaInizio)) {
			cas.push_back(temp);
		}

		//se nella posizione in alto a sx c'� un pezzo avversario
		temp.setRiga(rigaInizio + 1);
		temp.setColonna(colonnaInizio - 1);
		if (temp.setRiga(rigaInizio + 1) && temp.setColonna(colonnaInizio - 1)) {
			cas.push_back(temp);
		}

		//se nella posizione in alto a dx c'� un pezzo avversario
		//verr� controllato nel metodo chiamante
		temp.setRiga(rigaInizio + 1);
		temp.setColonna(colonnaInizio + 1);
		if (temp.setRiga(rigaInizio + 1) && temp.setColonna(colonnaInizio + 1)) {
			cas.push_back(temp);

		}


	}


	//se � nero
	if (!getColore()) {

		//due posizioni in basso
		if (primaMossa) {
			temp.setRiga(rigaInizio - 2);
			temp.setColonna(colonnaInizio);
			if (temp.setRiga(rigaInizio - 2) && temp.setColonna(colonnaInizio)) {
				cas.push_back(temp);
			}
		}

		//1 in basso
		temp.setRiga(rigaInizio - 1);
		temp.setColonna(colonnaInizio);
		if (temp.setRiga(rigaInizio - 1) && temp.setColonna(colonnaInizio)) {
			cas.push_back(temp);
		}

		//se nella posizione in basso a sx c'� un pezzo avversario
		temp.setRiga(rigaInizio - 1);
		temp.setColonna(colonnaInizio - 1);
		if (temp.setRiga(rigaInizio - 1) && temp.setColonna(colonnaInizio - 1)) {
			cas.push_back(temp);
		}

		//se nella posizione in basso a dx c'� un pezzo avversario
		temp.setRiga(rigaInizio - 1);
		temp.setColonna(colonnaInizio + 1);
		if (temp.setRiga(rigaInizio - 1) && temp.setColonna(colonnaInizio + 1)) {
			cas.push_back(temp);
		}




	}


	//ritorna il vector
	return cas;


}