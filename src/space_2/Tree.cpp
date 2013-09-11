#include "Tree.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Tree::Tree(void)
{
	this->mTreeData = NULL;

	this->setBackgroundColor(sf::Color(25, 26, 28), true);
	this->setBorderColor(sf::Color(194, 194, 194), true);
	this->setBorderSize(2, true);
	this->setPadding(0);
	this->setForceScrollBar(true);
	this->setSeparatorHeight(1);
	this->setSeparatorColor(sf::Color(86, 87, 89));
}

Tree::~Tree(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
TreeData* Tree::getTreeData()
{
	return this->mTreeData;
}

void Tree::setTreeData( TreeData* p_data )
{
	if(this->mTreeData != p_data)
	{
		this->mTreeData = p_data;
		this->notifyTreeDataChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void Tree::notifyNodesChanged()
{
	this->updateNodes();
}

void Tree::notifyTreeDataChanged()
{
	this->updateNodes();
}

void Tree::updateNodes()
{
	this->clear(true);
	if(this->mTreeData != NULL)
	{
		for(int i = 0; i < this->mTreeData->getRootCount(); i++)
		{
			this->addNode(this->mTreeData->getRoot(i));
		}
		this->notifyDataSetChanged();
	}
}

void Tree::addNode(NodeData* p_data)
{
	Node* currentView = new Node(p_data, this);
	this->addItem(currentView, false);

	if(p_data->isExpand())
	{
		for(int i = 0; i < p_data->getChildCount(); i++)
		{
			NodeData* currentChild = p_data->getChild(i);
			this->addNode(currentChild);
		}
	}
}
