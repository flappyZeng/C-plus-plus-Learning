#include "StrVec.h"
#include<algorithm>

//移动构造函数， noexcept的作用是告知编译器此函数不抛出异常，这也是
//移动构造函数的常用手法
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
	// TODO: 在此处插入 return 语句
	return *this;
}

StrVec& StrVec::operator=(StrVec&& rhs) noexcept
{
	if (this != &rhs)
	{
		//先判断，先free;
		free();
		element = rhs.element;
		first_free = rhs.first_free;
		cap = rhs.cap;

		rhs.element = rhs.first_free = rhs.cap = nullptr;  //旧的地址指针要置空
	}
	
	return *this;
	// TODO: 在此处插入 return 语句
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

//需要将原来的StrVec中的元素移动到更大的内存空间，使用移动构造函数
void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = element;
	/*
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++)); //告知使用移动构造函数, 这里的move只是将对应元素的所有权交给指定位置的对象，并不存在拷贝行为, std::move返回一个右值引用
	*/
	//使用移动迭代器
	//原来uninitialized_copy调用的是construct的拷贝构造函数，现在使用的是移动构造函数
	auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), newdata);
	free();
	element = newdata;
	first_free = last;
	cap = element + newcapacity;
}

//移动迭代器适配器，普通的迭代器的解引用运算符返回一个指向元素的左值，
//但是移动迭代器的解引用运算符返回一个指向该元素的 右值引用
//使用make_move_iterator将普通的迭代器换成一个移动迭代器，其他照常；

