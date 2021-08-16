
// CustomSerialNumberTestDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCustomSerialNumberTestDlg 对话框



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
	ON_BN_CLICKED(IDC_BUTTON_Del, &CCustomSerialNumberTestDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_Get, &CCustomSerialNumberTestDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_Del3, &CCustomSerialNumberTestDlg::OnBnClickedButtonDel3)
	ON_BN_CLICKED(IDC_BUTTON_Del4, &CCustomSerialNumberTestDlg::OnBnClickedButtonDel4)
END_MESSAGE_MAP()


// CCustomSerialNumberTestDlg 消息处理程序

BOOL CCustomSerialNumberTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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
		AfxMessageBox(_T("加载CustomSerialNumber.dll 失败"));
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCustomSerialNumberTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCustomSerialNumberTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCustomSerialNumberTestDlg::OnBnClickedButtonAddormodify()
{
	SetCustomSerialNumber(("测试"));
}


void CCustomSerialNumberTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();


}


void CCustomSerialNumberTestDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	char* pData = GetCustomSerialNumber("测试", 1);
	if (pData == NULL)
		return;

	CString strData(pData);

	AfxMessageBox(strData);

	//获取内容成功后，一定要外部显示调用释放接口
	FreeMemory(pData);

	
}


void CCustomSerialNumberTestDlg::OnBnClickedButtonGet()
{

}


void CCustomSerialNumberTestDlg::OnBnClickedButtonDel3()
{
	DelCustomSerialNumber("测试");
}


void CCustomSerialNumberTestDlg::OnBnClickedButtonDel4()
{
	// TODO: 在此添加控件通知处理程序代码


	
	
}
