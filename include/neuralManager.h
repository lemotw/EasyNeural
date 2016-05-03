#ifndef NEURALMANAGER_H
#define NEURALMANAGER_H

#define ENDPOINT    4294967295
#define SIGNALPOINT 4294967293
#define SIGNALNULL  4294967294

#define LINE_EXTENCTION_POINT 255
#define NORMAL                254

#include "neural.h"
#include <list>
#include <iostream>

struct connection
{
	unsigned int inputEnd;
	unsigned int outputEnd;

	char  		 status;
	double 		 weightVal;
};

class neuralManager
{
	public:

		neuralManager(){}

/////////////////////////////////////////////////////Function addEntrance

		inline void addEntrance(unsigned int mark)
		{
			for(unsigned int i : Entrance)
				if(i == mark)
					return;
			Entrance.insert(mark);
			return;
		}

//Add Entrance if the set dosen't contain as the new.

////////////////////////////////////////////////////Function reDO

		void reDO(unsigned int enter,Signal Data)
		{

			if(enter == ENDPOINT)
			{
				Data.SignalOrigin = ENDPOINT;
				outputStore.push_back(Data);
				return;
			}
			//If the process at the ENDPOINT, it will return final result.
			
			if(network[enter].inputConnected[0] != SIGNALPOINT)
				network[enter].SignalIn.push_back(Data);
			//Push previous Neural's output to next Neural's input.

			if(network[enter].isReady() )
			{

				Signal DataRecursive = network[enter].transferFunc(enter);
				network[enter].SignalIn.clear();
				outputStore.push_back(DataRecursive);

				for(auto i : network[enter].outputConnected)
					reDO(i,DataRecursive);
					//Recursive 
			}

				return;
		}

//Provide for active(),or you can use to active part of network.
		
///////////////////////////////////////////////////Function active

	inline void active(){
		
		outputStore.clear();

		for(auto i : Entrance)
		{
			Signal nullSignal;
			nullSignal.SignalOrigin = SIGNALPOINT;
			
			reDO(i,nullSignal);
			//Make a empty Signal to avtive the reDO().
		}

	}
//According to the Entrance, the function will acess any neural with reDO() and memoried the output of any part.

///////////////////////////////////////////////////Function modifyWeight

		inline void addWeight(unsigned int Neural,unsigned int Origin,double changeVal)
		{
			for(auto i : network[Neural].weight)
				if(i.SignalOrigin == Origin)
					i.value = changeVal;

			Weight pushed{pushed.SignalOrigin = Origin, pushed.value = changeVal};
			network[Neural].weight.push_back(pushed);
		}

		inline void addWeight(connection con)
		{
			for(auto i : network[con.outputEnd].weight)
				if(i.SignalOrigin == con.inputEnd)
				{
					i.value = con.weightVal;
					return;
				}

			Weight pushed{pushed.SignalOrigin = con.inputEnd, pushed.value = con.weightVal};
			network[con.outputEnd].weight.push_back(pushed);
		}
//As the function name, modify the special Neural's weight.

		inline void addWeight(unsigned int addIn, Weight weightAdd)
		{network[addIn].weight.push_back(weightAdd);}

//////////////////////////////////////////////////Function makeConnect

		inline void makeConnect(unsigned int inpSet, unsigned int outSet)
		{
			if(inpSet <= network.size())
				network[inpSet].outputConnected.push_back(outSet);

			if(outSet <= network.size())
				network[outSet].inputConnected.push_back(inpSet);	
		}
//As the function name, make two different Neural link. 
//And the first param is the Neural which receive the output Neural of second param.

//////////////////////////////////////////////////Function addNeural

		inline void addNeural(neural added, unsigned int* returnID)
		{
			added.neuralMark = this -> network.size();
			*returnID        = added.neuralMark;

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
					//Make sure whether the neural mark which you want to delete exist in network.
				}
			}
		
			if(flag){
				
				for(unsigned int i : network[deleted].outputConnected)
				{
					for(int j=0 ; j<network[i].inputConnected.size() ; ++j)
					{
						if(*(network[i].inputConnected.begin() + j) == deleted)
							network[i].inputConnected.erase(network[i].inputConnected.begin() + j);
					}

					for(int j=0 ; j<network[i].weight.size() ; ++j)
					{
						if((network[i].weight.begin() + j)->SignalOrigin == deleted)
							network[i].weight.erase(network[i].weight.begin() + j);
					}

				}
				//Clean the relation of the deleted output.

				for(auto i : network[deleted].inputConnected)
				{
					for(int j=0 ; j<network[i].outputConnected.size() ;++j)
					{
						if(*(network[i].outputConnected.begin() + j) == deleted)
							network[i].outputConnected.erase(network[i].outputConnected.begin() + j);
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
				if(*i > deletedID)
					*i = *i - 1;
			}
			//If the ID greater than the deletedID, then it will minus the ID from 1.
		}
		//When deleteNeural() has been used ,then it will call this function to update
		 

////////////////////////////////////////////////////////////////Function addID
	inline void addID(unsigned* added)
	{
		for(auto i : IDlist)
			if(*i == *added)
				return;
		//Check the struct of neuralID had be not added.
		IDlist.push_back(added);
	}
	//To addID.
	
///////////////////////////////////////////////////////////////Function makeSignalPoint

	static double emptyCountor(vector<Signal> ss, vector<Weight> ww)
	{return ss[0].value;}

	static Signal emptyJudge(double vv, unsigned int mm)
	{Signal returnVal{returnVal.SignalOrigin = mm, returnVal.value = vv};
	 return returnVal;}

	inline unsigned int makeSignalPoint()
	{
	
		neural SignalP(emptyCountor,emptyJudge);
		SignalP.inputConnected.push_back(SIGNALPOINT);
		auto markRt = addNeural(SignalP);
		//Make a neuron which use to translation Signal in the neural network.
		
		addEntrance(markRt);

		return markRt;
	
	}

///////////////////////////////////////////////////////////////Function pushSignalIn

	void pushSignalIn(Signal In, unsigned int mark)
	{
		In.SignalOrigin =  SIGNALPOINT;
		network[mark].SignalIn.push_back(In);
	}

///////////////////////////////////////////////////////////////

	Signal getOutputVal(unsigned int forcus)
	{

		for(Signal i : outputStore)
		{
			if(forcus == i.SignalOrigin)
				return i;
		}
		Signal ret{ret.SignalOrigin = SIGNALNULL, ret.value = 0.0};
		return ret;
	}

//////////////////////////////////////////////////////////////Function deleteConnection

	void deleteConnection(unsigned int inputEnd,unsigned int outputEnd)
	{
	
		for(int i=0 ; network[inputEnd].outputConnected.size() ; ++i)
		{
		
			if(*(network[inputEnd].outputConnected.begin() + i) == outputEnd)
				network[inputEnd].outputConnected.erase(network[inputEnd].outputConnected.begin() + i);
	
		}

		for(int i=0 ; i<network[outputEnd].inputConnected.size() ; ++i)
		{
		
			if(*(network[outputEnd].inputConnected.begin() + i) == inputEnd)
				network[outputEnd].inputConnected.erase(network[outputEnd].inputConnected.begin() + i);
		
		}

		for(int i=0 ; network[outputEnd].weight.size() ; ++i)
		{
			if(network[outputEnd].weight[i].SignalOrigin == inputEnd)
				network[outputEnd].weight.erase(network[outputEnd].weight.begin() + i);
		}
	}
//////////////////////////////////////////////////////////////Function make_connection_table

   	double make_connection_table(unsigned int enter, unsigned int origin)
	{

		static bool flag = true;
		if(flag)
		{
			connection_Table.clear();
			flag = false;

			for(auto i:Entrance)
				make_connection_table(i, SIGNALPOINT);

			return 0.0;
		}
		else
		{
		
			connection pushed;
			pushed.inputEnd = enter;

			if(network[enter].outputConnected.size() > 1)
				pushed.status = LINE_EXTENCTION_POINT;
			else
				pushed.status = NORMAL;

			for(auto i:network[enter].outputConnected)
			{
				pushed.outputEnd = i;
				pushed.weightVal = make_connection_table(i, enter);
				connection_Table.push_front(pushed);
			}

		for(auto i:network[enter].weight)
				if(i.SignalOrigin == origin)
					return i.value;
			return 0.0;
		
		}
	}

//////////////////////////////////////////////////////////////
		vector<neural>        network;
		vector<Signal>        outputStore;

		vector<unsigned int*> IDlist;
		set<unsigned int>     Entrance;
		list<connection>	  connection_Table;
};

#endif
