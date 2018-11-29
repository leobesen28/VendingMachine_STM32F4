
#include "StackNode.h"

//Constructor
Node_S::Node_S(Logs value, Node_S* nextNode){
       this->value = value;
       this->nextNode = nextNode;
}
//get the node value
Logs Node_S::getValue(){
     return value;
}
//get the pointer to the next node
Node_S* Node_S::getNextNode(){
     return nextNode;
}
//set value
void Node_S::setValue(Logs value){
     this->value = value;
}
//set pointed to the next node
void Node_S::setNextNode(Node_S* nextNode){
       this->nextNode = nextNode;
}


//Constructor
Stack::Stack(){
   head = 0;
}

//Destructor
Stack::~Stack(){
  Node_S* cursor = head;
  while(head) {
    cursor = cursor->getNextNode();
    delete head;
    head = cursor;
  }
  head = 0; 
}

//Insert a new node in the first position of the stack
void Stack::insertFirst(Logs dat) {
  head = new Node_S(dat, this->head);
}

//read first element in the stack
Logs Stack::readFirst() {
   return head->getValue(); 
}

//remove first element in the stack
Logs Stack::removeFirst() {
  Logs retval;
  if (head != 0){
     retval = head->getValue();
     Node_S* oldHead = head;
     head = head->getNextNode();
     delete oldHead;
  }
  return retval;
}

//return pointer to the first element - head
Node_S* Stack::getHead(void){
	return head;
}
