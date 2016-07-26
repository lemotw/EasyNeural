#include "neuralConfigger.h"

//FileReader/

void FileReader::load_Movement()
{

	regex ConFormat {R"(con<\s*I:\w+\s*,\s*O:\w+\s*>)"};
	regex NeuronFormat {R"(neuron<\s*name:\w+\s*,\s*FunCou:\w+\s*,\s*FunJud:\w+\s*>)"};

	for(string LinePer; getline(this.FileStream, LinePer);)
	{
	
		auto SearchBegin = sregex_iterator(LinePer.begin(), LinePer.end(), ConFormat);
		auto SearchEnd   = sregex_iterator();

		for(auto i=SearchBegin ; i!=SearchBegin ; ++i)
			this.LineStore.push(*i.str*());

		SearchBegin      = sregex_iterator(LinePer.begin(), LinePer.end(), NeuronFormat);

		for(auto i=SearchBegin ; i!=SearchBegin ; ++i)
			this.LineStore.push(*i.str*());
	}
}

//Configger

void Configger::make_Connect(string neuralConnnect)
{
	int offset = 0;
	string inputName  = "";
	string outputName = "";
	bool inputFlag  = false;
	bool outputFlag = false;

	for(char chr:neuralConnnect)
	{
	
		if(chr == "I:"[offset] && !outputFlag)
		{
			++offset;
			inputFlag  = true;
			continue;
		}

		else if(chr == "O:"[offset/3] && !inputFlag)
		{
			offset += 3;
			outputFlag = true;
			continue;
		}

		else if(offset == 2)
			inputName  += chr;

		else if(offset == 6)
			outputName += chr;

		else if(chr == ' ' || chr == '\t')
		{
			offset = 0;
			inputFlag  = false;
			outputFlag = false;
			inputName  = "";
			outputName = "";
		}
		else
		{
			offset = 0;
			inputFlag  = false;
			outputFlag = false;
			inputName  = "";
			outputName = "";	
		}
	//If the tag is Input then set the step to 1,
	//else set the step to 3.
	
	}

	Manager.makeConnect(this.neuronTable[inputName], this.neuronTable[outputName]);
}

void Configger::store_Neuron(string neuralSt)
{
	
	int offset        = 0;

	string neuronName = "";
	string couName 	  = "";
	string judName    = "";

	bool neuralFlag   = false;
	bool couFlag      = false;
	bool judFlag      = false;

	for(char chr:neuralConnnect)
	{
	
		if(chr == "name:"[offset] && (!couFlag || !judFlag) )
		{
			++offset;
			neuralFlag  = true;
			continue;
		}

		else if(chr == "FunCou:"[offset/5] && (!neuralFlag || !judFlag) )
		{
			offset += 5;
			couFlag = true;
			continue;
		}
		else if(chr == "FunJud:"[offset/31] && (!neuralFlag || !couFlag))
		{
			offset += 31;
			judFlag = true;
			continue;
		}

		else if(offset == 4)
			neuronName  += chr;

		else if(offset == 30)
			couName += chr;

		else if(offset == 186)
			judName += chr;

		else if(chr == ' ' || chr == '\t')
		{
			offset     = 0;
			neuralFlag = false;
			couFlag    = false;
			judFlag    = false;

			neuronName = "";
			couName    = "";
			judName    = "";
		}
		else
		{
			offset     = 0;
			neuralFlag = false;
			couFlag    = false;
			judFlag    = false;

			neuronName = "";
			couName    = "";	
			judName    = "";
		}
	}

	this.neuronTable[neuronName] = this.Manager.addNeural(get_countor(couName), get_judge(judName));
}

countor Configger::get_countor(string functionName)
{
	switch(functionName)
	{
		
		case "Hard_Limit":
			countor couRt = Hard_Limit;
			return couRt;

		case "Hard_Limits":
			countor couRt = Hard_Limits;
			return couRt;

		case "Linear":
			countor couRt = Linear;
			return couRt;

		case "Saturating_Linear":
			countor couRt = Saturating_Linear;
			return couRt;

		case "Saturating_Linears":
			countor couRt = Saturating_Linears;
			return couRt;

		case "Postive_Linear":
			countor couRt = Postive_Linear;
			return couRt;

		case "Log_Sigmoid":
			countor couRt = Log_Sigmoid;
			return couRt;

		case "Hyperbolic_Tangent_Sigmoid":
			countor couRt = Hyperbolic_Tangent_Sigmoid;
			return couRt;



		default:
			if(countorStore.count(functionName) > 0)
				return countorStore[functionName];
			else
				return nullptr;
	}
}

judge Configger::get_judge(string functionName)
{
	switch(functionName)
	{
		
		case "sumOfSignal":
			judge judRt = sumOfSignal;
			return judRt;

		default:
			if(judgeStore.count(functionName) > 0)
				return countorStore[functionName];
			else
				return nullptr;
	}
}

void config()
{

	this.file.load_Movement();

	for(string command = this.file.get_Movement() ;
		command != "END" ; command = this.file.get_Movement())
	{
	
		switch(command[0])
		{
			case 'n':
				store_Neuron(command);
				break;
			case 'c':
				make_Connect(command);
				break;
			default:
				continue;
		}
	
	}

}
