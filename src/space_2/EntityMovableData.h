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

	std::string getReactorSound();
	void setReactorSound(std::string p_sound);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromEntityMovableData(EntityMovableData* p_data);
	virtual void notifyReactorJsonChanged();
	virtual void notifyReactorSoundChanged();


private:
	// Attributs
	std::string mReactorJson;
	std::string mReactorSound;
};

