#include <iterator>
#include <iostream>
#include <string>

#include "bidirectional_map_node.h"
#include "bidirectional_map_iterator.h"

template <typename T>
class iterator : public wrapper<T> {
protected:
	void increment() { }
	void decrement() { }
public:
	/* TODO this is just a toy; other construtors? */
	explicit iterator(const T &t = T()) :
		wrapper<T>(new T(t)) { }
	/* FIXME can I use move-semantics for this? */
	T &&operator*() {
		T data = *(this->ptr);
		return std::move(data);
	}
};

int main(void) {
	int zero_int = 0;
	std::string zero_string = "0";
	Node<int, std::string> m(zero_int);
	Node<std::string, int> n(zero_string);
	m.link = &n; n.link = &m;
	std::cout << *m << std::endl;
	std::cout << *n << std::endl;
	iterator<int> it1;
	iterator<std::string> it2;
	std::cout << *it1 << std::endl;
	std::cout << *it2 << std::endl;
	return 0;
}
