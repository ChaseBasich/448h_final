#pragma once
#include <string>

using namespace std;
class Symbol
{
public:
	Symbol(int index, double min, double max);
	~Symbol();

	bool isEvaluated();
	double eval();
	void reset();

private:
	int index;
	double min;
	double max;
	
	double value;
	bool evaluated;

	/*
	enum SymType {
		Constant, Cos, Sin, Combination, Random
	};

	enum Operator {
		Add, Subtract, Multiply
	};

	Symbol();
	Symbol(double value);
	Symbol(string equation);
	~Symbol();

	double Evaluate();
	double ReEvaluate();

	SymType GetType();

	Symbol& operator* (Symbol &s);
	Symbol& operator+ (Symbol &s);
	Symbol& operator- (Symbol &s);

	Symbol& operator+= (Symbol &s);
	Symbol& operator-= (Symbol &s);
private:
	SymType type;
	double value;
	double scale;

	//for 

	//for combination symbols
	Symbol *child1;
	Symbol *child2;
	Operator op;

	*/
};

