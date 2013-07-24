#pragma once
#include "Resource.h"
#include "Selectable.h"
#include "Job.h"
#include "TextBox.h"


class JobView: public Block
{
public:
	// Constructor - Destructor
	JobView(Job *p_job = NULL,
			double p_x = 0,
			double p_y = 0);
	~JobView(void);

	// Getters - Setters
	bool hasJob();
	Job *getJob();
	void setJob(Job *p_job);

	bool isSelectable();
	void setSelectable(bool p_selectable);

	// Methods
	void notifyPositionChanged();
	void notifyJobChanged();
	void updatePosition();
	void update(sf::Event myEvent);
	void draw();


private:
	// Attributs
	Job *mJob;
	bool mSelectable;
	sf::Sprite *mJobSprite;
	TextBox *mTBName;
	sf::RectangleShape mOverlayOver;
};

