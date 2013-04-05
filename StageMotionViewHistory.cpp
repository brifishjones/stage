// StageMotionViewHistory.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageMotionViewHistory.h"
#include "stageDoc.h"
#include "stageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageMotionViewHistory dialog


CStageMotionViewHistory::CStageMotionViewHistory(CWnd* pParent /*=NULL*/)
	: CDialog(CStageMotionViewHistory::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStageMotionViewHistory)
	//}}AFX_DATA_INIT
}


void CStageMotionViewHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageMotionViewHistory)
	DDX_Control(pDX, IDC_EYE_MOTION_LIST, m_motionList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageMotionViewHistory, CDialog)
	//{{AFX_MSG_MAP(CStageMotionViewHistory)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_CLEAR_ALL, OnClearAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageMotionViewHistory message handlers

BOOL CStageMotionViewHistory::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	
	// TODO: Add extra initialization here
	//LPCTSTR lpszItem = "device";

	CStageEyeMotion *ptrEyeMotion = pDoc->m_eyeList->m_motion;
	char s[128];
	char t[4];

	m_motionList.ResetContent();

    while (ptrEyeMotion != NULL)
    {
		if (ptrEyeMotion->m_type == YO_MOTION_ANCHOR)
		{
			sprintf(t, "A"); 
		}
		else
		{
			sprintf(t, "H");
		}
		sprintf(s,
		"%02d:%02d:%02d     (%5.1f, %5.1f, %5.1f)  (%5.1f, %5.1f, %5.1f)     fov: %3.1f   %s", 
		ptrEyeMotion->m_time / (60 * pDoc->m_framesPerSecond),
		(ptrEyeMotion->m_time % (60 * pDoc->m_framesPerSecond)) / pDoc->m_framesPerSecond, 
		(ptrEyeMotion->m_time % (60 * pDoc->m_framesPerSecond)) % pDoc->m_framesPerSecond, 
		ptrEyeMotion->m_eye[0], ptrEyeMotion->m_eye[1], ptrEyeMotion->m_eye[2],
		ptrEyeMotion->m_eye[3], ptrEyeMotion->m_eye[4], ptrEyeMotion->m_eye[5], 
		ptrEyeMotion->m_fieldOfView, t);

		m_motionList.AddString(s);
		ptrEyeMotion = ptrEyeMotion->m_next;
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageMotionViewHistory::OnRemove() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStageEyeMotion *ptrMotion;
	int i = 0;
	int j = m_motionList.GetCount();
	GLint min;
	GLint sec;
	GLint frm;
	GLint t;
	char s[128];
	char *p;

	while (i < j)
	{
		if (m_motionList.GetSel(i))
		{
			m_motionList.GetText(i, s);
			sscanf(s, "%d", &min);
			p = &s[3];
			sscanf(p, "%d", &sec);
			p = &s[6];
			sscanf(p, "%d", &frm);
			//sscanf(s, "%d  *%s %d *%s %d", &min, &sec, &frm);
			t = (min * 60 * pDoc->m_framesPerSecond)
				+ (sec * pDoc->m_framesPerSecond)
				+ frm;

			ptrMotion = pDoc->m_eyeList->m_motion;
			while (ptrMotion != NULL && t != 0)
			{
				if (t == ptrMotion->m_time)
				{
					// flag motion for removal
					ptrMotion->m_time = -ptrMotion->m_time;
					ptrMotion = NULL;
				}
				else
				{
					ptrMotion = ptrMotion->m_next;
				}
			}

			m_motionList.DeleteString(i);
			j--;
		}
		else
		{
			i++;
		}
	}
	return;
	
}

void CStageMotionViewHistory::OnClearAll() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	pDoc->m_eyeList->m_motion->m_time = INT_MAX;
	m_motionList.ResetContent();
	return;
	
}

void CStageMotionViewHistory::OnOK() 
{
	// TODO: Add extra validation here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStageEyeMotion *ptrMotion = pDoc->m_eyeList->m_motion;
	CStageEyeMotion *prevMotion = pDoc->m_eyeList->m_motion;

	
	while (ptrMotion != NULL)
    {
		// clear all is selected
		if (ptrMotion->m_time == INT_MAX
			&& ptrMotion == pDoc->m_eyeList->m_motion)
		{
			while (ptrMotion != NULL)
			{
				prevMotion = ptrMotion->m_next;
				delete (ptrMotion);
				ptrMotion = prevMotion;
			}
			pDoc->m_eyeList->m_motion = NULL;
			pDoc->m_motionEffectModified = TRUE;
			return;
		}
		// node is tagged for delete
		else if (ptrMotion->m_time < 0)
		{
			prevMotion->m_next = ptrMotion->m_next;
			delete (ptrMotion);
			ptrMotion = prevMotion->m_next;
			pDoc->m_motionEffectModified = TRUE;
		}
		else
		{
			prevMotion = ptrMotion;
			ptrMotion = ptrMotion->m_next;
		}
	}
	CDialog::OnOK();
	return;
}

void CStageMotionViewHistory::OnCancel() 
{
	// TODO: Add extra cleanup here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStageEyeMotion *ptrMotion = pDoc->m_eyeList->m_motion;

	
	while (ptrMotion != NULL)
    {
		if (ptrMotion->m_time == INT_MAX
			&& ptrMotion == pDoc->m_eyeList->m_motion)
		{
			ptrMotion->m_time = 0;
		}
		else if (ptrMotion->m_time < 0)
		{
			ptrMotion->m_time = -ptrMotion->m_time;
		}
		ptrMotion = ptrMotion->m_next;
	}
	CDialog::OnCancel();
}
