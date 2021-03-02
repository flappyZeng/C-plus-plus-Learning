#include "String.h"
#include "String.h"
#include<iostream>


std::allocator<char> String::alloc = std::allocator<char>();
std::pair<char*, char*> String::alloc_n_copy(const char*p, const char*q)
{
	auto s1 = alloc.allocate(q - p);
	auto s2 = std::uninitialized_copy(p, q, s1);
	return std::pair<char*, char*>({s1, s2});
}

void String::free()
{
	if (elements)
	{
		std::for_each(first_free, elements, [this](char& c) {alloc.destroy(&c); });
		alloc.deallocate(elements, cap - elements);
	}
}

void String::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++)); //告知使用移动构造函数, 这里的move只是将对应元素的所有权交给指定位置的对象，并不存在拷贝行为
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

String::String(const char* p)
{
	char* q = const_cast<char*>(p);
	while (*q) { q++; }
	auto newdata = alloc_n_copy(p, q);
}

String::String(const String& rhs)
{
	auto p = alloc_n_copy(rhs.elements, rhs.first_free);
	elements = p.first;
	first_free = cap = p.second;
	std::cout << "调用拷贝构造函数" << std::endl;
}

String& String::operator=(const String& rhs)
{
	auto data = alloc_n_copy(rhs.elements, rhs.first_free);
	free();
	elements = data.first;
	first_free = cap = data.second;
	std::cout << "调用赋值构造函数" << std::endl;
	return *this;
	// TODO: 在此处插入 return 语句
}

String::String(String&& s):
elements(s.elements), first_free(s.first_free), cap(s.cap)
{
	std::cout << "调用移动构造函数" << std::endl;
	s.elements = s.first_free = s.cap = nullptr;
}

String& String::operator=(String&& rhs)
{
	if (this != &rhs)
	{
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	std::cout << "调用移动赋值运算符" << std::endl;
	return *this;
	// TODO: 在此处插入 return 语句
}

void String::print(const std::string& s)
{
	std::cout << s << std::endl;
}
