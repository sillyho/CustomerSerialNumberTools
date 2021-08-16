#pragma once
#include "CDateItem.h"

// CDateItemDialog 对话框

class CDateItemDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDateItemDialog)

public:
	CDateItemDialog(CDateItem* pDateItem, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDateItemDialog();

	CDateItem* m_pDateItem;

	int m_Row;
	int m_Col;
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();



	afx_msg void OnBnClickedRadioYear();
	afx_msg void OnBnClickedRadioMonth();
	afx_msg void OnBnClickedRadioDay();
	virtual BOOL OnInitDialog();
	CListCtrl m_LIstDate;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);

	CEdit m_InputEdit;
	afx_msg void OnEnKillfocusEditData();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
