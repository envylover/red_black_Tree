#include<iostream>
#include "red_black_tree.h"
int main()
{

	redBlackTree<int, char> a;
	for (int i = 20; i >0; i--)
	{
		a.push(i, 'a' + i);
	}
	auto r1 = a.rank(10);
	for (auto j : a)
		cout << j.first << "  " << j.second << endl;
	return 0;
}