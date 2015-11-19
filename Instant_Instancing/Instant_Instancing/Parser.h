#include <map>
#include <vector>
#include "Procedure.h"
#include "Mesh.h"

#pragma once
class Parser
{
public:
	Parser() {}
	~Parser() {}

	void parseLine(std::string line);

private:
	std::vector<std::string> tokenize(std::string str);

	std::map<std::string, Procedure> procedures;
	std::map<std::string, Mesh> meshes;
};