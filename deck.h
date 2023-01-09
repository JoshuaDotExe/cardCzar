#include <bitset>
#include <list>

class deck{
public:
    bool ignoreSuits;
    bool removeJokers;
    int numOfPacks;
    std::list<std::bitset<4>> bitValue;
    std::list<std::bitset<2>> bitSuit;
};