#ifndef NEURALMANAGER_H
#define NEURALMANAGER_H

#define ENDPOINT   4294967295
#define STARTPOINT 4294967294

#include "neural.h"

class neuralManager
{
	public:

		neuralManager(){this -> Size = 1;}

/////////////////////////////////////////////////////		

		void setEntrance(unsigned int mark)
		{
			for(auto i : this -> Entrance)
				if(i == mark)
					return;
			Entrance.push_back(mark);
			return;
		}

////////////////////////////////////////////////////

		Signal active(unsigned int enter,Signal Data)
		{
			if(enter == ENDPOINT)
					return Data;

			Signal output;
			this -> network.at(enter).SignalIn.push_back(Data);

			if(this -> network.at(enter).isReady() )
			{

				auto result = this -> network.at(enter).countValue(network.at(enter).SignalIn, network.at(enter).weight);
				auto output = this -> network.at(enter).judgeFunc(result,enter);

				for(i : this -> network.at(enter).outputConnected)
					output = active(i,output);
				
			}
			return output;
		}

/////////////////////////////////////////////////////////////////

		void modifyWeight(unsigned int Neural,unsigned int Origin,double changeVal)
		{
			for(i : this -> network.at(Neural).weight)
				if(i.SignalOrigin == Origin)
					i.value = changeVal;
		}

/////////////////////////////////////////////////////////////////

		void addNeural(neural added)
		{
			added.neuralMark = this -> Size;
			this -> network.push_back(added);
			++Size;
		}

/////////////////////////////////////////////////////////////////

		inline void deleteNeural(unsigned int deleted){this -> network.erase(network.begin() + deleted);}

/////////////////////////////////////////////////////////////////

		vector<neural> network;
		vector<unsigned int> Entrance;
		unsigned int   Size;

};

#endif
