#include"Base.h"

using std::cin;
using std::endl;
using std::cout;

void caculate()
{
	bool b = true;

	//b1��true��ԭ��b --����Ϊint--> 1 --> ȡ�� --> -1 --ǿ��ת��Ϊbool --> true
	bool b1 = -b; // ���Ҳ��true, boolֵ��Ӧ�òμ�����

	//��ֵ��������ص���������������
	int a, c;
	a = c = 1; //����
}
int maincal()
{
	std::string s = "word";
	std::string p1 = s + ((s[s.size() - 1] == 's')?"" : "s");
	//int grade = 90;
	//cout << (grade > 60) ? "fail" : "pass"; //���1��

	unsigned char bits = 0227;
	cout << (bits << 8) << endl; // char����λ����ᱻ����Ϊint����

	long long  x[10], * p = x;
	cout << sizeof(x) << endl; //��������ռ����������С
	cout << sizeof(*x) << endl;//����������Ԫ�ش�С
	cout << sizeof(p) << endl;//����ָ���С��һ����ַ��32λ��
	cout << sizeof(*p) << endl;//����������Ԫ�ش�С
	return 0;
}