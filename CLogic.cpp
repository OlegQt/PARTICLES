#include "CLogic.h"
CLogic::CLogic()
{
}
CLogic::~CLogic()
{
	this->array.clear();
}

void CLogic::AddArrow(float xA, float yA, float xB, float yB)
{
	this->array.push_back(CArrow(xA, yA, xB, yB));
}
void CLogic::SetScreenDpi(float w, float h)
{
	this->Width = w;
	this->Height = h;
}
CArrow* CLogic::PullArrow(int num)
{	
	return &this->array.at(num);
	//return nullptr;
}
unsigned int CLogic::GetArraySize()
{
	return this->array.size();
}

void CLogic::SolveArray()
{
	if (!this->array.empty())
	{
		CArrow* pAr = nullptr;
		for (int iter = 0; iter < array.size(); iter++)
		{
			pAr = &array.at(iter);
			pAr->xPos += pAr->Vx;
			pAr->yPos += pAr->Vy;
			
			if (pAr->xPos < 0+pAr->Diameter)
			{				
				pAr->Vx *= -1;
			}
			if (pAr->xPos > Width - pAr->Diameter)
			{				
				pAr->Vx *= -1;
			}

			if (pAr->yPos < 0 + pAr->Diameter)
			{
				pAr->Vy *= -1;
			}
			if (pAr->yPos > Height - pAr->Diameter)
			{
				pAr->Vy *= -1;
			}
		}
	}
}
