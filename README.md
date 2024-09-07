
# Application Note

## Game Rules
Starting from the extra point 1 project, all the missing game rules have been implemented by extending the function:

```c
void GRAPHgetMosseValide(int idVerticePartenza, int v[], int coloreGiocatore, int* flagDiagonale);
```

A flag has been added, which is activated or deactivated depending on whether the player can move diagonally. This flag helps to correctly manage the array of valid moves. The maximum size of the array is 4 if diagonal moves are not possible, but all four directions are allowed. It is 5 if diagonal movement is possible. Once this functionality was extended, loading the array remained largely unchanged, except for the check for diagonal movement. This check is still made on the data structure representing the game state on the board. In particular, it is verified that there is no wall corresponding to an edge with weight 1 that blocks the diagonal move of the player. Additionally, the user can manage diagonal moves by splitting them into two moves: first moving left/right and then up/down or vice versa on the highlighted squares indicating valid positions. Alternatively, the user can move the joystick diagonally directly. In this case, the game piece will move diagonally. This is possible because, in the RIT handler function, when polling for an interrupt event in a joystick direction, it is checked if a pair of events occurs simultaneously. For example, a possible pair of events might be UP + LEFT, which is checked with:

```c
(LPC_GPIO1->FIOPIN & (1<<29)) == 0) && ((LPC_GPIO1->FIOPIN & (1<<27)) == 0)
```

When the player makes their final move, the GUI layer of the application handles clearing the squares marked as possible valid moves and starts a new turn for the opponent with the updated board state.

## Menu
To start playing, the user must press the KEY 0 button when the board is powered on. At this point, in the RIT handler where button bouncing is managed, the game initializes. During initialization, the game enters the `INIT_MODE`. In this mode, the game displays a series of menus to configure various game settings. The initial menu allows the user to choose between single or dual board mode, navigated using the joystick and confirmed by pressing it. The current selection is represented by a variable that graphically shows the user's menu choice. Once a choice is made, it is recorded in the `Partita` data structure, which describes the game state using various fields.

After selecting the single or dual board mode, the user can choose whether to play against an NPC, depending on the previous choice. In summary, the game can have four different modes:

- (SINGLE_BOARD + HUMAN)
- (SINGLE_BOARD + NPC)
- (TWO_BOARDS + HUMAN)
- (TWO_BOARDS + NPC)

Getter functions like:

```c
int QUORIDORisInit(void);
int PARTITAisSetNPC(Partita partita);
int PARTITAisTwoBoard(Partita partita);
```

can be used to verify the current game mode at any time. This is useful during code execution and in the RIT handler, as it allows specific functions to be executed based on the set mode. Depending on the chosen mode, an initialization function is executed to correctly initialize the game instance according to the user's choices:

- `void QUORIDORstartSingleBoardHuman(void);`
- `void QUORIDORstartSingleBoardNPC(void);`
- `void QUORIDORstartTwoBoardsHuman(void);`
- `void QUORIDORstartTwoBoardsNPC(void);`

These functions initialize the entire game environment and players, which can be easily created with a function that defines the player type based on various flags:

```c
void GIOCATOREcrea(int colore, int isNPC, int isExternalBoard);
```

## Multiplayer
For multiplayer mode, after selecting the `TWO_BOARDS` and `NPC/HUMAN` modes using the joystick, the handshake function is executed. This function starts `TIMER0` with a period of 3 seconds. When the timer expires, it is disabled, and it checks whether the handshake packet with value `0xFF000000` has been received. If the packet is received before the 3 seconds expire, the timer stops early, providing a 3-second handshake window to verify the connection with another board. If the handshake packet is not received, an error message is displayed.

After the game starts, the following two functions:

- `void CANQsendMossa(Mossa mossa);`
- `Mossa CANQreadMossa(void);`

are used to send the move just made by the board and receive the opponent's move. These functions are used to manage the current turn. When a move is received, it is unpacked, creating a `MOSSA` object read by the application that updates the state and board graphics. At this stage, the function:

```c
int MOSSA_da_XY_2_posizione(int x, int y, int isPlayer)
```

converts the universal `(x, y)` coordinate system to the internal coordinate system managed by the project.

## NPC
When the player selects `SINGLE_BOARD` mode with an NPC, player 2 is set as the NPC by default. The best move decision logic keeps track of the board state and selects the move that will most quickly lead to victory. Each move is assigned a weight: the higher the weight, the better the move. The moves are weighted in the following order:

1. Forward move: the quickest route to promotion.
2. Left or right move.
3. Backward move: a forced move when the opponent's walls prevent any other choice.

The available move with the highest weight is selected as the final choice, and the turn passes to the opponent.

```c
int GIOCATORE_NPC_getBestDirection(int colore);
```

The weight of a move is dynamic and varies based on the NPC's previous moves. If a move has just been made, the counter-move's weight is reduced to a minimum value. A counter-move refers to the opposite move, allowing the NPC to return to its previous position. This way, the NPC player quickly exits such traps.

Finally, the NPC player can also place walls after verifying they do not create loops to reduce the opponent's chances of winning, using the function:

```c
int NPCCONTROLLERinserireMuro(int *posizione, int *isVerticale, int coloreAvversario);
```

The wall selection is managed by a controller that "observes" the opponent's (human player's) moves. When it detects a repeated pattern, it places a wall to interrupt it. This technique is based on the premise that if the opponent is making repeated moves, they are moving toward victory without hindrance.

---

*Samuele Pasquale*  
Application Note
