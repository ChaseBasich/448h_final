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
	vector<string> tokenize(string str);

	map<string, Procedure> procedures;
	map<string, Mesh> meshes;
	Procedure *currProcedure;
};
