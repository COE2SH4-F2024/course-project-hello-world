#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "food.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMechs = nullptr;
Player* player = nullptr;
food* gameFood = nullptr; 


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
    player = new Player(gameMechs);
    gameFood = new food();

    objPos playerPos = player->getPlayerPos();
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
    player->updatePlayerDir(); 
    player->movePlayer();    

    objPos foodPosition = gameFood->getFoodPos(); 
    if (player->getPlayerPos().isPosEqual(&foodPosition)) {
        gameMechs->incrementScore(); // i added increment food here
        objPos playerPos = player->getPlayerPos(); 
        gameFood->generateFood(playerPos); 
    }

    gameMechs->clearInput();  
}


void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos pos = player->getPlayerPos();
    for (int i = 0; i < gameMechs->getBoardSizeY(); i++) {
        for (int j = 0; j < gameMechs->getBoardSizeX(); j++) {
            if (j == gameMechs->getBoardSizeX() - 1) {
                MacUILib_printf("#\n");
            } else if (i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0) {
                MacUILib_printf("#");
            } else if (player->getPlayerPos().pos->y == i && player->getPlayerPos().pos->x == j) {
                MacUILib_printf("%c", player->getPlayerPos().getSymbol());
            } else if (gameFood->getFoodPos().pos->y == i && gameFood->getFoodPos().pos->x == j) {
                MacUILib_printf("%c", gameFood->getFoodPos().getSymbol()); 
            } else {
                MacUILib_printf(" ");
            }
        }
    }

    MacUILib_printf("Player Position: (%d, %d)\n",player->getPlayerPos().getObjPos().pos->x,  player->getPlayerPos().getObjPos().pos->y);


    // Display FSM state
    cout << "Player Direction: ";
    switch (player->getDirection()) {
        case Player::UP: MacUILib_printf("UP\n"); break; 
        case Player::DOWN: MacUILib_printf("DOWN\n"); break; 
        case Player::LEFT: MacUILib_printf("LEFT\n"); break; 
        case Player::RIGHT: MacUILib_printf("RIGHT\n"); break; 
        case Player::FROZEN: MacUILib_printf("FROZEN\n"); break; 
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); 
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete player;
    delete gameFood; 
    delete gameMechs;
    

    MacUILib_uninit();
}
