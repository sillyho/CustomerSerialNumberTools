#include "stdafx.h"

#include "MyTool.h"

#include <direct.h>
#include <fstream>
#include <io.h>

CMyTool* CMyTool::instance_ = NULL;

// 默认配置,外面可设置
std::string CMyTool::base_chars_ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

CMyTool::CMyTool()
{
}


CMyTool::~CMyTool()
{
}

CMyTool * CMyTool::Instance()
{
	if (instance_ == NULL)
	{
		instance_ = new CMyTool();
	}

	return instance_;
}

int CMyTool::CreateDirectoryRecursion(std::string path)
{
	int len = path.length();
	char tmpDirPath[1000] = { 0 };
	for (int i = 0; i < len; i++)
	{
		tmpDirPath[i] = path[i];
		if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
		{
			if (_access(tmpDirPath, 0) == -1)
			{
				int ret = _mkdir(tmpDirPath);
				if (ret == -1) return ret;
			}
		}
	}
	return 0;
}

CString CMyTool::GetModuleDirPath()
{
	HMODULE module = GetModuleHandle(0);
	char pFileName[MAX_PATH];
	GetModuleFileNameA(module, pFileName, MAX_PATH);

	CString csFullPath(pFileName);
	int nPos = csFullPath.ReverseFind(_T('\\'));
	if (nPos < 0)
		return CString("");
	else
		return csFullPath.Left(nPos);
}

std::string CMyTool::Increment(std::string src, bool is_from_recursion)
{
	if (is_from_recursion && src.empty())
	{
		std::string res = "";
		return res + base_chars_.at(0);
	}

	char last_char = src.at(src.length() - 1);
	std::string fragment = src.substr(0, src.length() - 1);

	if (base_chars_.find(last_char) < base_chars_.length() - 1)
	{
		last_char = base_chars_[base_chars_.find(last_char) + 1];
		return fragment + last_char;
	}

	return Increment(fragment, true) + base_chars_.at(0);
}