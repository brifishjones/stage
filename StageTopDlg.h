#if !defined(AFX_STAGETOPDLG_H__D280147F_7498_4A81_B256_77E6FB81AD9D__INCLUDED_)
#define AFX_STAGETOPDLG_H__D280147F_7498_4A81_B256_77E6FB81AD9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageTopDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageTopDlg window

class CStageTopDlg : public CDialogBar
{
// Construction
public:
	CStageTopDlg();


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageTopDlg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStageTopDlg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStageTopDlg)
	afx_msg void OnPlay(void);
	afx_msg void OnPause(void);
	afx_msg void OnRewind(void);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnUpdateTime(void);
	afx_msg void OnUpdatePlaybackBackgroundUI(CCmdUI*);
	afx_msg void OnUpdatePlayUI(CCmdUI *);
	afx_msg void OnUpdatePauseUI(CCmdUI *);
	afx_msg void OnUpdateRewindUI(CCmdUI *);
	afx_msg void OnUpdateMinutesUI(CCmdUI *);
	afx_msg void OnUpdateSecondsUI(CCmdUI *);
	afx_msg void OnUpdateFramesUI(CCmdUI *);
	afx_msg void OnUpdateTimeUI(CCmdUI *);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	void YoRewindFastForwardSim(double);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGETOPDLG_H__D280147F_7498_4A81_B256_77E6FB81AD9D__INCLUDED_)
