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
	typedef bidirectional_map_iterator iterator;
	typedef iterator<K, V> key_iterator;
	typedef iterator<V, K> value_iterator;

private:

	/* Representation */
	Node<K, V> *key_root;
	Node<V, K> *value_root;
	size_type count;

public:

	/* Constructors */
	bidirectional_map() :
		key_root(nullptr),
		value_root(nullptr),
		count(0) { }

	/* Very simple! */
	size_type size() const {
		return count;
	}

	/* Printing is simple, too! */
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
	key_iterator&& find(const K &key) const {
		Node<K, V> dummy(key);
		return key_iterator(find(&dummy, key_head));
	}
	value_iterator&& find(const V &value) const {
		Node<V, K> dummy(value);
		return value_iterator(find(&dummy, value_head));
	}

	/* Modifiers */
	bool insert(const entry_type &entry);
	bool erase(const iterator &it);

	/* Operators */
	const V &operator[](const K &key) {
		return *find(key);
	}
	const K &operator[](const V &value) {
		return *find(value);
	}

	/* Iteration  */
	key_iterator &&key_begin() const {
		return key_iterator(this, key_root);
	}
	key_iterator &&key_end() const {
		key_iterator it;
		return std::move(--it);
	}
	value_iterator &&value_begin() const {
		return value_iterator(value_root);
	}
	value_iterator &&value_end() const {
		value_iterator it;
		return std::move(--it);
	}

};

// TODO implement
template <typename K, typename V> bool
bidirectional_map<K, V>::insert(const bidirectional_map<K, V>::entry_type &entry) {
	return false;
}

// TODO implement
template <typename K, typename V> bool
bidirectional_map<K, V>::erase(const bidirectional_map<K, V>::iterator &it) {
	return false;
}

#endif // BM_H
