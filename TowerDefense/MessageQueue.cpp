#include "stdafx.h"
#include "MessageQueue.h"


MessageQueue::MessageQueue()
{
}


MessageQueue::~MessageQueue()
{
}

std::mutex& MessageQueue::getMutex()
{
	return mut;
}

void MessageQueue::push(Message m)
{
	queue.push(m);
}

Message MessageQueue::pop()
{
	Message mg = queue.front();
	queue.pop();
	return mg;
}

int MessageQueue::getsize()
{
	return queue.size();
}
