#include "Option.h"
#include "Resource.h"
#include "Game.h"
#include "TitleScreen.h"

int main()
{
	Option mOption;
	Resource mRessource;
	EventManager mEventManager;
	TitleScreen mTitleScreen;
	Game mGame;

//	LoadingGameScreen screen;
//	screen.launch();

	mTitleScreen.launch();

	return EXIT_SUCCESS;
}
