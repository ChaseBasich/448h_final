#include "stdafx.h"
#include "Parser.h"
#include "Cube.h"
#include "Sphere.h"

using namespace std;

//returns true on success, false on failure
bool Parser::parseFile(string &fileName) {
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

void Parser::parseLine(string &line)
{
	vector<string> tokens = tokenize(line);
	/*
	for (size_t i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << endl;
	}
	*/
	if (tokens.size() == 0)
		return;
	else if (tokens[0].compare("Cube") == 0) {
		meshes[tokens[1]] = Cube();
	}
	else if (tokens[0].compare("Sphere") == 0) {
		meshes[tokens[1]] = Sphere(false);
	}
	else if (tokens[0].compare("Mesh") == 0) {
		meshes[tokens[1]] = Mesh(tokens[2]);
	}
	else if (tokens[0].compare("Procedure") == 0) {
		procedures[tokens[1]] = Procedure();
		currProcedure = &(procedures[tokens[1]]);
	}
	else if (tokens[0].compare("Translate") == 0) {
		currProcedure->addTranslate(parseVal(tokens[1]), parseVal(tokens[2]), parseVal(tokens[3]));
	}
	else if (tokens[0].compare("Rotate") == 0) {
		pair<float, float> zero(0, 0);
		pair<float, float> one(1, 1);
		if (tokens[1].compare("X") == 0) {
			currProcedure->addRotate(one, zero, zero, parseVal(tokens[2]));
		} else if (tokens[1].compare("Y") == 0) {
			currProcedure->addRotate(zero, one, zero, parseVal(tokens[2]));
		} else if (tokens[1].compare("Z") == 0) {
			currProcedure->addRotate(zero, zero, one, parseVal(tokens[2]));
		} else {
			currProcedure->addRotate(parseVal(tokens[1]), parseVal(tokens[2]), parseVal(tokens[3]), parseVal(tokens[4]));
		}
	}
	else if (tokens[0].compare("Scale") == 0) {
		currProcedure->addScale(parseVal(tokens[1]), parseVal(tokens[2]), parseVal(tokens[3]));
	}
	else if (tokens[0].compare("Instance") == 0) {
		currProcedure->addInstance(meshes[tokens[1]]);
	}
	else if (tokens[0].compare("Do") == 0) {
		pair<float, float> n(1, 1);
		if (tokens.size() == 3)
			n = parseVal(tokens[2]);
		currProcedure->addProcedure(procedures[tokens[1]], n.first, n.second, false);
	}
	else if (tokens[0].compare("Add") == 0) {
		pair<float, float> n(1, 1);
		if (tokens.size() == 3)
			n = parseVal(tokens[2]);
		currProcedure->addProcedure(procedures[tokens[1]], n.first, n.second, true);
	}
	else if (tokens[0].compare("Evaluate") == 0) {
		meshes[tokens[2]] = procedures[tokens[1]].eval();
	}
	else if (tokens[0].compare("Save") == 0) {
		meshes[tokens[1]].Write(tokens[2]);
	}
}

vector<string> Parser::tokenize(string &str)
{
	size_t spaceLoc = -1;

	vector<string> tokens;

	if (str.length() == 0 || str[0] == '#')
		return tokens;

	while (true) {
		size_t nextSpaceLoc = str.find(" ", spaceLoc + 1);
		nextSpaceLoc = std::min(nextSpaceLoc, str.find("\t", spaceLoc + 1));
		if (nextSpaceLoc != string::npos)
		{
			tokens.push_back(str.substr(spaceLoc + 1, nextSpaceLoc - spaceLoc - 1));
			spaceLoc = nextSpaceLoc;
		}
		else
		{
			break;
		}
	}
	tokens.push_back(str.substr(spaceLoc + 1));

	return tokens;
}

pair<float, float> Parser::parseVal(string &str)
{
	if (str[0] == '[') {
		size_t commaLoc = str.find(',');
		float f1 = atof(str.substr(1, commaLoc - 1).c_str());
		float f2 = atof(str.substr(commaLoc + 1).c_str());
		return pair<float, float>(f1, f2);
	}
	else {
		float f = atof(str.c_str());
		return pair<float, float>(f, f);
	}
}