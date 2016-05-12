#ifndef NEURAL_H
#define NEURAL_H

#define ENDPOINT    4294967295
#define SIGNALPOINT 4294967293

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
typedef double(*countor)(vector<Signal>, vector<Weight>);
//Two template of function pointer.

class neural
{

	public:

		neural(countor countFunction,judge judgeFunction)
		{this -> countValue = countFunction;this -> judgeFunc = judgeFunction;}

///////////////////////////////////////////////////Function isReady
		bool isReady()
		{
			vector<unsigned int> input = this -> inputConnected;
			//Cope a new input list.

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
			//Compare the input list and SignalIn.
			//If all pared, return True.

			if(input.empty() )
				return true;
			else
				return false;
		}

/////////////////////////////////////////////////Function addWeight

		inline void addWeight(double wei, unsigned int mark){
			Weight weiAdd;
			weiAdd.SignalOrigin = mark;
			weiAdd.value        = wei;
			weight.push_back(weiAdd);
		}

		inline void addWeight(Weight weiAdd){weight.push_back(weiAdd);}
		
////////////////////////////////////////////////Function transferFunc

		inline Signal transferFunc(unsigned int mark)
		{return judgeFunc(countValue(SignalIn,weight) ,mark);}

////////////////////////////////////////////////Operatir ==

		
		bool operator == (const unsigned int & compare)
		{
			if(this -> neuralMark == compare)
				return true;
			else 
				return false;
		}

////////////////////////////////////////////////

		judge    	            judgeFunc;
		countor 				countValue;

		vector<unsigned int>    outputConnected;
		vector<unsigned int>	inputConnected;
		vector<Weight> 			weight;
		vector<Signal>			SignalIn;

		unsigned int   			neuralMark;
};

#endif
