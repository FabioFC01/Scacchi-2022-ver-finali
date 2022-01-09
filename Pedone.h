#ifndef Pedone_h
#define Pedone_h

#include "Pezzo.h"
#include <iostream>

#include <vector>

using namespace std;

class Pedone : public Pezzo {
	//classe del pezzo Pedone
	//� una classe derivata della classe Pezzo

private:
	//valore booleano che � true se il pedone si trova nella posizione iniziale
	//perch� se fosse cos� pu� fare un salto in avanti di due caselle
	//dopo la prima mossa questo valore sar� sempre false
	bool primaMossa;

	




public:
	//costruttore
	Pedone(const bool color);

	//metodo move della classe Pezzo
	bool move (const Casella inizio, const Casella arrivo, const bool cattura) override;


	std::vector<Casella> getCaselleIntermedie(const Casella inizio, const Casella fine) override;

	//metodo che da tutte le posizioni dove si pu� spostare il pedone data la casella di partenza
	//immaginando la scacchiera vuota
	std::vector<Casella> mossePezzo(const Casella inizio) override;


	

};

#endif