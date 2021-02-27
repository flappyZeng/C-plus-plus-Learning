#include"Screen.h"
#include"Sales_data.h"
#include"Person.h"


int mainclass()
{
	Person p = Person("xiaozhang", "hunan");
	std::cout << p.getAdderess() << std::endl;
	Screen mySc(5, 5, 'X');
	mySc.move(4, 0).set('#').display(std::cout);
	std::cout << "\n";
	mySc.display(std::cout);
	std::cout << "\n";
	return 0;
}
