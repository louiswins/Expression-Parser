#ifndef OPS_H
#define OPS_H

#include <iostream>
#include <tr1/memory>

class ptree;
/* Just use ptree_ptr instead of ptree* and you'll never have a memory leak!
 * (For certain definitions of "never".) You can even use it in an STL
 * container! What joy! */
typedef std::tr1::shared_ptr<ptree> ptree_ptr;

class ptree {
public:
	virtual int eval() = 0;
	virtual void print(int indent=0) = 0;
};

class bin_operator : public ptree {
public:
	bin_operator(ptree_ptr left, ptree_ptr right) : l(left), r(right) {}
	bin_operator(ptree *left, ptree *right) : l(left), r(right) {}

protected:
	ptree_ptr l;
	ptree_ptr r;
};
class un_operator : public ptree {
public:
	un_operator(ptree_ptr term) : t(term) {}
	un_operator(ptree *term) : t(term) {}

protected:
	ptree_ptr t;
};

class int_literal : public ptree {
public:
	int_literal(int value) : v(value) {}
	int eval() { return v; }
	void print(int indent=0) {
		while (indent--) std::cout << "   ";
		std::cout << v << "\n";
	}

protected:
	int v;
};

class amp_operator : public bin_operator {
public:
	amp_operator(ptree_ptr l, ptree_ptr r) : bin_operator(l, r) {}
	amp_operator(ptree *l, ptree *r) : bin_operator(l, r) {}
	int eval();
	void print(int indent);
};
class at_operator : public bin_operator {
public:
	at_operator(ptree_ptr l, ptree_ptr r) : bin_operator(l, r) {}
	at_operator(ptree *l, ptree *r) : bin_operator(l, r) {}
	int eval();
	void print(int indent=0);
};
class pct_operator : public un_operator {
public:
	pct_operator(ptree_ptr t) : un_operator(t) {}
	pct_operator(ptree *t) : un_operator(t) {}
	int eval();
	void print(int indent=0);
};

#endif /* OPS_H */
