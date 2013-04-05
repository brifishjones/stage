// StageViewPart.cpp : implementation file
//


#include "stdafx.h"
#include "stage.h"
#include "StageInheritMaterial.h"
#include "StageViewPart.h"
#include "StageLightDialog.h"
#include "StageRobot6Dlg.h"
#include "StageRotaryTableDlg.h"
#include "StageConveyorDlg.h"
#include "StageCameraDlg.h"
#include "StageGripperDlg.h"
#include "StageBarCodeReaderDlg.h"
#include "StageBarrettHandDlg.h"
#include "StageScaleDlg.h"
#include "StageTrainDlg.h"
//#include "StageChooseName.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"
#include "image.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageViewPart dialog


CStageViewPart::CStageViewPart(CWnd* pParent /*=NULL*/)
	: CDialog(CStageViewPart::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageViewPart::IDD, pParent);

	//{{AFX_DATA_INIT(CStageViewPart)
	m_deviceVisible = FALSE;
	m_partAlpha = 0;
	m_partBlue = 0;
	m_partGreen = 0;
	m_partRed = 0;
	m_partShininess = 0;
	m_textureBlending = FALSE;
	m_originVisible = FALSE;
	m_originAltDisplayed = FALSE;
	//}}AFX_DATA_INIT
}


void CStageViewPart::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageViewPart)
	DDX_Control(pDX, IDC_SNAP_TO_LIST, m_snapToList);
	DDX_Control(pDX, IDC_PART_RENDER_MODE, m_partRenderMode);
	DDX_Control(pDX, IDC_PART_SLIDER_SHININESS, m_partSliderShininess);
	DDX_Control(pDX, IDC_TXYZ, m_txyz);
	DDX_Control(pDX, IDC_PART_MATERIAL, m_partMaterial);
	DDX_Control(pDX, IDC_PART_SLIDER_RED, m_partSliderRed);
	DDX_Control(pDX, IDC_PART_SLIDER_GREEN, m_partSliderGreen);
	DDX_Control(pDX, IDC_PART_SLIDER_BLUE, m_partSliderBlue);
	DDX_Control(pDX, IDC_PART_SLIDER_ALPHA, m_partSliderAlpha);
	DDX_Check(pDX, IDC_DEVICE_VISIBLE, m_deviceVisible);
	DDX_Text(pDX, IDC_PART_ALPHA, m_partAlpha);
	DDV_MinMaxUInt(pDX, m_partAlpha, 0, 255);
	DDX_Text(pDX, IDC_PART_BLUE, m_partBlue);
	DDV_MinMaxUInt(pDX, m_partBlue, 0, 255);
	DDX_Text(pDX, IDC_PART_GREEN, m_partGreen);
	DDV_MinMaxUInt(pDX, m_partGreen, 0, 255);
	DDX_Text(pDX, IDC_PART_RED, m_partRed);
	DDV_MinMaxUInt(pDX, m_partRed, 0, 255);
	DDX_Text(pDX, IDC_PART_SHININESS, m_partShininess);
	DDV_MinMaxUInt(pDX, m_partShininess, 0, 128);
	DDX_Check(pDX, IDC_TEXTURE_BLENDING, m_textureBlending);
	DDX_Check(pDX, IDC_ORIGIN_VISIBLE, m_originVisible);
	DDX_Check(pDX, IDC_ORIGIN_ALT_DISPLAYED, m_originAltDisplayed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageViewPart, CDialog)
	//{{AFX_MSG_MAP(CStageViewPart)
	ON_EN_KILLFOCUS(IDC_PART_ALPHA, OnKillfocusPartAlpha)
	ON_EN_KILLFOCUS(IDC_PART_BLUE, OnKillfocusPartBlue)
	ON_EN_KILLFOCUS(IDC_PART_GREEN, OnKillfocusPartGreen)
	ON_EN_KILLFOCUS(IDC_PART_RED, OnKillfocusPartRed)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_PART_MATERIAL, OnSelchangePartMaterial)
	ON_EN_KILLFOCUS(IDC_PART_SHININESS, OnKillfocusPartShininess)
	ON_EN_KILLFOCUS(IDC_TRANSLATE_X, OnKillfocusTranslateX)
	ON_EN_KILLFOCUS(IDC_TRANSLATE_Y, OnKillfocusTranslateY)
	ON_EN_KILLFOCUS(IDC_TRANSLATE_Z, OnKillfocusTranslateZ)
	ON_EN_KILLFOCUS(IDC_ROTATE_X, OnKillfocusRotateX)
	ON_EN_KILLFOCUS(IDC_ROTATE_Y, OnKillfocusRotateY)
	ON_EN_KILLFOCUS(IDC_ROTATE_Z, OnKillfocusRotateZ)
	ON_CBN_SELCHANGE(IDC_PART_RENDER_MODE, OnSelchangePartRenderMode)
	ON_CBN_SELCHANGE(IDC_TXYZ, OnSelchangeTxyz)
	ON_BN_CLICKED(IDC_DEVICE_VISIBLE, OnDeviceVisible)
	ON_BN_CLICKED(IDC_ROTATE_RESTORE, OnRotateRestore)
	ON_BN_CLICKED(IDC_TRANSLATE_RESTORE, OnTranslateRestore)
	ON_BN_CLICKED(IDC_TRANSLATE_DECREASE_X, OnTranslateDecreaseX)
	ON_BN_CLICKED(IDC_TRANSLATE_DECREASE_Y, OnTranslateDecreaseY)
	ON_BN_CLICKED(IDC_TRANSLATE_DECREASE_Z, OnTranslateDecreaseZ)
	ON_BN_CLICKED(IDC_TRANSLATE_INCREASE_X, OnTranslateIncreaseX)
	ON_BN_CLICKED(IDC_TRANSLATE_INCREASE_Y, OnTranslateIncreaseY)
	ON_BN_CLICKED(IDC_TRANSLATE_INCREASE_Z, OnTranslateIncreaseZ)
	ON_BN_CLICKED(IDC_ALPHA_RESTORE, OnAlphaRestore)
	ON_BN_CLICKED(IDC_BLUE_RESTORE, OnBlueRestore)
	ON_BN_CLICKED(IDC_GREEN_RESTORE, OnGreenRestore)
	ON_BN_CLICKED(IDC_RED_RESTORE, OnRedRestore)
	ON_BN_CLICKED(IDC_SHININESS_RESTORE, OnShininessRestore)
	ON_BN_CLICKED(IDC_PART_PARENT_INHERIT, OnPartParentInherit)
	ON_BN_CLICKED(IDC_TEXTURE_BLENDING, OnTextureBlending)
	ON_BN_CLICKED(IDC_TEXTURE_DELETE, OnTextureDelete)
	ON_BN_CLICKED(IDC_TEXTURE_NEW, OnTextureNew)
	ON_BN_CLICKED(IDC_TEXTURE_ROTATE, OnTextureRotate)
	ON_CBN_SELCHANGE(IDC_SNAP_TO_LIST, OnSelchangeSnapToList)
	ON_BN_CLICKED(IDC_SNAP_TO, OnSnapTo)
	ON_EN_KILLFOCUS(IDC_BAR_CODE, OnKillfocusBarCode)
	ON_EN_KILLFOCUS(IDC_MASS, OnKillfocusMass)
	ON_BN_CLICKED(IDC_ROTATE_INCREASE_X, OnRotateIncreaseX)
	ON_BN_CLICKED(IDC_ROTATE_INCREASE_Y, OnRotateIncreaseY)
	ON_BN_CLICKED(IDC_ROTATE_INCREASE_Z, OnRotateIncreaseZ)
	ON_BN_CLICKED(IDC_ROTATE_DECREASE_X, OnRotateDecreaseX)
	ON_BN_CLICKED(IDC_ROTATE_DECREASE_Y, OnRotateDecreaseY)
	ON_BN_CLICKED(IDC_ROTATE_DECREASE_Z, OnRotateDecreaseZ)
	ON_EN_KILLFOCUS(IDC_SMOOTH_SHADE_ANGLE, OnKillfocusSmoothShadeAngle)
	ON_BN_CLICKED(IDC_ORIGIN_ALT_CREATE, OnOriginAltCreate)
	ON_BN_CLICKED(IDC_ORIGIN_ALT_DISPLAYED, OnOriginAltDisplayed)
	ON_BN_CLICKED(IDC_ORIGIN_VISIBLE, OnOriginVisible)
	ON_EN_SETFOCUS(IDC_TRANSLATE_X, OnSetfocusTranslateX)
	ON_EN_SETFOCUS(IDC_BAR_CODE, OnSetfocusBarCode)
	ON_EN_SETFOCUS(IDC_MASS, OnSetfocusMass)
	ON_EN_SETFOCUS(IDC_PART_ALPHA, OnSetfocusPartAlpha)
	ON_EN_SETFOCUS(IDC_PART_BLUE, OnSetfocusPartBlue)
	ON_EN_SETFOCUS(IDC_PART_GREEN, OnSetfocusPartGreen)
	ON_EN_SETFOCUS(IDC_PART_RED, OnSetfocusPartRed)
	ON_EN_SETFOCUS(IDC_PART_SHININESS, OnSetfocusPartShininess)
	ON_EN_SETFOCUS(IDC_ROTATE_X, OnSetfocusRotateX)
	ON_EN_SETFOCUS(IDC_ROTATE_Y, OnSetfocusRotateY)
	ON_EN_SETFOCUS(IDC_ROTATE_Z, OnSetfocusRotateZ)
	ON_EN_SETFOCUS(IDC_SMOOTH_SHADE_ANGLE, OnSetfocusSmoothShadeAngle)
	ON_EN_SETFOCUS(IDC_TRANSLATE_Y, OnSetfocusTranslateY)
	ON_EN_SETFOCUS(IDC_TRANSLATE_Z, OnSetfocusTranslateZ)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageViewPart message handlers

BOOL CStageViewPart::YoInitDialog() 
{

	CWnd* pCBox;
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	int i;
	GLint index;
	int dWidth;
	int dHeight;
	RECT rect;
	RECT mfRect;
	CREATESTRUCT cs;
	char s[256];
	CStagePolygonList *currentPolygonList;

	m_init = TRUE;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    cs.cy = ::GetSystemMetrics(SM_CYSCREEN); 
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN); 

	this->GetWindowRect(&rect);
	dWidth = rect.right - rect.left;
	pMainFrame->GetWindowRect(&mfRect);
	rect.right = YO_MIN(mfRect.right + dWidth, cs.cx);
	rect.left = rect.right - dWidth;
	rect.right -= 3;
	rect.left -= 3;
	if (rect.top >= mfRect.top)
	{
		dHeight = rect.bottom - rect.top;
		rect.top = mfRect.top;
		rect.bottom = rect.top + dHeight;
	}
	//rect.top -= 20;
	//rect.bottom -= 20;
	this->MoveWindow(&rect, TRUE);

	m_origVisible = pDoc->m_currentDevice->m_visible;
	m_origMass = pDoc->m_currentDevice->m_mass;
	sprintf(m_origBarCode, "%s", pDoc->m_currentDevice->m_barCode);
	for (i = 0; i < 3; i++)
	{
		m_origTranslate[i] = pDoc->m_currentPart->m_translate[i];
		m_origRotate[i] = pDoc->m_currentPart->m_rotate[i];
	}
	for (i = 0; i < 4; i++)
	{
		m_origAmbient[i] = pDoc->m_currentPart->m_ambient[i];
		m_origDiffuse[i] = pDoc->m_currentPart->m_diffuse[i];
		m_origSpecular[i] = pDoc->m_currentPart->m_specular[i];
		m_origEmission[i] = pDoc->m_currentPart->m_emission[i];
		m_origWireframe[i] = pDoc->m_currentPart->m_wireframe[i];
	}
	m_origShininess = pDoc->m_currentPart->m_shininess;
	m_origTxyz = pDoc->m_currentPart->m_txyz;
	m_origRenderMode = pDoc->m_currentPart->m_renderMode;
	m_origSmoothShadeAngle = pDoc->m_currentPart->m_smoothShadeAngle;
	m_origOriginVisible = pDoc->m_currentPart->m_originVisible;
	m_origOriginAltDisplayed = pDoc->m_currentPart->m_altOriginDisplayed;

	// init dialog

	sprintf(s, "%s  -  %s", pDoc->m_currentDevice->m_name,
		pDoc->m_currentPart->m_partName);
	SetWindowText((LPCTSTR)s);

	sprintf(s, "Make changes to Device: %s   Part %s...",
		pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(s);

	pCBox = (CComboBox*)this->GetDlgItem(IDC_DEVICE_PARENT_NAME);
	pCBox->SetWindowText(pDoc->m_currentDevice->m_parent);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)this->GetDlgItem(IDC_PART_PARENT_NAME);
	pCBox->SetWindowText(pDoc->m_currentPart->m_partParent);
	pCBox->UpdateWindow();

	m_deviceVisible = pDoc->m_currentDevice->m_visible;
	m_originVisible = pDoc->m_currentPart->m_originVisible;
	m_originAltDisplayed = pDoc->m_currentPart->m_altOriginDisplayed;

	sprintf(s, "%.3lf", pDoc->m_currentDevice->m_mass);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_MASS);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)this->GetDlgItem(IDC_BAR_CODE);
	pCBox->SetWindowText(pDoc->m_currentDevice->m_barCode);
	pCBox->UpdateWindow();

	YoUpdateTranslateRotate();

	//pCBox = (CComboBox*)GetDlgItem(IDC_SLIDER_ROTATE_X);
	//((CSliderCtrl *)pCBox)->SetRange((int)pDoc->m_currentPart->m_rotate[0] - 180,
	//	(int)pDoc->m_currentPart->m_rotate[0] + 180);
	//((CSliderCtrl *)pCBox)->SetPos((int)pDoc->m_currentPart->m_rotate[0]);

	//pCBox = (CComboBox*)GetDlgItem(IDC_SLIDER_ROTATE_Y);
	//((CSliderCtrl *)pCBox)->SetRange((int)pDoc->m_currentPart->m_rotate[1] - 180,
	//	(int)pDoc->m_currentPart->m_rotate[1] + 180);
	//((CSliderCtrl *)pCBox)->SetPos((int)pDoc->m_currentPart->m_rotate[1]);

	//pCBox = (CComboBox*)GetDlgItem(IDC_SLIDER_ROTATE_Z);
	//((CSliderCtrl *)pCBox)->SetRange((int)pDoc->m_currentPart->m_rotate[2] - 180,
	//	(int)pDoc->m_currentPart->m_rotate[2] + 180);
	//((CSliderCtrl *)pCBox)->SetPos((int)pDoc->m_currentPart->m_rotate[2]);


	//m_translateX = pDoc->m_currentPart->m_translate[0];
	//m_translateY = pDoc->m_currentPart->m_translate[1];
	//m_translateZ = pDoc->m_currentPart->m_translate[2];
	//m_rotateX = pDoc->m_currentPart->m_rotate[0];
	//m_rotateY = pDoc->m_currentPart->m_rotate[1];
	//m_rotateZ = pDoc->m_currentPart->m_rotate[2];

	//m_deviceName = CString(pDoc->m_currentDevice->m_name);

	for (i = 0; i < 4; i++)
	{
		m_ambient[i] = (UINT)(pDoc->m_currentPart->m_ambient[i] * 255.0);
		m_diffuse[i] = (UINT)(pDoc->m_currentPart->m_diffuse[i] * 255.0);
		m_specular[i] = (UINT)(pDoc->m_currentPart->m_specular[i] * 255.0);
		m_emission[i] = (UINT)(pDoc->m_currentPart->m_emission[i] * 255.0);
		m_wireframe[i] = (UINT)(pDoc->m_currentPart->m_wireframe[i] * 255.0);
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
	m_partMaterial.AddString("Wireframe");
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

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_smoothShadeAngle);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_SMOOTH_SHADE_ANGLE);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	m_snapToList.ResetContent();
	m_snapToList.AddString("Coordinate");
	m_snapToList.AddString("Edge");
	m_snapToList.AddString("Edge Center");
	m_snapToList.AddString("Part");
	m_snapToList.AddString("Polygon");
	m_snapToList.AddString("Polygon Center");
	m_snapToList.AddString("Vertex");
	m_snapToList.SetCurSel(pDoc->m_snapToViewPart);
	m_snapToMode = pDoc->m_snapToViewPart;

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

	//pDoc->m_currentPolygonIndex = -1;
	m_inheritingMaterial = FALSE;
	m_selectingAltOrigin = FALSE;
	m_snapTo = FALSE;

	if (pDoc->m_currentPolygonIndex > -1)
	{
		index = pDoc->m_currentPolygonIndex;
		for (currentPolygonList = pDoc->m_currentPart->m_polygonList; index >= 10; currentPolygonList = currentPolygonList->m_next)
		{
			index -= 10;
		}
		if (currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10] != NULL
			&& currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureMode == GL_MODULATE)
		{
			m_textureBlending = TRUE;
		}
		else
		{
			m_textureBlending = FALSE;
		}
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageViewPart::OnKillfocusPartAlpha() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();

	UpdateData(TRUE);
	m_partSliderAlpha.SetPos(m_partAlpha);
	YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_ALPHA);
	pView->YoRender(YO_RENDER_FULL);
	
}

void CStageViewPart::OnKillfocusPartBlue() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();

	UpdateData(TRUE);
	m_partSliderBlue.SetPos(m_partBlue);
	YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_BLUE);
	pView->YoRender(YO_RENDER_FULL);
	
}

void CStageViewPart::OnKillfocusPartGreen() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();

	UpdateData(TRUE);
	m_partSliderGreen.SetPos(m_partGreen);
	YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_GREEN);
	pView->YoRender(YO_RENDER_FULL);

}

void CStageViewPart::OnKillfocusPartRed() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();

	UpdateData(TRUE);
	m_partSliderRed.SetPos(m_partRed);
	YoUpdateMaterial(m_partMaterial.GetCurSel(), YO_RED);
	pView->YoRender(YO_RENDER_FULL);

}

void CStageViewPart::OnOK() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	int i;
	char s[256];
	CStagePolygonList *currentPolygonList;
	CStageTextureCoords *currentTextureCoords;
	CStageTextureCoords *ptrTextureCoords;

	if (pDoc->m_isMovement)
	{
		pDoc->YoEStop();
	}

	YoCancelSnapInherit();

	sprintf(s, "Device: %s   Part %s",
		pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(s);

	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		//((CMainFrame *)pMainFrame)->m_lightDialog->OnCancel();
		((CMainFrame *)pMainFrame)->m_lightDialog->DestroyWindow();
	}
	else if (((CMainFrame *)pMainFrame)->m_robot6DlgActive == TRUE)
	{
		((CMainFrame *)pMainFrame)->m_robot6Dialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_robot6DlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_rotaryTableDlgActive == TRUE)
	{
		((CMainFrame *)pMainFrame)->m_rotaryTableDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_rotaryTableDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_conveyorDlgActive == TRUE)
	{
		((CMainFrame *)pMainFrame)->m_conveyorDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_conveyorDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_cameraDlgActive == TRUE)
	{
		((CStageCamera *)pDoc->m_currentDevice)->m_enabled = FALSE;
		pDoc->m_camera = NULL;

		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
			pView->m_clipFront, pView->m_clipRear);

		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
			pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
			pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

		((CMainFrame *)pMainFrame)->m_cameraDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_cameraDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_gripperDlgActive == TRUE)
	{
		((CMainFrame *)pMainFrame)->m_gripperDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_gripperDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_barCodeReaderDlgActive == TRUE)
	{
		((CMainFrame *)pMainFrame)->m_barCodeReaderDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_barCodeReaderDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_barrettHandDlgActive == TRUE)
	{
		((CMainFrame *)pMainFrame)->m_barrettHandDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_barrettHandDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_scaleDlgActive == TRUE)
	{
		((CMainFrame *)pMainFrame)->m_scaleDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_scaleDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_trainDlgActive == TRUE)
	{

		((CMainFrame *)pMainFrame)->m_trainDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_trainDlgActive = FALSE;
	}

	// delete origTexture info for all polygons with original textures
	currentPolygonList = pDoc->m_currentPart->m_polygonList;
	for (i = 0; i < pDoc->m_currentPart->m_numberPolygons; i++)
	{
		if (currentPolygonList->m_textureModified[i % 10] == TRUE
			&& currentPolygonList->m_origTexture[i % 10] != NULL)
		{
			if (currentPolygonList->m_origTexture[i % 10]->m_RGBImage != NULL)
			{
				//use same routine that allocated it
				//LocalFree(currentPolygonList->m_origTexture[i % 10]->m_RGBImage);
			}
			for (currentTextureCoords = currentPolygonList->m_origTexture[i % 10]->m_textureCoords;
				currentTextureCoords != NULL;)
			{
				ptrTextureCoords = currentTextureCoords;
				currentTextureCoords = currentTextureCoords->m_next;
				delete(ptrTextureCoords);
			}
			delete(currentPolygonList->m_origTexture[i % 10]);
			currentPolygonList->m_origTexture[i % 10] = NULL;
			currentPolygonList->m_origTextureStartVertex[i % 10] = 0;
		}
		currentPolygonList->m_textureModified[i % 10] = FALSE;

		if (i % 10 == 9)
		{
			currentPolygonList = currentPolygonList->m_next;
		}
	}
	pDoc->m_currentPolygonIndex = -1;
	pDoc->m_snapToViewPart = m_snapToMode;

	((CMainFrame *)pMainFrame)->m_viewPartActive = FALSE;
	CDialog::OnOK();
	DestroyWindow();
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;
}

void CStageViewPart::OnCancel() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	int i;
	double z;
	char s[256];
	CStagePolygonList *currentPolygonList;
	CStageTextureCoords *currentTextureCoords;
	CStageTextureCoords *ptrTextureCoords;
	CStageConveyorSegment *ptrSegment;
	CStageConveyorStopGate *ptrStopGate;
	CStageConveyorTransverseLift *ptrTransverseLift;
	CStageConveyorPallet *ptrPallet;


	if (pDoc->m_isMovement)
	{
		pDoc->YoEStop();
	}

	YoCancelSnapInherit();

	sprintf(s, "Original properties restored for Device: %s   Part: %s",
		pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(s);

	pDoc->m_currentDevice->m_visible = m_origVisible;
	pDoc->m_currentPart->m_originVisible = m_origOriginVisible;
	pDoc->m_currentPart->m_altOriginDisplayed = m_origOriginAltDisplayed;
	pDoc->m_currentDevice->m_mass = m_origMass;
	sprintf(pDoc->m_currentDevice->m_barCode, "%s", m_origBarCode);

	for (i = 0; i < 3; i++)
	{
		pDoc->m_currentPart->m_translate[i] = m_origTranslate[i];
		pDoc->m_currentPart->m_rotate[i] = m_origRotate[i];
	}
	for (i = 0; i < 4; i++)
	{
		pDoc->m_currentPart->m_ambient[i] = m_origAmbient[i];
		pDoc->m_currentPart->m_diffuse[i] = m_origDiffuse[i];
		pDoc->m_currentPart->m_specular[i] = m_origSpecular[i];
		pDoc->m_currentPart->m_emission[i] = m_origEmission[i];
		pDoc->m_currentPart->m_wireframe[i] = m_origWireframe[i];
	}
	pDoc->m_currentPart->m_shininess = m_origShininess;
	pDoc->m_currentPart->m_txyz = m_origTxyz;
	pDoc->m_currentPart->m_renderMode = m_origRenderMode;
	pDoc->m_currentPart->m_smoothShadeAngle = m_origSmoothShadeAngle;
	pDoc->m_currentPart->YoComputeNormals();

	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		((CStageLight *)pDoc->m_currentDevice)->m_intensity = ((CMainFrame *)pMainFrame)->m_lightDialog->m_origIntensity;
		((CStageLight *)pDoc->m_currentDevice)->m_enabled = ((CMainFrame *)pMainFrame)->m_lightDialog->m_origEnabled;
		((CStageLight *)pDoc->m_currentDevice)->m_pointSource = ((CMainFrame *)pMainFrame)->m_lightDialog->m_origPointSource;
		((CStageLight *)pDoc->m_currentDevice)->m_spotCutoff = ((CMainFrame *)pMainFrame)->m_lightDialog->m_origSpotlightAngle;
		for (i = 0; i < 3; i++)
		{
			((CStageLight *)pDoc->m_currentDevice)->m_attenuation[i] = ((CMainFrame *)pMainFrame)->m_lightDialog->m_origAttenuation[i];
		}

		//((CMainFrame *)pMainFrame)->m_lightDialog->OnCancel();
		((CMainFrame *)pMainFrame)->m_lightDialog->DestroyWindow();
		pView->YoRender(YO_RENDER_LIGHT);
	}
	else if (((CMainFrame *)pMainFrame)->m_robot6DlgActive == TRUE)
	{
		for (i = 1; i <= 6; i++)
		{
			((CStageRobot6 *)pDoc->m_currentDevice)->m_j[i] = ((CMainFrame *)pMainFrame)->m_robot6Dialog->m_origJ[i];
		}
		((CStageRobot6 *)pDoc->m_currentDevice)->m_speed = ((CMainFrame *)pMainFrame)->m_robot6Dialog->m_origSpeed;
		((CStageRobot6 *)pDoc->m_currentDevice)->m_minAccelTime = ((CMainFrame *)pMainFrame)->m_robot6Dialog->m_origMinAccelTime;
		((CStageRobot6 *)pDoc->m_currentDevice)->m_jointInterpolation = ((CMainFrame *)pMainFrame)->m_robot6Dialog->m_origJointInterpolation;
		((CStageRobot6 *)pDoc->m_currentDevice)->m_elbowUp = ((CMainFrame *)pMainFrame)->m_robot6Dialog->m_origElbowUp;
		((CStageRobot6 *)pDoc->m_currentDevice)->m_lefty = ((CMainFrame *)pMainFrame)->m_robot6Dialog->m_origLefty;
		((CStageRobot6 *)pDoc->m_currentDevice)->m_wristFlipped = ((CMainFrame *)pMainFrame)->m_robot6Dialog->m_origWristFlipped;

		((CMainFrame *)pMainFrame)->m_robot6Dialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_robot6DlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_rotaryTableDlgActive == TRUE)
	{
		((CStageRotaryTable *)pDoc->m_currentDevice)->m_endPosition = ((CMainFrame *)pMainFrame)->m_rotaryTableDialog->m_origEndPosition;
		((CStageRotaryTable *)pDoc->m_currentDevice)->m_currentPosition = ((CMainFrame *)pMainFrame)->m_rotaryTableDialog->m_origCurrentPosition;
		((CStageRotaryTable *)pDoc->m_currentDevice)->m_directionPositive = ((CMainFrame *)pMainFrame)->m_rotaryTableDialog->m_origDirectionPositive;
		((CStageRotaryTable *)pDoc->m_currentDevice)->m_velocity = ((CMainFrame *)pMainFrame)->m_rotaryTableDialog->m_origVelocity;
		((CStageRotaryTable *)pDoc->m_currentDevice)->m_acceleration = ((CMainFrame *)pMainFrame)->m_rotaryTableDialog->m_origAcceleration;

		((CMainFrame *)pMainFrame)->m_rotaryTableDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_rotaryTableDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_cameraDlgActive == TRUE)
	{
		((CStageCamera *)pDoc->m_currentDevice)->m_clipFront = ((CMainFrame *)pMainFrame)->m_cameraDialog->m_origClipFront;
		((CStageCamera *)pDoc->m_currentDevice)->m_clipRear = ((CMainFrame *)pMainFrame)->m_cameraDialog->m_origClipRear;
		((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView = ((CMainFrame *)pMainFrame)->m_cameraDialog->m_origFieldOfView;
	
		((CStageCamera *)pDoc->m_currentDevice)->m_enabled = FALSE;
		pDoc->m_camera = NULL;

		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
			pView->m_clipFront, pView->m_clipRear);

		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
			pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
			pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

		((CMainFrame *)pMainFrame)->m_cameraDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_cameraDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_conveyorDlgActive == TRUE)
	{
		for (ptrSegment = ((CStageConveyor *)pDoc->m_currentDevice)->m_ptrSegment; ptrSegment != NULL; ptrSegment = ptrSegment->m_ptrNextSegment)
		{
			ptrSegment->m_acceleration = ptrSegment->m_origAcceleration;
			ptrSegment->m_maxVelocity = ptrSegment->m_origMaxVelocity;
			ptrSegment->m_relSpeed = ptrSegment->m_origRelSpeed;
			ptrSegment->m_directionForward = ptrSegment->m_origDirectionForward;

			for (ptrStopGate = ptrSegment->m_ptrStopGate; ptrStopGate != NULL; ptrStopGate = ptrStopGate->m_ptrNextStopGate)
			{
				ptrStopGate->m_stop = ptrStopGate->m_origStop;
			}
			for (ptrTransverseLift = ptrSegment->m_ptrTransverseLift; ptrTransverseLift != NULL;
				ptrTransverseLift = ptrTransverseLift->m_ptrNextTransverseLift)
			{
				if (ptrTransverseLift->m_ptrPart != NULL)
				{
					ptrTransverseLift->m_up = ptrTransverseLift->m_origUp;
					if (ptrTransverseLift->m_up)
					{
						z = YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
					}
					else
					{
						z = 0.0f;
					}
					ptrTransverseLift->m_ptrPart->m_translate[2]
						= ((CStageConveyor *)pDoc->m_currentDevice)->m_offset[2] - 6.35
						+ ptrTransverseLift->m_position[2] + z;
				}
			}
			for (ptrPallet = ptrSegment->m_ptrPallet; ptrPallet != NULL;
				ptrPallet = ptrPallet->m_ptrNextPallet)
			{
				ptrPallet->m_relativePosition = ptrPallet->m_origRelativePosition;
				ptrPallet->m_distance = ptrPallet->m_origDistance;
				for (i = 0; i < 3; i++)
				{
					ptrPallet->m_position[i] = ptrPallet->m_origPosition[i];
					ptrPallet->m_startPosition[i] = ptrPallet->m_origStartPosition[i];
					ptrPallet->m_endPosition[i]= ptrPallet->m_origEndPosition[i];
				}
				if (ptrPallet->m_ptrOrigSegment != ptrPallet->m_ptrSegment)
				{
					((CStageConveyor *)pDoc->m_currentDevice)->YoTransferPallet(ptrPallet, ptrPallet->m_ptrOrigSegment);	
				}
				else
				{
					((CStageConveyor *)pDoc->m_currentDevice)->YoUpdatePalletGraphicsPosition(ptrPallet);
				}
			}
		}

		((CMainFrame *)pMainFrame)->m_conveyorDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_conveyorDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_gripperDlgActive == TRUE)
	{
		((CMainFrame *)pMainFrame)->m_gripperDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_gripperDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_barCodeReaderDlgActive == TRUE)
	{
		((CMainFrame *)pMainFrame)->m_barCodeReaderDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_barCodeReaderDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_barrettHandDlgActive == TRUE)
	{
		for (i = 0; i < 3; i++)
		{
			((CStageBarrettHand *)pDoc->m_currentDevice)->m_fingerFixed[i] = ((CMainFrame *)pMainFrame)->m_barrettHandDialog->m_origFingerFixed[i];
			((CStageBarrettHand *)pDoc->m_currentDevice)->m_fingerRight[i] = ((CMainFrame *)pMainFrame)->m_barrettHandDialog->m_origFingerRight[i];
			((CStageBarrettHand *)pDoc->m_currentDevice)->m_fingerLeft[i] = ((CMainFrame *)pMainFrame)->m_barrettHandDialog->m_origFingerLeft[i];
		}
		((CStageBarrettHand *)pDoc->m_currentDevice)->m_velocity = ((CMainFrame *)pMainFrame)->m_barrettHandDialog->m_origVelocity;
		((CStageBarrettHand *)pDoc->m_currentDevice)->m_spread = ((CMainFrame *)pMainFrame)->m_barrettHandDialog->m_origSpread;
		((CMainFrame *)pMainFrame)->m_barrettHandDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_barrettHandDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_scaleDlgActive == TRUE)
	{
		((CStageScale *)pDoc->m_currentDevice)->m_units = ((CMainFrame *)pMainFrame)->m_scaleDialog->m_origUnits;

		((CMainFrame *)pMainFrame)->m_scaleDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_scaleDlgActive = FALSE;
	}
	else if (((CMainFrame *)pMainFrame)->m_trainDlgActive == TRUE)
	{
		((CStageTrain *)pDoc->m_currentDevice)->m_ptrTrackSeg = ((CMainFrame *)pMainFrame)->m_trainDialog->m_ptrOrigTrackSeg;
		((CStageTrain *)pDoc->m_currentDevice)->m_directionPositive = ((CMainFrame *)pMainFrame)->m_trainDialog->m_origDirectionPositive;
		((CStageTrain *)pDoc->m_currentDevice)->m_ptrTrackSegEnd = ((CMainFrame *)pMainFrame)->m_trainDialog->m_ptrOrigTrackSegEnd;
		((CStageTrain *)pDoc->m_currentDevice)->m_relativePositionEnd = ((CMainFrame *)pMainFrame)->m_trainDialog->m_origRelativePositionEnd;
		((CStageTrain *)pDoc->m_currentDevice)->m_relativePosition = ((CMainFrame *)pMainFrame)->m_trainDialog->m_origRelativePosition;
		((CStageTrain *)pDoc->m_currentDevice)->m_velocity = ((CMainFrame *)pMainFrame)->m_trainDialog->m_origVelocity;
		((CStageTrain *)pDoc->m_currentDevice)->m_acceleration = ((CMainFrame *)pMainFrame)->m_trainDialog->m_origAcceleration;

		((CMainFrame *)pMainFrame)->m_trainDialog->DestroyWindow();
		((CMainFrame *)pMainFrame)->m_trainDlgActive = FALSE;
	}

	// restore original texture info for all polygons in currentPart
	currentPolygonList = pDoc->m_currentPart->m_polygonList;
	for (i = 0; i < pDoc->m_currentPart->m_numberPolygons; i++)
	{
		if (currentPolygonList->m_textureModified[i % 10] == TRUE
			&& currentPolygonList->m_texture[i % 10] != NULL)
		{
			if (currentPolygonList->m_texture[i % 10]->m_RGBImage != NULL)
			{
				//use same routine that allocated it
				//LocalFree(currentPolygonList->m_texture[i % 10]->m_RGBImage);
			}
			for (currentTextureCoords = currentPolygonList->m_texture[i % 10]->m_textureCoords;
				currentTextureCoords != NULL;)
			{
				ptrTextureCoords = currentTextureCoords;
				currentTextureCoords = currentTextureCoords->m_next;
				delete(ptrTextureCoords);
			}
			delete(currentPolygonList->m_texture[i % 10]);
			currentPolygonList->m_texture[i % 10] = currentPolygonList->m_origTexture[i % 10];
			currentPolygonList->m_textureModified[i % 10] = FALSE;
			currentPolygonList->m_origTexture[i % 10] = NULL;
			currentPolygonList->m_textureStartVertex[i % 10] = currentPolygonList->m_origTextureStartVertex[i % 10];
		}
		else if (currentPolygonList->m_textureModified[i % 10] == TRUE)
		{
			currentPolygonList->m_texture[i % 10] = currentPolygonList->m_origTexture[i % 10];
			currentPolygonList->m_textureModified[i % 10] = FALSE;
			currentPolygonList->m_origTexture[i % 10] = NULL;
			currentPolygonList->m_textureStartVertex[i % 10] = currentPolygonList->m_origTextureStartVertex[i % 10];
		}

		if (i % 10 == 9)
		{
			currentPolygonList = currentPolygonList->m_next;
		}
	}
	pDoc->m_currentPolygonIndex = -1;
	pDoc->m_snapToViewPart = m_snapToMode;

	((CMainFrame *)pMainFrame)->m_viewPartActive = FALSE;
	CDialog::OnCancel();
	DestroyWindow();
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

}

void CStageViewPart::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	YoCancelSnapInherit();

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
	/****
	else if ((CSliderCtrl *)pScrollBar == &m_sliderRotateX)
	{
		pDoc->m_currentPart->m_rotate[0] = (GLdouble)m_sliderRotateX.GetPos();
		sprintf(s, "%.1lf", pDoc->m_currentPart->m_rotate[0]);
		pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_X);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

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
	else if ((CSliderCtrl *)pScrollBar == &m_sliderRotateY)
	{
		pDoc->m_currentPart->m_rotate[1] = (GLdouble)m_sliderRotateY.GetPos();
		sprintf(s, "%.1lf", pDoc->m_currentPart->m_rotate[1]);
		pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Y);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

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
	else if ((CSliderCtrl *)pScrollBar == &m_sliderRotateZ)
	{
		pDoc->m_currentPart->m_rotate[2] = (GLdouble)m_sliderRotateZ.GetPos();
		sprintf(s, "%.1lf", pDoc->m_currentPart->m_rotate[2]);
		pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Z);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

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
	****/

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


void CStageViewPart::YoTranslateRotate(GLdouble t[3], GLdouble r[3], GLdouble tr)
// alter one of x, y, z translation, or x, y, z rotation (degrees) of current part
// 5 of 6 variables of t and r should be 0.0 (i.e. no action is taken)
// 1 of 6 variables is 1.0, which means that the designated t or r should use value of tr
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	GLdouble m[16];
	GLdouble n[16];
	GLdouble mInv[16];
	GLdouble translate[3];
	GLdouble rotate[3];
	int i;

	if (t[0] == 1.0 || t[1] == 1.0 || t[2] == 1.0)
	// handle translation
	{
		if (m_originAltDisplayed == TRUE)
		{
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadIdentity();
			pView->YoTxyz(pDoc->m_currentPart,
				pDoc->m_currentPart->m_translate,
				pDoc->m_currentPart->m_rotate);
			::glMultMatrixd(pDoc->m_currentPart->m_altOrigin);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			if (t[0] == 1.0)
			{
				m[12] = tr / pDoc->m_unitScaleFactor;
			}
			else if (t[1] == 1.0)
			{
				m[13] = tr / pDoc->m_unitScaleFactor;
			}
			else if (t[2] == 1.0)
			{
				m[14] = tr / pDoc->m_unitScaleFactor;
			}
			::glLoadMatrixd(m);
			pDoc->YoMatrixInverse(pDoc->m_currentPart->m_altOrigin, mInv);
			::glMultMatrixd(mInv);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			pDoc->m_currentPart->m_txyz = YO_TXYZ_TXYZ;
			pDoc->YoTranslateRotateValues(m,
				pDoc->m_currentPart->m_translate,
				pDoc->m_currentPart->m_rotate);
			for (i = 0; i < 3; i++)
			{
				pDoc->m_currentPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}
			::glPopMatrix();
		}
		else
		{
			if (t[0] == 1.0)
			{
				pDoc->m_currentPart->m_translate[0] = tr / pDoc->m_unitScaleFactor;
			}
			else if (t[1] == 1.0)
			{
				pDoc->m_currentPart->m_translate[1] = tr / pDoc->m_unitScaleFactor;
			}
			else if (t[2] == 1.0)
			{
				pDoc->m_currentPart->m_translate[2] = tr / pDoc->m_unitScaleFactor;
			}
		}
	}
	else   // handle rotation
	{
		if (m_originAltDisplayed == TRUE)
		{
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadIdentity();
			pView->YoTxyz(pDoc->m_currentPart,
				pDoc->m_currentPart->m_translate,
				pDoc->m_currentPart->m_rotate);

			::glPushMatrix();
			::glLoadIdentity();
			if (pDoc->m_currentDevice->m_type == YO_ROBOT6)
			{
				((CStageRobot6 *)pDoc->m_currentDevice)->YoRotateJoint(pDoc->m_currentPart);
			}				
			else if (pDoc->m_currentDevice->m_type == YO_ROTARY_TABLE)
			{
				((CStageRotaryTable *)pDoc->m_currentDevice)->YoRotateTable(pDoc->m_currentPart);
			}
			else if (pDoc->m_currentDevice->m_type == YO_BARRETT_HAND)
			{
				((CStageBarrettHand *)pDoc->m_currentDevice)->YoPositionFinger(pDoc->m_currentPart);
			}
			else if (pDoc->m_currentDevice->m_type == YO_GRIPPER)
			{
				((CStageGripper *)pDoc->m_currentDevice)->YoPositionFinger(pDoc->m_currentPart);
			}

			::glGetDoublev(GL_MODELVIEW_MATRIX, n);
			::glPopMatrix();
			::glMultMatrixd(n);

			::glMultMatrixd(pDoc->m_currentPart->m_altOrigin);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			pDoc->m_currentPart->m_txyz = YO_TXYZ_TXYZ;
			pDoc->YoTranslateRotateValues(m, translate, rotate);
			for (i = 0; i < 3; i++)
			{
				rotate[i] *= YO_RADIANS_TO_DEGREES;
				if (r[i] != 0.0)
				{
					rotate[i] = r[i] * tr;
				}
			}

			::glLoadIdentity();
			pView->YoTxyz(pDoc->m_currentPart, translate, rotate);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			pDoc->YoMatrixInverse(pDoc->m_currentPart->m_altOrigin, mInv);
			::glMultMatrixd(mInv);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			pDoc->YoMatrixInverse(n, mInv);
			::glMultMatrixd(mInv);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);

			pDoc->m_currentPart->m_txyz = YO_TXYZ_TXYZ;
			pDoc->YoTranslateRotateValues(m,
				pDoc->m_currentPart->m_translate,
				pDoc->m_currentPart->m_rotate);
			for (i = 0; i < 3; i++)
			{
				pDoc->m_currentPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}
			::glPopMatrix();
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				if (r[i] != 0.0)
				{
					pDoc->m_currentPart->m_rotate[i] = r[i] * tr;
				}
			}
		}
	}

	return;
}


void CStageViewPart::YoUpdateTranslateRotate(void)
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	GLdouble m[16];
	GLdouble t[3];
	GLdouble r[3];
	char s[128];
	int i;

	if (m_originAltDisplayed == TRUE)
	{
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();
		pView->YoTxyz(pDoc->m_currentPart,
			pDoc->m_currentPart->m_translate,
			pDoc->m_currentPart->m_rotate);
		::glMultMatrixd(pDoc->m_currentPart->m_altOrigin);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);

		pDoc->m_currentPart->m_txyz = YO_TXYZ_TXYZ;
		pDoc->YoTranslateRotateValues(m, t, r);
		for (i = 0; i < 3; i++)
		{
			r[i] *= YO_RADIANS_TO_DEGREES;
		}
		::glPopMatrix();
	}
	else
	{
		t[0] = pDoc->m_currentPart->m_translate[0];
		t[1] = pDoc->m_currentPart->m_translate[1];
		t[2] = pDoc->m_currentPart->m_translate[2];
		r[0] = pDoc->m_currentPart->m_rotate[0];
		r[1] = pDoc->m_currentPart->m_rotate[1];
		r[2] = pDoc->m_currentPart->m_rotate[2];
	}

	//::EnterCriticalSection(&pDoc->m_criticalSection);

	sprintf(s, "%.3lf", t[0] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.3lf", t[1] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.3lf", t[2] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", r[0]);
	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", r[1]);
	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", r[2]);
	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	//::LeaveCriticalSection(&pDoc->m_criticalSection);


	//pCBox = (CComboBox*)GetDlgItem(IDC_SLIDER_ROTATE_X);
	//((CSliderCtrl *)pCBox)->SetRange((int)pDoc->m_currentPart->m_rotate[0] - 180,
	//	(int)pDoc->m_currentPart->m_rotate[0] + 180);
	//((CSliderCtrl *)pCBox)->SetPos((int)pDoc->m_currentPart->m_rotate[0]);

	//pCBox = (CComboBox*)GetDlgItem(IDC_SLIDER_ROTATE_Y);
	//((CSliderCtrl *)pCBox)->SetRange((int)pDoc->m_currentPart->m_rotate[1] - 180,
	//	(int)pDoc->m_currentPart->m_rotate[1] + 180);
	//((CSliderCtrl *)pCBox)->SetPos((int)pDoc->m_currentPart->m_rotate[1]);

	//pCBox = (CComboBox*)GetDlgItem(IDC_SLIDER_ROTATE_Z);
	//((CSliderCtrl *)pCBox)->SetRange((int)pDoc->m_currentPart->m_rotate[2] - 180,
	//	(int)pDoc->m_currentPart->m_rotate[2] + 180);
	//((CSliderCtrl *)pCBox)->SetPos((int)pDoc->m_currentPart->m_rotate[2]);


	return;
}

void CStageViewPart::YoUpdateMaterial(int type, UINT rgba)
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
	else if (type == 4)  // wireframe
	{
		if (rgba == YO_RED)
		{
			m_wireframe[rgba] = m_partRed;
		}
		else if (rgba == YO_GREEN)
		{
			m_wireframe[rgba] = m_partGreen;
		}
		else if (rgba == YO_BLUE)
		{
			m_wireframe[rgba] = m_partBlue;
		}
		else if (rgba == YO_ALPHA)
		{
			m_specular[rgba] = m_partAlpha;
		}
		pDoc->m_currentPart->m_wireframe[rgba] = (GLfloat)m_wireframe[rgba] / 255.0f;
	}
	return;
}

void CStageViewPart::YoCancelSnapInherit(void)
// stop process of inheriting material, selecting alternate origin, or snapping to
// and restore cursor to arrow
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[128];

	sprintf(s, "");
	pDoc->YoMessage(s);
	SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);
	
	m_inheritingMaterial = FALSE;
	m_selectingAltOrigin = FALSE;
	m_snapTo = FALSE;

	return;
}


void CStageViewPart::YoRestoreMaterial(int type, UINT rgba)
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	if (type == 0)  // ambient
	{
		pDoc->m_currentPart->m_ambient[rgba] = m_origAmbient[rgba];
		m_ambient[rgba] = (UINT)(pDoc->m_currentPart->m_ambient[rgba] * 255.0);

		if (rgba == YO_RED)
		{
			m_partRed = m_ambient[rgba];
		}
		else if (rgba == YO_GREEN)
		{
			m_partGreen = m_ambient[rgba];
		}
		else if (rgba == YO_BLUE)
		{
			m_partBlue = m_ambient[rgba];
		}
		else if (rgba == YO_ALPHA)
		{
			m_partAlpha = m_ambient[rgba];
		}
	}

	else if (type == 1)  // diffuse
	{
		pDoc->m_currentPart->m_diffuse[rgba] = m_origDiffuse[rgba];
		m_diffuse[rgba] = (UINT)(pDoc->m_currentPart->m_diffuse[rgba] * 255.0);

		if (rgba == YO_RED)
		{
			m_partRed = m_diffuse[rgba];
		}
		else if (rgba == YO_GREEN)
		{
			m_partGreen = m_diffuse[rgba];
		}
		else if (rgba == YO_BLUE)
		{
			m_partBlue = m_diffuse[rgba];
		}
		else if (rgba == YO_ALPHA)
		{
			m_partAlpha = m_diffuse[rgba];
		}
	}

	else if (type == 2)  // emission
	{
		pDoc->m_currentPart->m_emission[rgba] = m_origEmission[rgba];
		m_emission[rgba] = (UINT)(pDoc->m_currentPart->m_emission[rgba] * 255.0);

		if (rgba == YO_RED)
		{
			m_partRed = m_emission[rgba];
		}
		else if (rgba == YO_GREEN)
		{
			m_partGreen = m_emission[rgba];
		}
		else if (rgba == YO_BLUE)
		{
			m_partBlue = m_emission[rgba];
		}
		else if (rgba == YO_ALPHA)
		{
			m_partAlpha = m_emission[rgba];
		}
	}
	else if (type == 3)  // specular
	{
		pDoc->m_currentPart->m_specular[rgba] = m_origSpecular[rgba];
		m_specular[rgba] = (UINT)(pDoc->m_currentPart->m_specular[rgba] * 255.0);

		if (rgba == YO_RED)
		{
			m_partRed = m_specular[rgba];
		}
		else if (rgba == YO_GREEN)
		{
			m_partGreen = m_specular[rgba];
		}
		else if (rgba == YO_BLUE)
		{
			m_partBlue = m_specular[rgba];
		}
		else if (rgba == YO_ALPHA)
		{
			m_partAlpha = m_specular[rgba];
		}
	}
	else if (type == 4)  // wireframe
	{
		pDoc->m_currentPart->m_wireframe[rgba] = m_origWireframe[rgba];
		m_wireframe[rgba] = (UINT)(pDoc->m_currentPart->m_wireframe[rgba] * 255.0);

		if (rgba == YO_RED)
		{
			m_partRed = m_wireframe[rgba];
		}
		else if (rgba == YO_GREEN)
		{
			m_partGreen = m_wireframe[rgba];
		}
		else if (rgba == YO_BLUE)
		{
			m_partBlue = m_wireframe[rgba];
		}
		else if (rgba == YO_ALPHA)
		{
			m_partAlpha = m_wireframe[rgba];
		}
	}

	UpdateData(FALSE);

	if (rgba == YO_RED)
	{
		m_partSliderRed.SetPos(m_partRed);
	}
	else if (rgba == YO_GREEN)
	{
		m_partSliderGreen.SetPos(m_partGreen);
	}
	else if (rgba == YO_BLUE)
	{
		m_partSliderBlue.SetPos(m_partBlue);
	}
	else if (rgba == YO_ALPHA)
	{
		m_partSliderAlpha.SetPos(m_partAlpha);
	}

	pView->YoRender(YO_RENDER_FULL);

	return;
}


void CStageViewPart::OnSelchangePartMaterial() 
{

	YoCancelSnapInherit();

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
	else if (m_partMaterial.GetCurSel() == 4)  // wireframe
	{
		m_partRed = m_wireframe[0];
		m_partGreen = m_wireframe[1];
		m_partBlue = m_wireframe[2];
		m_partAlpha = m_wireframe[3];
		m_partSliderRed.SetPos(m_partRed);
		m_partSliderGreen.SetPos(m_partGreen);
		m_partSliderBlue.SetPos(m_partBlue);
		m_partSliderAlpha.SetPos(m_partAlpha);
	}
	UpdateData(FALSE);
	return;
	
}

void CStageViewPart::OnKillfocusPartShininess() 
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


void CStageViewPart::PostNcDestroy() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
	delete this;
}

void CStageViewPart::OnKillfocusTranslateX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_X);
	pCBox->GetWindowText(s, 64);
	translate[0] = 1.0;
	sscanf(s, "%lf", &tr);
	tr /= pDoc->m_unitScaleFactor;

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;

/***
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;
	GLdouble m[16];
	GLdouble mInv[16];
	int i;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_X);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);

	if (m_originAltDisplayed == TRUE)
	{
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();
		pView->YoTxyz(pDoc->m_currentPart,
			pDoc->m_currentPart->m_translate,
			pDoc->m_currentPart->m_rotate);
		::glMultMatrixd(pDoc->m_currentPart->m_altOrigin);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
		m[12] = t / pDoc->m_unitScaleFactor;
		::glLoadMatrixd(m);
		pDoc->YoMatrixInverse(pDoc->m_currentPart->m_altOrigin, mInv);
		::glMultMatrixd(mInv);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
		pDoc->m_currentPart->m_txyz = YO_TXYZ_TXYZ;
		pDoc->YoTranslateRotateValues(m,
			pDoc->m_currentPart->m_translate,
			pDoc->m_currentPart->m_rotate);
		for (i = 0; i < 3; i++)
		{
			pDoc->m_currentPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
		}
		::glPopMatrix();
	}
	else
	{
		pDoc->m_currentPart->m_translate[0] = t / pDoc->m_unitScaleFactor;
	}
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;	
***/

}

void CStageViewPart::OnKillfocusTranslateY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_Y);
	pCBox->GetWindowText(s, 64);
	translate[1] = 1.0;
	sscanf(s, "%lf", &tr);
	tr /= pDoc->m_unitScaleFactor;

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;				
	
}

void CStageViewPart::OnKillfocusTranslateZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_Z);
	pCBox->GetWindowText(s, 64);
	translate[2] = 1.0;
	sscanf(s, "%lf", &tr);
	tr /= pDoc->m_unitScaleFactor;

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;		
	
}

void CStageViewPart::OnKillfocusRotateX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_X);
	pCBox->GetWindowText(s, 64);
	rotate[0] = 1.0;
	sscanf(s, "%lf", &tr);

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;	

}

void CStageViewPart::OnKillfocusRotateY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Y);
	pCBox->GetWindowText(s, 64);
	rotate[1] = 1.0;
	sscanf(s, "%lf", &tr);

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;

/***
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;
	GLdouble m[16];
	GLdouble mInv[16];
	GLdouble translate[3];
	GLdouble rotate[3];
	int i;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Y);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);

	if (m_originAltDisplayed == TRUE)
	{
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();
		pView->YoTxyz(pDoc->m_currentPart,
			pDoc->m_currentPart->m_translate,
			pDoc->m_currentPart->m_rotate);
		::glMultMatrixd(pDoc->m_currentPart->m_altOrigin);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
		pDoc->m_currentPart->m_txyz = YO_TXYZ_TXYZ;
		pDoc->YoTranslateRotateValues(m, translate, rotate);
		for (i = 0; i < 3; i++)
		{
			rotate[i] *= YO_RADIANS_TO_DEGREES;
		}
		rotate[1] = t;
		::glLoadIdentity();
		pView->YoTxyz(pDoc->m_currentPart, translate, rotate);
		pDoc->YoMatrixInverse(pDoc->m_currentPart->m_altOrigin, mInv);
		::glMultMatrixd(mInv);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
		pDoc->m_currentPart->m_txyz = YO_TXYZ_TXYZ;
		pDoc->YoTranslateRotateValues(m,
			pDoc->m_currentPart->m_translate,
			pDoc->m_currentPart->m_rotate);
		for (i = 0; i < 3; i++)
		{
			pDoc->m_currentPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
		}
		::glPopMatrix();
	}
	else
	{
		pDoc->m_currentPart->m_rotate[1] = t;
	}
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;	
***/
	
}

void CStageViewPart::OnKillfocusRotateZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Z);
	pCBox->GetWindowText(s, 64);
	rotate[2] = 1.0;
	sscanf(s, "%lf", &tr);

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageViewPart::OnSelchangePartRenderMode() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	YoCancelSnapInherit();
	pDoc->m_currentPart->m_renderMode = (UINT)m_partRenderMode.GetCurSel();
	pView->YoRender(YO_RENDER_FULL);
}

void CStageViewPart::OnSelchangeTxyz() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	YoCancelSnapInherit();
	pDoc->m_currentPart->m_txyz = (UINT)m_txyz.GetCurSel();

	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);	
}

void CStageViewPart::OnDeviceVisible() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	YoCancelSnapInherit();
	UpdateData(TRUE);
	pDoc->m_currentDevice->m_visible = m_deviceVisible;
	
	//pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);	
}

void CStageViewPart::OnRotateRestore() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	YoCancelSnapInherit();

	pDoc->m_currentPart->m_rotate[0] = m_origRotate[0];
	pDoc->m_currentPart->m_rotate[1] = m_origRotate[1];
	pDoc->m_currentPart->m_rotate[2] = m_origRotate[2];

	YoUpdateTranslateRotate();

	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
}

void CStageViewPart::OnTranslateRestore() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	YoCancelSnapInherit();

	pDoc->m_currentPart->m_translate[0] = m_origTranslate[0];
	pDoc->m_currentPart->m_translate[1] = m_origTranslate[1];
	pDoc->m_currentPart->m_translate[2] = m_origTranslate[2];
	
	YoUpdateTranslateRotate();

	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
}


void CStageViewPart::OnTranslateDecreaseX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();
	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_X);
	pCBox->GetWindowText(s, 64);
	translate[0] = 1.0;
	sscanf(s, "%lf", &tr);
	tr /= pDoc->m_unitScaleFactor;
	tr -= ((fabs(pDoc->m_currentPart->m_max[0] - pDoc->m_currentPart->m_min[0])
		+ fabs(pDoc->m_currentPart->m_max[1] - pDoc->m_currentPart->m_min[1])
		+ fabs(pDoc->m_currentPart->m_max[2] - pDoc->m_currentPart->m_min[2]))
		/ 3.0);

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageViewPart::OnTranslateDecreaseY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();
	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_Y);
	pCBox->GetWindowText(s, 64);
	translate[1] = 1.0;
	sscanf(s, "%lf", &tr);
	tr /= pDoc->m_unitScaleFactor;
	tr -= ((fabs(pDoc->m_currentPart->m_max[0] - pDoc->m_currentPart->m_min[0])
		+ fabs(pDoc->m_currentPart->m_max[1] - pDoc->m_currentPart->m_min[1])
		+ fabs(pDoc->m_currentPart->m_max[2] - pDoc->m_currentPart->m_min[2]))
		/ 3.0);

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewPart::OnTranslateDecreaseZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();
	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_Z);
	pCBox->GetWindowText(s, 64);
	translate[2] = 1.0;
	sscanf(s, "%lf", &tr);
	tr /= pDoc->m_unitScaleFactor;
	tr -= ((fabs(pDoc->m_currentPart->m_max[0] - pDoc->m_currentPart->m_min[0])
		+ fabs(pDoc->m_currentPart->m_max[1] - pDoc->m_currentPart->m_min[1])
		+ fabs(pDoc->m_currentPart->m_max[2] - pDoc->m_currentPart->m_min[2]))
		/ 3.0);

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewPart::OnTranslateIncreaseX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();
	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_X);
	pCBox->GetWindowText(s, 64);
	translate[0] = 1.0;
	sscanf(s, "%lf", &tr);
	tr /= pDoc->m_unitScaleFactor;
	tr += ((fabs(pDoc->m_currentPart->m_max[0] - pDoc->m_currentPart->m_min[0])
		+ fabs(pDoc->m_currentPart->m_max[1] - pDoc->m_currentPart->m_min[1])
		+ fabs(pDoc->m_currentPart->m_max[2] - pDoc->m_currentPart->m_min[2]))
		/ 3.0);

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;
	
/***
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[32];
	CWnd *pCBox;
	GLdouble m[16];
	GLdouble mInv[16];
	int i;

	if (m_originAltDisplayed == TRUE)
	{
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();
		pView->YoTxyz(pDoc->m_currentPart,
			pDoc->m_currentPart->m_translate,
			pDoc->m_currentPart->m_rotate);
		::glMultMatrixd(pDoc->m_currentPart->m_altOrigin);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
		m[12] += ((fabs(pDoc->m_currentPart->m_max[0] - pDoc->m_currentPart->m_min[0])
			+ fabs(pDoc->m_currentPart->m_max[1] - pDoc->m_currentPart->m_min[1])
			+ fabs(pDoc->m_currentPart->m_max[2] - pDoc->m_currentPart->m_min[2]))
			/ 3.0);
		sprintf(s, "%.3lf", m[12] * pDoc->m_unitScaleFactor);
		::glLoadMatrixd(m);
		pDoc->YoMatrixInverse(pDoc->m_currentPart->m_altOrigin, mInv);
		::glMultMatrixd(mInv);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
		pDoc->m_currentPart->m_txyz = YO_TXYZ_TXYZ;
		pDoc->YoTranslateRotateValues(m,
			pDoc->m_currentPart->m_translate,
			pDoc->m_currentPart->m_rotate);
		for (i = 0; i < 3; i++)
		{
			pDoc->m_currentPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
		}
		::glPopMatrix();
	}
	else
	{
		pDoc->m_currentPart->m_translate[0]
			+= ((fabs(pDoc->m_currentPart->m_max[0] - pDoc->m_currentPart->m_min[0])
			+ fabs(pDoc->m_currentPart->m_max[1] - pDoc->m_currentPart->m_min[1])
			+ fabs(pDoc->m_currentPart->m_max[2] - pDoc->m_currentPart->m_min[2]))
			/ 3.0);
		sprintf(s, "%.3lf", pDoc->m_currentPart->m_translate[0]
			* pDoc->m_unitScaleFactor);
	}

	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;
***/
}

void CStageViewPart::OnTranslateIncreaseY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();
	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_Y);
	pCBox->GetWindowText(s, 64);
	translate[1] = 1.0;
	sscanf(s, "%lf", &tr);
	tr /= pDoc->m_unitScaleFactor;
	tr += ((fabs(pDoc->m_currentPart->m_max[0] - pDoc->m_currentPart->m_min[0])
		+ fabs(pDoc->m_currentPart->m_max[1] - pDoc->m_currentPart->m_min[1])
		+ fabs(pDoc->m_currentPart->m_max[2] - pDoc->m_currentPart->m_min[2]))
		/ 3.0);

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageViewPart::OnTranslateIncreaseZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();
	pCBox = (CComboBox*)GetDlgItem(IDC_TRANSLATE_Z);
	pCBox->GetWindowText(s, 64);
	translate[2] = 1.0;
	sscanf(s, "%lf", &tr);
	tr /= pDoc->m_unitScaleFactor;
	tr += ((fabs(pDoc->m_currentPart->m_max[0] - pDoc->m_currentPart->m_min[0])
		+ fabs(pDoc->m_currentPart->m_max[1] - pDoc->m_currentPart->m_min[1])
		+ fabs(pDoc->m_currentPart->m_max[2] - pDoc->m_currentPart->m_min[2]))
		/ 3.0);

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageViewPart::OnAlphaRestore() 
{
	YoCancelSnapInherit();
	YoRestoreMaterial(m_partMaterial.GetCurSel(), YO_ALPHA);
	return;
}

void CStageViewPart::OnBlueRestore() 
{
	YoCancelSnapInherit();
	YoRestoreMaterial(m_partMaterial.GetCurSel(), YO_BLUE);
	return;
}

void CStageViewPart::OnGreenRestore() 
{
	YoCancelSnapInherit();
	YoRestoreMaterial(m_partMaterial.GetCurSel(), YO_GREEN);
	return;
}

void CStageViewPart::OnRedRestore() 
{
	YoCancelSnapInherit();
	YoRestoreMaterial(m_partMaterial.GetCurSel(), YO_RED);
	return;
}

void CStageViewPart::OnShininessRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	YoCancelSnapInherit();
	pDoc->m_currentPart->m_shininess = m_origShininess;
	m_partShininess = (UINT)pDoc->m_currentPart->m_shininess;

	UpdateData(FALSE);

	m_partSliderShininess.SetPos(m_partShininess);

	pView->YoRender(YO_RENDER_FULL);

	return;
}

void CStageViewPart::OnPartParentInherit() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[128];

	if (pDoc->m_isMovement)
	{
		pDoc->YoEStop();
	}

	m_snapTo = FALSE;
	m_selectingAltOrigin = FALSE;

	if (m_inheritingMaterial == FALSE)
	{
		m_inheritingMaterial = TRUE;
		//m_inheritDialog = new (CStageInheritMaterial);
		//m_inheritDialog->YoInitDialog();
		//m_inheritDialog->ShowWindow(SW_SHOW);

		sprintf(s, "Select a part to inherit its material, or click the Inherit button again to cancel");
		pDoc->YoMessage(s);
		SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorSelect);
	}
	else
	{
		m_inheritingMaterial = FALSE;
		sprintf(s, "Inherit material canceled");
		pDoc->YoMessage(s);
		SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);
	}

	return;	
}


void CStageViewPart::OnTextureBlending() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePolygonList *currentPolygonList;
	CStageTextureCoords *ptrTextureCoords;
	CStageTextureCoords *ptrOrigTextureCoords;
	int index;
	int i;

	YoCancelSnapInherit();
	if (pDoc->m_currentPolygonIndex < 0)
	{
		// texture blending cannot be checked
		m_textureBlending = FALSE;
		UpdateData(FALSE);
		return;
	}
	
	index = pDoc->m_currentPolygonIndex;
	for (currentPolygonList = pDoc->m_currentPart->m_polygonList; index >= 10; currentPolygonList = currentPolygonList->m_next)
	{
		index -= 10;
	}

	if (currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10] == NULL)
	{
		m_textureBlending = FALSE;
		UpdateData(FALSE);
		return;
	}

	if (currentPolygonList->m_textureModified[pDoc->m_currentPolygonIndex % 10] == FALSE)
	{
		// duplicate texture info
		currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]
			= new CStageTexture();
		currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_textureMode
			= currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureMode;
		//currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords
		//	= new CStageTextureCoords();
		for (i = 0; i < currentPolygonList->m_numberSides[pDoc->m_currentPolygonIndex % 10]; i += 4)
		{
			ptrTextureCoords = new CStageTextureCoords();
			ptrTextureCoords->m_next = currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords;
			currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords = ptrTextureCoords;

		}
		currentPolygonList->m_origTextureStartVertex[pDoc->m_currentPolygonIndex % 10]
			= currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10];

		ptrOrigTextureCoords = currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords;
		for (ptrTextureCoords = currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords;
			ptrTextureCoords != NULL; ptrTextureCoords = ptrTextureCoords->m_next)
		{
			for (i = 0; i < 4; i++)
			{
				ptrOrigTextureCoords->m_textureCoords[i][0] = ptrTextureCoords->m_textureCoords[i][0];
				ptrOrigTextureCoords->m_textureCoords[i][1] = ptrTextureCoords->m_textureCoords[i][1];
			}
			ptrOrigTextureCoords = ptrOrigTextureCoords->m_next;
		}


		if (currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage != NULL)
		{
			sprintf(currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_DIBFileName,
				"%s", currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_DIBFileName);
			currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage = new CGLImage();
			currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage->
				SpecialCreate(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage->m_iWidth,
				currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage->m_iHeight,
				currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage->m_pBits);

			//currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage
			//	= (class CGLImage *)malloc(sizeof(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage)) ;
			//memcpy(currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage,
			//	currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage,
			//	sizeof(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage));
		}
		currentPolygonList->m_textureModified[pDoc->m_currentPolygonIndex % 10] = TRUE;
	}

	UpdateData(TRUE);
	if (m_textureBlending == TRUE)
	{
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureMode
			= GL_MODULATE;
	}
	else
	{
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureMode
			= GL_DECAL;
	}

	pView->YoRender(YO_RENDER_FULL);
	return;

}

void CStageViewPart::OnTextureDelete() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	int index;
	CStagePolygonList *currentPolygonList;
	CStageTextureCoords *currentTextureCoords;
	CStageTextureCoords *ptrTextureCoords;

	YoCancelSnapInherit();
	if (pDoc->m_currentPolygonIndex < 0)
	{
		return;
	}
	
	index = pDoc->m_currentPolygonIndex;
	for (currentPolygonList = pDoc->m_currentPart->m_polygonList; index >= 10; currentPolygonList = currentPolygonList->m_next)
	{
		index -= 10;
	}

	if (currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10] == NULL)
	{
		return;
	}

	if (currentPolygonList->m_textureModified[pDoc->m_currentPolygonIndex % 10] == FALSE)
	{
		currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]
			= currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10];
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10] = NULL;
		currentPolygonList->m_textureModified[pDoc->m_currentPolygonIndex % 10] = TRUE;
		currentPolygonList->m_origTextureStartVertex[pDoc->m_currentPolygonIndex % 10]
			= currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10];
	}
	else
	{
		if (currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage != NULL)
		{
			//use same routine that allocated it
			//LocalFree(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage);
		}
		for (currentTextureCoords = currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords;
			currentTextureCoords != NULL;)
		{
			ptrTextureCoords = currentTextureCoords;
			currentTextureCoords = currentTextureCoords->m_next;
			delete(ptrTextureCoords);
		}
		delete(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]);
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10] = NULL;
		currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10] = 0;
	}

	pView->YoRender(YO_RENDER_FULL);
	return;

}

void CStageViewPart::OnTextureNew() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	int index;
	int i;
	CStagePolygonList *currentPolygonList;
	CStageTextureCoords *currentTextureCoords;
	CStageTextureCoords *ptrTextureCoords;
	CString s;

	if (pDoc->m_isMovement)
	{
		pDoc->YoEStop();
	}

	YoCancelSnapInherit();

	CFileDialog dlg
		(TRUE,    // open
		NULL,    // no default extension
		NULL,    // no initial file name
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		//"Image files (*.DIB, *.BMP)|*.DIB;*.BMP|All files (*.*)|*.*||");
		"All files (*.*)|*.*|Image files (*.DIB, *.BMP)|*.DIB;*.BMP||");

	// TODO: Add your control notification handler code here
	if (pDoc->m_currentPolygonIndex < 0)
	{
		return;
	}

	index = pDoc->m_currentPolygonIndex;
	for (currentPolygonList = pDoc->m_currentPart->m_polygonList; index >= 10; currentPolygonList = currentPolygonList->m_next)
	{
		index -= 10;
	}

	if (dlg.DoModal() == IDOK)
	{
		s = dlg.GetPathName();
	}
	else
	{
		return;
    }

	if (currentPolygonList->m_textureModified[pDoc->m_currentPolygonIndex % 10] == FALSE)
	{
		currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]
			= currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10];
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10] = NULL;
		currentPolygonList->m_origTextureStartVertex[pDoc->m_currentPolygonIndex % 10]
			= currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10];

		if (pDoc->m_currentPart->m_renderMode != YO_RENDER_MODE_TEXTURE_POLYGON_FILLED)
		{
			pDoc->m_currentPart->m_renderMode = YO_RENDER_MODE_TEXTURE_POLYGON_FILLED;
			m_partRenderMode.SetCurSel(pDoc->m_currentPart->m_renderMode);
			UpdateData(FALSE);
		}
		currentPolygonList->m_textureModified[pDoc->m_currentPolygonIndex % 10] = TRUE;
	}

	if (currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10] != NULL)
	{
		if (currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage != NULL)
		{
			//use same routine that allocated it
			//LocalFree(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage);
		}
		for (currentTextureCoords = currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords;
			currentTextureCoords != NULL;)
		{
			ptrTextureCoords = currentTextureCoords;
			currentTextureCoords = currentTextureCoords->m_next;
			delete(ptrTextureCoords);
		}
		delete(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]);
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10] = NULL;
	}


	// install new texture
	currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]
		= new CStageTexture();
	currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureMode
		= GL_DECAL;
	sprintf(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_DIBFileName, "%s", LPCSTR(s));
	currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->YoInitFromDIB();

	for (i = 0; i < currentPolygonList->m_numberSides[pDoc->m_currentPolygonIndex % 10]; i += 4)
	{
		ptrTextureCoords = new CStageTextureCoords();
		ptrTextureCoords->m_next = currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords = ptrTextureCoords;

	}

	currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10] = pDoc->m_closestVertexIndex;
	pDoc->m_currentPart->YoPositionTexture(pDoc->m_currentPolygonIndex, currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10]);
	/***
	if (pDoc->m_closestVertexIndex == 1)
	{
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[1][0] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[1][1] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[2][0] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[2][1] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[3][0] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[3][1] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[0][0] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[0][1] = 1.0;
	}
	else if (pDoc->m_closestVertexIndex == 2)
	{
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[2][0] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[2][1] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[3][0] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[3][1] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[0][0] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[0][1] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[1][0] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[1][1] = 1.0;
	}
	else if (pDoc->m_closestVertexIndex == 3)
	{
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[3][0] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[3][1] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[0][0] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[0][1] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[1][0] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[1][1] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[2][0] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[2][1] = 1.0;
	}
	else
	{
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[0][0] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[0][1] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[1][0] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[1][1] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[2][0] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[2][1] = 1.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[3][0] = 0.0;
		currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords->m_textureCoords[3][1] = 1.0;
	}
	***/

	pView->YoRender(YO_RENDER_FULL);
	return;
}


void CStageViewPart::OnTextureRotate() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	int index;
	int i;
	CStagePolygonList *currentPolygonList;
	CStageTextureCoords *ptrTextureCoords;
	CStageTextureCoords *ptrOrigTextureCoords;

	YoCancelSnapInherit();

	if (pDoc->m_currentPolygonIndex < 0)
	{
		return;
	}
	
	index = pDoc->m_currentPolygonIndex;
	for (currentPolygonList = pDoc->m_currentPart->m_polygonList; index >= 10; currentPolygonList = currentPolygonList->m_next)
	{
		index -= 10;
	}

	if (currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10] == NULL)
	{
		return;
	}

	if (currentPolygonList->m_textureModified[pDoc->m_currentPolygonIndex % 10] == FALSE)
	{
		// duplicate texture info
		currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]
			= new CStageTexture();
		currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_textureMode
			= currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureMode;
		currentPolygonList->m_origTextureStartVertex[pDoc->m_currentPolygonIndex % 10]
			= currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10];
		//currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords
		//	= new CStageTextureCoords();
		for (i = 0; i < currentPolygonList->m_numberSides[pDoc->m_currentPolygonIndex % 10]; i += 4)
		{
			ptrTextureCoords = new CStageTextureCoords();
			ptrTextureCoords->m_next = currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords;
			currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords = ptrTextureCoords;

		}

		ptrOrigTextureCoords = currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords;
		for (ptrTextureCoords = currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureCoords;
			ptrTextureCoords != NULL; ptrTextureCoords = ptrTextureCoords->m_next)
		{
			for (i = 0; i < 4; i++)
			{
				ptrOrigTextureCoords->m_textureCoords[i][0] = ptrTextureCoords->m_textureCoords[i][0];
				ptrOrigTextureCoords->m_textureCoords[i][1] = ptrTextureCoords->m_textureCoords[i][1];
			}
			ptrOrigTextureCoords = ptrOrigTextureCoords->m_next;
		}

		if (currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage != NULL)
		{
			sprintf(currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_DIBFileName,
				"%s", currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_DIBFileName);
			currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage = new CGLImage();
			currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage->
				SpecialCreate(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage->m_iWidth,
				currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage->m_iHeight,
				currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage->m_pBits);

			//currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage
			//	= (class CGLImage *)malloc(sizeof(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage)) ;
			//memcpy(currentPolygonList->m_origTexture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage,
			//	currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage,
			//	sizeof(currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_RGBImage));
		}
		currentPolygonList->m_textureModified[pDoc->m_currentPolygonIndex % 10] = TRUE;
	}

	if (currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10]
		>= currentPolygonList->m_numberSides[pDoc->m_currentPolygonIndex % 10] - 1)
	{
		currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10] = 0;
	}
	else
	{
		currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10]++;
	}

	pDoc->m_currentPart->YoPositionTexture(pDoc->m_currentPolygonIndex,
		currentPolygonList->m_textureStartVertex[pDoc->m_currentPolygonIndex % 10]);

	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageViewPart::OnSelchangeSnapToList() 
{
	YoCancelSnapInherit();

	if (m_snapToList.GetCurSel() == 0)
	{
		m_snapToMode = YO_SNAP_COORDINATE;
	}
	else if (m_snapToList.GetCurSel() == 1)
	{
		m_snapToMode = YO_SNAP_EDGE;
	}
	else if (m_snapToList.GetCurSel() == 2)
	{
		m_snapToMode = YO_SNAP_EDGE_CENTER;
	}
	else if (m_snapToList.GetCurSel() == 3)
	{
		m_snapToMode = YO_SNAP_PART;
	}
	else if (m_snapToList.GetCurSel() == 4)
	{
		m_snapToMode = YO_SNAP_POLYGON;
	}
	else if (m_snapToList.GetCurSel() == 5)
	{
		m_snapToMode = YO_SNAP_POLYGON_CENTER;
	}
	else if (m_snapToList.GetCurSel() == 6)
	{
		m_snapToMode = YO_SNAP_VERTEX;
	}
	return;		
}

void CStageViewPart::OnSnapTo() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[128];

	if (pDoc->m_isMovement)
	{
		pDoc->YoEStop();
	}

	m_inheritingMaterial = FALSE;
	m_selectingAltOrigin = FALSE;

	if (m_snapTo == FALSE)
	{
		m_snapTo = TRUE;

		if (m_snapToMode == YO_SNAP_COORDINATE)
		{
			sprintf(s, "Select a coordinate system to which the part will align, or click the snap to button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_EDGE)
		{
			sprintf(s, "Select an edge to which the part will align, or click the snap to button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_EDGE_CENTER)
		{
			sprintf(s, "Select an edge center to which the part will align, or click the snap to button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_PART)
		{
			sprintf(s, "Select another part to which the part will align, or click the snap to button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_POLYGON)
		{
			sprintf(s, "Select a polygon to which the part will align, or click the snap to button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_POLYGON_CENTER)
		{
			sprintf(s, "Select a polygon center to which the part will align, or click the snap to button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_VERTEX)
		{
			sprintf(s, "Select a vertex to which the part will align, or click the snap to button again to cancel");
		}

		pDoc->YoMessage(s);
		SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorSelect);
	}
	else
	{
		m_snapTo = FALSE;
		sprintf(s, "Snap To canceled");
		pDoc->YoMessage(s);
		SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);
	}

	return;
	
}

void CStageViewPart::OnKillfocusBarCode() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	pCBox = (CComboBox*)GetDlgItem(IDC_BAR_CODE);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%s", &pDoc->m_currentDevice->m_barCode);
	return;
	
}

void CStageViewPart::OnKillfocusMass() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	pCBox = (CComboBox*)GetDlgItem(IDC_MASS);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &pDoc->m_currentDevice->m_mass);
	return;	
}

void CStageViewPart::OnRotateIncreaseX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_X);
	pCBox->GetWindowText(s, 64);
	rotate[0] = 1.0;
	sscanf(s, "%lf", &tr);
	tr += 90.0;

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;


/***
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble m[16];
	GLdouble mInv[16];
	GLdouble translate[3];
	GLdouble rotate[3];
	int i;

	// TODO: Add your control notification handler code here

	if (m_originAltDisplayed == TRUE)
	{
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();
		pView->YoTxyz(pDoc->m_currentPart,
			pDoc->m_currentPart->m_translate,
			pDoc->m_currentPart->m_rotate);
		::glMultMatrixd(pDoc->m_currentPart->m_altOrigin);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
		pDoc->m_currentPart->m_txyz = YO_TXYZ_TXYZ;
		pDoc->YoTranslateRotateValues(m, translate, rotate);
		for (i = 0; i < 3; i++)
		{
			rotate[i] *= YO_RADIANS_TO_DEGREES;
		}
		rotate[0] += 90.0;
		sprintf(s, "%.1lf", rotate[0]);
		::glLoadIdentity();
		pView->YoTxyz(pDoc->m_currentPart, translate, rotate);
		pDoc->YoMatrixInverse(pDoc->m_currentPart->m_altOrigin, mInv);
		::glMultMatrixd(mInv);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
		pDoc->m_currentPart->m_txyz = YO_TXYZ_TXYZ;
		pDoc->YoTranslateRotateValues(m,
			pDoc->m_currentPart->m_translate,
			pDoc->m_currentPart->m_rotate);
		for (i = 0; i < 3; i++)
		{
			pDoc->m_currentPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
		}
		::glPopMatrix();
	}
	else
	{
		pDoc->m_currentPart->m_rotate[0] += 90.0;
		if (pDoc->m_currentPart->m_rotate[0] >= 360.0)
		{
			pDoc->m_currentPart->m_rotate[0] -= 360.0;
		}
		sprintf(s, "%.1lf", pDoc->m_currentPart->m_rotate[0]);
	}

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;
***/

}

void CStageViewPart::OnRotateIncreaseY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Y);
	pCBox->GetWindowText(s, 64);
	rotate[1] = 1.0;
	sscanf(s, "%lf", &tr);
	tr += 90.0;

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;

}

void CStageViewPart::OnRotateIncreaseZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Z);
	pCBox->GetWindowText(s, 64);
	rotate[2] = 1.0;
	sscanf(s, "%lf", &tr);
	tr += 90.0;

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;

}

void CStageViewPart::OnRotateDecreaseX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_X);
	pCBox->GetWindowText(s, 64);
	rotate[0] = 1.0;
	sscanf(s, "%lf", &tr);
	tr -= 90.0;

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;

}

void CStageViewPart::OnRotateDecreaseY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Y);
	pCBox->GetWindowText(s, 64);
	rotate[1] = 1.0;
	sscanf(s, "%lf", &tr);
	tr -= 90.0;

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;

}

void CStageViewPart::OnRotateDecreaseZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble tr;
	GLdouble translate[3] = {0.0, 0.0, 0.0};
	GLdouble rotate[3] = {0.0, 0.0, 0.0};

	YoCancelSnapInherit();

	pCBox = (CComboBox*)GetDlgItem(IDC_ROTATE_Z);
	pCBox->GetWindowText(s, 64);
	rotate[2] = 1.0;
	sscanf(s, "%lf", &tr);
	tr -= 90.0;

	YoTranslateRotate(translate, rotate, tr);
	YoUpdateTranslateRotate();
	
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		pView->YoRender(YO_RENDER_LIGHT);
	}
	pView->YoRender(YO_RENDER_FULL);
	return;

}

void CStageViewPart::OnKillfocusSmoothShadeAngle() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	pCBox = (CComboBox*)GetDlgItem(IDC_SMOOTH_SHADE_ANGLE);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%f", &pDoc->m_currentPart->m_smoothShadeAngle);

	pDoc->m_currentPart->YoComputeNormals();
	sprintf(s, "%.1f", pDoc->m_currentPart->m_smoothShadeAngle);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}


void CStageViewPart::OnOriginAltCreate() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[128];

	if (pDoc->m_isMovement)
	{
		pDoc->YoEStop();
	}

	m_snapTo = FALSE;
	m_inheritingMaterial = FALSE;

	if (m_selectingAltOrigin == FALSE)
	{
		m_selectingAltOrigin = TRUE;

		if (m_snapToMode == YO_SNAP_COORDINATE)
		{
			sprintf(s, "Select a coordinate system as the part's alternate origin, or click the alternate button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_EDGE)
		{
			sprintf(s, "Select an edge as the part's alternate origin, or click the alternate button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_EDGE_CENTER)
		{
			sprintf(s, "Select an edge center as the part's alternate origin, or click the alternate button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_PART)
		{
			sprintf(s, "Select another part as the part's alternate origin, or click the alternate button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_POLYGON)
		{
			sprintf(s, "Select a polygon as the part's alternate origin, or click the alternate button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_POLYGON_CENTER)
		{
			sprintf(s, "Select a polygon center as the part's alternate origin, or click the alternate button again to cancel");
		}
		else if (m_snapToMode == YO_SNAP_VERTEX)
		{
			sprintf(s, "Select a vertex as the part's alternate origin, or click the alternate button again to cancel");
		}

		pDoc->YoMessage(s);
		SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorSelect);
	}
	else
	{
		m_selectingAltOrigin = FALSE;
		sprintf(s, "Select alternative origin canceled");
		pDoc->YoMessage(s);
		SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);
	}

	return;		
}

void CStageViewPart::OnOriginAltDisplayed() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[128];

	YoCancelSnapInherit();

	// make certain that alternative origin has been specified
	if (pDoc->m_currentPart->m_altOrigin[0] == 1.0
		&& pDoc->m_currentPart->m_altOrigin[1] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[2] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[3] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[4] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[5] == 1.0
		&& pDoc->m_currentPart->m_altOrigin[6] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[7] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[8] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[9] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[10] == 1.0
		&& pDoc->m_currentPart->m_altOrigin[11] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[12] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[13] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[14] == 0.0
		&& pDoc->m_currentPart->m_altOrigin[15] == 1.0)
	{
		sprintf(s, "Alternate origin cannot be checked.  First define an alternate origin by selecting the Alternate button");
		pDoc->YoMessage(s);
		m_originAltDisplayed = FALSE;
		UpdateData(FALSE);
		return;
	}

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	pDoc->m_currentPart->m_altOriginDisplayed = m_originAltDisplayed;

	YoUpdateTranslateRotate();
	pView->YoRender(YO_RENDER_FULL);

	return;	
}


void CStageViewPart::OnOriginVisible() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	YoCancelSnapInherit();
	UpdateData(TRUE);
	pDoc->m_currentPart->m_originVisible = m_originVisible;
	
	//pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
}


void CStageViewPart::OnSetfocusTranslateX() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusBarCode() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusMass() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusPartAlpha() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusPartBlue() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusPartGreen() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusPartRed() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusPartShininess() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusRotateX() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusRotateY() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusRotateZ() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusSmoothShadeAngle() 
{
	YoCancelSnapInherit();
	return;
}

void CStageViewPart::OnSetfocusTranslateY() 
{
	YoCancelSnapInherit();
	return;	
}

void CStageViewPart::OnSetfocusTranslateZ() 
{
	YoCancelSnapInherit();
	return;
}
