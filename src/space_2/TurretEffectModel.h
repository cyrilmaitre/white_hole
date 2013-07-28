#pragma once
#include "Resource.h"
#include "KeyValueFile.h"


class TurretEffectModel
{
public:
	// Constructor - Destructor
	TurretEffectModel(KeyValueFile* p_config);
	~TurretEffectModel(void);

	// Getters - Setters
	std::string getSprite();
	void setSprite(std::string p_sprite);

	std::string getWeaponPositionJson();
	void setWeaponPositionJson(std::string p_json);

	int getWeaponPositionCount();
	sf::Vector2f getWeaponPosition(int p_index);
		
	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	std::string mSprite;
	std::string mWeaponPositionJson;
	std::vector<sf::Vector2f> mWeaponPosition;

	// Methods
	void notifyWeaponPositionJsonChanged();
};

