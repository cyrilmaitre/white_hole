#pragma once
#include "FieldSet.h"
#include "TextBox.h"
#include "PopupDropDown.h"
#include "DropDownable.h"


class DropDownList : public FieldSet
{
public:
	// Constrcutor - Destructor
	DropDownList(void);
	~DropDownList(void);

	// Methods
	void addDropDownable(DropDownable* p_dropDownable);
	void removeDropDownable(DropDownable* p_dropDownable);
	void removeAllDropDownable();
	DropDownable* getSelectedDropDownable();

	void updatePosition();
	void update();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyDropDownableChanged();


private:
	// Attributs
	TextBox mText;
	sf::Sprite* mIconDrop;
	PopupDropDown mDropDown;
};

