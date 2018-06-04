#pragma once
#include <string>
#include <set>
//#include "message.h"

class Message;

class Folder {
	//friend class Message;

public:
	Folder(const Folder&);
	Folder& operator=(const Folder&);

	void addMsg(Message* msg)
	{
		messages.insert(msg);
	}
	void remMsg(Message* msg)
	{
		messages.erase(msg);
	}

	void add_to_Messages(const Folder&);
	void remove_from_Messages(const Folder&);

private:
	std::set<Message*> messages;
};

Folder::Folder(const Folder& f) 
	: messages(f.messages)
{
	add_to_Messages(f);
}

Folder & Folder::operator=(const Folder &f)
{
	remove_from_Messages(*this);
	messages = f.messages;
	add_to_Messages(*this);

	return *this;
}

void Folder::add_to_Messages(const Folder& f)
{
	for (auto msg : f.messages)
		msg->addFolder(this);
}

void Folder::remove_from_Messages(const Folder& f)
{
	for (auto msg : f.messages)
		msg->remFolder(this);
}

