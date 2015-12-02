#include "stdafx.h"
#include "Symbol.h"

/*
Symbol& Symbol::operator*(Symbol &s) {
	if (type == SymType::Constant) {
		if (s.type == SymType::Constant) {
			return Symbol(value * s.value);
		}
		else {
			Symbol copy(s);
			copy.scale *= value;
			return copy;
		}
	}

	else if (s.type == SymType::Constant) {
		Symbol copy(*this);
		copy.scale *= s.value;
		return copy;
	}

	else {
		Symbol combo;
		combo.child1 = *this;
	}


	
}

Symbol& Symbol::operator-(Symbol &s) {
	if (type == SymType::Constant){
		if (s.type == SymType::Constant){
			return Symbol(value + s.value);
		}
	}
}
Symbol& Symbol::operator-(Symbol &s) {
	if (type == SymType::Constant){
		if (s.type == SymType::Constant){
			return Symbol(value - s.value);
		}
	}
}
*/

void Symbol::reset() {
	value = 0;
	evaluated = false;
}

double Symbol::eval() {
	if (!evaluated) {
		value = (max - min) * ((double)rand() / (double)RAND_MAX) + min;
		evaluated = true;
	}	
	return value;
}

bool Symbol::isEvaluated() {
	return evaluated;
}

Symbol::Symbol(int _index, double _min, double _max)
{
	index = _index;
	min = _min;
	max = _max;

	evaluated = false;
}


Symbol::~Symbol()
{
}
