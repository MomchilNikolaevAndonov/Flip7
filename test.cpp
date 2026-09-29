#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;

int main()
{
      vector<int> rep_cards;
    cout<<"ti si pederas";
    rep_cards.push_back(1);   
     cout<<"ti si pederas";
    for (int i = 1; i < 14; i++)
        {
         rep_cards.push_back(i);         
        };

      for(int i : rep_cards)
      {
        cout<<i;
      }
   
    return 0;
}
