#include "quote.h"
#include<iostream>

double print_total(std::ostream& os, const Quote& item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}

std::string Quote::isbn() const
{
	return bookNo;
}

Quote& Quote::operator=(Quote& rhs)
{
	if (this != &rhs)
		swap(this, &rhs);
	return  *this;
}

void Quote::debug() const
{
	std::cout << "member in class Quote: \n";
	std::cout << "bookNo: " << bookNo << std::endl;
	std::cout << "price: " << price << std::endl;
}

Bulk_quote::Bulk_quote(const std::string& book, double sales_price, std::size_t _min_qty, double _distount):
	Disc_quote(book, sales_price, _min_qty, discount)
{
}

double Bulk_quote::net_price(std::size_t n) const
{
	if (n > quantity)
		return  n * (1 - discount) * price;
	else
		return n * price;
}

void Bulk_quote::debug() const
{
	std::cout << "member in class Bulk_quote: \n";
	std::cout << "1. from base class Quote: \n";
	std::cout << "bookNo" << Quote::isbn() << std::endl;
	std::cout << "price: " << price << std::endl;
	std::cout << "2. from  class Bulk_quote: \n";
	std::cout << "discount: " << discount << std::endl;
	std::cout << "quantity: " << quantity << std::endl;
}

Bulk_quote_exceed::Bulk_quote_exceed(const std::string& book, double sales_price, std::size_t _min_qty, double _discount)
:Disc_quote(book, sales_price, _min_qty,_discount)
{
}

double Bulk_quote_exceed::net_price(std::size_t n) const
{
	if (n <= quantity)
		return n * price;
	return quantity * price + (n - quantity) * price * (1 - discount);
}

void Bulk_quote_exceed::debug() const
{
	std::cout << "member in class Bulk_quote_exceed: \n";
	std::cout << "1. from base class Quote: \n";
	std::cout << "bookNo" << Quote::isbn() << std::endl;
	std::cout << "price: " << price << std::endl;
	std::cout << "2. from  class Bulk_quote_exceed: \n";
	std::cout << "discount: " << discount << std::endl;
	std::cout << "quantity: " << quantity << std::endl;
}
