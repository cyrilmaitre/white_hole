#pragma once
#include "Job.h"
#include "Factory.h"

class Job;

// Define
#define JOB_CONFIG					"job-"
#define JOB_CONFIG_MERCENARY		JOB_CONFIG"1"
#define JOB_CONFIG_INDUSTRIALIST	JOB_CONFIG"2"
#define JOB_CONFIG_TRADER			JOB_CONFIG"3"
#define JOB_CONFIG_BUILDER			JOB_CONFIG"4"

class JobFactory: public Factory<Job>
{
public:
	// Constructor - Destructor
	JobFactory(void);
	~JobFactory(void);

	// Methods
	Job* getJobMercenary();
	Job* getJobIndustrialist();
	Job* getJobTrader();
	Job* getJobBuilder();
	Job* getJob(std::string p_configName, bool p_useLoaded = true);
	Job* getJob(long p_jobId, bool p_useLoaded = true);

	// Static
	static JobFactory *mInstance;
};

