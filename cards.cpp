//cards.cpp
//Authors: Veltson Bastien

#include "cards.h"
#include <iostream>

using namespace std;

Card::Card(char s, string v) {
        suit = s;
        value = v;
}

Card::Card(const Card& c) {
        suit = c.getSuit();
        value = c.getCardNumber();
}

char Card::getSuit() const {
        return suit;
}

string Card::getCardNumber() const {
        return value;
}

bool operator==(const Card& c1, const Card& c2) {
        return (c1.getSuit() == c2.getSuit() && c1.getCardNumber() == c2.getCardNumber());
}

bool operator<(const Card& c1, const Card& c2) {
        int s1 = 0, s2 = 0;
        s1 = c1.orderCard();
        s2 = c2.orderCard();
        return s1 < s2;
}

bool operator>(const Card& c1, const Card& c2) {
        return !(c1 < c2);
}

ostream& operator<<(ostream& stream, const Card& card) {
        stream << card.getSuit() << " " << card.getCardNumber();
        return stream;
}

int Card::orderCard() const {
        int num = 0;
        char s = getSuit();
        if(s == 'c') num += 100;
        else if(s == 'd') num += 200;
        else if(s == 's') num += 300;
        else if(s == 'h') num += 400;

        string v = getCardNumber();
        if(v == "a") num += 1;
        else if(v == "2") num += 2;
        else if(v == "3") num += 3;
        else if(v == "4") num += 4;
        else if(v == "5") num += 5;
        else if(v == "6") num += 6;
        else if(v == "7") num += 7;
        else if(v == "8") num += 8;
        else if(v == "9") num += 9;
        else if(v == "10") num += 10;
        else if(v == "j") num += 11;
        else if(v == "q") num += 12;
        else if(v == "k") num += 13;

        return num;
}

Hand::Hand(string namepass) {
        name = namepass;
}

Hand::~Hand() {
        Node *n = find(getSmallestCard());
        while(n) {
                Node *r = n;
                n = successor(n);
                remove(r->value);
        }
}

Card* Hand::getNextCard(Card *c) const {
        Node *n = find(c);
        Node *ne = successor(n);
        if(ne) return ne->value;
        else return nullptr;
}

Card* Hand::getPrevCard(Card *c) const {
        Node *n = find(c);
        Node *ne = predecessor(n);
        if(ne) return ne->value;
        else return nullptr;
}

void Hand::printInorder() const {
        printInorder(root);
}

bool Hand::contains(Card *c) const {
        Node *n = find(c);
        return n != nullptr;
}

Card* Hand::getSmallestCard() const {
        Node *t = root;
        while(t->left) {
                t = t->left;
        }
        return t->value;
}

Card* Hand::getLargestCard() const {
        Node *t = root;
        while(t->right) {
                t = t->right;
        }
        return t->value;
}

string Hand::getName() const {
        return name;
}

void Hand::remove(Card *c) {
        Node* n = find(c);

        if(!n) {
                return;
        }

        Node* parent = n->parent;
        if(parent) {
                if(!n->left) {
                        if(parent->right == n) {
                                parent->right = n->right;
                        } else {
                                parent->left = n->right;
                        }
                        if(n->right) {
                                n->right->parent = parent;
                        }
			//delete n->value;
                        //delete n;
                       	return;
                } else if (!n->right) {
                        if(parent->left == n) {
                                parent->left = n->left;
                        } else {
                                parent->right = n->left;
                        }
                        if(n->left) {
                                n->left->parent = parent;
                        }
			//delete n->value;
                        //delete n;
                        return;
                }

                //Two children
                Node* succ = successor(n);
                remove(succ->value);
                n->value = succ->value;
        } else {
                //ROOT
                //One child or none
                if(!n->left) {
                        root = n->right;
                        if(root) root->parent = nullptr;
                        //delete n->value;
                        //delete n
            		return;
                } else if (!n->right) {
                        root = n->left;
                        if(root) root->parent = nullptr;
                        ///delete n->value;
                        //delete n;
			return;
                }
                //Two children
                Node* succ = successor(n);
                remove(succ->value);
                n->value = succ->value;
        }

        return;
}

void Hand::insert(Card *c) {
        if (!root) {
                root = new Node(c);
        } else {
                insert(c, root);
        }
}

ostream& operator<<(ostream& stream, const Hand& hand) {
        stream << hand.name << "'s cards:" << endl;
        hand.printInorder();
        return stream;
}

void Hand::printInorder(Node* n) const {
        if (!n) return;
        printInorder(n->left);
        cout << *(n->value) << endl;
        printInorder(n->right);
}

void Hand::insert(Card* c, Node *n) {
        if (*c == *(n->value))
                return;

        if (*c < *(n->value)) {
                if (n->left)
                        return insert(c, n->left);
                else {
                        n->left = new Node(c);
                        n->left->parent = n;
                        return;
                }
        }
        else {
                if (n->right) {
                        return insert(c, n->right);
                }
                else {
                        n->right = new Node(c);
                        n->right->parent = n;
                        return;
                }
        }
}

Node* Hand::predecessor(Node *n) const {
        if(!n) return nullptr;

        if(*(getSmallestCard()) == *(n->value))
                return nullptr;

        if(n->left) {
                n = n->left;
                while(n->right) {
                        n = n->right;
                }
                return n;
        }

        Node *p = n->parent;
        while(p && p->left && *(n->value) == *(p->left->value)) {
                n = p;
                if(!p->parent) break;
                p = p->parent;
        }

        return p;
}

Node* Hand::successor(Node *n) const {
        if(!n) return nullptr;

        if(*(getLargestCard()) == *(n->value))
                return nullptr;

        if(n->right) {
                n = n->right;
                while(n->left) {
                        n = n->left;
                }
                return n;
        }

        Node *p = n->parent;
        while(p && p->right && *(n->value) == *(p->right->value)) {
                n = p;
                if(!p->parent) break;
                p = p->parent;
        }

        return p;
}

Node* Hand::find(Card *c) const {
        if(!root) {
                return nullptr;
        }
        return search(root, c);
}

bool isCard(Card *c){
  return c->getSuit() == 's' && c->getCardNumber() == "q";
}

Node* Hand::search(Node* n, Card *c) const {
        if(!n) return nullptr;
        if(*(n->value) == *c) return n;
        if(*(n->value) < *c) return search(n->right, c);
        return search(n->left, c);
}

