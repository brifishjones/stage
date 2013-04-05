// StageBarCodeReaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "stageViewPart.h"
#include "StageBarCodeReaderDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageBarCodeReaderDlg dialog


CStageBarCodeReaderDlg::CStageBarCodeReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageBarCodeReaderDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageBarCodeReaderDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageBarCodeReaderDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageBarCodeReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageBarCodeReaderDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageBarCodeReaderDlg, CDialog)
	//{{AFX_MSG_MAP(CStageBarCodeReaderDlg)
	ON_BN_CLICKED(IDC_BCR_GET_CODE, OnBcrGetCode)
	ON_BN_CLICKED(IDC_BCR_TRIGGER, OnBcrTrigger)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageBarCodeReaderDlg message handlers

void CStageBarCodeReaderDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}


BOOL CStageBarCodeReaderDlg::YoInitDialog() 
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

	sprintf(s, "");
	pCBox = (CComboBox*)this->GetDlgItem(IDC_BCR_CODE);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	pCBox = (CComboBox*)this->GetDlgItem(IDC_BCR_TRIGGER);
	((CButton *)pCBox)->SetCheck(0);
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageBarCodeReaderDlg::OnBcrTrigger() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;
	char s[256];

	if (((CStageBarCodeReader *)pDoc->m_currentDevice)->m_scanning == FALSE)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_BCR_TRIGGER);
		((CButton *)pCBox)->SetCheck(1);
		sprintf(s, "TRIGGER");
		((CStageBarCodeReader *)pDoc->m_currentDevice)->YoHandleCommand(s);

		sprintf(s, "");
		pCBox = (CComboBox*)GetDlgItem(IDC_BCR_CODE);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_BCR_TRIGGER);
		((CButton *)pCBox)->SetCheck(0);
		sprintf(s, "TRIGGEROFF");
		((CStageBarCodeReader *)pDoc->m_currentDevice)->YoHandleCommand(s);
	}

	if (pDoc->m_isMovement)
	{
		pDoc->m_resumeMove = TRUE;
	}

	return;	
}

void CStageBarCodeReaderDlg::OnBcrGetCode() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;
	char s[256];

	if (((CStageBarCodeReader *)pDoc->m_currentDevice)->m_scanning == FALSE)
	{
		sprintf(s, "");
		pCBox = (CComboBox*)GetDlgItem(IDC_BCR_CODE);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		return;
	}

	sprintf(s, "GETSCAN");
	((CStageBarCodeReader *)pDoc->m_currentDevice)->YoHandleCommand(s);

	if (pDoc->m_isMovement)
	{
		pDoc->m_resumeMove = TRUE;
	}

	return;	
}

void CStageBarCodeReaderDlg::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}
