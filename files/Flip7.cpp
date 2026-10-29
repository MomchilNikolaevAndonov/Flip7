#include <iostream>
#include <random>
#include <vector>
#include "header.h"
#include "neural_network.h"


using namespace std;

int main()
{
    //Game setup  
    int NN_training = 10;
    int longest_round = 0;
    int game_count = 0;
    int round_count = 0;
    vector<int> excluded_cards;
    Game game;
    Players players[n_players];
    game.make_deck();  
    game.resuffle(true, Game::find_excluded_cards(players, n_players));


    vector<float> NN_output;
    vector<float> NN_inputs;

do
{

     Game::reset_game(players, n_players);
     game.resuffle(true, Game::find_excluded_cards(players, n_players));
     round_count = 0;
    // Game process  
    do{
             
        for (int i = 0; i < n_players; i++) { 
            game.resuffle(false, Game::find_excluded_cards(players, n_players));
            players[i].reset_round();
            players[i].getCards(game.deck.back());     
            game.deck.pop_back();        
            game.card_index++;
         }

        //Round of the game
        do {

             for (int i = 0; i < n_players; i++) {

                // Skip players who have already ended their round
                if (players[i].round_end) 
                    continue;

                    
                //print the cards and ask if they want to draw another card
                players[i].print_cards(i);

                NN_inputs = NN::calc_NN_input(players[i]);
                NN_output = players[i].nn.Brain(NN_inputs);


                for(int j = 0; j < NN_inputs.size(); j++){
                    cout<<NN_inputs[j]<<" ";
                }
                cout<<endl;

                //Clear NN
                players[i].nn.clear_NN();
  
                //print NN choice
                bool NN_choice = NN::make_choice(NN_output[0]);
                if(NN_choice)cout<<"NN Choice: get Card"<<endl;
                else cout<<"NN Choice: pass"<<endl;

                //resuffele
                excluded_cards = Game::find_excluded_cards(players, n_players);
                game.resuffle(false, excluded_cards);

                // Ask the player if they want to draw another card
                if (!players[i].want_card(NN_choice)) {
                    players[i].getCards(game.deck.back());
                    game.deck.pop_back();
                    game.card_index++;
                    players[i].print_cards(i);
                }




                 // Check if the deck is empty and reshuffle if necessary
                game.resuffle(false, Game::find_excluded_cards(players, n_players));
                      
                players[i].check_lose();

                if (players[i].round_end) {
                    cout << "Player " << i + 1 << ": ended the round!" << endl;
                }

                
                cout << endl;
            }

        } while (!Game::end_round(n_players, players)); 


  
        // Calculate scores for each player
        for (int i = 0; i < n_players; i++)      
                if(!players[i].lose)
                 players[i].calc_score();


                    
       round_count++;
       if(longest_round < round_count)       
            longest_round = round_count;

       if (round_count >= 200) {
            NN::mutate_ALL(n_players, players);
            round_count++;
        }
        
    }while (game.game_end(n_players, players) == false);



    cout << "Final Scores: " << endl;
    for (int i = 0; i < n_players; i++)
    {
        cout << "Player " << i + 1 << ": " << players[i].score << endl;
    }
    cout << "Game Over!" << endl;

  // int winner_index = check_winner(n_players, players);

  game_count++;
 } while(game_count < NN_training);

 cout<<"max rounds:"<< longest_round;

    return 0;
}
