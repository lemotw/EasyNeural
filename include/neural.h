#ifndef NEURAL_H
#define NEURAL_H

#include <vector>

using namespace std;

typedef double (*judge)();
typedef double (*count)(double* ,int);

struct weightPoint
{
	int    weightFrom;
	double weight;
}

class neural
{

	public:

		neural(int mark, judgeFunc judgeFunction)
		{
			judgeFunc  = judgeFunction;
			neuralMark = mark;
		}

		noneParam           judgeFunc;
		count 				countValue;

		vector<int>         SignalOut;
		vector<weightPoint> weight;

		int                 neuralMark;
};


#endif
