#include "parser.h"
#include "ops.h"
#include <iostream>
#include <tr1/memory>
using namespace std;


int main() {
	parser p;

	ptree_ptr expr = p.read_expression();

	expr->print();
	cout << "result: " << expr->eval() << "\n";

	return 0;
}
