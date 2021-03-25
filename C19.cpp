#include<iostream>
#include<cstdlib>
#include<string>
#include"Query.h"
#include"Screen.h"
using namespace std;

//����new ��delete
//�������������new��delete����������new ��delete�����Ǿ�̬�ģ���Ϊnew�ĵ����ڶ�����֮ǰ��delete�ĵ����ڶ�������֮�� ͬʱҲ���ܲ����κ����е����ݳ�Ա

/*
void* operator new(size_t size) {
	if (void* mem = malloc(size))
		return mem;
	else
		throw bad_alloc();
}
void operator delete(void* mem) noexcept
{
	free(mem);
}
*/
//�����������������ٶ��󣬵��ǲ����ͷ��ڴ�

//dynamic_cast�����
// dynamic_cast<type*>(e)  , ָ������ת��ʧ�ܣ���e��0
// dynamic_cast<type&>(e)  �� ��������ת��ʧ�� ���׳��쳣bad_cast
// dynamic_cast<type&&>(e)	  ��������ת��ʧ�� ���׳��쳣bad_cast

//������type������һ�������ͣ�����ͨ�������Ӧ�����麯��

//e������Ҳ��Ҫ��
// 1.e��Ŀ������type�� ���У�ע���ǹ��У� ������
// 2.e��Ŀ������type�Ĺ��л���
// 3.e��Ŀ����type;

//C19T3
class A {
public:
	A() { cout << "A()" << endl; }
	virtual ~A() { cout << "~A()" << endl; };
};

class B :public A{
public:
	B() { cout << "B()" << endl; };
	virtual ~B() { cout << "~B()" << endl; };
};

class C :public B {
public:
	C() { cout << "C()" << endl; }
	virtual ~C() { cout << "~C()" << endl; };
};

class D :public B, public A {
public:
	D() { cout << "D()" << endl; }
	virtual ~D() { cout << "~D()" << endl; };
};


//ö������

//�޶��������ö������
enum class open_modes {input, output, append};

//���޶��������ö������
enum color {red, yellow = 3, green};

//������ʹ������
color eyes = green;  //����
//open_modes in = input; �����У���Ϊ�޶��������򣬿������Ϊnamespace,Ҫʹ���޶���
open_modes in = open_modes::input;

//ö�ٳ�Ա�������const������������һ��ö�ٳ�Ա�൱��������һ���������ʽ
constexpr color book_color = red;


//���������޶��������ö�ٲ��ᷢ�����͵� ��ʽת��
int i = color::red;  //����
//int j = open_modes::input; ���󣬲�����ʽת��Ϊint

//ͨ����������ö�������ڲ�����������
//���ڲ��޶��������ö�����ͣ���Ĭ���������л�����������ģ���˴���Σ�գ������������ʱ����ȷ˵���ڲ����ݵ�����
//�����޶��������ö�����ͣ���Ĭ��������int�����Բ�����ȷ����
enum appen_size : unsigned {small ,middle, big};

int main()
{
	std::string *sp = new string("a value");
	int* p = new(nothrow) int(10);  //��ʽҪ����ò��׳��쳣��new�����
	int* q = new(p) int(20);  //����һ��ָ���ַ����ônew���������µ��ڴ棬�����þ��ڴ�
	cout << *p << endl;

	A* pa = new C;
	if (B * pb = dynamic_cast<B*>(pa))
		cout << "True" << endl;
	else
		cout << "False" << endl;

	B* pbb = new B;   //����ط�Ϊʲô��false�����ϵڶ�����B��C�Ĺ��л���
	if (C * pc = dynamic_cast<C*>(pbb))
		cout << "True" << endl;
	else
		cout << "False" << endl;

	A* paa = new D;
	if (B * pb = dynamic_cast<B*>(paa))
		cout << "True" << endl;
	else
		cout << "False" << endl;
	string* s = new string("6");
	string* b = new string("abc");
	cout << (typeid(*pa) == typeid(*paa)) << endl;  //�Ƚ϶���������Ƿ���ͬ

	Query_base* qu = new AndQuery(Query("abc"), Query("cde"));
	AndQuery* aq;
	if (aq = dynamic_cast<AndQuery*>(qu))
		cout << "true" << endl;
	else
		cout << "false" << endl;

	AndQuery aqq = AndQuery(Query("abc"), Query("cde"));
	Query_base& qs = aqq;
	const AndQuery& aqs = dynamic_cast<AndQuery&>(qs);
	/*
	try {
	   //����
		const AndQuery& aqs = dynamic_cast<AndQuery&>(qs);
		cout << "true" << endl;
	}
	catch (bad_cast) {
		cout << "false" << endl;
	}
	*/
	//����һ����
	cout << (typeid(*aq) == typeid(aqs)) << endl;
	cout << (typeid(*aq) == typeid(AndQuery)) << endl;
	cout << (typeid(aqs) == typeid(AndQuery)) << endl;

	cout << typeid(*pa).name() << endl;

	//��Աָ�룺����ָ����ķǾ�̬��Ա��ָ��
	const string Screen::* pdata = Screen::data();    //������һ��ָ��Screen���congs string��Ա��ָ�루ֻ�ܶ�ȡ������д�룩
	Screen myScreen, *pScreen = &myScreen;
	//auto s = myScreen.*pdata;
	auto s = pScreen->*pdata;

	auto pmf = &Screen::get_cursor;
	//pmf = &Screen::get; ��������Ϊ����ָ���Ӧ�ĺ����ķ���ֵ���Ͳ�һ��
	return 0;
}