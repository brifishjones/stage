// StageEyeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageEyeDialog.h"

#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageEyeDialog dialog


CStageEyeDialog::CStageEyeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStageEyeDialog::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageEyeDialog::IDD, pParent);
	//{{AFX_DATA_INIT(CStageEyeDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageEyeDialog::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageEyeDialog)
	DDX_Control(pDX, IDC_EYE_SLIDER_FOV, m_eyeSliderFOV);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageEyeDialog, CDialog)
	//{{AFX_MSG_MAP(CStageEyeDialog)
	ON_EN_KILLFOCUS(IDC_EYE_CLIPFRONT, OnKillfocusEyeClipfront)
	ON_BN_CLICKED(IDC_EYE_CLIPFRONT_RESTORE, OnEyeClipfrontRestore)
	ON_EN_KILLFOCUS(IDC_EYE_CLIPREAR, OnKillfocusEyeCliprear)
	ON_BN_CLICKED(IDC_EYE_CLIPREAR_RESTORE, OnEyeCliprearRestore)
	ON_EN_KILLFOCUS(IDC_EYE_TOX, OnKillfocusEyeTox)
	ON_EN_KILLFOCUS(IDC_EYE_TOY, OnKillfocusEyeToy)
	ON_EN_KILLFOCUS(IDC_EYE_TOZ, OnKillfocusEyeToz)
	ON_EN_KILLFOCUS(IDC_EYE_FROMX, OnKillfocusEyeFromx)
	ON_EN_KILLFOCUS(IDC_EYE_FROMY, OnKillfocusEyeFromy)
	ON_EN_KILLFOCUS(IDC_EYE_FROMZ, OnKillfocusEyeFromz)
	ON_BN_CLICKED(IDC_EYE_RESTORE_FOV, OnEyeRestoreFov)
	ON_BN_CLICKED(IDC_EYE_RESTORE_FROM, OnEyeRestoreFrom)
	ON_BN_CLICKED(IDC_EYE_RESTORE_TO, OnEyeRestoreTo)
	ON_EN_KILLFOCUS(IDC_EYE_FOV, OnKillfocusEyeFov)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageEyeDialog message handlers

BOOL CStageEyeDialog::YoInitDialog() 
{
	m_init = TRUE;

	CDialog::OnInitDialog();

	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStageEyeDialog::OnKillfocusEyeClipfront() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];
	GLdouble clipFront;
	RECT rect;

	pMainFrame->GetWindowRect(&rect);
	if (rect.right - rect.left < YO_THRESH_WIDTH || pMainFrame->m_wndDlgEyeVisible == FALSE
		|| pMainFrame->m_wndDlgEye == NULL)
	{
		return;
	}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_CLIPFRONT);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &clipFront);
	pView->m_clipFront = clipFront / pDoc->m_unitScaleFactor; 

	pView->m_clipFront = YO_MAX(pView->m_clipFront, 0.1);
	pView->m_clipFront = YO_MIN(pView->m_clipFront, pView->m_clipRear);
	sprintf(s, "%.2lf", pView->m_clipFront * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	::glMatrixMode(GL_MODELVIEW);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageEyeDialog::OnEyeClipfrontRestore() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_CLIPFRONT);
	pView->m_clipFront = m_clipFrontOrig;
	sprintf(s, "%.2lf", pView->m_clipFront * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	::glMatrixMode(GL_MODELVIEW);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageEyeDialog::OnKillfocusEyeCliprear() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];
	GLdouble clipRear;
	RECT rect;

	pMainFrame->GetWindowRect(&rect);
	if (rect.right - rect.left < YO_THRESH_WIDTH || pMainFrame->m_wndDlgEyeVisible == FALSE
		|| pMainFrame->m_wndDlgEye == NULL)
	{
		return;
	}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_CLIPREAR);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &clipRear);
	pView->m_clipRear = clipRear / pDoc->m_unitScaleFactor;

	pView->m_clipRear = YO_MAX(pView->m_clipRear, pView->m_clipFront);
	sprintf(s, "%.2lf", pView->m_clipRear * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	::glMatrixMode(GL_MODELVIEW);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageEyeDialog::OnEyeCliprearRestore() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_CLIPREAR);
	pView->m_clipRear = m_clipRearOrig;
	sprintf(s, "%.1lf", pView->m_clipRear * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	::glMatrixMode(GL_MODELVIEW);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageEyeDialog::OnKillfocusEyeTox() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];
	GLdouble toX;
	RECT rect;

	pMainFrame->GetWindowRect(&rect);
	if (rect.right - rect.left < YO_THRESH_WIDTH || pMainFrame->m_wndDlgEyeVisible == FALSE
		|| pMainFrame->m_wndDlgEye == NULL)
	{
		return;
	}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOX);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &toX);
	pView->m_eye[3] = toX / pDoc->m_unitScaleFactor;
	
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageEyeDialog::OnKillfocusEyeToy() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];
	GLdouble toY;
	RECT rect;

	pMainFrame->GetWindowRect(&rect);
	if (rect.right - rect.left < YO_THRESH_WIDTH || pMainFrame->m_wndDlgEyeVisible == FALSE
		|| pMainFrame->m_wndDlgEye == NULL)
	{
		return;
	}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOY);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &toY);
	pView->m_eye[4] = toY / pDoc->m_unitScaleFactor;
	
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageEyeDialog::OnKillfocusEyeToz() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];
	GLdouble toZ;
	RECT rect;

	pMainFrame->GetWindowRect(&rect);
	if (rect.right - rect.left < YO_THRESH_WIDTH || pMainFrame->m_wndDlgEyeVisible == FALSE
		|| pMainFrame->m_wndDlgEye == NULL)
	{
		return;
	}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOZ);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &toZ);
	pView->m_eye[5] = toZ / pDoc->m_unitScaleFactor;
	
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageEyeDialog::OnKillfocusEyeFromx() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];
	GLdouble fromX;
	RECT rect;

	pMainFrame->GetWindowRect(&rect);
	if (rect.right - rect.left < YO_THRESH_WIDTH || pMainFrame->m_wndDlgEyeVisible == FALSE
		|| pMainFrame->m_wndDlgEye == NULL)
	{
		return;
	}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMX);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &fromX);
	pView->m_eye[0] = fromX / pDoc->m_unitScaleFactor; 
	
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageEyeDialog::OnKillfocusEyeFromy() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];
	GLdouble fromY;
	RECT rect;

	pMainFrame->GetWindowRect(&rect);
	if (rect.right - rect.left < YO_THRESH_WIDTH || pMainFrame->m_wndDlgEyeVisible == FALSE
		|| pMainFrame->m_wndDlgEye == NULL)
	{
		return;
	}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMY);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &fromY);
	pView->m_eye[1] = fromY / pDoc->m_unitScaleFactor; 
	
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageEyeDialog::OnKillfocusEyeFromz() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];
	GLdouble fromZ;
	RECT rect;

	pMainFrame->GetWindowRect(&rect);
	if (rect.right - rect.left < YO_THRESH_WIDTH || pMainFrame->m_wndDlgEyeVisible == FALSE
		|| pMainFrame->m_wndDlgEye == NULL)
	{
		return;
	}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMZ);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &fromZ);
	pView->m_eye[2] = fromZ / pDoc->m_unitScaleFactor; 
	
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageEyeDialog::OnEyeRestoreFov() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FOV);
	pView->m_fieldOfView = m_fieldOfViewOrig;	
	sprintf(s, "%.1lf", pView->m_fieldOfView);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	m_eyeSliderFOV.SetPos((int)pView->m_fieldOfView);

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	::glMatrixMode(GL_MODELVIEW);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageEyeDialog::OnEyeRestoreFrom() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMX);
	pView->m_eye[0] = m_eyeOrig[0];	
	sprintf(s, "%.1lf", pView->m_eye[0] * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMY);
	pView->m_eye[1] = m_eyeOrig[1];	
	sprintf(s, "%.1lf", pView->m_eye[1] * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMZ);
	pView->m_eye[2] = m_eyeOrig[2];	
	sprintf(s, "%.1lf", pView->m_eye[2] * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageEyeDialog::OnEyeRestoreTo() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOX);
	pView->m_eye[3] = m_eyeOrig[3];	
	sprintf(s, "%.1lf", pView->m_eye[3] * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOY);
	pView->m_eye[4] = m_eyeOrig[4];	
	sprintf(s, "%.1lf", pView->m_eye[4] * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOZ);
	pView->m_eye[5] = m_eyeOrig[5];	
	sprintf(s, "%.1lf", pView->m_eye[5] * pDoc->m_unitScaleFactor);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageEyeDialog::OnKillfocusEyeFov() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];
	RECT rect;

	pMainFrame->GetWindowRect(&rect);
	if (rect.right - rect.left < YO_THRESH_WIDTH || pMainFrame->m_wndDlgEyeVisible == FALSE
		|| pMainFrame->m_wndDlgEye == NULL)
	{
		return;
	}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FOV);
	pCBox->GetWindowText(s, 32);
	sscanf(s, "%lf", &pView->m_fieldOfView);
	
	pView->m_fieldOfView = YO_MAX(pView->m_fieldOfView, 0.0);
	pView->m_fieldOfView = YO_MIN(pView->m_fieldOfView, 180.0);
	sprintf(s, "%.1lf", pView->m_fieldOfView);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	m_eyeSliderFOV.SetPos((int)pView->m_fieldOfView);

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	::glMatrixMode(GL_MODELVIEW);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageEyeDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	char s[32];
	CWnd *pCBox;

	if ((CSliderCtrl *)pScrollBar == &m_eyeSliderFOV)
	{
		pView->m_fieldOfView = m_eyeSliderFOV.GetPos();
		sprintf(s, "%.1lf", pView->m_fieldOfView);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FOV);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
			pView->m_clipFront, pView->m_clipRear);
		::glMatrixMode(GL_MODELVIEW);

		//::glMatrixMode(GL_MODELVIEW);
		//::glLoadIdentity();
		//::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		//	pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		//	pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

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
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CStageEyeDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}
