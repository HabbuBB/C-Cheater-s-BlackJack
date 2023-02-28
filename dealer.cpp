#include "dealer.h"

#include <iostream>

Dealer::Dealer() : Player() {}

void Dealer::showFirstCards() {
    const std::string& firstCard = hand.front();
    std::cout << "\x1B[31m------Dealer's hand------\n";
    std::cout << firstCard << ", Hidden|Hidden\n";
    std::cout << "Total: " << showFirstCardsValue() << "\033[0m\n\n";
}

int Dealer::showFirstCardsValue(){
    const std::string& card = hand.front();
    const std::string& rank = card.substr(0, card.find("|"));
    if (rank == "A") {
        // Aces can be 1 or 11, depending on the total value of the hand
        return 11;
    } else if (rank == "J" || rank == "Q" || rank == "K") {
        // Face cards are worth 10
        return 10;
    } else {
        // Number cards are worth their number value
        return std::stoi(rank);
    }
}

void Dealer::showHand() {
    std::cout << "\x1B[31m------Dealer's hand------\n";
    getHand();
    const int dealerTotal = calculateHand();
    std::cout << "Dealer total: " << dealerTotal << "\033[0m\n\n";
}
