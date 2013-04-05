// StageRobot6SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageRobot6SetupDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageRobot6SetupDlg dialog


CStageRobot6SetupDlg::CStageRobot6SetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageRobot6SetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStageRobot6SetupDlg)
	m_j1Min = 0.0;
	m_j1Max = 0.0;
	m_j1MaxAccel = 0.0;
	m_j2Max = 0.0;
	m_j2MaxSpeed = 0.0;
	m_j2MaxAccel = 0.0;
	m_j2Min = 0.0;
	m_j1MaxSpeed = 0.0;
	m_j3MaxAccel = 0.0;
	m_j3Max = 0.0;
	m_j3MaxSpeed = 0.0;
	m_j3Min = 0.0;
	m_j3MinAccelTime = 0.0;
	m_j2MinAccelTime = 0.0;
	m_j1MinAccelTime = 0.0;
	m_j4Max = 0.0;
	m_j4MaxAccel = 0.0;
	m_j4MaxSpeed = 0.0;
	m_j4Min = 0.0;
	m_j4MinAccelTime = 0.0;
	m_j5Max = 0.0;
	m_j5MaxAccel = 0.0;
	m_j5MaxSpeed = 0.0;
	m_j5Min = 0.0;
	m_j5MinAccelTime = 0.0;
	m_j6Max = 0.0;
	m_j6MaxAccel = 0.0;
	m_j6MaxSpeed = 0.0;
	m_j6Min = 0.0;
	m_j6MinAccel = 0.0;
	m_tcfRx = 0.0;
	m_tcfRy = 0.0;
	m_tcfRz = 0.0;
	m_tcfX = 0.0;
	m_tcfY = 0.0;
	m_tcfZ = 0.0;
	//}}AFX_DATA_INIT
}


void CStageRobot6SetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageRobot6SetupDlg)
	DDX_Text(pDX, IDC_J1_MIN, m_j1Min);
	DDX_Text(pDX, IDC_J1_MAX, m_j1Max);
	DDX_Text(pDX, IDC_J1_MAX_ACCEL, m_j1MaxAccel);
	DDX_Text(pDX, IDC_J2_MAX, m_j2Max);
	DDX_Text(pDX, IDC_J2_MAX_SPEED, m_j2MaxSpeed);
	DDX_Text(pDX, IDC_J2_MAX_ACCEL, m_j2MaxAccel);
	DDX_Text(pDX, IDC_J2_MIN, m_j2Min);
	DDX_Text(pDX, IDC_J1_MAX_SPEED, m_j1MaxSpeed);
	DDX_Text(pDX, IDC_J3_MAX_ACCEL, m_j3MaxAccel);
	DDX_Text(pDX, IDC_J3_MAX, m_j3Max);
	DDX_Text(pDX, IDC_J3_MAX_SPEED, m_j3MaxSpeed);
	DDX_Text(pDX, IDC_J3_MIN, m_j3Min);
	DDX_Text(pDX, IDC_J3_MIN_ACCEL_TIME, m_j3MinAccelTime);
	DDX_Text(pDX, IDC_J2_MIN_ACCEL_TIME, m_j2MinAccelTime);
	DDX_Text(pDX, IDC_J1_MIN_ACCEL_TIME, m_j1MinAccelTime);
	DDX_Text(pDX, IDC_J4_MAX, m_j4Max);
	DDX_Text(pDX, IDC_J4_MAX_ACCEL, m_j4MaxAccel);
	DDX_Text(pDX, IDC_J4_MAX_SPEED, m_j4MaxSpeed);
	DDX_Text(pDX, IDC_J4_MIN, m_j4Min);
	DDX_Text(pDX, IDC_J4_MIN_ACCEL_TIME, m_j4MinAccelTime);
	DDX_Text(pDX, IDC_J5_MAX, m_j5Max);
	DDX_Text(pDX, IDC_J5_MAX_ACCEL, m_j5MaxAccel);
	DDX_Text(pDX, IDC_J5_MAX_SPEED, m_j5MaxSpeed);
	DDX_Text(pDX, IDC_J5_MIN, m_j5Min);
	DDX_Text(pDX, IDC_J5_MIN_ACCEL_TIME, m_j5MinAccelTime);
	DDX_Text(pDX, IDC_J6_MAX, m_j6Max);
	DDX_Text(pDX, IDC_J6_MAX_ACCEL, m_j6MaxAccel);
	DDX_Text(pDX, IDC_J6_MAX_SPEED, m_j6MaxSpeed);
	DDX_Text(pDX, IDC_J6_MIN, m_j6Min);
	DDX_Text(pDX, IDC_J6_MIN_ACCEL_TIME, m_j6MinAccel);
	DDX_Text(pDX, IDC_TCF_RX, m_tcfRx);
	DDX_Text(pDX, IDC_TCF_RY, m_tcfRy);
	DDX_Text(pDX, IDC_TCF_RZ, m_tcfRz);
	DDX_Text(pDX, IDC_TCF_X, m_tcfX);
	DDX_Text(pDX, IDC_TCF_Y, m_tcfY);
	DDX_Text(pDX, IDC_TCF_Z, m_tcfZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageRobot6SetupDlg, CDialog)
	//{{AFX_MSG_MAP(CStageRobot6SetupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageRobot6SetupDlg message handlers

void CStageRobot6SetupDlg::OnOK() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	UpdateData(TRUE);

	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[1][0] = m_j1Min;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[2][0] = m_j2Min;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[3][0] = m_j3Min - 180.0;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[4][0] = m_j4Min;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[5][0] = m_j5Min;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[6][0] = m_j6Min;
	
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[1][1] = m_j1Max;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[2][1] = m_j2Max;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[3][1] = m_j3Max - 180.0;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[4][1] = m_j4Max;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[5][1] = m_j5Max;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[6][1] = m_j6Max;

	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[1][1] = m_j1MaxSpeed;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[2][1] = m_j2MaxSpeed;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[3][1] = m_j3MaxSpeed;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[4][1] = m_j4MaxSpeed;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[5][1] = m_j5MaxSpeed;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[6][1] = m_j6MaxSpeed;

	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[1][0] = m_j1MaxAccel;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[2][0] = m_j2MaxAccel;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[3][0] = m_j3MaxAccel;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[4][0] = m_j4MaxAccel;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[5][0] = m_j5MaxAccel;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[6][0] = m_j6MaxAccel;

	((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[0] = m_tcfX;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[1] = m_tcfY;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[2] = m_tcfZ;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[3] = m_tcfRx;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[4] = m_tcfRy;
	((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[5] = m_tcfRz;

	CDialog::OnOK();
}

void CStageRobot6SetupDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CStageRobot6SetupDlg::OnInitDialog() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_j1Min = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[1][0];
	m_j2Min = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[2][0];
	m_j3Min = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[3][0] + 180.0;
	m_j4Min = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[4][0];
	m_j5Min = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[5][0];
	m_j6Min = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[6][0];

	m_j1Max = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[1][1];
	m_j2Max = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[2][1];
	m_j3Max = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[3][1] + 180.0;
	m_j4Max = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[4][1];
	m_j5Max = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[5][1];
	m_j6Max = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMinMax[6][1];

	m_j1MaxSpeed = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[1][1];
	m_j2MaxSpeed = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[2][1];
	m_j3MaxSpeed = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[3][1];
	m_j4MaxSpeed = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[4][1];
	m_j5MaxSpeed = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[5][1];
	m_j6MaxSpeed = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[6][1];

	m_j1MaxAccel = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[1][0];
	m_j2MaxAccel = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[2][0];
	m_j3MaxAccel = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[3][0];
	m_j4MaxAccel = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[4][0];
	m_j5MaxAccel = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[5][0];
	m_j6MaxAccel = ((CStageRobot6 *)pDoc->m_currentDevice)->m_jMaxAccelMaxSpeed[6][0];

	m_tcfX = ((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[0];
	m_tcfY = ((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[1];
	m_tcfZ = ((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[2];
	m_tcfRx = ((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[3];
	m_tcfRy = ((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[4];
	m_tcfRz = ((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[5];

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
