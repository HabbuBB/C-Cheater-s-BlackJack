#ifndef DEALER_H
#define DEALER_H

#include "player.h"
#include <vector>

class Dealer: public Player{
    public:
        Dealer();
        void showFirstCards();
        int showFirstCardsValue();
        void showHand();
};




#endif // DEALER_H