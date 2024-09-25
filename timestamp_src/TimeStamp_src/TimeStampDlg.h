// TimeStampDlg.h : header file
//

#if !defined(AFX_TIMESTAMPDLG_H__27A2A63A_AE64_11D2_A96B_7A41B5000000__INCLUDED_)
#define AFX_TIMESTAMPDLG_H__27A2A63A_AE64_11D2_A96B_7A41B5000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BtnST.h"
#include "DropComboBox.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CTimeStampDlg dialog

class CTimeStampDlg : public CDialog
{
// Construction
public:
	CTimeStampDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeStampDlg)
	enum { IDD = IDD_TIMESTAMP_DIALOG };
	CSpinButtonCtrl	m_DaysSpin;
	CSpinButtonCtrl	m_MinsSpin;
	CSpinButtonCtrl	m_HrsSpin;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CButtonST	m_btnHelp;
	CDropComboBox	m_FileCombo;
	CButtonST	m_btnFileBrowse;
	CButtonST	m_btnDirBrowse;
	CButton     m_chkUseRelative;
	CString	m_strFile;
	int		m_nHours;
	int		m_nMins;
	int		m_nDays;
	BOOL    m_bUseRelative;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeStampDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CreateToolTips();
	void InitialiseButtons();
    void GetPrevSettings();
    void SaveCurrentSettings();
    void RecurseDirectories(CString& strDir);
    void StampFile(LPCTSTR szFile);

	HICON m_hIcon;
    CToolTipCtrl m_tooltip;
    CTime m_FileTime;
    UINT  m_nTimerID;

	// Generated message map functions
	//{{AFX_MSG(CTimeStampDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHelpBtn();
	afx_msg void OnBrowseFile();
	afx_msg void OnBrowseDir();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMESTAMPDLG_H__27A2A63A_AE64_11D2_A96B_7A41B5000000__INCLUDED_)
