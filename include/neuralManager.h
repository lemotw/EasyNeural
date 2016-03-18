#ifndef NEURALMANAGER_H
#define NEURALMANAGER_H

#define ENDPOINT   4294967295
#define STARTPOINT 4294967294

#include "neural.h"

class neuralManager
{
	public:

		neuralManager(){Size = 1;}

/////////////////////////////////////////////////////		

		void setEntrance(unsigned int mark)
		{
			for(auto i : Entrance)
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
			network.at(enter).SignalIn.push_back(Data);

			if(network.at(enter).isReady() )
			{

				auto result = network.at(enter).countValue(network.at(enter).SignalIn, network.at(enter).weight);
				auto output = network.at(enter).judgeFunc(result,enter);

				for(i:network.at(enter).outputConnected)
					output = active(i,output);
				
			}
			return output;
		}

/////////////////////////////////////////////////////////////////

		void modifyWeight(unsigned int Neural,unsigned int Origin,double changeVal)
		{
			for(i:network.at(Neural).weight)
				if(i.SignalOrigin == Origin)
					i.value = changeVal;
		}

/////////////////////////////////////////////////////////////////

		void addNeural(neural added)
		{
			added.neuralMark = Size;
			network.push_back(added);
			++Size;
		}

/////////////////////////////////////////////////////////////////

		void deleteNeural(unsigned int deleted)
		{
			for(unsigned int i = 0;i < network.size();++i)
				if(network.at(i).neuralMark == deleted){
					network.erase(network.begin() + i);
					return;
				}
		}

/////////////////////////////////////////////////////////////////

		vector<neural> network;
		vector<unsigned int> Entrance;
		unsigned int   Size;

};

#endif
