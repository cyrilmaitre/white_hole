#pragma once
#include "WindowMessage.h"

class WindowError : public WindowMessage
{
public:
	// Constructor - Destructor
	WindowError(std::string p_title, std::string p_message);
	~WindowError(void);
};

