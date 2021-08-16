// CObjectListDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "CObjectListDialog.h"
#include "afxdialogex.h"
#include "CFixItemDialog.h"
#include "CSerialItemDialog.h"
#include "CDateItemDialog.h"
#include "resource.h"
// CObjectListDialog 对话框





IMPLEMENT_DYNAMIC(CObjectListDialog, CDialogEx)

CObjectListDialog::CObjectListDialog(CString Name, BOOL bNew, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETLIST, pParent)
{
	m_Name = Name;
	m_bNew = bNew;
}

CObjectListDialog::~CObjectListDialog()
{
}

void CObjectListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Data, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CObjectListDialog, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_Data, &CObjectListDialog::OnNMRClickListData)
	ON_COMMAND(ID_11_32780, &CObjectListDialog::On1132780)
	ON_BN_CLICKED(IDOK, &CObjectListDialog::OnBnClickedOk)
	ON_COMMAND(ID_32781, &CObjectListDialog::On32781)
	ON_COMMAND(ID_32782, &CObjectListDialog::On32782)
	ON_COMMAND(ID_32783, &CObjectListDialog::On32783)
	ON_COMMAND(ID_11_32784, &CObjectListDialog::On1132784)
END_MESSAGE_MAP()


// CObjectListDialog 消息处理程序


BOOL CObjectListDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListMenu.LoadMenuW(IDR_MENU1);

	InitListControl();
	SetDlgItemText(IDC_EDIT_NAME, m_Name);
	GetDlgItem(IDC_EDIT_NAME)->EnableWindow(FALSE);
	if (!m_bNew)
	{
		//加载列表
		if (!CSerializeTool::LoadRule(m_Name, m_SerialTool))
		{
			MessageBoxW(_T("加载规则失败!"), _T("失败"), MB_OK | MB_ICONERROR);
		}
		else
		{
			CString strTemp;
			for (int i = 0; i < m_SerialTool.m_arrItems.GetCount(); i++)
			{
				strTemp.Format(_T("%d"), i + 1);
				m_ListCtrl.InsertItem(i, strTemp);

				if (m_SerialTool.m_arrItems[i]->Type == ItemType::Fixed)
					strTemp.Format(_T("%s"), _T("固定文本"));
				else if (m_SerialTool.m_arrItems[i]->Type == ItemType::SerialNumber)
					strTemp.Format(_T("%s"), _T("序列号"));
				else if (m_SerialTool.m_arrItems[i]->Type == ItemType::Date)
					strTemp.Format(_T("%s"), _T("日期"));

				m_ListCtrl.SetItemText(i, 1, strTemp);

				strTemp.Format(_T("%s"), m_SerialTool.m_arrItems[i]->ToString());
				m_ListCtrl.SetItemText(i, 2, strTemp);

				m_ListCtrl.SetHotItem(i);
				m_ListCtrl.EnsureVisible(i, TRUE);
			}
		}

	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CObjectListDialog::InitListControl()
{
	m_ListCtrl.InsertColumn(0, _T("索引"), LVCFMT_LEFT, 50);
	m_ListCtrl.InsertColumn(1, _T("类型"), LVCFMT_LEFT, 100);
	m_ListCtrl.InsertColumn(2, _T("内容"), LVCFMT_LEFT, 200);
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVIS_SELECTED | LVS_EX_FULLROWSELECT);

}
void CObjectListDialog::UpdateIndex()
{
	int nCount = m_ListCtrl.GetItemCount();
	CString strTemp;
	for (int i = 0; i < nCount; i++)
	{
		strTemp.Format(_T("%d"), i + 1);
		m_ListCtrl.SetItemText(i, 0, strTemp);

		m_ListCtrl.SetHotItem(i);
		m_ListCtrl.EnsureVisible(i, TRUE);
	}
}

void CObjectListDialog::OnNMRClickListData(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CPoint ptCurSel(0, 0);
	GetCursorPos(&ptCurSel);
	//转换为当前控件坐标系的坐标
	m_ListCtrl.ScreenToClient(&ptCurSel);
	LVHITTESTINFO HitTestInfo;
	HitTestInfo.pt = ptCurSel;
	//判断坐标命中第几项
	//int nItem = m_ListCtrl.HitTest(&HitTestInfo);

	//if (nItem != -1)
	//{
	CMenu* nMenu = m_ListMenu.GetSubMenu(0);
	POINT pos;
	GetCursorPos(&pos);
	nMenu->TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);
	//} 


	*pResult = 0;
}

void CObjectListDialog::onContextCmd(UINT ID)
{





}


void CObjectListDialog::On1132780()
{
	// TODO: 在此添加命令处理程序代码
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	int nItem = m_ListCtrl.GetNextSelectedItem(pos);
	if (nItem == -1)
	{
		return;
	}
	m_ListCtrl.DeleteItem(nItem);
	m_SerialTool.m_arrItems.RemoveAt(nItem);

}


void CObjectListDialog::OnBnClickedOk()
{
	//1 判定文件名是否正确
	CString Name;
	GetDlgItemText(IDC_EDIT_NAME, Name);
	if (Name == _T(""))
	{
		MessageBox(_T("请输入规则名称!"), _T("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	if (Name.FindOneOf(_T("//")) >= 0 || Name.FindOneOf(_T("\\")) >= 0 || Name.FindOneOf(_T(":")) >= 0 || Name.FindOneOf(_T("*")) >= 0
		|| Name.FindOneOf(_T(">")) >= 0 || Name.FindOneOf(_T("<")) >= 0 || Name.FindOneOf(_T("?")) >= 0 || Name.FindOneOf(_T("\"")) >= 0)
	{
		MessageBox(_T("规则名称存在非法字符!"), _T("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	if (CSerializeTool::IsExistRule(Name))
	{
		if (MessageBox(_T("已经存在，是否覆盖保存?"), _T("提示"), MB_ICONEXCLAMATION | MB_YESNO) != IDYES)
		{
			return;
		}

	}
	if (CSerializeTool::SaveRule(Name, m_SerialTool))
	{
		MessageBox(_T("保存成功!"), _T("成功"), MB_OK);
		CDialogEx::OnOK();
	}
	else
	{
		MessageBox(_T("保存失败!"), _T("失败"), MB_OK | MB_ICONERROR);
	}
	// TODO: 在此添加控件通知处理程序代码

}


void CObjectListDialog::On32781()
{
	// TODO: 在此添加命令处理程序代码
	CFixedItem* pcd = new CFixedItem();
	CFixItemDialog  cfd(pcd);
	CString strIndex;
	int nCount = m_ListCtrl.GetItemCount();
	if (cfd.DoModal() == IDOK)
	{
		strIndex.Format(_T("%d"), nCount + 1);
		m_ListCtrl.InsertItem(nCount, strIndex);
		m_ListCtrl.SetItemText(nCount, 1, _T("固定文本"));
		m_ListCtrl.SetItemText(nCount, 2, pcd->Value);
		m_SerialTool.AddItem(pcd);

	}
}


void CObjectListDialog::On32782()
{
	// TODO: 在此添加命令处理程序代码
	//新建序列号
	CSerialItem* pcs = new CSerialItem(_T("0123456789"), 3, _T("001"), _T("001"), _T("999"), FALSE);
	CSerialItemDialog  cfd(pcs);
	CString strIndex;
	int nCount = m_ListCtrl.GetItemCount();
	if (cfd.DoModal() == IDOK)
	{
		strIndex.Format(_T("%d"), nCount + 1);
		m_ListCtrl.InsertItem(nCount, strIndex);
		m_ListCtrl.SetItemText(nCount, 1, _T("序列号"));
		m_ListCtrl.SetItemText(nCount, 2, pcs->ToString());
		m_SerialTool.AddItem(pcs);
	}
}


void CObjectListDialog::On32783()
{
	// TODO: 在此添加命令处理程序代码
	//日期类型
	CDateItem* pcd = new CDateItem(DateType::Year);
	CDateItemDialog cid(pcd);
	CString strIndex;
	int nCount = m_ListCtrl.GetItemCount();
	if (cid.DoModal() == IDOK)
	{
		strIndex.Format(_T("%d"), nCount + 1);
		m_ListCtrl.InsertItem(nCount, strIndex);
		m_ListCtrl.SetItemText(nCount, 1, _T("日期"));
		m_ListCtrl.SetItemText(nCount, 2, pcd->ToString());
		m_SerialTool.AddItem(pcd);
	}


}


void CObjectListDialog::On1132784()
{
	// TODO: 在此添加命令处理程序代码
	//修改
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	int nItem = m_ListCtrl.GetNextSelectedItem(pos);
	if (nItem == -1)
	{
		return;
	}
	CString strType = m_ListCtrl.GetItemText(nItem, 1);
	if (strType == _T("固定文本"))
	{

		CFixItemDialog  cfd(((CFixedItem*)((m_SerialTool.m_arrItems.ElementAt(nItem)))));
		CString strIndex;
		int nCount = m_ListCtrl.GetItemCount();
		if (cfd.DoModal() == IDOK)
		{
			m_ListCtrl.SetItemText(nItem, 2, (m_SerialTool.m_arrItems.ElementAt(nItem))->Value);
		}
	}
	else if (strType == _T("序列号"))
	{
		CSerialItemDialog  cfd(((CSerialItem*)((m_SerialTool.m_arrItems.ElementAt(nItem)))));
		CString strIndex;
		int nCount = m_ListCtrl.GetItemCount();
		if (cfd.DoModal() == IDOK)
		{
			m_ListCtrl.SetItemText(nItem, 2, ((CSerialItem*)((m_SerialTool.m_arrItems.ElementAt(nItem))))->ToString());
		}
	}
	else if (strType == _T("日期"))
	{
		CDateItemDialog cid(((CDateItem*)((m_SerialTool.m_arrItems.ElementAt(nItem)))));
		CString strIndex;
		int nCount = m_ListCtrl.GetItemCount();
		if (cid.DoModal() == IDOK)
		{
			m_ListCtrl.SetItemText(nItem, 2, ((CDateItem*)((m_SerialTool.m_arrItems.ElementAt(nItem))))->ToString());

		}
	}

}
