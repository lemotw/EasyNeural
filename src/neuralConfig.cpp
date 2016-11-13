#include "neuralConfig.h"

//Jud
#define Hard_Limit					"Hard_Limit1"
#define Hard_Limits					"Hard_Limits1"
#define Linear          			"Linear1"
#define Saturating_Linear			"Saturating_Linear1"
#define Saturating_Linears 			"Saturating_Linears1"
#define Postive_Linear				"Postive_Linear1"
#define Log_Sigmoid					"Log_Sigmoid1"
#define Hyperbolic_Tangent_Sigmoid	"Hyperbolic_Tangent_Sigmoid1"

//Cou
#define sumOfSignal					"sumOfSignal1"
//For getFunction test

void initNeuron(string cou, string jud, string name)
{

	cout << "Init Neuron:" << name <<"  ";
	cout << "count:" << cou << "  ";
	cout << "judge:" << jud << endl;

}

void connect(string input, string output)
{

	cout << "connect " << input;
    cout << "with " << output << endl;

}

//Class: FileReader Config TestUnit

//FileReader


void FileReader::loadToken()
{

	if(FileStream.is_open())
	{
		regex ConFormat {R"(con<\s*I:\w+\s*,\s*O:\w+\s*>)"};
		regex NeuronFormat {R"(neuron<\s*Name:\w+\s*,\s*FunCou:\w+\s*,\s*FunJud:\w+\s*>)"};

		for(string str;getline(FileStream,str);)
		{
		
			auto Begin = sregex_iterator(str.begin(), str.end(), ConFormat);
			auto End   = sregex_iterator();

			for(auto i=Begin; i!=End ; ++i)
				TokenPool.push( (*i).str() );
			
			Begin      = sregex_iterator(str.begin(), str.end(), NeuronFormat);

			for(auto i=Begin; i!=End ; ++i)
				TokenPool.push( (*i).str() );	
		
		}	

	}
	else
		return;
}

string FileReader::getString()
{

	if(TokenPool.size() > 0)
	{
		string Rt( TokenPool.front() );
		TokenPool.pop();
		return Rt;
	}
	else
		return "";

}

//Config

queue<Token> Configer::analysisToken(string Line)
{

	queue<Token> Rt;

	while(true)
	{
		int pos = 0;	

		if( (pos = Line.find("I:") )!= string::npos)
			Rt.push(Token(InputNeuron,getAfterInfo(Line, pos+2) ) );

		else if( (pos = Line.find("O:") ) != string::npos)
			Rt.push(Token(OutputNeuron, getAfterInfo(Line, pos+2) ) );

		else if( (pos = Line.find("Name:") ) != string::npos)
			Rt.push(Token(NeuronName, getAfterInfo(Line, pos+5) ) );

		else if( (pos = Line.find("FunCou:") ) != string::npos)
			Rt.push(Token(FunctionCou, getAfterInfo(Line, pos+7) ) );

		else if( (pos = Line.find("FunJud:") ) != string::npos)
			Rt.push(Token(FunctionJud, getAfterInfo(Line, pos+7) ) );

		else
			break;
	}

	return Rt;
}

string Configer::getAfterInfo(string& MainLine, int pos)
{

	string Rtinfo("");
	bool flag = false;

	for(int i=pos ;/* MainLine[i] != ','||MainLine[i] != '>'*/ ; ++i)
	{

		if(MainLine[i] == ' '||MainLine[i] == '\t'||
		   MainLine[i] == ','||MainLine[i] == '>')
			
			if(flag)
				break;
			else
				continue;

		else
		{
			flag = true;
			Rtinfo += MainLine[i];
		}

	}

	MainLine = MainLine.substr(pos+Rtinfo.length(), MainLine.length());
	return Rtinfo;
}

string Configer::getFunctionCou(string functionName)
{

	if(functionName == "sumOfSignal")
		return sumOfSignal;
	else 
		return "";
}

string Configer::getFunctionJud(string functionName)
{

	if(functionName == "Hard_Limit")
		return Hard_Limit;

	else if(functionName == "Hard_Limits")
		return Hard_Limits;

	else if(functionName == "Linear")
		return Linear;

	else if(functionName == "Saturating_Linear")
		return Saturating_Linear;

	else if(functionName == "Saturating_Linears")
		return Saturating_Linears;

	else if(functionName == "Postive_Linear")
		return Postive_Linear;

	else if(functionName == "Log_Sigmoid")
		return Log_Sigmoid;

	else if(functionName == "Hyperbolic_Tangent_Sigmoid")
		return Hyperbolic_Tangent_Sigmoid;

	else
		return "";
}

void Configer::done()
{
	cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;

	while(true)
	{
	//Do perLine

		string analysised(getLine() );
		auto TokenList = analysisToken(analysised);
		
		bool moveType = analysised[0] == 'n'?true:false;
		//Select which type to do true(n) false(c)

		string Name, input ,output ,jud , cou;

		while(!TokenList.empty() )
		{
		//Do perMove
			cout << "aaaaaaa" <<endl;	
			auto i = TokenList.front();
			TokenList.pop();

			switch(i.first)
			{
				
				case TokenType::FunctionCou:
					if( (cou = couPool[i->second]) == "")
						if( (cou = getFunctionCou(i->second)) == "")

					break;

				case TokenType::FunctionJud:
					if( (jud = judPool[i->second]) == "")
						if( (jud = getFunctionJud(i->second)) == "")

					break;

				case TokenType::NeuronName:
					Name = i->second;
					break;
			
				case TokenType::InputNeuron:
					input = i->second;
					break;

				case TokenType::OutputNeuron:
					output = i->second;
					cout << "ssssssssssssssssssss" << endl;
					break;

				default:
					break;
			}	


			if(moveType && TokenList.empty() )
			{
				initNeuron(cou,jud,Name);
				break;
			//neuron
			}
			else if(TokenList.empty() )
			{
				connect(input,output);
				break;
			//connect
			}
		
		}

		if(analysised == "")
			break;
	}

}

bool Configer::addFunctionCou(string functionName, countor function)
{
	
	if(couPool.count(functionName) != 1)
		return false;
	
	couPool[functionName] = function;
	return true;

}

bool Configer::addFunctionJud(string functionName, judge function)
{
	
	if(judPool.count(functionName) != 1)
		return false;

	judPool[functionName] = function;
	return true;

}

bool Configer::rmFunctionCou(string functionName)
{

	if(couPool[functionName] == NULL)
		return false;

	couPool.erase(couPool.find(functionName));
	return true;

}

bool Configer::rmFunctionJud(string functionName)
{

	if(judPool[functionName] == NULL)
		return false;

	judPool.erase(judPool.find(functionName));
	return true;

}

//TestUnit

void TestUnit::testGetToken(string path)
{

	FileReader reader(path);

	reader.loadToken();

	string str(reader.getString());
	while(str.size())
	{
		cout << str << endl;
		str = reader.getString();
	}
	return;
}

void TestUnit::getString(string path)
{

	Configer configer(path);

	string linel(configer.getLine() );
	auto Tokens = configer.analysisToken(linel);

	while(!Tokens.empty())
	{
		
		Token rnd = Tokens.front();
		Tokens.pop();
		cout << rnd.second << " type: " << rnd.first << endl;
	
	}

	cout << linel <<endl;
	return;
}

void TestUnit::DoMovement(string path)
{
			
	Configer configer(path);
	configer.done();

	return;

}
