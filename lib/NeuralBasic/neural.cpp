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

void Dendritic_Output::handle(double Signal){
    Signal *= weight;

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

void Dendritic_Input::handle(double Signal){
    Signal *= weight;

}


//Dendritic_Input


//Neural

Neural::Neural(int inputSize ,int outputSize){

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

//Neural
