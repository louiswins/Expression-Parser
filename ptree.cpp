#include "ptree.h"
#include <iostream>
#include <cassert>

namespace {
	void indentify(int how_much) {
		while (how_much--) std::cout << "   ";
	}
}

// a & b == gcd(2+a, 3+b)
int amp_operator::eval() const {
	int a = 2 + l->eval(),
	    b = 3 + r->eval(),
	    t;
	while (b) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}
void amp_operator::print(int indent) const {
	indentify(indent);
	std::cout << "&\n";
	l->print(indent+1);
	r->print(indent+1);
}
// %a == max(5a, 3a+10)
int pct_operator::eval() const {
	int a = t->eval();
	// (5a >= 3a+10) == (a >= 5)
	return (a >= 5) ? 5*a : 3*a+10;
}
void pct_operator::print(int indent) const {
	indentify(indent);
	std::cout << "%\n";
	t->print(indent+1);
}
// a @ b == (a+5) mod b
int at_operator::eval() const {
	int a = l->eval(),
	    b = r->eval();
	assert(b != 0);
	return (a+5) % b;
}
void at_operator::print(int indent) const {
	indentify(indent);
	std::cout << "@\n";
	l->print(indent+1);
	r->print(indent+1);
}
