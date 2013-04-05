// stage.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "stage.h"

#include "MainFrm.h"
#include "IpFrame.h"
#include "stageDoc.h"
#include "stageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageApp

BEGIN_MESSAGE_MAP(CStageApp, CWinApp)
	//{{AFX_MSG_MAP(CStageApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageApp construction

CStageApp::CStageApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CStageApp object

CStageApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {AC3DF5A0-6281-11D1-883A-3C8B00C10000}
static const CLSID clsid =
{ 0xac3df5a0, 0x6281, 0x11d1, { 0x88, 0x3a, 0x3c, 0x8b, 0x0, 0xc1, 0x0, 0x0 } };

/////////////////////////////////////////////////////////////////////////////
// CStageApp initialization

BOOL CStageApp::InitInstance()
{
	m_init = FALSE;

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CStageDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CStageView));
	pDocTemplate->SetServerInfo(
		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
		RUNTIME_CLASS(CInPlaceFrame));
	AddDocTemplate(pDocTemplate);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
		// Note: SDI applications register server objects only if /Embedding
		//   or /Automation is present on the command line.

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
		COleTemplateServer::RegisterAll();

		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_INPLACE_SERVER);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_init = TRUE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CStageApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CStageApp commands

BOOL CStageApp::OnIdle(LONG lCount) 
{
	if (m_init == FALSE)
	{
		CWinApp::OnIdle(lCount);
	}

	CWnd *pWnd = GetMainWnd( );
	CView *pView = ((CMainFrame *)pWnd)->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	static long i = 0;
	if (i % 1000 == 0)
	{
		TRACE2("%ld: CStageApp::OnIdle(%ld)\n", i, lCount);
		TRACE2(     "m_animationState = %d   m_timeCurrent = %lf\n",
			pDoc->m_animationState, pDoc->m_timeCurrent);
	}
	i++;

	/***
	if (pDoc->m_isMovement && pView->GetCapture() != pView
		&& pDoc->m_mode != YO_MODE_PLAY_SIM)
	{
		pDoc->YoMove();
	}
	else if (pDoc->m_isMovement && pDoc->m_mode == YO_MODE_PLAY_SIM
		&& pDoc->m_animationState == YO_PLAY)
	{
		pDoc->YoPlay();
	}


	if (pDoc->m_resumeMove == TRUE && pView->GetCapture() != pView
		&& pDoc->m_mode != YO_MODE_PLAY_SIM)
	{
		pDoc->m_resumeMove = FALSE;
		pDoc->YoMove();      
	}
	else if (pDoc->m_resumeMove == TRUE && pDoc->m_mode == YO_MODE_PLAY_SIM
		&& pDoc->m_animationState == YO_PLAY)
	{
		pDoc->m_resumeMove = FALSE;
		TRACE1("CStageApp::OnIdle pDoc->m_resumeMove = %d (before YoPlay)\n", pDoc->m_resumeMove);
		pDoc->YoPlay();
		TRACE1("CStageApp::OnIdle pDoc->m_resumeMove = %d (after YoPlay)\n", pDoc->m_resumeMove);
	}
	***/

	return CWinApp::OnIdle(lCount); 
}

	
