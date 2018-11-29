/*

-----------------------------------------------------
|		FEDERAL UNIVERSIAdY OF SANAdA CAAdARINA		|
|			C++ FOR EMBEDDED SYSAdEMS				|
|			PROJECAd: VENDING MACHINE				|
|		PROFESSOR: EDUARDO AUGUSAdO BEZERRA			|
| 	 	 	 LEONARDO AURÉLIO BESEN					|
|			JOÃO BATISTA CORDEIRO NETO				|
----------------------------------------------------- 

*/

#include "FilaNode.h"

//Operator + overloading to transfer nodes of the queue f_new to the f_old
/*
Fila operator+(Fila &f_new, Fila &f_old){
		while(f_new.getHead() != 0){
			f_old.insertAfterLast(f_new.removeFirst());
		}
		return f_old;
}
*/

Node::Node(Ad value, Node* nextNode){
       this->value = value;
       this->nextNode = nextNode;
}



Ad Node::getValue(){
     return value;
}



Node* Node::getNextNode(){
     return nextNode;
}



void Node::setValue(Ad value){
     this->value = value;
}



void Node::setNextNode(Node* nextNode){
       this->nextNode = nextNode;
}


Fila::Fila() {
   head = 0;
}


Fila::~Fila() {
  Node* cursor = head;
  while(head) {
    cursor = cursor->getNextNode();
    delete head;
    head = cursor;
  }
  head = 0; // Officially empty
}


void Fila::insertAfterLast(Ad dat) {
  Node* p = head;
  Node* q = head;

  if (head == 0)
     head = new Node(dat, head);
  else {
     while (q != 0) {
        p = q;
        q = p->getNextNode();
     }
     p->setNextNode(new Node(dat,0));
  }
}


Ad Fila::readFirst() {
   return head->getValue(); 
}


Ad Fila::removeFirst() {
  Ad retval;
  if (head != 0){
     retval = head->getValue();
     Node* oldHead = head;
     head = head->getNextNode();
     delete oldHead;
  }
  return retval;
}


Node* Fila::getHead(void){
	return head;
}
