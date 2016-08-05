#ifndef NEURALCONFIG
#define NEURALCONFIG

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <regex>

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


	private:
			FileReader reader;

};

class TestUnit
{
	public:
		void testGetToken(string path); //FileReader	
		//Catch the Token in file.

		void getString(string TokenLine); //Configer
		//Try get Function info.
	
	//	void getName(string TokenLine); //Configer
		//Try get the value of var.

};
