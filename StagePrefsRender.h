// StagePrefsRender.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsRender dialog

class CStagePrefsRender : public CPropertyPage
{
	DECLARE_DYNCREATE(CStagePrefsRender)

// Construction
public:
	CStagePrefsRender();
	~CStagePrefsRender();

// Dialog Data
	//{{AFX_DATA(CStagePrefsRender)
	enum { IDD = IDD_PREFS_RENDER };
	BOOL	m_motionBlur;
	UINT	m_motionBlurIterations;
	int		m_framesPerSecond;
	BOOL	m_boundingBox;
	BOOL	m_antiAlias;
	BOOL	m_outputBitmap;
	//}}AFX_DATA
	BOOL m_init;
	BOOL m_origBoundingBox;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStagePrefsRender)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStagePrefsRender)
	virtual BOOL OnInitDialog();
	afx_msg void OnBoundingBox();
	afx_msg void OnRenderDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
