#include<iostream>
#include<cstdlib>
#include<string>
#include"Query.h"
#include"Screen.h"
using namespace std;

//重载new 和delete
//如果在类中重载new和delete操作符，则new 和delete必须是静态的，因为new的调用在对象构造之前，delete的调用在对象销毁之后， 同时也不能操作任何类中的数据成员

/*
void* operator new(size_t size) {
	if (void* mem = malloc(size))
		return mem;
	else
		throw bad_alloc();
}
void operator delete(void* mem) noexcept
{
	free(mem);
}
*/
//调用析构函数会销毁对象，但是不会释放内存

//dynamic_cast运算符
// dynamic_cast<type*>(e)  , 指针类型转换失败，则e是0
// dynamic_cast<type&>(e)  ， 引用类型转换失败 则将抛出异常bad_cast
// dynamic_cast<type&&>(e)	  引用类型转换失败 则将抛出异常bad_cast

//上述的type必须是一个类类型，并且通常情况下应该有虚函数

//e的类型也有要求：
// 1.e是目标类型type的 公有（注意是公有） 派生类
// 2.e是目标类型type的公有基类
// 3.e是目标类type;

//C19T3
class A {
public:
	A() { cout << "A()" << endl; }
	virtual ~A() { cout << "~A()" << endl; };
};

class B :public A{
public:
	B() { cout << "B()" << endl; };
	virtual ~B() { cout << "~B()" << endl; };
};

class C :public B {
public:
	C() { cout << "C()" << endl; }
	virtual ~C() { cout << "~C()" << endl; };
};

class D :public B, public A {
public:
	D() { cout << "D()" << endl; }
	virtual ~D() { cout << "~D()" << endl; };
};


//枚举类型

//限定作用域的枚举类型
enum class open_modes {input, output, append};

//不限定作用域的枚举类型
enum color {red, yellow = 3, green};

//上述的使用区别
color eyes = green;  //可行
//open_modes in = input; 不可行，因为限定了作用域，可以理解为namespace,要使用限定符
open_modes in = open_modes::input;

//枚举成员本身就是const，所以声明了一个枚举成员相当于声明了一个常量表达式
constexpr color book_color = red;


//两个区别，限定作用域的枚举不会发生类型的 隐式转换
int i = color::red;  //可行
//int j = open_modes::input; 错误，不会隐式转换为int

//通过：来声明枚举类型内部的数据类型
//对于不限定作用域的枚举类型，其默认类型是有机器本身决定的，因此存在危险，最好在声明的时候明确说明内部数据的类型
//对于限定作用域的枚举类型，其默认类型是int，可以不用明确给出
enum appen_size : unsigned {small ,middle, big};

int main()
{
	std::string *sp = new string("a value");
	int* p = new(nothrow) int(10);  //显式要求调用不抛出异常的new运算符
	int* q = new(p) int(20);  //传入一个指针地址，那么new将不分配新的内存，而是用旧内存
	cout << *p << endl;

	A* pa = new C;
	if (B * pb = dynamic_cast<B*>(pa))
		cout << "True" << endl;
	else
		cout << "False" << endl;

	B* pbb = new B;   //这个地方为什么是false，符合第二条。B是C的公有基类
	if (C * pc = dynamic_cast<C*>(pbb))
		cout << "True" << endl;
	else
		cout << "False" << endl;

	A* paa = new D;
	if (B * pb = dynamic_cast<B*>(paa))
		cout << "True" << endl;
	else
		cout << "False" << endl;
	string* s = new string("6");
	string* b = new string("abc");
	cout << (typeid(*pa) == typeid(*paa)) << endl;  //比较对象的类型是否相同

	Query_base* qu = new AndQuery(Query("abc"), Query("cde"));
	AndQuery* aq;
	if (aq = dynamic_cast<AndQuery*>(qu))
		cout << "true" << endl;
	else
		cout << "false" << endl;

	AndQuery aqq = AndQuery(Query("abc"), Query("cde"));
	Query_base& qs = aqq;
	const AndQuery& aqs = dynamic_cast<AndQuery&>(qs);
	/*
	try {
	   //可行
		const AndQuery& aqs = dynamic_cast<AndQuery&>(qs);
		cout << "true" << endl;
	}
	catch (bad_cast) {
		cout << "false" << endl;
	}
	*/
	//都是一样的
	cout << (typeid(*aq) == typeid(aqs)) << endl;
	cout << (typeid(*aq) == typeid(AndQuery)) << endl;
	cout << (typeid(aqs) == typeid(AndQuery)) << endl;

	cout << typeid(*pa).name() << endl;

	//成员指针：可以指向类的非静态成员的指针
	const string Screen::* pdata = Screen::data();    //声明了一个指向Screen类的congs string成员的指针（只能读取，不能写入）
	Screen myScreen, *pScreen = &myScreen;
	//auto s = myScreen.*pdata;
	auto s = pScreen->*pdata;

	auto pmf = &Screen::get_cursor;
	//pmf = &Screen::get; 不允许，因为函数指针对应的函数的返回值类型不一样
	return 0;
}