// StageViewPart.h : header file
//

class CStageInheritMaterial;

/////////////////////////////////////////////////////////////////////////////
// CStageViewPart dialog

class CStageViewPart : public CDialog
{
// Construction
public:
	CStageViewPart(CWnd* pParent = NULL);   // standard constructor
	void YoUpdateMaterial(int, UINT);
	void YoUpdateTranslateRotate(void);
	void YoCancelSnapInherit(void);

	void YoRestoreMaterial(int, UINT);
	void YoTranslateRotate(GLdouble t[3], GLdouble r[3], GLdouble);
	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageViewPart)
	enum { IDD = IDD_DEVICE_PART };
	CComboBox	m_snapToList;
	CComboBox	m_partRenderMode;
	CSliderCtrl	m_partSliderShininess;
	CComboBox	m_txyz;
	CComboBox	m_partMaterial;
	CSliderCtrl	m_partSliderRed;
	CSliderCtrl	m_partSliderGreen;
	CSliderCtrl	m_partSliderBlue;
	CSliderCtrl	m_partSliderAlpha;
	BOOL	m_deviceVisible;
	UINT	m_partAlpha;
	UINT	m_partBlue;
	UINT	m_partGreen;
	UINT	m_partRed;
	UINT	m_partShininess;
	BOOL	m_textureBlending;
	BOOL	m_originVisible;
	BOOL	m_originAltDisplayed;
	//}}AFX_DATA

	UINT m_ambient[4];
	UINT m_diffuse[4];
	UINT m_specular[4];
	UINT m_emission[4];
	UINT m_wireframe[4];
	BOOL m_init;

	BOOL m_origVisible;
	BOOL m_origOriginVisible;
	BOOL m_origOriginAltDisplayed;
	GLdouble m_origMass;
	char m_origBarCode[32];
	GLdouble m_origTranslate[3];
	GLdouble m_origRotate[3];
	GLfloat m_origAmbient[4];
	GLfloat m_origDiffuse[4];
	GLfloat m_origSpecular[4];
	GLfloat m_origEmission[4];
	GLfloat m_origWireframe[4];
	GLfloat m_origShininess;
	UINT m_origTxyz;
	GLint m_origRenderMode;
	GLfloat m_origSmoothShadeAngle;

	CStageInheritMaterial *m_inheritDialog;
	BOOL m_inheritingMaterial;
	BOOL m_selectingAltOrigin;
	BOOL m_snapTo;
	int m_snapToMode;
	// GLdouble m_mSnapTo[16];

	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageViewPart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageViewPart)
	afx_msg void OnKillfocusPartAlpha();
	afx_msg void OnKillfocusPartBlue();
	afx_msg void OnKillfocusPartGreen();
	afx_msg void OnKillfocusPartRed();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangePartMaterial();
	afx_msg void OnKillfocusPartShininess();
	afx_msg void OnKillfocusTranslateX();
	afx_msg void OnKillfocusTranslateY();
	afx_msg void OnKillfocusTranslateZ();
	afx_msg void OnKillfocusRotateX();
	afx_msg void OnKillfocusRotateY();
	afx_msg void OnKillfocusRotateZ();
	afx_msg void OnSelchangePartRenderMode();
	afx_msg void OnSelchangeTxyz();
	afx_msg void OnDeviceVisible();
	afx_msg void OnRotateRestore();
	afx_msg void OnTranslateRestore();
	afx_msg void OnTranslateDecreaseX();
	afx_msg void OnTranslateDecreaseY();
	afx_msg void OnTranslateDecreaseZ();
	afx_msg void OnTranslateIncreaseX();
	afx_msg void OnTranslateIncreaseY();
	afx_msg void OnTranslateIncreaseZ();
	afx_msg void OnAlphaRestore();
	afx_msg void OnBlueRestore();
	afx_msg void OnGreenRestore();
	afx_msg void OnRedRestore();
	afx_msg void OnShininessRestore();
	afx_msg void OnPartParentInherit();
	afx_msg void OnTextureBlending();
	afx_msg void OnTextureDelete();
	afx_msg void OnTextureNew();
	afx_msg void OnTextureRotate();
	afx_msg void OnSelchangeSnapToList();
	afx_msg void OnSnapTo();
	afx_msg void OnKillfocusBarCode();
	afx_msg void OnKillfocusMass();
	afx_msg void OnRotateIncreaseX();
	afx_msg void OnRotateIncreaseY();
	afx_msg void OnRotateIncreaseZ();
	afx_msg void OnRotateDecreaseX();
	afx_msg void OnRotateDecreaseY();
	afx_msg void OnRotateDecreaseZ();
	afx_msg void OnKillfocusSmoothShadeAngle();
	afx_msg void OnOriginAltCreate();
	afx_msg void OnOriginAltDisplayed();
	afx_msg void OnOriginVisible();
	afx_msg void OnSetfocusTranslateX();
	afx_msg void OnSetfocusBarCode();
	afx_msg void OnSetfocusMass();
	afx_msg void OnSetfocusPartAlpha();
	afx_msg void OnSetfocusPartBlue();
	afx_msg void OnSetfocusPartGreen();
	afx_msg void OnSetfocusPartRed();
	afx_msg void OnSetfocusPartShininess();
	afx_msg void OnSetfocusRotateX();
	afx_msg void OnSetfocusRotateY();
	afx_msg void OnSetfocusRotateZ();
	afx_msg void OnSetfocusSmoothShadeAngle();
	afx_msg void OnSetfocusTranslateY();
	afx_msg void OnSetfocusTranslateZ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
