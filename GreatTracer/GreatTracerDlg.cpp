// GreatTracerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GreatTracer.h"
#include "GreatTracerDlg.h"
#include "VIEWDLG.h"
#include "TX_PROPER_DIALOG.h"

CVIEWDLG *CVDLG=NULL;//view 对话框实例//不可free		

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGreatTracerDlg 对话框




CGreatTracerDlg::CGreatTracerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGreatTracerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGreatTracerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, clc);//高能预警  完成clc的实例化，实现与listcontrol的数据交换
}

BEGIN_MESSAGE_MAP(CGreatTracerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_VIEW_PROJECTVIEW, &CGreatTracerDlg::OnViewProjectview)
//	ON_COMMAND(ID_TEST, &CGreatTracerDlg::OnTest)
ON_COMMAND(ID_HELP_ABOUT, &CGreatTracerDlg::OnHelpAbout)
END_MESSAGE_MAP()


// CGreatTracerDlg 消息处理程序

BOOL CGreatTracerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	m_Menu.LoadMenu(IDR_MAIN_MENU);
	SetMenu(&m_Menu);
	//添加ListControl数据
	clc.InsertColumn( 0, "ID", LVCFMT_LEFT,40);// 插入列 
	clc.InsertColumn( 1, "NAME", LVCFMT_LEFT, 50 );
	clc.InsertColumn(2,"X",LVCFMT_LEFT,40);
	clc.InsertColumn(3,"Y",LVCFMT_LEFT,40);
	clc.InsertColumn(4,"Z",LVCFMT_LEFT,40);
	//list插入数据
	int nRow = clc.InsertItem(0, "01");
	clc.SetItemText(nRow,1,"Tx");clc.SetItemText(nRow,2,"35");clc.SetItemText(nRow,3,"35");clc.SetItemText(nRow,4,"0");
	nRow=clc.InsertItem(1,"02");
	clc.SetItemText(nRow,1,"Rx");clc.SetItemText(nRow,2,"60");clc.SetItemText(nRow,3,"60");clc.SetItemText(nRow,4,"5");
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGreatTracerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGreatTracerDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGreatTracerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGreatTracerDlg::OnViewProjectview()
{
	// TODO: 在此添加命令处理程序代码
	if(!CVDLG){
		CVDLG=new CVIEWDLG();
		CVDLG->Create(IDD_VIEW_DIALOG);
		CVDLG->ShowWindow(SW_NORMAL);
	}
	else if(CVDLG&&!CVDLG->IsWindowVisible()){
		CVDLG->ShowWindow(SW_NORMAL);
	}
}

void CGreatTracerDlg::OnHelpAbout()
{
	// TODO: 在此添加命令处理程序代码
}
