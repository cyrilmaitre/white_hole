#pragma once
#include "WindowMessage.h"


class WindowMessageSuccess : public WindowMessage
{
public:
	// Constructor - Destructor
	WindowMessageSuccess(std::string p_title, std::string p_message);
	~WindowMessageSuccess(void);
};

