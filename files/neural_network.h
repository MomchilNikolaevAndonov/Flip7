#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include <iostream>
#include <vector>
using namespace std;


const vector<int> networkShape = {14, 14, 7, 1};
const float MutateChance = 0.5;
const float MutateAmount = 0.2;



class NN{  
    public:  

       NN();

    class Layer{
        private:
            int n_inputs;
            int n_nodes;

        public:
            vector<vector<float>> weightArrays;
            vector<float> biasesArray;
            vector<float> nodeArray;

        public:
            Layer(int n_inputs, int n_nodes);

            void MutateLayer(float, float);

            void Forward(vector<float>);

            void Activation();
        
   };

  
        vector<Layer> layers;
        vector<float> Brain(vector<float>);
        void clear_NN();
        void MutateNetwork(float, float);
 

};
#endif // NEURAL_NETWORK_H