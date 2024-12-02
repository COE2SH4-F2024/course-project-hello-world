#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"

#include <cstdlib>
#include <ctime>

// Constructor: Seeds the random number generator
food::food() {
    std::srand(std::time(0)); // Seed RNG with the current time
}

// Destructor: Currently no resources to free
food::~food() {}

// Generates a new food position, avoiding collision with existing blocks
void food::generateFood(objPosArrayList* blockOff) {
    objPos elementLoc;
    bool regenerate;

    do {
        regenerate = false;

        // Generate random x and y positions within the game board boundaries
        foodPos.pos->x = 1 + std::rand() % 28; // X-coordinate (1 to 28)
        foodPos.pos->y = 1 + std::rand() % 13; // Y-coordinate (1 to 13)

        // Check for collisions with blocked positions
        for (int i = 0; i < blockOff->getSize(); i++) {
            elementLoc = blockOff->getElement(i);
            if (foodPos.isPosEqual(&elementLoc)) {
                regenerate = true; // Regenerate food position if collision detected
            }
        }
    } while (regenerate); // Repeat until a valid position is found

    // Set the food symbol
    foodPos.symbol = 'o';
}

// Returns the current food position
objPos food::getFoodPos() const {
    return foodPos;
}
