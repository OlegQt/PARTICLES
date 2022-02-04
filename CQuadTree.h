#pragma once
#include "CArrow.h"
#include <iostream>
#include <vector>


class CQuadTree
{
public:
	CQuadTree();
	~CQuadTree();

	bool IsSubDevided();
	bool IsInside(int x, int y);

	bool AddElement(CArrow * pAr);
	bool Solve();
	bool SetBorder(RECT);
	bool Subdivide();

	RECT GetBorder();
	CQuadTree * GetChild(short);
	
	
private:
	CQuadTree* leaf[4];
	CArrow* ar[4];
	RECT border;
	unsigned short Load;
};

