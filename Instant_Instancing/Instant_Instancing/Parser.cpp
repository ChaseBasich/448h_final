#include "stdafx.h"
#include "Parser.h"

using namespace std;

void Parser::parseLine(string line)
{
	vector<string> tokens = tokenize(line);
	for (size_t i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << endl;
	}
}

vector<string> Parser::tokenize(string str)
{
	vector<string> tokens;
	size_t spaceLoc = -1;

	while (true) {
		size_t nextSpaceLoc = str.find(" ", spaceLoc + 1);
		if (nextSpaceLoc != string::npos)
		{
			tokens.push_back(str.substr(spaceLoc + 1, nextSpaceLoc - spaceLoc));
			spaceLoc = nextSpaceLoc;
		}
		else
			break;
	}
	tokens.push_back(str.substr(spaceLoc + 1));

	return tokens;
}