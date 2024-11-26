#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMechs = nullptr;
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
    
    cout << "Game initialized! Use W/A/S/D to move, ESC to exit." << endl;
    gameMechs = new GameMechs();
    player = new Player(gameMechs);

    exitFlag = false;
}

void GetInput(void)
{
   if (MacUILib_hasChar()) { // Check if input is available
        char input = MacUILib_getChar(); // Get the input
        gameMechs->setInput(input); // Set input in GameMechs
    }
}

void RunLogic(void)
{
    player->updatePlayerDir(); // Update FSM state based on input
    player->movePlayer();      // Move player based on the direction
    gameMechs->clearInput();   // Clear input to prevent double processing
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // Retrieve and display the player's position
    objPos pos = player->getPlayerPos();
    for(int i = 0; i < gameMechs->getBoardSizeY(); i++){
        for(int j = 0; j < gameMechs->getBoardSizeX(); j++){
            if(j == gameMechs->getBoardSizeX()-1){
                MacUILib_printf("#\n");
            }
            else if(i == 0 || i == gameMechs->getBoardSizeY()-1 || j == 0){
                MacUILib_printf("#");
            }
            else if(i == 7 && j == 18){
                MacUILib_printf("M");
            }
            else if(i == 2 && j == 26){
                MacUILib_printf("8");
            }
            else{
                MacUILib_printf(" ");
            }
        }
    }

    MacUILib_printf("Player Position: (%d, %d)\n",player->getPlayerPos().getObjPos().pos->x,  player->getPlayerPos().getObjPos().pos->y);
    //cout << "Player Position: (" << pos.pos->x << ", " << pos.pos->y << ")" << endl;

    // Display FSM state
    cout << "Player Direction: ";
    switch (player->getDirection()) {
        case Player::UP: MacUILib_printf("UP\n"); break; //cout << "UP"; break;
        case Player::DOWN: MacUILib_printf("DOWN\n"); break; //cout << "DOWN"; break;
        case Player::LEFT: MacUILib_printf("LEFT\n"); break; //cout << "LEFT"; break;
        case Player::RIGHT: MacUILib_printf("RIGHT\n"); break; //cout << "RIGHT"; break;
        case Player::FROZEN: MacUILib_printf("FROZEN\n"); break; //cout << "FROZEN"; break;
    }
    //cout << endl;
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete player;
    //player->~Player();
    

    MacUILib_uninit();
}
