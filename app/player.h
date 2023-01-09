#include <string>
#include <list>
#include <unordered_map>
#include <iostream>

class Player {
public:
    std::string name;
    std::list<std::string> inventory;
    int score = 0;
    bool finished = false;

    void pickupCard(std::string);
    void resetStats();
    int cardsVal(std::unordered_map<std::string, int>, bool);
};

/*
    Used to calculate the value of an input player's card inventory,
    also needs to be fed the map of card values and 
    told whether or not to update the player's score, assumes false.
*/
int Player::cardsVal(std::unordered_map<std::string, int> cardValues, bool UpdatePlayerTotal = false){
    std::list<std::string>::iterator itr;
    int total = 0;
    for (itr = inventory.begin(); itr != inventory.end(); itr++){
        total += cardValues[*itr];
    }
    // Checks for an ace to turn into a 1 value
    if (total > 21){
        int numOfAces = 0;
        for (itr = inventory.begin(); itr != inventory.end(); itr++){
            if (*itr == "A"){numOfAces++;}
        }
        // Reduces an ace's value to 1 as many times as there are aces in the inv and the score is above 21
        while(numOfAces > 0 && total > 21){
            total-=10;
            numOfAces--;
        }
        if (total > 21){
            finished = true;
        }
    }
    if (UpdatePlayerTotal == true){
        score = total;
    }
    return total;
}

void Player::pickupCard(std::string newCard){
    inventory.push_back(newCard);
}

void Player::resetStats(){
    inventory.empty();
}