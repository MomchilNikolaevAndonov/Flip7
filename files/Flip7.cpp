#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "header.h"
#include "neural_network.h"


using namespace std;
/*
int size_of_arr(int arr[]){

    if(arr[0] == NULL)       
        return 0;

    cout<<sizeof(arr) / sizeof(arr[0]);
    return sizeof(arr) / sizeof(arr[0]);
}
*/

vector<int> find_excluded_cards(Players players[], int n_players){
    vector<int> excluded_cards;
    for (int i = 0; i < n_players; i++) {
        for (int j = 0; j < players[i].cards.size(); j++) {
            excluded_cards.push_back(players[i].cards[j]);
        }
    }
    return excluded_cards;
}

void natural_selection(Players players[], int n_players){
    // Sort players based on their scores in descending order
    sort(players, players + n_players, [](const Players& a, const Players& b) {
        return a.score > b.score;
    });

    for (int i = 1; i < n_players-1; ++i) {
        players[1].nn.layers = players[0].nn.layers;
        players[i].Mutate();
    }

}


void mutate_ALL(int n_players, Players players[]){
    for(int i = 0; i < n_players; i++){
        players[i].Mutate();
    }
}

// int check_winner(int n_players, Players players[]){
//     int winner_index = -1;
//     int max_score = -1;

//     for (int i = 0; i < n_players; i++) {
//         if (players[i].score > max_score) {
//             max_score = players[i].score;
//             winner_index = i;
//         }
//     }

//     return winner_index;
// }

void reset_game(Players players[], int n_players){
    for(int i = 0; i < n_players; i++){
        players[i].reset_game();
    }
}

vector<float> count_cards(vector<int> players_cards){
    vector<float> rep_cards;
    for(int i = 0; i < 20; i++)
        rep_cards.push_back(0);

    for(int i = 0; i < players_cards.size(); i++)
    {       
        rep_cards.at(players_cards[i])++; 
               
    }
  
    return rep_cards;

}

vector<float> calc_NN_input(Players player){
    //makes red_cap for the num of each card in 1 deck
    vector<int> rep_cards;
    rep_cards.push_back(1);   
    for (int i = 1; i < 14; i++)
        rep_cards.push_back(i);         
     
       
    vector<float> NN_inputs = count_cards(player.cards);


    //makes sutable NN_inputs
    for(int i = 0; i < rep_cards.size(); i++){
        NN_inputs[i] = NN_inputs[i] / rep_cards[i];
    }

    return NN_inputs;

}

bool end_round(int n_players, Players players[]){

    for (int i = 0; i < n_players; i++)
    {
        if (!players[i].round_end) {
            return false;
        }
       
    }
    return true;
}

double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

bool make_choice(float NN_output){
    float drawOutput = sigmoid(NN_output);
    cout<<drawOutput<<endl;
    if (drawOutput >= 0.5)
    {
        return true;
    }
    else
    {
        return false;
    }

}


int main()
{
    //Game setup  
    int game_count = 0;
    int round_count = 0;
    vector<int> excluded_cards;
    Game game;
    Players players[n_players];
    game.make_deck();  
    game.resuffle(true, find_excluded_cards(players, n_players));


    vector<float> NN_output;
    vector<float> NN_inputs;

do
{

    reset_game(players, n_players);
     game.resuffle(true, find_excluded_cards(players, n_players));
     round_count = 0;
    // Game process  
    do{
            
        for (int i = 0; i < n_players; i++) { 
            game.resuffle(false, find_excluded_cards(players, n_players));
            players[i].reset_round();
            players[i].getCards(game.deck[game.card_index]);           
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

                NN_inputs = calc_NN_input(players[i]);
                NN_output = players[i].nn.Brain(NN_inputs);


                for(int j = 0; j < NN_inputs.size(); j++){
                    cout<<NN_inputs[j]<<" ";
                }
                cout<<endl;

                //Clear NN
                players[i].nn.clear_NN();
  

                bool NN_choice = make_choice(NN_output[0]);
                cout<<"NN Choice: "<<NN_choice<<endl;
                //TODO:add the NN_output to the decision

                excluded_cards = find_excluded_cards(players, n_players);
                game.resuffle(false, excluded_cards);

                // Ask the player if they want to draw another card
                if (!players[i].want_card(NN_choice)) {
                    players[i].getCards(game.deck[game.card_index]);
                    game.card_index++;
                    players[i].print_cards(i);
                }

                game.resuffle(false, find_excluded_cards(players, n_players));
                
                // Check if the deck is empty and reshuffle if necessary

                      
                players[i].check_lose();

                if (players[i].round_end) {
                    cout << "Player " << i + 1 << ": ended the round!" << endl;
                }

                
                cout << endl;
            }
        } while (!end_round(n_players, players)); 



        // Calculate scores for each player
        for (int i = 0; i < n_players; i++)      
                if(!players[i].lose)
                 players[i].calc_score();
            
       round_count++;          
       if (round_count >= 200) {
            mutate_ALL(n_players, players);
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
 } while(game_count < 100);

    return 0;
}
