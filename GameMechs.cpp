#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include <time.h>

// Default Constructor: Initializes the game mechanics with default values
GameMechs::GameMechs() {
    input = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 30; // Default board width
    boardSizeY = 15; // Default board height
    score = 0;
}

// Parameterized Constructor: Initializes the game mechanics with custom board size
GameMechs::GameMechs(int boardX, int boardY) {
    input = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// Destructor: Cleans up resources (if needed in future extensions)
GameMechs::~GameMechs() {}

// Returns the status of the exit flag
bool GameMechs::getExitFlagStatus() const {
    return exitFlag;
}

// Returns the status of the lose flag
bool GameMechs::getLoseFlagStatus() const {
    return loseFlag;
}

// Returns the most recent input character
char GameMechs::getInput() const {
    return input;
}

// Returns the current game score
int GameMechs::getScore() const {
    return score;
}

// Increments the game score by one
void GameMechs::incrementScore() {
    score++;
}

// Returns the board width
int GameMechs::getBoardSizeX() const {
    return boardSizeX;
}

// Returns the board height
int GameMechs::getBoardSizeY() const {
    return boardSizeY;
}

// Sets the exit flag to true
void GameMechs::setExitTrue() {
    exitFlag = true;
}

// Sets the lose flag to true
void GameMechs::setLoseFlag() {
    loseFlag = true;
}

// Sets the input character
void GameMechs::setInput(char this_input) {
    input = this_input;
}

// Clears the input character
void GameMechs::clearInput() {
    input = 0;
}

// Copy Constructor: Performs a deep copy of the other GameMechs object
GameMechs::GameMechs(const GameMechs& other) {
    input = other.input;
    exitFlag = other.exitFlag;
    loseFlag = other.loseFlag;
    score = other.score;
    boardSizeX = other.boardSizeX;
    boardSizeY = other.boardSizeY;
}

// Copy Assignment Operator: Copies data from the other GameMechs object
GameMechs& GameMechs::operator=(const GameMechs& other) {
    if (this != &other) { // Check for self-assignment
        input = other.input;
        exitFlag = other.exitFlag;
        loseFlag = other.loseFlag;
        score = other.score;
        boardSizeX = other.boardSizeX;
        boardSizeY = other.boardSizeY;
    }
    return *this;
}
