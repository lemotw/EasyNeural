#ifndef NEURALCONFIGGER
#define NEURALCONFIGGER

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <queue>

#include "neuralManager.h"
#include "neuronFun.h"

using namespace std;

class FileReader
{

	public:

		FileReader(string path)
		{FileStream.open(path);}

		inline bool is_open()
		{return FileStream.is_open();}

		inline string get_Movement()
		{
			if(Line.size() > 0)
			{
				string LineRt = LineStore.front();
				LineStore.pop();
				return LineRt;
			}
			else
				return "END";
		}

		void load_Movement();

	private:

		ifstream FileStream;
		queue<string> LineStore;
}

class Configger
{

	public:

		Configger(string path)
		{file = new FileReader(path);}	
	
		inline changeManager(neuralManager& ref)
		{this.Manager = ref;}

		void store_Neuron(string);

		void make_Connect(string);
		
		countor get_countor(string);
		judge   get_judge(string);

		void config();



		map<string, countor> countorStore;
		map<string, judge>   judgeStore;
		//Accessable map for user push their own function

	private:

		FileReader 	  			 file;
		map<string,unsigned int> neuronTable;
		neuralManager& 			 Manager;
}
