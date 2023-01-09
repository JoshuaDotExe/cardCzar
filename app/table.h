#include <string>
#include <unordered_map>
#include <iostream>

#include "player.h"
#include "deck.h"

class Table{
    cardsDeck deck;
    std::list<Player> players;
};