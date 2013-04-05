#if !defined(AFX_STAGESCRIPTDLG_H__43E5FB06_B426_4191_9E6C_4C14D9D97E50__INCLUDED_)
#define AFX_STAGESCRIPTDLG_H__43E5FB06_B426_4191_9E6C_4C14D9D97E50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageScriptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageScriptDlg dialog

class CStageScriptDlg : public CDialog
{
// Construction
public:
	CStageScriptDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);
	BOOL YoReadScript(LPCTSTR);
	BOOL YoWriteScript(LPCTSTR);
	void YoPlay(void);
	void YoPause(void);
	void YoRewind(void);
	BOOL YoRewindFastForwardSim(void);

// Dialog Data
	//{{AFX_DATA(CStageScriptDlg)
	enum { IDD = IDD_SCRIPT_DLG };
	CEdit	m_scriptEdit;
	CListBox	m_scriptList;
	//}}AFX_DATA

	BOOL m_init;
	BOOL m_loop;
	int m_animationState;
	int m_lineNumber;
	BOOL m_modeEdit;
	double m_timeSleepFastForward;
	double m_timeFastForward;
	CBitmap m_bmRewind;
	CBitmap m_bmPlay;
	CBitmap m_bmPause;
	CBitmap m_bmLoop;
	CBitmap m_bmLoopOn;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageScriptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageScriptDlg)
	afx_msg void OnScriptSaveAs();
	afx_msg void OnScriptSave();
	afx_msg void OnScriptRewind();
	afx_msg void OnScriptPausePlay();
	afx_msg void OnScriptOpen();
	afx_msg void OnScriptNew();
	afx_msg void OnScriptLoop();
	afx_msg void OnSetfocusScriptList();
	afx_msg void OnClose();
	afx_msg void OnScriptPause();
	afx_msg void OnScriptPlay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGESCRIPTDLG_H__43E5FB06_B426_4191_9E6C_4C14D9D97E50__INCLUDED_)
