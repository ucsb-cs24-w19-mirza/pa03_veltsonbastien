#ifndef UTILITY_H
#define UTILITY_H 

#include <string> 
using namespace std; 


//what will be used for the tests 

void assertEquals(double expected, 
		  double actual, 
		  std::string message="");
#define ASSERT_EQUALS(expected,actual) assertEquals(expected,actual,#actual)


void assertEquals(string expected, 
		  string actual, 
		  std::string message="");


void startTestGroup(std::string name);

#define START_TEST_GROUP(name) startTestGroup(name)


