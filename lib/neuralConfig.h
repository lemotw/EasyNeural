#ifndef NEURALCONFIG
#define NEURALCONFIG

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <regex>
#include <map>

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
#define sumOfSignal					"sumOfSignal" 
//For getFunction test


using namespace std;

enum TokenType{FunctionCou, FunctionJud, NeuronName, 
			   InputNeuron, OutputNeuron};

typedef string countor;
typedef string judge;
typedef pair<TokenType, string> Token;

class FileReader
{
	public:

		FileReader(string path)
		{FileStream.open(path);}

		FileReader(){}

void loadToken();

		string getString();


/*
		bool changeFile(string path)
		{
		
			if(FileStream.open(path))
				return true;
			else
				return false;

		}
*/
	private:
		ifstream 	  FileStream;
		queue<string> TokenPool;
};

class Configer
{

	public:
		
		Configer(string path) : reader(path)
		{reader.loadToken();}

		string getLine()
		{return reader.getString();}
		//Done

		string eatSpace(string eaten)
		{
			string Rt("");

			for(char chr:eaten)
				if(chr == ' ' || chr == '\t')
					continue;
				else
					Rt += chr;

			return Rt; 
		}
		//Done

		queue<Token> analysisToken(string Line);
		//Done

		string  	 getAfterInfo(string& MainLine, int pos);
		//Done
		
		string		 getFunctionJud(string functionName);
		string		 getFunctionCou(string functionName);
		//Prepare Try

		bool         addFunctionCou(string functionName, countor function);
		bool		 addFunctionJud(string functionName, judge   function);

		bool		 rmFunctionCou(string functionName);
		bool		 rmFunctionJud(string functionName);

		void done();
		//Prepare Try

	private:
			FileReader			reader;
			map<string,countor> couPool;
			map<string,judge>   judPool;
};

class TestUnit
{
	public:
		void testGetToken(string path); //FileReader	
		//Catch the Token in file.

		void getString(string TokenLine); //Configer
		//Try get Function info.
	
		void DoMovement(string TokenLine); //Configer
		//Try get the value of var.

};

#endif
