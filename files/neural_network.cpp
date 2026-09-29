#include <iostream>
#include <vector>
#include <random> 
#include "header.h"
using namespace std;


random_device rd;
mt19937 gen(rd());  
// Define the range: [-1.0, 1.0) - Upper bound is excluded by default
uniform_real_distribution<double> distrib(-1.0, 1.0);
uniform_real_distribution<double> rand_n(0, 1.0);



class Layer
{
private:
    int n_inputs;
    int n_nodes;

public:
    vector<vector<float>> weightArrays;
    vector<float> biasesArray;
    vector<float> nodeArray;

public:
    Layer(int n_inputs, int n_nodes)
    {
        this->n_inputs = n_inputs;
        this->n_nodes = n_nodes;

        weightArrays = vector<vector<float>>(
          n_nodes,
          vector<float>(n_inputs)
      );

        biasesArray = vector<float>(n_nodes);
        nodeArray = vector<float>(n_nodes);
    }

    void MutateLayer(float MutationChance, float MutateAmount){
          for(int i = 0;i < n_nodes; i++){

               for(int j = 0; j < n_inputs; j++)
               {
                    if(rand_n(gen) < MutationChance)
                    {
                         weightArrays[i][j] += distrib(gen)*MutateAmount;
                    }
               }

               if(rand_n(gen) < MutationChance)
               {
                    biasesArray[i] += distrib(gen)*MutateAmount;
               }

          }
    }


    void Forward(vector<float> inputsArray)
    {
          for(int  i=0; i < n_nodes; i++)
          {
               //sum of weights*inputs 
              
               for(int j = 0; j < n_inputs; j++)
               {
                    nodeArray[i] += weightArrays[i][j] * inputsArray[j];

               }

               //add the bias  
              
               nodeArray[i] += biasesArray[i];
               
          }

    }

    void Activation()
    {
      for(int  i=0; i < n_nodes; i++)
      {
          if(nodeArray[i] < 0)
          {
               nodeArray[i] = 0;
          }
      }

    }
};

vector<Layer> layers;

void Wake()
{
      for (int i = 0; i < networkShape.size() - 1; i++)
     {
         layers.emplace_back(
             networkShape[i],
             networkShape[i + 1]
         );
     }

}

void MutateNetwork(float MutationChance, float MutationAmount){
     for(int i = 0; i < layers.size(); i++)
          layers[i].MutateLayer(MutationChance, MutationAmount);
}


vector<float> Brain(vector<float> inputs)
{

     Wake();
    
     for (int i = 0; i < layers.size(); i++)
     {
          cout<<layers.size()<<endl;
        
          if(i == 0)
          {  
               cout<<"kwo stara purwia pyr"<<endl;
               layers[i].Forward(inputs);           
               layers[i].Activation();
               

          }
          else if(i == layers.size() - 1)
          {
               
               layers[i].Forward(layers[i - 1].nodeArray);
          }
          else
          {
               cout<<"moq greshaka ne si chak takuv"<<endl;
               layers[i].Forward(layers[i - 1].nodeArray);
               layers[i].Activation();
          } 
         
     } 
      

     return(layers[layers.size() - 1].nodeArray);
}

