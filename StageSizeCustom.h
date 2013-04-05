#if !defined(AFX_STAGESIZECUSTOM_H__C3717EB3_D1BB_44FF_9C76_5BD9D0B48234__INCLUDED_)
#define AFX_STAGESIZECUSTOM_H__C3717EB3_D1BB_44FF_9C76_5BD9D0B48234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageSizeCustom.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageSizeCustom dialog

class CStageSizeCustom : public CDialog
{
// Construction
public:
	CStageSizeCustom(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStageSizeCustom)
	enum { IDD = IDD_SIZE_CUSTOM };
	UINT	m_sizeHeight;
	UINT	m_sizeWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageSizeCustom)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageSizeCustom)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGESIZECUSTOM_H__C3717EB3_D1BB_44FF_9C76_5BD9D0B48234__INCLUDED_)
