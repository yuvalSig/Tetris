#pragma once
#include "Block.h"
#include "GameConfig.h"

class Point;
class Block;

class Player {
	Block* currentShape = nullptr;	// The block currently dropping
	short int* gameGrid = new short int[GameConfig::GAME_WIDTH * GameConfig::GAME_HEIGHT];	
	int startx, starty, dropx, dropy;
	/* A boolean array of player's game board and occupied points, represents the
	 taken points(by dropped blocks) in the board. Array is one-dimensional, and
	 and each y has GAME_WIDTH different spots in the array - a 1D array representing
	  a 2D array for efficiency reasons. */
public:
	int getColor() { Block* temp = getCurrent(); return temp->getColor(); }
	int getDropX() { return dropx; }
	int getDropY() { return dropy; }
	Block* getCurrent() { return currentShape; }
	void setGameGrid(int src);		// Sets gameGrid array to true to initialize game
	int setNewCurrent();
	void setCurrent(Block* toAdd);
	void setStartAndDropXY(int startingx, int startingy, int droppingx, int droppingy);
	void initializeGame(int startingx, int startingy, int droppingx, int droppingy);
	bool isSpotAvailable(int x, int y);
	void markGameGrid(Point* cubes, int mark);	// Marks cubes' coordinates as mark's value on gameGrid
	bool isCurrentAtMin();			// Should the block stop dropping down? 
	int automaticDrop();			// Drop block by 1 y point. If block is at minimum, return false
	void dropBlock();					// Slowly drop the currentShape block untill fully shown in board
	bool isMoveValid(GameConfig::keys direction);	// Could current move in given direction? If so, move it
	void drawCurrent();					// Draw block on the board
	void eraseCurrent();		// Erase the drawing of the given coordinates on the board
	void drawGameGrid();
	void deleteCurrent() { if (currentShape != nullptr) delete currentShape; }
	void deleteGameGrid() { if (gameGrid != nullptr) delete[] gameGrid; }
};
