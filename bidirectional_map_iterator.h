#include <utility>
using namespace std::rel_ops;

template <class T>
class wrapper {

protected:

	/* Representation */
	T *ptr;

	/* Utility functions */
	void virtual increment() { }
	void virtual decrement() { }

public:

	/* Constructors */
	explicit wrapper(T *t = nullptr) :
		ptr(t) { }
	explicit wrapper(const wrapper<T> &it) :
		ptr(it.ptr) { }
	wrapper<T> &operator=(const wrapper<T> &it) {
		if (this != &it) {
			ptr = it.ptr;
		}
	}

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
