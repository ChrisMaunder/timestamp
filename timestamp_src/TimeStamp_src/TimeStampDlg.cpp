// TimeStampDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimeStamp.h"
#include "TimeStampDlg.h"

#include "Dirdialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include "BtnST.h"
#include "HyperLink.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_HyperLink;
	CButtonST	m_OKBtn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_HYPER, m_HyperLink);
	DDX_Control(pDX, IDOK, m_OKBtn);
	//}}AFX_DATA_MAP
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_OKBtn.SetIcon( IDI_OK256 );
	m_OKBtn.SetActiveFgColor(RGB(0,0,200));

    m_HyperLink.SetURL(_T("http://www.codeproject.com/members/Chris-Maunder"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeStampDlg dialog

CTimeStampDlg::CTimeStampDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeStampDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeStampDlg)
	m_strFile = _T("");
	m_nHours = 0;
	m_nMins = 0;
	m_nDays = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_nTimerID = 1;
    m_bUseRelative = false;
}

void CTimeStampDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeStampDlg)
	DDX_Control(pDX, IDC_DAYSSPIN, m_DaysSpin);
	DDX_Control(pDX, IDC_MINSSPIN, m_MinsSpin);
	DDX_Control(pDX, IDC_HRSSPIN, m_HrsSpin);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_HELPBTN, m_btnHelp);
	DDX_Control(pDX, IDC_FILE, m_FileCombo);
	DDX_Control(pDX, IDC_BROWSE, m_btnFileBrowse);
	DDX_Control(pDX, IDC_DIR, m_btnDirBrowse);
	DDX_Check(pDX, IDC_USERELATIVE, m_bUseRelative);
	DDX_CBString(pDX, IDC_FILE, m_strFile);
	DDX_Text(pDX, IDC_HRSEDIT, m_nHours);
	DDX_Text(pDX, IDC_MINSEDIT, m_nMins);
	DDX_Text(pDX, IDC_DAYSEDIT, m_nDays);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimeStampDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeStampDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_HELPBTN, OnHelpBtn)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowseFile)
	ON_BN_CLICKED(IDC_DIR, OnBrowseDir)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeStampDlg message handlers

BOOL CTimeStampDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    m_FileCombo.SetMaxFiles(10);
   
	m_DaysSpin.SetRange(-10000, 10000);
	m_MinsSpin.SetRange(-300, 300);         // +/- 5hrs
	m_HrsSpin.SetRange(-72, 72);            // +/- 3 days

    GetPrevSettings();
	InitialiseButtons();
    CreateToolTips();

    m_nTimerID = SetTimer(m_nTimerID, 1000, NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimeStampDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	    OnHelpBtn();
	else
		CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimeStampDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimeStampDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTimeStampDlg::CreateToolTips()
{
    // Create the ToolTip control.
    m_tooltip.Create(this);
    
    m_tooltip.AddTool(GetDlgItem(IDC_FILE), IDS_CBOX_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_DIR), IDS_DIR_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_BROWSE), IDS_FILE_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDOK), IDS_CHECK_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDCANCEL), IDS_EXIT_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_HELPBTN), IDS_HELPBTN);
    m_tooltip.AddTool(GetDlgItem(IDC_DAYSEDIT), IDS_DAYS_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_HRSEDIT), IDS_HRS_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_MINSEDIT), IDS_MINS_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_USERELATIVE), IDS_USERELATIVE);
    
    m_tooltip.Activate(TRUE);
}

void CTimeStampDlg::InitialiseButtons()
{
	m_btnOK.SetIcon( IDI_OK256 );
	m_btnOK.SetActiveFgColor(RGB(0,0,200));

	m_btnCancel.SetIcon( IDI_CANCEL256 );
	m_btnCancel.SetActiveFgColor(RGB(0,0,200));

	m_btnHelp.SetIcon(IDI_HELP_ON, IDI_HELP_OFF); 
    m_btnDirBrowse.SetIcon( IDI_BROWSE256 );

	m_btnFileBrowse.SetIcon( IDI_FILE_OPEN );
	m_btnFileBrowse.SetActiveFgColor(RGB(0,0,200));
}

void CTimeStampDlg::GetPrevSettings()
{
    int nNumSaved = AfxGetApp()->GetProfileInt(_T("Settings"), _T("File Count"), 0);
    for (int i = 0; i < nNumSaved; i++)
    {
        CString strEntry, strFile;
        strEntry.Format(_T("File %d"), i);

        strFile = AfxGetApp()->GetProfileString(_T("Settings"), strEntry, _T(""));
        if (!i)
            m_strFile = strFile;
        if (CDropComboBox::Exist(strFile))
            m_FileCombo.AddString(strFile);
    }

	// restore the last selection
	int nSelection = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Selection"), -1);
	if (nSelection >= 0 && nSelection < m_FileCombo.GetCount())
    {
        m_FileCombo.SetCurSel(nSelection);
        m_FileCombo.GetLBText(nSelection, m_strFile);
    }

    m_nDays = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Days"), 0);
    m_nHours = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Hrs"), 0);
    m_nMins = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Mins"), 0);
    
    int value = AfxGetApp()->GetProfileInt(_T("Settings"), _T("UseRelative"), 0);
    m_bUseRelative = value == 1;

    int x = AfxGetApp()->GetProfileInt(_T("Settings"), _T("x"), -1);
    int y = AfxGetApp()->GetProfileInt(_T("Settings"), _T("y"), -1);
    if (x >= 0 && x < GetSystemMetrics(SM_CXSCREEN) &&
        y >= 0 && y < GetSystemMetrics(SM_CYSCREEN))
    {
        CRect rect;
        GetWindowRect(rect);
        rect.OffsetRect(x - rect.left, y - rect.top);
        MoveWindow(rect);
    }

    UpdateData(FALSE);
}

void CTimeStampDlg::SaveCurrentSettings()
{    
    UpdateData(TRUE);

    CRect rect;
    GetWindowRect(rect);

    int nNumSaved = m_FileCombo.GetCount();
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("File Count"), nNumSaved);
    for (int i = 0; i < nNumSaved; i++)
    {
        CString strEntry, strFile;
        strEntry.Format(_T("File %d"), i);
        m_FileCombo.GetLBText(i, strFile);
        AfxGetApp()->WriteProfileString(_T("Settings"), strEntry, strFile);
    }

	// save the last selection position
	int nSelection = m_FileCombo.GetCurSel();
	if (nSelection != -1)
	    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Selection"), nSelection);
	else
	{
		nSelection = m_FileCombo.FindString(0, m_strFile);
		AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Selection"), nSelection);
	}

    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Days"), m_nDays);
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Hrs"), m_nHours);
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Mins"), m_nMins);
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("UseRelative"), m_bUseRelative?1:0);

    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("x"), rect.left);
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("y"), rect.top);
}

void CTimeStampDlg::OnHelpBtn() 
{
    CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CTimeStampDlg::OnBrowseFile() 
{
    UpdateData(TRUE);

	CString strFilter = _T("All Files (*.*) |*.*||");

	CFileDialog	dlg(TRUE, NULL, m_strFile, OFN_HIDEREADONLY|OFN_EXPLORER, strFilter, NULL); 

	dlg.m_ofn.lpstrTitle = _T("Select file");

	if (dlg.DoModal() == IDOK) 
    {
		m_strFile = dlg.GetPathName();
        UpdateData(FALSE);
		m_FileCombo.SetEditSel(dlg.GetPathName().GetLength(), dlg.GetPathName().GetLength());
	}
}

void CTimeStampDlg::OnBrowseDir() 
{
    UpdateData(TRUE);

	CDirDialog dlg; 
	dlg.m_strTitle = _T("Choose directory");
	dlg.m_strSelDir = m_strFile;

	if (dlg.DoBrowse()) 
	{
		m_strFile = dlg.m_strPath;
		UpdateData(FALSE);
		m_FileCombo.SetEditSel(m_strFile.GetLength(), m_strFile.GetLength());
	}
}

BOOL CTimeStampDlg::PreTranslateMessage(MSG* pMsg) 
{
    // Let the ToolTip process this message.
	m_tooltip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CTimeStampDlg::OnCancel() 
{
	SaveCurrentSettings();
	CDialog::OnCancel();
}

void CTimeStampDlg::OnOK() 
{
    CWaitCursor wait;
    UpdateData(TRUE);

    m_strFile.TrimLeft(); m_strFile.TrimRight(); 

    if (m_strFile.IsEmpty())
    {
        MessageBox(_T("You must specify a file or directory"));
        return;
    }

    if (CDropComboBox::Exist(m_strFile))
    {
        m_FileCombo.PushString(m_strFile);
        m_FileCombo.SetWindowText(m_strFile);
    }

    m_btnOK.EnableWindow(FALSE);
    UpdateWindow();

    CTime time = CTime::GetCurrentTime();
    m_FileTime = time + CTimeSpan(m_nDays,m_nHours,m_nMins,0);

    if (CDropComboBox::IsDirectory(m_strFile))
        RecurseDirectories(m_strFile);
    else
        StampFile(m_strFile);

    m_btnOK.EnableWindow(TRUE);
}

void CTimeStampDlg::RecurseDirectories(CString& strDir)
{
    CString strFilter = strDir + _T("\\*.*");

    CFileFind finder;
    BOOL bWorking = finder.FindFile(strFilter);
    while (bWorking)
    {
        bWorking = finder.FindNextFile();
        
        if (!finder.IsDots())
        {
            if (finder.IsDirectory())
                RecurseDirectories(finder.GetFilePath());
            else
                StampFile(finder.GetFilePath());
        }
    }
}

void CTimeStampDlg::StampFile(LPCTSTR szFile)
{
    TRACE1("File is \"%s\"\n", szFile);
    
    if (strlen(szFile) > _MAX_PATH)
        return;

    CFileStatus fs;
    if (CFile::GetStatus(szFile, fs))
    {
        if (m_bUseRelative)
            fs.m_mtime = fs.m_mtime + CTimeSpan(m_nDays,m_nHours,m_nMins,0);
        else
            fs.m_mtime = m_FileTime;
            
        CFile::SetStatus(szFile, fs);
    }
}

void CTimeStampDlg::OnTimer(UINT nIDEvent) 
{
    ASSERT(m_nTimerID == nIDEvent);

    CString strTime = CTime::GetCurrentTime().Format(_T("%X"));
    SetDlgItemText(IDC_TIME, strTime);
}

BOOL CTimeStampDlg::DestroyWindow() 
{
    KillTimer(m_nTimerID);

	return CDialog::DestroyWindow();
}
