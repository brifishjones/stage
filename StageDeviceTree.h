// StageDeviceTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageDeviceTree dialog

class CStageDeviceTree : public CDialog
{
// Construction
public:
	CStageDeviceTree(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStageDeviceTree)
	enum { IDD = IDD_DEVICE_TREE };
	CTreeCtrl	m_deviceTree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageDeviceTree)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageDeviceTree)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
