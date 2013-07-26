#pragma once
#include "Resource.h"
#include "KeyValueFile.h"


class EntityData
{
public:
	// Constructor - Destructor
	EntityData(void);
	~EntityData(void);

	// Getters - Setters
	std::string getFlashingLightJson();
	void setFlashingLightJson(std::string p_json);

	std::string getRadarJson();
	void setRadarJson(std::string p_json);

	std::string getTurretJson();
	void setTurretJson(std::string p_json);

	std::string getWeaponJson();
	void setWeaponJson(std::string p_json);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromEntityData(EntityData* p_data);
	virtual void notifyFlashingLightJsonChanged();
	virtual void notifyRadarJsonChanged();
	virtual void notifyTurretJsonChanged();
	virtual void notifyWeaponJsonChanged();


private:
	// Attributs
	std::string mFlashingLightJson;
	std::string mRadarJson;
	std::string mTurretJson;
	std::string mWeaponJson;
};

