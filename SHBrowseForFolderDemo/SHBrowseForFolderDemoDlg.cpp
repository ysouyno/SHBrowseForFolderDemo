
// SHBrowseForFolderDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SHBrowseForFolderDemo.h"
#include "SHBrowseForFolderDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSHBrowseForFolderDemoDlg dialog




CSHBrowseForFolderDemoDlg::CSHBrowseForFolderDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSHBrowseForFolderDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSHBrowseForFolderDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSHBrowseForFolderDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CSHBrowseForFolderDemoDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()


// CSHBrowseForFolderDemoDlg message handlers

BOOL CSHBrowseForFolderDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSHBrowseForFolderDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSHBrowseForFolderDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSHBrowseForFolderDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
	TCHAR sz[MAX_PATH] = {0};
	GetClassName(hwnd, sz, MAX_PATH);

	if (_tcsicmp(sz, L"SHBrowseForFolder ShellNameSpace Control") == 0)
	{
		CRect *parent_rect = (CRect *)lParam;
		CRect rect;
		GetClientRect(hwnd, &rect);
		rect.top = parent_rect->right * 0.049 * 2;
		rect.left = parent_rect->right * 0.049;
		rect.right = parent_rect->right - rect.left * 2;
		rect.bottom = parent_rect->bottom - parent_rect->bottom * 0.3;
		::MoveWindow(hwnd, rect.left, rect.top, rect.right, rect.bottom, TRUE);
		return FALSE;
	}

	return TRUE;
}

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
	{
		CRect rect;
		GetClientRect(hwnd, &rect);
		EnumChildWindows(hwnd, EnumChildProc, (LPARAM)&rect);

		HWND text_hwnd = ::GetDlgItem(hwnd, 0x3742);
		if (text_hwnd)
		{
			::MoveWindow(text_hwnd, 0, 0, 1, 1, TRUE);
		}
	}

	return 0;
}

void CSHBrowseForFolderDemoDlg::OnBnClickedButtonTest()
{
	// TODO: Add your control notification handler code here
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.ulFlags = BIF_NEWDIALOGSTYLE;
	bi.hwndOwner = this->GetSafeHwnd();
	bi.lpfn = BrowseCallbackProc;

	LPMALLOC pmalloc;
	TCHAR sz[MAX_PATH] = {0};

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (NULL != pidl)
	{
		SHGetPathFromIDList(pidl, sz);
		AfxMessageBox(sz);
		if (SUCCEEDED(SHGetMalloc(&pmalloc)))
		{
			pmalloc->Free(pidl);
			pmalloc->Release();
		}
	}
}
