/**********

5/28/2020  Tang Xinyu

  *********************/
#include "common.h"

 int ALGORITHM;	//实现多个路由算法的时候执行的是哪一个，该程序只实现了一个，用于Routing.cpp中
 int GENERATETYPE;//用于选择linkrate的增长方式
 int flowalg;
 int totalcircle;//程序总的运行周期
 int knode;//二维网络中每维的节点数


 int getsize(vector<Message*>* mess);


int main()
 {	
 for(int allgen = 1; allgen < 2; allgen++){
	 int threshold = 800;
	 Allrouting* rout1 =NULL;
	 GENERATETYPE = allgen;	
	 flowalg = 1;
	 totalcircle = 100000;
	 knode    = 8;
	 Q2DTorus* tor = NULL;//网络结构，以前实现的torus网络，为了简单，我改为了mesh结构但名字没有改
	 Event* s = NULL;
	 int r1, r2, r3;
	 string gen[5] = {"0","1", "2", "3", "4"};
	 string filename[5] = {"data//gene4//Bubble Flow",
						   "data//gene4//clue-WF",
						   "data\\PAR.txt",
						   "data//gene4//xxx.txt",
						   "data//gene4//FCclue-WF",
							 };//结果的输出文件路径，因为以前实现了5种路由算法，所以这里有5个文件路径


	 /*for (int lop = 0; lop < 5; lop++) { ;
		 filename[lop].replace(10, 1, gen[GENERATETYPE]);				 
	 }*/

	


	 int r1buffer[5] = {1, 2, 1, 1, 2};//虚拟信道1缓存大小，以message个数为基本单位
	 int r2buffer[5] = {2, 1, 1, 0, 1};//虚拟信道2缓存大小，若无虚拟通道不使用r2
	 int r3buffer[5] = {2, 1, 1, 0, 1 };//虚拟信道3缓存大小
	 int alg[5] = {0, 1, 2, 3, 2};
	

	 /***
	 round = 2 : Dimension Order Routing，该程序只实现了xy路由，所以round的值不改变，只为2，循环只在实现多种路由算法时才有意义
  ***/

	 for(int round = 2 ; round < 3;round++){ 	
		 //ofstream out = ofstream(filename[round]);		
		 ofstream out;
		 out.open(filename[round]);
				 float linkrate = 0;
				 double max = 0;
				
	/************************************************************************************

						start simulate

  ***********************************************************************************/
	//linkrate控制消息产生速率
	 for(linkrate = 0.01; linkrate < 1;){

				 r1 = r1buffer[round] * MESSLENGTH;	//以flit个数为基本单位
				 r2 = r2buffer[round] * MESSLENGTH;	
				 r3 = r3buffer[round] * MESSLENGTH;
			     tor = new Q2DTorus(knode, r1, r2, r3); //初始化网络结构
				 

				 switch(round){

				 case 1: case 2:
					   ALGORITHM = 3;							  
					   rout1 = new Routing(tor);
					   break;
				 }
				 
			
				  	s = new Event(rout1);			
				 
								 
			float msgpercir = (float)  (linkrate * 2 * 2 * knode/ (MESSLENGTH * 10)) ;//每个周期每个节点产生的message数，还要除以10是因为allvecmess有10个元素
			//saturationRate = (double)(knode * 2 * 2) / (double)(knode * knode); 在mesh网络中的饱和吞吐量
			//msgpercir = linkrate * saturationRate * knode * knode; 每个周期每个节点产生的flit数
		
			vector<Message*> allvecmess[10];
			float k = 0;
			int allmess = 0;



  	/************************************************************************************

					genarate message

  ***********************************************************************************/
	//执行totalcircle个周期，getsize(allvecmess) < threshold只是自己加的限制条件，可以有也可以删除，具体的threshold和totalcircle值也可以在前面修改									
			for(int i = 0; i < totalcircle && getsize(allvecmess) < threshold; i++){		
				vector<Message*>& vecmess = allvecmess[ i % 10];
				for(  k += msgpercir ; k > 0; k--){					
								allmess++;//总的产生消息数加一
							vecmess.push_back(s->genMes());//产生消息放入	allvecmess的某个元素中	
				}


	/************************************************************************************

					release link

  ***********************************************************************************/


		for(vector<Message*>::iterator it = vecmess.begin(); it != vecmess.end(); it++){

				/* if the tail of a message shifts , 
				the physical link the message  occupied should release.				
				  */

			if((*it)->releaselink == true){ 
			 	assert((*it)->routpath[MESSLENGTH - 1].buff->linkused);
			 (*it)->routpath[MESSLENGTH - 1].buff->linkused = false;//释放链路					
			 (*it)->releaselink = false;
			}
		}
	



	/************************************************************************************

					forward message				

  ***********************************************************************************/
		for(vector<Message*>::iterator it = vecmess.begin(); it != vecmess.end();){
			if((*it)->active == false){	  // when a message arrive at its destination, it is not active
				delete (*it);
				it = vecmess.erase(it);//消息到达目的节点，将它从vecmess中删除				
			}
			else
				s->forwardMes(*(*it++));//调用Routing.cpp中函数转发消息								
		}		
	}




/*****************************************************************************

				output results
  ****************************************************************************/

	int size = getsize(allvecmess);


//s->totalcir/s->messarrive 平均延迟的计算公式；linkrate * ((float) s->messarrive / allmess)吞吐量的计算公式
	cout << endl << endl <<"linkrate:"<< linkrate<<"    arrive:  " << s->messarrive << "    in the network : "
		<< size <<  endl << "average latency: " 
		<< (s->totalcir/s->messarrive) << "  nomalized accepted traffic: "
		<<  linkrate * ((float) s->messarrive / allmess) 
		<<  endl << endl ;
	out << linkrate << " " << (s->totalcir / s->messarrive) 
		<< " " << linkrate * ((float)s->messarrive / allmess) << endl;
	





	/************************************************************************************

						whether arrive at saturation point

  ***********************************************************************************/
	if ( linkrate * ((float) s->messarrive / allmess) > max 
		&&  ((linkrate * ((float) s->messarrive / allmess) - max)/ max) > 0.01
		&& getsize(allvecmess) < threshold) 
		max = linkrate * ((float) s->messarrive / allmess);


	else {
			cout << "Saturation point, drain......." << endl;
			drain(allvecmess,tor,s);		
			int size = 0;
			for(int j = 0; j < 10; j++){
				if(!allvecmess[j].empty()){
					size += allvecmess[j].size();
				}
			}
			cout << "in the network:      "  << size << endl;
			outtotest(allvecmess,tor);
			bufferleft(tor, knode);
			cout << "max:" << max << endl;
			break;
	}





	/************************************************************************************
                    clean
  *******************************************************************************************/


			for(int m = 0; m < 10; m++){
				for(vector<Message*>::iterator it = allvecmess[m].begin();
							it != allvecmess[m].end(); it++)
					delete (*it);
			}
			delete rout1;
			delete tor;
			delete s;	


			switch(GENERATETYPE){
			case 1:	 				
					if(linkrate < 0.5) linkrate += 0.05;
					else  linkrate += 0.02;				
					break;

			case 2: case 3: 
					if(linkrate < 0.3) linkrate += 0.1;
					else linkrate += 0.02;
					break;
			case 4:
					if(linkrate < 0.4) linkrate += 0.1;
					else linkrate += 0.02;
					break;


			}
				
		 }   // each linkrate end
		 out.close();
	} // round end
  }
  return 1;
}


