// COCIANCICH FABIO - 2016268

#include "Exception.h"

//funzione membro per ottenere descrizione
	//dell'eccezione
const string Exception::what() const {
	return description_;
}