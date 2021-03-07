#pragma once
#include<string>

//�κι��캯��֮��ķǾ�̬�������������麯��

class Quote{
public:
	Quote() = default; //���캯���������麯��
	Quote(const std::string& book, double sales_price) : bookNo(book), price(sales_price) {}

	std::string isbn() const;
	virtual double net_price(std::size_t n) const { return price * n; };
	virtual ~Quote() = default; //����Ĭ�϶�����Ҫ���麯��
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
	virtual double net_price(std::size_t) const = 0;  //���麯�������߸���Ϊ�������
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

//item�������Ǹ��ݴ���Ĳ��������Ķ�̬���ͣ��������Ĳ���Ϊ���ָ���������ʱ���������ǲ����ڱ���ʱȷ���ģ���Ҫ���ݴ���Ĳ�����̬ȷ��
double print_total(std::ostream& os, const Quote& item, size_t n);

//ps�� �麯����Ĭ��ʵ�����ɵ����ߵľ�̬���;�����
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
	p->f();  //�������10��

}
*/
