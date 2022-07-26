/************


  The event class define events occur in one circle.

  Luo Wei, 3/21/2009


  ********************/







#ifndef   EVEN_T
#define   EVEN_T
#include"Routing.h"
#include"Message.h"
//#include"AllMessage.h"
#include"Q2DTorus.h"
#include"Q2DTorusNode.h"


class Event{
public:
	int consumed;
	double totalcir; // total circle all the messages take;
	int messarrive; // how many message arrived
	Allrouting* rout;
	Q2DTorus* tor;
	int k;// k * k *k torus
	
Message* 	genMes();          //generate a message
void        forwardMes(Message&);//forward a message
//void        consumeMes(Message&);
			Event(Allrouting*);
};


















#endif