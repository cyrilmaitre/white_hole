#pragma once
#include "Scrollable.h"
#include "Listable.h"

class List: public Scrollable
{
public:
	// Constructor - Destructor
	List();
	~List();

	// Getters - Setters
	int getPadding();
	void setPadding(int p_padding);

	int getSeperatorHeight();
	void setSeparatorHeight(int p_height);

	sf::Color getSeparatorColor();
	void setSeparatorColor(sf::Color p_color);

	int getContentWidth(bool p_forceScrollBar = false);
	int getContentHeight();	
	int getItemCount();
	Listable* getItem(int p_index);

	bool isAutoResizeHeight();
	void setAutoResizeHeight(bool p_auto);

	bool isAutoResizeWidth();
	void setAutoResizeWidth(bool p_auto);

	// Methods
	void addItem(Listable *p_item, bool p_notify = true);
	void removeItem(Listable *p_item, bool p_notify = true);
	void removeItem(int p_index, bool p_notify = true);
	void clear(bool p_notify = true);

	void notifyDataSetChanged();

	void update(sf::Event p_event);
	void draw();
	

protected:
	// Methods
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyScrollbarThumbPositionChanged();
	void notifyScrollOccured(bool p_up);


private:
	// Attributs
	int mPadding;
	int mItemIndexFirst;
	int mItemIndexLast;
	bool mAutoResizeHeight;
	bool mAutoResizeWidth;
	sf::RectangleShape mSeparatorShape;
	std::vector<Listable*> mItems;

	// Methods
	void updateScrollbar();
	void updateScrollbarSize();
	void updateScrollbarPosition();
	void updateScrollbarThumbPosition();
	void updateItems(sf::Event p_event);
	void updateItemsPosition();
	void updateSeparatorSize();
	void updateItemIndexFirst();
	void updateItemIndexLast();

	void incIndexFirstElement();
	void decIndexFirstElement();
	void resizeHeight();
	void resizeWidth();
};
