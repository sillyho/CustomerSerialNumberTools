#pragma once


#include "CSerialItem.h"
// CSerialItemDialog 对话框

class CSerialItemDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSerialItemDialog)

public:
	CSerialItemDialog(CSerialItem* pcs, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSerialItemDialog();

	CSerialItem* m_pSerialItem;
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERIAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
