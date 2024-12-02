#include "Player.h"

// Constructor: Initializes player position, direction, and links to GameMechs and Food objects
Player::Player(GameMechs* thisGMRef, food* thisFood) {
    mainGameMechsRef = thisGMRef;
    foodObj = thisFood;
    myDir = FROZEN;

    // Create player position list and initialize with a starting position
    playerPosList = new objPosArrayList();
    objPos headPos = objPos(mainGameMechsRef->getBoardSizeX() / 2,
                            mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(headPos);
}

// Destructor: Frees dynamically allocated memory
Player::~Player() {
    delete playerPosList;
}

// Returns the current positions of all segments of the player (snake)
objPosArrayList* Player::getPlayerPos() const {
    return playerPosList;
}

// Updates player's direction based on user input
void Player::updatePlayerDir() {
    char input = mainGameMechsRef->getInput(); // Get the most recent input

    // FSM-style direction update
    if (input == 'w' && (myDir == RIGHT || myDir == LEFT || myDir == FROZEN)) {
        myDir = UP;
    } else if (input == 's' && (myDir == RIGHT || myDir == LEFT || myDir == FROZEN)) {
        myDir = DOWN;
    } else if (input == 'd' && (myDir == UP || myDir == DOWN || myDir == FROZEN)) {
        myDir = RIGHT;
    } else if (input == 'a' && (myDir == UP || myDir == DOWN || myDir == FROZEN)) {
        myDir = LEFT;
    } else if (input == 27) { // ESC key
        mainGameMechsRef->setExitTrue();
    }
}

// Moves the player (snake) in the current direction, handles collisions, and updates segments
void Player::movePlayer() {
    objPos temp = playerPosList->getHeadElement(); // Temporary object for the new head position

    // Check for self-collision
    if (checkSelfCollision()) {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
        return;
    }

    // Update position based on direction and handle wrapping
    if (myDir == UP) {
        temp.pos->y = (temp.pos->y <= 1) ? mainGameMechsRef->getBoardSizeY() - 2 : temp.pos->y - 1;
    } else if (myDir == DOWN) {
        temp.pos->y = (temp.pos->y >= mainGameMechsRef->getBoardSizeY() - 2) ? 1 : temp.pos->y + 1;
    } else if (myDir == LEFT) {
        temp.pos->x = (temp.pos->x <= 1) ? mainGameMechsRef->getBoardSizeX() - 2 : temp.pos->x - 1;
    } else if (myDir == RIGHT) {
        temp.pos->x = (temp.pos->x >= mainGameMechsRef->getBoardSizeX() - 2) ? 1 : temp.pos->x + 1;
    }

    // Insert the new head position
    playerPosList->insertHead(temp);

    // Remove tail segment unless food is consumed
    objPos foodLoc = foodObj->getFoodPos();
    if (!temp.isPosEqual(&foodLoc)) {
        playerPosList->removeTail();
    }
}

// Returns the current direction of the player
Player::Dir Player::getDirection() const {
    return myDir;
}

// Checks if the player has consumed food
bool Player::checkFoodConsumption() {
    return foodObj->getFoodPos().pos->x == playerPosList->getHeadElement().pos->x &&
           foodObj->getFoodPos().pos->y == playerPosList->getHeadElement().pos->y;
}

// Increases the player's length by incrementing the score
void Player::increasePlayerLength() {
    mainGameMechsRef->incrementScore();
}

// Checks if the player collides with itself
bool Player::checkSelfCollision() {
    bool collision = false;
    for (int i = 1; i < playerPosList->getSize(); i++) {
        objPos elementLoc = playerPosList->getElement(i).getObjPos();
        if (playerPosList->getHeadElement().isPosEqual(&elementLoc)) {
            collision = true;
            break;
        }
    }
    return collision;
}
