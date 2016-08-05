#include "neuralConfig.h"

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
		cout << MainLine[i];

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


	auto Tokens = configer.analysisToken(configer.getLine() );

	while(!Tokens.empty())
	{
		
		Token rnd = Tokens.front();
		Tokens.pop();
		cout << rnd.second << " type: " << rnd.first << endl;
	
	}
	return;
}
/*
void TestUnit::getName(string path)
{

	Configer configer(path);

	string str("");
	while(str = configer.searchName(config.getTokenLine()))
		cout << str << endl;

	return;

}
*/

#endif
