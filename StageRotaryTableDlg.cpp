// StageRotaryTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "stageViewPart.h"
#include "StageRotaryTableDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageRotaryTableDlg dialog


CStageRotaryTableDlg::CStageRotaryTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageRotaryTableDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageRotaryTableDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageRotaryTableDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageRotaryTableDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageRotaryTableDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageRotaryTableDlg, CDialog)
	//{{AFX_MSG_MAP(CStageRotaryTableDlg)
	ON_BN_CLICKED(IDC_ROTARY_TABLE_GO, OnRotaryTableGo)
	ON_BN_CLICKED(IDC_ROTARY_TABLE_HOME, OnRotaryTableHome)
	ON_BN_CLICKED(IDC_ROTARY_TABLE_DIRECTION, OnRotaryTableDirection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageRotaryTableDlg message handlers

BOOL CStageRotaryTableDlg::YoInitDialog() 
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

	m_origEndPosition = ((CStageRotaryTable *)pDoc->m_currentDevice)->m_endPosition;
	m_origCurrentPosition = ((CStageRotaryTable *)pDoc->m_currentDevice)->m_currentPosition;
	m_origDirectionPositive = ((CStageRotaryTable *)pDoc->m_currentDevice)->m_directionPositive;
	m_origVelocity = ((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity;
	m_origAcceleration = ((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration;

	sprintf(s, "%.1f", ((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTARY_TABLE_VELOCITY);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "%.1f", ((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTARY_TABLE_ACCEL);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%ld", ((CStageRotaryTable *)pDoc->m_currentDevice)->m_currentPosition);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTARY_TABLE_CURRENT_POSITION);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "%ld", ((CStageRotaryTable *)pDoc->m_currentDevice)->m_endPosition);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTARY_TABLE_END_POSITION);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "0.0");
	pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTARY_TABLE_TIME_OF_MOVE);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
		
	if (((CStageRotaryTable *)pDoc->m_currentDevice)->m_directionPositive == TRUE)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTARY_TABLE_DIRECTION);
		pCBox->SetWindowText("+");
		pCBox->UpdateWindow();
	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTARY_TABLE_DIRECTION);
		pCBox->SetWindowText("-");
		pCBox->UpdateWindow();
	}
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageRotaryTableDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}

void CStageRotaryTableDlg::OnRotaryTableGo() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;
	char s[256];

	// TODO: Add your control notification handler code here
	pCBox = (CComboBox*)GetDlgItem(IDC_ROTARY_TABLE_ACCEL);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%f", &((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration);
	((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration
		= YO_MAX(0.01f, ((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration);
	((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration
		= YO_MIN(999.99f, ((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration);
	sprintf(s, "%.2lf", ((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTARY_TABLE_VELOCITY);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%f", &((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity);
	((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity
		= YO_MAX(0.01f, ((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity);
	((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity
		= YO_MIN(200.0f, ((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity);
	sprintf(s, "%.2lf", ((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	pCBox = (CComboBox*)GetDlgItem(IDC_ROTARY_TABLE_END_POSITION);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%ld", &((CStageRotaryTable *)pDoc->m_currentDevice)->m_distance);

	sprintf(s, "G");
	if(((CStageRotaryTable *)pDoc->m_currentDevice)->YoHandleSim(s))
	{
		pDoc->YoMove();
	}
}

void CStageRotaryTableDlg::OnRotaryTableHome() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;
	char s[256];

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTARY_TABLE_ACCEL);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%f", &((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration);
	((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration
		= YO_MAX(0.01f, ((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration);
	((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration
		= YO_MIN(999.99f, ((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration);
	sprintf(s, "%.2lf", ((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTARY_TABLE_VELOCITY);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%f", &((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity);
	((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity
		= YO_MAX(0.01f, ((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity);
	((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity
		= YO_MIN(200.0f, ((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity);
	sprintf(s, "%.2lf", ((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "GH%f", ((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity);
	if (((CStageRotaryTable *)pDoc->m_currentDevice)->YoHandleSim(s))
	{
		pDoc->YoMove();
	}

}

void CStageRotaryTableDlg::OnRotaryTableDirection() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;

	// TODO: Add your control notification handler code here
	if (((CStageRotaryTable *)pDoc->m_currentDevice)->m_directionPositive == TRUE)
	{
		((CStageRotaryTable *)pDoc->m_currentDevice)->m_directionPositive = FALSE;
		pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTARY_TABLE_DIRECTION);
		pCBox->SetWindowText("-");
		pCBox->UpdateWindow();
	}
	else
	{
		((CStageRotaryTable *)pDoc->m_currentDevice)->m_directionPositive = TRUE;
		pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTARY_TABLE_DIRECTION);
		pCBox->SetWindowText("+");
		pCBox->UpdateWindow();
	}

	return;
}

void CStageRotaryTableDlg::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}
