// StageBarrettHandDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "stageViewPart.h"
#include "StageBarrettHandDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageBarrettHandDlg dialog


CStageBarrettHandDlg::CStageBarrettHandDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageBarrettHandDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageBarrettHandDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageBarrettHandDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageBarrettHandDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageBarrettHandDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageBarrettHandDlg, CDialog)
	//{{AFX_MSG_MAP(CStageBarrettHandDlg)
	ON_EN_KILLFOCUS(IDC_BARRETTHAND_VELOCITY, OnKillfocusBarretthandVelocity)
	ON_EN_KILLFOCUS(IDC_BARRETTHAND_TIP, OnKillfocusBarretthandTip)
	ON_BN_CLICKED(IDC_BARRETTHAND_SPREAD_OPEN, OnBarretthandSpreadOpen)
	ON_BN_CLICKED(IDC_BARRETTHAND_SPREAD_CLOSE, OnBarretthandSpreadClose)
	ON_EN_KILLFOCUS(IDC_BARRETTHAND_SPREAD, OnKillfocusBarretthandSpread)
	ON_EN_KILLFOCUS(IDC_BARRETTHAND_MIDDLE, OnKillfocusBarretthandMiddle)
	ON_BN_CLICKED(IDC_BARRETTHAND_JOINT_OPEN, OnBarretthandJointOpen)
	ON_BN_CLICKED(IDC_BARRETTHAND_JOINT_CLOSE, OnBarretthandJointClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageBarrettHandDlg message handlers

void CStageBarrettHandDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}

BOOL CStageBarrettHandDlg::YoInitDialog() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	int dWidth;
	int dHeight;
	RECT rect;
	RECT mfRect;
	CREATESTRUCT cs;
	char s[128];
	CWnd *pCBox;
	int i;

	m_init = TRUE;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    cs.cy = ::GetSystemMetrics(SM_CYSCREEN); 
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN); 

	this->GetWindowRect(&rect);
	dWidth = (rect.right - rect.left);
	dHeight = rect.bottom - rect.top;
	((CMainFrame *)pMainFrame)->m_viewPart->GetWindowRect(&mfRect);
	//rect.right = YO_MIN(mfRect.right + dWidth, cs.cx);
	//rect.left = rect.right - dWidth;
	rect.top = YO_MIN(mfRect.bottom, cs.cy - dHeight);
	rect.bottom = rect.top + dHeight;
	rect.left = mfRect.left;
	rect.right = rect.left + dWidth;
	//rect.right -= 3;
	//rect.left -= 3;
	//rect.top -= 8;
	//rect.bottom -= 8;
	this->MoveWindow(&rect, TRUE);

	for (i = 0; i < 3; i++)
	{
		m_origFingerFixed[i] = ((CStageBarrettHand *)pDoc->m_currentDevice)->m_fingerFixed[i];
		m_origFingerLeft[i] = ((CStageBarrettHand *)pDoc->m_currentDevice)->m_fingerLeft[i];
		m_origFingerRight[i] = ((CStageBarrettHand *)pDoc->m_currentDevice)->m_fingerRight[i];
	}
	m_origSpread = ((CStageBarrettHand *)pDoc->m_currentDevice)->m_spread;
	m_origVelocity = ((CStageBarrettHand *)pDoc->m_currentDevice)->m_velocity;

	m_middle = 140.0f;
	m_tip = 45.0;
	m_spread = 180.0;
	m_velocity = m_origVelocity;

	sprintf(s, "%.1lf", m_middle);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_BARRETTHAND_MIDDLE);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();


	sprintf(s, "%.1lf", m_tip);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_BARRETTHAND_TIP);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", m_spread);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_BARRETTHAND_SPREAD);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", m_velocity);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_BARRETTHAND_VELOCITY);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageBarrettHandDlg::OnKillfocusBarretthandVelocity() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[128];
	CWnd *pCBox;

	pCBox = (CComboBox*)GetDlgItem(IDC_BARRETTHAND_VELOCITY);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &m_velocity);
	m_velocity = YO_MIN(m_velocity, 999999.9);
	m_velocity = YO_MAX(m_velocity, 1.0);

	sprintf(s, "%.1lf", m_velocity);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	((CStageBarrettHand *)pDoc->m_currentDevice)->m_velocity = m_velocity;

	return;	
}

void CStageBarrettHandDlg::OnKillfocusBarretthandTip() 
{
	char s[128];
	CWnd *pCBox;

	pCBox = (CComboBox*)GetDlgItem(IDC_BARRETTHAND_TIP);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &m_tip);
	m_tip = YO_MIN(m_tip, 45.0);
	m_tip = YO_MAX(m_tip, 0.0);

	sprintf(s, "%.1lf", m_tip);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	return;
}

void CStageBarrettHandDlg::OnBarretthandSpreadOpen() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[128];

	if (pDoc->m_isMovement)
	{
		((CStageBarrettHand *)pDoc->m_currentDevice)->YoEStop();
	}
	
	sprintf(s, "SPREAD 0.0");
	((CStageBarrettHand *)pDoc->m_currentDevice)->YoHandleCommand(s);

	if (pDoc->m_isMovement)
	{
		pDoc->m_resumeMove = TRUE;
	}

	return;		
}

void CStageBarrettHandDlg::OnBarretthandSpreadClose() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[128];

	if (pDoc->m_isMovement)
	{
		((CStageBarrettHand *)pDoc->m_currentDevice)->YoEStop();
	}
	
	sprintf(s, "SPREAD %.1lf", m_spread);
	((CStageBarrettHand *)pDoc->m_currentDevice)->YoHandleCommand(s);

	if (pDoc->m_isMovement)
	{
		pDoc->m_resumeMove = TRUE;
	}

	return;		
}

void CStageBarrettHandDlg::OnKillfocusBarretthandSpread() 
{
	char s[128];
	CWnd *pCBox;

	pCBox = (CComboBox*)GetDlgItem(IDC_BARRETTHAND_SPREAD);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &m_spread);
	m_spread = YO_MIN(m_spread, 180.0);
	m_spread = YO_MAX(m_spread, 0.0);

	sprintf(s, "%.1lf", m_spread);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	return;
}

void CStageBarrettHandDlg::OnKillfocusBarretthandMiddle() 
{
	char s[128];
	CWnd *pCBox;

	pCBox = (CComboBox*)GetDlgItem(IDC_BARRETTHAND_MIDDLE);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &m_middle);
	m_middle = YO_MIN(m_middle, 140.0);
	m_middle = YO_MAX(m_middle, 0.0);

	sprintf(s, "%.1lf", m_middle);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	return;
}

void CStageBarrettHandDlg::OnBarretthandJointOpen() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[128];

	if (pDoc->m_isMovement)
	{
		((CStageBarrettHand *)pDoc->m_currentDevice)->YoEStop();
	}
	
	sprintf(s, "OPEN");
	((CStageBarrettHand *)pDoc->m_currentDevice)->YoHandleCommand(s);

	if (pDoc->m_isMovement)
	{
		pDoc->m_resumeMove = TRUE;
	}

	return;

}

void CStageBarrettHandDlg::OnBarretthandJointClose() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[128];

	if (pDoc->m_isMovement)
	{
		((CStageBarrettHand *)pDoc->m_currentDevice)->YoEStop();
	}
	
	sprintf(s, "CLOSE %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf",
		m_middle, m_tip, m_middle, m_tip, m_middle, m_tip);
	((CStageBarrettHand *)pDoc->m_currentDevice)->YoHandleCommand(s);

	if (pDoc->m_isMovement)
	{
		pDoc->m_resumeMove = TRUE;
	}

	return;	
}

void CStageBarrettHandDlg::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}
