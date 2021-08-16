#pragma once
#include "stdafx.h"

enum ItemType
{
	Fixed = 0,
	SerialNumber = 1,
	Date = 2
};
enum DateType
{
	Year = 0,
	Month = 1,
	Day = 2
};

class CItem :public CObject
{
public:
	DECLARE_SERIAL(CItem);
	CItem();
	virtual  ~CItem();
	virtual void Clear();
	virtual void Serialize(CArchive& archive);
	virtual CString ToString();
	virtual BOOL Plus(int nloop = 1);
	virtual void Clone(CItem&);

public:
	CString Value;
	ItemType Type;
};

