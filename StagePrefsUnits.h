#if !defined(AFX_STAGEPREFSUNITS_H__67469C00_3C04_4C63_86F9_2333DBE242A1__INCLUDED_)
#define AFX_STAGEPREFSUNITS_H__67469C00_3C04_4C63_86F9_2333DBE242A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StagePrefsUnits.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsUnits dialog

class CStagePrefsUnits : public CPropertyPage
{
	DECLARE_DYNCREATE(CStagePrefsUnits)

// Construction
public:
	CStagePrefsUnits();
	~CStagePrefsUnits();

// Dialog Data
	//{{AFX_DATA(CStagePrefsUnits)
	enum { IDD = IDD_PREFS_UNITS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA
	BOOL m_init;
	GLint m_units;
	GLint m_origUnits;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStagePrefsUnits)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStagePrefsUnits)
	virtual BOOL OnInitDialog();
	afx_msg void OnUnitsFeet();
	afx_msg void OnUnitsInches();
	afx_msg void OnUnitsMeters();
	afx_msg void OnUnitsMillimeters();
	afx_msg void OnUnitsDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGEPREFSUNITS_H__67469C00_3C04_4C63_86F9_2333DBE242A1__INCLUDED_)
