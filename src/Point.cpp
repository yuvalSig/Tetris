#include "Point.h"
#include "Block.h"
#include "Player.h"
#include <Windows.h>
#include <conio.h>
#include "General.h"

using namespace std;
class Block;
class Player;





void Point::move(GameConfig::keys direction) {
	if ((direction == GameConfig::keys::LPLEFT) || (direction == GameConfig::keys::RPLEFT))
		x -= 1;
	else if ((direction == GameConfig::keys::LPRIGHT) || (direction == GameConfig::keys::RPRIGHT))
		x += 1;
	
}

void Point::rotateCounterClockWise(Point* center) {
	int diffx = x - center->getx();
	int diffy = y - center->gety();
	x = center->getx() + diffy;
	y = center->gety() - diffx;

	// Return...
}

void Point::rotateClockWise(Point* center) {
	int diffx = x - center->getx();
	int diffy = y - center->gety();
	x = center->getx() - diffy;
	y = center->gety() + diffx;
}

void Point::rotate(Point* center,GameConfig::keys direction) {
	if ((direction == GameConfig::keys::LPCW) || (direction == GameConfig::keys::RPCW))
		rotateClockWise(center);
	else if ((direction == GameConfig::keys::LPCOUNTERCW) || (direction == GameConfig::keys::RPCOUNTERCW)) {
		rotateCounterClockWise(center);
	}
}

int Point::isRotateValid(GameConfig::keys direction, Player& p) {
	Point* center;
	center = p.getCurrent()->getCubes();
	rotate(center, direction);
	if(!p.isSpotAvailable(x, y))
		return 4;
	else
		return 0;
}

bool Point::isMoveValid(GameConfig::keys direction, Player& p){
	Point temp;
	bool res = false;
	temp.set(x, y);		// x and y are block current's cubes array points
	temp.move(direction);
	res= p.isSpotAvailable(temp.getx(), temp.gety());
	/*if (res)			This shouldnt be here! we should update only after all 
	*					points are valid!
		set(temp.getx(), temp.gety());*/
	return res;
}

void Point::paint(int startx, int starty, int bgcolor) {
	gotoxy(startx + x, starty + y);
	if (bgcolor == GameConfig::BLOCK_CHAR_HANDLE_WITHOUT_COLOR) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[7]);
		cout << GameConfig::BLOCK_CHAR_HANDLE_WITHOUT_COLOR;
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgcolor);	// Sets color of text to 
		cout << GameConfig::BLOCK_CHAR;																	// given color
	}
}
