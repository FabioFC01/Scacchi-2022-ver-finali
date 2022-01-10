#ifndef Torre_h
#define Torre_h

#include "Pezzo.h"
#include "Casella.h"
#include <iostream>

using namespace std;

class Torre : public Pezzo {
	//classe del pezzo Torre

private:






public:
	//costruttore
	Torre(const bool color);
	//color true per bianco
	//false per nero

	//metodo move della classe Pezzo
	bool move(const Casella inizio, const Casella arrivo, const bool cattura) override;

	//metodo getCaselleIntermedie della classe Pezzo
	std::vector<Casella> getCaselleIntermedie(const Casella inizio, const Casella fine) override;

	//metodo che da tutte le posizioni in qui si può spostare immaginando una scacchiera vuota
	std::vector<Casella> mossePezzo(const Casella inizio) override;





};

#endif