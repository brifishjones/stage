// StageScriptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageScriptDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageScriptDlg dialog


CStageScriptDlg::CStageScriptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageScriptDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageScriptDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageScriptDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageScriptDlg)
	DDX_Control(pDX, IDC_SCRIPT_EDIT, m_scriptEdit);
	DDX_Control(pDX, IDC_SCRIPT_LIST, m_scriptList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageScriptDlg, CDialog)
	//{{AFX_MSG_MAP(CStageScriptDlg)
	ON_BN_CLICKED(IDC_SCRIPT_SAVE_AS, OnScriptSaveAs)
	ON_BN_CLICKED(IDC_SCRIPT_SAVE, OnScriptSave)
	ON_BN_CLICKED(IDC_SCRIPT_REWIND, OnScriptRewind)
	ON_BN_CLICKED(IDC_SCRIPT_PAUSE_PLAY, OnScriptPausePlay)
	ON_BN_CLICKED(IDC_SCRIPT_OPEN, OnScriptOpen)
	ON_BN_CLICKED(IDC_SCRIPT_NEW, OnScriptNew)
	ON_BN_CLICKED(IDC_SCRIPT_LOOP, OnScriptLoop)
	ON_LBN_SETFOCUS(IDC_SCRIPT_LIST, OnSetfocusScriptList)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SCRIPT_PAUSE, OnScriptPause)
	ON_BN_CLICKED(IDC_SCRIPT_PLAY, OnScriptPlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageScriptDlg message handlers

void CStageScriptDlg::PostNcDestroy() 
{
	if (m_animationState != YO_PAUSE)
	{
		YoPause();
	}

	CDialog::PostNcDestroy();
	delete this;
}

BOOL CStageScriptDlg::YoInitDialog() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	CWnd *pCBox;

	m_init = TRUE;
	m_loop = FALSE;
	m_modeEdit = TRUE;
	m_animationState = YO_PAUSE;
	m_lineNumber = 0;
	//m_timeSleep = 0.0f;
	CDialog::OnInitDialog();

	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_REWIND);
	m_bmRewind.LoadBitmap(IDB_REWIND);
	pMainFrame->YoTransparentBitmap(&m_bmRewind, 0xff0000);
	((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmRewind);
	((CButton *)pCBox)->SetCheck(0);

	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PAUSE);
	m_bmPause.LoadBitmap(IDB_PAUSE);
	pMainFrame->YoTransparentBitmap(&m_bmPause, 0xff0000);
	((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmPause);
	((CButton *)pCBox)->SetCheck(1);

	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PLAY);
	m_bmPlay.LoadBitmap(IDB_PLAY);
	pMainFrame->YoTransparentBitmap(&m_bmPlay, 0xff0000);
	((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmPlay);
	((CButton *)pCBox)->SetCheck(0);

	//pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_LOOP);
	//m_bmLoop.LoadBitmap(IDB_LOOP);
	//m_bmLoopOn.LoadBitmap(IDB_LOOP_ON);
	//pMainFrame->YoTransparentBitmap(&m_bmLoop, 0xff0000);
	//pMainFrame->YoTransparentBitmap(&m_bmLoopOn, 0xff0000);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmLoop);
	((CButton *)pCBox)->SetCheck(0);
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageScriptDlg::YoRewind()
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}	
	FILE *fp;
	char s[256];
	CWnd *pCBox;
	int i;
	int j;
	int lineCount;

	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PLAY);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PAUSE);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_REWIND);
	((CButton *)pCBox)->SetCheck(1);

	//m_timeSleep = 0.0f;
	pDoc->YoEStop();
	m_animationState = YO_PAUSE;
	pDoc->YoMessage("");

	if ((fp = fopen(pDoc->m_fileName, "r")) == NULL)
	{
		sprintf(s, "Cannot Rewind.  Unable to find file:\n   %s", pDoc->m_fileName);
		AfxMessageBox(s);
	}
	else
	{
		pDoc->YoFreeWorkcell();
		if (pDoc->YoReadWorkcell(fp) == FALSE)
		{
			fclose(fp);
			sprintf(s, "Error: Rewind failed while reading file.\nIncorrect file format or corrupt data encountered.");
			AfxMessageBox(s);
			SendMessage(WM_COMMAND, ID_FILE_NEW, (LPARAM)0);
		}
		else
		{
			fclose(fp);
			pMainFrame->RedrawWindow();
		}
	}

	if (m_modeEdit == TRUE)
	{
		m_modeEdit = FALSE;
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_EDIT);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_LIST);
		pCBox->ShowWindow(SW_SHOW);
		m_scriptList.ResetContent();
		lineCount = m_scriptEdit.GetLineCount();

		for (i = 0; i < lineCount; i++)
		{
			memset(s, 0, 256);
			m_scriptEdit.GetLine(i, s, 256);

			for (j = 0; (j < 255) && (s[j] != '\r') && (s[j] != '\n') && (s[j] != 0); j++);
			s[j] = '\0';
			if (s[0] != '\0')
			{
				m_scriptList.AddString(CString(s));
			}
		}
		//m_lineNumber = 0;
		this->RedrawWindow();
	}

	m_lineNumber = 0;
	pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_LIST);
	((CListBox *)pCBox)->SetCurSel(0);

	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PLAY);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PAUSE);
	((CButton *)pCBox)->SetCheck(1);
	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_REWIND);
	((CButton *)pCBox)->SetCheck(0);

	return;
}


void CStageScriptDlg::YoPause()
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	int i;

				if (pDoc->m_mode == YO_MODE_RECORD_SIM
				//&& pDoc->m_commandList != NULL
				&& pView->m_fp != NULL)
			{
				pMainFrame->OnModeRecordSim();
				//::GetSystemTime(&gmTimeEnd);
				//timeEnd = gmTimeEnd;
				//timeStart = m_pDoc->m_commandList->m_gmTime;
				//spanSec = timeEnd - timeStart;
				//tms = gmTimeEnd.wMilliseconds - m_pDoc->m_commandList->m_gmTime.wMilliseconds;
				//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
				//m_pDoc->m_timeEnd = (GLint)(m_pDoc->m_framesPerSecond * timeElapsed);
			}

	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PLAY);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PAUSE);
	((CButton *)pCBox)->SetCheck(1);
	pCBox->SetFocus();
	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_REWIND);
	((CButton *)pCBox)->SetCheck(0);

	//m_timeSleep = 0.0f;
	pDoc->YoEStop();
	m_animationState = YO_PAUSE;
	i = m_scriptEdit.LineIndex(m_lineNumber);
	m_scriptEdit.SetSel(i, i + 1, TRUE);
	pDoc->m_resumeMove = FALSE;
	if (pDoc->m_camera != NULL)
	{
		pDoc->m_camera->m_enabled = FALSE;
		pDoc->m_camera = NULL;
	}


	return;
}

void CStageScriptDlg::YoPlay()
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];
	char command[64];
	int lineCount;
	BOOL done = FALSE;
	double timeElapsed;
	double timeSleep;
	SYSTEMTIME gmTimeCurrent;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	int tms;
	CTimeSpan spanSec;

	TRACE0("CStageScriptDlg::YoPlay()\n");

	//if (pDoc->m_isMovement)
	//{
	//	return;
	//}

	lineCount = m_scriptEdit.GetLineCount();

	if ((lineCount = m_scriptList.GetCount()) <= 0)
	// note that m_scriptList.GetCount() may return a different value
	// than m_scriptEdit.GetLineCount()
	{
		YoPause();
		return;
	}

	m_animationState = YO_PLAY;

	::GetSystemTime(&gmTimeCurrent);
	timeCurrent = gmTimeCurrent;
	timeStart = pDoc->m_gmTimeStart;
	spanSec = timeCurrent - timeStart;
	tms = gmTimeCurrent.wMilliseconds - pDoc->m_gmTimeStart.wMilliseconds;
	timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0)
		+ m_timeSleepFastForward;// - m_timeFastForward;

	TRACE3("YoPlay(): timeElapsed = %.3lf   m_timeSleepTotal = %.3lf   m_timeSleepFastForward = %.3lf\n",
		timeElapsed, pDoc->m_timeSleepTotal, m_timeSleepFastForward);

	if (timeElapsed > pDoc->m_timeSleepTotal)
	{
		timeElapsed = pDoc->m_timeSleepTotal;
	}

	pDoc->m_gmTime = pDoc->m_gmTimeStart;
	pDoc->YoChangeTime(&pDoc->m_gmTime, timeElapsed - m_timeFastForward);

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	if (timeElapsed < pDoc->m_timeSleepTotal)
	{
		return;
	}

	if (m_lineNumber < lineCount)
	{
		memset(s, 0, 256);
		m_scriptList.SetCurSel(m_lineNumber);
		m_scriptList.GetText(m_lineNumber, s);

		sscanf(s, "%s", command);
		TRACE3("%d:%d: %s\n", m_lineNumber, lineCount, s);

		if (strcmp(command, "-sleep") == 0)
		{
			sscanf(s, "%*s %lf", &timeSleep);
			pDoc->m_timeSleepTotal += fabs(timeSleep);
			m_lineNumber++;
			if (m_lineNumber >= 20 && m_lineNumber % 20 == 0)
			{
				m_scriptList.SetTopIndex(m_lineNumber - 2);
			}
		}
		else
		{
			while (done == FALSE)
			{
				if (pDoc->YoHandleCommand(s) == FALSE)
				{
					YoPause();
					break;
				}

				m_lineNumber++;
				if (m_lineNumber >= 20 && m_lineNumber % 20 == 0)
				{
					m_scriptList.SetTopIndex(m_lineNumber - 2);
				}

				if (m_loop == TRUE && m_lineNumber >= lineCount)
				{
					m_lineNumber = 0;
				}
				else if (m_lineNumber >= lineCount)
				{
					YoPause();
					break;
				}

				memset(s, 0, 256);
				m_scriptList.SetCurSel(m_lineNumber);
				m_scriptList.GetText(m_lineNumber, s);
				sscanf(s, "%s", command);
				if (strcmp(command, "-sleep") == 0)
				{
					done = TRUE;
				}
			}

		}

		//if (pDoc->m_isMovement)
		//{
		//	pDoc->YoMove();
		//}
		//((CStageView *)pView)->YoRender(YO_RENDER_LIGHT);
		//((CStageView *)pView)->YoRender(YO_RENDER_FULL);

		//if (i + 1 == lineCount)
		//{
		//	YoPause();
		//}
	}

	else if (m_loop == FALSE && m_lineNumber >= lineCount)
	{
		YoPause();
	}

	else if (m_loop == TRUE && m_lineNumber >= lineCount)
	{
		m_lineNumber = 0;
	}

	else if (pDoc->m_isMovement)
	{
		pDoc->YoMove();

	}

	else
	{
		YoPause();
	}

	return;
}

BOOL CStageScriptDlg::YoReadScript(LPCTSTR lpszPathName) 
{
	int i;
	char s[256];
	FILE *fp;
	int ch = 0;
	char command[32];
	BOOL done = FALSE;
	BOOL init = FALSE;
	
	m_scriptEdit.SetWindowText("");


	if ((fp = fopen((char *)lpszPathName, "r")) == NULL)
	{
		return FALSE;
	}

	while(!done)
	{
		// Read in single line from file
		memset(s, 0, 256);
		for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\r';
			s[i + 1] = '\n';
		}

		sscanf(s, "%s", command);

		if (init == FALSE && strcmp(command, "STAGE_SCRIPT") != 0)
		{
			// not a stage script file
			fclose(fp);
			return FALSE;
		}
		else
		{
			init = TRUE;
		}

		if (strcmp(command, "NULL") == 0)
		{
			fclose(fp);
			done = TRUE;
		}
		else if (strcmp(command, "STAGE_SCRIPT") != 0)
		{
			m_scriptEdit.SetSel(-1, 0, TRUE);
			m_scriptEdit.ReplaceSel(s);
		}
	}

	return TRUE;
}


BOOL CStageScriptDlg::YoWriteScript(LPCTSTR lpszPathName)
{
	int i;
	int j;
	char s[256];
	FILE *fp;
	int ch = 0;
	BOOL done = FALSE;
	
	if ((fp = fopen((char *)lpszPathName, "w")) == NULL)
	{
		return FALSE;
	}

	memset(s, 0, 256);
	fprintf(fp, "STAGE_SCRIPT\n");

	for (i = 0; i < m_scriptEdit.GetLineCount(); i++)
	{
		memset(s, 0, 256);
		m_scriptEdit.GetLine(i, s, 256);

		for (j = 0; (j < 255) && (s[j] != '\r') && (s[j] != '\n') && (s[j] != 0); j++);
		s[j] = '\0';
		if (s[0] != '\0')
		{
			fprintf(fp, "%s\n", s);
		}
	}
	
	fprintf(fp, "NULL");
	fclose(fp);
	return TRUE;
}


void CStageScriptDlg::OnScriptSaveAs() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];

	YoPause();

	CFileDialog saveAsScript
		(FALSE,    // save
		NULL,    // no default extension
		NULL,    // file name
		OFN_HIDEREADONLY,
		//"Stage Script files (*.SCP)|*.SCP|All files (*.*)|*.*||");
		"All files (*.*)|*.*|Stage Script files (*.SCP)|*.SCP||");


	saveAsScript.m_ofn.lpstrTitle = "Save As...";

	if (saveAsScript.DoModal() == IDOK)
	{
		sprintf(s, "%s", (LPCSTR)saveAsScript.GetPathName());
		if (YoWriteScript(s) == TRUE)
		{
			sprintf(pDoc->m_scriptName, "%s", (LPCSTR)saveAsScript.GetPathName());
			SetWindowText((LPCSTR)pDoc->m_scriptName);
		}
		else
		{
			sprintf(s, "Error saving script file.\nUnable to write data to file.");
			AfxMessageBox(s);
		}
	}

	return;	
}

void CStageScriptDlg::OnScriptSave() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];

	YoPause();

	if (strcmp(pDoc->m_scriptName, "") == 0)
	{
		CFileDialog saveAsScript
			(FALSE,    // save
			NULL,    // no default extension
			NULL,    // file name
			OFN_HIDEREADONLY,
			//"Stage Script files (*.SCP)|*.SCP|All files (*.*)|*.*||");
			"All files (*.*)|*.*|Stage Script files (*.SCP)|*.SCP||");

		saveAsScript.m_ofn.lpstrTitle = "Save...";

		if (saveAsScript.DoModal() == IDOK)
		{
			sprintf(s, "%s", (LPCSTR)saveAsScript.GetPathName());
			if (YoWriteScript(s) == TRUE)
			{
				sprintf(pDoc->m_scriptName, "%s", (LPCSTR)saveAsScript.GetPathName());
				SetWindowText((LPCSTR)pDoc->m_scriptName);
			}
			else
			{
				sprintf(s, "Error saving script file.\nUnable to write data to file.");
				AfxMessageBox(s);
			}
		}
	}
	else
	{
		if (YoWriteScript((LPCSTR)pDoc->m_scriptName) == FALSE)
		{
			sprintf(s, "Error saving script file.\nUnable to write data to file.");
			AfxMessageBox(s);
		}
	}

	return;		
}

void CStageScriptDlg::OnScriptRewind() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	TRACE0("CStageScriptDlg::OnScriptRewind()\n");

	if (strcmp(pDoc->m_fileName, "") == 0)
	{
		YoPause();
		AfxMessageBox("Please save main workcell file before proceeding");
		return;
	}
	else if (pDoc->m_mode == YO_MODE_RECORD_SIM)
	// needed because OnScriptRewind() message is somehow triggered--can't figure out why it is called
	{
		return;
	}
	//else if (m_scriptEdit.GetLineCount() <= 0)
	//{
	//	YoPause();
	//	return;
	//}

	BeginWaitCursor();
	YoRewind();
	m_scriptEdit.SetSel(0, 0, FALSE);
	EndWaitCursor();

	return;
}

void CStageScriptDlg::OnScriptPausePlay() 
{
	/***
	if (m_animationState == YO_PLAY)
	{
		YoPause();
	}
	else
	{
		YoPlay();
	}
	***/
	return;
}

void CStageScriptDlg::OnScriptOpen() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[256];

	YoPause();

	if (m_modeEdit == FALSE)
	{
		m_modeEdit = TRUE;
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_LIST);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_EDIT);
		pCBox->ShowWindow(SW_SHOW);
		this->RedrawWindow();
	}

	// choose a script file
	CFileDialog chooseScript
		(TRUE,    // open
		NULL,    // no default extension
		NULL,    // file name
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		//"Stage Script files (*.SCP)|*.SCP|All files (*.*)|*.*||");
		"All files (*.*)|*.*|Stage Script files (*.SCP)|*.SCP||");

	chooseScript.m_ofn.lpstrTitle = "Open...";

	if (chooseScript.DoModal() == IDOK)
	{
		m_lineNumber = 0;
		pDoc->m_timeSleepTotal = 0.0;
		sprintf(s, "%s", (LPCSTR)chooseScript.GetPathName());
		if (YoReadScript(s) == TRUE)
		{
			sprintf(pDoc->m_scriptName, "%s", (LPCSTR)chooseScript.GetPathName());
			SetWindowText((LPCSTR)pDoc->m_scriptName);
			m_scriptEdit.SetSel(0, 0, TRUE);
		}
		else
		{
			sprintf(s, "Error reading script file.\nIncorrect file format or corrupt data encountered.");
			AfxMessageBox(s);
		}
	}

	return;
}

void CStageScriptDlg::OnScriptNew() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];
	CWnd *pCBox;

	YoPause();

	if (m_modeEdit == FALSE)
	{
		m_modeEdit = TRUE;
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_LIST);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_EDIT);
		pCBox->ShowWindow(SW_SHOW);
		this->RedrawWindow();
	}

	sprintf(pDoc->m_scriptName, "");
	sprintf(s, "");
	pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_EDIT);
	pCBox->SetWindowText(s);
	SetWindowText("Untitled");
	return;
}

void CStageScriptDlg::OnScriptLoop() 
{
	CWnd *pCBox;

	if (m_loop)
	{
		m_loop = FALSE;
		pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_LOOP);
		//((CButton * )pCBox)->SetBitmap((HBITMAP)m_bmLoop);
		((CButton * )pCBox)->SetCheck(0);
	}
	else
	{
		m_loop = TRUE;
		pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_LOOP);
		//((CButton * )pCBox)->SetBitmap((HBITMAP)m_bmLoopOn);
		((CButton * )pCBox)->SetCheck(1);
	}
}

void CStageScriptDlg::OnSetfocusScriptList() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	int listTopLine;
	int editTopLine;

	if (m_modeEdit == FALSE)
	{
		YoPause();
		m_modeEdit = TRUE;
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_LIST);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_EDIT);
		pCBox->ShowWindow(SW_SHOW);

		// return to the same place in edit mode as last command executed in list
		listTopLine = m_scriptList.GetTopIndex();
		editTopLine = m_scriptEdit.GetFirstVisibleLine();
		m_scriptEdit.LineScroll(listTopLine - editTopLine, 0);
		//m_scriptEdit.SetSel(-1, 0, TRUE);

		this->RedrawWindow();
	}

	return;
}

void CStageScriptDlg::OnClose() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}

	TRACE0("CStageScriptDlg::OnClose()\n");
	YoPause();
	pMainFrame->m_wndDlgScriptVisible = FALSE;
	::SetActiveWindow(pMainFrame->m_hWnd);

	CDialog::OnClose();
}

void CStageScriptDlg::OnScriptPause() 
{

	YoPause();
	return;	
}

void CStageScriptDlg::OnScriptPlay() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	int nStartChar;
	int nEndChar;
	int i;
	int j;
	int lineCount;
	int nErrorCode;
	char s[256];
	SYSTEMTIME gmTimeCurrent;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	int tms;
	CTimeSpan spanSec;

	TRACE0("CStageScriptDlg::OnScriptPlay()\n");


	if (strcmp(pDoc->m_fileName, "") == 0)
	{
		YoPause();
		AfxMessageBox("Please save main workcell file before proceeding");
		return;
	}

	if (pDoc->m_acceptSocket)
	{
		pDoc->m_acceptSocket->OnClose(nErrorCode);
		pDoc->m_acceptSocket = NULL;
	}
	if (pDoc->m_socket)
	{
		pDoc->m_socket->OnClose(nErrorCode);
		pDoc->m_socket = NULL;
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_CONNECT);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_LISTEN);
		pCBox->ShowWindow(SW_HIDE);
		//pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_MODE_SOCKET);
		//((CButton *)pCBox)->SetBitmap((HBITMAP)pMainFrame->m_bmCircleRed);
	}

	if (m_modeEdit == TRUE)
	{
		m_modeEdit = FALSE;
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_EDIT);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCRIPT_LIST);
		pCBox->ShowWindow(SW_SHOW);
		m_scriptList.ResetContent();
		lineCount = m_scriptEdit.GetLineCount();

		for (i = 0; i < lineCount; i++)
		{
			memset(s, 0, 256);
			m_scriptEdit.GetLine(i, s, 256);

			for (j = 0; (j < 255) && (s[j] != '\r') && (s[j] != '\n') && (s[j] != 0); j++);
			s[j] = '\0';
			if (s[0] != '\0')
			{
				m_scriptList.AddString(CString(s));
			}
		}
		//m_lineNumber = 0;
		this->RedrawWindow();
	}

	m_scriptEdit.GetSel(nStartChar, nEndChar);
	m_lineNumber = m_scriptEdit.LineFromChar(nEndChar);
	m_timeSleepFastForward = 0.0;
	m_timeFastForward = 0.0;

	if (m_lineNumber > 0)
	{
		if (YoRewindFastForwardSim() == FALSE)
		{
			return;
		}

		m_timeSleepFastForward = pDoc->m_timeSleepTotal;
		::GetSystemTime(&gmTimeCurrent);
		timeCurrent = gmTimeCurrent;
		timeStart = pDoc->m_gmTimeStart;
		spanSec = timeCurrent - timeStart;
		tms = gmTimeCurrent.wMilliseconds - pDoc->m_gmTimeStart.wMilliseconds;
		m_timeFastForward = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0) - 0.001;
	}

	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PLAY);
	((CButton *)pCBox)->SetCheck(1);
	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PAUSE);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_REWIND);
	((CButton *)pCBox)->SetCheck(0);

	pDoc->YoMessage("");

	::GetSystemTime(&pDoc->m_gmTimeStart);
	if (m_lineNumber == 0)
	{
		pDoc->m_gmTime = pDoc->m_gmTimeStart;
	}

	YoPlay();

	return;		
}

BOOL CStageScriptDlg::YoRewindFastForwardSim()
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}	
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	char s[256];
	char command[64];
	FILE *fp;
	CWnd *pCBox;
	double timeSleep;
	int lineNumber;


	//m_timeSleep = 0.0f;
	pDoc->YoEStop();
	m_animationState = YO_PAUSE;
	pDoc->YoMessage("");

	if ((fp = fopen(pDoc->m_fileName, "r")) == NULL)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PLAY);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PAUSE);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_REWIND);
		((CButton *)pCBox)->SetCheck(0);

		sprintf(s, "Cannot Rewind.  Unable to find file:\n   %s", pDoc->m_fileName);
		AfxMessageBox(s);
		return FALSE;
	}
	else
	{
		pDoc->YoFreeWorkcell();
		if (pDoc->YoReadWorkcell(fp) == FALSE)
		{
			fclose(fp);
			pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PLAY);
			((CButton *)pCBox)->SetCheck(0);
			pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_PAUSE);
			((CButton *)pCBox)->SetCheck(1);
			pCBox = (CComboBox*)GetDlgItem(IDC_SCRIPT_REWIND);
			((CButton *)pCBox)->SetCheck(0);

			sprintf(s, "Error: Rewind failed while reading file.\nIncorrect file format or corrupt data encountered.");
			AfxMessageBox(s);
			SendMessage(WM_COMMAND, ID_FILE_NEW, (LPARAM)0);
			return FALSE;
		}
		else
		{
			fclose(fp);
			pView->YoRender(YO_RENDER_QUICK);
		}
	}

	sprintf(s, "Fast Forward...");
	pDoc->YoMessage(s);
	pDoc->m_scriptFastForward = TRUE;
	::GetSystemTime(&pDoc->m_gmTimeStart);
	pDoc->m_gmTime = pDoc->m_gmTimeStart;

	for (lineNumber = 0; lineNumber < m_lineNumber; lineNumber++)
	{
		memset(s, 0, 256);
		m_scriptList.GetText(lineNumber, s);

		sscanf(s, "%s", command);
		if (strcmp(command, "-sleep") == 0)
		{
			sscanf(s, "%*s %lf", &timeSleep);
			pDoc->m_timeSleepTotal += fabs(timeSleep);
			pDoc->m_gmTime = pDoc->m_gmTimeStart;
			pDoc->YoChangeTime(&pDoc->m_gmTime, pDoc->m_timeSleepTotal);
		}
		else
		{
			if (pDoc->m_isMovement)
			{
				// adjust m_gmTime to make sure motion is completed
				// before executing next command after a -sleep
				//pDoc->m_timeSleepTotal += 1.0;
				pDoc->YoMove();
				//pDoc->m_timeSleepTotal -= 1.0;
			}
			pView->YoRender(YO_RENDER_QUICK);
			// 100 ms is an arbitrary value that is close to the render time
			// during normal playback
			//pDoc->YoChangeTime(&pDoc->m_gmTime, 0.1);
			TRACE3("m_gmTime(%d %d): %s\n", pDoc->m_gmTime.wSecond, pDoc->m_gmTime.wMilliseconds, s);
			if (pDoc->YoHandleCommand(s) == FALSE)
			{
				YoPause();
				m_scriptList.SetCurSel(lineNumber);
				return FALSE;
			}
		}

		if (pDoc->m_isMovement)
		{
			pDoc->YoMove();
		}
	}

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	pDoc->m_scriptFastForward = FALSE;

/***
		if (timePos >= pDoc->m_timeCurrent
		&& timePos < pDoc->m_timeEnd)
	{
		sprintf(s, "Fast Forward...");
		pDoc->YoMessage(s);
		for (;
			pDoc->m_currentCommand != NULL && pDoc->m_currentCommand->m_time <= timePos;
			pDoc->m_currentCommand = pDoc->m_currentCommand->m_next)
		{
			if (pDoc->m_currentCommand != pDoc->m_commandList)
			{
				pDoc->m_timeCurrent = pDoc->m_currentCommand->m_time - 0.05;
				if (pDoc->m_isMovement)
				{
					pDoc->YoMove();
				}
				pView->YoRender(YO_RENDER_QUICK);
				//pView->YoRender(YO_RENDER_FULL);
			}
			pDoc->m_timeCurrent = pDoc->m_currentCommand->m_time;
			pDoc->YoHandleCommand(pDoc->m_currentCommand->m_buf);
			TRACE2("%.3lf: %s\n", pDoc->m_currentCommand->m_time, pDoc->m_currentCommand->m_buf);
			if (pDoc->m_isMovement)
			{
				pDoc->YoMove();
			}
			//pView->YoRender(YO_RENDER_LIGHT);
			//pView->YoRender(YO_RENDER_FULL);
		}
		pDoc->m_timeCurrent = timePos;
		if (pDoc->m_isMovement)
		{
			pDoc->YoMove();
		}
	}
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	pDoc->YoMessage("");
	EndWaitCursor();



	if (lineNumber >= m_lineNumber)
	{
		sprintf(s, "Fast Forward...");
		pDoc->YoMessage(s);

		memset(s, 0, 256);
		m_scriptList.SetCurSel(m_lineNumber);
		m_scriptList.GetText(m_lineNumber, s);

		sscanf(s, "%s", command);
		if (strcmp(command, "-sleep") == 0)
		{
			::GetSystemTime(&m_gmTimeSleepStart);
			sscanf(s, "%*s %lf", &m_timeSleep);
		}
		else
		{
			pDoc->YoHandleCommand(s);
		}
		TRACE1("%s\n", s);

		if (pDoc->m_isMovement)
		{
			pDoc->YoMove();
			//if (::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_NOREMOVE))
			//{
			//	YoPause();
			//	break;
			//}
		}
		//if (::PeekMessage(&msg, ((CWnd*)this)->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_NOREMOVE))
		//{
		//	break;
		//}	
		m_lineNumber++;

		//((CStageView *)pView)->YoRender(YO_RENDER_LIGHT);
		//((CStageView *)pView)->YoRender(YO_RENDER_FULL);

		//if (i + 1 == lineCount)
		//{
		//	YoPause();
		//}

			if (pDoc->m_currentCommand != pDoc->m_commandList)
			{
				pDoc->m_timeCurrent = pDoc->m_currentCommand->m_time - 0.05;
				if (pDoc->m_isMovement)
				{
					pDoc->YoMove();
				}
				pView->YoRender(YO_RENDER_QUICK);
				//pView->YoRender(YO_RENDER_FULL);
			}
			pDoc->m_timeCurrent = pDoc->m_currentCommand->m_time;
			pDoc->YoHandleCommand(pDoc->m_currentCommand->m_buf);
			TRACE2("%.3lf: %s\n", pDoc->m_currentCommand->m_time, pDoc->m_currentCommand->m_buf);
			if (pDoc->m_isMovement)
			{
				pDoc->YoMove();
			}
			//pView->YoRender(YO_RENDER_LIGHT);
			//pView->YoRender(YO_RENDER_FULL);

		pDoc->m_timeCurrent = timePos;
		if (pDoc->m_isMovement)
		{
			pDoc->YoMove();
		}
	}
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	pDoc->YoMessage("");
	EndWaitCursor();
	**/
	return TRUE;
}
