#include"Base.h"
using std::cin;
using std::cout;
using std::endl;

int funcString()
{
	//string的输入是受enter和空格影响的
	std::string s, t;
	cin >> s >> t;     //输入    Hello World    ;
	cout << t << "  " << s << endl;   //输出world Hello;
	return 0;
}

void getLine()
{
	std::string line;
	while(getline(cin, line))   //getline函数读取的字符并没有换行符，换行符被丢弃了
	{
		cout << line << endl;
	}
}

int mainString()
{
	//funcString();
	//getLine();
	std::string s;
	cout << s[0] << endl;
	return 0;
}