#include "Node.h"
#include "Tree.h"
#include "SpriteParameterFactory.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR			sf::Color(255, 255, 255, 0)
#define PADDING					3
#define TB_BACKGROUNDCOLOR		sf::Color(255, 255, 255, 0)
#define TB_FONTCOLOR			sf::Color(192, 192, 192)
#define TB_MARGINLEFT			PADDING * 2
#define LEVEL_OFFSET			16


//*************************************************************
// Constructor - Destructor
//*************************************************************
Node::Node( NodeData* p_data, Tree* p_tree )
{
	this->mTree = NULL;
	this->mNodeData = NULL;
	this->mNodeTextBox = NULL;
	this->mIcon = NULL;
	this->mIconExpand = NULL;

	this->mNodeTextBox = this->getNodeTextBox();
	this->mNodeTextBox->setAutoResize(false);

	this->setTree(p_tree);
	this->setNodeData(p_data);

	this->setBackgroundColor(BACKGROUNDCOLOR, true);
}

Node::~Node(void)
{
	delete this->mNodeTextBox;

	if(this->mIcon != NULL)
		delete this->mIcon;

	if(this->mIconExpand != NULL)
		delete this->mIconExpand;
}


//*************************************************************
// Getters - Setters
//*************************************************************
Tree* Node::getTree()
{
	return this->mTree;
}

void Node::setTree( Tree* p_tree )
{
	if(this->mTree != p_tree)
	{
		this->mTree = p_tree;
		this->notifyTreeChanged();
	}
}

NodeData* Node::getNodeData()
{
	return this->mNodeData;
}

void Node::setNodeData( NodeData* p_data )
{
	if(this->mNodeData != p_data)
	{
		this->mNodeData = p_data;
		this->notifyNodeDataChanged();
	}
}

TextBox* Node::getNodeTextBox()
{
	TextBox* returnTB = new TextBox();
	returnTB->setBackgroundColor(TB_BACKGROUNDCOLOR, true);
	returnTB->setFontColor(TB_FONTCOLOR);
	return returnTB;
}


//*************************************************************
// Methods
//*************************************************************
void Node::updatePosition()
{
	float levelOffset = this->mNodeData->getLevel() * LEVEL_OFFSET;
	if(this->mIcon != NULL)
	{
		this->mIcon->setPosition(this->getX() + levelOffset + PADDING, this->getY() + PADDING);
		this->mNodeTextBox->setPosition(this->mIcon->getPosition().x + this->mIcon->getGlobalBounds().width + TB_MARGINLEFT, this->getY() + PADDING);
	}
	else
	{
		this->mNodeTextBox->setPosition(this->getX() + levelOffset + PADDING, this->getY() + PADDING);
	}

	if(this->mIconExpand != NULL)
		this->mIconExpand->setPosition(this->getRightX() - this->mIconExpand->getGlobalBounds().width - PADDING, this->getY() + PADDING);
}

void Node::updateTextBox()
{
	// TB Width
	int tbWidth = this->getWidth() - PADDING * 2 - this->mNodeData->getLevel() * LEVEL_OFFSET;

	if(this->mIconExpand != NULL)
		tbWidth -= this->mIconExpand->getGlobalBounds().width;

	if(this->mIcon != NULL)
		tbWidth -= this->mIcon->getGlobalBounds().width + TB_MARGINLEFT - PADDING * 2;

	this->mNodeTextBox->setWidth(tbWidth);

	// Text
	if(this->mNodeData != NULL)
		this->mNodeTextBox->setText(this->mNodeData->getText());
}

void Node::updateIcon()
{
	// Icon
	if(this->mIcon != NULL)
	{
		delete this->mIcon;
		this->mIcon = NULL;
	}
	
	if(this->mNodeData != NULL && this->mNodeData->getIcon() != "" && this->mNodeData->getIconSprite() != NULL)
		this->mIcon = this->mNodeData->getIconSprite()->getSpritePtr(this->mNodeData->getIcon(), this->getHeight() - PADDING * 2, this->getHeight() - PADDING * 2);

	// Icon Expand
	if(this->mIconExpand != NULL)
	{
		delete this->mIconExpand;
		this->mIconExpand= NULL;
	}

	if(this->mNodeData != NULL && this->mNodeData->canExpand())
	{
		if(this->mNodeData->isExpand())
			this->mIconExpand = SpriteParameterFactory::getSpriteParameterIcon16X16()->getSpritePtr(IC_16X16_COLLAPSE, this->getHeight() - PADDING * 2, this->getHeight() - PADDING * 2);
		else
			this->mIconExpand = SpriteParameterFactory::getSpriteParameterIcon16X16()->getSpritePtr(IC_16X16_EXPAND, this->getHeight() - PADDING * 2, this->getHeight() - PADDING * 2);
	}

	// TextBox & Position
	this->updateTextBox();
	this->updatePosition();
}

void Node::update( sf::Event p_event )
{
	Listable::update(p_event);
	if(this->isVisible())
	{
		if(this->isClicked())
		{
			if(this->mNodeData != NULL && this->mNodeData->canExpand())
			{
				this->mNodeData->setExpand(!this->mNodeData->isExpand());
				this->notifyExpandChanged();
			}
		}
	}
}

void Node::draw()
{
	Listable::draw();
	if(this->isVisible())
	{
		if(this->mIcon != NULL)
			Resource::resource->getApp()->draw(*this->mIcon);
		if(this->mIconExpand != NULL)
			Resource::resource->getApp()->draw(*this->mIconExpand);
		this->mNodeTextBox->draw();
	}
}

void Node::notifyExpandChanged()
{
	if(this->mTree != NULL)
		this->mTree->notifyNodesChanged();
}

void Node::notifyNodeDataChanged()
{
	this->updateSize();
	if(this->mNodeData != NULL)
		this->updateIcon();
}

void Node::notifyPositionChanged()
{
	Listable::notifyPositionChanged();
	this->updatePosition();
}

void Node::notifySizeChanged()
{
	Listable::notifySizeChanged();
	this->updateIcon();
}

void Node::notifyTreeChanged()
{
	this->updateSize();
}

void Node::updateSize()
{
	if(this->mTree != NULL && this->mNodeData != NULL)
		this->setSize(this->mTree->getContentWidth(true), this->mNodeTextBox->getHeight() + PADDING * 2);
}

