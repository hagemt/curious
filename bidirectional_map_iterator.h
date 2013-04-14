#ifndef BM_ITERATOR_H
#define BM_ITERATOR_H

#include <cassert>
#include <utility>

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

	/* Constructors -- very simple */
	explicit iterator_base(const T *t = nullptr) : ptr(t) { }
	explicit iterator_base(const iterator_base<T> &it) = default;
	explicit iterator_base(iterator_base<T> &&it) = delete;

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

};

/*

#include <iterator>

namespace std {

template <class T, class A = std::allocator<T>>
struct iterator_traits<iterator_base<T>> {
	typedef A::difference_type difference_type;
	typedef A::value_type value_type;
	typedef A::reference reference;
	typedef A::pointer pointer;
	typedef std::bidirectional_iterator_tag iterator_category;
};

}

*/

#endif // BM_ITERATOR_H
