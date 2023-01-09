#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

class cardsDeck{
public:
    int topCard;
    std::string deck[52];
    std::unordered_map<std::string, int> cardValues;

    void initValues();
    void buildDeck();
    void shuffleDeck();
    std::string withdraw();
private:
    std::string cardHouse[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int cardHouseVals[13] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
};

void cardsDeck::initValues(void){
    // Places cards and associated values into unordered map
    for (int i=0; i<13; i++){
        cardValues[cardHouse[i]] = cardHouseVals[i];
    }
}

void cardsDeck::buildDeck(void){
    int deckCount = 0;
    for (int i=0; i<4; i++) {
        for (int j=0; j<13; j++)    {
            deck[deckCount] = cardHouse[j];
            deckCount++;
        }
    }
}

void cardsDeck::shuffleDeck(void){
    for(int i=0; i<52; i++){
        int r = i + (rand() % (52-i));
        swap(deck[i], deck[r]);
    }
}

std::string cardsDeck::withdraw(void){
    topCard++;
    return deck[topCard-1];
}