#include"Base.h"
using std::cin;
using std::cout;
using std::endl;

int funcString()
{
	//string����������enter�Ϳո�Ӱ���
	std::string s, t;
	cin >> s >> t;     //����    Hello World    ;
	cout << t << "  " << s << endl;   //���world Hello;
	return 0;
}

void getLine()
{
	std::string line;
	while(getline(cin, line))   //getline������ȡ���ַ���û�л��з������з���������
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