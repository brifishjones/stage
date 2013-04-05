#if !defined(AFX_STAGEPREFSNETWORK_H__5C77CA7F_BE19_46C0_B58F_AE2A64180A5A__INCLUDED_)
#define AFX_STAGEPREFSNETWORK_H__5C77CA7F_BE19_46C0_B58F_AE2A64180A5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StagePrefsNetwork.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsNetwork dialog

class CStagePrefsNetwork : public CPropertyPage
{
	DECLARE_DYNCREATE(CStagePrefsNetwork)

// Construction
public:
	CStagePrefsNetwork();
	~CStagePrefsNetwork();

// Dialog Data
	//{{AFX_DATA(CStagePrefsNetwork)
	enum { IDD = IDD_PREFS_NETWORK };
	UINT	m_port;
	//}}AFX_DATA
	BOOL m_init;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStagePrefsNetwork)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStagePrefsNetwork)
	virtual BOOL OnInitDialog();
	afx_msg void OnNetworkDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGEPREFSNETWORK_H__5C77CA7F_BE19_46C0_B58F_AE2A64180A5A__INCLUDED_)
