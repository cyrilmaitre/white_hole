#pragma once
#include "Listable.h"
#include "TextBox.h"
#include "NodeData.h"

class Tree;

class Node : public Listable
{
public:
	// Constructor - Destructor
	Node(NodeData* p_data, Tree* p_tree);
	~Node(void);

	// Getters - Setters
	Tree* getTree();
	void setTree(Tree* p_tree);

	NodeData* getNodeData();
	void setNodeData(NodeData* p_data);

	bool isExpand();
	void setExpand(bool p_expand);

	// Methods
	void expand();
	void collapse();
	void updatePosition();
	void updateTextBox();
	void update(sf::Event p_event);
	void draw();
	void notifyExpandChanged();
	void notifyNodeDataChanged();
	void notifyTreeChanged();
	void notifyPositionChanged();
	void notifySizeChanged();


private:
	// Attributs
	Tree* mTree;

	bool mExpand;
	NodeData* mNodeData;
	TextBox mNodeTextBox;
};

