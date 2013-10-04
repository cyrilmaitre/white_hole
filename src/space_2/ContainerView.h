#pragma once
#include "Focusable.h"

// Define
#define CONTAINERVIEW_WIDTH							36
#define CONTAINERVIEW_HEIGHT						36
#define CONTAINERVIEW_BACKGROUND_COLOR				sf::Color(65, 65, 65)
#define CONTAINERVIEW_BACKGROUND_COLOROVER			sf::Color(255, 127, 39)
#define CONTAINERVIEW_BACKGROUNDICON_HEIGHT			32
#define CONTAINERVIEW_BACKGROUNDICON_WIDTH			32

class ContainerView : public Focusable
{
public:
	// Enum
	enum ContainerViewType
	{
		ContainerStackView,
		ContainerItemView
	};

	// Constructor - Destructor
	ContainerView(void);
	~ContainerView(void);
	void deleteIcon();

	// Getters - Setters
	sf::Sprite* getIcon();

	ContainerViewType getContainerViewType();
	void setContainerViewType(ContainerViewType p_type);

	// Methods
	virtual void update();
	void updatePosition();
	virtual void update(sf::Event p_event);
	virtual void draw();
	void notifyPositionChanged();


protected:
	// Attributs
	sf::RectangleShape mBackground;
	sf::RectangleShape mBackgroundIcon;
	sf::Sprite* mIcon;
	ContainerViewType mContainerViewType;
};

