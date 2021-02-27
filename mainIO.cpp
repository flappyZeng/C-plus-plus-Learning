#include<iostream>
#include<string>
#include<fstream>
#include <windows.h> //windows系统选择#include <windows.h>, 如果是linux则是unistd.h

using std::endl;//换行，用来刷新缓冲区
using std::cin;
using std::cout;
using std::ends;
using std::flush;
using std::nounitbuf;
using std::unitbuf; 

std::istream& readIO(std::istream& op)
{
	char ch;
	while ((op >> ch) && !op.eof())
	{
		cout << ch;
	}
	op.clear();
	return op;

}
void test_unitbuf()
{
	cout << "Hi!" << endl;
	Sleep(5);
	cout << "Hi!" << flush;//flush是缓冲区的内容
	cout << "Hi!" << ends;
	cout << unitbuf;
	cout << "first" << "second" << endl;
}

void test_fstream()
{
	std::string fileName = "C:\\Users\\Administrator\\Desktop\\test.txt";
	std::ifstream input(fileName, std::ifstream::in);
	//std::ofstream out(fileName, std::ifstream::app);
	if (input)
	{
		std::string s;
		while (input >> s)
		{
			cout << s << endl;
		}
		input.close();
	}

}
int mainio()
{
	/*
	cout << std::unitbuf;
	auto old_state = cin.rdstate();
	cin.clear();
	readIO(cin);
	*/
	test_fstream();
	return 0;
}



