// StageViewTag.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageViewTag.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageViewTag dialog


CStageViewTag::CStageViewTag(CWnd* pParent /*=NULL*/)
	: CDialog(CStageViewTag::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageViewTag::IDD, pParent);

	//{{AFX_DATA_INIT(CStageViewTag)
	m_visible = FALSE;
	m_pathGreen = 0;
	m_pathRed = 0;
	m_pathBlue = 0;
	//}}AFX_DATA_INIT
}


void CStageViewTag::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageViewTag)
	DDX_Control(pDX, IDC_TAG_SNAP, m_tagSnap);
	DDX_Control(pDX, IDC_PATH_SLIDER_RED, m_pathSliderRed);
	DDX_Control(pDX, IDC_PATH_SLIDER_GREEN, m_pathSliderGreen);
	DDX_Control(pDX, IDC_PATH_SLIDER_BLUE, m_pathSliderBlue);
	DDX_Check(pDX, IDC_PATH_VISIBLE, m_visible);
	DDX_Text(pDX, IDC_PATH_GREEN, m_pathGreen);
	DDV_MinMaxUInt(pDX, m_pathGreen, 0, 255);
	DDX_Text(pDX, IDC_PATH_RED, m_pathRed);
	DDV_MinMaxUInt(pDX, m_pathRed, 0, 255);
	DDX_Text(pDX, IDC_PATH_BLUE, m_pathBlue);
	DDV_MinMaxUInt(pDX, m_pathBlue, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageViewTag, CDialog)
	//{{AFX_MSG_MAP(CStageViewTag)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_PATH_BLUE, OnKillfocusPathBlue)
	ON_EN_KILLFOCUS(IDC_PATH_GREEN, OnKillfocusPathGreen)
	ON_EN_KILLFOCUS(IDC_PATH_RED, OnKillfocusPathRed)
	ON_EN_KILLFOCUS(IDC_TAG_ROTATE_X, OnKillfocusTagRotateX)
	ON_EN_KILLFOCUS(IDC_TAG_ROTATE_Y, OnKillfocusTagRotateY)
	ON_EN_KILLFOCUS(IDC_TAG_ROTATE_Z, OnKillfocusTagRotateZ)
	ON_EN_KILLFOCUS(IDC_TAG_TRANSLATE_X, OnKillfocusTagTranslateX)
	ON_EN_KILLFOCUS(IDC_TAG_TRANSLATE_Y, OnKillfocusTagTranslateY)
	ON_EN_KILLFOCUS(IDC_TAG_TRANSLATE_Z, OnKillfocusTagTranslateZ)
	ON_BN_CLICKED(IDC_TAG_TRANSLATE, OnTagTranslateRestore)
	ON_BN_CLICKED(IDC_TAG_ROTATE, OnTagRotateRestore)
	ON_BN_CLICKED(IDC_PATH_BLUE_RESTORE, OnPathBlueRestore)
	ON_BN_CLICKED(IDC_PATH_GREEN_RESTORE, OnPathGreenRestore)
	ON_BN_CLICKED(IDC_PATH_RED_RESTORE, OnPathRedRestore)
	ON_BN_CLICKED(IDC_TAG_90_X, OnTag90X)
	ON_BN_CLICKED(IDC_TAG_90_Y, OnTag90Y)
	ON_BN_CLICKED(IDC_TAG_90_Z, OnTag90Z)
	ON_CBN_SELCHANGE(IDC_TAG_SNAP, OnSelchangeTagSnap)
	ON_BN_CLICKED(IDC_PATH_VISIBLE, OnPathVisible)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageViewTag message handlers

BOOL CStageViewTag::YoInitDialog() 
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
	char s[128];

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
	rect.top -= 20;
	rect.bottom -= 20;
	this->MoveWindow(&rect, TRUE);

	m_origVisible = pDoc->m_currentTag->m_ptrPath->m_visible;
	for (i = 0; i < 3; i++)
	{
		m_origTranslate[i] = pDoc->m_currentTag->m_translate[i];
		m_origRotate[i] = pDoc->m_currentTag->m_rotate[i];
		m_origColor[i] = pDoc->m_currentTag->m_ptrPath->m_color[i];
	}

	// init dialog

	sprintf(s, "%s  -  %d", pDoc->m_currentTag->m_ptrPath->m_name,
		pDoc->m_currentTag->m_tag);
	SetWindowText((LPCTSTR)s);

	pCBox = (CComboBox*)this->GetDlgItem(IDC_PATH_DEVICE);
	pCBox->SetWindowText(pDoc->m_currentTag->m_ptrPath->m_ptrPart->m_deviceName);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)this->GetDlgItem(IDC_PATH_PART);
	pCBox->SetWindowText(pDoc->m_currentTag->m_ptrPath->m_ptrPart->m_partName);
	pCBox->UpdateWindow();

	m_visible = pDoc->m_currentTag->m_ptrPath->m_visible;

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_translate[0] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_TRANSLATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_translate[1] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_TRANSLATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_translate[2] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_TRANSLATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[0]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_ROTATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_ROTATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[2]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_ROTATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	m_pathRed = (UINT)(pDoc->m_currentTag->m_ptrPath->m_color[0] * 255.0);
	m_pathGreen = (UINT)(pDoc->m_currentTag->m_ptrPath->m_color[1] * 255.0);
	m_pathBlue = (UINT)(pDoc->m_currentTag->m_ptrPath->m_color[2] * 255.0);

	m_tagSnap.ResetContent();
	m_tagSnap.AddString("Coordinate");
	m_tagSnap.AddString("Edge");
	m_tagSnap.AddString("Edge Center");
	m_tagSnap.AddString("Part");
	m_tagSnap.AddString("Polygon");
	m_tagSnap.AddString("Polygon Center");
	m_tagSnap.AddString("Vertex");
	m_tagSnap.SetCurSel(pDoc->m_snapToViewTag);
	m_tagSnapMode = pDoc->m_snapToViewTag;

	m_pathSliderRed.SetRange(0, 255);
	m_pathSliderRed.SetPos(m_pathRed);
	m_pathSliderGreen.SetRange(0, 255);
	m_pathSliderGreen.SetPos(m_pathGreen);
	m_pathSliderBlue.SetRange(0, 255);
	m_pathSliderBlue.SetPos(m_pathBlue);

	if (m_visible)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_PATH_VISIBLE);
		((CButton *)pCBox)->SetCheck(1);
	}

	UpdateData(FALSE);
	SetClassLong(((CStageView *)pView)->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorSelect);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageViewTag::YoUpdateDialog() 
{
	CWnd* pCBox;
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[128];

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_translate[0] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_TRANSLATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_translate[1] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_TRANSLATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_translate[2] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_TRANSLATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[0]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_ROTATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_ROTATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[2]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_ROTATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	return;
}


void CStageViewTag::PostNcDestroy() 
{
	//CFrameWnd *pMainFrame = GetTopLevelFrame();
	//CStageView *pView = (CStageView *)pMainFrame->GetActiveView();

	// TODO: Add your specialized code here and/or call the base class
	//SetClassLong(((CStageView *)pView)->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);
	CDialog::PostNcDestroy();
	delete this;
}


void CStageViewTag::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your message handler code here and/or call default
	if ((CSliderCtrl *)pScrollBar == &m_pathSliderRed)
	{
		m_pathRed = m_pathSliderRed.GetPos();
		pDoc->m_currentTag->m_ptrPath->m_color[0] = (GLfloat)m_pathRed / 255.0f;
	}
	else if ((CSliderCtrl *)pScrollBar == &m_pathSliderGreen)
	{
		m_pathGreen = m_pathSliderGreen.GetPos();
		pDoc->m_currentTag->m_ptrPath->m_color[1] = (GLfloat)m_pathGreen / 255.0f;
	}
	else if ((CSliderCtrl *)pScrollBar == &m_pathSliderBlue)
	{
		m_pathBlue = m_pathSliderBlue.GetPos();
		pDoc->m_currentTag->m_ptrPath->m_color[2] = (GLfloat)m_pathBlue / 255.0f;
	}

	UpdateData(FALSE);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	if (nSBCode == SB_ENDSCROLL)
	{
		pView->YoRender(YO_RENDER_FULL);
	}
	else
	{
		pView->YoRender(YO_RENDER_QUICK);
	}
}

void CStageViewTag::OnKillfocusPathBlue() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_pathSliderBlue.SetPos(m_pathBlue);
	pDoc->m_currentTag->m_ptrPath->m_color[2] = (GLfloat)m_pathBlue / 255.0f;
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageViewTag::OnKillfocusPathGreen() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_pathSliderGreen.SetPos(m_pathGreen);
	pDoc->m_currentTag->m_ptrPath->m_color[1] = (GLfloat)m_pathGreen / 255.0f;
	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageViewTag::OnKillfocusPathRed() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_pathSliderRed.SetPos(m_pathRed);
	pDoc->m_currentTag->m_ptrPath->m_color[0] = (GLfloat)m_pathRed / 255.0f;
	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageViewTag::OnKillfocusTagRotateX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_ROTATE_X);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &pDoc->m_currentTag->m_rotate[0]);

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewTag::OnKillfocusTagRotateY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_ROTATE_Y);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &pDoc->m_currentTag->m_rotate[1]);

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewTag::OnKillfocusTagRotateZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_ROTATE_Z);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &pDoc->m_currentTag->m_rotate[2]);

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewTag::OnKillfocusTagTranslateX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_TRANSLATE_X);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);
	pDoc->m_currentTag->m_translate[0] = t / pDoc->m_unitScaleFactor;
	
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewTag::OnKillfocusTagTranslateY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_TRANSLATE_Y);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);
	pDoc->m_currentTag->m_translate[1] = t / pDoc->m_unitScaleFactor;
	
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewTag::OnKillfocusTagTranslateZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_TRANSLATE_Z);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);
	pDoc->m_currentTag->m_translate[2] = t / pDoc->m_unitScaleFactor;
	
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewTag::OnTagTranslateRestore() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[32];
	CWnd *pCBox;

	pDoc->m_currentTag->m_translate[0] = m_origTranslate[0];
	sprintf(s, "%.1lf", pDoc->m_currentTag->m_translate[0]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_TRANSLATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pDoc->m_currentTag->m_translate[1] = m_origTranslate[1];
	sprintf(s, "%.1lf", pDoc->m_currentTag->m_translate[1]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_TRANSLATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pDoc->m_currentTag->m_translate[2] = m_origTranslate[2];
	sprintf(s, "%.1lf", pDoc->m_currentTag->m_translate[2]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_TRANSLATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageViewTag::OnTagRotateRestore() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[32];
	CWnd *pCBox;

	pDoc->m_currentTag->m_rotate[0] = m_origRotate[0];
	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[0]);
	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_ROTATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pDoc->m_currentTag->m_rotate[1] = m_origRotate[1];
	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[1]);
	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_ROTATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pDoc->m_currentTag->m_rotate[2] = m_origRotate[2];
	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[2]);
	pCBox = (CComboBox*)GetDlgItem(IDC_TAG_ROTATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageViewTag::OnPathBlueRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	pDoc->m_currentTag->m_ptrPath->m_color[2] = m_origColor[2];
	m_pathBlue = (UINT)(pDoc->m_currentTag->m_ptrPath->m_color[2] * 255.0);
	UpdateData(FALSE);
	m_pathSliderBlue.SetPos(m_pathBlue);
	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageViewTag::OnPathGreenRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	pDoc->m_currentTag->m_ptrPath->m_color[1] = m_origColor[1];
	m_pathGreen = (UINT)(pDoc->m_currentTag->m_ptrPath->m_color[1] * 255.0);
	UpdateData(FALSE);
	m_pathSliderGreen.SetPos(m_pathGreen);
	pView->YoRender(YO_RENDER_FULL);
	return;	
	
}

void CStageViewTag::OnPathRedRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	pDoc->m_currentTag->m_ptrPath->m_color[0] = m_origColor[0];
	m_pathRed = (UINT)(pDoc->m_currentTag->m_ptrPath->m_color[0] * 255.0);
	UpdateData(FALSE);
	m_pathSliderRed.SetPos(m_pathRed);
	pView->YoRender(YO_RENDER_FULL);
	return;	
	
}

void CStageViewTag::OnTag90X() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	pDoc->m_currentTag->m_rotate[0]
		= (GLfloat)(((GLint)pDoc->m_currentTag->m_rotate[0] + 90) % 360);

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[0]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_ROTATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}


void CStageViewTag::OnTag90Y() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	pDoc->m_currentTag->m_rotate[1]
		= (GLfloat)(((GLint)pDoc->m_currentTag->m_rotate[1] + 90) % 360);

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_ROTATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageViewTag::OnTag90Z() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	pDoc->m_currentTag->m_rotate[2]
		= (GLfloat)(((GLint)pDoc->m_currentTag->m_rotate[2] + 90) % 360);

	sprintf(s, "%.1lf", pDoc->m_currentTag->m_rotate[2]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TAG_ROTATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageViewTag::OnSelchangeTagSnap() 
{
	if (m_tagSnap.GetCurSel() == 0)
	{
		m_tagSnapMode = YO_SNAP_COORDINATE;
	}
	else if (m_tagSnap.GetCurSel() == 1)
	{
		m_tagSnapMode = YO_SNAP_EDGE;
	}
	else if (m_tagSnap.GetCurSel() == 2)
	{
		m_tagSnapMode = YO_SNAP_EDGE_CENTER;
	}
	else if (m_tagSnap.GetCurSel() == 3)
	{
		m_tagSnapMode = YO_SNAP_PART;
	}
	else if (m_tagSnap.GetCurSel() == 4)
	{
		m_tagSnapMode = YO_SNAP_POLYGON;
	}
	else if (m_tagSnap.GetCurSel() == 5)
	{
		m_tagSnapMode = YO_SNAP_POLYGON_CENTER;
	}
	else if (m_tagSnap.GetCurSel() == 6)
	{
		m_tagSnapMode = YO_SNAP_VERTEX;
	}
	return;	
}

void CStageViewTag::OnOK() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	SetClassLong(((CStageView *)pView)->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);

	pDoc->m_snapToViewTag = m_tagSnapMode;
	((CMainFrame *)pMainFrame)->m_viewTagActive = FALSE;
	CDialog::OnOK();
	DestroyWindow();
}

void CStageViewTag::OnCancel() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	int i;

	SetClassLong(((CStageView *)pView)->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);
	
	pDoc->m_currentTag->m_ptrPath->m_visible = m_origVisible;
	for (i = 0; i < 3; i++)
	{
		pDoc->m_currentTag->m_translate[i] = m_origTranslate[i];
		pDoc->m_currentTag->m_rotate[i] = m_origRotate[i];
		pDoc->m_currentTag->m_ptrPath->m_color[i] = m_origColor[i];
	}

	pDoc->m_snapToViewTag = m_tagSnapMode;
	((CMainFrame *)pMainFrame)->m_viewTagActive = FALSE;
	CDialog::OnCancel();
	DestroyWindow();
	pView->YoRender(YO_RENDER_FULL);
}


void CStageViewTag::OnPathVisible() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	pDoc->m_currentTag->m_ptrPath->m_visible = m_visible;
	
	//pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);	
}
