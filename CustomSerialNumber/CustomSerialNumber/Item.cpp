#include "stdafx.h"
#include "Item.h"

IMPLEMENT_SERIAL(CItem, CObject, 1)

CItem::CItem()
{

}

CItem::~CItem()
{
}

void CItem::Serialize(CArchive& archive)
{
	CObject::Serialize(archive);

	if (archive.IsStoring())
	{
		archive << Type << Value;
	}
	else
	{
		int nType;
		archive >> nType >> Value;
		Type = (ItemType)nType;
	}
}
CString CItem::ToString()
{
	return Value;
}
BOOL CItem::Plus(int nloop)
{
	return TRUE;

}
void CItem::Clear()
{

}
void CItem::Clone(CItem& ct)
{

}