#include <random>
#include <list>
#include <bitset>
#include <iostream>
#include <string>
#include <iterator>

#include "deck.h"


int main(){
    srand(time(NULL));
    deck cards;
    cards.build();
    for (int i=0; i<2000000; i++){
        //cards.build();
        cards.reshuffle();
        
        //cards.printDeck();
    }
    
    //for(std::list<int>::iterator itr = cards.cards.begin(); itr != cards.cards.end(); itr++){
    //    std::cout << *itr;
    //}
    std::cout << std::endl;
}
