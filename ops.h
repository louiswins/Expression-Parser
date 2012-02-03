#ifndef OPS_H
#define OPS_H

#include <iostream>
#include <tr1/memory>

class ptree;
typedef std::tr1::shared_ptr<ptree> ptree_ptr;

class ptree {
public:
	virtual int eval() = 0;
	virtual void print(int indent=0) = 0;
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

class amp_operator : public ptree {
public:
	amp_operator(ptree_ptr left, ptree_ptr right) : l(left), r(right) {}
	amp_operator(ptree *left, ptree *right) : l(left), r(right) {}
	int eval();
	void print(int indent=0);
private:
	ptree_ptr l;
	ptree_ptr r;
};
class at_operator : public ptree {
public:
	at_operator(ptree_ptr left, ptree_ptr right) : l(left), r(right) {}
	at_operator(ptree *left, ptree *right) : l(left), r(right) {}
	int eval();
	void print(int indent=0);
private:
	ptree_ptr l;
	ptree_ptr r;
};
class pct_operator : public ptree {
public:
	pct_operator(ptree_ptr tree) : t(tree) {}
	pct_operator(ptree *tree) : t(tree) {}
	int eval();
	void print(int indent=0);
private:
	ptree_ptr t;
};

#endif /* OPS_H */
