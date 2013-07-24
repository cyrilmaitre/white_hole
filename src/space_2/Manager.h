#pragma once
#include "ManagerConfig.h"

class Manager
{
public:
	// Getters - Setters
	ManagerConfig* getConfig();
	void setConfig(ManagerConfig* p_config);

	static Manager* getInstance();


private:
	// Constructor - Destructor
	Manager(void);
	~Manager(void);

	// Methods
	void deleteConfig();

	// Attributs
	ManagerConfig* mConfig;

	static Manager* mInstance;
};
