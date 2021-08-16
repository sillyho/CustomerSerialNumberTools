#pragma once
#include "Item.h"
#include <afxtempl.h>
class CDateItem : 
	public CItem
{
public:
	DateType TypeDate;

public:
	CDateItem();
	CDateItem(DateType dt);
	CString ToString();
	void Serialize(CArchive& archive);
	BOOL Plus(int nLoop=1);
	void Clear();
	void Clone(CItem& ci);
	CMap<int, int, CString, CString> m_DateMapYear;
	CMap<int, int, CString, CString> m_DateMapMonth;
	CMap<int, int, CString, CString> m_DateMapDay;

private:

	void InitMap();

	int YearCount;//50Äê
	int MonthCount;//12ÔÂ
	int DayCount;//31Ìì
};

