#include "neuralManager.h"



double signalPointCountor(vector<Signal> s, vector<Weight> w)
{return s[0].value;}

Signal signalPointJudge(double vv, unsigned int mm)
{
	Signal returnVal{returnVal.SignalOrigin = mm, returnVal.value = vv};
	return returnVal;
}
//To provide two function for makeSP make SignalPoint neuron.


/////////////////////////////////////////////////////Function addEntrance

void neuralManager::addEntrance(unsigned int mark)
{
	for(unsigned int i : Entrance)
		if(i == mark)
			return;
	Entrance.insert(mark);
	return;
}

////////////////////////////////////////////////////Function reDO

void neuralManager::reDO(unsigned int enter,Signal Data)
{

	if(enter == static_cast<unsigned int>(TypeOfSignalEnd::ENDPOINT))
	{
		Data.SignalOrigin = static_cast<unsigned int>(TypeOfSignalEnd::ENDPOINT);
		outputStore.push_back(Data);
		return;
	}
	//If the process at the static_cast<unsigned int>(TypeOfSignalEnd::ENDPOINT), it will return final result.
			
	if(network[enter].inputConnected[0] != static_cast<unsigned int>(TypeOfSignalEnd::SIGNALPOINT))
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

///////////////////////////////////////////////////Function active

void neuralManager::active(){
		
	outputStore.clear();

	for(auto i : Entrance)
	{
		Signal nullSignal;
		nullSignal.SignalOrigin = static_cast<unsigned int>(TypeOfSignalEnd::SIGNALPOINT);
			
		reDO(i,nullSignal);
		//Make a empty Signal to avtive the reDO().
	}

}

///////////////////////////////////////////////////Function addWeight

void neuralManager::addWeight(unsigned int Neural,unsigned int Origin,double changeVal)
{
	
	Weight     pushed{pushed.SignalOrigin = Origin, pushed.value = changeVal};

	connection con{con.inputEnd = Origin, con.outputEnd = Neural, 
				   con.weightVal = changeVal};
	//Make the con and weight which will be pushed.

	for(int i=0 ; i<network[Neural].weight.size() ; ++i)
		if(network[Neural].weight[i].SignalOrigin == Origin)
			network[Neural].weight.erase(network[Neural].weight.begin() + i);
			
	for(int i=0 ; i<connection_Table.size() ; ++i)
		if(connection_Table[i].inputEnd == Origin && connection_Table[i].outputEnd == Neural)
			connection_Table.erase(connection_Table.begin() + i);
	//Search whether they have been vector.

	network[Neural].weight.push_back(pushed);
	connection_Table.push_back(con);
}

void neuralManager::addWeight(connection con)
{

	Weight pushed{pushed.SignalOrigin = con.inputEnd, pushed.value = con.weightVal};
	//Make the weight who will be pushed.

	for(int i=0 ; i<network[con.outputEnd].weight.size() ; ++i)
		if(network[con.outputEnd].weight[i].SignalOrigin == con.inputEnd)
			network[con.outputEnd].weight.erase(network[con.outputEnd].weight.begin() + i);

	for(int i=0 ; i<connection_Table.size() ; ++i)
		if(connection_Table[i].inputEnd == con.inputEnd && connection_Table[i].outputEnd == con.outputEnd )
			connection_Table.erase(connection_Table.begin() + i);
	//Search for whether they have been vector.

	network[con.outputEnd].weight.push_back(pushed);
	connection_Table.push_back(con);
}

//////////////////////////////////////////////////Function makeConnect

void neuralManager::makeConnect(unsigned int source, unsigned int target, double weightVal=1.0)
{
	if(source <= network.size())
		network[source].outputConnected.push_back(target);

	if(target <= network.size())
		network[target].inputConnected.push_back(source);

	
	addWeight(target ,source ,weightVal);
}

//////////////////////////////////////////////////Function addNeural

void neuralManager::addNeural(countor initc ,judge initj ,unsigned int* ID)
{
	neural pushed(initc, initj);

	pushed.neuralMark = network.size();
	*ID               = pushed.neuralMark;

	IDlist.push_back(ID);
	network.push_back(pushed);
}

unsigned int neuralManager::addNeural(countor initc ,judge initj)
{
		
	neural pushed(initc, initj);

	pushed.neuralMark = network.size();
	network.push_back(pushed);
			
	return pushed.neuralMark;
}

unsigned int neuralManager::addNeural(neural pushed)
{
		
	pushed.neuralMark = network.size();
	network.push_back(pushed);
	return pushed.neuralMark;

}

/////////////////////////////////////////////////Function deleteNeural

void neuralManager::deleteNeural(unsigned int deleted){
			
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
				if(*(network[i].inputConnected.begin() + j) == deleted)
					network[i].inputConnected.erase(network[i].inputConnected.begin() + j);
					
			for(int j=0 ; j<network[i].weight.size() ; ++j)
				if((network[i].weight.begin() + j)->SignalOrigin == deleted)
					network[i].weight.erase(network[i].weight.begin() + j);

		}
		//Clean the relation of the deleted output.

		for(auto i : network[deleted].inputConnected)
		{
			for(int j=0 ; j<network[i].outputConnected.size() ;++j)
				if(*(network[i].outputConnected.begin() + j) == deleted)
					network[i].outputConnected.erase(network[i].outputConnected.begin() + j);
		
		}
		//Clean the relation of the deleted input.

		network.erase(network.begin() + deleted);
		updateID(deleted);
	}

}

/////////////////////////////////////////////////////////////////Function updateID

void neuralManager::updateID(unsigned int deletedID)
{

	for(auto i : IDlist)
	{
		if(*i > deletedID)
			*i = *i - 1;
	}
	//If the ID greater than the deletedID, then it will minus the ID from 1.
}
		 
////////////////////////////////////////////////////////////////Function addID

void neuralManager::addID(unsigned* added)
{
	for(auto i : IDlist)
		if(*i == *added)
			return;
	//Check the struct of neuralID had be not added.
	IDlist.push_back(added);
}
	
///////////////////////////////////////////////////////////////Function makeSP

unsigned int neuralManager::makeSP()
{

	neural SignalP(signalPointCountor,signalPointJudge);
	SignalP.inputConnected.push_back(static_cast<unsigned int>(TypeOfSignalEnd::SIGNALPOINT));
	auto markRt = addNeural(SignalP);
	//Make a neuron which use to translation Signal in the neural network.
		
	addEntrance(markRt);

	return markRt;
	
}

///////////////////////////////////////////////////////////////Function pushSignalIn

void neuralManager::pushSignalIn(Signal In, unsigned int mark)
{
	In.SignalOrigin =  static_cast<unsigned int>(TypeOfSignalEnd::SIGNALPOINT);
	network[mark].SignalIn.push_back(In);
}

///////////////////////////////////////////////////////////////Function getOutputVal

Signal neuralManager::getOutputVal(unsigned int forcus)
{

	for(Signal i : outputStore)
	{
		if(forcus == i.SignalOrigin)
			return i;
	}
	Signal ret{ret.SignalOrigin = static_cast<unsigned int>(TypeOfSignalEnd::SIGNALNULL), ret.value = 0.0};
	return ret;
}

//////////////////////////////////////////////////////////////Function deleteConnect

void neuralManager::deleteConnect(unsigned int inputEnd,unsigned int outputEnd)
{
	
	for(int i=0 ; i<network[inputEnd].outputConnected.size() ; ++i)
		if(network[inputEnd].outputConnected[i] == outputEnd)
			network[inputEnd].outputConnected.erase(network[inputEnd].outputConnected.begin() + i);
	
	for(int i=0 ; i<network[outputEnd].inputConnected.size() ; ++i)
		if(network[outputEnd].inputConnected[i] == inputEnd)
			network[outputEnd].inputConnected.erase(network[outputEnd].inputConnected.begin() + i);
		
	for(int i=0 ; network[outputEnd].weight.size() ; ++i)
		if(network[outputEnd].weight[i].SignalOrigin == inputEnd)
			network[outputEnd].weight.erase(network[outputEnd].weight.begin() + i);

	for(int i=0 ; i<connection_Table.size() ; ++i)
		if(connection_Table[i].inputEnd == inputEnd && connection_Table[i].outputEnd == outputEnd)
			connection_Table.erase(connection_Table.begin() + i);

}

/////////////////////////////////////////////////////////Function setEP

void neuralManager::makeEP(unsigned int target)
{
	network[target].outputConnected.push_back((unsigned int)TypeOfSignalEnd::ENDPOINT);

}

/////////////////////////////////////////////////////////
