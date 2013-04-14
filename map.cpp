#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>

#include "bidirectional_map.h"

typedef bidirectional_map<int, std::string> map;

#define VALUE "zero"

int main(void) {
	/* Place something in the map */
	map m;
	m.insert(std::make_pair(0, VALUE));
	/* Check that find works */
	map::key_iterator it1, it2, itend = m.key_end();
	std::tie(it1, it2) = std::make_tuple(m.find(0), m.find(1));
	assert(it1 != itend);
	assert(it2 == itend);
	/* Operator test */
	std::cout << m[0] << std::endl;
	return 0;
}
