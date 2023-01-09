#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <unordered_map>

#include "deck.h"
#include "player.h"


/*
    Takes in a list of players, ignores the first one
    and finds out if any players are able to play
*/
bool gameFinishedCheck(std::list<Player> players){
    std::list<Player>::iterator itr;
    itr = players.begin();
    itr++;
    for (itr; itr!=players.end(); itr++){
        if (itr->finished == false){return false;}
        continue; 
    }
    return true;
}
/*
    Takes a list of players and prints out their hands, each on a new row.
    Takes a bool value on whether or not it should censor the dealer's first card, assumes true.
*/
void printHands(std::list<Player> players, bool censor = true){
    std::list<Player>::iterator plyrItr;
    plyrItr = players.begin();
    std::list<std::string>::iterator cardItr;
    // Prints out the dealer's hand to work with the censor exception
    bool dealerFirstCard = true;
    std::cout << plyrItr->name << " :";
    for (cardItr = plyrItr->inventory.begin(); cardItr != plyrItr->inventory.end(); cardItr++){
        if (dealerFirstCard == true && censor == true){std::cout << " ?"; dealerFirstCard = false; continue;}
        std::cout << " " << *cardItr;
    }
    if (censor == false){
        std::cout << " : " << plyrItr->score << " Points";
        if (plyrItr->score > 21){std::cout << " !BUST!";}
    }
    std::cout << std::endl;
    plyrItr++;
    // Prints out the rest of the players
    for (plyrItr; plyrItr != players.end(); plyrItr++){
        std::cout << plyrItr->name << " :";
        for (cardItr = plyrItr->inventory.begin(); cardItr != plyrItr->inventory.end(); cardItr++){
            std::cout << " " << *cardItr;
        }
        std::cout << " : " << plyrItr->score << " Points";
        if (plyrItr->score > 21){std::cout << " !BUST!";}
        std::cout << std::endl << std::endl;
    }

}

int main()  {
    srand(time(NULL));
    std::cout << std::endl;

    cardsDeck cards;
    cards.initValues();
    cards.buildDeck();
    cards.shuffleDeck();

    Player dealer, p1;
    dealer.name = "Dealer";
    p1.name = "Player";

    std::list<Player> players;
    players.push_back(dealer);
    players.push_back(p1);

    std::list<Player>::iterator playerItr;

    /*
        Deals the starting two cards one at a time to all players
        starting with the dealer.
    */
    for (int i = 0; i < 2; i++){
        for (playerItr = players.begin(); playerItr != players.end(); playerItr++){
            playerItr->inventory.push_back(cards.withdraw());
            playerItr->cardsVal(cards.cardValues, true);
        }
    }
    
    // std::list<std::string>::iterator invItr;
    // for (playerItr = players.begin(); playerItr != players.end(); playerItr++){
    //     std::cout << playerItr->name << " : ";
    //     for (invItr = playerItr->inventory.begin(); invItr != playerItr->inventory.end(); invItr++) {
    //         std::cout << *invItr << " ";
    //     }
    //     std::cout << ": " << playerItr->cardsVal(cards.cardValues, true) << " Points" << std::endl;
    // }
    int win = 0, draw = 0, loss = 0;
    printHands(players);
    while(gameFinishedCheck(players)==false){
        for (playerItr = players.begin(); playerItr != players.end(); playerItr++){
            if (playerItr->name == "Dealer"){continue;}
            bool cardsDrawn = false;
            std::string hitIn;
            while (true){
                std::cout << playerItr->name << "'s turn!" << std::endl;
                if (playerItr->score == 21){
                        if (cardsDrawn == false){
                            std::cout << "Blackjack!" << std::endl << std::endl;
                            }
                        playerItr->finished = true;
                        break;
                    }
                std::cout << "Would you like to hit? Y/N : ";
                std::cin >> hitIn;
                std::cout << std::endl;
                if (hitIn == "Y" or hitIn == "y"){
                    playerItr->inventory.push_back(cards.withdraw());
                    playerItr->cardsVal(cards.cardValues, true);
                    printHands(players);
                    // Blackjack check + 21 check
                    if (playerItr->score == 21){
                        std::cout << "Stand!" << std::endl << std::endl;
                        playerItr->finished = true;
                    }
                    break;
                }
                if (hitIn == "N" or hitIn == "n"){
                    std::cout << "Stand!" << std::endl << std::endl;
                    playerItr->finished = true;
                    break;
                }
            }
        }
    }
    std::cout << players.front().name << "'s turn!" << std::endl;
    // Dealer always draws when their score is under 17
    while (players.front().score < 17){
        players.front().inventory.push_back(cards.withdraw());
        players.front().cardsVal(cards.cardValues, true);
    }
    printHands(players, false);

    // Win/Loss info
    bool dealerDisplayed = false;
    int dealerScore = players.front().score;
    for (playerItr = players.begin(); playerItr != players.end(); playerItr++){
        std::cout << playerItr->name << "'s score : " << playerItr->score;
        if (playerItr->score > 21 ) {std::cout << " : !BUST!" << std::endl;}
        else if (playerItr->score > dealerScore) {std::cout << " : Win!" << std::endl;}
        else if (playerItr->score < dealerScore) {std::cout << " : Loss!" << std::endl;}
        else if (playerItr->score == dealerScore && playerItr != players.begin()) {std::cout << " : Tie!" << std::endl;}
        std::cout << std::endl;
    }
    
    return 0;
}


