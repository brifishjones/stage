// StageTrackDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageTrackDlg dialog

class CStageTrackDlg : public CDialog
{
// Construction
public:
	CStageTrackDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);
	void YoUpdateTranslateRotate(void);
	void YoUpdateColor(void);

// Dialog Data
	//{{AFX_DATA(CStageTrackDlg)
	enum { IDD = IDD_TRACK };
	CComboBox	m_trackSnap;
	CSliderCtrl	m_trackSliderRed;
	CSliderCtrl	m_trackSliderGreen;
	CSliderCtrl	m_trackSliderBlue;
	BOOL	m_trackVisible;
	UINT	m_trackBlue;
	UINT	m_trackGreen;
	UINT	m_trackRed;
	//}}AFX_DATA

	BOOL m_init;
	BOOL m_origVisible;
	GLdouble m_origTranslate[3];
	GLdouble m_origRotate[3];
	GLfloat m_origColor[3];
	int m_snapToMode;
	BOOL m_snapTo;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageTrackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageTrackDlg)
	afx_msg void OnKillfocusTrackTranslateX();
	afx_msg void OnKillfocusTrackTranslateY();
	afx_msg void OnKillfocusTrackTranslateZ();
	afx_msg void OnKillfocusTrackRotateX();
	afx_msg void OnKillfocusTrackRotateY();
	afx_msg void OnKillfocusTrackRotateZ();
	afx_msg void OnTrackRedRestore();
	afx_msg void OnTrackGreenRestore();
	afx_msg void OnTrackBlueRestore();
	afx_msg void OnSelchangeSnapToList();
	afx_msg void OnTrackSwitchClosed();
	afx_msg void OnTrackSwitchOpened();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnTrackDecreaseX();
	afx_msg void OnTrackDecreaseY();
	afx_msg void OnTrackDecreaseZ();
	afx_msg void OnTrackIncreaseX();
	afx_msg void OnTrackIncreaseX90();
	afx_msg void OnTrackIncreaseY();
	afx_msg void OnTrackIncreaseY90();
	afx_msg void OnTrackIncreaseZ();
	afx_msg void OnTrackIncreaseZ90();
	afx_msg void OnTrackSnapTo();
	afx_msg void OnKillfocusTrackBlue();
	afx_msg void OnKillfocusTrackRed();
	afx_msg void OnKillfocusTrackGreen();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
