//Veltson Bastien

#ifndef CARDS_H
#define CARDS_H

#include <iostream>
using namespace std;

class Card{
  public:
    Card(char s = 's', string v = "b");
    Card(const Card& c);
    char getSuit() const;
    string getCardNumber() const;
    friend bool operator ==(const Card& c1, const Card& c2);
    friend bool operator <(const Card& c1, const Card& c2);
    friend bool operator >(const Card& c1, const Card& c2);
    friend ostream& operator <<(ostream& stream, const Card& card);
  private:
    int orderCard() const;
    char suit;
    string value;
};

struct Node {
    Card* value = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    Node(Card *info) {
      this->value = info;
    }

    Node(Card *val, Node *left, Node *right, Node *parent) {
      this->value = val;
      this->left = left;
      this->right = right;
      this->parent = parent;
    }
};

class Hand{
  public:
    Hand(string namePass);
    ~Hand();
    Card* getNextCard(Card *c) const;
    Card* getPrevCard(Card *c) const;
    void printInorder() const;
    bool contains(Card *c) const;
    Card* getSmallestCard() const;
    Card* getLargestCard() const;
    string getName() const;
    void remove(Card *c);
    void insert(Card *c);
    friend ostream& operator <<(ostream& stream, const Hand& hand);
    
    private:
    void printInorder(Node *n) const;
    void insert(Card *c, Node *n);
    Node* predecessor(Node *n) const;
    Node* successor(Node *n) const;
    Node* find(Card *c) const;
    Node* search(Node *n, Card *c) const;

    Node* root = 0;
    string name;
};


#endif
 
