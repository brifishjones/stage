// StageInheritMaterial.cpp : implementation file
//

#include "stdafx.h"
#include "stage.h"
#include "StageInheritMaterial.h"
#include "StageViewPart.h"
#include "stageDoc.h"
#include "stageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageInheritMaterial dialog


CStageInheritMaterial::CStageInheritMaterial(CWnd* pParent /*=NULL*/)
	: CDialog(CStageInheritMaterial::IDD, pParent)
{
	m_init = FALSE;
	Create(CStageInheritMaterial::IDD, pParent);
	//{{AFX_DATA_INIT(CStageInheritMaterial)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStageInheritMaterial::DoDataExchange(CDataExchange* pDX)
{
	if (m_init == FALSE)
	{
		return;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageInheritMaterial)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageInheritMaterial, CDialog)
	//{{AFX_MSG_MAP(CStageInheritMaterial)
	ON_BN_CLICKED(IDC_INHERIT_PARENT, OnInheritParent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageInheritMaterial message handlers

void CStageInheritMaterial::OnInheritParent() 
{

	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
	CStageDoc *pDoc = pView->GetDocument();
	CStagePart *ptrParent;
	int i;

	if (strcmp(pDoc->m_currentPart->m_partParent, "NULL") == 0)
	{
		return;
	}

	ptrParent = pDoc->YoPartLookup(pDoc->m_currentDevice, pDoc->m_currentPart->m_partParent);
	if (ptrParent == NULL)
	{
		return;
	}

	for (i = 0; i < 4; i++)
	{
		pDoc->m_currentPart->m_ambient[i] = ptrParent->m_ambient[i];
		pDoc->m_currentPart->m_diffuse[i] = ptrParent->m_diffuse[i];
		pDoc->m_currentPart->m_specular[i] = ptrParent->m_specular[i];
		pDoc->m_currentPart->m_emission[i] = ptrParent->m_emission[i];
		pDoc->m_currentPart->m_wireframe[i] = ptrParent->m_wireframe[i];

		((CMainFrame *)pMainFrame)->m_viewPart->m_ambient[i]
			= (UINT)(pDoc->m_currentPart->m_ambient[i] * 255.0);
		((CMainFrame *)pMainFrame)->m_viewPart->m_diffuse[i]
			= (UINT)(pDoc->m_currentPart->m_diffuse[i] * 255.0);
		((CMainFrame *)pMainFrame)->m_viewPart->m_specular[i]
			= (UINT)(pDoc->m_currentPart->m_specular[i] * 255.0);
		((CMainFrame *)pMainFrame)->m_viewPart->m_emission[i]
			= (UINT)(pDoc->m_currentPart->m_emission[i] * 255.0);
		((CMainFrame *)pMainFrame)->m_viewPart->m_wireframe[i]
			= (UINT)(pDoc->m_currentPart->m_wireframe[i] * 255.0);
	}

	if (((CMainFrame *)pMainFrame)->m_viewPart->m_partMaterial.GetCurSel() == 0)  // ambient
	{
		((CMainFrame *)pMainFrame)->m_viewPart->m_partRed
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_ambient[0];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partGreen
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_ambient[1];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partBlue
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_ambient[2];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partAlpha
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_ambient[3];
	}
	else if (((CMainFrame *)pMainFrame)->m_viewPart->m_partMaterial.GetCurSel() == 1)  // diffuse
	{
		((CMainFrame *)pMainFrame)->m_viewPart->m_partRed
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_diffuse[0];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partGreen
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_diffuse[1];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partBlue
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_diffuse[2];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partAlpha
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_diffuse[3];
	}
	else if (((CMainFrame *)pMainFrame)->m_viewPart->m_partMaterial.GetCurSel() == 2)  // emission
	{
		((CMainFrame *)pMainFrame)->m_viewPart->m_partRed
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_emission[0];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partGreen
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_emission[1];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partBlue
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_emission[2];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partAlpha
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_emission[3];
	}
	else if (((CMainFrame *)pMainFrame)->m_viewPart->m_partMaterial.GetCurSel() == 3)  // specular
	{
		((CMainFrame *)pMainFrame)->m_viewPart->m_partRed
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_specular[0];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partGreen
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_specular[1];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partBlue
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_specular[2];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partAlpha
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_specular[3];
	}
	else if (((CMainFrame *)pMainFrame)->m_viewPart->m_partMaterial.GetCurSel() == 4)  // wireframe
	{
		((CMainFrame *)pMainFrame)->m_viewPart->m_partRed
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_wireframe[0];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partGreen
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_wireframe[1];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partBlue
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_wireframe[2];
		((CMainFrame *)pMainFrame)->m_viewPart->m_partAlpha
			= ((CMainFrame *)pMainFrame)->m_viewPart->m_wireframe[3];
	}

	pDoc->m_currentPart->m_shininess = ptrParent->m_shininess;
	((CMainFrame *)pMainFrame)->m_viewPart->m_partShininess = (UINT)pDoc->m_currentPart->m_shininess;
	UpdateData(FALSE);

	((CMainFrame *)pMainFrame)->m_viewPart->m_partSliderRed.SetPos(((CMainFrame *)pMainFrame)->m_viewPart->m_partRed);
	((CMainFrame *)pMainFrame)->m_viewPart->m_partSliderGreen.SetPos(((CMainFrame *)pMainFrame)->m_viewPart->m_partGreen);
	((CMainFrame *)pMainFrame)->m_viewPart->m_partSliderBlue.SetPos(((CMainFrame *)pMainFrame)->m_viewPart->m_partBlue);
	((CMainFrame *)pMainFrame)->m_viewPart->m_partSliderAlpha.SetPos(((CMainFrame *)pMainFrame)->m_viewPart->m_partAlpha);
	((CMainFrame *)pMainFrame)->m_viewPart->m_partSliderShininess.SetPos(((CMainFrame *)pMainFrame)->m_viewPart->m_partShininess);

	pView->YoRender(YO_RENDER_FULL);
	
}

void CStageInheritMaterial::OnCancel() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	int i;

	// TODO: Add extra cleanup here
	SetClassLong(((CStageView *)pView)->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);
	((CMainFrame *)pMainFrame)->m_viewPart->m_inheritingMaterial = FALSE;
	((CMainFrame *)pMainFrame)->m_viewPart->m_selectingAltOrigin = FALSE;
	((CMainFrame *)pMainFrame)->m_viewPart->m_snapTo = FALSE;

	for (i = 0; i < 4; i++)
	{
		pDoc->m_currentPart->m_ambient[i] = m_origAmbient[i];
		pDoc->m_currentPart->m_diffuse[i] = m_origDiffuse[i];
		pDoc->m_currentPart->m_specular[i] = m_origSpecular[i];
		pDoc->m_currentPart->m_emission[i] = m_origEmission[i];
		pDoc->m_currentPart->m_wireframe[i] = m_origWireframe[i];
	}
	pDoc->m_currentPart->m_shininess = m_origShininess;
	pDoc->m_currentPart->m_renderMode = m_origRenderMode;
	
	CDialog::OnCancel();
	DestroyWindow();
	((CStageView *)pView)->YoRender(YO_RENDER_FULL);

}

void CStageInheritMaterial::OnOK() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();

	// TODO: Add extra validation here
	SetClassLong(((CStageView *)pView)->m_hWnd, GCL_HCURSOR, (long)((CMainFrame *)pMainFrame)->m_hCursorArrow);
	((CMainFrame *)pMainFrame)->m_viewPart->m_inheritingMaterial = FALSE;
	((CMainFrame *)pMainFrame)->m_viewPart->m_selectingAltOrigin = FALSE;
	((CMainFrame *)pMainFrame)->m_viewPart->m_snapTo = FALSE;

	CDialog::OnOK();
	DestroyWindow();
}


BOOL CStageInheritMaterial::YoInitDialog() 
{
	CWnd* pCBox;
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	int i;
	int dWidth;
	int dHeight;
	RECT rect;
	RECT mfRect;
	CREATESTRUCT cs;

	m_init = TRUE;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    cs.cy = ::GetSystemMetrics(SM_CYSCREEN); 
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN); 

	this->GetWindowRect(&rect);
	dWidth = (rect.right - rect.left);
	dHeight = (rect.bottom - rect.top);
	((CMainFrame *)pMainFrame)->m_viewPart->GetWindowRect(&mfRect);

	rect.right = YO_MIN(mfRect.left + dWidth + 5, cs.cx);
	rect.left = rect.right - dWidth;
	rect.top = mfRect.top + 125;
	rect.bottom = mfRect.top + 125 + dHeight;

	this->MoveWindow(&rect, TRUE);


	for (i = 0; i < 4; i++)
	{
		m_origAmbient[i] = pDoc->m_currentPart->m_ambient[i];
		m_origDiffuse[i] = pDoc->m_currentPart->m_diffuse[i];
		m_origSpecular[i] = pDoc->m_currentPart->m_specular[i];
		m_origEmission[i] = pDoc->m_currentPart->m_emission[i];
		m_origWireframe[i] = pDoc->m_currentPart->m_wireframe[i];
	}
	m_origShininess = pDoc->m_currentPart->m_shininess;
	m_origRenderMode = pDoc->m_currentPart->m_renderMode;

	if (strcmp(pDoc->m_currentPart->m_partParent, "NONE") == 0)
	{
		pCBox = (CComboBox*)GetDlgItem(IDC_INHERIT_PARENT);
		pCBox->EnableWindow(FALSE);	
	}

	return TRUE;
}

void CStageInheritMaterial::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
}
