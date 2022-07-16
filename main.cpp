#include<iostream>
#include"dungeonCombat.h"
#include"player.h"
#include"ascii.h"
#include <windows.h>

int main (){
    std::string pName;
    int pMaxHealth = 30, pAtk = 3, pCoins= 0, pLvl = 1, pExp = 0, pChoice, highestDungeonCleared = 0;
    int pHealth = pMaxHealth;
    bool gameRun=1;

    // system("color 0C");
    
    
    while(gameRun) 
    {
        clrscr();
        printTitle();                                                                                

        std::cout << "\n\nWelcome to Dumbgeon, the dumbest dungeon game ever made (citation required).";
        printDashboard(pHealth, pMaxHealth, pCoins, pExp, pLvl);
        std::cout << "\n-----------\nWhere do you want to go next?\n1. Dungeons\n2. Store\n3. Exit\n";
        
        std::cin >> pChoice;        
        
        switch (pChoice) {
            
            case 1: 
            {
                if (pHealth <= 0) {
                    std::cout << "Eh, I don't think you should be fighting in that state... go heal up.\n1.1. yeah, i'll go check the store out";
                    std::cin >>pChoice;
                    break;
                }
                int i, dungeonLevel;
                std::cout << "\nWhich dungeon do you want to go to?\n";
                for (i=0; i<highestDungeonCleared+1;i++){
                    std::cout << "dungeon number " << i+1<< std::endl;
                }
                std::cin >> dungeonLevel;

                if (dungeonLevel > 0 && dungeonLevel <= highestDungeonCleared+1) 
                {
                    std::cout << "You are in dungeon " << dungeonLevel;
                    dungeon(&pHealth, &pMaxHealth, &pAtk, &pCoins, &pLvl, &pExp, dungeonLevel, &highestDungeonCleared);
                } 
                else if (dungeonLevel > highestDungeonCleared) 
                {
                    std::cout << "This dungeon is too much for you.";
                } 
                else 
                {
                    std::cout << "why are you trying to break my code";
                }

                break;
            }
            
            case 2: 
            {
                std::cout << "you are in store\n1. Buy health potion (5 coins)\n2. Level up\n2. Leave\n";
                std::cin >> pChoice;
                
                switch (pChoice) {
                    case 1: 
                        if (pCoins > 5) {
                            std::cout << "Healed 100 health";
                            pHealth = pHealth + 100;
                            if (pHealth>pMaxHealth) pHealth = pMaxHealth;
                            pCoins = pCoins - 5;
                        } else {
                            std::cout << "You don't have enough cash, sorry kid. If you can't fight anymore... this may be the end for you.";
                        }
                        break;
                    case 2:
                        levelUp(&pMaxHealth, &pHealth, &pAtk, &pLvl, &pExp);
                        break;
                    case 3:
                        break;
                    default:
                        std::cout << "Sorry, we don't sell those.";
                        break;
                }
                break;
            }
            
            case 3:
                gameRun=0;
                break;
            
            default:
                std::cout << "that place? ah yeah you better not go there just yet buddy.";
                break;
        }
    }
    
    return 0;
}