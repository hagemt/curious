#ifndef BM_ITERATOR_H
#define BM_ITERATOR_H

#include <cassert>
#include <utility>

namespace teh {

namespace ds {

using namespace std::rel_ops;
/* FIXME is this ^ correct use of std::rel_ops? */

/* A wrapper class to simplify implementation */
template <class T>
class iterator_base {

protected:

	/* Representation */
	const T *ptr;

	/* Utility functions */
	void virtual increment() {
		assert(ptr);
	}
	void virtual decrement() {
		assert(ptr);
	}

public:

	/* Constructors/destructor -- very simple */
	explicit iterator_base(const T *t = nullptr) : ptr(t) { }
	explicit iterator_base(const iterator_base<T> &it) : ptr(it.ptr) { }
	explicit iterator_base(iterator_base<T> &&it) :
		ptr(it.ptr) {
		/* FIXME this is necessary, right? */
		it.ptr = nullptr;
	}
	virtual ~iterator_base() {
		ptr = nullptr;
	}

	iterator_base<T> &operator=(const iterator_base<T> &it) {
		ptr = it.ptr;
	}

	/* These call increment */
	iterator_base<T> &&operator++() {
		this->increment();
		iterator_base<T> copy = *this;
		return std::move(copy);
	}
	iterator_base<T> &&operator++(int) {
		iterator_base<T> copy = *this;
		this->increment();
		return std::move(copy);
	}

	/* These call decrement */
	iterator_base<T> &&operator--() {
		this->decrement();
		iterator_base<T> copy = *this;
		return std::move(copy);
	}
	iterator_base<T> &&operator--(int) {
		iterator_base<T> copy = *this;
		this->decrement();
		return std::move(copy);
	}

	/* FIXME is this ^ improper use of std::move? */

	/* Check for the same contents */
	bool operator==(const iterator_base<T> &it) const {
		return *ptr == *(it.ptr);
	}

	/* Compare contents */
	bool operator<(const iterator_base<T> &it) const {
		return *ptr < *(it.ptr);
	}

}; // iterator_base<T>

} // namespace ds

} // namespace teh

/******************************************************************************

#include <iterator>
// FIXME finish this...

namespace std {

template <class T, class A = std::allocator<T>>
struct iterator_traits<iterator_base<T>> {
	typedef A::difference_type difference_type;
	typedef A::value_type value_type;
	typedef A::reference reference;
	typedef A::pointer pointer;
	typedef std::bidirectional_iterator_tag iterator_category;
};

} // namespace std

******************************************************************************/

namespace teh {

namespace ds {

/* A specialized iterator for this map using Node */
template <typename K, typename V>
class bidirectional_map_iterator : public iterator_base<Node<K, V>> {

	/* Types */
	typedef Node<K, V> TreeNode;

	/* Maintain a reference to the hierarchy */
	const TreeNode *root;
	/* FIXME ^ should be const? */

	/* Incrementing end is a noop */
	void increment() {
		const TreeNode *n = this->ptr;
		if (n) {
			this->ptr = n->next();
		}
	}

	/* Decrementing end requires special case */
	void decrement() {
		const TreeNode *n = this->ptr;
		if (n) {
			this->ptr = n->prev();
		} else {
			/* The largest element is right-most */
			for (n = root; n->right; n = n->right);
			this->ptr = n;
		}
	}

public:

	/* Construction is straightforward using base */
	explicit bidirectional_map_iterator(const TreeNode *tree, const TreeNode *n = nullptr) :
		iterator_base<TreeNode>(n),
		root(tree) { }
	explicit bidirectional_map_iterator(const bidirectional_map_iterator<K, V> &it) :
		iterator_base<TreeNode>(it.ptr),
		root(it.root) { }
	explicit bidirectional_map_iterator(bidirectional_map_iterator &&it) :
		iterator_base<TreeNode>(it.ptr),
		root(it.root) {
		/* FIXME this is necessary, right? */
		it.ptr = nullptr;
		it.root = nullptr;
	}
	/* TODO can we shorten this name? */
	virtual ~bidirectional_map_iterator() {
		root = nullptr;
	}
	/* FIXME does the super-class destructor get called? */

	bidirectional_map_iterator<K, V> &operator=(const bidirectional_map_iterator<K, V> &it) {
		if (this != &it) {
			ptr = it.ptr;
			root = it.root;
		}
		return *this;
	}

	/* Fetch the first entry from the node */
	const A &&operator*() {
		assert(this->ptr);
		return std::move(**(this->ptr));
	}

	typedef bidirectional_map_iterator<B, A> link_iterator;

	/* This flips the relation */
	link_iterator &&follow_link() const {
		assert(this->ptr);
		return std::move(link_iterator(this->ptr->link));
	}

}; // bidirectional_map_iterator<K, V>

} // namespace ds

} // namespace teh

#endif // BM_ITERATOR_H
