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
			NodeData* currentRoot = this->mTreeData->getRoot(i);
			Node* currentRootView = new Node(currentRoot, this);
			this->addItem(currentRootView, false);
		}
		this->notifyDataSetChanged();
	}
}
