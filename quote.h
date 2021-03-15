#pragma once
#include<string>
#include<iostream>
//�κι��캯��֮��ķǾ�̬�������������麯��

class Quote{
public:
	Quote() = default; //���캯���������麯��
	Quote(const Quote&) = default;
	Quote(const std::string& book, double sales_price) : bookNo(book), price(sales_price) {}
	virtual Quote* clone() const & { return  new Quote(*this); }
	virtual Quote* clone()  && { return new Quote(std::move(*this)); }
	std::string isbn() const;
	Quote& operator=(Quote& rhs);
	virtual double net_price(std::size_t n) const { return price * n; };
	virtual ~Quote() = default; //����Ĭ�϶�����Ҫ������������
	virtual void debug() const;
	void swap(Quote* lhs, Quote* rhs)
	{
		if (lhs != rhs)
		{
			using std::swap;
			swap(lhs->bookNo, rhs->bookNo);
			swap(lhs->price, rhs->price);
		}
	}
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
	virtual double net_price(std::size_t) const = 0;  //���麯�������߸���Ϊ�������
protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string& book, double sales_price, std::size_t _min_qty, double _distount);
	virtual Bulk_quote* clone() const & { return  new Bulk_quote(*this); }
	virtual Bulk_quote* clone()  && { return new Bulk_quote(std::move(*this)); }
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

//item�������Ǹ��ݴ���Ĳ��������Ķ�̬���ͣ��������Ĳ���Ϊ���ָ���������ʱ���������ǲ����ڱ���ʱȷ���ģ���Ҫ���ݴ���Ĳ�����̬ȷ��
double print_total(std::ostream& os, const Quote& item, size_t n);

//ps�� �麯����Ĭ��ʵ�����ɵ����ߵľ�̬���;�����

class A {
public:
	virtual void f(int a = 10) { std::cout << a << std::endl; }
};
class B : public  A {
public:
	void f(int a = 5) { std::cout << a << std::endl; }
};
/*
int mainc()
{
	A a;
	B b;
	A* p = &b;
	Bulk_quote bq;
	p->f();  //�������10��
	return 0;
}
*/

