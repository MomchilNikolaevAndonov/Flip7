#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "header.h"


using namespace std;
/*
int size_of_arr(int arr[]){

    if(arr[0] == NULL)       
        return 0;

    cout<<sizeof(arr) / sizeof(arr[0]);
    return sizeof(arr) / sizeof(arr[0]);
}
*/
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
    return 1.0 / (1.0 + std::exp(-x));
}

bool make_choice(int NN_output){
    double drawOutput = sigmoid(NN_output);

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
    int card_index = 0;
    Game game;
    Players players[n_players];
    game.make_deck();  
    game.resuffle(game.deck);


    vector<float> NN_output;
    vector<float> NN_inputs;
do{ 

    // Game process  
    do{
           
        for (int i = 0; i < n_players; i++) {
            players[i].reset_round();
            players[i].getCards(game.deck[card_index]);
            card_index++;
         }
    
        //Round of the game
        do {

             for (int i = 0; i < n_players; i++) {

                if (players[i].round_end) 
                    continue;
                 
                //print the cards and ask if they want to draw another card
                players[i].print_cards(i);

                //ToDO:add the NN_inputs to the NN: num of every card(enemy self),current points(enemy/srlf), game points(enemy/self)
                //NN_inputs = calc_NN_input(game.deck, players[i]);


                NN_inputs = calc_NN_input(players[i]);      
                 
                NN_output = players[i].player_decision(NN_inputs);
                cout<<"ojvmoq greshaka ne si chak takuv"<<endl;  
                bool NN_choice = make_choice(NN_output[0]);
                //TODO:add the NN_output to the decision

                if (!players[i].want_card(NN_choice)) {
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

    for(int i = 0; i < n_players; i++){
        players[i].Mutate();
    }

}while(true);

    cout << "Final Scores: " << endl;
    for (int i = 0; i < n_players; i++)
    {
        cout << "Player " << i + 1 << ": " << players[i].score << endl;
    }
    cout << "Game Over!" << endl;
    return 0;
}
