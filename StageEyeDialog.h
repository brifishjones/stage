// StageEyeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageEyeDialog dialog

class CStageEyeDialog : public CDialog
{
// Construction
public:
	CStageEyeDialog(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageEyeDialog)
	enum { IDD = IDD_EYE };
	CSliderCtrl	m_eyeSliderFOV;
	//}}AFX_DATA

	GLdouble m_eyeOrig[6];
	GLdouble m_clipFrontOrig;
	GLdouble m_clipRearOrig;
	GLdouble m_fieldOfViewOrig;
	BOOL m_init;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageEyeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageEyeDialog)
	afx_msg void OnKillfocusEyeClipfront();
	afx_msg void OnEyeClipfrontRestore();
	afx_msg void OnKillfocusEyeCliprear();
	afx_msg void OnEyeCliprearRestore();
	afx_msg void OnKillfocusEyeTox();
	afx_msg void OnKillfocusEyeToy();
	afx_msg void OnKillfocusEyeToz();
	afx_msg void OnKillfocusEyeFromx();
	afx_msg void OnKillfocusEyeFromy();
	afx_msg void OnKillfocusEyeFromz();
	afx_msg void OnEyeRestoreFov();
	afx_msg void OnEyeRestoreFrom();
	afx_msg void OnEyeRestoreTo();
	afx_msg void OnKillfocusEyeFov();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
