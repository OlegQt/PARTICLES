#pragma once
#include "CQuadTree.h"
#include "CMatrix.h"
#include <vector>

#define SPEED_MAX 0.9f
#define DIAMETER 2.0f


class CLogic
{
public:
	CLogic();
	~CLogic();
	// SETfunctions
	void AddElement(float, float, float, float);
	void SetScreenDpi(float, float);
	void SetQuantityZero();

	// Global variables
	bool LMpushed;
	float xPos, yPos;
	std::vector<CArrow*>collusion;

	// GET functions
	CQuadTree* GetTree();
	int GetElemensQuantity();
	// SOLVEfunctions
	void TreeCalculation(CQuadTree*);

private:

	float Width, Height; // Screen sizes in pixels
	CQuadTree* QTree;
	

	int num = 0; // Elements ammount


};

