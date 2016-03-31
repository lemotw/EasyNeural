#ifndef NEURALMANAGER_H
#define NEURALMANAGER_H

#define ENDPOINT   4294967295
#define SIGNALPOINT 0
#define SIGNALNULL  4294967294

#include "neural.h"
#include "iostream"

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
			cout << Data.SignalOrigin;

			if(Data.SignalOrigin != SIGNALNULL)
			{

				cout << "erri";
				this -> network.at(enter).SignalIn.push_back(Data);
			

				if(this -> network.at(enter).isReady() )
				{

					auto output = network.at(enter).transferFunc(enter);

					for(auto i : network.at(enter).outputConnected)
						output = go(i,output);
					cout << "gg";
				
				}
				return output;
			}
			else
			{
				
				

			}
		//
		}
		//Provide for active(),or you can use to active part of network.
		
/////////////////////////////////////////////////////////////////

	inline vector<Signal> active(){
		vector<Signal> output;
		for(auto i : Entrance)
		{
			Signal nullSignal;
			nullSignal.SignalOrigin = SIGNALNULL;
			output.push_back(go(i,nullSignal));
		}
		return output;
	}
	//According to the Entrance, the function will acess any neural with go() and memoried the output of any part.

/////////////////////////////////////////////////////////////////

		inline void modifyWeight(unsigned int Neural,unsigned int Origin,double changeVal)
		{
			for(auto i : this -> network.at(Neural-1).weight)
				if(i.SignalOrigin == Origin)
					i.value = changeVal;
		}
		//As the function name.

/////////////////////////////////////////////////////////////////

		inline void makeConnect(unsigned int inpSet, unsigned int outSet)
		{
			if(inpSet <= network.size() && inpSet > 0)
				network.at(inpSet-1).outputConnected.push_back(outSet);

			if(outSet <= network.size() && outSet > 0)
				network.at(outSet-1).outputConnected.push_back(inpSet);	
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
		double couTest(unsigned int x){return network.at(x).countValue(network.at(x-1).SignalIn, network.at(x-1).weight);}
/////////////////////////////////////////////////////////////////

		vector<neural>    network;
		set<unsigned int> Entrance;

};

#endif
