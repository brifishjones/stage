// StageRotaryTableDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageRotaryTableDlg dialog

class CStageRotaryTableDlg : public CDialog
{
// Construction
public:
	CStageRotaryTableDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageRotaryTableDlg)
	enum { IDD = IDD_ROTARY_TABLE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL m_init;
	long m_origEndPosition;
	long m_origCurrentPosition;
	BOOL m_origDirectionPositive;
	float m_origVelocity;
	float m_origAcceleration;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageRotaryTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageRotaryTableDlg)
	afx_msg void OnRotaryTableGo();
	afx_msg void OnRotaryTableHome();
	afx_msg void OnRotaryTableDirection();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
