#include "List.h"

//******************************
// Define
//******************************
#define DEFAULT_SEPARATOR_HEIGHT		0
#define DEFAULT_SEPARATOR_COLOR			sf::Color(0, 0, 0, 0)


//******************************
// Constructor - Destructor
//******************************
List::List()
{
	this->getScrollbar()->setButtonScrollActionDelegated(true);

	this->mItemIndexFirst = 0;
	this->mItemIndexLast = 0;
	this->setAutoResizeHeight(false);
	this->setAutoResizeHeightMax(-1);
	this->setAutoResizeWidth(false);
	this->setAutoResizeWidthMax(-1);

	this->mPadding = -1;
	this->setPadding(0);

	this->setSeparatorHeight(DEFAULT_SEPARATOR_HEIGHT);
	this->setSeparatorColor(DEFAULT_SEPARATOR_COLOR);
	this->setForceScrollBar(false);

	this->notifySizeChanged();
}

List::~List(void)
{
	for(int i = 0; i < this->getItemCount(); i++)
		delete this->mItems[i];
}


//******************************
// Getters - Setters
//******************************
int List::getPadding()
{
	return this->mPadding;
}

void List::setPadding( int p_padding )
{
	if(this->mPadding != p_padding)
	{
		this->mPadding = p_padding;
		this->notifySizeChanged();
	}
}

int List::getSeperatorHeight()
{
	return this->mSeparatorShape.getSize().y;
}

void List::setSeparatorHeight( int p_height )
{
	this->mSeparatorShape.setSize(sf::Vector2f(this->getContentWidth(), p_height));
}

sf::Color List::getSeparatorColor()
{
	return this->mSeparatorShape.getFillColor();
}

void List::setSeparatorColor( sf::Color p_color )
{
	this->mSeparatorShape.setFillColor(p_color);
}

int List::getContentWidth(bool p_forceScrollBar)
{
	if(p_forceScrollBar || this->isForceScrollbar() || this->mScrollBar->isUsefull())
		return this->getWidth() - this->getScrollbar()->getWidth() - this->getPadding() * 2;
	else
		return this->getWidth() - this->getPadding() * 2;
}

int List::getContentHeight()
{
	return this->getHeight() - this->getPadding() * 2;
}

int List::getItemCount()
{
	return this->mItems.size();
}

Listable* List::getItem( int p_index )
{
	return this->mItems[p_index];
}

bool List::isAutoResizeHeight()
{
	return this->mAutoResizeHeight;
}

void List::setAutoResizeHeight( bool p_auto )
{
	this->mAutoResizeHeight = p_auto;
}

int List::getAutoResizeHeightMax()
{
	return this->mAutoResizeHeightMax;
}

void List::setAutoResizeHeightMax( int p_max )
{
	this->mAutoResizeHeightMax = p_max;
}

bool List::isAutoResizeWidth()
{
	return this->mAutoResizeWidth;
}

void List::setAutoResizeWidth( bool p_auto )
{
	this->mAutoResizeWidth = p_auto;
}

int List::getAutoResizeWidthMax()
{
	return this->mAutoResizeWidthMax;
}

void List::setAutoResizeWidthMax( int p_max )
{
	this->mAutoResizeWidthMax = p_max;
}


//******************************
// Methods
//******************************
void List::addItem( Listable *p_item, bool p_notify )
{	
	p_item->setList(this);
	this->mItems.push_back(p_item);
	this->notifyItemAdded(p_item);

	if(p_notify)
		this->notifyDataSetChanged();
}

void List::removeItem( Listable *p_item, bool p_notify )
{
	for(int i = 0; i < this->getItemCount(); i++)
		if(this->mItems[i] == p_item)
			this->removeItem(i, p_notify);
}

void List::removeItem( int p_index, bool p_notify )
{
	this->notifyItemRemoved(this->mItems[p_index]);
	delete this->mItems[p_index];
	this->mItems.erase(this->mItems.begin() + p_index);

	if(p_notify)
		this->notifyDataSetChanged();
}

void List::clear(bool p_notify)
{
	for(int i = 0; i < this->mItems.size(); i++)
	{
		this->notifyItemRemoved(this->mItems[i]);
		delete this->mItems[i];
	}
	this->mItems.clear();

	if(p_notify)
		this->notifyDataSetChanged();
}

void List::notifyItemAdded( Listable *p_item )
{

}

void List::notifyItemRemoved( Listable *p_item )
{

}

void List::notifyDataSetChanged()
{
	if(this->isAutoResizeHeight())
		this->resizeHeight();

	if(this->isAutoResizeWidth())
		this->resizeWidth();

	this->updateScrollbar();
	this->updateItemIndexFirst();
}

void List::notifyPositionChanged()
{
	Scrollable::notifyPositionChanged();
	this->updateScrollbarPosition();
	this->updateItemsPosition();
}

void List::notifySizeChanged()
{
	Scrollable::notifySizeChanged();
	this->updateScrollbarSize();
	this->updateItemIndexFirst();
	this->updateSeparatorSize();
	this->updateScrollbarPosition();
	this->updateItemsPosition();
}

void List::notifyScrollbarThumbPositionChanged()
{
	this->updateItemIndexFirst();
}

void List::notifyScrollOccured( bool p_up )
{
	if(p_up)
		this->decIndexFirstElement();
	else
		this->incIndexFirstElement();
}

void List::update( sf::Event p_event )
{
	if(this->isVisible() && this->isEnable())
	{
		// Update Items
		this->updateItems(p_event);

		// Update Scrollable
		Scrollable::update(p_event);

		// Delegate of button scroll
		if(this->getScrollbar()->getButtonScrollUp()->isClicked())
			this->decIndexFirstElement();
		
		if(this->getScrollbar()->getButtonScrollDown()->isClicked())
			this->incIndexFirstElement();

		// Update Scrollbar
		if(this->mScrollBar->isThumbPositionChanged())
			this->notifyScrollbarThumbPositionChanged();
	}
}

void List::updateItems( sf::Event p_event )
{
	for(int i = this->mItemIndexFirst; i <= this->mItemIndexLast; i++)
	{
		this->mItems[i]->update(p_event);
	}
}

void List::updateScrollbar()
{
	int areaHeight = 0;
	for(int i = 0; i < this->getItemCount(); i++)
		areaHeight += this->mItems[i]->getHeight();
	areaHeight += (this->getItemCount() - 1) * this->getSeperatorHeight();
		
	this->mScrollBar->setScrollAreaHeight(areaHeight);
	this->updateScrollbarVisibility();

	this->mScrollBar->updateButtonPosition();
	this->mScrollBar->updateSpritePosition();
	this->mScrollBar->updateThumbPosition();
	this->mScrollBar->updateThumbPositionRange();
}

void List::updateScrollbarSize()
{
	this->mScrollBar->setScrollBarHeight(this->getHeight());
}

void List::updateScrollbarPosition()
{
	this->mScrollBar->setPosition(this->getX() + this->getWidth() - this->mScrollBar->getWidth(), this->getY());
}

void List::updateScrollbarThumbPosition()
{
	int scrollOffset = 0;
	for(int i = 0; i < this->mItemIndexFirst; i++)
	{
		scrollOffset += this->mItems[i]->getHeight();
		scrollOffset += this->getSeperatorHeight();
	}
	this->mScrollBar->setScrollOffsetInPx(scrollOffset, false);
}

void List::updateSeparatorSize()
{
	this->mSeparatorShape.setSize(sf::Vector2f(this->getContentWidth(), this->getSeperatorHeight()));
}

void List::updateItemsPosition()
{
	if(this->getItemCount() == 0)
		return;

	// Update items visible & position
	for(int i = 0; i < this->getItemCount(); i++)
		this->mItems[i]->setVisible(false);

	int positionX = this->getX() + this->getPadding();
	int positionY = this->getY() + this->getPadding();
	for(int i = this->mItemIndexFirst; i <= this->mItemIndexLast; i++)
	{
		this->mItems[i]->setVisible(true);
		this->mItems[i]->setPosition(positionX, positionY);
		positionY += this->mItems[i]->getHeight();
		positionY += this->getSeperatorHeight();
	}
}

void List::updateItemIndexFirst()
{
	this->mItemIndexFirst = 0;
	int scrollOffset = this->mScrollBar->getScrollOffsetInPx();
	while(scrollOffset > 0 && this->mItemIndexFirst < this->getItemCount() - 1)
	{
		if(scrollOffset >= (this->mItems[this->mItemIndexFirst]->getHeight() / 2))
		{
			scrollOffset -= this->mItems[this->mItemIndexFirst]->getHeight();
			scrollOffset -= this->getSeperatorHeight();
			this->mItemIndexFirst++;
		}
		else
		{
			scrollOffset = 0;
			if(this->mItemIndexFirst > 0)
				this->mItemIndexFirst++;
		}
	}

	this->updateItemIndexLast();
}

void List::updateItemIndexLast()
{
	this->mItemIndexLast = this->mItemIndexFirst;
	int areaHeight = this->getContentHeight();
	while(areaHeight > 0 && this->mItemIndexLast < this->getItemCount())
	{
		areaHeight -= this->mItems[this->mItemIndexLast]->getHeight();
		areaHeight -= this->getSeperatorHeight();
		this->mItemIndexLast++;
	}
	this->mItemIndexLast--;
	if(areaHeight < -this->getSeperatorHeight())
		this->mItemIndexLast--;

	this->updateItemsPosition();
}

void List::incIndexFirstElement()
{
	if(this->mItemIndexLast < (this->getItemCount() - 1))
	{
		this->mItemIndexFirst++;
		this->updateItemIndexLast();
		this->updateScrollbarThumbPosition();
	}
}

void List::decIndexFirstElement()
{
	if(this->mItemIndexFirst > 0)
	{
		this->mItemIndexFirst--;
		this->updateItemIndexLast();
		this->updateScrollbarThumbPosition();
	}
}

void List::draw()
{
	if(this->isVisible())
	{
		// Draw Scrollable
		Scrollable::draw(false);

		// Draw Items
		if(this->getItemCount() > 0)
		{
			for(int i = this->mItemIndexFirst; i <= this->mItemIndexLast; i++)
			{
				this->mItems[i]->draw();

				this->mSeparatorShape.setPosition(this->getX() + this->getPadding(), this->mItems[i]->getY() + this->mItems[i]->getHeight());
				Resource::resource->getApp()->draw(this->mSeparatorShape);
			}
		}

		// Draw Scrollbar
		this->mScrollBar->draw();
	}	
}

void List::resizeHeight()
{
	int itemsHeight = 0;
	for(int i = 0; i < this->getItemCount(); i++)
		itemsHeight += this->mItems[i]->getHeight();

	int newHeight = itemsHeight + this->getSeperatorHeight() * this->getItemCount() + this->getPadding() * 2;
	if(this->getAutoResizeHeightMax() > 0)
	{
		if(newHeight > this->getAutoResizeHeightMax())
		{
			this->setAutoResizeHeight(false);
			newHeight = this->getAutoResizeHeightMax();
		}
		else
		{
			this->setAutoResizeHeight(true);
		}
	}
	this->setHeight(newHeight);
}

void List::resizeWidth()
{
	int maxItemWidth = 0;
	for(int i = 0; i < this->getItemCount(); i++)
	{
		if(this->mItems[i]->getWidth() > maxItemWidth)
			maxItemWidth = this->mItems[i]->getWidth();
	}

	int newWidth = 0;
	if(this->hasScrollBar())
		newWidth = maxItemWidth + this->getPadding() * 2 + this->mScrollBar->getWidth();
	else
		newWidth = maxItemWidth + this->getPadding() * 2;

	if(this->getAutoResizeWidthMax() > 0)
	{
		if(newWidth > this->getAutoResizeWidthMax())
		{
			this->setAutoResizeWidth(false);
			newWidth = this->getAutoResizeWidthMax();
		}
		else
		{
			this->setAutoResizeWidth(true);
		}
		
	}
	this->setWidth(newWidth);
}










