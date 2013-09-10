#include "DebugScreen.h"
#include "ImageGIFFactory.h"
#include "Manager.h"

//*************************************************************
// Define
//*************************************************************
#define BUTTON_WIDTH				150
#define BUTTON_HEIGHT				25
#define BUTTON_BORDERSIZE			2
#define BUTTONBACK_OFFSETY			10
#define BUTTONRIGHT_OFFSETX			10
#define PROGRESSBAR_UPDATE_FREQ		100
#define STRING_TEST					"(ABCDEFGH)IJKLMNOPQRSTUVWXYZabcdefgh(ijklmn)opqrstuvwxyz1234567890+-/*?!.:;,%*é`[](){}=@àç"


//*************************************************************
// Constructor - Destructor
//*************************************************************
DebugScreen::DebugScreen(void)
{
	this->mButtonBack.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	this->mButtonBack.setBorderSize(BUTTON_BORDERSIZE, true);
	this->mButtonBack.setTitle(Resource::resource->getBundle()->getString("back"));

	this->mButtonBack.setView(this->mScreenView);

	this->mProgressBarValue = 0;
	this->mProgressBarPercent.setMode(ProgressBar::UiProgressBarMode::ModePercent);
	this->mProgressBarTitle.setMode(ProgressBar::UiProgressBarMode::ModeTitle);
	this->mProgressBarNone.setMode(ProgressBar::UiProgressBarMode::ModeNone);

	this->mFontSizeTiny.setFontColor(sf::Color(255,255,255));
	this->mFontSizeTiny.setFontSize(Manager::getInstance()->getConfig()->getFontSizeTiny());
	this->mFontSizeTiny.setText("Font size: Tiny");

	this->mFontSizeSmall.setFontColor(sf::Color(255,255,255));
	this->mFontSizeSmall.setFontSize(Manager::getInstance()->getConfig()->getFontSizeSmall());
	this->mFontSizeSmall.setText("Font size: Small");
	
	this->mFontSizeMedium.setFontColor(sf::Color(255,255,255));
	this->mFontSizeMedium.setFontSize(Manager::getInstance()->getConfig()->getFontSizeMedium());
	this->mFontSizeMedium.setText("Font size: Medium");

	this->mFontSizeLarge.setFontColor(sf::Color(255,255,255));
	this->mFontSizeLarge.setFontSize(Manager::getInstance()->getConfig()->getFontSizeLarge());
	this->mFontSizeLarge.setText("Font size: Large");

	this->mFontSizeHuge.setFontColor(sf::Color(255,255,255));
	this->mFontSizeHuge.setFontSize(Manager::getInstance()->getConfig()->getFontSizeHuge());
	this->mFontSizeHuge.setText("Font size: Huge");

	this->mTextbox.setAutoResize(false);
	this->mTextbox.setSize(250, 40);
	this->mTextbox.setBackgroundColor(sf::Color(125, 125, 125), true);
	this->mTextbox.setFontColor(sf::Color(255, 255, 255));
	this->mTextbox.setText("This text box doesn't resize herself, that's bad new");

	this->mTextboxAutoResize.setSize(250, 40);
	this->mTextboxAutoResize.setBackgroundColor(sf::Color(125, 125, 125), true);
	this->mTextboxAutoResize.setFontColor(sf::Color(255, 255, 255));
	this->mTextboxAutoResize.setText("This text box resize herself, so the entire text is visible");

	this->mTextBoxFontSize.setBackgroundColor(sf::Color(125, 125, 125), true);
	this->mTextBoxFontSize.setFontColor(sf::Color(255, 255, 255));
	this->mTextBoxFontSize.setText("Font size: " + Tools::buildStringWithInt(this->mTextBoxFontSize.getFontSize()) + " || " + STRING_TEST);
	this->mButtonUpFontSize.setTitle("Inc FontSize");
	this->mButtonDownFontSize.setTitle("Dec FontSize");

	this->mButtonLoading.setTitle("Hide");
	this->mGIFLoading = ImageGIFFactory::getGifLoadingSquareCircle();

	this->mTextboxMultiline.setSize(150, 85);
	this->mTextboxMultiline.setBackgroundColor(sf::Color(125, 125, 125), true);
	this->mTextboxMultiline.setFontColor(sf::Color(255, 255, 255));
	this->mTextboxMultiline.setText("This text box supportt multi-line text.<br/>I can make a new line width br tag like htlm does.<br/>That it, it's simple but work great !<br/>Braw Braw sisi la famille on est la et on rigole zéro... oéoéoéo");

	this->mTextboxMultilineAutoResizeHeight.setSize(250, 80);
	this->mTextboxMultilineAutoResizeHeight.setAutoResizeHeight(true);
	this->mTextboxMultilineAutoResizeHeight.setBackgroundColor(sf::Color(125, 125, 125), true);
	this->mTextboxMultilineAutoResizeHeight.setFontColor(sf::Color(255, 255, 255));
	this->mTextboxMultilineAutoResizeHeight.setText("This text box support multi-line text.<br/>I can make a new line width br tag like htlm does.<br/>That it, it's simple but work great !<br/>Braw Braw sisi la famille on est la et on rigole zéro... oéoéoéo");

	this->mTextboxMultilineAutoResizeWidth.setSize(150, 80);
	this->mTextboxMultilineAutoResizeWidth.setAutoResizeWidth(true);
	this->mTextboxMultilineAutoResizeWidth.setBackgroundColor(sf::Color(125, 125, 125), true);
	this->mTextboxMultilineAutoResizeWidth.setFontColor(sf::Color(255, 255, 255));
	this->mTextboxMultilineAutoResizeWidth.setText("This text box support multi-line text.<br/>I can make a new line width br tag like htlm does.<br/>That it, it's simple but work great !<br/>Braw Braw sisi la famille on est la et on rigole zéro... oéoéoéo");

	this->mTextboxMultilineAutoResizeHeightWidth.setSize(150, 80);
	this->mTextboxMultilineAutoResizeHeightWidth.setAutoResizeWidth(true);
	this->mTextboxMultilineAutoResizeHeightWidth.setAutoResizeHeight(true);
	this->mTextboxMultilineAutoResizeHeightWidth.setBackgroundColor(sf::Color(125, 125, 125), true);
	this->mTextboxMultilineAutoResizeHeightWidth.setFontColor(sf::Color(255, 255, 255));
	this->mTextboxMultilineAutoResizeHeightWidth.setText("This text box support multi-line text.<br/>I can make a new line width br tag like htlm does.<br/>That it, it's simple but work great !<br/>Braw Braw sisi la famille on est la et on rigole zéro... oéoéoéo");

	this->mLabelDefaultTextbox.setText("Default TextBox:");
	this->mLabelDefaultTextbox.setFontSize(ManagerConfig::FontSize::Large);
	this->mLabelDefaultTextbox.setFontColor(sf::Color(255, 106, 0));

	this->mLabelDefaultTextfield.setText("Default TexField:");
	this->mLabelDefaultTextfield.setFontSize(ManagerConfig::FontSize::Large);
	this->mLabelDefaultTextfield.setFontColor(sf::Color(255, 106, 0));

	this->mLabelDefaultTextfield.setText("Default TexField:");
	this->mLabelDefaultTextfield.setFontSize(ManagerConfig::FontSize::Large);
	this->mLabelDefaultTextfield.setFontColor(sf::Color(255, 106, 0));

	this->mLabelDefaultButton.setText("Default Button:");
	this->mLabelDefaultButton.setFontSize(ManagerConfig::FontSize::Large);
	this->mLabelDefaultButton.setFontColor(sf::Color(255, 106, 0));

	this->mLabelDefaultProgressBar.setText("Default ProgressBar:");
	this->mLabelDefaultProgressBar.setFontSize(ManagerConfig::FontSize::Large);
	this->mLabelDefaultProgressBar.setFontColor(sf::Color(255, 106, 0));

	// Tree
	NodeData* root1 = new NodeData();
	NodeData* root1Child1 = new NodeData();
	NodeData* root1Child1Child1 = new NodeData();
	NodeData* root1Child1Child2 = new NodeData();
	NodeData* root1Child1Child3 = new NodeData();
	NodeData* root1Child1Child4 = new NodeData();
	NodeData* root1Child2 = new NodeData();
	NodeData* root1Child3 = new NodeData();
	root1Child1->addChild(root1Child1Child1);
	root1Child1->addChild(root1Child1Child2);
	root1Child1->addChild(root1Child1Child3);
	root1Child1->addChild(root1Child1Child4);
	root1->addChild(root1Child1);
	root1->addChild(root1Child2);
	root1->addChild(root1Child3);

	NodeData* root2 = new NodeData();
	NodeData* root2Child1 = new NodeData();
	NodeData* root2Child2 = new NodeData();
	NodeData* root2Child3 = new NodeData();
	root2->addChild(root2Child1);
	root2->addChild(root2Child2);
	root2->addChild(root2Child3);

	NodeData* root3 = new NodeData();
	NodeData* root4 = new NodeData();
	NodeData* root5 = new NodeData();

	this->mTree.addRoot(root1);
	this->mTree.addRoot(root2);
	this->mTree.addRoot(root3);
	this->mTree.addRoot(root4);
	this->mTree.addRoot(root5);

	this->mTreeView.setSize(200, 400);
	this->mTreeView.setBackgroundColor(sf::Color(255, 255, 255, 0), true);
	this->mTreeView.setBorderColor(sf::Color(200, 200, 200), true);
	this->mTreeView.setBorderSize(2, true);

	this->updatePosition();
}

DebugScreen::~DebugScreen(void)
{
	this->mTree.destroyRoots();
}


//*************************************************************
// Methods
//*************************************************************
void DebugScreen::launch()
{
	this->update();
	while(Resource::resource->getApp()->isOpen() && Resource::resource->isAppRunning() && this->mRunning)
	{		
		// Event
		this->update();
		if(Resource::resource->getApp()->pollEvent(this->mEvent))
		{
			if( this->mEvent.type == sf::Event::Closed)
				Resource::resource->setAppRunning(false);

			if( this->mEvent.type == sf::Event::Resized)
			{
				Resource::resource->resizeAllView();
				this->notifyAppSizeChanged();
			}

			this->update(this->mEvent);
		}

		// Action
		if(this->mButtonBack.isClicked())
			this->launchBack();

		if(this->mButtonLoading.isClicked())
		{
			this->mGIFLoading->setVisible(!this->mGIFLoading->isVisible());
			if(this->mGIFLoading->isVisible())
				this->mButtonLoading.setTitle("Hide");
			else
				this->mButtonLoading.setTitle("Show");
		}

		if(this->mButtonUpFontSize.isClicked())
		{
			this->mTextBoxFontSize.setFontSize(this->mTextBoxFontSize.getFontSize() + 1);
			this->mTextBoxFontSize.setText("Font size: " + Tools::buildStringWithInt(this->mTextBoxFontSize.getFontSize()) + " || " + STRING_TEST);
		}

		if(this->mButtonDownFontSize.isClicked())
		{
			this->mTextBoxFontSize.setFontSize(this->mTextBoxFontSize.getFontSize() - 1);
			this->mTextBoxFontSize.setText("Font size: " + Tools::buildStringWithInt(this->mTextBoxFontSize.getFontSize()) + " || " + STRING_TEST);
		}

		// Draw
		this->draw();
	}
}

void DebugScreen::update()
{
	BaseScreen::update();

	this->mGIFLoading->update();

	if(this->mProgressBarClock.getElapsedTimeAsMilliseconds() > PROGRESSBAR_UPDATE_FREQ)
	{
		this->mProgressBarValue++;
		if(this->mProgressBarValue > 100)
			this->mProgressBarValue = 0;

		this->mProgressBarNone.setValue(this->mProgressBarValue);
		this->mDefaultProgressBar.setValue(this->mProgressBarValue);
		this->mProgressBarPercent.setValue(this->mProgressBarValue);
		this->mProgressBarTitle.setValue(this->mProgressBarValue);
		this->mProgressBarClock.restart();
	}
}

void DebugScreen::update( sf::Event p_event )
{
	this->mButtonBack.update(p_event);
	this->mButtonLoading.update(p_event);
	this->mButtonDownFontSize.update(p_event);
	this->mButtonUpFontSize.update(p_event);

	this->mDefaultTextfield.update(p_event);
	this->mDefaultButton.update(p_event);

	this->mTextboxMultiline.update(p_event);
	this->mTextboxMultilineAutoResizeHeight.update(p_event);

	this->mTreeView.update(p_event);
}

void DebugScreen::updatePosition()
{
	BaseScreen::updatePosition();

	this->mButtonBack.setX((int)Resource::resource->getViewUi()->getSize().x - this->mButtonBack.getWidth() - BUTTONRIGHT_OFFSETX);
	this->mButtonBack.setY((int)Resource::resource->getViewUi()->getSize().y - this->mButtonBack.getHeight() - BUTTONBACK_OFFSETY);

	this->mProgressBarNone.setPosition(10, 10);
	this->mProgressBarPercent.setPosition(this->mProgressBarNone.getX(), this->mProgressBarNone.getY() + this->mProgressBarNone.getHeight() + 15);
	this->mProgressBarTitle.setPosition(this->mProgressBarPercent.getX(), this->mProgressBarPercent.getY() + this->mProgressBarPercent.getHeight() + 15);

	this->mButtonLoading.setPosition(this->mProgressBarNone.getRightX() + 25, 20 + this->mGIFLoading->getHeight());
	this->mGIFLoading->setPosition(this->mButtonLoading.getCenterX() - this->mGIFLoading->getWidth() / 2, 10);
	this->mFieldset.setPosition(10, this->mProgressBarTitle.getY() + this->mProgressBarTitle.getHeight() + 25);

	this->mFontSizeTiny.setPosition(this->mFieldset.getRightX() + 25, this->mFieldset.getY());
	this->mFontSizeSmall.setPosition(this->mFontSizeTiny.getX(), this->mFontSizeTiny.getBottomY() + 10);
	this->mFontSizeMedium.setPosition(this->mFontSizeTiny.getX(), this->mFontSizeSmall.getBottomY() + 10);
	this->mFontSizeLarge.setPosition(this->mFontSizeTiny.getX(), this->mFontSizeMedium.getBottomY() + 10);
	this->mFontSizeHuge.setPosition(this->mFontSizeTiny.getX(), this->mFontSizeLarge.getBottomY() + 10);

	this->mTreeView.setPosition(this->mFontSizeHuge.getRightX() + 50, 10);

	this->mTextboxAutoResize.setPosition(10, this->mFieldset.getBottomY() + 25);
	this->mTextbox.setPosition(10, this->mTextboxAutoResize.getBottomY() + 10);

	this->mTextboxMultiline.setPosition(10, this->mTextbox.getBottomY() + 25);
	this->mTextboxMultilineAutoResizeHeight.setPosition(this->mTextboxMultiline.getRightX() + 10, this->mTextboxMultiline.getY());
	this->mTextboxMultilineAutoResizeWidth.setPosition(this->mTextboxMultilineAutoResizeHeight.getRightX() + 10, this->mTextboxMultiline.getY());
	this->mTextboxMultilineAutoResizeHeightWidth.setPosition(this->mTextboxMultilineAutoResizeWidth.getRightX() + 10, this->mTextboxMultiline.getY());

	this->mButtonDownFontSize.setPosition(10, this->mTextboxMultilineAutoResizeHeight.getBottomY() + 25);
	this->mButtonUpFontSize.setPosition(this->mButtonDownFontSize.getRightX() + 10, this->mButtonDownFontSize.getY());
	this->mTextBoxFontSize.setPosition(this->mButtonDownFontSize.getX(), this->mButtonDownFontSize.getBottomY() + 10);

	this->mLabelDefaultTextbox.setPosition(this->mFieldset.getContentX(), this->mFieldset.getContentY());
	this->mDefaultTextbox.setPosition(this->mLabelDefaultTextbox.getX(), this->mLabelDefaultTextbox.getBottomY() + 10);

	this->mLabelDefaultTextfield.setPosition(this->mLabelDefaultTextbox.getRightX() + 100, this->mLabelDefaultTextbox.getY());
	this->mDefaultTextfield.setPosition(this->mLabelDefaultTextfield.getX(), this->mLabelDefaultTextfield.getBottomY() + 10);

	this->mLabelDefaultButton.setPosition(this->mLabelDefaultTextbox.getX(), this->mDefaultTextfield.getBottomY() + 25);
	this->mDefaultButton.setPosition(this->mLabelDefaultButton.getX(), this->mLabelDefaultButton.getBottomY() + 10);

	this->mLabelDefaultProgressBar.setPosition(this->mLabelDefaultTextfield.getX(), this->mLabelDefaultButton.getY());
	this->mDefaultProgressBar.setPosition(this->mLabelDefaultProgressBar.getX(), this->mLabelDefaultProgressBar.getBottomY() + 10);
}

void DebugScreen::draw()
{
	BaseScreen::draw();

	this->mButtonBack.draw();
	this->mProgressBarNone.draw();
	this->mProgressBarPercent.draw();
	this->mProgressBarTitle.draw();

	this->mButtonLoading.draw();
	this->mGIFLoading->draw();
	this->mFieldset.draw();

	this->mFontSizeTiny.draw();
	this->mFontSizeSmall.draw();
	this->mFontSizeMedium.draw();
	this->mFontSizeLarge.draw();
	this->mFontSizeHuge.draw();

	this->mButtonDownFontSize.draw();
	this->mButtonUpFontSize.draw();
	this->mTextBoxFontSize.draw();

	this->mTextboxAutoResize.draw();
	this->mTextbox.draw();

	this->mTextboxMultiline.draw();
	this->mTextboxMultilineAutoResizeHeight.draw();
	this->mTextboxMultilineAutoResizeWidth.draw();
	this->mTextboxMultilineAutoResizeHeightWidth.draw();

	this->mLabelDefaultTextbox.draw();
	this->mDefaultTextbox.draw();

	this->mLabelDefaultTextfield.draw();
	this->mDefaultTextfield.draw();

	this->mLabelDefaultButton.draw();
	this->mDefaultButton.draw();

	this->mLabelDefaultProgressBar.draw();
	this->mDefaultProgressBar.draw();

	this->mTreeView.draw();

	Resource::resource->getApp()->display();
}

void DebugScreen::launchBack()
{
	this->mRunning = false;
}

