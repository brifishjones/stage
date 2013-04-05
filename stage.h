// stage.h : main header file for the STAGE application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "gl\gl.h"
#include "gl\glu.h"
#include "gl\glaux.h"
#include "math.h"
#include "float.h"
#include "string.h"

/////////////////////////////////////////////////////////////////////////////
// CStageApp:
// See stage.cpp for the implementation of this class
//

class CStageApp : public CWinApp
{
public:
	CStageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
	BOOL m_init;
		// Server object for document creation

	//{{AFX_MSG(CStageApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
