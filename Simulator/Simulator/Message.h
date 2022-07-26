/*********     
		9/11/2007,Luo Wei.
		The definition of message.




********/

#ifndef  MESS_AGE
#define  MESS_AGE
#define PROCESSTIME 16
#define TIMEOUT   50000
#include<iostream>
#include<string>
#include<assert.h>
#include"Q2DTorusNode.h"
using namespace std;
class Buffer;
class NodeInfo;


/************************
  Message info    
  ******************************/
class Message{
public:
	int length ;       		// measured by flits;
	int src;         			//The source of the message
	int dst;
	int timeout;   				//measured by circle ,the time limit of message waits for a channel       
	int begintrans;  //when a message is generated ,it needs some time until transmitting,begintrans record this.
	int step;       //how many steps this message has walked;
	bool active; // check this message whether consumed or arrive at dst
NodeInfo* routpath; // : the ith flit now at routpath[i].node and take routpath[i].buffer 
	int count;// the total time a message  consumed
  bool releaselink;  // if the tail of a message shifts , the physical link the message occupied should release.

  bool turn;//  used in bubble flow control, if true, then the request escape channel need 2 buffers.
			
	


	Message( ){
		src = -1;
		dst = -1;
	}


	Message(int src1, int dst1){
		begintrans = PROCESSTIME;
		src = src1;
		dst = dst1;
		routpath = new NodeInfo[MESSLENGTH];
		assert(routpath);
		for(int i = 0 ; i < MESSLENGTH; i++){
			routpath[i].node = src;
			routpath[i].channel = 0;
			routpath[i].buff = NULL;
			
		}
		step = 0;
		active = true;
		length = MESSLENGTH;
		count = 0;
		releaselink = false;
		turn = true;
		timeout = 0;
	
	}

	 ~Message(){
 	delete []routpath;
}


	void setLength(int n)
	{
		length = n;
	}

};





#endif