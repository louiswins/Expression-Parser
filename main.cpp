#include "parser.h"
#include "ops.h"
#include <iostream>
#include <tr1/memory>
using namespace std;


int main() {
	parser p;

	ptree_ptr expr = p.read_expression();

	if (expr) {
		expr->print();
		cout << "result: " << expr->eval() << "\n";
	} else {
		cout << "no expression received.\n";
	}

	return 0;
}
