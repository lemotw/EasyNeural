#include "neuralManager.h"
#include <iostream>

using namespace std;

typedef Signal(*judge)(double, unsigned int);
typedef double(*countor)(vector<Signal>, vector<Weight>);

Signal jud(double in, unsigned int mark);

double cou(vector<Signal> signalIN, vector<Weight> weig);

int main(void)
{
	
	judge   initj = jud;
	countor initc = cou;

	neuralManager net;

	neural ne1(initc,initj);

	unsigned int ne1_mark = net.addNeural(ne1);
	unsigned int signalp  = net.makeSignalPoint();
	unsigned int signalp1 = net.makeSignalPoint();

	net.makeConnect(signalp, ne1_mark);
	net.makeConnect(signalp1, ne1_mark);
	net.makeConnect(ne1_mark,ENDPOINT);
	
	Weight weToSignal{weToSignal.SignalOrigin = signalp, weToSignal.value = 0.5};
	Weight weToSignal1{weToSignal.SignalOrigin = signalp1, weToSignal.value = 0.5};

	net.addWeight(ne1_mark, signalp, weToSignal.value);
	//net.addWeight(ne1_mark, signalp1, weToSignal1.value);

	Signal pp;
	pp.SignalOrigin = SIGNALPOINT;
	double in;

	cout << "Enter :";
	cin >> in;
	pp.value = in;

	net.pushSignalIn(pp, signalp);

	cout << "Enter :";
	cin >> in;
	pp.value = in;

	net.pushSignalIn(pp, signalp1);

	vector<Signal> result;

	result = net.active();

	for(auto i : result)
		cout << i.value << endl;

}

double cou(vector<Signal> signalIN, vector<Weight> weig)
{

	double sum = 0.0;
	bool flg   = true;
	for(auto i:signalIN)
	{
		for(auto j:weig)
		{
			if(j.SignalOrigin == i.SignalOrigin)
			{
				sum += j.value * i.value;
				cout << "In" << j.value * i.value << endl;
				flg = false;
				break;
			}
		}
		if(flg)
			sum += i.value;
		cout << "sumv" << sum << endl;
		flg = true;
	}

	return sum;
}

Signal jud(double in, unsigned int mark)
{
	Signal returnVal;
	returnVal.SignalOrigin = mark;
	if(in > 1)
		returnVal.value = 1;
	else if(in < 0)
		returnVal.value = 0;
	else
		returnVal.value = in;
	cout << returnVal.value;
	return returnVal;
}
