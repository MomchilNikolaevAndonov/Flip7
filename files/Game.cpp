#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

# include "header.h"
using namespace std;

     Game::Game(){};

    bool Game::game_end(int n_players, Players players[]){
    for (int i = 0; i < n_players; i++)
        {
            if (players[i].score >= 200) {
                return true;
            }
        }
        return false;
    }

    void Game::del_excluded_cards(vector<int> excluded_cards) {
        for (int i = 0; i < excluded_cards.size(); i++) {
          auto pos_of_ex_cards = remove(deck.begin(), deck.end(), excluded_cards[i]);
          deck.erase(pos_of_ex_cards, deck.end());
        }
    }

    
    void Game::make_deck() {
        reff_deck.push_back(0); // Add the zero card to the deck
        for (int i = 1; i < 14; i++)
        {
            for (int j = 0; j < i; j++)
            {
                reff_deck.push_back(i);
            }
        };

       deck = reff_deck; // Copy the reference deck to the actual deck
    }

    
    void Game::resuffle(bool force_reshuffle, vector<int> excluded_cards) {

        random_device rd;
        
        // 2. Initialize the standard Mersenne Twister engine with the seed
        mt19937 g(rd());

        if (force_reshuffle || card_index >= 92 || deck.size() == 0) {
            cout << "Deck is empty. Reshuffling..." << endl;
            deck = reff_deck; // Reset the deck to the reference deck
            del_excluded_cards(excluded_cards);
            shuffle(deck.begin(), deck.end(), g); // Shuffle the deck
            card_index = 0;
        }
        
    }

    vector<float> Game::count_cards(vector<int> players_cards){
    vector<float> rep_cards;
    for(int i = 0; i < 20; i++)
        rep_cards.push_back(0);

    for(int i = 0; i < players_cards.size(); i++)
    {       
        rep_cards.at(players_cards[i])++; 
               
    }
  
    return rep_cards;
    }

    void Game::reset_game(Players players[], int n_players){
    for(int i = 0; i < n_players; i++){
        players[i].reset_game();
    }
}


vector<int> Game::find_excluded_cards(Players players[], int n_players){
    vector<int> excluded_cards;
    for (int i = 0; i < n_players; i++) {
        for (int j = 0; j < players[i].cards.size(); j++) {
            excluded_cards.push_back(players[i].cards[j]);
        }
    }
    return excluded_cards;
}

bool Game::end_round(int n_players, Players players[]){

    for (int i = 0; i < n_players; i++)
    {    
        if (!players[i].round_end) {
            return false;
        }
       
    }
    return true;
}
