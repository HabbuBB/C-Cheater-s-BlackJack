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
#include "game.h"


Game::Game(){
    
}


struct Score {
    std::string name;
    int chips;
};

void Game::saveScore(const std::string& name, int chips) {
    // Create an empty vector for scores
    std::vector<Score> scores;
    
    // Open the scores file
    std::ifstream file("scores.txt");

    // If the file is open, read all the scores and add them to vector
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Use an istringstream to parse line into Score object
            std::istringstream iss(line);
            Score score;
            iss >> score.name >> score.chips;
            scores.push_back(score);
        }
        file.close();
    }

    // Add the new score to the vector
    Score newScore = {name, chips};
    scores.push_back(newScore);

    // Sort scores based on chips
    std::sort(scores.begin(), scores.end(),
              [](const Score& a, const Score& b) { return a.chips > b.chips; });

    // Open the scores file for writing
    std::ofstream outfile("scores.txt");

    // Write top 10 scores to the file
    int numScores = std::min(static_cast<int>(scores.size()), 10);
    for (int i = 0; i < numScores; i++) {
        outfile << scores[i].name << " " << scores[i].chips << std::endl;
    }

    std::cout << "Saved to scoreboard!" << std::endl;

    // Close the file
    outfile.close();
}

void Game::printScores() {
    std::ifstream file("scores.txt");
    std::cout << "\x1B[34m";
    std::cout << "-----Scoreboard------" << std::endl;
    if (file.is_open()) {
        std::string line;
        int i = 1;
        while (std::getline(file, line) && i <= 10) {
            std::istringstream iss(line);
            std::string name;
            int chips;
            iss >> name >> chips;
            std::cout << i << ". " << name << " - " << chips << " chips" << std::endl;
            i++;
        }
        file.close();
    }
    std::cout << "\033[0m";
}

void Game::playerPlay(Player& player, Cards& deck, Dealer& dealer){
    int playerMove;
    std::cout << "(1) Hit" << std::endl 
    << "(2) Stand" << std::endl 
    << "(3) Double down" << std::endl
    << "(4) See card chances" << std::endl
    << "What will you do: ";
    std::cin >> playerMove;
    std::cout << std::endl;

    if(playerMove == 1) {
        player.takeCard(deck.drawCard());
        dealer.showFirstCards();
        player.showHand();
        //Call the function recursively until player busts
        if(player.calculateHand() < 22){
            playerPlay(player, deck, dealer);
        }
    }else if (playerMove == 2){
        dealerPlayGame(dealer, deck);
        dealer.showHand();
        player.showHand();
    }else if (playerMove == 3){
        if(player.getChips() < (player.getCurrentBet() * 2)){
            std::cout << "Not enough chips! Current chips amount is " << player.getChips() 
            << " and your bet is " << player.getCurrentBet() << " chips." << std::endl;
            playerPlay(player, deck, dealer);
        }else{
            player.setCurrentBet((player.getCurrentBet() * 2));
            player.takeCard(deck.drawCard());
            player.showHand();
            dealerPlayGame(dealer, deck);
            dealer.showHand();
        }

    }else if(playerMove == 4){
        dealer.showFirstCards();
        player.showHand();
        deck.getCardChances();
        playerPlay(player, deck, dealer);
    }else{
        std::cout << "Invalid choice!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        playerPlay(player, deck, dealer);
        
    }
}

void Game::dealerPlayGame(Dealer& dealer, Cards& deck){
    while(dealer.calculateHand() < 17){
        dealer.takeCard(deck.drawCard());
    }
}

std::string Game::whoWins(Player& player, Dealer& dealer){
    int playerScore = player.calculateHand();
    int dealerScore = dealer.calculateHand();
    if(playerScore > 21){
        std::cout << "Player busts!" << std::endl;
        return "Dealer";
    }else if(dealerScore > 21){
        std::cout << "Dealer busts!" << std::endl;
        return "Player";
    }else if(playerScore > dealerScore){
        return "Player";
    }else if(playerScore == dealerScore){
        return "Tie";
    }else{
        return "Dealer";
    }
}