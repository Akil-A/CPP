#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

    string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    string symbols[4] = { "♠", "♥", "♣", "♦"};

class Card
{   
    private:
        string suit;
        int value;
 
    public:
        Card(string s, int v) { 
        	suit = s; value = v; 
        }

        string getSuite() { 
        	return suit; 
        }
        int getValue() { 
        	return value; }

        string toString() { // Set symbols according to suit and return symbol and value
            int x;

            if(suit == "Clubs") 
                x = 0;
            if(suit == "Hearts") 
                x = 1;
            if(suit == "Spades")    
                x = 2;
            if(suit == "Diamonds")
                x = 3;

            return symbols[x] + " " + to_string(value); 
        }       
};

class Deck 
{
private:
    vector<Card> deck;
    
    public:

       Deck() { // make deck

            for(int i = 0; i < 4; i++) 
                for (int j = 0; j< 13; j++)
                    deck.push_back(Card(suits[i],j));         
        }

        void shuffle(){
            
            srand(time(0));   
            random_shuffle(deck.begin(), deck.end()); 
        }

        Card drawCard(){

            Card c = deck.front(); 
            deck.erase(deck.begin());
            return c;
        }

        vector<Card> getDeck() {
            return deck;
        }
};

struct player {

    string name;
    int money;
    bool busted = false;
    bool hit = false;
    vector<Card> hand;
};

void writeHand(vector<player> &playerV, int x) { // Writes players hand

     cout << playerV[x].name  << " ";

     for(int i = 0; i<playerV[x].hand.size(); i++)
        cout << playerV[x].hand[i].toString() << " ";
    
    cout << endl;
}

int score(vector<player> &playerV, int x) { // Get players score and checks if player is busted

    int playerScore = 0;

        for(int i = 0; i<playerV[x].hand.size(); i++) {

            playerScore += playerV[x].hand[i].getValue(); 

            if(playerScore > 21)
                playerV[x].busted = true;
        }          
        return playerScore; 
}

void decision(vector<player> &playerV, Deck &deck) { // Player decides if (s)he wants to stand or hit

    string x;
    int i = 0; 

    while(i<playerV.size() - 1){

        do 
        {   
            if(playerV[i].busted) { // Player is busted go to next player
                i++;
                break;
            }
            writeHand(playerV, i);
            cout << playerV[i].name << "     Score: " << score(playerV, i) << "     (s)tand or (h)it?" << endl;
            cin >> x;
        }while(x != "s" && x != "h"); // Do while player doesn't press s or h

        if(x == "h") { // Player hits, deal card
            playerV[i].hand.push_back(deck.drawCard());

            if(playerV[i].busted) { // Check if player is busted after hit
                cout << playerV[i].name " is busted" << endl;
                i++; // Busted, go to next player
            }
        }

        if(x == "s") // Player stands, go to next player
            i++;
    }
}

void play() {
  
  Deck deck;
  deck.shuffle();
  int players;

  cout << "### Welcome to Blackjack ###" << endl << endl;
  cout << "How many players? (1-7)" << endl;
  
  do { 

    cout << "It's only place for 1-7 players" << endl;
    cout << "Enter number of players: ";
    cin >> players;
    }while(players < 1 || players > 7);

    vector<player> playerV; // Vector of Players

    for(int i = 0; i<players+1; i++) // Make new Players, last "Player" is Dealer
        playerV.push_back(player());

    for(int i = 0; i<players; i++) { // Set Players name and money
        playerV[i].name = "Player" + to_string(i+1);
        playerV[i].money = 150; 
    }

    playerV[playerV.size()-1].name = "Dealer"; // Set name for Dealer


    for(int i = 0; i<playerV.size(); i++){          //**********  
        playerV[i].hand.push_back(deck.drawCard()); //
    }                                               // 
                                                    // Deal two cards to everyone clockwise
    for(int i = 0; i<playerV.size(); i++){          //
        playerV[i].hand.push_back(deck.drawCard()); //
    }                                               //**********

    decision(playerV, deck);

};


 int main() {

    play();
 }
