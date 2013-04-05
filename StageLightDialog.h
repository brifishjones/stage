// StageLightDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageLightDialog dialog

class CStageLightDialog : public CDialog
{
// Construction
public:
	CStageLightDialog(CWnd* pParent = NULL);   // standard constructor

	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageLightDialog)
	enum { IDD = IDD_LIGHT_DLG };
	CSliderCtrl	m_lightSliderSpotlightAngle;
	CSliderCtrl	m_lightSliderIntensity;
	CSliderCtrl	m_lightSliderAttenuation;
	BOOL	m_lightEnabled;
	UINT	m_lightIntensity;
	UINT	m_lightAttenuation;
	BOOL	m_lightPointSource;
	UINT	m_lightSpotlightAngle;
	//}}AFX_DATA

	int m_att;
	UINT m_attenuation[3];
	BOOL m_init;

	GLfloat m_origIntensity;
	BOOL	m_origEnabled;
	BOOL	m_origPointSource;
	GLfloat	m_origSpotlightAngle;
	GLfloat	m_origAttenuation[3];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageLightDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageLightDialog)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusLightAttenuation();
	afx_msg void OnLightAttenuationList();
	afx_msg void OnLightEnabled();
	afx_msg void OnKillfocusLightIntensity();
	afx_msg void OnLightPointSource();
	afx_msg void OnKillfocusLightSpotlightAngle();
	afx_msg void OnRestoreLightAttenuation();
	afx_msg void OnRestoreLightIntensity();
	afx_msg void OnRestoreLightSpotlightAngle();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
