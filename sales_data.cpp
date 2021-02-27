#include"Sales_data.h"

using std::cin;
using std::cout;
using std::endl;

Sales_data::Sales_data():bookNo(""), units_sold(0), revenue(0.0)
{
	cout << "执行无参数构造函数" << endl;
}

Sales_data::~Sales_data()
{
	cout << "执行析构函数" << endl;
}

Sales_data::Sales_data(const std::string& bookNo) : bookNo(bookNo)
{
	cout << "一个参数的构造函数" << endl;
}

Sales_data::Sales_data(const std::string& bookNo, unsigned int units_sold) : bookNo(bookNo), units_sold(units_sold), revenue(0.0)
{
	cout << "两个参数的构造函数" << endl;
}

Sales_data::Sales_data(const std::string& bookNo, unsigned int units_sold, double revenue) : bookNo(bookNo), units_sold(units_sold), revenue(revenue)
{
	cout << "三个参数的构造函数" << endl;
}

Sales_data::Sales_data(std::istream& op)
{
	read(op, *this);
	cout << "调用read函数的构造函数" << endl;
}

Sales_data& Sales_data::combine(Sales_data trans)
{
	units_sold += trans.units_sold;
	revenue += trans.revenue;
	return *this;
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

std::istream& read(std::istream& op, Sales_data & in)
{
	double price;
	op >> in.bookNo >> in.units_sold >> price;
	in.revenue = in.units_sold * price;
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




