#pragma once

#include <SFML\System.hpp>

class ConcurrentTask
{
public:
	ConcurrentTask();
	void execute();
	bool isFinished();
	float getCompletion();

private:
	void runTask();

private:
	sf::Thread mThread;
	bool mFinished;
	sf::Clock mElapsedTime;
	sf::Mutex mMutex;
};

