#include "CommandQueue.h"

void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command popCommand = mQueue.front();
	mQueue.pop();
	return popCommand;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}
