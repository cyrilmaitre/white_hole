#pragma once
#include "NetworkJob.h"

// Define
#define NETWORKJOB_MANAGER_MAX_JOB		256

class NetworkJobManager
{
public:
	// Getters - Setters
	bool hasJob();

	// Methods
	static void init();
	static void uninit();
	static NetworkJobManager* getInstance();

	int getJobCount();
	int getJobCountMax();
	void addJob(NetworkJob* p_job);
	void removeJob(int p_position);
	void update();


private:
	// Constructor - Destructor
	NetworkJobManager(void);
	~NetworkJobManager(void);

	// Attributs
	static NetworkJobManager* mInstance;

	std::vector<NetworkJob*> mJobs;
};

