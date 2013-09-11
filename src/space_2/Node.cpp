#include "Node.h"
#include "Tree.h"


//*************************************************************
// Define
//*************************************************************



//*************************************************************
// Constructor - Destructor
//*************************************************************
Node::Node( NodeData* p_data, Tree* p_tree )
{
	this->mTree = NULL;
	this->mNodeData = NULL;

	this->mNodeTextBox.setAutoResize(false);

	this->setTree(p_tree);
	this->setNodeData(p_data);
}

Node::~Node(void)
{
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


//*************************************************************
// Methods
//*************************************************************
void Node::updatePosition()
{
	this->mNodeTextBox.setPosition(this->getX(), this->getY());
}

void Node::updateTextBox()
{
	this->mNodeTextBox.setWidth(this->getWidth());
}

void Node::update( sf::Event p_event )
{
	Listable::update(p_event);
	if(this->isVisible())
	{
		if(this->isClicked())
		{
			this->mNodeData->setExpand(!this->mNodeData->isExpand());
			this->notifyExpandChanged();
		}
	}
}

void Node::draw()
{
	Listable::draw();
	if(this->isVisible())
	{
		this->mNodeTextBox.draw();
	}
}

void Node::notifyExpandChanged()
{
	if(this->mTree != NULL)
		this->mTree->notifyNodesChanged();
}

void Node::notifyNodeDataChanged()
{
	if(this->mNodeData != NULL)
	{
		this->mNodeTextBox.setText(this->mNodeData->getText());
	}
}

void Node::notifyPositionChanged()
{
	Listable::notifyPositionChanged();
	this->updatePosition();
}

void Node::notifySizeChanged()
{
	Listable::notifySizeChanged();
	this->updateTextBox();
}

void Node::notifyTreeChanged()
{
	if(this->mTree != NULL)
	{
		this->setSize(this->mTree->getContentWidth(), this->mNodeTextBox.getHeight());
	}
}





