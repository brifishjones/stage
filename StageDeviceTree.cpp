// StageDeviceTree.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageDeviceTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageDeviceTree dialog


CStageDeviceTree::CStageDeviceTree(CWnd* pParent /*=NULL*/)
	: CDialog(CStageDeviceTree::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStageDeviceTree)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageDeviceTree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageDeviceTree)
	DDX_Control(pDX, IDC_DEVICE_TREE, m_deviceTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageDeviceTree, CDialog)
	//{{AFX_MSG_MAP(CStageDeviceTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageDeviceTree message handlers

BOOL CStageDeviceTree::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	LPCTSTR lpszItem = "device";

	m_deviceTree.InsertItem(lpszItem, TVI_ROOT, TVI_LAST);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
