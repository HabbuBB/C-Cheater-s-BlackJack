#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player{
    public:
        Player();

        void takeCard(const std::string& card);
        int getChips();
        int currentBet;

        int calculateHand();
        void showHand();
        void getHand();
        
        void setCurrentBet(int bet);
        int getCurrentBet();
        void updateChips(int bet);
        void resetHand();
        
         //Current affecting aces is the ace you get from one move (2 cards at start, 1 on card draw)
        int currentAffectingAces;
        

    protected:
        //Vector is a great way of having a dynamic array.
        std::vector<std::string> hand;
        int chips;
        long seed;
        
};


#endif // PLAYER_H