FILE *config;
int totalPlayers = 4; //how many players
int debugX = 0, debugY = 0;		//For Debug()
int clickX, clickY; //to record mouse click position
int rollFlag = 0;	//to initialize roll. 0 means not initialized 
int roll_timerIndex;
int dice = 1;		//Dice roll
int playerTurn = 0;	//counts the player turn
int diceResults[3];	//keeps the dice results. max 3 6s
int diceResult;
int diceResultsCount = 0;	//Keeps track if there is/are 6s
int moveFlag = 0;	//Move function works if the flag is set to 1
int player = 0;		//Player 0, 1, 2, 3
int pieceSelectionFlag;		//selecting the piece to be moved
int diceResultsIndex = 0;		//to move according the diceResults[]
int flagOfSix = 0;		//If there are sixes in the diceResults array
int gameState = 0;		//gameState 0 = menu. 1 normal mode. 2 pause menu. 3 player selection. 4 = vs. pc
int loss = 99;

class Ludo {
public:
	int piece[4][4][3], index[512][2];				//[i][j][k]. i = color. j = pieceNo. k = index, state, piecePersonalIndex
	void move(int a, int b, int result);
	int pieceLoss(int b);
	void Initial();
	void Piece();
	void Player();
	void PieceChange(int b, int result);
	void Roll();

}normal, snake;		//pieceLog keeps the record of the coordinates of the pieces. piece[a][b][c]. a = 4 color. b = 4 pieces of each color. 

void Ludo :: Initial()						//For changing the initial value of any variable
{
	int i = 0, j, k;
	for ( ; i < 6; i++) {
		index[i][1] = 315;
		index[i][0] = 469 - i * smallSq;
		index[99+i][0] = index[i][0];
		index[99 + i][1] = 315 + smallSq;
		index[50 - i][0] = index[i][0];
		index[50 - i][1] = 314 + 2 * smallSq;
	}
	for (j=0; i < 12; i++, j++) {
		index[i][1] = 283 - j * smallSq;
		index[i][0] = 281;
		index[18 - j][1] = index[i][1];
		index[18 - j][0] = 281 - 2 * smallSq;
		index[204 - j][1] = index[i][1];
		index[204 - j][0] = 281 - smallSq;
	}
	for (j =0, i = 19; i < 25; i++, j++) {
		index[i][1] = 315;
		index[i][0] = 187 - j * smallSq;
		index[31 - j][1] = 315 + 2 * smallSq;
		index[31 - j][0] = index[i][0];
		index[304 - j][1] = 315 + smallSq;
		index[304 - j][0] = index[i][0];
	}
	for (j =0, i = 32; i < 38; i++, j++) {
		index[i][1] = 408+j*smallSq;
		index[i][0] = 219;
		index[44 - j][0] = 218 + 2 * smallSq;
		index[44 - j][1] = index[i][1];
		index[404 - j][0] = 219 + smallSq;
		index[404 - j][1] = index[i][1];
	}
	index[25][0] = index[24][0]; index[25][1] = index[24][1] + smallSq;
	index[12][0] = index[11][0] - smallSq; index[12][1] = index[11][1];
	index[38][0] = index[37][0] + smallSq; index[38][1] = index[37][1];
	index[51][0] = index[50][0]; index[51][1] = index[50][1] - smallSq;


	index[60][0] = 421; index[60][1] = 204;
	index[61][0] = 388; index[61][1] = 236;
	index[62][0] = 358; index[62][1] = 204;
	index[63][0] = 388; index[63][1] = 173;

	index[70][0] = 139; index[70][1] = 204;
	index[71][0] = 107; index[71][1] = 235;
	index[72][0] = 76; index[72][1] = 204;
	index[73][0] = 107; index[73][1] = 173;

	index[80][0] = 139; index[80][1] = 485;
	index[81][0] = 107; index[81][1] = 516;
	index[82][0] = 76; index[82][1] = 485;
	index[83][0] = 107; index[83][1] = 454;

	index[90][0] = 421; index[90][1] = 487;
	index[91][0] = 389; index[91][1] = 518;
	index[92][0] = 358; index[92][1] = 487;
	index[93][0] = 389; index[93][1] = 456;

	//To initial every piece to be in home. Setting piece[a][b][c] = 0


	//Initial Piece Position
	for (i = 0, k=6; i < 4; i++, k++) {
		for (j = 0; j < 4; j++) {
			piece[i][j][0] = (k * 10) + j; piece[i][j][1] = 0;
			piece[i][j][2] = 0;
		}
	}

	//piece[1][1][0] = 11;	piece[1][1][2] = 50; piece[1][1][1] = 1;		//#####
}

/*void Ludo::Initial()						//Debug Initial
{
	int i = 0, j, k;
	for (; i < 6; i++) {
		index[i][1] = 315;
		index[i][0] = 469 - i * smallSq;
		index[99 + i][0] = index[i][0];
		index[99 + i][1] = 315 + smallSq;
		index[50 - i][0] = index[i][0];
		index[50 - i][1] = 314 + 2 * smallSq;
	}
	for (j = 0; i < 12; i++, j++) {
		index[i][1] = 283 - j * smallSq;
		index[i][0] = 281;
		index[18 - j][1] = index[i][1];
		index[18 - j][0] = 281 - 2 * smallSq;
		index[204 - j][1] = index[i][1];
		index[204 - j][0] = 281 - smallSq;
	}
	for (j = 0, i = 19; i < 25; i++, j++) {
		index[i][1] = 315;
		index[i][0] = 187 - j * smallSq;
		index[31 - j][1] = 315 + 2 * smallSq;
		index[31 - j][0] = index[i][0];
		index[304 - j][1] = 315 + smallSq;
		index[304 - j][0] = index[i][0];
	}
	for (j = 0, i = 32; i < 38; i++, j++) {
		index[i][1] = 408 + j * smallSq;
		index[i][0] = 219;
		index[44 - j][0] = 218 + 2 * smallSq;
		index[44 - j][1] = index[i][1];
		index[404 - j][0] = 219 + smallSq;
		index[404 - j][1] = index[i][1];
	}
	index[25][0] = index[24][0]; index[25][1] = index[24][1] + smallSq;
	index[12][0] = index[11][0] - smallSq; index[12][1] = index[11][1];
	index[38][0] = index[37][0] + smallSq; index[38][1] = index[37][1];
	index[51][0] = index[50][0]; index[51][1] = index[50][1] - smallSq;


	index[60][0] = 421; index[60][1] = 204;
	index[61][0] = 388; index[61][1] = 236;
	index[62][0] = 358; index[62][1] = 204;
	index[63][0] = 388; index[63][1] = 173;

	index[70][0] = 139; index[70][1] = 204;
	index[71][0] = 107; index[71][1] = 235;
	index[72][0] = 76; index[72][1] = 204;
	index[73][0] = 107; index[73][1] = 173;

	index[80][0] = 139; index[80][1] = 485;
	index[81][0] = 107; index[81][1] = 516;
	index[82][0] = 76; index[82][1] = 485;
	index[83][0] = 107; index[83][1] = 454;

	index[90][0] = 421; index[90][1] = 487;
	index[91][0] = 389; index[91][1] = 518;
	index[92][0] = 358; index[92][1] = 487;
	index[93][0] = 389; index[93][1] = 456;

	//To initial every piece to be in home. Setting piece[a][b][c] = 0

	for (i = 0, k = 6; i < 4; i++, k++) {
		for (j = 0; j < 4; j++) {
			piece[i][j][0] = (k * 10) + j; piece[i][j][1] = 0;
			piece[i][j][2] = 10;
		}
	}

	//Initial Piece Position
	piece[0][0][0] = 10;	piece[0][0][1] = 1;	
	piece[0][2][0] = 9;		piece[0][2][1] = 1;	
	piece[1][1][0] = 8;		piece[1][1][1] = 1;	
	piece[1][0][0] = 19;	piece[1][3][1] = 1;	
	piece[3][1][0] = 18;	piece[3][1][1] = 1;
	piece[3][0][0] = 22;	piece[3][0][1] = 1;
	piece[2][0][0] = 35;	piece[2][0][1] = 1;
	piece[2][2][0] = 45;	piece[2][2][1] = 1;
	piece[0][3][0] = 63;	piece[0][3][1] = 0;
	piece[1][3][0] = 73;	piece[1][3][1] = 0;
	piece[2][3][0] = 83;	piece[2][3][1] = 0;
	piece[3][3][0] = 93;	piece[3][3][1] = 0;
}*/