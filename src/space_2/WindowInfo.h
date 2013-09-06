#pragma once
#include "WindowMessage.h"


class WindowInfo : public WindowMessage
{
public:
	// Constructor - Destructor
	WindowInfo(std::string p_title, std::string p_message);
	~WindowInfo(void);
};

