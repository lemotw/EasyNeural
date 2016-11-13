#include "neurons.h"

double Hard_Limit(double signal)
{
	if(signal >= 0)
		return 1;
	else
		return 0;
}

double Hard_Limits(double signal)
{
	if(signal >= 0)
		return 1;
	else 
		return -1;
}

double Linear(double signal)
{return signal;}

double Saturating_Linear(double signal)
{
	if(signal <= 1 && signal >= 0)
		return signal;
	else
	{
		if(signal > 0)
			return 1;
		else
			return 0;
	}
}

double Saturating_Linears(double signal)
{
	if(signal <= 1 && signal >= -1)
		return signal;
	else
	{
		if(signal > 0)
			return 1;
		else
			return -1;
	}
}

double Postive_Linear(double signal)
{
	if(signal <= 0)
		return 0;
	else
		return signal;
}

double Log_Sigmoid(double signal)
{return 1/(1 + exp(signal) );}

double Hyperbolic_Tangent_Sigmoid(double signal)
{return (exp(signal) - exp(-signal) ) / (exp(signal) + exp(-signal) );}

double sumOfSignal(vector<Signal> signal ,vector<Weight> weight)
{
	double sum(0.0);
	
	for(auto i:signal)
	{
		for(auto j:Weight)
		{
			if(i.SignalOrigin == j.SignalOrigin)
				sum += i.value * j.value;
		}
	}

	return sum;
}
