#include<iostream>
#include"Sales_data.h"
#include <list>
#include "Template.h"
using namespace std;

//����ģ��,��������ʹ�ô���С�ںţ�ʹ�ú�����³���Բ�ǿ�����Կ���ʹ��less�Լ�

//ps: 1.����ģ��Ӧ�þ������ٶ�ʵ�����͵�Ҫ��Ҫ����������ڶ������ͣ�
//    2.�볣�����Ա��ͬ��ģ���ͷ�ļ�����Ҫ���� ���� �Լ� ���塣
template<typename T>
int compare(const T& v1, const T& v2)
{
	if (less<T>()(v1, v2))	return -1;
	if (less<T>()(v2, v1))	return 1;
	return 0;
}

//������ģ�����
template<unsigned N, unsigned M> //���Բ���class����typename������ʹ��ʱ���봫���Ӧ���͵� �������ʽ
int compare(const char(&p1)[N], const char(&p2)[M])
{
	return strcmp(p1, p2);
}
//������� compare("hi", "mom") ����ģ���ʵ������ ->  compare(const char(&p1)[3], const char(&p2)[4]) (�Զ����Ͽ��ַ���Ϊ�ս��)


//Ϊinline��ģ�庯����inline��������template֮��
template<typename T> inline T min(const T&, const T&);



//C16T1:
//ʵ�����Ķ��壺 ��Ϊ����ģ�崫�����Ĳ���ʱ����������ģ���ڵĲ�����typename��class)�滻Ϊ��Ӧ�����ͣ������ɶ�Ӧ�Ĵ��룬�ù��̳�Ϊʵ����

//C16T4 find��ģ��
template<typename ITR, typename T>
ITR Myfind(const ITR& begin, const ITR& end, const T& val)
{
	for (ITR it = begin; it != end; ++it)
		if (*it == val)
			return it;
	return end;
}

//C16T5 �����Լ���begin�Լ�end��
template<typename T, unsigned N>
auto Mybegin(const T (&arr)[N])
{
	return arr;
}
template<typename T, unsigned N>
auto Myend(const T(&arr)[N])
{
	return arr + N;
}

//C16T7
template<typename T, unsigned N>
constexpr size_t getSize(const T(&arr)[N])
{
	return N;
}


int main()
{
	cout << compare(1, 2);
	cout << compare(1.0, 2.0);
	cout << compare('a', 'b');
	//cout << compare(1, 2.0);
	vector<int>vc{ 1, 2, 3, 4, 5, 6 };
	list<string>lst{ initializer_list<string>{"a","b", "c", "d", "e"} };
	cout << Myfind(vc.begin(), vc.end(), 6) - vc.begin() << endl;
	//list��forward���ǲ������洢�� ���Բ�֧�ֵ������ļӼ���ȷ��Ԫ�ص�λ��
	cout << *Myfind(lst.cbegin(), lst.cend(), "d") << endl;
	//compare(Sales_data(), Sales_data());
	auto it = begin(vc);
	return 0;
}