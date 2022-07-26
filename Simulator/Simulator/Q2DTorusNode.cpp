#include "Q2DTorusNode.h"

void Buffer::bufferMin (int chn , int n) {       //share buffers are used first,when no share buffers ,		
			
		if(R1 == chn){								//	the separate buffers are used.So first we check the			
												// separate buffers whether used.
		  r1 -= n;
		}													
		else if(R2 == chn) {
		  r2 -= n;
		}
		else {
		  r3 -= n;
		}
/*

   the following is for flow control
  */
        c -= 1;
	 if(R2 == chn)
		 s++;  



}

void	Buffer::bufferPlus (int chn ,int n) {   
		assert( chn == R1 || chn == R2 || chn == R3);
		if(R1 == chn){
		 r1 += n;					
		}													
		else if (R2 == chn){
		 r2 += n;		
		}	
		else {
		 r3 += n;
		}
/*

   the following is for flow control
  */
        c += 1;
	 if(R2 == chn)
		 s--;  
		
}



void	Q2DTorusNode::setCoordinate(int _nodeid ,int _x, int _y){
				nodeid = _nodeid;
				x = _x;
				y = _y;
			
				}


void	Q2DTorusNode::setbuffer( int buff1, int buff2,int buff3)            //   num is the share buffer number
	{ 

		
	 bufferxneg = new Buffer();
	 bufferxpos = new Buffer();
	 bufferyneg = new Buffer();
	 bufferypos = new Buffer();

		clearBuffer();
	 
	 	 
	 bufferxneg->r1  = buff1;
	 bufferxpos->r1  = buff1;
	 bufferyneg->r1  = buff1;
	 bufferypos->r1  = buff1;


	 bufferxneg->r2  = buff2;
	 bufferxpos->r2  = buff2;
	 bufferyneg->r2  = buff2;
	 bufferypos->r2  = buff2;

	 bufferxneg->r3 = buff3;
	 bufferxpos->r3 = buff3;
	 bufferyneg->r3 = buff3;
	 bufferypos->r3 = buff3;


/*

   the following is for flow control
  */
	 bufferxneg->c  = (buff1 + buff2) / MESSLENGTH;
	 bufferxpos->c  = (buff1 + buff2) / MESSLENGTH;
	 bufferyneg->c  = (buff1 + buff2) / MESSLENGTH;
	 bufferypos->c  = (buff1 + buff2) / MESSLENGTH;


	 bufferxneg->s  = 0;
	 bufferxpos->s  = 0;
	 bufferyneg->s  = 0;
	 bufferypos->s  = 0;


	}

void	Q2DTorusNode::setLinkBuffer(int x1, int x2, int y1, int y2)
	{
		linkxneg = x1;
		linkxpos = x2;
		linkyneg = y1;
		linkypos = y2;
		
		
		if (linkxneg != -1) bufferxneglink = (*torus)[linkxneg]->bufferxpos;
		else bufferxneglink = NULL;
		if (linkxpos != -1) bufferxposlink = (*torus)[linkxpos]->bufferxneg;
		else bufferxposlink = NULL;
			
		if (linkyneg != -1) bufferyneglink = (*torus)[linkyneg]->bufferypos;
		else bufferyneglink = NULL;
	    if (linkypos != -1) bufferyposlink = (*torus)[linkypos]->bufferyneg;
		else bufferyposlink = NULL;
	  
	
	}

void	Q2DTorusNode::bufferPlus(Buffer* buff, int chn , int n)
	  {
			buff->bufferPlus(chn,n);
	  }

void	 Q2DTorusNode::bufferMin(Buffer* buff, int chn,int n)
	  {
			buff->bufferMin(chn,n);
	  }

void	Q2DTorusNode::clearBuffer(){
	  		bufferxneg->linkused  = false;
			bufferxpos->linkused  = false;
			bufferyneg->linkused  = false;
			bufferypos->linkused  = false;
			  		 
		 
	  }

void    Q2DTorusNode::setTorus(Q2DTorus * torus){
		this->torus = torus;
}