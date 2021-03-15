#include"Base.h"

//using 声明不应该出现在头文件内
using std::cin;
using std::cout;
//c++11
/*
	constexpr c++11新规定的关键字
	声明constexpr的一定是一个常量，而且必须使用常量初始化
*/
constexpr int  retInt()
{
	return 10;
}

int func_constexpr()
{
	int k = 10;
	const int mf = 10;
	constexpr int num = 20;   // 声明一个constexpr常量
	// constexpr int num3 = k ，不可行，因为k不是常量
	constexpr int num2 = mf + 1; // 使用一个常量声明constexpr
	constexpr int num4 = retInt(); //只有函数返回的是constexpr类型才可用

	// 指针也能定义为constexpr类型，但是指针必须指向nullptr或者0或固定地址的对象；
	//constexpr int* p = &num; 错误
	constexpr int* ps = nullptr; // 可行
	constexpr int* p = 0; // 可行
	
	return 0;
}

void testFunction()
{
	int z = 0, &r = z;
	auto a = r; //整数
	
	const int ci = z, &cr = ci;  // cosnt int , cosnt int&
	auto b = ci; //int
	auto c = cr; //int;
	auto d = &z; //int *;
	auto e = &ci;//const int *;

	a = 42;
	b = 42;
	c = 42; 
	//d = 42; 报错 int -> int*
	//e = 42; 报错 int --> const int *


	const int i = 42;
	auto j = i;
	const auto& k = i;
	auto* p = &i;
	const auto j2 = i, & k2 = i;
}
/*
字面值类型：
	基本算数类型、引用类型以及指针都是字面值类型
	★ 自定义的类、IO库、string类型则不属于字面值类型

*/


// decltype 不需要明确表达式的值，用表达式推断初始化变量
void testDecltype()
{
	int i = 10;
	decltype(i) k = 10; // 推断i的类型
	decltype(func_constexpr()) ms = 20; //用func_constexpr的返回值类型作为ms的类型

	// decltype与auto不一样，decltype返回的类型和被判断类型的一致的；
	const int m = 10;
	auto intA = m; //int类型
	decltype(m) constIntA = m; //const int 类型

	//decltype的返回类型可以是引用类型
	int t = 42, *p = &t, &j = i;
	decltype(t + 0) b;
	decltype(*p) d = b; //引用类型，必须初始化

	//decltype(())双层括号返回的一定是引用类型
	decltype((t)) e = b; //引用类型必须初始化

	//赋值操作会产生引用
	int a = 3, s = 4;
	decltype(a) c = a; //int
	decltype((a)) r = a; //int &
	decltype(a = s) n = a; //int & 表达式不会产生计算

	cout << a << " " << s << " " << c << " " << r << " " << n; // 3 4 3 3 3

}
/*
int main()
{
	testDecltype();
	return 0;
}
*/