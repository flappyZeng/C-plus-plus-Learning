#pragma once
#include<string>

//任何构造函数之外的非静态函数都可以是虚函数

class Quote{
public:
	Quote() = default; //构造函数不能是虚函数
	Quote(const std::string& book, double sales_price) : bookNo(book), price(sales_price) {}

	std::string isbn() const;
	virtual double net_price(std::size_t n) const { return price * n; };
	virtual ~Quote() = default; //基类默认都是需要是虚函数
	virtual void debug() const;
private:
	std::string bookNo;

protected:
	double price = 0.0;
}; 

class Disc_quote : public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string& book, double price, std::size_t qty, double disc)
		:Quote(book, price), quantity(qty), discount(disc)
	{
	}
	virtual double net_price(std::size_t) const = 0;  //纯虚函数，告诉该类为抽象基类
protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string& book, double sales_price, std::size_t _min_qty, double _distount);

	double net_price(std::size_t n) const override;
	virtual void debug() const override;
};

class Bulk_quote_exceed : public Disc_quote {
public:
	Bulk_quote_exceed() = default;
	Bulk_quote_exceed(const std::string& book, double sales_price, std::size_t _min_qty, double _distount);

	double net_price(std::size_t n) const override;
	virtual void debug() const override;
};

//item的类型是根据传入的参数决定的动态类型，当函数的参数为类的指针或者引用时，其类型是不能在编译时确定的，需要根据传入的参数动态确定
double print_total(std::ostream& os, const Quote& item, size_t n);

//ps： 虚函数的默认实参是由调用者的静态类型决定的
/*
class A {
public:
	virtual void f(int a = 10) { std::cout << a << std::endl; }
};
class B : public  A {
public:
	void f(int a = 5) { std::cout << a << std::endl; }
};
int main()
{
	A a;
	B b;
	A* p = &b;
	p->f();  //输出的是10；

}
*/
