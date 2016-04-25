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
			for(auto i : Entrance)
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
			{
				Data.SignalOrigin = ENDPOINT;
				outputStore.push_back(Data);
				return Data;
			}
			//If the process at the ENDPOINT, it will return final result.
			Signal returnVal;
			Signal output;

			if(network.at(enter).inputConnected.at(0) != SIGNALPOINT)
				network.at(enter).SignalIn.push_back(Data);
			//Push previous Neural's output to next Neural's input.

			if(network.at(enter).isReady() )
			{

				auto output = network.at(enter).transferFunc(enter);
				outputStore.push_back(output);

				for(auto i : network.at(enter).outputConnected)
					output = go(i,output);
					//Recursive 
				returnVal = output;
				
			}

				return returnVal;
		}

//Provide for active(),or you can use to active part of network.
		
///////////////////////////////////////////////////Function active

	inline void active(){
		for(auto i : Entrance)
		{
			Signal nullSignal;
			nullSignal.SignalOrigin = SIGNALPOINT;
			
			Signal re = go(i,nullSignal);
			//Make a empty Signal to avtive the go().
		}
	}
//According to the Entrance, the function will acess any neural with go() and memoried the output of any part.

///////////////////////////////////////////////////Function modifyWeight

		inline void addWeight(unsigned int Neural,unsigned int Origin,double changeVal)
		{
			for(auto i : network.at(Neural).weight)
				if(i.SignalOrigin == Origin)
					i.value = changeVal;
			Weight pushed{pushed.SignalOrigin = Origin, pushed.value = changeVal};
			network.at(Neural).weight.push_back(pushed);
		}
//As the function name, modify the special Neural's weight.

//////////////////////////////////////////////////Function makeConnect

		inline void makeConnect(unsigned int inpSet, unsigned int outSet)
		{
			if(inpSet <= network.size())
				network.at(inpSet).outputConnected.push_back(outSet);

			if(outSet <= network.size())
				network.at(outSet).inputConnected.push_back(inpSet);	
		}
//As the function name, make two different Neural link. 
//And the first param is the Neural which receive the output Neural of second param.

//////////////////////////////////////////////////Function addNeural

		inline void addNeural(neural added, neuralID* returnID)
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
			return added.neuralMark; 
		}

//As the function name, add the new Neural to the network.

/////////////////////////////////////////////////Function deleteNeural

		inline void deleteNeural(unsigned int deleted){
			
			bool flag = false;

			for(auto i : network)
			{
				if(i.neuralMark == deleted)
				{
					flag = true;
					break;
				}
			}
			//Check the deleted whether in the network.
		
			if(flag){
				
				for(auto i : network.at(deleted).outputConnected)
				{
					for(int j=0 ; j<network.at(i).inputConnected.size() ; ++j)
					{
						if(*(network.at(i).inputConnected.begin() + j) == deleted)
							network.at(i).inputConnected.erase(network.at(i).inputConnected.begin() + j);
					}

					for(int j=0 ; j<network.at(i).weight.size() ; ++j)
					{
						if((network.at(i).weight.begin() + j)->SignalOrigin == deleted)
							network.at(i).weight.erase(network.at(i).weight.begin() + j);
					}

				}
			//Clean the relation of the deleted output.

				for(auto i : network.at(deleted).inputConnected)
				{
					for(int j=0 ; j<network.at(i).outputConnected.size() ;++j)
					{
						if(*(network.at(i).outputConnected.begin() + j) == deleted)
							network.at(i).outputConnected.erase(network.at(i).outputConnected.begin() + j);
					}
				}
				//Clean the relation of the deleted input.

				network.erase(network.begin() + deleted);
				updateID(deleted);
			}

		}
//As the function name, delete Neural.

/////////////////////////////////////////////////////////////////Function updateID

		void updateID(unsigned int deletedID)
		{

			for(auto i : IDlist)
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
		for(auto i : IDlist)
			if(i -> ID == added -> ID)
				return;
		//Check the struct of neuralID had be not added.
		IDlist.push_back(added);
	}
	//To addID.
	
///////////////////////////////////////////////////////////////Function makeSignalPoint

	static double emptyCountor(vector<Signal> ss, vector<Weight> ww)
	{return ss.at(0).value;}

	static Signal emptyJudge(double vv, unsigned int mm)
	{Signal returnVal{returnVal.SignalOrigin = mm, returnVal.value = vv};
	 return returnVal;}

	inline unsigned int makeSignalPoint()
	{
	
		neural SignalP(emptyCountor,emptyJudge);
		SignalP.inputConnected.push_back(SIGNALPOINT);
		auto markRt = addNeural(SignalP);
		
		addEntrance(markRt);

		return markRt;
	
	}

///////////////////////////////////////////////////////////////Function pushSignalIn

	void pushSignalIn(Signal In, unsigned int mark)
	{
		In.SignalOrigin =  SIGNALPOINT;
		network.at(mark).SignalIn.push_back(In);
	}

///////////////////////////////////////////////////////////////

	vector<Signal> getOutputVal(unsigned int get)
	{
		vector<Signal> returnSet;

		for(auto i : outputStore)
		{
			if(get == i.SignalOrigin)
				returnSet.push_back(i);
		}

		return returnSet;
	}

//////////////////////////////////////////////////////////////

		vector<neural>    network;
		vector<neuralID*> IDlist;
		vector<Signal>    outputStore;
		set<unsigned int> Entrance;

};

#endif
