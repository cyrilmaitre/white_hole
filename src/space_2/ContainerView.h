#pragma once
#include "Block.h"
#include "TextBox.h"
#include "Containerable.h"
#include "ContainerRowView.h"

// Define
#define CONTAINERVIEW_ROW_PADDINGTOP		5
#define CONTAINERVIEW_ROW_PADDINGBOTTOM		5
#define CONTAINERVIEW_ROW_PADDINGLEFT		5
#define CONTAINERVIEW_ROW_PADDINGRIGHT		5
#define CONTAINERVIEW_ROW_PADDING			5
#define CONTAINERVIEW_ROW_WIDTH				CONTAINERVIEW_ROW_PADDING + CONTAINER_ROW_SIZE * (CONTAINERVIEW_ROW_PADDING + CONTAINERSTACKVIEW_WIDTH)
#define CONTAINERVIEW_ROW_HEIGHT			CONTAINERSTACKVIEW_HEIGHT
#define CONTAINERVIEW_BACKGROUND_COLOR		sf::Color(127, 127, 127)
#define CONTAINERVIEW_BORDER_COLOR			sf::Color(100, 100, 100)
#define CONTAINERVIEW_BORDER_SIZE			2

class ContainerView : public Block
{
public:
	// Constructor - Destructor
	ContainerView(	double p_x = 0,
					double p_y = 0);
	~ContainerView(void);

	// Getters - Setters
	Containerable* getContainerable();
	void setContainerable(Containerable* p_containerable);

	bool isContainerableChanged();

	// Methods
	void addContainerRowView(ContainerRowView* p_view);
	void clear();

	void notifyContainerableChanged();
	void notifyPositionChanged();
	void update();
	void updateEstimation();
	void updateEstimationPosition();
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	Containerable* mContainerable;
	std::vector<ContainerRowView*> mContainerRowViews;
	sf::RectangleShape mBottomShape;
	TextBox mTBEstimation;
	bool mContainerableChanged;
};

