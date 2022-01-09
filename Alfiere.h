#ifndef Alfiere_h
#define Alfiere_h

#include "Pezzo.h"
#include <iostream>

using namespace std;

class Alfiere : public Pezzo {
	//classe del pezzo Alfiere
	//� una classe derivata della classe Pezzo

private:





public:
	//costruttore
	Alfiere(const bool color);

	//metodo move della classe Pezzo
	bool move(const Casella inizio, const Casella arrivo, const bool cattura) override;

	//metodo che rid� le caselle in una mossa
	std::vector<Casella> getCaselleIntermedie(const Casella inizio, const Casella fine) override;

	//metodo che da tutte le posizioni dove si pu� spostare l'alfiere data la casella di partenza
	//immaginando la scacchiera vuota
	std::vector<Casella> mossePezzo(const Casella inizio) override;







};

#endif