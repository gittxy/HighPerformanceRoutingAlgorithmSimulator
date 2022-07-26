#ifndef CO_MM_O1
#define CO_MM_O1




#include"Q2DTorus.h"
#include"Routing.h"
#include"Event.h"
#include<vector>
#include <fstream>




void outtotest(vector<Message*>* vecmess, Q2DTorus* tor);
void bufferleft(Q2DTorus* tor, int knode);
void drain(vector<Message*>* vecmess, Q2DTorus* tor, Event* s);










#endif