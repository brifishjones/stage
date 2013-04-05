// StageChooseDevice.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageChooseDevice dialog

class CStageChooseDevice : public CDialog
{
// Construction
public:
	CStageChooseDevice(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStageChooseDevice)
	enum { IDD = IDD_CHOOSE_DEVICE };
	CListBox	m_listName;
	CString	m_editName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageChooseDevice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageChooseDevice)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
