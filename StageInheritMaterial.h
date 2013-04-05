// StageInheritMaterial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageInheritMaterial dialog

class CStageInheritMaterial : public CDialog
{
// Construction
public:
	CStageInheritMaterial(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);
	
	GLfloat m_origAmbient[4];
	GLfloat m_origDiffuse[4];
	GLfloat m_origSpecular[4];
	GLfloat m_origEmission[4];
	GLfloat m_origWireframe[4];
	GLfloat m_origShininess;
	GLint m_origRenderMode;
	BOOL m_init;

// Dialog Data
	//{{AFX_DATA(CStageInheritMaterial)
	enum { IDD = IDD_INHERIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageInheritMaterial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageInheritMaterial)
	afx_msg void OnInheritParent();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
