#include "stdafx.h"
#include "Parser.h"
#include "Cube.h"

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
	vector<string> tokens = tokenize(line);
	/*
	for (size_t i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << endl;
	}
	*/
	if (tokens.size() == 0)
		return;
	else if (tokens[0].compare("Cube")) {
		meshes[tokens[1]] = Cube();
	}
	else if (tokens[0].compare("Mesh")) {
		//ADD MESH CONSTRUCTOR THAT TAKES IN A FILENAME
		//meshes[tokens[1]] = Mesh(tokens[2]);
	}
	else if (tokens[0].compare("Procedure")) {
		procedures[tokens[1]] = Procedure();
		currProcedure = &(procedures[tokens[1]]);
	}
	else if (tokens[0].compare("Translate")) {
		currProcedure->addTranslate(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
	}
	else if (tokens[0].compare("Rotate")) {
		if (tokens[1].compare("X")) {
			currProcedure->addRotate(1, 0, 0, atof(tokens[2].c_str()));
		} else if (tokens[1].compare("Y")) {
			currProcedure->addRotate(0, 1, 0, atof(tokens[2].c_str()));
		} else if (tokens[1].compare("Z")) {
			currProcedure->addRotate(0, 0, 1, atof(tokens[2].c_str()));
		} else {
			currProcedure->addRotate(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()), atof(tokens[4].c_str()));
		}
	}
	else if (tokens[0].compare("Scale")) {
		currProcedure->addScale(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
	}
	else if (tokens[0].compare("Instance")) {
		currProcedure->addInstance(meshes[tokens[1]]);
	}
	else if (tokens[0].compare("Procedure")) {
		int n = 1;
		if (tokens.size() == 3)
			n = atoi(tokens[2].c_str());
		currProcedure->addProcedure(procedures[tokens[1]], n);
	}
	else if (tokens[0].compare("Evaluate")) {
		meshes[tokens[2]] = procedures[tokens[1]].eval();
	}
	else if (tokens[0].compare("Save")) {
		meshes[tokens[1]].Write(tokens[2]);
	}
}

vector<string> Parser::tokenize(string str)
{
	size_t spaceLoc = -1;

	vector<string> tokens;

	if (str[0] == '#')
		return tokens;

	while (true) {
		//TODO - SKIP TABS AS WELL
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