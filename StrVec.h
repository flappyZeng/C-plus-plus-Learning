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

	//工具函数
	void chk_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}

	std::pair<std::string*, std::string*>alloc_n_copy(const std::string*, const std::string*);
	void free();
	void reallocate();

public:
	StrVec(StrVec&&s) noexcept; //移动构造函数,带有右值引用
	StrVec() : element(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(const StrVec&);
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&&) noexcept; //移动赋值运算符
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
ps: 编译器自动合成移动构造函数的要求：
		当类中没有定义任何版本的拷贝控制成员，并且类的每一个非static数据成员都可以移动时
	编译器才会为该类合成移动构造函数或者移动赋值运算符

	1.编译器可以 移动内置 类型的成员
    2.如果一个成员是类类型，且该类有对应的移动操作，编译器也能移动这个成员


	如果类定义了一个移动构造函数或者一个移动赋值运算符，则该类的合成拷贝构造函数和拷贝赋值运算符会被定义为删除的
	这告诉我们如果一个类定义了移动构造函数或者移动赋值运算符，我们就必须要手动的定义相关的
	拷贝构造函数以及赋值运算符。

	StrVec v1, v2;
	移动构造函数和拷贝构造函数的使用场景：
	移动构造函数接收右值：
	StrVec getVec(istream &);
	v2 = getVec(cin);  
	上式就是调用移动构造函数，因为getVec返回的是一个右值

	拷贝构造函数接收一个左值
	v2 = v1;

	当类中没有定义移动构造函数时，即使使用了move操作，也会通过转换调用拷贝构造函数
	class Foo{
	public:
		Foo() = default;
		Foo(const Foo&);
	};
	Foo x;
	Foo y(x);
	Foo z(std::move(x));
	上述调用的都是拷贝构造函数，因为没有定义相关的移动构造函数

	*/

	template<typename T>
	class Vec {
		static std::allocator<T>alloc;
	private:
		T* element;
		T* first_free;
		T* cap;

		void chk_n_alloc()
		{
			if (size() == capacity()) reallocate();
		}

		std::pair<T*, T*> alloc_n_copy(const T*, const T*);
		void free();
		void reallocate();

	public:
		Vec(Vec&& s) noexcept; //移动构造函数,带有右值引用
		Vec() : element(nullptr), first_free(nullptr), cap(nullptr) {}
		Vec(const Vec&);
		Vec& operator=(const Vec&);
		Vec& operator=(Vec&&) noexcept; //移动赋值运算符
		Vec(const std::initializer_list<T>& s);
		~Vec() { free(); };

		void push_back(const T&);
		void push_back(T&& s);
		size_t size() { return first_free - element; }
		size_t capacity() { return cap - element; }
		std::string* begin() const { return element; }
		std::string* end() const { return first_free; }
	};

	template<typename T>
	std::pair<T*, T*> Vec<T>::alloc_n_copy(const T* a, const T* b)
	{
		auto data = alloc.allocate(b - a);
		return { data, std::uninitialized_copy(a, b, data) };
	}

	template<typename T>
	void Vec<T>::free() {
		if (element)
		{
			/*
			for (auto p = first_free; p != element;)
				alloc.destroy(--p);
			*/
			std::for_each(first_free, element, [this](T& p) { alloc.destroy(&p); });
			alloc.deallocate(element, cap - element);
		}
	}

	template<typename T>
	void Vec<T>::reallocate()
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

	template<typename T>
	Vec<T>::Vec(Vec&& s) noexcept: //移动构造函数,不报异常
	element(s.element), first_free(s.first_free), cap(s.cap)
	{
		s.element = s.first_free = s.cap = nullptr;
	}

	template<typename T>
	Vec<T>::Vec(const Vec& s)
	{
		auto newdata = alloc_n_copy(s.begin(), s.end());
		element = newdata.first;
		first_free = cap = newdata.second;
	}

	template<typename T>
	Vec<T>& Vec<T>::operator=(const Vec<T>& rhs)
	{
		auto data = alloc_n_copy(rhs.begin(), rhs.end());
		free();
		element = data.first;
		first_free = cap = data.second;
		// TODO: 在此处插入 return 语句
		return *this;
	}

	template<typename T>
	Vec<T>& Vec<T>::operator=(Vec<T>&& rhs) noexcept
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

	template<typename T>
	Vec<T>::Vec(const std::initializer_list<T>& s)
	{
		auto newdata = alloc_n_copy(s.begin(), s.end());
		element = newdata.first;
		first_free = cap = newdata.second;
	}

	template<typename T>
	void Vec<T>::push_back(const T& s)
	{
		chk_n_alloc();
		alloc.construct(first_free++, s);
	}
	template<typename T>
	void Vec<T>::push_back( T&& s)
	{
		chk_n_alloc();
		alloc.construct(first_free++, std::move(s));
	}
	;
#endif // !_STRVEC_H