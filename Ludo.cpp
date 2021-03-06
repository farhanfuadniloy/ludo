/*
	##########################      Ludo       ##########################
	CSE 1202
		Aishwarya Ghosh_SK-50
		Farhan Fuad Haque_AE-35

	### Informations ###
		Each Square Side Length 37.4 px
		4 big squares are referenced as b
		sq.b side length = 271
		   2
		3 -|- 1
		   4

		Blue = 0; Yellow = 1; Green = 2; Red = 3;

	### Code References ###
		Class starts with an Underscore "_"
		Function starts with Capital
		camelCase convention is followed for the variables

		Final

	### Project To-Do
		Sound
		Pair
		UI
		CheatCode
*/


# include "iGraphics.h"
# define smallSq 32
# define PLAYERTIME 10
# define RADIUS 10
# include "initial.h"
# include "loadsave.h"


int playerTimer = PLAYERTIME;
int playerPos[4][2] = { {365, 78}, {43, 78}, {43,617}, {365,612} };	//Used in Ludo :: Player(). Player Name Position

int mposx, mposy;
char homemenu[15] = "dices.bmp"; //for homemenu
char button[10][15] = { "button1.bmp", "button2.bmp", "button3.bmp" };

char debugString[100];	int debugFlag = 0;	//Debug string. Located in move();


char debugStringMouse[100]; int debugMx, debugMy;			//Left Click Mouse mx, my
char debugString2[100] = "hello hello hello how low"; int debugString2X, debugString2Y;
char debugString3[100] = "hmm";	//piece selection flag
char debugString4[100];
char debugString5[100];
char debugString6[100];
char debugString7[100];
char debugString8[100];
char colorString[100];
char diceString[100];

struct buttonCordinate			//For Menu
{
	int x;
	int y;
}bCordinate[3];

void delay(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

int Ludo::pieceLoss(int b)
{
	int i, j;	//To determine if a piece will be eaten by another one. deathFlag = 0 means won't be eaten

	for (i = 0; i < totalPlayers; i++) {						//#### KHAWA GELE JA HOBE
		if (totalPlayers == 2 && i != 0)
			i++;
		for (j = 0; j < 4; j++) {
			if (piece[player][b][0] == piece[i][j][0] && player != i && piece[player][b][0] != 1 &&
				piece[player][b][0] != 14 && piece[player][b][0] != 27 && piece[player][b][0] != 40) {
						
					piece[i][j][0] = (60 + i * 10) + j;
					piece[i][j][2] = 0;
					piece[i][j][1] = 0;
						
					return 1;
			}
		}
	}
	return 0;
}

void PlayerChange()
{
	if (totalPlayers == 2) {
		player += 2;
		if (player > totalPlayers)
			player = 0;
	}
	else
		player++;
	if (player == totalPlayers && totalPlayers != 2)
		player = 0;
	diceResults[0] = 0; diceResults[1] = 0; diceResults[2] = 0;
	diceResultsCount = 0;
	flagOfSix = 0;
	pieceSelectionFlag = 0;
	loss = 99;
	playerTimer = PLAYERTIME;
}

void PlayerTimer()			//Time each player is going to get
{
	playerTimer--;
	if (playerTimer == 0) {
		playerTimer = 10;
		PlayerChange();
	}
}

void Ludo :: PieceChange(int b, int result)
{
	int temp;
	temp = piece[player][b][2] + result;
	if (temp > 51) {

		if ((100 + temp % 52) > 105);
		else {
			piece[player][b][0] = ((player + 1) * 100) + (temp % 52);
			piece[player][b][2] = 0;
		}
	}
	else {

		piece[player][b][0] = (piece[player][b][0] + result) % 52;
		piece[player][b][2] += result;
	}
}

void Ludo :: move(int a, int b, int result)		//piece[a][b]. -|- 4 sections get 4 side number. called by iMouse(). 1 diceResults[] at a time
{
	int i, j; //To determine if a piece will be eaten by another one. If piceLoss = 0, means no pieceLoss

		if(flagOfSix!= 0){

			if (piece[a][b][1] == 0) {
				piece[a][b][1] = 1; 
				piece[a][b][0] = 1 + (a * 13);
			}
			else {
				normal.PieceChange(b, result);
				loss += normal.pieceLoss(b);		//khawa jay kina and gele ja hobe. must be called after every piece Movement
			}
		}

		else {
			if (piece[player][b][1] == 1) {
				normal.PieceChange(b, result);
			}
			loss += normal.pieceLoss(b);
			if(loss == 99)
				PlayerChange();
			else {
				loss = 99;
				diceResults[0] = 0; diceResults[1] = 0; diceResults[2] = 0;
				diceResultsCount = 0;
				flagOfSix = 0;
				pieceSelectionFlag = 0;
			}
		}
	
}

void RollFlag()		//To change Roll Flag after 5 sec by iSetTimer()
{
	if (rollFlag == 1) {

		int homeFlag = 0;	//all pieces home

		if (flagOfSix == 3) {	//Means 3 6s
			PlayerChange();
		}
		else if (dice == 6) {
			flagOfSix++;
			diceResults[diceResultsCount] = 6;
			diceResultsCount++;
		}
		else {
			diceResults[diceResultsCount] = dice;
			diceResultsCount++;		//so that the loop works in move()
			for (int i = 0; i < 4; i++) {
				if (normal.piece[player][i][1] == 1) {
					homeFlag = 1; break;		//at least one out
				}
			}
			if (homeFlag == 0 && flagOfSix == 0) {
				PlayerChange();
			}
			else
				pieceSelectionFlag = 1;
		}

		sprintf(debugString2, "dRes[0] = %d, dRes[1] = %d, dRes[2] = %d; count = %d", diceResults[0], diceResults[1], diceResults[2], diceResultsCount);
	}

	rollFlag = 0;
}

void DiceChange()
{
	if (rollFlag == 1)
		dice = (rand() % 6) + 1;
}

void Ludo :: Roll()
{
	int roll_delayFlag = 0;
	if (rollFlag == 1) {
		sprintf(diceString, "images/%d.bmp", dice);
		iShowBMP(20, 27, diceString);
	}
}

void Debug()			//For debugging and finding co-ordinates purpose only
{
	char debugPos[100], playerggg[100];
	iSetColor(0, 0, 0);
	iPoint(debugX, debugY);
	iCircle(debugX, debugY, 5);
	sprintf(debugPos, "x is %d and y is %d", debugX, debugY);
	sprintf(playerggg, "Player: %d", player);
	iSetColor(255, 255, 255);
	iText(200, 700, debugPos);
	iText(10, 650, debugString);
	iText(10, 500, debugString);
}

void pieceDesign(int i, int j, int flag)
{
	int temp = 0;
	if (flag == 1)
		temp += i;
	if (i == 0)
		iSetColor(100, 100, 255);
	else if (i == 1)
		iSetColor(150, 0, 0);
	else if (i == 2)
		iSetColor(0, 150, 0);
	else
		iSetColor(150, 150, 0);

	iFilledCircle(normal.index[normal.piece[i][j][0]][0] + temp, normal.index[normal.piece[i][j][0]][1] + temp, RADIUS);
	iSetColor(0, 0, 0);
	iCircle(normal.index[normal.piece[i][j][0]][0] + temp, normal.index[normal.piece[i][j][0]][1] + temp, RADIUS + 1);
	iCircle(normal.index[normal.piece[i][j][0]][0] + temp, normal.index[normal.piece[i][j][0]][1]  + temp, RADIUS - 2);
}

void Ludo :: Piece()
{
	int flag;		//flag for stoppage or normal position
	for (int i = 0; i < totalPlayers; i++) {
		if (totalPlayers == 2 && i!=0)
			i++;
		sprintf(colorString, "images/piece%d.bmp", i);
		for (int j = 0; j < 4; j++) {
			flag = 0;
			if (piece[i][j][0] == 1 || piece[i][j][0] == 14 || piece[i][j][0] == 27 || piece[i][j][0] == 40){
				flag = 1;
				pieceDesign(i, j, flag);
				//iShowBMP(index[piece[i][j][0]][0] + i, index[piece[i][j][0]][1] + i, colorString);
			}
			else {
				pieceDesign(i, j, flag);
				//iFilledCircle(index[piece[i][j][0]][0] + 3, index[piece[i][j][0]][1] + 3, RADIUS);
			}
				//iShowBMP(index[piece[i][j][0]][0], index[piece[i][j][0]][1], colorString);
			//iShowBMP2(index[piece[i][j][0]][0], index[piece[i][j][0]][1], colorString, 0);
		}
	}

}

void Ludo :: Player()	//Shows Player Names. Active Player and time remaining.
{
	char playerString[100];
	iSetColor(0, 200, 0);
	iFilledRectangle(playerPos[player][0] - 5, playerPos[player][1] - 6, 71, 20);
	iSetColor(255, 0, 0);
	iFilledRectangle(playerPos[player][0] - 5, playerPos[player][1] - 6, (71 / PLAYERTIME) * (PLAYERTIME - playerTimer), 20);
	iSetColor(0, 0, 0);
	for (int i = 0; i < totalPlayers; i++) {
		sprintf(playerString, "Player %d", i + 1);
		if (totalPlayers == 2 && i != 0) {
			i++;
			if(player == 2)
				sprintf(playerString, "Player 2");
		}
		iText(playerPos[i][0], playerPos[i][1], playerString);
	}
}

void iDraw()
{
	//iClear();
	
	if (gameState == 0) {
		//homemenu
		iShowBMP(0, 0, "dices.bmp");
		//Debug();
	}

	else if (gameState == 2) {
		iShowBMP(0, 0, "images/pause.bmp");
		//Debug();
	}

	else if (gameState == 3) {
		iShowBMP(0, 0, "images/player.bmp");
		//Debug();
	}

	else {
		iShowBMP(0, 0, "images/board_2.bmp");
		char diceString2[100];
		sprintf(diceString2, "images/%d.bmp", dice);
		iShowBMP(20, 27, diceString2);
		
		//Debug(); //iSetColor(0, 0, 0);	iText(50, 27, debugString); iText(300, 27, debugStringMouse); iText(50, 700, debugString2);
		//sprintf(debugString3, "Piece Selection Flag = %d", pieceSelectionFlag); iText(50, 640, debugString3);	iText(50, 100, debugString5);
		//iText(200, 640, debugString4);

		iSetColor(0, 0, 0);
		if (gameState == 4) {		//vs. PC
			normal.Player();				//######################
			normal.Piece();
			normal.Roll();
		}
		else {
			normal.Player();
			normal.Piece();
			normal.Roll();
		}
	}
}

void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{
	int i;	//for loop

	sprintf(debugStringMouse, "mx = %d, my = %d", mx, my);

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		debugX = mx;	debugY = my;
	}

	//Game Start Menu. gameState = 0
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && gameState == 0) {
		if (mx >= 174 && mx <= 486 && my >= 278 && my <= 329) {
			gameState = 3;		//Player Selection menu
		}
		else if (mx >= 188 && mx <= 488 && my >= 181 && my <= 238) {
			Load();
			gameState = 1;
		}
		else if (mx >= 277 && mx <= 394 && my >= 95 && my <= 145)
			exit(0);
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && pieceSelectionFlag == 1) {	//pieceselection when dice != 6
		int tempI;	//temporary i for pc moves
								//PC flag will determine if a piece can be eaten. for vs PC only
		for (i = 0; i < 4; i++) {
			if (gameState == 4 && player == 2) {
				tempI = rand() % 4;
				if (flagOfSix == 2) {
					//pieceEatTest();	//will determine if a piece can be eaten. for vs PC only. Check before iDraw();
					normal.move(player, tempI, diceResults[1]);
					flagOfSix--;
					diceResults[1] = diceResults[2];
				}
				else if (flagOfSix == 1) {
					normal.move(player, tempI, diceResults[0]);
					flagOfSix--;
					diceResults[0] = diceResults[1];
				}
				else {
					while( normal.piece[player][tempI][1] == 0) 
						tempI = rand() % 4;
					normal.move(player, tempI, diceResults[0]);
				}
			}

			else if ((mx > normal.index[normal.piece[player][i][0]][0] - RADIUS && mx < normal.index[normal.piece[player][i][0]][0] + RADIUS) && (my > normal.index[normal.piece[player][i][0]][1] - RADIUS && my < normal.index[normal.piece[player][i][0]][1] + RADIUS)) {
				//pieceSelectionFlag = 0;				called after iMouse();
				sprintf(debugStringMouse, "piece is selected in position (%d, %d) for player: %d", mx, my, player);		//#######


				if (flagOfSix == 2) {
					normal.move(player, i, diceResults[1]);
					flagOfSix--;
					diceResults[1] = diceResults[2];
				}
				else if (flagOfSix == 1) {
					normal.move(player, i, diceResults[0]);
					flagOfSix--;
					diceResults[0] = diceResults[1];
				}
				else {
					normal.move(player, i, diceResults[0]);
				}
			}
		}
	}
	//Pause Menu
	if (gameState == 2 && mx > 116 && mx < 367 && my > 560 && my < 610)
		gameState = 1;
	if (gameState == 2 && mx > 63 && mx < 434 && my > 410 && my < 466)
		gameState = 0;
	if (gameState == 2 && mx > 60 && mx < 414 && my > 261 && my < 314) {	//###### Save Game Function
		Save();	//calls the Save function
		gameState = 1;
	}
	if (gameState == 2 && mx > 170 && mx < 338 && my > 108 && my < 165)
		exit(0);
	//Player Selection Menu
	if (gameState == 3 && mx > 74 && mx < 224 && my > 245 && my < 294) {	
		normal.Initial();  gameState = 1; totalPlayers = 2;
	}
	else if(gameState == 3 && mx > 72 && mx < 175 && my > 320 && my < 365){		//vs. PC
		normal.Initial(); gameState = 4; totalPlayers = 2;
	}
	else if (gameState == 3 && mx > 76 && mx < 226 && my > 169 && my < 223) {
		normal.Initial(); gameState = 1; totalPlayers = 3;
	}
	else if (gameState == 3 && mx > 74 && mx < 224 && my > 101 && my < 148) {
		normal.Initial();	gameState = 1; totalPlayers = 4;
	}
}


void iKeyboard(unsigned char key)
{
	if (key == 'w') {
		debugY += 1;
	}
	else if (key == 'a') {
		debugX -= 1;
	}
	else if (key == 's') {
		debugY -= 1;
	}
	else if (key == 'd') {
		debugX += 1;
	}
	if (key == ' ' && pieceSelectionFlag == 0)		//Roll Dice
		rollFlag = 1;
}

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_F1 && (gameState == 1 || gameState == 4) )		//To pause the game
		gameState = 2;
}

int main()
{
	int sum = 100;
	for (int l = 2; l >= 0; l--)
	{
		bCordinate[l].x = 300;
		bCordinate[l].y = sum;
		sum += 100;
	}

	normal.Initial();
	//sprintf(debugString, "piece[0][3] = %d", normal.piece[0][3][2]);
	roll_timerIndex = iSetTimer(2000, RollFlag);
	iSetTimer(100, DiceChange);
	iSetTimer(1000, PlayerTimer);
	iInitialize(500, 720, "Ludo");
	return 0;
}