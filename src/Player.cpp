#include "Player.h"
#include "Block.h"
//void Player::newCurrent() {

//}

void Player::setGameGrid(int src) {
	for (int i = 0; i < GameConfig::GAME_HEIGHT; i++)
		for (int j = 0; j < GameConfig::GAME_WIDTH; j++)
			gameGrid[i * GameConfig::GAME_WIDTH + j] = src;
}



void Player::drawCurrent() {
	currentShape->draw(getColor());
}

void Player::eraseCurrent() {
	currentShape->draw();
}

void Player::markGameGrid(Point* cubes, int mark) {
	for (int i = 0; i < GameConfig::BLOCK_SIZE; i++)
		gameGrid[(cubes[i].gety()-starty) * GameConfig::GAME_WIDTH + (cubes[i].getx()-startx)] = mark;

}

int Player::setNewCurrent() {
	Block* curr = new Block;
	int i = 0;
	bool game_over = false;
	Point* currCubes;
	if (currentShape != nullptr) {
		currCubes = currentShape->getCubes();
		markGameGrid(currCubes, currentShape->getColor());
		delete currentShape;
	}
	curr->generateShape(*this);		// Yuvals function
	currCubes=curr->getCubes();
	while (i < GameConfig::BLOCK_SIZE && !game_over) {
		if (!isSpotAvailable(currCubes[i].getx(),currCubes[i].gety()))
			game_over=true;
		i++;
	}
	
	if (game_over) {
		if (dropx == GameConfig::DROPXLP)
			return 2;		// Player 2 wins!
		else
			return 1;		// Player 1 wins!
	}
	else {
		currentShape = curr;
		drawCurrent();
		return 0;
	}
}

void Player::setCurrent(Block* toAdd) {
	if (currentShape != nullptr)
		delete currentShape;
	if (toAdd)
		currentShape = toAdd;
	else {
		cout << "\nBlock given in setCurrent function invalid!";
		setNewCurrent();
	}
}


bool Player::isMoveValid(GameConfig::keys direction) {
	Block* temp = currentShape;
	return temp->move(direction, *this);
}

bool Player::isSpotAvailable(int x, int y) {
	if ((x >= startx) && (x < startx + GameConfig::GAME_WIDTH) && (y >= starty) && (y < starty + GameConfig::GAME_HEIGHT))
		return (gameGrid[(y - starty) * GameConfig::GAME_WIDTH + (x - startx)]==GameConfig::COLORS[7]);
	else
		return false;
}

// Return true if spot's available and false otherwise


bool Player::isCurrentAtMin() {			// Should the block stop dropping down?
	bool res = false;
	int i = 0;
	Point* temp = currentShape->getCubes();
	int px,py;
	while (i < GameConfig::BLOCK_SIZE && !res) {
		px = temp[i].getx();
		py = temp[i].gety();
		if (!isSpotAvailable(px, py + 1))
			res = true;
		i++;
	}
	return res;
}

int Player::automaticDrop() {
	bool res = true;		// Res is true unless current is at the minimum
	Point* temp = currentShape->getCubes();		// Get current's cubes array by pointer - to change the original array
	if (!isCurrentAtMin()) {
		eraseCurrent();		// Erase shape from the board
		for (int i = 0; i < GameConfig::BLOCK_SIZE; i++) 	// Add 1 to every cube's y
			temp[i].sety(temp[i].gety() + 1);

		drawCurrent();			// Draw new current on the board after drop
		return 0;
	}			
	else {
		res = false;
		return setNewCurrent();
	}
}

void Player::dropBlock() {
	while (!isCurrentAtMin()) {
		automaticDrop();
	}
	setNewCurrent();
}

void Player::setStartAndDropXY(int startingx, int startingy, int droppingx, int droppingy) {
	startx = startingx;
	starty = startingy;
	dropx = droppingx;
	dropy = droppingy;
}

void Player::initializeGame(int startingx, int startingy, int droppingx, int droppingy) {
	setStartAndDropXY(startingx, startingy, droppingx, droppingy);
	setGameGrid(GameConfig::COLORS[7]);
	setNewCurrent();
}

void Player::drawGameGrid() {
	Point* temp=new Point;
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++) {	// Enter for loops and go over every coordinate in the board
		for (int j = 0; j < GameConfig::GAME_HEIGHT; j++) {
			if (!isSpotAvailable(i+startx, j+starty)) {		// If spot isn't available in the board, paint it using random colors
				temp->set(i, j);
				temp->paint(startx, starty, gameGrid[j * GameConfig::GAME_WIDTH + i]);
			}
		}
	}
	delete temp;
}

