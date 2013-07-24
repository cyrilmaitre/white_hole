#pragma once

class IdGenerator
{
public:
	// Constructor - Destructor
	IdGenerator(long p_index = 0);
	~IdGenerator(void);

	// Getters - Setters
	long getNextId();

	// Methods
	void reset(long p_index = 0);
	void incIndex(long p_offset);
	void decIndex(long p_offset);


private:
	// Attributs
	long mIndex;
};


