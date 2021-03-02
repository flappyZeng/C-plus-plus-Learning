#ifndef MESSAGE_H
#define MESSAGE_H

#pragma once

#include<string>
#include<set>
class Message;

class Folder {
public:
	Folder() {}
	Folder(Folder& f) : messages(f.messages) {};
	Folder& operator=(const Folder&);

	void addMsg(Message*);
	void remMsg(Message*);
private:
	std::set<Message*>messages;
};

class Message{
	friend class Folder;
	friend void swap(Message& lhs, Message& rhs);
public:
	explicit Message(const std::string& str = "") : contents(str) {}
	Message(const Message& mes);
	Message& operator=(const Message& mes);
	~Message();
	void save(Folder& f)
	{
		folders.insert(&f);
		f.addMsg(this);
	}
	void remove(Folder& f)
	{
		folders.erase(&f);
		f.remMsg(this);
	}

	//将m对应的folders指向本身
	void move_folders(Message* m);  //使用移动构造函数移动folders
	Message& operator=(Message&& m); //移动赋值运算符
private:
	std::string contents;
	std::set<Folder*>folders;
	//相关的工具函数
	void add_to_Folders(const Message&);
	void remove_from_Folders();

};
#endif // !MESSAGE_H



