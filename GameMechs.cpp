#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include <time.h>

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    // default board size
    boardSizeX = 30; // columns
    boardSizeY = 10; // rows
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    boardSizeX = boardX; 
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{

}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{   
    return loseFlag;
}
    

char GameMechs::getInput() const {
    return input;
}

int GameMechs::getScore() const
{
    return score;  
}

void GameMechs::incrementScore()
{
        score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
        input = this_input;

}

void GameMechs::clearInput()
{
        input = 0;
}

// More methods should be added here

//Copy Constructor
GameMechs::GameMechs(const GameMechs& other) {
    input = other.input;
    exitFlag = other.exitFlag;
    loseFlag = other.loseFlag;
    score = other.score;
    boardSizeX = other.boardSizeX;
    boardSizeY = other.boardSizeY;
}

//Copy Assignment Operator
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