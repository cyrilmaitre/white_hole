#pragma once


class Terminable
{
public:
	// Constructor - Destructor
	Terminable(void);
	virtual ~Terminable(void);

	// Methods
	virtual void terminate(bool p_instant);
};

