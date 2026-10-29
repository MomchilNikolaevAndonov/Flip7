#include <vector>
#include <random> 
#include <iostream>
#include <algorithm>
#include "header.h"
#include "neural_network.h"
using namespace std;


random_device rd;
mt19937 gen(rd());  
// Define the range: [-1.0, 1.0) - Upper bound is excluded by default
uniform_real_distribution<double> distrib(-1.0, 1.0);
uniform_real_distribution<double> rand_n(0, 1.0);


//NN Constructor
NN::NN()
{   

      for (int i = 0; i < networkShape.size() - 1; i++)
          layers.emplace_back(networkShape[i],networkShape[i + 1]);
          
      MutateNetwork(MutateChance, MutateAmount);     
}



     int n_inputs;
     int n_nodes;


     vector<vector<float>> weightArrays;
     vector<float> biasesArray;
     vector<float> nodeArray;

     //Add comment
     NN::Layer::Layer(int n_inputs, int n_nodes){
          this->n_inputs = n_inputs;
          this->n_nodes = n_nodes;

          weightArrays = vector<vector<float>>(n_nodes, vector<float>(n_inputs));

          biasesArray = vector<float>(n_nodes);
          nodeArray = vector<float>(n_nodes);
     }

     //Add comment
     void NN::Layer::MutateLayer(float MutationChance, float MutateAmount){
               for(int i = 0;i < n_nodes; i++){

                    for(int j = 0; j < n_inputs; j++){
                         if(rand_n(gen) < MutationChance){
                              weightArrays[i][j] += distrib(gen)*MutateAmount;
                         }
                    }

                    if(rand_n(gen) < MutationChance){
                         biasesArray[i] += distrib(gen)*MutateAmount;
                    }

               }
     }

     //Add comment
     void NN::Layer::Forward(vector<float> inputsArray){
               for(int  i=0; i < n_nodes; i++){

                    //sum of weights*inputs 
                    for(int j = 0; j < n_inputs; j++){
                         nodeArray[i] += weightArrays[i][j] * inputsArray[j];
                    }

                    //add the bias
                    nodeArray[i] += biasesArray[i];                   
               }
     }

     //Add comment
     void NN::Layer::Activation(){
          for(int  i=0; i < n_nodes; i++){
               if(nodeArray[i] < 0){
                    nodeArray[i] = 0;
               }
          }

     }


//Starts the mutation from here
void NN::MutateNetwork(float MutationChance, float MutationAmount){
     for(int i = 0; i < layers.size(); i++)
          layers[i].MutateLayer(MutationChance, MutationAmount);
}

//Add comment
vector<float> NN::Brain(vector<float> inputs){

     for (int i = 0; i < layers.size(); i++)
     {     
          if(i == 0){  

               layers[i].Forward(inputs);           
               layers[i].Activation();
          }
          else if(i == layers.size() - 1){

               layers[i].Forward(layers[i - 1].nodeArray);
     
          }
          else{

               layers[i].Forward(layers[i - 1].nodeArray);
               layers[i].Activation();

          } 
     } 
     
     return(layers[layers.size() - 1].nodeArray);
}

//Deletes the values in the NN
void NN::clear_NN(){
     for (int i = 0; i < layers.size(); i++){
          for(int j = 0; j < layers[i].nodeArray.size(); j++)
               layers[i].nodeArray[j] = 0;
     }                          
}

//Slects the winner from the previous game and copyes it's NN to the Others, than mutates it
void NN::natural_selection(Players players[], int n_players){
    // Sort players based on their scores in descending order
    sort(players, players + n_players, [](const Players& a, const Players& b) {
        return a.score > b.score;
    });

    for (int i = 1; i < n_players-1; ++i) {
        players[1].nn.layers = players[0].nn.layers;
        players[i].Mutate();
    }

}

//Mutates all the players
void NN::mutate_ALL(int n_players, Players players[]){
    for(int i = 0; i < n_players; i++){
        players[i].Mutate();
    }
}

//
vector<float> NN::calc_NN_input(Players player){
    //makes red_cap for the num of each card in 1 deck
    vector<int> rep_cards;
    rep_cards.push_back(1);   
    for (int i = 1; i < 14; i++)
        rep_cards.push_back(i);         
     
        
    vector<float> NN_inputs = Game::count_cards(player.cards);


    //makes sutable NN_inputs
    for(int i = 0; i < rep_cards.size(); i++){
        NN_inputs[i] = NN_inputs[i] / rep_cards[i];
    }

    return NN_inputs;

}


double NN::sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

bool NN::make_choice(float NN_output){
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