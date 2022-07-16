#include<iostream>
#include"ascii.h"

class Enemy 
{
    public:
    int health, drop, atk, maxHealth, exp;
    
    Enemy () {

    }

    Enemy (int enemyNum, int dungeonLevel) {
        int modifier = enemyNum*dungeonLevel + dungeonLevel;

        int base = rand() % 10;
        base = base * dungeonLevel * 4;

        health = base + modifier;
        maxHealth = health;
        drop = (int)(base + modifier) / 10;
        if (drop < 2) drop = 2; 
        exp = (base + modifier + dungeonLevel * 10);
        if (dungeonLevel > 2) exp = exp *4;
            

        base = base / ( dungeonLevel * 4 ) ;
        if (base < 5) base = 5;;
        atk = (int) ((enemyNum + dungeonLevel*10) / base);
        if (atk == 0) atk = 1;
    }
    
    int* getHealth () 
	{
        return &health;
    }

    int getMaxHealth() {
        return maxHealth;
    }
    
    int getDrop () 
	{
        return drop;
    }
    
    int getAtk () 
	{
        int effAtk;
        effAtk = abs((rand() % 10 - 5)) + atk;
        return atk;
    }

    int getExp () 
    {
        return exp;
    }
    
    int attack(int* enemyHealth, int pAtk) 
	{
        *enemyHealth = *enemyHealth - pAtk;
        return *enemyHealth;
    }
};

void attackPlayer (Enemy enemy, int* pHealth) 
{
	*pHealth = *pHealth - enemy.getAtk();
}

int fight (int* pHealth, int pAtk, bool* enemyDefeated, Enemy* enemy1, bool* runAway)
{
    int pChoice;

    std::cout << "\nEnemy health:\n";
    showHealth(*enemy1->getHealth(), enemy1->getMaxHealth());
    std::cout << "\nWhat do you want to do?\n1. Attack\n";
    std::cin >> pChoice;
    
    switch (pChoice) {
        case 1:
            enemy1->attack(enemy1->getHealth(), pAtk);
            attackPlayer(*enemy1, pHealth);
            if (*pHealth <= 0) {
                return 2;
            }
            break;
            
        // case 2:
        //     *runAway = true;
        //     break;
            
        default:
            std::cout << "\nERROR: Incorrect input.";
            break;
    }
    return 1;
}

void dungeon (int* pHealth, int* pMaxHealth, int* pAtk, int* pCoins, int* pLvl, int* pExp, int dungeonLevel, int* highestDungeonCleared) 
{   
    int i;
    bool runAway = false;
    while (runAway == false){
        for (i=1;i<9;i++)
            while(runAway == false){ 
            {
                int enemyNum = i;
                Enemy enemy1(enemyNum, dungeonLevel);
                bool enemyDefeated = false;
                while (enemyDefeated == false)
                {
                    
                    if (*enemy1.getHealth() > 0)
                    {
                        clrscr();
                        std::cout << "DUNGEON LEVEL: " << dungeonLevel<< " / ENEMY NUMBER: " << enemyNum << std::endl ;
                        printDashboard(*pHealth, *pMaxHealth, *pCoins, *pExp, *pLvl);
                        if (fight(pHealth, *pAtk, &enemyDefeated, &enemy1, &runAway) == 2)
                        {
                            printDead();
                            return;
                        } 
                    } 
                    else 
                    {
                        printWin();
                        std::cout << "\nYou find " << enemy1.getDrop() << " slimy coins on the monsters body, yuck\n"; 
                        std::cout << "\nYou've learnt a bit from fighting that monster, you recieve " << enemy1.getExp() << " experience";
                        *pCoins = *pCoins + enemy1.getDrop();
                        *pExp = *pExp + enemy1.getExp();
                        std::cout<< "---\nEnter anything (on the keyboard) to continue";
                        int temp;
                        std::cin >> temp;
                        break;
                    }
                }
            }
        }

        if (runAway ==false){
            int enemyNum = 30;
            Enemy enemy1(enemyNum, dungeonLevel);
            bool enemyDefeated = false;
            while (enemyDefeated == false)
            {
                clrscr();
                std::cout<< "BOSS FIGHT" << std::endl ;
                printDashboard(*pHealth, *pMaxHealth, *pCoins, *pExp, *pLvl);
                if (*enemy1.getHealth() > 0) {
                    if (fight(pHealth, *pAtk, &enemyDefeated, &enemy1, &runAway) == 2)
                    {
                        printDead();
                        return;
                    }
                } 
                else 
                {
                    printDungeonCleared();
                    if (*highestDungeonCleared == dungeonLevel-1) {
                        *highestDungeonCleared = *highestDungeonCleared+1;
                        std::cout << "new dungeon unlocked";
                    } else if (dungeonLevel-1 > *highestDungeonCleared) {
                        std::cout  << "YOU CHEATED ME??? CRYING";
                    }
                    *pCoins = *pCoins + enemy1.getDrop();
                    break;
                }
            }
            }
        }
    

}
