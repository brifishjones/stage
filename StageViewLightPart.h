// StageViewLightPart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageViewLightPart dialog

class CStageViewLightPart : public CDialog
{
// Construction
public:
	CStageViewLightPart(CWnd* pParent = NULL);   // standard constructor
	void YoUpdateMaterial(int, UINT);
	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageViewLightPart)
	enum { IDD = IDD_LIGHT_PART };
	CSliderCtrl	m_lightSliderSpotlightAngle;
	CSliderCtrl	m_lightSliderIntensity;
	CSliderCtrl	m_lightSliderAttenuation;
	CComboBox	m_txyz;
	CSliderCtrl	m_partSliderShininess;
	CSliderCtrl	m_partSliderRed;
	CSliderCtrl	m_partSliderGreen;
	CSliderCtrl	m_partSliderBlue;
	CSliderCtrl	m_partSliderAlpha;
	CComboBox	m_partRenderMode;
	CComboBox	m_partMaterial;
	CString	m_deviceName;
	BOOL	m_deviceVisible;
	CString	m_parentName;
	UINT	m_partAlpha;
	UINT	m_partBlue;
	UINT	m_partGreen;
	UINT	m_partRed;
	CString	m_partName;
	UINT	m_partShininess;
	CString	m_textureName;
	UINT	m_lightIntensity;
	BOOL	m_lightEnabled;
	BOOL	m_lightPointSource;
	UINT	m_lightSpotlightAngle;
	UINT	m_lightAttenuation;
	//}}AFX_DATA

	UINT m_ambient[4];
	UINT m_diffuse[4];
	UINT m_specular[4];
	UINT m_emission[4];
	int m_att;
	UINT m_attenuation[3];
	BOOL m_init;

	BOOL m_origVisible;
	GLdouble m_origTranslate[3];
	GLdouble m_origRotate[3];
	char m_origDeviceName[64];
	char m_origParent[64];
	char m_origPartName[64];
	GLfloat m_origAmbient[4];
	GLfloat m_origDiffuse[4];
	GLfloat m_origSpecular[4];
	GLfloat m_origEmission[4];
	GLfloat m_origShininess;
	UINT m_origTxyz;
	GLint m_origRenderMode;
	GLfloat m_origIntensity;
	BOOL	m_origEnabled;
	BOOL	m_origPointSource;
	GLfloat	m_origSpotlightAngle;
	GLfloat	m_origAttenuation[3];


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageViewLightPart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageViewLightPart)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
