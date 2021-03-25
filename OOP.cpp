#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include"quote.h"
class Base {
public:
	static void statmem() {
		std::cout << "I am static member!" << std::endl;
	}
	friend class pal;
	void memfcn(Base& b) { b = *this; }  //func

private:
	static int statVal;
public:
	int baseWord;
};

int Base::statVal = 0;

class Derived : private Base {
	void f(const Derived _obj)
	{
		Base::statmem();  //���Է���
		Derived::statmem();  //�̳���Ҳ���Է���
		_obj.statmem(); //ͨ��Derived������з���
		statmem();   //DerivedҲ����ͨ��thisָ����ʣ��ȼ���this->statmem();

		// Base::statVal; �޷����ʸ����˽�о�̬����
	}
private:
	int member;
public:
	using Base::baseWord; //�ı��Ա�ķ���Ȩ�ޣ�����Derived�������û����ܷ���baseWord
};
class pal {
	int f(Base b) { return b.statVal; }
	//int f2(Derived d) { return d.member; } ,���ɷ��ʣ���Ԫ�����д�����
	int f3(Derived d) { return d.baseWord; } //���Է��ʣ�
};

struct Pub_Derv: public Base{
	void memfcn(Base& b) { b = *this; }
};
struct Pro_Derv : protected Base {
	void memfcn(Base& b) { b = *this; }
};
struct Pri_Derv : private Base {
	void memfcn(Base& b) { b = *this; }
};
//�����������ϣ�������ʲô��ʽ�̳���Base,������ĳ�Ա�����Լ���Ԫ����������������ൽ���������ת��


struct Derived_from_Public : public Pub_Derv {
	void memfcn(Base& b) { b = *this; }
};
struct Derived_from_Private : public Pri_Derv {
	//void memfcn(Base& b) { b = *this; }
};
struct Derived_From_Protected : public Pro_Derv {
	void memfcn(Base& b) { b = *this; }
};
//�����������������ĳ�Ա�����Լ���Ԫ������������������public����protected�ļ̳з�ʽ�����������ת��

class BaseT {
	char data[3];
public:
	virtual void f() { std::cout << "Base::f" << std::endl; }
	virtual void g() { std::cout << "Base::g" << std::endl; }
	virtual void h() { std::cout << "Base::h" << std::endl; }

};
int f()
{
	char c = 'a';
	return true;
}
class BaseE {

};
int maint()
{
	
	/*
	Quote qu("abc", 3.00);
	Bulk_quote bq("abc", 3.00, 3, 0.3);
	Bulk_quote_exceed bqe("abc", 3.00, 3, 0.2);
	print_total(std::cout, bqe, 4);
	print_total(std::cout, qu, 4);
	print_total(std::cout, bq, 4);
	
	Derived D = Derived();
	std::cout << D.baseWord << std::endl; //���Է��ʣ���Ϊusing Base::baseWord;
	//Disc_quote dq; ����������Ϊ�������Ķ���
	Pub_Derv d1;
	Pri_Derv d2;
	Pro_Derv d3;
	Derived_from_Public dd1;
	Derived_from_Private dd2;
	Derived_From_Protected dd3;

	Base* p = &d1;  //���У���Ϊd1��public�̳���base
	//Base* p2 = &d2;  �����У���Ϊd2��private�̳���base;
	//Base* p3 = &d3;  �����У���Ϊd2��protected�̳���base;
	Base* p4 = &dd1;  //���У�dd1��public�̳���Pub_Derv����Pub_Derv��public�̳���Base;
	//Base* p5 = &dd2; �����У�d2�������У�ͬ��
	//Base *p6 = &dd3; �����У�d3�������У�

	std::set<int>vc{ 1,2 ,3, 4, 5, 6, 7, 8, 9 };
	std::cout << vc.count(1) << std::endl;
	
	char s1[] = { " abcd " }; 
	int a[3];
	a[0] = 0; a[1] = 1; a[2] = 2;
	int* p, * q;
	p = a;
	q = &a[2];
	//std::cout << a[q - p];
	std::cout << sizeof(BaseT) << std::endl;
	*/
	int k = 2000;
	while (k > 1)
	{
		k = k >> 1;
		std::cout << 2;
	}
	
	int i = 010, j = 10; 
	std::cout << i << j << std::endl;
	printf("%d,%d\n", ++i, j--);
	
	return 0;
}

#include"./Query.h"
int mainQuery()
{
	std::string path = "C:\\Users\\Administrator\\Desktop\\words.txt";
	std::ifstream ifs(path, std::ifstream::in);
	TextQuery text(ifs);
	Query q = Query("is") | Query("are");
	print(std::cout, q.eval(text));
	return 0;
}



