#pragma once
#include "Animation.h"

// Define
#define ANIMATIONMANAGER_MAX	255

class AnimationManager
{
public:
	// Methods
	static void addAnimation(Animation *p_animation);
	static void update();
	static void draw();


private:
	// Constructor - Destructor
	AnimationManager(void);
	~AnimationManager(void);

	// Attributs
	static std::vector<Animation*> mAnimations;

	// Methods
	static void removeAnimation(int p_postion);
};

