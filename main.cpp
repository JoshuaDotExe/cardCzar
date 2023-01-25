#include <random>
#include <list>
#include <bitset>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

#include <sqlite3.h>

#include "sqldb.h"
#include "deck.h"


int main(){
    srand(time(NULL));

    int pArr[52][52];
    for(int i=0; i<52; i++){
        for(int j=0; j<52; j++){
            pArr[i][j]=0;
        }
    }

    SQLiteDB db;
    
    deck cards;
    cards.build();
    int counter;
    
    // std::vector<bool> tempVec = cards.exportBits();
    for (int i=0; i<10000; i++){
        cards.reshuffle();  // 2.2 seconds @ 1 mil iters
        db.insert(cards.exportStr());
        counter=0;
        for(int num: cards.cards){
            pArr[counter][num]+=1;
            counter++;

        }
    }
    std::cout << std::endl;
}


