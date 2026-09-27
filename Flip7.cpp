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

void calc_score(Players players[], int player){
        if(!players[player].lose)
         players[player].calc_score();
                      
}


//void shuffle(int card_index,Game& game){}



int main()
{
    const int n_players = 4;
    int card_index = 0;

    Game game;
    Players players[n_players];

    game.make_deck();  
    game.resuffle(game.deck);
 
    // Game process  
    do{
       
        for (int i = 0; i < n_players; i++) {
            players[i].reset();
            players[i].getCards(game.deck[card_index]);
            calc_score(players, i);
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
                players[i].print_cards(i);

                if (players[i].player_another_card(i)) {

                    players[i].getCards(game.deck[card_index]);

                    calc_score(players, i);
                    
                    card_index++;
                    players[i].print_cards(i);
                }
                
                // Check if the deck is empty and reshuffle if necessary
                //shuffle(card_index, game);
                if(card_index >= 92){
                    cout  << endl << endl << endl;
                    cout << "Deck is empty. Reshuffling..." << endl;
                    game.make_deck();  
                    game.resuffle(game.deck);
                    card_index = 0;
                }
                     
                players[i].lose = players[i].check_lose();

                if (players[i].round_end) {
                     if(players[i].lose)
                        cout << "Player " << i + 1 << ": ended the round! Points: " << players[i].score << endl;
                     else
                        cout << "Player " << i + 1 << ": ended the round! Points: " << players[i].score + players[i].round_score<< endl;
                }

                cout << endl;
            }
         

        } while (!end_round(n_players, players)); 


        for(int i = 0; i < n_players; i++)
            if(!players[i].lose)
                players[i].save_score();

        
       
        
    }while (game.game_end(n_players, players) == false);


    cout << "Final Scores: " << endl;
    for (int i = 0; i < n_players; i++)
    {
        cout << "Player " << i + 1 << ": " << players[i].score << endl;
    }
    cout << "Game Over!" << endl;
    return 0;
}
