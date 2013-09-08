#pragma once
#include "WindowMessage.h"

class WindowMessageError : public WindowMessage
{
public:
	// Constructor - Destructor
	WindowMessageError(std::string p_title, std::string p_message);
	~WindowMessageError(void);
};

