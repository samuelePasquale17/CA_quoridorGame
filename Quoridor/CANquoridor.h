#ifndef CANQUORIDOR_H 
#define CANQUORIDOR_H

#include "Mossa.h"


void CANQhandshake(void);

void CANQsendMossa(Mossa mossa);
Mossa CANQreadMossa(void);
void CANhandshakeClear(void);

#endif
