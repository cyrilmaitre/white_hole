#pragma once
#include "Resource.h"
#include "ContainerView.h"
#include "ContainerItemView.h"
#include "ContainerStackView.h"


class ContainerViewManager
{
public:
	// Methods
	static void init();
	static void uninit();
	static ContainerViewManager* getInstance();

	ContainerView* getDraggedView();
	void setDraggedView(ContainerView* p_view);
	bool isViewDragged();
	bool isViewDragged(ContainerView* p_view);

	ContainerView* getDraggedDestinationView();

	void addView(ContainerView* p_view);
	void removeView(ContainerView* p_view);
	void releaseDrag();
	void releaseDrag(ContainerStackView* p_source, ContainerStackView* p_destination);
	void releaseDrag(ContainerStackView* p_source, ContainerItemView* p_destination);
	void releaseDrag(ContainerItemView* p_source, ContainerStackView* p_destination);
	void releaseDrag(ContainerItemView* p_source, ContainerItemView* p_destination);
	void notifyDraggedViewChanged();
	void draw();


private:
	// Constructor - Destructor
	ContainerViewManager(void);
	~ContainerViewManager(void);
	void deleteDraggedViewIcon();

	// Attributs
	static ContainerViewManager* mInstance;

	ContainerView* mDraggedView;
	sf::Sprite* mDraggedViewIcon;

	std::list<ContainerView*> mViews;
};

