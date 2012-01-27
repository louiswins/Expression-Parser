#include "ops.h"
#include <iostream>
#include <cassert>

static void indentify(int how_much) {
	while (how_much--) std::cout << "   ";
}

int amp_op::eval() {
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
void amp_op::print(int indent) {
	indentify(indent);
	std::cout << "&\n";
	l->print(indent+1);
	r->print(indent+1);
}
int pct_op::eval() {
	int a = t->eval();
	// (5a >= 3a+10) == (a >= 5)
	return (a >= 5) ? 5*a : 3*a+10;
}
void pct_op::print(int indent) {
	indentify(indent);
	std::cout << "%\n";
	t->print(indent+1);
}
int at_op::eval() {
	int a = l->eval(),
	    b = r->eval();
	assert(b != 0);
	return (a+5) % b;
}
void at_op::print(int indent) {
	indentify(indent);
	std::cout << "@\n";
	l->print(indent+1);
	r->print(indent+1);
}
