#include "cards.h"

#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

Cards::Cards(int deckAmountInput=1) :
    deckAmount(deckAmountInput),
    topCard(0),
    cardTypes{ 0 }
{
    fillDeck();
}

void Cards::fillDeck()
{
    // The four suits in a deck of cards
    std::string suits[] = { "spades", "diamonds", "clubs", "hearts" };

    // The thirteen possible values for a card in a deck
    std::string values[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

    // Reserving the size of the deck to avoid reallocation
    deck.reserve(deckAmount * 52);

    // Adding cards to the deck for each deck in the game
    for (int i = 0; i < deckAmount; i++) {
        // Adding cards for each suit
        for (const auto& suit : suits) {
            // Adding cards for each value
            for (const auto& value : values) {
                // Adding the card to the deck
                deck.emplace_back(value + '|' + suit);
            }
        }
    }

}

std::string Cards::drawCard()
{
    // Checking if there are any cards left in the deck
    if (topCard >= static_cast<int>(deck.size())) {
        return "End";
    }
    else {
        // Removing and returning the top card from the deck
        std::string temp = deck[topCard];
        topCard++;
        return temp;
    }
}

void Cards::shuffle()
{
    // Creating a random number generator to shuffle the deck
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, static_cast<int>(deck.size()) - 1);

    // Shuffling the deck by swapping two random cards 1000 times
    for (int i = 0; i < 1000; i++) {
        int location1 = distr(gen);
        int location2 = distr(gen);
        std::swap(deck[location1], deck[location2]);
    }
}


// Initializes the card type amounts
void Cards::setCardTypeAmounts() {
    //Reset card types so they are all zero
    std::fill(cardTypes, cardTypes+13, 0);
    for (int i = topCard; i < deck.size(); i++) {
        std::string card = deck[i];
        std::string value = getCardValue(card);
        int index = -1;
        if (value == "A") index = 0;
        else if (value == "2") index = 1;
        else if (value == "3") index = 2;
        else if (value == "4") index = 3;
        else if (value == "5") index = 4;
        else if (value == "6") index = 5;
        else if (value == "7") index = 6;
        else if (value == "8") index = 7;
        else if (value == "9") index = 8;
        else if (value == "10") index = 9;
        else if (value == "J") index = 10;
        else if (value == "Q") index = 11;
        else if (value == "K") index = 12;
        else std::cout << "Error! Card type in " << value << " not recognized!" << std::endl;
        if (index != -1) cardTypes[index]++;
    }
}

// Calculates and prints the chances for the next card value
void Cards::getCardChances() {
    setCardTypeAmounts();
    int deckLength = deck.size() - topCard;

    std::cout << deckLength << std::endl;
    std::cout << (cardTypes[9] + cardTypes[10] + cardTypes[11] + cardTypes[12]) << std::endl;

    std::cout << "\x1B[34m" << "Chances for the next card value to be: " << std::endl;
    std::cout << "A" << " - " << (cardTypes[0] / (float)deckLength) * 100 << "%" << " | ";
    for (int i = 1; i < 9; i++) {
        std::string value = std::to_string(i + 1);
        std::cout << value << " - " << (cardTypes[i] / (float)deckLength) * 100 << "%" << " | ";
    }
    std::cout << "10 - " << ((cardTypes[9] + cardTypes[10] + cardTypes[11] + cardTypes[12]) / (float)deckLength) * 100 << "%" << std::endl << std::endl;
    std::cout << "\033[0m";
}

// Returns the value of a card
std::string Cards::getCardValue(std::string const& Card) {
    std::string value = Card.substr(0, Card.find("|"));
    if (value == "1") value += "0"; // Convert "10" to "1"
    return value;
}

// Returns the suite of a card
std::string Cards::getCardSuite(std::string const& Card) {
    return Card.substr(Card.find("|") + 1);
}


int Cards::getSize() {
    return deck.size();
}

int Cards::getTopCard() {
    return topCard;
}