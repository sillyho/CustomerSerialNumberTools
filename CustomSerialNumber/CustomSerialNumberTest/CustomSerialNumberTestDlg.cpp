
// CustomSerialNumberTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CustomSerialNumberTest.h"
#include "CustomSerialNumberTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


typedef void(*SETCUSTOMSERIALNUMBER)(const char* name);
typedef void(*DELCUSTOMSERIALNUMBER)(const char* name);
typedef char* (*GETCUSTOMSERIALNUMBER)(const char* name,int nloop);
typedef void(*FREEMEMORY)(void* p_addr);

SETCUSTOMSERIALNUMBER SetCustomSerialNumber;
DELCUSTOMSERIALNUMBER DelCustomSerialNumber;
GETCUSTOMSERIALNUMBER GetCustomSerialNumber;
FREEMEMORY FreeMemory;


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCustomSerialNumberTestDlg �Ի���



CCustomSerialNumberTestDlg::CCustomSerialNumberTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CUSTOMSERIALNUMBERTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomSerialNumberTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCustomSerialNumberTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_AddOrModify, &CCustomSerialNumberTestDlg::OnBnClickedButtonAddormodify)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_Get, &CCustomSerialNumberTestDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_Del, &CCustomSerialNumberTestDlg::OnBnClickedButtonDel)
END_MESSAGE_MAP()


// CCustomSerialNumberTestDlg ��Ϣ�������

BOOL CCustomSerialNumberTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	h_module_ = LoadLibraryW(_T("CustomSerialNumber.dll"));
	if (h_module_ != NULL)
	{

		SetCustomSerialNumber = (SETCUSTOMSERIALNUMBER)GetProcAddress(h_module_, "SetCustomSerialNumber");
		DelCustomSerialNumber = (DELCUSTOMSERIALNUMBER)GetProcAddress(h_module_, "DelCustomSerialNumber");
		GetCustomSerialNumber = (GETCUSTOMSERIALNUMBER)GetProcAddress(h_module_, "GetCustomSerialNumber");
		FreeMemory = (FREEMEMORY)GetProcAddress(h_module_, "FreeMemory");

	}
	else
	{
		AfxMessageBox(_T("����CustomSerialNumber.dll ʧ��"));
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCustomSerialNumberTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCustomSerialNumberTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCustomSerialNumberTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCustomSerialNumberTestDlg::OnBnClickedButtonAddormodify()
{
	if (SetCustomSerialNumber != NULL)
	{
		SetCustomSerialNumber(("����"));
	}
}


void CCustomSerialNumberTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();


}

void CCustomSerialNumberTestDlg::OnBnClickedButtonGet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (GetCustomSerialNumber != NULL)
	{
		char* pData = GetCustomSerialNumber("����", 1);
		if (pData == NULL)
			return;

		CString strData(pData);

		AfxMessageBox(strData);

		//��ȡ���ݳɹ���һ��Ҫ�ⲿ��ʾ�����ͷŽӿ�
		if (FreeMemory != NULL)
		{
			FreeMemory(pData);
		}
	}
}


void CCustomSerialNumberTestDlg::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (DelCustomSerialNumber != NULL)
	{
		DelCustomSerialNumber("����");
	}
}
