#include <bitset>
#include <list>
#include <unordered_map>
#include <vector>

class deck{
private:
    char valueID[14] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'X'};
    int cardIndex[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    std::bitset<2> suitBits[4] = {{0x00},{0x01},{0x10},{0x11}};
    char suitID[4] = {'h', 'd', 'c', 's'};
    std::unordered_map<int, std::string> _indexToStrInit();
public:
    bool ignoreSuits;
    bool removeJokers;
    int numOfPacks;
    int numOfCards;
    int numOfJokers;
    std::vector<int> cards;
    std::unordered_map<int, std::string> indexToStr = _indexToStrInit();
    template<size_t N1, size_t N2>
    std::bitset<N1+N2> bitConcat(std::bitset<N1>, std::bitset<N2>);
    std::vector<bool> exportBits();
    std::string exportBitStr();
    std::string exportStr();
    void build(int, bool);
    void reshuffle();
    void printDeck();
};

// generates unordered map for turning index values into string equivalent
std::unordered_map<int, std::string> deck::_indexToStrInit(){
    std::unordered_map<int, std::string> val;
    for (int i=0; i<13; i++){
        val[cardIndex[i]]=valueID[i];
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

void deck::build(int numberOfPacks=1, bool addJokers=false){
    ignoreSuits = true;
    numOfPacks=numberOfPacks;
    numOfCards=13*4*numOfPacks;
    if(addJokers==true){numOfCards+=numOfPacks*2;}
    // creates unshuffled deck of cards
    for (int i=0;i<numOfPacks;i++){
        for (int j=1;j<=numOfCards;j++){
            cards.push_back(j);
        }
    }
}

/*
    Uses the fisher yates array shuffle method, O(3n)
*/
void deck::reshuffle(){
    // shuffler
    for (int i=0; i<numOfCards;i++){
        int randNum = rand()%numOfCards;
        std::iter_swap(cards.begin()+i, cards.begin()+randNum);
    }
}

void deck::printDeck(){
    std::list<int>::iterator itr;
    char c1,c2;
    int num1;
    for (int i=0; i<numOfCards;i++){
        num1=cards.at(i);
        if (num1/13==4*numOfPacks){if(num1%2==1){std::cout << "rX ";}else{std::cout << "bX ";}continue;}
        std::cout << suitID[num1/13] << valueID[num1%13] << ' ';
    }
    std::cout << std::endl;
}

/*
    Produces a bool vector containing the values of the deck turned into bits.
    Each card represents 4 or 6 bits. If 6 bits then the first two denote suit,
    the next 4 denote card value.
*/
std::vector<bool> deck::exportBits(){
    std::vector<bool> deckBits;
    std::bitset<6> b1;
    for (int i=0; i<numOfCards;i++){
        b1=cards.at(i);
        for (char j: b1.to_string()){
            deckBits.push_back(j=='1');
        }
    }
    return deckBits;
}

std::string deck::exportBitStr(){
    std::string s1;
    std::bitset<6> b1;
    for (int i=0; i<numOfCards;i++){
        b1=cards.at(i);
        s1+=b1.to_string();
    }
    return s1;
}

std::string deck::exportStr(){
    std::list<int>::iterator itr;
    std::string s1 = "";
    char c1,c2;
    int num1;
    for (int i=0; i<numOfCards;i++){
        num1=cards.at(i);
        if (num1/13==4*numOfPacks){if(num1%2==1){s1+="rX";}else{s1+="bX";}continue;}
        s1+= suitID[num1/13];
        s1+= valueID[num1%13];
    }
    return s1;
}