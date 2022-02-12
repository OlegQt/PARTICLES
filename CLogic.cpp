#include "CLogic.h"
CLogic::CLogic()
{
	this->QTree = new CQuadTree();
	this->num = 0;
	this->LMpushed = false;
}
CLogic::~CLogic()
{
	this->QTree->~CQuadTree();
}

void CLogic::AddElement(float xA, float yA, float xB, float yB)
{
	//int r = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
	float Vx = (static_cast<float>(rand()) / RAND_MAX) * SPEED_MAX * 2 - SPEED_MAX;
	float Vy = (static_cast<float>(rand()) / RAND_MAX) * SPEED_MAX * 2 - SPEED_MAX;
	if (!this->QTree->InsertElement(new CArrow(xA, yA, Vx, Vy, DIAMETER)))
	{
		//MessageBox(NULL, L"can`t add element", L"", NULL);
	}
}
void CLogic::SetScreenDpi(float w, float h)
{
	this->Width = w;
	this->Height = h;

	RECT rect{ 0,0,w,h };
	this->QTree->SetBorder(rect);
}
void CLogic::SetQuantityZero()
{
	this->num = 0;
}

CQuadTree* CLogic::GetTree()
{
	return this->QTree;
}
void CLogic::TreeCalculation(CQuadTree* pT)
{
	CArrow* pA = nullptr;
	CArrow* pB = nullptr;
	int i;
	if (pT->IsSubDevided())
	{
		for (i = 0; i < 4; i++)
		{
			TreeCalculation(pT->GetChild(i));
		}
		// call Qtree function MergeLeafs to
		// check if children leafs have no alements
		// In this case call Qtree function will merge al foure children into one leaf
		pT->MergeLeafs();
	}
	else
	{
		for (i = 0; i < pT->GetLoad(); i++)
		{
			pA = pT->GetArrow(i);
			// Moove Elements
			pA->xPos += pA->Vx;
			pA->yPos += pA->Vy;
			// Chek if Elements close to borders only if Node touches the screen border
			if (pT->GetBorder().right == this->Width)
			{
				if (pA->xPos >= this->Width - pA->Diameter)
				{
					//Reverse speed
					pA->Vx *= -1;
					// Return position inside leaf borders
					pA->xPos = this->Width - pA->Diameter;
				}
			}
			if (pT->GetBorder().left == 0)
			{
				if (pA->xPos <= 0 + pA->Diameter)
				{
					// Reverse speed
					pA->Vx *= -1;
					// Return position inside leaf borders
					pA->xPos = 0 + pA->Diameter;
				}
			}
			if (pT->GetBorder().top == 0)
			{
				if (pA->yPos <= 0 + pA->Diameter)
				{
					// Reverse speed
					pA->Vy *= -1;
					// Return position inside leaf borders
					pA->yPos = 0 + pA->Diameter;
				}
			}
			if (pT->GetBorder().bottom == this->Height)
			{
				if (pA->yPos >= this->Height - pA->Diameter)
				{
					// Reverse speed
					pA->Vy *= -1;
					// Return position inside leaf borders
					pA->yPos = this->Height - pA->Diameter;
				}
			}
			// Check neibours
			for (int l = i + 1; l < pT->GetLoad(); l++)
			{
				pB = pT->GetArrow(l);
				if (CMatrix::Distance(pA->xPos, pA->yPos, pB->xPos, pB->yPos) < pA->Diameter + pB->Diameter)
				{
					//pA->Mass = 10;
					//pB->Mass = 10;
					this->collusion.push_back(new CArrow(pA->xPos, pA->yPos, pB->xPos, pB->yPos,pA->Diameter));
					//pA->Vx = 0;
					//pA->Vy = 0;
					//pB->Vx = 0;
					//pB->Vy = 0;
				}
			}

		}

		// Chek if Some elements get out from node
		pT->CheckTreeLeaf(this->QTree);
		num += pT->GetLoad();
	}
	pA = nullptr;
	pB = nullptr;
}

int CLogic::GetElemensQuantity()
{
	return this->num;
}