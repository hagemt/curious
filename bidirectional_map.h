#ifndef BM_H
#define BM_H

#include "bidirectional_map_node.h"
#include "bidirectional_map_iterator.h"

/* TODO Add allocator(s)? */
template <typename K, typename V>
class bidirectional_map {

	/* Generic find function */
	template <typename A, typename B> bidirectional_map_iterator<A, B> &&
	find(const A &element, const Node<A, B> *node) const {
		if (!node || element == *(node->ptr)) {
			return bidirectional_map_iterator<A, B>(node);
		}
		/* FIXME use iteration instead? */
		return (element < *(node->ptr))
			? find(element, node->left)
			: find(element, node->right);
	}

public:

	/* Types */
	typedef size_t size_type;
	typedef std::pair<K, V> entry_type;
	typedef bidirectional_map_iterator<K, V> key_iterator;
	typedef bidirectional_map_iterator<V, K> value_iterator;

private:

	/* Representation */
	Node<K, V> *key_root;
	Node<V, K> *value_root;
	size_type element_count;

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
		return std::move(key_iterator(find(key, key_head)));
	}
	value_iterator &&find(const V &value) const {
		return std::move(value_iterator(find(value, value_head)));
	}

	/* Modifiers */
	std::pair<bool, key_iterator> &&insert(const entry_type &entry);
	bool erase(const entry_type &entry);

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

template <typename K, typename V> std::pair<bool, key_iterator> &&
bidirectional_map<K, V>::insert(const bidirectional_map<K, V>::entry_type &entry) {
	key_iterator key_it = find(entry.first);
	value_iterator value_it = find(entry.second);
	std::pair<bool, key_iterator> p = std::make_pair(false, key_it);
	/* Only permit non-duplicates */
	if (key_it == key_end() && value_it == value_end()) {
		// TODO implement fully
		p.second = key_it;
		p.first = true;
		++element_count;
	}
	return std::move(p);
}

template <typename K, typename V> bool
bidirectional_map<K, V>::erase(const bidirectional_map<K, V>::entry_type &entry) {
	key_iterator key_it = find(entry.first);
	value_iterator value_it = find(entry.second);
	if (key_it == key_end() || value_it == value_end()) {
		return false;
	}
	// TODO implement fully
	--element_count;
	return true;
}

#endif // BM_H
