#pragma once
#include "WindowPopup.h"
#include "Button.h"
#include "WindowChoiceAction.h"
#include "WindowChoiceActionObject.h"


class WindowChoice : public WindowPopup
{
public:
	// Constructor - Destructor
	WindowChoice(	std::string p_title, std::string p_message, SpriteParameter* p_spriteSheet, std::string p_spriteIndex, std::string p_windowIconIdex, 
					std::string p_buttonTrueTitle, std::string p_buttonFalseTitle, WindowChoiceAction* p_actions, WindowChoiceActionObject* p_actionObject = NULL, std::string p_actionCommand = "");
	~WindowChoice(void);
	void deleteAction();

	// Getters - Setters
	void setButtonTrueTitle(std::string p_title);
	void setButtonFalseTitle(std::string p_title);

	bool hasAction();
	WindowChoiceAction* getAction();
	void setAction(WindowChoiceAction* p_action);

	WindowChoiceActionObject* getActionObject();
	void setActionObject(WindowChoiceActionObject* p_object);

	std::string getActionCommand();
	void setActionCommand(std::string p_command);

	// Methods
	void notifyPositionChanged();
	void notifySizeChanged();
	void updateMessageTextBox();
	void updatePosition();
	void update(sf::Event p_event);
	void drawContent();


private:
	// Attributs
	Button mButtonTrue;
	Button mButtonFalse;
	WindowChoiceAction* mAction;
	WindowChoiceActionObject* mActionObject;
	std::string mActionCommand;
};

