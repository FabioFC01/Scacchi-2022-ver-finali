#include "Pezzo.h"

//implementiamo i vari metodi della classe Pezzo



//1 per i bianchi, 0 per i neri
void Pezzo::setColore(const bool b) {
	colore = b;
}

/*
bool Pezzo::move(const Casella inizio, const Casella arrivo, const bool cattura) {

	return true;
}
*/

bool Pezzo::dentroScacchiera(const int rig, const int col) {
	if ((rig <= 7 && rig >= 0) && (col <= 7 && col >= 0)) {
		//tale casella è all'interno della scacchiera
		return true;
	}
	else {
		return false;
	}
}

void Pezzo::setCatturato(const bool c) {
	catturato = c;
}