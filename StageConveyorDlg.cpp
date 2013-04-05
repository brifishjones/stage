// StageConveyorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "stageViewPart.h"
#include "StageConveyorDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageConveyorDlg dialog


CStageConveyorDlg::CStageConveyorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageConveyorDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageConveyorDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageConveyorDlg)
	//}}AFX_DATA_INIT
}


void CStageConveyorDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageConveyorDlg)
	DDX_Control(pDX, IDC_CONVEYOR_SEGMENT_LIST, m_segmentList);
	DDX_Control(pDX, IDC_CONVEYOR_STOP_GATE_LIST, m_stopGateList);
	DDX_Control(pDX, IDC_CONVEYOR_TRANS_LIFT_LIST, m_transLiftList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageConveyorDlg, CDialog)
	//{{AFX_MSG_MAP(CStageConveyorDlg)
	ON_BN_CLICKED(IDC_CONVEYOR_STOP, OnConveyorStop)
	ON_BN_CLICKED(IDC_CONVEYOR_STOP_GATE_DOWN, OnConveyorStopGateDown)
	ON_LBN_SELCHANGE(IDC_CONVEYOR_STOP_GATE_LIST, OnSelchangeConveyorStopGateList)
	ON_BN_CLICKED(IDC_CONVEYOR_STOP_GATE_UP, OnConveyorStopGateUp)
	ON_EN_KILLFOCUS(IDC_CONVEYOR_ACCEL, OnKillfocusConveyorAccel)
	ON_BN_CLICKED(IDC_CONVEYOR_FORWARD, OnConveyorForward)
	ON_EN_KILLFOCUS(IDC_CONVEYOR_MAX_SPEED, OnKillfocusConveyorMaxSpeed)
	ON_BN_CLICKED(IDC_CONVEYOR_PAUSE, OnConveyorPause)
	ON_EN_KILLFOCUS(IDC_CONVEYOR_REL_SPEED, OnKillfocusConveyorRelSpeed)
	ON_BN_CLICKED(IDC_CONVEYOR_REVERSE, OnConveyorReverse)
	ON_LBN_SELCHANGE(IDC_CONVEYOR_SEGMENT_LIST, OnSelchangeConveyorSegmentList)
	ON_BN_CLICKED(IDC_CONVEYOR_TRANS_LIFT_DOWN, OnConveyorTransLiftDown)
	ON_LBN_SELCHANGE(IDC_CONVEYOR_TRANS_LIFT_LIST, OnSelchangeConveyorTransLiftList)
	ON_BN_CLICKED(IDC_CONVEYOR_TRANS_LIFT_UP, OnConveyorTransLiftUp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageConveyorDlg message handlers

BOOL CStageConveyorDlg::YoInitDialog() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	int dWidth;
	int dHeight;
	RECT rect;
	RECT mfRect;
	CREATESTRUCT cs;
	CString name;
	int i;
	char s[128];
	CWnd *pCBox;
	CStagePart *ptrPart;
	CStageConveyorSegment *ptrSegment;
	CStageConveyorStopGate *ptrStopGate;
	CStageConveyorTransverseLift *ptrTransverseLift;
	CStageConveyorPallet *ptrPallet;

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

	m_segmentList.ResetContent();
	m_stopGateList.ResetContent();
	m_transLiftList.ResetContent();

	if (((CStageConveyor *)pDoc->m_currentDevice)->m_ptrSegment != NULL)
	{
		sprintf(s, "%.2f", ((CStageConveyor *)pDoc->m_currentDevice)->m_ptrSegment->m_maxVelocity);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		sprintf(s, "%.2f", ((CStageConveyor *)pDoc->m_currentDevice)->m_ptrSegment->m_relSpeed);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_CONVEYOR_REL_SPEED);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		sprintf(s, "%.2f", ((CStageConveyor *)pDoc->m_currentDevice)->m_ptrSegment->m_acceleration);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_CONVEYOR_ACCEL);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		for (ptrSegment = ((CStageConveyor *)pDoc->m_currentDevice)->m_ptrSegment; ptrSegment != NULL; ptrSegment = ptrSegment->m_ptrNextSegment)
		{
			ptrSegment->m_origAcceleration = ptrSegment->m_acceleration;
			ptrSegment->m_origMaxVelocity = ptrSegment->m_maxVelocity;
			ptrSegment->m_origRelSpeed = ptrSegment->m_relSpeed;
			ptrSegment->m_origDirectionForward = ptrSegment->m_directionForward;
			m_segmentList.AddString(CString(ptrSegment->m_ptrPart->m_partName));

			for (ptrStopGate = ptrSegment->m_ptrStopGate; ptrStopGate != NULL; ptrStopGate = ptrStopGate->m_ptrNextStopGate)
			{
				ptrStopGate->m_origStop = ptrStopGate->m_stop;
				m_stopGateList.AddString(CString(ptrStopGate->m_ptrPart->m_partName));
			}

			for (ptrTransverseLift = ptrSegment->m_ptrTransverseLift; ptrTransverseLift != NULL;
				ptrTransverseLift = ptrTransverseLift->m_ptrNextTransverseLift)
			{
				ptrTransverseLift->m_origUp = ptrTransverseLift->m_up;
				if (ptrTransverseLift->m_ptrMirrorTransverseLift != NULL)
				{
					m_transLiftList.AddString(CString(ptrTransverseLift->m_ptrPart->m_partName));
				}
			}
			for (ptrPallet = ptrSegment->m_ptrPallet; ptrPallet != NULL;
				ptrPallet = ptrPallet->m_ptrNextPallet)
			{
				for (i = 0; i < 3; i++)
				{
					ptrPallet->m_origStartPosition[i] = ptrPallet->m_startPosition[i];
					ptrPallet->m_origPosition[i] = ptrPallet->m_position[i];
					ptrPallet->m_origEndPosition[i] = ptrPallet->m_endPosition[i];
				}
				ptrPallet->m_ptrOrigSegment = ptrPallet->m_ptrSegment;
				ptrPallet->m_origDistance = ptrPallet->m_distance;
				ptrPallet->m_origRelativePosition = ptrPallet->m_relativePosition;
			}
		}

		m_segmentList.SetCurSel(0);

		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(0);


		if (m_stopGateList.GetCount() > 0)
		{
			m_stopGateList.SetCurSel(0);

			m_stopGateList.GetText(m_stopGateList.GetCurSel(), name);
			ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
			ptrStopGate = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindStopGate(ptrPart);
			
			if (ptrStopGate->m_stop == TRUE)
			{
				pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_UP);
				((CButton *)pCBox)->SetCheck(1);
				pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_DOWN);
				((CButton *)pCBox)->SetCheck(0);
			}
			else
			{
				pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_UP);
				((CButton *)pCBox)->SetCheck(0);
				pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_DOWN);
				((CButton *)pCBox)->SetCheck(1);
			}

		}
		if (m_transLiftList.GetCount() > 0)
		{
			m_transLiftList.SetCurSel(0);

			m_transLiftList.GetText(m_transLiftList.GetCurSel(), name);
			ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
			ptrTransverseLift = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindTransverseLift(ptrPart);
			
			if (ptrTransverseLift->m_up == TRUE)
			{
				pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_UP);
				((CButton *)pCBox)->SetCheck(1);
				pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_DOWN);
				((CButton *)pCBox)->SetCheck(0);
			}
			else
			{
				pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_UP);
				((CButton *)pCBox)->SetCheck(0);
				pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_DOWN);
				((CButton *)pCBox)->SetCheck(1);
			}
		}

	}
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageConveyorDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}

void CStageConveyorDlg::OnConveyorStop() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[256];
	CWnd *pCBox;
	CString name;

	sprintf(s, "STOP");
	((CStageConveyor *)pDoc->m_currentDevice)->YoHandleSim(s);
	
	pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
	((CButton *)pCBox)->SetCheck(1);

	pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
	((CEdit *)pCBox)->SetReadOnly(FALSE);
	pCBox->UpdateWindow();
	pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_REL_SPEED);
	((CEdit *)pCBox)->SetReadOnly(FALSE);
	pCBox->UpdateWindow();
	pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_ACCEL);
	((CEdit *)pCBox)->SetReadOnly(FALSE);
	pCBox->UpdateWindow();

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	return;		
}

void CStageConveyorDlg::OnConveyorStopGateDown() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorStopGate *ptrStopGate;
	char s[256];
	CWnd *pCBox;
	CString name;

	m_stopGateList.GetText(m_stopGateList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrStopGate = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindStopGate(ptrPart);

	sprintf(s, "SG %s 0", (char *)LPCSTR(name));
	((CStageConveyor *)pDoc->m_currentDevice)->YoHandleSim(s);
	
	if (ptrStopGate->m_stop == TRUE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_UP);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_DOWN);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_UP);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_DOWN);
		((CButton *)pCBox)->SetCheck(1);
	}

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	return;

}

void CStageConveyorDlg::OnSelchangeConveyorStopGateList() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorStopGate *ptrStopGate;
	CWnd *pCBox;
	CString name;

	m_stopGateList.GetText(m_stopGateList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrStopGate = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindStopGate(ptrPart);

	if (ptrStopGate->m_stop == TRUE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_UP);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_DOWN);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_UP);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_DOWN);
		((CButton *)pCBox)->SetCheck(1);
	}

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	return;	
}

void CStageConveyorDlg::OnConveyorStopGateUp() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorStopGate *ptrStopGate;
	char s[256];
	CWnd *pCBox;
	CString name;

	m_stopGateList.GetText(m_stopGateList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrStopGate = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindStopGate(ptrPart);

	sprintf(s, "SG %s 1", (char *)LPCSTR(name));
	((CStageConveyor *)pDoc->m_currentDevice)->YoHandleSim(s);
	
	if (ptrStopGate->m_stop == TRUE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_UP);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_DOWN);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_UP);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_STOP_GATE_DOWN);
		((CButton *)pCBox)->SetCheck(1);
	}

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	return;
	
}

void CStageConveyorDlg::OnKillfocusConveyorAccel() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorSegment *ptrSegment;
	CWnd *pCBox;
	CString name;
	char s[64];
	double a;

	m_segmentList.GetText(m_segmentList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrSegment = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindSegment(ptrPart);

	pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_ACCEL);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &a);
	a = YO_MAX(a, 10.0);
	a = YO_MIN(a, 999999.0);

	((CStageConveyor *)pDoc->m_currentDevice)->m_ptrSegment->m_acceleration = a;

	sprintf(s, "%.2f", a);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	//if (pDoc->m_isMovement)
	//{
	//	pDoc->YoMove();
	//}

	return;		
}

void CStageConveyorDlg::OnConveyorForward() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorSegment *ptrSegment;
	char s[256];
	CWnd *pCBox;
	CString name;

	m_segmentList.GetText(m_segmentList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrSegment = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindSegment(ptrPart);

	sprintf(s, "GO %s %lf",
		(char *)LPCSTR(name), ptrSegment->m_maxVelocity * ptrSegment->m_relSpeed / 100.0f);
	((CStageConveyor *)pDoc->m_currentDevice)->YoHandleSim(s);
	
	if (s[0] == 'X' && ptrSegment->m_moving == FALSE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(1);
	}
	else if (s[0] == 'X' && ptrSegment->m_moving == TRUE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(0);
	}

	if (((CStageConveyor *)pDoc->m_currentDevice)->m_moving)
	{
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_REL_SPEED);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_ACCEL);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->UpdateWindow();
	}
	else
	{
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_REL_SPEED);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_ACCEL);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
	}

	if (pDoc->m_isMovement)
	{
		pDoc->m_resumeMove = TRUE;
		//pDoc->YoMove();
	}

	return;
}

void CStageConveyorDlg::OnKillfocusConveyorMaxSpeed() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorSegment *ptrSegment;
	CWnd *pCBox;
	CString name;
	char s[64];
	double v;

	m_segmentList.GetText(m_segmentList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrSegment = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindSegment(ptrPart);

	pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &v);
	v = YO_MAX(v, 0.01);
	v = YO_MIN(v, 10000.0);
	((CStageConveyor *)pDoc->m_currentDevice)->m_ptrSegment->m_maxVelocity = v;

	sprintf(s, "%.2f", v);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}


	return;
}

void CStageConveyorDlg::OnConveyorPause() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorSegment *ptrSegment;
	char s[256];
	CWnd *pCBox;
	CString name;

	m_segmentList.GetText(m_segmentList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrSegment = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindSegment(ptrPart);

	sprintf(s, "STOP %s", (char *)LPCSTR(name));
	((CStageConveyor *)pDoc->m_currentDevice)->YoHandleSim(s);
	
	pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
	((CButton *)pCBox)->SetCheck(1);

	// conveyor doesn't decrement m_moving until conveyor deaccelerates
	if (((CStageConveyor *)pDoc->m_currentDevice)->m_moving <= 1)
	{
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_REL_SPEED);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_ACCEL);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
	}

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	return;	
}

void CStageConveyorDlg::OnKillfocusConveyorRelSpeed() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorSegment *ptrSegment;
	CWnd *pCBox;
	CString name;
	char s[64];

	m_segmentList.GetText(m_segmentList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrSegment = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindSegment(ptrPart);

	pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REL_SPEED);
	pCBox->GetWindowText(s, 64);
	sscanf(s, "%lf", &ptrSegment->m_relSpeed);
	ptrSegment->m_relSpeed = YO_MAX(ptrSegment->m_relSpeed, 0.1);
	ptrSegment->m_relSpeed = YO_MIN(ptrSegment->m_relSpeed, 100.0);

	sprintf(s, "%.2f", ptrSegment->m_relSpeed);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	return;	
}

void CStageConveyorDlg::OnConveyorReverse() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorSegment *ptrSegment;
	char s[256];
	CWnd *pCBox;
	CString name;

	m_segmentList.GetText(m_segmentList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrSegment = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindSegment(ptrPart);

	sprintf(s, "GO %s %lf",
		(char *)LPCSTR(name), -ptrSegment->m_maxVelocity * ptrSegment->m_relSpeed / 100.0f);
	((CStageConveyor *)pDoc->m_currentDevice)->YoHandleSim(s);
	
	if (s[0] == 'X' && ptrSegment->m_moving == FALSE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(1);
	}
	else if (s[0] == 'X' && ptrSegment->m_moving == TRUE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(0);
	}

	if (((CStageConveyor *)pDoc->m_currentDevice)->m_moving)
	{
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_REL_SPEED);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_ACCEL);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->UpdateWindow();
	}
	else
	{
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_REL_SPEED);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_ACCEL);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
	}

	if (pDoc->m_isMovement)
	{
		pDoc->m_resumeMove = TRUE;
		//pDoc->YoMove();
	}

	return;
}

void CStageConveyorDlg::OnSelchangeConveyorSegmentList() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorSegment *ptrSegment;
	char s[64];
	CWnd *pCBox;
	CString name;

	m_segmentList.GetText(m_segmentList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrSegment = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindSegment(ptrPart);

	if (ptrSegment->m_moving == TRUE && ptrSegment->m_directionForward == TRUE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(0);
	}
	else if (ptrSegment->m_moving == TRUE && ptrSegment->m_directionForward == FALSE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(1);

	}

	sprintf(s, "%.2f", ptrSegment->m_maxVelocity);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.2f", ptrSegment->m_relSpeed);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_CONVEYOR_REL_SPEED);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	sprintf(s, "%.2f", ptrSegment->m_acceleration);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_CONVEYOR_ACCEL);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (((CStageConveyor *)pDoc->m_currentDevice)->m_moving)
	{
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_REL_SPEED);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_ACCEL);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->UpdateWindow();
	}
	else
	{
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_REL_SPEED);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox *)GetDlgItem(IDC_CONVEYOR_ACCEL);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
	}

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	return;	
}

void CStageConveyorDlg::OnConveyorTransLiftDown() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorTransverseLift *ptrTransLift;
	char s[256];
	CWnd *pCBox;
	CString name;

	m_transLiftList.GetText(m_transLiftList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrTransLift = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindTransverseLift(ptrPart);

	sprintf(s, "TL %s 0", (char *)LPCSTR(name));
	((CStageConveyor *)pDoc->m_currentDevice)->YoHandleSim(s);
	
	if (ptrTransLift->m_up == TRUE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_UP);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_DOWN);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_UP);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_DOWN);
		((CButton *)pCBox)->SetCheck(1);
	}

	//pView->YoRender(YO_RENDER_LIGHT);
	//pView->YoRender(YO_RENDER_FULL);

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	return;
	
}

void CStageConveyorDlg::OnSelchangeConveyorTransLiftList() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorTransverseLift *ptrTransLift;
	CWnd *pCBox;
	CString name;

	m_transLiftList.GetText(m_transLiftList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrTransLift = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindTransverseLift(ptrPart);

	if (ptrTransLift->m_up == TRUE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_UP);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_DOWN);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_UP);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_DOWN);
		((CButton *)pCBox)->SetCheck(1);
	}

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	return;		
}

void CStageConveyorDlg::OnConveyorTransLiftUp() 
{
	// TODO: Add your control notification handler code here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrPart;
	CStageConveyorTransverseLift *ptrTransLift;
	char s[256];
	CWnd *pCBox;
	CString name;

	m_transLiftList.GetText(m_transLiftList.GetCurSel(), name);
	ptrPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	ptrTransLift = ((CStageConveyor *)pDoc->m_currentDevice)->YoFindTransverseLift(ptrPart);

	sprintf(s, "TL %s 1", (char *)LPCSTR(name));
	((CStageConveyor *)pDoc->m_currentDevice)->YoHandleSim(s);
	
	if (ptrTransLift->m_up == TRUE)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_UP);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_DOWN);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_UP);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)GetDlgItem(IDC_CONVEYOR_TRANS_LIFT_DOWN);
		((CButton *)pCBox)->SetCheck(1);
	}

	if (pDoc->m_isMovement)
	{
		pDoc->YoMove();
	}

	return;
		
}

void CStageConveyorDlg::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}
