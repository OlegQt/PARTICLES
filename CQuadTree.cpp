#include "CQuadTree.h"

CQuadTree::CQuadTree()
{
	this->Load = 0;
	this->border = RECT();
	for (int i = 0; i < 4; i++)
	{
		this->leaf[i] = nullptr;
		this->ar[i] = nullptr;
	}

}
CQuadTree::~CQuadTree()
{
	if (IsSubDevided())
	{
		this->leaf[0]->~CQuadTree();
		this->leaf[1]->~CQuadTree();
		this->leaf[2]->~CQuadTree();
		this->leaf[3]->~CQuadTree();
	}
	else
	{
		for (int i = 0; i < this->Load; i++)
		{
			this->ar[0] = nullptr;
		}
	}
}

bool CQuadTree::IsSubDevided()
{
	if (this->leaf[0] != nullptr)
	{
		return true;
	}
	else return false;
}
bool CQuadTree::IsInside(int x, int y)
{
	if (x > border.left && x < border.right)
	{
		if (y > border.top && y < border.bottom)
		{
			return true;
		}
		else return false;
	}
	else return false;

}
bool CQuadTree::AddElement(CArrow* pAr)
{
	if (this->IsSubDevided())
	{
		if (this->leaf[0]->AddElement(pAr)) {
			//MessageBox(NULL, L"TL", L"click", NULL);
			return true;
		}
		if (this->leaf[1]->AddElement(pAr)) {
			//MessageBox(NULL, L"TR", L"click", NULL);
			return true;
		}
		if (this->leaf[2]->AddElement(pAr)) {
			//MessageBox(NULL, L"BL", L"click", NULL);
			return true;
		}
		if (this->leaf[3]->AddElement(pAr)) {
			//MessageBox(NULL, L"BR", L"click", NULL);
			return true;
		}
		//this->leaf[0]->AddElement(pAr);
		//this->leaf[1]->AddElement(pAr);
		//this->leaf[2]->AddElement(pAr);
		//this->leaf[3]->AddElement(pAr);

	}
	else
	{
		if (this->Load < 4) // < MAXLOAD
		{
			// If position inside rectangle add to array
			if (IsInside(pAr->xPos, pAr->yPos))
			{
				this->Load++;
				ar[Load - 1] = pAr;
				return true;
			}
		}
		else
		{
			// subdivede
			this->Subdivide();
			this->AddElement(pAr);
			
			// Transfer all elements to this children leafs
			for (int i = 0; i < Load; i++)
			{
				this->AddElement(this->ar[i]);
				this->ar[i] = nullptr;
			}
			this->Load = 0;
			return false;
		}
	}
}

bool CQuadTree::Solve()
{
	bool flag = true;
	if (this->IsSubDevided())
	{
		this->leaf[0]->Solve();
		this->leaf[1]->Solve();
		this->leaf[2]->Solve();
		this->leaf[3]->Solve();
	}
	else
	{
		CArrow* pAr = nullptr;
		for (int i = 0; i < this->Load; i++)
		{
			pAr = this->ar[i];
			pAr->Vx++;
		}
	}
	return false;
}
bool CQuadTree::SetBorder(RECT rect)
{
	this->border = rect;
	return false;
}
bool CQuadTree::Subdivide()
{
	RECT halfBorder{ 0,0,0,0 };
	long hW = (border.right - border.left) / 2;
	long hH = (border.bottom - border.top) / 2;
	// TOP LEFT
	halfBorder.left = border.left;
	halfBorder.top = border.top;
	halfBorder.right = border.left+hW;
	halfBorder.bottom =border.top+hH;
	this->leaf[0] = new CQuadTree();
	this->leaf[0]->SetBorder(halfBorder);
	// TOP RIGHT
	halfBorder.left = border.left + hW;
	halfBorder.top = border.top;
	halfBorder.right = border.right;
	halfBorder.bottom = border.top+hH;
	this->leaf[1] = new CQuadTree();
	this->leaf[1]->SetBorder(halfBorder);
	// BOTTOM LEFT
	halfBorder.left = border.left;
	halfBorder.top = border.top + hH;
	halfBorder.right = border.left+hW;
	halfBorder.bottom = border.bottom;
	this->leaf[2] = new CQuadTree();
	this->leaf[2]->SetBorder(halfBorder);
	// BOTTOM RIGHT
	halfBorder.left = border.left+hW;
	halfBorder.top = border.top+hH;
	halfBorder.right = border.right;
	halfBorder.bottom = border.bottom;
	this->leaf[3] = new CQuadTree();
	this->leaf[3]->SetBorder(halfBorder);
	return false;
}

RECT CQuadTree::GetBorder()
{
	return this->border;
}
CQuadTree* CQuadTree::GetChild(short n)
{
	return this->leaf[n];
}
