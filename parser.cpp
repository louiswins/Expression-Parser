#include "ops.h"
#include "parser.h"
#include <iostream>
#include <sstream>
using namespace std;

ptree_ptr parser::read_expression() {
	ptree_ptr ret = ampersand_op();
	if (!match("\n")) {
		_l.flush_line();
		return ptree_ptr();
	}
	return ret;
}

ptree_ptr parser::ampersand_op() {
	ptree_ptr ret = percent_op();

	while (ret && _l.token() == "&") {
		match("&");
		ptree_ptr tmp = percent_op();
		if (!tmp) return ptree_ptr();
		ret = ptree_ptr(new amp_operator(ret, tmp));
	}

	return ret;
}

ptree_ptr parser::percent_op() {
	if (_l.token() == "%") {
		match("%");
		ptree_ptr tmp = percent_op();
		if (!tmp) return ptree_ptr();
		return ptree_ptr(new pct_operator(tmp));
	} else {
		return at_op();
	}
}

ptree_ptr parser::at_op() {
	ptree_ptr ret = term();

	if (ret && _l.token() == "@") {
		match("@");
		ptree_ptr tmp = at_op();
		if (!tmp) return ptree_ptr();
		ret = ptree_ptr(new at_operator(ret, tmp));
	}
	return ret;
}

ptree_ptr parser::term() {
	if (_l.token() == "(") {
		match("(");
		ptree_ptr ret = ampersand_op();
		if (!match(")")) return ptree_ptr();
		return ret;
	} else {
		return number();
	}
}

ptree_ptr parser::number() {
	int ret;
	if (!(istringstream(_l.token()) >> ret)) {
		// the conversion failed; it's not actually a number.
		return ptree_ptr();
	}
	match(_l.token());
	return ptree_ptr(new int_literal(ret));
}

bool parser::match(const string tok) {
	// lexical error
	if (!_l.good()) return false;
	if (tok == _l.token()) {
		_l.getToken();
		return true;
	} else {
		cout << "line " << _l.line_no() << " syntax error\n";
		return false;
	}
}
