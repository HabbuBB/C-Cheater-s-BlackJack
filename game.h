#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include "cards.h"
#include "player.h"
#include "dealer.h"

class Game {
public:
    Game();
    void saveScore(const std::string& name, int chips);
    void printScores();
    void playerPlay(Player& player, Cards& deck, Dealer& dealer);
    void dealerPlayGame(Dealer& dealer, Cards& deck);
    std::string whoWins(Player& player, Dealer& dealer);

};

#endif /* GAME_H */
