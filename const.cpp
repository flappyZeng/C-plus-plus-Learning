#include"Base.h"

int func_const()
{
	//����const
	//����const��ʾָ�뱾����һ������
	//�ײ�const��ʾָ����ָ�Ķ�����һ������

	
	int i = 0;
	int* const p1 = &i; // ����һ������const;
	const int c2 = 42; // ��Ҳ��һ������const;
	const int *p2 = &c2; //���ָ��p2�ǿ��Ա��ı�ģ����� p2 = &c1,˵�����Ƕ���const
	const int* const p3 = p2; // ǰ���ǵײ�const�������Ƕ���const


	//int* p = p3;//����Ǳ���ģ�ǰ���ǵײ�const ,�����Ƕ���const
	const int* const p4 = p2; //ǰ���Ƕ���const�������ǵײ�const������ǿ��е�


	/*
		����const ��ʾ����Ķ����ǳ������������������޹�
		�ײ�const����ָ���Լ����ø������͵Ļ������Ͳ����йأ�ָ��ȿ����ǵײ�constҲ�����Ƕ���const)
	*/
	const int* ps = &i;  //�ײ�const
	int* const pt = &i; // ����const

	return 0;
}
