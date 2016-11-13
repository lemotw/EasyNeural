#include "neuralManager.h"
#include <iostream>

using namespace std;

typedef Signal(*judge)(double,unsigned int);
typedef double(*countor)(vector<Signal>, vector<Weight>);

Signal jud(double in,unsigned int mark)
{
	Signal returnVal;
	returnVal.SignalOrigin = mark;

	returnVal.value = in==2?1:0;

	return returnVal;
}

double cou(vector<Signal> signalIn,vector<Weight> weight)
{
	double sum = 0.0;

	for(auto i:signalIn)
		sum += i.value;

	return sum;
}

int main(void)
{
	judge   initj = jud;
	countor initc = cou;
	neuralManager net;

	double val;
	Signal signal;
	signal.SignalOrigin = static_cast<unsigned int>(TypeOfSignalEnd::SIGNALPOINT) ;

	unsigned int n1_mark   = net.addNeural(initc, initj);
	unsigned int signalin1 = net.makeSP();
	unsigned int signalin2 = net.makeSP();

	net.makeConnect(signalin1,n1_mark,1);
	net.makeConnect(signalin2,n1_mark,1);
	net.makeEP(n1_mark);
	
	net.addEntrance(signalin1);
	net.addEntrance(signalin2);

	cout << "Input the first Signal:";
	cin >> val;
	signal.value = val;
	net.pushSignalIn(signal, signalin1);

	cout << "Input the second Signal:";
	cin >> val;
	signal.value = val;
	net.pushSignalIn(signal, signalin2);

	net.active();
	cout << "Output: " << net.getOutputVal(n1_mark).value << endl;

	return 0;
}
