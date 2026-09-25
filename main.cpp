#include <iostream>
#include <vector>
using namespace std;


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


vector<int> networkShape = {2, 3, 1};
vector<Layer> layers;

vector<float> Brain(vector<float> inputs)
{

     for (int i = 0; i < layers.size(); i++)
     {
          if(i == 0)
          {
               layers[i].Forward(inputs);
               layers[i].Activation();
          }
          else if(i == layers.size() - 1)
          {
               layers[i].Forward(layers[i - 1].nodeArray);
          }
          else
          {
               layers[i].Forward(layers[i - 1].nodeArray);
               layers[i].Activation();
          }
     }
     

     return(layers[layers.size() - 1].nodeArray);
}


int main()
{
     for (int i = 0; i < networkShape.size() - 1; i++)
     {
         layers.emplace_back(
             networkShape[i],
             networkShape[i + 1]
         );
     }
    return 0;
}

