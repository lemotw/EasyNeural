#ifndef NEURAL_H
#define NEURAL_H

#include <vector>

using namespace std;

struct Signal
{
	unsigned int    SignalOrigin;
	double 			value;
}

typedef Signal (*judge)(double);
typedef double (*count)();

typedef Signal Weight;

class neural
{

	public:

		neural(unsigned int mark, judgeFunc judgeFunction)
		{
			judgeFunc  = judgeFunction;
			neuralMark = mark;
		}

///////////////////////////////////////////////////
		bool isReady()
		{
			vector<unsigned int> input = inputConnected;

			size_t size = input.size();
			unsigned int minus = 0;

			for(unsigned int i = 0;i < size;++i)
			{
				for(auto j : SignalIn)
				{
					if(j == *(input.begin()+i-minus))
					{
						x.erase(input.begin()+i-minus);
						++minus;
					}	
				}
			}

			if(input.empty() )
				return true;
			else
				return false;
		}

/////////////////////////////////////////////////

		bool operator == (const unsigned int & compare)
		{
			if(neuralMark == compare)
				return true;
			else 
				return false;
		}

////////////////////////////////////////////////

		noneParam           judgeFunc;
		count 				countValue;

		vector<unsigned int>    outputConnected;
		vector<unsigned int>	inputConnected;
		vector<Weight> 			weight;
		vector<Signal>			SignalIn;

		unsigned int   			neuralMark;
};


#endif
