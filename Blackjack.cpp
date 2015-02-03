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

        string toString() { 
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
    vector<Card> hand;
};



void play(){
  
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
        playerV[i].name = "Player" + (i+1);
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

    /*cout << "Name: " << playerV[playerV.size()-1].name << endl
    << "  Card1  " << playerV[playerV.size()-1].hand[0].toString() << endl
    << "  Card2  " <<  playerV[playerV.size()-1].hand[1].toString() << endl
    << "  Card1 Value:  " <<  playerV[playerV.size()-1].hand[0].getValue() << endl
    << "  Card2 Value:  " << playerV[playerV.size()-1].hand[1].getValue() << endl
    << endl;*/

    /*for(int x = 0; x<playerV.size(); x++) {
        player p = playerV[x];
        for(int i = 0; i<2; i++)
            cout << p.hand[i].toString();
    }*/
    /*vector<Card> d = deck.getDeck();
    for (int i = 0; i < d.size(); i++) cout << d[i].toString() << endl;*/

    


};

 int main() {

    /*Deck deck;
    deck.shuffle();
    Card c = deck.drawCard();
    cout << c.toString() << endl;*/
    play();
 }

