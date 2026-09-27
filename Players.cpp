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


    void Players::reset(){
        round_end = false;
        cards.clear();
    }

    void Players::print_cards(int n){
        cout << "Cards: ";
        for(int i = 0; i < cards.size(); i++){
            cout << cards[i] << " ";
        }
        cout << endl;
        cout  << "Points this round: " << score;
        cout << endl;

    }

    bool Players::player_decision(int n){
        char decision;
        cout <<  "Do you want to draw another card? (y/n): ";
        cin >> decision;

        if (decision == 'n' || decision == 'N') {
            round_end = true;
            return round_end;
        }
        else if (decision == 'y' || decision == 'Y') {
            round_end = false;
            return round_end;
        }
        else {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
            return player_decision(n); // Recursively ask again
        }
    }