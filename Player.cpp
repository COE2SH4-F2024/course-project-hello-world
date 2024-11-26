#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = FROZEN;
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, 
                        mainGameMechsRef->getBoardSizeY() / 2, 
                        '*'); // Using '@' as player symbol

    // more actions to be included

}


Player::~Player()
{
    // delete any heap members here
    delete[] mainGameMechsRef;
    mainGameMechsRef = nullptr;
    
}

objPos Player::getPlayerPos() const
{
   return playerPos;  // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic      

  char input = mainGameMechsRef->getInput(); // Get the most recent input

    if (input == 'w' && (myDir == RIGHT || myDir == LEFT || myDir == FROZEN) && playerPos.pos->x != 0 && playerPos.pos->x != 19) {
        myDir = UP;
        playerPos.pos->y--;
    } else if (input == 's' && (myDir == RIGHT || myDir == LEFT || myDir == FROZEN) && playerPos.pos->x != 0 && playerPos.pos->x != 19) {
        myDir = DOWN;
        playerPos.pos->y++;
    } else if (input == 'd' && (myDir == UP || myDir == DOWN || myDir == FROZEN) && playerPos.pos->y != 0 && playerPos.pos->y != 9) {
        myDir = RIGHT;
        playerPos.pos->x++;
    } else if (input == 'a' && (myDir == UP || myDir == DOWN || myDir == FROZEN) && playerPos.pos->y != 0 && playerPos.pos->y != 9) {
        myDir = LEFT;
        playerPos.pos->x--;
    } else if (input == 27) { // ESC key
        mainGameMechsRef->setExitTrue();
    }
}

void Player::movePlayer()
{
// PPA3 Finite State Machine logic
    if (myDir == UP) {
        if (playerPos.pos->y == 0) {
            playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 1; // Wrap around
        } else {
            playerPos.pos->y--;
        }
    } else if (myDir == DOWN) {
        if (playerPos.pos->y >= mainGameMechsRef->getBoardSizeY() - 1) {
            playerPos.pos->y = 0; // Wrap around
        } else {
            playerPos.pos->y++;
        }
    } else if (myDir == LEFT) {
        if (playerPos.pos->x == 0) {
            playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 1; // Wrap around
        } else {
            playerPos.pos->x--;
        }
    } else if (myDir == RIGHT) {
        if (playerPos.pos->x >= mainGameMechsRef->getBoardSizeX() - 2) { // this made it loop around better
            playerPos.pos->x = 0; // Wrap around
        } else {
            playerPos.pos->x++;
        }
    }
}

Player::Dir Player::getDirection() const {
    return myDir; // Return the current direction
}