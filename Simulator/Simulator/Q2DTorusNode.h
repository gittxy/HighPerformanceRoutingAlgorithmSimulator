//  3 dimension torus nodes. 
//  5/28/2020  Tang Xinyu

#ifndef Q2DTorusNode_H
#define Q2DTorusNode_H
#include<iostream>
#include<string>
#include<assert.h>
#define R1  1
#define R2  2
#define R3  3
using namespace std;
#define MESSLENGTH 16
#include "Q2DTorus.h"
class Q2DTorus;

class Buffer{   // R1 and R2 and R3 reserve some buffers separately,they can also use sharebuffer.
public:
	bool linkused;   // in a physical circle ,check whether physical link is used , only one flit is allowed to pass the link in a circle
	int r1;
	int r2;
	int r3;
	void	bufferMin (int chn , int n)	;	
	void	bufferPlus (int chn ,int n);

	int c; // flow control buffer
	int s; // flow control special buffer
};



/**************************************************


	this class define the info of a flit in the torus node
	including nodeid, buffer
	************************************************/
class NodeInfo{  
public:				//nextnode is the node to be routed,and vchannel is the virtual channel(R1 or R2) used. 
	int node;   	
	int channel;  // which is used : R1 or R2 or R3
	Buffer* buff;// point to the buffer occupy ,such as bufferxneg......
	NodeInfo():node(-1){
		
	}
};




class Q2DTorusNode{

private:
	int nodeid;
	
public:
	Buffer* bufferxneg;//the buffer  of x axis negative direction
	Buffer* bufferxpos;//the buffer  of x axis positive direction
	Buffer* bufferyneg;
	Buffer* bufferypos;

	int linkxneg;//the node to x axis negative direction link
	int linkxpos;
	int linkyneg;
	int linkypos;

	Q2DTorus* torus;
	
	Buffer* bufferxneglink;
	Buffer* bufferxposlink;//the buffer x positive direction link to, it is the buffer of neighbor node
	Buffer* bufferyneglink; // ...
	Buffer* bufferyposlink;


	

	int x; //x coordinate
	int y;// y coordinate



void	setCoordinate(int _nodeid ,int _x, int _y);

void	setbuffer( int buff1, int buff2, int buff3);            //   num is the share buffer number
	
void	setLinkBuffer(int x1, int x2, int y1, int y2);

void    setTorus(Q2DTorus * torus);	

void	bufferPlus(Buffer* buff, int chn , int n);
	 
void	bufferMin(Buffer* buff, int chn,int n);
	  
void	clearBuffer();


	~Q2DTorusNode(){
		delete  bufferxneg;
		delete  bufferyneg;
		delete  bufferxpos;
		delete  bufferypos;
	
	}

};
#endif