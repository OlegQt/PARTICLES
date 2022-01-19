#pragma once
#include "CArrow.h"
#include "CMatrix.h"
#include <vector>

#define STARN 74

class CLogic
{
public:
	CLogic();
	~CLogic();

	void AddElement(float,float,float);
	void AddArrow(float,float,float,float);

	void CreateStar();
	void RotateStar();
	void MooveStar(float, float);
	void SolveInteraction(int a, int b);
	unsigned int GetArraySize();
	CArrow* GetElement(int num);

private:
	
	std::vector<CArrow>array;
};

