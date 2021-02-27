#include"Base.h"

using std::cin;
using std::cout;
using std::endl;

void func_type_trans()
{
	unsigned char a = 0;
	a = 178;
	cout <<"a: "<<  a << endl;
}

void explicit_trans()
{
	int i = 0, j = 1;
	double d = 0.0;
	//static_cast: ����߱���ȷ���������ת����ֻҪ����������const,���Խ������Ͱ�ȫ��ת��ΪС����
	double slope = static_cast<double>(i) / j;  //����static_cast��iת��Ϊdouble
	void* p = &d;
	double* dp = static_cast<double*>(p);   //��void* --> double*

	//dynamic_cast�� ����ʱ��������ʶ��

	//const_cast: const_castֻ�ܸı��������ײ��const��ֻ��ȥ��const�������������ת��
	char c = 'a';
	const char* pc = &c;
	char* pcc = const_cast<char*>(pc);  //����ת����������ζ�����һ����������pcc����дֵ����Ϊ��δ����

	char ch = 'a';
	const int in = 10;

	const int* pin = &in; //����ͨ��pin�޸�in��
	const char* pch = &ch;  //����ͨ��pch�޸�ch��

	int* pincc = const_cast<int*>(pin);
	*pincc = 20;  //δ������Ϊ

	char* pchcc = const_cast<char*>(pch);  //����ͨ��pchcc�޸�ch��ֵ��
	*pchcc = 'd'; //���У�


	//reinterpret_cast:��ָ������ͽ������½��ͣ��ϵͲ��) ��Σ�յ�ת����
	int* ip = &i;
	char* pcs = reinterpret_cast<char*>(ip);  //������

}

int maintrans()
{
	func_type_trans();
	return 0;
}