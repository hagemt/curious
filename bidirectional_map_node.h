/* Simple class for data encapsulation */
template <typename A, typename B>
struct Node {

	/* Representation is data, linked node, and children */
	A *data;
	Node<B, A> *link;
	Node<A, B> *left, *right;

	/* Constructors/destructors */
	explicit Node(const A &a = A()) :
		data(new A(a)),
		link(nullptr),
		left(nullptr),
		right(nullptr) { }
	explicit Node(const Node<A, B> &n) = delete;
	//explicit Node&&(const Node<A, B> &n) = delete;
	~Node() { delete data; }

	/* Derefs just get the data */
	const A &operator*() const {
		return *data;
	}

};

#include <iostream>

template <typename A, typename B> std::ostream &
operator<<(std::ostream &ostr, const Node<A, B> &n);
