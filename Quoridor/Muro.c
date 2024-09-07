/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


/* Includes */
#include "Muro.h"
#include "Giocatore.h"


/**
	@brief			Variabili globali che memorizzano i muri che sono stati posizionati sulla
							scacchiera tramite un vettore che viene dimensionato a 16, che è il numero
							massimo di muri che possono essere posizionati in una partita nel complesso
							dai due giocatori (8 muri per giocatore 1 e 8 muri per giocatore 2). Il vettore
							è un vettore di muri e parallelamente si tiene un contatore del numero di muri
							posizionati complessivamente che viene utilizzato come indice del vettore
*/
Muro muriPiazzati[16];
int cntMuriPiazzati = 0;


/**
	@brief			Funzione che crea un muro e lo aggiunge al vettore di muri incrementando l'indice.
							Inoltre la funzione aggiorna il numero di muri posizionati per il giocatore che 
							ha posizionato il nuovo muro.
	@parameter	v1:								Vertice 1 del nuovo muro
	@parameter	v2:								Vertice 2 del nuovo muro
	@parameter	coloreGiocatore:	Identificativo del giocatore che ha posizionato il muro. Gli ID
																dei giocatori possono essere [ROSSO, BLU] e vengono definiti in
																Quoridor.h
*/
void MUROcrea(int v1, int v2, int coloreGiocatore) {
	Muro muro;
	muro.v1 = v1;
	muro.v2 = v2;
	muriPiazzati[cntMuriPiazzati++] = muro;
	GIOCATOREaddMuro(coloreGiocatore);
}


/**
	@brief			Funzione che inizializza la struttura dati azzerando il contatore, permettendo 
							così nelle scritture successive di sovrascrivere eventuali muri aggiunti 
							in una partita precedente
*/
void MUROinitMuri(void) {
	cntMuriPiazzati = 0;
}


/**
	@brief			Funzione che rimuove l'ultimo muro inserito dal vettore di muri. La rimozione è 
							possibile semplicemente decrementando l'indice del vettore. Inoltre si aggiorna
							il numero di muri posizionati dal giocatore decrementandolo di una unità.
	@parameter	coloreGiocatore:	Identificativo del giocatore che richiede la rimozione del muro. 
																Gli ID dei giocatori possono essere {ROSSO, BLU} e vengono 
																definiti in Quoridor.h
*/
void MUROrimuoviLastMuro(int coloreGiocatore) {
	cntMuriPiazzati--;
	GIOCATOREremoveMuro(coloreGiocatore);
}


/**
	@brief			Funzione che ricevuto un muro come parametro verifica se il muro è verticale o
							orizzontale e restituisce il risultato. Per determinare se è verticale o 
							orizzontale si calcola la diffenza del valore dei due vertici, se è in valore 
							assoluto uguale a 2 allora il muro è orizzontale siccome i vertici sono uno 
							successivo all'altro con distanza 2 (perchè nel grafo un muro equivale a 2 archi).
							Se il muro è orizzontale invece la differenza in modulo sarebbe uguale a 16 siccome
							i vertici sono uno sopra/sotto l'altro con il punto medio del muro.
	@parameter	muro:							Muro per il quale si verifica se è orizzontale o verticale
	@return			Il valore di ritorno può essere {MURO_ORIZZONTALE, MURO_VERTICALE}
*/
int MUROisVertical(Muro muro) {
	if (muro.v1 - muro.v2 == 2 || muro.v1 - muro.v2 == -2) {
		return MURO_ORIZZONTALE;
	} else {
		return MURO_VERTICALE;
	}
}


/**
	@brief			Funzione che restituisce il vertice v1 del muro
	@parameter	muro:							Muro per il quale si restituisce il valore v1
	@return			Il valore del vertice v1
*/
int MUROgetVertice1(Muro muro) {
	return muro.v1;
}


/**
	@brief			Funzione che restituisce il vertice v2 del muro
	@parameter	muro:							Muro per il quale si restituisce il valore v2
	@return			Il valore del vertice v2
*/
int MUROgetVertice2(Muro muro) {
	return muro.v2;
}


/**
	@brief			Funzione che verifica se il muro è verticale o orizzontale e restituisce il 
							risultato del controllo
	@parameter	muro:							Muro per il quale si verifica se è orizzontale o verticale
	@return			Il valore di ritorno può essere {MURO_ORIZZONTALE, MURO_VERTICALE}
*/
int MUROorientamento(Muro muro) {
	if (MUROisVertical(muro) == 1) return MURO_VERTICALE;
	return MURO_ORIZZONTALE;
}


/**
	@brief			Funzione che una volta chiamata ruota il muro, da orizzontale a verticale o 
							viceversa. Il muro che viene ruotato è l'ultimo muro che è stato inserito
							nel vettore dei muri. Questo perchè quest'ultimo è il muro corrente in fase
							di gioco, e quindi il muro che viene ruotato dal giocatore del turno
*/
void MUROruotaMuro() {
	MUROordinaVertici(&(muriPiazzati[cntMuriPiazzati-1]));
	if (MUROisVertical(muriPiazzati[cntMuriPiazzati-1]) == 1) {
		(muriPiazzati[cntMuriPiazzati-1]).v2 = (muriPiazzati[cntMuriPiazzati-1]).v1 + 2; /* da verticale a orizzontale */
	} else {
		(muriPiazzati[cntMuriPiazzati-1]).v2 = (muriPiazzati[cntMuriPiazzati-1]).v1 + 16; /* da orizzontale a verticale */
	}
}


/**
	@brief			Funzione che imposta il valore di v1 al muro passato by reference dal chiamante
	@parameter	muro:							Riferimento al muro per il quale si aggiorna il valore di v1
	@parameter	vertice:					Valore del vertice da salvare in v1
*/
void MUROsetV1(Muro *muro, int vertice) {
	muro->v1 = vertice;
}


/**
	@brief			Funzione che imposta il valore di v2 al muro passato by reference dal chiamante
	@parameter	muro:							Riferimento al muro per il quale si aggiorna il valore di v2
	@parameter	vertice:					Valore del vertice da salvare in v2
*/
void MUROsetV2(Muro *muro, int vertice) {
	muro->v2 = vertice;
}


/**
	@brief			Funzione che verifica se i due muri passati come parametro sono uguali
	@parameter	m1:							Muro 1
	@parameter	m2:							Muro 2
	@return			Il valore di ritorno restituisce il risultato del confronto che può essere 1 se
							i due muri sono uguali o 0 se i due muri sono diversi
*/
int MUROeq(Muro m1, Muro m2) {
	MUROordinaVertici(&m1);
	MUROordinaVertici(&m2);
	return (m1.v1 == m2.v1 && m1.v2 == m2.v2);
}


/**
	@brief			Funzione che passato un muro by reference verifica che i vertici v1 e v2 siano
							ordinati come specificato nella descrizione della definizione del tipo di dato
							Muro. Se non sono ordinati vengono scambiati (v1 <-> v2)
	@parameter	muro:							Riferimento al muro per il quale si verifica l'ordine di v1 e v2
*/
void MUROordinaVertici(Muro *muro) {
	int tmp;
	if (muro-> v1 > muro->v2) { /* swap */
		tmp = muro->v1;	
		muro->v1 = muro->v2;
		muro->v2 = tmp;
	}
}

/**
	@brief			Funzione che restituisce l'ultimo muro che è stato piazzato che si trovo in ultima
							posizione del vettore di muri
	@return			Ultimo muro piazzato
*/
Muro MUROgetLastMuro() {
	return muriPiazzati[cntMuriPiazzati-1];
}


/**
	@brief			Funzione che dato un muro come parametro verifica se quest'ultimo è già presente
							nel vettore globale di muri
	@parameter	muro:							Muro per il quale si verifica se è presente o meno tra i muri già
																inseriti nel vettore globale di muri
	@return			Risultato del controllo che può essere 1 se il muro è già presente o 0 se il muro
							non è ancora presente
*/
int MUROmuroPresente(Muro muro) {
	int i;
	for (i = 0; i < cntMuriPiazzati; i++) {
		if (MUROeq(muro, muriPiazzati[i]) == 1) return 1;
	}
	return 0;
}


/**
	@brief			Funzione che dato un muro by reference carica i valori di v1 e v2. Questa funzione
							Permette di inizializzare un muro creato dal chiamante senza però aggiungerlo 
							nel vettore globale dei muri posizionati in scacchiera
	@parameter	muro:							Riferimento al muro che deve essere inizializzato con i valori di 
																v1 e v2
	@parameter	v1:								Vertice v1
	@parameter	v2:								Vertice v2
*/
void MUROcreaSenzaAggiungere(Muro *muro, int v1, int v2) {
	muro->v1 = v1;
	muro->v2 = v2;
}


/**
	@brief			Funzione che dato un muro come parametro verifica se questo si sovrappone interamente
							o parzialmente o si incrocia con anche solo un muro tra i muri già presenti sulla 
							scacchiera e memorizzati nel vettore globale dei muri. La funzione da la possibilità
							di escludere in fase di verifica un muro in particolare. Se non si vuole utilizzare
							Questa funzionalità basta passare nuovamente lo stesso muro, escludendo se stesso in fase
							di verifica, oppure un muro void con un valore di vertici v1 e v2 non validi (es. -1 o > 63).
	@parameter	muro:							Muro per il quale si verifica eventuale sovrapposizione parziale, totale o
																incroco con un muro in scacchiera
	@parameter	daEscludere:			Muro che può essere escluso in fase di verifica. Se funzionalità non 
																necessaria fornire lo stesso numero o un muro void
	@return			Risultato del controllo che può essere 1 se il muro si sovrappone con uno dei muri presenti o 0 
							se il muro non si sovrappone nè totalmente nè parzialmente con nessun muro in scacchiera
*/
int MUROsiSovrappone(Muro muro, Muro daEscludere) {
	int i, muroVerticale = MUROisVertical(muro);
	int v1, v2, v3 = MUROgetVertice1(muro), v4 = MUROgetVertice2(muro), v1_test, v2_test;
	Muro muroTest;
	for (i = 0; i < cntMuriPiazzati; i++) {
		if (MUROeq(muriPiazzati[i], daEscludere) != 1) { /* esclusione muro da escludere */
			if (MUROisVertical(muriPiazzati[i]) == muroVerticale) { /* muri nella stessa direzione */
				v1 = MUROgetVertice1(muriPiazzati[i]);
				v2 = MUROgetVertice2(muriPiazzati[i]);
				if (muroVerticale == 1) { /* direzione verticale */
					if ( (v3 == (v1 + 8)) && (v3 == (v2 - 8)) ) return 1;
					if ( (v4 == (v1 + 8)) && (v4 == (v2 - 8)) ) return 1;
				} else { /* direzione orizzontale */
					if ( (v3 == (v1 + 1)) && (v3 == (v2 - 1)) ) return 1;
					if ( (v4 == (v1 + 1)) && (v4 == (v2 - 1)) ) return 1;
				}
			} else { /* direzione ortogonale */				
				v1 = MUROgetVertice1(muriPiazzati[i]);
				v2 = MUROgetVertice2(muriPiazzati[i]);
				
				/* verifica che i due muri non si incrocino */
				if (muroVerticale == 1) {
					v1_test = v3+8-1;
					v2_test = v3+8+1;
					MUROcreaSenzaAggiungere(&muroTest, v1_test, v2_test);
					
					if (MUROmuroPresente(muroTest) == 1) return 1;
				} else {
					v1_test = v3+1-8;
					v2_test = v3+1+8;
					MUROcreaSenzaAggiungere(&muroTest, v1_test, v2_test);
					if (MUROmuroPresente(muroTest) == 1) return 1;
				}
			}
		}
	}
	return 0; /* nessuna sovrapposizione */
}
