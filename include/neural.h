#ifndef NEURAL_H
#define NEURAL_H

#include <vector>

using namespace std;

struct Signal
{
	unsigned int    SignalOrigin;
	double 			value;
};

struct Weight
{
	unsigned int SignalOrigin;
	double       value;
};

typedef Signal(*judge)(double,unsigned int);
typedef double(*count)(vector<Signal>, vector<Weight>);


class neural
{

	public:

		neural(count countFunction,judge judgeFunction)
		{this -> countValue = countFunction;this -> judgeFunc = judgeFunction;}

///////////////////////////////////////////////////
		bool isReady()
		{
			vector<unsigned int> input = this -> inputConnected;

			size_t size = input.size();
			unsigned int minus = 0;

			for(unsigned int i = 0;i < size;++i)
			{
				for(auto j : this -> SignalIn)
				{
					if(j.SignalOrigin == *(input.begin()+i-minus))
					{
						input.erase(input.begin()+i-minus);
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
			if(this -> neuralMark == compare)
				return true;
			else 
				return false;
		}

////////////////////////////////////////////////

		judge    	            judgeFunc;
		count 					countValue;

		vector<unsigned int>    outputConnected;
		vector<unsigned int>	inputConnected;
		vector<Weight> 			weight;
		vector<Signal>			SignalIn;

		unsigned int   			neuralMark;
};


#endif
