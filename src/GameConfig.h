#pragma once
using namespace std;

class GameConfig {
public:
	enum class keys { LPLEFT = 'a', LPRIGHT = 'd', LPCW = 's', LPCOUNTERCW = 'w', LPDROP = 'x', RPLEFT = 'j', RPRIGHT = 'l', RPCW = 'k', RPCOUNTERCW = 'i', RPDROP = 'm', ESC = 27 };
	enum class shapes { Vertical, Square, Cross, SerpentRight, AngleRight, AngleLeft, ZigzagLeft };
	//enum class shapes { I, J, L, O, S, RS, T };//todo - give meaningfull names to shapes
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int STARTING_X_LEFT = 1;	// Left border of left-player's board
	static constexpr int STARTING_Y_LEFT = 3;	// Top border of left-player's board
	static constexpr int STARTING_X_RIGHT = 20;	// Left border of right-player's board
	static constexpr int STARTING_Y_RIGHT = 3;	// Top border of right-player's board
	static constexpr int DROPXLP = 6, DROPYLP = 3, DROPXRP = 25, DROPYRP = 3;	// Make sure RP is correct
							// DROPXLP is the drop point's x (of current dropping block) for left player
	static constexpr char BLOCK_CHAR_HANDLE_COLOR = ' ';
	static constexpr char BLOCK_CHAR_HANDLE_WITHOUT_COLOR = 'X';
	static const int NUM_OF_COLORS ;
	static const int COLORS[];
	static constexpr int NUM_OF_SHAPES = 7;
	static constexpr int BLOCK_SIZE = 4;
	static constexpr char BLOCK_CHAR = ' ';
	static constexpr int SLEEP_TIME = 500;
};
