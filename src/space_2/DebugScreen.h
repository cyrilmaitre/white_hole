#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include "ProgressBar.h"
#include "Clock.h"
#include "FieldSet.h"
#include "ImageGIFFactory.h"
#include "TextBox.h"
#include "TextBoxMultiLine.h"
#include "TextField.h"
#include "TreeData.h"
#include "NodeData.h"
#include "Tree.h"
#include "DropDownList.h"


class DebugScreen : public BaseScreen
{
public:
	// Constructor - Destructor
	DebugScreen(void);
	~DebugScreen(void);

	// Methods
	void launch();
	void launchBack();
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	Button mButtonBack;
	ProgressBar mProgressBarNone;
	ProgressBar mProgressBarPercent;
	ProgressBar mProgressBarTitle;
	int mProgressBarValue;
	mks::Clock mProgressBarClock;

	FieldSet mFieldset;
	ImageGIF* mGIFLoading;
	Button mButtonLoading;

	TextBox mTextbox;
	TextBox mTextboxAutoResize;

	TextBox mTextBoxFontSize;
	Button mButtonUpFontSize;
	Button mButtonDownFontSize;

	TextBoxMultiLine mTextboxMultiline;
	TextBoxMultiLine mTextboxMultilineAutoResizeHeight;
	TextBoxMultiLine mTextboxMultilineAutoResizeWidth;
	TextBoxMultiLine mTextboxMultilineAutoResizeHeightWidth;

	TextBox mLabelDefaultTextbox;
	TextBox mDefaultTextbox;

	TextBox mLabelDefaultTextfield;
	TextField mDefaultTextfield;

	TextBox mLabelDefaultButton;
	Button mDefaultButton;

	TextBox mLabelDefaultProgressBar;
	ProgressBar mDefaultProgressBar;

	TextBox mFontSizeTiny;
	TextBox mFontSizeSmall;
	TextBox mFontSizeMedium;
	TextBox mFontSizeLarge;
	TextBox mFontSizeHuge;

	TreeData mTree;
	Tree* mTreeView;

	DropDownList mDopDownList;
};

