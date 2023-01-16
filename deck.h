#include <bitset>
#include <list>
#include <unordered_map>
#include <vector>

class deck{
private:
    std::string fullSuit[14] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "X"};
    int cardIndex[14] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    std::bitset<4> valueBitEquivalents[14] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    std::bitset<2> suitBits[4] = {00,01,10,11};
    std::unordered_map<int, std::string> _indexToStrInit();
    std::unordered_map<int, std::bitset<4>> _indexToBitInit();
    std::unordered_map<int, int> _indexToValueInit();
public:
    bool ignoreSuits;
    bool removeJokers;
    int numOfPacks;
    int numOfCards;
    std::vector<int> cards;
    std::unordered_map<int, std::string> indexToStr = _indexToStrInit();
    std::unordered_map<int, std::bitset<4>> indexToBit = _indexToBitInit();
    template<size_t N1, size_t N2>
    std::bitset<N1+N2> bitConcat(std::bitset<N1>, std::bitset<N2>);
    std::vector<bool> exportBits();
    void build(int, bool);
    void reshuffle();
    void printDeck();
};

// generates unordered map for turning index values into string equivalent
std::unordered_map<int, std::string> deck::_indexToStrInit(){
    std::unordered_map<int, std::string> val;
    for (int i=0; i<13; i++){
        val[cardIndex[i]]=fullSuit[i];
    }
    return val;
}

std::unordered_map<int, std::bitset<4>> deck::_indexToBitInit(){
    std::unordered_map<int, std::bitset<4>> val;
    for (int i=0; i<14; i++){
        val[cardIndex[i]]=valueBitEquivalents[i];
    }
    return val;
}

/*
    Max length bitsets able to be added together = size_t bits
*/
template<size_t N1, size_t N2>
std::bitset<N1+N2> deck::bitConcat(std::bitset<N1> b1, std::bitset<N2> b2){
    std::string s1 = b1.to_string();
    std::string s2 = b2.to_string();
    return std::bitset<N1+N2>(s1+s2);
}

/*
    Uses the fisher yates array shuffle method, O(3n)
*/
void deck::build(int numberOfPacks=1, bool addJokers=false){
    ignoreSuits = true;
    numOfPacks=numberOfPacks;
    numOfCards=13*4*numOfPacks;
    if(addJokers==true){numOfCards+=numOfPacks*2;}
    // creates unshuffled deck of cards
    for (int i=0;i<numOfPacks;i++){
        for (int j=0;j<4;j++){
            for (int k=1;k<14;k++){
                cards.push_back(k);
            }
        }
    }
    // adds jokers to deck
    if(addJokers==true){
        int numOfJokers = 2*numOfPacks;
        for (int i=numOfCards-numOfJokers; i<numOfCards; i++){
            cards.push_back(14);
        }
    }
    // shuffler
    // for (int i=0; i<numOfCards;i++){
    //     int randNum = rand()%numOfCards;
    //     std::iter_swap(cards.begin()+i, cards.begin()+randNum);
    // }
}

void deck::reshuffle(){
    // shuffler
    for (int i=0; i<numOfCards;i++){
        int randNum = rand()%numOfCards;
        std::iter_swap(cards.begin()+i, cards.begin()+randNum);
    }
}

void deck::printDeck(){
    std::list<int>::iterator itr;
    for (int i=0; i<numOfCards;i++){
        std::cout << cards.at(i);
    }
    std::cout << std::endl;
}

/*
    Produces a bool vector containing the values of the deck turned into bits.
    Each card represents 4 or 6 bits. If 6 bits then the first two denote suit,
    the next 4 denote card value.
*/
std::vector<bool> deck::exportBits(){
    int bitsPerCard = 4;
    if (ignoreSuits=false){bitsPerCard+=2;}
    const int totalBits = bitsPerCard*numOfCards;
    std::vector<bool> deckBits;
    std::string tempStr;
    for (int i=0; i<numOfCards;i++){
        std::bitset<4> tempBit = cards.at(i);
        tempStr = tempBit.to_string();
        for (int j=0; j<bitsPerCard;j++){
            deckBits.push_back(tempStr[j]=='1');
        }
    }
    return deckBits;
}
