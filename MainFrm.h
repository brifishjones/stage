// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

/****
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
#include "StageLightDlg.h"
#include "StageViewPart.h"
#include "StageViewLightPart.h"
#include "StageDeviceTransformation.h"
#include "StageEyeDialog.h"
***/
#include "stageTopDlg.h"


class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
public:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//CString m_minutes;
	//CString m_seconds;
	//CString m_frames;
	//CSliderCtrl	m_sliderCurrentTime;
	CString m_dialogChooseNameTitle;
	//CSliderCtrl	m_sliderFieldOfView;
	HCURSOR m_hCursorArrow;
	HCURSOR m_hCursorWait;
	HCURSOR m_hCursorPan;
	HCURSOR m_hCursorSelect;
	HCURSOR m_hCursorLink;


protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
public:
	//CDialogBar  m_wndDlgBarTop;
	CStageTopDlg m_wndDlgBarTop;
	CDialogBar  m_wndDlgBarLeft;
	class CStageScriptDlg  *m_wndDlgScript;
	class CStageEyeDialog *m_wndDlgEye;
	//CStageViewLightPart *m_viewLightPart;
	class CStageViewPart *m_viewPart;
	class CStageViewTag *m_viewTag;
	class CStageEyeViewDlg *m_eyeViewDlg;
	class CStageLightDialog *m_lightDialog;
	class CStageRobot6Dlg *m_robot6Dialog;
	class CStageRotaryTableDlg *m_rotaryTableDialog;
	class CStageConveyorDlg *m_conveyorDialog;
	class CStageGripperDlg *m_gripperDialog;
	class CStageBarCodeReaderDlg *m_barCodeReaderDialog;
	class CStageBarrettHandDlg *m_barrettHandDialog;
	class CStageCameraDlg *m_cameraDialog;
	class CStageScaleDlg *m_scaleDialog;
	class CStageTrainDlg *m_trainDialog;
	class CStageTrackDlg *m_trackDialog;
	class CStageAnalysisDlg *m_analysis;
	BOOL m_analysisActive;
	BOOL m_wndDlgEyeVisible;
	BOOL m_wndDlgScriptVisible;
	CBitmap m_bmRewind;
	CBitmap m_bmRewindHL;
	CBitmap m_bmPlay;
	CBitmap m_bmPlayHL;
	CBitmap m_bmPause;
	CBitmap m_bmPauseHL;
	CBitmap m_bmWalk;
	CBitmap m_bmPan;
	CBitmap m_bmDeviceTranslate;
	CBitmap m_bmSimRecord;
	CBitmap m_bmCircleGreen;
	CBitmap m_bmCircleYellow;
	CBitmap m_bmCircleRed;
	BOOL m_init;
	BOOL m_viewPartActive;
	BOOL m_viewTagActive;
	BOOL m_lightDlgActive;
	BOOL m_robot6DlgActive;
	BOOL m_rotaryTableDlgActive;
	BOOL m_conveyorDlgActive;
	BOOL m_cameraDlgActive;
	BOOL m_gripperDlgActive;
	BOOL m_barCodeReaderDlgActive;
	BOOL m_barrettHandDlgActive;
	BOOL m_scaleDlgActive;
	BOOL m_trainDlgActive;
	BOOL m_trackDlgActive;
	BOOL m_eyeViewDlgActive;
	DWORD m_colorBtnFace;
	DWORD m_colorBtnText;
	DWORD m_colorHighLight;
	DWORD m_colorHighLightText;
	DWORD m_colorCaptionText;
	DWORD m_colorMenu;
	DWORD m_colorMenuText;
	DWORD m_colorWindow;
	DWORD m_colorActiveCaption;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPrefs();
	afx_msg void OnViewDeviceTree();
	afx_msg void OnMotionInsertAnchor();
	afx_msg void OnMotionInsertHold();
	afx_msg void OnMotionViewHistory();
	afx_msg void OnViewCurrentPart();
	afx_msg void OnUpdateViewCurrentPart(CCmdUI* pCmdUI);
	afx_msg void OnDeviceAttach();
	afx_msg void OnDeviceChoose();
	afx_msg void OnDeviceClone();
	afx_msg void OnDeviceDetach();
	afx_msg void OnDeviceRename();
	afx_msg void OnDeviceDelete();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize320x240();
	afx_msg void OnSize640x480();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMotionInsertPartAnchor();
	afx_msg void OnMotionInsertPartHold();
	afx_msg void OnMotionViewPartHistory();
	afx_msg void OnUpdateDeviceAttach(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeviceChoose(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeviceClone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeviceDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeviceDetach(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeviceRename(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveCopyAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileUpdate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMotionInsertAnchor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMotionInsertHold(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMotionInsertPartAnchor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMotionInsertPartHold(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMotionViewHistory(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMotionViewPartHistory(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrefs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDeviceTree(CCmdUI* pCmdUI);
	afx_msg void OnDeviceCreate();
	afx_msg void OnUpdateDeviceCreate(CCmdUI* pCmdUI);
	afx_msg void OnPartAttach();
	afx_msg void OnUpdatePartAttach(CCmdUI* pCmdUI);
	afx_msg void OnPartChoose();
	afx_msg void OnUpdatePartChoose(CCmdUI* pCmdUI);
	afx_msg void OnPartDelete();
	afx_msg void OnUpdatePartDelete(CCmdUI* pCmdUI);
	afx_msg void OnPartRename();
	afx_msg void OnUpdatePartRename(CCmdUI* pCmdUI);
	afx_msg void OnPartUpdate();
	afx_msg void OnUpdatePartUpdate(CCmdUI* pCmdUI);
	afx_msg void OnHelpAnalysis();
	afx_msg void OnUpdateHelpAnalysis(CCmdUI* pCmdUI);
	afx_msg void OnTagChoose();
	afx_msg void OnTagCreate();
	afx_msg void OnTagDelete();
	afx_msg void OnTagDeletePath();
	afx_msg void OnTagNewPath();
	afx_msg void OnTagReattachPath();
	afx_msg void OnTagRenamePath();
	afx_msg void OnTagTagOnTcf();
	afx_msg void OnViewCurrentTag();
	afx_msg void OnUpdateViewCurrentTag(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTagChoose(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTagCreate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTagDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTagDeletePath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTagNewPath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTagReattachPath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTagRenamePath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTagTagOnTcf(CCmdUI* pCmdUI);
	afx_msg void OnDeviceImport();
	afx_msg void OnUpdateDeviceImport(CCmdUI* pCmdUI);
	afx_msg void OnViewEyeInfo();
	afx_msg void OnUpdateViewEyeInfo(CCmdUI* pCmdUI);
	afx_msg void OnFileRevert();
	afx_msg void OnUpdateFileRevert(CCmdUI* pCmdUI);
	afx_msg void OnDeviceExport();
	afx_msg void OnUpdateDeviceExport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppAbout(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnTagChoosePath();
	afx_msg void OnUpdateTagChoosePath(CCmdUI* pCmdUI);
	afx_msg void OnSizeCustom();
	afx_msg void OnSize720x480();
	afx_msg void OnUpdateSize320x240(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSize640x480(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSize720x480(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSizeCustom(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
public:
	afx_msg void OnModeWalk(void);
	afx_msg void OnModePan(void);
	afx_msg void OnModeDeviceTranslate(void);
	afx_msg void OnModeScript(void);
	afx_msg void OnModeEye(void);
	afx_msg void OnModeRecordSim(void);
	afx_msg void OnModeSocket(void);
	//afx_msg void OnPause(void);
	//afx_msg void OnPlay(void);
	//afx_msg void OnRewind(void);
	//afx_msg void YoSetCurrentTime(CCmdUI *);
	//afx_msg void OnUpdatePauseUI(CCmdUI *);
	//afx_msg void OnUpdatePlayUI(CCmdUI *);
	//afx_msg void OnUpdateRewindUI(CCmdUI *);
	//afx_msg void OnUpdateMinutesUI(CCmdUI *);
	//afx_msg void OnUpdateSecondsUI(CCmdUI *);
	//afx_msg void OnUpdateFramesUI(CCmdUI *);
	//afx_msg void OnUpdateTimeUI(CCmdUI *);
	afx_msg void OnUpdateDeviceTranslateUI(CCmdUI *);
	afx_msg void OnUpdateWalkUI(CCmdUI *);
	afx_msg void OnUpdatePanUI(CCmdUI *);
	afx_msg void OnUpdateScriptUI(CCmdUI *);
	afx_msg void OnUpdateEyeUI(CCmdUI *);
	afx_msg void OnUpdateRecordSimUI(CCmdUI *);
	afx_msg void OnUpdateSocketUI(CCmdUI *);
	//afx_msg void OnUpdateImmediateModeUI(CCmdUI *);
	// device transformations
	afx_msg void OnUpdateSliderFieldOfView(void);
	//afx_msg void OnImmediateMode(void);

//public:
	//afx_msg void OnUpdateTime(void);
	DECLARE_MESSAGE_MAP()

// Stage helper functions
public:
	void YoUpdateEyeDlg(void);
	void YoMoveEyeDlg(void);
	void YoUpdateLeftDlg(void);
	void YoTransparentBitmap(CBitmap *, COLORREF);

};

/////////////////////////////////////////////////////////////////////////////
