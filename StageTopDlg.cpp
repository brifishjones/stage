// StageTopDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageTopDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageTopDlg


CStageTopDlg::CStageTopDlg()
{
	return;
}

CStageTopDlg::~CStageTopDlg()
{
}


BEGIN_MESSAGE_MAP(CStageTopDlg, CDialogBar)
	//{{AFX_MSG_MAP(CStageTopDlg)
	ON_WM_HSCROLL()
	ON_COMMAND(IDC_PLAY, OnPlay)
	ON_COMMAND(IDC_PAUSE, OnPause)
	ON_COMMAND(IDC_REWIND, OnRewind)
	ON_UPDATE_COMMAND_UI(IDC_PLAY, OnUpdatePlayUI)
	ON_UPDATE_COMMAND_UI(IDC_PAUSE, OnUpdatePauseUI)
	ON_UPDATE_COMMAND_UI(IDC_REWIND, OnUpdateRewindUI)
	ON_UPDATE_COMMAND_UI(IDC_PLAYBACK_BACKGROUND, OnUpdatePlaybackBackgroundUI)
	ON_EN_KILLFOCUS(IDC_MINUTES, OnUpdateTime)
	ON_UPDATE_COMMAND_UI(IDC_MINUTES, OnUpdateMinutesUI)
	ON_UPDATE_COMMAND_UI(IDC_SECONDS, OnUpdateSecondsUI)
	ON_UPDATE_COMMAND_UI(IDC_FRAMES, OnUpdateFramesUI)
	ON_UPDATE_COMMAND_UI(IDC_TIME, OnUpdateTimeUI)
	ON_WM_CTLCOLOR()
	ON_EN_KILLFOCUS(IDC_SECONDS, OnUpdateTime)
	ON_EN_KILLFOCUS(IDC_FRAMES, OnUpdateTime)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStageTopDlg message handlers

void CStageTopDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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
	double timePos;
	int min;
	int sec;
	int frm;
	char s[64];
	static BOOL resumePlay = FALSE;

	if (pDoc->m_mode != YO_MODE_PLAY_SIM)
	{
		return;
	}

	if (pDoc->m_animationState == YO_PLAY)
	{
		pDoc->YoPause();
		resumePlay = TRUE;
	}
	else if (pDoc->m_animationState == YO_PAUSE)
	{
		CDialogBar::OnHScroll(nSBCode, nPos, pScrollBar);

		pCBox = (CComboBox*)GetDlgItem(IDC_TIME);
		timePos = (double)((CSliderCtrl *)pCBox)->GetPos();

		min = (int)(timePos / 60.0);
		sec = (int)timePos - (min * 60);

		if (pDoc->m_realTime == TRUE)
		{
			//frm = (int)((timePos
			//	- (double)((int)timePos)) * 100.0);
			frm = (int)((timePos
				- (double)((int)timePos)) * 100.0 * 0.5);
		}
		else
		{
			frm = (int)((timePos
				- (double)((int)timePos)) * pDoc->m_framesPerSecond);
		}
		
		sprintf(s, "%02d", min);
		pCBox = (CComboBox*)GetDlgItem(IDC_MINUTES);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%02d", sec);
		pCBox = (CComboBox*)GetDlgItem(IDC_SECONDS);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%02d", frm);
		pCBox = (CComboBox*)GetDlgItem(IDC_FRAMES);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

	}

	if (nSBCode == SB_ENDSCROLL)
	{
		//pDoc->m_currentCommand = pDoc->m_commandList;
		YoRewindFastForwardSim(timePos);

		if (resumePlay == TRUE)
		{
			OnPlay();
		}
		resumePlay = FALSE;
	}

	//OnUpdateTime();

	return;
}


void CStageTopDlg::OnUpdateTime()
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
	char s[64];
	int min;
	int sec;
	int frm;
	double timePos;

	if (pDoc->m_mode != YO_MODE_PLAY_SIM
		// prevent access to routine when called by framework
		|| pDoc->m_animationState == YO_PLAY)
	{
		return;
	}

	pCBox = (CComboBox*)GetDlgItem(IDC_MINUTES);
	memset(s, 0, 64);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%d", &min);
	pCBox = (CComboBox*)GetDlgItem(IDC_SECONDS);
	memset(s, 0, 64);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%d", &sec);
	pCBox = (CComboBox*)GetDlgItem(IDC_FRAMES);
	memset(s, 0, 64);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%d", &frm);

	if (pDoc->m_realTime == TRUE)
	{
		timePos = ((double)min * 60.0)
			+ (double)sec
			+ ((double)frm * .01);
	}
	else
	{
		timePos = ((double)min * 60.0)
			+ (double)sec
			+ ((double)frm / (double)pDoc->m_framesPerSecond);
	}

	TRACE3("CStageTopDlg::OnUpdateTime() %lf %lf %lf ",
		pDoc->m_timeCurrent, timePos, pDoc->m_timeEnd);
	TRACE3("%d %d %d\n", min, sec, frm);
	if (timePos + .0001 >= pDoc->m_timeCurrent
		&& timePos - .0001 <= pDoc->m_timeCurrent)
	{
		return;
	}

	pDoc->m_timeModified = TRUE;

	timePos = YO_MAX(timePos, 0.0);
	timePos = YO_MIN(timePos, pDoc->m_timeEnd);

	min = (int)(timePos / 60.0);
	sec = (int)timePos - (min * 60);
	if (pDoc->m_realTime == TRUE)
	{
		//frm = (int)((timePos
		//	- (double)((int)timePos)) * 100.0);
		frm = (int)((timePos
			- (double)((int)timePos)) * 100.0 + 0.5);
	}
	else
	{
		frm = (int)(((timePos
			- (double)((int)timePos))
			* (double)pDoc->m_framesPerSecond) + 0.5);
	}

	sprintf(s, "%02d", min);
	pCBox = (CComboBox*)GetDlgItem(IDC_MINUTES);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	sprintf(s, "%02d", sec);
	pCBox = (CComboBox*)GetDlgItem(IDC_SECONDS);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	sprintf(s, "%02d", frm);
	pCBox = (CComboBox*)GetDlgItem(IDC_FRAMES);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)GetDlgItem(IDC_TIME);
	((CSliderCtrl *)pCBox)->SetRange(0, (int)pDoc->m_timeEnd);
	((CSliderCtrl *)pCBox)->SetPos((int)timePos);

	YoRewindFastForwardSim(timePos);
	return;
}


void CStageTopDlg::OnPlay()
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
	CWnd* pCBox;

	if (pDoc->m_mode != YO_MODE_PLAY_SIM)
	{
		return;
	}

	//if (pDoc->m_motionEffectModified == TRUE
	//	|| pDoc->m_motionEffectModified == YO_MOTION_EFFECT_MODIFIED_ALL)
	//{
	//	pDoc->YoUpdateScore();
	//}
	//else if (pDoc->m_timeModified)
	//{
	//	pDoc->YoRestoreCurrentScore();
	//}

	pCBox = (CComboBox*)GetDlgItem(IDC_PLAY);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmPlayHL);
	pCBox->UpdateWindow();
	pCBox = (CComboBox*)GetDlgItem(IDC_PAUSE);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmPause);
	pCBox->UpdateWindow();
	pCBox = (CComboBox*)GetDlgItem(IDC_REWIND);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmRewind);
	pCBox->UpdateWindow();

	//pDoc->m_animationState = YO_PLAY;

	//pDoc->m_threadRender = AfxBeginThread(YoThreadPlay, pView);
	pDoc->YoMessage("");
	pDoc->m_animationState = YO_PLAY;
	//pDoc->YoPlay();
	//pDoc->m_threadRender = NULL;
	return;

}


void CStageTopDlg::OnPause()
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

	if (pDoc->m_mode != YO_MODE_PLAY_SIM)
	{
		return;
	}

	pDoc->YoPause();
	return;
}

void CStageTopDlg::OnRewind()
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

	if (pDoc->m_mode != YO_MODE_PLAY_SIM)
	{
		return;
	}

	sprintf(s, "Rewind...");
	pDoc->YoMessage(s);

	BeginWaitCursor();
	pDoc->YoRewind();
	EndWaitCursor();

	pDoc->YoMessage("");
	return;
}


void CStageTopDlg::OnUpdateMinutesUI(CCmdUI *pCmdUI)
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

	pCBox = (CComboBox*)GetDlgItem(IDC_MINUTES);
	if (pDoc->m_mode == YO_MODE_PLAY_SIM)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}


void CStageTopDlg::OnUpdateSecondsUI(CCmdUI *pCmdUI)
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

	pCBox = (CComboBox*)GetDlgItem(IDC_SECONDS);
	if (pDoc->m_mode == YO_MODE_PLAY_SIM)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}


void CStageTopDlg::OnUpdateFramesUI(CCmdUI *pCmdUI)
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

	pCBox = (CComboBox*)GetDlgItem(IDC_FRAMES);
	if (pDoc->m_mode == YO_MODE_PLAY_SIM)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}


void CStageTopDlg::OnUpdatePlaybackBackgroundUI(CCmdUI *pCmdUI)
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

	pCBox = (CComboBox*)GetDlgItem(IDC_PLAYBACK_BACKGROUND);
	if (pDoc->m_mode == YO_MODE_PLAY_SIM)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}


void CStageTopDlg::OnUpdatePlayUI(CCmdUI *pCmdUI)
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

	pCBox = (CComboBox*)GetDlgItem(IDC_PLAY);
	if (pDoc->m_mode == YO_MODE_PLAY_SIM)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}


void CStageTopDlg::OnUpdatePauseUI(CCmdUI *pCmdUI)
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

	pCBox = (CComboBox*)GetDlgItem(IDC_PAUSE);
	if (pDoc->m_mode == YO_MODE_PLAY_SIM)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}


void CStageTopDlg::OnUpdateRewindUI(CCmdUI *pCmdUI)
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

	pCBox = (CComboBox*)GetDlgItem(IDC_REWIND);
	if (pDoc->m_mode == YO_MODE_PLAY_SIM)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}


void CStageTopDlg::OnUpdateTimeUI(CCmdUI *pCmdUI)
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

	pCBox = (CComboBox*)GetDlgItem(IDC_TIME);
	if (pDoc->m_mode == YO_MODE_PLAY_SIM)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}

	return;
}


/***
void CStageTopDlg::OnImmediateMode()
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
	int nErrorCode;
	CWnd *pCBox;
	char s[128];



	if (pDoc->m_socket == NULL)
	{
		pDoc->YoSocketInit();
		//pCBox = (CComboBox*)GetDlgItem(IDC_IMMEDIATE_MODE);
		//((CButton *)pCBox)->SetBitmap((HBITMAP)pMainFrame->m_bmCircleYellow);
		//((CButton *)pCBox)->SetCheck(0);
		return;
	}

	if (pDoc->m_acceptSocket && pDoc->m_isMovement == 0)
	{
		//pCBox = (CComboBox*)GetDlgItem(IDC_IMMEDIATE_MODE);
		//((CButton *)pCBox)->SetCheck(0);
		if (AfxMessageBox("Current Connection will be closed", MB_OKCANCEL, 0) == IDOK)
		{
			pDoc->m_acceptSocket->OnClose(nErrorCode);
		}
		else
		{
			return;
		}
	}
	else if (pDoc->m_acceptSocket && pDoc->m_isMovement)
	{
		//pCBox = (CComboBox*)GetDlgItem(IDC_IMMEDIATE_MODE);
		//((CButton *)pCBox)->SetCheck(0);
		sprintf(s, "NO disconnect when devices in motion");
		pDoc->YoMessage(s);
		return;
	}

	pDoc->m_socket->OnClose(nErrorCode);
	//pCBox = (CComboBox*)GetDlgItem(IDC_IMMEDIATE_MODE);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)pMainFrame->m_bmCircleRed);

	//((CButton *)pCBox)->SetCheck(0);

	return;
}
/***

/***
void CStageTopDlg::OnUpdateImmediateModeUI(CCmdUI *pCmdUI)
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

	pCBox = (CComboBox*)GetDlgItem(IDC_IMMEDIATE_MODE);
	//if (pDoc->m_mode == YO_MODE_WORKCELL)
	//{
	//	pCBox->ShowWindow(SW_SHOW);
	//}
	//else
	{
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}
***/


void CStageTopDlg::YoRewindFastForwardSim(double timePos)
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
	char s[64];
	FILE *fp;

	pDoc->m_accumCount = 0;

	BeginWaitCursor();
	if (timePos < pDoc->m_timeCurrent)
	{
		if ((fp = fopen(pDoc->m_fileName, "r")) == NULL)
		{
			sprintf(s, "Cannot Rewind.  Unable to find file:\n   %s", pDoc->m_fileName);
			AfxMessageBox(s);
		}
		else
		{
			//fclose(fp);	
			sprintf(s, "Rewind...");
			pDoc->YoMessage(s);
			pView->YoRender(YO_RENDER_QUICK);
			pDoc->YoFreeWorkcell();
			if (pDoc->YoReadWorkcell(fp) == FALSE)
			{
				EndWaitCursor();
				fclose(fp);
				sprintf(s, "Error: Rewind failed while reading file.\nIncorrect file format or corrupt data encountered.");
				AfxMessageBox(s);
				pMainFrame->SendMessage(WM_COMMAND, ID_FILE_NEW, (LPARAM)0);
				return;
			}
			fclose(fp);
			pView->YoRender(YO_RENDER_QUICK);
		}
	}

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
	return;
}

HBRUSH CStageTopDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);
	
	//pDC->SetBkMode(TRANSPARENT);
	//pDC->SetBkMode(OPAQUE);
	//pDC->SetTextColor(RGB(128, 128, 128));
	//COLORREF cr = pDC->SetBkColor(0xFF0000);
		//cr = pDC->GetBkColor();
		//TRACE1("cr = %0x\n", cr);

		//CBrush   brBackground;
		//VERIFY(brBackground.CreateSolidBrush(PALETTERGB(255, 153, 255)));
		//return brBackground;
	

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

