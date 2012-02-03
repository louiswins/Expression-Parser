#include "parser.h"
#include "lexer.h"
#include "ops.h"
#include <iostream>
#include <tr1/memory>
using namespace std;


int main() {
	parser p;

	while (p.has_expression()) {
		ptree_ptr expr = p.read_expression();

		if (expr) {
			expr->print();
			cout << "result: " << expr->eval() << "\n";
		}
		// Oh, RAII. How I love thee.
	}

	cout << "\n"; // There is an extra newline in the example files.

	return 0;
}
