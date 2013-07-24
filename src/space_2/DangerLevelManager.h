#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "DangerLevel.h"

class DangerLevelManager
{
public:
	// Constructor - Destructor
	DangerLevelManager(KeyValueFile *p_config);
	~DangerLevelManager(void);

	// Getters - Setters
	int getLevelMin();
	void setLevelMin(int p_min);

	int getLevelMed();

	int getLevelMax();
	void setLevelMax(int p_max);

	int getLevelCount();
	void setLevelCount(int p_count);

	float getLevelUpChanceMin();
	void setLevelUpChanceMin(float p_min);

	float getLevelUpChanceMax();
	void setLevelUpChanceMax(float p_max);

	// Methods
	DangerLevel* generateDangerLevel(int p_dangerLevelCount, int p_dangerLevelSum);

	// Static
	static DangerLevelManager *getInstance();
	static void init();
	static void uninit();


private:
	// Attributs
	int mLevelMin;
	int mLevelMax;
	int mLevelCount;
	float mLevelUpChanceMin;
	float mLevelUpChanceMax;

	// Static
	static DangerLevelManager *mInstance;
};

