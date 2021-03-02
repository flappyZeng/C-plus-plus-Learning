#ifndef _STRVEC_H
#define _STRVEC_H

#include<memory>
#include<string>

class StrVec {
	static std::allocator<std::string>alloc;

private:
	std::string* element;
	std::string* first_free;
	std::string* cap;

	//工具函数
	void chk_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}

	std::pair<std::string*, std::string*>alloc_n_copy(const std::string*, const std::string*);
	void free();
	void reallocate();

public:
	StrVec(StrVec&&s) noexcept; //移动构造函数,带有右值引用
	StrVec() : element(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(const StrVec&);
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&&) noexcept; //移动赋值运算符
	StrVec(const std::initializer_list<std::string>& s);
	~StrVec() { free(); };
	
	void push_back(const std::string&);
	void push_back(std::string&& s);
	size_t size() { return first_free - element; }
	size_t capacity() { return cap - element; }
	std::string* begin() const { return element; }
	std::string* end() const { return first_free; }
};
std::allocator<std::string> StrVec::alloc =  std::allocator<std::string>();

/*
ps: 编译器自动合成移动构造函数的要求：
		当类中没有定义任何版本的拷贝控制成员，并且类的每一个非static数据成员都可以移动是
	编译器才会为该类合成移动构造函数或者移动赋值运算符

	1.编译器可以 移动内置 类型的成员
    2.如果一个成员是类类型，且该类有对应的移动操作，编译器也能移动这个成员


	如果类定义了一个移动构造函数或者一个移动赋值运算符，则该类的合成拷贝构造函数和拷贝赋值运算符会被定义为删除的
	这告诉我们如果一个类定义了移动构造函数或者移动赋值运算符，我们就必须要手动的定义相关的
	拷贝构造函数以及赋值运算符。

	StrVec v1, v2;
	移动构造函数和拷贝构造函数的使用场景：
	移动构造函数接收右值：
	StrVec getVec(istream &);
	v2 = getVec(cin);  
	上式就是调用移动构造函数，因为getVec返回的是一个右值

	拷贝构造函数接收一个左值
	v2 = v1;

	当类中没有定义移动构造函数时，即使使用了move操作，也会通过转换调用拷贝构造函数
	class Foo{
	public:
		Foo() = default;
		Foo(const Foo&);
	};
	Foo x;
	Foo y(x);
	Foo z(std::move(x));
	上述调用的都是拷贝构造函数，因为没有定义相关的移动构造函数

	*/
#endif // !_STRVEC_H