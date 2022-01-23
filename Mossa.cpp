// COCIANCICH FABIO - 2016268

#include "Mossa.h"

Mossa::Mossa(Casella part, Casella arr) {
	partenza = part;
	arrivo = arr;

}

void Mossa::setCasellaPartenza(Casella par) {
	partenza = par;
}

void Mossa::setCasellaArrivo(Casella arr) {
	arrivo = arr;
}
