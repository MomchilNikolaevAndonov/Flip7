#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;




class Players{
private:
    vector<int> cards;
    
public://not suposted to be public 
    bool lose = false;  
    bool round_end = false;
    int score;

public:
    Players() : score(0), cards(vector<int>()) {}

    void getCards(int card){
        cards.push_back(card);
    }

    void calc_score(){

        int value = 0;
        for(int i = 0; i < cards.size(); i++){
            value += cards[i];
        }
        score += value;
    }

    bool check_lose(){

        // Sort the input array
        sort(cards.begin(), cards.end());

        // Iterate through the sorted array
        for (int i = 1; i < cards.size(); ++i) {

            // Check if adjacent elements are equal
            if (cards[i] == cards[i - 1]){
             round_end = true;
             return  round_end;// Set round_end to true if duplicate found
            }

        }
        // Set round_end to true if no duplicates found
         return false;  // No duplicates, player does not lose
    }


    void reset(){
        round_end = false;
        cards.clear();
    }

    void print_cards(int n){
        cout << "Cards: ";
        for(int i = 0; i < cards.size(); i++){
            cout << cards[i] << " ";
        }
        cout << endl;
        cout  << "Points this round: " << score;
        cout << endl;

    }

    bool player_decision(int n){
        char decision;
        cout <<  "Do you want to draw another card? (y/n): ";
        cin >> decision;

        if (decision == 'n' || decision == 'N') {
            round_end = true;
            return round_end;
        }
        else if (decision == 'y' || decision == 'Y') {
            round_end = false;
            return round_end;
        }
        else {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
            return player_decision(n); // Recursively ask again
        }
    }


};

class Game{
    
public:
    int deck[92];
    bool game_end(int n_players, Players players[]){
    for (int i = 0; i < n_players; i++)
        {
            if (players[i].score >= 200) {
                return true;
            }
        }
        return false;
    }

    
    void make_deck(){
        int count = 1;
        for (int i = 1; i < 14; i++)
        {
            for (int j = 0; j < i; j++)
            {
                deck[count] = i;
                count++;
            }
        };
    }

    
    void resuffle(int cards[]){


    random_device rd;

    // 2. Initialize the standard Mersenne Twister engine with the seed
    mt19937 g(rd());

    // 3. Shuffle the array
    shuffle(cards, cards + 92, g);
    }

    
};






bool end_round(int n_players, Players players[]){

    for (int i = 0; i < n_players; i++)
    {
        if (!players[i].round_end) {
            return false;
        }
       
    }
    return true;
}



int main()
{
    const int n_players = 4;
    
    int card_index = 0;
    Game game;
    Players players[n_players];
    game.make_deck();  
    game.resuffle(game.deck);
    card_index = 0;

    

    // Game process  
    do{
       
        
        for (int i = 0; i < n_players; i++) {
            players[i].reset();
        }
         for (int i = 0; i < n_players; i++) {

            players[i].getCards(game.deck[card_index]);
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

                //print the cards and ask if they want to draw another card
                players[i].print_cards(i);
                if (!players[i].player_decision(i)) {
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


    //give each player a card
    //ask if they want to get another card
    //draw till they say no or they lose
    //calculate score
    //check if they have won
    cout << "Final Scores: " << endl;
    for (int i = 0; i < n_players; i++)
    {
        cout << "Player " << i + 1 << ": " << players[i].score << endl;
    }
    cout << "Game Over!" << endl;
    return 0;
}
