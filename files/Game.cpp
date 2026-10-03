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

    
    void Game::make_deck(){
        deck[0] = 0; // Add the zero card to the deck
        int count = 1; // Start counting from the next index
        for (int i = 1; i < 14; i++)
        {
            for (int j = 0; j < i; j++)
            {
                deck[count] = i;
                count++;
            }
        };
    }

    
    void Game::resuffle(bool force_reshuffle){

        random_device rd;
        
        // 2. Initialize the standard Mersenne Twister engine with the seed
        mt19937 g(rd());

        if (force_reshuffle) {
            cout << "Deck is empty. Reshuffling..." << endl;
            make_deck();
            shuffle(deck, deck + 92, g);
            card_index = 0;
            return;
        }

        if(card_index >= 92){
            cout << "Deck is empty. Reshuffling..." << endl;
            make_deck();
            shuffle(deck, deck + 92, g);
            card_index = 0;
        }
        
    }

    
