#include<iostream>
#include"Sales_data.h"
#include <list>
#include "Template.h"
#include<functional>
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
auto Mybegin(const T(&arr)[N])
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

template<typename T> T fobj(T a, T b)
{
	plus<T>Tadd;
	return Tadd(a, b);
}
template<typename T> T fref(const T& a, const T& b)
{
	plus<T>Tadd;
	return Tadd(a, b);;
};

std::string s1("a value");
const std::string s2("another value");


//C16T35
template<typename T>T  cal(T a, int b)
{
	plus<T>Tadd;
	return static_cast<T>(Tadd(a, b));
}
template <typename T> T fcn(T a, T b) {
	plus<T>Tadd;
	return static_cast<T>(Tadd(a, b));
}


//�����۵�
int k = std::move(42);

//C16T49
template<typename T> void f(T) {
	cout << "����f(T)" << endl;
}
template<typename T> void f(const T*) {
	cout << "����f(const T*) " << endl;
}
template<typename T> void g(T) {
	cout << "����g(T)" << endl;
}
template<typename T> void g(T*) {
	cout << "����g(T*)" << endl;
}


//�ɱ����ģ��
template<typename T, typename... Args>
void foo(const T& t, const Args& ... rest)
{
	cout << sizeof...(Args) << endl;
	cout << sizeof...(rest) << endl;
}


//���Դ�ӡ���������
template<typename T>
ostream& Myprint(ostream& os, const T& t)
{
	return os << t;
}
template<typename T,  typename ...Args>
ostream& Myprint(ostream& os, const T& t, const Args&... rest)
{
	os << t << ",1 ,  ";
	return Myprint(os, rest...);
}
int mainC17()
{
	cout << compare(1, 2);
	cout << compare(1.0, 2.0);
	cout << compare('a', 'b');
	
	cout << compare("abc", "defg");
	//cout << compare("abc", "def");  �Ͷ��ģ��ͬʱƥ�䣬�޷�ʵ��������˱���
	//cout << compare(1, 2.0);
	vector<int>vc{ 1, 2, 3, 4, 5, 6 };
	list<string>lst{ initializer_list<string>{"a","b", "c", "d", "e"} };
	cout << Myfind(vc.begin(), vc.end(), 6) - vc.begin() << endl;
	//list��forward���ǲ������洢�� ���Բ�֧�ֵ������ļӼ���ȷ��Ԫ�ص�λ��
	cout << *Myfind(lst.cbegin(), lst.cend(), "d") << endl;
	//compare(Sales_data(), Sales_data());
	auto it = begin(vc);

	//fobj(s1, s2);   //����   const string to string��
	//fref(s1, s2);   //����   string& to cosnt string&;
	//int a[10], b[10];
	//fobj(a, b);  //���� arr -> point;
	//fref(a, b);  �����У������� arr -> const arr&��ת����

	double d = 0;
	float f1 = 10.0;
	char c = 0;
	cal(c, 'c');  //���� char -> int;
	cal(d, f1);  //���� cal(double, int); float -> int;
	fcn(c, 'c');  //���У� fcn(char, char) 
	//fcn(d, f); �����У��������Ͳ�ƥ�䣻

	int i = 42, *p = &i;
	const int ci = 0, *p2 = &ci;
	g(42);  //����g(T)
	g(p);   //����g(T*)
	g(ci);  //����g(T)
	g(p2);  //����g(T*)
	f(42);  //����f(T)
	f(p);   //����f(T)
	f(ci);  //����f(T)
	f(p2); //����f(const T*)
	

	int ii = 0; double dd = 3.14; string ss = "how now brown now";
	foo(ii, ss, 42, dd);
	foo(ss, 42, "hi");
	foo(d, ss);
	foo("hi");
	Myprint(cout, ii, dd, ss);
	//vc.emplace_back("abc");

	shared_ptr<int>pps = make_shared<int>(10);
	return 0;
}

