#include <random>
#include <list>
#include <bitset>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

#include <sqlite3.h>

#include "deck.h"


int main(){
    srand(time(NULL));
    // sqlite3 *db;
    // char *zErrMsg=0;
    int pArr[52][52];
    for(int i=0; i<52; i++){
        for(int j=0; j<52; j++){
            pArr[i][j]=0;
        }
    }
    deck cards;
    cards.build();
    int counter;
    // std::vector<bool> tempVec = cards.exportBits();
    for (int i=0; i<1000; i++){
        cards.reshuffle();  // 2.2 seconds
        counter=0;
        for(int num: cards.cards){
            pArr[counter][num]+=1;
            counter++;
        }
        // cards.printDeck();
        // int counter = 0;
        // std::cout << std::endl;
    }
    std::cout << std::endl;
}


