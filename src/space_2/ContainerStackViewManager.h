#pragma once
#include "Resource.h"
#include "ContainerStackView.h"


class ContainerStackViewManager
{
public:
	// Methods
	static void init();
	static void uninit();
	static ContainerStackViewManager* getInstance();

	ContainerStackView* getDraggedView();
	void setDraggedView(ContainerStackView* p_view);
	bool isViewDragged();
	bool isViewDragged(ContainerStackView* p_view);

	ContainerStackView* getDraggedDestinationView();

	void addView(ContainerStackView* p_view);
	void removeView(ContainerStackView* p_view);
	void releaseDrag();
	void notifyDraggedViewChanged();
	void draw();


private:
	// Constructor - Destructor
	ContainerStackViewManager(void);
	~ContainerStackViewManager(void);
	void deleteDraggedViewIcon();

	// Attributs
	static ContainerStackViewManager* mInstance;

	ContainerStackView* mDraggedView;
	sf::Sprite* mDraggedViewIcon;

	std::list<ContainerStackView*> mViews;
};

