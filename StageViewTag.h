// StageViewTag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageViewTag dialog

class CStageViewTag : public CDialog
{
// Construction
public:
	CStageViewTag(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);
	void YoUpdateDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageViewTag)
	enum { IDD = IDD_TAG };
	CComboBox	m_tagSnap;
	CSliderCtrl	m_pathSliderRed;
	CSliderCtrl	m_pathSliderGreen;
	CSliderCtrl	m_pathSliderBlue;
	BOOL	m_visible;
	UINT	m_pathGreen;
	UINT	m_pathRed;
	UINT	m_pathBlue;
	//}}AFX_DATA

	BOOL m_init;
	BOOL m_origVisible;
	GLdouble m_origTranslate[3];
	GLdouble m_origRotate[3];
	GLfloat m_origColor[3];
	int m_tagSnapMode;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageViewTag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageViewTag)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusPathBlue();
	afx_msg void OnKillfocusPathGreen();
	afx_msg void OnKillfocusPathRed();
	afx_msg void OnKillfocusTagRotateX();
	afx_msg void OnKillfocusTagRotateY();
	afx_msg void OnKillfocusTagRotateZ();
	afx_msg void OnKillfocusTagTranslateX();
	afx_msg void OnKillfocusTagTranslateY();
	afx_msg void OnKillfocusTagTranslateZ();
	afx_msg void OnTagTranslateRestore();
	afx_msg void OnTagRotateRestore();
	afx_msg void OnPathBlueRestore();
	afx_msg void OnPathGreenRestore();
	afx_msg void OnPathRedRestore();
	afx_msg void OnTag90X();
	afx_msg void OnTag90Y();
	afx_msg void OnTag90Z();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeTagSnap();
	afx_msg void OnPathVisible();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
