// StageGripperDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageGripperDlg dialog

class CStageGripperDlg : public CDialog
{
// Construction
public:
	CStageGripperDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageGripperDlg)
	enum { IDD = IDD_GRIPPER_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL m_init;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageGripperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageGripperDlg)
	afx_msg void OnGripperClose();
	afx_msg void OnGripperOpen();
	afx_msg void OnGripperTypeRotating();
	afx_msg void OnGripperTypeTranslating();
	afx_msg void OnKillfocusGripperDisplacementClose();
	afx_msg void OnKillfocusGripperDisplacementOpen();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
