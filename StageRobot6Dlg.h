// StageRobot6Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageRobot6Dlg dialog

class CStageRobot6Dlg : public CDialog
{
// Construction
public:
	CStageRobot6Dlg(CWnd* pParent = NULL);   // standard constructor

	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageRobot6Dlg)
	enum { IDD = IDD_ROBOT6_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL m_init;
	GLdouble m_origJ[7];
	BOOL m_origLefty;
	BOOL m_origElbowUp;
	BOOL m_origWristFlipped;
	GLint m_origSpeed;
	GLdouble m_origMinAccelTime;
	BOOL m_origJointInterpolation;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageRobot6Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageRobot6Dlg)
	afx_msg void OnKillfocusJoint1();
	afx_msg void OnKillfocusJoint2();
	afx_msg void OnKillfocusJoint3();
	afx_msg void OnKillfocusJoint4();
	afx_msg void OnKillfocusJoint5();
	afx_msg void OnKillfocusJoint6();
	afx_msg void OnLefty();
	afx_msg void OnRighty();
	afx_msg void OnWristFlipped();
	afx_msg void OnElbowDown();
	afx_msg void OnElbowUp();
	afx_msg void OnKillfocusSpeed();
	afx_msg void OnDecreaseJoint1();
	afx_msg void OnDecreaseJoint2();
	afx_msg void OnDecreaseJoint3();
	afx_msg void OnDecreaseJoint4();
	afx_msg void OnDecreaseJoint5();
	afx_msg void OnDecreaseJoint6();
	afx_msg void OnIncreaseJoint1();
	afx_msg void OnIncreaseJoint2();
	afx_msg void OnIncreaseJoint3();
	afx_msg void OnIncreaseJoint4();
	afx_msg void OnIncreaseJoint5();
	afx_msg void OnIncreaseJoint6();
	afx_msg void OnSetup();
	afx_msg void OnKillfocusMinAccelTime();
	afx_msg void OnEstop();
	afx_msg void OnHome();
	virtual void OnOK();
	afx_msg void OnInterpolationJoint();
	afx_msg void OnInterpolationLinear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
