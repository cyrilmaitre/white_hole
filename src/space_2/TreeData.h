#pragma once
#include "Resource.h"

class NodeData;

class TreeData
{
public:
	// Constructor - Destructor
	TreeData(void);
	~TreeData(void);
	void destroyRoots();

	// Getters - Setters
	bool hasRoot();
	int getRootCount();
	NodeData* getRoot(int p_index);

	bool isDataChanged();

	// Methods
	void addRoot(NodeData* p_root, bool p_orderAlphabetically = true);
	void removeRoot(NodeData* p_root);
	void notifyDataChanged();


private:
	// Attributs
	std::vector<NodeData*> mRoots;
	bool mDataChanged;
};

