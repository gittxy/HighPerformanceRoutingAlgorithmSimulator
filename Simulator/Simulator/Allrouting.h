#ifndef ALLROUTING_H
#define ALLROUTING_H

#include "Q2Dtorus.h"
#include "Message.h"
class Message;
class Q2DTorus;
class NodeInfo;
class Allrouting{
public:
   	NodeInfo* next;
	Q2DTorus* torus;
	int k;
	virtual NodeInfo*	forward(Message& s){return NULL;};
  // implemented by child
};


#endif