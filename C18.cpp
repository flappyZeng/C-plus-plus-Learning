#include<iostream>
#include<memory>
//多重继承
struct Base1 {
	Base1() = default;
	Base1(const std::string&);
	Base1(std::shared_ptr<int>);
	
	std::string name;
};

struct Base2{
	Base2() = default;
	Base2(const std::string&);
	Base2(int);

	std::string catagory;
};

//下列会报错，因为D1继承了两个相同的接受string的构造函数，如果没有定义下面的D1(const std::string&s)无法通过编译
struct D1 : public Base1, public Base2 {
	using Base1::Base1;
	using Base2::Base2;
	D1(const std::string& s) :Base1(s), Base2(s) {}
};

//如果继承相同的构造函数，则该类必须为改构造函数提供自己实现的版本
struct D2 : public Base1, public Base2 {
	using Base1::Base1;
	using Base2::Base2;;
	D2(const std::string& s) :Base1(s), Base2(s) {}
	D2() = default;
};

class base {
public:
	base() = default;
	base(int a): k(a) { std::cout << "base" << std::endl; }
	~base() { std::cout << "~base" << std::endl; }
private:
	int k;
};
class derive : public base {
public:
	derive() = default;
	derive(int b,  int k = 0) :base(k), b(b) { std::cout << "derive" << std::endl; }
	~derive() { std::cout << "~derive" << std::endl; }
private:
	int b;
};

class Do : public derive {
public:
	Do() = default;
	Do(int k, int b) : derive(k, b), num(0), B(3), A(5) { std::cout << "Do" << std::endl; }
	~Do() { std::cout << "~Do" << std::endl; }
private:
	int num;
	base A;
	derive B;
};


class AnimalZoo {
public:
	//AnimalZoo():catagory("Animal in Zoo") { std::cout << "default AnimalZoo" << std::endl; }
	AnimalZoo(const std::string& s = "Animal in Zoo") :catagory(s) { std::cout << "AnimalZoo" << std::endl; }
	~AnimalZoo(){ std::cout << "~AnimalZoo" << std::endl; }
public:
	std::string catagory;
};

class Bear : public  virtual AnimalZoo {
public:
	 Bear(const std::string& _bearName = "anonymous bear", const std::string& zoo = "Animal in Zoo(Bear)") :AnimalZoo(zoo), bear_name(_bearName) { std::cout << "Bear" << std::endl; }
	~Bear() { std::cout << "~bear" << std::endl; }
public:
	std::string bear_name;
};

class Endangerous :  virtual public AnimalZoo {
public:
	Endangerous(const int level = 1, const std::string & _zooName = "Animal in Zoo(Endangerous)"):AnimalZoo(_zooName),endangerous_level(level)  { std::cout << "endangerous" << std::endl; }
	~Endangerous(){ std::cout << "~endangerous" << std::endl; }
public:
	int endangerous_level;
};

//默认情况下，虚基类总是先于非虚基类构造，与他们的继承体系的次序与位置无关
class Panda : public Bear, public Endangerous {
public:
	//Panda() :  panda_name("anonymous panda") { std::cout << "default Panda" << std::endl; }
	//构造顺序 ： AnimalZoo -> Bear -> Endangerous -> Panda, 析构顺序相反
	Panda(const std::string& zoo = "Animal in Zoo", const int level = 1, const std::string _panda_name = "anonymous panda", const std::string &bear_name = "bear"):Endangerous(level), Bear(bear_name), panda_name(_panda_name){ std::cout << "Panda" << std::endl; }
	~Panda(){ std::cout << "~Panda" << std::endl; }
public:
	std::string panda_name;
};




int mainC18()
{
	/*
	Do d;
	std::cout << "无参数" << std::endl;
	std::cout << std::endl;
	Do D(1, 2);
	*/
	Panda da("DaXingAnLing", 1, "LingLing");
	std::cout << da.Panda::Bear::catagory << std::endl;  //如果不是虚继承，则更具名称限定符访问对应基类的直接基类的AnimalZoo的成员，是虚继承的话，被继承的子类负责公共基类的子部分的定义，访问的AnimalZoo成员只有唯一的一种
	return 0;
}