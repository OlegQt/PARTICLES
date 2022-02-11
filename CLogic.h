#pragma once
#include "CQuadTree.h"
#include "CMatrix.h"
#include <vector>


class CLogic
{
public:
	CLogic();
	~CLogic();
	// SETfunctions
	void AddElement(float, float, float, float);
	void SetScreenDpi(float, float);
	void SetQuantityZero();
	

	// GET functions
	CQuadTree* GetTree();
	int GetElemensQuantity();
	// SOLVEfunctions
	void TreeCalculation(CQuadTree*);
private:

	float Width, Height; // Screen sizes in pixels
	CQuadTree* QTree;

	int num = 0;

};

