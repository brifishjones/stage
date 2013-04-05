// StageDeviceTransformation.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageDeviceTransformation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageDeviceTransformation dialog


CStageDeviceTransformation::CStageDeviceTransformation(CWnd* pParent /*=NULL*/)
	: CDialog(CStageDeviceTransformation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStageDeviceTransformation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageDeviceTransformation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageDeviceTransformation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageDeviceTransformation, CDialog)
	//{{AFX_MSG_MAP(CStageDeviceTransformation)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageDeviceTransformation message handlers
