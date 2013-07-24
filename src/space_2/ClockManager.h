#pragma once
#include <SFML/Graphics.hpp>

class ClockManager
{
public:
	// Getters - Setters
	static float getElapsedTimeAsSeconds();
	static long getElapsedTimeAsMilliseconds();
	static int getIteration();

	// Methods
	static void update();


private:
	// Constructor - Destructor
	ClockManager(void);
	~ClockManager(void);

	// Attributs
	static sf::Clock mClock;
	static float mElapsedTimeAsSeconds;
	static long mElapsedTimeAsMilliseconds;
	static long mIteration;
};


