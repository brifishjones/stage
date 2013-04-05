// StagePartMotion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStagePartMotion dialog

class CStagePartMotion : public CDialog
{
// Construction
public:
	CStagePartMotion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStagePartMotion)
	enum { IDD = IDD_PART_MOTION };
	CListBox	m_partMotionList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStagePartMotion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStagePartMotion)
	afx_msg void OnPartClearAll();
	afx_msg void OnPartRemove();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
