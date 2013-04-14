#include "bidirectional_map_node.h"
#include "bidirectional_map_iterator.h"

template <typename A, typename B>
class iterator : public iterator_base<Node<A, B>> {
protected:
	void increment() {
		const Node<A, B> *node = this->ptr;
		if (node) {
			this->ptr = node->next();
		}
	}
	void decrement() {
		const Node<A, B> *node = this->ptr;
		if (node) {
			this->ptr = node->prev();
		}
	}
public:
	/* Default, copy, and rvalue construction */
	explicit iterator(Node<A, B> *n = nullptr) :
		iterator_base<Node<A, B>>(n) { }
	explicit iterator(const iterator<A, B> &it) = default;
	explicit iterator(iterator &&it) = delete;

	/* FIXME memory leak if allocation occurred */
	virtual ~iterator() { }
	/* Essential operators */
	A &&operator*() {
		assert(this->ptr);
		return std::move(A(**(this->ptr)));
	}
	iterator<B, A> &&follow_link() const {
		assert(this->ptr);
		return std::move(iterator<B, A>(this->ptr->link));
	}
};

#include <iostream>
#include <utility>

#define TYPE0 int
#define TYPE1 double

typedef Node<TYPE0, TYPE1> key_node;
typedef Node<TYPE1, TYPE0> val_node;
typedef iterator<TYPE0, TYPE1> key_itr;
typedef iterator<TYPE1, TYPE0> val_itr;

template <typename A, typename B> std::ostream &
operator<<(std::ostream &ostr, const std::pair<A, B> &p) {
	return ostr << "pair = (" << p.first << "," << p.second << ")";
}

int
main(void)
{
	/* Initialize some nodes and iterators */
	TYPE0 a(0);
	TYPE1 b(0);
	key_node m(a);
	val_node n(b);
	m.link = &n;
	n.link = &m;
	key_itr itm(&m);
	val_itr itn(&n);

	/* Print results */
	using std::cout;
	using std::endl;
	cout << std::make_pair(a, b) << endl;
	cout << "1st node contains: " << *m << endl;
	cout << "2nd node contains: " << *n << endl;
	assert(a == *m);
	assert(b == *n);
	cout << "1st iterator contains: " << *itm << endl;
	cout << "1st iterator links to: " << *itm.follow_link() << endl;
	assert(a == *itm);
	assert(b == *itm.follow_link());
	cout << "2st iterator contains: " << *itn << endl;
	cout << "2st iterator links to: " << *itn.follow_link() << endl;
	assert(b == *itn);
	assert(a == *itn.follow_link());

	return 0;
}
