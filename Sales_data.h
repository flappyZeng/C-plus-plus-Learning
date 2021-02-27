#ifndef SALES_DATA_H
#define SALES_DATA_H
#include"Base.h"

class Sales_data {

private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0;
	inline double avg_price() const { return units_sold ? revenue / units_sold : 0; };

public:
	Sales_data();
	~Sales_data();
	Sales_data(std::istream& op);
	explicit Sales_data(const std::string& bookNo); //防止构造函数的隐式转换
	Sales_data(const std::string& bookNo, unsigned int units_sold);
	Sales_data(const std::string& bookNo, unsigned int units_sold, double revenue);
	
	std::string isbn() const;
	Sales_data& combine(Sales_data trans);
	/*
	Sales_data operator=(Sales_data trans)
	{
		this->bookNo = trans.bookNo;
		this->units_sold = trans.units_sold;
		this->revenue = trans.revenue;
		return *this;
	}
	*/
	
	friend std::istream& read(std::istream& op, Sales_data& in);
	friend std::ostream& print(std::ostream& op, const Sales_data& out);
	friend Sales_data add(const Sales_data& lhs, const Sales_data& rhs);
};

std::istream& read(std::istream& op, Sales_data& in);
std::ostream& print(std::ostream& op, const Sales_data& out);
Sales_data add(const Sales_data& lhs, const Sales_data& rhs);
#endif // !SALES_DATA_H

