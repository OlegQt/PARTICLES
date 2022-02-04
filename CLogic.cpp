#include "CLogic.h"
CLogic::CLogic()
{
	this->QTree = new CQuadTree();
}
CLogic::~CLogic()
{
	this->array.clear();
}

void CLogic::AddArrow(float xA, float yA, float xB, float yB)
{
	//this->array.push_back(CArrow(xA, yA, xB, yB));
	//this->QTree->AddElement(&array.back());
	if (num == 10)
	{
		int y = 0;
	}
	this->QTree->AddElement(new CArrow(xA, yA, xB, yB));
	num++;
}
void CLogic::SetScreenDpi(float w, float h)
{
	this->Width = w;
	this->Height = h;

	RECT rect{ 0,0,w,h };
	this->QTree->SetBorder(rect);
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
std::pair<float, float> CLogic::GetScreenRect()
{
	return std::pair<float, float>(this->Width,this->Height);
}

CQuadTree* CLogic::GetTree()
{
	return this->QTree;
}

void CLogic::SolveArray()
{
	if (false)
	{
		if (!this->array.empty())
		{
			CArrow* pAr = nullptr;
			for (int iter = 0; iter < array.size(); iter++)
			{
				pAr = &array.at(iter);
				pAr->xPos += pAr->Vx;
				pAr->yPos += pAr->Vy;
				// float dV = 0.5f;

				// ѕровер€ем выход шарика за границы и отражаем
				if (pAr->xPos < 0 + pAr->Diameter)
				{
					pAr->Vx *= -1;
				}
				else if (pAr->xPos > Width - pAr->Diameter)
				{
					pAr->Vx *= -1;
				}

				else if (pAr->yPos < 0 + pAr->Diameter)
				{
					pAr->Vy *= -1;
				}
				else if (pAr->yPos > Height - pAr->Diameter)
				{
					pAr->Vy *= -1;
				}
			}
		}
	}
}
