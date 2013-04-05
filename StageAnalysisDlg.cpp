// StageAnalysisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageAnalysisDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageAnalysisDlg dialog


CStageAnalysisDlg::CStageAnalysisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageAnalysisDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageAnalysisDlg::IDD, pParent);
	
	//{{AFX_DATA_INIT(CStageAnalysisDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}



void CStageAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageAnalysisDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageAnalysisDlg, CDialog)
	//{{AFX_MSG_MAP(CStageAnalysisDlg)
	ON_BN_CLICKED(IDC_COORDINATE, OnCoordinate)
	ON_BN_CLICKED(IDC_DEVICE, OnDevice)
	ON_BN_CLICKED(IDC_EDGE, OnEdge)
	ON_BN_CLICKED(IDC_EDGE_CENTER, OnEdgeCenter)
	ON_BN_CLICKED(IDC_PART, OnPart)
	ON_BN_CLICKED(IDC_POLYGON, OnPolygon)
	ON_BN_CLICKED(IDC_POLYGON_CENTER, OnPolygonCenter)
	ON_BN_CLICKED(IDC_VERTEX, OnVertex)
	ON_BN_CLICKED(IDC_RESET_X, OnResetX)
	ON_BN_CLICKED(IDC_RESET_Y, OnResetY)
	ON_BN_CLICKED(IDC_RESET_Z, OnResetZ)
	ON_EN_KILLFOCUS(IDC_OFFSET_X, OnKillfocusOffsetX)
	ON_EN_KILLFOCUS(IDC_OFFSET_Y, OnKillfocusOffsetY)
	ON_EN_KILLFOCUS(IDC_OFFSET_Z, OnKillfocusOffsetZ)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageAnalysisDlg message handlers

void CStageAnalysisDlg::PostNcDestroy() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
	delete this;
}


BOOL CStageAnalysisDlg::YoInitDialog()
{
	CWnd* pCBox;
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	int dWidth;
	RECT rect;
	RECT mfRect;
	CREATESTRUCT cs;

	m_init = TRUE;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bmSquareGray.LoadBitmap(IDB_SQUARE_GRAY);
	m_bmSquarePurple.LoadBitmap(IDB_SQUARE_PURPLE);

	m_selected = 0;
	m_ptrDevice[0] = NULL;
	m_ptrDevice[1] = NULL;
	m_ptrTag[0] = NULL;
	m_ptrTag[1] = NULL;
	m_mode = YO_ANALYSIS_MODE_VERTEX;

	m_idc[0] = IDC_VERTEX_FIRST;
	m_idc[1] = IDC_VERTEX_SECOND;
	//m_token = 1;

	pCBox = GetDlgItem(IDC_OFFSET_X);
	pCBox->SetWindowText("");
	pCBox->UpdateWindow();
	pCBox->EnableWindow(FALSE);

	pCBox = GetDlgItem(IDC_OFFSET_Y);
	pCBox->SetWindowText("");
	pCBox->UpdateWindow();
	pCBox->EnableWindow(FALSE);

	pCBox = GetDlgItem(IDC_OFFSET_Z);
	pCBox->SetWindowText("");
	pCBox->UpdateWindow();
	pCBox->EnableWindow(FALSE);

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
	
	return TRUE;
}


void CStageAnalysisDlg::OnOK() 
{
	// TODO: Add extra validation here
	CFrameWnd *pMainFrame = GetTopLevelFrame();
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	
	SetClassLong(((CStageView *)pView)->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);
	((CMainFrame *)pMainFrame)->m_analysisActive = FALSE;

	pDoc->YoMessage("");
	CDialog::OnOK();
	DestroyWindow();
}

void CStageAnalysisDlg::OnCoordinate() 
{
	// TODO: Add your control notification handler code here

	m_mode = YO_ANALYSIS_MODE_COORDINATE;
	
}

void CStageAnalysisDlg::OnDevice() 
{
	// TODO: Add your control notification handler code here

	m_mode = YO_ANALYSIS_MODE_DEVICE;

}

void CStageAnalysisDlg::OnEdge() 
{
	// TODO: Add your control notification handler code here
	//if (m_selected == 2)
	//{
	//	YoResetDistance();
	//}
	
	/***
	if (m_selected == 0)
	{
		m_idc[0] = IDC_EDGE_FIRST;
		m_idc[1] = IDC_EDGE_SECOND;
		m_token = 1;
	}
	else if (m_selected == 1)
	{
		m_idc[1] = IDC_EDGE_SECOND;
		m_token = 2;
	}
	else if (m_selected == 2)
	{
		m_idc[0] = IDC_EDGE_FIRST;
		m_token = 1;
	}
	***/

	m_mode = YO_ANALYSIS_MODE_EDGE;
	
}

void CStageAnalysisDlg::OnEdgeCenter() 
{
	// TODO: Add your control notification handler code here
	
	m_mode = YO_ANALYSIS_MODE_EDGE_CENTER;

}

void CStageAnalysisDlg::OnPart() 
{
	// TODO: Add your control notification handler code here

	m_mode = YO_ANALYSIS_MODE_PART;

}

void CStageAnalysisDlg::OnPolygon() 
{
	// TODO: Add your control notification handler code here
	
	m_mode = YO_ANALYSIS_MODE_POLYGON;

}

void CStageAnalysisDlg::OnPolygonCenter() 
{
	// TODO: Add your control notification handler code here
	
	m_mode = YO_ANALYSIS_MODE_POLYGON_CENTER;
	
}

void CStageAnalysisDlg::OnVertex() 
{
	// TODO: Add your control notification handler code here

	m_mode = YO_ANALYSIS_MODE_VERTEX;
	
}


void CStageAnalysisDlg::YoUpdateMode(int selected)
{
	if (selected == 1)
	{
		if (m_mode == YO_ANALYSIS_MODE_COORDINATE)
		{
			m_idc[0] = IDC_COORDINATE_FIRST;
		}
		else if (m_mode == YO_ANALYSIS_MODE_DEVICE)
		{
			m_idc[0] = IDC_DEVICE_FIRST;
		}
		else if (m_mode == YO_ANALYSIS_MODE_EDGE)
		{
			m_idc[0] = IDC_EDGE_FIRST;
		}
		else if (m_mode == YO_ANALYSIS_MODE_EDGE_CENTER)
		{
			m_idc[0] = IDC_EDGE_CENTERED_FIRST;
		}
		else if (m_mode == YO_ANALYSIS_MODE_PART)
		{
			m_idc[0] = IDC_PART_FIRST;
		}
		else if (m_mode == YO_ANALYSIS_MODE_POLYGON)
		{
			m_idc[0] = IDC_POLYGON_FIRST;
		}
		else if (m_mode == YO_ANALYSIS_MODE_POLYGON_CENTER)
		{
			m_idc[0] = IDC_POLYGON_CENTERED_FIRST;
		}
		else if (m_mode == YO_ANALYSIS_MODE_VERTEX)
		{
			m_idc[0] = IDC_VERTEX_FIRST;
		}
	}
	else if (selected == 2)
	{
		if (m_mode == YO_ANALYSIS_MODE_COORDINATE)
		{
			m_idc[1] = IDC_COORDINATE_SECOND;
		}
		else if (m_mode == YO_ANALYSIS_MODE_DEVICE)
		{
			m_idc[1] = IDC_DEVICE_SECOND;
		}
		else if (m_mode == YO_ANALYSIS_MODE_EDGE)
		{
			m_idc[1] = IDC_EDGE_SECOND;
		}
		else if (m_mode == YO_ANALYSIS_MODE_EDGE_CENTER)
		{
			m_idc[1] = IDC_EDGE_CENTERED_SECOND;
		}
		else if (m_mode == YO_ANALYSIS_MODE_PART)
		{
			m_idc[1] = IDC_PART_SECOND;
		}
		else if (m_mode == YO_ANALYSIS_MODE_POLYGON)
		{
			m_idc[1] = IDC_POLYGON_SECOND;
		}
		else if (m_mode == YO_ANALYSIS_MODE_POLYGON_CENTER)
		{
			m_idc[1] = IDC_POLYGON_CENTERED_SECOND;
		}
		else if (m_mode == YO_ANALYSIS_MODE_VERTEX)
		{
			m_idc[1] = IDC_VERTEX_SECOND;
		}
	}
	return;

}


void CStageAnalysisDlg::YoUpdateSelected()
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CWnd *pCBox;
	RECT rect;
	RECT adRect;
	int offsetX = 3;
	int offsetY = 22;
	char s[32];

	this->GetWindowRect(&adRect);
	if (m_selected == 0)
	{
		pCBox = (CWnd *)GetDlgItem(m_idc[0]);
		pCBox->ShowWindow(SW_SHOW);
		pCBox = (CWnd *)GetDlgItem(IDC_FIRST);
		pCBox->EnableWindow(FALSE);

		pCBox = (CWnd *)GetDlgItem(m_idc[1]);
		pCBox->EnableWindow(TRUE);
		pCBox = (CWnd *)GetDlgItem(IDC_SECOND);
		pCBox->EnableWindow(FALSE);

//		(CWnd *)((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmSquareGray);
//		pCBox = (CComboBox*)GetDlgItem(m_idc[1]);
//		pCBox->SetBitmap((HBITMAP)m_bmSquareGray);
	}
	else if (m_selected == 1)
	{
		pCBox = (CWnd *)GetDlgItem(m_idc[0]);
		pCBox->ShowWindow(SW_SHOW);
		pCBox = (CWnd *)GetDlgItem(m_idc[1]);
		pCBox->ShowWindow(SW_SHOW);
		pCBox = (CWnd *)GetDlgItem(IDC_FIRST);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CWnd *)GetDlgItem(IDC_SECOND);
		pCBox->ShowWindow(SW_HIDE);
		YoUpdateMode(1);

		pCBox = (CWnd *)GetDlgItem(m_idc[0]);
		pCBox->GetWindowRect(&rect);
		rect.top = rect.top - adRect.top - offsetY;
		rect.bottom = rect.bottom - adRect.top - offsetY;
		rect.left = rect.left - adRect.left - offsetX;
		rect.right = rect.right - adRect.left - offsetX;
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CWnd *)GetDlgItem(IDC_FIRST);
		pCBox->MoveWindow(&rect, TRUE);
		pCBox->ShowWindow(SW_SHOW);

		pCBox = GetDlgItem(IDC_OFFSET_X);
		if (pCBox->IsWindowEnabled() == TRUE)
		{
			pCBox->SetWindowText("");
			pCBox->UpdateWindow();
			pCBox->EnableWindow(FALSE);

			pCBox = GetDlgItem(IDC_OFFSET_Y);
			pCBox->SetWindowText("");
			pCBox->UpdateWindow();
			pCBox->EnableWindow(FALSE);

			pCBox = GetDlgItem(IDC_OFFSET_Z);
			pCBox->SetWindowText("");
			pCBox->UpdateWindow();
			pCBox->EnableWindow(FALSE);

			pCBox = GetDlgItem(IDC_DISTANCE);
			pCBox->SetWindowText("");
			pCBox->UpdateWindow();
		}

		/***
		pCBox = (CWnd *)GetDlgItem(m_idc[1]);
		pCBox->ShowWindow(SW_SHOW);
		pCBox = (CWnd *)GetDlgItem(IDC_SECOND);
		pCBox->ShowWindow(SW_HIDE);

		if (m_token == 2)
		{
			YoUpdateMode(1);
		}
		m_token = 1;
		***/

//		pCBox = (CComboBox*)GetDlgItem(m_idc[0]);
//		pCBox->SetBitmap((HBITMAP)m_bmSquarePurple);
//		pCBox = (CComboBox*)GetDlgItem(m_idc[1]);
//		pCBox->SetBitmap((HBITMAP)m_bmSquareGray);
	}
	else if (m_selected == 2)
	{
		YoUpdateMode(2);
		pCBox = (CWnd *)GetDlgItem(m_idc[1]);
		pCBox->GetWindowRect(&rect);
		rect.top = rect.top - adRect.top - offsetY;
		rect.bottom = rect.bottom - adRect.top - offsetY;
		rect.left = rect.left - adRect.left - offsetX;
		rect.right = rect.right - adRect.left - offsetX;
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CWnd *)GetDlgItem(IDC_SECOND);
		pCBox->MoveWindow(&rect, TRUE);
		pCBox->ShowWindow(SW_SHOW);

		m_offset[0] = m_analysisPointInWorldCoords[1][0] - m_analysisPointInWorldCoords[0][0];
		m_offset[1] = m_analysisPointInWorldCoords[1][1] - m_analysisPointInWorldCoords[0][1];
		m_offset[2] = m_analysisPointInWorldCoords[1][2] - m_analysisPointInWorldCoords[0][2];
		m_offsetOrig[0] = m_offset[0];
		m_offsetOrig[1] = m_offset[1];
		m_offsetOrig[2] = m_offset[2];
		m_distance = sqrt(m_offset[0] * m_offset[0] 
			+ m_offset[1] * m_offset[1] + m_offset[2] * m_offset[2]);

		pCBox = (CComboBox*)GetDlgItem(IDC_OFFSET_X);
		sprintf(s, "%.3f", m_offset[0] * pDoc->m_unitScaleFactor);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		pCBox->EnableWindow(TRUE);

		pCBox = (CComboBox*)GetDlgItem(IDC_OFFSET_Y);
		sprintf(s, "%.3f", m_offset[1] * pDoc->m_unitScaleFactor);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		pCBox->EnableWindow(TRUE);

		pCBox = (CComboBox*)GetDlgItem(IDC_OFFSET_Z);
		sprintf(s, "%.3f", m_offset[2] * pDoc->m_unitScaleFactor);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		pCBox->EnableWindow(TRUE);

		pCBox = (CComboBox*)GetDlgItem(IDC_DISTANCE);
		sprintf(s, "%.3f", m_distance * pDoc->m_unitScaleFactor);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		
		/***
		if (m_token == 1)
		{
			YoUpdateMode(2);
		}
		m_token = 2;
		***/

//		pCBox = (CComboBox*)GetDlgItem(m_idc[1]);
//		pCBox->SetBitmap((HBITMAP)m_bmSquarePurple);
	}

}


void CStageAnalysisDlg::YoResetDistance()
{
	CWnd *pCBox;

	// TODO: Add your control notification handler code here
	m_selected = 0;

	pCBox = GetDlgItem(IDC_OFFSET_X);
	pCBox->SetWindowText("");
	pCBox->UpdateWindow();
	pCBox->EnableWindow(FALSE);

	pCBox = GetDlgItem(IDC_OFFSET_Y);
	pCBox->SetWindowText("");
	pCBox->UpdateWindow();
	pCBox->EnableWindow(FALSE);

	pCBox = GetDlgItem(IDC_OFFSET_Z);
	pCBox->SetWindowText("");
	pCBox->UpdateWindow();
	pCBox->EnableWindow(FALSE);

	pCBox = GetDlgItem(IDC_DISTANCE);
	pCBox->SetWindowText("");
	pCBox->UpdateWindow();

}

void CStageAnalysisDlg::OnResetX() 
{
	CWnd* pCBox;
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[32];

	// TODO: Add your control notification handler code here
	if (m_selected == 2)
	{
		//m_offset[0] = m_offsetOrig[0];
		//m_distance = sqrt(m_offset[0] * m_offset[0] 
		//	+ m_offset[1] * m_offset[1] + m_offset[2] * m_offset[2]);

		pCBox = (CComboBox*)GetDlgItem(IDC_OFFSET_X);
		//sprintf(s, "%.2f", m_offset[0] / pDoc->m_unitScaleFactor);
		sprintf(s, "%.2f", m_offsetOrig[0] / pDoc->m_unitScaleFactor);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		YoDoOffset(0);

		//pCBox = (CComboBox*)GetDlgItem(IDC_DISTANCE);
		//sprintf(s, "%.2f", m_distance / pDoc->m_unitScaleFactor);
		//pCBox->SetWindowText(s);
		//pCBox->UpdateWindow();
	}
	return;
}

void CStageAnalysisDlg::OnResetY() 
{
	CWnd* pCBox;
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[32];

	// TODO: Add your control notification handler code here
	if (m_selected == 2)
	{
		//m_offset[1] = m_offsetOrig[1];
		//m_distance = sqrt(m_offset[0] * m_offset[0] 
		//	+ m_offset[1] * m_offset[1] + m_offset[2] * m_offset[2]);

		pCBox = (CComboBox*)GetDlgItem(IDC_OFFSET_Y);
		//sprintf(s, "%.2f", m_offset[1] / pDoc->m_unitScaleFactor);
		sprintf(s, "%.2f", m_offsetOrig[1] / pDoc->m_unitScaleFactor);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		YoDoOffset(1);

		//pCBox = (CComboBox*)GetDlgItem(IDC_DISTANCE);
		//sprintf(s, "%.2f", m_distance / pDoc->m_unitScaleFactor);
		//pCBox->SetWindowText(s);
		//pCBox->UpdateWindow();
	}
	return;	
}

void CStageAnalysisDlg::OnResetZ() 
{
	CWnd* pCBox;
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[32];

	// TODO: Add your control notification handler code here
	if (m_selected == 2)
	{
		//m_offset[2] = m_offsetOrig[2];
		//m_distance = sqrt(m_offset[0] * m_offset[0] 
		//	+ m_offset[1] * m_offset[1] + m_offset[2] * m_offset[2]);

		pCBox = (CComboBox*)GetDlgItem(IDC_OFFSET_Z);
		//sprintf(s, "%.2f", m_offset[2] / pDoc->m_unitScaleFactor);
		sprintf(s, "%.2f", m_offsetOrig[2] / pDoc->m_unitScaleFactor);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		YoDoOffset(2);

		//pCBox = (CComboBox*)GetDlgItem(IDC_DISTANCE);
		//sprintf(s, "%.2f", m_distance / pDoc->m_unitScaleFactor);
		//pCBox->SetWindowText(s);
		//pCBox->UpdateWindow();
	}
	return;	
}


void CStageAnalysisDlg::YoDoOffset(int xyz)
{
	CWnd* pCBox;
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	char s[32];
	GLdouble m[16];
	GLdouble mInv[16];
	GLdouble prevOffset;
	CStageDevice *curDevice;
	CStageDevice *ptrDevice;
	CStagePart *ptrPart;
	CStageTag *ptrTag;
	int i;
	BOOL attached = FALSE;
	CStagePart *ptrAttachedFromPart;
	char parent[64];
	//MSG msg;

	TRACE0("YoDoOffset()\n");

	// TODO: Add your control notification handler code here
	if (m_selected == 2)
	{
		prevOffset = m_offset[xyz];

		if (xyz == 0)
		{
			pCBox = (CComboBox*)GetDlgItem(IDC_OFFSET_X);
		}
		else if (xyz == 1)
		{
			pCBox = (CComboBox*)GetDlgItem(IDC_OFFSET_Y);
		}
		else
		{
			pCBox = (CComboBox*)GetDlgItem(IDC_OFFSET_Z);
		}
		pCBox->GetWindowText(s, 32);
		sscanf(s, "%lf", &m_offset[xyz]);
		m_offset[xyz] /= pDoc->m_unitScaleFactor;

		if (prevOffset == m_offset[xyz])
		{
			return;
		}

		if (m_ptrDevice[1] != NULL)
		{
			ptrDevice = pDoc->m_currentDevice;
			ptrPart = pDoc->m_currentPart;
			pDoc->m_currentDevice = m_ptrDevice[1];
			pDoc->m_currentPart = m_ptrDevice[1]->m_ptrPart;

			if (strcmp(pDoc->m_currentDevice->m_parent, "NONE") != 0)
			{
				sprintf(parent, "%s", pDoc->m_currentDevice->m_parent);
				if (pDoc->m_currentDevice->m_attachedFromPart == NULL)
				{
					curDevice = pDoc->YoDeviceHashLookup(parent);
					ptrAttachedFromPart = curDevice->m_ptrPart;
				}
				else
				{
					ptrAttachedFromPart = pDoc->m_currentDevice->m_attachedFromPart;
				}

				pDoc->YoDetachDevice();

				// reattach device at world coords (rightmost position)
				for (curDevice = pDoc->m_deviceList;
					curDevice->m_right != NULL;
					curDevice = curDevice->m_right);
				curDevice->m_right = pDoc->m_currentDevice;
				pDoc->m_currentDevice->m_left = curDevice;
				attached = TRUE;
			}

			pDoc->YoModelMatrixOfCurrentPart(m);
			m[12 + xyz] += m_offset[xyz] - prevOffset;
			m_analysisPointInWorldCoords[1][xyz] += m_offset[xyz] - prevOffset;

			pDoc->m_currentDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
			pDoc->YoTranslateRotateValues(m,
				pDoc->m_currentDevice->m_ptrPart->m_translate,
				pDoc->m_currentDevice->m_ptrPart->m_rotate);
			for (i = 0; i < 3; i++)
			{
				pDoc->m_currentDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}

			if (attached == TRUE)
			{
				pDoc->YoDetachDevice();
				sprintf(pDoc->m_currentDevice->m_parent, "%s", 
					parent);
				pDoc->YoAttachDevice(ptrAttachedFromPart);
			}

			pDoc->m_currentDevice = ptrDevice;
			pDoc->m_currentPart = ptrPart;

			((CStageView *)pView)->YoRender(YO_RENDER_LIGHT);
			((CStageView *)pView)->YoRender(YO_RENDER_FULL);

		}
		else if (m_ptrTag[1] != NULL)
		{
			ptrDevice = pDoc->m_currentDevice;
			ptrPart = pDoc->m_currentPart;
			ptrTag = pDoc->m_currentTag;
			pDoc->m_currentTag = m_ptrTag[1];
			pDoc->m_currentPart = m_ptrTag[1]->m_ptrPath->m_ptrPart;
			pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(pDoc->m_currentPart->m_deviceName);

			pDoc->YoModelMatrixOfCurrentPart(m);
			pDoc->YoMatrixInverse(m, mInv);
			pDoc->YoModelMatrixOfCurrentTag();
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadMatrixd(mInv);
			pDoc->m_mTag[12 + xyz] += m_offset[xyz] - prevOffset;
			m_analysisPointInWorldCoords[1][xyz] += m_offset[xyz] - prevOffset;
			::glMultMatrixd(pDoc->m_mTag);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			pDoc->YoTranslateRotateValues(m,
				pDoc->m_currentTag->m_translate,
				pDoc->m_currentTag->m_rotate);
			for (i = 0; i < 3; i++)
			{
				pDoc->m_currentTag->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}
			::glPopMatrix();			
			
			pDoc->m_currentDevice = ptrDevice;
			pDoc->m_currentPart = ptrPart;
			pDoc->m_currentTag = ptrTag;

			((CStageView *)pView)->YoRender(YO_RENDER_FULL);
		}

		m_distance = sqrt(m_offset[0] * m_offset[0] 
			+ m_offset[1] * m_offset[1] + m_offset[2] * m_offset[2]);

		pCBox = (CComboBox*)GetDlgItem(IDC_DISTANCE);
		sprintf(s, "%.3f", m_distance * pDoc->m_unitScaleFactor);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		//::PeekMessage(&msg, NULL, WM_KILLFOCUS, WM_KILLFOCUS, PM_REMOVE);
	}
	return;
}

void CStageAnalysisDlg::OnKillfocusOffsetX() 
{
	YoDoOffset(0);
	return;
}

void CStageAnalysisDlg::OnKillfocusOffsetY() 
{
	YoDoOffset(1);
	return;
}

void CStageAnalysisDlg::OnKillfocusOffsetZ() 
{
	YoDoOffset(2);
	return;
}
