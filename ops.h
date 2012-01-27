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

class bin_op : public ptree {
public:
	bin_op(ptree *left, ptree *right) : l(left), r(right) {}

protected:
	ptree_ptr l;
	ptree_ptr r;
};
class un_op : public ptree {
public:
	un_op(ptree *term) : t(term) {}

protected:
	ptree_ptr t;
};

class int_lit : public ptree {
public:
	int_lit(int value) : v(value) {}
	int eval() { return v; }
	void print(int indent=0) {
		while (indent--) std::cout << "   ";
		std::cout << v << "\n";
	}

protected:
	int v;
};

class amp_op : public bin_op {
public:
	amp_op(ptree *l, ptree *r) : bin_op(l, r) {}
	int eval();
	void print(int indent);
};
class at_op : public bin_op {
public:
	at_op(ptree *l, ptree *r) : bin_op(l, r) {}
	int eval();
	void print(int indent=0);
};
class pct_op : public un_op {
public:
	pct_op(ptree *t) : un_op(t) {}
	int eval();
	void print(int indent=0);
};

#endif /* OPS_H */
