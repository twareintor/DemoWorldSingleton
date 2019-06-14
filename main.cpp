/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

#include "CWorld.h"

int main()
{
    CWorld* world = CWorld::getInstance(nullptr);
    CWorld* world2 = CWorld::getInstance(nullptr);
    CWorld* world3 = world;
    std::cout<<(void*)world<<std::endl;

    CAsset* p1 = world->spawn(ID_GENERIC);
    CAsset* p2 = world->clone(p1); 
    
    CAsset* plant01 = world->spawn(ID_PLANT);
    CAsset* animal01 = world->spawn(ID_ANIMAL_HERBIVORE);
    
    world->release(p1);
    world->release(plant01);
    world->release(animal01);
    world->release(p2);
    world3->release();
    world2->release();
    world->release();

    return 0;
}


