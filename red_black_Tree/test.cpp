#include<iostream>
#include "red_black_tree.h"
int main()
{

	redBlackTree<int, char> a;
	for (int i = 10; i >0; i--)
	{
		a.push(i, 'a' + i);
	}
	for (auto i : a)
		std::cout << i.first << std::endl;
	auto r1 = a.rank(10);
	return 0;
}