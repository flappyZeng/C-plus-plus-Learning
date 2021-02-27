#include "Message.h"


void Folder::addMsg(Message *m)
{
	messages.emplace(m);
}

void Folder::remMsg(Message* m)
{
	messages.erase(m);
}


Folder::Folder(Folder& f)
{
	messages = f.messages;
}

Folder& Folder::operator=(const Folder&f)
{
	messages = f.messages;
}


void Message::add_to_Folders(const Message& m)
{
	for (auto f : m.folders)
		f->addMsg(this);
}

Message::Message(const Message& m):
	contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}

void Message::remove_from_Folders()
{
	for (auto f : folders)
		f->remMsg(this);


}
Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message& rhs)
{
	//��һ����Ϊ�˷�ֹ��ֵ�Ķ����Ǳ���������ɾ��������Mess
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

void swap(Message& lhs, Message& rhs)
{
	using std::swap;
	for (auto f : lhs.folders)
		f->remMsg(&lhs);

	for (auto f : rhs.folders)
		f->remMsg(&rhs);

	//������õ���folder�����Լ�contents����ϵͳʵ�ֵ�swap����;
	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);

	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}
