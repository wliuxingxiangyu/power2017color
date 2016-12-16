// GreatTracerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GreatTracer.h"
#include "GreatTracerDlg.h"
#include "VIEWDLG.h"
#include "TX_PROPER_DIALOG.h"

CVIEWDLG *CVDLG=NULL;//view �Ի���ʵ��//����free		

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CGreatTracerDlg �Ի���




CGreatTracerDlg::CGreatTracerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGreatTracerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGreatTracerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, clc);//����Ԥ��  ���clc��ʵ������ʵ����listcontrol�����ݽ���
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


// CGreatTracerDlg ��Ϣ�������

BOOL CGreatTracerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	m_Menu.LoadMenu(IDR_MAIN_MENU);
	SetMenu(&m_Menu);
	//���ListControl����
	clc.InsertColumn( 0, "ID", LVCFMT_LEFT,40);// ������ 
	clc.InsertColumn( 1, "NAME", LVCFMT_LEFT, 50 );
	clc.InsertColumn(2,"X",LVCFMT_LEFT,40);
	clc.InsertColumn(3,"Y",LVCFMT_LEFT,40);
	clc.InsertColumn(4,"Z",LVCFMT_LEFT,40);
	//list��������
	int nRow = clc.InsertItem(0, "01");
	clc.SetItemText(nRow,1,"Tx");clc.SetItemText(nRow,2,"35");clc.SetItemText(nRow,3,"35");clc.SetItemText(nRow,4,"0");
	nRow=clc.InsertItem(1,"02");
	clc.SetItemText(nRow,1,"Rx");clc.SetItemText(nRow,2,"60");clc.SetItemText(nRow,3,"60");clc.SetItemText(nRow,4,"5");
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGreatTracerDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGreatTracerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGreatTracerDlg::OnViewProjectview()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
}
