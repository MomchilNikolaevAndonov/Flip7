#ifndef HEADER_H
#define HEADER_H
#include <vector>
#include "neural_network.h"
using namespace std;

const int n_players = 4;

class Players {
private:
    
public: 
    vector<int> cards;
    bool lose = false;
    bool round_end = false;
    int score = 0;
    NN nn;
    
    Players(); 

    void getCards(int card);

    void calc_score();

    void check_lose();

    void reset_round();

    void reset_game();

    void print_cards(int n);

    vector<float> player_decision(vector<float>);

    void Mutate();
 
    bool want_card(bool);
    
};




class Game{
    private:
   

  public:
    int deck[92];
    
    Game();

    bool game_end(int n_players, Players players[]);
    
    void make_deck();
  
    int resuffle(int card_index);
   
};

#endif // HEADER_H