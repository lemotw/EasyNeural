#ifndef NEURAL_H
#define NEURAL_H

class Dendritic_Output{

    public:
    	Dendritic_Output(double ,Neural*);

	    void handle(double);
    	//Handle the income signal
    	void modifyWeight(double);
    	//Make a interface for outside to modify inner weight
    	void modifyConnect(Neural*);
    	//Make a interface for outside to modify inner Connect

    private:
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

	    void ouputSignal(double);
        //Assign the signal for every output Dendritics
        void comeinHandle(double ,short);
        //Get input Signal and pair ID for get weight

    private:
	    Dendritic * inputLink;
    	//This for input end dendritic array
	    Dendritic * outputLink;
    	//This for output end dendritic array
        
        double bias;
        //There put a bias that can modify which number added

};

#endif
