#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class food
{
    private:
        objPos foodPos;

    public:

        food();
        ~food();
        
        void generateFood(objPosArrayList* blockOff);
        objPos getFoodPos() const;

     

};


#endif 
