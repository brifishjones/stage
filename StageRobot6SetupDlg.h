// StageRobot6SetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageRobot6SetupDlg dialog

class CStageRobot6SetupDlg : public CDialog
{
// Construction
public:
	CStageRobot6SetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStageRobot6SetupDlg)
	enum { IDD = IDD_ROBOT6_SETUP };
	double	m_j1Min;
	double	m_j1Max;
	double	m_j1MaxAccel;
	double	m_j2Max;
	double	m_j2MaxSpeed;
	double	m_j2MaxAccel;
	double	m_j2Min;
	double	m_j1MaxSpeed;
	double	m_j3MaxAccel;
	double	m_j3Max;
	double	m_j3MaxSpeed;
	double	m_j3Min;
	double	m_j3MinAccelTime;
	double	m_j2MinAccelTime;
	double	m_j1MinAccelTime;
	double	m_j4Max;
	double	m_j4MaxAccel;
	double	m_j4MaxSpeed;
	double	m_j4Min;
	double	m_j4MinAccelTime;
	double	m_j5Max;
	double	m_j5MaxAccel;
	double	m_j5MaxSpeed;
	double	m_j5Min;
	double	m_j5MinAccelTime;
	double	m_j6Max;
	double	m_j6MaxAccel;
	double	m_j6MaxSpeed;
	double	m_j6Min;
	double	m_j6MinAccel;
	double	m_tcfRx;
	double	m_tcfRy;
	double	m_tcfRz;
	double	m_tcfX;
	double	m_tcfY;
	double	m_tcfZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageRobot6SetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageRobot6SetupDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
