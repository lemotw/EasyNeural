#ifndef NEURALMANAGER_H
#define NEURALMANAGER_H

#define ENDPOINT 4294967295

#include "neural.h"

class neuralManager
{
	public:

		neuralManager()
		{
			Size = 1;
		}
		
		void setEntrance(unsigned int mark)
		{
			for(auto i : Entrance)
				if(neural == mark)
					return;
			Entrance.push_back(enterP);
			return;
		}

		Signal active(unsigned int enter,Signal Data)
		{
			if(enter == ENDPOINT)
					return Data;

			Signal output;
			*(network.begin()+enter).SignalIn.push_back(Data);

			if(*(network.begin+enter).isReady() )
			{

				auto result = *(network.begin+enter).counter();
				auto output = *(network.begin+enter).judgeFunc(result);

				for(i:*(network.begin+enter).outputConnected)
					output = active(i,output);
				
			}
			return output;
		}

		void modifyWeight(unsigned int Neural,unsigned int Origin,double changeVal)
		{
			for(i:*(network.begin()+Neural).weight)
				if(i.SignalOrigin == Origin)
					i.value = changeVal;
		}

		void addNeural(neural added)
		{
			added.neuralMark = Size;
			network.push_back(added);
			++Size;
		}

		void deleteNeural(unsigned int deleted)
		{
			for(unsigned int i = 0;i < network.size();++i)
				if(*(network.begin() + i).neuralMark == deleted){
					network.erase(network.begin() + i);
					return;
				}
		}

		vector<neural> network;
		vector<neural> Entrance;
		unsigned int   Size;

};

#endif
