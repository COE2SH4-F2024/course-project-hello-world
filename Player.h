#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.
    
    public:
       /* i implmented this, from ppa3*/ 
        enum Dir { FROZEN, LEFT, RIGHT, UP, DOWN };
        
        Player(GameMechs* thisGMRef, food* thisFood);
        ~Player();

        objPosArrayList* getPlayerPos() const; // Upgrade this in iteration 3.       
        void updatePlayerDir();
        void movePlayer();

        Dir getDirection() const; //i added this

        // More methods to be added here
        bool checkFoodConsumption();
        void increasePlayerLength();
        bool checkSelfCollision();

    private:
    
        objPosArrayList* playerPosList; // Upgrade this in iteration 3.       
        
        /* i implmented this, from ppa3*/ 
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

        food* foodObj;
};

#endif