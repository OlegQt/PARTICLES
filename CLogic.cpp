#include "CLogic.h"
CLogic::CLogic()
{
}
CLogic::~CLogic()
{
	this->array.clear();
}

void CLogic::AddElement(float xPos, float yPos, float Diameter)
{
	this->array.push_back(CArrow(xPos, yPos, Diameter));
}
void CLogic::AddArrow(float xA, float yA, float xB, float yB)
{
	this->array.push_back(CArrow(xA, yA, xB, yB));
}
void CLogic::CreateStar()
{

	if (this->array.size()) this->array.clear();

	for (int iter = 0; iter < STARN; iter++)
	{
		CArrow pArrow = CArrow(0.0f, 0.0f, 500.0f, 0.0f);
		CMatrix::rotate(&pArrow, iter*360/ STARN);
		CMatrix::sum(&pArrow, 250, 250);

		this->array.push_back(pArrow);
	}
	for (int iter = 0; iter < STARN; iter++)
	{
		CArrow pArrow = CArrow(0.0f, 0.0f, 500.0f, 0.0f);
		CMatrix::rotate(&pArrow, iter * 360 / STARN);
		CMatrix::sum(&pArrow,200, 250);

		this->array.push_back(pArrow);
	}



}
void CLogic::RotateStar()
{
	if (this->array.size())
	{
		for (int iter = STARN; iter < STARN*2; iter++)
		{
			float dX = this->array.at(iter).xPos;
			float dY = this->array.at(iter).yPos;
			CMatrix::sum(&this->array.at(iter), -dX, -dY);
			CMatrix::rotate(&this->array.at(iter), 1.0f);
			CMatrix::sum(&this->array.at(iter), dX, dY);
		}
	}
}
void CLogic::MooveStar(float a,float b)
{
	if (this->array.size())
	{
		for (int iter = STARN; iter < STARN * 2; iter++)
		{
			float dX = this->array.at(iter).xPos;
			float dY = this->array.at(iter).yPos;
			CMatrix::sum(&this->array.at(iter), -dX+a, -dY+b);
			//CMatrix::sum(&this->array.at(iter), -a, -b);
		}
	}
}
void CLogic::SolveInteraction(int a, int b)
{
	// расчет косинуса угла между вектором скорости первого шара и осью между ними

}
unsigned int CLogic::GetArraySize()
{
	return this->array.size();
}
CArrow* CLogic::GetElement(int num)
{
	return &this->array.at(num);
}
