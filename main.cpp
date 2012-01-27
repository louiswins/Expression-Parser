#include "ops.h"
#include <iostream>
#include <tr1/memory>
using namespace std;


int main() {
	// magic lack of memory leaks! Huzzah!
	ptree_ptr tree(new amp_op(
		new pct_op(
			new pct_op(
				new at_op(
					new int_lit(3),
					new int_lit(4)
				)
			)
		),
		new at_op(
			new int_lit(5),
			new pct_op(
				new amp_op(
					new int_lit(6),
					new int_lit(7)
				)
			)
		)
	));
	tree->print();
	cout << "result: " << tree->eval() << "\n";

	return 0;
}
