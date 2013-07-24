#pragma once
#include "Resource.h"
#include "Clock.h"

// Define
#define RUNNINGSTATS_UPDATE_FREQUENCY		500
#define RUNNINGSTATS_BACKGROUND_COLOR		sf::Color(0, 0, 0, 200)
#define RUNNINGSTATS_BACKGROUND_HEIGHT		300
#define RUNNINGSTATS_BACKGROUND_POSITION	sf::Vector2f(0, 0)
#define RUNNINGSTATS_BACKGROUND_PADDING		10
#define RUNNINGSTATS_LINE_OFFSET			25
#define RUNNINGSTATS_COLUMN_OFFSET			300
#define RUNNINGSTATS_VELOCITY_OFFSET		80

class RunningStats
{
public:
	// Getters - Setters
	static bool isShow();
	static void setShow(bool p_isShow);

	static sf::Vector2f getTextPosition(int line, int column);

	static float getFrameRate();
	static SIZE_T getMemoryUsage();
	static double getCpuUsage();

	// Methods
	static void init();
	static void update();
	static void update(sf::Event p_event);
	static void draw();


protected:
	// Constructor - Destructor
	RunningStats(void);
	~RunningStats(void);


private:
	// Attributs
	static bool mShow;
	static float mFrameRate;
	static int mFrameCount;
	static mks::Clock mFrameRateClock;
	static mks::Clock mRunningStatsClock;

	static double mCPUUsage;
	static ULARGE_INTEGER mLastCPU;
	static ULARGE_INTEGER mLastSysCPU;
	static ULARGE_INTEGER mLastUserCPU;
	static int mNumProcessors;
	static HANDLE mSelf;
};

