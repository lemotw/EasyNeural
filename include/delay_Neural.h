#ifndef DELAY_NEURAL_H
#define DELAY_NEURAL_H

#include "neural.h"

class delayNeural
{

	public: 

////////////////////////////////////Function transferFunc

		Signal transferFunc(unsigned int mark)		
		{
			SignalIn.at(0).SignalOrigin = mark;
			Signal returnVal = SignalIn.at(0);
			SignalIn.erase(SignalIn.begin() );

			return returnVal;
		}

////////////////////////////////////Function initSet

		inline void initSet(Signal init)
		{data.insert(data.begin() , init);}
		//Set the init value.

////////////////////////////////////

		vector<Signal>       SignalIn;

		vector<unsigned int> outputConnected;
		unsigned int inputConnected;

		unsigned int neuralMark;
};

#endif
