#pragma once
#include "WindowMessage.h"


class WindowMessageInfo : public WindowMessage
{
public:
	// Constructor - Destructor
	WindowMessageInfo(std::string p_title, std::string p_message);
	~WindowMessageInfo(void);
};

