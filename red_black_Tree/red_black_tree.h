#pragma once
#include<stack>
#include<map>
#include<memory>
#include<string>
#include<coroutine>
#include<thread>
#include "Tree.h"
#include "Task.h"
template<typename Key
	, typename Ty
	/*,typename Compare = Less<Ty>*/>
	class redBlackTree
{
	using value_pointer_v = typename _MyTree<Key, Ty>::Node*;
	using value_type = typename _MyTree<Key, Ty>;
	_MyTree<Key, Ty> _tree;
	std::atomic_bool isReady = false;
public:
	class iterator;
	redBlackTree() {};
	redBlackTree(redBlackTree&& other);
	redBlackTree& operator = (redBlackTree&& other);
	redBlackTree& operator = (redBlackTree& other);
	void push(Key key, Ty value) {
		_tree.Insert(key, value);
	}
	void remove(Key key)
	{
		_tree.Delete(key);
	}
	auto rank(Key key)
	{
		return _tree.rank(key);
	}
	iterator begin() {
		inorder(_tree._root);
		Task<value_pointer_v>::_m_coroutine.resume();
		return { Task<value_pointer_v>::current_p };
	}
	iterator end() {
		iterator i{ (this->_tree).Tree_Max(_tree._root) };
		return i;
	}

public:
	class iterator
	{
		using value_pointer_v = typename _MyTree<Key, Ty>::Node*;
		value_pointer_v p = nullptr;
	public:
		iterator(value_pointer_v ptr) :p(ptr) {
		}
		iterator() = default;
		iterator(iterator&) = default;
		iterator(iterator&& other) {
			p = other.p;
			other.p = nullptr;
		}
		iterator& operator ++() {
			Task<value_pointer_v>::_m_coroutine.resume();
			p = Task<value_pointer_v>::current_p;
			return *this;
		}
		iterator& operator ++(int) {
			iterator temp{ p };
			Task<value_pointer_v>::_m_coroutine.resume();
			p = Task<value_pointer_v>::current_p;
			return temp;
		}
		bool operator !=(iterator& other) {
			return p != other.p;
		}
		bool operator ==(iterator& other) {
			return p == other.p;
		}
		std::pair<Key, Ty> operator*() {
			if (p)
			{
				return p->pair;
			}
			throw string{ "error" };
		}
	};

};


