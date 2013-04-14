#ifndef BM_ITERATOR_H
#define BM_ITERATOR_H

#include <cassert>
#include <utility>

using namespace std::rel_ops;
/* FIXME is this ^ correct use of std::rel_ops? */

template <class T>
class iterator_base {

protected:

	/* Representation */
	T *ptr;

	/* Utility functions */
	void virtual increment() {
		assert(ptr);
	}
	void virtual decrement() {
		assert(ptr);
	}

public:

	/* Constructors -- very simple */
	explicit iterator_base(T *t = nullptr) : ptr(t) { }
	explicit iterator_base(const iterator_base<T> &it) = default;
	explicit iterator_base(iterator_base<T> &&it) = delete;

	wrapper<T> &&operator++() {
		this->increment();
		return wrapper<T>(*this);
	}
	wrapper<T> &&operator++(int) {
		wrapper<T> copy = *this;
		this->increment();
		return std::move(copy);
	}

	wrapper<T> &&operator--() {
		this->decrement();
		return wrapper<T>(*this);
	}
	wrapper<T> &&operator--(int) {
		wrapper<T> copy = *this;
		this->decrement();
		return std::move(copy);
	}

	bool operator==(const wrapper<T> &it) const {
		return ptr == it.ptr;
	}

	bool operator<(const wrapper<T> &it) const {
		wrapper<T> copy = *this;
		return *copy < *it;
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
