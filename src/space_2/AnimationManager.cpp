#include "AnimationManager.h"


//******************************
// Init static
//******************************
std::vector<Animation*> AnimationManager::mAnimations;


//******************************
// Constructor - Destructor
//******************************
AnimationManager::AnimationManager(void)
{
}

AnimationManager::~AnimationManager(void)
{
}


//******************************
// Methods
//******************************
void AnimationManager::addAnimation( Animation *p_animation )
{
	if(AnimationManager::mAnimations.size() < ANIMATIONMANAGER_MAX)
		AnimationManager::mAnimations.push_back(p_animation);
	else
		delete p_animation;
}

void AnimationManager::removeAnimation( int p_position )
{
	delete AnimationManager::mAnimations[p_position];
	AnimationManager::mAnimations.erase(AnimationManager::mAnimations.begin() + p_position);
}

void AnimationManager::update()
{
	for(int i = 0; i < AnimationManager::mAnimations.size(); i++)
	{
		AnimationManager::mAnimations[i]->update();

		if(AnimationManager::mAnimations[i]->isFinished())
			AnimationManager::removeAnimation(i);
	}
}

void AnimationManager::draw()
{
	for(int i = 0; i < AnimationManager::mAnimations.size(); i++)
	{
		AnimationManager::mAnimations[i]->draw();
	}
}
