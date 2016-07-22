#include "networkMaker.h"


//FileReader-----------------------

void FileReader::storeToken(std::string currentStr)
{

	Token stored;

	stored.Token_str = currentStr;

	switch(currentStr)
	{
		case "+":
		case "-":
		case "*":
		case "/":
			stored.Token_type = OPERATER_TOKEN;
			this.TokenBuffer.push(stored);
			break;

		case "(":
			stored.Token_type = RIGHT_SMALL_BLACKETS;
			this.TokenBuffer.push(stored);
			break;

		case ")":
			stored.Token_type = LEFT_SMALL_BLACKETS;
			this.TokenBuffer.push(stored);
			break;

		case "{":
			stored.Token_type = RIGHT_MID_BLACKETS;
			this.TokenBuffer.push(stored);
			break;

		case "}":
			stored.Token_type = LEFT_MID_BLACKETS;
			this.TokenBuffer.push(stored);
			break;

		case ";":
			stored.Token_type = END_TOKEN;
			this.TokenBuffer.push(stored);
			break;

		case "neuron":
		case "var":
			stored.Token_type = DECLEAR_TOKEN;
			this.TokenBuffer.push(stored);
			break;

		default:
			stored.Token_type = NAME_TOKEN;
			this.TokenBuffer.push(stored);
			break;
	}
}

//----------------------------------------

void FileReader::scanWord(std::string scannedString)
{

	std::string word = "";
	bool startScan   = true;

	for(char innerChr : scannedString)
	{
	
		if(innerChr == ';' || innerChr == '=' || 
		   innerChr == '{' || innerChr == '}' || 
		   innerChr == '(' || innerChr == ')' ||
		   innerChr == '+' || innerChr == '-' ||
		   innerChr == '*' || innerChr == '/')
		{
			
			if(word != "")
				this.storeToken(word);

			word = innerChr;
			this.storeToken(word);

			word = "";
			startScan = true;
			continue;
		
		}
	
		if(startScan)
		{
		
			if(innerChr == ' ' || innerChr == '\t')
				continue;
			else
			{
				startScan = false;
				word     += innerChr;
				continue;
			}
		
		}

		if(innerChr == ' ' || innerChr == '\t')
		{
		
			startScan = true;
			this.storeToken(word);
			word      = "";
			continue;

		}
		else
		{

			word     += innerChr;
			continue;

		}
	}

	return;

}

//-----------------------------

Token FileReader::read_Word()
{

	if(this.wordBuffer.empty())
	{

		std::string linePara = this.read_Line();
		Token returnVal;

		this.scanWord(linePara);

		returnVal	         = this wordBuffer.front();
		this.wordBuffer.pop();
		return returnVal;
		
	}
	else
	{
	
		Token returnVal = this wordBuffer.front();
		this.wordBuffer.pop();
		return returnVal;
	
	}

}

//--------------------------------

//--------------------------------Parser

inline void Parser::loadLine()
{
	Token inFor;
	Line recurrentLine;

	for(inFor=reader.read_Word() ; loader.Token_type==END_TOKEN ; loader=reader.read_Word() )
		recurrentLine.Tokens = inFor;	
	
	this.LineBuffer.push(recurrentLine);
}

void Parser::classify(Line &classified)
{
	bool operateFlag = false;
	bool declareFlag = false;

	for(auto i:classified.Tokens)
	{

		if(i.Token_type == DECLARE_TOKEN)
			declareFlag = true;

		if(i.Token_type == END_TOKEN)
		{

			if(declareFlag)
			{
				classified.Flag = INIT;
				return;
			}

			classified.Flag = DESIGNATE;
			return;
		}

		if(i.Token_type == OPERATER_TOKEN)
			operateFlag = true;

	}

	if(declareFlag)
		classified.Flag = DECLEAR
	else if(operateFlag)
		classified.Flag = OPERATE;
	else
		classified.Flag = NARRATIVE;

}

//--------------------------------
