#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "header.h"
using namespace std;





    Players::Players() : score(0), cards(vector<int>()) {}

    void Players::getCards(int card){
        cards.push_back(card);
    }

    void Players::calc_score(){

        int value = 0;
        for(int i = 0; i < cards.size(); i++){
            value += cards[i];
        }
        score += value;
    }

    bool Players::check_lose(){

        // Sort the input array
        sort(cards.begin(), cards.end());

        // Iterate through the sorted array
        for (int i = 1; i < cards.size(); ++i) {

            // Check if adjacent elements are equal
            if (cards[i] == cards[i - 1]){
             round_end = true;
             return  round_end;// Set round_end to true if duplicate found
            }

        }
        // Set round_end to true if no duplicates found
         return false;  // No duplicates, player does not lose
    }


    void Players::reset_round(){
        round_end = false;
        cards.clear();
    }

    void Players::print_cards(int i){
        cout << "Player " << i + 1 << ": " << endl;
        cout << "Cards: ";
        for(int i = 0; i < cards.size(); i++){
            cout << cards[i] << " ";
        }
        cout << endl;
        cout  << "Points this round: " << score;
        cout << endl;

    }

    vector<float> Players::player_decision(vector<float> NN_inputs){
        return Brain(NN_inputs);
    }

    void Players::Mutate(){
        MutateNetwork(MutateChance, MutateAmount);
    }

    bool Players::want_card(bool decision){

        if (decision) {
            round_end = true;
            return round_end;
        }
        else if (decision) {
            round_end = false;
            return round_end;
        }
         exit(3);
         return true;
}