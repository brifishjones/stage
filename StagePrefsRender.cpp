// StagePrefsRender.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StagePrefsRender.h"
#include "StageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsRender property page

IMPLEMENT_DYNCREATE(CStagePrefsRender, CPropertyPage)

CStagePrefsRender::CStagePrefsRender() : CPropertyPage(CStagePrefsRender::IDD)
{
	m_init = FALSE;
	//{{AFX_DATA_INIT(CStagePrefsRender)
	m_motionBlur = FALSE;
	m_motionBlurIterations = 0;
	m_framesPerSecond = 0;
	m_boundingBox = FALSE;
	m_antiAlias = FALSE;
	m_outputBitmap = FALSE;
	//}}AFX_DATA_INIT
}

CStagePrefsRender::~CStagePrefsRender()
{
}

void CStagePrefsRender::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStagePrefsRender)
	DDX_Check(pDX, IDC_MOTION_BLUR, m_motionBlur);
	DDX_Text(pDX, IDC_MOTION_BLUR_ITERATIONS, m_motionBlurIterations);
	DDV_MinMaxUInt(pDX, m_motionBlurIterations, 1, 64);
	DDX_Text(pDX, IDC_FRAMES_PER_SECOND, m_framesPerSecond);
	DDV_MinMaxInt(pDX, m_framesPerSecond, 0, 59);
	DDX_Check(pDX, IDC_BOUNDING_BOX, m_boundingBox);
	DDX_Check(pDX, IDC_ANTIALIAS, m_antiAlias);
	DDX_Check(pDX, IDC_OUTPUT_BITMAP, m_outputBitmap);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStagePrefsRender, CPropertyPage)
	//{{AFX_MSG_MAP(CStagePrefsRender)
	ON_BN_CLICKED(IDC_BOUNDING_BOX, OnBoundingBox)
	ON_BN_CLICKED(IDC_RENDER_DEFAULTS, OnRenderDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsRender message handlers

BOOL CStagePrefsRender::OnInitDialog() 
{
	m_init = TRUE;
	CPropertyPage::OnInitDialog();
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStagePrefsRender::OnBoundingBox() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	pDoc->m_boundingBox = m_boundingBox;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}

void CStagePrefsRender::OnRenderDefaults() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	pDoc->m_boundingBox = YO_DEFAULT_RENDER_BOUNDING_BOX;
	m_boundingBox = YO_DEFAULT_RENDER_BOUNDING_BOX;

	m_antiAlias = YO_DEFAULT_RENDER_ANTI_ALIAS;
	m_framesPerSecond = YO_DEFAULT_RENDER_FRAMES_PER_SECOND;
	m_motionBlur = FALSE;
	m_motionBlurIterations = YO_DEFAULT_RENDER_MOTION_BLUR_ITERATIONS;
	m_outputBitmap = FALSE;

	UpdateData(FALSE);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
	
}
