#ifndef NEURALMANAGER_H
#define NEURALMANAGER_H

#include "neural.h"
#include <list>
#include <iostream>

enum class TypeOfSignalEnd : unsigned int
{

	ENDPOINT    = 4294967295,
	SIGNALNULL  = 4294967294,
   	SIGNALPOINT = 4294967293 

};

struct connection
{
	unsigned int inputEnd;
	unsigned int outputEnd;

	double 		 weightVal;
};

class neuralManager
{
	public:

		neuralManager(){}

//_____________________________________________________________________________________________________

		void 		 addEntrance(unsigned int mark);
		void 		 reDO(unsigned int enter,Signal Data);
		void 		 active();

//_____________________________________________________________________________________________________

		void 		 addWeight(unsigned int Neural,unsigned int Origin,double changeVal);
		void 		 addWeight(connection con);

		void  		 makeConnect(unsigned int source, unsigned int target, double weightVal);

		void		 deleteConnect(unsigned int inputEnd,unsigned int outputEnd);
//_____________________________________________________________________________________________________

		unsigned int makeSP();
		void         makeEP(unsigned int target);

		void		 addNeural(countor initc ,judge initj ,unsigned int* ID);
		unsigned int addNeural(countor initc ,judge initj);
		unsigned int addNeural(neural pushed);

		void 		 deleteNeural(unsigned int deleted);

//_____________________________________________________________________________________________________

		void		 updateID(unsigned int deletedID);	
		void		 addID(unsigned* added);

		void  		 pushSignalIn(Signal In, unsigned int mark);
		Signal		 getOutputVal(unsigned int forcus);

//_____________________________________________________________________________________________________	

		vector<neural>        network;
		vector<Signal>        outputStore;

		vector<unsigned int*> IDlist;
		set<unsigned int>     Entrance;
		vector<connection>	  connection_Table;
};

#endif
