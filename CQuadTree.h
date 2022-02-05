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
	void RemoveElement(short);

	RECT GetBorder(); // Return RECT structure for this Qtree element
	CQuadTree * GetChild(short); // Return pointer to Qtree child (TL,TR,BL,BR)
	int GetLoad(); // Return ammount of particles inside this Qtree node
	CArrow* GetArrow(int num); //Return pointer to particle Array
	
private:
	CQuadTree* leaf[4];
	CArrow* ar[4];
	RECT border;
	unsigned short Load;
};

