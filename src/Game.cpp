#include "Game.h"
#include "Block.h"
using namespace std;

int Game::menu(Game* g1) {
	int input=-1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	system("cls");	// Clear screen of menu's output
	cout << "Welcome to the Tetris game!\nEnter input your input:\nStart new game - 1\n";
	if (g1)
		cout << "Continue paused game - 2\n";
	cout << "Present instructions and keys - 8\nExit - 9\n";
	cin >> input;				// Main idea: menu exits and returns 9 only in case 9 was inputted during menu.
								// if we have a winner we should (according to instructions) return to the menu
		while (!isInputValid(input, (g1 != nullptr))) {
		cout << "\nInput invalid. try again:";
		cin >> input;
	}
	switch (input) {											
	case 1:
		winner = start();
		input = winner;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		system("cls");
		if (winner != -1) {
			cout << announceWinner(winner);
			g1->exitGame();		// Delete objects after game is over with exitGame function
		}
		break;
	case 2:
		g1->setWinner(g1->continueGame(g1));
		input = g1->getWinner();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		system("cls");
		if (winner != -1) {
			cout << announceWinner(winner);
			g1->exitGame();		// Delete objects after game is over with exitGame function
		}
		break;
	case 8:
		printInstructions();
		cout << "\nPress any key to continue...";
		_getch();
		break;
	case 9:
		break;
	}
	return input;
}

int Game::continueGame(Game* toContinue) {
	char curr = 0;
	winner = 0;
	if (toContinue == nullptr) {	// Check Game pointer for nullptr
		cout << "\nNo saved game in memory. Starting new game!";
		start();
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[7]);
		system("cls");	// Clear screen of menu's output
		players = toContinue->getPlayersPointer();
		drawBorderSomewhere();
		drawGameGrids();
		while (winner == 0) {			// Enter while loop untill we have a winner
			for (int i = 0; i < 2; i++) {
				if (_kbhit()) {
					curr = _getch();
					if ((GameConfig::keys)curr == GameConfig::keys::ESC) {
						winner = -1;
						break;
					}
					else if (isCharForLeftPlayer((GameConfig::keys)curr)) {		// If input is players 1's input
						players[0].isMoveValid((GameConfig::keys)curr);

					}
					else {			// If input is player 2's input
						players[1].isMoveValid((GameConfig::keys)curr);
					}				// Need to add if case for basic keys like pause
				}
			}
			if (winner != -1) {
				Sleep(GameConfig::SLEEP_TIME);
				winner = players[0].automaticDrop();
				if (winner == 0)
					winner = players[1].automaticDrop();
				else
					break;
			}
		}

	}
	return winner;		// For compilation only!!
}

void Game::drawGameGrids() {
	players[0].drawGameGrid();
	players[1].drawGameGrid();
}

int Game::start() {
	srand((unsigned int)std::time(0));	// Seed random number generator with currentShape time
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	system("cls");	// Clear screen of menu's output
	drawBorderSomewhere();		// Draw game borders
	char curr = 0;				// Curr is for key's input (from players)
	players[0].initializeGame(GameConfig::STARTING_X_LEFT, GameConfig::STARTING_Y_LEFT, GameConfig::DROPXLP, GameConfig::DROPYLP);
	players[1].initializeGame(GameConfig::STARTING_X_RIGHT,GameConfig::STARTING_Y_RIGHT, GameConfig::DROPXRP, GameConfig::DROPYRP);
	while (winner==0) {			// Enter while loop untill we have a winner
		for (int i = 0; i < 2; i++) {
			if (_kbhit()) {
				curr = _getch();
				if ((GameConfig::keys)curr == GameConfig::keys::ESC) {
					winner = -1;
					break;
				}
				else if (isCharForLeftPlayer((GameConfig::keys)curr)) {		// If input is players 1's input
					players[0].isMoveValid((GameConfig::keys)curr);

				}
				else {			// If input is player 2's input
					players[1].isMoveValid((GameConfig::keys)curr);
				}				// Need to add if case for basic keys like pause
			}
		}
		if (winner != -1) {
			Sleep(GameConfig::SLEEP_TIME);
			winner = players[0].automaticDrop();
			if (winner == 0)
				winner = players[1].automaticDrop();
			else
				break;
		}
	}
	return winner;
}

const char* Game::announceWinner(int num) {// Function maps out return values given an int value
	if (num == 1)
		return "player 1";
	else if (num == 2)
		return "player 2";
	else if (num == 3)
		return "tie";
	else
		return "Error";
}

void Game::drawBorderSomewhere() {
	gotoxy(GameConfig::STARTING_X_LEFT+5, 0);
	cout << "P1";
	gotoxy(GameConfig::STARTING_X_RIGHT+5, 0);
	cout << "P2";
	for (int col = GameConfig::STARTING_X_LEFT; col < (GameConfig::STARTING_X_LEFT + GameConfig::GAME_WIDTH); col++) {		// col<width+1 because the col at the width place is playable
		gotoxy(col, GameConfig::STARTING_Y_LEFT - 1);	// For each column, draw the upper and lower border
		cout << "-";
		gotoxy(col, (GameConfig::STARTING_Y_LEFT + GameConfig::GAME_HEIGHT));
		cout << "-";
	}
	for (int row = GameConfig::STARTING_Y_LEFT; row < (GameConfig::STARTING_Y_LEFT + GameConfig::GAME_HEIGHT); row++) {
		gotoxy(GameConfig::STARTING_X_LEFT - 1, row);		// For each row, draw the left and right border
		cout << "|";
		gotoxy((GameConfig::STARTING_X_LEFT + GameConfig::GAME_WIDTH), row);
		cout << "|";
	}
	// Print right player's borders
	for (int col = GameConfig::STARTING_X_RIGHT; col < (GameConfig::STARTING_X_RIGHT + GameConfig::GAME_WIDTH); col++) {
		gotoxy(col, GameConfig::STARTING_Y_RIGHT - 1);
		cout << "-";
		gotoxy(col, (GameConfig::STARTING_Y_RIGHT + GameConfig::GAME_HEIGHT));
		cout << "-";
	}
	for (int row = GameConfig::STARTING_Y_RIGHT; row < (GameConfig::STARTING_Y_RIGHT + GameConfig::GAME_HEIGHT); row++) {
		gotoxy(GameConfig::STARTING_X_RIGHT - 1, row);
		cout << "|";
		gotoxy((GameConfig::STARTING_X_RIGHT + GameConfig::GAME_WIDTH), row);
		cout << "|";
	}
}

bool Game::isCharForLeftPlayer(GameConfig::keys keyPressed) {
	if (keyPressed == GameConfig::keys::LPCOUNTERCW || keyPressed == GameConfig::keys::LPCW)
		return true;
	else if (keyPressed == GameConfig::keys::LPLEFT || keyPressed == GameConfig::keys::LPRIGHT || keyPressed == GameConfig::keys::LPDROP)
		return true;
	else
		return false;
}

void Game::printInstructions() {
	system("cls");
	cout << "BASIC GAME RULES:";
	cout << "\nIn Tetris, you must arrange a sequence of small shapes called Tetraminos, into complete lines.";
	cout << "\nAs each line is completed, it will disappear from the screen.";
	cout << "\nTetraminos fall from the top of the play field to the bottom.";
	cout << "\nEach Tetramino is made up of four blocks, arranged into seven different patterns.";
	cout << "\nA player loses if a Tetramino cannot fall into his board, therefore the other player will win.";
	cout << "\nBASIC KEYS:\nLeft Player:\na - move left, d - move right\ns - rotate clockwise, w - rotate counter-clockwise";
	cout << "\nx - drop Tetramino\nRight Player:\nj - move left, l - move right\nk - rotate clockwise, i - rotate ";
	cout << "counter-clockwise\nm - drop Tetramino";
}

bool Game::isInputValid(int input, bool saved_game) {
	if (input == 2 && saved_game)	// Check option for trying to enter saved game, when no saved game exists
		return true;
	if (input == 1 || input == 8 || input == 9)
		return true;
	else
		return false;
}

void Game::exitGame() {
	for (int i = 0; i < 2; i++) {
		players[i].deleteCurrent();
		players[i].deleteGameGrid();
	}
}

