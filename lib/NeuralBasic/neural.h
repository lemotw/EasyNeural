#ifndef NEURAL_H
#define NEURAL_H

class Dendritic_Output{

    public:
    	Dendritic_Output(double ,Neural*);

	    bool outPut(double);
    	//Sendout the signal.
    	void modifyWeight(double);
    	//Make a interface for outside to modify inner weight
    	void modifyConnect(Neural*);
    	//Make a interface for outside to modify inner Connect

    priate:
	    Neural* connected;
	    //Contain address which neural this dendritic is connect with
	    double weight;

};

class Dendritic_Input{

	public:
		Dendritic_Input();

	    void handle(double);
    	//Handle the income signal
    	void modifyWeight(double );
    	//Make a interface for outside to modify inner weight

	private:
		double weight;
};

class Neural{

    public:

		Neural(){inputLink=NULL,outputLink=NULL,bias=0.0;}
    	Neural(int ,int);
		Neural(int ,int ,double* ,double* ,double);

		~Neural()

	    void outputSignal(double);
        //Assign the signal for every output Dendritics
        void comeinHandle(double ,short);
        //Get input Signal and pair ID for get weight
		short getIDcounter(){return IDcounter;}


    private:
	    Dendritic * inputLink;
    	//This for input end dendritic array
	    Dendritic * outputLink;
    	//This for output end dendritic array
        
		bool * outputID;
        double bias;
		double sum;
		short IDcounter;

};

#endif
