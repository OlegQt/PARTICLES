#pragma once
#include <windows.h>
class CArrow
{
public:
	CArrow(float,float,float);
	CArrow(float, float, float,float);
	CArrow();
	~CArrow();

	float xPos, yPos,Diameter;
	float Vx, Vy, Vz;
	float Mass;

	typedef struct vector
	{
		float pos;
	};
	vector pos = { 0.1f };

};


