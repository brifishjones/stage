// StageChooseName.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageChooseName.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageChooseName dialog


CStageChooseName::CStageChooseName(CWnd* pParent /*=NULL*/)
	: CDialog(CStageChooseName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStageChooseName)
	m_editName = _T("");
	//}}AFX_DATA_INIT
}


void CStageChooseName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageChooseName)
	DDX_Control(pDX, IDC_LIST_NAME, m_listName);
	DDX_Text(pDX, IDC_EDIT_NAME, m_editName);
	DDV_MaxChars(pDX, m_editName, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageChooseName, CDialog)
	//{{AFX_MSG_MAP(CStageChooseName)
	ON_LBN_SELCHANGE(IDC_LIST_NAME, OnSelchangeListName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageChooseName message handlers

BOOL CStageChooseName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();

	CStageDevice *ptrDevice;
	CStagePart *ptrPart;
	CStagePart *currentPart;
	CStagePath *ptrPath;
	int i;

	m_listName.ResetContent();
	((CWnd *)this)->SetWindowText(((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle);

	if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Rename Device") == 0)
	{
		m_editName = CString(pDoc->m_currentDevice->m_name);
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			for (ptrDevice = pDoc->m_deviceHash[i];
				ptrDevice != NULL;
				ptrDevice = ptrDevice->m_nextHash)
			{
				m_listName.AddString(CString(ptrDevice->m_name));
			}
		}
	}

	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Clone Device") == 0)
	{
		m_editName = CString(pDoc->m_currentDevice->m_name);
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			for (ptrDevice = pDoc->m_deviceHash[i];
				ptrDevice != NULL;
				ptrDevice = ptrDevice->m_nextHash)
			{
				m_listName.AddString(CString(ptrDevice->m_name));
			}
		}
	}

	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Rename Part") == 0)
	{
		m_editName = CString(pDoc->m_currentPart->m_partName);

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
		}
		while (pDoc->YoPopPart() != NULL);
	}
	
	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("STEP 1: Create Device") == 0
		|| ((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("STEP 1: Import Device") == 0)
	{
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			for (ptrDevice = pDoc->m_deviceHash[i];
				ptrDevice != NULL;
				ptrDevice = ptrDevice->m_nextHash)
			{
				m_listName.AddString(CString(ptrDevice->m_name));
			}
		}
	}
	
	/***
	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Rename Part") == 0)
	{
		m_editName = CString(pDoc->m_currentPart->m_partName);
		pDoc->m_partStack = NULL;
		ptrPart = pDoc->m_currentDevice->m_ptrPart;
		while (ptrPart != NULL)
		{
			m_listName.AddString(CString(ptrPart->m_partName));
			if (ptrPart->m_down != NULL)
			{
				if (ptrPart->m_right != NULL)
				{
					pDoc->YoPushPart(ptrPart->m_right);
				}
				ptrPart = ptrPart->m_down;
			}
			else if (ptrPart->m_right != NULL)
			{
				ptrPart = ptrPart->m_right;
			}
			else if (pDoc->m_partStack != NULL)
			{
				ptrPart = pDoc->YoPopPart();
			}
			else 
			{
				ptrPart = NULL; 
			}
		}
	}
	**/

	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Create Path") == 0)
	{
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			for (ptrPath = pDoc->m_pathHash[i];
				ptrPath != NULL;
				ptrPath = ptrPath->m_nextHash)
			{
				m_listName.AddString(CString(ptrPath->m_name));
			}
		}
	}

	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Rename Path") == 0)
	{
		m_editName = CString(pDoc->m_currentTag->m_ptrPath->m_name);
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			for (ptrPath = pDoc->m_pathHash[i];
				ptrPath != NULL;
				ptrPath = ptrPath->m_nextHash)
			{
				m_listName.AddString(CString(ptrPath->m_name));
			}
		}
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStageChooseName::OnOK() 
{
	// TODO: Add extra validation here
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	CStageDevice *ptrDevice;
	CStageDevice *prevDevice = NULL;
	CStagePath *ptrPath;
	CStagePath *prevPath = NULL;
	CStagePart *curPart;
	BOOL done = FALSE;
	int i;
	char s[128];

	UpdateData(TRUE);

	if (strcmp((char *)LPCSTR(m_editName), "") == 0)
	{
		return;
	}

	if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Rename Device") == 0)
	{
		if (pDoc->YoDeviceHashLookup((char *)LPCSTR(m_editName)) == NULL)
		{
			// remove the original name from the device hash table
			i = (int)pDoc->YoHash(pDoc->m_currentDevice->m_name, YO_HASH_VALUE, YO_HASH_SIZE);
			
			for (ptrDevice = pDoc->m_deviceHash[i];
				ptrDevice != NULL && strcmp(pDoc->m_currentDevice->m_name, ptrDevice->m_name) != 0;
				ptrDevice = ptrDevice->m_nextHash)
			{
				prevDevice = ptrDevice;
			}
			if (prevDevice == NULL)
			{
				pDoc->m_deviceHash[i] = ptrDevice->m_nextHash;
			}
			else
			{
				prevDevice->m_nextHash = ptrDevice->m_nextHash;
			}
			ptrDevice->m_nextHash = NULL;

		/***	
			for (ptrDevice = pDoc->m_deviceHash[i];
				(strcmp(pDoc->m_currentDevice->m_name, ptrDevice->m_name) != 0)
				|| (ptrDevice->m_nextHash != NULL
				&& (strcmp(pDoc->m_currentDevice->m_name, ptrDevice->m_nextHash->m_name) != 0));
				ptrDevice = ptrDevice->m_nextHash);
			if (ptrDevice == pDoc->m_deviceHash[i]
				&& strcmp(pDoc->m_currentDevice->m_name, ptrDevice->m_name) == 0)
			{
				pDoc->m_deviceHash[i] = ptrDevice->m_nextHash;
				ptrDevice->m_nextHash = NULL;
			}
			else
			{
				ptrDevice->m_nextHash = ptrDevice->m_nextHash->m_nextHash;
				ptrDevice->m_nextHash->m_nextHash = NULL;
			}
		***/

			// reinstall new name in device hash table
			sprintf(pDoc->m_currentDevice->m_name, "%s", (char *)LPCSTR(m_editName));
			pDoc->YoDeviceHashInstall(pDoc->m_currentDevice);

			if (((CMainFrame *)pMainFrame)->m_viewPartActive == TRUE)
			{
				sprintf(s, "%s  -  %s", pDoc->m_currentDevice->m_name,
					pDoc->m_currentPart->m_partName);
				((CWnd *)((CMainFrame *)pMainFrame)->m_viewPart)->SetWindowText((LPCTSTR)s);
			}

			// update all parts with new device name
			pDoc->m_partStack = NULL;
			curPart = pDoc->m_currentDevice->m_ptrPart;
			while (done == FALSE)
			{
				sprintf(curPart->m_deviceName, "%s", pDoc->m_currentDevice->m_name);

				if (curPart->m_down != NULL)
				{
					if (curPart->m_right != NULL)
					{
						pDoc->YoPushPart(curPart->m_right);
					}
					curPart = curPart->m_down;
				}
				else if (curPart->m_right != NULL)
				{
					curPart = curPart->m_right;
				}
				else if (pDoc->m_partStack != NULL)
				{
					curPart = pDoc->YoPopPart();
				}
				else 
				{
					done = TRUE;
				}

			}  //end while (!done)
			while (pDoc->YoPopPart() != NULL);

			// if the renamed device has children, then update with new name
			for (ptrDevice = pDoc->m_currentDevice->m_down; ptrDevice != NULL; ptrDevice = ptrDevice->m_right)
			{
				sprintf(ptrDevice->m_parent, "%s", pDoc->m_currentDevice->m_name);
			}
		}
	}

	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Clone Device") == 0)
	{
		if (pDoc->YoDeviceHashLookup((char *)LPCSTR(m_editName)) != NULL)
		{
			sprintf(s, "%s", (char *)LPCSTR(m_editName));
			pDoc->YoGetUniqueDeviceName(s);
			m_editName = s;
		}
		pDoc->YoCloneDevice((char *)LPCSTR(m_editName));
	}

	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("STEP 1: Create Device") == 0
		|| ((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("STEP 1: Import Device") == 0)
	{
		if (pDoc->YoDeviceHashLookup((char *)LPCSTR(m_editName)) != NULL)
		{
			sprintf(s, "%s", (char *)LPCSTR(m_editName));
			pDoc->YoGetUniqueDeviceName(s);
			m_editName = s;
		}
	}
	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Rename Part") == 0)
	{
		if (pDoc->YoPartLookup(pDoc->m_currentDevice, (char *)LPCSTR(m_editName)) == NULL)
		{
			sprintf(pDoc->m_currentPart->m_partName, "%s", (char *)LPCSTR(m_editName));
			if (((CMainFrame *)pMainFrame)->m_viewPartActive == TRUE)
			{
				sprintf(s, "%s  -  %s", pDoc->m_currentDevice->m_name,
					pDoc->m_currentPart->m_partName);
				((CWnd *)((CMainFrame *)pMainFrame)->m_viewPart)->SetWindowText((LPCTSTR)s);

			}
			// if the renamed part has children, then update with new name
			for (curPart = pDoc->m_currentPart->m_down; curPart != NULL; curPart = curPart->m_right)
			{
				sprintf(curPart->m_partParent, "%s", pDoc->m_currentPart->m_partName);
			}
		}
	}

	else if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Create Path") == 0)
	{
		if (pDoc->YoPathHashLookup((char *)LPCSTR(m_editName)) != NULL)
		{
			sprintf(s, "%s", (char *)LPCSTR(m_editName));
			pDoc->YoGetUniquePathName(s);
			m_editName = s;
		}
	}

	if (((CMainFrame *)pMainFrame)->m_dialogChooseNameTitle.Compare("Rename Path") == 0)
	{
		if (pDoc->YoPathHashLookup((char *)LPCSTR(m_editName)) == NULL)
		{
			// remove the original name from the path hash table
			i = (int)pDoc->YoHash(pDoc->m_currentTag->m_ptrPath->m_name, YO_HASH_VALUE, YO_HASH_SIZE);
			
			for (ptrPath = pDoc->m_pathHash[i];
				ptrPath != NULL && strcmp(pDoc->m_currentTag->m_ptrPath->m_name, ptrPath->m_name) != 0;
				ptrPath = ptrPath->m_nextHash)
			{
				prevPath = ptrPath;
			}
			if (prevPath == NULL)
			{
				pDoc->m_pathHash[i] = ptrPath->m_nextHash;
			}
			else
			{
				prevPath->m_nextHash = ptrPath->m_nextHash;
			}
			ptrPath->m_nextHash = NULL;

			// reinstall new name in path hash table
			sprintf(pDoc->m_currentTag->m_ptrPath->m_name, "%s", (char *)LPCSTR(m_editName));
			pDoc->YoPathHashInstall(pDoc->m_currentTag->m_ptrPath);

			if (((CMainFrame *)pMainFrame)->m_viewTagActive == TRUE)
			{
				sprintf(s, "%s  -  %d", pDoc->m_currentTag->m_ptrPath->m_name,
					pDoc->m_currentTag->m_tag);
				((CWnd *)((CMainFrame *)pMainFrame)->m_viewTag)->SetWindowText((LPCTSTR)s);
			}
		}
	}
	
	CDialog::OnOK();
	return;
}

void CStageChooseName::OnSelchangeListName() 
{
	// TODO: Add your control notification handler code here
	m_listName.GetText(m_listName.GetCurSel(), m_editName);
	UpdateData(FALSE);
	return;
	
}
