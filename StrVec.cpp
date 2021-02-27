#include "StrVec.h"

void StrVec::push_back(const std::string& s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
};

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string* a, const std::string* b)
{
	auto data = alloc.allocate(b - a);
	return { data, std::uninitialized_copy(a, b, data) };
}