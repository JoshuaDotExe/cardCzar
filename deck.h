#include <bitset>
#include <list>
#include <unordered_map>

class deck{
private:
    std::string fullSuit[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int valuePoints[13] = {11,2,3,4,5,6,7,8,9,10,10,10,10};
    int cardIndex[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    std::bitset<4> valueBitEquivalents[13] = {0001,0010,0011,0100,0101,0110,0111,1000,1001,1010,1011,1100,1101};
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
    std::list<std::bitset<6>> bitDeck;
    std::list<std::bitset<4>> bitValueDeck;
    std::list<std::bitset<2>> bitSuitDeck;
    std::unordered_map<int, std::string> indexToStr = _indexToStrInit();
    std::unordered_map<int, std::bitset<4>> indexToBit = _indexToBitInit();
    std::unordered_map<int, int> indexToVal = _indexToValueInit();
    template<size_t N1, size_t N2>
    std::bitset<N1+N2> bitConcat(std::bitset<N1>, std::bitset<N2>);
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
    for (int i=0; i<13; i++){
        val[cardIndex[i]]=valueBitEquivalents[i];
    }
    return val;
}

std::unordered_map<int, int> deck::_indexToValueInit(){
    std::unordered_map<int, int> val;
    for (int i=0; i<13; i++){
        val[cardIndex[i]]=valuePoints[i];
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
    numOfPacks=numberOfPacks;
    numOfCards = 13*4*numOfPacks;
    if(addJokers==true){numOfCards+=numOfPacks*2;}
    // creates unshuffled deck of cards
    int d1[numOfCards];
    int counter = 0;
    for (int i=0;i<numOfPacks;i++){
        for (int j=0;j<4;j++){
            for (int k=1;k<14;k++){
                d1[counter]=k;
                counter++;
            }
        }
    }
    // adds jokers to deck
    if(addJokers==true){
        int numOfJokers = 2*numOfPacks;
        for (int i=numOfCards-numOfJokers; i<numOfCards; i++){
            d1[i] = 14;
        }

    }
    // shuffler
    int randNum=0;
    int tempHolder;
    for (int i=0; i<numOfCards;i++){
        randNum = rand()%numOfCards;
        tempHolder = d1[randNum];
        d1[randNum] = d1[i];
        d1[i] = tempHolder;
    }
    // move shuffled d1 into cards list
    for (int i=0; i<numOfCards;i++){
        cards.push_back(d1[i]);
    }

}

void deck::reshuffle(){
    // shuffler
    int randNum=0;
    int tempHolder;
    for (int i=0; i<numOfCards;i++){
        randNum = rand()%numOfCards;
        std::iter_swap(cards.begin()+i, cards.begin()+randNum);
    }
}

void deck::printDeck(){
    // prints out deck
    std::list<int>::iterator itr;
    for (int i=0; i<numOfCards;i++){
        std::cout << cards.at(i);
    }
    std::cout << std::endl;
}



//     attempt num 1
    // int randNum=0;
    // int cardsLeft=13;
    // int tempNum=0;
    // while(availCards.empty()==false){
    //     randNum=rand()%cardsLeft;
    //     tempNum=availCards.at(randNum);
    //     cards.push_back(tempNum);
    //     cardTracker[tempNum]--;
    //     if (cardTracker[tempNum]==0){
    //         cardsLeft--;
    //         std::cout << availCards.at(randNum) << std::endl;
    //         availCards.erase(availCards.begin()+randNum);
    //     }

// // jokers not implemented
// void deck::build(int numOfPacks = 1, bool removeJokers = true, bool ignoreSuits = true){
//     std::cout << "got here";
//     int difCards = 13, deckSize = difCards*(numOfPacks*4);
//     //      if (removeJokers==false){deckSize+(numOfPacks*2);}
//     int cardsInPack[deckSize];
//     int cardTracker[difCards];
//     for (int i=0; i<13;i++){
//         cardTracker[i]=4*numOfPacks;
//     }
//     //      Adds jokers into possible pick rota
//     //      if (removeJokers==false){cardTracker[13]=2*numOfPacks;}
//     // Creates list of ints that'll have objects removed when none are left to use
//     std::list<int> availCards; 
//     for (int i=0; i<difCards; i++){
//         availCards.push_back(i);
//     }
//     int randNum=0;
//     while (availCards.empty()==false){
//         randNum=rand()/difCards;
//         if (cardIndex[randNum] == 1){
//             availCards.remove(randNum);
//         }
//         cards.push_back(randNum+1);
//     }
// }