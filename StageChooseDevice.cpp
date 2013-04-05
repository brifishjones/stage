// StageChooseDevice.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageChooseDevice.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageChooseDevice dialog


CStageChooseDevice::CStageChooseDevice(CWnd* pParent /*=NULL*/)
	: CDialog(CStageChooseDevice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStageChooseDevice)
	m_editName = _T("");
	//}}AFX_DATA_INIT
}


void CStageChooseDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageChooseDevice)
	DDX_Control(pDX, IDC_LIST_NAME, m_listName);
	DDX_Text(pDX, IDC_EDIT_NAME, m_editName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageChooseDevice, CDialog)
	//{{AFX_MSG_MAP(CStageChooseDevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageChooseDevice message handlers

BOOL CStageChooseDevice::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStageDevice *ptrDevice;
	CStagePart *currentPart;
	CStagePart *ptrPart;
	CStagePath *ptrPath;
	CStageTag *ptrTag;
	int i;
	int sel = 0;
	char s[256];
	CWnd *pCBox;

	pCBox = (CComboBox *)GetDlgItem(IDC_INVISIBLE);

	m_listName.ResetContent();
	((CWnd *)this)->SetWindowText(((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle);

	if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Choose Device") == 0)
	{
		pCBox->ShowWindow(SW_SHOW);
		m_editName = "Select a device:";
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			for (ptrDevice = pDoc->m_deviceHash[i];
				ptrDevice != NULL;
				ptrDevice = ptrDevice->m_nextHash)
			{
				if (ptrDevice->m_visible == TRUE)
				{
					m_listName.AddString(CString(ptrDevice->m_name));
				}
				else
				{
					sprintf(s, "%s ***", ptrDevice->m_name);
					m_listName.AddString(CString(s));
				}
				//if (ptrDevice == pDoc->m_currentDevice)
				//{
				//	m_listName.SetCurSel(m_listName.GetCount() - 1);
				//}
			}
		}
		UpdateData(FALSE);
		if (pDoc->m_currentDevice->m_visible == TRUE)
		{
			m_listName.SelectString(0, (LPCTSTR)pDoc->m_currentDevice->m_name);
		}
	}
	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Choose Path") == 0)
	{
		pCBox->ShowWindow(SW_SHOW);
		m_editName = "Select a path:";
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			for (ptrPath = pDoc->m_pathHash[i];
				ptrPath != NULL;
				ptrPath = ptrPath->m_nextHash)
			{
				if (ptrPath->m_visible == TRUE)
				{
					m_listName.AddString(CString(ptrPath->m_name));
				}
				else
				{
					sprintf(s, "%s ***", ptrPath->m_name);
					m_listName.AddString(CString(s));
				}
				//if (ptrDevice == pDoc->m_currentDevice)
				//{
				//	m_listName.SetCurSel(m_listName.GetCount() - 1);
				//}
			}
		}
		UpdateData(FALSE);
		if (pDoc->m_currentTag->m_ptrPath->m_visible == TRUE)
		{
			m_listName.SelectString(0, (LPCTSTR)pDoc->m_currentTag->m_ptrPath->m_name);
		}
	}
	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Attach Device") == 0)
	{
		pCBox->ShowWindow(SW_HIDE);
		sprintf(s, "Attach %s to:", pDoc->m_currentDevice->m_name);
		m_editName = CString(s);
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			for (ptrDevice = pDoc->m_deviceHash[i];
				ptrDevice != NULL;
				ptrDevice = ptrDevice->m_nextHash)
			{
				if (ptrDevice != pDoc->m_currentDevice)
				{
					m_listName.AddString(CString(ptrDevice->m_name));
					//if (strcmp(pDoc->m_currentDevice->m_parent, ptrDevice->m_name) == 0)
					//{
					//	m_listName.SetCurSel(m_listName.GetCount() - 1);
					//	TRACE1("GetCount - 1 = %d\n", m_listName.GetCount() - 1);
					//}
				}
			}
		}
		UpdateData(FALSE);
		if (strcmp(pDoc->m_currentDevice->m_parent, "NULL") != 0)
		{
			m_listName.SelectString(0, (LPCTSTR)pDoc->m_currentDevice->m_parent);
		}
		
	}
	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Choose Part") == 0)
	{
		pCBox->ShowWindow(SW_HIDE);
		sprintf(s, "Device: %s   Select current part:", pDoc->m_currentDevice->m_name);
		m_editName = CString(s);

		pDoc->m_partStack = NULL;

		for (currentPart = pDoc->m_currentDevice->m_ptrPart; currentPart != NULL;)
		{
			ptrPart = currentPart;
			if (currentPart->m_down != NULL)
			{
				if (currentPart->m_right != NULL)
				{
					pDoc->YoPushPart(currentPart->m_right);
				}
				currentPart = currentPart->m_down;
			}
			else if (currentPart->m_right != NULL)
			{
				currentPart = currentPart->m_right;
			}
			else if (pDoc->m_partStack != NULL)
			{
				currentPart = pDoc->YoPopPart();
			}
			else 
			{
				currentPart = NULL; 
			}

			m_listName.AddString(CString(ptrPart->m_partName));
			//if (ptrPart == pDoc->m_currentPart)
			//{
			//	m_listName.SetCurSel(m_listName.GetCount() - 1);
			//}

		}
		while (pDoc->YoPopPart() != NULL);
		UpdateData(FALSE);
		m_listName.SelectString(0, (LPCTSTR)pDoc->m_currentPart->m_partName);
	}

	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Choose Tag") == 0)
	{
		pCBox->ShowWindow(SW_HIDE);
		sprintf(s, "Path: %s   Select current tag:", pDoc->m_currentTag->m_ptrPath->m_name);
		m_editName = CString(s);

		i = 0;
		for (ptrTag = pDoc->m_currentTag->m_ptrPath->m_ptrTag;
			ptrTag != NULL;
			ptrTag = ptrTag->m_nextTag)
		{
			sprintf(s, "%d", ptrTag->m_tag);
			m_listName.AddString(CString(s));
			if (ptrTag == pDoc->m_currentTag)
			{
				sel = i;
			}
			i++;
		}
		UpdateData(FALSE);
		m_listName.SetCurSel(sel);
	}

	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("STEP 2: Choose Device Type") == 0)
	{
		pCBox->ShowWindow(SW_HIDE);
		//sprintf(s, "List of Device types:");
		m_editName = CString("List of Device types:");

		m_listName.AddString("1 - Static Device");
		m_listName.AddString("2 - Light");
		m_listName.AddString("3 - Camera");
		m_listName.AddString("4 - Train");
		//m_listName.AddString("2 - Robot (6 dof)");
		//m_listName.AddString("3 - Rotary Table");
		//m_listName.AddString("4 - Gripper");
		//m_listName.AddString("5 - Bar Code Reader");
		//m_listName.AddString("6 - Scale");
		UpdateData(FALSE);

		m_listName.SelectString(0, "1 - Static Device");
	}


	//UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStageChooseDevice::OnOK() 
{
	// TODO: Add extra validation here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CString name;
	CStagePath *ptrPath;
	CStageTag *ptrTag;
	UINT i;
	char s[256];

	if (m_listName.GetCurSel() == LB_ERR)
	{
		return;
	}

	if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Choose Device") == 0)
	{
		m_listName.GetText(m_listName.GetCurSel(), name);
		// strip off trailing *** from invisible devices
		sprintf(s, "%s", LPCSTR(name));
		for (i = strlen(s); s[i - 1] == '*' && i > 0; i--);
		if (i == strlen(s) - 3)
		{
			s[strlen(s) - 4] = '\0';
		}
		pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(s);
		pDoc->m_currentPart = pDoc->m_currentDevice->m_ptrPart;
	}
	if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Choose Path") == 0)
	{
		m_listName.GetText(m_listName.GetCurSel(), name);
		// strip off trailing *** from invisible paths
		sprintf(s, "%s", LPCSTR(name));
		for (i = strlen(s); s[i - 1] == '*' && i > 0; i--);
		if (i == strlen(s) - 3)
		{
			s[strlen(s) - 4] = '\0';
		}
		ptrPath = pDoc->YoPathHashLookup(s);
		pDoc->m_currentTag = ptrPath->m_ptrTag;
	}
	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Attach Device") == 0)
	{
		//m_listName.GetText(m_listName.GetCurSel(), name);
		//pDoc->YoDetachDevice();
		//sprintf(pDoc->m_currentDevice->m_parent, "%s", (char *)LPCSTR(name));
		//pDoc->YoAttachDevice();
	}
	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Choose Part") == 0)
	{
		m_listName.GetText(m_listName.GetCurSel(), name);
		pDoc->m_currentPart = pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(name));
	}
	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Choose Tag") == 0)
	{
		m_listName.GetText(m_listName.GetCurSel(), name);
		sscanf(name, "%d", &i);

		for (ptrTag = pDoc->m_currentTag->m_ptrPath->m_ptrTag;
			ptrTag != NULL;
			ptrTag = ptrTag->m_nextTag)
		{
			if (ptrTag->m_tag == i)
			{
				pDoc->m_currentTag = ptrTag;
				break;
			}
		}	
	}
	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("STEP 2: Choose Device Type") == 0)
	{
		m_listName.GetText(m_listName.GetCurSel(), m_editName);
		UpdateData(FALSE);
	}

	//((CStageView *)pView)->YoRender(YO_RENDER_FULL);
	((CMainFrame *)pMainFrame)->RedrawWindow();

	CDialog::OnOK();
	return;
}
