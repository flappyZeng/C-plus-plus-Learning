#include<iostream>
#include"quote.h"
class Base {
public:
	static void statmem() {
		std::cout << "I am static member!" << std::endl;
	}
private:
	static int statVal;
};

int Base::statVal = 0;


class Derived : public Base {
	void f(const Derived _obj)
	{
		Base::statmem();  //���Է���
		Derived::statmem();  //�̳���Ҳ���Է���
		_obj.statmem(); //ͨ��Derived������з���
		statmem();   //DerivedҲ����ͨ��thisָ����ʣ��ȼ���this->statmem();

		// Base::statVal; �޷����ʸ����˽�о�̬����
	}
};

int main()
{
	Quote qu("abc", 3.00);
	Bulk_quote bq("abc", 3.00, 3, 0.3);
	Bulk_quote_exceed bqe("abc", 3.00, 3, 0.2);
	print_total(std::cout, bqe, 4);
	print_total(std::cout, qu, 4);
	print_total(std::cout, bq, 4);
	//Disc_quote dq; ����������Ϊ�������Ķ���
	return 0;
}



