// StageEyeViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageEyeViewDlg dialog

class CStageEyeViewDlg : public CDialog
{
// Construction
public:
	CStageEyeViewDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);
	void YoUpdateButtons(void);

// Dialog Data
	//{{AFX_DATA(CStageEyeViewDlg)
	enum { IDD = IDD_EYE_VIEW_DLG };
	CListBox	m_listName;
	CString	m_editName;
	//}}AFX_DATA

BOOL m_init;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageEyeViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageEyeViewDlg)
	afx_msg void OnEyeViewDelete();
	afx_msg void OnEyeViewGoTo();
	afx_msg void OnEyeViewNew();
	afx_msg void OnEyeViewRename();
	afx_msg void OnEyeViewSet();
	afx_msg void OnChangeEyeViewName();
	afx_msg void OnSelchangeEyeViewList();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
