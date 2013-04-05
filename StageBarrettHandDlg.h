#if !defined(AFX_STAGEBARRETTHANDDLG_H__EA44BF84_F40D_40C4_B265_DDF951344E91__INCLUDED_)
#define AFX_STAGEBARRETTHANDDLG_H__EA44BF84_F40D_40C4_B265_DDF951344E91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageBarrettHandDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageBarrettHandDlg dialog

class CStageBarrettHandDlg : public CDialog
{
// Construction
public:
	CStageBarrettHandDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageBarrettHandDlg)
	enum { IDD = IDD_BARRETTHAND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL m_init;
	double m_middle;
	double m_tip;
	double m_spread;
	double m_velocity;
	double m_origVelocity;
	double m_origSpread;  // 0.0 to 180.0
	double m_origFingerFixed[3];
	double m_origFingerLeft[3];
	double m_origFingerRight[3];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageBarrettHandDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageBarrettHandDlg)
	afx_msg void OnKillfocusBarretthandVelocity();
	afx_msg void OnKillfocusBarretthandTip();
	afx_msg void OnBarretthandSpreadOpen();
	afx_msg void OnBarretthandSpreadClose();
	afx_msg void OnKillfocusBarretthandSpread();
	afx_msg void OnKillfocusBarretthandMiddle();
	afx_msg void OnBarretthandJointOpen();
	afx_msg void OnBarretthandJointClose();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGEBARRETTHANDDLG_H__EA44BF84_F40D_40C4_B265_DDF951344E91__INCLUDED_)
