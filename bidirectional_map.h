#ifndef BM_H
#define BM_H

#include "bidirectional_map_node.h"
#include "bidirectional_map_iterator.h"

namespace teh::ds {

/* TODO Add allocator(s)? */
template <typename K, typename V>
class bidirectional_map {

public:

	/* Types */
	typedef size_t size_type;
	typedef std::pair<K, V> entry_type;
	typedef bidirectional_map_iterator<K, V> key_iterator;
	typedef bidirectional_map_iterator<V, K> value_iterator;
	typedef std::pair<bool, key_iterator> key_iterator_pair;
	typedef std::pair<bool, value_iterator> value_iterator_pair;

private:

	/* Representation */
	Node<K, V> *key_root;
	Node<V, K> *value_root;
	size_type element_count;

	/* Generic find function, for utility */
	template <typename A, typename B> bidirectional_map_iterator<A, B> &&
	find(const A &element, const Node<A, B> *node) const {
		if (!node || element == *(node->data)) {
			return std::move(bidirectional_map_iterator<A, B>(node));
		}
		/* FIXME use iteration instead? Does this tail-optimize? */
		return (element < *(node->data))
			? find(element, node->left)
			: find(element, node->right);
	}

public:

	/* Constructors */
	bidirectional_map() :
		key_root(nullptr),
		value_root(nullptr),
		element_count(0) { }

	/* Very simple! */
	size_type size() const {
		return element_count;
	}

	/* Printing simply dumps the roots FIXME doesn't need size? */
	void print(std::ostream &ostr) const {
		ostr << "=================================================" << std::endl;
		if (key_root) {
			ostr << "KEYS:" << std::endl << *key_root;
		}
		ostr << "-------------------------------------------------" << std::endl;
		if (value_root) {
			ostr << "VALUES:" << std::endl << *value_root;
		}
		ostr << "=================================================" << std::endl;
	}

	/* Use dummy nodes */
	key_iterator &&find(const K &key) const {
		return std::move(key_iterator(find(key, key_root)));
	}
	value_iterator &&find(const V &value) const {
		return std::move(value_iterator(find(value, value_root)));
	}

	/* Modifiers */
	key_iterator_pair &&insert(const entry_type &entry);
	// FIXME add: value_iterator_pair &&insert(const entry_type &entry);
	size_type erase(const entry_type &entry);

	/* Operators */
	const V &operator[](const K &key) {
		return *find(key);
	}
	const K &operator[](const V &value) {
		return *find(value);
	}

	/* Iteration */
	key_iterator &&key_begin() const {
		return std::move(key_iterator(key_root, key_root));
	}
	key_iterator &&key_end() const {
		return std::move(--key_iterator(key_root));
	}
	value_iterator &&value_begin() const {
		return std::move(value_iterator(value_root, value_root));
	}
	value_iterator &&value_end() const {
		return std::move(--value_iterator(value_root));
	}

};

/* Useful reference definitions and implementation */
typedef bidirectional_map<K, V> bmap<K, V>;
typedef bmap<K, V>::key_iterator_pair key_iterator_pair<K, V>;
typedef bmap<K, V>::value_iterator_pair value_iterator_pair<K, V>;

/**
 * \brief Try to add something to this bidirectional-map
 *
 * \argument entry use std::make_pair(key, value) to prepare
 * \returns a pair, whether it was added and an iterator
 */
template <typename K, typename V> iterator_pair<K, V> &&
bmap<K, V>::insert(const bmap<K, V>::entry_type &entry)
{
	key_iterator key_it = find(entry.first);
	value_iterator value_it = find(entry.second);
	key_iterator_pair p = std::make_pair(false, key_it);
	/* Only permit non-duplicates */
	if (key_it == key_end() && value_it == value_end()) {
		// TODO implement fully
		p.second = key_it;
		p.first = true;
		++element_count;
	}
	return std::move(p);
}

/**
 * \brief Try to remove something from this bidirectional-map
 *
 * \argument entry use std::make_pair(key, value) to prepare
 * \returns a boolean, whether or not an entry was removed
 */
template <typename K, typename V> typename bmap<K, V>::size_type
bmap<K, V>::erase(const bmap<K, V>::entry_type &entry)
{
	key_iterator key_it = find(entry.first);
	value_iterator value_it = find(entry.second);
	if (key_it == key_end() || value_it == value_end()) {
		return 0;
	}
	// TODO implement fully
	--element_count;
	return 1;
}

} // namespace teh::ds

#endif // BM_H
