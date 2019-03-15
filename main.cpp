#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

int main(int argv, char** argc){
        if(argv < 3) {
                cout << "Please provide 2 file names" << endl;
                return 1;
        }

        ifstream cardFile1 (argc[1]);
        ifstream cardFile2 (argc[2]);
        string line;

        if (cardFile1.fail() || cardFile2.fail() ) {
                cout << "Could not open file " << argc[2];
                return 1;
        }

        Hand *alice = new Hand("Alice");
        Hand *bob = new Hand("Bob");

        //Read each file
        while (getline (cardFile1, line) && (line.length() > 0)) {
                char suit = line[0];
                string val = line.substr(2);
                Card *c = new Card(suit, val);
                alice->insert(c);
        }
        cardFile1.close();


        while (getline (cardFile2, line) && (line.length() > 0)) {
                char suit = line[0];
                string val = line.substr(2);
                Card *c = new Card(suit, val);
                bob->insert(c);
        }
        cardFile2.close();
        
bool aliceTurn = true;
        Card *aliceCard = alice->getSmallestCard();
        Card *bobCard = bob->getLargestCard();
        while(aliceCard && bobCard) {
                if(aliceTurn) {
                        if(bob->contains(aliceCard)) {
                                cout << alice->getName() << " picked matching card " << *aliceCard << endl;
                                Card *t = alice->getNextCard(aliceCard);
                                if(*bobCard == *aliceCard) bobCard = bob->getPrevCard(bobCard);
                                bob->remove(aliceCard);
                                alice->remove(aliceCard);
                                aliceCard = t;
                                aliceTurn = !aliceTurn;
                        } else {
                                aliceCard = alice->getNextCard(aliceCard);
                        }
                } else {
                        if(alice->contains(bobCard)) {
                                cout << bob->getName() << " picked matching card " << *bobCard << endl;
                                Card *t = bob->getPrevCard(bobCard);
                                if(*aliceCard == *bobCard) aliceCard = alice->getNextCard(aliceCard);
                                alice->remove(bobCard);
                                bob->remove(bobCard);
                                bobCard = t;
                                aliceTurn = !aliceTurn;
                        } else {
                                bobCard = bob->getPrevCard(bobCard);
                        }
                }
        }

        cout << endl;
        cout << *alice << endl;
        cout << *bob;

        delete alice;
        delete bob;

        return 0;
}

