// COCIANCICH FABIO - 2016268

#ifndef Exception_h
#define Exception_h

#include <string>

using namespace std;

class Exception {

private:
	string description_{ "Generic error" };

public:
	//costruttore base
	Exception(void) {}

	//costruttore con argomento
	Exception(const string& arg) {
		description_ = arg;
	}

	//funzione membro per ottenere descrizione
	//dell'eccezione
	const string what() const;



};

#endif