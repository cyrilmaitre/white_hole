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
#define CONTAINERVIEW_ROW_WIDTH				CONTAINERVIEW_ROW_PADDING + CONTAINER_ROW_SIZE * (CONTAINERVIEW_ROW_PADDING + CONTAINERVIEW_WIDTH)
#define CONTAINERVIEW_ROW_HEIGHT			CONTAINERVIEW_HEIGHT
#define CONTAINERVIEW_BACKGROUND_COLOR		sf::Color(127, 127, 127)
#define CONTAINERVIEW_BORDER_COLOR			sf::Color(100, 100, 100)
#define CONTAINERVIEW_BORDER_SIZE			2

class ContainerableView : public Block
{
public:
	// Constructor - Destructor
	ContainerableView(	double p_x = 0,
					double p_y = 0);
	~ContainerableView(void);

	// Getters - Setters
	Containerable* getContainerable();
	void setContainerable(Containerable* p_containerable);

	bool isDisplayEstimation();
	void setDisplayEstimation(bool p_estimation);

	bool isContainerableChanged();

	// Methods
	void addContainerRowView(ContainerRowView* p_view);
	void clear();

	void update();
	void updatePosition();
	void updateHeight();
	void updateEstimation();
	void updateEstimationPosition();
	void update(sf::Event p_event);
	void draw();
	
	void notifyContainerableChanged();
	void notifyPositionChanged();


private:
	// Attributs
	Containerable* mContainerable;
	std::vector<ContainerRowView*> mContainerRowViews;
	sf::RectangleShape mBottomShape;
	TextBox mTBEstimation;
	bool mDisplayEstimation;
	bool mContainerableChanged;
};

