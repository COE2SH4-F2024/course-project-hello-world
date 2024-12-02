#include "Player.h"


Player::Player(GameMechs* thisGMRef, food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    foodObj = thisFood;
    myDir = FROZEN;

    // more actions to be included
    playerPosList = new objPosArrayList();
    objPos headPos = objPos(mainGameMechsRef->getBoardSizeX()/2,
                            mainGameMechsRef->getBoardSizeY()/2, '*');

    playerPosList->insertHead(headPos);
}


Player::~Player()
{
    // delete any heap members here
    delete[] playerPosList;
    
}

objPosArrayList* Player::getPlayerPos() const
{
   return playerPosList;  // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic      

  char input = mainGameMechsRef->getInput(); // Get the most recent input

    if (input == 'w' && (myDir == RIGHT || myDir == LEFT || myDir == FROZEN)) {
        myDir = UP;
        //playerPos.pos->y--;
    } else if (input == 's' && (myDir == RIGHT || myDir == LEFT || myDir == FROZEN)) {
        myDir = DOWN;
        //playerPos.pos->y++;
    } else if (input == 'd' && (myDir == UP || myDir == DOWN || myDir == FROZEN) && playerPosList->getHeadElement().pos->y != 0 && playerPosList->getHeadElement().pos->y != 14) {
        myDir = RIGHT;
        //playerPos.pos->x++;
    } else if (input == 'a' && (myDir == UP || myDir == DOWN || myDir == FROZEN) && playerPosList->getHeadElement().pos->y != 0 && playerPosList->getHeadElement().pos->y != 14) {
        myDir = LEFT;
        //playerPos.pos->x--;
    } else if (input == 27) { // ESC key
        mainGameMechsRef->setExitTrue();
    }
}

void Player::movePlayer()
{
    objPos temp = objPos();
    //temp.pos->x = playerPosList->getHeadElement().pos->x;
    //temp.symbol = '*';
    temp = playerPosList->getHeadElement();

    if(checkSelfCollision()){
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
        return;
    }
// PPA3 Finite State Machine logic
    if (myDir == UP) {
        if (playerPosList->getHeadElement().pos->y <= 1) {
            temp.pos->y = mainGameMechsRef->getBoardSizeY() - 2;    //wrap around
            //playerPosList->getHeadElement().pos->y = mainGameMechsRef->getBoardSizeY() - 1; // Wrap around
        } else {
            temp.pos->y = playerPosList->getHeadElement().pos->y - 1;
            //playerPos.pos->y--;
        }
    } else if (myDir == DOWN) {
        if (playerPosList->getHeadElement().pos->y >= mainGameMechsRef->getBoardSizeY() - 2) {
            temp.pos->y = 1;
            //playerPos.pos->y = 0; // Wrap around
        } else {
            temp.pos->y = playerPosList->getHeadElement().pos->y + 1;
            //playerPos.pos->y++;
        }
    } else if (myDir == LEFT) {
        if (playerPosList->getHeadElement().pos->x <= 1) {
            temp.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
            //playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 1; // Wrap around
        } else {
            temp.pos->x = playerPosList->getHeadElement().pos->x - 1;
            //playerPos.pos->x--;
        }
    } else if (myDir == RIGHT) {
        if (playerPosList->getHeadElement().pos->x >= mainGameMechsRef->getBoardSizeX() - 2) { // this made it loop around better
            temp.pos->x = 1;
            //playerPos.pos->x = 0; // Wrap around
        } else {
            temp.pos->x = playerPosList->getHeadElement().pos->x + 1;
            //playerPos.pos->x++;
        }
    }

    objPos foodLoc = foodObj->getFoodPos();
    playerPosList->insertHead(temp); //Inserts the next position to the head of the snake
    if(temp.isPosEqual(&foodLoc) == false){
        playerPosList->removeTail();
    }
         //Removes one part from the tail of the snake
}

Player::Dir Player::getDirection() const 
{
    return myDir; // Return the current direction
}

bool Player::checkFoodConsumption()
{
    return foodObj->getFoodPos().pos->x == playerPosList->getHeadElement().pos->x 
        && foodObj->getFoodPos().pos->y == playerPosList->getHeadElement().pos->y;
}

void Player::increasePlayerLength()
{
    mainGameMechsRef->incrementScore();
}

bool Player::checkSelfCollision()
{
    bool collision = false;
    objPos elementLoc;
    for(int i = 1; i < playerPosList->getSize(); i++){
        elementLoc = playerPosList->getElement(i).getObjPos();
        if(playerPosList->getHeadElement().isPosEqual(&elementLoc)){
            collision = true;
        }
    }
    return collision;
}