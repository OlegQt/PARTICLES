#pragma once
#include <windows.h>

// ����� CArrow ������������ ����� ���������,
// � ������� ������ ������� ������ � ��������� ������������
// ���������� ������� ������� xPos, yPos
// ���������� ������� ������� Vx,Vy
// ��� �� ����� ������������ ������ ����� ��� ������������ ������ ��������,
// ����� ��� ���������� ������, ���������� ������, ��������� � ���������� � ������������

class CArrow
{
public:
	CArrow(float, float, float,float,float);
	CArrow();
	~CArrow();

public:
	void MakeMovement();

	float xPos, yPos,Diameter;
	float Vx, Vy, Vz;
	float Mass;

};


