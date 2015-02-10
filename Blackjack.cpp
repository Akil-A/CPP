#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

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
            return value = v; 
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
            mt19937 generator (time(0));
            std::shuffle(deck.begin(), deck.end(), generator); 
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
    double money;
    int bet = 0;
    bool busted = false;
    bool won = false;
    bool standOut = false;
    bool isBet = false;
    bool blackjack = false;
    vector<Card> hand;
};

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

            if(playerScore == 21 && playerV[x].hand.size() == 2)
                playerV[x].blackjack = true;
        }          
        return playerScore; 
}

void writeHand(vector<player> &playerV, int x) { // Writes players hand
     int playerScore = score(playerV, x);
     cout << "==============================================" << endl;
     cout << playerV[x].name  << " ";

     for(int i = 0; i<playerV[x].hand.size(); i++)
        cout << playerV[x].hand[i].toString() << " ";
    
    cout << " Score: " << playerScore << endl << "==============================================" << endl;
}

void bet(vector<player> &playerV) {

    int playerBet = 0;
    string s;

    for(int i = 0; i<(playerV.size()-1); i++) {

        do
        {
            cout << endl << playerV[i].name << " bet from 1 to " << playerV[i].money << " or (s)tand out" << endl;
            cin >> playerBet;
            if (cin.fail()) {
                cin.clear();
                cin >> s;
            }
            cout << endl;
        }while( (playerBet < 1 || playerBet > playerV[i].money) && (s != "s") );

        if(s == "s")
            playerV[i].standOut = true;

        if(playerBet != 0) {
            playerV[i].bet = playerBet;
            playerV[i].money -= playerBet;
            playerV[i].isBet = true;
        }
    }
}

void dealer(vector<player> &playerV, Deck &deck) {

    while( score(playerV, playerV.size()-1) < 17)
        playerV[playerV.size()-1].hand.push_back(deck.drawCard());

    writeHand(playerV, playerV.size()-1);
}

void whoWon(vector<player> &playerV, Deck &deck) {

    dealer(playerV, deck);
    int dealerScore = score(playerV, playerV.size()-1);
    int dealerI = playerV.size()-1;

    if(playerV[dealerI].blackjack) {
        cout << "Dealer has blackjack" << endl;
        for(int i = 0; i<(playerV.size()-1); i++) {

            if(!playerV[i].busted && !playerV[i].isBet && !playerV[i].standOut) {
                playerV[i].money -= playerV[i].bet;
                cout << playerV[i].name << " has lost " << playerV[i].bet << endl;
                playerV[i].busted = true;
            }
        }
    }else if(dealerScore > 21) {
        cout << "Dealer busted" << " Score: " << dealerScore << endl;
        for(int i = 0; i<(playerV.size()-1); i++) {

            if(!playerV[i].won && !playerV[i].busted && playerV[i].isBet && !playerV[i].standOut) {
                playerV[i].won = true;
                playerV[i].money += (playerV[i].bet * 2);
                cout << "*** " << playerV[i].name << " has won " << (playerV[i].bet * 2) << " chips***" << endl;
            }
        }
    }else{
        for(int i = 0; i<(playerV.size()-1); i++) {

            if( (score(playerV,i) < dealerScore) && dealerScore <= 21 && !playerV[i].standOut && playerV[i].isBet && !playerV[i].won && !playerV[i].busted){
                cout << "***" << playerV[i].name << " lost " << playerV[i].bet << " chips***" << endl;
                playerV[i].busted = true;
            }else if(score(playerV,i) == dealerScore && !playerV[i].standOut && playerV[i].isBet && !playerV[i].won && !playerV[i].busted) {
                cout << playerV[i].name << " has drawn, you will get your money back" << endl;
                playerV[i].money += playerV[i].bet;
            }else if( (score(playerV,i) > dealerScore) && !playerV[i].won && !playerV[i].standOut && playerV[i].isBet && !playerV[i].busted){
                cout << "***" << playerV[i].name << " won " << (playerV[i].bet * 2) << " chips***" << endl;
                playerV[i].won = true;
                playerV[i].money += (playerV[i].bet * 2);
            }
        }
    }
}

void decision(vector<player> &playerV, Deck &deck) { // Player decides if (s)he wants to stand or hit

    string x;
    int i = 0; 
    int playerScore = 0;
    int dealerScore = score(playerV, playerV.size()-1);

    while( i<(playerV.size()-1) ){
        do 
        {   
            cout << playerV[playerV.size()-1].name << " " << playerV[playerV.size()-1].hand[0].toString() << " ?" << endl;
            writeHand(playerV, i);
            playerScore = score(playerV, i);
            
            if(playerV[i].blackjack) { 
                cout << "====== " << playerV[i].name << "  You have Blackjack!" << " You won " << (playerV[i].bet*1.5) << " chips" << " ======" << endl << endl; 
                playerV[i].money += (playerV[i].bet*1.5);
                playerV[i].won = true;
                i++;
            }else if(playerScore == 21 && !playerV[i].won) {
                cout << playerV[i].name << " has 21 score and stands auto" << endl;
                x = "s";
            } else if(!playerV[i].won){
                cout << playerV[i].name << " (s)tand or (h)it?" << endl;
                cin >> x;
                cout << endl;
            }
        }while(x != "s" && x != "h"); // Do while player doesn't press s or h

        if(x == "h" && !playerV[i].won) { // Player hits, deal card
            playerV[i].hand.push_back(deck.drawCard());
            playerScore = score(playerV, i);

            if(playerV[i].busted && !playerV[i].won && playerV[i].name != "Dealer") { // Check if player is busted after hit
                writeHand(playerV, i);
                playerV[i].busted = true;
                cout << playerV[i].name << " is busted and has lost " << playerV[i].bet << " chips" << endl << endl;
                i++;
            }
        }
        if(x == "s")
            i++;
        playerScore = 0;
    }
}


vector<player> playerV; // Vector of Players

void start() {

  Deck deck;
  deck.shuffle();

    for(int i = 0; i<playerV.size(); i++){          //**********  
        playerV[i].hand.push_back(deck.drawCard()); //
    }                                               // 
                                                    // Deal two cards to everyone clockwise
    for(int i = 0; i<playerV.size(); i++){          //
        playerV[i].hand.push_back(deck.drawCard()); //
    }                                               //**********
    bet(playerV);                                     
    decision(playerV, deck);
    whoWon(playerV, deck);  
}

void reset(vector<player> &playerV) {
    string x;

      do
      {
        cout << endl << "Play more? (y)es, (n)o" << endl;
        cin >> x;
        if(x == "y") {
            
            for(int i = 0; i<playerV.size(); i++) {
                playerV[i].bet = 0;
                playerV[i].busted = false;
                playerV[i].won = false;
                playerV[i].standOut = false;
                playerV[i].isBet = false;
                playerV[i].hand.clear();
            }
        start();
        }          
    }while(x == "y");
}

 int main() {
  
  int players;

  cout << endl << "######### Welcome to Blackjack #########" << endl << endl;
  
  do { 
    cout << "Enter number of players (1-7): ";
    cin >> players;
    }while(players < 1 || players > 7);

    for(int i = 0; (i<players+1); i++) // Make new Players, last Player is Dealer
        playerV.push_back(player());

    for(int i = 0; i<players; i++) { // Set Players name and money
        playerV[i].name = "Player" + to_string(i+1);
        playerV[i].money = 150; 
    }

    playerV[playerV.size()-1].name = "Dealer"; // Set name for Dealer

    start();
    reset(playerV);
 }
