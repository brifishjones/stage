// StageScaleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "stageViewPart.h"
#include "StageScaleDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageScaleDlg dialog


CStageScaleDlg::CStageScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageScaleDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageScaleDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageScaleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageScaleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageScaleDlg, CDialog)
	//{{AFX_MSG_MAP(CStageScaleDlg)
	ON_BN_CLICKED(IDC_SCALE_GET_MASS, OnScaleGetMass)
	ON_BN_CLICKED(IDC_SCALE_KG, OnScaleKg)
	ON_BN_CLICKED(IDC_SCALE_LB, OnScaleLb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageScaleDlg message handlers

void CStageScaleDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}


BOOL CStageScaleDlg::YoInitDialog() 
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

	m_origUnits = ((CStageScale *)pDoc->m_currentDevice)->m_units;

	sprintf(s, "");
	pCBox = (CComboBox*)this->GetDlgItem(IDC_SCALE_MASS);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
		
	if (((CStageScale *)pDoc->m_currentDevice)->m_units == YO_UNITS_KILOGRAMS)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCALE_KG);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCALE_LB);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCALE_KG);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_SCALE_LB);
		((CButton *)pCBox)->SetCheck(1);
	}
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStageScaleDlg::OnScaleGetMass() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[128];

	if (((CStageScale *)pDoc->m_currentDevice)->m_units == YO_UNITS_POUNDS)
	{
		sprintf(s, "LB");
	}
	else
	{
		sprintf(s, "KG");
	}

	((CStageScale *)pDoc->m_currentDevice)->YoHandleCommand(s);

	return;	
}

void CStageScaleDlg::OnScaleKg() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	((CStageScale *)pDoc->m_currentDevice)->m_units = YO_UNITS_KILOGRAMS;
	return;			
}

void CStageScaleDlg::OnScaleLb() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	((CStageScale *)pDoc->m_currentDevice)->m_units = YO_UNITS_POUNDS;
	return;		
	
}

void CStageScaleDlg::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}
