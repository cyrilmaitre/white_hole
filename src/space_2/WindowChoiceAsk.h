#pragma once
#include "WindowChoice.h"
#include "WindowChoiceActionObject.h"


class WindowChoiceAsk : public WindowChoice
{
public:
	// Constructor - Destructor
	WindowChoiceAsk(std::string p_title, std::string p_message, WindowChoiceAction* p_actions, WindowChoiceActionObject* p_object = NULL, std::string p_actionCommand = "");
	~WindowChoiceAsk(void);
};

