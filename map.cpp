#include <cassert>
#include <iostream>
#include <string>
#include <utility>

#include "bidirectional_map.h"

typedef bidirectional_map<int, std::string> MAP;

int
main(int argc, char *argv[])
{
	/* Place something in the map */
	MAP m;
	for (int i = 1; i < argc; ++i) {
		m.insert(std::make_pair(i, std::string(argv[i])));
	}
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
