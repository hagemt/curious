#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

#include "bidirectional_map.h"
using namespace teh::ds;

typedef bidirectional_map<int, std::string> MAP;

int
main(int argc, char *argv[])
{
	/* Require at least one argument */
	if (argc < 2) {
		return (EXIT_FAILURE);
	}

	/* Create a map containing the arguments */
	MAP m;
	for (int i = 1; i < argc; ++i) {
		m.insert(std::make_pair(i, std::string(argv[i])));
	}

	/* Check that find works */
	MAP::key_iterator it0, it1, itend = m.key_end();
	it0 = m.find(0);
	it1 = m.find(1);
	assert(it0 == itend);
	assert(it1 == itend);

	using std::cout;
	using std::endl;
	/* Operator test(s) */
	for (int i = 1; i < argc; ++i) {
		cout << m[i];
	}
	cout << endl;

	/* Dump contents */
	cout << endl;
	m.print(cout);
	cout << endl;

	return (EXIT_SUCCESS);
}
