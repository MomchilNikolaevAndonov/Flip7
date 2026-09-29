#ifndef HEADER_H
#define HEADER_H
#include <vector>
using namespace std;

const int n_players = 4;
const float MutateChance = 0.5;
const float MutateAmount = 0.2;
const vector<int> networkShape = {14, 14, 7, 1};



vector<float> Brain(vector<float>);
void MutateNetwork(float, float);

class Players {
private:
    


public: 
    vector<int> cards;
    bool lose = false;
    bool round_end = false;
    int score;
    
    Players(); 

    void getCards(int card);

    void calc_score();

    bool check_lose();

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
  
    void resuffle(int cards[]);
   
};

#endif // HEADER_H