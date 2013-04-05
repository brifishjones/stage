// StageMotionViewHistory.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageMotionViewHistory dialog

class CStageMotionViewHistory : public CDialog
{
// Construction
public:
	CStageMotionViewHistory(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStageMotionViewHistory)
	enum { IDD = IDD_EYE_MOTION };
	CListBox	m_motionList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageMotionViewHistory)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageMotionViewHistory)
	virtual BOOL OnInitDialog();
	afx_msg void OnRemove();
	afx_msg void OnClearAll();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
