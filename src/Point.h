#pragma once
#include "GameConfig.h"
#include <iostream>

class Player;
class Point {		// Class point is done!
	int x = 1, y = 1;
public:
	void set(int x, int y) { this->x = x; this->y = y; }
	int getx() { return x; }
	void setx(int src) { x = src; }
	int gety() { return y; }
	void sety(int src) { y = src; }
	void move(GameConfig::keys direction);		// Moves the point to given direction
	void rotate(Point* center, GameConfig::keys direction);
	bool isMoveValid(GameConfig::keys direction, Player& p);	// Is move valid in given direction for given player?
																// if so move and return true, else return false
	int isRotateValid(GameConfig::keys direction, Player& p);	// Is rotate valid in given direction for given player?
																// if so rotate and return true, else return false
	void paint(int startx, int starty, int bgcolor = 7);
	void rotateClockWise(Point* center);
	void rotateCounterClockWise(Point* center);
};
