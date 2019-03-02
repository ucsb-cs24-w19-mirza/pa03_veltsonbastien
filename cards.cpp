#include <iostream> 
#include "cards.h" 
#include "utility.h" 


using std::cout; 

//********** CARD ********** // 

//Default Constructor: 
Cards::Cards(){} 

//Parametrized Constructor: 
   Cards::Cards(string s, string cn){
    suit = s; 
    cardNumber = cn; 
   }

//Getters: 
  string Cards::getSuit(){
   return suit; 
  }

  string Cards::getCardNumber(){
    return cardNumber;
   }

//Overloaded != operator: 
  bool operator!= (Cards& c1, Cards& c2){
          return (c2.suit == c2.suit && (c1.cardNumber == c2.cardNumber)); 
  }


//Overloaded == operator:  
  bool operator== (Cards& c1, Cards& c2){
	  return (c1.suit == c2.suit && (c1.cardNumber == c2.cardNumber));
  }


//Overloaded < operator:  
  bool operator< (Cards& c1, Cards& c2){
	  return (c1.suit < c2.suit && (c1.cardNumber < c2.cardNumber));
  }


//Overloaded <= operator:  
  bool operator<= (Cards& c1, Cards& c2){
	  return (c1.suit <= c2.suit && (c1.cardNumber <= c2.cardNumber));
  }

//Overloaded > operator:  
  bool operator> (Cards& c1, Cards& c2){
	  return (c1.suit > c2.suit && (c1.cardNumber > c2.cardNumber));
  }

//********** HAND ********** //

//Constructor: 
Hand::Hand():root(0){} 

//Destructor: 
Hand::~Hand(){
 clear(root); 
}

// recursive helper for destructor
void Hand::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}


//append() function for special case: 
bool Hand::append(Cards c){
    // handle special case of empty tree first
    if (!root) {
	root = new Node(c);
	return true;
    }
    // otherwise use recursive helper
    return append(c, root);	
}


//append() function after special case handled : 
bool Hand::append(Cards c, Node* n){
    if (c == n->info)
	return false;
    if (c < n->info) {
	if (n->left)
	    return append(c, n->left);
	else {
	    n->left = new Node(c);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return append(c, n->right);
	else {
	    n->right = new Node(c);
	    n->right->parent = n;
	    return true;
	}
    }  
}


//remove() function 
Node* Hand::remove(Node* n, Cards c){
   if(n == NULL) return root; 
   if(c < n->info) 
	   n->left = remove(n->left, c); 
   else if(c > n->info)
	   n->right = remove(n->right, c); 
   else{
     if(n->left == NULL){
       Node* temp = n->right; 
       free(root); 
       return temp; 
     }//end of if left == null 
     else if(n->right == NULL){
       Node* temp = n->left; 
       free(root); 
       return temp; 
     }//end of if right == null 
     Node* temp = getSuccessor(n->right->info); 
     n->info = temp->info; 
     n->right = remove(n->right, temp->info); 
   } //end of else 
   return n; 
}//end of remove 

Node* Hand::getNodeFor(Cards c, Node* n) const{
    //edge case 
    if(n==NULL) return n; 
    //if they're the same, return root 
    else if(n->info == c) return n;
    //check if we need to continue down the left side  
    else if(c <= n->info) return getNodeFor(c, n->left); 
    //or check if we need to continue down the right side
    else return getNodeFor(c, n->right); 
}

Node* Hand::getSuccessor(Cards c) const{
      Node* n = getNodeFor(c,root); 
      Node* temp = 0; 
      if(n->right != NULL){
        temp = n->right; 
	while(temp->left != NULL){
          temp = temp->left; 
	}//end of while 
	return temp; 
      } else{
        Node* temp2 = root; 
	Node* n2 = getNodeFor(c, root); //512 
	while(temp2->info != n2->info){
         if(n2->info <= temp2->info){
	  temp = temp2; 
	  temp2 = temp2->left; 
	 }//end of if check 
	  else{
           temp2 = temp2->right;
	  }
	}//end of second while 
         return temp; 	
      }
      return root;  
}


//********** PLAYER ********** // 

 Player::Player(string pn, int cc){
     playerName = pn;
     currentCounter = cc;
   }

   //member functions

   void Player::setName(string s){
     playerName = s;
   }//end of s

   void Player::setCounter(int counter){
    currentCounter = counter;
   }

   void Player::setHand(Hand* h){
    playerHand = *h;
   }

   string Player::getName(){
    return playerName;
   }

   int Player::getCounter(){
    return currentCounter;
   }

   Hand Player::getHand() const{
    return playerHand;
   }

 void Player::printInOrder() const {
    printInOrder(getHand().root);
 }

 void Player::printInOrder(Node* n) const {
    //check the edge cases first 
    if(n!=NULL){
      if(n->left){
        printInOrder(n->left); 
      }//end of n-left
         cout<<n->info.suit<<" "<<n->info.cardNumber; 
      if(n->right){
        printInOrder(n->right); 
      }//end of n-right
    }//end of null check     
 }

