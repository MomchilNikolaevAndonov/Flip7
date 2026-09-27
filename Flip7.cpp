#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

# include "header.h"
using namespace std;









bool end_round(int n_players, Players players[]){

    for (int i = 0; i < n_players; i++)
    {
        if (!players[i].round_end) {
            return false;
        }
       
    }
    return true;
}



int main()
{
    const int n_players = 4;
    
    int card_index = 0;
    Game game;
    Players players[n_players];
    game.make_deck();  
    game.resuffle(game.deck);
    card_index = 0;

    

    // Game process  
    do{
       
        
        for (int i = 0; i < n_players; i++) {
            players[i].reset();
            players[i].getCards(game.deck[card_index]);
            card_index++;
         }

        
        //Round of the game
        do
        { 
             for (int i = 0; i < n_players; i++) {

                 if (players[i].round_end) {
                    continue;
                 }
                
                cout << "Player " << i + 1 << ": " << endl;

                //print the cards and ask if they want to draw another card
                players[i].print_cards(i);
                if (!players[i].player_decision(i)) {
                    players[i].getCards(game.deck[card_index]);
                    card_index++;
                    players[i].print_cards(i);
                }
                
                // Check if the deck is empty and reshuffle if necessary
                if(card_index >= 92){
                    cout << "Deck is empty. Reshuffling..." << endl;
                    game.make_deck();  
                    game.resuffle(game.deck);
                    card_index = 0;
               }

                      
                players[i].lose = players[i].check_lose();
                if (players[i].round_end) {
                    cout << "Player " << i + 1 << ": ended the round!" << endl;
                }

                
                cout << endl;
            }
        } while (!end_round(n_players, players)); 



        // Calculate scores for each player
        for (int i = 0; i < n_players; i++)
            {
                if(!players[i].lose)
                 players[i].calc_score();
            }
       
        
    }while (game.game_end(n_players, players) == false);


    //give each player a card
    //ask if they want to get another card
    //draw till they say no or they lose
    //calculate score
    //check if they have won
    cout << "Final Scores: " << endl;
    for (int i = 0; i < n_players; i++)
    {
        cout << "Player " << i + 1 << ": " << players[i].score << endl;
    }
    cout << "Game Over!" << endl;
    return 0;
}
