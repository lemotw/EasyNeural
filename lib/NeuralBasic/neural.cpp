#include "neural.h"
#include <stdlib.h>
//Neural

Neural::Neural(int inputSize ,int outputSize){
	outputID  = new bool[outputSize];
	for(int i=0;i<outputSize;++i)
		outputID[i] = false;

	inputLink = new Dendritic_Input[inputSize];
	//Create input end dendritic
	
	for(int i=0;i<inputSize;++i)
		inputLink[i].modifyWeight(1.0);
	//Set the weight
	
	outputLink = new Dendritic_Output[outputSize];
	//Create output end dendritic
	
	for(int i=0;i<outputSize;++i)
		outputLink[i].modifyWeight(1.0);
	//Set the weight

	bias = 0.0;
}

Neural::Neural(int inputSize ,int outputSize ,double* weightOut, double* weightIn, double biasIn){

	inputLink = new Dendritic_Input[inputSize];
	//Create input end dendritic
	
	for(int i=0;i<inputSize;++i)
		inputLink[i].modifyWeight(weightIn[i]);
	//Set the weight

	outputLink = new Dendritic_Output[outputSize];
	//Create output end dendritic
	
	for(int i=0;i<outputSize;++i)
		outputLink[i].modifyWeight(weightOut[i]);
	//Set the weight

	bias = biasIn;
}

void Neural::comeinHandle(double signal ,short ID){

	sum += inputLink[ID].handle(signal);

}

void Neural::outputSignal(){

	for(int i=0;i<(sizeof(outputLink)/sizeof(Dendritic_Output));++i)
		if(!outputID[i])outputID[i] = true;

	for(int i=0;i<(sizeof(outputLink)/sizeof(Dendritic_Output));++i)
		if(!outputID[i])exit(0);

}

//Neural
