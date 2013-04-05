// StageViewLightPart.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
//#include "StageViewPart.h"
//#include "StageChooseName.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageViewLightPart dialog

/****

CStageViewLightPart::CStageViewLightPart(CWnd* pParent)
	: CDialog(CStageViewLightPart::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageViewLightPart::IDD, pParent);

	//{{AFX_DATA_INIT(CStageViewLightPart)
	m_deviceName = _T("");
	m_deviceVisible = FALSE;
	m_parentName = _T("");
	m_partAlpha = 0;
	m_partBlue = 0;
	m_partGreen = 0;
	m_partRed = 0;
	m_partName = _T("");
	m_partShininess = 0;
	m_textureName = _T("");
	m_lightIntensity = 0;
	m_lightEnabled = FALSE;
	m_lightPointSource = FALSE;
	m_lightSpotlightAngle = 0;
	m_lightAttenuation = 0;
	//}}AFX_DATA_INIT

	m_att = 0;

}


void CStageViewLightPart::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageViewLightPart)
	DDX_Control(pDX, IDC_LIGHT_SLIDER_SPOTLIGHT_ANGLE, m_lightSliderSpotlightAngle);
	DDX_Control(pDX, IDC_LIGHT_SLIDER_INTENSITY, m_lightSliderIntensity);
	DDX_Control(pDX, IDC_LIGHT_SLIDER_ATTENUATION, m_lightSliderAttenuation);
	DDX_Control(pDX, IDC_TXYZ, m_txyz);
	DDX_Control(pDX, IDC_PART_SLIDER_SHININESS, m_partSliderShininess);
	DDX_Control(pDX, IDC_PART_SLIDER_RED, m_partSliderRed);
	DDX_Control(pDX, IDC_PART_SLIDER_GREEN, m_partSliderGreen);
	DDX_Control(pDX, IDC_PART_SLIDER_BLUE, m_partSliderBlue);
	DDX_Control(pDX, IDC_PART_SLIDER_ALPHA, m_partSliderAlpha);
	DDX_Control(pDX, IDC_PART_RENDER_MODE, m_partRenderMode);
	DDX_Control(pDX, IDC_PART_MATERIAL, m_partMaterial);
	DDX_Text(pDX, IDC_DEVICE_NAME, m_deviceName);
	DDV_MaxChars(pDX, m_deviceName, 64);
	DDX_Check(pDX, IDC_DEVICE_VISIBLE, m_deviceVisible);
	DDX_Text(pDX, IDC_PARENT_NAME, m_parentName);
	DDX_Text(pDX, IDC_PART_ALPHA, m_partAlpha);
	DDV_MinMaxUInt(pDX, m_partAlpha, 0, 255);
	DDX_Text(pDX, IDC_PART_BLUE, m_partBlue);
	DDV_MinMaxUInt(pDX, m_partBlue, 0, 255);
	DDX_Text(pDX, IDC_PART_GREEN, m_partGreen);
	DDV_MinMaxUInt(pDX, m_partGreen, 0, 255);
	DDX_Text(pDX, IDC_PART_RED, m_partRed);
	DDV_MinMaxUInt(pDX, m_partRed, 0, 255);
	DDX_Text(pDX, IDC_PART_NAME, m_partName);
	DDX_Text(pDX, IDC_PART_SHININESS, m_partShininess);
	DDV_MinMaxUInt(pDX, m_partShininess, 0, 128);
	DDX_Text(pDX, IDC_TEXTURE_NAME, m_textureName);
	DDX_Text(pDX, IDC_LIGHT_INTENSITY, m_lightIntensity);
	DDV_MinMaxUInt(pDX, m_lightIntensity, 0, 255);
	DDX_Check(pDX, IDC_LIGHT_ENABLED, m_lightEnabled);
	DDX_Check(pDX, IDC_LIGHT_POINT_SOURCE, m_lightPointSource);
	DDX_Text(pDX, IDC_LIGHT_SPOTLIGHT_ANGLE, m_lightSpotlightAngle);
	DDV_MinMaxUInt(pDX, m_lightSpotlightAngle, 0, 180);
	DDX_Text(pDX, IDC_LIGHT_ATTENUATION, m_lightAttenuation);
	DDV_MinMaxUInt(pDX, m_lightAttenuation, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageViewLightPart, CDialog)
	//{{AFX_MSG_MAP(CStageViewLightPart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageViewLightPart message handlers

void CStageViewLightPart::OnCancel() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	int i;

	pDoc->m_currentDevice->m_visible = m_origVisible;
	for (i = 0; i < 3; i++)
	{
		pDoc->m_currentPart->m_translate[i] = m_origTranslate[i];
		pDoc->m_currentPart->m_rotate[i] = m_origRotate[i];
	}
	sprintf(pDoc->m_currentDevice->m_name, "%s", m_origDeviceName);
	sprintf(pDoc->m_currentDevice->m_parent, "%s", m_origParent);
	sprintf(pDoc->m_currentPart->m_partName, "%s", m_origPartName);
	for (i = 0; i < 4; i++)
	{
		pDoc->m_currentPart->m_ambient[i] = m_origAmbient[i];
		pDoc->m_currentPart->m_diffuse[i] = m_origDiffuse[i];
		pDoc->m_currentPart->m_specular[i] = m_origSpecular[i];
		pDoc->m_currentPart->m_emission[i] = m_origEmission[i];
	}
	pDoc->m_currentPart->m_shininess = m_origShininess;
	pDoc->m_currentPart->m_txyz = m_origTxyz;
	pDoc->m_currentPart->m_renderMode = m_origRenderMode;

	((CStageLight *)pDoc->m_currentDevice)->m_intensity = m_origIntensity;
	((CStageLight *)pDoc->m_currentDevice)->m_enabled = m_origEnabled;
	((CStageLight *)pDoc->m_currentDevice)->m_pointSource = m_origPointSource;
	((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff = m_origSpotlightAngle;
	for (i = 0; i < 3; i++)
	{
		((CStageLight *)pDoc->m_currentDevice)->m_attenuation[i] = m_origAttenuation[i];
	}

	((CMainFrame *)pMainFrame)->m_viewLightPartActive = FALSE;
	CDialog::OnCancel();
	DestroyWindow();
	pView->YoRender(YO_RENDER_FULL);
}

void CStageViewLightPart::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your message handler code here and/or call default
	if ((CSliderCtrl *)pScrollBar == &m_partSliderRed)
	{
		m_partRed = m_partSliderRed.GetPos();
		YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_RED);
	}
	else if ((CSliderCtrl *)pScrollBar == &m_partSliderGreen)
	{
		m_partGreen = m_partSliderGreen.GetPos();
		YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_GREEN);
	}
	else if ((CSliderCtrl *)pScrollBar == &m_partSliderBlue)
	{
		m_partBlue = m_partSliderBlue.GetPos();
		YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_BLUE);
	}
	else if ((CSliderCtrl *)pScrollBar == &m_partSliderAlpha)
	{
		m_partAlpha = m_partSliderAlpha.GetPos();
		YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_ALPHA);
	}
	else if ((CSliderCtrl *)pScrollBar == &m_partSliderShininess)
	{
		m_partShininess = m_partSliderShininess.GetPos();
		pDoc->m_currentPart->m_shininess = (GLfloat)m_partShininess;
	}
	// light specific
	else if ((CSliderCtrl *)pScrollBar == &m_lightSliderIntensity)
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
}


void CStageViewLightPart::YoUpdateMaterial(int type, UINT rgba)
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	//UpdateData(TRUE);

	if (type == 0)  // ambient
	{
		if (rgba == YO_RED)
		{
			m_ambient[rgba] = m_partRed;
		}
		else if (rgba == YO_GREEN)
		{
			m_ambient[rgba] = m_partGreen;
		}
		else if (rgba == YO_BLUE)
		{
			m_ambient[rgba] = m_partBlue;
		}
		else if (rgba == YO_ALPHA)
		{
			m_ambient[rgba] = m_partAlpha;
		}
		pDoc->m_currentPart->m_ambient[rgba] = (GLfloat)m_ambient[rgba] / 255.0f;
	}

	else if (type == 1)  // diffuse
	{
		if (rgba == YO_RED)
		{
			m_diffuse[rgba] = m_partRed;
		}
		else if (rgba == YO_GREEN)
		{
			m_diffuse[rgba] = m_partGreen;
		}
		else if (rgba == YO_BLUE)
		{
			m_diffuse[rgba] = m_partBlue;
		}
		else if (rgba == YO_ALPHA)
		{
			m_diffuse[rgba] = m_partAlpha;
		}
		pDoc->m_currentPart->m_diffuse[rgba] = (GLfloat)m_diffuse[rgba] / 255.0f;
	}

	else if (type == 2)  // emission
	{
		if (rgba == YO_RED)
		{
			m_emission[rgba] = m_partRed;
		}
		else if (rgba == YO_GREEN)
		{
			m_emission[rgba] = m_partGreen;
		}
		else if (rgba == YO_BLUE)
		{
			m_emission[rgba] = m_partBlue;
		}
		else if (rgba == YO_ALPHA)
		{
			m_emission[rgba] = m_partAlpha;
		}
		pDoc->m_currentPart->m_emission[rgba] = (GLfloat)m_emission[rgba] / 255.0f;
	}
	else if (type == 3)  // specular
	{
		if (rgba == YO_RED)
		{
			m_specular[rgba] = m_partRed;
		}
		else if (rgba == YO_GREEN)
		{
			m_specular[rgba] = m_partGreen;
		}
		else if (rgba == YO_BLUE)
		{
			m_specular[rgba] = m_partBlue;
		}
		else if (rgba == YO_ALPHA)
		{
			m_specular[rgba] = m_partAlpha;
		}
		pDoc->m_currentPart->m_specular[rgba] = (GLfloat)m_specular[rgba] / 255.0f;
	}
	return;
}


BOOL CStageViewLightPart::YoInitDialog() 
{
	
	CWnd* pCBox;
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	int i;
	int dWidth;
	RECT rect;
	RECT mfRect;
	CREATESTRUCT cs;
	char s[64];

	m_init = TRUE;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    cs.cy = ::GetSystemMetrics(SM_CYSCREEN); 
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN); 

	this->GetWindowRect(&rect);
	dWidth = (rect.right - rect.left);
	pMainFrame->GetWindowRect(&mfRect);
	rect.right = YO_MIN(mfRect.right + dWidth, cs.cx);
	rect.left = rect.right - dWidth;
	rect.right -= 3;
	rect.left -= 3;
	rect.top -= 8;
	rect.bottom -= 8;
	this->MoveWindow(&rect, TRUE);

	m_origVisible = pDoc->m_currentDevice->m_visible;
	for (i = 0; i < 3; i++)
	{
		m_origTranslate[i] = pDoc->m_currentPart->m_translate[i];
		m_origRotate[i] = pDoc->m_currentPart->m_rotate[i];
	}
	sprintf(m_origDeviceName, "%s", pDoc->m_currentDevice->m_name);
	sprintf(m_origParent, "%s", pDoc->m_currentDevice->m_parent);
	sprintf(m_origPartName, "%s", pDoc->m_currentPart->m_partName);
	for (i = 0; i < 4; i++)
	{
		m_origAmbient[i] = pDoc->m_currentPart->m_ambient[i];
		m_origDiffuse[i] = pDoc->m_currentPart->m_diffuse[i];
		m_origSpecular[i] = pDoc->m_currentPart->m_specular[i];
		m_origEmission[i] = pDoc->m_currentPart->m_emission[i];
	}
	m_origShininess = pDoc->m_currentPart->m_shininess;
	m_origTxyz = pDoc->m_currentPart->m_txyz;
	m_origRenderMode = pDoc->m_currentPart->m_renderMode;

	// init dialog
	m_deviceVisible = pDoc->m_currentDevice->m_visible;

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_translate[0] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRANSLATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_translate[1] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRANSLATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_translate[2] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRANSLATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_rotate[0]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_rotate[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_rotate[2]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_ROTATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	//m_translateX = pDoc->m_currentPart->m_translate[0];
	//m_translateY = pDoc->m_currentPart->m_translate[1];
	//m_translateZ = pDoc->m_currentPart->m_translate[2];
	//m_rotateX = pDoc->m_currentPart->m_rotate[0];
	//m_rotateY = pDoc->m_currentPart->m_rotate[1];
	//m_rotateZ = pDoc->m_currentPart->m_rotate[2];
	m_deviceName = CString(pDoc->m_currentDevice->m_name);
	m_parentName = CString(pDoc->m_currentDevice->m_parent);
	m_partName = CString(pDoc->m_currentPart->m_partName);

	for (i = 0; i < 4; i++)
	{
		m_ambient[i] = (UINT)(pDoc->m_currentPart->m_ambient[i] * 255.0);
		m_diffuse[i] = (UINT)(pDoc->m_currentPart->m_diffuse[i] * 255.0);
		m_specular[i] = (UINT)(pDoc->m_currentPart->m_specular[i] * 255.0);
		m_emission[i] = (UINT)(pDoc->m_currentPart->m_emission[i] * 255.0);
	}
	m_partShininess = (UINT)(pDoc->m_currentPart->m_shininess);

	m_partRed = m_ambient[0];
	m_partGreen = m_ambient[1];
	m_partBlue = m_ambient[2];
	m_partAlpha = m_ambient[3];

	m_partMaterial.ResetContent();
	m_partMaterial.AddString("Ambient");
	m_partMaterial.AddString("Diffuse");
	m_partMaterial.AddString("Specular");
	m_partMaterial.AddString("Emission");
	m_partMaterial.SetCurSel(0);

	m_txyz.ResetContent();
	m_txyz.AddString("txyz");
	m_txyz.AddString("txzy");
	m_txyz.AddString("tyxz");
	m_txyz.AddString("tyzx");
	m_txyz.AddString("tzxy");
	m_txyz.AddString("tzyx");
	m_txyz.AddString("xyzt");
	m_txyz.AddString("xzyt");
	m_txyz.AddString("yxzt");
	m_txyz.AddString("yzxt");
	m_txyz.AddString("zxyt");
	m_txyz.AddString("zyxt");
	m_txyz.SetCurSel(pDoc->m_currentPart->m_txyz);

	m_partRenderMode.ResetContent();
	m_partRenderMode.AddString("Wireframe");
	m_partRenderMode.AddString("Filled Polygon");
	m_partRenderMode.AddString("Polygon Point");
	m_partRenderMode.AddString("Polygon Line");
	m_partRenderMode.AddString("Textured Polygon");
	m_partRenderMode.AddString("Textured Point");
	m_partRenderMode.AddString("Textured Line");
	m_partRenderMode.SetCurSel(pDoc->m_currentPart->m_renderMode);

	m_partSliderRed.SetRange(0, 255);
	m_partSliderRed.SetPos(m_partRed);
	m_partSliderGreen.SetRange(0, 255);
	m_partSliderGreen.SetPos(m_partGreen);
	m_partSliderBlue.SetRange(0, 255);
	m_partSliderBlue.SetPos(m_partBlue);
	m_partSliderAlpha.SetRange(0, 255);
	m_partSliderAlpha.SetPos(m_partAlpha);
	m_partSliderShininess.SetRange(0, 128);
	m_partSliderShininess.SetPos(m_partShininess);


	
	if (m_deviceVisible)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_DEVICE_VISIBLE);
		((CButton *)pCBox)->SetCheck(1);
	}

	// do light specific initialization
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

void CStageViewLightPart::OnKillfocusPartAlpha() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();

	UpdateData(TRUE);
	m_partSliderAlpha.SetPos(m_partAlpha);
	YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_ALPHA);
	pView->YoRender(YO_RENDER_FULL);
	
}

void CStageViewLightPart::OnKillfocusPartBlue() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();

	UpdateData(TRUE);
	m_partSliderAlpha.SetPos(m_partBlue);
	YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_BLUE);
	pView->YoRender(YO_RENDER_FULL);		
}

void CStageViewLightPart::OnKillfocusPartGreen() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();

	UpdateData(TRUE);
	m_partSliderAlpha.SetPos(m_partGreen);
	YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_GREEN);
	pView->YoRender(YO_RENDER_FULL);
	
}

void CStageViewLightPart::OnKillfocusPartRed() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();

	UpdateData(TRUE);
	m_partSliderAlpha.SetPos(m_partRed);
	YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_RED);
	pView->YoRender(YO_RENDER_FULL);
	
}

void CStageViewLightPart::OnKillfocusPartShininess() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_partSliderShininess.SetPos(m_partShininess);
	pDoc->m_currentPart->m_shininess = (GLfloat)m_partShininess;
	pView->YoRender(YO_RENDER_FULL);
}

void CStageViewLightPart::OnListDevices() 
{
	// TODO: Add your control notification handler code here
	
}

void CStageViewLightPart::OnListParents() 
{
	// TODO: Add your control notification handler code here
	
}

void CStageViewLightPart::OnListParts() 
{
	// TODO: Add your control notification handler code here
	
}

void CStageViewLightPart::OnSelchangePartMaterial() 
{
	// TODO: Add your control notification handler code here
	if (m_partMaterial.GetCurSel() == 0)  // ambient
	{
		m_partRed = m_ambient[0];
		m_partGreen = m_ambient[1];
		m_partBlue = m_ambient[2];
		m_partAlpha = m_ambient[3];
		m_partSliderRed.SetPos(m_partRed);
		m_partSliderGreen.SetPos(m_partGreen);
		m_partSliderBlue.SetPos(m_partBlue);
		m_partSliderAlpha.SetPos(m_partAlpha);
	}
	else if (m_partMaterial.GetCurSel() == 1)  // diffuse
	{
		m_partRed = m_diffuse[0];
		m_partGreen = m_diffuse[1];
		m_partBlue = m_diffuse[2];
		m_partAlpha = m_diffuse[3];
		m_partSliderRed.SetPos(m_partRed);
		m_partSliderGreen.SetPos(m_partGreen);
		m_partSliderBlue.SetPos(m_partBlue);
		m_partSliderAlpha.SetPos(m_partAlpha);
	}
	else if (m_partMaterial.GetCurSel() == 2)  // emission
	{
		m_partRed = m_emission[0];
		m_partGreen = m_emission[1];
		m_partBlue = m_emission[2];
		m_partAlpha = m_emission[3];
		m_partSliderRed.SetPos(m_partRed);
		m_partSliderGreen.SetPos(m_partGreen);
		m_partSliderBlue.SetPos(m_partBlue);
		m_partSliderAlpha.SetPos(m_partAlpha);
	}
	else if (m_partMaterial.GetCurSel() == 3)  // specular
	{
		m_partRed = m_specular[0];
		m_partGreen = m_specular[1];
		m_partBlue = m_specular[2];
		m_partAlpha = m_specular[3];
		m_partSliderRed.SetPos(m_partRed);
		m_partSliderGreen.SetPos(m_partGreen);
		m_partSliderBlue.SetPos(m_partBlue);
		m_partSliderAlpha.SetPos(m_partAlpha);
	}

	UpdateData(FALSE);
}

void CStageViewLightPart::OnOK() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 

	// TODO: Add extra validation here
	((CMainFrame *)pMainFrame)->m_viewLightPartActive = FALSE;
	CDialog::OnOK();
	DestroyWindow();


}

void CStageViewLightPart::OnKillfocusLightAttenuation() 
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
}

void CStageViewLightPart::OnKillfocusLightIntensity() 
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
}

void CStageViewLightPart::OnKillfocusLightSpotlightAngle() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_lightSliderSpotlightAngle.SetPos(m_lightSpotlightAngle);
	((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff = (GLfloat)m_lightSpotlightAngle;
	if (((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff > 90.0)
	{
		((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff = 180.0f;
	}
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);}

void CStageViewLightPart::OnListAttenuation() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[32];
	
	pCBox = (CComboBox*)GetDlgItem(IDC_LIST_ATTENUATION);
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
	
}

void CStageViewLightPart::OnKillfocusRotateX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_X);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &pDoc->m_currentPart->m_rotate[0]);
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewLightPart::OnKillfocusRotateY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Y);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &pDoc->m_currentPart->m_rotate[1]);
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewLightPart::OnKillfocusRotateZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Z);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &pDoc->m_currentPart->m_rotate[2]);
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewLightPart::OnKillfocusTranslateX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_X);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);
	pDoc->m_currentPart->m_translate[0] = t / pDoc->m_unitScaleFactor;
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
	
}

void CStageViewLightPart::OnKillfocusTranslateY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_Y);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);
	pDoc->m_currentPart->m_translate[1] = t / pDoc->m_unitScaleFactor;
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
	
}

void CStageViewLightPart::OnKillfocusTranslateZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_Z);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);
	pDoc->m_currentPart->m_translate[2] = t / pDoc->m_unitScaleFactor;
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
	
}

void CStageViewLightPart::PostNcDestroy() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
	delete this;
}

void CStageViewLightPart::OnSelchangeTxyz() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	pDoc->m_currentPart->m_txyz = (UINT)m_txyz.GetCurSel();
	pView->YoRender(YO_RENDER_FULL);	
}

void CStageViewLightPart::OnSelchangePartRenderMode() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	pDoc->m_currentPart->m_renderMode = (UINT)m_partRenderMode.GetCurSel();
	pView->YoRender(YO_RENDER_FULL);	
}

void CStageViewLightPart::OnLightEnabled() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	((CStageLight *)pDoc->m_currentDevice)->m_enabled = m_lightEnabled;
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	
}

void CStageViewLightPart::OnLightPointSource() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	((CStageLight *)pDoc->m_currentDevice)->m_pointSource = m_lightPointSource;
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	
}

void CStageViewLightPart::OnDeviceVisible() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	((CStageLight *)pDoc->m_currentDevice)->m_visible = m_deviceVisible;
	
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	
}
***/
