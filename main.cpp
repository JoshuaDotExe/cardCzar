#include <random>
#include <list>
#include <bitset>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <fstream>

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

    // deletes test.db file if exists for convenience
    std::ifstream fileTest;
    fileTest.open("test.db");
    if(fileTest){
        remove("test.db");
    }

    SQLiteDB db;
    
    deck cards;
    cards.build();
    int counter;
    int sqlInt1 = sqlite3_open("test.db", &db.db);

    int iter1 = 10000;
    for (int i=0; i<iter1; i++){
        cards.reshuffle();  // 2.2 seconds @ 1 mil iters
        if(db.insert(cards.exportUTF8())){return 0;}
        counter=0;
        for(int num: cards.cards){
            pArr[counter][num]+=1;
            counter++;

        }
    }
    sqlite3_close(db.db);
}


