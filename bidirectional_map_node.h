#ifndef BM_NODE_H
#define BM_NODE_H

#include <cassert>
#include <iostream>
#include <utility>

namespace teh {

namespace ds {

//using namespace std::rel_ops;
/* FIXME is this ^ correct use of std::rel_ops? */

/* Simple class for data encapsulation */
template <typename A, typename B>
struct Node {

	/* Representation captures a piece of data */
	const A *data;
	/* Each Node is reflexively linked */
	const Node<B, A> *link;
	/* And knows its children and parent */
	const Node<A, B> *left, *right, *parent;

	Node<A, B> *prev() const {
		const Node<A, B> *n = this;
		/* Start from here, check upward for left children */
		while (n->left == nullptr) {
			/* If there is no parent, this node is minimal */
			if (n->parent == nullptr) {
				/* No smaller node exists */
				return nullptr;
			}
			n = n->parent;
		}
		/* To the left is a valid node, get the right-most child */
		n = n->left;
		while (n->right) {
			n = n->right;
		}
		return const_cast<Node<A, B> *>(n);
	}

	Node<A, B> *next() const {
		const Node<A, B> *n = this;
		/* Start from here, check upward for right children */
		while (n->right == nullptr) {
			/* If there is no parent, this node is maximal */
			if (n->parent == nullptr) {
				/* No larger node exists */
				return nullptr;
			}
			n = n->parent;
		}
		/* To the right is a valid node, get the left-most child */
		n = n->right;
		while (n->left) {
			n = n->left;
		}
		return const_cast<Node<A, B> *>(n);
	}

private:

	/* FIXME shouldn't do this? */
	void destroy() {
		if (data) { delete data; }
		//if (link) { link->link = nullptr; }
	}

	/* Copying duplicates data, shallow-copies link, etc. */
	void copy(const Node<A, B> &n) {
		/* Replace the data */
		data = (n.data == nullptr) ? nullptr : new A(*n);
		/* Update all the pointers */
		link = n.link;
		left = n.left;
		right = n.right;
		parent = n.parent;
	}

public:

	/* Constructors/destructors */
	Node() = delete;
	/* FIXME ^ should default first argument below instead? */
	explicit Node(const A &a, Node<B, A> *node = nullptr) :
		data(new A(a)), link(node),
		left(nullptr), right(nullptr), parent(nullptr) { }
	/* Copy replicates data */
	explicit Node(const Node<A, B> &n) { this->copy(n); }
	/* Move takes data (just copies everything) */
	explicit Node(Node<A, B> &&n) :
		data(n.data), link(n.node),
		left(n.left), right(n.right), parent(n.parent) {
		/* FIXME this is necessary, right? */
		n.data = nullptr; n.link = nullptr;
		n.left = n.right = n.parent = nullptr;
	}
	virtual ~Node() {
		this->destroy();
	}

	/* This replaces all information, replicating data */
	Node<A, B> &operator=(const Node<A, B> &n) {
		if (this != &n) {
			this->destroy();
			this->copy(n);
		}
		return *this;
	}

	/* Dereference just fetches the data */
	const A &&operator*() const {
		assert(data);
		return std::move(*data);
	}

	bool operator==(const Node<A, B> &n) {
		assert(data && n.data);
		return *data == *n.data;
	}

	bool operator<(const Node<A, B> &n) {
		assert(data && n.data);
		return *data < *n.data;
	}

};

} // namespace ds

} // namespace teh

template <typename A, typename B> std::ostream &
operator<<(std::ostream &ostr, const teh::ds::Node<A, B> &n);

#endif // BM_NODE_H
