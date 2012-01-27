#include "ops.h"
#include "parser.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

class syntax_error : public std::exception {};

ptree_ptr parser::read_expression() {
	l.getToken();
	try {
		ptree_ptr ret = ampersand_op();
		if (l.hasTokens()) {
			throw syntax_error();
		}
		return ret;
	} catch (syntax_error &e) {
		std::cout << "line " << l.line_no() << " syntax error\n";
		return ptree_ptr();
	}
}

ptree_ptr parser::ampersand_op() {
	ptree_ptr ret = percent_op();

	while (l.token() == "&") {
		match("&");
		ret = ptree_ptr(new amp_operator(ret, percent_op()));
	}

	return ret;
}

ptree_ptr parser::percent_op() {
	if (l.token() == "%") {
		match("%");
		return ptree_ptr(new pct_operator(percent_op()));
	} else {
		return at_op();
	}
}

ptree_ptr parser::at_op() {
	ptree_ptr ret = term();

	if (l.token() == "@") {
		match("@");
		ret = ptree_ptr(new at_operator(ret, at_op()));
	}
	return ret;
}

ptree_ptr parser::term() {
	if (l.token() == "(") {
		match("(");
		ptree_ptr ret = ampersand_op();
		match(")");
		return ret;
	} else {
		return number();
	}
}

ptree_ptr parser::number() {
	int ret;
	std::istringstream ss(l.token());
	ss >> ret;
	match(l.token());
	return ptree_ptr(new int_literal(ret));
}

void parser::match(const std::string tok) {
	if (l.hasTokens() && tok == l.token()) {
		l.getToken();
	} else {
		throw syntax_error();
	}
}
