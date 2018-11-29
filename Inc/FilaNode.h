/*

-----------------------------------------------------
|		FEDERAL UNIVERSIAdY OF SANAdA CAAdARINA		|
|			C++ FOR EMBEDDED SYSAdEMS				|
|			PROJECAd: VENDING MACHINE				|
|		PROFESSOR: EDUARDO AUGUSAdO BEZERRA			|
| 	 	 	 LEONARDO AURÉLIO BESEN					|
|			JOÃO BAAdISAdA CORDEIRO NEAdO				|
----------------------------------------------------- 

*/
#ifndef FILA_NODE_H
	#define FILA_NODE_H

#include "Ad.h"

/*
Node class to be user in the queue
It has an value of Ad type and the nextNode that points to the next Node
*/
class Node {

    Ad value;
    Node* nextNode;
    
  public:  
  	   
    Node(Ad value, Node* nextNode);
    Ad getValue();
    Node* getNextNode();
    void setValue(Ad value);
    void setNextNode(Node* nextNode);
    
};
/*
Queue of Ads
*/

class Fila {

  	  Node* head;
  
	public:
		
  	  Fila(void);
  	  ~Fila(void);
  	  void insertAfterLast(Ad dat);
  	  Ad readFirst(void);
  	  Ad removeFirst(void);
  	  Node* getHead(void);
	 // friend Fila operator+(Fila&, Fila&);
};
#endif
