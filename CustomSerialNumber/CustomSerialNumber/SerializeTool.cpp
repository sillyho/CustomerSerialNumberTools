#include "stdafx.h"
#include "SerializeTool.h"
#include "CManagerDialog.h"
#include "CObjectListDialog.h"

IMPLEMENT_SERIAL(CSerializeTool, CObject, 1)

CSerializeTool::CSerializeTool()
{
}


CSerializeTool::~CSerializeTool()
{
	ClearItems();
}

void CSerializeTool::AddItem(CItem* item)
{
	m_arrItems.Add(item);
}

void CSerializeTool::ClearItems()
{

	for (int i = 0; i < m_arrItems.GetSize(); i++)
	{
		m_arrItems[i]->Clear(); 

		delete m_arrItems[i];
	}
	m_arrItems.RemoveAll();
}

void CSerializeTool::Serialize(CArchive & archive)
{

	CObject::Serialize(archive);

	if (archive.IsStoring())
	{
		int i;
		archive << m_arrItems.GetSize();
		for (i = 0; i < m_arrItems.GetSize(); i++)
		{
			archive << m_arrItems[i]->Type;
			m_arrItems[i]->Serialize(archive);
		}
	}
	else
	{
		int count, i;
		archive >> count;
		m_arrItems.RemoveAll();
		int nType;
		for (i = 0; i < count; i++)
		{
			archive >> nType;
			CItem* pItem = NULL;
			if (nType == (int)ItemType::Fixed)
			{
				pItem = new CFixedItem();
			}
			else if (nType == (int)ItemType::SerialNumber)
			{
				pItem = new CSerialItem();
			}
			else if (nType == (int)ItemType::Date)
			{
				pItem = new CDateItem();
			}
			pItem->Serialize(archive);
			m_arrItems.Add(pItem);
		}
	}
}


BOOL CSerializeTool::Plus(int nloop )
{
	for (int i = 0; i < m_arrItems.GetSize(); i++)
	{
		if(!m_arrItems[i]->Plus(nloop))
			return FALSE;
	}
	return TRUE;
}
CString CSerializeTool::ToString()
{
	CString strValue = _T("");
	for (int i = 0; i < m_arrItems.GetSize(); i++)
	{
		strValue +=m_arrItems[i]->ToString();
	}
	return strValue;
}

BOOL CSerializeTool::SaveRule(CString Name, CSerializeTool& cz)
{
	try
	{
		CString Dir = GetCurrentDir() + "\\rules";
		if (!PathIsDirectory(Dir))
		{
			CreateDirectory(Dir, NULL);
		}
		CString strFileName;
		strFileName.Format(_T("%s\\%s.dat"), Dir, Name);
		CFile write_file;
		write_file.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&write_file, CArchive::store);
		cz.Serialize(ar);
		ar.Close();
		write_file.Close();
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

BOOL CSerializeTool::LoadRule(CString Name, CSerializeTool& cz)
{
	try
	{
		CString fileName = GetCurrentDir() + "\\rules\\" + Name+_T(".dat");
		if (!PathFileExists(fileName))
			return FALSE;
		
		CFile read_file;
		read_file.Open(fileName, CFile::modeRead);
		CArchive ar2(&read_file, CArchive::load);
		cz.Serialize(ar2);
		ar2.Close();
		read_file.Close();
		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
	
}
void CSerializeTool::GetRules(vector<CString>& vectorRules)
{
	vectorRules.empty();
	CString csDirPath = GetCurrentDir() + "\\rules\\*.dat";
	HANDLE file;
	WIN32_FIND_DATA fileData;
	file = FindFirstFile(csDirPath.GetBuffer(), &fileData);
	if (file != INVALID_HANDLE_VALUE)
	{
		CString tmp(fileData.cFileName);
		tmp.Replace(_T(".dat"), _T(""));
		vectorRules.push_back(tmp);
		while (FindNextFile(file, &fileData))
		{
			CString tmp2(fileData.cFileName);
			tmp2.Replace(_T(".dat"), _T(""));
			vectorRules.push_back(tmp2);
		}
	}
}
void CSerializeTool::DeleteRule(CString fileName)
{
	CString csDirPath = GetCurrentDir() + "\\rules\\"+ fileName+_T(".dat");
	if (PathFileExists(csDirPath))
	{
		DeleteFile(csDirPath);
	}
}
void CSerializeTool::ModifyRule(CString fileName)
{
	CObjectListDialog cd(fileName,FALSE);
	cd.DoModal();
}
void CSerializeTool::NewRule(CString fileName)
{
	CObjectListDialog cd(fileName, TRUE);
	cd.DoModal();
}
BOOL CSerializeTool::IsExistRule(CString fileName)
{
	CString csDirPath;
	csDirPath.Format(_T("%s\\rules\\%s.dat"), GetCurrentDir(), fileName) ;

	return (PathFileExists(csDirPath));
}
CString CSerializeTool::GetCurrentDir()
{
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path= path.Left(pos);
	return path;
}

void CSerializeTool::ManagerRules(CString& selectRuleName)
{
	CManagerDialog cd;
	if (cd.DoModal() == IDOK)
	{
		selectRuleName = cd.strSelectRule;
	}
	else
	{
		selectRuleName = _T("");
	}
}