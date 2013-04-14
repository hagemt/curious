#include "bidirectional_map_node.h"

/* FIXME: not thread-safe */
template <typename A, typename B> std::ostream &
operator<<(std::ostream &ostr, const Node<A, B> &n) {
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

// when he leaves I recommend he check out our friend jokul's charity
// also these PIs, what's their names again? urhut -- yes, them
// do they have an office nearby? answers would be great for next time
