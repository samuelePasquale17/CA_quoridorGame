#include "NPCController.h"
#include "Giocatore.h"

int direzioneMosseAvversario[4] = {0};


void NPCControllerInit() {
	int i;
	for (i = 0; i < 4; i++) direzioneMosseAvversario[i] = 0;
}

void NPCCONTROLLERmossaAvversario(int direzione) {
	int i;
	for (i = 0; i < 4; i++) if (i != direzione-1) direzioneMosseAvversario[i] = 0;
	direzioneMosseAvversario[direzione-1]++;
}

int NPCCONTROLLERinserireMuro(int *posizione, int *isVerticale, int coloreAvversario) {
	int i, direzione = -1, posAvversario;
	for (i = 0; i < 4; i++) {
		if (direzioneMosseAvversario[i] >= 3) direzione = i+1;
	}
	
	if (direzione != -1) {
		posAvversario = GIOCATOREgetPosizione(coloreAvversario);
		switch (direzione) {
			case 1:
				*posizione = posAvversario;
				*isVerticale = 0;
			break;
			case 2:
				*posizione = posAvversario + 1;
				*isVerticale = 1;
			break;
			case 3:
				*posizione = posAvversario + 8;
				*isVerticale = 0;
			break;
			case 4:
				*posizione = posAvversario;
				*isVerticale = 1;
			break;
			default:
				direzione = -1;
			break;
		}
	}
	
	if (direzione == -1) return 0;
	return 1;
}
