#if !defined(AFX_STAGESCALEDLG_H__6C5D9DD8_47F2_45AA_BE69_EB0D4CB6561D__INCLUDED_)
#define AFX_STAGESCALEDLG_H__6C5D9DD8_47F2_45AA_BE69_EB0D4CB6561D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageScaleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageScaleDlg dialog

class CStageScaleDlg : public CDialog
{
// Construction
public:
	CStageScaleDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageScaleDlg)
	enum { IDD = IDD_SCALE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL m_init;
	int m_origUnits;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageScaleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageScaleDlg)
	afx_msg void OnScaleGetMass();
	afx_msg void OnScaleKg();
	afx_msg void OnScaleLb();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGESCALEDLG_H__6C5D9DD8_47F2_45AA_BE69_EB0D4CB6561D__INCLUDED_)
