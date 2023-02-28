#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>

class Cards{
    public:
        Cards(int deckAmountInput);
        int deckAmount;
        //12 different types of cards. Aces, twos, ..., tens, jacks, queens, kings. It's a float to make calculating percentages possible.
        float cardTypes[13] = {0};
        void shuffle();
        std::string drawCard();

        void setCardTypeAmounts();
        void getCardChances();

        int getSize();
        
        int getTopCard();

    protected:
        std::vector<std::string> deck;
        long seed;
        //Integer, that says what is the index of the top card in the deck
        int topCard;


    private:
        void fillDeck();
        std::string getCardValue(std::string const&);
        std::string getCardSuite(std::string const&);
};


#endif // CARDS_H