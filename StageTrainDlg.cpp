// StageTrainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "stageViewPart.h"
#include "StageTrainDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageTrainDlg dialog


CStageTrainDlg::CStageTrainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageTrainDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageTrainDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageTrainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageTrainDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageTrainDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageTrainDlg, CDialog)
	//{{AFX_MSG_MAP(CStageTrainDlg)
	ON_BN_CLICKED(IDC_TRAIN_GO, OnTrainGo)
	ON_EN_KILLFOCUS(IDC_TRAIN_VELOCITY, OnKillfocusTrainVelocity)
	ON_EN_KILLFOCUS(IDC_TRAIN_ACCELERATION, OnKillfocusTrainAcceleration)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageTrainDlg message handlers


BOOL CStageTrainDlg::YoInitDialog(void)
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

	m_init = TRUE;
	CDialog::OnInitDialog();

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

	sprintf(s, "%.1f", ((CStageTrain *)pDoc->m_currentDevice)->m_velocity);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRAIN_VELOCITY);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "%.1f", ((CStageTrain *)pDoc->m_currentDevice)->m_acceleration);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRAIN_ACCELERATION);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_translate[0]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRAIN_POSITION_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_translate[1]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRAIN_POSITION_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "%s", ((CStageTrain *)pDoc->m_currentDevice)->m_ptrTrackSeg->m_ptrPart->m_partName);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRAIN_TRACK);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.3lf", ((CStageTrain *)pDoc->m_currentDevice)->m_relativePosition);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRAIN_RELATIVE_POSITION);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	// don't allow user to modify x, y translate or z rotate
	// if attached to track
	pCBox = (CComboBox *)((CMainFrame *)pMainFrame)->m_viewPart->GetDlgItem(IDC_TRANSLATE_X);
	((CEdit *)pCBox)->SetReadOnly(TRUE);

	pCBox = (CComboBox *)((CMainFrame *)pMainFrame)->m_viewPart->GetDlgItem(IDC_TRANSLATE_Y);
	((CEdit *)pCBox)->SetReadOnly(TRUE);

	pCBox = (CComboBox *)((CMainFrame *)pMainFrame)->m_viewPart->GetDlgItem(IDC_ROTATE_Z);
	((CEdit *)pCBox)->SetReadOnly(TRUE);

	m_ptrOrigTrackSeg = ((CStageTrain *)pDoc->m_currentDevice)->m_ptrTrackSeg;
	m_origDirectionPositive = ((CStageTrain *)pDoc->m_currentDevice)->m_directionPositive;
	m_ptrOrigTrackSegEnd = ((CStageTrain *)pDoc->m_currentDevice)->m_ptrTrackSegEnd;
	m_origRelativePositionEnd = ((CStageTrain *)pDoc->m_currentDevice)->m_relativePositionEnd;
	m_origRelativePosition = ((CStageTrain *)pDoc->m_currentDevice)->m_relativePosition;
	m_origVelocity = ((CStageTrain *)pDoc->m_currentDevice)->m_velocity;
	m_origAcceleration = ((CStageTrain *)pDoc->m_currentDevice)->m_acceleration;
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageTrainDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}

void CStageTrainDlg::OnTrainGo() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;
	char s[256];

	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRAIN_GO);

	if (((CStageTrain *)pDoc->m_currentDevice)->m_moving)
	{
		sprintf(s, "STOP");
		((CStageTrain *)pDoc->m_currentDevice)->YoHandleCommand(s);
	}
	else
	{
		((CButton *)pCBox)->SetCheck(1);
		sprintf(s, "GO");
		((CStageTrain *)pDoc->m_currentDevice)->YoHandleCommand(s);
		pDoc->YoMove();
	}

	return;	
}

void CStageTrainDlg::OnKillfocusTrainVelocity() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;
	char s[256];

	pCBox = (CComboBox*)GetDlgItem(IDC_TRAIN_VELOCITY);
	pCBox->GetWindowText(s, 256);
	sscanf(s, "%lf", &((CStageTrain *)pDoc->m_currentDevice)->m_velocity);
	sprintf(s, "%.1lf", ((CStageTrain *)pDoc->m_currentDevice)->m_velocity);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "VELOCITY %lf", ((CStageTrain *)pDoc->m_currentDevice)->m_velocity);
	((CStageTrain *)pDoc->m_currentDevice)->YoHandleCommand(s);

	return;
}


void CStageTrainDlg::OnKillfocusTrainAcceleration() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;
	char s[256];

	pCBox = (CComboBox*)GetDlgItem(IDC_TRAIN_ACCELERATION);
	pCBox->GetWindowText(s, 256);
	sscanf(s, "%lf", &((CStageTrain *)pDoc->m_currentDevice)->m_acceleration);
	sprintf(s, "%.1lf", ((CStageTrain *)pDoc->m_currentDevice)->m_acceleration);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "ACCELERATION %lf", ((CStageTrain *)pDoc->m_currentDevice)->m_acceleration);
	((CStageTrain *)pDoc->m_currentDevice)->YoHandleCommand(s);
	
	return;	
}

void CStageTrainDlg::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}
