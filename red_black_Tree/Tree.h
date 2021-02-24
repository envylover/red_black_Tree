#pragma once
template<typename Key
	, typename Ty
	/*, typename Compare = Less<Ty>*/>
	struct _Tree
{
	using RANK = unsigned long long;
	struct Node
	{
		std::pair<Key, Ty> pair;
		enum class Color
		{
			red,
			black
		}_color = Node::Color::red;
		Node* right = nullptr;
		Node* left = nullptr;
		Node* parent = nullptr;
		size_t size = 1;
	}*_root = nullptr;
	size_t _size = 0;
	_Tree() {};
	~_Tree() {
		if (_root)
			delete _root;
	}

	using value_type = Ty;
	using pNode = Node*;
	void Insert(Key key, value_type value) {
		pNode p = new Node;
		p->pair = std::pair<Key, Ty>{ key,value };
		//p->_color = Node::Color::red;
		if (!_root)
		{
			_root = p;
		}
		else
		{
			pNode y = _root;
			pNode x = y;
			while (x)
			{
				y = x;
				++(x->size);
				if (key < x->pair.first)
					x = x->left;
				else
					x = x->right;		
			}
			p->parent = y;
			if (key < y->pair.first)
			{
				y->left = p;
			}
			else
			{
				y->right = p;
			}
		}
		Insert_FixUp(p);
	}
	void Insert(std::pair<Key, Ty> p) {
		Insert(p->first, p->second);
	}
	pNode FindByKey(Key key) {
		pNode p = _root;
		while (p)
		{
			if (key < p->pair.first)
				p = p->left;
			else if (key > p->pair.first)
				p = p->right;
			else
				break;
		}
		return p;
	}
	static pNode Tree_Minimm(pNode root)
	{
		if (!root)
			return root;
		while (root->left)
			root = root->left;
		return root;
	}
	static pNode Tree_Max(pNode root)
	{
		if (!root)
			return root;
		while (root->right)
			root = root->right;
		return root;
	}
	void Delete(Key key) {
		pNode z = FindByKey(key);
		pNode y = z;
		pNode x = nullptr;
		typename Node::Color y_original_color = y->_color;
		if (!z->left)
		{
			x = z->right;
			Transplant(z, z->right);
		}
		else if (!z->right) {
			x = z->left;
			Transplant(z, z->left);
		}
		else {//z结点有两个子节点
			y = Tree_Minimm(z->right);
			y_original_color = y->_color;
			x = y->right;
			if (y->parent == z)
			{
				if (x)
					x->parent = y;
			}
			else
			{
				Transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			Transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->_color = z->_color;
		}
		delete z;
		if (y_original_color == Node::Color::black)
			Delete_FixUp(x);
	}
	RANK rank(Key key)
	{
		auto x = FindByKey(key);
		if (!x)
			return 0;
		auto r = (x->left ? x->left->size : 0) + 1;
		auto y = x;
		while (y != _root)
		{
			if (y == y->parent->right)
				r = r + (y->parent->left ? y->parent->left->size : 0) + 1;
			y = y->parent;
		}
		return r;
	}
private:

	void left_rotate(pNode root) {
		pNode x = root, y = root->right;

		y->parent = x->parent;
		x->right = y->left;
		y->left = x;
		x->parent = y;
		if (x->right)
			x->right->parent = x;
		if (y->parent)
		{
			if (x == y->parent->left)
			{
				y->parent->left = y;
			}
			else
			{
				y->parent->right = y;
			}
		}
		y->size = x->size;
		x->size = (x->left ? x->left->size : 0) + (x->right ? x->right->size : 0) + 1;
		
		return;
	}
	/*void exchange_color(pNode x, pNode y) {
		typename Node::Color color = x->_color;
		x->_color = y->_color;
		y->_color = color;
	}*/
	void right_rotate(pNode root) {
		pNode y = root, x = root->left;
		x->parent = y->parent;
		y->left = x->right;
		x->right = y;
		y->parent = x;
		if (y->left)
			y->left->parent = y;
		if (x->parent)
		{
			if (y == x->parent->left)
				x->parent->left = x;
			else
				x->parent->right = x;
		}
		x->size = y->size;
		y->size = (y->left ? y->left->size : 0) + (y->right ? y->right->size : 0) + 1;
		return;
	}
	bool is_red(pNode root)
	{
		if (!root)
			return false;
		return root->_color == Node::Color::red ? true : false;
	}
	void Insert_FixUp(pNode z) {
		while (is_red(z->parent))
		{
			if (z->parent == z->parent->parent->left)
			{//当插入位置的父亲结点为左支的时候
				pNode y = z->parent->parent->right;
				if (is_red(y))
				{
					z->parent->_color = Node::Color::black;
					y->_color = Node::Color::black;
					z->parent->parent->_color = Node::Color::red;
					z = z->parent->parent;
					continue;
				}
				else if (z == z->parent->right)
				{
					z = z->parent;
					left_rotate(z);
				}
				z->parent->_color = Node::Color::black;

				z->parent->parent->_color = Node::Color::red;
				right_rotate(z->parent->parent);
			}
			else
			{//当插入位置的父亲结点为右支的时候
				pNode y = z->parent->parent->left;
				if (is_red(y))
				{
					z->parent->_color = Node::Color::black;
					y->_color = Node::Color::black;
					z->parent->parent->_color = Node::Color::red;
					z = z->parent->parent;
					continue;
				}
				else if (z == z->parent->left)
				{
					z = z->parent;
					right_rotate(z);
				}
				z->parent->_color = Node::Color::black;
				z->parent->parent->_color = Node::Color::red;
				left_rotate(z->parent->parent);
			}
		}
		while (z)
		{
			_root = z;
			z = z->parent;
		}
		_root->_color = Node::Color::black;
	}
	void Delete_FixUp(pNode x) {
		if (!x)
			return;
		while (x != _root && !is_red(x))
		{
			if (x == x->parent->left)
			{
				pNode w = x->parent->right;
				if (is_red(w))
				{
					w->_color = Node::Color::black;
					x->parent->_color = Node::Color::red;
					left_rotate(x->parent);
					w = x->parent->right;
				}
				if (!is_red(w->left) && !is_red(w->right))
				{
					w->_color = Node::Color::red;
					x = x->parent;
					continue;
				}
				else if (!is_red(w->right))
				{
					w->left->_color = Node::Color::black;
					w->_color = Node::Color::red;
					right_rotate(w);
					w = x->parent->right;
				}
				w->_color = x->parent->_color;
				x->parent->_color = Node::Color::black;
				w->right->_color = Node::Color::black;
				left_rotate(x->parent);
				x = _root;
			}
			else
			{
				pNode w = x->parent->left;
				if (is_red(w))
				{
					w->_color = Node::Color::black;
					x->parent->_color = Node::Color::red;
					right_rotate(x->parent);
					w = x->parent->left;
				}
				if (!is_red(w->right) && !is_red(w->left))
				{
					w->_color = Node::Color::red;
					x = x->parent;
					continue;
				}
				else if (!is_red(w->left))
				{
					w->right->_color = Node::Color::black;
					w->_color = Node::Color::red;
					left_rotate(w);
					w = x->parent->left;
				}
				w->_color = x->parent->_color;
				x->parent->_color = Node::Color::black;
				w->left->_color = Node::Color::black;
				right_rotate(x->parent);
				x = _root;
			}
		}
	}
	void Transplant(pNode x, pNode y) {
		if (!x->parent)
			_root = y;
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
			x->parent->right = y;
		if (y)
			y->parent = x->parent;
	}
};
