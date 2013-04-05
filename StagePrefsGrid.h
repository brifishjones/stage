// StagePrefsGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsGrid dialog

class CStagePrefsGrid : public CPropertyPage
{
	DECLARE_DYNCREATE(CStagePrefsGrid)

// Construction
public:
	CStagePrefsGrid();
	~CStagePrefsGrid();

// Dialog Data
	//{{AFX_DATA(CStagePrefsGrid)
	enum { IDD = IDD_PREFS_GRID };
	CSliderCtrl	m_gridSliderRed;
	CSliderCtrl	m_gridSliderGreen;
	CSliderCtrl	m_gridSliderBlue;
	BOOL	m_gridVisible;
	UINT	m_gridBlue;
	UINT	m_gridGreen;
	UINT	m_gridRed;
	float	m_gridLength;
	float	m_gridSpacing;
	float	m_gridWidth;
	//}}AFX_DATA
	BOOL m_init;
	BOOL m_origGridVisible;
	float m_origGridWidth;
	float m_origGridLength;
	float m_origGridSpacing;
	UINT m_origGridBlue;
	UINT m_origGridGreen;
	UINT m_origGridRed;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStagePrefsGrid)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStagePrefsGrid)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusGridBlue();
	afx_msg void OnKillfocusGridRed();
	afx_msg void OnKillfocusGridGreen();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGridBlueRestore();
	afx_msg void OnGridGreenRestore();
	afx_msg void OnGridLengthRestore();
	afx_msg void OnGridRedRestore();
	afx_msg void OnGridSpacingRestore();
	afx_msg void OnGridWidthRestore();
	afx_msg void OnKillfocusGridLength();
	afx_msg void OnKillfocusGridSpacing();
	afx_msg void OnGridVisible();
	afx_msg void OnKillfocusGridWidth();
	afx_msg void OnGridDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
