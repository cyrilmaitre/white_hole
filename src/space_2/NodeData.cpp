#include "NodeData.h"


//*************************************************************
// Init static
//*************************************************************
IdGenerator NodeData::mIdgenerator;


//*************************************************************
// Constructor - Destructor
//*************************************************************
NodeData::NodeData( TreeData* p_tree, NodeData* p_parent )
{
	this->mTree = NULL;
	this->mParent = NULL;

	this->setId(NodeData::mIdgenerator.getNextId());
	this->setTree(p_tree);
	this->setParent(p_parent);
}

NodeData::~NodeData(void)
{
}

void NodeData::destroyChilds()
{
	for(int i = 0; i < this->mChilds.size(); i++)
	{
		if(this->mChilds[i] != NULL)
		{
			this->mChilds[i]->destroyChilds();
			delete this->mChilds[i];
			this->mChilds[i] = NULL;
		}
	}
	this->mChilds.clear();
}


//*************************************************************
// Getters - Setters
//*************************************************************
long NodeData::getId()
{
	return this->mId;
}

void NodeData::setId( long p_id )
{
	this->mId = p_id;
}

bool NodeData::hasTree()
{
	return this->mTree != NULL;
}

TreeData* NodeData::getTree()
{
	return this->mTree;
}

void NodeData::setTree( TreeData* p_tree )
{
	this->mTree = p_tree;
	for(int i = 0; i < this->mChilds.size(); i++)
		this->mChilds[i]->setTree(p_tree);
}

bool NodeData::hasParent()
{
	return this->mParent != NULL;
}

NodeData* NodeData::getParent()
{
	return this->mParent;
}

void NodeData::setParent( NodeData* p_parent )
{
	this->mParent = p_parent;
}

bool NodeData::hasChilds()
{
	return this->mChilds.size() > 0;
}

int NodeData::getChildCount()
{
	int childsCount = 0;
	for(int i = 0; i < this->mChilds.size(); i++)
		childsCount += 1 + this->mChilds[i]->getChildCount();
	return childsCount;
}

NodeData* NodeData::getChild( int p_index )
{
	if(p_index < 0)
		p_index = 0;
	else if(p_index >= this->mChilds.size())
		p_index = this->mChilds.size() - 1;

	return this->mChilds[p_index];
}

bool NodeData::isRoot()
{
	return !this->hasParent();
}

bool NodeData::isLeaf()
{
	return !this->hasChilds();
}

std::string NodeData::getText()
{
	return "Node #" + Tools::buildStringWithInt(this->getId());
}


//*************************************************************
// Methods
//*************************************************************
void NodeData::addChild( NodeData* p_child )
{
	p_child->setParent(this);
	this->mChilds.push_back(p_child);
	
	if(this->hasTree())
		this->getTree()->notifyDataChanged();
}

void NodeData::removeChild( NodeData* p_child )
{
	for(int i = 0; i < this->mChilds.size(); i++)
	{
		if(p_child->getId() == this->mChilds[i]->getId())
		{
			this->mChilds.erase(this->mChilds.begin() + i);
			if(this->hasTree())
				this->getTree()->notifyDataChanged();
			break;
		}
	}
}


