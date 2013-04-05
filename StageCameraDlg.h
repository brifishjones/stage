#if !defined(AFX_STAGECAMERADLG_H__94962DB9_C57B_425B_9B2B_F8AEF13A5937__INCLUDED_)
#define AFX_STAGECAMERADLG_H__94962DB9_C57B_425B_9B2B_F8AEF13A5937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageCameraDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageCameraDlg dialog

class CStageCameraDlg : public CDialog
{
// Construction
public:
	CStageCameraDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageCameraDlg)
	enum { IDD = IDD_CAMERA_DLG };
	CSliderCtrl	m_cameraSliderFOV;
	BOOL	m_cameraEnabled;
	//}}AFX_DATA

	BOOL m_init;
	double m_origFieldOfView;
	double m_origClipFront;
	double m_origClipRear;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageCameraDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageCameraDlg)
	afx_msg void OnKillfocusCameraClipFront();
	afx_msg void OnKillfocusCameraClipRear();
	afx_msg void OnCameraEnabled();
	afx_msg void OnKillfocusCameraFieldOfView();
	afx_msg void OnRestoreCameraClipFront();
	afx_msg void OnRestoreCameraClipRear();
	afx_msg void OnRestoreCameraFieldOfView();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGECAMERADLG_H__94962DB9_C57B_425B_9B2B_F8AEF13A5937__INCLUDED_)
