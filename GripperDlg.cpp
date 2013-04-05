// GripperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "GripperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGripperDlg dialog


CGripperDlg::CGripperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGripperDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGripperDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGripperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGripperDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGripperDlg, CDialog)
	//{{AFX_MSG_MAP(CGripperDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGripperDlg message handlers

void CGripperDlg::OnOK() 
{
	// TODO: Add extra validation here
	// disable OK including Enter key shortcut
	return;
	
	//CDialog::OnOK();
}
