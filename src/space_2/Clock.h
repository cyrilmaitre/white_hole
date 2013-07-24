#pragma once

namespace mks
{
	class Clock
	{
	public:
		// Constructor - Destructor
		Clock(void);
		~Clock(void);

		// Getters - Setters
		float getElapsedTimeAsSeconds();
		long getElapsedTimeAsMilliseconds();

		// Methods
		void restart();


	private:
		// Attributs
		float mTimeStartAsSeconds;
		float mElapsedTimeAsSeconds;
		long mTimeStartAsMilliseconds;
		long mElapsedTimeAsMilliseconds;
		long mLastIterationSeconds;
		long mLastIterationMilliseconds;
	};
}

