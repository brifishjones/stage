// StageEyeViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageEyeViewDlg.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageEyeViewDlg dialog


CStageEyeViewDlg::CStageEyeViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStageEyeViewDlg::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageEyeViewDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CStageEyeViewDlg)
	m_editName = _T("");
	//}}AFX_DATA_INIT
}


void CStageEyeViewDlg::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageEyeViewDlg)
	DDX_Control(pDX, IDC_EYE_VIEW_LIST, m_listName);
	DDX_Text(pDX, IDC_EYE_VIEW_NAME, m_editName);
	DDV_MaxChars(pDX, m_editName, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageEyeViewDlg, CDialog)
	//{{AFX_MSG_MAP(CStageEyeViewDlg)
	ON_BN_CLICKED(IDC_EYE_VIEW_DELETE, OnEyeViewDelete)
	ON_BN_CLICKED(IDC_EYE_VIEW_GO_TO, OnEyeViewGoTo)
	ON_BN_CLICKED(IDC_EYE_VIEW_NEW, OnEyeViewNew)
	ON_BN_CLICKED(IDC_EYE_VIEW_RENAME, OnEyeViewRename)
	ON_BN_CLICKED(IDC_EYE_VIEW_SET, OnEyeViewSet)
	ON_EN_CHANGE(IDC_EYE_VIEW_NAME, OnChangeEyeViewName)
	ON_LBN_SELCHANGE(IDC_EYE_VIEW_LIST, OnSelchangeEyeViewList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageEyeViewDlg message handlers

void CStageEyeViewDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}


BOOL CStageEyeViewDlg::YoInitDialog() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	int i;
	int dWidth;
	RECT rect;
	RECT mfRect;
	CREATESTRUCT cs;
	CStageEyeView *ptrEyeView;

	m_init = TRUE;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    cs.cy = ::GetSystemMetrics(SM_CYSCREEN); 
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN); 

	this->GetWindowRect(&rect);
	dWidth = (rect.right - rect.left);
	pMainFrame->GetWindowRect(&mfRect);
	rect.right = YO_MIN(mfRect.right + dWidth, cs.cx);
	rect.left = rect.right - dWidth;
	rect.right -= 3;
	rect.left -= 3;
	//rect.top -= 20;
	//rect.bottom -= 20;
	this->MoveWindow(&rect, TRUE);
	
	m_listName.ResetContent();
	m_editName = "";

	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		for (ptrEyeView = pDoc->m_eyeViewHash[i];
			ptrEyeView != NULL;
			ptrEyeView = ptrEyeView->m_nextHash)
		{
			m_listName.AddString(CString(ptrEyeView->m_name));
		}
	}

	YoUpdateButtons();
	return TRUE;
}

void CStageEyeViewDlg::YoUpdateButtons()
{
	CWnd *pCBox;
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	char s[64];
	int curSel;
	CStageEyeView *ptrEyeView;

	UpdateData(TRUE);
	sprintf(s, "%s", (LPCSTR)m_editName);
	ptrEyeView = pDoc->YoEyeViewHashLookup(s);
	curSel = m_listName.FindString(-1, (LPCTSTR)m_editName);

	pCBox = (CComboBox*)GetDlgItem(IDC_EYE_VIEW_DELETE);
	if (ptrEyeView != NULL)
	{
		pCBox->EnableWindow(TRUE);
	}
	else
	{
		pCBox->EnableWindow(FALSE);
	}

	pCBox = (CComboBox*)GetDlgItem(IDC_EYE_VIEW_GO_TO);
	if (ptrEyeView != NULL)
	{
		pCBox->EnableWindow(TRUE);
	}
	else
	{
		pCBox->EnableWindow(FALSE);
	}

	pCBox = (CComboBox*)GetDlgItem(IDC_EYE_VIEW_SET);
	if (ptrEyeView != NULL)
	{
		pCBox->EnableWindow(TRUE);
	}
	else
	{
		pCBox->EnableWindow(FALSE);
	}

	pCBox = (CComboBox*)GetDlgItem(IDC_EYE_VIEW_RENAME);
	if (m_editName != ""
		&& ptrEyeView == NULL
		&& m_listName.GetCurSel() != LB_ERR)
	{
		pCBox->EnableWindow(TRUE);
	}
	else
	{
		pCBox->EnableWindow(FALSE);
	}

	pCBox = (CComboBox*)GetDlgItem(IDC_EYE_VIEW_NEW);
	if (m_editName != ""
		&& ptrEyeView == NULL)
	{
		pCBox->EnableWindow(TRUE);
	}
	else
	{
		pCBox->EnableWindow(FALSE);
	}

	if (curSel != LB_ERR)
	{
		m_listName.SetCurSel(curSel);
	}


	return;
}

void CStageEyeViewDlg::OnEyeViewDelete() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStageEyeView *ptrEyeView;
	
	ptrEyeView = pDoc->YoEyeViewHashLookup((char *)LPCSTR(m_editName));
	m_listName.DeleteString(m_listName.GetCurSel());
	m_editName = "";
	UpdateData(FALSE);
	delete ptrEyeView;

	m_listName.SetCurSel(-1);
	YoUpdateButtons();
	return;
}

void CStageEyeViewDlg::OnEyeViewGoTo() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStageEyeView *ptrEyeView;
	int i;
	
	ptrEyeView = pDoc->YoEyeViewHashLookup((char *)LPCSTR(m_editName));

	for (i = 0; i < 9; i++)
	{
		((CStageView *)pView)->m_eye[i] = ptrEyeView->m_eye[i];
	}
	pView->m_fieldOfView = ptrEyeView->m_eye[9];
	pView->m_clipFront = ptrEyeView->m_eye[10];
	pView->m_clipRear = ptrEyeView->m_eye[11];

	::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView,
		pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	
    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
	::gluLookAt(pView->m_eye[0],
		pView->m_eye[1],
		pView->m_eye[2],
		pView->m_eye[3], 
		pView->m_eye[4],
		pView->m_eye[5],
		pView->m_eye[6],
		pView->m_eye[7],
		pView->m_eye[8]);

	pMainFrame->YoUpdateEyeDlg();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CStageEyeViewDlg::OnEyeViewNew() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStageEyeView *ptrEyeView;
	int i;

	ptrEyeView = new CStageEyeView(pDoc);

	sprintf(ptrEyeView->m_name, "%s", m_editName);
	for (i = 0; i < 9; i++)
	{
		ptrEyeView->m_eye[i] = pView->m_eye[i];
	}
	ptrEyeView->m_eye[9] = pView->m_fieldOfView;
	ptrEyeView->m_eye[10] = pView->m_clipFront;
	ptrEyeView->m_eye[11] = pView->m_clipRear;

	pDoc->YoEyeViewHashInstall(ptrEyeView);
	m_listName.AddString(m_editName);
	YoUpdateButtons();

	return;
}

void CStageEyeViewDlg::OnEyeViewRename() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStageEyeView *ptrEyeView;
	CStageEyeView *prevEyeView = NULL;
	int i;
	char s[64];

	m_listName.GetText(m_listName.GetCurSel(), s);
	
	if (pDoc->YoDeviceHashLookup((char *)LPCSTR(m_editName)) == NULL)
	{
		// remove the original name from the eye view hash table
		i = (int)pDoc->YoHash(s, YO_HASH_VALUE, YO_HASH_SIZE);
		
		for (ptrEyeView = pDoc->m_eyeViewHash[i];
			ptrEyeView != NULL && strcmp(s, ptrEyeView->m_name) != 0;
			ptrEyeView = ptrEyeView->m_nextHash)
		{
			prevEyeView = ptrEyeView;
		}
		if (prevEyeView == NULL)
		{
			pDoc->m_eyeViewHash[i] = ptrEyeView->m_nextHash;
		}
		else
		{
			prevEyeView->m_nextHash = ptrEyeView->m_nextHash;
		}
		ptrEyeView->m_nextHash = NULL;

		// reinstall new name in eye view hash table
		sprintf(ptrEyeView->m_name, "%s", (char *)LPCSTR(m_editName));
		pDoc->YoEyeViewHashInstall(ptrEyeView);

		m_listName.DeleteString(m_listName.GetCurSel());
		m_listName.AddString(m_editName);
		YoUpdateButtons();
	}

	return;
	
}

void CStageEyeViewDlg::OnEyeViewSet() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStageEyeView *ptrEyeView;
	int i;

	ptrEyeView = pDoc->YoEyeViewHashLookup((char *)LPCSTR(m_editName));

	for (i = 0; i < 9; i++)
	{
		ptrEyeView->m_eye[i] = ((CStageView *)pView)->m_eye[i];
	}
	ptrEyeView->m_eye[9] = pView->m_fieldOfView;
	ptrEyeView->m_eye[10] = pView->m_clipFront;
	ptrEyeView->m_eye[11] = pView->m_clipRear;

	return;	
}

void CStageEyeViewDlg::OnChangeEyeViewName() 
{
	YoUpdateButtons();
	return;
}

void CStageEyeViewDlg::OnSelchangeEyeViewList() 
{
	m_listName.GetText(m_listName.GetCurSel(), m_editName);
	UpdateData(FALSE);
	YoUpdateButtons();
	return;
}

void CStageEyeViewDlg::OnOK() 
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame(); 

	// TODO: Add extra validation here
	pMainFrame->m_eyeViewDlgActive = FALSE;
	CDialog::OnOK();
}
