#pragma once
#include "Auto.h"

// Define
#define AUTOMANAGER_MAX		512

class AutoManager
{
public:
	// Getters - Setters
	static int getAutoCount();
	static int getAutoCountMax();

	// Methods
	static Auto* add(Auto* p_impact);
	static void update();
	static void draw();


private:
	// Constructor - Destructor
	AutoManager(void);
	~AutoManager(void);

	// Methods
	static void remove(int p_position);

	// Attributs
	static std::vector<Auto*> mAutos;
};

