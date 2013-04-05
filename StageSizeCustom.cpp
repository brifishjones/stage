// StageSizeCustom.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageSizeCustom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageSizeCustom dialog


CStageSizeCustom::CStageSizeCustom(CWnd* pParent /*=NULL*/)
	: CDialog(CStageSizeCustom::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStageSizeCustom)
	m_sizeHeight = 0;
	m_sizeWidth = 0;
	//}}AFX_DATA_INIT
}


void CStageSizeCustom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageSizeCustom)
	DDX_Text(pDX, IDC_SIZE_HEIGHT, m_sizeHeight);
	DDX_Text(pDX, IDC_SIZE_WIDTH, m_sizeWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageSizeCustom, CDialog)
	//{{AFX_MSG_MAP(CStageSizeCustom)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageSizeCustom message handlers
