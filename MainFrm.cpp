// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "stage.h"

#include "stageDoc.h"
#include "stageView.h"

#include "StagePrefsRender.h"
#include "StagePrefsGrid.h"
#include "StagePrefsLighting.h"
#include "StagePrefsNetwork.h"
#include "StagePrefsUnits.h"
#include "StageDeviceTree.h"
#include "StageMotionViewHistory.h"
#include "StagePartMotion.h"
#include "StageChooseName.h"
#include "StageChooseDevice.h"
#include "StageLightDialog.h"
#include "StageRobot6Dlg.h"
#include "StageRotaryTableDlg.h"
#include "StageConveyorDlg.h"
#include "StageCameraDlg.h"
#include "StageGripperDlg.h"
#include "StageBarCodeReaderDlg.h"
#include "StageBarrettHandDlg.h"
#include "StageScaleDlg.h"
#include "StageTrainDlg.h"
#include "StageTrackDlg.h"
#include "StageViewPart.h"
#include "StageViewTag.h"
#include "StageSizeCustom.h"
//#include "StageViewLightPart.h"
//#include "StageDeviceTransformation.h"
#include "StageEyeDialog.h"
#include "StageScriptDlg.h"
#include "StageAnalysisDlg.h"
#include "StageEyeViewDlg.h"
//#include "StageTopDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_PREFS, OnPrefs)
	ON_COMMAND(ID_VIEW_DEVICE_TREE, OnViewDeviceTree)
	ON_COMMAND(ID_MOTION_INSERT_ANCHOR, OnMotionInsertAnchor)
	ON_COMMAND(ID_MOTION_INSERT_HOLD, OnMotionInsertHold)
	ON_COMMAND(ID_MOTION_VIEW_HISTORY, OnMotionViewHistory)
	ON_COMMAND(ID_VIEW_CURRENT_PART, OnViewCurrentPart)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CURRENT_PART, OnUpdateViewCurrentPart)
	ON_COMMAND(ID_DEVICE_ATTACH, OnDeviceAttach)
	ON_COMMAND(ID_DEVICE_CHOOSE, OnDeviceChoose)
	ON_COMMAND(ID_DEVICE_CLONE, OnDeviceClone)
	ON_COMMAND(ID_DEVICE_DETACH, OnDeviceDetach)
	ON_COMMAND(ID_DEVICE_RENAME, OnDeviceRename)
	ON_COMMAND(ID_DEVICE_DELETE, OnDeviceDelete)
	ON_WM_MOVE()
	ON_COMMAND(ID_SIZE_320X240, OnSize320x240)
	ON_COMMAND(ID_SIZE_640X480, OnSize640x480)
	ON_WM_SIZE()
	ON_COMMAND(ID_MOTION_INSERT_PART_ANCHOR, OnMotionInsertPartAnchor)
	ON_COMMAND(ID_MOTION_INSERT_PART_HOLD, OnMotionInsertPartHold)
	ON_COMMAND(ID_MOTION_VIEW_PART_HISTORY, OnMotionViewPartHistory)
	ON_UPDATE_COMMAND_UI(ID_DEVICE_ATTACH, OnUpdateDeviceAttach)
	ON_UPDATE_COMMAND_UI(ID_DEVICE_CHOOSE, OnUpdateDeviceChoose)
	ON_UPDATE_COMMAND_UI(ID_DEVICE_CLONE, OnUpdateDeviceClone)
	ON_UPDATE_COMMAND_UI(ID_DEVICE_DELETE, OnUpdateDeviceDelete)
	ON_UPDATE_COMMAND_UI(ID_DEVICE_DETACH, OnUpdateDeviceDetach)
	ON_UPDATE_COMMAND_UI(ID_DEVICE_RENAME, OnUpdateDeviceRename)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_COPY_AS, OnUpdateFileSaveCopyAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_UPDATE, OnUpdateFileUpdate)
	ON_UPDATE_COMMAND_UI(ID_MOTION_INSERT_ANCHOR, OnUpdateMotionInsertAnchor)
	ON_UPDATE_COMMAND_UI(ID_MOTION_INSERT_HOLD, OnUpdateMotionInsertHold)
	ON_UPDATE_COMMAND_UI(ID_MOTION_INSERT_PART_ANCHOR, OnUpdateMotionInsertPartAnchor)
	ON_UPDATE_COMMAND_UI(ID_MOTION_INSERT_PART_HOLD, OnUpdateMotionInsertPartHold)
	ON_UPDATE_COMMAND_UI(ID_MOTION_VIEW_HISTORY, OnUpdateMotionViewHistory)
	ON_UPDATE_COMMAND_UI(ID_MOTION_VIEW_PART_HISTORY, OnUpdateMotionViewPartHistory)
	ON_UPDATE_COMMAND_UI(ID_PREFS, OnUpdatePrefs)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DEVICE_TREE, OnUpdateViewDeviceTree)
	ON_COMMAND(ID_DEVICE_CREATE, OnDeviceCreate)
	ON_UPDATE_COMMAND_UI(ID_DEVICE_CREATE, OnUpdateDeviceCreate)
	ON_COMMAND(ID_PART_ATTACH, OnPartAttach)
	ON_UPDATE_COMMAND_UI(ID_PART_ATTACH, OnUpdatePartAttach)
	ON_COMMAND(ID_PART_CHOOSE, OnPartChoose)
	ON_UPDATE_COMMAND_UI(ID_PART_CHOOSE, OnUpdatePartChoose)
	ON_COMMAND(ID_PART_DELETE, OnPartDelete)
	ON_UPDATE_COMMAND_UI(ID_PART_DELETE, OnUpdatePartDelete)
	ON_COMMAND(ID_PART_RENAME, OnPartRename)
	ON_UPDATE_COMMAND_UI(ID_PART_RENAME, OnUpdatePartRename)
	ON_COMMAND(ID_PART_UPDATE, OnPartUpdate)
	ON_UPDATE_COMMAND_UI(ID_PART_UPDATE, OnUpdatePartUpdate)
	ON_COMMAND(ID_HELP_ANALYSIS, OnHelpAnalysis)
	ON_UPDATE_COMMAND_UI(ID_HELP_ANALYSIS, OnUpdateHelpAnalysis)
	ON_COMMAND(ID_TAG_CHOOSE, OnTagChoose)
	ON_COMMAND(ID_TAG_CREATE, OnTagCreate)
	ON_COMMAND(ID_TAG_DELETE, OnTagDelete)
	ON_COMMAND(ID_TAG_DELETE_PATH, OnTagDeletePath)
	ON_COMMAND(ID_TAG_NEW_PATH, OnTagNewPath)
	ON_COMMAND(ID_TAG_REATTACH_PATH, OnTagReattachPath)
	ON_COMMAND(ID_TAG_RENAME_PATH, OnTagRenamePath)
	ON_COMMAND(ID_TAG_TAG_ON_TCF, OnTagTagOnTcf)
	ON_COMMAND(ID_VIEW_CURRENT_TAG, OnViewCurrentTag)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CURRENT_TAG, OnUpdateViewCurrentTag)
	ON_UPDATE_COMMAND_UI(ID_TAG_CHOOSE, OnUpdateTagChoose)
	ON_UPDATE_COMMAND_UI(ID_TAG_CREATE, OnUpdateTagCreate)
	ON_UPDATE_COMMAND_UI(ID_TAG_DELETE, OnUpdateTagDelete)
	ON_UPDATE_COMMAND_UI(ID_TAG_DELETE_PATH, OnUpdateTagDeletePath)
	ON_UPDATE_COMMAND_UI(ID_TAG_NEW_PATH, OnUpdateTagNewPath)
	ON_UPDATE_COMMAND_UI(ID_TAG_REATTACH_PATH, OnUpdateTagReattachPath)
	ON_UPDATE_COMMAND_UI(ID_TAG_RENAME_PATH, OnUpdateTagRenamePath)
	ON_UPDATE_COMMAND_UI(ID_TAG_TAG_ON_TCF, OnUpdateTagTagOnTcf)
	ON_COMMAND(ID_DEVICE_IMPORT, OnDeviceImport)
	ON_UPDATE_COMMAND_UI(ID_DEVICE_IMPORT, OnUpdateDeviceImport)
	ON_COMMAND(ID_VIEW_EYE_INFO, OnViewEyeInfo)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EYE_INFO, OnUpdateViewEyeInfo)
	ON_COMMAND(ID_FILE_REVERT, OnFileRevert)
	ON_UPDATE_COMMAND_UI(ID_FILE_REVERT, OnUpdateFileRevert)
	ON_COMMAND(ID_DEVICE_EXPORT, OnDeviceExport)
	ON_UPDATE_COMMAND_UI(ID_DEVICE_EXPORT, OnUpdateDeviceExport)
	ON_UPDATE_COMMAND_UI(ID_APP_ABOUT, OnUpdateAppAbout)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_TAG_CHOOSE_PATH, OnTagChoosePath)
	ON_UPDATE_COMMAND_UI(ID_TAG_CHOOSE_PATH, OnUpdateTagChoosePath)
	ON_COMMAND(ID_SIZE_CUSTOM, OnSizeCustom)
	ON_COMMAND(ID_SIZE_720X480, OnSize720x480)
	ON_UPDATE_COMMAND_UI(ID_SIZE_320X240, OnUpdateSize320x240)
	ON_UPDATE_COMMAND_UI(ID_SIZE_640X480, OnUpdateSize640x480)
	ON_UPDATE_COMMAND_UI(ID_SIZE_720X480, OnUpdateSize720x480)
	ON_UPDATE_COMMAND_UI(ID_SIZE_CUSTOM, OnUpdateSizeCustom)
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDC_WALK, OnModeWalk)
	ON_COMMAND(IDC_PAN, OnModePan)
	ON_COMMAND(IDC_DEVICE_TRANSLATE, OnModeDeviceTranslate)
	ON_COMMAND(IDC_SCRIPT, OnModeScript)
	ON_COMMAND(IDC_EYE, OnModeEye)
	ON_COMMAND(IDC_RECORD, OnModeRecordSim)
	ON_COMMAND(IDC_SOCKET, OnModeSocket)
	//ON_COMMAND(IDC_PLAY, OnPlay)
	//ON_COMMAND(IDC_PAUSE, OnPause)
	//ON_COMMAND(IDC_REWIND, OnRewind)
	//ON_COMMAND(IDC_IMMEDIATE_MODE, OnImmediateMode)
	//ON_EN_KILLFOCUS(IDC_MINUTES, OnUpdateTime)
	//ON_EN_KILLFOCUS(IDC_SECONDS, OnUpdateTime)
	//ON_EN_KILLFOCUS(IDC_FRAMES, OnUpdateTime)
	//ON_TB_THUMBTRACK(IDC_TIME, OnUpdateTime)
	//ON_EN_UPDATE(IDC_TIME, OnUpdateTime)
	//ON_UPDATE_COMMAND_UI(IDC_TIME, YoSetCurrentTime)
	//ON_UPDATE_COMMAND_UI(IDC_PLAY, OnUpdatePlayUI)
	//ON_UPDATE_COMMAND_UI(IDC_PAUSE, OnUpdatePauseUI)
	//ON_UPDATE_COMMAND_UI(IDC_REWIND, OnUpdateRewindUI)
	//ON_UPDATE_COMMAND_UI(IDC_TIME, OnUpdateTimeUI)
	//ON_UPDATE_COMMAND_UI(IDC_MINUTES, OnUpdateMinutesUI)
	//ON_UPDATE_COMMAND_UI(IDC_SECONDS, OnUpdateSecondsUI)
	//ON_UPDATE_COMMAND_UI(IDC_FRAMES, OnUpdateFramesUI)
	ON_UPDATE_COMMAND_UI(IDC_DEVICE_TRANSLATE, OnUpdateDeviceTranslateUI)
	ON_UPDATE_COMMAND_UI(IDC_WALK, OnUpdateWalkUI)
	ON_UPDATE_COMMAND_UI(IDC_PAN, OnUpdatePanUI)
	ON_UPDATE_COMMAND_UI(IDC_SCRIPT, OnUpdateScriptUI)
	ON_UPDATE_COMMAND_UI(IDC_EYE, OnUpdateEyeUI)
	ON_UPDATE_COMMAND_UI(IDC_RECORD, OnUpdateRecordSimUI)
	ON_UPDATE_COMMAND_UI(IDC_SOCKET, OnUpdateSocketUI)
	//ON_UPDATE_COMMAND_UI(IDC_IMMEDIATE_MODE, OnUpdateImmediateModeUI)
	// Device Transformations
//	ON_EN_SETFOCUS(IDC_SLIDER_FOV, OnUpdateSliderFieldOfView)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_init = FALSE;
	TRACE0("CMainFrame::CMainFrame()\n");
	
}

CMainFrame::~CMainFrame()
{
	TRACE0("CMainFrame::~CMainFrame()\n");
	// return system parameters to their original configuration
	CONST INT lpaElements[] = {COLOR_WINDOW, COLOR_BTNFACE, COLOR_HIGHLIGHT, COLOR_BTNTEXT,
		COLOR_HIGHLIGHTTEXT, COLOR_CAPTIONTEXT, COLOR_MENU, COLOR_MENUTEXT, COLOR_ACTIVECAPTION};
	CONST COLORREF lpaRgbValues[]
		= {m_colorWindow, m_colorBtnFace, m_colorHighLight, m_colorBtnText, 
		m_colorHighLightText, m_colorCaptionText, m_colorMenu, m_colorMenuText, m_colorActiveCaption};
	::SetSysColors(9, lpaElements, lpaRgbValues);

	return;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CWnd *pCBox;

	TRACE3("GL_DECAL = %d       GL_MODULATE = %d       GL_BLEND = %d\n",
		GL_DECAL, GL_MODULATE, GL_BLEND);

	// set system colors to match stage GUI
	m_colorWindow = ::GetSysColor(COLOR_WINDOW);
	m_colorBtnFace = ::GetSysColor(COLOR_BTNFACE);
	m_colorHighLight = ::GetSysColor(COLOR_HIGHLIGHT);
	m_colorBtnText = ::GetSysColor(COLOR_BTNTEXT);
	m_colorHighLightText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_colorCaptionText = ::GetSysColor(COLOR_CAPTIONTEXT);
	m_colorMenu = ::GetSysColor(COLOR_MENU);
	m_colorMenuText = ::GetSysColor(COLOR_MENUTEXT);
	m_colorActiveCaption = ::GetSysColor(COLOR_ACTIVECAPTION);

	CONST INT lpaElements[] = {COLOR_WINDOW, COLOR_BTNFACE, COLOR_HIGHLIGHT, COLOR_BTNTEXT,
		COLOR_HIGHLIGHTTEXT, COLOR_CAPTIONTEXT, COLOR_MENU, COLOR_MENUTEXT, COLOR_ACTIVECAPTION};
	CONST COLORREF lpaRgbValues[]
		= {RGB(231, 231, 214), RGB(192, 192, 192), RGB(102, 102, 153), RGB(57, 57, 57), 
		RGB(192, 220, 192), RGB(255, 255, 255), RGB(192, 192, 192), RGB(57, 57, 57), RGB(102, 102, 153)};
	::SetSysColors(9, lpaElements, lpaRgbValues);

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	m_init = TRUE;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndDlgBarTop.Create(this, IDD_STAGE_TOP,
		CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY, IDD_STAGE_TOP))  
	{
		TRACE0("Failed to create top dialog bar\n");
		return -1;      // fail to create
	}
	//CWnd* pButton = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_PAUSE_PLAY);
	//((CButton *)pButton)->SetState(TRUE);

	if (!m_wndDlgBarLeft.Create(this, IDD_STAGE_LEFT,
		CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY, IDD_STAGE_LEFT))
	{
		TRACE0("Failed to create left dialog bar\n");
		return -1;      // fail to create
	}

	//CDC *pDC;
	//pDC = m_wndDlgBarTop.GetDC();
	//pDC->SetBkColor(0x008888);
	//m_wndDlgBarTop.ReleaseDC(pDC);

	//pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_WALK);
	//((CButton *)pCBox)->SetCheck(1);

	pCBox = (CComboBox*)m_wndDlgBarTop.GetDlgItem(IDC_REWIND);
	m_bmRewind.LoadBitmap(IDB_REWIND24);
	m_bmRewindHL.LoadBitmap(IDB_REWIND24_HL);
	//YoTransparentBitmap(&m_bmRewind, 0xff0000);
	((CStatic *)pCBox)->SetBitmap((HBITMAP)m_bmRewind);

	pCBox = (CComboBox*)m_wndDlgBarTop.GetDlgItem(IDC_PAUSE);
	m_bmPause.LoadBitmap(IDB_PAUSE24);
	m_bmPauseHL.LoadBitmap(IDB_PAUSE24_HL);
	((CStatic *)pCBox)->SetBitmap((HBITMAP)m_bmPause);

	pCBox = (CComboBox*)m_wndDlgBarTop.GetDlgItem(IDC_PLAY);
	m_bmPlay.LoadBitmap(IDB_PLAY24);
	m_bmPlayHL.LoadBitmap(IDB_PLAY24_HL);
	((CStatic *)pCBox)->SetBitmap((HBITMAP)m_bmPlay);

	//pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_SOCKET);
	//m_bmCircleRed.LoadBitmap(IDB_CIRCLE_RED);
	//YoTransparentBitmap(&m_bmCircleRed, 0xff0000);
	//m_bmCircleYellow.LoadBitmap(IDB_CIRCLE_YELLOW);
	//YoTransparentBitmap(&m_bmCircleYellow, 0xff0000);
	//m_bmCircleGreen.LoadBitmap(IDB_CIRCLE_GREEN);
	//YoTransparentBitmap(&m_bmCircleGreen, 0xff0000);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmCircleRed);

	//pCBox = (CComboBox*)m_wndDlgBarTop.GetDlgItem(IDC_IMMEDIATE_MODE);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmCircleRed);

	//pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_WALK);
	//m_bmWalk.LoadBitmap(IDB_WALK);
	//YoTransparentBitmap(&m_bmWalk, 0xff0000);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmWalk);

	//pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_PAN);
	//m_bmPan.LoadBitmap(IDB_PAN);
	//YoTransparentBitmap(&m_bmPan, 0xff0000);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmPan);

	//pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_DEVICE_TRANSLATE);
	//m_bmDeviceTranslate.LoadBitmap(IDB_DEVICE_TRANSLATE);
	//YoTransparentBitmap(&m_bmDeviceTranslate, 0xff0000);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmDeviceTranslate);

	//pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_RECORD_SIM);
	//m_bmSimRecord.LoadBitmap(IDB_SIM_REC);
	//YoTransparentBitmap(&m_bmSimRecord, 0xff0000);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmSimRecord);
	
	//RECT rect;
	//pCBox->GetWindowRect(&rect);
	//TRACE2("left/top (%d, %d)       ", rect.left, rect.top);
	//TRACE2("right/bottom (%d, %d)\n", rect.right, rect.bottom);

	m_wndDlgScript = NULL;
	m_wndDlgEye = NULL;
	m_wndDlgEye = new CStageEyeDialog;
	m_wndDlgEye->YoInitDialog();
	m_wndDlgScript = new CStageScriptDlg;
	m_wndDlgScript->YoInitDialog();

	m_viewPartActive = FALSE;
	m_lightDlgActive = FALSE;
	m_robot6DlgActive = FALSE;
	m_rotaryTableDlgActive = FALSE;
	m_conveyorDlgActive = FALSE;
	m_gripperDlgActive = FALSE;
	m_barCodeReaderDlgActive = FALSE;
	m_barrettHandDlgActive = FALSE;
	m_scaleDlgActive = FALSE;
	m_trainDlgActive = FALSE;
	m_trackDlgActive = FALSE;
	m_cameraDlgActive = FALSE;
	m_viewTagActive = FALSE;
	m_analysisActive = FALSE;
	m_eyeViewDlgActive = FALSE;
	m_wndDlgEyeVisible = FALSE;
	m_wndDlgScriptVisible = FALSE;

	m_hCursorArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	//m_hCursorPan = AfxGetApp()->LoadStandardCursor(IDC_HAND); 
	m_hCursorSelect = AfxGetApp()->LoadCursor(IDC_SELECT);
	m_hCursorLink = AfxGetApp()->LoadCursor(IDC_LINK);

	//m_viewLightPartActive = FALSE;
	//POSITION pos = GetFirstViewPosition();
	//CStageView *pView = (CStageView *)GetNextView(pos);
	//CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	//pMainFrame->m_wndDlgDeviceTransformation = new CStageDeviceTransformation;
/***
	m_wndDlgDeviceTransformation = new CStageDeviceTransformation;
	m_wndDlgDeviceTransformation->ShowWindow(SW_HIDE);
	m_wndDlgEye = new CStageEyeDialog;
	m_wndDlgEye->ShowWindow(SW_HIDE);
	m_wndDlgDeviceTransformation->GetClientRect(&rect);
	rect.left += 300;
	rect.top += 4;
	rect.right += 300;
	rect.bottom += 4;
	m_wndDlgDeviceTransformation->MoveWindow(&rect, FALSE);
	//m_wndDlgDeviceTransformation->UpdateData(FALSE);
	m_wndDlgDeviceTransformation->ShowWindow(SW_SHOW);
	//m_wndDlgDeviceTransformation->EnableWindow(TRUE);
***/


/*	if (!m_wndDlgBar.Create(IDD_DIALOGBAR, this))
	{
		TRACE0("Failed to create top dialog bar\n");
		return -1;      // fail to create
	}
	//m_wndDlgBar.m_sEdit = "Hello";
	m_wndDlgBar.UpdateData(FALSE);
	m_wndDlgBar.ShowWindow(SW_SHOW);
	m_wndDlgBar.EnableWindow();
*/
	
	//UpdateData(FALSE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// Create a window without min/max buttons or sizable border 
    //cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER
	//	| WS_MAXIMIZEBOX | WS_MINIMIZEBOX;

    // Size the window to 1/3 screen size and center it 
    //cs.cy = ::GetSystemMetrics(SM_CYSCREEN); 
    //cs.cx = ::GetSystemMetrics(SM_CXSCREEN); 
	cs.cy = 616;
	cs.cx = 717;
    cs.y = 0; //((cs.cy * 3) - cs.cy) / 2; 
    cs.x = 0; //((cs.cx * 3) - cs.cx) / 2;


	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnModeWalk()
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;

	if (pView->m_mode != YO_MODE_DEVICE_TRANSLATE)
	{
		pDoc->m_undo->YoUndo();
	}

	pView->m_mode = YO_MODE_WALK;
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_WALK_ON);
	pCBox->ShowWindow(SW_SHOW);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_PAN_ON);
	pCBox->ShowWindow(SW_HIDE);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_DEVICE_TRANSLATE_ON);
	pCBox->ShowWindow(SW_HIDE);

	return;

	/***
	//pView->YoRenderStockScene();
	pView->m_mode = YO_MODE_WALK;
	CWnd* pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_WALK);
	((CButton *)pCBox)->SetCheck(1);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_PAN);
	((CButton *)pCBox)->SetCheck(0);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_DEVICE_TRANSLATE);
	((CButton *)pCBox)->SetCheck(0);

	//if (pDoc->m_acceptSocket != NULL && pDoc->m_isMovement)
	//{
	//	pDoc->YoMove();
	//}

	return;
	***/
}


void CMainFrame::OnModeDeviceTranslate()
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[256];

	pDoc->m_undo->YoUndo();

	/***
	if (pDoc->m_currentDevice == NULL)
	{
		if (pView->m_mode == YO_MODE_WALK)
		{
			pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_WALK);
			pCBox->ShowWindow(SW_SHOW);
			pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_PAN);
			pCBox->ShowWindow(SW_HIDE);
		}
		else
		{
			pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_WALK);
			pCBox->ShowWindow(SW_HIDE);
			pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_PAN);
			pCBox->ShowWindow(SW_SHOW);
		}

		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_DEVICE_TRANSLATE);
		pCBox->ShowWindow(SW_HIDE);
		return;
	}
	***/

	sprintf(s, "Translate %s with the left mouse button...", pDoc->m_currentDevice->m_name);
	pDoc->YoMessage(s);

	pView->m_mode = YO_MODE_DEVICE_TRANSLATE;
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_DEVICE_TRANSLATE_ON);
	pCBox->ShowWindow(SW_SHOW);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_WALK_ON);
	pCBox->ShowWindow(SW_HIDE);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_PAN_ON);
	pCBox->ShowWindow(SW_HIDE);

	return;
}

void CMainFrame::OnModeScript()
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	int dWidth;
	RECT rect;
	RECT mfRect;
	CREATESTRUCT cs;
	CWnd *pCBox;

	pDoc->m_undo->YoUndo();

	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SCRIPT_ON);
	if (m_wndDlgScriptVisible == TRUE)
	{
		m_wndDlgScript->ShowWindow(SW_HIDE);
		m_wndDlgScriptVisible = FALSE;
		pCBox->ShowWindow(SW_HIDE);
		return;
	}
	else
	{
		m_wndDlgScriptVisible = TRUE;
		pCBox->ShowWindow(SW_SHOW);
	}


    cs.cy = ::GetSystemMetrics(SM_CYSCREEN); 
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN); 

	m_wndDlgScript->GetWindowRect(&rect);
	dWidth = (rect.right - rect.left);
	GetWindowRect(&mfRect);
	rect.right = YO_MIN(mfRect.right + dWidth, cs.cx);
	rect.left = rect.right - dWidth;
	rect.right -= 3;
	rect.left -= 3;
	m_wndDlgScript->MoveWindow(&rect, TRUE);
	m_wndDlgScript->ShowWindow(SW_SHOW);

	if (m_wndDlgScript->m_modeEdit == TRUE)
	{
		pCBox = ((CComboBox*)m_wndDlgScript)->GetDlgItem(IDC_SCRIPT_LIST);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = ((CComboBox*)m_wndDlgScript)->GetDlgItem(IDC_SCRIPT_EDIT);
		pCBox->ShowWindow(SW_SHOW);
		m_wndDlgScript->RedrawWindow();
	}

	::SetActiveWindow(this->m_hWnd);

	return;

}

void CMainFrame::OnModeEye()
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	int i;
	RECT rect;
	CWnd *pCBox;

	pDoc->m_undo->YoUndo();

	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_EYE_ON);
	if (m_wndDlgEyeVisible == TRUE)
	{
		m_wndDlgEye->ShowWindow(SW_HIDE);
		m_wndDlgEyeVisible = FALSE;
		pCBox->ShowWindow(SW_HIDE);
		return;
	}
	else
	{
		m_wndDlgEyeVisible = TRUE;
		pCBox->ShowWindow(SW_SHOW);
		YoMoveEyeDlg();
	}

	GetWindowRect(&rect);
	if (rect.right - rect.left < YO_THRESH_WIDTH)
	{
		m_wndDlgEye->ShowWindow(SW_HIDE);
		return;
	}

	for (i = 0; i < 6; i++)
	{
		m_wndDlgEye->m_eyeOrig[i] = pView->m_eye[i];
	}
	m_wndDlgEye->m_clipFrontOrig = pView->m_clipFront;
	m_wndDlgEye->m_clipRearOrig = pView->m_clipRear;
	m_wndDlgEye->m_fieldOfViewOrig = pView->m_fieldOfView;

	YoUpdateEyeDlg();

	m_wndDlgEye->ShowWindow(SW_SHOW);

	::SetActiveWindow(this->m_hWnd);
 
	return;
}


void CMainFrame::OnModeRecordSim()
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];
	CWnd *pCBox;
	CStageCommand *ptrCommand;

	pDoc->m_undo->YoUndo();

	if (pDoc->m_mode == YO_MODE_WORKCELL)
	{
		CFileDialog recordSim
			(FALSE,    // save
			NULL,    // no default extension
			NULL,    // file name
			OFN_HIDEREADONLY,
			//"Stage Sim files (*.SIM)|*.SIM|All files (*.*)|*.*||");
			"All files (*.*)|*.*|Stage Simulation files (*.SIM)|*.SIM||");

		//sprintf(s, "Record Simulation"); 
		recordSim.m_ofn.lpstrTitle = "Record Simulation";

		if (recordSim.DoModal() == IDOK)
		{
			pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_RECORD_ON);
			pCBox->ShowWindow(SW_SHOW);
			pDoc->m_mode = YO_MODE_RECORD_SIM;

			sprintf(s, "%s", (LPCSTR)recordSim.GetPathName());
			if (pDoc->YoWriteWorkcell((LPCTSTR)s) == FALSE)
			{
				pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_RECORD_ON);
				pCBox->ShowWindow(SW_HIDE);
				pDoc->m_mode = YO_MODE_WORKCELL;
				sprintf(s, "ERROR: Attempt to record simulation failed.  Could not write file.");
				pDoc->YoMessage(s);
				return;
			}
			else
			{
				for (pDoc->m_currentCommand = pDoc->m_commandList; pDoc->m_currentCommand != NULL;)
				{
					ptrCommand = pDoc->m_currentCommand;
					pDoc->m_currentCommand = pDoc->m_currentCommand->m_next;
					delete ptrCommand;
				}
				pDoc->m_commandList = NULL;
				pDoc->m_currentCommand = NULL;

				ptrCommand = new CStageCommand(pDoc);
				::GetSystemTime(&ptrCommand->m_gmTime);
				sprintf(ptrCommand->m_buf, "SIMULATION_BEGIN");
				ptrCommand->YoInsertCommand();
				sprintf(s, "Recording Simulation...");
				pDoc->YoMessage(s);

			}

		}
		else
		{
			pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_RECORD_ON);
			pCBox->ShowWindow(SW_HIDE);
			pDoc->m_mode = YO_MODE_WORKCELL;
			sprintf(s, "Record simulation aborted.");
			pDoc->YoMessage(s);
		}
	}

	else if (pDoc->m_mode == YO_MODE_RECORD_SIM)
	{
		if (pView->m_fp != NULL)
		{
			ptrCommand = new CStageCommand(pDoc);
			::GetSystemTime(&ptrCommand->m_gmTime);
			sprintf(ptrCommand->m_buf, "SIMULATION_END");
			ptrCommand->YoInsertCommand();

			if (pDoc->m_commandList != NULL)
			{
				pDoc->m_commandList->YoWriteCommands(pView->m_fp);
			}
			fprintf(pView->m_fp, "NULL\n");
			fclose(pView->m_fp);
		}

		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_RECORD_ON);
		pCBox->ShowWindow(SW_HIDE);
		pDoc->m_mode = YO_MODE_WORKCELL;
		sprintf(s, "Simulation recorded successfully.");
		pDoc->YoMessage(s);
		return;

	}

	return;
}


void CMainFrame::OnModeSocket()
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	int nErrorCode;
	CWnd *pCBox;
	char s[128];

	pDoc->m_undo->YoUndo();

	if (pDoc->m_socket == NULL)
	{
		pDoc->YoSocketInit();
		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_CONNECT);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_LISTEN);
		pCBox->ShowWindow(SW_SHOW);
		return;
	}

	if (pDoc->m_acceptSocket && pDoc->m_isMovement == 0)
	{
		//pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_SOCKET);
		//((CButton *)pCBox)->SetCheck(0);
		if (AfxMessageBox("Current TCP/IP connection will be closed.", MB_OKCANCEL, 0) == IDOK)
		{
			pDoc->m_acceptSocket->OnClose(nErrorCode);
		}
		else
		{
			return;
		}
	}
	else if (pDoc->m_acceptSocket && pDoc->m_isMovement)
	{
		//pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_SOCKET);
		//((CButton *)pCBox)->SetCheck(0);
		sprintf(s, "No socket disconnect when devices in motion");
		pDoc->YoMessage(s);
		return;
	}

	pDoc->m_socket->OnClose(nErrorCode);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_CONNECT);
	pCBox->ShowWindow(SW_HIDE);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_LISTEN);
	pCBox->ShowWindow(SW_HIDE);
		//pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_MODE_SOCKET);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)m_bmCircleRed);
	//((CButton *)pCBox)->SetCheck(0);

	return;

}


void CMainFrame::OnUpdateSocketUI(CCmdUI *pCmdUI)
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	int nErrorCode;

	// TODO: Add your command update UI handler code here
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET);
	if (pDoc->m_mode == YO_MODE_WORKCELL && m_wndDlgScriptVisible == FALSE)
	{
		pCBox->ShowWindow(SW_SHOW);
		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_LISTEN);
		if (pDoc->m_socket == NULL && pDoc->m_acceptSocket == NULL)
		{
			pCBox->ShowWindow(SW_HIDE);
		}
		else if (pDoc->m_socket != NULL && pDoc->m_acceptSocket == NULL)
		{
			pCBox->ShowWindow(SW_SHOW);
		}
		else if (pDoc->m_socket != NULL && pDoc->m_acceptSocket != NULL)
		{
			pCBox->ShowWindow(SW_HIDE);
		}

		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_CONNECT);
		if (pDoc->m_socket == NULL && pDoc->m_acceptSocket == NULL)
		{
			pCBox->ShowWindow(SW_HIDE);
		}
		else if (pDoc->m_socket != NULL && pDoc->m_acceptSocket == NULL)
		{
			pCBox->ShowWindow(SW_HIDE);
		}
		else if (pDoc->m_socket != NULL && pDoc->m_acceptSocket != NULL)
		{
			pCBox->ShowWindow(SW_SHOW);
		}
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);

		if (pDoc->m_acceptSocket != NULL)
		// this routine should never be called
		{
			pDoc->m_acceptSocket->OnClose(nErrorCode);
			pDoc->m_acceptSocket = NULL;
		}
		if (pDoc->m_socket != NULL)
		{
			pDoc->m_socket->OnClose(nErrorCode);
			pDoc->m_socket = NULL;
		}

		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_CONNECT);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_LISTEN);
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}


void CMainFrame::YoUpdateLeftDlg()
{


	return;
}


void CMainFrame::YoMoveEyeDlg()
{
	RECT rect;
	RECT mfRect;
	int dwidth;
	
	// TODO: Add your message handler code here

	if (m_wndDlgBarTop.m_hWnd)
	{
		m_wndDlgBarTop.GetWindowRect(&mfRect);
		m_wndDlgEye->GetWindowRect(&rect);
		dwidth = rect.right - rect.left;
		rect.right = mfRect.right - 10;
		rect.left = mfRect.right - 10 - dwidth;
		rect.bottom = mfRect.top + 3 + (rect.bottom - rect.top);
		rect.top = mfRect.top + 3;
		//rect.right = x + 300 + rect.right - rect.left;
		//rect.bottom = y + 3 + rect.bottom - rect.top;
		//rect.left = x + 300;
		//rect.top = y + 3;
		m_wndDlgEye->MoveWindow(&rect, TRUE);
	}
	return;
}

void CMainFrame::YoUpdateEyeDlg()
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[32];
	CWnd *pCBox;

	if (m_wndDlgEyeVisible == TRUE)
	{
		sprintf(s, "%.1lf", pView->m_eye[0] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)m_wndDlgEye->GetDlgItem(IDC_EYE_FROMX);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", pView->m_eye[1] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)m_wndDlgEye->GetDlgItem(IDC_EYE_FROMY);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", pView->m_eye[2] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)m_wndDlgEye->GetDlgItem(IDC_EYE_FROMZ);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", pView->m_eye[3] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)m_wndDlgEye->GetDlgItem(IDC_EYE_TOX);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", pView->m_eye[4] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)m_wndDlgEye->GetDlgItem(IDC_EYE_TOY);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", pView->m_eye[5] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)m_wndDlgEye->GetDlgItem(IDC_EYE_TOZ);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", pView->m_fieldOfView);
		pCBox = (CComboBox*)m_wndDlgEye->GetDlgItem(IDC_EYE_FOV);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", pView->m_clipFront * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)m_wndDlgEye->GetDlgItem(IDC_EYE_CLIPFRONT);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", pView->m_clipRear * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)m_wndDlgEye->GetDlgItem(IDC_EYE_CLIPREAR);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		pCBox = (CComboBox*)m_wndDlgEye->GetDlgItem(IDC_EYE_SLIDER_FOV);
		((CSliderCtrl *)pCBox)->SetRange(0, 180);
		((CSliderCtrl *)pCBox)->SetPos((int)pView->m_fieldOfView);
	}

	return;
}

void CMainFrame::OnModePan()
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;

	if (pView->m_mode != YO_MODE_DEVICE_TRANSLATE)
	{
		pDoc->m_undo->YoUndo();
	}

	pView->m_mode = YO_MODE_PAN;
	//SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)m_hCursorPan);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_WALK_ON);
	pCBox->ShowWindow(SW_HIDE);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_PAN_ON);
	pCBox->ShowWindow(SW_SHOW);
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_DEVICE_TRANSLATE_ON);
	pCBox->ShowWindow(SW_HIDE);

	return;
}

void CMainFrame::OnPrefs() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CPropertySheet prefsPropSheet("Prefs", NULL, 0);

	CStagePrefsRender prefsRender;
	CStagePrefsGrid prefsGrid;
	CStagePrefsLighting prefsLighting;
	CStagePrefsNetwork prefsNetwork;
	CStagePrefsUnits prefsUnits;
	char s[256];
	//CStagePrefsOutput prefsOutput;

	//pDoc->m_undo->YoUndo();
	//sprintf(s, "Setting preferences...");
	//pDoc->YoMessage(s);

	// transfer document variables to prefs property sheet
	prefsGrid.m_gridVisible = (BOOL)pDoc->m_grid[0];
	prefsGrid.m_gridSpacing = pDoc->m_grid[1] * (float)pDoc->m_unitScaleFactor;
	prefsGrid.m_gridLength = pDoc->m_grid[2] * (float)pDoc->m_unitScaleFactor;
	prefsGrid.m_gridWidth = pDoc->m_grid[3] * (float)pDoc->m_unitScaleFactor;
	prefsGrid.m_gridRed = (UINT)pDoc->m_grid[4];
	prefsGrid.m_gridGreen = (UINT)pDoc->m_grid[5];
	prefsGrid.m_gridBlue = (UINT)pDoc->m_grid[6];

	prefsGrid.m_origGridVisible = prefsGrid.m_gridVisible;
	prefsGrid.m_origGridSpacing = pDoc->m_grid[1];
	prefsGrid.m_origGridLength = pDoc->m_grid[2];
	prefsGrid.m_origGridWidth = pDoc->m_grid[3];
	prefsGrid.m_origGridRed = prefsGrid.m_gridRed;
	prefsGrid.m_origGridGreen = prefsGrid.m_gridGreen;
	prefsGrid.m_origGridBlue = prefsGrid.m_gridBlue;

	if (pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR)
	{
		prefsRender.m_motionBlur = TRUE;
	}
	prefsRender.m_motionBlurIterations = (UINT)pDoc->m_motionBlurIterations;
	if (pDoc->m_render3d & YO_RENDER3D_SHADOWS)
	{
		//prefsRender.m_shadows = TRUE;
	}
	prefsRender.m_framesPerSecond = pDoc->m_framesPerSecond;
	prefsRender.m_antiAlias = pDoc->m_antiAlias;
	prefsRender.m_outputBitmap = pDoc->m_outputBitmap;
	prefsRender.m_boundingBox = pDoc->m_boundingBox;

	prefsRender.m_origBoundingBox = prefsRender.m_boundingBox;

	//prefsLighting.m_localViewer = (BOOL)pDoc->m_lighting[0];
	prefsLighting.m_twoSide = (BOOL)pDoc->m_lighting[1];
	prefsLighting.m_lightingSunAltitude = pDoc->m_sunAltitude;
	prefsLighting.m_lightingSunAzimuth = pDoc->m_sunAzimuth;
	prefsLighting.m_lightingSunIntensity = pDoc->m_sunIntensity;

	prefsLighting.m_origTwoSide = prefsLighting.m_twoSide;
	prefsLighting.m_origLightingSunIntensity = prefsLighting.m_lightingSunIntensity;
	prefsLighting.m_origLightingSunAltitude = prefsLighting.m_lightingSunAltitude;
	prefsLighting.m_origLightingSunAzimuth = prefsLighting.m_lightingSunAzimuth;

	prefsNetwork.m_port = (UINT)pDoc->m_port;

	prefsUnits.m_units = pDoc->m_units;
	prefsUnits.m_origUnits = prefsUnits.m_units;

	prefsPropSheet.AddPage(&prefsRender);
	prefsPropSheet.AddPage(&prefsLighting);
	prefsPropSheet.AddPage(&prefsUnits);
	prefsPropSheet.AddPage(&prefsGrid);
	prefsPropSheet.AddPage(&prefsNetwork);
	//prefsPropSheet.AddPage(&prefsOutput);

	if (prefsPropSheet.DoModal() == IDOK)
	// Bug in CPropSheet::DoModal at line: HWND hWnd = (HWND)::PropertySheet((PROPSHEETHEADER*)psh);
	{
		sprintf(s, "Preferences updated.");
		pDoc->YoMessage(s);

		//pDoc->m_grid[0] = (GLint)prefsGrid.m_gridVisible;
		//pDoc->m_grid[1] = (GLint)prefsGrid.m_gridSpacing;
		//pDoc->m_grid[2] = (GLint)prefsGrid.m_gridLength;
		//pDoc->m_grid[3] = (GLint)prefsGrid.m_gridWidth;
		//pDoc->m_grid[4] = (GLint)prefsGrid.m_gridRed;
		//pDoc->m_grid[5] = (GLint)prefsGrid.m_gridGreen;
		//pDoc->m_grid[6] = (GLint)prefsGrid.m_gridBlue;

		//pDoc->m_units = prefsUnits.m_units;
		//pDoc->YoUnitScaleFactor();
		//YoUpdateEyeDlg();

		pDoc->m_render3d = 0;
		if (prefsRender.m_motionBlur)
		{
			pDoc->m_render3d |= YO_RENDER3D_MOTION_BLUR;
			//pDoc->m_motionBlurIterations = (GLint)prefsRender.m_motionBlurIterations;
		}
		//else
		//{
		//	pDoc->m_motionBlurIterations = 1;
		//}
		//if (prefsRender.m_shadows)
		//{
		//	pDoc->m_render3d |= YO_RENDER3D_SHADOWS;
		//}

		pDoc->m_motionBlurIterations = (GLint)prefsRender.m_motionBlurIterations;
		pDoc->m_framesPerSecond = prefsRender.m_framesPerSecond;
		pDoc->m_antiAlias = prefsRender.m_antiAlias;
		pDoc->m_outputBitmap = prefsRender.m_outputBitmap;
		if (pDoc->m_outputBitmap == TRUE && pDoc->m_mode == YO_MODE_PLAY_SIM)
		{
			pDoc->m_realTime = FALSE;
		}
		else
		{
			pDoc->m_realTime = TRUE;
		}

		pDoc->m_port = (u_short)prefsNetwork.m_port;
		//pDoc->m_boundingBox = prefsRender.m_boundingBox;

		//pDoc->m_lighting[0] = (GLint)prefsLighting.m_localViewer;
		//pDoc->m_lighting[1] = (GLint)prefsLighting.m_twoSide;
		//pDoc->m_sunAltitude = prefsLighting.m_lightingSunAltitude;
		//pDoc->m_sunAzimuth = prefsLighting.m_lightingSunAzimuth;
		//pDoc->m_sunIntensity = (float)prefsLighting.m_lightingSunIntensity / 255.0f;
	}
	else
	{
		sprintf(s, "Original preferences restored.");
		pDoc->YoMessage(s);

		pDoc->m_boundingBox = prefsRender.m_origBoundingBox;

		pDoc->m_grid[0] = (float)prefsGrid.m_origGridVisible;
		pDoc->m_grid[1] = prefsGrid.m_origGridSpacing;
		pDoc->m_grid[2] = prefsGrid.m_origGridLength;
		pDoc->m_grid[3] = prefsGrid.m_origGridWidth;
		pDoc->m_grid[4] = (float)prefsGrid.m_origGridRed;
		pDoc->m_grid[5] = (float)prefsGrid.m_origGridGreen;
		pDoc->m_grid[6] = (float)prefsGrid.m_origGridBlue;

		pDoc->m_units = prefsUnits.m_origUnits;
		pDoc->YoUnitScaleFactor();
		YoUpdateEyeDlg();

		//pDoc->m_lighting[0] = (GLint)prefsLighting.m_origLocalViewer;
		pDoc->m_lighting[1] = (GLint)prefsLighting.m_origTwoSide;
		pDoc->m_sunAltitude = prefsLighting.m_origLightingSunAltitude;
		pDoc->m_sunAzimuth = prefsLighting.m_origLightingSunAzimuth;
		pDoc->m_sunIntensity = prefsLighting.m_origLightingSunIntensity;
	}

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;

}

void CMainFrame::OnViewDeviceTree() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageDeviceTree deviceTree;

	pDoc->m_undo->YoUndo();

	if (deviceTree.DoModal() == IDOK)
	{
		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}
	
}

void CMainFrame::YoTransparentBitmap(CBitmap *bitmap, COLORREF transColor)
{
	// Takes already loaded bitmap and makes all transcolor bits the
	// same as the current button, menu, etc. background color

	DWORD sysColor;
	BITMAP bm;
	COLORREF pixColor;
	CDC pDC;
	int i;
	int j;

	bitmap->GetBitmap(&bm);
	sysColor = ::GetSysColor(COLOR_3DFACE);
	pDC.CreateCompatibleDC(NULL);
	pDC.SelectObject(bitmap);

	for (j = 0; j < bm.bmHeight; j++)
	{
		for (i = 0; i < bm.bmWidth; i++)
		{
			pixColor = pDC.GetPixel(i, j);
			if (pixColor == transColor)
			{
				pDC.SetPixel(i, j, sysColor);
			}
		}
	}

	return;
}


void CMainFrame::OnUpdateDeviceTranslateUI(CCmdUI *pCmdUI)
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;

	// TODO: Add your command update UI handler code here
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_DEVICE_TRANSLATE);
	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		//&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}

	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_DEVICE_TRANSLATE_ON);
	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL)
		&& pView->m_mode == YO_MODE_DEVICE_TRANSLATE)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}

	return;
}

void CMainFrame::OnUpdateWalkUI(CCmdUI *pCmdUI)
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;

	// TODO: Add your command update UI handler code here
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_WALK);
	if (pDoc->m_mode == YO_MODE_WORKCELL)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}

	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_WALK_ON);
	if (pDoc->m_mode == YO_MODE_WORKCELL && pView->m_mode == YO_MODE_WALK)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}
	
	return;
}

void CMainFrame::OnUpdatePanUI(CCmdUI *pCmdUI)
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;

	// TODO: Add your command update UI handler code here
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_PAN);
	if (pDoc->m_mode == YO_MODE_WORKCELL)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}

	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_PAN_ON);
	if (pDoc->m_mode == YO_MODE_WORKCELL && pView->m_mode == YO_MODE_PAN)
	{
		pCBox->ShowWindow(SW_SHOW);
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
	}
	
	return;
}


void CMainFrame::OnUpdateRecordSimUI(CCmdUI *pCmdUI)
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;

	// TODO: Add your command update UI handler code here
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_RECORD);
	if (pDoc->m_mode != YO_MODE_PLAY_SIM
		&& (pDoc->m_acceptSocket != NULL || m_wndDlgScriptVisible == TRUE))
	{
		pCBox->ShowWindow(SW_SHOW);
		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_RECORD_ON);
		if (pDoc->m_mode == YO_MODE_RECORD_SIM)
		{
			pCBox->ShowWindow(SW_SHOW);
		}
		else
		{
			pCBox->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_RECORD_ON);
		pCBox->ShowWindow(SW_HIDE);
	}

	return;
}


void CMainFrame::OnUpdateEyeUI(CCmdUI *pCmdUI)
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;

	// TODO: Add your command update UI handler code here
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_EYE);
	if (pDoc->m_mode == YO_MODE_WORKCELL)
	{
		pCBox->ShowWindow(SW_SHOW);

		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_EYE_ON);
		if (m_wndDlgEyeVisible == TRUE)
		{
			pCBox->ShowWindow(SW_SHOW);
		}
		else
		{
			pCBox->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		pCBox->ShowWindow(SW_HIDE);

		if (m_wndDlgEyeVisible == TRUE)
		{
			m_wndDlgEye->ShowWindow(SW_HIDE);
			m_wndDlgEyeVisible = FALSE;
		}

		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_EYE_ON);
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}
	

void CMainFrame::OnUpdateScriptUI(CCmdUI *pCmdUI)
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	BOOL ret;

	// TODO: Add your command update UI handler code here
	pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SCRIPT);

	if (pDoc->m_mode != YO_MODE_PLAY_SIM
		&& pDoc->m_acceptSocket == NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE)
	{
		pCBox->ShowWindow(SW_SHOW);
		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SCRIPT_ON);
		if (m_wndDlgScriptVisible == TRUE)
		{
			pCBox->ShowWindow(SW_SHOW);
		}
		else
		{
			pCBox->ShowWindow(SW_HIDE);
		}
	}
	else 
	{
		ret = pCBox->ShowWindow(SW_HIDE);
		if (ret != FALSE)
		{
			m_wndDlgScript->SendMessage(WM_CLOSE);
		}
		pCBox = (CComboBox*)m_wndDlgBarLeft.GetDlgItem(IDC_SCRIPT_ON);
		pCBox->ShowWindow(SW_HIDE);
	}
	return;
}


void CMainFrame::OnUpdateSliderFieldOfView()
{
	return;
}

void CMainFrame::OnMotionInsertAnchor() 
{
	/***
	// TODO: Add your command handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageEyeMotion *ptrMotion;
	int i;

	if (!pView )
	{
		return;
	}
	// Fail if view is of wrong kind
	
	if (!pView->IsKindOf(RUNTIME_CLASS(CStageView))) 
	{
		return;
	}
	pDoc->m_undo->YoUndo();
	ptrMotion = new CStageEyeMotion(pDoc);
	ptrMotion->m_time = pDoc->m_timeCurrent;
	ptrMotion->m_type = YO_MOTION_ANCHOR;
	for (i = 0; i < 9; i++)
	{
		ptrMotion->m_eye[i] = pView->m_eye[i];
	}
	ptrMotion->m_clipFront = pView->m_clipFront;
	ptrMotion->m_clipRear = pView->m_clipRear;
	ptrMotion->m_fieldOfView = pView->m_fieldOfView;

	pDoc->YoInsertEyeMotion(ptrMotion);
	***/
	return;
	
}

void CMainFrame::OnMotionInsertHold() 
{
	/***
	// TODO: Add your command handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageEyeMotion *ptrMotion;
	int i;

	if (!pView )
	{
		return;
	}
	// Fail if view is of wrong kind
	
	if (!pView->IsKindOf(RUNTIME_CLASS(CStageView))) 
	{
		return;
	}
	pDoc->m_undo->YoUndo();
	ptrMotion = new CStageEyeMotion(pDoc);
	ptrMotion->m_time = pDoc->m_timeCurrent;
	ptrMotion->m_type = YO_MOTION_HOLD;
	for (i = 0; i < 9; i++)
	{
		ptrMotion->m_eye[i] = pView->m_eye[i];
	}
	ptrMotion->m_clipFront = pView->m_clipFront;
	ptrMotion->m_clipRear = pView->m_clipRear;
	ptrMotion->m_fieldOfView = pView->m_fieldOfView;

	pDoc->YoInsertEyeMotion(ptrMotion);
	***/
	return;
}

void CMainFrame::OnMotionViewHistory() 
{
	// TODO: Add your command handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageMotionViewHistory motionViewHistory;

	pDoc->m_undo->YoUndo();
	if (motionViewHistory.DoModal() == IDOK)
	{
	}
	
}

void CMainFrame::DoDataExchange(CDataExchange* pDX) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_init == FALSE)
	{
		return;
	}

	CFrameWnd::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TIME, m_sliderCurrentTime);
	//DDX_Text(pDX, IDC_MINUTES, m_minutes);
	//DDV_MaxChars(pDX, m_minutes, 2);
	//DDX_Text(pDX, IDC_SECONDS, m_seconds);
	//DDV_MaxChars(pDX, m_seconds, 2);
	//DDX_Text(pDX, IDC_FRAMES, m_frames);
	//DDV_MaxChars(pDX, m_frames, 2);
}


void CMainFrame::OnViewCurrentPart() 
{
	// TODO: Add your command handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStagePart *ptrPart;
	int i = 0;

	pDoc->m_undo->YoUndo();

	if (pDoc->m_currentDevice->m_type == YO_TRACK)
	{
		m_trackDialog = new CStageTrackDlg;
		m_trackDialog->YoInitDialog();
		m_trackDlgActive = TRUE;
		m_trackDialog->ShowWindow(SW_SHOW);
	}
	else
	{
		m_viewPart = new CStageViewPart;
		m_viewPart->YoInitDialog();
		m_viewPartActive = TRUE;
		m_viewPart->ShowWindow(SW_SHOW);
	}

	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		m_lightDialog = new CStageLightDialog;
		m_lightDialog->YoInitDialog();
		m_lightDialog->ShowWindow(SW_SHOW);
	}
	else if (pDoc->m_currentDevice->m_type == YO_ROBOT6)
	{
		for (ptrPart = pDoc->m_currentDevice->m_ptrPart;
			ptrPart != NULL && i <= 6; ptrPart = ptrPart->m_down)
		{
			// check to make certain robot is fully assembled
			i++;
		}
		//if (i >= 6)
		{
			m_robot6Dialog  = new CStageRobot6Dlg;
			m_robot6Dialog->YoInitDialog();
			m_robot6Dialog->ShowWindow(SW_SHOW);
			m_robot6DlgActive = TRUE;
		}
	}
	else if (pDoc->m_currentDevice->m_type == YO_ROTARY_TABLE)
	{
		m_rotaryTableDialog = new CStageRotaryTableDlg;
		m_rotaryTableDialog->YoInitDialog();
		m_rotaryTableDialog->ShowWindow(SW_SHOW);
		m_rotaryTableDlgActive = TRUE;
	}
	else if (pDoc->m_currentDevice->m_type == YO_CONVEYOR)
	{
		m_conveyorDialog = new CStageConveyorDlg;
		m_conveyorDialog->YoInitDialog();
		m_conveyorDialog->ShowWindow(SW_SHOW);
		m_conveyorDlgActive = TRUE;
	}
	else if (pDoc->m_currentDevice->m_type == YO_CAMERA)
	{
		m_cameraDialog = new CStageCameraDlg;
		m_cameraDialog->YoInitDialog();
		m_cameraDialog->ShowWindow(SW_SHOW);
		m_cameraDlgActive = TRUE;
	}
	else if (pDoc->m_currentDevice->m_type == YO_GRIPPER)
	{
		m_gripperDialog = new CStageGripperDlg;
		m_gripperDialog->YoInitDialog();
		m_gripperDialog->ShowWindow(SW_SHOW);
		m_gripperDlgActive = TRUE;
	}
	else if (pDoc->m_currentDevice->m_type == YO_BAR_CODE_READER)
	{
		m_barCodeReaderDialog = new CStageBarCodeReaderDlg;
		m_barCodeReaderDialog->YoInitDialog();
		m_barCodeReaderDialog->ShowWindow(SW_SHOW);
		m_barCodeReaderDlgActive = TRUE;
	}
	else if (pDoc->m_currentDevice->m_type == YO_BARRETT_HAND)
	{
		m_barrettHandDialog = new CStageBarrettHandDlg;
		m_barrettHandDialog->YoInitDialog();
		m_barrettHandDialog->ShowWindow(SW_SHOW);
		m_barrettHandDlgActive = TRUE;
	}
	else if (pDoc->m_currentDevice->m_type == YO_SCALE)
	{
		m_scaleDialog = new CStageScaleDlg;
		m_scaleDialog->YoInitDialog();
		m_scaleDialog->ShowWindow(SW_SHOW);
		m_scaleDlgActive = TRUE;
	}
	else if (pDoc->m_currentDevice->m_type == YO_TRAIN
		&& ((CStageTrain *)pDoc->m_currentDevice)->m_ptrTrackSeg != NULL)
	{
		m_trainDialog = new CStageTrainDlg;
		m_trainDialog->YoInitDialog();
		m_trainDialog->ShowWindow(SW_SHOW);
		m_trainDlgActive = TRUE;
	}
	return;

}


void CMainFrame::OnUpdateViewCurrentPart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& m_wndDlgScriptVisible == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;
	
}


void CMainFrame::OnViewCurrentTag() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pDoc->m_undo->YoUndo();

	m_viewTag = new CStageViewTag;
	m_viewTag->YoInitDialog();
	m_viewTagActive = TRUE;
	m_viewTag->ShowWindow(SW_SHOW);

	return;
}


void CMainFrame::OnUpdateViewCurrentTag(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& pDoc->m_currentTag != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& m_wndDlgScriptVisible == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;
}


void CMainFrame::OnDeviceAttach() 
{
	// TODO: Add your command handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];

	pDoc->m_undo->YoUndo();
	pDoc->m_deviceBeingAttached = TRUE;
	SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)m_hCursorLink);
	sprintf(s, "Attach %s to a device selected with the left mouse button...", pDoc->m_currentDevice->m_name);
	pDoc->YoMessage(s);
	return;
	
}

void CMainFrame::OnDeviceChoose() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseDevice chooseDevice;
	char s[256];

	pDoc->m_undo->YoUndo();
	sprintf(s, "Selecting device...");
	pDoc->YoMessage(s);
	m_dialogChooseNameTitle = "Choose Device";

	if (chooseDevice.DoModal() == IDOK)
	{
		sprintf(s, "Device: %s   Part: %s",
			pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
		pDoc->YoMessage(s);
	}
	else
	{
		sprintf(s, "Choose device aborted.");
		pDoc->YoMessage(s);
	}

	return;
}


void CMainFrame::OnTagChoosePath() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseDevice choosePath;
	char s[256];

	pDoc->m_undo->YoUndo();
	sprintf(s, "Selecting path...");
	pDoc->YoMessage(s);
	m_dialogChooseNameTitle = "Choose Path";

	if (choosePath.DoModal() == IDOK)
	{
		sprintf(s, "Path: %s   Tag: %d",
			pDoc->m_currentTag->m_ptrPath->m_name, pDoc->m_currentTag->m_tag);
		pDoc->YoMessage(s);
	}
	else
	{
		sprintf(s, "Choose path aborted.");
		pDoc->YoMessage(s);
	}

	return;	
}


void CMainFrame::OnUpdateTagChoosePath(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& pDoc->m_currentTag != NULL
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL)
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_PATH_DELETE
		|| pDoc->m_numberOfPaths > 1))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}


void CMainFrame::OnDeviceCreate() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseName chooseName;
	CString s;
	char t[256];
	CStageChooseDevice chooseDeviceType;
	CStageDevice *ptrDevice;
	CStagePart *ptrPart;

	pDoc->m_undo->YoUndo();
	sprintf(t, "Constructing new device...");
	pDoc->YoMessage(t);

	m_dialogChooseNameTitle = "STEP 1: Create Device";

	if (chooseName.DoModal() != IDOK)
	{
		sprintf(t, "Create device aborted.");
		pDoc->YoMessage(t);
		return;
	}

	m_dialogChooseNameTitle = "STEP 2: Choose Device Type";

	if (chooseDeviceType.DoModal() != IDOK)
	{
		sprintf(t, "Create device aborted.");
		pDoc->YoMessage(t);
		return;
	}


	// choose a base part file
	CFileDialog choosePart
		(TRUE,    // open
		NULL,    // no default extension
		NULL,    // file name
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		//"Stage Part files (*.PRT)|*.PRT|All files (*.*)|*.*||");
		"All files (*.*)|*.*|Stage Part files (*.PRT)|*.PRT||");

	choosePart.m_ofn.lpstrTitle = "STEP 3: Choose a base part";

	if (choosePart.DoModal() == IDOK)
	{
		if (chooseDeviceType.m_editName == "2 - Light")
		{
			ptrDevice = new CStageLight(pDoc);
			ptrDevice->m_type = YO_LIGHT;
			ptrDevice->YoInitDevice(ptrDevice);
			//((CStageLight *)ptrDevice)->YoGetLight();
		}
		else if (chooseDeviceType.m_editName == "3 - Camera")
		{
			ptrDevice = new CStageCamera(pDoc);
			ptrDevice->m_type = YO_CAMERA;
			ptrDevice->YoInitDevice(ptrDevice);
		}
		else if (chooseDeviceType.m_editName == "4 - Train")
		{
			ptrDevice = new CStageTrain(pDoc);
			ptrDevice->m_type = YO_TRAIN;
			ptrDevice->YoInitDevice(ptrDevice);
		}
		/***
		else if (chooseDeviceType.m_editName == "2 - Robot (6 dof)")
		{
			ptrDevice = new CStageRobot6(pDoc);
			ptrDevice->m_type = YO_ROBOT6;
			ptrDevice->YoInitDevice(ptrDevice);
		}
		else if (chooseDeviceType.m_editName == "3 - Rotary Table")
		{
			ptrDevice = new CStageRotaryTable(pDoc);
			ptrDevice->m_type = YO_ROTARY_TABLE;
			ptrDevice->YoInitDevice(ptrDevice);
		}
		else if (chooseDeviceType.m_editName == "4 - Gripper")
		{
			ptrDevice = new CStageGripper(pDoc);
			ptrDevice->m_type = YO_GRIPPER;
			ptrDevice->YoInitDevice(ptrDevice);
		}
		else if (chooseDeviceType.m_editName == "5 - Bar Code Reader")
		{
			ptrDevice = new CStageBarCodeReader(pDoc);
			ptrDevice->m_type = YO_BAR_CODE_READER;
			ptrDevice->YoInitDevice(ptrDevice);
		}
		else if (chooseDeviceType.m_editName == "6 - Scale")
		{
			ptrDevice = new CStageScale(pDoc);
			ptrDevice->m_type = YO_SCALE;
			ptrDevice->YoInitDevice(ptrDevice);
		}
		***/
		else
		{
			ptrDevice = new CStageDevice(pDoc);
			ptrDevice->m_type = YO_DEVICE;
			ptrDevice->YoInitDevice(ptrDevice);
		}
		sprintf(ptrDevice->m_name, "%s", chooseName.m_editName);
		//pDoc->YoDeviceHashInstall(ptrDevice);
		pDoc->YoInsertDevice(ptrDevice, NULL);

		ptrPart = new CStagePart(pDoc);
		ptrPart->YoInitPart(ptrPart);
		ptrPart->m_displayListID = pDoc->YoGetNewDisplayListID(ptrPart, NULL);

		sprintf(ptrPart->m_deviceName, "%s", ptrDevice->m_name);
		s = choosePart.GetFileTitle();
		sprintf(ptrPart->m_partName, "%s", (LPCSTR)s);

		pDoc->m_currentDevice = ptrDevice;
		pDoc->m_currentPart = ptrPart;
			
		s = choosePart.GetPathName();
		sprintf(ptrPart->m_partFile, "%s", (LPCSTR)s);
		pDoc->YoInsertPart(ptrDevice, ptrPart);
		if (ptrPart->YoReadPartFile(ptrPart->m_partFile) == FALSE)
		{
			sprintf(t, "Device not created.  Error reading base part file:\n   %s\nIncorrect file format or corrupt data encountered.",
				s);
			AfxMessageBox(t);
			pDoc->YoDeleteDevice();
			sprintf(t, "Create device aborted.");
			pDoc->YoMessage(t);
			this->RedrawWindow();
			return;
		}

		ptrPart->m_translate[0] = pView->m_eye[3];
		ptrPart->m_translate[1] = pView->m_eye[4];
		ptrPart->m_translate[2] = pView->m_eye[5];
	}
	else
	{
		sprintf(t, "Create device aborted.");
		pDoc->YoMessage(t);
		return;
    }

	sprintf(t, "Device: %s   Part: %s",
		pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(t);

	//SendMessage(WM_COMMAND, ID_VIEW_CURRENT_PART, (LPARAM)0);

	return;	
}


void CMainFrame::OnDeviceClone() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseName chooseName;
	char s[256];

	pDoc->m_undo->YoUndo();
	sprintf(s, "Cloning %s...", pDoc->m_currentDevice->m_name);
	pDoc->YoMessage(s);

	m_dialogChooseNameTitle = "Clone Device";

	if (chooseName.DoModal() == IDOK)
	{
		//pView->YoRender(YO_RENDER_LIGHT);
		//pView->YoRender(YO_RENDER_FULL);
		//SendMessage(WM_COMMAND, ID_VIEW_CURRENT_PART, (LPARAM)0);
		sprintf(s, "Cloned Device: %s   Part: %s",
			pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
		pDoc->YoMessage(s);
		this->RedrawWindow();
	}
	else
	{
		sprintf(s, "Clone device aborted.");
		pDoc->YoMessage(s);
	}

	return;
	
}

void CMainFrame::OnDeviceDetach() 
{
	// TODO: Add your command handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageDevice *ptrDevice;
	char s[256];

	pDoc->m_undo->YoUndo();
	if (strcmp(pDoc->m_currentDevice->m_parent, "NONE") == 0)
	{
		return;
	}

	pDoc->YoDetachDevice();

	if (pDoc->m_deviceList == NULL)
	{
		pDoc->m_deviceList = pDoc->m_currentDevice;
		return;
	}

	// reattach device at world coords (rightmost position)
	for (ptrDevice = pDoc->m_deviceList;
		ptrDevice->m_right != NULL;
		ptrDevice = ptrDevice->m_right);
	ptrDevice->m_right = pDoc->m_currentDevice;
	pDoc->m_currentDevice->m_left = ptrDevice;

	sprintf(s, "Device %s detached from parent", pDoc->m_currentDevice->m_name);
	pDoc->YoMessage(s);


	return;	
}

void CMainFrame::OnDeviceRename() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseName chooseName;
	char s[256];

	pDoc->m_undo->YoUndo();
	sprintf(s, "Enter a new name for %s...", pDoc->m_currentDevice->m_name);
	pDoc->YoMessage(s);
	m_dialogChooseNameTitle = "Rename Device";

	if (chooseName.DoModal() == IDOK)
	{
		sprintf(s, "Renamed device: %s   Part: %s",
			pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
		pDoc->YoMessage(s);
	}
	else
	{
		sprintf(s, "Rename device aborted.");
		pDoc->YoMessage(s);
	}

	return;	
}

void CMainFrame::OnDeviceDelete()
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];

	pDoc->m_undo->YoUndo();

	if (pDoc->m_currentDevice == NULL)
	{
		return;
	}

	sprintf(s, "Device %s deleted.", pDoc->m_currentDevice->m_name);
	pDoc->YoMessage(s);

	pDoc->m_undo->m_undoMode = YO_UNDO_DEVICE_DELETE;
	pDoc->m_undo->m_undoDeviceDelete = pDoc->m_currentDevice;
	pDoc->m_undo->m_undoDeviceDelete->m_visible = FALSE;

	if (pDoc->m_undo->m_undoDeviceDelete->m_type == YO_LIGHT)
	{
		((CStageLight *)pDoc->m_undo->m_undoDeviceDelete)->m_enabled = FALSE;
	}
	//pDoc->YoDeleteDevice();

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;

}

/****
void CMainFrame::OnDeviceDelete() 
{
	// TODO: Add your command handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageLight *ptrLight;
	//CStageDevice *currentDevice;
	CStageDevice *ptrDevice;
	CStageDevice *prevDevice;
	CStagePart *currentPart;
	CStagePart *ptrPart;
	//CStageMotion *currentMotion;
	//CStageMotion *ptrMotion;
	//CStageEffect *currentEffect;
	//CStageEffect *ptrEffect;
	//CStageScore *currentScore;
	//CStageScore *ptrScore;
	//CStageTexture *currentTexture;
	//CStageTexture *ptrTexture;
	int i;
	GLdouble m[16];

	pDoc->YoDetachDevice();

	// last device in workcell
	if (pDoc->m_deviceList == NULL)
	{
		pDoc->m_deviceList = pDoc->m_currentDevice;
		pDoc->YoFreeWorkcell();
		return;
	}

	// remove the  name from the device hash table
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


	// delete parts associated with device
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


		//glDeleteLists(ptrPart->m_displayListID, 1);
		//glDeleteLists(ptrPart->m_wireframeDisplayListID, 1);
		delete(ptrPart);
	}

	// reconstruct device list without device to be deleted
	if (pDoc->m_deviceList == NULL)
	{
		if (pDoc->m_currentDevice->m_right != NULL)
		{
			pDoc->m_deviceList = pDoc->m_currentDevice->m_right;
			pDoc->m_currentDevice->m_right->m_left = NULL;
			if (pDoc->m_currentDevice->m_down != NULL)
			{
				for (ptrDevice = pDoc->m_deviceList;
					ptrDevice->m_right != NULL;
					ptrDevice = ptrDevice->m_right);
				pDoc->m_currentDevice->m_down->m_left = ptrDevice;
				ptrDevice->m_right = pDoc->m_currentDevice->m_down;
				pDoc->m_currentDevice->m_down->m_up = NULL;
				sprintf(pDoc->m_currentDevice->m_down->m_parent, "NONE");
				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				::glLoadIdentity();
				pView->YoTxyz(pDoc->m_currentDevice->m_ptrPart,
					pDoc->m_currentDevice->m_ptrPart->m_translate,
					pDoc->m_currentDevice->m_ptrPart->m_rotate);
				pView->YoTxyz(pDoc->m_currentDevice->m_down->m_ptrPart,
					pDoc->m_currentDevice->m_down->m_ptrPart->m_translate,
					pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate);		
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				pDoc->m_currentDevice->m_down->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
				pDoc->YoTranslateRotateValues(m,
					pDoc->m_currentDevice->m_down->m_ptrPart->m_translate,
					pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate);
				for (i = 0; i < 3; i++)
				{
					pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
				}
				::glPopMatrix();
			}
		}
		else if (pDoc->m_currentDevice->m_down != NULL)
		{
			pDoc->m_deviceList = pDoc->m_currentDevice->m_down;
			pDoc->m_currentDevice->m_down->m_up = NULL;
			sprintf(pDoc->m_currentDevice->m_down->m_parent, "NONE");
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadIdentity();
			pView->YoTxyz(pDoc->m_currentDevice->m_ptrPart,
				pDoc->m_currentDevice->m_ptrPart->m_translate,
				pDoc->m_currentDevice->m_ptrPart->m_rotate);
			pView->YoTxyz(pDoc->m_currentDevice->m_down->m_ptrPart,
				pDoc->m_currentDevice->m_down->m_ptrPart->m_translate,
				pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate);		
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			pDoc->m_currentDevice->m_down->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
			pDoc->YoTranslateRotateValues(m,
				pDoc->m_currentDevice->m_down->m_ptrPart->m_translate,
				pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate);
			for (i = 0; i < 3; i++)
			{
				pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}
			::glPopMatrix();
		}
	}
	else
	{
		for (ptrDevice = pDoc->m_deviceList;
			ptrDevice->m_right != NULL;
			ptrDevice = ptrDevice->m_right);
		if (pDoc->m_currentDevice->m_right != NULL)
		{
			pDoc->m_currentDevice->m_right->m_left = ptrDevice;
			ptrDevice->m_right = pDoc->m_currentDevice->m_right; 
			if (pDoc->m_currentDevice->m_down != NULL)
			{
				for (ptrDevice = ptrDevice;
					ptrDevice->m_right != NULL;
					ptrDevice = ptrDevice->m_right);
				pDoc->m_currentDevice->m_down->m_left = ptrDevice;
				ptrDevice->m_right = pDoc->m_currentDevice->m_down;
				pDoc->m_currentDevice->m_down->m_up = NULL;
				sprintf(pDoc->m_currentDevice->m_down->m_parent, "NONE");
				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				::glLoadIdentity();
				pView->YoTxyz(pDoc->m_currentDevice->m_ptrPart,
					pDoc->m_currentDevice->m_ptrPart->m_translate,
					pDoc->m_currentDevice->m_ptrPart->m_rotate);
				pView->YoTxyz(pDoc->m_currentDevice->m_down->m_ptrPart,
					pDoc->m_currentDevice->m_down->m_ptrPart->m_translate,
					pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate);		
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				pDoc->m_currentDevice->m_down->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
				pDoc->YoTranslateRotateValues(m,
					pDoc->m_currentDevice->m_down->m_ptrPart->m_translate,
					pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate);
				for (i = 0; i < 3; i++)
				{
					pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
				}
				::glPopMatrix();
			}
		}
		else if (pDoc->m_currentDevice->m_down != NULL)
		{
			ptrDevice->m_right = pDoc->m_currentDevice->m_down;
			pDoc->m_currentDevice->m_down->m_left = ptrDevice;
			pDoc->m_currentDevice->m_down->m_up = NULL;
			sprintf(pDoc->m_currentDevice->m_down->m_parent, "NONE");
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadIdentity();
			pView->YoTxyz(pDoc->m_currentDevice->m_ptrPart,
				pDoc->m_currentDevice->m_ptrPart->m_translate,
				pDoc->m_currentDevice->m_ptrPart->m_rotate);
			pView->YoTxyz(pDoc->m_currentDevice->m_down->m_ptrPart,
				pDoc->m_currentDevice->m_down->m_ptrPart->m_translate,
				pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate);		
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			pDoc->m_currentDevice->m_down->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
			pDoc->YoTranslateRotateValues(m,
				pDoc->m_currentDevice->m_down->m_ptrPart->m_translate,
				pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate);
			for (i = 0; i < 3; i++)
			{
				pDoc->m_currentDevice->m_down->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}
			::glPopMatrix();
		}
	}

	// if device to be deleted is a light, then remove it from light list
	if (pDoc->m_currentDevice->m_type == YO_LIGHT)
	{
		::glDisable(((CStageLight *)pDoc->m_currentDevice)->m_target);
		for (ptrLight = pDoc->m_lightList;
			ptrLight != (CStageLight *)pDoc->m_currentDevice
			&& ptrLight->m_ptrLight != NULL
			&& ptrLight->m_ptrLight != (CStageLight *)pDoc->m_currentDevice;
			ptrLight = ptrLight->m_ptrLight);
		if (ptrLight == (CStageLight *)pDoc->m_currentDevice)
		{
			pDoc->m_lightList = ptrLight->m_ptrLight;
		}
		else
		{
			ptrLight->m_ptrLight = ((CStageLight *)pDoc->m_currentDevice)->m_ptrLight;
		}
	}

	delete (pDoc->m_currentDevice);
	pDoc->m_currentDevice = pDoc->m_deviceList;
	pDoc->m_currentPart = pDoc->m_currentDevice->m_ptrPart;
	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
	
}
***/

void CMainFrame::OnMove(int x, int y) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CFrameWnd::OnMove(x, y);
	
	pDoc->m_undo->YoUndo();

	YoMoveEyeDlg();
	return;	
}

void CMainFrame::OnSize320x240() 
{
	// TODO: Add your command handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	RECT rect;
	RECT vrect;
	char s[256];

	pDoc->m_undo->YoUndo();
	//sprintf(s, "Graphics window sized to 320 X 240 pixels");
	//pDoc->YoMessage(s);

	GetWindowRect(&rect);
	pView->GetWindowRect(&vrect);

	// note: pView border is 2 pixels on a side
	rect.right += (320 - (vrect.right - vrect.left) + 4);
	rect.bottom += (240 - (vrect.bottom - vrect.top) + 4);
	MoveWindow(&rect, TRUE);

	// sometimes one more pass is required because of double menu
	pView->GetWindowRect(&vrect);
	if ((vrect.bottom - vrect.top) != 244)
	{
		rect.bottom += (240 - (vrect.bottom - vrect.top) + 4);
	}
	MoveWindow(&rect, TRUE);
	YoMoveEyeDlg();

	sprintf(s, "Graphics window sized to %d X %d pixels",
		vrect.right - vrect.left - 4, vrect.bottom - vrect.top - 4);
	pDoc->YoMessage(s);
	/***
	if (320 <= pView->m_windowSize[0] && 240 <= pView->m_windowSize[1])
	{
		::glViewport(0, 0, 320, 240);
		pView->m_aspectRatio = 4.0 / 3.0;
	}
	else
	{
		::glViewport(0, 0, pView->m_windowSize[0], pView->m_windowSize[1]); 
		pView->m_aspectRatio = (GLdouble)pView->m_windowSize[0] /
			(GLdouble)pView->m_windowSize[1];
	}


	//pView->SendMessage(WM_SIZE, (WPARAM)320, (LPARAM)240);
	***/
	return;
	
}

void CMainFrame::OnSize640x480() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	RECT rect;
	RECT vrect;
	char s[256];

	pDoc->m_undo->YoUndo();
	//sprintf(s, "Graphics window sized to 640 X 480 pixels");
	//pDoc->YoMessage(s);

	GetWindowRect(&rect);
	pView->GetWindowRect(&vrect);

	// note: pView border is 2 pixels on a side
	rect.right += (640 - (vrect.right - vrect.left) + 4);
	rect.bottom += (480 - (vrect.bottom - vrect.top) + 4);
	MoveWindow(&rect, TRUE);

	// sometimes one more pass is required because of double menu
	pView->GetWindowRect(&vrect);
	if ((vrect.bottom - vrect.top) != 484)
	{
		rect.bottom += (480 - (vrect.bottom - vrect.top) + 4);
	}
	MoveWindow(&rect, TRUE);

	sprintf(s, "Graphics window sized to %d X %d pixels (VHS format)",
		vrect.right - vrect.left - 4, vrect.bottom - vrect.top - 4);
	pDoc->YoMessage(s);

	return;	
}




void CMainFrame::OnSize720x480() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	RECT rect;
	RECT vrect;
	char s[256];

	pDoc->m_undo->YoUndo();
	//sprintf(s, "Graphics window sized to 640 X 480 pixels");
	//pDoc->YoMessage(s);

	GetWindowRect(&rect);
	pView->GetWindowRect(&vrect);

	// note: pView border is 2 pixels on a side
	rect.right += (720 - (vrect.right - vrect.left) + 4);
	rect.bottom += (480 - (vrect.bottom - vrect.top) + 4);
	MoveWindow(&rect, TRUE);

	// sometimes one more pass is required because of double menu
	pView->GetWindowRect(&vrect);
	if ((vrect.bottom - vrect.top) != 484)
	{
		rect.bottom += (480 - (vrect.bottom - vrect.top) + 4);
	}
	MoveWindow(&rect, TRUE);

	sprintf(s, "Graphics window sized to %d X %d pixels (DVD format)",
		vrect.right - vrect.left - 4, vrect.bottom - vrect.top - 4);
	pDoc->YoMessage(s);

	return;	
	
}



void CMainFrame::OnSizeCustom() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	RECT rect;
	RECT vrect;
	CREATESTRUCT cs;
	CStageSizeCustom sizeCustom;
	char s[256];
	int width;
	int height;

	pDoc->m_undo->YoUndo();
	GetWindowRect(&rect);
	pView->GetWindowRect(&vrect);

	sizeCustom.m_sizeWidth = vrect.right - vrect.left - 4;
	sizeCustom.m_sizeHeight = vrect.bottom - vrect.top - 4;

	if (sizeCustom.DoModal() == IDOK)
	{
		cs.cy = ::GetSystemMetrics(SM_CYSCREEN); 
		cs.cx = ::GetSystemMetrics(SM_CXSCREEN); 
		
		height = YO_MAX(sizeCustom.m_sizeHeight, 80);
		height = YO_MIN(height, cs.cy - 156);
		width = YO_MAX(sizeCustom.m_sizeWidth, 120);
		width = YO_MIN(width, cs.cx - 69);

		// note: pView border is 2 pixels on a side
		rect.right += (width - (vrect.right - vrect.left) + 4);
		rect.bottom += (height - (vrect.bottom - vrect.top) + 4);
		MoveWindow(&rect, TRUE);

		// sometimes one more pass is required because of double menu
		pView->GetWindowRect(&vrect);
		if ((vrect.bottom - vrect.top) != height + 4)
		{
			rect.bottom += (height - (vrect.bottom - vrect.top) + 4);
		}
		MoveWindow(&rect, TRUE);

		sprintf(s, "Graphics window sized to %d X %d pixels",
			vrect.right - vrect.left - 4, vrect.bottom - vrect.top - 4);
		pDoc->YoMessage(s);
	}
	else
	{
		sprintf(s, "Graphics window remains at %d X %d pixels",
			vrect.right - vrect.left - 4, vrect.bottom - vrect.top - 4);
		pDoc->YoMessage(s);
	}

	return;
}

void CMainFrame::OnUpdateSize320x240(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if ((pDoc->m_mode == YO_MODE_WORKCELL
		&& m_wndDlgScript != NULL
		&& m_wndDlgScript->m_animationState == YO_PAUSE)
		|| (pDoc->m_mode == YO_MODE_PLAY_SIM
		&& pDoc->m_animationState == YO_PAUSE))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateSize640x480(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if ((pDoc->m_mode == YO_MODE_WORKCELL
		&& m_wndDlgScript != NULL
		&& m_wndDlgScript->m_animationState == YO_PAUSE)
		|| (pDoc->m_mode == YO_MODE_PLAY_SIM
		&& pDoc->m_animationState == YO_PAUSE))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateSize720x480(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if ((pDoc->m_mode == YO_MODE_WORKCELL
		&& m_wndDlgScript != NULL
		&& m_wndDlgScript->m_animationState == YO_PAUSE)
		|| (pDoc->m_mode == YO_MODE_PLAY_SIM
		&& pDoc->m_animationState == YO_PAUSE))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateSizeCustom(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if ((pDoc->m_mode == YO_MODE_WORKCELL
		&& m_wndDlgScript != NULL
		&& m_wndDlgScript->m_animationState == YO_PAUSE)
		|| (pDoc->m_mode == YO_MODE_PLAY_SIM
		&& pDoc->m_animationState == YO_PAUSE))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;	
}


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	if (m_init == FALSE)
	{
		return;
	}

	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];
	RECT vrect;
	static init = FALSE;

	CFrameWnd::OnSize(nType, cx, cy);

	pDoc->m_undo->YoUndo();

	pView->GetWindowRect(&vrect);
	// note: pView border is 2 pixels on a side

	if ((int)cx < YO_THRESH_WIDTH && m_wndDlgEyeVisible == TRUE && m_wndDlgEye != NULL)
	{
		m_wndDlgEye->ShowWindow(SW_HIDE);
	}
	else if ((int)cx >= YO_THRESH_WIDTH && m_wndDlgEyeVisible == TRUE && m_wndDlgEye != NULL)
	{
		m_wndDlgEyeVisible = FALSE;
		//YoMoveEyeDlg();
		SendMessage(WM_COMMAND, IDC_EYE, (LPARAM)0);
	}

	if (!init)
	{
		init = TRUE;
	}
	else
	{
		sprintf(s, "Graphics window sized to %d X %d pixels",
			vrect.right - vrect.left - 4, vrect.bottom - vrect.top - 4);
		pDoc->YoMessage(s);
	}

	return;
}


void CMainFrame::OnMotionInsertPartAnchor() 
{
	/***
	// TODO: Add your command handler code here
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageMotion *ptrMotion;
	int i;

	if (!pView )
	{
		return;
	}
	// Fail if view is of wrong kind
	
	if (!pView->IsKindOf(RUNTIME_CLASS(CStageView))) 
	{
		return;
	}
	pDoc->m_undo->YoUndo();
	ptrMotion = new CStageMotion(pDoc);
	ptrMotion->m_time = pDoc->m_timeCurrent;
	ptrMotion->m_type = YO_MOTION_ANCHOR;

	for (i = 0; i < 3; i++)
	{
		ptrMotion->m_translate[i] = pDoc->m_currentPart->m_translate[i];
		ptrMotion->m_rotate[i] = pDoc->m_currentPart->m_rotate[i];
	}

	pDoc->YoInsertPartMotion(ptrMotion, pDoc->m_currentPart);
	***/
	return;	
}


void CMainFrame::OnMotionInsertPartHold() 
{

	/***
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageMotion *ptrMotion;
	int i;

	if (!pView )
	{
		return;
	}
	// Fail if view is of wrong kind
	
	if (!pView->IsKindOf(RUNTIME_CLASS(CStageView))) 
	{
		return;
	}
	pDoc->m_undo->YoUndo();
	ptrMotion = new CStageMotion(pDoc);
	ptrMotion->m_time = pDoc->m_timeCurrent;
	ptrMotion->m_type = YO_MOTION_HOLD;

	for (i = 0; i < 3; i++)
	{
		ptrMotion->m_translate[i] = pDoc->m_currentPart->m_translate[i];
		ptrMotion->m_rotate[i] = pDoc->m_currentPart->m_rotate[i];
	}

	pDoc->YoInsertPartMotion(ptrMotion, pDoc->m_currentPart);
	***/
	return;		
}


void CMainFrame::OnMotionViewPartHistory() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStagePartMotion partMotionViewHistory;

	pDoc->m_undo->YoUndo();

	if (partMotionViewHistory.DoModal() == IDOK)
	{
	}
	
}

void CMainFrame::OnUpdateDeviceAttach(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;	
}

void CMainFrame::OnUpdateDeviceChoose(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}


void CMainFrame::OnUpdateDeviceClone(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))

	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}


void CMainFrame::OnUpdateDeviceDelete(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))

	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}


void CMainFrame::OnUpdateDeviceDetach(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}


void CMainFrame::OnUpdateDeviceRename(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		//&& m_viewPartActive == FALSE
		//&& m_analysisActive == FALSE
		//&& m_viewTagActive == FALSE
		//&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& pDoc->m_undo->m_undoMode != YO_UNDO_OFF)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;
}


void CMainFrame::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}


void CMainFrame::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;
}


void CMainFrame::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pCmdUI->Enable(FALSE);
	/***
	// TODO: Add your command update UI handler code here
	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	***/
	return;	
}


void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pCmdUI->Enable(FALSE);
	/***
	// TODO: Add your command update UI handler code here
	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	***/
	return;	
}


void CMainFrame::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pCmdUI->Enable(FALSE);
	/***
	// TODO: Add your command update UI handler code here
	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	***/
	return;		
}


void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;	
}


void CMainFrame::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;	
}


void CMainFrame::OnUpdateFileSaveCopyAs(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;	
}


void CMainFrame::OnUpdateFileUpdate(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;
}


void CMainFrame::OnUpdateMotionInsertAnchor(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pCmdUI->Enable(FALSE);
	/***
	// TODO: Add your command update UI handler code here
	if (pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	***/
	return;	
}

void CMainFrame::OnUpdateMotionInsertHold(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pCmdUI->Enable(FALSE);
	/***
	// TODO: Add your command update UI handler code here
	if (pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	***/
	return;	
}

void CMainFrame::OnUpdateMotionInsertPartAnchor(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pCmdUI->Enable(FALSE);
	/****
	// TODO: Add your command update UI handler code here
	if (pDoc->m_currentPart != NULL && pDoc->m_currentDevice != NULL
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	****/
	return;	
}

void CMainFrame::OnUpdateMotionInsertPartHold(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pCmdUI->Enable(FALSE);
	/***
	// TODO: Add your command update UI handler code here
	if (pDoc->m_currentPart != NULL && pDoc->m_currentDevice != NULL
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	***/
	return;	
}

void CMainFrame::OnUpdateMotionViewHistory(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pCmdUI->Enable(FALSE);
	/***
	// TODO: Add your command update UI handler code here
	if (pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	***/
	return;	
}

void CMainFrame::OnUpdateMotionViewPartHistory(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pCmdUI->Enable(FALSE);
	/****
	// TODO: Add your command update UI handler code here
	if (pDoc->m_currentPart != NULL && pDoc->m_currentDevice != NULL
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	***/
	return;	
}

void CMainFrame::OnUpdatePrefs(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)

	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;	
}

void CMainFrame::OnUpdateViewDeviceTree(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);

	return;
}


void CMainFrame::OnUpdateDeviceCreate(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnPartAttach() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CString s;
	char t[256];
	int i;
	CStagePart *ptrPart;

	pDoc->m_undo->YoUndo();

	// choose a base part file
	CFileDialog choosePart
		(TRUE,    // open
		NULL,    // no default extension
		NULL,    // file name
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		//"Stage Part files (*.PRT)|*.PRT|All files (*.*)|*.*||");
		"All files (*.*)|*.*|Stage Part files (*.PRT)|*.PRT||");

	sprintf(t, "Attach part to %s", pDoc->m_currentPart->m_partName);
	choosePart.m_ofn.lpstrTitle = t;

	sprintf(t, "Attaching part from file to %s...", pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(t);

	if (choosePart.DoModal() == IDOK)
	{
		ptrPart = new CStagePart(pDoc);
		ptrPart->YoInitPart(ptrPart);
		ptrPart->m_displayListID = pDoc->YoGetNewDisplayListID(ptrPart, NULL);

		sprintf(ptrPart->m_deviceName, "%s", pDoc->m_currentDevice->m_name);
		sprintf(ptrPart->m_partParent, "%s", pDoc->m_currentPart->m_partName);
		ptrPart->m_renderMode = pDoc->m_currentPart->m_renderMode;
		for (i = 0; i < 4; i++)
		{
			ptrPart->m_ambient[i] = pDoc->m_currentPart->m_ambient[i];
			ptrPart->m_diffuse[i] = pDoc->m_currentPart->m_diffuse[i];
			ptrPart->m_specular[i] = pDoc->m_currentPart->m_specular[i];
			ptrPart->m_emission[i] = pDoc->m_currentPart->m_emission[i];
			ptrPart->m_wireframe[i] = pDoc->m_currentPart->m_wireframe[i];
		}
		ptrPart->m_shininess = pDoc->m_currentPart->m_shininess;

		s = choosePart.GetFileTitle();
		sprintf(ptrPart->m_partName, "%s", (LPCSTR)s);
		while (pDoc->YoPartLookup(pDoc->m_currentDevice, ptrPart->m_partName) != NULL)
		{
			sprintf(ptrPart->m_partName, "%sx", ptrPart->m_partName);
		}
			
		s = choosePart.GetPathName();
		sprintf(ptrPart->m_partFile, "%s", (LPCSTR)s);
		pDoc->m_currentPart = ptrPart;
		pDoc->YoInsertPart(pDoc->m_currentDevice, ptrPart);
		if (ptrPart->YoReadPartFile(ptrPart->m_partFile) == FALSE)
		{
			sprintf(t, "Part not attached.  Error reading part file:\n   %s\nIncorrect file format or corrupt data encountered.",
				s);
			AfxMessageBox(t);
			pDoc->YoDeletePart();
			sprintf(t, "Part attach aborted.");
			pDoc->YoMessage(t);
			return;
		}
		pView->YoRender(YO_RENDER_FULL);
		sprintf(t, "Part: %s successfully attached.", pDoc->m_currentPart->m_partName);
		pDoc->YoMessage(t);

	}
	else
	{
		sprintf(t, "Part attach aborted.");
		pDoc->YoMessage(t);
	}

	return;		
}

void CMainFrame::OnUpdatePartAttach(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;
}

void CMainFrame::OnPartChoose() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseDevice chooseDevice;
	char s[256];

	pDoc->m_undo->YoUndo();
	sprintf(s, "Selecting part...");
	pDoc->YoMessage(s);
	m_dialogChooseNameTitle = "Choose Part";

	if (chooseDevice.DoModal() == IDOK)
	{
		sprintf(s, "Device: %s   Part: %s",
			pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
		pDoc->YoMessage(s);
	}
	else
	{
		sprintf(s, "Choose part aborted.");
		pDoc->YoMessage(s);
	}
	
	return;
}

void CMainFrame::OnUpdatePartChoose(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnPartDelete() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];

	pDoc->m_undo->YoUndo();

	if (pDoc->m_currentDevice == NULL || pDoc->m_currentPart == NULL)
	{
		return;
	}

	sprintf(s, "Part %s and all of its siblings deleted.", pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(s);

	if (pDoc->m_currentDevice->m_ptrPart == pDoc->m_currentPart)
	// base part, therefore delete device
	{
		pDoc->m_undo->m_undoMode = YO_UNDO_DEVICE_DELETE;
		pDoc->m_undo->m_undoDeviceDelete = pDoc->m_currentDevice;
		pDoc->m_currentDevice->m_visible = FALSE;
		if (pDoc->m_undo->m_undoDeviceDelete->m_type == YO_LIGHT)
		{
			((CStageLight *)pDoc->m_undo->m_undoDeviceDelete)->m_enabled = FALSE;
		}
	}
	else
	{
		pDoc->m_undo->m_undoMode = YO_UNDO_PART_DELETE;
		pDoc->m_undo->m_undoPartDelete = pDoc->m_currentPart;
	}

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	return;
}


void CMainFrame::OnUpdatePartDelete(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		//&& pDoc->m_currentPart != pDoc->m_currentDevice->m_ptrPart
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_currentDevice->m_type == YO_DEVICE
		|| pDoc->m_currentDevice->m_type == YO_LIGHT
		|| pDoc->m_currentDevice->m_type == YO_CAMERA
		|| pDoc->m_currentDevice->m_type == YO_TRAIN)
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnPartRename() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseName chooseName;
	char s[512];

	pDoc->m_undo->YoUndo();
	sprintf(s, "Enter a new name for %s...", pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(s);
	m_dialogChooseNameTitle = "Rename Part";

	if (chooseName.DoModal() == IDOK)
	{
		sprintf(s, "Device: %s   Renamed part: %s",
			pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
		pDoc->YoMessage(s);
	}
	else
	{
		sprintf(s, "Rename part aborted.");
		pDoc->YoMessage(s);
	}

	return;	
}

void CMainFrame::OnUpdatePartRename(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_currentDevice->m_type == YO_DEVICE
		|| pDoc->m_currentDevice->m_type == YO_LIGHT
		|| pDoc->m_currentDevice->m_type == YO_CAMERA
		|| pDoc->m_currentDevice->m_type == YO_TRAIN)
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnPartUpdate() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CString s;
	char t[256];
	int i;
	//CStagePolygonList *currentPolygonList;
	//CStagePolygonList *ptrPolygonList;
	//CStageVertexList *currentVertexList;
	//CStageVertexList *ptrVertexList;
	//CStageVertices *currentVertices;
	//CStageVertices *ptrVertices;
	//CStageTexture *currentTexture;
	//CStageTexture *ptrTexture;
	//CStageTextureCoords *currentTextureCoords;
	//CStageTextureCoords *ptrTextureCoords;
	CStagePart *ptrPart;
	CStagePart *ptrUpdatePart;
	CStagePart *curPart;
	CStagePart *prevPart = NULL;
	CStagePath *ptrPath;

	ptrPart = pDoc->m_currentPart;

	pDoc->m_undo->YoUndo();
	sprintf(t, "Replacing %s with an updated part...", pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(t);

	// choose a base part file
	CFileDialog choosePart
		(TRUE,    // open
		NULL,    // no default extension
		NULL,    // file name
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		//"Stage Part files (*.PRT)|*.PRT|All files (*.*)|*.*||");
		"All files (*.*)|*.*|Stage Part files (*.PRT)|*.PRT||");

	sprintf(t, "Update %s with...", pDoc->m_currentPart->m_partName);
	choosePart.m_ofn.lpstrTitle = t;

	if (choosePart.DoModal() == IDOK)
	{
		/***
		for (currentVertexList = pDoc->m_currentPart->m_vertexList; currentVertexList != NULL;)
		{
			ptrVertexList = currentVertexList;
			currentVertexList = currentVertexList->m_next;
			delete(ptrVertexList);
		}
		pDoc->m_currentPart->m_vertexList = NULL;
		pDoc->m_currentPart->m_numberVertices = 0;

		currentPolygonList = pDoc->m_currentPart->m_polygonList;
		for (i = 0; i < pDoc->m_currentPart->m_numberPolygons; i++)
		{
			for (currentVertices = currentPolygonList->m_vertices[i % 10]; currentVertices != NULL;)
			{
				ptrVertices = currentVertices;
				currentVertices = currentVertices->m_next;
				delete(ptrVertices);
			}
			if (currentPolygonList->m_texture[i % 10] != NULL)
			{
				// clean up after the AUX function
				if (currentPolygonList->m_texture[i % 10]->m_RGBImage != NULL)
				{
					//use same routine that allocated it
					//LocalFree(currentPolygonList->m_texture[i % 10]->m_RGBImage);
				}
				for (currentTextureCoords = currentPolygonList->m_texture[i % 10]->m_textureCoords;
					currentTextureCoords != NULL;)
				{
					ptrTextureCoords = currentTextureCoords;
					currentTextureCoords = currentTextureCoords->m_next;
					delete(ptrTextureCoords);
				}
				delete(currentPolygonList->m_texture[i % 10]);
			}
			if (i % 10 == 9 && i != pDoc->m_currentPart->m_numberPolygons - 1)
			{
				ptrPolygonList = currentPolygonList;
				currentPolygonList = currentPolygonList->m_next;
				delete(ptrPolygonList);
			}
		}

		delete(currentPolygonList);
		pDoc->m_currentPart->m_polygonList = NULL;
		pDoc->m_currentPart->m_numberPolygons = 0;

		pDoc->m_currentPart->m_min[0] = FLT_MAX;
		pDoc->m_currentPart->m_min[1] = FLT_MAX;
		pDoc->m_currentPart->m_min[2] = FLT_MAX;
		pDoc->m_currentPart->m_max[0] = -FLT_MAX;
		pDoc->m_currentPart->m_max[1] = -FLT_MAX;
		pDoc->m_currentPart->m_max[2] = -FLT_MAX;

		s = choosePart.GetPathName();
		sprintf(pDoc->m_currentPart->m_partFile, "%s", (LPCSTR)s);
		if (pDoc->m_currentPart->YoReadPartFile(pDoc->m_currentPart->m_partFile) == FALSE)
		{
			pDoc->YoDeletePart();
			return;
		}
		***/

		ptrUpdatePart = new CStagePart(pDoc);
		ptrUpdatePart->YoInitPart(ptrUpdatePart);
		pDoc->m_currentPart = ptrUpdatePart;

		s = choosePart.GetPathName();
		sprintf(ptrUpdatePart->m_partFile, "%s", (LPCSTR)s);
		if (ptrUpdatePart->YoReadPartFile(ptrUpdatePart->m_partFile) == FALSE)
		{
			sprintf(t, "Error: Part update failed while reading file.\nIncorrect file format or corrupt data encountered.");
			AfxMessageBox(t);
			delete ptrUpdatePart;
			return;
		}

		ptrUpdatePart->m_displayListID = ptrPart->m_displayListID;
		sprintf(ptrUpdatePart->m_deviceName, "%s", ptrPart->m_deviceName);
		sprintf(ptrUpdatePart->m_partName, "%s", ptrPart->m_partName);
		sprintf(ptrUpdatePart->m_partParent, "%s", ptrPart->m_partParent);
		ptrUpdatePart->m_renderMode = ptrPart->m_renderMode;
		ptrUpdatePart->m_txyz = ptrPart->m_txyz;
		//ptrUpdatePart->m_wireframeDisplayListID = ptrPart->m_wireframeDisplayListID;

		ptrUpdatePart->m_originVisible = ptrPart->m_originVisible;
		for (i = 0; i < 16; i++)
		{
			ptrUpdatePart->m_altOrigin[i] = ptrPart->m_altOrigin[i];
		}
		ptrUpdatePart->m_altOriginDisplayed = ptrPart->m_altOriginDisplayed;

		for (i = 0; i < 3; i++)
		{
			ptrUpdatePart->m_translate[i] = ptrPart->m_translate[i];
			ptrUpdatePart->m_rotate[i] = ptrPart->m_rotate[i];
		}

		for (i = 0; i < 4; i++)
		{
			ptrUpdatePart->m_ambient[i] = ptrPart->m_ambient[i];
			ptrUpdatePart->m_diffuse[i] = ptrPart->m_diffuse[i];
			ptrUpdatePart->m_specular[i] = ptrPart->m_specular[i];
			ptrUpdatePart->m_emission[i] = ptrPart->m_emission[i];
			ptrUpdatePart->m_wireframe[i] = ptrPart->m_wireframe[i];
		}
		ptrUpdatePart->m_shininess = ptrPart->m_shininess;

		for (curPart = pDoc->m_pickPart[ptrPart->m_displayListID % YO_HASH_SIZE];
			curPart != ptrPart;)
		{
			prevPart = curPart;
			curPart = curPart->m_pick;
		}
		if (prevPart == NULL)
		{
			pDoc->m_pickPart[ptrPart->m_displayListID % YO_HASH_SIZE] = ptrUpdatePart;
		}
		else
		{
			prevPart->m_pick = ptrUpdatePart;
		}
		ptrUpdatePart->m_pick = ptrPart->m_pick;
		ptrPart->m_pick = NULL;

		if (ptrPart->m_attachedDevice != NULL)
		{
			ptrPart->m_attachedDevice->m_attachedFromPart = ptrUpdatePart;
		}
		ptrUpdatePart->m_attachedDevice = ptrPart->m_attachedDevice;
		ptrPart->m_attachedDevice = NULL;

		for (ptrPath = ptrPart->m_path; ptrPath != NULL; ptrPath = ptrPath->m_nextPath)
		{
			ptrPath->m_ptrPart = ptrUpdatePart;
		}
		ptrUpdatePart->m_path = ptrPart->m_path;
		ptrPart->m_path = NULL;

		if (ptrPart->m_up != NULL)
		{
			ptrUpdatePart->m_up = ptrPart->m_up;
			ptrPart->m_up->m_down = ptrUpdatePart;
			ptrPart->m_up = NULL;
		}
		if (ptrPart->m_down != NULL)
		{
			ptrUpdatePart->m_down = ptrPart->m_down;
			ptrPart->m_down->m_up = ptrUpdatePart;
			ptrPart->m_down = NULL;
		}
		if (ptrPart->m_left != NULL)
		{
			ptrUpdatePart->m_left = ptrPart->m_left;
			ptrPart->m_left->m_right = ptrUpdatePart;
			ptrPart->m_left = NULL;
		}
		if (ptrPart->m_right != NULL)
		{
			ptrUpdatePart->m_right = ptrPart->m_right;
			ptrPart->m_right->m_left = ptrUpdatePart;
			ptrPart->m_right = NULL;
		}
		
		if (pDoc->m_currentDevice->m_ptrPart == ptrPart)
		{
			pDoc->m_currentDevice->m_ptrPart = ptrUpdatePart;
		}
		pDoc->m_undo->m_undoMode = YO_UNDO_PART_UPDATE;
		pDoc->m_undo->m_undoPartDelete = ptrPart;

		sprintf(t, "Part %s successfully updated.", pDoc->m_currentPart->m_partName);
		pDoc->YoMessage(t);

		this->RedrawWindow();
		//pView->YoRender(YO_RENDER_FULL);
	}
	else
	{
		sprintf(t, "Part update aborted.");
		pDoc->YoMessage(t);
	}

	return;		
}

void CMainFrame::OnUpdatePartUpdate(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& pDoc->m_currentDevice->m_type != YO_TRACK
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnHelpAnalysis() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];


	pDoc->m_undo->YoUndo();
	sprintf(s, "Find measurements between devices, parts, vertices, polygons, etc...");
	pDoc->YoMessage(s);

	m_analysis = new CStageAnalysisDlg;
	m_analysis->YoInitDialog();
	m_analysisActive = TRUE;
	m_analysis->ShowWindow(SW_SHOW);
	SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)m_hCursorSelect);

	return;

}

void CMainFrame::OnUpdateHelpAnalysis(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnTagChoose() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseDevice chooseDevice;
	char s[256];

	pDoc->m_undo->YoUndo();
	sprintf(s, "Selecting tag...");
	pDoc->YoMessage(s);

	m_dialogChooseNameTitle = "Choose Tag";

	if (chooseDevice.DoModal() == IDOK)
	{
		sprintf(s, "Path: %s   Tag: %d",
			pDoc->m_currentTag->m_ptrPath->m_name, pDoc->m_currentTag->m_tag);
		pDoc->YoMessage(s);
	}
	else
	{
		sprintf(s, "Choose tag aborted.");
		pDoc->YoMessage(s);
	}

	return;	
}

void CMainFrame::OnTagCreate() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageTag *ptrTag;
	int i;
	char s[256];

	pDoc->m_undo->YoUndo();

	if (pDoc->m_currentTag == NULL)
	{
		return;
	}

	ptrTag = new CStageTag(pDoc);

	for (i = 0; i < 3; i++)
	{
		ptrTag->m_translate[i] = 0.0f;
		ptrTag->m_rotate[i] = 0.0f;
	}
	
	ptrTag->m_ptrPath = pDoc->m_currentTag->m_ptrPath;
	ptrTag->m_tag = UINT_MAX;
	pDoc->m_currentTag->m_ptrPath->YoInsertTag(ptrTag);

	sprintf(s, "Tag %d created on path %s.", ptrTag->m_tag, ptrTag->m_ptrPath->m_name);
	pDoc->YoMessage(s);

	pView->YoRender(YO_RENDER_FULL);
	return;
}

void CMainFrame::OnTagDelete() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];

	pDoc->m_undo->YoUndo();

	if (pDoc->m_currentTag == NULL)
	{
		return;
	}

	sprintf(s, "Tag %d deleted from path %s.", pDoc->m_currentTag->m_tag, pDoc->m_currentTag->m_ptrPath->m_name);
	pDoc->YoMessage(s);

	if (pDoc->m_currentTag->m_nextTag == NULL && pDoc->m_currentTag->m_prevTag == NULL)
	// last tag in path
	{
		pDoc->m_undo->m_undoMode = YO_UNDO_PATH_DELETE;
		pDoc->m_undo->m_undoTagDelete = pDoc->m_currentTag;
		pDoc->m_undo->m_undoTagDelete->m_ptrPath->m_visible = FALSE;
	}
	else
	{
		pDoc->m_undo->m_undoMode = YO_UNDO_TAG_DELETE;
		pDoc->m_undo->m_undoTagDelete = pDoc->m_currentTag;
	}

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;


/***
	dTag = pDoc->m_currentTag;

	if (dTag->m_nextTag == NULL && dTag->m_prevTag == NULL)
	// last tag in the path
	{
		dTag->m_ptrPath->YoDeleteTag(dTag);
		// try to find another path associated with m_currentPart
		if (pDoc->m_currentPart->m_path != NULL)
		{
			pDoc->m_currentTag = pDoc->m_currentPart->m_path->m_ptrTag;
			pView->YoRender(YO_RENDER_FULL);
			return;
		}
		// try to find any path
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			if (pDoc->m_pathHash[i] != NULL)
			{
				pDoc->m_currentTag = pDoc->m_pathHash[i]->m_ptrTag;
				pView->YoRender(YO_RENDER_FULL);
				return;
			}
		}
		pDoc->m_currentTag = NULL;
		pView->YoRender(YO_RENDER_FULL);
		return;
	}
	else if (dTag->m_nextTag != NULL)
	{
		pDoc->m_currentTag = dTag->m_nextTag;
		dTag->m_ptrPath->YoDeleteTag(dTag);
		pView->YoRender(YO_RENDER_FULL);
		return;
	}
	else if (dTag->m_prevTag != NULL)
	{
		pDoc->m_currentTag = dTag->m_prevTag;
		dTag->m_ptrPath->YoDeleteTag(dTag);
		pView->YoRender(YO_RENDER_FULL);
		return;
	}
***/

/***
	pDoc->m_currentTag->m_ptrPath->YoDeleteTag(pDoc->m_currentTag);

	dTag = pDoc->m_currentTag;

	if (dTag == NULL)
	{
		return;
	}
	
	if (dTag == dTag->m_ptrPath->m_ptrTag)
	{
		if (dTag->m_nextTag != NULL)
		{
			dTag->m_nextTag->m_prevTag = NULL;
			pDoc->m_currentTag = dTag->m_nextTag;
		}
		dTag->m_ptrPath->m_ptrTag = dTag->m_nextTag;
		pDoc->m_currentTag = NULL;
	}
	else
	{
		if (dTag->m_nextTag != NULL)
		{
			dTag->m_nextTag->m_prevTag = dTag->m_prevTag;
			pDoc->m_currentTag = dTag->m_nextTag;
		}
		dTag->m_prevTag->m_nextTag = dTag->m_nextTag;
		pDoc->m_currentTag = dTag->m_prevTag;
	}

	delete dTag;

	if (pDoc->m_currentTag == NULL)
	{
		delete ptrPath;
		// try to find another path associated with m_currentPart
		if (pDoc->m_currentPart->m_path != NULL)
		{
			pDoc->m_currentTag = pDoc->m_currentPart->m_path->m_ptrTag;
		}
		// try to find any path
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			if (pDoc->m_pathHash[i] != NULL)
			{
				pDoc->m_currentTag = pDoc->m_pathHash[i]->m_ptrTag;
				break;
			}
		}
	}

	return;	
***/
}

void CMainFrame::OnTagDeletePath() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	//CStageTag *dTag;
	//CStageTag *ptrTag;
	//int i;
	char s[256];

	pDoc->m_undo->YoUndo();

	if (pDoc->m_currentTag == NULL)
	{
		return;
	}

	sprintf(s, "Path %s deleted.", pDoc->m_currentTag->m_ptrPath->m_name);
	pDoc->YoMessage(s);

	pDoc->m_undo->m_undoMode = YO_UNDO_PATH_DELETE;
	pDoc->m_undo->m_undoTagDelete = pDoc->m_currentTag;
	pDoc->m_undo->m_undoTagDelete->m_ptrPath->m_visible = FALSE;

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);

	return;
	
	/***
	ptrTag = pDoc->m_currentTag->m_ptrPath->m_ptrTag;

	while (ptrTag != NULL)
	{
		dTag = ptrTag;
		ptrTag = ptrTag->m_nextTag;
		dTag->m_ptrPath->YoDeleteTag(dTag);
	}

	// try to find another path associated with m_currentPart
	if (pDoc->m_currentPart->m_path != NULL)
	{
		pDoc->m_currentTag = pDoc->m_currentPart->m_path->m_ptrTag;
		pView->YoRender(YO_RENDER_FULL);
		return;
	}
	// try to find any path
	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		if (pDoc->m_pathHash[i] != NULL)
		{
			pDoc->m_currentTag = pDoc->m_pathHash[i]->m_ptrTag;
			pView->YoRender(YO_RENDER_FULL);
			return;
		}
	}

	pDoc->m_currentTag = NULL;
	pView->YoRender(YO_RENDER_FULL);
	return;
	***/
}

void CMainFrame::OnTagNewPath() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseName chooseName;
	CString s;
	CStagePath *ptrPath;
	CStageTag *ptrTag;
	int i;
	char t[256];

	pDoc->m_undo->YoUndo();
	sprintf(t, "Constructing new path and attaching it to Device: %s   Part %s...",
		pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(t);

	m_dialogChooseNameTitle = "Create Path";

	if (chooseName.DoModal() != IDOK)
	{
		sprintf(t, "Create path aborted.");
		pDoc->YoMessage(t);
		return;
	}

	ptrPath = new CStagePath(pDoc);
	ptrPath->YoInitPath(pDoc->m_currentPart);

	sprintf(ptrPath->m_name, "%s", chooseName.m_editName);
	pDoc->YoPathHashInstall(ptrPath);

	ptrTag = new CStageTag(pDoc);
	ptrTag->m_tag = 1;
	for (i = 0; i < 3; i++)
	{
		ptrTag->m_translate[i] = 0.0f;
		ptrTag->m_rotate[i] = 0.0f;
	}
	ptrTag->m_ptrPath = ptrPath;
	ptrPath->YoInsertTag(ptrTag);
	pDoc->m_currentTag = ptrTag;

	pView->YoRender(YO_RENDER_FULL);

	sprintf(t, "New Path: %s   Tag: %d created and attached to Device: %s   Part: %s",
		pDoc->m_currentTag->m_ptrPath->m_name, pDoc->m_currentTag->m_tag,
		pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(t);

	return;		
}

void CMainFrame::OnTagReattachPath() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageTag *ptrTag;
	CStageTag *currentTag;
	CStagePath *ptrPath;
	CStagePath *prevPath = NULL;
	GLdouble m[16];
	GLdouble mInv[16];
	int i;
	char s[256];

	pDoc->m_undo->YoUndo();

	if (pDoc->m_currentPart == pDoc->m_currentTag->m_ptrPath->m_ptrPart)
	{
		sprintf(s, "Path %s attached to Device: %s   Part: %s", pDoc->m_currentTag->m_ptrPath->m_name,
			pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
		pDoc->YoMessage(s);
		return;
	}

	currentTag = pDoc->m_currentTag;
	pDoc->YoModelMatrixOfCurrentPart(m);
	pDoc->YoMatrixInverse(m, mInv);
	::glMatrixMode(GL_MODELVIEW);

	for (ptrTag = pDoc->m_currentTag->m_ptrPath->m_ptrTag;
		ptrTag != NULL; ptrTag = ptrTag->m_nextTag)
	{
		pDoc->m_currentTag = ptrTag;
		pDoc->YoModelMatrixOfCurrentTag();
		::glPushMatrix();
		::glLoadMatrixd(mInv);
		::glMultMatrixd(pDoc->m_mTag);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);

		pDoc->YoTranslateRotateValues(m,
			ptrTag->m_translate,
			ptrTag->m_rotate);
		for (i = 0; i < 3; i++)
		{
			ptrTag->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
		}
		::glPopMatrix();
	}

	pDoc->m_currentTag = currentTag;

	// relink paths of previous part
	for (ptrPath = pDoc->m_currentTag->m_ptrPath->m_ptrPart->m_path; ptrPath != pDoc->m_currentTag->m_ptrPath;)
	{
		prevPath = ptrPath;
		ptrPath = ptrPath->m_nextPath;
	}
	if (prevPath == NULL)
	{
		pDoc->m_currentTag->m_ptrPath->m_ptrPart->m_path = pDoc->m_currentTag->m_ptrPath->m_nextPath;
	}
	else
	{
		prevPath->m_nextPath = pDoc->m_currentTag->m_ptrPath->m_nextPath;
	}

	pDoc->m_currentTag->m_ptrPath->m_ptrPart = pDoc->m_currentPart;
	pDoc->m_currentTag->m_ptrPath->m_nextPath = pDoc->m_currentPart->m_path;
	pDoc->m_currentPart->m_path = pDoc->m_currentTag->m_ptrPath;

	sprintf(s, "Path %s reattached to Device: %s   Part: %s", pDoc->m_currentTag->m_ptrPath->m_name,
		pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
	pDoc->YoMessage(s);
	return;
}

void CMainFrame::OnTagRenamePath() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseName chooseName;
	char s[256];

	pDoc->m_undo->YoUndo();
	sprintf(s, "Enter a new name for %s...", pDoc->m_currentTag->m_ptrPath->m_name);
	pDoc->YoMessage(s);
	m_dialogChooseNameTitle = "Rename Path";

	if (chooseName.DoModal() == IDOK)
	{
		sprintf(s, "Renamed path: %s   Tag: %d",
			pDoc->m_currentTag->m_ptrPath->m_name, pDoc->m_currentTag->m_tag);
		pDoc->YoMessage(s);
	}
	else
	{
		sprintf(s, "Rename path aborted.");
		pDoc->YoMessage(s);
	}
	return;	
}

void CMainFrame::OnTagTagOnTcf() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[256];

	pDoc->m_undo->YoUndo();

	if (pDoc->m_currentTag == NULL
		|| pDoc->m_currentDevice->m_type != YO_ROBOT6)
	{
		return;
	}

	((CStageRobot6 *)pDoc->m_currentDevice)->YoTagOnTcf();
	pView->YoRender(YO_RENDER_FULL);

	sprintf(s, "%s%d positioned on TCF of robot %s", pDoc->m_currentTag->m_ptrPath->m_name,
		pDoc->m_currentTag->m_tag, pDoc->m_currentDevice->m_name);
	pDoc->YoMessage(s);


	return;	
}


void CMainFrame::OnUpdateTagChoose(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& pDoc->m_currentTag != NULL
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL)
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_PATH_DELETE
		|| pDoc->m_numberOfPaths > 1))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateTagCreate(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& pDoc->m_currentTag != NULL
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL)
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_PATH_DELETE
		|| pDoc->m_numberOfPaths > 1))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateTagDelete(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& pDoc->m_currentTag != NULL
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL)
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_PATH_DELETE
		|| pDoc->m_numberOfPaths > 1))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateTagDeletePath(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& pDoc->m_currentTag != NULL
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL)
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_PATH_DELETE
		|| pDoc->m_numberOfPaths > 1))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateTagNewPath(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateTagReattachPath(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& pDoc->m_currentTag != NULL
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL)
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_PATH_DELETE
		|| pDoc->m_numberOfPaths > 1))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateTagRenamePath(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& pDoc->m_currentTag != NULL
		&& m_analysisActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL)
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_PATH_DELETE
		|| pDoc->m_numberOfPaths > 1))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateTagTagOnTcf(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& pDoc->m_currentDevice->m_type == YO_ROBOT6
		&& pDoc->m_currentTag != NULL
		&& m_analysisActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL)
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_PATH_DELETE
		|| pDoc->m_numberOfPaths > 1))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnDeviceImport() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageChooseName chooseName;
	char s[256];
	char t[64];
	//FILE *fp;
	//char command[32];
	//int done = FALSE;
	//int ch = 0;
	//int i;

	pDoc->m_undo->YoUndo();
	sprintf(s, "Reading a device from a file...");
	pDoc->YoMessage(s);

	m_dialogChooseNameTitle = "STEP 1: Import Device";

	if (chooseName.DoModal() != IDOK)
	{
		sprintf(s, "Import device aborted.");
		pDoc->YoMessage(s);
		return;
	}

	// choose a device file
	CFileDialog chooseDevice
		(TRUE,    // open
		NULL,    // no default extension
		NULL,    // file name
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		//"Stage Device files (*.DVC)|*.DVC|All files (*.*)|*.*||");
		"All files (*.*)|*.*|Stage Device files (*.DVC)|*.DVC||");

	chooseDevice.m_ofn.lpstrTitle = "STEP 2: Choose a device";

	if (chooseDevice.DoModal() == IDOK)
	{
		sprintf(s, "%s", (LPCSTR)chooseDevice.GetPathName());
		sprintf(t, "%s", chooseName.m_editName);

		if (pDoc->YoImportDevice(s, t) == TRUE)
		{
			pDoc->m_currentDevice->m_ptrPart->m_translate[0] = pView->m_eye[3];
			pDoc->m_currentDevice->m_ptrPart->m_translate[1] = pView->m_eye[4];
			pDoc->m_currentDevice->m_ptrPart->m_translate[2] = pView->m_eye[5];
			sprintf(s, "Device: %s   Part: %s",
				pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
			pDoc->YoMessage(s);
			pView->YoRender(YO_RENDER_LIGHT);
			pView->YoRender(YO_RENDER_FULL);

			//SendMessage(WM_COMMAND, ID_VIEW_CURRENT_PART, (LPARAM)0);
		}
	}
	else
	{
		sprintf(s, "Import device aborted.");
		pDoc->YoMessage(s);
	}

	return;		
}

void CMainFrame::OnUpdateDeviceImport(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnViewEyeInfo() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	pDoc->m_undo->YoUndo();

	m_eyeViewDlg = new CStageEyeViewDlg();
	m_eyeViewDlg->YoInitDialog();
	m_eyeViewDlgActive = TRUE;
	m_eyeViewDlg->ShowWindow(SW_SHOW);
	return;
}

void CMainFrame::OnUpdateViewEyeInfo(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& m_wndDlgScriptVisible == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnFileRevert() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	FILE *fp;
	char s[256];

	pDoc->m_undo->YoUndo();

	// save the current workcell
	sprintf(s, "%s.UNDO", pDoc->m_fileName);
	if (pDoc->YoWriteWorkcell(s))
	{
		pDoc->m_undo->m_undoMode = YO_UNDO_FILE_REVERT;
	}
	else
	{
		pDoc->m_undo->m_undoMode = YO_UNDO_OFF;
		sprintf(s,
			"File Revert cannot be undone.\nSelect OK to continue or Cancel to abort.");
		if (AfxMessageBox(s, MB_OKCANCEL) == IDCANCEL)
		{
			sprintf(s, "Revert aborted.");
			pDoc->YoMessage(s);
			return;
		}
	}

	if ((fp = fopen(pDoc->m_fileName, "r")) == NULL)
	{
		pDoc->m_undo->m_undoMode = YO_UNDO_OFF;
		sprintf(s, "Error: Revert failed.  Cannot find file:\n   %s", pDoc->m_fileName);
		AfxMessageBox(s);
		return;
	}
	else
	{
		fclose(fp);
		BeginWaitCursor();
		pDoc->YoFreeWorkcell();
		fp = fopen(pDoc->m_fileName, "r");
		if (pDoc->YoReadWorkcell(fp) == FALSE)
		{
			EndWaitCursor();
			sprintf(s, "Error reading file:\n   %s\nIncorrect file format or corrupt data encountered",
				pDoc->m_fileName);
			AfxMessageBox(s);
			fclose(fp);
			
			// Try to restore unreverted workcell
			if (pDoc->m_undo->m_undoMode == YO_UNDO_FILE_REVERT)
			{
				BeginWaitCursor();
				pDoc->YoFreeWorkcell();
				sprintf(s, "%s.UNDO", pDoc->m_fileName);
				fp = fopen(s, "r");
				if (pDoc->YoReadWorkcell(fp) == FALSE)
				{
					// This routine should never have to be called
					EndWaitCursor();
					sprintf(s, "Error restoring file.  Unable to read workcell.\nIncorrect file format or corrupt data encountered");
					AfxMessageBox(s);
					fclose(fp);
					SendMessage(WM_COMMAND, ID_FILE_NEW, (LPARAM)0);
					return;
				}
			}
			else
			{
				SendMessage(WM_COMMAND, ID_FILE_NEW, (LPARAM)0);
				return;
			}
		}
		fclose(fp);

		this->RedrawWindow();
		EndWaitCursor();
	}
	return;
	
}

void CMainFrame::OnUpdateFileRevert(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& strcmp(pDoc->m_fileName, "") != 0)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;	
}


void CMainFrame::OnDeviceExport() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	char s[128];

	CFileDialog exportDevice
		(FALSE,    // save
		NULL,    // no default extension
		NULL,    // file name
		OFN_HIDEREADONLY,
		//"Stage Device files (*.DVC)|*.DVC|All files (*.*)|*.*||");
		"All files (*.*)|*.*|Stage Device files (*.DVC)|*.DVC||");

	pDoc->m_undo->YoUndo();
	sprintf(s, "Exporting device %s to file...", pDoc->m_currentDevice->m_name); 
	pDoc->YoMessage(s);

	exportDevice.m_ofn.lpstrTitle = "Export Device";

	if (exportDevice.DoModal() == IDOK)
	{
		sprintf(s, "%s", (LPCSTR)exportDevice.GetPathName());
		pView->m_fp = fopen(s, "w");
		if (pView->m_fp == NULL)
		{
			return;
		}
		pView->YoRenderDevice(YO_RENDER_SAVE_DEVICE);
		fprintf(pView->m_fp, "NULL\n");
		fclose(pView->m_fp);
		sprintf(s, "Device %s exported to file.", pDoc->m_currentDevice->m_name); 
		pDoc->YoMessage(s);
	}
	else
	{
		sprintf(s, "Export device aborted.");
		pDoc->YoMessage(s);
	}
	
	return;
}

void CMainFrame::OnUpdateDeviceExport(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode == YO_MODE_WORKCELL
		&& pDoc->m_currentPart != NULL
		&& pDoc->m_currentDevice != NULL
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE
		&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
		|| pDoc->m_deviceList != pDoc->m_currentDevice
		|| pDoc->m_currentDevice->m_down != NULL
		|| pDoc->m_currentDevice->m_right != NULL))

	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateAppAbout(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

void CMainFrame::OnUpdateAppExit(CCmdUI* pCmdUI) 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode != YO_MODE_RECORD_SIM
		&& m_viewPartActive == FALSE
		&& m_analysisActive == FALSE
		&& m_viewTagActive == FALSE
		&& m_eyeViewDlgActive == FALSE
		&& pDoc->m_acceptSocket == NULL
		&& pDoc->m_animationState == YO_PAUSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	return;		
}

/***
void CMainFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_animationState == YO_PLAY)
	{
		pDoc->YoPause();
	}
	else if (pDoc->m_animationState == YO_PAUSE)
	{
		CMainFrame::OnHScroll(nSBCode, nPos, pScrollBar);
	}

	if (nSBCode == SB_ENDSCROLL)
	{
		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}

}
***/

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	//TRACE1("OnCmdMsg %d\n", nID);
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// timer routine is called to animate workcell
	// other messages with higher priority are processed first

	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_isMovement && pView->GetCapture() != pView
		&& pDoc->m_mode != YO_MODE_PLAY_SIM
		&& m_wndDlgScript != NULL
		&& m_wndDlgScript->m_animationState != YO_PLAY)
	{
		pDoc->YoMove();
	}

	if (pView->GetCapture() != pView
		&& pDoc->m_mode != YO_MODE_PLAY_SIM
		&& m_wndDlgScript != NULL
		&& m_wndDlgScript->m_animationState == YO_PLAY)
	{
		m_wndDlgScript->YoPlay();
	}

	/***
	else if (pDoc->m_mode == YO_MODE_PLAY_SIM
		&& pDoc->m_animationState == YO_PLAY
		&& pDoc->m_realTime == FALSE
		&& pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR
		&& pDoc->m_renderMode == YO_RENDER3D
		&& pDoc->m_isMovement)
	{
		if (pDoc->m_accumCount % pDoc->m_motionBlurIterations == 0)
		{
			::glClearAccum(0.0f, 0.0f, 0.0f, 0.0f);
			::glClear(GL_ACCUM_BUFFER_BIT);
		}
		pDoc->YoPlay();
		::glAccum(GL_ACCUM, 1.0f / pDoc->m_motionBlurIterations);
		pDoc->m_accumCount++;

		if (pDoc->m_accumCount % pDoc->m_motionBlurIterations == pDoc->m_motionBlurIterations - 1)
		{
			pDoc->m_accumCount = 0;
			::glAccum(GL_RETURN, 1.0f);
			if (::SwapBuffers(pView->m_pDC->GetSafeHdc()) == FALSE)
			{
				AfxMessageBox("ERROR in CMainFrame::OnTimer().  SwapBuffers failed.");
			}
		}
	}
	***/

	else if (pDoc->m_mode == YO_MODE_PLAY_SIM
		&& pDoc->m_animationState == YO_PLAY)
	{
		pDoc->YoPlay();
	}

	CFrameWnd::OnTimer(nIDEvent);
	return;
}


void CMainFrame::OnEditUndo() 
{
	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	int i;
	double tempEye[9];
	double tempTranslate[3];
	char undoFileName[512];
	char s[256];
	FILE *fp;
	CStagePart *curPart;
	CStagePart *prevPart = NULL;
	CStagePath *ptrPath;

	if (pDoc->m_undo->m_undoMode == YO_UNDO_OFF)
	{
		return;
	}

	if (pDoc->m_undo->m_undoMode == YO_UNDO_EYE_POSITION)
	{
		for (i = 0; i < 9; i++)
		{
			tempEye[i] = pView->m_eye[i];
			pView->m_eye[i] = pDoc->m_undo->m_undoEye[i];
			pDoc->m_undo->m_undoEye[i] = tempEye[i];
		}

		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
			pView->m_clipFront, pView->m_clipRear);
		
		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
			pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
			pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

		YoUpdateEyeDlg();
	}
	
	else if (pDoc->m_undo->m_undoMode == YO_UNDO_PART_POSITION)
	{
		for (i = 0; i < 3; i++)
		{
			tempTranslate[i] = pDoc->m_currentDevice->m_ptrPart->m_translate[i];
			pDoc->m_currentDevice->m_ptrPart->m_translate[i] = pDoc->m_undo->m_undoPartTranslate[i];
			pDoc->m_undo->m_undoPartTranslate[i] = tempTranslate[i];
		}
		sprintf(s, "Original translation restored.");
		pDoc->YoMessage(s);
	}

	else if (pDoc->m_undo->m_undoMode == YO_UNDO_DEVICE_DELETE)
	{
		pDoc->m_undo->m_undoDeviceDelete->m_visible = TRUE;
		pDoc->m_undo->m_undoDeviceDelete = NULL;
		pDoc->m_undo->m_undoMode = YO_UNDO_OFF;
		sprintf(s, "Device: %s restored.", pDoc->m_currentDevice->m_name);
		pDoc->YoMessage(s);
	}

	else if (pDoc->m_undo->m_undoMode == YO_UNDO_PART_DELETE)
	{
		pDoc->m_undo->m_undoPartDelete = NULL;
		pDoc->m_undo->m_undoMode = YO_UNDO_OFF;
		sprintf(s, "Part: %s restored.", pDoc->m_currentPart->m_partName);
		pDoc->YoMessage(s);
	}

	else if (pDoc->m_undo->m_undoMode == YO_UNDO_PART_UPDATE)
	{
		for (curPart = pDoc->m_pickPart[pDoc->m_currentPart->m_displayListID % YO_HASH_SIZE];
			curPart != pDoc->m_currentPart;)
		{
			prevPart = curPart;
			curPart = curPart->m_pick;
		}
		if (prevPart == NULL)
		{
			pDoc->m_pickPart[pDoc->m_currentPart->m_displayListID % YO_HASH_SIZE] = pDoc->m_undo->m_undoPartDelete;
		}
		else
		{
			prevPart->m_pick = pDoc->m_undo->m_undoPartDelete;
		}
		pDoc->m_undo->m_undoPartDelete->m_pick = pDoc->m_currentPart->m_pick;

		if (pDoc->m_currentPart->m_attachedDevice != NULL)
		{
			pDoc->m_currentPart->m_attachedDevice->m_attachedFromPart = pDoc->m_undo->m_undoPartDelete;
		}
		pDoc->m_undo->m_undoPartDelete->m_attachedDevice = pDoc->m_currentPart->m_attachedDevice;
		pDoc->m_currentPart->m_attachedDevice = NULL;

		for (ptrPath = pDoc->m_currentPart->m_path; ptrPath != NULL; ptrPath = ptrPath->m_nextPath)
		{
			ptrPath->m_ptrPart = pDoc->m_undo->m_undoPartDelete;
		}
		pDoc->m_undo->m_undoPartDelete->m_path = pDoc->m_currentPart->m_path;
		pDoc->m_currentPart->m_path = NULL;

		if (pDoc->m_currentPart->m_up != NULL)
		{
			pDoc->m_undo->m_undoPartDelete->m_up = pDoc->m_currentPart->m_up;
			pDoc->m_currentPart->m_up->m_down = pDoc->m_undo->m_undoPartDelete;
		}
		if (pDoc->m_currentPart->m_down != NULL)
		{
			pDoc->m_undo->m_undoPartDelete->m_down = pDoc->m_currentPart->m_down;
			pDoc->m_currentPart->m_down->m_up = pDoc->m_undo->m_undoPartDelete;
		}
		if (pDoc->m_currentPart->m_left != NULL)
		{
			pDoc->m_undo->m_undoPartDelete->m_left = pDoc->m_currentPart->m_left;
			pDoc->m_currentPart->m_left->m_right = pDoc->m_undo->m_undoPartDelete;
		}
		if (pDoc->m_currentPart->m_right != NULL)
		{
			pDoc->m_undo->m_undoPartDelete->m_right = pDoc->m_currentPart->m_right;
			pDoc->m_currentPart->m_right->m_left = pDoc->m_undo->m_undoPartDelete;
		}

		if (pDoc->m_currentDevice->m_ptrPart == pDoc->m_currentPart)
		{
			pDoc->m_currentDevice->m_ptrPart = pDoc->m_undo->m_undoPartDelete;
		}
		pDoc->m_currentPart->m_displayListID = -1;
		delete pDoc->m_currentPart;
		pDoc->m_currentPart = pDoc->m_undo->m_undoPartDelete;
		pDoc->m_undo->m_undoPartDelete = NULL;
		pDoc->m_undo->m_undoMode = YO_UNDO_OFF;
		sprintf(s, "Original model of Part: %s restored.", pDoc->m_currentPart->m_partName);
		pDoc->YoMessage(s);
	}

	else if (pDoc->m_undo->m_undoMode == YO_UNDO_PATH_DELETE)
	{
		pDoc->m_undo->m_undoTagDelete->m_ptrPath->m_visible = TRUE;
		pDoc->m_undo->m_undoTagDelete = NULL;
		pDoc->m_undo->m_undoMode = YO_UNDO_OFF;
		sprintf(s, "Path: %s restored.", pDoc->m_currentTag->m_ptrPath->m_name);
		pDoc->YoMessage(s);
	}

	else if (pDoc->m_undo->m_undoMode == YO_UNDO_TAG_DELETE)
	{
		pDoc->m_undo->m_undoTagDelete = NULL;
		pDoc->m_undo->m_undoMode = YO_UNDO_OFF;
		sprintf(s, "Tag: %d restored on Path: %s.", pDoc->m_currentTag->m_tag,
			pDoc->m_currentTag->m_ptrPath->m_name);
		pDoc->YoMessage(s);
	}

	else if (pDoc->m_undo->m_undoMode == YO_UNDO_FILE_REVERT)
	{
		sprintf(undoFileName, "%s.UNDO", pDoc->m_fileName);
		if ((fp = fopen(undoFileName, "r")) == NULL)
		{
			sprintf(s, "Error: Revert undo failed.  Cannot find file\n   %s", undoFileName);
			AfxMessageBox(s);
		}
		else
		{
			BeginWaitCursor();
			pDoc->YoFreeWorkcell();

			if (pDoc->YoReadWorkcell(fp) == FALSE)
			{
				EndWaitCursor();
				sprintf(s, "Error: Revert undo failed while reading file.\nIncorrect file format or corrupt data encountered.");
				AfxMessageBox(s);
				BeginWaitCursor();
				fclose(fp);
				pDoc->YoFreeWorkcell();

				// Try to restore unreverted workcell
				fp = fopen(pDoc->m_fileName, "r");
				if (pDoc->YoReadWorkcell(fp) == FALSE)
				{
					// This routine should never have to be called
					EndWaitCursor();
					sprintf(s, "Error restoring file.  Unable to read workcell.\nIncorrect file format or corrupt data encountered");
					AfxMessageBox(s);
					fclose(fp);
					SendMessage(WM_COMMAND, ID_FILE_NEW, (LPARAM)0);
					return;
				}
				fclose(fp);
			}
			else
			{
				fclose(fp);
				::DeleteFile((LPCTSTR)undoFileName);
			}
			EndWaitCursor();
		}
		pDoc->m_undo->m_undoMode = YO_UNDO_OFF;
	}

	this->RedrawWindow();
	//pView->YoRender(YO_RENDER_LIGHT);
	//pView->YoRender(YO_RENDER_FULL);

	return;
	
}


void CMainFrame::OnClose() 
{
	TRACE0("CMainFrame::OnClose()\n");

	CStageView *pView = (CStageView *)GetActiveView();
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDoc *pDoc = pView->GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	int i;
	char *s;

	KillTimer(1);
	if (m_wndDlgScript != NULL)
	{
		m_wndDlgScript->DestroyWindow();
		m_wndDlgScript = NULL;
	}

	s = pDoc->m_fileName;
	if (strcmp(pDoc->m_fileName, "") != 0 && pDoc->m_mode != YO_MODE_PLAY_SIM)
	{
		
		for (i = strlen(pDoc->m_fileName); i >= 0 && *(s + i) != '\\'; i--);
		if (i < 0)
		{
			pDoc->YoWriteWorkcell("autoBackup.stg");
		}
		else
		{
			sprintf(s + i + 1, "autoBackup.stg");
		}
	}
	
	CFrameWnd::OnClose();
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
	
	TRACE0("CMainFrame::OnSetFocus()\n");
	//	if (m_viewPartActive == TRUE)
	//	{
	//		m_viewPart->YoCancelSnapInherit();
	//	}
	return;	
}
