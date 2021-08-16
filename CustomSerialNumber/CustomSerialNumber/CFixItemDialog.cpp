// CFixItemDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "CustomSerialNumber.h"
#include "CFixItemDialog.h"
#include "afxdialogex.h"
#include "resource.h"

// CFixItemDialog 对话框

IMPLEMENT_DYNAMIC(CFixItemDialog, CDialogEx)

CFixItemDialog::CFixItemDialog(CFixedItem* ci, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FIX, pParent)
{
	m_pFixedItem = ci;
}

CFixItemDialog::~CFixItemDialog()
{

}

void CFixItemDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFixItemDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFixItemDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CFixItemDialog 消息处理程序


void CFixItemDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strData = _T("");
	GetDlgItemText(IDC_EDIT_NAME, strData);
	m_pFixedItem->Value = strData;

	CDialogEx::OnOK();
}


BOOL CFixItemDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT_NAME, m_pFixedItem->Value);
	// TODO:  在此添加额外的初始化
	((CEdit*)(GetDlgItem(IDC_EDIT_NAME)))->SetSel(-1);
	GetDlgItem(IDC_EDIT_NAME)->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CFixItemDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)//捕捉回车
	{
		if (GetFocus() != GetDlgItem(IDC_EDIT_NAME))
		{
			return  FALSE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}