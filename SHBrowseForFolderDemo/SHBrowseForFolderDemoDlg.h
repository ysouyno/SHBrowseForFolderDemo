
// SHBrowseForFolderDemoDlg.h : header file
//

#pragma once


// CSHBrowseForFolderDemoDlg dialog
class CSHBrowseForFolderDemoDlg : public CDialogEx
{
// Construction
public:
	CSHBrowseForFolderDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SHBROWSEFORFOLDERDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTest();
};
