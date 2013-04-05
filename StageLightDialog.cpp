// StageLightDialog.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "stageViewPart.h"
#include "StageLightDialog.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageLightDialog dialog


CStageLightDialog::CStageLightDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStageLightDialog::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageLightDialog::IDD, pParent);

	//{{AFX_DATA_INIT(CStageLightDialog)
	m_lightEnabled = FALSE;
	m_lightIntensity = 0;
	m_lightAttenuation = 0;
	m_lightPointSource = FALSE;
	m_lightSpotlightAngle = 0;
	//}}AFX_DATA_INIT

	m_att = 0;
}


void CStageLightDialog::DoDataExchange(CDataExchange* pDX)
{

	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageLightDialog)
	DDX_Control(pDX, IDC_LIGHT_SLIDER_SPOTLIGHT_ANGLE, m_lightSliderSpotlightAngle);
	DDX_Control(pDX, IDC_LIGHT_SLIDER_INTENSITY, m_lightSliderIntensity);
	DDX_Control(pDX, IDC_LIGHT_SLIDER_ATTENUATION, m_lightSliderAttenuation);
	DDX_Check(pDX, IDC_LIGHT_ENABLED, m_lightEnabled);
	DDX_Text(pDX, IDC_LIGHT_INTENSITY, m_lightIntensity);
	DDV_MinMaxUInt(pDX, m_lightIntensity, 0, 255);
	DDX_Text(pDX, IDC_LIGHT_ATTENUATION, m_lightAttenuation);
	DDV_MinMaxUInt(pDX, m_lightAttenuation, 0, 100);
	DDX_Check(pDX, IDC_LIGHT_POINT_SOURCE, m_lightPointSource);
	DDX_Text(pDX, IDC_LIGHT_SPOTLIGHT_ANGLE, m_lightSpotlightAngle);
	DDV_MinMaxUInt(pDX, m_lightSpotlightAngle, 0, 180);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageLightDialog, CDialog)
	//{{AFX_MSG_MAP(CStageLightDialog)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_LIGHT_ATTENUATION, OnKillfocusLightAttenuation)
	ON_BN_CLICKED(IDC_LIGHT_ATTENUATION_LIST, OnLightAttenuationList)
	ON_BN_CLICKED(IDC_LIGHT_ENABLED, OnLightEnabled)
	ON_EN_KILLFOCUS(IDC_LIGHT_INTENSITY, OnKillfocusLightIntensity)
	ON_BN_CLICKED(IDC_LIGHT_POINT_SOURCE, OnLightPointSource)
	ON_EN_KILLFOCUS(IDC_LIGHT_SPOTLIGHT_ANGLE, OnKillfocusLightSpotlightAngle)
	ON_BN_CLICKED(IDC_RESTORE_LIGHT_ATTENUATION, OnRestoreLightAttenuation)
	ON_BN_CLICKED(IDC_RESTORE_LIGHT_INTENSITY, OnRestoreLightIntensity)
	ON_BN_CLICKED(IDC_RESTORE_LIGHT_SPOTLIGHT_ANGLE, OnRestoreLightSpotlightAngle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageLightDialog message handlers

void CStageLightDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}

BOOL CStageLightDialog::YoInitDialog() 
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

	m_origEnabled = ((CStageLight *)pDoc->m_currentDevice)->m_enabled;
	m_origPointSource = ((CStageLight *)pDoc->m_currentDevice)->m_pointSource;
	m_origIntensity = ((CStageLight *)pDoc->m_currentDevice)->m_intensity;
	for (i = 0; i < 3; i++)
	{
		m_origAttenuation[i] = ((CStageLight *)pDoc->m_currentDevice)->m_attenuation[i];
	}
	m_origSpotlightAngle = ((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff;

	
	m_lightEnabled = ((CStageLight *)pDoc->m_currentDevice)->m_enabled;
	m_lightPointSource = ((CStageLight *)pDoc->m_currentDevice)->m_pointSource;

	m_lightIntensity = (UINT)(((CStageLight *)pDoc->m_currentDevice)->m_intensity * 255.0);
	m_lightSliderIntensity.SetRange(0, 255);
	m_lightSliderIntensity.SetPos(m_lightIntensity);

	for (i = 0; i < 3; i++)
	{
		m_attenuation[i] = (UINT)(((CStageLight *)pDoc->m_currentDevice)->m_attenuation[i] * 10.0);
	}
	m_lightAttenuation = m_attenuation[0];
	m_lightSliderAttenuation.SetRange(0, 100);
	m_lightSliderAttenuation.SetPos(m_lightAttenuation);

	m_lightSpotlightAngle = (UINT)((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff;
	m_lightSliderSpotlightAngle.SetRange(0, 180);
	m_lightSliderSpotlightAngle.SetPos((UINT)m_lightSpotlightAngle);

	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStageLightDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	if ((CSliderCtrl *)pScrollBar == &m_lightSliderIntensity)
	{
		m_lightIntensity = m_lightSliderIntensity.GetPos();
		((CStageLight *)pDoc->m_currentDevice)->m_intensity = (GLfloat)m_lightIntensity / 255.0f;
	}
	else if ((CSliderCtrl *)pScrollBar == &m_lightSliderSpotlightAngle)
	{
		m_lightSpotlightAngle = m_lightSliderSpotlightAngle.GetPos();
		((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff = (GLfloat)m_lightSpotlightAngle;
		if (((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff > 90.0)
		{
			((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff = 180.0f;
		}
	}
	else if ((CSliderCtrl *)pScrollBar == &m_lightSliderAttenuation)
	{
		m_lightAttenuation = m_lightSliderAttenuation.GetPos();
		m_attenuation[m_att] = m_lightAttenuation;
		((CStageLight *)pDoc->m_currentDevice)->m_attenuation[m_att] = (GLfloat)m_attenuation[m_att] / 10.0f;
	}

	UpdateData(FALSE);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

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


void CStageLightDialog::OnKillfocusLightAttenuation() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_lightSliderAttenuation.SetPos(m_lightAttenuation);
	m_attenuation[m_att] = m_lightAttenuation;
	((CStageLight *)pDoc->m_currentDevice)->m_attenuation[m_att] = (GLfloat)m_attenuation[m_att] / 10.0f;
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
}


void CStageLightDialog::OnLightAttenuationList() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[32];
	
	pCBox = (CComboBox*)GetDlgItem(IDC_LIGHT_ATTENUATION_LIST);
	if (m_att == 2)
	{
		m_att = 0;
		pCBox->SetWindowText("Constant");
	}
	else if (m_att == 0)
	{
		m_att++;
		pCBox->SetWindowText("Linear");
	}
	else if (m_att == 1)
	{
		m_att++;
		pCBox->SetWindowText("Quad");
	}
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)GetDlgItem(IDC_LIGHT_ATTENUATION);
	sprintf(s, "%d", m_attenuation[m_att]);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)GetDlgItem(IDC_LIGHT_SLIDER_ATTENUATION);
	((CSliderCtrl *)pCBox)->SetPos(m_attenuation[m_att]);

	return;
}


void CStageLightDialog::OnLightEnabled() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_lightEnabled == FALSE)
	{
		((CStageLight *)pDoc->m_currentDevice)->YoFreeLight();
	}
	else
	{
		if (((CStageLight *)pDoc->m_currentDevice)->YoGetLight() == FALSE)
		{
			AfxMessageBox("Enable Light Failed.  Disable a different light and retry.");
			m_lightEnabled = FALSE;
			UpdateData(FALSE);
		}
	}
		
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
	
}


void CStageLightDialog::OnKillfocusLightIntensity() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_lightSliderIntensity.SetPos(m_lightIntensity);
	((CStageLight *)pDoc->m_currentDevice)->m_intensity = (GLfloat)m_lightIntensity / 255.0f;
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
	
}


void CStageLightDialog::OnLightPointSource() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	((CStageLight *)pDoc->m_currentDevice)->m_pointSource = m_lightPointSource;
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;	
}


void CStageLightDialog::OnKillfocusLightSpotlightAngle() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_lightSliderSpotlightAngle.SetPos(m_lightSpotlightAngle);
	((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff = (GLfloat)m_lightSpotlightAngle;
	if (((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff >= 90.0)
	{
		((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff = 180.0f;
	}
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
}


void CStageLightDialog::OnRestoreLightAttenuation() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	((CStageLight *)pDoc->m_currentDevice)->m_attenuation[m_att] = m_origAttenuation[m_att];
	m_lightAttenuation = (UINT)(((CStageLight *)pDoc->m_currentDevice)->m_attenuation[m_att] * 10.0);
	UpdateData(FALSE);

	m_lightSliderAttenuation.SetPos(m_lightAttenuation);

	pView->YoRender(YO_RENDER_FULL);

	return;		
}


void CStageLightDialog::OnRestoreLightIntensity() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	((CStageLight *)pDoc->m_currentDevice)->m_intensity = m_origIntensity;
	m_lightIntensity = (UINT)(((CStageLight *)pDoc->m_currentDevice)->m_intensity * 255.0);
	UpdateData(FALSE);

	m_lightSliderIntensity.SetPos(m_lightIntensity);

	pView->YoRender(YO_RENDER_FULL);

	return;	
}


void CStageLightDialog::OnRestoreLightSpotlightAngle() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff = m_origSpotlightAngle;
	m_lightSpotlightAngle = (UINT)((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff;
	UpdateData(FALSE);

	m_lightSliderSpotlightAngle.SetPos(m_lightSpotlightAngle);

	pView->YoRender(YO_RENDER_FULL);

	return;
}

void CStageLightDialog::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}
