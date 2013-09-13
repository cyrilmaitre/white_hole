#include "Tree.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR			sf::Color(25, 26, 28)
#define BORDERCOLOR				sf::Color(194, 194, 194)
#define BORDERSIZE				2
#define PADDING					0
#define SEPARATOR_HEIGHT		1
#define SEPARATOR_COLOR			sf::Color(86, 87, 89)


//*************************************************************
// Constructor - Destructor
//*************************************************************
Tree::Tree(void) : ListSelectableGroup(true)
{
	this->mTreeData = NULL;

	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);
	this->setForceScrollBar(true);
	this->setSeparatorHeight(SEPARATOR_HEIGHT);
	this->setSeparatorColor(SEPARATOR_COLOR);
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
