// StageTrackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageTrackDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageTrackDlg dialog


CStageTrackDlg::CStageTrackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageTrackDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageTrackDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageTrackDlg)
	m_trackVisible = FALSE;
	m_trackBlue = 0;
	m_trackGreen = 0;
	m_trackRed = 0;
	//}}AFX_DATA_INIT
}


void CStageTrackDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageTrackDlg)
	DDX_Control(pDX, IDC_SNAP_TO_LIST, m_trackSnap);
	DDX_Control(pDX, IDC_TRACK_SLIDER_RED, m_trackSliderRed);
	DDX_Control(pDX, IDC_TRACK_SLIDER_GREEN, m_trackSliderGreen);
	DDX_Control(pDX, IDC_TRACK_SLIDER_BLUE, m_trackSliderBlue);
	DDX_Check(pDX, IDC_TRACK_VISIBLE, m_trackVisible);
	DDX_Text(pDX, IDC_TRACK_BLUE, m_trackBlue);
	DDV_MinMaxUInt(pDX, m_trackBlue, 0, 255);
	DDX_Text(pDX, IDC_TRACK_GREEN, m_trackGreen);
	DDV_MinMaxUInt(pDX, m_trackGreen, 0, 255);
	DDX_Text(pDX, IDC_TRACK_RED, m_trackRed);
	DDV_MinMaxUInt(pDX, m_trackRed, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageTrackDlg, CDialog)
	//{{AFX_MSG_MAP(CStageTrackDlg)
	ON_EN_KILLFOCUS(IDC_TRACK_TRANSLATE_X, OnKillfocusTrackTranslateX)
	ON_EN_KILLFOCUS(IDC_TRACK_TRANSLATE_Y, OnKillfocusTrackTranslateY)
	ON_EN_KILLFOCUS(IDC_TRACK_TRANSLATE_Z, OnKillfocusTrackTranslateZ)
	ON_EN_KILLFOCUS(IDC_TRACK_ROTATE_X, OnKillfocusTrackRotateX)
	ON_EN_KILLFOCUS(IDC_TRACK_ROTATE_Y, OnKillfocusTrackRotateY)
	ON_EN_KILLFOCUS(IDC_TRACK_ROTATE_Z, OnKillfocusTrackRotateZ)
	ON_BN_CLICKED(IDC_TRACK_RED_RESTORE, OnTrackRedRestore)
	ON_BN_CLICKED(IDC_TRACK_GREEN_RESTORE, OnTrackGreenRestore)
	ON_BN_CLICKED(IDC_TRACK_BLUE_RESTORE, OnTrackBlueRestore)
	ON_CBN_SELCHANGE(IDC_SNAP_TO_LIST, OnSelchangeSnapToList)
	ON_BN_CLICKED(IDC_TRACK_SWITCH_CLOSED, OnTrackSwitchClosed)
	ON_BN_CLICKED(IDC_TRACK_SWITCH_OPENED, OnTrackSwitchOpened)
	ON_BN_CLICKED(IDC_TRACK_DECREASE_X, OnTrackDecreaseX)
	ON_BN_CLICKED(IDC_TRACK_DECREASE_Y, OnTrackDecreaseY)
	ON_BN_CLICKED(IDC_TRACK_DECREASE_Z, OnTrackDecreaseZ)
	ON_BN_CLICKED(IDC_TRACK_INCREASE_X, OnTrackIncreaseX)
	ON_BN_CLICKED(IDC_TRACK_INCREASE_X90, OnTrackIncreaseX90)
	ON_BN_CLICKED(IDC_TRACK_INCREASE_Y, OnTrackIncreaseY)
	ON_BN_CLICKED(IDC_TRACK_INCREASE_Y90, OnTrackIncreaseY90)
	ON_BN_CLICKED(IDC_TRACK_INCREASE_Z, OnTrackIncreaseZ)
	ON_BN_CLICKED(IDC_TRACK_INCREASE_Z90, OnTrackIncreaseZ90)
	ON_BN_CLICKED(IDC_TRACK_SNAP_TO, OnTrackSnapTo)
	ON_EN_KILLFOCUS(IDC_TRACK_BLUE, OnKillfocusTrackBlue)
	ON_EN_KILLFOCUS(IDC_TRACK_RED, OnKillfocusTrackRed)
	ON_EN_KILLFOCUS(IDC_TRACK_GREEN, OnKillfocusTrackGreen)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageTrackDlg message handlers

BOOL CStageTrackDlg::YoInitDialog() 
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

	m_origVisible = pDoc->m_currentDevice->m_visible;
	for (i = 0; i < 3; i++)
	{
		m_origTranslate[i] = pDoc->m_currentDevice->m_ptrPart->m_translate[i];
		m_origRotate[i] = pDoc->m_currentDevice->m_ptrPart->m_rotate[i];
		m_origColor[i] = pDoc->m_currentDevice->m_ptrPart->m_wireframe[i];
	}

	// init dialog

	sprintf(s, "%s  -  %s", pDoc->m_currentDevice->m_name,
		pDoc->m_currentPart->m_partName);
	SetWindowText((LPCTSTR)s);

	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_PARENT);
	pCBox->SetWindowText(pDoc->m_currentDevice->m_parent);
	pCBox->UpdateWindow();

	m_trackVisible = pDoc->m_currentDevice->m_visible;

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_translate[0] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_TRANSLATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_translate[1] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_TRANSLATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_translate[2] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_TRANSLATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();


	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_rotate[0]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_ROTATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_rotate[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_ROTATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_rotate[2]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_ROTATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	m_trackRed = (UINT)(pDoc->m_currentDevice->m_ptrPart->m_wireframe[0] * 255.0);
	m_trackGreen = (UINT)(pDoc->m_currentDevice->m_ptrPart->m_wireframe[1] * 255.0);
	m_trackBlue = (UINT)(pDoc->m_currentDevice->m_ptrPart->m_wireframe[2] * 255.0);

	m_trackSnap.ResetContent();
	m_trackSnap.AddString("Coordinate");
	m_trackSnap.AddString("Edge");
	m_trackSnap.AddString("Edge Center");
	m_trackSnap.AddString("Part");
	m_trackSnap.AddString("Polygon");
	m_trackSnap.AddString("Polygon Center");
	m_trackSnap.AddString("Vertex");
	m_trackSnap.SetCurSel(pDoc->m_snapToViewPart);
	m_snapToMode = pDoc->m_snapToViewPart;

	m_snapTo = FALSE;

	m_trackSliderRed.SetRange(0, 255);
	m_trackSliderRed.SetPos(m_trackRed);
	m_trackSliderGreen.SetRange(0, 255);
	m_trackSliderGreen.SetPos(m_trackGreen);
	m_trackSliderBlue.SetRange(0, 255);
	m_trackSliderBlue.SetPos(m_trackBlue);

	if (m_trackVisible)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_VISIBLE);
		((CButton *)pCBox)->SetCheck(1);
	}

	if (pDoc->m_currentPart->m_ptrTrackSeg->m_type == YO_TRACK_LINE)
	{
		sprintf(s, "line");
	}
	if (pDoc->m_currentPart->m_ptrTrackSeg->m_type == YO_TRACK_CIRCLE)
	{
		sprintf(s, "circle");
	}
	if (pDoc->m_currentPart->m_ptrTrackSeg->m_type == YO_TRACK_SWITCH)
	{
		sprintf(s, "switch");
	}
	if (pDoc->m_currentPart->m_ptrTrackSeg->m_type == YO_TRACK_CROSS)
	{
		sprintf(s, "cross");
	}
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_TYPE);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%s", pDoc->m_currentPart->m_partName);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_STATIC_TRACK);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_ptrTrackSeg->m_from[0]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_START_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_ptrTrackSeg->m_from[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_START_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_ptrTrackSeg->m_to[0]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_END_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentPart->m_ptrTrackSeg->m_to[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_END_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (pDoc->m_currentPart->m_ptrTrackSeg->m_type == YO_TRACK_SWITCH)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_STATIC_SWITCH);
		pCBox->ShowWindow(SW_SHOW);

		sprintf(s, "%.1lf", pDoc->m_currentPart->m_ptrTrackSeg->m_switch[0]);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_X);
		pCBox->ShowWindow(SW_SHOW);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		sprintf(s, "%.1lf", pDoc->m_currentPart->m_ptrTrackSeg->m_switch[1]);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_Y);
		pCBox->ShowWindow(SW_SHOW);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		if (pDoc->m_currentPart->m_ptrTrackSeg->m_switchStatus == YO_SWITCH_OPENED)
		{
			pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_OPENED);
			pCBox->ShowWindow(SW_SHOW);
			((CButton *)pCBox)->SetCheck(1);
			pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_CLOSED);
			pCBox->ShowWindow(SW_SHOW);
			((CButton *)pCBox)->SetCheck(0);
		}
		else
		{
			pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_OPENED);
			pCBox->ShowWindow(SW_SHOW);
			((CButton *)pCBox)->SetCheck(0);
			pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_CLOSED);
			pCBox->ShowWindow(SW_SHOW);
			((CButton *)pCBox)->SetCheck(1);
		}
	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_STATIC_SWITCH);
		pCBox->ShowWindow(SW_HIDE);

		pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_X);
		pCBox->ShowWindow(SW_HIDE);

		pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_Y);
		pCBox->ShowWindow(SW_HIDE);

		pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_OPENED);
		pCBox->ShowWindow(SW_HIDE);

		pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_CLOSED);
		pCBox->ShowWindow(SW_HIDE);
	}

	if (pDoc->m_currentPart->m_ptrTrackSeg->m_type == YO_TRACK_CIRCLE)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_STATIC_RADIUS);
		pCBox->ShowWindow(SW_SHOW);

		sprintf(s, "%.1lf", pDoc->m_currentPart->m_ptrTrackSeg->m_radius);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_RADIUS);
		pCBox->ShowWindow(SW_SHOW);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		pCBox = (CComboBox*)this->GetDlgItem(IDC_STATIC_HEADING);
		pCBox->ShowWindow(SW_SHOW);

		sprintf(s, "%.1lf", pDoc->m_currentPart->m_ptrTrackSeg->m_heading);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_HEADING);
		pCBox->ShowWindow(SW_SHOW);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_STATIC_RADIUS);
		pCBox->ShowWindow(SW_HIDE);

		pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_RADIUS);
		pCBox->ShowWindow(SW_HIDE);

		pCBox = (CComboBox*)this->GetDlgItem(IDC_STATIC_HEADING);
		pCBox->ShowWindow(SW_HIDE);

		pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_HEADING);
		pCBox->ShowWindow(SW_HIDE);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStageTrackDlg::YoUpdateTranslateRotate()
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[128];

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_translate[0] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_TRANSLATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_translate[1] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_TRANSLATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_translate[2] * pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_TRANSLATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_rotate[0]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_ROTATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_rotate[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_ROTATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_rotate[2]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_ROTATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	return;
}

void CStageTrackDlg::YoUpdateColor(void)
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	int i;

	for (ptrPart = pDoc->m_currentDevice->m_ptrPart->m_down; ptrPart != NULL; ptrPart = ptrPart->m_right)
	{
		for (i = 0; i < 4; i++)
		{
			ptrPart->m_wireframe[i] = pDoc->m_currentDevice->m_ptrPart->m_wireframe[i];
		}
	}

	return;
}

void CStageTrackDlg::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
	delete this;
}

void CStageTrackDlg::OnKillfocusTrackTranslateX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_TRANSLATE_X);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);
	pDoc->m_currentDevice->m_ptrPart->m_translate[0] = t / pDoc->m_unitScaleFactor;
	
	pView->YoRender(YO_RENDER_FULL);
	return;			
}

void CStageTrackDlg::OnKillfocusTrackTranslateY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_TRANSLATE_Y);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);
	pDoc->m_currentDevice->m_ptrPart->m_translate[1] = t / pDoc->m_unitScaleFactor;
	
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnKillfocusTrackTranslateZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];
	GLdouble t;

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_TRANSLATE_Z);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &t);
	pDoc->m_currentDevice->m_ptrPart->m_translate[2] = t / pDoc->m_unitScaleFactor;
	
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnKillfocusTrackRotateX() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_ROTATE_X);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &pDoc->m_currentDevice->m_ptrPart->m_rotate[0]);

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnKillfocusTrackRotateY() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_ROTATE_Y);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &pDoc->m_currentDevice->m_ptrPart->m_rotate[1]);

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnKillfocusTrackRotateZ() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here

	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_ROTATE_Z);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &pDoc->m_currentDevice->m_ptrPart->m_rotate[2]);

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnTrackRedRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	pDoc->m_currentDevice->m_ptrPart->m_wireframe[0] = m_origColor[0];
	m_trackRed = (UINT)(pDoc->m_currentDevice->m_ptrPart->m_wireframe[0] * 255.0);
	UpdateData(FALSE);
	m_trackSliderRed.SetPos(m_trackRed);
	YoUpdateColor();
	pView->YoRender(YO_RENDER_FULL);
	return;	
	
}

void CStageTrackDlg::OnTrackGreenRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	pDoc->m_currentDevice->m_ptrPart->m_wireframe[1] = m_origColor[1];
	m_trackGreen = (UINT)(pDoc->m_currentDevice->m_ptrPart->m_wireframe[1] * 255.0);
	UpdateData(FALSE);
	m_trackSliderGreen.SetPos(m_trackGreen);
	YoUpdateColor();
	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnTrackBlueRestore() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	pDoc->m_currentDevice->m_ptrPart->m_wireframe[2] = m_origColor[2];
	m_trackBlue = (UINT)(pDoc->m_currentDevice->m_ptrPart->m_wireframe[2] * 255.0);
	UpdateData(FALSE);
	m_trackSliderBlue.SetPos(m_trackBlue);
	YoUpdateColor();
	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageTrackDlg::OnSelchangeSnapToList() 
{
	if (m_trackSnap.GetCurSel() == 0)
	{
		m_snapToMode = YO_SNAP_COORDINATE;
	}
	else if (m_trackSnap.GetCurSel() == 1)
	{
		m_snapToMode = YO_SNAP_EDGE;
	}
	else if (m_trackSnap.GetCurSel() == 2)
	{
		m_snapToMode = YO_SNAP_EDGE_CENTER;
	}
	else if (m_trackSnap.GetCurSel() == 3)
	{
		m_snapToMode = YO_SNAP_PART;
	}
	else if (m_trackSnap.GetCurSel() == 4)
	{
		m_snapToMode = YO_SNAP_POLYGON;
	}
	else if (m_trackSnap.GetCurSel() == 5)
	{
		m_snapToMode = YO_SNAP_POLYGON_CENTER;
	}
	else if (m_trackSnap.GetCurSel() == 6)
	{
		m_snapToMode = YO_SNAP_VERTEX;
	}
	return;		
}

void CStageTrackDlg::OnTrackSwitchClosed() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;

	pDoc->m_currentPart->m_ptrTrackSeg->m_switchStatus = YO_SWITCH_CLOSED;
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_OPENED);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_CLOSED);
	((CButton *)pCBox)->SetCheck(1);

	return;
}

void CStageTrackDlg::OnTrackSwitchOpened() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;

	pDoc->m_currentPart->m_ptrTrackSeg->m_switchStatus = YO_SWITCH_OPENED;
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_OPENED);
	((CButton *)pCBox)->SetCheck(1);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_SWITCH_CLOSED);
	((CButton *)pCBox)->SetCheck(0);

	return;	
}

void CStageTrackDlg::OnCancel() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	int i;

	SetClassLong(((CStageView *)pView)->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);
	
	pDoc->m_currentDevice->m_visible = m_origVisible;
	for (i = 0; i < 3; i++)
	{
		pDoc->m_currentDevice->m_ptrPart->m_translate[i] = m_origTranslate[i];
		pDoc->m_currentDevice->m_ptrPart->m_rotate[i] = m_origRotate[i];
		pDoc->m_currentDevice->m_ptrPart->m_wireframe[i] = m_origColor[i];
	}
	YoUpdateColor();

	pDoc->m_snapToViewPart = m_snapToMode;
	((CMainFrame *)pMainFrame)->m_trackDlgActive = FALSE;
	CDialog::OnCancel();
	DestroyWindow();
	pView->YoRender(YO_RENDER_FULL);

	return;
}

void CStageTrackDlg::OnOK() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	SetClassLong(((CStageView *)pView)->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);

	pDoc->m_snapToViewPart = m_snapToMode;
	((CMainFrame *)pMainFrame)->m_trackDlgActive = FALSE;
	CDialog::OnOK();
	DestroyWindow();
	
	return;
}

void CStageTrackDlg::OnTrackDecreaseX() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[32];
	CWnd *pCBox;

	pDoc->m_currentDevice->m_ptrPart->m_translate[0] -= 1000.0;
	sprintf(s, "%.3lf", pDoc->m_currentDevice->m_ptrPart->m_translate[0]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_TRANSLATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnTrackDecreaseY() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[32];
	CWnd *pCBox;

	pDoc->m_currentDevice->m_ptrPart->m_translate[1] -= 1000.0;
	sprintf(s, "%.3lf", pDoc->m_currentDevice->m_ptrPart->m_translate[1]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_TRANSLATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnTrackDecreaseZ() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[32];
	CWnd *pCBox;

	pDoc->m_currentDevice->m_ptrPart->m_translate[2] -= 1000.0;
	sprintf(s, "%.3lf", pDoc->m_currentDevice->m_ptrPart->m_translate[2]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_TRANSLATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnTrackIncreaseX() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[32];
	CWnd *pCBox;

	pDoc->m_currentDevice->m_ptrPart->m_translate[0] += 1000.0;
	sprintf(s, "%.3lf", pDoc->m_currentDevice->m_ptrPart->m_translate[0]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_TRANSLATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;	
}

void CStageTrackDlg::OnTrackIncreaseX90() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	pDoc->m_currentDevice->m_ptrPart->m_rotate[0]
		= (GLdouble)(((GLint)pDoc->m_currentTag->m_rotate[0] + 90) % 360);

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_rotate[0]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_ROTATE_X);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnTrackIncreaseY() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[32];
	CWnd *pCBox;

	pDoc->m_currentDevice->m_ptrPart->m_translate[1] += 1000.0;
	sprintf(s, "%.3lf", pDoc->m_currentDevice->m_ptrPart->m_translate[1]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_TRANSLATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnTrackIncreaseY90() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	pDoc->m_currentDevice->m_ptrPart->m_rotate[1]
		= (GLdouble)(((GLint)pDoc->m_currentTag->m_rotate[1] + 90) % 360);

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_rotate[1]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_ROTATE_Y);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnTrackIncreaseZ() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[32];
	CWnd *pCBox;

	pDoc->m_currentDevice->m_ptrPart->m_translate[2] += 1000.0;
	sprintf(s, "%.3lf", pDoc->m_currentDevice->m_ptrPart->m_translate[2]
		* pDoc->m_unitScaleFactor);
	pCBox = (CComboBox*)GetDlgItem(IDC_TRACK_TRANSLATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnTrackIncreaseZ90() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CWnd *pCBox;
	char s[64];

	// TODO: Add your control notification handler code here
	pDoc->m_currentDevice->m_ptrPart->m_rotate[2]
		= (GLdouble)(((GLint)pDoc->m_currentTag->m_rotate[2] + 90) % 360);

	sprintf(s, "%.1lf", pDoc->m_currentDevice->m_ptrPart->m_rotate[2]);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_TRACK_ROTATE_Z);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pView->YoRender(YO_RENDER_FULL);
	return;		
}

void CStageTrackDlg::OnTrackSnapTo() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();

	// TODO: Add your control notification handler code here
	m_snapTo = TRUE;
	SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)pMainFrame->m_hCursorSelect);
	return;	
}

void CStageTrackDlg::OnKillfocusTrackBlue() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_trackSliderBlue.SetPos(m_trackBlue);
	pDoc->m_currentDevice->m_ptrPart->m_wireframe[2] = (GLfloat)m_trackBlue / 255.0f;
	YoUpdateColor();
	pView->YoRender(YO_RENDER_FULL);
	return;	
	
}

void CStageTrackDlg::OnKillfocusTrackRed() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_trackSliderRed.SetPos(m_trackRed);
	pDoc->m_currentDevice->m_ptrPart->m_wireframe[0] = (GLfloat)m_trackRed / 255.0f;
	YoUpdateColor();
	pView->YoRender(YO_RENDER_FULL);
	return;	
	
}

void CStageTrackDlg::OnKillfocusTrackGreen() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	UpdateData(TRUE);
	m_trackSliderGreen.SetPos(m_trackGreen);
	pDoc->m_currentDevice->m_ptrPart->m_wireframe[1] = (GLfloat)m_trackGreen / 255.0f;
	YoUpdateColor();
	pView->YoRender(YO_RENDER_FULL);
	return;	
	
}

void CStageTrackDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();

	// TODO: Add your message handler code here and/or call default
	if ((CSliderCtrl *)pScrollBar == &m_trackSliderRed)
	{
		m_trackRed = m_trackSliderRed.GetPos();
		pDoc->m_currentDevice->m_ptrPart->m_wireframe[0] = (GLfloat)m_trackRed / 255.0f;
	}
	else if ((CSliderCtrl *)pScrollBar == &m_trackSliderGreen)
	{
		m_trackGreen = m_trackSliderGreen.GetPos();
		pDoc->m_currentDevice->m_ptrPart->m_wireframe[1] = (GLfloat)m_trackGreen / 255.0f;
	}
	else if ((CSliderCtrl *)pScrollBar == &m_trackSliderBlue)
	{
		m_trackBlue = m_trackSliderBlue.GetPos();
		pDoc->m_currentDevice->m_ptrPart->m_wireframe[2] = (GLfloat)m_trackBlue / 255.0f;
	}

	UpdateData(FALSE);
	YoUpdateColor();
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	if (nSBCode == SB_ENDSCROLL)
	{
		pView->YoRender(YO_RENDER_FULL);
	}
	else
	{
		pView->YoRender(YO_RENDER_QUICK);
	}
	return;
}
