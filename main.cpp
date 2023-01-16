#include <random>
#include <list>
#include <bitset>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

#include "deck.h"


int main(){
    srand(time(NULL));
    deck cards;
    cards.build();
    //std::vector<bool> tempVec = cards.exportBits();
    for (int i=0; i<1000000; i++){
        cards.reshuffle();  // 2.2 seconds
        
        //cards.printDeck();
    }
    std::cout << std::endl;
}
