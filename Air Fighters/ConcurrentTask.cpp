#include "ConcurrentTask.h"

static float completionTime = 3.0f;

ConcurrentTask::ConcurrentTask()
	: mThread(&ConcurrentTask::runTask, this),
	mFinished(false)
{}

void ConcurrentTask::execute()
{
	mFinished = false;
	mElapsedTime.restart();
	mThread.launch();
}

bool ConcurrentTask::isFinished()
{
	sf::Lock lock(mMutex);
	return mFinished;
}

float ConcurrentTask::getCompletion()
{
	sf::Lock lock(mMutex);

	return mElapsedTime.getElapsedTime().asSeconds() / completionTime;
}

void ConcurrentTask::runTask()
{
	//Dummy task for concurrency testing
	bool finished = false;
	while (!finished)
	{
		sf::Lock lock(mMutex);
		if (mElapsedTime.getElapsedTime().asSeconds >= completionTime)
		{
			finished = true;
		}
	}

	{
		sf::Lock lock(mMutex);
		mFinished = true;
	}
}
