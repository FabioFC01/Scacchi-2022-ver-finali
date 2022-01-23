// COCIANCICH FABIO - 2016268

#include "Pezzo.h"

//1 per i bianchi, 0 per i neri
void Pezzo::setColore(const bool b) {
	colore = b;
}


bool Pezzo::dentroScacchiera(const int rig, const int col) const {
	if ((rig <= 7 && rig >= 0) && (col <= 7 && col >= 0)) {
		//tale casella è all'interno della scacchiera
		return true;
	}
	else {
		return false;
	}
}