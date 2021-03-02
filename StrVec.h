#ifndef _STRVEC_H
#define _STRVEC_H

#include<memory>
#include<string>

class StrVec {
	static std::allocator<std::string>alloc;

private:
	std::string* element;
	std::string* first_free;
	std::string* cap;

	//���ߺ���
	void chk_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}

	std::pair<std::string*, std::string*>alloc_n_copy(const std::string*, const std::string*);
	void free();
	void reallocate();

public:
	StrVec(StrVec&&s) noexcept; //�ƶ����캯��,������ֵ����
	StrVec() : element(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(const StrVec&);
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&&) noexcept; //�ƶ���ֵ�����
	StrVec(const std::initializer_list<std::string>& s);
	~StrVec() { free(); };
	
	void push_back(const std::string&);
	void push_back(std::string&& s);
	size_t size() { return first_free - element; }
	size_t capacity() { return cap - element; }
	std::string* begin() const { return element; }
	std::string* end() const { return first_free; }
};
std::allocator<std::string> StrVec::alloc =  std::allocator<std::string>();

/*
ps: �������Զ��ϳ��ƶ����캯����Ҫ��
		������û�ж����κΰ汾�Ŀ������Ƴ�Ա���������ÿһ����static���ݳ�Ա�������ƶ���
	�������Ż�Ϊ����ϳ��ƶ����캯�������ƶ���ֵ�����

	1.���������� �ƶ����� ���͵ĳ�Ա
    2.���һ����Ա�������ͣ��Ҹ����ж�Ӧ���ƶ�������������Ҳ���ƶ������Ա


	����ඨ����һ���ƶ����캯������һ���ƶ���ֵ������������ĺϳɿ������캯���Ϳ�����ֵ������ᱻ����Ϊɾ����
	������������һ���ඨ�����ƶ����캯�������ƶ���ֵ����������Ǿͱ���Ҫ�ֶ��Ķ�����ص�
	�������캯���Լ���ֵ�������

	StrVec v1, v2;
	�ƶ����캯���Ϳ������캯����ʹ�ó�����
	�ƶ����캯��������ֵ��
	StrVec getVec(istream &);
	v2 = getVec(cin);  
	��ʽ���ǵ����ƶ����캯������ΪgetVec���ص���һ����ֵ

	�������캯������һ����ֵ
	v2 = v1;

	������û�ж����ƶ����캯��ʱ����ʹʹ����move������Ҳ��ͨ��ת�����ÿ������캯��
	class Foo{
	public:
		Foo() = default;
		Foo(const Foo&);
	};
	Foo x;
	Foo y(x);
	Foo z(std::move(x));
	�������õĶ��ǿ������캯������Ϊû�ж�����ص��ƶ����캯��

	*/
#endif // !_STRVEC_H