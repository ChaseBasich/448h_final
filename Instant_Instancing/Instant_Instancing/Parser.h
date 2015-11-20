#include <map>
#include <vector>
#include "Procedure.h"
#include "Mesh.h"

using namespace std;

#pragma once
class Parser
{
public:
	Parser() {}
	~Parser() {}

	bool parseFile(string fileName);//returns true on success
	void parseLine(string line);

private:

	void tokenize(string str);

	vector<string> tokens;
	map<string, Procedure> procedures;
	map<string, Mesh> meshes;
};