
// CustomSerialNumberTestDlg.h : ͷ�ļ�
//

#pragma once


// CCustomSerialNumberTestDlg �Ի���
class CCustomSerialNumberTestDlg : public CDialogEx
{
// ����
public:
	CCustomSerialNumberTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOMSERIALNUMBERTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	HMODULE h_module_;

	CString m_CurRuleName;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
