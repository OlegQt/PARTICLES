#include "CArrow.h"


CArrow::CArrow()
{}
CArrow::CArrow(float xA, float yA, float xB, float yB,float d)
{
	this->xPos = xA;
	this->yPos = yA;

	this->Vx = xB;
	this->Vy = yB;
	this->Diameter = d;
}
CArrow::~CArrow()
{
}

void CArrow::MakeMovement()
{
	xPos += Vx;
	yPos += Vy;
}

