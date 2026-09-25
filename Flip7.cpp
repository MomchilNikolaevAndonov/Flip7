#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

class Players{
    int cards[92];
    int score;

public:
    Players() : score(0) {
        for(int i = 0; i < 92; i++) {
            cards[i] = 0;
        }
    }

    void getCards(int card){
        cards[0] = card;
    }

    void calc_score(){
        int value = 0;
        for(int i = 0; i < sizeof(cards)/sizeof(cards[0]); i++){
            value += cards[i];
        }
        score += value;
    }

    bool check_lose(){
    
        int n = 92;

        // Sort the input array
        sort(cards, cards + n);

        // Iterate through the sorted array
        for (int i = 1; i < n; ++i) {

            // Check if adjacent elements are equal
            if (cards[i] == cards[i - 1])
                return true;
        }
        return false;
   }

    int print(int index)
    {
        return cards[index];
    }

};



void ramdomize(int cards[]){


    random_device rd;

    // 2. Initialize the standard Mersenne Twister engine with the seed
    mt19937 g(rd());

    // 3. Shuffle the array
    shuffle(cards, cards + 92, g);
}

void make_deck(int cards[]){
    int count = 1;
    for (int i = 1; i < 14; i++)
    {
        for (int j = 0; j < i; j++)
        {
            cards[count] = i;
            count++;
        }
    }

}




int main()
{
    const int n_players = 4;
    
    int cards[92] = {0};
    int card_index = 0;
    Players players[n_players];

    make_deck(cards);
    for (int i = 0; i < n_players; i++)
    {
        players[i].getCards(cards[card_index]);
        card_index++;
    }

       for (int i = 0; i < n_players; i++)
    {
        cout << players[i].print(0) << " ";
        card_index++;
    }



    //give each player a card
    //ask if they want to get another card
    //draw till they say no or they lose
    //calculate score
    //check if they have won

    return 0;
}