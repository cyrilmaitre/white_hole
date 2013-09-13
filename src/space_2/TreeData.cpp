#include "TreeData.h"
#include "NodeData.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
TreeData::TreeData(void)
{
	this->mDataChanged = false;
}

TreeData::~TreeData(void)
{
}

void TreeData::destroyRoots()
{
	for(int i = 0; i < this->mRoots.size(); i++)
	{
		if(this->mRoots[i] != NULL)
		{
			this->mRoots[i]->destroyChilds();
			delete this->mRoots[i];
			this->mRoots[i] = NULL;
		}
	}
	this->mRoots.clear();
	this->notifyDataChanged();
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool TreeData::hasRoot()
{
	return this->mRoots.size() > 0;
}

int TreeData::getRootCount()
{
	return this->mRoots.size();
}

NodeData* TreeData::getRoot( int p_index )
{
	if(p_index < 0)
		p_index = 0;
	else if(p_index >= this->getRootCount())
		p_index = this->getRootCount() - 1;

	return this->mRoots[p_index];
}


bool TreeData::isDataChanged()
{
	bool returnValue = this->mDataChanged;
	this->mDataChanged = false;
	return returnValue;
}


//*************************************************************
// Methods
//*************************************************************
void TreeData::addRoot( NodeData* p_root, bool p_orderAlphabetically )
{
	p_root->setTree(this);
	
	if(p_orderAlphabetically)
	{
		bool inserted = false;
		for(int i = 0; i < this->mRoots.size(); i++)
		{
			std::string newRootText = p_root->getText();
			std::string currentRootText = this->mRoots[i]->getText();
			int compareResult = newRootText.compare(currentRootText); 
			if( compareResult < 0 || compareResult == 0)
			{
				this->mRoots.insert(this->mRoots.begin() + i, p_root);
				inserted = true;
				break;
			}
		}

		if(!inserted)
			this->mRoots.push_back(p_root);
	}
	else
	{
		this->mRoots.push_back(p_root);
	}

	this->notifyDataChanged();
}

void TreeData::removeRoot( NodeData* p_root )
{
	for(int i = 0; i < this->mRoots.size(); i++)
	{
		if(p_root->getId() == this->mRoots[i]->getId())
		{
			this->mRoots.erase(this->mRoots.begin() + i);
			this->notifyDataChanged();
			break;
		}
	}
}

void TreeData::notifyDataChanged()
{
	this->mDataChanged = true;
}
