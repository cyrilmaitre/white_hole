#pragma once
#include "BackgroundGeneration.h"

class BackgroundSpaceManager
{
public:
	// Getters - Setters
	BackgroundSpace* getBackgroundSpaceScreen();
	BackgroundSpace* getBackgroundSpaceSector();
	
	static BackgroundSpaceManager* getInstance();

	// Methods
	void notifyAppSizeChanged();

	static void init();
	static void uninit();


private:
	// Constructor - Destructor
	BackgroundSpaceManager(void);
	~BackgroundSpaceManager(void);

	// Attributs
	BackgroundSpace* mBackgroundSpaceScreen;
	std::vector<BackgroundSpace*> mBackgroundSpaceSectorPool;

	static BackgroundSpaceManager* mInstance;
};

