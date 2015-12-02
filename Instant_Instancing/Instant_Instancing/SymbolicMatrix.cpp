#pragma warning(disable:4996) 

#include "stdafx.h"
#include "SymbolicMatrix.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "exprtk\exprtk.hpp"

typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double> expression_t;
typedef exprtk::parser<double> parser_t;

unordered_map<int, Symbol> SymbolicMatrix::AddSymbols(unordered_map<int, Symbol> s1, unordered_map<int, Symbol> s2){
	unordered_map<int, Symbol> symbols;

	for (auto it = s2.begin(); it != s2.end(); it++) {
		symbols.insert(*it);
	}

	for (auto it = s1.begin(); it != s1.end(); it++) {
		symbols.insert(*it);
	}

	return symbols;
}

SymbolicMatrix SymbolicMatrix::operator* (SymbolicMatrix &m) {
	SymbolicMatrix copy;

	for (int i = 0; i < NUM_ROWS; i++){
		for (int n = 0; n < NUM_COLS; n++){
			string result = "(";

			for (int x = 0; x < NUM_ROWS; x++) {
				result += "(" + entries[i * NUM_ROWS + x];
				result += ")*(";
				result += m.entries[n + x * NUM_ROWS] + ")";
				if (x < NUM_ROWS - 1)
				{
					result += "+";
				}
			}
			result += ")";
			copy.entries[i * NUM_ROWS + n] = result;
		}
	}
	copy.symbols = AddSymbols(symbols, m.symbols);
	return copy;
}

SymbolicMatrix SymbolicMatrix::operator+ (SymbolicMatrix &m) {
	SymbolicMatrix copy;

	for (int i = 0; i < NUM_ROWS; i++){
		for (int n = 0; n < NUM_COLS; n++){
			copy.entries[i * NUM_ROWS + n] = "(" + entries[i * NUM_ROWS + n] + ")+(" + m.entries[i * NUM_ROWS + n] + ")";
		}
	}

	copy.symbols = AddSymbols(symbols, m.symbols);
	return copy;
}

SymbolicMatrix SymbolicMatrix::operator- (SymbolicMatrix &m) {
	SymbolicMatrix copy;

	for (int i = 0; i < NUM_ROWS; i++){
		for (int n = 0; n < NUM_COLS; n++){
			copy.entries[i * NUM_ROWS + n] = "(" + entries[i * NUM_ROWS + n] + ")-(" + m.entries[i * NUM_ROWS + n] + ")";
		}
	}

	copy.symbols = AddSymbols(symbols, m.symbols);
	return copy;
}

double SymbolicMatrix::toRadians(double angle) {
	return angle * M_PI / 180;
}

SymbolicMatrix SymbolicMatrix::RotateX(double min, double max) {
	SymbolicMatrix copy(*this);

	min = toRadians(min);
	max = toRadians(max);

	int index = rand();
	while (symbols.find(index) != symbols.end()) {
		index = rand();
	}

	copy.symbols.insert(pair<int, Symbol>(index, Symbol(index, min, max)));
	string name = "(s" + to_string(index) + ")";
	string cos = "cos(" + name + ")";
	string sin = "sin(" + name + ")";

	string newEntries[16] = {
		"1", "0", "0", "0",
		"0", cos , sin, "0",
		"0", sin, "-" + cos, "0",
		"0", "0", "0", "1"
	};

	SymbolicMatrix temp(newEntries);
	copy = temp * copy;

	return copy;
}

SymbolicMatrix SymbolicMatrix::RotateY(double min, double max) {
	SymbolicMatrix copy(*this);

	min = toRadians(min);
	max = toRadians(max);

	int index = rand();
	while (symbols.find(index) != symbols.end()) {
		index = rand();
	}

	copy.symbols.insert(pair<int, Symbol>(index, Symbol(index, min, max)));
	string name = "(s" + to_string(index) + ")";
	string cos = "cos(" + name + ")";
	string sin = "sin(" + name + ")";

	string newEntries[16] = {
		cos, "0", sin, "0",
		"0", "1", "0", "0",
		sin, "0", "-" + cos, "0",
		"0", "0", "0", "1"
	};

	SymbolicMatrix temp(newEntries);
	copy = temp * copy;

	return copy;
}

SymbolicMatrix SymbolicMatrix::RotateZ(double min, double max) {
	SymbolicMatrix copy(*this);

	min = toRadians(min);
	max = toRadians(max);

	int index = rand();
	while (symbols.find(index) != symbols.end()) {
		index = rand();
	}

	copy.symbols.insert(pair<int, Symbol>(index, Symbol(index, min, max)));
	string name = "(s" + to_string(index) + ")";
	string cos = "cos(" + name + ")";
	string sin = "sin(" + name + ")";

	string newEntries[16] = {
		cos, sin, "0", "0",
		sin, "-" + cos, "0", "0",
		"0", "0", "1", "0",
		"0", "0", "0", "1"
	};

	SymbolicMatrix temp(newEntries);
	copy = temp * copy;

	return copy;
}
/*
string SymbolicMatrix::replaceNames(string equation) {
	for (auto it = symbols.begin(); it != symbols.end(); it++) {
		int index = it->first;
		string name = "(s" + to_string(index) + ")";
		Symbol s = it->second;

		double value = s.eval();
		

		int start = 0;
		while ((start = equation.find(name, start)) != string::npos) {
			equation.replace(start, name.length(), to_string(value));
			start += to_string(value).length();
		}
	}
	
	return equation;
}

string SymbolicMatrix::replaceTrig(string equation) {

	string cosString = "cos(";

	int start = 0;
	while ((start = equation.find(cosString, start)) != string::npos) {
		int endParen = equation.find(")", start + cosString.length());
		double angle = stod(equation.substr(start, endParen - start));

		double value = cos(angle);

		equation.replace(start, endParen - start + 1, to_string(value));
		start += to_string(value).length();
	}

	string sinString = "sin(";

	int start = 0;
	while ((start = equation.find(sinString, start)) != string::npos) {
		int endParen = equation.find(")", start + sinString.length());
		double angle = stod(equation.substr(start, endParen - start));

		double value = sin(angle);

		equation.replace(start, endParen - start + 1, to_string(value));
		start += to_string(value).length();
	}
	return equation;
}
*/

double SymbolicMatrix::evaluateString(string equation) {

	symbol_table_t symbol_table;
	for (auto it = symbols.begin(); it != symbols.end(); it++) {
		string name = "s" + to_string(it->first);
		double val = it->second.eval();
		symbol_table.add_variable(name, val);
	}
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(equation, expression);

	return expression.value();
}

glm::mat4 SymbolicMatrix::Eval(){
	glm::mat4 results;
	for (int i = 0; i < 16; i++) {
		//column first for mat4
		int col = i % 4;
		int row = i / 4;
		results[col][row] = evaluateString(entries[i]);
	}
	//reset the random values after evaluating
	for (auto it = symbols.begin(); it != symbols.end(); it++) {
		it->second.reset();
	}
	return results;
}

SymbolicMatrix::SymbolicMatrix(string e[16]) 
{
	for (int i = 0; i < 16; i++){
		entries[i] = e[i];
	}
}

SymbolicMatrix::SymbolicMatrix(glm::mat4 &m)
{
	for (int i = 0; i < 4; i++){
		for (int n = 0; n < 4; n++) {
			//glm::mat4 is a column major matrix
			double val = m[i][n];

			int index = n * 4 + i;
			entries[i] = to_string(val);
		}
	}
}

SymbolicMatrix::SymbolicMatrix()
{
	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 4; n++) {
			if (i == n) {
				entries[i * 4 + n] = "1";
			}
			else {
				entries[i * 4 + n] = "0";
			}
		}
	}
}


SymbolicMatrix::~SymbolicMatrix()
{
}
