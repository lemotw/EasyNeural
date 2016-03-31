#include "neuralManager.h"
#include <iostream>

using namespace std;

typedef Signal(*judge)(double,unsigned int);
typedef double(*count)(vector<Signal>, vector<Weight>);
//Define function pointer type to init class.

Signal jud(double in,unsigned int mark);
double cou(vector<Signal> signalIn,vector<Weight> weight);
//Define the function of neural's count and transfer,basically the count function always is sum of the signal multiply weight.

int main(void)
{
	judge initj = jud;
	count initc = cou;

	neuralManager net;

	neural l1(initc, initj) ,l2(initc, initj) ,l3(initc, initj) ,l4(initc, initj);

	double firSignal = 7;
	double secSignal = 4;

	//Signal for first Entrance and second Entrance.

	net.addNeural(l1);net.addNeural(l2);net.addNeural(l3);net.addNeural(l4);

	net.makeConnect(SIGNALPOINT,1);
	net.makeConnect(SIGNALPOINT,4);
	net.makeConnect(4,1);
	net.makeConnect(1,2);
	net.makeConnect(2,3);
	net.makeConnect(3,ENDPOINT);

	//Make connect

	Signal signal;
	signal.SignalOrigin = SIGNALPOINT;
	signal.value        = firSignal;
	
	net.network.at(0).SignalIn.push_back(signal);

	signal.value        = secSignal;

	net.network.at(3).SignalIn.push_back(signal);

	//Full the Entrance Neural's SignalIn which must be fulled.
	
	net.addEntrance(1);
	net.addEntrance(4);

	vector<Signal> result;
//    cout << net.couTest(2);
	result = net.active();

	for(auto i:result)
		cout << i.SignalOrigin << ":" << i.value << endl;

	//That the network work.

	return 0;

}

Signal jud(double in,unsigned int mark)
{
	Signal returnVal;
	returnVal.SignalOrigin = mark;	

	if(in > 5)
		returnVal.value = in;
	else
		returnVal.value = 0;
	cout << "ssssssssssssssssssss";

	return returnVal;
}

double cou(vector<Signal> signalIn,vector<Weight> weight)
{
	double sum(6.0);

//	for(auto i:signalIn)
//	{
//		for(auto j:weight)
//			if(j.SignalOrigin == i.SignalOrigin)
//				sum += j.value*i.value;
//	}
//	if(sum == 0.0)
//		for(auto i:signalIn)
//			sum += i.value;
	cout << "sum" << sum << endl;
	return sum;
}
