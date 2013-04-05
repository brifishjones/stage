// StageChooseName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageChooseName dialog

class CStageChooseName : public CDialog
{
// Construction
public:
	CStageChooseName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStageChooseName)
	enum { IDD = IDD_CHOOSE_NAME };
	CListBox	m_listName;
	CString	m_editName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageChooseName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageChooseName)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeListName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
