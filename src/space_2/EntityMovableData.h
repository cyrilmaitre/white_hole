#pragma once
#include "Resource.h"
#include "KeyValueFile.h"


class EntityMovableData
{
public:
	// Constructor - Destructor
	EntityMovableData(void);
	~EntityMovableData(void);

	// Getters - Setters
	std::string getReactorJson();
	void setReactorJson(std::string p_json);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromEntityMovableData(EntityMovableData* p_data);
	virtual void notifyReactorJsonChanged();


private:
	// Attributs
	std::string mReactorJson;
};

