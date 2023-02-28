#include "player.h"

#include <string>
#include <iostream>
#include <vector>

Player::Player() : currentAffectingAces(0), chips(100), currentBet(0) {}

void Player::takeCard(const std::string& card) {
    hand.push_back(card);
    currentAffectingAces = 0;
}

int Player::calculateHand() {
    int total = 0;
    int numAces = 0;
    
    // Loop through each card in the hand and add up its value
    for (const auto& card : hand) {
        // Extract the rank of the card (the first character before the "|")
        const std::string rank = card.substr(0, card.find("|"));

        int value = 0;
        if (rank == "A") {
            value = 11;
            numAces++;
            currentAffectingAces++;
        } else if (rank == "J" || rank == "Q" || rank == "K") {
            value = 10;
        } else if (rank == "Hidden") {
            value = 0;
        } else {
            value = stoi(rank);
        }

        total += value;
    }

    // If there are any aces in the hand and the total is over 21, try to reduce the value of the aces
    while (numAces > 0 && total > 21) {
        total -= 10;
        numAces--;
        currentAffectingAces--;
    }

    return total;
}

void Player::getHand() {
    for (const auto& card : hand) {
        std::cout << card << std::endl;
    }
}

int Player::getChips() {
    return chips;
}

//Adds to player's chip amount. Bet can be removed from the amount if it is negative.
void Player::updateChips(int bet) {
    chips += bet;
}

void Player::setCurrentBet(int bet) {
    currentBet = bet;
}

int Player::getCurrentBet() {
    return currentBet;
}

void Player::resetHand() {
    hand.clear();
}

void Player::showHand() {
    const int handValue = calculateHand();
    std::cout << "\x1B[34m------Your hand------" << std::endl;
    getHand();
     // If there are aces in the hand that are affecting the value, print out two possible values
    if (currentAffectingAces > 0) {
        std::cout << "Total: " << handValue << " or " << handValue - 10 << std::endl << std::endl;
    } else {
        std::cout << "Total: " << handValue << std::endl << std::endl;
    }
    std::cout << "\033[0m";
}
