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
        	return value; 
        }
        int setValue(int v) { 
            value = v; 
        }

        string toString() { // Set symbols according to suit and return symbol and value
            int x;

            if(suit == "Clubs") 
                x = 0;
            else if(suit == "Hearts") 
                x = 1;
            else if(suit == "Spades")    
                x = 2;
            else if(suit == "Diamonds")
                x = 3;

            if(value == 11)
               return symbols[x] + " " + "Ace";
            else if(value == 12)
                return symbols[x] + " " + "Jack";
            else if(value == 13)
                return symbols[x] + " " + "Queen";
            else if(value == 14)
                return symbols[x] + " " + "King";

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
                for (int j = 2; j < 15; j++)
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
    bool won = false;
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
    int aces = 0;
    int value = 0;

        for(int i = 0; i<playerV[x].hand.size(); i++) {

            value = playerV[x].hand[i].getValue();

            if(value > 11)
                playerScore += 10;
            else
                playerScore += value; 
            
            if(value == 11)
                aces++;

            while(playerScore > 21 && aces != 0) {
                playerScore -= 10;
                aces--;
            }

            if(playerScore > 21)
                playerV[x].busted = true;
        }          
        return playerScore; 
}

void decision(vector<player> &playerV, Deck &deck) { // Player decides if (s)he wants to stand or hit

    string x;
    int i = 0; 
    int playerScore = 0;

    while(i<playerV.size() - 1){

        do 
        {   
            if(playerV[i].busted || playerV[i].won == true) { // Player is busted or has won, go to next player
                i++;
                break;
            }
            writeHand(playerV, i);
            playerScore = score(playerV, i);

            if(playerScore == 21) {
                cout << playerV[i].name << "  You won!" << endl;
                playerV[i].won = true;
            }
            else {
                cout << playerV[i].name << "     Score: " << playerScore << "     (s)tand or (h)it?" << endl;
                cin >> x;
            }
        }while(x != "s" && x != "h"); // Do while player doesn't press s or h

        if(x == "h" && playerV[i].won != true) { // Player hits, deal card
            playerV[i].hand.push_back(deck.drawCard());
            playerScore = score(playerV, i);

            if(playerScore == 21 && playerV[i].won != true) {
                cout << playerV[i].name << "  You won!" << endl;
                playerV[i].won = true;
            }
            if(playerV[i].busted && playerV[i].won != true) { // Check if player is busted after hit
                writeHand(playerV, i);
                cout << playerV[i].name << " is busted" << "     Score: " << playerScore << endl;
                i++; // Busted, go to next player
            }
        }
        if(x == "s") // Player stands, go to next player
            i++;
        playerScore = 0;
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
