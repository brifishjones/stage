// StagePrefsLighting.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StagePrefsLighting.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsLighting property page

IMPLEMENT_DYNCREATE(CStagePrefsLighting, CPropertyPage)

CStagePrefsLighting::CStagePrefsLighting() : CPropertyPage(CStagePrefsLighting::IDD)
{
	m_init = FALSE;
	//{{AFX_DATA_INIT(CStagePrefsLighting)
	m_lightingSunAltitude = 0.0f;
	m_lightingSunAzimuth = 0.0f;
	m_twoSide = FALSE;
	m_lightingSunIntensity = 0.0f;
	//}}AFX_DATA_INIT
}

CStagePrefsLighting::~CStagePrefsLighting()
{
}

void CStagePrefsLighting::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStagePrefsLighting)
	DDX_Control(pDX, IDC_LIGHTING_SUN_SLIDER_INTENSITY, m_lightingSunSliderIntensity);
	DDX_Text(pDX, IDC_LIGHTING_SUN_ALTITUDE, m_lightingSunAltitude);
	DDV_MinMaxFloat(pDX, m_lightingSunAltitude, -90.f, 90.f);
	DDX_Text(pDX, IDC_LIGHTING_SUN_AZIMUTH, m_lightingSunAzimuth);
	DDV_MinMaxFloat(pDX, m_lightingSunAzimuth, -360.f, 360.f);
	DDX_Check(pDX, IDC_TWO_SIDE, m_twoSide);
	DDX_Text(pDX, IDC_LIGHTING_SUN_INTENSITY, m_lightingSunIntensity);
	DDV_MinMaxFloat(pDX, m_lightingSunIntensity, 0.f, 1.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStagePrefsLighting, CPropertyPage)
	//{{AFX_MSG_MAP(CStagePrefsLighting)
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
	ON_EN_KILLFOCUS(IDC_LIGHTING_SUN_ALTITUDE, OnKillfocusLightingSunAltitude)
	ON_EN_KILLFOCUS(IDC_LIGHTING_SUN_AZIMUTH, OnKillfocusLightingSunAzimuth)
	ON_EN_KILLFOCUS(IDC_LIGHTING_SUN_INTENSITY, OnKillfocusLightingSunIntensity)
	ON_BN_CLICKED(IDC_TWO_SIDE, OnTwoSide)
	ON_BN_CLICKED(IDC_LIGHTING_SUN_ALTITUDE_RESTORE, OnLightingSunAltitudeRestore)
	ON_BN_CLICKED(IDC_LIGHTING_SUN_AZIMUTH_RESTORE, OnLightingSunAzimuthRestore)
	ON_BN_CLICKED(IDC_LIGHTING_SUN_INTENSITY_RESTORE, OnLightingSunIntensityRestore)
	ON_BN_CLICKED(IDC_LIGHTING_SUN_FRONT, OnLightingSunFront)
	ON_BN_CLICKED(IDC_LIGHTING_SUN_LEFT, OnLightingSunLeft)
	ON_BN_CLICKED(IDC_LIGHTING_SUN_RIGHT, OnLightingSunRight)
	ON_BN_CLICKED(IDC_LIGHTING_DEFAULTS, OnLightingDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsLighting message handlers

void CStagePrefsLighting::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	if ((CSliderCtrl *)pScrollBar == &m_lightingSunSliderIntensity)
	{
		m_lightingSunIntensity = (float)m_lightingSunSliderIntensity.GetPos() / 100.0f;
		pDoc->m_sunIntensity = m_lightingSunIntensity;
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


BOOL CStagePrefsLighting::OnInitDialog() 
{
	m_init = TRUE;
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lightingSunSliderIntensity.SetRange(0, 100);
	m_lightingSunSliderIntensity.SetPos((int)(m_lightingSunIntensity * 100.0));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStagePrefsLighting::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CPropertyPage::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CStagePrefsLighting::OnKillfocusLightingSunAltitude() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);

	pDoc->m_sunAltitude = m_lightingSunAltitude;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;
}

void CStagePrefsLighting::OnKillfocusLightingSunAzimuth() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);

	pDoc->m_sunAzimuth = m_lightingSunAzimuth;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;
}


void CStagePrefsLighting::OnKillfocusLightingSunIntensity() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);

	m_lightingSunSliderIntensity.SetPos((int)(m_lightingSunIntensity * 100.0));
	pDoc->m_sunIntensity = m_lightingSunIntensity;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}


void CStagePrefsLighting::OnTwoSide() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);

	pDoc->m_lighting[1] = (GLint)m_twoSide;
	::glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, pDoc->m_lighting[1]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}


void CStagePrefsLighting::OnLightingSunAltitudeRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_lightingSunAltitude = m_origLightingSunAltitude;
	UpdateData(FALSE);

	pDoc->m_sunAltitude = m_lightingSunAltitude;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}

void CStagePrefsLighting::OnLightingSunAzimuthRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_lightingSunAzimuth = m_origLightingSunAzimuth;
	UpdateData(FALSE);

	pDoc->m_sunAzimuth = m_lightingSunAzimuth;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}

void CStagePrefsLighting::OnLightingSunIntensityRestore() 
{

	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	m_lightingSunIntensity = m_origLightingSunIntensity;
	UpdateData(FALSE);

	m_lightingSunSliderIntensity.SetPos((int)(m_lightingSunIntensity * 100.0));
	pDoc->m_sunIntensity = m_lightingSunIntensity;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}


void CStagePrefsLighting::OnLightingSunFront() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	double x;
	double y;
	double z;
	double r;
	double rhat;
	double theta;
	double phi;

	x = pView->m_eye[0] - pView->m_eye[3];
	y = pView->m_eye[1] - pView->m_eye[4];
	z = pView->m_eye[2] - pView->m_eye[5];

	r = sqrt(x * x + y * y);

	if ((x > 0.0 && y >= 0.0) || x < 0.0)
	{
		theta = atan2(y, x);
	}
	else if (x > 0.0 && y < 0.0)
	{
		theta = 2.0 * PI + atan2(y, x);
	}
	else if (y > 0.0)
	{
		theta = PI / 2.0;
	}
	else if (y < 0.0)
	{
		theta = -PI / 2.0;
	}
	else
	{
		theta = 0.0;
	}

	rhat = sqrt(r * r + z * z);

	if (r != 0.0)
	{
		phi = atan2(z, r);
	}
	else if (z > 0.0)
	{
		phi = PI / 2.0;
	}
	else if (z < 0.0)
	{
		phi = -PI / 2.0;
	}
	else
	{
		phi = 0.0;
	}
	
	m_lightingSunAzimuth = (float)(theta * YO_RADIANS_TO_DEGREES);
	pDoc->m_sunAzimuth = m_lightingSunAzimuth;
	m_lightingSunAltitude = (float)(phi * YO_RADIANS_TO_DEGREES);
	pDoc->m_sunAltitude = m_lightingSunAltitude;
	UpdateData(FALSE);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}

void CStagePrefsLighting::OnLightingSunLeft() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	double x;
	double y;
	double z;
	double r;
	double rhat;
	double theta;
	double phi;

	x = pView->m_eye[0] - pView->m_eye[3];
	y = pView->m_eye[1] - pView->m_eye[4];
	z = pView->m_eye[2] - pView->m_eye[5];

	r = sqrt(x * x + y * y);

	if ((x > 0.0 && y >= 0.0) || x < 0.0)
	{
		theta = atan2(y, x);
	}
	else if (x > 0.0 && y < 0.0)
	{
		theta = 2.0 * PI + atan2(y, x);
	}
	else if (y > 0.0)
	{
		theta = PI / 2.0;
	}
	else if (y < 0.0)
	{
		theta = -PI / 2.0;
	}
	else
	{
		theta = 0.0;
	}

	rhat = sqrt(r * r + z * z);

	if (r != 0.0)
	{
		phi = atan2(z, r);
	}
	else if (z > 0.0)
	{
		phi = PI / 2.0;
	}
	else if (z < 0.0)
	{
		phi = -PI / 2.0;
	}
	else
	{
		phi = 0.0;
	}
	
	m_lightingSunAzimuth = (float)(theta * YO_RADIANS_TO_DEGREES) - 90.0f;
	if (m_lightingSunAzimuth < 0.0)
	{
		m_lightingSunAzimuth += 360.0;
	}
	pDoc->m_sunAzimuth = m_lightingSunAzimuth;
	m_lightingSunAltitude = (float)(phi * YO_RADIANS_TO_DEGREES);
	pDoc->m_sunAltitude = m_lightingSunAltitude;
	UpdateData(FALSE);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;		
}

void CStagePrefsLighting::OnLightingSunRight() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	double x;
	double y;
	double z;
	double r;
	double rhat;
	double theta;
	double phi;

	x = pView->m_eye[0] - pView->m_eye[3];
	y = pView->m_eye[1] - pView->m_eye[4];
	z = pView->m_eye[2] - pView->m_eye[5];

	r = sqrt(x * x + y * y);

	if ((x > 0.0 && y >= 0.0) || x < 0.0)
	{
		theta = atan2(y, x);
	}
	else if (x > 0.0 && y < 0.0)
	{
		theta = 2.0 * PI + atan2(y, x);
	}
	else if (y > 0.0)
	{
		theta = PI / 2.0;
	}
	else if (y < 0.0)
	{
		theta = -PI / 2.0;
	}
	else
	{
		theta = 0.0;
	}

	rhat = sqrt(r * r + z * z);

	if (r != 0.0)
	{
		phi = atan2(z, r);
	}
	else if (z > 0.0)
	{
		phi = PI / 2.0;
	}
	else if (z < 0.0)
	{
		phi = -PI / 2.0;
	}
	else
	{
		phi = 0.0;
	}
	
	m_lightingSunAzimuth = (float)(theta * YO_RADIANS_TO_DEGREES) + 90.0f;
	if (m_lightingSunAzimuth >= 360.0)
	{
		m_lightingSunAzimuth -= 360.0;
	}
	pDoc->m_sunAzimuth = m_lightingSunAzimuth;
	m_lightingSunAltitude = (float)(phi * YO_RADIANS_TO_DEGREES);
	pDoc->m_sunAltitude = m_lightingSunAltitude;
	UpdateData(FALSE);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;	
}

void CStagePrefsLighting::OnLightingDefaults() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	pDoc->m_lighting[1] = YO_DEFAULT_LIGHTING_TWO_SIDED;
	m_twoSide = YO_DEFAULT_LIGHTING_TWO_SIDED;
	::glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, YO_DEFAULT_LIGHTING_TWO_SIDED);

	pDoc->m_sunIntensity = YO_DEFAULT_SUN_INTENSITY;
	m_lightingSunIntensity = YO_DEFAULT_SUN_INTENSITY;
	m_lightingSunSliderIntensity.SetPos((int)(m_lightingSunIntensity * 100.0));

	pDoc->m_sunAzimuth = YO_DEFAULT_SUN_AZIMUTH;
	m_lightingSunAzimuth = YO_DEFAULT_SUN_AZIMUTH;

	pDoc->m_sunAltitude = YO_DEFAULT_SUN_ALTITUDE;
	m_lightingSunAltitude = YO_DEFAULT_SUN_ALTITUDE;

	UpdateData(FALSE);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	
}
