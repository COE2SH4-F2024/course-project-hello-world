#include "objPos.h"

// Default Constructor: Initializes position to (0, 0) and sets the symbol to NULL
objPos::objPos() {
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; // NULL
}

// Parameterized Constructor: Initializes position and symbol with given values
objPos::objPos(int xPos, int yPos, char sym) {
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Destructor: Frees dynamically allocated memory for position
objPos::~objPos() {
    delete pos;
    pos = nullptr;
}

// Copy Constructor: Creates a deep copy of the original objPos
objPos::objPos(const objPos& orgnl) {
    pos = new Pos;
    pos->x = orgnl.pos->x;
    pos->y = orgnl.pos->y;
    symbol = orgnl.symbol;
}

// Copy Assignment Operator: Assigns values from one objPos to another with deep copying
objPos& objPos::operator=(const objPos& orgnl) {
    if (this == &orgnl) { // Handle self-assignment
        return *this;
    }

    this->pos->x = orgnl.pos->x;
    this->pos->y = orgnl.pos->y;
    this->symbol = orgnl.symbol;

    return *this;
}

// Sets the position and symbol using another objPos
void objPos::setObjPos(objPos o) {
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

// Sets the position and symbol using individual values
void objPos::setObjPos(int xPos, int yPos, char sym) {
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Returns a copy of the current objPos
objPos objPos::getObjPos() const {
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;

    return returnPos;
}

// Returns the symbol of the current objPos
char objPos::getSymbol() const {
    return symbol;
}

// Checks if the position matches with the reference objPos
bool objPos::isPosEqual(const objPos* refPos) const {
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

// Returns the symbol if the position matches the reference objPos
char objPos::getSymbolIfPosEqual(const objPos* refPos) const {
    if (isPosEqual(refPos)) {
        return symbol;
    } else {
        return 0;
    }
}
