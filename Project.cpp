#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"

using namespace std;

// Constants
#define DELAY_CONST 100000

// Global pointers for game objects
GameMechs* gameMechs = nullptr;
food* gameFood = nullptr;
Player* player = nullptr;

bool exitFlag; // Exit flag for the game loop

// Function prototypes
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void) {
    Initialize();

    // Main game loop
    while (gameMechs->getExitFlagStatus() == false) {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

// Initialize game components
void Initialize(void) {
    MacUILib_init(); // Initialize MacUILib
    MacUILib_clearScreen();

    // Allocate memory for game objects
    gameMechs = new GameMechs();
    gameFood = new food();
    player = new Player(gameMechs, gameFood);

    // Generate initial food position
    objPosArrayList* playerPos = player->getPlayerPos();
    gameFood->generateFood(playerPos);

    exitFlag = false;
}

// Capture player input and pass it to GameMechs
void GetInput(void) {
    if (MacUILib_hasChar()) {
        char input = MacUILib_getChar();
        gameMechs->setInput(input);
    }
}

// Main game logic: check collisions, update state, and move player
void RunLogic(void) {
    objPosArrayList* playerPos = player->getPlayerPos();
    objPos foodPosition = gameFood->getFoodPos();

    // Check if the player consumes food
    if (player->checkFoodConsumption()) {
        player->increasePlayerLength();
        gameFood->generateFood(playerPos); // Generate new food
    }

    // Update player's direction and position
    player->updatePlayerDir();
    player->movePlayer();

    // Clear input buffer
    gameMechs->clearInput();
}

// Render the game board and UI
void DrawScreen(void) {
    MacUILib_clearScreen();
    bool printChar;

    objPosArrayList* playerPos = player->getPlayerPos();

    // Draw the game board
    for (int i = 0; i < gameMechs->getBoardSizeY(); i++) {
        for (int j = 0; j < gameMechs->getBoardSizeX(); j++) {
            printChar = true;

            // Draw borders
            if (j == gameMechs->getBoardSizeX() - 1 && printChar) {
                MacUILib_printf("#\n");
                printChar = false;
            } else if ((i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0) && printChar) {
                MacUILib_printf("#");
                printChar = false;
            }

            // Draw player
            for (int k = 0; k < playerPos->getSize() && printChar; k++) {
                if (playerPos->getElement(k).pos->y == i && playerPos->getElement(k).pos->x == j) {
                    MacUILib_printf("%c", playerPos->getHeadElement().symbol);
                    printChar = false;
                }
            }

            // Draw food
            if (gameFood->getFoodPos().pos->y == i && gameFood->getFoodPos().pos->x == j && printChar) {
                MacUILib_printf("%c", gameFood->getFoodPos().getSymbol());
                printChar = false;
            } else if (printChar) {
                MacUILib_printf(" ");
            }
        }
    }

    // Display score
    MacUILib_printf("Score:\t%d\n", gameMechs->getScore());

    // Display game end messages
    if (gameMechs->getExitFlagStatus()) {
        if (gameMechs->getLoseFlagStatus()) {
            MacUILib_printf("Game Over: You Lost!");
        } else {
            MacUILib_printf("You have exited the game");
        }
    }
}

// Add a delay to control game speed
void LoopDelay(void) {
    MacUILib_Delay(DELAY_CONST);
}

// Clean up allocated memory and resources
void CleanUp(void) {
    delete player;
    delete gameFood;
    delete gameMechs;

    MacUILib_uninit(); // Uninitialize MacUILib
}
