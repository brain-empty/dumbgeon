#if !defined(PLAYER_H)
#define PLAYER_H
#include<iostream>

bool canLevelUp (int pLvl, int pExp) {
    int reqExp[12];
    int i;
    reqExp[2] = 25;
    for (i = 3 ; i<=10 ; i++) reqExp[i] = reqExp[i-1] * 4;
    
    if (pExp > reqExp[pLvl+1]) 
    {
        return true;
    } 
    else
    {
        std::cout << "\nExp requierd for next level : " << reqExp[pLvl+1] << std::endl;
        return false;
    }
} 

void levelUp(int* pMaxHealth, int* pHealth, int* pAtk, int* pLvl, int* pExp) 
{
    int temp;
    if (canLevelUp( *pLvl, *pExp))
    {
        *pLvl = *pLvl + 1;
        *pMaxHealth = *pMaxHealth + *pLvl * 10;
        *pHealth = *pMaxHealth;
        *pAtk = *pAtk + *pLvl;
        std::cout << "Levelled up to" << *pLvl;
        std::cout << "\n1. Brilliant!\n";
    }
    else
    {
        int temp;
        std::cout << "You can't level up";
        std::cout << "\n1. i'll try harder!\n";
    }
    std::cin >> temp;
}

#endif