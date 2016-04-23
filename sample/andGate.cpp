#include "neuralManager.h"
#include <iostream>

typedef Signal(*judge)(double,unsigned int);
typedef double(*countor)(vector<Signal>, vector<Weight>);
//Define function pointer type to init class.

Signal jud(double in,unsigned int mark);
double cou(vector<Signal> signalIn,vector<Weight> weight);
//Define the function of neural's count and transfer,basically the count function always is sum of the signal multiply weight.

int main(void)
{
	judge   initj = jud;
	countor initc = cou;

	neuralManager net;

	neural n1(initc,initj);

	double val;
	Signal signal;
	signal.SignalOrigin = 0;

	//The Signal in.

	net.addNeural(n1);

	net.makeConnect(SIGNALPOINT,0);
	net.makeConnect(0,ENDPOINT);
	//Make link.

	cout << "Input the first Signal:";
	cin >> val;
	signal.value = val;

	net.Signal_Init_Set.push_back(signal);

	cout << "Input the second Signal:";
	cin >> val;
	signal.value = val;

	net.network.at(0).SignalIn.push_back(signal);

	net.addEntrance(0);
	//Add entrance.

	vector<Signal> result;
	result = net.active();

//	std::cout << "x" << result[0].value << endl;

	for(auto i:result)
		cout << i.value << endl;
	//print result

	return 0;

}

Signal jud(double in,unsigned int mark)
{
	Signal returnVal;
	returnVal.SignalOrigin = mark;

//	cout << "The result of cou :" << in << endl;

	if(in == 2)
		returnVal.value = 1;
	else
		returnVal.value = 0;

//	cout << "The final output : " << returnVal.value << endl;

	return returnVal;
}

double cou(vector<Signal> signalIn,vector<Weight> weight)
{
	double sum = 0.0;

	for(auto i:signalIn)
	{
		sum += i.value;
//		cout << "Signal : " << i.value << endl;
	}

	return sum;
}
