// TimeStamp.h : main header file for the TIMESTAMP application
//

#if !defined(AFX_TIMESTAMP_H__27A2A638_AE64_11D2_A96B_7A41B5000000__INCLUDED_)
#define AFX_TIMESTAMP_H__27A2A638_AE64_11D2_A96B_7A41B5000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTimeStampApp:
// See TimeStamp.cpp for the implementation of this class
//

class CTimeStampApp : public CWinApp
{
public:
	CTimeStampApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeStampApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTimeStampApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMESTAMP_H__27A2A638_AE64_11D2_A96B_7A41B5000000__INCLUDED_)
