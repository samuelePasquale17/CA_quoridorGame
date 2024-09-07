/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


#ifndef MURO_H
#define MURO_H


/**
	@brief			La gestione dei muri avviene tramite una struct che memorizza i due
							vertici estremi del muoro chiamati v1 e v2. Si noti che nella
							rappresentazione tramite grafo un muro equivale a due archi che
							hanno in comune un vertice che sarebbe il punto medio dell'arco.
							Gli archi sono pesati e i muri hanno un peso di 1.
							Il valore dei vertici v1 e v2 sono equivalenti ai valore dei 
							corrispettivi vertici nel grafo
*/


/**
	@brief			Definizione del tipo Muro che rappresenta un muro sulla scacchiera
	@attribute	v1:	Vertice in alto se muro verticale o vertice a sinistra se muro orizzontale
	@attribute	v2:	Vertice in basso se muro verticale o vertice a destra se muro orizzontale
*/
typedef struct muro_s {
	int v1;
	int v2;
} Muro;


/* Defines */
#define MURO_ORIZZONTALE 0
#define MURO_VERTICALE 1


/* Prototipi */
void MUROinitMuri(void);
void MUROcrea(int v1, int v2, int coloreGiocatore);
void MUROrimuoviLastMuro(int coloreGiocatore);
Muro MUROgetLastMuro(void);
void MUROruotaMuro(void);
int MUROisVertical(Muro muro);
int MUROgetVertice1(Muro muro);
int MUROgetVertice2(Muro muro);
int MUROorientamento(Muro muro);
void MUROsetV1(Muro *muro, int vertice);
void MUROsetV2(Muro *muro, int vertice);
int MUROeq(Muro m1, Muro m2);
void MUROordinaVertici(Muro *muro);
int MUROmuroPresente(Muro muro);
void MUROcreaSenzaAggiungere(Muro *muro, int v1, int v2);
int MUROsiSovrappone(Muro muro, Muro daEscludere);

#endif
