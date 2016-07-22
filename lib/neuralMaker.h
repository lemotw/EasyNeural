#include "neuralManager.h"
#include "tokenType.h"

#include <string>
#include <queue>
#include <fstream>
#include <iostream>

using namespace std;

struct Token
{
	std::string Token_str;
	char        Token_type;
}

struct Line
{

	vector<Token> Tokens;
	char          Flag;

}

class FileReader
{

	public:

		//--------------------------------------------------------

		FileReader(std::string initPath)
		{
			file.open(initPath);
			path = initPath;
		}

		//--------------------------------------------------------
		
		inline void changeFile(std::string newPath)
		{
			file.open(newPath);
			path = newPath;
		}

		//--------------------------------------------------------

		inline bool isOpen()
		{return file.is_open();}

		//--------------------------------------------------------
		
		void storeToken();

		//--------------------------------------------------------

		inline char read_Char()
		{return file.get();}

		//--------------------------------------------------------

		inline std::string read_Line()
		{
			std::string returnLine;
			getline(file,line);
			return line;
		}

		//--------------------------------------------------------

		void scanWord(std::string);

		//--------------------------------------------------------

		inline void seek(int offset, std::ios_base::seekdir base);
		{file.seekg(offset, base);}
	
		//--------------------------------------------------------

		inline void seek(std::ios_base::seekdir base)
		{file.seekg(0, base);}

		//--------------------------------------------------------
		
		std::string read_Word();

		//--------------------------------------------------------
	private:

		std::string  path;
		queue<Token> TokenBuffer;
		ifstream     file;
}

class Parser
{

	public:

		inline void loadLine();
		void deToken();

	private:
		FileReader reader;
		queue<Line> lineBuffer;

}
