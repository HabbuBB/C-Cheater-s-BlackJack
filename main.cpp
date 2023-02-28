#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "cards.h"
#include "player.h"
#include "dealer.h"
//Not sure if this is good practice, but all the game functions are moved to a game class just to declutter the main.cpp
#include "game.h"



//Template function for forcing the player to enter inputs until a valid input is given.
template<typename F>
void runUntilValid(F func){
    while (!func()) {
        // Keep calling the function until it returns true
    }
}



int main(){
    std::cout << "\x1B[34m"<< "Welcome to Cheater's BlackJack!" << std::endl << 
    "Start by choosing the amount of decks in the game" << std::endl <<
    "This affects the difficulty and length of the game" << "\033[0m" << std::endl << std::endl;

    int deckAmount;
    //Ask the player for input until a valid value is given as input.
    runUntilValid([&deckAmount](){
        std::cout << "Input deck amount 1, 2 or 3: ";
        std::cin >> deckAmount;
        if(std::cin.fail() || deckAmount != 1 && deckAmount != 2 && deckAmount != 3){
            std::cout << "Invalid value! Try again" << std::endl;

            // Clear the error flag on std::cin and ignore any remaining characters in the input buffer
            //This is to avoid infinite loop when user inputs something that isn't a number
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }else{
            return true;
        }
    });
        

    
    std::cout << std::endl << "\x1B[34m" << "Starting a game with " << deckAmount << " deck(s) and 100 chips" << "\033[0m\t\t" << std::endl;
    
    
    Cards deck(deckAmount);  
    deck.shuffle();

    Player player;
    Dealer dealer;
    Game game;
    
    //End game when player runs out of chips or if cards left in deck is less than 10, meaning there isn't enough cards for another game.
    //This is calculated by taking the size of the deck vector and subtracting the topCard index from it
    bool isValid;
    while(player.getChips() > 0 && (deck.getSize() - deck.getTopCard()) > 10){

        runUntilValid([&player](){
            
            int betAmount;
            //TODO: Set up this so that you can only bet your chip amount
            std::cout << "\x1B[34m" << "Current chips: \033[0m" << player.getChips() <<  std::endl << std::endl
            << "Enter bet amount: ";
            std::cin >> betAmount;
            if(betAmount <= player.getChips() && betAmount > 0){
                player.setCurrentBet(betAmount);
                return true;
            }else{
                std::cout << "Invalide bet amount! Current chips: " << player.getChips() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return false;
            }
        });
            
        
        
        
        player.takeCard(deck.drawCard());
        dealer.takeCard(deck.drawCard());
        player.takeCard(deck.drawCard());
        dealer.takeCard(deck.drawCard());

        dealer.showFirstCards();
        player.showHand();
        game.playerPlay(player, deck, dealer);

        std::cout << "\x1B[33m";
        std::string whoWon = game.whoWins(player, dealer);
        if(whoWon == "Player"){
            player.updateChips(player.getCurrentBet());
            std::cout << "You win! You won " << player.getCurrentBet() << " chips!" << std::endl << std::endl; 
        }else if(whoWon=="Tie"){
            std::cout << "Tie! You got your " << player.getCurrentBet() << " chips back!" << std::endl << std::endl;   
        }else{
            //Add negative amount of bet if player loses
            player.updateChips(-(player.getCurrentBet()));
            std::cout << "Dealer wins. You lost " << player.getCurrentBet() << " chips" << std::endl << std::endl;
        }
        std::cout << "\033[0m";

        player.resetHand();
        dealer.resetHand();
        player.setCurrentBet(0);
    }
    std::cout << "Game finished!" << std::endl;
    if((deck.getSize() - deck.getTopCard()) <= 10){
        std::cout << "There aren't enough cards in the deck anymore!" << std::endl;
    }

    if(player.getChips() <= 0){
        std::cout << "You ran out of chips. Better luck next time!" << std::endl;
    }else{
        std::cout << "You finished with " << player.getChips() << " chips!" << std::endl << "Good job on beating the dealer!" << std::endl;
        std::string name;
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << std::endl;

        //Save score to a file
        game.saveScore(name, player.getChips());

        //Show the scores after they are finished.
        game.printScores();

    }

    return 0;
}
