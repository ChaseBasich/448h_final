#include "stdafx.h"
#include "Parser.h"

using namespace std;

//returns true on success, false on failure
bool Parser::parseFile(string fileName) {
	fstream file;
	file.open(fileName);

	string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			parseLine(line);
		}
		file.close();
		return true;
	}
	else {
		cout << "Can't open file" << endl;
		return false;
	}
}

void Parser::parseLine(string line)
{
	tokenize(line);
	for (size_t i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << endl;
	}
}

void Parser::tokenize(string str)
{
	size_t spaceLoc = -1;

	while (true) {
		size_t nextSpaceLoc = str.find(" ", spaceLoc + 1);
		if (nextSpaceLoc != string::npos)
		{
			tokens.push_back(str.substr(spaceLoc + 1, nextSpaceLoc - spaceLoc));
			spaceLoc = nextSpaceLoc;
		}
		else
		{
			break;
		}
	}
	tokens.push_back(str.substr(spaceLoc + 1));
}