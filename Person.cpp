#include"Person.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

Person::Person():name(""), adderess("")
{
	cout << "无参的构造函数" << endl;
	
}
Person::Person(const std::string& name):name(name), adderess("")
{
	cout << "一个参数的构造函数" << endl;
}
Person::Person(const std::string& name, const std::string& adderess):name(name), adderess(adderess)
{
	cout << "两个参数的构造函数" << endl;
}
Person::Person(std::istream& op)
{
	read(op, *this);
	cout << "调用read函数的构造函数" << endl;
}

const string& Person::getName() const
{
	return name;
}
const string& Person::getAdderess() const
{
	return adderess;
}

std::istream& read(std::istream& op, Person& in)
{
	op >> in.name >> in.adderess;
	return op;
}
std::ostream& print(std::ostream& op, Person& out)
{
	op << "name: " << out.name << endl;
	op << "adderess: " << out.adderess << endl;
	return op;
}
