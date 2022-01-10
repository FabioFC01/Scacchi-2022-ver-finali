#include "ChessBoard.h"



//costruttore
/*
	*
	* Configurazione iniziale scacchiera

	8 TCADRACT
	7 PPPPPPPP
	6
	5
	4
	3
	2 pppppppp
	1 tcadract
	  ABCDEFGH


	  dove
	  P pedone
	  T torre
	  C cavallo
	  A alfiere
	  D regina
	  R re
	  ---
	  MAIUSCOLE --- PEZZI NERI
	  minuscole --- pezzi bianchi

	  inizia il bianco
	*/

/*
* 
* indici per la nostra matrice
* 
*	bianchi minuscoli
* 
*   0 tcadract
	1 pppppppp
	2
	3
	4
	5
	6 PPPPPPPP
	7 TCADRACT
	  01234567
	  ABCDEFGH

	  neri


	quindi è come se la scacchiera fosse vista dall'altra parte
	con i numeri delle righe diminuiti di 1


*/
ChessBoard::ChessBoard() {

	



	//inizializziamo il booleano turno a 1
	//significa che è il turno del bianco
	turno = 1;
	scaccoMatto = 0;
	partitaTerminata = 0;
	statoPartita = Attiva;



	


	


	this->resetScacchiera();


	//per scegliere il tipo di partita
	this->sceltaPartita();


	srand(time(NULL));


	//se è stata scelta la partita giocatore - pc
	if (tipoPartita == 0) {

		int turnoGiocatoreUmano = rand() % 2;	//0 oppure 1

		//l'umano avrà il turno del nero
		//e il pc avrà il turno del bianco
		if (turnoGiocatoreUmano == 0) {

			//umano nero
			giocNero =  Player(false, true);
			//pc bianco
			giocBianco = Player(true, false);
		}
		//oppure l'opposto
		else if (turnoGiocatoreUmano == 1) {
			//umano bianco
			giocBianco = Player(true, true);
			//pc nero
			giocNero = Player(false, false);


		}

	}
	//se invece è stata scelta una partita tra due pc
	else if (tipoPartita == 1) {

		//pc bianco
		giocBianco = Player(true, false);
		//pc nero
		giocNero = Player(false, false);


	}


	
}	//fine  costruttore



void ChessBoard::stampa() const {
	//per stampare come vogliono le istruzioni le righe vanno stampate
	//in ordine decrescente seguendo la numerazione della nostra matrice
	
	int riga;
	int colonna;

	cout << endl << "  ---------------------  " << endl;


	//scorrimento di riga
	for (riga = 7; riga >= 0; riga--) {


		//per stampare le righe a fianco della scacchiera
		std::cout << (riga + 1) << " ";


		//scorrimento di colonne, lungo la riga prestabilita
		for (colonna = 0; colonna < 8; colonna++) {

			//se c'è qualcosa in quella casella
			if (scacchiera[riga][colonna] != nullptr) {
				std::cout << (*scacchiera[riga][colonna]).getSimbolo();
			}
			else {
				std::cout << " ";
			}
		}

		//arrivati a fine riga si va a capo
		std::cout << endl;


	}
	//finito di stampare la scacchiera stampiamo 
	//le lettere che denominano le colonne
	std::cout << endl;
	std::cout << "  ABCDEFGH" << endl << endl;

}


//metodo per chiedere e ottenere l'input per la successiva mossa
//del giocatore umano
Mossa ChessBoard::input() {
	string in;



	bool idoneo = false;



	do {
		//chiedi input
		std::cout << "Inserisci input :   ";
		getline(cin, in);   //B1 C2


		//controlla che la lunghezza sia corretta e che
		//all'indice 2 ci sia uno spazio
		if (in.length() == 5 && in[2] == ' ') {

			idoneo = true;
		}
		else {
			idoneo = false;
		}



	} while (!idoneo);

	//a questo punto l'input è corretto


//tiene i 4 valori delle coordinate


	int dati[4];

	string input_minuscolo = "";

	char c;
	int temp;

	char lettera;


	for (unsigned int i = 0; i < in.length(); i++) {
		//leggo un carattere della stringa
		c = in[i];

		//conversione
		temp = tolower(c);

		lettera = char(temp);

		//aggiunta alla stringa
		input_minuscolo += lettera;



	}




	//std::cout << input_minuscolo << endl;  //funziona

	//mettiamo gli indici ascii delle lettere in dati[4]


	//in dati ci sono i valori ascii di lettere e numeri
	dati[0] = input_minuscolo[0];	//colonna partenza
	dati[1] = input_minuscolo[1];	//riga partenza
	dati[2] = input_minuscolo[3];	//colonna arrivo
	dati[3] = input_minuscolo[4];	//riga arrivo



	//ora dobbiamo convertirli negli indici che usiamo nella scacchiera quindi
	//a --> 0 , b --> 1 , ... , h --> 7    per le colonne
	//1 --> 0 , 2 --> 1 , ... , 8 --> 7    per le righe

	//le due lettere minuscole
	dati[0] -= 97;
	dati[2] -= 97;

	//i due numeri
	dati[1] -= 49;
	dati[3] -= 49;


	//funziona
	//ora posso mandarli alle funzioni move ecc...

	Casella iniz(dati[1], dati[0]);
	Casella arr(dati[3], dati[2]);

	Mossa moss(iniz, arr);

	//facciamo il return

	return moss;



}

void ChessBoard::sceltaPartita() {
	//scelta del tipo di partita
	string input;

	std::cout << "Vuoi fare una partita giocatore - pc (inserisci 1)     o assistere ad una partita pc - pc  (inserisci 2) ?" << endl;
	cin >> input;

	while (!(input == "1" || input == "2")) {
		std::cout << "Input errato, riprovare " << endl;
		cin >> input;
	}
	//input corretto
	if (input == "1") {
		tipoPartita = 0;
	}
	if (input == "2") {
		tipoPartita = 1;
	}

}


void ChessBoard::faiMossa() {

	//mettiamo il contatore di caselle controllare qui cosi
	//poi faccio il cout
	int caselleAnalizzate = 0;

	//se è il turno del bianco
	//il bianco deve fare una mossa
	//ovvero il Player giocBianco
	if (turno) {

		//se il giocatore è umano
		if (giocBianco.getUmano()) {

			//input
			Mossa prossimaMossa = input();

			//controlla che tale mossa sia corretta
			//nel caso lo sia eseguila
			bool mossaCorretta = mossaFattibile(prossimaMossa);

			while (!mossaCorretta) {
				//richiedi altro input
				prossimaMossa = input();
				//controlla se è fattibile, nel caso esegui la mossa
				mossaCorretta = mossaFattibile(prossimaMossa);
			}
		}

		//se invece il giocatore non è umano
		else {

			srand(time(NULL));

			//spara un numero a caso tra 0 e 63
			int casellaIniziale = rand() % 64;

			//conta quante caselle abbiamo guardato sulla scacchiera
			caselleAnalizzate = 0;

			//intero che dice se la casellaIniziale aumenterà
			//o diminuirà ogni iterazione
			//vale 0 oppure 1
			int aumentoCasella = rand() & 2;

			if (aumentoCasella == 0) {
				aumentoCasella = -1;
			}


			//riga    = casellaIniziale / 8
			//colonna = casellaIniziale % 8

			bool mossaFatta = false;

			int riga = casellaIniziale / 8;
			int colonna = casellaIniziale % 8;

			while ((!mossaFatta) && (caselleAnalizzate < 70)) {

				//calcoliamo in quale riga e colonna ci troviamo
				riga = casellaIniziale / 8;
				colonna = casellaIniziale % 8;

				//controlliamo che in questa casella ci sia un pezzo
				if (scacchiera[riga][colonna] != nullptr) {
					//controlliamo che il pezzo sia bianco
					if ((*scacchiera[riga][colonna]).getColore()) {

						//ora cerchiamo l'elenco di posti in cui si può muovere
						//tale pezzo bianco
						// 
						//creiamo casella con la posizione di partenza
						Casella partenza(riga, colonna);

						std::vector<Casella> mosse = (*scacchiera[riga][colonna]).mossePezzo(partenza);


						//se è pedone
						if ((*scacchiera[riga][colonna]).getSimbolo() == 'p') {
							//controlliamo e nel caso togliamo le caselle di spostamento
							//diagonale se nella casella d'arrivo non c'è un pezzo avversario (non re nero)


							//scorriamo il vector, se ha almeno un elemento
							//ed eliminiamo le caselle scorrette
							if (mosse.size() > 0) {
								for (int j = mosse.size() - 1; j >= 0; j--) {
									//se la casella non ha la stessa colonna del pedone
									//il movimento è diagonale
									if (mosse[j].getColonna() != colonna) {

										//se non c'è nessun pezzo, o ce n'è uno bianco, o è il re nero
										//allora la mossa va eliminata
										if (scacchiera[mosse[j].getRiga()][mosse[j].getColonna()] == nullptr) {
											//eliminazione
											mosse.erase(mosse.begin() + j);
										}
										//pezz bianco
										else if ((*scacchiera[mosse[j].getRiga()][mosse[j].getColonna()]).getColore()) {
											mosse.erase(mosse.begin() + j);
										}
										//re nero
										else if ((*scacchiera[mosse[j].getRiga()][mosse[j].getColonna()]).getSimbolo() == 'R') {
											mosse.erase(mosse.begin() + j);
										}
									}
									//se il movimento è in alto/basso
									else if (mosse[j].getColonna() == colonna) {
										//se dove vai c'è un pezzo, non puoi andarci
										if (scacchiera[mosse[j].getRiga()][mosse[j].getColonna()] != nullptr) {
											//eliminazione
											mosse.erase(mosse.begin() + j);
										}
									}
								}
								//fine correzione mosse per pedone
							}
							//fine if sul pedone
						}
						//fuori if sul pedone


						//proviamo una ad una le varie mosse 
						//e vediamo se sono regolari

						for (unsigned int i = 0; i < mosse.size(); i++) {

							//se non è stata ancora fatta una mossa regolare
							if (!mossaFatta) {

								//casella di arrivo
								Casella arrivo(mosse[i].getRiga(), mosse[i].getColonna());
								Mossa mossaDaProvare(partenza, arrivo);

								//proviamo a fare la mossa
								//se mossaFatta == true allora 
								//la mossa è stata fatta
								mossaFatta = mossaFattibile(mossaDaProvare);



							}



						}







					}
				}
				//fuori dall'if che controlla se in quella casella c'è un pezzo
				//qui abbiamo finito di provare le mosse del pezzo in quella casella
				//(se c'era un pezzo con mosse)

				//incrementiamo il numero per la casella
				casellaIniziale = casellaIniziale + aumentoCasella;
				caselleAnalizzate++;

				//se però il valore è sopra il 63 
				//bisogna reimpostarlo a 0
				if (casellaIniziale > 63) {
					casellaIniziale = 0;
				}

				//se il valore scende sotto lo 0
				//lo si reimposta a 63
				if (casellaIniziale < 0) {
					casellaIniziale = 63;
				}





			}
			//fuori dal while (!mossaFatta)


			cout << endl << caselleAnalizzate << endl;




			/*
				DA IMPLEMENTARE IL PC
				CHE FA UNA DELLE MOSSE POSSIBILI SCEGLIENDO A CASO

				scorri tutta la scacchiera partendo da una casella e prendendo 
				una direzione casuale (aumenta o diminuisci)

				ogni volta che trovi in una tale casella della scacchiera un pezzo 
				del tuo stesso colore devi chiamare il metodo mossePezzo,
				prendere tutte le caselle che ti sono arrivate (ricordati di togliere 
				quelle eventualmente sbagliate dei pedoni)
				e prova, una casella per volta, a fare una mossa e vedere se è legale
				con il metodo mossaFattibile

				se finisci il vector senza aver trovato una mossa fattibile allora
				passa ad un'altra casella 

				passa tutta la scacchiera così

				se arrivi in fondo alla scacchiera riprendi da dove eri partito 
				inizialmente e procedi nella direzione opposta fino all'ultima casella
				della scacchiera disponibile

				dovresti trovare almeno una mossa fattibile dato che prima di arrivare
				qui è stato chiamato il metodo possoFareMosse
			
			*/

		}
		//fuori dall'else (giocatore bianco non umano)










	}
	//se invece è turno del nero
	else {

		//se il giocatore è umano
		if (giocNero.getUmano()) {

			//input
			Mossa prossimaMossa = input();

			//controlla che tale mossa sia corretta
			//nel caso lo sia eseguila
			bool mossaCorretta = mossaFattibile(prossimaMossa);

			while (!mossaCorretta) {
				//richiedi altro input
				prossimaMossa = input();
				//controlla se è fattibile, nel caso esegui la mossa
				mossaCorretta = mossaFattibile(prossimaMossa);
			}
		}

		//se invece il giocatore nero è pc
		else {



			srand(time(NULL));

			//spara un numero a caso tra 0 e 63
			int casellaIniziale = rand() % 64;

			//conta quante caselle abbiamo analizzato
			caselleAnalizzate = 0;

			//intero che dice se la casellaIniziale aumenterà
			//o diminuirà ogni iterazione
			//vale 0 oppure 1
			int aumentoCasella = rand() & 2;

			if (aumentoCasella == 0) {
				aumentoCasella = -1;
			}


			//riga    = casellaIniziale / 8
			//colonna = casellaIniziale % 8

			bool mossaFatta = false;

			int riga = casellaIniziale / 8;
			int colonna = casellaIniziale % 8;

			while ((!mossaFatta) &&  (caselleAnalizzate < 70)  ) {

				//calcoliamo in quale riga e colonna ci troviamo
				riga = casellaIniziale / 8;
				colonna = casellaIniziale % 8;

				//controlliamo che in questa casella ci sia un pezzo
				if (scacchiera[riga][colonna] != nullptr) {
					//controlliamo che il pezzo sia nero
					if (! (*scacchiera[riga][colonna]).getColore()) {

						//ora cerchiamo l'elenco di posti in cui si può muovere
						//tale pezzo nero
						// 
						//creiamo casella con la posizione di partenza
						Casella partenza(riga, colonna);

						std::vector<Casella> mosse = (*scacchiera[riga][colonna]).mossePezzo(partenza);


						//se è pedone
						if ((*scacchiera[riga][colonna]).getSimbolo() == 'P') {
							//controlliamo e nel caso togliamo le caselle di spostamento
							//diagonale se nella casella d'arrivo non c'è un pezzo avversario (non re bianco)


							//scorriamo il vector, se ha almeno un elemento
							//ed eliminiamo le caselle scorrette
							if (mosse.size() > 0) {
								for (int j = mosse.size() - 1; j >= 0; j--) {
									//se la casella non ha la stessa colonna del pedone
									//il movimento è diagonale
									if (mosse[j].getColonna() != colonna) {

										//se non c'è nessun pezzo, o ce n'è uno nero, o è il re bianco
										//allora la mossa va eliminata
										if (scacchiera[mosse[j].getRiga()][mosse[j].getColonna()] == nullptr) {
											//eliminazione
											mosse.erase(mosse.begin() + j);
										}
										//pezz nero
										else if (!((*scacchiera[mosse[j].getRiga()][mosse[j].getColonna()]).getColore())) {
											mosse.erase(mosse.begin() + j);
										}
										//re bianco
										else if ((*scacchiera[mosse[j].getRiga()][mosse[j].getColonna()]).getSimbolo() == 'r') {
											mosse.erase(mosse.begin() + j);
										}



									}
									//se il movimento è in alto/basso
									else if (mosse[j].getColonna() == colonna) {
										//se dove vai c'è un pezzo, non puoi andarci
										if (scacchiera[mosse[j].getRiga()][mosse[j].getColonna()] != nullptr) {
											//eliminazione
											mosse.erase(mosse.begin() + j);
										}

									}

								}

								//fine correzione mosse per pedone
							}



							//fine if sul pedone
						}
						//fuori dall'if sul pedone


						//proviamo una ad una le varie mosse 
						//e vediamo se sono regolari

						for (unsigned int i = 0; i < mosse.size(); i++) {

							//se non è stata ancora fatta una mossa regolare
							if (!mossaFatta) {

								//casella di arrivo
								Casella arrivo(mosse[i].getRiga(), mosse[i].getColonna());
								Mossa mossaDaProvare(partenza, arrivo);

								//proviamo a fare la mossa
								//se mossaFatta == true allora 
								//la mossa è stata fatta
								mossaFatta = mossaFattibile(mossaDaProvare);



							}



						}







					}
				}
				//fuori dall'if che controlla se in quella casella c'è un pezzo
				//qui abbiamo finito di provare le mosse del pezzo in quella casella
				//(se c'era un pezzo con mosse)

				//incrementiamo il numero per la casella
				casellaIniziale = casellaIniziale + aumentoCasella;
				caselleAnalizzate++;

				//se però il valore è sopra il 63 
				//bisogna reimpostarlo a 0
				if (casellaIniziale > 63) {
					casellaIniziale = 0;
				}

				//se il valore scende sotto lo 0
				//lo si reimposta a 63
				if (casellaIniziale < 0) {
					casellaIniziale = 63;
				}





			}
			//fuori dal while (!mossaFatta)

			cout << endl << caselleAnalizzate << endl;

			


		}
		//fuori dall'else (giocatore nero non umano)



	}
	//fuori dall'else (turno del nero)






}	//fine metodo faiMossa




//metodo principale che gestisce la partita
void ChessBoard::partita() {
	

	









}


//gestione della partita pc - pc
void  ChessBoard::partita_1() {



}







//gestione partita giocatore-giocatore
void ChessBoard::partita_2() {



	
	
	//finchè la partita non è terminata
	while (statoPartita == Attiva) {

		//controlla che il giocatore possa fare mosse
		if (!possoFareMosse()) {

			if (reSottoScacco()) {
				//questa è la condizione di scacco matto
				statoPartita = ScaccoMatto;

				if (turno) {
					cout << "SCACCO MATTO !!! " << endl;
					cout << "Il nero vince" << endl;
				}
				else {
					cout << "SCACCO MATTO !!! " << endl;
					cout << "Il bianco vince" << endl;
				}

			}
			else {
				statoPartita = Stallo;
				if (turno) {
					cout << "STALLO !!! " << endl;
					cout << "Il nero vince" << endl;
				}
				else {
					cout << "STALLO !!! " << endl;
					cout << "Il bianco vince" << endl;
				}


			}


		}

		//se sei qui il giocatore di questo turno può fare mosse






		if (statoPartita == Attiva) {


			//fai fare la mossa al giocatore
			faiMossa();



			/*
			//input
			Mossa prossimaMossa = input();

			//controlla che tale mossa sia corretta
			//nel caso lo sia eseguila
			bool mossaCorretta = mossaFattibile(prossimaMossa);

			while (!mossaCorretta) {
				//richiedi altro input
				prossimaMossa = input();
				//controlla se è fattibile, nel caso esegui la mossa
				mossaCorretta = mossaFattibile(prossimaMossa);
			}
			*/

			stampa();
			cambiaTurno();

		}


	//fine while (statoPartita == Attiva)
	}
		



		
}	//fine del movimento di un singolo pezzo
	
	//fine partita 2










//metodo per ottenere una det. pezzo
	//date le coordinate
Pezzo* ChessBoard::getPezzo(int rig, int col) const {
	//se la casella scelta è fuori dalla scacchiera
	if (rig < 0 || rig > 7 || col < 0 || col > 7) {
		throw new Exception("error: out of bounds");
	}

	return scacchiera[rig][col];

}


//funzione di chiamata alla funzione move
bool   ChessBoard::call(Pezzo* pez, const Casella inizio, const Casella arrivo, const bool cattura) {

	return  (*pez).move(inizio,arrivo,cattura);

}





//metodo resetScacchiera
void ChessBoard::resetScacchiera() {

	//scacchiera[riga][colonna]

	//inizializza tutta la scacchiera a nullptr
	for (int riga = 0; riga < 8; riga++) {
		for (int colonna = 0; colonna < 8; colonna++) {
			scacchiera[riga][colonna] = nullptr;
		}
	}

	//inizializziamo i pedoni bianchi

	scacchiera[1][0] = new Pedone(true);
	scacchiera[1][1] = new Pedone(true);
	scacchiera[1][2] = new Pedone(true);
	scacchiera[1][3] = new Pedone(true);
	scacchiera[1][4] = new Pedone(true);
	scacchiera[1][5] = new Pedone(true);
	scacchiera[1][6] = new Pedone(true);
	scacchiera[1][7] = new Pedone(true);
	
	//inizializziamo i pedoni neri
	Pezzo* ped1N = new Pedone(false);
	Pezzo* ped2N = new Pedone(false);
	Pezzo* ped3N = new Pedone(false);
	Pezzo* ped4N = new Pedone(false);
	Pezzo* ped5N = new Pedone(false);
	Pezzo* ped6N = new Pedone(false);
	Pezzo* ped7N = new Pedone(false);
	Pezzo* ped8N = new Pedone(false);

	scacchiera[6][0] = ped1N;
	scacchiera[6][1] = ped2N;
	scacchiera[6][2] = ped3N;
	scacchiera[6][3] = ped4N;
	scacchiera[6][4] = ped5N;
	scacchiera[6][5] = ped6N;
	scacchiera[6][6] = ped7N;
	scacchiera[6][7] = ped8N;
	
	//ci rimane da inizializzare il resto della scacchiera

	//due re (nero e bianco)
	Pezzo* rB = new Re(true);
	Pezzo* rN = new Re(false);

	scacchiera[0][4] = rB;
	scacchiera[7][4] = rN;


	//due regine
	Pezzo* regB = new Regina(true);
	Pezzo* regN = new Regina(false);

	scacchiera[0][3] = regB;
	scacchiera[7][3] = regN;



	//i 4 cavalli
	Pezzo* cav1B = new Cavallo(true);
	Pezzo* cav2B = new Cavallo(true);
	Pezzo* cav1N = new Cavallo(false);
	Pezzo* cav2N = new Cavallo(false);

	scacchiera[0][1] = cav1B;
	scacchiera[0][6] = cav2B;
	scacchiera[7][1] = cav1N;
	scacchiera[7][6] = cav2N;


	//4 alfieri
	Pezzo* alf1B = new Alfiere(true);
	Pezzo* alf2B = new Alfiere(true);
	Pezzo* alf1N = new Alfiere(false);
	Pezzo* alf2N = new Alfiere(false);

	scacchiera[0][2] = alf1B;
	scacchiera[0][5] = alf2B;
	scacchiera[7][2] = alf1N;
	scacchiera[7][5] = alf2N;

	//4 torri
	Pezzo* tor1B = new Torre(true);
	Pezzo* tor2B = new Torre(true);
	Pezzo* tor1N = new Torre(false);
	Pezzo* tor2N = new Torre(false);

	scacchiera[0][0] = tor1B;
	scacchiera[0][7] = tor2B;
	scacchiera[7][0] = tor1N;
	scacchiera[7][7] = tor2N;



	// ORA CHE SONO STATI INIZIALIZZATI TUTTI I PEZZI
	//CREIAMO I VECTOR PER I DUE GIOCATORI CON I VARI PEZZI

	
	/*
	//Pedoni
	giocBianco.push_back(ped1B);
	giocBianco.push_back(ped2B);
	giocBianco.push_back(ped3B);
	giocBianco.push_back(ped4B);
	giocBianco.push_back(ped5B);
	giocBianco.push_back(ped6B);
	giocBianco.push_back(ped7B);
	giocBianco.push_back(ped8B);

	giocNero.push_back(ped1N);
	giocNero.push_back(ped2N);
	giocNero.push_back(ped3N);
	giocNero.push_back(ped4N);
	giocNero.push_back(ped5N);
	giocNero.push_back(ped6N);
	giocNero.push_back(ped7N);
	giocNero.push_back(ped8N);

	//re
	giocBianco.push_back(rB);
	giocNero.push_back(rN);

	//regina
	giocBianco.push_back(regB);
	giocNero.push_back(regN);

	//cavalli
	giocBianco.push_back(cav1B);
	giocBianco.push_back(cav2B);
	giocNero.push_back(cav1N);
	giocNero.push_back(cav2N);

	//alfieri
	giocBianco.push_back(alf1B);
	giocBianco.push_back(alf2B);
	giocNero.push_back(alf1N);
	giocNero.push_back(alf2N);

	//torri
	giocBianco.push_back(tor1B);
	giocBianco.push_back(tor2B);
	giocNero.push_back(tor1N);
	giocNero.push_back(tor2N);

	// i due vettori sono stati completati
	*/








	



}

/*
*	--- controlla ---
	caselle di inizio e di fine dentro la scacchiera
	pezzo nella casella di partenza
*/
bool ChessBoard::inputCorretto(const  Mossa &prossimaMossa) {

	//controlliamo che le caselle di partenza e arrivo siano corrette
	//e che ci sia un pezzo nella casella di partenza
	
	//controlla casella di partenza
	if (!prossimaMossa.getCasellaPartenza().casellaValida()) {
		return false;
	}
	//controlla casella d'arrivo
	if (!prossimaMossa.getCasellaArrivo().casellaValida()) {
		return false;
	}

	//controlla che nella casella di partenza ci sia un pezzo
	if (scacchiera[prossimaMossa.getCasellaPartenza().getRiga()][prossimaMossa.getCasellaPartenza().getColonna()] == nullptr) {

		return false;
	}


	//se sei qui allora l'input è corretto
	return true;


}

//metodo che controlla tutto quello che c'è da controllare in una mossa
//per dichiararla corretta secondo le regole del gioco
//se la mossa è corretta viene eseguita
bool ChessBoard::mossaFattibile(const Mossa& mossa) {

	//primi controlli (caselle dentro scacchiera, pezzo nella casella d'inizio)
	if(!inputCorretto(mossa)) {
		return false;
	}

	//controlliamo che le caselle di inizio e di fine non siano le stesse
	//se lo dovessero essere la mossa non è valida
	if ((mossa.getCasellaPartenza().getColonna() == mossa.getCasellaArrivo().getColonna()) &&
		(mossa.getCasellaPartenza().getRiga()    == mossa.getCasellaArrivo().getRiga())) {

		return false;

	}
	
	//il pezzo che si sta muovendo deve avere lo stesso colore del giocatore di quel turno
	//(un giocatore bianco non può muovere un pezzo nero)

	
	Pezzo* pezInizio;
	pezInizio = scacchiera[mossa.getCasellaPartenza().getRiga()][mossa.getCasellaPartenza().getColonna()];
	//1 per i bianchi, 0 per i neri
	bool colorePezzoPartenza = (*pezInizio).getColore();
												// turno ha 1 per i bianchi, 0 per i neri
	//se il colore non è lo stesso di chi ha il turno la mossa è errata
	if (colorePezzoPartenza != turno) {
		return false;
	}



	//se c'è un pezzo da catturare nella casella di fine 
	//deve avere un colore opposto rispetto a quello di chi sta facendo la mossa
	//e opposto al colore del pezzo che si sta muovendo
	if (scacchiera[mossa.getCasellaArrivo().getRiga()][mossa.getCasellaArrivo().getColonna()] != nullptr) {
		//colore del pezzo è 1 per i bianchi, 0 per i neri
		bool colorePezzoArrivo = (*scacchiera[mossa.getCasellaArrivo().getRiga()][mossa.getCasellaArrivo().getColonna()]).getColore();

		//se i due colori combaciano la mossa non è corretta
		if (colorePezzoPartenza == colorePezzoArrivo) {
			return false;
		}

	}

	Pezzo* pezFine = nullptr;
	if (scacchiera[mossa.getCasellaArrivo().getRiga()][mossa.getCasellaArrivo().getColonna()] != nullptr) {
		pezFine = scacchiera[mossa.getCasellaArrivo().getRiga()][mossa.getCasellaArrivo().getColonna()];

	}

	//casella di arrivo non può essere occupata da un re avversario (se c'è qualcosa in quella casella)
	//((*scacchiera[fine.getRiga()][fine.getColonna()]).getSimbolo() != ('r' && 'R'));
	if (scacchiera[mossa.getCasellaArrivo().getRiga()][mossa.getCasellaArrivo().getColonna()] != nullptr) {
		if (((*pezFine)).getSimbolo() == ('r' || 'R')) {
			return false;
		}
	}


	// ----

	//lo spostamento di quel pezzo deve avvenire secondo le regole di quel pezzo
	//immaginandolo in una scacchiera vuota
	

	bool pezzoDaCatturare = (scacchiera[mossa.getCasellaArrivo().getRiga()][mossa.getCasellaArrivo().getColonna()] != nullptr);

	//la mossa è regolare per quel pezzo? (immaginando una scacchiera vuota)
	bool mossaRegolarePezzo = (*pezInizio).move(mossa.getCasellaPartenza(), mossa.getCasellaArrivo(), pezzoDaCatturare);

	if (!mossaRegolarePezzo) {
		//se non è regolare return false
		return false;
	}

	// -----
	/*
		il pezzo, facendo il movimento tra la casella di inizio e di fine 
		non può passare sopra ad altri pezzi (a meno che non sia un cavallo)
	*/
	//otteniamo il vector di Caselle dove controlleremo che i pezzi tra la casella di inizio e di fine
	//siano tutti vuoti
	std::vector<Casella> cas = (*pezInizio).getCaselleIntermedie(mossa.getCasellaPartenza(), mossa.getCasellaArrivo());

	for (unsigned int i = 0; i < cas.size(); i++) {

		Casella temp = cas[i];

		//se una casella intermedia è occupata da un pezzo
		if (scacchiera[temp.getRiga()][temp.getColonna()] != nullptr) {
			//mossa non valida
			return false;
		}

	}





	// ----------------------------------------------------------------------------
	//controlla che facendo questa mossa il re del giocatore che ha il turno
	//non sia sotto scacco

	//per farlo prima devo muovere il pezzo e vedere se dopo l'esecuzione
	//della mossa il re di chi ha il turno è sotto scacco

	//facciamo la mossa
	Casella in = mossa.getCasellaPartenza();
	Casella ar = mossa.getCasellaArrivo();

	//pezInizio è un oggetto Pezzo* che punta al pezzo da muovere
	scacchiera[ar.getRiga()][ar.getColonna()] = pezInizio;
	//pezFine punta al pezzo che ne stava nella casella finale (se c'era)
	scacchiera[in.getRiga()][in.getColonna()] = nullptr;

	// ----

	//ora che abbiamo eseguito la mossa dobbiamo controllare se il nostro re è sotto scacco
	//il metodo tiene conto di qual è il turno attuale

	//se il re è sotto scacco dobbiamo ritornare alla condizione iniziale 
	//e dobbiamo annullare la mossa appena fatta
	if (reSottoScacco()) {

		//rimetti l'oggetto Pezzo* dov'era prima di eseguire la mossa
		scacchiera[in.getRiga()][in.getColonna()] = pezInizio;

		//pezFine può essere nullptr o un puntatore ad un Pezzo
		scacchiera[ar.getRiga()][ar.getColonna()] = pezFine;


		//ritorna false perchè non si può fare la mossa
		//(il re sarebbe sotto scacco quindi non è una mossa valida)

		return false;

	}

	

	//se nessun controllo precedente ha dato come risultato return false
	//la mossa è corretta
	//ricorda che abbiamo anche eseguito tale mossa
	return true;

}


/*
	metodo che controlla se i pezzi avversari (rispetto a chi gioca quel turno)
	mettono sotto scacco il re

	ritorna true se il re di chi ha il turno ora è sotto scacco, false altrimenti

*/
bool ChessBoard::reSottoScacco() {

	//bisogna dividere il codice in due parti
	//a seconda di chi sta giocando questo turno

	//se è il turno del bianco
	if (turno) {
		//dobbiamo controllare se almeno uno dei pezzi neri ha la possibilità di spostarsi 
		//dove sta il re bianco attualmente

		//scorriamo la scacchiera per guardare dove si trovano i pezzi neri 


		//cerchiamo il re bianco per trovare le sue coordinate
		int rigaReBianco = -1;
		int colonnaReBianco = -1;
		//righe
		for (int riga = 7; riga >= 0; riga--) {
			//colonne
			for (int colonna = 0; colonna < 8; colonna++) {
				//c'è qualcosa nella casella?
				if ((scacchiera[riga][colonna]) != nullptr) {
					//è il re bianco?
					if ((*scacchiera[riga][colonna]).getSimbolo() == 'r') {
						rigaReBianco = riga;
						colonnaReBianco = colonna;
					}
				}
			}
		}

		//abbiamo le coordinate del re bianco

		for (int riga = 7; riga >= 0; riga--) {
			for (int colonna = 0; colonna < 8; colonna++) {

				//se quella casella non è vuota
				if ((scacchiera[riga][colonna]) != nullptr) {
					//se quel pezzo è nero (avversario)
					if ((*scacchiera[riga][colonna]).getColore() == false) {

						Casella temp(riga, colonna);

						//vettore con tutte le mosse che può fare
						std::vector<Casella> cas = (*scacchiera[riga][colonna]).mossePezzo(temp);

						//devo controllare che in nessuno di questi posti ci sia il re bianco
						for (unsigned int i = 0; i < cas.size(); i++) {
							//se una di queste posizioni è uguale a quella del re bianco
							if ((cas[i].getColonna() == colonnaReBianco) && (cas[i].getRiga() == rigaReBianco)) {
								//controllo che tra la posizioni di inizio e di fine non ci siano pezzi in mezzo
								Casella i(riga, colonna);
								Casella f(rigaReBianco, colonnaReBianco);

								//otteniamo il vettore con i pezzi intermedi
								std::vector<Casella> intermedie = (*scacchiera[riga][colonna]).getCaselleIntermedie(i, f);

								//se tutte le caselle del vettore intermedie sono vuote allora il re è sotto scacco
								bool tutteCaselleVuote = true;
								for (unsigned int j = 0; j < intermedie.size(); j++) {
									//se tale casella non è vuota
									if (scacchiera[intermedie[j].getRiga()][intermedie[j].getColonna()] != nullptr) {
										tutteCaselleVuote = false;
									}
								}

								//se tutte le caselle intermedie sono vuote
								//il re bianco è sotto scacco
								if (tutteCaselleVuote) {
									return true;
								}

							}
						}
					}
				}
			}
		}



		//se sei qui il re bianco non è sotto scacco
		return false;

		//fine parte dedicata al turno del bianco
	}
	//se è il turno del nero
	//bisogna controllare se il re nero è sotto scacco
	else {

		//cerchiamo il re nero per trovare le sue coordinate
		int rigaReNero = -1;
		int colonnaReNero = -1;
		//righe
		for (int riga = 7; riga >= 0; riga--) {
			//colonne
			for (int colonna = 0; colonna < 8; colonna++) {
				//c'è qualcosa nella casella?
				if ((scacchiera[riga][colonna]) != nullptr) {
					//è il re bianco?
					if ((*scacchiera[riga][colonna]).getSimbolo() == 'R') {
						rigaReNero = riga;
						colonnaReNero = colonna;
					}
				}
			}
		}

		//abbiamo le coordinate del re nero

		for (int riga = 7; riga >= 0; riga--) {
			for (int colonna = 0; colonna < 8; colonna++) {

				//se quella casella non è vuota
				if ((scacchiera[riga][colonna]) != nullptr) {
					//se quel pezzo è bianco (avversario)
					if ((*scacchiera[riga][colonna]).getColore() == true) {

						Casella temp(riga, colonna);

						//vettore con tutte le mosse che può fare
						std::vector<Casella> cas = (*scacchiera[riga][colonna]).mossePezzo(temp);

						//devo controllare che in nessuno di questi posti ci sia il re nero
						for (unsigned int i = 0; i < cas.size(); i++) {
							//se una di queste posizioni è uguale a quella del re nero
							if ((cas[i].getColonna() == colonnaReNero) && (cas[i].getRiga() == rigaReNero)) {

								//controllo che tra la posizioni di inizio e di fine non ci siano pezzi in mezzo
								Casella i(riga, colonna);
								Casella f(rigaReNero, colonnaReNero);

								//otteniamo il vettore con i pezzi intermedi
								std::vector<Casella> intermedie = (*scacchiera[riga][colonna]).getCaselleIntermedie(i, f);

								//se tutte le caselle del vettore intermedie sono vuote allora il re è sotto scacco
								bool tutteCaselleVuote = true;
								for (unsigned int j = 0; j < intermedie.size(); j++) {
									//se tale casella non è vuota
									if (scacchiera[intermedie[j].getRiga()][intermedie[j].getColonna()] != nullptr) {
										tutteCaselleVuote = false;
									}
								}

								//se tutte le caselle intermedie sono vuote
								//il re nero è sotto scacco
								if (tutteCaselleVuote) {
									return true;
								}

							}
						}
					}
				}
			}
		}

		//se sei qui signfica che il re nero non è sotto scacco
		return false;
		//fine parte per il turno del nero

	}



}


void ChessBoard::cambiaTurno() {

	
	bool prossimoTurno = !turno;

	turno = prossimoTurno;


}



/*
		metodo che controlla se un giocatore può fare
		almeno una mossa considerata regolare
		ritorna true se può farne almeno una,
		false altrimenti

	*/


bool ChessBoard::possoFareMosse() {

	//se è turno del bianco
	if (turno) {

		//scorrimento righe
		for (int riga = 7; riga >= 0; riga--) {
			//scorrimento colonne
			for (int colonna = 0; colonna < 8; colonna++) {
				//se c'è un pezzo in questa casella
				if (scacchiera[riga][colonna] != nullptr) {
					//se quel pezzo è bianco e non catturato
					if ((*scacchiera[riga][colonna]).getColore() && (!(*scacchiera[riga][colonna]).getCatturato())) {

						Casella in(riga, colonna);

						std::vector<Casella> mosse = (*scacchiera[riga][colonna]).mossePezzo(in);


						//se è pedone
						if ((*scacchiera[riga][colonna]).getSimbolo() == 'p') {
							//controlliamo e nel caso togliamo le caselle di spostamento
							//diagonale se nella casella d'arrivo non c'è un pezzo avversario (non re nero)


							//scorriamo il vector, se ha almeno un elemento
							//ed eliminiamo le caselle scorrette
							if (mosse.size() > 0) {
								for (int j = mosse.size() - 1; j >= 0; j--) {
									//se la casella non ha la stessa colonna del pedone
									//il movimento è diagonale
									if (mosse[j].getColonna() != colonna) {

										//se non c'è nessun pezzo, o ce n'è uno bianco, o è il re nero
										//allora la mossa va eliminata
										if (scacchiera[mosse[j].getRiga()][mosse[j].getColonna()] == nullptr) {
											//eliminazione
											mosse.erase(mosse.begin() + j);
										}
										//pezz bianco
										else if ((*scacchiera[mosse[j].getRiga()][mosse[j].getColonna()]).getColore()) {
											mosse.erase(mosse.begin() + j);
										}
										//re nero
										else if ((*scacchiera[mosse[j].getRiga()][mosse[j].getColonna()]).getSimbolo() == 'R') {
											mosse.erase(mosse.begin() + j);
										}
									}
									//se il movimento è in alto/basso
									else if (mosse[j].getColonna() == colonna) {
										//se dove vai c'è un pezzo, non puoi andarci
										if (scacchiera[mosse[j].getRiga()][mosse[j].getColonna()] != nullptr) {
											//eliminazione
											mosse.erase(mosse.begin() + j);
										}

									}

								}

								//fine correzione mosse per pedone
							}



							//fine if sul pedone
						}
						//fuori dall'if sul pedone

						//cerchiamo di capire se c'è almeno una mossa sul vector corretta
						//nel caso facciamo return true


						//scorriamo il vector e guardiamo ogni mossa
						for (unsigned int i = 0; i < mosse.size(); i++) {
							Casella fin(mosse[i].getRiga(), mosse[i].getColonna());

							//controlliamo che il pezzo non passi sopra ad altri pezzi nella mossa
							std::vector<Casella> intermedie = (*scacchiera[riga][colonna]).getCaselleIntermedie(in, fin);
							//scorriamo il vector di caselle intermedie per capire se sono tutte vuote
							bool tutteCaselleVuote = true;
							for (unsigned int k = 0; k < intermedie.size(); k++) {
								if (scacchiera[intermedie[k].getRiga()][intermedie[k].getColonna()] != nullptr) {
									tutteCaselleVuote = false;
								}
							}

							//se tutte le caselle erano vuote
							if (tutteCaselleVuote) {

								//controlliamo che la casella di arrivo non abbia un pezzo del colore bianco
								//ammesso che ci sia un pezzo nella casella di fine
								//se la casella di fine non ha pezzi, o ne ha uno nero
								if (((scacchiera[mosse[i].getRiga()][mosse[i].getColonna()]) == nullptr) || (!((*scacchiera[mosse[i].getRiga()][mosse[i].getColonna()]).getColore()))) {


									//la casella di arrivo non può avere il re avversario
									//ammesso che ci sia un pezzo
									if ((scacchiera[mosse[i].getRiga()][mosse[i].getColonna()]) != nullptr) {

										//se c'è un pezzo ma è nero e non il re nero
										if ((*scacchiera[mosse[i].getRiga()][mosse[i].getColonna()]).getSimbolo() != 'R') {

											//controlliamo che facendo quella mossa il mio re non sia sotto scacco
											Pezzo* pezInizio = scacchiera[riga][colonna];
											Pezzo* pezFine = scacchiera[mosse[i].getRiga()][mosse[i].getColonna()];

											//pezInizio è un oggetto Pezzo* che punta al pezzo da muovere
											scacchiera[mosse[i].getRiga()][mosse[i].getColonna()] = pezInizio;
											//pezFine punta al pezzo che ne stava nella casella finale
											scacchiera[in.getRiga()][in.getColonna()] = nullptr;

											//ora che ho fatto la mossa, vediamo se il mio re è sottoscacco

											bool reScacco = reSottoScacco();

											//se non lo dovesse essere, cioè se reScacco == false
											//abbiamo trovato almeno una mossa fattibile 
											//quindi facciamo return true

											//rimettiamo a posto i pezzi spostati prima
											scacchiera[in.getRiga()][in.getColonna()] = pezInizio;
											scacchiera[mosse[i].getRiga()][mosse[i].getColonna()] = pezFine;

											//e cancelliamo i puntatori
											

											//ritorno
											if (!reScacco) {
												return true;
											}









										}

									}
									//se la casella di arrivo non ha pezzi
									else {

										//controlliamo che facendo quella mossa il mio re non sia sotto scacco
										Pezzo* pezInizio = scacchiera[riga][colonna];
										Pezzo* pezFine = scacchiera[mosse[i].getRiga()][mosse[i].getColonna()];

										//pezInizio è un oggetto Pezzo* che punta al pezzo da muovere
										scacchiera[mosse[i].getRiga()][mosse[i].getColonna()] = pezInizio;
										//pezFine punta al pezzo che ne stava nella casella finale
										scacchiera[in.getRiga()][in.getColonna()] = nullptr;

										//ora che ho fatto la mossa, vediamo se il mio re è sottoscacco

										bool reScacco = reSottoScacco();

										//se non lo dovesse essere, cioè se reScacco == false
										//abbiamo trovato almeno una mossa fattibile 
										//quindi facciamo return true

										//rimettiamo a posto la mossa fatta
										scacchiera[in.getRiga()][in.getColonna()] = pezInizio;
										scacchiera[mosse[i].getRiga()][mosse[i].getColonna()] = nullptr;

										

										if (!reScacco) {
											return true;
										}



									}

								}
							}
						}
					}
				}
			}
		}
		//fine parte dedicata al turno del bianco

		//se il bianco è arrivato qui nessuna mossa è fattibile da un suo pezzo

		return false;
	}
	//inizio parte dedicata al turno del nero
	else {

	//scorrimento righe
	for (int riga = 7; riga >= 0; riga--) {
		//scorrimento colonne
		for (int colonna = 0; colonna < 8; colonna++) {
			//se c'è un pezzo in questa casella
			if (scacchiera[riga][colonna] != nullptr) {
				//se quel pezzo è nero e non catturato
				if ( (!((*scacchiera[riga][colonna]).getColore()))  && (!(*scacchiera[riga][colonna]).getCatturato())) {

					Casella in(riga, colonna);

					std::vector<Casella> mosse = (*scacchiera[riga][colonna]).mossePezzo(in);


					//se è pedone
					if ((*scacchiera[riga][colonna]).getSimbolo() == 'P') {
						//controlliamo e nel caso togliamo le caselle di spostamento
						//diagonale se nella casella d'arrivo non c'è un pezzo avversario (non re bianco)


						//scorriamo il vector, se ha almeno un elemento
						//ed eliminiamo le caselle scorrette
						if (mosse.size() > 0) {
							for (int j = mosse.size() - 1; j >= 0; j--) {
								//se la casella non ha la stessa colonna del pedone
								//il movimento è diagonale
								if (mosse[j].getColonna() != colonna) {

									//se non c'è nessun pezzo, o ce n'è uno nero, o è il re bianco
									//allora la mossa va eliminata
									if (scacchiera[mosse[j].getRiga()][mosse[j].getColonna()] == nullptr) {
										//eliminazione
										mosse.erase(mosse.begin() + j);
									}
									//pezz nero
									else if ( !((*scacchiera[mosse[j].getRiga()][mosse[j].getColonna()]).getColore())) {
										mosse.erase(mosse.begin() + j);
									}
									//re bianco
									else if ((*scacchiera[mosse[j].getRiga()][mosse[j].getColonna()]).getSimbolo() == 'r') {
										mosse.erase(mosse.begin() + j);
									}



								}
								//se il movimento è in alto/basso
								else if (mosse[j].getColonna() == colonna) {
									//se dove vai c'è un pezzo, non puoi andarci
									if (scacchiera[mosse[j].getRiga()][mosse[j].getColonna()] != nullptr) {
										//eliminazione
										mosse.erase(mosse.begin() + j);
									}

								}

							}

							//fine correzione mosse per pedone
						}



						//fine if sul pedone
					}
					//fuori dall'if sul pedone

					//cerchiamo di capire se c'è almeno una mossa sul vector corretta
					//nel caso facciamo return true


					//scorriamo il vector e guardiamo ogni mossa
					for (unsigned int i = 0; i < mosse.size(); i++) {
						Casella fin(mosse[i].getRiga(), mosse[i].getColonna());

						//controlliamo che il pezzo non passi sopra ad altri pezzi nella mossa
						std::vector<Casella> intermedie = (*scacchiera[riga][colonna]).getCaselleIntermedie(in, fin);
						//scorriamo il vector di caselle intermedie per capire se sono tutte vuote
						bool tutteCaselleVuote = true;
						for (unsigned int k = 0; k < intermedie.size(); k++) {
							if (scacchiera[intermedie[k].getRiga()][intermedie[k].getColonna()] != nullptr) {
								tutteCaselleVuote = false;
							}
						}

						//se tutte le caselle erano vuote
						if (tutteCaselleVuote) {

							//controlliamo che la casella di arrivo non abbia un pezzo del colore nero
							//ammesso che ci sia un pezzo nella casella di fine
							//se la casella di fine non ha pezzi, o ne ha uno bianco
							if (((scacchiera[mosse[i].getRiga()][mosse[i].getColonna()]) == nullptr) || ((*scacchiera[mosse[i].getRiga()][mosse[i].getColonna()]).getColore())) {


								//la casella di arrivo non può avere il re avversario
								//ammesso che ci sia un pezzo
								if ((scacchiera[mosse[i].getRiga()][mosse[i].getColonna()]) != nullptr) {

									//se c'è un pezzo ma è bianco e non il re bianco
									if ((*scacchiera[mosse[i].getRiga()][mosse[i].getColonna()]).getSimbolo() != 'r') {

										//controlliamo che facendo quella mossa il mio re non sia sotto scacco
										Pezzo* pezInizio = scacchiera[riga][colonna];
										Pezzo* pezFine = scacchiera[mosse[i].getRiga()][mosse[i].getColonna()];

										//pezInizio è un oggetto Pezzo* che punta al pezzo da muovere
										scacchiera[mosse[i].getRiga()][mosse[i].getColonna()] = pezInizio;
										//pezFine punta al pezzo che ne stava nella casella finale
										scacchiera[in.getRiga()][in.getColonna()] = nullptr;

										//ora che ho fatto la mossa, vediamo se il mio re è sottoscacco

										bool reScacco = reSottoScacco();

										//se non lo dovesse essere, cioè se reScacco == false
										//abbiamo trovato almeno una mossa fattibile 
										//quindi facciamo return true

										//rimettiamo a posto i pezzi spostati prima
										scacchiera[in.getRiga()][in.getColonna()] = pezInizio;
										scacchiera[mosse[i].getRiga()][mosse[i].getColonna()] = pezFine;

										

										//ritorno
										if (!reScacco) {
											return true;
										}









									}

								}
								//se la casella di arrivo non ha pezzi
								else {

									//controlliamo che facendo quella mossa il mio re non sia sotto scacco
									Pezzo* pezInizio = scacchiera[riga][colonna];
									Pezzo* pezFine = scacchiera[mosse[i].getRiga()][mosse[i].getColonna()];

									//pezInizio è un oggetto Pezzo* che punta al pezzo da muovere
									scacchiera[mosse[i].getRiga()][mosse[i].getColonna()] = pezInizio;
									//pezFine punta al pezzo che ne stava nella casella finale
									scacchiera[in.getRiga()][in.getColonna()] = nullptr;

									//ora che ho fatto la mossa, vediamo se il mio re è sottoscacco

									bool reScacco = reSottoScacco();

									//se non lo dovesse essere, cioè se reScacco == false
									//abbiamo trovato almeno una mossa fattibile 
									//quindi facciamo return true

									//rimettiamo a posto la mossa fatta
									scacchiera[in.getRiga()][in.getColonna()] = pezInizio;
									scacchiera[mosse[i].getRiga()][mosse[i].getColonna()] = nullptr;

									

									if (!reScacco) {
										return true;
									}



								}

							}
						}
					}
				}
			}
		}
	}



	//se il nero è arrivato qui non può fare nessuna mossa legale

	return false;

	}


}
