// StageRobot6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "stageViewPart.h"
#include "StageRobot6Dlg.h"
#include "stageRobot6SetupDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageRobot6Dlg dialog


CStageRobot6Dlg::CStageRobot6Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageRobot6Dlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageRobot6Dlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageRobot6Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageRobot6Dlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageRobot6Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageRobot6Dlg, CDialog)
	//{{AFX_MSG_MAP(CStageRobot6Dlg)
	ON_EN_KILLFOCUS(IDC_JOINT1, OnKillfocusJoint1)
	ON_EN_KILLFOCUS(IDC_JOINT2, OnKillfocusJoint2)
	ON_EN_KILLFOCUS(IDC_JOINT3, OnKillfocusJoint3)
	ON_EN_KILLFOCUS(IDC_JOINT4, OnKillfocusJoint4)
	ON_EN_KILLFOCUS(IDC_JOINT5, OnKillfocusJoint5)
	ON_EN_KILLFOCUS(IDC_JOINT6, OnKillfocusJoint6)
	ON_BN_CLICKED(IDC_LEFTY, OnLefty)
	ON_BN_CLICKED(IDC_RIGHTY, OnRighty)
	ON_BN_CLICKED(IDC_WRIST_FLIPPED, OnWristFlipped)
	ON_BN_CLICKED(IDC_ELBOW_DOWN, OnElbowDown)
	ON_BN_CLICKED(IDC_ELBOW_UP, OnElbowUp)
	ON_EN_KILLFOCUS(IDC_SPEED, OnKillfocusSpeed)
	ON_BN_CLICKED(IDC_DECREASE_JOINT1, OnDecreaseJoint1)
	ON_BN_CLICKED(IDC_DECREASE_JOINT2, OnDecreaseJoint2)
	ON_BN_CLICKED(IDC_DECREASE_JOINT3, OnDecreaseJoint3)
	ON_BN_CLICKED(IDC_DECREASE_JOINT4, OnDecreaseJoint4)
	ON_BN_CLICKED(IDC_DECREASE_JOINT5, OnDecreaseJoint5)
	ON_BN_CLICKED(IDC_DECREASE_JOINT6, OnDecreaseJoint6)
	ON_BN_CLICKED(IDC_INCREASE_JOINT1, OnIncreaseJoint1)
	ON_BN_CLICKED(IDC_INCREASE_JOINT2, OnIncreaseJoint2)
	ON_BN_CLICKED(IDC_INCREASE_JOINT3, OnIncreaseJoint3)
	ON_BN_CLICKED(IDC_INCREASE_JOINT4, OnIncreaseJoint4)
	ON_BN_CLICKED(IDC_INCREASE_JOINT5, OnIncreaseJoint5)
	ON_BN_CLICKED(IDC_INCREASE_JOINT6, OnIncreaseJoint6)
	ON_BN_CLICKED(IDC_SETUP, OnSetup)
	ON_EN_KILLFOCUS(IDC_MIN_ACCEL_TIME, OnKillfocusMinAccelTime)
	ON_BN_CLICKED(IDC_ESTOP, OnEstop)
	ON_BN_CLICKED(IDC_HOME, OnHome)
	ON_BN_CLICKED(IDC_INTERPOLATION_JOINT, OnInterpolationJoint)
	ON_BN_CLICKED(IDC_INTERPOLATION_LINEAR, OnInterpolationLinear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageRobot6Dlg message handlers


BOOL CStageRobot6Dlg::YoInitDialog() 
{
	
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	int i;
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
	dWidth = rect.right - rect.left;
	dHeight = rect.bottom - rect.top;
	((CMainFrame *)pMainFrame)->m_viewPart->GetWindowRect(&mfRect);
	//rect.right = YO_MIN(mfRect.right + dWidth, cs.cx);
	//rect.left = rect.right - dWidth;
	rect.top = YO_MIN(mfRect.bottom, cs.cy - dHeight);
	rect.bottom = rect.top + dHeight;
	rect.left = mfRect.left;
	rect.right = rect.left + dWidth;
	//rect.top -= 8;
	//rect.bottom -= 8;
	this->MoveWindow(&rect, TRUE);

	for (i = 1; i <= 6; i++)
	{
		m_origJ[i] = ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[i];
	}
	m_origSpeed = ((CStageRobot6 *)pDoc->m_currentDevice)->m_speed;
	m_origMinAccelTime = ((CStageRobot6 *)pDoc->m_currentDevice)->m_minAccelTime;
	m_origJointInterpolation = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jointInterpolation;
	m_origElbowUp = ((CStageRobot6 *)pDoc->m_currentDevice)->m_elbowUp;
	m_origLefty = ((CStageRobot6 *)pDoc->m_currentDevice)->m_lefty;
	m_origWristFlipped = ((CStageRobot6 *)pDoc->m_currentDevice)->m_wristFlipped;

	//sprintf(s, "%.1lf", pDoc->m_currentDevice->m_translate[0] * pDoc->m_unitScaleFactor);
	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT1);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[2]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT2);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[3] + 180.0);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT3);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[4]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT4);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[5]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT5);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[6]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT6);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%d", ((CStageRobot6 *)pDoc->m_currentDevice)->m_speed);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_SPEED);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.2lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_minAccelTime);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_MIN_ACCEL_TIME);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (((CStageRobot6 *)pDoc->m_currentDevice)->m_jointInterpolation == TRUE)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_INTERPOLATION_JOINT);
		((CButton *)pCBox)->SetCheck(1);
	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_INTERPOLATION_LINEAR);
		((CButton *)pCBox)->SetCheck(1);
	}

	if (((CStageRobot6 *)pDoc->m_currentDevice)->m_elbowUp == TRUE)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_ELBOW_UP);
		((CButton *)pCBox)->SetCheck(1);
	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_ELBOW_DOWN);
		((CButton *)pCBox)->SetCheck(1);
	}

	if (((CStageRobot6 *)pDoc->m_currentDevice)->m_lefty == TRUE)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_LEFTY);
		((CButton *)pCBox)->SetCheck(1);
	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_RIGHTY);
		((CButton *)pCBox)->SetCheck(1);
	}

	if (((CStageRobot6 *)pDoc->m_currentDevice)->m_wristFlipped == TRUE)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_WRIST_FLIPPED);
		((CButton *)pCBox)->SetCheck(1);
	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_WRIST_FLIPPED);
		((CButton *)pCBox)->SetCheck(0);
	}

	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageRobot6Dlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	delete this;
}


void CStageRobot6Dlg::OnKillfocusJoint1() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_JOINT1);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &((CStageRobot6 *)pDoc->m_currentDevice)->m_j[1]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;			
}

void CStageRobot6Dlg::OnKillfocusJoint2() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_JOINT2);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &((CStageRobot6 *)pDoc->m_currentDevice)->m_j[2]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageRobot6Dlg::OnKillfocusJoint3() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_JOINT3);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &((CStageRobot6 *)pDoc->m_currentDevice)->m_j[3]);
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[3] -= 180.0;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageRobot6Dlg::OnKillfocusJoint4() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_JOINT4);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &((CStageRobot6 *)pDoc->m_currentDevice)->m_j[4]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageRobot6Dlg::OnKillfocusJoint5() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_JOINT5);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &((CStageRobot6 *)pDoc->m_currentDevice)->m_j[5]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageRobot6Dlg::OnKillfocusJoint6() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_JOINT6);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &((CStageRobot6 *)pDoc->m_currentDevice)->m_j[6]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageRobot6Dlg::OnLefty() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	((CStageRobot6 *)pDoc->m_currentDevice)->m_lefty = TRUE;
	return;
}

void CStageRobot6Dlg::OnRighty() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	((CStageRobot6 *)pDoc->m_currentDevice)->m_lefty = FALSE;
	return;	
}

void CStageRobot6Dlg::OnWristFlipped() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;

	pCBox = (CComboBox*)this->GetDlgItem(IDC_WRIST_FLIPPED);

	if (((CStageRobot6 *)pDoc->m_currentDevice)->m_wristFlipped == TRUE)
	{
		((CStageRobot6 *)pDoc->m_currentDevice)->m_wristFlipped = FALSE;
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		((CStageRobot6 *)pDoc->m_currentDevice)->m_wristFlipped = TRUE;
		((CButton *)pCBox)->SetCheck(1);
	}

	return;		
}

void CStageRobot6Dlg::OnElbowDown() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	((CStageRobot6 *)pDoc->m_currentDevice)->m_elbowUp = FALSE;
	return;	
}

void CStageRobot6Dlg::OnElbowUp() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	((CStageRobot6 *)pDoc->m_currentDevice)->m_elbowUp = TRUE;
	return;	
}

void CStageRobot6Dlg::OnKillfocusSpeed() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_SPEED);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%d", &((CStageRobot6 *)pDoc->m_currentDevice)->m_speed);

	((CStageRobot6 *)pDoc->m_currentDevice)->m_speed
		= YO_MAX(1, ((CStageRobot6 *)pDoc->m_currentDevice)->m_speed);
	((CStageRobot6 *)pDoc->m_currentDevice)->m_speed
		= YO_MIN(100, ((CStageRobot6 *)pDoc->m_currentDevice)->m_speed);

	sprintf(s, "%d", ((CStageRobot6 *)pDoc->m_currentDevice)->m_speed);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	return;		
}

void CStageRobot6Dlg::OnDecreaseJoint1() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[1]
		= YO_MAX(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[1] - 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[1][0]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT1);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnDecreaseJoint2() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[2]
		= YO_MAX(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[2] - 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[2][0]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[2]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT2);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnDecreaseJoint3() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[3]
		= YO_MAX(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[3] - 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[3][0]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[3] + 180.0);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT3);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnDecreaseJoint4() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[4]
		= YO_MAX(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[4] - 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[4][0]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[4]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT4);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnDecreaseJoint5() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[5]
		= YO_MAX(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[5] - 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[5][0]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[5]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT5);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnDecreaseJoint6() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[6]
		= YO_MAX(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[6] - 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[6][0]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[6]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT6);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnIncreaseJoint1() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[1]
		= YO_MIN(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[1] + 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[1][1]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT1);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnIncreaseJoint2() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[2]
		= YO_MIN(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[2] + 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[2][1]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[2]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT2);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnIncreaseJoint3() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[3]
		= YO_MIN(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[3] + 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[3][1]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[3] + 180.0);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT3);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnIncreaseJoint4() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[4]
		= YO_MIN(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[4] + 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[4][1]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[4]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT4);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnIncreaseJoint5() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[5]
		= YO_MIN(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[5] + 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[5][1]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[5]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT5);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnIncreaseJoint6() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	((CStageRobot6 *)pDoc->m_currentDevice)->m_j[6]
		= YO_MIN(((CStageRobot6 *)pDoc->m_currentDevice)->m_j[6] + 10.0,
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[6][1]);

	sprintf(s, "%.1lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_j[6]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_JOINT6);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStageRobot6Dlg::OnSetup() 
{
	CStageRobot6SetupDlg setup;
	// TODO: Add your control notification handler code here
	
	setup.DoModal();
	return;
}

void CStageRobot6Dlg::OnKillfocusMinAccelTime() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_MIN_ACCEL_TIME);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &((CStageRobot6 *)pDoc->m_currentDevice)->m_minAccelTime);

	((CStageRobot6 *)pDoc->m_currentDevice)->m_minAccelTime
		= YO_MAX(0.01, ((CStageRobot6 *)pDoc->m_currentDevice)->m_minAccelTime);
	((CStageRobot6 *)pDoc->m_currentDevice)->m_minAccelTime
		= YO_MIN(20.0, ((CStageRobot6 *)pDoc->m_currentDevice)->m_minAccelTime);

	sprintf(s, "%.2lf", ((CStageRobot6 *)pDoc->m_currentDevice)->m_minAccelTime);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	return;		
}

void CStageRobot6Dlg::OnEstop() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[128];
	
	if (((CStageRobot6 *)pDoc->m_currentDevice)->m_moving)
	{
		sprintf(s, "BRAKE");
		((CStageRobot6 *)pDoc->m_currentDevice)->YoHandleCommand(s);
	}
	
	return;
}

void CStageRobot6Dlg::OnHome() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[128];
	
	sprintf(s, "MOVEJOINTS %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf",
		((CStageRobot6 *)pDoc->m_currentDevice)->m_home[1],
		((CStageRobot6 *)pDoc->m_currentDevice)->m_home[2],
		((CStageRobot6 *)pDoc->m_currentDevice)->m_home[3],
		((CStageRobot6 *)pDoc->m_currentDevice)->m_home[4],
		((CStageRobot6 *)pDoc->m_currentDevice)->m_home[5],
		((CStageRobot6 *)pDoc->m_currentDevice)->m_home[6]);
	((CStageRobot6 *)pDoc->m_currentDevice)->YoHandleCommand(s);
	
	return;	
}

void CStageRobot6Dlg::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}

void CStageRobot6Dlg::OnInterpolationJoint() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	((CStageRobot6 *)pDoc->m_currentDevice)->m_jointInterpolation = TRUE;
	return;		
}

void CStageRobot6Dlg::OnInterpolationLinear() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	((CStageRobot6 *)pDoc->m_currentDevice)->m_jointInterpolation = FALSE;
	return;		
}

