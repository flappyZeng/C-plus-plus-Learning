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

	//¹¤¾ßº¯Êý
	void chk_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}
	std::pair<std::string*, std::string*>alloc_n_copy(const std::string*, const std::string*);
	void free();
	void reallocate();

public:
	StrVec() : element(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(const StrVec&);
	StrVec& operator=(const StrVec&);
	~StrVec();
	
	void push_back(const std::string&);
	size_t size() { return first_free - element; }
	size_t capacity() { return cap - element; }
	std::string* begin() const { return element; }
	std::string* end() const { return first_free; }


};
#endif // !_STRVEC_H