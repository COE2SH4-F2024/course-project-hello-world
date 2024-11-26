#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = FROZEN;
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, 
                        mainGameMechsRef->getBoardSizeY() / 2, 
                        '@'); // Using '@' as player symbol

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

    if (input == 'w' && myDir != UP && (myDir == FROZEN || myDir == LEFT || myDir == RIGHT)) {
        myDir = UP;
    } if (input == 's' && myDir != DOWN && (myDir == FROZEN || myDir == LEFT || myDir == RIGHT)) {
        myDir = DOWN;
    } if (input == 'a' && myDir != LEFT && (myDir == FROZEN || myDir == UP || myDir == DOWN)) {
        myDir = LEFT;
    } if (input == 'd' && myDir != RIGHT && (myDir == FROZEN || myDir == UP || myDir == DOWN)) {
        myDir = RIGHT;
    } if (input == 27) { // ESC key
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
        if (playerPos.pos->y == mainGameMechsRef->getBoardSizeY() - 1) {
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
        if (playerPos.pos->x == mainGameMechsRef->getBoardSizeX() - 1) {
            playerPos.pos->x = 0; // Wrap around
        } else {
            playerPos.pos->x++;
        }
    }
}

Player::Dir Player::getDirection() const {
    return myDir; // Return the current direction
}