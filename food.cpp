#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"


#include <cstdlib>
#include <ctime>

food::food() {
    std::srand(std::time(0)); // Seed RNG
}

food::~food() {
    
}

void food::generateFood(objPosArrayList* blockOff) {
    objPos elementLoc;
    bool regenerate;

    do {
        regenerate = false;
        foodPos.pos->x = 1 + std::rand() % 28; 
        foodPos.pos->y = 1 + std::rand() % 13; 
        
        for(int i = 0; i < blockOff->getSize(); i++){
            elementLoc = blockOff->getElement(i);
            if(foodPos.isPosEqual(&elementLoc)){
            regenerate = true;
            }
        }
    } while (regenerate); 

    foodPos.symbol = 'o'; 
}

objPos food::getFoodPos() const {
    return foodPos;
}
