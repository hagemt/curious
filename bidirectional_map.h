#include "bidirectional_map_node.h"
#include "bidirectional_map_iterator.h"

/* TODO Add allocator(s)? */
template <typename K, typename V>
class bidirectional_map {

	/* A specialized iterator for this map using Node */
	template <typename A, typename B>
	class bidirectional_map_iterator : public wrapper<Node<A, B>> {
		/* Maintain a reference to the map */
		const bidirectional_map<K, V> *parent;
		/* This flips the relation */
		bidirectional_map_iterator<B, A> &&operator~() {
			return bidirectional_map_iterator<B, A>(node->link);
		}
		/* FIXME should these be in the super-class? */
		void increment() { }
		void decrement() { }
	public:
		explicit bidirectional_map_iterator(
				bidirectional_map<K, V> *obj,
				const Node<A, B> *n = nullptr) :
			parent(obj), iterator(n) { }
		/* Fetch the first entry from the node */
		const A &operator*() {
			return **node;
		}
	};

	template <typename A, typename B> tree_iterator<A, B>&&
	find(const A &element, const Node<A, B> *node) const {
		if (!node || element == *(node->data)) {
			return tree_iterator<A, B>(node);
		}
		return (element < *(node->data))
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
	iterator key_begin() const;
	iterator key_end() const;
	iterator value_begin() const;
	iterator value_end() const;

};

template <typename K, typename V> typename bidirectional_map<K, V>::iterator&&
bidirectional_map<K, V>::find(const K &key) const {
	iterator it;
	return std::move(it);
}
