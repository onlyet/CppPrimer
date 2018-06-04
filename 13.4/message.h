#pragma once
#include <string>
#include <set>
#include "folder.h"

class Folder;

class Message {
	friend class Folder;
	friend void swap(Message&, Message&);
public:
	explicit Message(const std::string &str = ""):
		contents(str){}
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	
	void save(Folder&);
	void remove(Folder&);

	void addFolder(Folder*);
	void remFolder(Folder*);

private:
	void add_to_Folders(const Message&);
	void remove_from_Floders();
private:
	std::string contents;
	std::set<Folder*> folders;
};

void Message::add_to_Folders(const Message& msg)
{
	for (auto &folder : msg.folders)
		folder->addMsg(this);
}
void Message::remove_from_Floders()
{
	for (auto & folder : this->folders)
		folder->remMsg(this);
}

void Message::save(Folder& f)
{
	f.addMsg(this);
	folders.insert(&f);
}

void Message::remove(Folder& f)
{
	f.remMsg(this);
	folders.erase(&f);
}

Message::Message(const Message& msg) 
	: contents(msg.contents), folders(msg.folders)
{
	add_to_Folders(msg);
}

Message& Message::operator=(const Message& msg)
{
	remove_from_Floders();
	contents = msg.contents;
	folders = msg.folders;
	add_to_Folders(msg);

	return *this;
}

Message::~Message()
{
	remove_from_Floders();
}

void swap(Message& l, Message &r)
{
	using std::swap;
	l.remove_from_Floders();
	r.remove_from_Floders();
	swap(l.contents, r.contents);
	swap(l.folders, r.folders);
	l.add_to_Folders(l);
	r.add_to_Folders(r);
}

void Message::addFolder(Folder *f)
{
	folders.insert(f);
}

void Message::remFolder(Folder *f)
{
	folders.erase(f);
}