#include <iostream> 
#include "cards.h"
#include <string>
#include <cctype>
#include <ctype.h>
#include <cstdio>
#include <fstream> 

using namespace std; 

int main(int argv, char** argc){
   if(argv != 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }    

  Player p1 ("Alice", 0);
  Player p2 ("Bob", 0);

  Hand* h1 = new Hand();
  Hand* h2 = new Hand();


  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail()){
    cout << "Could not open file " << argc[1];
    return 1;
  }

  if (cardFile2.fail()){
    cout << "Could not open file " << argc[2];
    return 1;
  }

//  cout<<p1.getName()<<"'s cards: "<<endl;
  while (getline (cardFile1, line) && (line.length() > 0)){
   //make the card bois here
         string suit (1,line[0]);
	 string name (1,line[2]);
	 Cards c (suit, name);
	 h1->append(c);
  }
  cardFile1.close();

 // cout<<endl;

//  cout<<p2.getName()<<"'s cards: "<<endl;
  while (getline (cardFile2, line) && (line.length() > 0)){
   //make card boi here
    string suit (1, line[0]);
    string name (1, line[2]);
    Cards c (suit,name);
    h2->append(c);
  }
  cardFile2.close();


  // Start the game

  //By now, we have two cloOnKEd lists (linked lists but i just like saying it like that)
  //and they are of hand type. now lets add each hand to the player

  p1.setHand(h1);
  p2.setHand(h2);

  int playerToTest = 1; 
  
     Node* stIterator = p2.getHand().getMin(p2.getHand().root);
     Node* refIterator = p1.getHand().getMin(p1.getHand().root); 

  while( p2.getHand().getSuccessor( stIterator->info ) != 0 && p1.getHand().getSuccessor(refIterator->info)) {
  
  if(playerToTest==1){ 
     stIterator = p2.getHand().getMin(p2.getHand().root);
     refIterator = p1.getHand().getMin(p1.getHand().root); 
     cout<<"Starting the game. Checking mins: "<<refIterator->info.suit<<","<<refIterator->info.cardNumber<<endl;  
     cout<<"and the other one is: "<<stIterator->info.suit<<","<<stIterator->info.cardNumber<<endl;
     //check while they both have a successor aka, we are not at the end of the BST
     while( p2.getHand().getSuccessor( stIterator->info ) != 0 && p1.getHand().getSuccessor(refIterator->info)) {
     //checkInOrder will return a boolean if the currently   
     cout<<"i'm in the first while"<<endl; 
     if( p1.checkInOrder(stIterator, refIterator) ){
       //if they matched, remove them both
       cout<<"there was a match found"<<endl;  
       p1.getHand().remove(stIterator, stIterator->info); 
       p2.getHand().remove(refIterator, refIterator->info); 
       //then switch the player 
       playerToTest = 2; 
       //now break out of loop 
       break;        
      } 
       //if they were not the same, move on the stIterator 
       cout<<"nothing found, increasing the iterator"<<endl; 
       stIterator = p2.getHand().getSuccessor( stIterator->info );
     }//end of while 
  }//end of if player to test is 1
  
  if(playerToTest==2){  
     Node* stIterator = p1.getHand().getMin(p1.getHand().root);
     Node* refIterator = p2.getHand().getMin(p2.getHand().root);

     //check while they both have a successor aka, we are not at the end of the BST
     while(p1.getHand().getSuccessor(stIterator->info) != 0 && p2.getHand().getSuccessor(refIterator->info) ) {
     //checkInOrder will return a boolean if the currently   
     if( p2.checkInOrder(stIterator, refIterator) ){
       //if they matched, remove them both 
       p1.getHand().remove(stIterator, stIterator->info); 
       p2.getHand().remove(refIterator, refIterator->info); 
       //then switch the player 
       playerToTest = 1; 
       //now break out of loop 
       break;        
      }
       //if they were not the same, move on the stIterator 
       stIterator = p1.getHand().getSuccessor(stIterator->info);
     }//end of while
   }//end of if player to test is 2 
     refIterator = p2.getHand().getSuccessor(refIterator->info);
  }//end of big while 

  p1.printInOrder();  
  p2.printInOrder();

  return 0; 

  }

