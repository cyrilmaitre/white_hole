#include "Option.h"
#include "Resource.h"
#include "Game.h"
#include "TitleScreen.h"
#include "Jukebox.h"

int main()
{
	Resource mRessource;
	EventManager mEventManager;
	TitleScreen mTitleScreen;
	Game mGame;

	/*
	// Mini game mario debug
	LoadingGameScreen screen;
	screen.launch();
	*/

	mTitleScreen.launch();

	Option::destroyInstance();
	Jukebox::destroyInstance();

	return EXIT_SUCCESS;
}
