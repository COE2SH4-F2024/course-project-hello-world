#include "objPosArrayList.h"

// Constructor: Initializes the list with a maximum capacity and allocates memory for the array
objPosArrayList::objPosArrayList() {
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
}

// Destructor: Frees the dynamically allocated memory for the array
objPosArrayList::~objPosArrayList() {
    delete[] aList;
}

// Returns the current size of the list
int objPosArrayList::getSize() const {
    return listSize;
}

// Inserts a new object at the head (start) of the list
void objPosArrayList::insertHead(objPos thisPos) {
    // Shift all elements one position to the right
    for (int i = listSize; i > 0; i--) {
        aList[i].setObjPos(aList[i - 1]);
    }

    // Insert the new object at the head
    aList[0].setObjPos(thisPos);
    listSize++;
}

// Inserts a new object at the tail (end) of the list
void objPosArrayList::insertTail(objPos thisPos) {
    aList[listSize] = thisPos;
    listSize++;
}

// Removes the object at the head (start) of the list
void objPosArrayList::removeHead() {
    // Shift all elements one position to the left
    for (int i = 0; i < listSize - 1; i++) {
        aList[i].setObjPos(aList[i + 1]);
    }
    listSize--;
}

// Removes the object at the tail (end) of the list
void objPosArrayList::removeTail() {
    listSize--;
}

// Returns the object at the head of the list
objPos objPosArrayList::getHeadElement() const {
    return aList[0];
}

// Returns the object at the tail of the list
objPos objPosArrayList::getTailElement() const {
    return aList[listSize - 1];
}

// Returns the object at a specific index in the list
objPos objPosArrayList::getElement(int index) const {
    return aList[index];
}
