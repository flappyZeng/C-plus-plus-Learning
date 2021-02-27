#include"TextQuery.h"


TextQuery::TextQuery(std::ifstream& infile):file(new std::vector<std::string>()) {
	std::string line;
	std::string word;
	int countLine = 0;
	while (std::getline(infile, line))
	{
		file->emplace_back(line);
		std::istringstream iss(line);
		while (iss >> word)
		{
			auto& lines = wm[word];  //map下标操作会默认添加新的键值对
			if (!lines)
				lines.reset(new std::set<int>);  //reset将指针指向新的内存空间，并销毁原有指示的空间
			lines->insert(countLine);
		}
		countLine++;
	}
}

TextQueryWithStrBlob::TextQueryWithStrBlob(std::ifstream& infile): file(new StrBlob())
{
	std::string line;
	std::string word;
	int countLine = 0;
	while (std::getline(infile, line))
	{
		file->push_back(line);
		std::istringstream iss(line);
		while (iss >> word)
		{
			auto& lines = wm[word];  //map下标操作会默认添加新的键值对
			if (!lines)
				lines.reset(new std::set<int>);  //reset将指针指向新的内存空间，并销毁原有指示的空间
			lines->insert(countLine);
		}
		countLine++;
	}
}
QueryResult TextQuery::query(std::string& s)
{
	static wsetp nodata(new std::set<int>);  //静态变量，就可以当作引用参数传递
	auto loc = wm.find(s);
	if (loc == wm.end())
	{
		return QueryResult(s, nodata, file);
	}
	else
		return QueryResult(s, loc->second, file);
}

QueryResultWithSrBlob TextQueryWithStrBlob::query(std::string& s)
{
	static wsetp nodata(new std::set<int>);  //静态变量，就可以当作引用参数传递
	auto loc = wm.find(s);
	if (loc == wm.end())
	{
		return QueryResultWithSrBlob(s, nodata, file);
	}
	else
		return QueryResultWithSrBlob(s, loc->second, file);
}

std::ostream& print(std::ostream& os,const QueryResult& query_result)
{
	os << query_result.sought << " occurs " << query_result.lines->size() << " "
		<< make_plural(query_result.lines->size(), "time", "s") << std::endl;
	for (auto num : *query_result.lines)
	{
		os << "\t(line " << num + 1 << ") ";
		os << *(query_result.file->begin() + num) << std::endl;
	}
	std::cout << std::endl;
	return os;
}

std::ostream& print(std::ostream& os, const QueryResultWithSrBlob& query_result)
{
	os << query_result.sought << " occurs " << query_result.lines->size() << " "
		<< make_plural(query_result.lines->size(), "time", "s") << std::endl;
	for (auto num : *query_result.lines)
	{
		os << "\t(line " << num + 1 << ") ";
		os << StrBlobPtr(*query_result.file,num).deref()  << std::endl;
	}
	std::cout << std::endl;
	return os;
}
std::string make_plural(size_t ctr, const std::string& word, const std::string& end)
{
	return (ctr > 1) ? word + end : word;
}

void runQueries(std::ifstream& infile)
{
	
	TextQueryWithStrBlob tq(infile);
	while (true)
	{
		std::cout << "Enter wrod to look for, or q to quit: ";
		std::string s;
		if (!(std::cin >> s) || s == "q") break;
		print(std::cout, tq.query(s));
	}
}
