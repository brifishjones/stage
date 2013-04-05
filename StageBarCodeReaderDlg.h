#if !defined(AFX_STAGEBARCODEREADERDLG_H__3B152682_3AB1_471C_A18B_C4458B056D6E__INCLUDED_)
#define AFX_STAGEBARCODEREADERDLG_H__3B152682_3AB1_471C_A18B_C4458B056D6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageBarCodeReaderDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageBarCodeReaderDlg dialog

class CStageBarCodeReaderDlg : public CDialog
{
// Construction
public:
	CStageBarCodeReaderDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL YoInitDialog(void);

// Dialog Data
	//{{AFX_DATA(CStageBarCodeReaderDlg)
	enum { IDD = IDD_BAR_CODE_READER_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL m_init;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageBarCodeReaderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageBarCodeReaderDlg)
	afx_msg void OnBcrGetCode();
	afx_msg void OnBcrTrigger();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGEBARCODEREADERDLG_H__3B152682_3AB1_471C_A18B_C4458B056D6E__INCLUDED_)
