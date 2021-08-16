#include "stdafx.h"
#include "CFixedItem.h"
#include "Item.h"

CFixedItem::CFixedItem()
{
	Type = ItemType::Fixed;
}
CFixedItem::CFixedItem(CString str)
{
	Value = str;
	Type = ItemType::Fixed;
}
CString CFixedItem ::ToString()
{
	return Value;
}
void CFixedItem::Serialize(CArchive& archive)
{
	CItem::Serialize(archive);
}
BOOL CFixedItem::Plus(int nloop )
{
	return TRUE;
}
void CFixedItem::Clear()
{

}
void CFixedItem::Clone(CItem&cf)
{
	cf.Type = this->Type;
	cf.Value = this->Value;
}