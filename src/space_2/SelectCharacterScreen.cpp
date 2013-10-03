#include "SelectCharacterScreen.h"
#include "Session.h"
#include "Game.h"

using namespace sf;
using namespace std;


//*************************************************************
// Define
//*************************************************************
#define SELECTSCREEN_FIELDSET_SELECT_WIDTH				1200
#define SELECTSCREEN_FIELDSET_SELECT_HEIGHT				720
#define SELECTSCREEN_FIELDSET_SELECT_BORDSIZE			2
#define SELECTSCREEN_FIELDSET_SELECT_BACKCOLOR			sf::Color(128, 128, 128, 75)
#define SELECTSCREEN_FIELDSET_SELECT_BORDCOLOR			sf::Color(128, 128, 128, 125)
#define SELECTSCREEN_BUTTON_WIDTH						150
#define SELECTSCREEN_BUTTON_HEIGHT						25
#define SELECTSCREEN_BUTTON_BORDERSIZE					2
#define SELECTSCREEN_BUTTONOPTIONS_OFFSETY				55
#define SELECTSCREEN_BUTTONLOGOUT_OFFSETY				10
#define SELECTSCREEN_BUTTONRIGHT_OFFSETX				10
#define SELECTSCREEN_BUTTON_CREATENEW_OFFSETY			20
#define SELECTSCREEN_BUTTON_PLAY_OFFSETY				20
#define SELECTSCREEN_LIST_CHARACTER_PADDING				6
#define SELECTSCREEN_LIST_CHARACTER_WIDTH				CHARACTERVIEW_SELECTSMALL_WIDTH + SCROLLBAR_WIDTH + SELECTSCREEN_LIST_CHARACTER_PADDING * 2
#define SELECTSCREEN_LIST_CHARACTER_BACK_COLOR			sf::Color(0, 0, 0, 0)
#define SELECTSCREEN_LIST_CHARACTER_BORD_COLOR			sf::Color(128, 128, 128, 125)
#define SELECTSCREEN_LIST_CHARACTER_BORD_SIZE			2
#define SELECTSCREEN_LIST_CHARACTER_SEPARATOR_HEIGHT	10
#define SELECTSCREEN_LIST_CHARACTER_SEPARATOR_COLOR		sf::Color(0, 0, 0, 0)
#define SELECTSCREEN_LIST_CHARACTER_HEIGHT				576
#define SELECTSCREEN_LIST_CHARACTER_OFFSETX				25
#define SELECTSCREEN_LIST_CHARACTER_OFFSETY				60
#define SELECTSCREEN_SELECTED_CHARACTER_OFFSETX			25
#define SELECTSCREEN_SELECTED_CHARACTER_OFFSETY			60


//*************************************************************
// Constructor - Destructor
//*************************************************************
SelectCharacterScreen::SelectCharacterScreen(void)
{
	this->mUser = NULL;

	this->mFieldsetSelect.setSize(SELECTSCREEN_FIELDSET_SELECT_WIDTH, SELECTSCREEN_FIELDSET_SELECT_HEIGHT);
	this->mFieldsetSelect.setTitle(Resource::resource->getBundle()->getString("selectScreenTitle"));
	this->mFieldsetSelect.setBackgroundColor(SELECTSCREEN_FIELDSET_SELECT_BACKCOLOR, true);
	this->mFieldsetSelect.setBorderSize(SELECTSCREEN_FIELDSET_SELECT_BORDSIZE, true);
	this->mFieldsetSelect.setBorderColor(SELECTSCREEN_FIELDSET_SELECT_BORDCOLOR, true);
	
	this->mButtonCreateNew.setSize(SELECTSCREEN_BUTTON_WIDTH, SELECTSCREEN_BUTTON_HEIGHT);
	this->mButtonCreateNew.setTitle(Resource::resource->getBundle()->getString("selectScreenButtonCreateNew"));
	this->mButtonCreateNew.setBorderSize(SELECTSCREEN_BUTTON_BORDERSIZE, true);
	
	this->mButtonPlay.setSize(SELECTSCREEN_BUTTON_WIDTH, SELECTSCREEN_BUTTON_HEIGHT);
	this->mButtonPlay.setTitle(Resource::resource->getBundle()->getString("play"));
	this->mButtonPlay.setBorderSize(SELECTSCREEN_BUTTON_BORDERSIZE, true);

	this->mButtonOption.setSize(SELECTSCREEN_BUTTON_WIDTH, SELECTSCREEN_BUTTON_HEIGHT);
	this->mButtonOption.setTitle(Resource::resource->getBundle()->getString("selectScreenButtonOption"));
	this->mButtonOption.setBorderSize(SELECTSCREEN_BUTTON_BORDERSIZE, true);
	
	this->mButtonLogout.setSize(SELECTSCREEN_BUTTON_WIDTH, SELECTSCREEN_BUTTON_HEIGHT);
	this->mButtonLogout.setTitle(Resource::resource->getBundle()->getString("selectScreenButtonLogout"));
	this->mButtonLogout.setBorderSize(SELECTSCREEN_BUTTON_BORDERSIZE, true);
	
	this->mCharactersList.setSize(SELECTSCREEN_LIST_CHARACTER_WIDTH, SELECTSCREEN_LIST_CHARACTER_HEIGHT);
	this->mCharactersList.setSeparatorHeight(SELECTSCREEN_LIST_CHARACTER_SEPARATOR_HEIGHT);
	this->mCharactersList.setSeparatorColor(SELECTSCREEN_LIST_CHARACTER_SEPARATOR_COLOR);
	this->mCharactersList.setBackgroundColor(SELECTSCREEN_LIST_CHARACTER_BACK_COLOR, true);
	this->mCharactersList.setBorderColor(SELECTSCREEN_LIST_CHARACTER_BORD_COLOR, true);
	this->mCharactersList.setBorderSize(SELECTSCREEN_LIST_CHARACTER_BORD_SIZE, true);
	this->mCharactersList.setPadding(SELECTSCREEN_LIST_CHARACTER_PADDING);
	this->mCharactersList.setForceScrollBar(true);

	this->mFieldsetSelect.setView(this->mScreenView);
	this->mCharactersList.setView(this->mScreenView);
	this->mButtonCreateNew.setView(this->mScreenView);
	this->mButtonOption.setView(this->mScreenView);
	this->mButtonLogout.setView(this->mScreenView);
}

SelectCharacterScreen::~SelectCharacterScreen(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
User* SelectCharacterScreen::getUser()
{
	return this->mUser;
}

void SelectCharacterScreen::setUser( User* p_user )
{
	if(this->mUser != p_user)
	{
		this->mUser = p_user;
		this->notifyUserChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void SelectCharacterScreen::launch()
{
	this->mRunning = true;
	this->notifyAppSizeChanged();
	while(Resource::resource->getApp()->isOpen() && Resource::resource->isAppRunning() && this->mRunning)
	{
		// Update
		this->update();

		// Update event
		if(Resource::resource->getApp()->pollEvent(this->mEvent))
		{
			if( this->mEvent.type == Event::Closed)
				Resource::resource->setAppRunning(false);

			if( this->mEvent.type == sf::Event::Resized)
			{
				Resource::resource->resizeAllView();
				this->notifyAppSizeChanged();
			}

			this->update(this->mEvent);
		}

		// Draw
		this->draw();
	}
}

void SelectCharacterScreen::update()
{
	BaseScreen::update();
	this->mCharacterSelectedView.update();
	if(this->mCharactersList.isSelectionChanged() && !this->mCharactersList.isEmpty())
		this->mCharacterSelectedView.setCharacter(((CharacterViewSelectSmall*)this->mCharactersList.getSelection())->getCharacter());

	if(this->mCharacterSelectedView.getCharacter() != NULL && this->mCharacterSelectedView.getCharacter()->getShipPiloted() != NULL)
		this->mButtonPlay.setEnable(true);
	else
		this->mButtonPlay.setEnable(false);
}

void SelectCharacterScreen::updatePosition()
{
	BaseScreen::updatePosition();
	sf::Vector2f windowSize = Resource::resource->getViewUi()->getSize();

	this->mFieldsetSelect.setPosition((windowSize.x - this->mFieldsetSelect.getWidth()) / 2, (windowSize.y - this->mFieldsetSelect.getHeight() - BASESCREEN_OVERLAY_HEIGHT) / 2);
	this->mCharactersList.setPosition(this->mFieldsetSelect.getX() + SELECTSCREEN_LIST_CHARACTER_OFFSETX, this->mFieldsetSelect.getY() + SELECTSCREEN_LIST_CHARACTER_OFFSETY);
	this->mCharacterSelectedView.setPosition(this->mCharactersList.getX() + this->mCharactersList.getWidth() + SELECTSCREEN_SELECTED_CHARACTER_OFFSETX, this->mFieldsetSelect.getY() + SELECTSCREEN_SELECTED_CHARACTER_OFFSETY);
	this->mButtonCreateNew.setPosition(this->mCharactersList.getX() + (this->mCharactersList.getWidth() - this->mButtonCreateNew.getWidth()) / 2, this->mCharactersList.getY() + this->mCharactersList.getHeight() + SELECTSCREEN_BUTTON_CREATENEW_OFFSETY);
	this->mButtonPlay.setPosition(this->mCharacterSelectedView.getX() + (this->mCharacterSelectedView.getWidth() - this->mButtonPlay.getWidth()) / 2, this->mCharacterSelectedView.getBottomY() + SELECTSCREEN_BUTTON_PLAY_OFFSETY);
	this->mButtonOption.setPosition(windowSize.x - this->mButtonOption.getWidth() - SELECTSCREEN_BUTTONRIGHT_OFFSETX, windowSize.y - this->mButtonOption.getHeight() - SELECTSCREEN_BUTTONOPTIONS_OFFSETY);
	this->mButtonLogout.setPosition(windowSize.x - this->mButtonLogout.getWidth() - SELECTSCREEN_BUTTONRIGHT_OFFSETX, windowSize.y - this->mButtonLogout.getHeight() - SELECTSCREEN_BUTTONLOGOUT_OFFSETY);
}

void SelectCharacterScreen::update( sf::Event p_event )
{
	this->mButtonCreateNew.update(p_event);
	this->mButtonPlay.update(p_event);
	this->mButtonOption.update(p_event);
	this->mButtonLogout.update(p_event);
	this->mCharactersList.update(p_event);

	if(this->mButtonOption.isClicked())
		this->launchOption();

	if(this->mButtonLogout.isClicked())
		this->launchLogout();

	if(this->mButtonCreateNew.isClicked())
		this->launchCreateNew();

	if(this->mButtonPlay.isClicked())
		this->launchPlay();
}

void SelectCharacterScreen::draw()
{
	// Draw base
	BaseScreen::draw();

	// Draw fieldsets
	this->mFieldsetSelect.draw();

	// Draw buttons
	this->mButtonCreateNew.draw();
	this->mButtonOption.draw();
	this->mButtonLogout.draw();
	this->mButtonPlay.draw();

	// Draw list
	this->mCharactersList.draw();

	// Draw selected character
	this->mCharacterSelectedView.draw();

	// Display
	Resource::resource->getApp()->display();
}

void SelectCharacterScreen::launchLogout()
{
	Session::setUser(NULL);
	Session::setUserJson(NULL);
	Session::setAuthenticated(false);
	this->setUser(NULL);
	this->mRunning = false;
}

void SelectCharacterScreen::launchOption()
{
	
}

void SelectCharacterScreen::launchCreateNew()
{
	this->hideScreen();

	bool refresh = this->mCreateScreen.launch();
	if(refresh)
		this->notifyUserChanged();

	this->showScreen();
}

void SelectCharacterScreen::launchPlay()
{
	this->hideScreen();

	Session::setSelectedCharacter(this->mCharacterSelectedView.getCharacter());
	Game::game->launch(Session::getSelectedCharacter());

	this->showScreen();
}

void SelectCharacterScreen::notifyUserChanged()
{
	this->mCharactersList.clear(false);
	if(this->mUser != NULL)
	{
		for(int i = 0; i < this->mUser->getCharactersCount(); i++)
			this->mCharactersList.addItem(new CharacterViewSelectSmall(this->mUser->getCharacter(i)));
	}
	this->mCharactersList.notifyDataSetChanged();
}



