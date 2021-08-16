// CustomSerialNumber.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "CustomSerialNumber.h"

#include "SerializeTool.h"
#include "Item.h"

#include <iostream>
#include<string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CObjectListDialog.h"



EXPORT_CUSTOMSERIALNUMBER void SetCustomSerialNumber(const char* serial_name)
{

	CString Dir = CSerializeTool::GetCurrentDir() + "\\rules";
	if (!PathIsDirectory(Dir))
	{
		CreateDirectory(Dir, NULL);
	}

	 CString name(serial_name);

	 if (!CSerializeTool::IsExistRule(name))
	 {
		 CObjectListDialog cd(name, TRUE);
		 cd.DoModal();
	 }
	 else
	 {
		 CObjectListDialog cd(name, FALSE);
		 cd.DoModal();
	 }
}

EXPORT_CUSTOMSERIALNUMBER void  DelCustomSerialNumber(const char* serial_name)
{
	CString name(serial_name);
	CSerializeTool::DeleteRule(name);
}

EXPORT_CUSTOMSERIALNUMBER char* GetCustomSerialNumber(const char* serial_name,int nLoop)
{
	CString Name(serial_name);
	CSerializeTool  m_SerialTool;
	if (!m_SerialTool.LoadRule(Name, m_SerialTool))
	{
		MessageBox(NULL,_T("加载规则失败,请检查规则是否存在!"), _T("错误"), MB_OK | MB_ICONERROR);
		return NULL;
	}
	CString strData = m_SerialTool.ToString();
	if (!m_SerialTool.Plus(nLoop))
	{
		MessageBox(NULL, _T("序列号递增失败，请检查是否达到上限!"), _T("错误"), MB_OK | MB_ICONERROR);
		return NULL;
	}
	if(!CSerializeTool::SaveRule(Name, m_SerialTool))
	{
		MessageBox(NULL, _T("更新保存规则失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return NULL;
	}

	int nLen = WideCharToMultiByte(CP_ACP, 0, strData, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
		return NULL;

	char* pResult = (char*)malloc(nLen * sizeof(char) + 1);
	WideCharToMultiByte(CP_ACP, 0, strData, -1, pResult, nLen, NULL, NULL);

	
	return pResult;
	
}

EXPORT_CUSTOMSERIALNUMBER void FreeMemory(void* p_addr)
{
	if ((p_addr != NULL) && (p_addr != ""))
	{
		free(p_addr);
		p_addr = NULL;
	}
}
