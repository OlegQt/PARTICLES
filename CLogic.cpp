#include "CLogic.h"
CLogic::CLogic()
{
	this->QTree = new CQuadTree();
}
CLogic::~CLogic()
{
	this->QTree->~CQuadTree();
}

void CLogic::AddElement(float xA, float yA, float xB, float yB)
{
	this->QTree->AddElement(new CArrow(xA, yA, xB, yB));
}
void CLogic::SetScreenDpi(float w, float h)
{
	this->Width = w;
	this->Height = h;

	RECT rect{ 0,0,w,h };
	this->QTree->SetBorder(rect);
}

CQuadTree* CLogic::GetTree()
{
	return this->QTree;
}
void CLogic::TreeCalculation(CQuadTree* pT)
{
	CArrow* pA = nullptr;
	int i;
	if (pT->IsSubDevided())
	{
		for (i = 0; i < 4; i++)
		{
			TreeCalculation(pT->GetChild(i));
		}
		// Проверка если в узле дерева все листы пусты
		// Необходимо превратить узел в лист (вызвать соотвествующую функцию из класса Qtree)
	}
	else
	{
		for (i = 0; i < pT->GetLoad(); i++)
		{
			pA = pT->GetArrow(i);
			pA->xPos += pA->Vx;
		}
		// Chek if Some elements get out from node
		pT->CheckTreeLeaf(this->QTree);
		// Chek if Elements close to borders onle if Node touches the screen border		

	}
}
