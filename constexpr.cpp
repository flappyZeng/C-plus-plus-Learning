#include"Base.h"

//using ������Ӧ�ó�����ͷ�ļ���
using std::cin;
using std::cout;
//c++11
/*
	constexpr c++11�¹涨�Ĺؼ���
	����constexpr��һ����һ�����������ұ���ʹ�ó�����ʼ��
*/
constexpr int  retInt()
{
	return 10;
}

int func_constexpr()
{
	int k = 10;
	const int mf = 10;
	constexpr int num = 20;   // ����һ��constexpr����
	// constexpr int num3 = k �������У���Ϊk���ǳ���
	constexpr int num2 = mf + 1; // ʹ��һ����������constexpr
	constexpr int num4 = retInt(); //ֻ�к������ص���constexpr���Ͳſ���

	// ָ��Ҳ�ܶ���Ϊconstexpr���ͣ�����ָ�����ָ��nullptr����0��̶���ַ�Ķ���
	//constexpr int* p = &num; ����
	constexpr int* ps = nullptr; // ����
	constexpr int* p = 0; // ����
	
	return 0;
}

void testFunction()
{
	int z = 0, &r = z;
	auto a = r; //����
	
	const int ci = z, &cr = ci;  // cosnt int , cosnt int&
	auto b = ci; //int
	auto c = cr; //int;
	auto d = &z; //int *;
	auto e = &ci;//const int *;

	a = 42;
	b = 42;
	c = 42; 
	//d = 42; ���� int -> int*
	//e = 42; ���� int --> const int *


	const int i = 42;
	auto j = i;
	const auto& k = i;
	auto* p = &i;
	const auto j2 = i, & k2 = i;
}
/*
����ֵ���ͣ�
	�����������͡����������Լ�ָ�붼������ֵ����
	�� �Զ�����ࡢIO�⡢string��������������ֵ����

*/


// decltype ����Ҫ��ȷ���ʽ��ֵ���ñ��ʽ�ƶϳ�ʼ������
void testDecltype()
{
	int i = 10;
	decltype(i) k = 10; // �ƶ�i������
	decltype(func_constexpr()) ms = 20; //��func_constexpr�ķ���ֵ������Ϊms������

	// decltype��auto��һ����decltype���ص����ͺͱ��ж����͵�һ�µģ�
	const int m = 10;
	auto intA = m; //int����
	decltype(m) constIntA = m; //const int ����

	//decltype�ķ������Ϳ�������������
	int t = 42, *p = &t, &j = i;
	decltype(t + 0) b;
	decltype(*p) d = b; //�������ͣ������ʼ��

	//decltype(())˫�����ŷ��ص�һ������������
	decltype((t)) e = b; //�������ͱ����ʼ��

	//��ֵ�������������
	int a = 3, s = 4;
	decltype(a) c = a; //int
	decltype((a)) r = a; //int &
	decltype(a = s) n = a; //int & ���ʽ�����������

	cout << a << " " << s << " " << c << " " << r << " " << n; // 3 4 3 3 3

}
/*
int main()
{
	testDecltype();
	return 0;
}
*/