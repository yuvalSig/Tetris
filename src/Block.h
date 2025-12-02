#pragma once
#include "GameConfig.h"
#include "Point.h"
#include <iostream>
#include <Windows.h>

class Block {		// Stopped here: need to continue class Block!
	GameConfig::shapes shape;		// A block contains a shape, color and it's cubes coordinates
	Point* cubes=new Point[GameConfig::BLOCK_SIZE];	// Note that each block contains exactly 4 cubes,
													// while that cubes[0] is the center
	int color;
public:
	
	void generateColors();
	GameConfig::shapes generateShape(Player& p);		// Generate block's shape and color
	void setCubes(Point* src) { if (src != nullptr) cubes = src; }
	void setCube(int index, int x, int y) { cubes[index].set(x, y); }
	int getColor() { return color; }
	Point* getCubes() { return cubes; }
	Block* copyBlock();		// Copy block and create a new block* with its values
	Point* copyCubes();		// Create and copy new Cubes array with block's cube's values
	bool move(GameConfig::keys direction, Player& p);	// Move block in given direction for given player p -
														// if valid return true, else return false
	bool rotate(GameConfig::keys direction, Player& p);	// Rotate block in given direction for player p -	
														// if valid return true, else return false
	void draw(int bgcolor = 7);
};



