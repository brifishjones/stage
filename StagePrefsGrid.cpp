// StagePrefsGrid.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StagePrefsGrid.h"
#include "StageDoc.h"
#include "stageView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsGrid property page

IMPLEMENT_DYNCREATE(CStagePrefsGrid, CPropertyPage)

CStagePrefsGrid::CStagePrefsGrid() : CPropertyPage(CStagePrefsGrid::IDD)
{
	m_init = FALSE;
	//{{AFX_DATA_INIT(CStagePrefsGrid)
	m_gridVisible = FALSE;
	m_gridBlue = 0;
	m_gridGreen = 0;
	m_gridRed = 0;
	m_gridLength = 0.0f;
	m_gridSpacing = 0.0f;
	m_gridWidth = 0.0f;
	//}}AFX_DATA_INIT
}

CStagePrefsGrid::~CStagePrefsGrid()
{
}

void CStagePrefsGrid::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStagePrefsGrid)
	DDX_Control(pDX, IDC_GRID_SLIDER_RED, m_gridSliderRed);
	DDX_Control(pDX, IDC_GRID_SLIDER_GREEN, m_gridSliderGreen);
	DDX_Control(pDX, IDC_GRID_SLIDER_BLUE, m_gridSliderBlue);
	DDX_Check(pDX, IDC_GRID_VISIBLE, m_gridVisible);
	DDX_Text(pDX, IDC_GRID_BLUE, m_gridBlue);
	DDV_MinMaxUInt(pDX, m_gridBlue, 0, 255);
	DDX_Text(pDX, IDC_GRID_GREEN, m_gridGreen);
	DDV_MinMaxUInt(pDX, m_gridGreen, 0, 255);
	DDX_Text(pDX, IDC_GRID_RED, m_gridRed);
	DDV_MinMaxUInt(pDX, m_gridRed, 0, 255);
	DDX_Text(pDX, IDC_GRID_LENGTH, m_gridLength);
	DDX_Text(pDX, IDC_GRID_SPACING, m_gridSpacing);
	DDX_Text(pDX, IDC_GRID_WIDTH, m_gridWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStagePrefsGrid, CPropertyPage)
	//{{AFX_MSG_MAP(CStagePrefsGrid)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_GRID_BLUE, OnKillfocusGridBlue)
	ON_EN_KILLFOCUS(IDC_GRID_RED, OnKillfocusGridRed)
	ON_EN_KILLFOCUS(IDC_GRID_GREEN, OnKillfocusGridGreen)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_GRID_BLUE_RESTORE, OnGridBlueRestore)
	ON_BN_CLICKED(IDC_GRID_GREEN_RESTORE, OnGridGreenRestore)
	ON_BN_CLICKED(IDC_GRID_LENGTH_RESTORE, OnGridLengthRestore)
	ON_BN_CLICKED(IDC_GRID_RED_RESTORE, OnGridRedRestore)
	ON_BN_CLICKED(IDC_GRID_SPACING_RESTORE, OnGridSpacingRestore)
	ON_BN_CLICKED(IDC_GRID_WIDTH_RESTORE, OnGridWidthRestore)
	ON_EN_KILLFOCUS(IDC_GRID_LENGTH, OnKillfocusGridLength)
	ON_EN_KILLFOCUS(IDC_GRID_SPACING, OnKillfocusGridSpacing)
	ON_BN_CLICKED(IDC_GRID_VISIBLE, OnGridVisible)
	ON_EN_KILLFOCUS(IDC_GRID_WIDTH, OnKillfocusGridWidth)
	ON_BN_CLICKED(IDC_GRID_DEFAULTS, OnGridDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsGrid message handlers

void CStagePrefsGrid::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	if ((CSliderCtrl *)pScrollBar == &m_gridSliderRed)
	{
		m_gridRed = m_gridSliderRed.GetPos();
		pDoc->m_grid[4] = (float)m_gridRed;
	}
	else if ((CSliderCtrl *)pScrollBar == &m_gridSliderGreen)
	{
		m_gridGreen = m_gridSliderGreen.GetPos();
		pDoc->m_grid[5] = (float)m_gridGreen;
	}
	else if ((CSliderCtrl *)pScrollBar == &m_gridSliderBlue)
	{
		m_gridBlue = m_gridSliderBlue.GetPos();
		pDoc->m_grid[6] = (float)m_gridBlue;
	}
	else
	{
		CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
	}

	UpdateData(FALSE);

	if (nSBCode == SB_ENDSCROLL)
	{
		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}
	else
	{
		pView->YoRender(YO_RENDER_QUICK);
	}

	return;
}

BOOL CStagePrefsGrid::OnInitDialog() 
{
	m_init = TRUE;
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_gridSliderRed.SetRange(0, 255);
	m_gridSliderRed.SetPos(m_gridRed);
	m_gridSliderGreen.SetRange(0, 255);
	m_gridSliderGreen.SetPos(m_gridGreen);
	m_gridSliderBlue.SetRange(0, 255);
	m_gridSliderBlue.SetPos(m_gridBlue);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStagePrefsGrid::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CPropertyPage::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CStagePrefsGrid::OnGridBlueRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_gridBlue = m_origGridBlue;
	UpdateData(FALSE);
	m_gridSliderBlue.SetPos(m_gridBlue);

	pDoc->m_grid[6] = (float)m_gridBlue;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;
}


void CStagePrefsGrid::OnGridGreenRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_gridGreen = m_origGridGreen;
	UpdateData(FALSE);
	m_gridSliderGreen.SetPos(m_gridGreen);

	pDoc->m_grid[5] = (float)m_gridGreen;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}


void CStagePrefsGrid::OnGridRedRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_gridRed = m_origGridRed;
	UpdateData(FALSE);
	m_gridSliderRed.SetPos(m_gridRed);

	pDoc->m_grid[4] = (float)m_gridRed;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}


void CStagePrefsGrid::OnGridLengthRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_gridLength = m_origGridLength * (float)pDoc->m_unitScaleFactor;
	UpdateData(FALSE);

	pDoc->m_grid[2] = m_origGridLength;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}


void CStagePrefsGrid::OnGridWidthRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_gridWidth = m_origGridWidth * (float)pDoc->m_unitScaleFactor;
	UpdateData(FALSE);

	pDoc->m_grid[3] = m_origGridWidth;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;
}


void CStagePrefsGrid::OnGridSpacingRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_gridSpacing = m_origGridSpacing * (float)pDoc->m_unitScaleFactor;
	UpdateData(FALSE);

	pDoc->m_grid[1] = m_origGridSpacing;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}


void CStagePrefsGrid::OnKillfocusGridSpacing() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);

	pDoc->m_grid[1] = m_gridSpacing / (float)pDoc->m_unitScaleFactor;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}


void CStagePrefsGrid::OnKillfocusGridLength() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);

	pDoc->m_grid[2] = m_gridLength / (float)pDoc->m_unitScaleFactor;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}


void CStagePrefsGrid::OnKillfocusGridWidth() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);

	pDoc->m_grid[3] = m_gridWidth / (float)pDoc->m_unitScaleFactor;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}


void CStagePrefsGrid::OnKillfocusGridRed() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_gridSliderRed.SetPos(m_gridRed);

	pDoc->m_grid[4] = (float)m_gridRed;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;
}


void CStagePrefsGrid::OnKillfocusGridGreen() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_gridSliderGreen.SetPos(m_gridGreen);

	pDoc->m_grid[5] = (float)m_gridGreen;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;
}


void CStagePrefsGrid::OnKillfocusGridBlue() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_gridSliderBlue.SetPos(m_gridBlue);

	pDoc->m_grid[6] = (float)m_gridBlue;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;
}


void CStagePrefsGrid::OnGridVisible() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_gridSliderBlue.SetPos(m_gridBlue);

	pDoc->m_grid[0] = (float)m_gridVisible;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}

BOOL CStagePrefsGrid::OnSetActive() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_gridSpacing = pDoc->m_grid[1] * (float)pDoc->m_unitScaleFactor;
	m_gridLength = pDoc->m_grid[2] * (float)pDoc->m_unitScaleFactor;
	m_gridWidth = pDoc->m_grid[3] * (float)pDoc->m_unitScaleFactor;

	UpdateData(FALSE);

	return CPropertyPage::OnSetActive();
}

void CStagePrefsGrid::OnGridDefaults() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	pDoc->m_grid[0] = (float)YO_DEFAULT_GRID_VISIBLE;
	pDoc->m_grid[1] = (float)YO_DEFAULT_GRID_SPACING;
	pDoc->m_grid[2] = (float)YO_DEFAULT_GRID_LENGTH;
	pDoc->m_grid[3] = (float)YO_DEFAULT_GRID_WIDTH;
	pDoc->m_grid[4] = (float)YO_DEFAULT_GRID_RED;
	pDoc->m_grid[5] = (float)YO_DEFAULT_GRID_GREEN;
	pDoc->m_grid[6] = (float)YO_DEFAULT_GRID_BLUE;

	m_gridVisible = TRUE;
	m_gridSpacing = pDoc->m_grid[1] * (float)pDoc->m_unitScaleFactor;
	m_gridLength = pDoc->m_grid[2] * (float)pDoc->m_unitScaleFactor;
	m_gridWidth = pDoc->m_grid[3] * (float)pDoc->m_unitScaleFactor;
	m_gridRed = (UINT)pDoc->m_grid[4];
	m_gridGreen = (UINT)pDoc->m_grid[5];
	m_gridBlue = (UINT)pDoc->m_grid[6];

	m_gridSliderRed.SetPos(m_gridRed);
	m_gridSliderGreen.SetPos(m_gridGreen);
	m_gridSliderBlue.SetPos(m_gridBlue);

	UpdateData(FALSE);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
}
