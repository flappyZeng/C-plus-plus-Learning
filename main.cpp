#include<iostream>
#include<vector>
#include"String.h"

using namespace std;
struct X {
	int i;
	std::string s;
};
struct hasX {
	X mem;
};

int main()
{
	X x, x2 = std::move(x); // 如果x2 = x，则是按值拷贝，两个地址不一样
	cout << &x << endl << &x2 << endl;  //两个地址一样
	hasX hx, hx2 = std::move(hx);
	std::vector<String>vS;
	char word[] = "abcde";
	String s("abc");
	std::cout << "这里" << endl;

	//下面一共调用了6次拷贝构造函数? 为什么是6次
	//原因：
	//	每次调用push_back都是将vector中的元素复制一遍
	for (int i = 0; i < 3; ++i)
	{
		vS.push_back(s);
		std::cout << std::endl;
	}
	
	vS.push_back(std::move(s));
	return 0;
}