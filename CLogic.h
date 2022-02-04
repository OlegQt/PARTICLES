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
	void AddArrow(float,float,float,float);
	void SetScreenDpi(float, float);

	// GET functions
	CArrow* PullArrow(int num);
	unsigned int GetArraySize();
	std::pair<float, float> GetScreenRect();
	CQuadTree * GetTree();

	// SOLVEfunctions
	void SolveArray();
private:
	
	std::vector<CArrow>array; // Main data massive
	float Width, Height; // Screen sizes in pixels
	CQuadTree * QTree;

	int num = 0;
	
};

