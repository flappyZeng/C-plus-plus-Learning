#pragma once
#include<memory>
#include<set>
#include"quote.h"

class cmp {
public:
	bool operator()(const std::shared_ptr<Quote>& lhs,
		const std::shared_ptr<Quote>& rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}
};
class Basket{
public:
	void add_item(const std::shared_ptr<Quote>& sale) { items.insert(sale); }
	void add_item(const Quote& sale);
	void add_item(const Quote&& sale);
	double total_receipt(std::ostream& os) const;

private:
	using spQ = std::shared_ptr<Quote>;
	static bool compare(std::shared_ptr<Quote> a, std::shared_ptr<Quote> b) { return a->isbn() < b->isbn(); }
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*>items{compare};
};
