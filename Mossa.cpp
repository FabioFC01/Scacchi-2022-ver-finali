#include "Mossa.h"

Mossa::Mossa(Casella part, Casella arr) {
	partenza = part;
	arrivo = arr;

}

//assegnamento di copia
Mossa& Mossa::operator= (const Mossa& a) {


	partenza = a.getCasellaPartenza();;
	arrivo = a.getCasellaArrivo();;

	return *this;

}