#pragma once
#include "Resource.h"
#include "IdGenerator.h"

class BackgroundSpace
{
public:
	// Constructor - Destructor
	BackgroundSpace(int p_width, int p_height, int p_columnsCount, int p_linesCount);
	~BackgroundSpace(void);

	// Getters - Setters
	int getId();

	int getBackgroundTile(int p_column, int p_line);
	void setBackgroundTile(int p_item_id, int p_column, int p_line);

	int getColumnsCount();
	int getLinesCount();

	bool hasBackgroundTexture();
	sf::RenderTexture* getBackgroundTexture();

	static int getBackgroundSpaceCachedCount();


private:
	// Attributes
	int mId;
	int **mBackgroundTiles;
	int mWidth;
	int mHeight;
	int mColumnsCount;
	int mLinesCount;
	sf::RenderTexture *mBackgroundTexture;

	static IdGenerator mIdGenerator;
	static std::vector<BackgroundSpace*> mBackgroundSpaceCached;

	// Methods
	void generateBackgroundTexture();

	static void cacheBackgroundSpace(BackgroundSpace* p_backgroundTexture);
	static void uncacheBackgroundSpace(BackgroundSpace* p_backgroundTexture);
	static void uncacheBackgroundSpace(int p_index);
};

