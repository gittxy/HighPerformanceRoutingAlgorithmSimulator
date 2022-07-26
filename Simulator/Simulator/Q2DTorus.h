// 3 dimension torus network .Written by Luo Wei in 3/20/2009.


#ifndef Q2DTORUS_H
#define Q2DTORUS_H
#include "Q2DTorusNode.h"
class Q2DTorusNode;
class Q2DTorus{
public:
	Q2DTorus(int n,  int R1buffer, int R2buffer, int R3buffer);//n*n 2Dtorus,
	Q2DTorusNode* operator [](int n);
	void clearAll();
	~Q2DTorus()
	{
		
		delete [] head;
	
	}
	int getNode(){return k;}
private:
	 int k;
	Q2DTorusNode* head;
};
#endif