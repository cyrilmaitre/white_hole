#pragma once
#include "Listable.h"
#include "TextBox.h"
#include "NodeData.h"
#include "SpriteParameter.h"

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

	virtual TextBox* getNodeTextBox();

	// Methods
	void updatePosition();
	void updateTextBox();
	void updateIcon();
	void updateSize();
	void update(sf::Event p_event);
	void draw();
	void notifyExpandChanged();
	void notifyNodeDataChanged();
	void notifyTreeChanged();
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifySelectedChanged();
	void notifyClickedChanged();


private:
	// Attributs
	Tree* mTree;

	NodeData* mNodeData;
	TextBox* mNodeTextBox;
	sf::Sprite* mIcon;
	sf::Sprite* mIconExpand;
};

