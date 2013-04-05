// StageGripperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "stageViewPart.h"
#include "StageGripperDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageGripperDlg dialog


CStageGripperDlg::CStageGripperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageGripperDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageGripperDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageGripperDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageGripperDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}


	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageGripperDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageGripperDlg, CDialog)
	//{{AFX_MSG_MAP(CStageGripperDlg)
	ON_BN_CLICKED(IDC_GRIPPER_CLOSE, OnGripperClose)
	ON_BN_CLICKED(IDC_GRIPPER_OPEN, OnGripperOpen)
	ON_BN_CLICKED(IDC_GRIPPER_TYPE_ROTATING, OnGripperTypeRotating)
	ON_BN_CLICKED(IDC_GRIPPER_TYPE_TRANSLATING, OnGripperTypeTranslating)
	ON_EN_KILLFOCUS(IDC_GRIPPER_DISPLACEMENT_CLOSE, OnKillfocusGripperDisplacementClose)
	ON_EN_KILLFOCUS(IDC_GRIPPER_DISPLACEMENT_OPEN, OnKillfocusGripperDisplacementOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageGripperDlg message handlers

void CStageGripperDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}


BOOL CStageGripperDlg::YoInitDialog() 
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

	sprintf(s, "%.3f", ((CStageGripper *)pDoc->m_currentDevice)->m_displacementOpen);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_DISPLACEMENT_OPEN);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "%.3f", ((CStageGripper *)pDoc->m_currentDevice)->m_displacementClose);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_DISPLACEMENT_CLOSE);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (((CStageGripper *)pDoc->m_currentDevice)->m_typeTranslating == TRUE)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_TYPE_TRANSLATING);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_TYPE_ROTATING);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_TYPE_TRANSLATING);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_TYPE_ROTATING);
		((CButton *)pCBox)->SetCheck(1);
	}
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageGripperDlg::OnGripperClose() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	((CStageGripper *)pDoc->m_currentDevice)->YoCloseGripper();
	return;
}

void CStageGripperDlg::OnGripperOpen() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	((CStageGripper *)pDoc->m_currentDevice)->YoOpenGripper();
	return;	
}

void CStageGripperDlg::OnGripperTypeRotating() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	((CStageGripper *)pDoc->m_currentDevice)->m_typeTranslating = FALSE;
	return;
}

void CStageGripperDlg::OnGripperTypeTranslating() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	((CStageGripper *)pDoc->m_currentDevice)->m_typeTranslating = TRUE;
	return;	
}

void CStageGripperDlg::OnKillfocusGripperDisplacementClose() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)GetDlgItem(IDC_GRIPPER_DISPLACEMENT_CLOSE);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &((CStageGripper *)pDoc->m_currentDevice)->m_displacementClose);
	return;
}

void CStageGripperDlg::OnKillfocusGripperDisplacementOpen() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)GetDlgItem(IDC_GRIPPER_DISPLACEMENT_OPEN);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &((CStageGripper *)pDoc->m_currentDevice)->m_displacementOpen);
	return;
}

void CStageGripperDlg::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}
