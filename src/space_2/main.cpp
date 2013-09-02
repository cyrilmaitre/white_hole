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

	// Launch Game
	while(mRessource.isAppRunning())
	{
		mTitleScreen.launch();
	}

	Resource::resource->getChatClient()->terminate(); // disconnect chat

	return EXIT_SUCCESS;
}
