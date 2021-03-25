#include<iostream>
#include<tuple>  //C++11
#include<regex> //c++11 正则表达式
#include<iomanip>

namespace a {
	inline namespace b {
		int aa = 0;
		int bb = 0;
	}
	inline namespace d {
		int aa = 2;
		int bb = 3;
	}
	namespace c {
		int aa = 1;
		int bb = 1;
	}
}
using namespace std;
int main17()
{
	std::tuple<int, float, char>tp = { 1, 1.1,0 };
	std::tuple<int, float, char>tp2{ 1, 2.0, 0 };
	//std::cout << tp[0]; 不能下标访问
	std::cout << std::get<0>(tp) << std::endl; //只能用get方法。

	/*
	std::string pattern{ "{^c}ei" };
	pattern = "[[:alpha:]]*{^c}ei[[:alpha:]]*";
	std::cout << pattern << std::endl;
	regex e(pattern);
	std::smatch result;
	std::string test_set = "receipt friend thief receive";
	std::cout << 3 << std::endl;
	if (std::regex_search(test_set, result, e))
		std::cout << result.str() << std::endl;
	*/
	//cout << std::internal << std::setw(12) << " abcde" << "a" << endl;
	//cout << std::left << std::setw(12) << " abcde" << "a" <<endl;
	//cout << std::right << std::setw(12) << " abcde" <<"a" << endl;
	cout << a::b::aa << endl;
	return 0;
}