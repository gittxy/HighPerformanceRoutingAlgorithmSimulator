#include"Routing2.h"
#include<assert.h>


NodeInfo*	Routing2::forward(Message& s ){
	

	int var1 = 0;
	int var2 = 0;
	int var = 0;
	next->node = -1;
	next->buff = NULL;
	
	NodeInfo* temp1 = xdimension(s);
	NodeInfo* temp2 = ydimension(s);



	if(temp1 != NULL) var1 = 1;
	if(temp2 != NULL) var2 = 1;
	int allbuff1 = 0;
	int allbuff2 = 0;
	var = var1*2 + var2;

	if(var == 3){
	 allbuff1 = temp1->buff->r1 + temp1->buff->r2;
	 allbuff2 = temp2->buff->r1 + temp2->buff->r2;
	}


	if(var == 2 || (var == 3 && allbuff1 >= allbuff2)){
		*next = * temp1;
		next->buff->bufferMin(next->channel, MESSLENGTH);
		next->buff->linkused = true;
	}

	else if(var == 1 || (var == 3 && allbuff1 < allbuff2)){
		*next = * temp2;
		next->buff->bufferMin(next->channel, MESSLENGTH);
		next->buff->linkused = true;
	}
			
	return next;

}



/*

check wether next hop could be along x dimension.


    

  */

NodeInfo*	Routing2::xdimension(const Message& s ){   
        Q2DTorusNode* cur = (*torus)[s.routpath[0].node];
		Q2DTorusNode* dst = (*torus)[s.dst];
	

		int curx = cur->x;
		int cury = cur->y;
		int dstx = dst->x;
		int dsty = dst->y;
	
		int xdis = dstx - curx;
		int ydis = dsty - cury;
		bool special = false;


		Buffer* xlink[2] = {cur->bufferxneglink, cur->bufferxposlink};
	
		int xlinknode[2] = {cur->linkxneg, cur->linkxpos};

		

		if(xdis == 0) return NULL;

		if(xdis > k/2  || xdis < -k/2){   
			Buffer* temp = xlink[0];
			xlink[0] = xlink[1];
			xlink[0] = temp;

			int temp1 = xlinknode[0];
			xlinknode[0] = xlinknode[1];
			xlinknode[1] = temp1;
		}
 
		if(xlink[xdis > 0]->linkused == true) return NULL;
		

      if(xdis > k/2 && curx == 0) special = true;
	  if(xdis < -k/2 && curx == k-1) special = true;
	  if((xdis <= k/2  && xdis >= -k/2) && (ydis <= k/2  && ydis >= -k/2))
		  special = true;
		
	  if(xlink[xdis > 0]->r1 < MESSLENGTH && !special)
		   return NULL;

	  if(xlink[xdis > 0]->r1 < MESSLENGTH && xlink[xdis > 0]->r2 < MESSLENGTH && special)
		   return NULL;

	  xtemp->buff = xlink[xdis > 0];
	  xtemp->node = xlinknode[xdis > 0];

	if(xlink[xdis > 0]->r1 >= MESSLENGTH)
	  xtemp->channel = R1;  // R1
	else xtemp->channel = R2;  // R2
 	
	  return xtemp;
}



NodeInfo*	Routing2::ydimension(const Message& s ){

		
		Q2DTorusNode* cur = (*torus)[s.routpath[0].node];
		Q2DTorusNode* dst = (*torus)[s.dst];

		int curx = cur->x;
		int cury = cur->y;
		int dstx = dst->x;
		int dsty = dst->y;
	
		int xdis = dstx - curx;
		int ydis = dsty - cury;
		bool special = false;


		Buffer* ylink[2] = {cur->bufferyneglink, cur->bufferyposlink};
	
		int ylinknode[2] = {cur->linkyneg, cur->linkypos};

		

		if(ydis == 0) return NULL;

		if(ydis > k/2  || ydis < -k/2){   
			Buffer* temp = ylink[0];
			ylink[0] = ylink[1];
			ylink[0] = temp;

			int temp1 = ylinknode[0];
			ylinknode[0] = ylinknode[1];
			ylinknode[1] = temp1;
		}

		if(ylink[ydis > 0]->linkused == true) return NULL;

        bool xwrap = (xdis <= k/2  && xdis >= -k/2);




      if(xwrap && ydis > k/2 && cury == 0) special = true;
	  if(xwrap && ydis < -k/2 && cury == k-1) special = true;
	  if(xwrap && ydis <= k/2  && ydis >= -k/2){
		  if(flowalg == 1){
			  if(xdis == 0)
				  special = true;
		  }
		  
		  else{
			  if(xdis >= 0)
				  special = true;
		  }
	

	  }
	   if(ylink[ydis > 0]->r1 < MESSLENGTH && !special)
		   return NULL;

	  if(ylink[ydis > 0]->r1 < MESSLENGTH && ylink[ydis > 0]->r2 < MESSLENGTH && special)
		   return NULL;


	  ytemp->buff = ylink[ydis > 0];
	  ytemp->node = ylinknode[ydis > 0];
	  if(ylink[ydis > 0]->r1 >= MESSLENGTH)
	  ytemp->channel = R1;  // R1
	else ytemp->channel = R2;  // R2
 	
	  return ytemp;
}
