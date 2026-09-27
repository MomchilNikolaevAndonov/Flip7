//
// Created by Ivan on 24.9.2026 г..
//

#ifndef HEADER_H
#define HEADER_H

#include <vector>
using namespace std;

class Players {
private:
    vector<int> cards;


public: 
   bool lose = false;
    bool round_end = false;
    int score;
    int round_score = 0;
    
    Players(); 

    void getCards(int card);

    void calc_score();

    void save_score();

    bool check_lose();

    void reset();

    void print_cards(int n);

    bool player_another_card(int n);
};

class Game{
    private:
   

  public:
    int deck[92];
    
    Game();

    bool game_end(int n_players, Players players[]);
    
    void make_deck();
  
    void resuffle(int cards[]);
   
};

#endif // HEADER_H