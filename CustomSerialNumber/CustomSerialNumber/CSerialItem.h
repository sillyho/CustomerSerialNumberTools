#pragma once
#include "Item.h"
class CSerialItem :
    public CItem
{
public:
	//当前值
	ULONG m_curOctValue;
	//最小值
	ULONG m_OctMinValue;
	//最大值
	ULONG m_OctMaxValue;
	//显示长度
	UINT m_StringLength;
	//是否循环（从最大值调到最小值）
	BOOL m_bCirculate;
public:
	//字符集合
	CString m_CharacterCollection;

public:
	CSerialItem();
	CSerialItem(CString, UINT);
	CSerialItem(CString, UINT, CString,CString,CString,BOOL);

	CString ToString();
	void Serialize(CArchive& archive);
	BOOL Plus(int nloop = 1);
	void Clear();
	void Clone(CItem& ct);
	CString OctToAny(ULONG);//10进制转任意进制
	ULONG AnyToOct(CString strAny);//任意进制转10进制
private:
	void OctToAny();//10进制转任意进制
	ULONG GetMax();

};

