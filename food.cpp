#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "food.h"


#include <cstdlib>
#include <ctime>

food::food() {
    std::srand(std::time(0)); // Seed RNG
}

food::~food() {
}

void food::generateFood(objPos blockOff) {
    do {
        foodPos.pos->x = 1 + std::rand() % 28; 
        foodPos.pos->y = 1 + std::rand() % 8; 
    } while (foodPos.isPosEqual(&blockOff)); 

    foodPos.symbol = 'o'; 
}

objPos food::getFoodPos() const {
    return foodPos;
}
