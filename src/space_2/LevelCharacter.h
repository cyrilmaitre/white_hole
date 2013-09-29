#pragma once
#include "Level.h"


class LevelCharacter : public Level
{
public:
	// Constructor - Destructor
	LevelCharacter(KeyValueFile* p_config);
	~LevelCharacter(void);
};

