// CManagerDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "CManagerDialog.h"
#include "afxdialogex.h"
#include "SerializeTool.h"
#include<vector>
#include<stdio.h>
#include "CObjectListDialog.h"
using namespace std;

// CManagerDialog 对话框

IMPLEMENT_DYNAMIC(CManagerDialog, CDialogEx)

CManagerDialog::CManagerDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MANAGER, pParent)
{
	strSelectRule = _T("");
}

CManagerDialog::~CManagerDialog()
{
}

void CManagerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Data, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CManagerDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CManagerDialog::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CManagerDialog::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CManagerDialog::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDOK, &CManagerDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CManagerDialog 消息处理程序


BOOL CManagerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listCtrl.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);
	m_listCtrl.InsertColumn(1, _T("规则名称"), LVCFMT_LEFT, 200);
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	RefreshRules();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CManagerDialog::RefreshRules()
{
	m_listCtrl.DeleteAllItems();
	vector<CString>ruleList;
	CSerializeTool::GetRules(ruleList);
	int nIndex = 0;
	CString strIndex;
	for (vector<CString> ::iterator it = ruleList.begin(); it != ruleList.end(); ++it, nIndex++)
	{
		strIndex.Format(_T("%d"), nIndex + 1);
		m_listCtrl.InsertItem(nIndex, strIndex);
		m_listCtrl.SetItemText(nIndex, 1, *it);
	}
}

void CManagerDialog::OnBnClickedButtonNew()
{
	// TODO: 在此添加控件通知处理程序代码
	CSerializeTool ct;
	CObjectListDialog cd(_T(""), TRUE);
	cd.DoModal();
	RefreshRules();
}


void CManagerDialog::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	if (nItem == -1)
	{
		return;
	}
	CString Name = m_listCtrl.GetItemText(nItem, 1);
	CSerializeTool::DeleteRule(Name);

	m_listCtrl.DeleteItem(nItem);


}


void CManagerDialog::OnBnClickedButtonEdit()
{

	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	if (nItem == -1)
	{
		return;
	}
	CString Name = m_listCtrl.GetItemText(nItem, 1);


	CSerializeTool ct;
	CObjectListDialog cd(Name, FALSE);
	cd.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void CManagerDialog::OnBnClickedOk()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	if (nItem == -1)
	{
		return;
	}
	strSelectRule = m_listCtrl.GetItemText(nItem, 1);

	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
