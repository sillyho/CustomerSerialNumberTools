
// CustomSerialNumberTestDlg.h : 头文件
//

#pragma once


// CCustomSerialNumberTestDlg 对话框
class CCustomSerialNumberTestDlg : public CDialogEx
{
// 构造
public:
	CCustomSerialNumberTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOMSERIALNUMBERTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	HMODULE h_module_;

	CString m_CurRuleName;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddormodify();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonDel();
};
