#define TYPE0 int
#define TYPE1 double

#include <iostream>
#include <utility>

template <typename A, typename B> std::ostream &
operator<<(std::ostream &ostr, const std::pair<A, B> &p) {
	return ostr << "pair = (" << p.first << "," << p.second << ")";
}

#include "bidirectional_map_node.h"
#include "bidirectional_map_iterator.h"
using namespace teh::ds;

typedef Node<TYPE0, TYPE1> key_node;
typedef Node<TYPE1, TYPE0> val_node;
typedef bidirectional_map_iterator<TYPE0, TYPE1> key_itr;
typedef bidirectional_map_iterator<TYPE1, TYPE0> val_itr;

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

	using std::cout;
	using std::endl;

	/* Print results */
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
