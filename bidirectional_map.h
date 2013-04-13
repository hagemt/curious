/* Simple class for data encapsulation */
template <typename A, typename B>
struct Node {
	A *data;
	Node<B, A> *link;
	Node<A, B> *left, *right;
	Node(const A &a = A()) :
		data(new A(a)),
		link(nullptr),
		left(nullptr),
		right(nullptr)
		{ }
	/* TODO delete copy and rvalue constructor */
	//Node(const Node &) = delete;
	//Node&&(const Node &) = delete;
	~Node() { delete data; }
};

/* TODO template over two types? */
template <typename T>
class tree_iterator {
	/* Representation */
	//Node *node;
public:
	/* TODO constructors via Node */
	tree_iterator<T> operator++() {
		return *this;
	}
	tree_iterator<T> operator--() {
		return *this;
	}
};

#include <iterator>
#include <iostream>
#include <map>
#include <utility>

template <typename K, typename V>
class bidirectional_map {

public:

	/* Types */
	typedef size_t size_type;
	typedef std::pair<K, V> entry_type;
	typedef tree_iterator<entry_type> iterator;
	typedef const iterator const_iterator;

private:

	/* Representation */
	Node<K, V> *key_root, *value_root;
	size_type count;

public:

	/* Constructors */
	bidirectional_map() :
		key_root(nullptr),
		value_root(nullptr),
		count(0)
		{ }

	/* Accessors */
	size_type size() const {
		return count;
	}
	iterator&& find(const K &key) const;
	void print(std::ostream &ostr) const;

	/* Modifiers */
	bool insert(const entry_type &entry);
	bool erase(const iterator &it);

	/* Operators */
	const V &operator[](const K &key);
	const K &operator[](const V &value);

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