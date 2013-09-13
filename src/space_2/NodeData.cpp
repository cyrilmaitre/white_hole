#include "NodeData.h"
#include "SpriteParameterFactory.h"


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
	this->mExpand = false;
	this->mLevel = 0;

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
	if(this->hasTree())
		this->getTree()->notifyDataChanged();
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
	if(this->mParent != p_parent)
	{
		this->mParent = p_parent;
		this->notifyParentChanged();
	}
}

bool NodeData::hasChilds()
{
	return this->mChilds.size() > 0;
}

int NodeData::getChildCount()
{
	return this->mChilds.size();
}

int NodeData::getChildCountSum()
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

bool NodeData::canExpand()
{
	return this->getChildCount() > 0;
}

bool NodeData::isExpand()
{
	return this->mExpand;
}

void NodeData::setExpand( bool p_expand )
{
	this->mExpand = p_expand;
}

int NodeData::getLevel()
{
	return this->mLevel;
}

void NodeData::setLevel( int p_level )
{
	if(this->mLevel != p_level)
	{
		this->mLevel = p_level;
		this;notifyLevelChanged();
	}
}

std::string NodeData::getText()
{
	return "Node #" + Tools::buildStringWithInt(this->getId());
}

std::string NodeData::getIcon()
{
	return IC_16X16_INFO;
}

SpriteParameter* NodeData::getIconSprite()
{
	return SpriteParameterFactory::getSpriteParameterIcon16X16();
}


//*************************************************************
// Methods
//*************************************************************
void NodeData::addChild( NodeData* p_child, bool p_orderAlphebetically )
{
	p_child->setParent(this);
	p_child->setTree(this->getTree());

	if(p_orderAlphebetically)
	{
		bool inserted = false;
		for(int i = 0; i < this->mChilds.size(); i++)
		{
			std::string newChildText = p_child->getText();
			std::string currentChildText = this->mChilds[i]->getText();
			int compareResult = newChildText.compare(currentChildText); 
			if( compareResult < 0 || compareResult == 0)
			{
				this->mChilds.insert(this->mChilds.begin() + i, p_child);
				inserted = true;
				break;
			}
		}

		if(!inserted)
			this->mChilds.push_back(p_child);
	}
	else
	{
		this->mChilds.push_back(p_child);
	}
	
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

void NodeData::expand()
{
	this->setExpand(true);
}

void NodeData::collapse()
{
	this->setExpand(false);
}

void NodeData::notifyParentChanged()
{
	if(this->mParent != NULL)
	{
		this->setLevel(this->mParent->getLevel() + 1);
	}
}

void NodeData::notifyLevelChanged()
{
	for(int i = 0; i < this->mChilds.size(); i++)
	{
		this->mChilds[i]->setLevel(this->getLevel() + 1);
	}
}




