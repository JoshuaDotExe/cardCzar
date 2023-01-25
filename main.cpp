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
    int sqlInt1 = sqlite3_open("test.db", &db.db);

    // std::vector<bool> tempVec = cards.exportBits();
    for (int i=0; i<1; i++){
        cards.reshuffle();  // 2.2 seconds @ 1 mil iters
        if(db.insert(cards.exportStr())){return 0;}
        counter=0;
        std::cout << cards.exportBitStr();
        for(int num: cards.cards){
            pArr[counter][num]+=1;
            counter++;

        }
    }
    sqlite3_close(db.db);
}


