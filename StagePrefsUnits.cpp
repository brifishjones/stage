// StagePrefsUnits.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StagePrefsUnits.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsUnits property page

IMPLEMENT_DYNCREATE(CStagePrefsUnits, CPropertyPage)

CStagePrefsUnits::CStagePrefsUnits() : CPropertyPage(CStagePrefsUnits::IDD)
{
	m_init = FALSE;
	//{{AFX_DATA_INIT(CStagePrefsUnits)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CStagePrefsUnits::~CStagePrefsUnits()
{
}

void CStagePrefsUnits::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStagePrefsUnits)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStagePrefsUnits, CPropertyPage)
	//{{AFX_MSG_MAP(CStagePrefsUnits)
	ON_BN_CLICKED(IDC_UNITS_FEET, OnUnitsFeet)
	ON_BN_CLICKED(IDC_UNITS_INCHES, OnUnitsInches)
	ON_BN_CLICKED(IDC_UNITS_METERS, OnUnitsMeters)
	ON_BN_CLICKED(IDC_UNITS_MILLIMETERS, OnUnitsMillimeters)
	ON_BN_CLICKED(IDC_UNITS_DEFAULTS, OnUnitsDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsUnits message handlers

BOOL CStagePrefsUnits::OnInitDialog() 
{
	CWnd *pCBox;

	m_init = TRUE;
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_units == YO_UNITS_MILLIMETERS)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_UNITS_MILLIMETERS);
		((CButton *)pCBox)->SetCheck(1);
	}
	else if (m_units == YO_UNITS_INCHES)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_UNITS_INCHES);
		((CButton *)pCBox)->SetCheck(1);
	}
	else if (m_units == YO_UNITS_FEET)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_UNITS_FEET);
		((CButton *)pCBox)->SetCheck(1);
	}
	else if (m_units == YO_UNITS_METERS)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_UNITS_METERS);
		((CButton *)pCBox)->SetCheck(1);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStagePrefsUnits::OnUnitsFeet() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_units = YO_UNITS_FEET;
	pDoc->m_units = m_units;
	pDoc->YoUnitScaleFactor();
	((CMainFrame *)pMainFrame)->YoUpdateEyeDlg();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}

void CStagePrefsUnits::OnUnitsInches() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_units = YO_UNITS_INCHES;
	pDoc->m_units = m_units;
	pDoc->YoUnitScaleFactor();
	((CMainFrame *)pMainFrame)->YoUpdateEyeDlg();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}

void CStagePrefsUnits::OnUnitsMeters() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_units = YO_UNITS_METERS;
	pDoc->m_units = m_units;
	pDoc->YoUnitScaleFactor();
	((CMainFrame *)pMainFrame)->YoUpdateEyeDlg();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}

void CStagePrefsUnits::OnUnitsMillimeters() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_units = YO_UNITS_MILLIMETERS;
	pDoc->m_units = m_units;
	pDoc->YoUnitScaleFactor();
	((CMainFrame *)pMainFrame)->YoUpdateEyeDlg();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}

void CStagePrefsUnits::OnUnitsDefaults() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;

	m_units = YO_UNITS_MILLIMETERS;
	pDoc->m_units = m_units;
	pDoc->YoUnitScaleFactor();
	((CMainFrame *)pMainFrame)->YoUpdateEyeDlg();

	pCBox = (CComboBox*)GetDlgItem(IDC_UNITS_MILLIMETERS);
	((CButton *)pCBox)->SetCheck(1);

	pCBox = (CComboBox*)GetDlgItem(IDC_UNITS_INCHES);
	((CButton *)pCBox)->SetCheck(0);

	pCBox = (CComboBox*)GetDlgItem(IDC_UNITS_FEET);
	((CButton *)pCBox)->SetCheck(0);

	pCBox = (CComboBox*)GetDlgItem(IDC_UNITS_METERS);
	((CButton *)pCBox)->SetCheck(0);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}
