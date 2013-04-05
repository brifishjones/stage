#if !defined(AFX_STAGETRAINDLG_H__81CC6F80_D6C0_11D3_883D_E60D09489F62__INCLUDED_)
#define AFX_STAGETRAINDLG_H__81CC6F80_D6C0_11D3_883D_E60D09489F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageTrainDlg.h : header file
//

class CStageTrackSeg;

/////////////////////////////////////////////////////////////////////////////
// CStageTrainDlg dialog

class CStageTrainDlg : public CDialog
{
// Construction
public:
	CStageTrainDlg(CWnd* pParent = NULL);   // standard constructor

	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageTrainDlg)
	enum { IDD = IDD_TRAIN_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL m_init;
	CStageTrackSeg *m_ptrOrigTrackSeg;
	BOOL m_origDirectionPositive;
	CStageTrackSeg *m_ptrOrigTrackSegEnd;
	double m_origRelativePositionEnd;
	double m_origRelativePosition;       // number between 0.0 (from) and 1.0 (to)
	double m_origVelocity;				// in mm / sec
	double m_origAcceleration;			// in mm / sec2

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageTrainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageTrainDlg)
	afx_msg void OnTrainGo();
	afx_msg void OnKillfocusTrainVelocity();
	afx_msg void OnKillfocusTrainAcceleration();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGETRAINDLG_H__81CC6F80_D6C0_11D3_883D_E60D09489F62__INCLUDED_)
