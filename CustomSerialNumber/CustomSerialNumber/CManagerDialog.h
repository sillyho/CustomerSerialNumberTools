#pragma once


// CManagerDialog 对话框

class CManagerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CManagerDialog)

public:
	CManagerDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CManagerDialog();
public:
	CString strSelectRule;
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MANAGER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedOk();
	void RefreshRules();
	CListCtrl m_listCtrl;
};
