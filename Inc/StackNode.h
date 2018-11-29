#ifndef STACK_NODE_H
	#define STACK_NODE_H

#include "Logs.h"

/*
Node class to be user in the stack
It has an value of Logs type and the nextNode that points to the next Node
*/

class Node_S {

    Logs value;
    Node_S* nextNode;
    
  public:  
  	   
    Node_S(Logs value, Node_S* nextNode);
    Logs getValue();
    Node_S* getNextNode();
    void setValue(Logs value);
    void setNextNode(Node_S* nextNode);
    
};
/*
Stack class to store the logs in a stack
*/

class Stack {

  Node_S* head;

public:
  Stack();
  ~Stack();
  void insertFirst(Logs dat);
  Logs readFirst();
  Logs removeFirst();
  Node_S* getHead(void);
};
#endif
