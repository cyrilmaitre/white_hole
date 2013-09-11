#include "Tree.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Tree::Tree(void)
{
	this->mTreeData = NULL;
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
	this->updateList();
}

void Tree::notifyTreeDataChanged()
{
	this->updateList();
}

void Tree::updateList()
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
