#pragma once
#include "SerializeTool.h"

// CObjectListDialog 对话框


class CObjectListDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectListDialog)

public:
	CObjectListDialog(CString Name, BOOL bNew, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CObjectListDialog();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETLIST };
#endif

	CString m_Name;
	BOOL m_bNew;
	CSerializeTool m_SerialTool;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitListControl();
	void UpdateIndex();

	CListCtrl m_ListCtrl;
	CMenu m_ListMenu;
	afx_msg void OnNMRClickListData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void onContextCmd(UINT ID);

	afx_msg void On1132780();
	afx_msg void OnBnClickedOk();
	afx_msg void On32781();
	afx_msg void On32782();
	afx_msg void On32783();
	afx_msg void On1132784();
};

