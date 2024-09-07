#include "Modalita.h"
#include "Quoridor.h"


Modalita modalita;


void MODALITAinit() {
	modalita.gameMode = -1;
	modalita.playerType = -1;
}


void MODALITAsetGameMode(int gameMode) {
	modalita.gameMode = gameMode;
}


void MODALITAsetPlayerType(int playerType) {
	modalita.playerType = playerType;
}


int MODALITAgetGameMode() {
	return modalita.gameMode;
}


int MODALITAgetPlayerMode() {
	return modalita.playerType;
}
