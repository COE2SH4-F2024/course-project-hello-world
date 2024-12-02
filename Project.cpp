#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMechs = nullptr;
food* gameFood = nullptr; 
Player* player = nullptr;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(gameMechs->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    gameMechs = new GameMechs();
    gameFood =  new food();
    player =  new Player(gameMechs, gameFood);


    objPosArrayList* playerPos = player->getPlayerPos();
    gameFood->generateFood(playerPos);


    exitFlag = false;
}

void GetInput(void)
{
   if (MacUILib_hasChar()) { 
        char input = MacUILib_getChar(); 
        gameMechs->setInput(input); 
    }
}

void RunLogic(void)
{
   objPosArrayList* playerPos = player->getPlayerPos();
    objPos foodPosition = gameFood->getFoodPos(); 
    if (player->checkFoodConsumption()) {
        player->increasePlayerLength();
        gameFood->generateFood(playerPos); 
    }   
    player->updatePlayerDir(); 
    player->movePlayer();    


    gameMechs->clearInput();  
}


void DrawScreen(void)
{
    MacUILib_clearScreen();
    bool printChar;
    objPosArrayList* playerPos = player->getPlayerPos();
    //MacUILib_printf("(%d, %d)\n", playerPos->getHeadElement().pos->x, playerPos->getHeadElement().pos->y);
    for (int i = 0; i < gameMechs->getBoardSizeY(); i++) {
        for (int j = 0; j < gameMechs->getBoardSizeX(); j++) {
            printChar = true;
            if (j == gameMechs->getBoardSizeX() - 1 && printChar) {
                MacUILib_printf("#\n");
                printChar = false;
            } 
            else if ((i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0) && printChar) {
                MacUILib_printf("#");
                printChar = false;
            } 
            
            
            for(int k = 0; k < playerPos->getSize() && printChar; k++){
                if(playerPos->getElement(k).pos->y == i && playerPos->getElement(k).pos->x == j){
                    MacUILib_printf("%c", playerPos->getHeadElement().symbol);
                    printChar = false;
                }
            }
                if(gameFood->getFoodPos().pos->y == i && gameFood->getFoodPos().pos->x == j && printChar){
                    MacUILib_printf("%c", gameFood->getFoodPos().getSymbol()); 
                    printChar = false;
                }
                else if(printChar){
                    MacUILib_printf(" ");
                }
            
            
            


        }
    }

    MacUILib_printf("Score:\t%d\n", gameMechs->getScore());

    if(gameMechs->getExitFlagStatus() == true){
        if(gameMechs->getLoseFlagStatus() == true){
            MacUILib_printf("Game Over: You Lost!");
        }
        else{
            MacUILib_printf("You have exited the game");
        }

    }

    //MacUILib_printf("Player Position: (%d, %d)\n",player->getPlayerPos().getObjPos().pos->x,  player->getPlayerPos().getObjPos().pos->y);


    // Display FSM state
    // MacUILib_printf("length: %d\n", playerPos->getSize());
    // MacUILib_printf("score: %d\n", gameMechs->getScore());
    // MacUILib_printf("Player Direction: ");
    // switch (player->getDirection()) {
    //     case Player::UP: MacUILib_printf("UP\n"); break; 
    //     case Player::DOWN: MacUILib_printf("DOWN\n"); break; 
    //     case Player::LEFT: MacUILib_printf("LEFT\n"); break; 
    //     case Player::RIGHT: MacUILib_printf("RIGHT\n"); break; 
    //     case Player::FROZEN: MacUILib_printf("FROZEN\n"); break; 
    // }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); 
}


void CleanUp(void)
{
   
    delete player;
    delete gameFood; 
    delete gameMechs;
    

    MacUILib_uninit();
}
