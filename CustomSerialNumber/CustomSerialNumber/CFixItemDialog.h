#pragma once


// CFixItemDialog 对话框
#include "CFixedItem.h"
class CFixItemDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFixItemDialog)

public:
	CFixItemDialog(CFixedItem* ci, CWnd* pParent = nullptr);   // 标准构造函数

	virtual ~CFixItemDialog();

	CFixedItem* m_pFixedItem;
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FIX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};