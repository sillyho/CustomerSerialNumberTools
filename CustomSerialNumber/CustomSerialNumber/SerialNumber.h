#pragma once


// CSerialNumber 对话框

class CSerialNumber : public CDialogEx
{
	DECLARE_DYNAMIC(CSerialNumber)

public:
	CSerialNumber(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSerialNumber();

public:
	// 规则名称
	CString serial_name_;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CustomSerialNumber };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
