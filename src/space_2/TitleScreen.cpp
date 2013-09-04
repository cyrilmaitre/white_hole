#include "TitleScreen.h"
#include "Resource.h"
#include "BackgroundGeneration.h"
#include "Option.h"
#include "Game.h"
#include "ShipFactory.h"
#include "Session.h"
#include "Network.h"
#include "ImageGIFFactory.h"
#include "NetworkDefine.h"

using namespace sf;
using namespace std;

//*************************************************************
// Define
//*************************************************************
#define TITLESCREEN_BUTTON_WIDTH				150
#define TITLESCREEN_BUTTON_HEIGHT				25
#define TITLESCREEN_BUTTON_BORDERSIZE			2
#define TITLESCREEN_TF_WIDTH					200
#define TITLESCREEN_TF_HEIGHT					20
#define TITLESCREEN_TF_BORDERSIZE				2
#define TITLESCREEN_TFUSERNAME_OFFSET_Y			110
#define TITLESCREEN_TFPASSWORD_OFFSET_Y			75
#define TITLESCREEN_BUTTONLOGIN_OFFSETY			20
#define TITLESCREEN_BUTTONDEBUG_OFFSETY			100
#define TITLESCREEN_BUTTONOPTIONS_OFFSETY		55
#define TITLESCREEN_BUTTONQUIT_OFFSETY			10
#define TITLESCREEN_BUTTONRIGHT_OFFSETX			10
#define TITLESCREEN_GIF_LOADING_OFFSETX			20
#define GAME_TITLE_FONTSIZE						50
#define GAME_TITLE_COLOR						sf::Color(255, 255, 255)
#define GAME_TITLE_WELCOME_FONTSIZE				25
#define GAME_TITLE_WELCOME_COLOR				sf::Color(255, 255, 255)
#define GAME_TITLE_WELCOME_OFFSETY				10


//*************************************************************
// Constructor - Destructor
//*************************************************************
TitleScreen::TitleScreen(void)
{
	// Init with default
	this->mGIFLoading			= NULL;
	this->mAuthenticateThread	= NULL;
	this->mSelectScreen			= NULL;

	this->mGIFLoading = ImageGIFFactory::getGifLoadingSquareCircle();
	this->mGIFLoading->setVisible(false);

	this->mTextBoxLoginFailed.setFontColor(sf::Color(255, 64, 64));
	this->mTextBoxLoginFailed.setVisible(false);
	this->mTextBoxLoginFailed.setText(Resource::resource->getBundle()->getString("titleScreenTBLoginFailed"));

	this->mGameTitle.setFont(Resource::resource->getFontUiTheme());
	this->mGameTitle.setFontColor(GAME_TITLE_COLOR);
	this->mGameTitle.setFontSize(GAME_TITLE_FONTSIZE);
	this->mGameTitle.setText(APP_GAME_NAME);

	this->mGameTitleWelcome.setFont(Resource::resource->getFontUiTheme());
	this->mGameTitleWelcome.setFontColor(GAME_TITLE_WELCOME_COLOR);
	this->mGameTitleWelcome.setFontSize(GAME_TITLE_WELCOME_FONTSIZE);
	this->mGameTitleWelcome.setText(Resource::resource->getBundle()->getString("welcome"));
	
	this->mButtonLogin.setSize(TITLESCREEN_BUTTON_WIDTH, TITLESCREEN_BUTTON_HEIGHT);
	this->mButtonLogin.setBorderSize(TITLESCREEN_BUTTON_BORDERSIZE, true);
	this->mButtonLogin.setTitle(Resource::resource->getBundle()->getString("titleScreenButtonLogin"));

	this->mButtonOption.setSize(TITLESCREEN_BUTTON_WIDTH, TITLESCREEN_BUTTON_HEIGHT);
	this->mButtonOption.setBorderSize(TITLESCREEN_BUTTON_BORDERSIZE, true);
	this->mButtonOption.setTitle(Resource::resource->getBundle()->getString("titleScreenButtonOption"));

	this->mButtonQuit.setSize(TITLESCREEN_BUTTON_WIDTH, TITLESCREEN_BUTTON_HEIGHT);
	this->mButtonQuit.setBorderSize(TITLESCREEN_BUTTON_BORDERSIZE, true);
	this->mButtonQuit.setTitle(Resource::resource->getBundle()->getString("titleScreenButtonQuit"));

	this->mButtonDebug.setSize(TITLESCREEN_BUTTON_WIDTH, TITLESCREEN_BUTTON_HEIGHT);
	this->mButtonDebug.setBorderSize(TITLESCREEN_BUTTON_BORDERSIZE, true);
	this->mButtonDebug.setTitle(Resource::resource->getBundle()->getString("titleScreenButtonDebug"));

	this->mTextFieldUsername.setSize(TITLESCREEN_TF_WIDTH, TITLESCREEN_TF_HEIGHT);
	this->mTextFieldUsername.setTitleFontColor(sf::Color(255, 255, 255));
	this->mTextFieldUsername.setType(TextField::TextFieldType::TypeText);
	this->mTextFieldUsername.setTitle(Resource::resource->getBundle()->getString("titleScreenTFUsername"));
	this->mTextFieldUsername.setTitleVisibility(true);

	this->mTextFieldPassword.setSize(TITLESCREEN_TF_WIDTH, TITLESCREEN_TF_HEIGHT);
	this->mTextFieldPassword.setTitleFontColor(sf::Color(255, 255, 255));	
	this->mTextFieldPassword.setType(TextField::TextFieldType::TypePassword);
	this->mTextFieldPassword.setTitle(Resource::resource->getBundle()->getString("titleScreenTFPassword"));
	this->mTextFieldPassword.setTitleVisibility(true);

	this->mButtonLogin.setView(this->mScreenView);
	this->mButtonOption.setView(this->mScreenView);
	this->mButtonQuit.setView(this->mScreenView);
	this->mGameTitle.setView(this->mScreenView);
	this->mTextFieldUsername.setView(this->mScreenView);
	this->mTextFieldPassword.setView(this->mScreenView);
	this->mGIFLoading->setView(this->mScreenView);
	this->mTextBoxLoginFailed.setView(this->mScreenView);

	this->updatePosition();

	// Debug
	this->mTextFieldUsername.setValue("watwat");
	this->mTextFieldPassword.setValue("watwat");
}

TitleScreen::~TitleScreen(void)
{
	if(this->mGIFLoading != NULL)
		delete this->mGIFLoading;

	if(this->mSelectScreen != NULL)
		delete this->mSelectScreen;
}


//*************************************************************
// Methode
//*************************************************************
void TitleScreen::launch()
{
	this->update();
	while(Resource::resource->getApp()->isOpen() && Resource::resource->isAppRunning() && this->mRunning)
	{		
		// Event
		this->update();
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
			
		// Action
		if(this->mButtonQuit.isClicked())
			this->launchQuit();

		if(this->mButtonDebug.isClicked())
			this->launchDebugScreen();

		if(this->mButtonOption.isClicked())
			this->launchOption();

		if(this->mButtonLogin.isClicked())
			this->launchLogin();

		if(Session::isAuthenticated())
			this->launchSelectScreen();

		// Draw
		this->draw();
	}
}

void TitleScreen::update()
{
	BaseScreen::update();
	this->mGIFLoading->update();
}

void TitleScreen::updatePosition()
{
	BaseScreen::updatePosition();

	// Update Button
	this->mTextFieldUsername.setX((int)Resource::resource->getViewUi()->getSize().x / 2 - this->mTextFieldUsername.getWidth() / 2);
	this->mTextFieldUsername.setY((int)Resource::resource->getViewUi()->getSize().y - this->mTextFieldUsername.getHeight() - TITLESCREEN_TFUSERNAME_OFFSET_Y);

	this->mTextFieldPassword.setX((int)Resource::resource->getViewUi()->getSize().x / 2 - this->mTextFieldPassword.getWidth() / 2);
	this->mTextFieldPassword.setY((int)Resource::resource->getViewUi()->getSize().y - this->mTextFieldPassword.getHeight() - TITLESCREEN_TFPASSWORD_OFFSET_Y);

	this->mButtonLogin.setX((int)Resource::resource->getViewUi()->getSize().x / 2 - this->mButtonLogin.getWidth() / 2);
	this->mButtonLogin.setY((int)Resource::resource->getViewUi()->getSize().y - this->mButtonLogin.getHeight() - TITLESCREEN_BUTTONLOGIN_OFFSETY);

	this->mButtonDebug.setX((int)Resource::resource->getViewUi()->getSize().x - this->mButtonOption.getWidth() - TITLESCREEN_BUTTONRIGHT_OFFSETX);
	this->mButtonDebug.setY((int)Resource::resource->getViewUi()->getSize().y - this->mButtonOption.getHeight() - TITLESCREEN_BUTTONDEBUG_OFFSETY);

	this->mButtonOption.setX((int)Resource::resource->getViewUi()->getSize().x - this->mButtonOption.getWidth() - TITLESCREEN_BUTTONRIGHT_OFFSETX);
	this->mButtonOption.setY((int)Resource::resource->getViewUi()->getSize().y - this->mButtonOption.getHeight() - TITLESCREEN_BUTTONOPTIONS_OFFSETY);

	this->mButtonQuit.setX((int)Resource::resource->getViewUi()->getSize().x - this->mButtonQuit.getWidth() - TITLESCREEN_BUTTONRIGHT_OFFSETX);
	this->mButtonQuit.setY((int)Resource::resource->getViewUi()->getSize().y - this->mButtonQuit.getHeight() - TITLESCREEN_BUTTONQUIT_OFFSETY);

	// Other
	this->mGIFLoading->setX(this->mButtonLogin.getX() + this->mButtonLogin.getWidth() + TITLESCREEN_GIF_LOADING_OFFSETX);
	this->mGIFLoading->setY(this->mButtonLogin.getY() - (15 - (this->mButtonLogin.getHeight() / 2)));
	this->mTextBoxLoginFailed.setX(this->mButtonLogin.getX() + this->mButtonLogin.getWidth() + TITLESCREEN_GIF_LOADING_OFFSETX);
	this->mTextBoxLoginFailed.setY(this->mButtonLogin.getY() - ((this->mTextBoxLoginFailed.getHeight() / 2) - (this->mButtonLogin.getHeight() / 2)));

	// Update Game Title
	this->mGameTitle.setX((int)Resource::resource->getViewUi()->getSize().x / 2 - this->mGameTitle.getWidth() / 2);
	this->mGameTitle.setY((int)((Resource::resource->getViewUi()->getSize().y / 2) - (this->mGameTitle.getHeight() / 2) - (BASESCREEN_OVERLAY_HEIGHT / 2)));

	this->mGameTitleWelcome.setX((int)Resource::resource->getViewUi()->getSize().x / 2 - this->mGameTitleWelcome.getWidth() / 2);
	this->mGameTitleWelcome.setY(this->mGameTitle.getY() - this->mGameTitleWelcome.getHeight() - GAME_TITLE_WELCOME_OFFSETY);
}

void TitleScreen::update( sf::Event p_event )
{
	this->mTextFieldUsername.update(p_event);
	this->mTextFieldPassword.update(p_event);
	this->mButtonLogin.update(p_event);
	this->mButtonDebug.update(p_event);
	this->mButtonOption.update(p_event);
	this->mButtonQuit.update(p_event);
}

void TitleScreen::draw()
{
	// Draw base
	BaseScreen::draw();

	// Draw Title
	this->mGameTitle.draw();
	this->mGameTitleWelcome.draw();

	// Draw Ui
	this->mTextFieldUsername.draw();
	this->mTextFieldPassword.draw();	
	this->mButtonLogin.draw();
	this->mButtonDebug.draw();
	this->mButtonOption.draw();
	this->mButtonQuit.draw();
	this->mGIFLoading->draw();
	this->mTextBoxLoginFailed.draw();

	Resource::resource->getApp()->display();
}

void TitleScreen::authenticateRequest()
{
	this->mGIFLoading->setVisible(true);
	this->mTextBoxLoginFailed.setVisible(false);

	// Create request body
	Json::Value jsonRequest;
	jsonRequest["username"] = this->mTextFieldUsername.getValue();
	jsonRequest["password"] = Tools::sha1(this->mTextFieldPassword.getValue());

	// Request
	Json::StyledWriter writer;
	sf::Http::Response response = Network::sendJsonRequest(sf::Http::Request::Post, NETWORK_HTTP_URI_LOGIN, writer.write(jsonRequest));
	Json::Value* jsonResponse = new Json::Value();   
	Json::Reader reader;
	bool parsingSuccessfull = reader.parse(response.getBody(), *jsonResponse);
	if(parsingSuccessfull)
	{
		if(jsonResponse->get("authenticated", "false").asString() == "true")
		{
			Session::setAuthenticated(true);
			Session::setUserJson(jsonResponse);

			//klm
			Resource::resource->getChatClient()->connect(this->mTextFieldUsername.getValue(), Tools::sha1(this->mTextFieldPassword.getValue())); //chat connect
		}
		else
		{
			this->mTextBoxLoginFailed.setVisible(true);
		}
	}
	else
	{
		this->mTextBoxLoginFailed.setVisible(true);
	}
	this->mGIFLoading->setVisible(false);
}

void TitleScreen::launchSelectScreen()
{
	this->hideScreen();

	Session::setUser(new User(Session::getUserJson()->get("user", NULL)));
	this->mSelectScreen = new SelectCharacterScreen();
	this->mSelectScreen->launch();
	delete this->mSelectScreen;
	this->mSelectScreen = NULL;
	
	this->showScreen();
}

void TitleScreen::launchDebugScreen()
{
	this->hideScreen();

	this->mDebugScreen = new DebugScreen();
	this->mDebugScreen->launch();
	delete this->mDebugScreen;
	this->mDebugScreen = NULL;

	this->showScreen();
}

void TitleScreen::launchLogin()
{
	if(this->mAuthenticateThread != NULL)
	{
		delete this->mAuthenticateThread;
		this->mAuthenticateThread = NULL;
	}

	this->mAuthenticateThread = new sf::Thread(&TitleScreen::authenticateRequest, this);
	this->mAuthenticateThread->launch();
}

void TitleScreen::launchOption()
{

}

void TitleScreen::launchQuit()
{
	Resource::resource->setAppRunning(false);
	this->mRunning = false;
}

void TitleScreen::showScreen()
{
	BaseScreen::showScreen();
	this->mGIFLoading->setVisible(false);
	this->mTextBoxLoginFailed.setVisible(false);
}
