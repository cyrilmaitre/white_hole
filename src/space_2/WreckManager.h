#pragma once
#include "Wreck.h"

// Define
#define WRECKMANAGER_COUNT_MAX		50

class WreckManager
{
public:
	// Getters - Setters
	static int getWreckCount();
	static int getWreckCountMax();

	// Methods
	static void add(Wreck* p_wreck);
	static void update();
	static void update(sf::Event p_event);
	static void draw();

private:
	// Constructor - Destructor
	WreckManager(void);
	~WreckManager(void);

	// Getters - Setters
	static bool isFull();

	// Methods
	static void remove(int p_position);
	static void removeFirst();

	// Attributs
	static std::vector<Wreck*> mWrecks;
};

