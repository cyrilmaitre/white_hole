#pragma once
#include "WindowMessage.h"


class WindowWarning : public WindowMessage
{
public:
	// Constructor - Destructor
	WindowWarning(std::string p_title, std::string p_message);
	~WindowWarning(void);
};

