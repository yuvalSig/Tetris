#pragma once
#include "GameConfig.h"
#include "General.h"
#include "Player.h"
#include <iostream>

class Game
{
	Player* players = new Player[2];	// Each game has 2 players - players[0]: left player, players[1]: right player
	int winner = 0;
	void drawBorderSomewhere();
	int start();
	int continueGame(Game* toContinue);
	bool isCharForLeftPlayer(GameConfig::keys keyPressed);
	Player* getPlayersPointer() { return players; }
	void printInstructions();
	bool isInputValid(int input, bool saved_game);
	void drawGameGrids();
	void updateGameColors();
public:
	int menu(Game* g1=nullptr);
	int getWinner() { return winner; }
	void setWinner(int src) { winner = src; }
	const char* announceWinner(int num);
	void exitGame();
};

