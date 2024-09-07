#ifndef MODALITA_H 
#define MODALITA_H

// GAME MODE
#define GAME_MODE_SINGLE_BOARD 2
#define GAME_MODE_TWO_BOARD 3
#define GAME_MODE_HUMAN 4
#define GAME_MODE_NPC 5


typedef struct modalita_s {
	int gameMode;
	int playerType;
} Modalita;

void MODALITAinit(void);
void MODALITAsetGameMode(int gameMode);
void MODALITAsetPlayerType(int playerType);
void MODALITAstartGame(void);

int MODALITAgetGameMode(void);
int MODALITAgetPlayerMode(void);

#endif
