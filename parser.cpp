#include "ops.h"
#include "parser.h"
#include <iostream>
#include <sstream>

ptree_ptr parser::read_expression() {
	l.getToken();
	ptree_ptr ret = ampersand_op();
	if (l.hasTokens()) {
		std::cout << "line " << l.line_no() << " syntax error\n";
		return ptree_ptr();
	}
	return ret;
}

ptree_ptr parser::ampersand_op() {
	ptree_ptr ret = percent_op();

	while (l.token() == "&") {
		match("&", "& expected");
		ret = ptree_ptr(new amp_operator(ret, percent_op()));
	}

	return ret;
}

ptree_ptr parser::percent_op() {
	if (l.token() == "%") {
		match("%", "% expected");
		return ptree_ptr(new pct_operator(percent_op()));
	} else {
		return at_op();
	}
}

ptree_ptr parser::at_op() {
	ptree_ptr ret = term();

	if (l.token() == "@") {
		match("@", "@ expected");
		ret = ptree_ptr(new at_operator(ret, at_op()));
	}
	return ret;
}

ptree_ptr parser::term() {
	if (l.token() == "(") {
		match("(", "( expected");
		ptree_ptr ret = ampersand_op();
		match(")", ") expected");
		return ret;
	} else {
		return number();
	}
}

ptree_ptr parser::number() {
	int ret;
	std::istringstream ss(l.token());
	ss >> ret;
	match(l.token(), "This should never happen!");
	return ptree_ptr(new int_literal(ret));
}

bool parser::match(const std::string tok, const std::string msg) {
	if (l.hasTokens() && tok == l.token()) {
		l.getToken();
		return true;
	} else {
		std::cout << "line " << l.line_no() << " syntax error: " << msg << "\n";
		return false;
	}
}
