#pragma once
#include "WindowMessage.h"


class WindowMessageWarning : public WindowMessage
{
public:
	// Constructor - Destructor
	WindowMessageWarning(std::string p_title, std::string p_message);
	~WindowMessageWarning(void);
};

