#pragma once
#include "afx.h"
#include "Item.h"
#include "CFixedItem.h"
#include "CSerialItem.h"
#include "CDateItem.h"
#include <vector>
using namespace std;
class CSerializeTool :
	public CObject
{
public:
	DECLARE_SERIAL(CSerializeTool);
	CSerializeTool();
	virtual ~CSerializeTool();

public:
	CArray<CItem*, CItem*> m_arrItems;

public:
	void AddItem(CItem* item);
	void ClearItems();
	void Serialize(CArchive& archive);

	//使用
	BOOL Plus(int nloop = 1);
	CString ToString();

	//设置部分
public:

	static BOOL SaveRule(CString Name, CSerializeTool& cz);
	static BOOL LoadRule(CString Name, CSerializeTool& cz);
	
	static void DeleteRule(CString Name);
	static void ModifyRule(CString Name);
	static void NewRule(CString Name);
	static BOOL IsExistRule(CString Name);
	static void ManagerRules(CString& selectRuleName);

	static CString GetCurrentDir();

	static void GetRules(vector<CString>& vectorRules);
};

