#ifndef PERSON_H
#define PERSON_H
#include"base.h"

class Person
{
	std::string name;
	std::string adderess;
public:
	Person();
	Person(const std::string& name);
	Person(const std::string& name, const std::string& adderess);
	Person(std::istream& op);

	const std::string& getName() const ;
	const std::string& getAdderess() const;

	friend std::istream& read(std::istream& op, Person& in);
	friend std::ostream& print(std::ostream& op, Person& in);
};

std::istream& read(std::istream& op, Person& in);
std::ostream& print(std::ostream& op, Person& in);


//class X && Y
class Y;

class X
{
private:
	Y *y = nullptr;
};

class Y
{
private:
	X x;
};
#endif // !PERSON_H