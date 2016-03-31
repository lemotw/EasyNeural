#ifndef NEURAL_H
#define NEURAL_H

#include <vector>
#include <set>

using namespace std;

struct Signal
{
	unsigned int SignalOrigin;
	double 		 value;
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
		//Check whether the all input is contain in SignalIn.

/////////////////////////////////////////////////

		inline void addWeight(double wei, unsigned int mark){
			Weight weiAdd;
			weiAdd.SignalOrigin = mark;
			weiAdd.value        = wei;
			weight.push_back(weiAdd);
		}

		inline void addWeight(Weight weiAdd){weight.push_back(weiAdd);}

		//As the function name.
		
////////////////////////////////////////////////

		inline Signal transferFunc(unsigned int mark)
		{return judgeFunc(countValue(SignalIn,weight) ,mark);}

////////////////////////////////////////////////

		
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
