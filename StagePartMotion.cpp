// StagePartMotion.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StagePartMotion.h"
#include "stageDoc.h"
#include "stageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStagePartMotion dialog


CStagePartMotion::CStagePartMotion(CWnd* pParent /*=NULL*/)
	: CDialog(CStagePartMotion::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStagePartMotion)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStagePartMotion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStagePartMotion)
	DDX_Control(pDX, IDC_PART_MOTION_LIST, m_partMotionList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStagePartMotion, CDialog)
	//{{AFX_MSG_MAP(CStagePartMotion)
	ON_BN_CLICKED(IDC_PART_CLEAR_ALL, OnPartClearAll)
	ON_BN_CLICKED(IDC_PART_REMOVE, OnPartRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStagePartMotion message handlers

void CStagePartMotion::OnPartClearAll() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	pDoc->m_currentPart->m_motion->m_time = INT_MAX;
	m_partMotionList.ResetContent();
	return;	
}

void CStagePartMotion::OnPartRemove() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStageMotion *ptrMotion;
	int i = 0;
	int j = m_partMotionList.GetCount();
	GLint min;
	GLint sec;
	GLint frm;
	GLint t;
	char s[128];
	char *p;

	while (i < j)
	{
		if (m_partMotionList.GetSel(i))
		{
			m_partMotionList.GetText(i, s);
			sscanf(s, "%d", &min);
			p = &s[3];
			sscanf(p, "%d", &sec);
			p = &s[6];
			sscanf(p, "%d", &frm);
			//sscanf(s, "%d  *%s %d *%s %d", &min, &sec, &frm);
			t = (min * 60 * pDoc->m_framesPerSecond)
				+ (sec * pDoc->m_framesPerSecond)
				+ frm;

			ptrMotion = pDoc->m_currentPart->m_motion;
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

			m_partMotionList.DeleteString(i);
			j--;
		}
		else
		{
			i++;
		}
	}
	return;
}


void CStagePartMotion::OnCancel() 
{
	// TODO: Add extra cleanup here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStageMotion *ptrMotion = pDoc->m_currentPart->m_motion;

	
	while (ptrMotion != NULL)
    {
		if (ptrMotion->m_time == INT_MAX
			&& ptrMotion == pDoc->m_currentPart->m_motion)
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

void CStagePartMotion::OnOK() 
{
	// TODO: Add extra validation here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStageMotion *ptrMotion = pDoc->m_currentPart->m_motion;
	CStageMotion *prevMotion = pDoc->m_currentPart->m_motion;

	
	while (ptrMotion != NULL)
    {
		// clear all is selected
		if (ptrMotion->m_time == INT_MAX
			&& ptrMotion == pDoc->m_currentPart->m_motion)
		{
			while (ptrMotion != NULL)
			{
				prevMotion = ptrMotion->m_next;
				delete (ptrMotion);
				ptrMotion = prevMotion;
			}
			pDoc->m_currentPart->m_motion = NULL;
			pDoc->m_currentPart->m_motionEffectModified = TRUE;
			pDoc->m_motionEffectModified = TRUE;
			return;
		}
		// node is tagged for delete
		else if (ptrMotion->m_time < 0)
		{
			prevMotion->m_next = ptrMotion->m_next;
			delete (ptrMotion);
			ptrMotion = prevMotion->m_next;
			pDoc->m_currentPart->m_motionEffectModified = TRUE;
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


BOOL CStagePartMotion::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	
	// TODO: Add extra initialization here
	//LPCTSTR lpszItem = "device";

	CStageMotion *ptrMotion = pDoc->m_currentPart->m_motion;
	char s[128];
	char t[4];

	m_partMotionList.ResetContent();

    while (ptrMotion != NULL)
    {
		if (ptrMotion->m_type == YO_MOTION_ANCHOR)
		{
			sprintf(t, "A"); 
		}
		else
		{
			sprintf(t, "H");
		}
		sprintf(s,
			"%02d:%02d:%02d     T:(%05.1f, %05.1f, %05.1f)  R:(%05.1f, %05.1f, %05.1f)    %s", 
		ptrMotion->m_time / (60 * pDoc->m_framesPerSecond),
		(ptrMotion->m_time % (60 * pDoc->m_framesPerSecond)) / pDoc->m_framesPerSecond, 
		(ptrMotion->m_time % (60 * pDoc->m_framesPerSecond)) % pDoc->m_framesPerSecond, 
		ptrMotion->m_translate[0], ptrMotion->m_translate[1], ptrMotion->m_translate[2],
		ptrMotion->m_rotate[0], ptrMotion->m_rotate[1], ptrMotion->m_rotate[2],
		t);

		m_partMotionList.AddString(s);
		ptrMotion = ptrMotion->m_next;
	}

	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
