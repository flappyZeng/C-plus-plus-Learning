#include"Base.h"

using std::cin;
using std::cout;
using std::endl;


int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

void print(int ia[])  //这个声明等价于print(int *ia)可以放任意的数组对象 ，不局限于10个
{
	cout << "调用指针版本" << endl;
	for (auto i = 0; i  != 10; ++i)
		cout << ia[i] << endl;
}

void print(int(&ia)[10])
{
	cout << "调用引用版本" << endl;
	for (auto i = 0; i != 10; ++i)
		cout << ia[i] << endl;
}

//返回数组的函数
int(*func(int arr[][10], int i))[10]
{
	return &arr[i];
}

//返回数组函数的第二类定义, 这个类似于python的语法：
auto func_two(int arr[][10], int i) -> int(*)[10]
{
	return &arr[i];
}

//返回数组函数的第三类定义, 这里不能单纯使用decltype(arr1)，因为这里decltype只能获取数据数组，能不能获取指针
decltype(arr1)* func_three(int arr[][10], int i)
{
	cout << __func__ << endl;  //用来保存函数名字的宏
	return &arr[i];
}

int mainarrs()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int arr3[][10] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10} };
	int(&b)[10] = arr1;
	func_three(arr3, 0);
	//print(b);
	return 0;
}