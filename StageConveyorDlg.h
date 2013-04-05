#if !defined(AFX_STAGECONVEYORDLG_H__609AF569_CB5B_476D_8AAB_5D533A693E55__INCLUDED_)
#define AFX_STAGECONVEYORDLG_H__609AF569_CB5B_476D_8AAB_5D533A693E55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageConveyorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageConveyorDlg dialog

class CStageConveyorDlg : public CDialog
{
// Construction
public:
	CStageConveyorDlg(CWnd* pParent = NULL);   // standard constructor

	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageConveyorDlg)
	enum { IDD = IDD_CONVEYOR_DLG };
	CListBox	m_segmentList;
	CListBox	m_stopGateList;
	CListBox	m_transLiftList;
	//}}AFX_DATA

	BOOL m_init;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageConveyorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageConveyorDlg)
	afx_msg void OnConveyorStop();
	afx_msg void OnConveyorStopGateDown();
	afx_msg void OnSelchangeConveyorStopGateList();
	afx_msg void OnConveyorStopGateUp();
	afx_msg void OnKillfocusConveyorAccel();
	afx_msg void OnConveyorForward();
	afx_msg void OnKillfocusConveyorMaxSpeed();
	afx_msg void OnConveyorPause();
	afx_msg void OnKillfocusConveyorRelSpeed();
	afx_msg void OnConveyorReverse();
	afx_msg void OnSelchangeConveyorSegmentList();
	afx_msg void OnConveyorTransLiftDown();
	afx_msg void OnSelchangeConveyorTransLiftList();
	afx_msg void OnConveyorTransLiftUp();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGECONVEYORDLG_H__609AF569_CB5B_476D_8AAB_5D533A693E55__INCLUDED_)
