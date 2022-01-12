#ifndef Cavallo_h
#define Cavallo_h

#include "Pezzo.h"
#include "Casella.h"
#include <iostream>


class Cavallo : public Pezzo {
	//classe del pezzo Cavallo

private:






public:
	//costruttore
	Cavallo(const bool color);
	//color true per bianco
	//false per nero

	//metodo move della classe Pezzo
	bool move(const Casella inizio, const Casella arrivo, const bool cattura) override;

	//metodo che controlla le posizioni in mezzo da controllare in una mossa
	//il cavallo non ha nulla da controllare
	std::vector<Casella> getCaselleIntermedie(const Casella inizio, const Casella fine) override;


	//metodo che da tutte le posizioni dove si può spostare il cavallo data la casella di partenza
	//immaginando la scacchiera vuota
	std::vector<Casella> mossePezzo(const Casella inizio) override;



};

#endif