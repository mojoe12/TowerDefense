#pragma once

#include <vector>
#include <queue>
#include "Message.h"
#include <mutex>

class MessageQueue
{
public:
	MessageQueue();
	~MessageQueue();

	std::mutex& getMutex();
	void push(Message);
	Message pop();
	int getsize();

private:
	std::queue<Message> queue;
	std::mutex mut;
};

