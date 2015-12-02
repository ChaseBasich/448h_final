#pragma once
#include <string>
#include "Symbol.h"
#include <vector>
#include <glm\glm.hpp>
#include <unordered_map>

#define NUM_ENTRIES 16
#define NUM_ROWS 4
#define NUM_COLS 4

using namespace std;

class SymbolicMatrix
{
public:
	SymbolicMatrix();
	SymbolicMatrix(glm::mat4 &m);
	SymbolicMatrix(string e[16]);
	~SymbolicMatrix();

	SymbolicMatrix RotateX(double min, double max);
	SymbolicMatrix RotateY(double min, double max);
	SymbolicMatrix RotateZ(double min, double max);

	glm::mat4 Eval();

	SymbolicMatrix& operator* (SymbolicMatrix &m);
	SymbolicMatrix& operator+ (SymbolicMatrix &m);
	SymbolicMatrix& operator- (SymbolicMatrix &m);

private:
	double evaluateString(string equation);
	/*
	string replaceNames(string equation);
	string replaceTrig(string equation);
	*/
	//used only in a 4x4 matrix, so 16 entries
	string entries[NUM_ENTRIES];
	unordered_map<int, Symbol> symbols;
};

