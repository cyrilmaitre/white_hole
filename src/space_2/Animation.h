#pragma once
#include "Resource.h"
#include "ImageGIF.h"
#include "MapObject.h"
#include "Clock.h"

// Define
#define ANIMATION_DURATION_INFINITE				-1
#define ANIMATION_ROTATION_DIRECTION_RIGHT		true
#define ANIMATION_ROTATION_DIRECTION_LEFT		false

class Animation
{
public:
	// Constructor - Destructor
	Animation(sf::Texture* p_texture, long p_spriteDuration = ANIMATION_DURATION_INFINITE, int p_x = 0, int p_y = 0);
	Animation(sf::Sprite p_sprite, long p_spriteDuration = ANIMATION_DURATION_INFINITE, int p_x = 0, int p_y = 0);
	Animation(ImageGIF* p_spriteGif, int p_spriteGifLoop = ANIMATION_DURATION_INFINITE, int p_x = 0, int p_y = 0);
	void init();
	~Animation(void);

	// Getters - Setters
	int getAnimationX();
	int getAnimationY();
	void setAnimationX(int p_x);
	void setAnimationY(int p_y);

	long getAnimationDuration();
	long getRotationDuration();
	long getScaleDuration();
	long getTranslationDuration();

	Object* getRelatedObject();
	void setRelatedObject(Object* p_object);

	MapObject* getRelatedObjectMap();
	void setRelatedObjectMap(MapObject* p_objectMap);

	int getRelatedObjectOffsetX();
	void setRelatedObjectOffsetX(int p_x);

	int getRelatedObjectOffsetY();
	void setRelatedObjectOffsetY(int p_y);

	bool isFinished();
	bool isSpriteFinished();
	bool isRotationFinished();
	bool isScaleFinished();
	bool isTranslationFinished();
	bool isStarted();
	bool isStoped();

	bool canBeRotated();
	bool canBeScaled();
	bool canBeTranslated();

	float getCurrentRotation();
	float getCurrentScaleX();
	float getCurrentScaleY();
	int getCurrentTranslationX();
	int getCurrentTranslationY();

	sf::Sprite getCurrentSprite();
	void setSpriteOriginCenter();

	// Methods
	void rotate(float p_angleStart, float p_angleEnd, long p_duration, bool p_rotationDirection);
	void rotate(float p_angleEnd, long p_duration, bool p_rotationDirection);
	void scale(float p_scaleXStart, float p_scaleYStart, float p_scaleXEnd, float p_scaleYEnd, long p_duration);
	void scale(float p_scaleXEnd, float p_scaleYEnd, long p_duration);
	void scaleNewSize(int p_newWidth, int p_newHeight, long p_duration);
	void translate(int p_positionXStart, int p_positionYStart, int p_positionXEnd, int p_positionYEnd, long p_duration);
	void translate(int p_positionXEnd, int p_positionYEnd, long p_duration);
	void start();
	void restart();
	void stop();

	void update();
	void updateRelatedObject();
	void updateRotation();
	void updateScale();
	void updateTranslation();
	void draw();


private:
	// Attributs
	sf::Sprite mSprite;
	long mSpriteDuration;

	ImageGIF* mSpriteGif;
	int mSpriteGifLoop;

	long mRotationDuration;
	float mRotationAngleStart;
	float mRotationAngleEnd;
	int mRotationAngleDirection;
	float mRotationAngleDiff;

	long mScaleDuration;
	float mScaleXStart;
	float mScaleYStart;
	float mScaleXEnd;
	float mScaleYEnd;
	float mScaleXDiff;
	float mScaleYDiff;

	long mTranslationDuration;
	int mTranslationXStart;
	int mTranslationYStart;
	int mTranslationXEnd;
	int mTranslationYEnd;
	int mTranslationXDiff;
	int mTranslationYDiff;

	Object* mRelatedObject;
	MapObject* mRelatedObjectMap;
	int mRelatedObjectOffsetX;
	int mRelatedObjectOffsetY;

	bool mStarted;
	bool mStoped;
	mks::Clock mClock;
};

