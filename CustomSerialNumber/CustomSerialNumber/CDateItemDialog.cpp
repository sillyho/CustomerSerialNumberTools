// CDateItemDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "CDateItemDialog.h"
#include "afxdialogex.h"
#include<string>
#include<iostream>
#include <vector>
#include<algorithm>
#include "resource.h"
using namespace std;

// CDateItemDialog 对话框

IMPLEMENT_DYNAMIC(CDateItemDialog, CDialogEx)

CDateItemDialog::CDateItemDialog(CDateItem* pDateItem, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DATE, pParent)
{
	m_pDateItem = pDateItem;


}

CDateItemDialog::~CDateItemDialog()
{
}

void CDateItemDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_LIstDate);
	DDX_Control(pDX, IDC_EDIT_DATA, m_InputEdit);
}


BEGIN_MESSAGE_MAP(CDateItemDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDateItemDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_YEAR, &CDateItemDialog::OnBnClickedRadioYear)
	ON_BN_CLICKED(IDC_RADIO_MONTH, &CDateItemDialog::OnBnClickedRadioMonth)
	ON_BN_CLICKED(IDC_RADIO_DAY, &CDateItemDialog::OnBnClickedRadioDay)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDateItemDialog::OnBnClickedButtonSave)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDateItemDialog::OnNMDblclkList1)

	ON_EN_KILLFOCUS(IDC_EDIT_DATA, &CDateItemDialog::OnEnKillfocusEditData)
END_MESSAGE_MAP()


// CDateItemDialog 消息处理程序


void CDateItemDialog::OnBnClickedOk()
{
	if (IsDlgButtonChecked(IDC_RADIO_YEAR) == BST_CHECKED)
	{
		m_pDateItem->TypeDate = DateType::Year;
	}
	if (IsDlgButtonChecked(IDC_RADIO_MONTH) == BST_CHECKED)
	{
		m_pDateItem->TypeDate = DateType::Month;
	}
	else if (IsDlgButtonChecked(IDC_RADIO_DAY) == BST_CHECKED)
	{
		m_pDateItem->TypeDate = DateType::Day;
	}

	
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CDateItemDialog::OnBnClickedRadioYear()
{
	m_LIstDate.DeleteAllItems();

	int nColCount = m_LIstDate.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColCount; i++)
	{
		m_LIstDate.DeleteColumn(0);
	}
	// TODO: 在此添加控件通知处理程序代码
	m_LIstDate.InsertColumn(0, _T("年份"), LVCFMT_LEFT, 50);
	m_LIstDate.InsertColumn(1, _T("值"), LVCFMT_LEFT, 100);
	m_LIstDate.SetExtendedStyle(m_LIstDate.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	POSITION po = m_pDateItem->m_DateMapYear.GetStartPosition();
	int TmpKey = 0;
	CString TmpValue = _T("");
	int iIndex = 0;
	CString strTemp;
	vector<int> vectorYear;
	while (po)
	{
		m_pDateItem->m_DateMapYear.GetNextAssoc(po, TmpKey, TmpValue);
		vectorYear.push_back(TmpKey);
	}
	sort(vectorYear.begin(), vectorYear.end());
	for (vector<int>::iterator it = vectorYear.begin(); it != vectorYear.end(); it++)
	{
		strTemp.Format(_T("%d"), *it);
		m_LIstDate.InsertItem(iIndex, strTemp);
		m_pDateItem->m_DateMapYear.Lookup(*it, strTemp);
		m_LIstDate.SetItemText(iIndex, 1, strTemp);

		iIndex++;
	}

}


void CDateItemDialog::OnBnClickedRadioMonth()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LIstDate.DeleteAllItems();

	int nColCount = m_LIstDate.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColCount; i++)
	{
		m_LIstDate.DeleteColumn(0);
	}
	// TODO: 在此添加控件通知处理程序代码
	m_LIstDate.InsertColumn(0, _T("月份"), LVCFMT_LEFT, 50);
	m_LIstDate.InsertColumn(1, _T("值"), LVCFMT_LEFT, 100);
	m_LIstDate.SetExtendedStyle(m_LIstDate.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	POSITION po = m_pDateItem->m_DateMapMonth.GetStartPosition();
	int TmpKey = 0;
	CString TmpValue = _T("");
	int iIndex = 0;
	CString strTemp;
	vector<int> vectorYear;
	while (po)
	{
		m_pDateItem->m_DateMapMonth.GetNextAssoc(po, TmpKey, TmpValue);
		vectorYear.push_back(TmpKey);
	}
	sort(vectorYear.begin(), vectorYear.end());
	for (vector<int>::iterator it = vectorYear.begin(); it != vectorYear.end(); it++)
	{
		strTemp.Format(_T("%d"), *it);
		m_LIstDate.InsertItem(iIndex, strTemp);
		m_pDateItem->m_DateMapMonth.Lookup(*it, strTemp);
		m_LIstDate.SetItemText(iIndex, 1, strTemp);


		iIndex++;
	}


}


void CDateItemDialog::OnBnClickedRadioDay()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	m_LIstDate.DeleteAllItems();

	int nColCount = m_LIstDate.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColCount; i++)
	{
		m_LIstDate.DeleteColumn(0);
	}
	// TODO: 在此添加控件通知处理程序代码
	m_LIstDate.InsertColumn(0, _T("日"), LVCFMT_LEFT, 50);
	m_LIstDate.InsertColumn(1, _T("值"), LVCFMT_LEFT, 100);
	m_LIstDate.SetExtendedStyle(m_LIstDate.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	POSITION po = m_pDateItem->m_DateMapDay.GetStartPosition();
	int TmpKey = 0;
	CString TmpValue = _T("");
	int iIndex = 0;
	CString strTemp;
	vector<int> vectorYear;
	while (po)
	{
		m_pDateItem->m_DateMapDay.GetNextAssoc(po, TmpKey, TmpValue);
		vectorYear.push_back(TmpKey);
	}
	sort(vectorYear.begin(), vectorYear.end());
	for (vector<int>::iterator it = vectorYear.begin(); it != vectorYear.end(); it++)
	{
		strTemp.Format(_T("%d"), *it);
		m_LIstDate.InsertItem(iIndex, strTemp);
		m_LIstDate.SetItemText(iIndex, 0, strTemp);

		m_pDateItem->m_DateMapDay.Lookup(*it, strTemp);
		m_LIstDate.SetItemText(iIndex, 1, strTemp);


		iIndex++;
	}
}


BOOL CDateItemDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();



	if (m_pDateItem->TypeDate == DateType::Year)
	{
		CheckDlgButton(IDC_RADIO_YEAR, BST_CHECKED);
		
		OnBnClickedRadioYear();
	}
	else if (m_pDateItem->TypeDate == DateType::Month)
	{
		CheckDlgButton(IDC_RADIO_MONTH, BST_CHECKED);

		OnBnClickedRadioMonth();
	}
	else if (m_pDateItem->TypeDate == DateType::Day)
	{
		CheckDlgButton(IDC_RADIO_DAY, BST_CHECKED);

		OnBnClickedRadioDay();
	}
	// TODO:  在此添加额外的初始化
	m_InputEdit.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDateItemDialog::OnBnClickedButtonSave()
{
	if (IsDlgButtonChecked(IDC_RADIO_YEAR) == BST_CHECKED)
	{
		m_pDateItem->TypeDate = DateType::Year;	m_pDateItem->m_DateMapYear.RemoveAll();
	}
	if (IsDlgButtonChecked(IDC_RADIO_MONTH) == BST_CHECKED)
	{
		m_pDateItem->TypeDate = DateType::Month; m_pDateItem->m_DateMapMonth.RemoveAll();
	}
	else if (IsDlgButtonChecked(IDC_RADIO_DAY) == BST_CHECKED)
	{
		m_pDateItem->TypeDate = DateType::Day; m_pDateItem->m_DateMapDay.RemoveAll();
	}


	int nCount = m_LIstDate.GetItemCount();
	CString strKey, strValue;
	for (int i = 0; i < nCount; i++)
	{
		if (m_pDateItem->TypeDate == DateType::Year)
		{
			m_pDateItem->m_DateMapYear.SetAt(_ttoi(m_LIstDate.GetItemText(i, 0)), m_LIstDate.GetItemText(i, 1));
		}
		else if (m_pDateItem->TypeDate == DateType::Month)
		{
			m_pDateItem->m_DateMapMonth.SetAt(_ttoi(m_LIstDate.GetItemText(i, 0)), m_LIstDate.GetItemText(i, 1));
		}
		else if (m_pDateItem->TypeDate == DateType::Day)
		{
			m_pDateItem->m_DateMapDay.SetAt(_ttoi(m_LIstDate.GetItemText(i, 0)), m_LIstDate.GetItemText(i, 1));
		}
	}

}


void CDateItemDialog::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码




	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//获得选中的行  
	m_Col = pNMListView->iSubItem;//获得选中列  


	if (pNMListView->iSubItem == 1 && m_Col == 1) //如果选择的是子项;  
	{
		m_LIstDate.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；  
		m_InputEdit.SetParent(&m_LIstDate);//转换坐标为列表框中的坐标  
		m_InputEdit.MoveWindow(rc);//移动Edit到RECT坐在的位置;  
		m_InputEdit.SetWindowText(m_LIstDate.GetItemText(m_Row, m_Col));//将该子项中的值放在Edit控件中；  
		m_InputEdit.ShowWindow(SW_SHOW);//显示Edit控件；  
		m_InputEdit.SetFocus();//设置Edit焦点  
		m_InputEdit.ShowCaret();//显示光标  
		m_InputEdit.SetSel(-1);//将光标移动到最后  
	}

	*pResult = 0;

}





void CDateItemDialog::OnEnKillfocusEditData()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tem;
	m_InputEdit.GetWindowText(tem);    //得到用户输入的新的内容  
	m_LIstDate.SetItemText(m_Row, m_Col, tem);   //设置编辑框的新内容  
	m_InputEdit.ShowWindow(SW_HIDE);

}


BOOL CDateItemDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)//捕捉回车
	{
		if (GetFocus() != GetDlgItem(IDC_EDIT_DATA))
		{
			return  FALSE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
