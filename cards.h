//Veltson Bastien 
//Feb 28, 2019 

#ifndef CARDS_H
#define CARDS_H 

#include <string> 
using namespace std; 


class Cards{
 public:
      string suit; 
      string cardNumber;  
      Cards(); 
      Cards(string s, string cn);
      string getSuit(); 
      string getCardNumber();  

friend bool operator!= (Cards& c1, Cards& c2); 
friend bool operator== (Cards& c1, Cards& c2);	
friend bool operator<  (Cards& c1, Cards& c2); 
friend bool operator<  (Cards& c1, Cards& c2); 
friend bool operator>  (Cards& c1, Cards& c2); 
}; 

      struct Node {
      Cards info;
      Node *left, *right, * parent;
      // useful constructor (from lab04):
      Node(Cards card) : info(card), left(0), right(0), parent(0) { }
      };

class Hand{
 public: 
	 Hand(); 
	 ~Hand(); 
	 bool append(Cards c); 
	 bool append(Cards c, Node* n); 
	 Node* remove(Node* n, Cards c); 
	 int length(); 
         void clear(Node* n); 
         Node* getNodeFor(Cards c, Node*n) const; 
	 Node* getSuccessor(Cards c) const;   // returns the Node containing the successor of the given value
 //default root node
	 Node* root; 
}; 


class Player{
 public:
   string playerName;
   int currentCounter;
   Hand playerHand;
   Player(); //constructor
   Player(string pN, int cC); //paremetrized
   string getName();
   int getCounter();
   Hand getHand() const;
   void setName(string s);
   void setCounter(int counter);
   void setHand(Hand* h);	
   void printInOrder() const;
   void printInOrder(Node* n) const; 	 
}; 

#endif

