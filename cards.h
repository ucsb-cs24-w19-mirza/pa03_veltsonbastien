//Veltson Bastien 
//Feb 28, 2019 

#ifndef CARDS_H
#define CARDS_H 

#include <string> 
using namespace std; 


class Cards{
 private:
      string suit; 
      string cardNumber; 

 public: 
      Cards(); 
      Cards(string s, string cn);
      string getSuit(); 
      string getCardNumber();  

friend bool operator== (Cards& c1, Cards& c2);	

}; 

      struct Node {
      int info;
      Node *left, *right, * parent;
      // useful constructor (from lab04):
      Node(int v=0) : info(v), left(0), right(0), parent(0) { }
      };
  

class Hand{
 public: 
	 Hand(); 
	 ~Hand(); 
	 void append(Cards c); 
	 void remove(Cards c); 
	 int length(); 

	 Node* root; 
}; 

class Player{
 private:
   string playerName;
   int currentCounter;
   Hand playerHand;

 public:
   Player(); //constructor
   Player(string pN, int cC); //paremetrized
   string getName();
   int getCounter();
   Hand getHand();
   void setName(string s);
   void setCounter(int counter);
   void setHand(Hand* h);
   friend std::ostream& operator<<(std::ostream& os, const Player& player);
};
#endif


