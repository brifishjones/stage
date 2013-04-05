/////////////////////////////////////////////////////////////////////////////
// CStageLightPartView dialog

class CStageLightPartView : public CDialog
{
// Construction
public:
	CStageLightPartView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStageLightPartView)
	enum { IDD = IDD_PART };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageLightPartView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageLightPartView)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
