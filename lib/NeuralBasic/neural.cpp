#include "neural.h"

//Dendritic_Output

Dendritic_Output::Dendritic_Output(){
    weight    = NULL;
	connected = NULL;
}

Dendritic_Output::Dendritic_Output(double wei,Neural * connect){

    weight    = wei;
	connected = connect;

}

void Dendritic_Output::modifyConnect(Neural* newConnect){
    connected = newConnect;
}

void Dendritic_Output::modifyWeight(double incomeWeight){    
	weight = incomeWeight;
}

double Dendritic_Output::output(double Signal){

	connected->comeinHandle(Signal,connected->getIDcounter() );

}

//Dendritic_Output


//Dendritic_Input

Dendritic_Input::Dendritic_Input(){
    weight    = NULL;
}

Dendritic_Input::Dendritic_Input(double wei){
    weight = wei;
}

void Dendritic_Input::modifyWeight(double incomeWeight){
    weight = incomeWeight;    
}

double Dendritic_Input::handle(double Signal){
    Signal *= weight;
	return Signal;
}


//Dendritic_Input


//Neural

Neural::Neural(int inputSize ,int outputSize){
	outputID  = new bool[outputSize];
	for(int i=0;i<outputSize;++i)
		bool[i] = false;

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

Neural::Neural(int intputSize ,int outputSize ,double* weightOut, double* weightIn, double biasIn){

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
		if(outputLink[i].outPut() && !outputID[i])outputID[i] = true;

	for(int i=0;i<(sizeof(outputLink)/sizeof(Dendritic_Output));++i)
		if(!outputID[i])exit(0);

}

//Neural
