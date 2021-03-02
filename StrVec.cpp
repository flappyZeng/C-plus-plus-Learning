#include "StrVec.h"
#include<algorithm>

//�ƶ����캯���� noexcept�������Ǹ�֪�������˺������׳��쳣����Ҳ��
//�ƶ����캯���ĳ����ַ�
StrVec::StrVec(StrVec&&s) noexcept:
element(s.element), first_free(s.first_free), cap(s.cap)
{
	s.element = s.first_free = s.cap = nullptr;
}

StrVec::StrVec(const StrVec& s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	element = newdata.first;
	first_free = cap = newdata.second;
}

StrVec& StrVec::operator=(const StrVec&rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	element = data.first;
	first_free = cap = data.second;
	// TODO: �ڴ˴����� return ���
	return *this;
}

StrVec& StrVec::operator=(StrVec&& rhs) noexcept
{
	if (this != &rhs)
	{
		//���жϣ���free;
		free();
		element = rhs.element;
		first_free = rhs.first_free;
		cap = rhs.cap;

		rhs.element = rhs.first_free = rhs.cap = nullptr;  //�ɵĵ�ַָ��Ҫ�ÿ�
	}
	
	return *this;
	// TODO: �ڴ˴����� return ���
}

StrVec::StrVec(const std::initializer_list<std::string>& s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	element = newdata.first;
	first_free = cap = newdata.second;
}

void StrVec::push_back(const std::string& s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}
void StrVec::push_back(std::string&& s)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}
;

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string* a, const std::string* b)
{
	auto data = alloc.allocate(b - a);
	return { data, std::uninitialized_copy(a, b, data) };
}

void StrVec::free()
{
	if (element)
	{
		/*
		for (auto p = first_free; p != element;)
			alloc.destroy(--p);
		*/
		std::for_each(first_free, element, [this](std::string&  p) { alloc.destroy(&p); });
		alloc.deallocate(element, cap - element);
	}
}

//��Ҫ��ԭ����StrVec�е�Ԫ���ƶ���������ڴ�ռ䣬ʹ���ƶ����캯��
void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = element;
	/*
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++)); //��֪ʹ���ƶ����캯��, �����moveֻ�ǽ���ӦԪ�ص�����Ȩ����ָ��λ�õĶ��󣬲������ڿ�����Ϊ, std::move����һ����ֵ����
	*/
	//ʹ���ƶ�������
	//ԭ��uninitialized_copy���õ���construct�Ŀ������캯��������ʹ�õ����ƶ����캯��
	auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), newdata);
	free();
	element = newdata;
	first_free = last;
	cap = element + newcapacity;
}

//�ƶ�����������������ͨ�ĵ������Ľ��������������һ��ָ��Ԫ�ص���ֵ��
//�����ƶ��������Ľ��������������һ��ָ���Ԫ�ص� ��ֵ����
//ʹ��make_move_iterator����ͨ�ĵ���������һ���ƶ��������������ճ���

