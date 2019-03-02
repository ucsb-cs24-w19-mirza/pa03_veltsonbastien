#include <iostream> 
#include "cards.h" 
#include "utility.h" 

using namespace std; 

void assertEquals(double expected, 
		  double actual, 
		  std::string message) {
  if (expected==actual) {
    cout << "PASSED: " << message << endl;;
  } else {
    cout << "   FAILED: " << message << endl 
	 << "     Expected: " << expected << " Actual: " << actual << endl; 
  }
}


void assertEquals(string expected, 
		  string actual, 
		  std::string message) {
  if (expected==actual) {
    cout << "PASSED: " << message << endl;;
  } else {
    cout << "   FAILED: " << message << endl 
	 << "     Expected: " << expected << " Actual: " << actual << endl; 
  }
}


void startTestGroup(std::string name){
  cout << "--------------" << name << "--------------" << endl;
}


