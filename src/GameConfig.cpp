#include "GameConfig.h"
#include <Windows.h>

const int GameConfig::COLORS[] = {
    BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,  // Vertical - white, need to change to actual color
    BACKGROUND_RED,                                       // Square
    BACKGROUND_GREEN,                                     // Cross
    BACKGROUND_BLUE,                                      // SerpentRight
    BACKGROUND_RED | BACKGROUND_GREEN,                    // AngleRight
    BACKGROUND_GREEN | BACKGROUND_BLUE,                   // AngleLeft
    BACKGROUND_RED | BACKGROUND_BLUE,
    7                                                     // Black
};
const int GameConfig::NUM_OF_COLORS = sizeof(COLORS) / sizeof(int);