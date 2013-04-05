// StagePrefsNetwork.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StagePrefsNetwork.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsNetwork property page

IMPLEMENT_DYNCREATE(CStagePrefsNetwork, CPropertyPage)

CStagePrefsNetwork::CStagePrefsNetwork() : CPropertyPage(CStagePrefsNetwork::IDD)
{
	m_init = FALSE;
	//{{AFX_DATA_INIT(CStagePrefsNetwork)
	m_port = 0;
	//}}AFX_DATA_INIT
}

CStagePrefsNetwork::~CStagePrefsNetwork()
{
}

void CStagePrefsNetwork::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStagePrefsNetwork)
	DDX_Text(pDX, IDC_NETWORK_PORT, m_port);
	DDV_MinMaxUInt(pDX, m_port, 1000, 9999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStagePrefsNetwork, CPropertyPage)
	//{{AFX_MSG_MAP(CStagePrefsNetwork)
	ON_BN_CLICKED(IDC_NETWORK_DEFAULTS, OnNetworkDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStagePrefsNetwork message handlers

BOOL CStagePrefsNetwork::OnInitDialog() 
{
	m_init = TRUE;
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStagePrefsNetwork::OnNetworkDefaults() 
{
	m_port = YO_DEFAULT_NETWORK_PORT;

	UpdateData(FALSE);	
}
