#pragma once
#include "Resource.h"
#include "Clock.h"

// Define
#define NETWORKJOB_MAX_LIFE		10	// sec
#define NETWORKJOB_RESULT		"result"
#define NETWORKJOB_RESULT_OK	"ok"
#define NETWORKJOB_RESULT_FAIL	"fail"

class NetworkJob
{
public:
	// Constructor - Destructor
	NetworkJob(void);
	~NetworkJob(void);

	// Getters - Setters
	sf::Thread* getJobThread();
	void setJobThread(sf::Thread* p_job);

	bool isRunning();
	void setRunning(bool p_running);

	bool isLaunched();
	void setLaunched(bool p_launched);

	bool isFinished();

	// Methods
	virtual void job() = 0;
	void launch();


protected:
	// Attributs
	mks::Clock mClock;
	sf::Thread *mJobThread;
	bool mRunning;
	bool mLaunched;
};

