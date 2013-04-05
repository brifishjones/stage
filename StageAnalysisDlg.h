// StageAnalysisDlg.h : header file
//

class CStageVertices;
class CStageDevice;
class CStageTag;

/////////////////////////////////////////////////////////////////////////////
// CStageAnalysisDlg dialog

class CStageAnalysisDlg : public CDialog
{
// Construction
public:
	CStageAnalysisDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);
	void YoResetDistance(void);
	void YoUpdateSelected(void);
	void YoUpdateMode(int);
	void YoDoOffset(int);

// Dialog Data
	//{{AFX_DATA(CStageAnalysisDlg)
	enum { IDD = IDD_ANALYSIS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL m_init;
	int m_mode;
	int m_selected;
	int m_idc[2];
	int m_token;
	CStageVertices *m_ptrPolygonVertices[2];
	CStageDevice *m_ptrDevice[2];
	CStageTag *m_ptrTag[2];
	GLdouble m_analysisPoint[2][3];
	GLdouble m_analysisPointInWorldCoords[2][3];
	GLdouble m_offset[3];
	GLdouble m_offsetOrig[3];
	GLdouble m_distance;
	CBitmap m_bmSquareGray;
	CBitmap m_bmSquarePurple;
	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageAnalysisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageAnalysisDlg)
	virtual void OnOK();
	afx_msg void OnCoordinate();
	afx_msg void OnDevice();
	afx_msg void OnEdge();
	afx_msg void OnEdgeCenter();
	afx_msg void OnPart();
	afx_msg void OnPolygon();
	afx_msg void OnPolygonCenter();
	afx_msg void OnVertex();
	afx_msg void OnResetX();
	afx_msg void OnResetY();
	afx_msg void OnResetZ();
	afx_msg void OnKillfocusOffsetX();
	afx_msg void OnKillfocusOffsetY();
	afx_msg void OnKillfocusOffsetZ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
