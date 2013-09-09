#pragma once
#include "WindowChoice.h"


class WindowChoiceAsk : public WindowChoice
{
public:
	// Constructor - Destructor
	WindowChoiceAsk(std::string p_title, std::string p_message, WindowChoiceAction* p_actions, std::string p_actionCommand = "");
	~WindowChoiceAsk(void);
};

