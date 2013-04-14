#ifndef BM_NODE_H
#define BM_NODE_H

#include <cassert>
#include <utility>

//#include "bidirectional_map_iterator.h"

/* Simple class for data encapsulation */
template <typename A, typename B>
struct Node {

	/* Representation captures a piece of data */
	A *data;
	/* Each Node is reflexively linked */
	Node<B, A> *link;
	/* And knows its children and parent */
	const Node<A, B> *left, *right, *parent;

//protected: // Utilities

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
		if (link) { link->link = nullptr; }
	}

	/* Copying duplicates data, shallow-copies link, etc. */
	void copy(const Node<A, B> &n) {
		/* Replace the data */
		this->destroy();
		data = new A(*n);
		/* Update all the pointers */
		link = n.link;
		left = n.left;
		right = n.right;
		parent = n.parent;
	}

public:

	/* Constructors/destructors */
	Node() = delete;
	explicit Node(const A &a, Node<B, A> *node = nullptr) :
		data(new A(a)), link(node),
		left(nullptr), right(nullptr),
		parent(nullptr) { }
	explicit Node(const Node<A, B> &n) :
		data(nullptr) { this->copy(n); }
	explicit Node(Node<A, B> &&n) = delete;
	virtual ~Node() {
		this->destroy();
	}

	/* This replaces all information */
	Node<A, B> &operator=(const Node<A, B> &n) {
		if (this != &n) {
			this->copy(n);
		}
		return *this;
	}

	/* Derefs just fetch the data */
	const A &&operator*() const {
		assert(data);
		return std::move(*data);
	}

};

#include <iostream>

template <typename A, typename B> std::ostream &
operator<<(std::ostream &ostr, const Node<A, B> &n);

#endif // BM_NODE_H
