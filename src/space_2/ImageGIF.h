#pragma once
#include "Object.h"
#include "SpriteParameter.h"
#include "Clock.h"

class ImageGIF: public Object
{
public:
	// Enum
	enum GIFOrientation
	{
		Horizontal = 0,
		Vertical
	};

	// Constructeur - Destructeur
	ImageGIF(	int p_nbFrame,
				int p_offsetX, 
				int p_offsetY, 
				float p_frequency,
				GIFOrientation p_orientation,
				sf::Texture* p_texture );
	ImageGIF(	SpriteParameter* p_sprite,
				float p_frequency,
				bool p_spriteDelete = false);
	~ImageGIF(void);

	// Getters - setters
	long getDurationInMilliseconds();
	float getDurationInSeconds();

	int getLoop();

	sf::Sprite& getSprite();
	int getWidth();
	int getHeight();

	// Graphics
	void update();
	void draw();


protected:
	// Methods
	void notifyPositionChanged();


private:
	// Attributs
	int mCurrentFrame;
	int mFrameCount;
	GIFOrientation mOrientation;
	bool mFirstFrame;
	int mLoop;

	int mOffsetX;
	int mOffsetY;

	float mFrequency;
	mks::Clock mClockFrequency;
	sf::Sprite mSprite;
	SpriteParameter* mSpriteParameter;
	bool mSpriteParameterDelete;
};



