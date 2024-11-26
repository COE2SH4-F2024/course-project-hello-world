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
    cout << "Player Position: (" << pos.pos->x << ", " << pos.pos->y << ")" << endl;

    // Display FSM state
    cout << "Player Direction: ";
    switch (player->getDirection()) {
        case Player::UP: cout << "UP"; break;
        case Player::DOWN: cout << "DOWN"; break;
        case Player::LEFT: cout << "LEFT"; break;
        case Player::RIGHT: cout << "RIGHT"; break;
        case Player::FROZEN: cout << "FROZEN"; break;
    }
    cout << endl;
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete player;

    MacUILib_uninit();
}
