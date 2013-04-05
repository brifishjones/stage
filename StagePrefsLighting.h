// StagePrefsLighting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsLighting dialog

class CStagePrefsLighting : public CPropertyPage
{
	DECLARE_DYNCREATE(CStagePrefsLighting)

// Construction
public:
	CStagePrefsLighting();
	~CStagePrefsLighting();

// Dialog Data
	//{{AFX_DATA(CStagePrefsLighting)
	enum { IDD = IDD_PREFS_LIGHTING };
	CSliderCtrl	m_lightingSunSliderIntensity;
	float	m_lightingSunAltitude;
	float	m_lightingSunAzimuth;
	BOOL	m_twoSide;
	float	m_lightingSunIntensity;
	//}}AFX_DATA
	BOOL m_init;
	BOOL m_origTwoSide;
	float m_origLightingSunIntensity;
	float m_origLightingSunAltitude;
	float m_origLightingSunAzimuth;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStagePrefsLighting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStagePrefsLighting)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillfocusLightingSunAltitude();
	afx_msg void OnKillfocusLightingSunAzimuth();
	afx_msg void OnKillfocusLightingSunIntensity();
	afx_msg void OnTwoSide();
	afx_msg void OnLightingSunAltitudeRestore();
	afx_msg void OnLightingSunAzimuthRestore();
	afx_msg void OnLightingSunIntensityRestore();
	afx_msg void OnLightingSunFront();
	afx_msg void OnLightingSunLeft();
	afx_msg void OnLightingSunRight();
	afx_msg void OnLightingDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
