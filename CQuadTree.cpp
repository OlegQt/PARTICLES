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
			delete(this->ar[0]);
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
bool CQuadTree::IsInside(float x, float y)
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

bool CQuadTree::PutElementInLeaf(CArrow* pAr, bool check)
{
	if (!this->IsInside(pAr->xPos, pAr->yPos)) return false;
	else
	{
		if (check)
		{
			for (int i = 0; i < Load; i++)
			{
				if (CMatrix::Distance(pAr->xPos, pAr->yPos, ar[i]->xPos, ar[i]->yPos) < pAr->Diameter * 3) return false;
			}
			ar[Load] = pAr; // Push element to array end
			this->Load++; // Increase element number		
			return true;
		}
		else
		{

			ar[Load] = pAr; // Push element to array end
			this->Load++; // Increase element number		
			return true;
		}
	}
}
bool CQuadTree::InsertElement(CArrow* pAr)
{
	if (this->IsSubDevided())
	{
		if (this->leaf[0]->InsertElement(pAr)) return true;
		if (this->leaf[1]->InsertElement(pAr)) return true;
		if (this->leaf[2]->InsertElement(pAr)) return true;
		if (this->leaf[3]->InsertElement(pAr))	return true;
	}
	else
	{
		if (this->Load < 4) return this->PutElementInLeaf(pAr, true);
		else
		{
			if (!this->Subdivide())
			{
				//MessageBox(NULL, L"can`t subdivide", L"", NULL);
				return false; // if grid mesh is to low
			}
			this->TransferAlltoLeafs(true);
			return this->PutElementInLeaf(pAr, true);
		}
		return false;
	}
}
bool CQuadTree::RelocateElement(CArrow* pAr)
{
	if (this->IsSubDevided())
	{
		if (this->leaf[0]->RelocateElement(pAr)) return true;
		if (this->leaf[1]->RelocateElement(pAr)) return true;
		if (this->leaf[2]->RelocateElement(pAr)) return true;
		if (this->leaf[3]->RelocateElement(pAr)) return true;
	}
	else
	{
		if (this->Load < 4) return this->PutElementInLeaf(pAr, false);
		else
		{
			if (!this->Subdivide())
			{
				//MessageBox(NULL, L"can`t subdivide", L"", NULL);
				return false; // if grid mesh is to low
			}
			else 
			{

				this->TransferAlltoLeafs(true);
				return this->PutElementInLeaf(pAr, true);
			}
		}
	}
}
void CQuadTree::RemoveElement(short num)
{
	if (this->Load > 1)
	{
		//Убираем пустой элемент массива (смещаем элементы влево)
		for (int i = num; i < this->Load - 1; i++)
		{
			this->ar[i] = this->ar[i + 1];
		}
		this->ar[Load - 1] = nullptr; // Delete last element
		this->Load--;
	}
	else if (this->Load == 1)
	{
		this->ar[0] = nullptr;
		this->Load--;
	}

}
bool CQuadTree::TransferAlltoLeafs(bool n)
{
	while (this->Load)
	{
		this->RelocateElement(this->ar[Load - 1]);
		this->ar[Load - 1] = nullptr;
		Load--;
	}
	return true;
}


bool CQuadTree::CheckTreeLeaf(CQuadTree* parent)
{
	// Проверяем все элементы внутри листа дерева
	// В случае, если элемент, выходит за пределы данного листа
	// производим удаление его из массива листа и затем вызываем
	// функцию добавления элемента в главное родительское дерево

	for (int i = 0; i < this->Load; i++)
	{
		CArrow* pA = this->GetArrow(i);
		if (!this->IsInside(pA->xPos, pA->yPos))
		{
			//parent->AddElement(pA);
			this->RemoveElement(static_cast<short>(i));
			if (parent->RelocateElement(pA)) return true;
			else
			{
				//MessageBeep(10);
				//parent->RelocateElement(pA);
			}
		}
	}
	return true;
}
bool CQuadTree::MergeLeafs()
{
	//if (!this->IsSubDevided()) return false;
	int LOAD = 0;
	bool flag = true;

	// Chek all children leafes
	// In case all 4 children are not subdivided 
	// and there are no elements inside them
	// Merge them into one leaf 
	for (int i = 0; i < 4; i++)
	{
		LOAD += this->leaf[i]->Load;
		if (this->leaf[i]->IsSubDevided()) flag = false;
	}
	if (LOAD == 0 && flag)
	{
		for (int i = 0; i < 4; i++)
		{
			delete(this->leaf[i]);
			this->leaf[i] = nullptr;
		}
		return true;
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
	if (hW < 6) return false;
	else {
		// TOP LEFT
		halfBorder.left = border.left;
		halfBorder.top = border.top;
		halfBorder.right = border.left + hW;
		halfBorder.bottom = border.top + hH;
		this->leaf[0] = new CQuadTree();
		this->leaf[0]->SetBorder(halfBorder);
		// TOP RIGHT
		halfBorder.left = border.left + hW;
		halfBorder.top = border.top;
		halfBorder.right = border.right;
		halfBorder.bottom = border.top + hH;
		this->leaf[1] = new CQuadTree();
		this->leaf[1]->SetBorder(halfBorder);
		// BOTTOM LEFT
		halfBorder.left = border.left;
		halfBorder.top = border.top + hH;
		halfBorder.right = border.left + hW;
		halfBorder.bottom = border.bottom;
		this->leaf[2] = new CQuadTree();
		this->leaf[2]->SetBorder(halfBorder);
		// BOTTOM RIGHT
		halfBorder.left = border.left + hW;
		halfBorder.top = border.top + hH;
		halfBorder.right = border.right;
		halfBorder.bottom = border.bottom;
		this->leaf[3] = new CQuadTree();
		this->leaf[3]->SetBorder(halfBorder);
		return true;
	}
}

RECT CQuadTree::GetBorder()
{
	return this->border;
}
CQuadTree* CQuadTree::GetChild(short n)
{
	return this->leaf[n];
}

int CQuadTree::GetLoad()
{
	return this->Load;
}
CArrow* CQuadTree::GetArrow(int num)
{
	return this->ar[num];
}
