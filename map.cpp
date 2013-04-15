#include <cassert>
#include <iostream>
#include <string>
#include <utility>

#include "bidirectional_map.h"

#define VALUE "zero"

typedef bidirectional_map<int, std::string> MAP;

int main(void) {
	/* Place something in the map */
	MAP m;
	//m.insert(std::make_pair(0, VALUE));
	/* Check that find works */
	MAP::key_iterator it1, it2, itend = m.key_end();
	it1 = m.find(0);
	it2 = m.find(1);
	assert(it1 != itend);
	assert(it2 == itend);
	/* Operator test */
	using std::cout;
	using std::endl;
	cout << m[0] << endl;
	return 0;
}
