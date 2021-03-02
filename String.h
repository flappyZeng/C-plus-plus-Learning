#pragma once
#include<memory>
#include<algorithm>
#include<string>
class String
{
	static std::allocator<char>alloc;
private:
	char* elements;
	char* first_free;
	char* cap;

public:
	std::pair<char*, char*>alloc_n_copy(const char*, const char*);
	void free();
	void reallocate();
	size_t size() { return first_free - elements; }
	size_t capacity() { return cap - elements; }


	String() : elements(nullptr), first_free(nullptr), cap(nullptr) { print( "调用默认构造函数" ); }
	String(const char* p);
	String(const String& rhs);
	String& operator=(const String & rhs);
	String(String&& s);
	String& operator=(String&& rhs);
	void print(const std::string& s);
};


