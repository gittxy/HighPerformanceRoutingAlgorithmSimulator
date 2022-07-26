
//#define BUFFER  10
#include <assert.h>
#include "Q2DTorus.h"

	Q2DTorus::Q2DTorus(int n, int R1buffer, int R2buffer, int R3buffer)
{

		
		k = n;
		int t = k*k;
		head = new Q2DTorusNode[t];
		assert(head);
		int x = 0, y = 0;
		for( x = 0; x < k; x++){
			for( y = 0; y < k; y++){
			
				int id = x  + y * k  ; 
				(head + id)->setTorus(this);
				(head+id)->setCoordinate(id, x, y);				
				(head+id)->setbuffer(R1buffer, R2buffer, R3buffer);
				
					
				
			}
		}
		
		for( x = 0; x < k; x++){
			for( y = 0; y < k; y++){
			
				int id = x  + y * k ; 
				int xneg, xpos , yneg, ypos;
				//注释中是torus网络结构，实现torus网络的同学可以借鉴
				/*if (x != 0)  xneg = (x - 1)  + y * k ;   // the node x negative direction link to
				else   xneg = (k - 1) + y * k ;
				if (x != k-1)  xpos = (x + 1)  + y * k ;
				else   xpos =  y * k ;

				if (y != 0)  yneg = x  + (y - 1) * k;  // the node y negative direction link to
				else   yneg = x  + (k - 1) * k;
				if (y != k-1)  ypos = x  + (y + 1) * k  ;
				else   ypos = x;*/
				
                //设置该节点各个方向相邻的节点
				if (x != 0)  xneg = (x - 1) + y * k;
				else   xneg = -1;
				if (x != k - 1)  xpos = (x + 1) + y * k;
				else   xpos = -1;

				if (y != 0)  yneg = x + (y - 1) * k;
				else   yneg = -1;
				if (y != k - 1)  ypos = x + (y + 1) * k;
				else   ypos = -1;
			
				(head + id)->setLinkBuffer(xneg, xpos, yneg, ypos);
				
				
			}
		}
}
	Q2DTorusNode* Q2DTorus::operator [](int n){
	return (head+n); 
	}
	

void	Q2DTorus::clearAll(){
		for(int i = 0; i < k * k ; i++){
			(head + i)->clearBuffer();
		}
	}
