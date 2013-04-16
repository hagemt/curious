#include "bidirectional_map_node.h"

/* FIXME: not safe under concurrency, use thread-local vs. static variable? */
template <typename A, typename B> std::ostream &
operator<<(std::ostream &ostr, const teh::ds::Node<A, B> &n) {
	static size_t depth = 0;
	if (n.right) {
		++depth;
		ostr << *(n.right);
		--depth;
	}
	for (size_t i = 0; i < depth; ++i) {
		ostr << '\t';
	}
	ostr << *(n.data) << "[" << *(n.link->data) << "]" << std::endl;
	if (n.left) {
		++depth;
		ostr << *(n.left);
		--depth;
	}
	return ostr;
}
