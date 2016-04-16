#ifndef NEURALMANAGER_H
#define NEURALMANAGER_H

#define ENDPOINT    4294967295
#define SIGNALPOINT 4294967293
#define SIGNALNULL  4294967294

#include "neural.h"
#include "iostream"

struct neuralID
{
	unsigned int ID;

};

class neuralManager
{
	public:

		neuralManager(){}

/////////////////////////////////////////////////////Function addEntrance

		inline void addEntrance(unsigned int mark)
		{
			for(auto i : this -> Entrance)
				if(i == mark)
					return;
			Entrance.insert(mark);
			return;
		}

//Add Entrance if the set dosen't contain as the new.

////////////////////////////////////////////////////Function go

		Signal go(unsigned int enter,Signal Data)
		{
			if(enter == ENDPOINT)
				return Data;
			//If the process at the ENDPOINT, it will return final result.

			Signal output;
//			cout << "Where Data from " << Data.SignalOrigin << endl;  for debug

				this -> network.at(enter).SignalIn.push_back(Data);
				//Push previous Neural's output to next Neural's input.

				if(this -> network.at(enter).isReady() )
				{
//					cout << "The input is ready." << endl;            for debug

					auto output = network.at(enter).transferFunc(enter);

					for(auto i : network.at(enter).outputConnected)
						output = go(i,output);
					//Recursive 

//					cout << "End of the loop." << endl;               for debug
				
				}
				return output;
		}
//Provide for active(),or you can use to active part of network.
		
///////////////////////////////////////////////////Function active

	inline vector<Signal> active(){
		vector<Signal> output;
		for(auto i : Entrance)
		{
			Signal nullSignal;
			nullSignal.SignalOrigin = SIGNALPOINT;
			output.push_back(go(i,nullSignal));
			//Make a empty Signal to avtive the go().
		}
		return output;
	}
//According to the Entrance, the function will acess any neural with go() and memoried the output of any part.

///////////////////////////////////////////////////Function modifyWeight

		inline void modifyWeight(unsigned int Neural,unsigned int Origin,double changeVal)
		{
			for(auto i : this -> network.at(Neural).weight)
				if(i.SignalOrigin == Origin)
					i.value = changeVal;
		}
//As the function name, modify the special Neural's weight.

//////////////////////////////////////////////////Function makeConnect

		inline void makeConnect(unsigned int inpSet, unsigned int outSet)
		{
			if(inpSet <= network.size() && outSet >= 0)
				network.at(inpSet).outputConnected.push_back(outSet);

			if(outSet <= network.size() && outSet >= 0)
				network.at(outSet).inputConnected.push_back(inpSet);	
		}
//As the function name, make two different Neural link. 
//And the first param is the Neural which receive the output Neural of second param.

//////////////////////////////////////////////////Function addNeural

		inline unsigned int addNeural(neural added, neuralID* returnID)
		{
			added.neuralMark = this -> network.size();
			returnID -> ID   = added.neuralMark;
			this -> IDlist.push_back(returnID);
			this -> network.push_back(added);
		}

		inline unsigned int addNeural(neural added)
		{
			added.neuralMark = this -> network.size();
			this -> network.push_back(added);
		}

//As the function name, add the new Neural to the network.

/////////////////////////////////////////////////Function deleteNeural

		inline void deleteNeural(unsigned int deleted){
			
			bool flag = false;

			for(auto i:network)
			{
				if(i.neuralMark == deleted)
				{
					flag = true;
					break;
				}
			}
			//Check the deleted whether in the network.
		
			if(flag){
				this -> network.erase(network.begin() + deleted);
				updateID(deleted);
			}

		}
//As the function name, delete Neural.

/////////////////////////////////////////////////////////////////Function updateID

		void updateID(unsigned int deletedID)
		{

			for(auto i:IDlist)
			{
				if(i -> ID > deletedID)
					i -> ID = (i -> ID) - 1;
			}
			//If the ID greater than the deletedID, then it will minus the ID from 1.
		}
		//When deleteNeural() has been used ,then it will call this function to update
		 

////////////////////////////////////////////////////////////////Function addID
	inline void addID(neuralID* added)
	{
		for(auto i:IDlist)
			if(i -> ID == added -> ID)
				return;
		//Check the struct of neuralID had be not added.
		IDlist.push_back(added);
	}
	//To addID.
	
///////////////////////////////////////////////////////////////

		vector<neural>    network;
		vector<neuralID*>  IDlist;
		set<unsigned int> Entrance;

};

#endif
