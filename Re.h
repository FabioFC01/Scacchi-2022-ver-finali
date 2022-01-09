#ifndef Re_h
#define Re_h

#include "Pezzo.h"
#include <iostream>

using namespace std;

class Re : public Pezzo {
	//classe del pezzo Re

private:
	





public:
	//costruttore
	Re(const bool color);
	//color true per bianco
	//false per nero

	//metodo move della classe Pezzo
	bool move(const Casella inizio, const Casella arrivo, const bool cattura) override;

	//mossa che d� l'elenco di caselle da controllare tra le coordinate di inizio e di fine di una mossa
	std::vector<Casella> getCaselleIntermedie(const Casella inizio, const Casella fine) override;


	//metodo che da tutte le posizioni dove si pu� spostare il re data la casella di partenza
	//immaginando la scacchiera vuota
	std::vector<Casella> mossePezzo(const Casella inizio) override;




};

#endif