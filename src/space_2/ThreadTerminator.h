#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include "Terminable.h"

class ThreadTerminator
{
public:
	// Constructor - Destructor
	ThreadTerminator(void);
	~ThreadTerminator(void);

	// Getters - Setters
	bool isRunning();
	void setRunning(bool p_value);

	int getTerminableCount();

	// Methods
	void update();
	void addTerminable(Terminable* p_terminable);


private:
	// Attributs
	sf::Mutex mMutex;
	bool mRunning;
	sf::Thread* mThreadTerminator;
	std::vector<Terminable*> mTerminables;

	// Methods
	Terminable* removeTerminable(int p_index);
};

