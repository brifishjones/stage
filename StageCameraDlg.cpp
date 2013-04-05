// StageCameraDlg.cpp : implementation file
//
#include "stdafx.h"
#include "stage.h"
#include "stageViewPart.h"
#include "StageCameraDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageCameraDlg dialog


CStageCameraDlg::CStageCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageCameraDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageCameraDlg::IDD, pParent);
	//{{AFX_DATA_INIT(CStageCameraDlg)
	m_cameraEnabled = FALSE;
	//}}AFX_DATA_INIT
}


void CStageCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageCameraDlg)
	DDX_Control(pDX, IDC_CAMERA_SLIDER_FIELD_OF_VIEW, m_cameraSliderFOV);
	DDX_Check(pDX, IDC_CAMERA_ENABLED, m_cameraEnabled);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageCameraDlg, CDialog)
	//{{AFX_MSG_MAP(CStageCameraDlg)
	ON_EN_KILLFOCUS(IDC_CAMERA_CLIP_FRONT, OnKillfocusCameraClipFront)
	ON_EN_KILLFOCUS(IDC_CAMERA_CLIP_REAR, OnKillfocusCameraClipRear)
	ON_BN_CLICKED(IDC_CAMERA_ENABLED, OnCameraEnabled)
	ON_EN_KILLFOCUS(IDC_CAMERA_FIELD_OF_VIEW, OnKillfocusCameraFieldOfView)
	ON_BN_CLICKED(IDC_RESTORE_CAMERA_CLIP_FRONT, OnRestoreCameraClipFront)
	ON_BN_CLICKED(IDC_RESTORE_CAMERA_CLIP_REAR, OnRestoreCameraClipRear)
	ON_BN_CLICKED(IDC_RESTORE_CAMERA_FIELD_OF_VIEW, OnRestoreCameraFieldOfView)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageCameraDlg message handlers

void CStageCameraDlg::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
	delete this;
}


BOOL CStageCameraDlg::YoInitDialog() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
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

	m_origFieldOfView = ((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView;
	m_origClipFront = ((CStageCamera *)pDoc->m_currentDevice)->m_clipFront;
	m_origClipRear = ((CStageCamera *)pDoc->m_currentDevice)->m_clipRear;

	sprintf(s, "%.1lf", m_origFieldOfView);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_CAMERA_FIELD_OF_VIEW);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)GetDlgItem(IDC_CAMERA_CLIP_FRONT);
	sprintf(s, "%.1lf", m_origClipFront * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)GetDlgItem(IDC_CAMERA_CLIP_REAR);
	sprintf(s, "%.1lf", m_origClipRear * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)GetDlgItem(IDC_CAMERA_SLIDER_FIELD_OF_VIEW);
	((CSliderCtrl *)pCBox)->SetRange(0, 180);
	m_cameraSliderFOV.SetPos((int)m_origFieldOfView);

	m_cameraEnabled = ((CStageCamera *)pDoc->m_currentDevice)->m_enabled;
	UpdateData(FALSE);
	
	if (((CStageCamera *)pDoc->m_currentDevice)->m_enabled)
	{
		pDoc->m_camera = (CStageCamera *)pDoc->m_currentDevice;

		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView,
			pView->m_aspectRatio,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipFront,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipRear);

		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}
	else
	{
		pDoc->m_camera = NULL;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CStageCameraDlg::OnKillfocusCameraClipFront() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[32];
	GLdouble clipFront;

	pCBox = (CComboBox*)GetDlgItem(IDC_CAMERA_CLIP_FRONT);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &clipFront);
	((CStageCamera *)pDoc->m_currentDevice)->m_clipFront = clipFront / pDoc->m_unitScaleFactor; 

	((CStageCamera *)pDoc->m_currentDevice)->m_clipFront
		= YO_MAX(((CStageCamera *)pDoc->m_currentDevice)->m_clipFront, 0.1);
	((CStageCamera *)pDoc->m_currentDevice)->m_clipFront
		= YO_MIN(((CStageCamera *)pDoc->m_currentDevice)->m_clipFront,
		((CStageCamera *)pDoc->m_currentDevice)->m_clipRear);
	sprintf(s, "%.1lf", ((CStageCamera *)pDoc->m_currentDevice)->m_clipFront * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	if (((CStageCamera *)pDoc->m_currentDevice)->m_enabled)
	{
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView,
			pView->m_aspectRatio,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipFront,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipRear);

		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}
	return;	
}

void CStageCameraDlg::OnKillfocusCameraClipRear() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[32];
	GLdouble clipRear;

	pCBox = (CComboBox*)GetDlgItem(IDC_CAMERA_CLIP_REAR);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &clipRear);
	((CStageCamera *)pDoc->m_currentDevice)->m_clipRear = clipRear / pDoc->m_unitScaleFactor; 

	((CStageCamera *)pDoc->m_currentDevice)->m_clipRear
		= YO_MAX(((CStageCamera *)pDoc->m_currentDevice)->m_clipRear,
		((CStageCamera *)pDoc->m_currentDevice)->m_clipFront);
	sprintf(s, "%.1lf", ((CStageCamera *)pDoc->m_currentDevice)->m_clipRear * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	if (((CStageCamera *)pDoc->m_currentDevice)->m_enabled)
	{
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView,
			pView->m_aspectRatio,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipFront,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipRear);

		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}

	return;		
}

void CStageCameraDlg::OnCameraEnabled() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	((CStageCamera *)pDoc->m_currentDevice)->m_enabled = m_cameraEnabled;

	if (((CStageCamera *)pDoc->m_currentDevice)->m_enabled)
	{
		pDoc->m_camera = (CStageCamera *)pDoc->m_currentDevice;

		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView,
			pView->m_aspectRatio,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipFront,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipRear);
	}
	else
	{
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
	}
		
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageCameraDlg::OnKillfocusCameraFieldOfView() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)GetDlgItem(IDC_CAMERA_FIELD_OF_VIEW);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView);
	
	((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView
		= YO_MAX(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView, 0.0);
	((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView
		= YO_MIN(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView, 180.0);
	sprintf(s, "%.1lf", ((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	m_cameraSliderFOV.SetPos((int)((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView);

	if (((CStageCamera *)pDoc->m_currentDevice)->m_enabled)
	{
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView,
			pView->m_aspectRatio,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipFront,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipRear);

		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}

	return;		
}

void CStageCameraDlg::OnRestoreCameraClipFront() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)GetDlgItem(IDC_CAMERA_CLIP_FRONT);
	((CStageCamera *)pDoc->m_currentDevice)->m_clipFront = m_origClipFront;
	sprintf(s, "%.1lf", ((CStageCamera *)pDoc->m_currentDevice)->m_clipFront * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (((CStageCamera *)pDoc->m_currentDevice)->m_enabled)
	{
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView,
			pView->m_aspectRatio,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipFront,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipRear);

		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}

	return;	
}

void CStageCameraDlg::OnRestoreCameraClipRear() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)GetDlgItem(IDC_CAMERA_CLIP_REAR);
	((CStageCamera *)pDoc->m_currentDevice)->m_clipRear = m_origClipRear;
	sprintf(s, "%.1lf", ((CStageCamera *)pDoc->m_currentDevice)->m_clipRear * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (((CStageCamera *)pDoc->m_currentDevice)->m_enabled)
	{
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView,
			pView->m_aspectRatio,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipFront,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipRear);

		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}

	return;
}

void CStageCameraDlg::OnRestoreCameraFieldOfView() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)GetDlgItem(IDC_CAMERA_FIELD_OF_VIEW);
	((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView = m_origFieldOfView;	
	sprintf(s, "%.1lf", ((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	m_cameraSliderFOV.SetPos((int)((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView);

	if (((CStageCamera *)pDoc->m_currentDevice)->m_enabled)
	{
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView,
			pView->m_aspectRatio,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipFront,
			((CStageCamera *)pDoc->m_currentDevice)->m_clipRear);

		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}	
}


void CStageCameraDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[32];
	CWnd *pCBox;

	if ((CSliderCtrl *)pScrollBar == &m_cameraSliderFOV)
	{
		((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView = m_cameraSliderFOV.GetPos();
		sprintf(s, "%.1lf", ((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView);
		pCBox = (CComboBox*)GetDlgItem(IDC_CAMERA_FIELD_OF_VIEW);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		if (((CStageCamera *)pDoc->m_currentDevice)->m_enabled)
		{
			::glMatrixMode(GL_PROJECTION);
			::glLoadIdentity();
			::gluPerspective(((CStageCamera *)pDoc->m_currentDevice)->m_fieldOfView,
				pView->m_aspectRatio,
				((CStageCamera *)pDoc->m_currentDevice)->m_clipFront,
				((CStageCamera *)pDoc->m_currentDevice)->m_clipRear);

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
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	return;
}

void CStageCameraDlg::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}
