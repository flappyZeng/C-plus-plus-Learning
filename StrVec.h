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
		������û�ж����κΰ汾�Ŀ������Ƴ�Ա���������ÿһ����static���ݳ�Ա�������ƶ�ʱ
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
		Vec(Vec&& s) noexcept; //�ƶ����캯��,������ֵ����
		Vec() : element(nullptr), first_free(nullptr), cap(nullptr) {}
		Vec(const Vec&);
		Vec& operator=(const Vec&);
		Vec& operator=(Vec&&) noexcept; //�ƶ���ֵ�����
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

	template<typename T>
	Vec<T>::Vec(Vec&& s) noexcept: //�ƶ����캯��,�����쳣
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
		// TODO: �ڴ˴����� return ���
		return *this;
	}

	template<typename T>
	Vec<T>& Vec<T>::operator=(Vec<T>&& rhs) noexcept
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