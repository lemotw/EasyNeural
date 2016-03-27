#ifndef NEURALMANAGER_H
#define NEURALMANAGER_H

#define ENDPOINT   4294967295
#define STARTPOINT 4294967294
#define SIGNALPOINT 0

#include "neural.h"

class neuralManager
{
	public:

		neuralManager(){}

/////////////////////////////////////////////////////		

		inline void addEntrance(unsigned int mark)
		{
			for(auto i : this -> Entrance)
				if(i == mark)
					return;
			Entrance.insert(mark);
			return;
		}

		//Add Entrance if the set dosen't contain as the new.

////////////////////////////////////////////////////

		Signal go(unsigned int enter,Signal Data)
		{
		//
			if(enter == ENDPOINT)
					return Data;

			Signal output;
			this -> network.at(enter-1).SignalIn.push_back(Data);
			

			if(this -> network.at(enter-1).isReady() )
			{

				auto result = this -> network.at(enter-1).countValue(network.at(enter-1).SignalIn, network.at(enter-1).weight);
				auto output = this -> network.at(enter-1).judgeFunc(result,enter);

				for(i : this -> network.at(enter-1).outputConnected)
					output = go(i,output);
				
			}
			return output;
		//
		}
		//Provide for active(),or you can use to active part of network.
		
/////////////////////////////////////////////////////////////////

	inline vector<Signal> active(){
		vector<Signal> output;
		for(i : Entrance)
		{
			output.push_back(go(i,NULL));
		}
		return output;
	}
	//According to the Entrance, the function will acess any neural with go() and memoried the output of any part.

/////////////////////////////////////////////////////////////////

		inline void modifyWeight(unsigned int Neural,unsigned int Origin,double changeVal)
		{
			for(i : this -> network.at(Neural-1).weight)
				if(i.SignalOrigin == Origin)
					i.value = changeVal;
		}
		//As the function name.

/////////////////////////////////////////////////////////////////

		inline void makeConnect(unsigned int inpSet, unsigned int outSet)
		{
			network.at(outSet-1).inputConnected.push_back(inpSet);
			network.at(inpSet-1).outputConnected.push_back(outSet);
		}
		//As the function name.

/////////////////////////////////////////////////////////////////

		inline void addNeural(neural added)
		{
			added.neuralMark = this -> network.size()+1;
			this -> network.push_back(added);
		}
		//As the function name.

/////////////////////////////////////////////////////////////////

		inline void deleteNeural(unsigned int deleted){this -> network.erase(network.begin() + deleted);}
		//As the function name.

/////////////////////////////////////////////////////////////////

		vector<neural>    network;
		set<unsigned int> Entrance;

};

#endif
