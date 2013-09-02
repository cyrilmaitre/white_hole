#pragma once
#include "KeyValueFile.h"


class DestructableData
{
public:
	// Constructor - Destructor
	DestructableData(void);
	~DestructableData(void);

	// Getters - Setters
	std::string getWreckSprite();
	void setWreckSprite(std::string p_sprite);

	std::string getWreckEmberSprite();
	void setWreckEmberSprite(std::string p_sprite);

	std::string getWreckElecSprite();
	void setWreckElecSprite(std::string p_sprite);

	std::string getShieldSprite();
	void setShieldSprite(std::string p_sprite);

	virtual double getShieldMax();
	void setShieldMax(double p_shieldMax);

	virtual double getShieldRegen();
	void setShieldRegen(double p_shieldRegen);

	virtual double getShieldResist();
	void setShieldResist(double p_shiedlResist);

	virtual double getArmorMax();
	void setArmorMax(double p_armorMax);

	virtual double getArmorRegen();
	void setArmorRegen(double p_armorRegen);

	virtual double getArmorResist();
	void setArmorResist(double p_armorResist);

	virtual double getStructureMax();
	void setStructureMax(double p_structureMax);

	virtual double getStructureRegen();
	void setStructureRegen(double p_strctureRegen);

	virtual double getStructureResist();
	void setStructureResist(double p_structureResist);

	bool isShieldMaxChanged();
	bool isArmorMaxChanged();
	bool isStructureMaxChanged();

	// Methods
	virtual void notifyShieldMaxChanged();
	virtual void notifyArmorMaxChanged();
	virtual void notifyStructureMaxChanged();
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromDestructableData(DestructableData* p_object);


protected:
	// Attributs
	std::string mWreckSprite;
	std::string mWreckEmberSprite;
	std::string mWreckElecSprite;
	std::string mShieldSprite;

	double mShieldMax;
	double mShieldRegen;
	double mShieldResist;
	bool mShieldMaxChanged;

	double mArmorMax;
	double mArmorRegen;
	double mArmorResist;
	bool mArmorMaxChanged;

	double mStructureMax;
	double mStructureRegen;
	double mStructureResist;
	bool mStructureMaxChanged;
};

