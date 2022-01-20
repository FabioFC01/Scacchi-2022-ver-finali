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




//assegnamento di copia
Mossa& Mossa::operator= (const Mossa& a) {


	partenza = a.getCasellaPartenza();;
	arrivo = a.getCasellaArrivo();;

	return *this;

}


//assegnamento move
Mossa& Mossa::operator= (Mossa&& a) {

	partenza = a.getCasellaPartenza();
	arrivo = a.getCasellaArrivo();

	return *this;
}

//costruttore move
Mossa::Mossa(Mossa&& a) {

	setCasellaPartenza(a.getCasellaPartenza());
	setCasellaArrivo(a.getCasellaArrivo());

}


//costruttore di copia
Mossa::Mossa(Mossa& a) {

	setCasellaPartenza(a.getCasellaPartenza());
	setCasellaArrivo(a.getCasellaArrivo());

}