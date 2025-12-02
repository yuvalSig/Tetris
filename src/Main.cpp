#define _CRT_SECURE_NO_WARNINGS
#include "General.h"
#include "GameConfig.h"
#include "Game.h"


int main() {
	
	Game* g = new Game;
	int flag=0;
	//winner = g->getWinner();
	while (flag != 9) {	// If game was paused - clear screen and present menu with continue option
		system("cls");
		if ((flag == 8&&g->getWinner()!=-1) || flag == 0)	// If instructions were presentedand winner indicates 
			flag = g->menu();								// game wasnt paused, present menu without continue option
		else
			flag = g->menu(g);
	}
	
	flag = g->getWinner();
	if(flag!=1&&flag!=2)
		g->exitGame();
}