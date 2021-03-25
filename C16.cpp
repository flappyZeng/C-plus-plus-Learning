#include<iostream>
#include"Sales_data.h"
#include <list>
#include "Template.h"
#include<functional>
using namespace std;

//函数模板,函数体内使用大于小于号，使得函数的鲁棒性不强，所以考虑使用less以及

//ps: 1.函数模板应该尽量减少对实参类型的要求（要求可以适用于多变的类型）
//    2.与常规类成员不同，模板的头文件必须要包含 声明 以及 定义。
template<typename T>
int compare(const T& v1, const T& v2)
{
	if (less<T>()(v1, v2))	return -1;
	if (less<T>()(v2, v1))	return 1;
	return 0;
}

//非类型模板参数
template<unsigned N, unsigned M> //可以不是class或者typename，但是使用时必须传入对应类型的 常量表达式
int compare(const char(&p1)[N], const char(&p2)[M])
{
	return strcmp(p1, p2);
}
//假如调用 compare("hi", "mom") 上述模板会实例化成 ->  compare(const char(&p1)[3], const char(&p2)[4]) (自动加上空字符作为终结符)


//为inline的模板函数，inline必须置于template之后
template<typename T> inline T min(const T&, const T&);



//C16T1:
//实例化的定义： 当为函数模板传入具体的参数时，编译器将模板内的参数（typename或class)替换为对应的类型，并生成对应的代码，该过程称为实例化

//C16T4 find的模板
template<typename ITR, typename T>
ITR Myfind(const ITR& begin, const ITR& end, const T& val)
{
	for (ITR it = begin; it != end; ++it)
		if (*it == val)
			return it;
	return end;
}

//C16T5 定义自己的begin以及end：
template<typename T, unsigned N>
auto Mybegin(const T(&arr)[N])
{
	return arr;
}
template<typename T, unsigned N>
auto Myend(const T(&arr)[N])
{
	return arr + N;
}

//C16T7
template<typename T, unsigned N>
constexpr size_t getSize(const T(&arr)[N])
{
	return N;
}

template<typename T> T fobj(T a, T b)
{
	plus<T>Tadd;
	return Tadd(a, b);
}
template<typename T> T fref(const T& a, const T& b)
{
	plus<T>Tadd;
	return Tadd(a, b);;
};

std::string s1("a value");
const std::string s2("another value");


//C16T35
template<typename T>T  cal(T a, int b)
{
	plus<T>Tadd;
	return static_cast<T>(Tadd(a, b));
}
template <typename T> T fcn(T a, T b) {
	plus<T>Tadd;
	return static_cast<T>(Tadd(a, b));
}


//引用折叠
int k = std::move(42);

//C16T49
template<typename T> void f(T) {
	cout << "调用f(T)" << endl;
}
template<typename T> void f(const T*) {
	cout << "调用f(const T*) " << endl;
}
template<typename T> void g(T) {
	cout << "调用g(T)" << endl;
}
template<typename T> void g(T*) {
	cout << "调用g(T*)" << endl;
}


//可变参数模板
template<typename T, typename... Args>
void foo(const T& t, const Args& ... rest)
{
	cout << sizeof...(Args) << endl;
	cout << sizeof...(rest) << endl;
}


//可以打印任意个参数
template<typename T>
ostream& Myprint(ostream& os, const T& t)
{
	return os << t;
}
template<typename T,  typename ...Args>
ostream& Myprint(ostream& os, const T& t, const Args&... rest)
{
	os << t << ",1 ,  ";
	return Myprint(os, rest...);
}
int mainC17()
{
	cout << compare(1, 2);
	cout << compare(1.0, 2.0);
	cout << compare('a', 'b');
	
	cout << compare("abc", "defg");
	//cout << compare("abc", "def");  和多个模板同时匹配，无法实例化，因此报错
	//cout << compare(1, 2.0);
	vector<int>vc{ 1, 2, 3, 4, 5, 6 };
	list<string>lst{ initializer_list<string>{"a","b", "c", "d", "e"} };
	cout << Myfind(vc.begin(), vc.end(), 6) - vc.begin() << endl;
	//list和forward都是不连续存储， 所以不支持迭代器的加减来确定元素的位置
	cout << *Myfind(lst.cbegin(), lst.cend(), "d") << endl;
	//compare(Sales_data(), Sales_data());
	auto it = begin(vc);

	//fobj(s1, s2);   //可行   const string to string；
	//fref(s1, s2);   //可行   string& to cosnt string&;
	//int a[10], b[10];
	//fobj(a, b);  //可行 arr -> point;
	//fref(a, b);  不可行，不存在 arr -> const arr&的转换；

	double d = 0;
	float f1 = 10.0;
	char c = 0;
	cal(c, 'c');  //可行 char -> int;
	cal(d, f1);  //可行 cal(double, int); float -> int;
	fcn(c, 'c');  //可行， fcn(char, char) 
	//fcn(d, f); 不可行，参数类型不匹配；

	int i = 42, *p = &i;
	const int ci = 0, *p2 = &ci;
	g(42);  //调用g(T)
	g(p);   //调用g(T*)
	g(ci);  //调用g(T)
	g(p2);  //调用g(T*)
	f(42);  //调用f(T)
	f(p);   //调用f(T)
	f(ci);  //调用f(T)
	f(p2); //调用f(const T*)
	

	int ii = 0; double dd = 3.14; string ss = "how now brown now";
	foo(ii, ss, 42, dd);
	foo(ss, 42, "hi");
	foo(d, ss);
	foo("hi");
	Myprint(cout, ii, dd, ss);
	//vc.emplace_back("abc");

	shared_ptr<int>pps = make_shared<int>(10);
	return 0;
}

