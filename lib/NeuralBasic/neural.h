#ifndef NEURAL_H
#define NEURAL_H

class Dendritic_Input;
class Dendritic_Output;

class Neural{

    public:

		Neural() : bias{0.0} {}
    	Neural(int ,int);
		Neural(int ,int ,double* ,double* ,double);

		~Neural(){delete outputID;}

	    void outputSignal();
        //Assign the signal for every output Dendritics
        void comeinHandle(double ,short);
        //Get input Signal and pair ID for get weight
		short getIDcounter(){return IDcounter;}

    private:
	    Dendritic_Input * inputLink;
    	//This for input end dendritic array
	    Dendritic_Output* outputLink;
    	//This for output end dendritic array
        
		bool * outputID;
        double bias;
		double sum;
		short IDcounter;

};


class Dendritic_Output{

    public:
		Dendritic_Output() : weight{0.0}, connected{nullptr} {}

    	Dendritic_Output(double wei ,Neural* connTo) : weight{wei}, connected{connTo} {}

	    void output(double Signal){connected -> comeinHandle(Signal, connected->getIDcounter());}
    	//Sendout the signal.
    	void modifyWeight(double wei){weight = wei;}
    	//Make a interface for outside to modify inner weight
    	void modifyConnect(Neural* connTo){connected = connTo;}
    	//Make a interface for outside to modify inner Connect

    private:
	    Neural* connected;
	    //Contain address which neural this dendritic is connect with
	    double weight;

};

class Dendritic_Input{

	public:
		Dendritic_Input() : weight{0.0} {}

		Dendritic_Input(double wei) : weight{wei} {}

	    double handle(double Signal){
			Signal*=weight;
			return Signal;
		}
    	//Handle the income signal
    	void modifyWeight(double wei){weight = wei;}
    	//Make a interface for outside to modify inner weight

	private:
		double weight;
};

#endif
