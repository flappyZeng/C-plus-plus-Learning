#include"Sales_data.h"

using std::cin;
using std::cout;
using std::endl;

Sales_data::Sales_data():bookNo(""), units_sold(0), revenue(0.0)
{
	cout << "ִ���޲������캯��" << endl;
}

Sales_data::~Sales_data()
{
	cout << "ִ����������" << endl;
}

Sales_data::Sales_data(const std::string& bookNo) : bookNo(bookNo)
{
	cout << "һ�������Ĺ��캯��" << endl;
}

Sales_data::Sales_data(const std::string& bookNo, unsigned int units_sold) : bookNo(bookNo), units_sold(units_sold), revenue(0.0)
{
	cout << "���������Ĺ��캯��" << endl;
}

Sales_data::Sales_data(const std::string& bookNo, unsigned int units_sold, double revenue) : bookNo(bookNo), units_sold(units_sold), revenue(revenue)
{
	cout << "���������Ĺ��캯��" << endl;
}

Sales_data::Sales_data(std::istream& op)
{
	read(op, *this);
	cout << "����read�����Ĺ��캯��" << endl;
}

Sales_data& Sales_data::combine(Sales_data trans)
{
	units_sold += trans.units_sold;
	revenue += trans.revenue;
	return *this;
}

Sales_data& Sales_data::operator+(const Sales_data& rhs)
{
	if (isbn() != rhs.isbn())
	{
		std::cout << "Different book can't do add operation!" << std::endl;
		return *this;
	}
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
	// TODO: �ڴ˴����� return ���
}

std::string Sales_data::isbn() const
{
	return bookNo;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

std::istream& operator>>(std::istream& op, Sales_data& in)
{
	return read(op, in);
	// TODO: �ڴ˴����� return ���
}

std::ostream& operator<<(std::ostream& op, const Sales_data& out)
{
	return print(op, out);
	// TODO: �ڴ˴����� return ���
}

std::istream& read(std::istream& op, Sales_data & in)
{
	double price;
	op >> in.bookNo >> in.units_sold >> price;
	//��Ӽ�����
	if (op)
		in.revenue = in.units_sold * price;
	else
		in = Sales_data();
	return op;
}

std::ostream& print(std::ostream& op, const Sales_data& out)
{
	op << "isbn: " << out.bookNo << endl;
	op << "unit_sold: " << out.units_sold << endl;
	op << "revenue: " << out.revenue << endl;
	return op;
}


int mainSales()
{
	Sales_data total;
	if(read(cin, total))
	{
		Sales_data trans;
		while (read(cin, trans))
		{
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else {
				print(cout, total) << endl;
				total = trans;
			}
		}
		print(cout, total) << endl;
	}
	else
	{
		std::cerr << "No data?!" << endl;
	}
	return 0;
}




