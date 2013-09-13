#pragma once
#include "ListSelectableGroup.h"
#include "Node.h"
#include "TreeData.h"


class Tree : public ListSelectableGroup
{
public:
	// Constructor - Destructor
	Tree(void);
	~Tree(void);

	// Getters - Setters
	TreeData* getTreeData();
	void setTreeData(TreeData* p_data);

	// Methods
	void addNode(NodeData* p_data);
	void updateNodes();
	void notifyNodesChanged();
	void notifyTreeDataChanged();


private:
	// Attributs
	TreeData* mTreeData;
};

