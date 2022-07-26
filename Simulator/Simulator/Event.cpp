#include"Event.h"

#include<math.h>
#include"Message.h"

extern int GENERATETYPE;

Event::Event(Allrouting * rout1){	
	 consumed = 0;
	 totalcir =0 ;
	 messarrive = 0;
	rout = rout1;
	tor = rout1->torus;
	k = rout1->k;
}



Message*  Event::genMes(){   //generate a message
		Q2DTorus* torus =NULL;
	if(rout != NULL)  torus = rout->torus;
	//uniform流量模式
	if(GENERATETYPE == 1){
		int tempRand;
		int  src, dest;
		tempRand = abs(rand()) % (k * k );
		src = tempRand;
		while (1){
			tempRand = abs(rand()) % (k * k );
			if ( tempRand != src){
				dest = tempRand;
				break;
			}
		}
		return new Message(src, dest);
	}
	if(GENERATETYPE == 2){
		int tempRand;
		int  src, dest;
		int  x;
		int  y;
	
		while (1){
		tempRand = abs(rand()) % (k * k );
		 x = (*torus)[tempRand]->x;
		 y = (*torus)[tempRand]->y;
		
		if ( x != (k - 1 - y) || y != (k - 1 - x) )
			break;
		}
		dest = (k - 1 - y)  + (k - 1 - x) * k;
		src = tempRand;
	
		return new Message(src, dest);
	}
	
	if(GENERATETYPE == 3){
		int tempRand;
		int  src, dest;
		int  x;
		int  y;
	
		while (1){
		tempRand = abs(rand()) % (k * k);
		 x = (*torus)[tempRand]->x;
		 y = (*torus)[tempRand]->y;
		
		if ( x != y  )
			break;
		}
		dest = y   + x * k ;
		src = tempRand;
	
		return new Message(src, dest);
	}
	if(GENERATETYPE == 4){
		int tempRand;
		int  src, dest;
		tempRand = abs(rand()) % 10;
		if(tempRand != 0){
			tempRand = abs(rand()) % (k * k );
			src = tempRand;
			while (1){
				tempRand = abs(rand()) % (k * k);
				if ( tempRand != src){
					dest = tempRand;
					break;
				}
			}
		}
		else{
				int temprand2 = abs(rand()) % 2;
				switch(temprand2){
				case 0:
					dest = (int) ((k - 1 - k/4) * k + k - 1 - k/4); break;
				case 1:
					dest = (int) (k/4 * k + k/4); break;
				
				}
			while (1){
				tempRand = abs(rand()) % (k * k);
				if ( tempRand != dest){
					src = tempRand;
					break;
				}
			}


		}
	
		
	
	
		return new Message(src, dest);
	}



}

void       Event::forwardMes(Message& s){
	if(s.begintrans <= 0) s.count++;		
	if( s.routpath[0].node == s.src) {
		if( s.begintrans > 0)
			s.begintrans --; // check whether process time  
		else{					
					s.begintrans--;
					NodeInfo* next ;
					assert(rout != NULL);		
					 next = rout->forward(s);
				if (next->node == -1){
								s.timeout++;
//						if(s.timeout == TIMEOUT) consumeMes(s);
						}
				else{
					s.timeout = 0;
					assert(s.routpath[0].node != next->node);
					s.routpath[0] = *next; 
					
				}
			
			
		}
	}
	else{
		if( s.routpath[0].node != s.dst){
			NodeInfo* next = NULL;
			if(rout != NULL)		
				next = rout->forward(s);//调用Allrouting.h中的forward()函数，得到header flit下一跳的节点
			if (next->node == -1){
						int i ;
						for( i = 1; i < MESSLENGTH && s.routpath[i].node == s.routpath[0].node; i++); //if blocked insert the flits until all are inserted
						if(i < MESSLENGTH){
						NodeInfo temp1 ,temp2; // all the flits forward one step
						temp2 = s.routpath[i - 1];
						while(i < MESSLENGTH){
							temp1 = s.routpath[i] ;
							s.routpath[i] = temp2;
							temp2 = temp1;
							i++;
						}
							if(temp2.node != s.routpath[MESSLENGTH - 1].node){
							assert(s.routpath[MESSLENGTH - 1].buff->linkused); 
								s.releaselink = true;
							}
							if(temp2.buff != NULL && temp2.node != s.routpath[MESSLENGTH - 1].node)
							 temp2.buff->bufferPlus(temp2.channel, MESSLENGTH);
						
						}
						s.timeout++;
					//	if(s.timeout == TIMEOUT) consumeMes(s);
			}
			else{
								s.timeout = 0;												
								NodeInfo temp1 ,temp2; // all the flits forward one step
								temp2 = s.routpath[0];
								int i = 1;
								while(i < MESSLENGTH){
									temp1 = s.routpath[i] ;
									s.routpath[i] = temp2;
									temp2 = temp1;
									i++;
									}
								if(temp2.node != s.routpath[MESSLENGTH - 1].node){
									assert(s.routpath[MESSLENGTH - 1].buff->linkused || s.routpath[MESSLENGTH - 1].buff->linkused ); 
									s.releaselink = true;   // the tail shift, release the physical link
								}
							if(temp2.buff != NULL && temp2.node != s.routpath[MESSLENGTH - 1].node) // maybe the last flit do not insert into the network
							 temp2.buff->bufferPlus(temp2.channel, MESSLENGTH);
							 
							  s.routpath[0] = *next ;
					
					
			}
		}


		else{
				 	  NodeInfo temp1 ,temp2; // all the flits forward one step
						temp2 = s.routpath[0];
						int i;
						for( i = 1; i < MESSLENGTH && s.routpath[i].node == s.routpath[0].node; i++);
						if( i == MESSLENGTH) {							
							s.routpath[i-1].buff->bufferPlus(s.routpath[i-1].channel,MESSLENGTH); // add buffer
							s.active = false;
							totalcir += s.count;
							messarrive++;
							return;
						}
							while(i < MESSLENGTH){
							temp1 = s.routpath[i] ;
							s.routpath[i] = temp2;
							temp2 = temp1;
							i++;
							}
						if(temp2.node != s.routpath[MESSLENGTH-1].node)
									s.releaselink = true;   // the tail shift, release the physical link
							
							if(temp2.buff != NULL && temp2.node != s.routpath[MESSLENGTH - 1].node) // maybe the last flit do not insert
						 temp2.buff->bufferPlus(temp2.channel, MESSLENGTH);
						 
						
		}

		
	}
	//cout << s.src << "dst: " << s.dst << endl ;

}
