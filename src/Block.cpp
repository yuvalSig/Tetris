#include "Block.h"
#include "Player.h"
#include "General.h"

class Player;
/*bool Block::isMoveValid(GameConfig::keys direction) {
	bool res = true;
	for(int i=0;i<GameConfig::BLOCK_SIZE;i++)
		if(cubes[i].isMoveValid())
}*/

void Block::generateColors() {
        // Set color based on shape 
    switch (shape) {
    case GameConfig::shapes::Vertical:
        color = GameConfig::COLORS[0]; // Color for Vertical
        break;
    case GameConfig::shapes::Square:
        color = GameConfig::COLORS[1]; // Color for Square
        break;
    case GameConfig::shapes::Cross:
        color = GameConfig::COLORS[2]; // Color for Cross
        break;
    case GameConfig::shapes::SerpentRight:
        color = GameConfig::COLORS[3]; // Color for Cross
        break;
    case GameConfig::shapes::AngleRight:
        color = GameConfig::COLORS[4]; // Color for Cross
        break;
    case GameConfig::shapes::AngleLeft:
        color = GameConfig::COLORS[5]; // Color for Cross
        break;
    case GameConfig::shapes::ZigzagLeft:
        color = GameConfig::COLORS[6]; // Color for Cross
        break;
            // Add cases for other shapes and assign corresponding colors
    default:
            // Default color if the shape is not recognized
        color = GameConfig::COLORS[0];
        break;
    }
}


GameConfig::shapes Block::generateShape(Player& p) {
    shape = (GameConfig::shapes)(rand() % GameConfig::NUM_OF_SHAPES);
    generateColors();
    int dropx = p.getDropX(), dropy = p.getDropY();
    // Randomly select a shape using a switch statement 
    switch ((int)shape) {
    case 0:
        // Set the cubes for the Vertical shape  white color
        shape = GameConfig::shapes::Vertical;
        for(int i=0;i<GameConfig::BLOCK_SIZE;i++)
            cubes[i].set(dropx, dropy+i);
        break;
    case 1:
        // Set the cubes for the Square shape , red color
        shape = GameConfig::shapes::Square;
        cubes[0].set(dropx, dropy);
        cubes[1].set(dropx, dropy+1);
        cubes[2].set(dropx+1, dropy);
        cubes[3].set(dropx+1, dropy+1);
        break;
    case 2:
        shape = GameConfig::shapes::Cross;
        // Set the cubes for the Cross shape green color
        cubes[0].set(dropx, dropy);
        cubes[1].set(dropx-1, dropy+1);
        cubes[2].set(dropx, dropy+1);
        cubes[3].set(dropx+1, dropy+1);
        break;
    case 3:
        shape = GameConfig::shapes::SerpentRight;
        // Set the cubes for the SerpentRight shape blue color
        cubes[0].set(dropx, dropy);
        cubes[1].set(dropx+1, dropy);
        cubes[2].set(dropx, dropy+1);
        cubes[3].set(dropx-1, dropy+1);
        break;
    case 4:
        shape = GameConfig::shapes::AngleRight;
        // Set the cubes for the AngleRight shape yellow color
        cubes[0].set(dropx, dropy);
        cubes[1].set(dropx, dropy+1);
        cubes[2].set(dropx, dropy+2);
        cubes[3].set(dropx+1, dropy+2);
        break;
    case 5:
        shape = GameConfig::shapes::AngleLeft;
        // Set the cubes for the AngleLeft shape Sky color
        cubes[0].set(dropx, dropy);
        cubes[1].set(dropx, dropy+1);
        cubes[2].set(dropx, dropy+2);
        cubes[3].set(dropx-1, dropy+2);
        break;
    case 6:
        shape = GameConfig::shapes::ZigzagLeft;
        // Set the cubes for the ZigzagLeft shape purple color
        cubes[0].set(dropx-1, dropy);
        cubes[1].set(dropx, dropy);
        cubes[2].set(dropx, dropy+1);
        cubes[3].set(dropx+1, dropy+1);
        break;
    }

    return shape;
}

bool Block::move(GameConfig::keys direction, Player& p) {
	bool res = true;
	int i = 0;
    if ((direction == GameConfig::keys::LPLEFT) || (direction == GameConfig::keys::RPLEFT) || (direction == GameConfig::keys::LPRIGHT) || (direction == GameConfig::keys::RPRIGHT)) {
        while ((i < GameConfig::BLOCK_SIZE) && (res)) {
            res = res&&(cubes[i].isMoveValid(direction, p));
            i++;
        }
        if (res) {
            p.eraseCurrent();
            for (int i = 0; i < GameConfig::BLOCK_SIZE; i++) 
                cubes[i].move(direction);
            p.drawCurrent();
        }
    }
	else if ((direction == GameConfig::keys::LPCW) || (direction == GameConfig::keys::LPCOUNTERCW) || (direction == GameConfig::keys::RPCW) || (direction == GameConfig::keys::RPCOUNTERCW))
		res = rotate(direction, p);
	else if ((direction == GameConfig::keys::RPDROP) || (direction == GameConfig::keys::LPDROP))
		p.dropBlock();

					// Need to add else case for LPDROP and RPDROP
		
	return res;
}

void Block::draw(int bgcolor) {
    for (int i = 0; i < GameConfig::BLOCK_SIZE; i++) {
        gotoxy(cubes[i].getx(), cubes[i].gety());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgcolor);	// Sets color of text to 
        // given color
        cout << GameConfig::BLOCK_CHAR;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
}


Block* Block::copyBlock() {
	Block* res = new Block;
	Point* rescubes = new Point[GameConfig::BLOCK_SIZE];
	res->color = color;
	res->shape = shape;
	for (int i = 0; i < GameConfig::BLOCK_SIZE; i++)
		rescubes[i].set(cubes[i].getx(), cubes[i].gety());
    res->setCubes(rescubes);
	return res;
}

Point* Block::copyCubes() {
	Point* res = new Point[GameConfig::BLOCK_SIZE];
	for (int i = 0; i < GameConfig::BLOCK_SIZE; i++)
		res[i].set(cubes[i].getx(), cubes[i].gety());
	return res;
}

bool Block::rotate(GameConfig::keys direction, Player& p) {
	int i=1;
	Block* test = copyBlock();
	Point* testCubes = test->getCubes();
	bool flag = true;
	while(i<GameConfig::BLOCK_SIZE&&flag) {
		testCubes[i].isRotateValid(direction, p);
		flag = flag&&p.isSpotAvailable(testCubes[i].getx(),testCubes[i].gety());
        i++;
	}
	if (flag) {
        p.eraseCurrent();
		p.setCurrent(test);     // We might have a memory leak like this - need to delete old current
        p.drawCurrent();
	}
    else {
        delete testCubes;
        delete test;
    }
	return flag;
}
