#pragma once
#include "Resource.h"
#include "TreeData.h"
#include "IdGenerator.h"


class NodeData
{
public:
	// Constructor - Destructor
	NodeData(TreeData* p_tree = NULL, NodeData* p_parent = NULL);
	~NodeData(void);
	void destroyChilds();

	// Getters - Setters
	long getId();
	void setId(long p_id);

	bool hasTree();
	TreeData* getTree();
	void setTree(TreeData* p_tree);

	bool hasParent();
	NodeData* getParent();
	void setParent(NodeData* p_parent);

	bool hasChilds();
	int getChildCount();
	NodeData* getChild(int p_index);

	bool isRoot();
	bool isLeaf();

	virtual std::string getText();

	// Methods
	void addChild(NodeData* p_child);
	void removeChild(NodeData* p_child);


private:
	// Attributs
	long mId;
	TreeData* mTree;
	NodeData* mParent;
	std::vector<NodeData*> mChilds;

	static IdGenerator mIdgenerator;
};

