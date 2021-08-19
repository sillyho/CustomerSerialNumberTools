// CSerialItemDialog.cpp: 实现文件
//

#include"stdafx.h"
#include "CustomSerialNumber.h"
#include "CSerialItemDialog.h"
#include "afxdialogex.h"
#include "resource.h"


// CSerialItemDialog 对话框

IMPLEMENT_DYNAMIC(CSerialItemDialog, CDialogEx)

CSerialItemDialog::CSerialItemDialog(CSerialItem* pcs, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SERIAL, pParent)
{
	m_pSerialItem = pcs;

}

CSerialItemDialog::~CSerialItemDialog()
{
}

void CSerialItemDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSerialItemDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSerialItemDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CSerialItemDialog 消息处理程序


BOOL CSerialItemDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (m_pSerialItem != nullptr)
	{
		SetDlgItemText(IDC_EDIT_NAME, m_pSerialItem->m_CharacterCollection);
		SetDlgItemText(IDC_EDIT_CUR, m_pSerialItem->OctToAny(m_pSerialItem->m_curOctValue));
		SetDlgItemText(IDC_EDIT_MIN, m_pSerialItem->OctToAny(m_pSerialItem->m_OctMinValue));
		SetDlgItemText(IDC_EDIT_MAX, m_pSerialItem->OctToAny(m_pSerialItem->m_OctMaxValue));
		CString strLen;
		strLen.Format(_T("%d"), m_pSerialItem->m_StringLength);
		SetDlgItemText(IDC_EDIT_LEN, strLen);
		if (m_pSerialItem->m_bCirculate)
			CheckDlgButton(IDC_CHECK_CIR, BST_CHECKED);
		else
			CheckDlgButton(IDC_CHECK_CIR, BST_UNCHECKED);

	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSerialItemDialog::OnBnClickedOk()
{
	CString strValue;
	GetDlgItemText(IDC_EDIT_NAME, strValue);
	m_pSerialItem->m_CharacterCollection = strValue;

	GetDlgItemText(IDC_EDIT_LEN, strValue);
	m_pSerialItem->m_StringLength = (UINT)(_ttoi(strValue));

	GetDlgItemText(IDC_EDIT_CUR, strValue);
	m_pSerialItem->m_curOctValue = m_pSerialItem->AnyToOct(strValue);

	GetDlgItemText(IDC_EDIT_MIN, strValue);
	m_pSerialItem->m_OctMinValue = m_pSerialItem->AnyToOct(strValue);

	GetDlgItemText(IDC_EDIT_MAX, strValue);
	m_pSerialItem->m_OctMaxValue = m_pSerialItem->AnyToOct(strValue);


	if (((CButton*)GetDlgItem(IDC_CHECK_CIR))->GetCheck() == BST_CHECKED)
	{
		m_pSerialItem->m_bCirculate = TRUE;
	}
	else
	{
		m_pSerialItem->m_bCirculate = FALSE;

	}

	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
