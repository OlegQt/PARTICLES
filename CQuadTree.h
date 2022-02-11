#pragma once
#include "CArrow.h"
#include "CMatrix.h"
#include <iostream>
#include <vector>


class CQuadTree
{
public:
	CQuadTree();
	~CQuadTree();

	bool IsSubDevided();
	bool IsInside(float x, float y);

	bool AddElement(CArrow * pAr); // Add entire new element(x,y) if there are no elements on this position
	bool RelocateElement(CArrow* pAr); // Its simillar to AddElement, but it`s used for elements wich leaves the leaf location
	bool PutElementInLeaf(CArrow* pAr, bool check); //Insert Element in Leaf
	bool TransferAlltoLeafs(bool); // Transfer all elements to children leafs

	bool CheckTreeLeaf(CQuadTree * parent); // Needed to send Parent Qtree as a parametr
	bool SetBorder(RECT);
	bool Subdivide();
	bool MergeLeafs();

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

