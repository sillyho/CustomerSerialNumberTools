#pragma once
#include "Item.h"

class CFixedItem :public CItem
{
public:
	CFixedItem();
	CFixedItem(CString);
	CString ToString();
	void Serialize(CArchive& archive);
	BOOL Plus(int nloop = 1);
	void Clear();
	void Clone(CItem&);
};

