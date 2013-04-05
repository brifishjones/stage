// stageDoc.cpp : implementation of the CStageDoc class
//

#include "stdafx.h"
#include "stage.h"

#include "stageDoc.h"
#include "SrvrItem.h"
#include "stageView.h"
//#include "stageDeviceTransformation.h"
#include "stageAnalysisDlg.h"
#include "stageViewPart.h"
#include "stageViewTag.h"
#include "stageRobot6Dlg.h"
#include "stageRotaryTableDlg.h"
#include "stageConveyorDlg.h"
#include "stageGripperDlg.h"
#include "stageBarCodeReaderDlg.h"
#include "stageScaleDlg.h"
#include "stageScriptDlg.h"
#include "stageTrainDlg.h"
#include "stageTrackDlg.h"
#include "stageTopDlg.h"
#include "MainFrm.h"
#include "image.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/***
UINT YoThreadPlay(LPVOID pParam)
{
	CStageThreadPlay *threadPlay = (CStageThreadPlay *)pParam;

	//if (tp == NULL || !tp->IsKindOf(RUNTIME_CLASS(CStageThreadPlay)))
	//{
	//	return 1;     // illegal parameter
	//}

	//else
	{
		char s[4];
		int min = 0;
		int sec = 0;
		int frm = 0;
		CWnd *pCBox;
		SYSTEMTIME gmTimeStart;
		SYSTEMTIME gmTimeCurrent;
		CTime timePlay;
		CTime timeStart;
		CTime timeCurrent;
		GLint tms;
		CTimeSpan spanSec;
		int timeFrame;
		double tp;
		//POSITION pos = pDoc->GetFirstViewPosition();
		//CStageView *pView = (CStageView *)(pDoc->GetNextView(pos));
		//CFrameWnd *pMainFrame = pView->GetTopLevelFrame();
		CMainFrame *pMainFrame = new CMainFrame;
		pMainFrame->FromHandle(threadPlay->m_hframeWND);
		CStageView *pView = new CStageView;
		pView->FromHandle(threadPlay->m_hviewWND);
		//((CStageView *)pView)->YoRender(YO_RENDER_FULL);
		return 1;
		CStageDoc *pDoc = pView->GetDocument();


		pDoc->m_animationState = YO_PAUSE;
		tp = pDoc->m_timeCurrent;
		timeFrame = (int)(tp * (double)pDoc->m_framesPerSecond); 

		for (pDoc->m_currentCommand = pDoc->m_commandList;
			pDoc->m_currentCommand != NULL && pDoc->m_currentCommand->m_time <= tp;
			pDoc->m_currentCommand = pDoc->m_currentCommand->m_next)
		{
			pDoc->m_timeCurrent = pDoc->m_currentCommand->m_time;
			pDoc->YoHandleCommand(pDoc->m_currentCommand->m_buf);
		}

		if (pDoc->m_realTime == TRUE)
		{
			::GetSystemTime(&gmTimeStart);
			gmTimeStart.wSecond -= (int)tp;
			gmTimeStart.wMilliseconds -= (int)((tp - (double)(int)tp) * 1000.0);
		}

		pDoc->m_timeCurrent = tp;
		pDoc->m_animationState = YO_PLAY;

		while (pDoc->m_timeCurrent <= pDoc->m_timeEnd
			&& pDoc->m_animationState == YO_PLAY)
		{
			while (pDoc->m_currentCommand != NULL
				&& pDoc->m_currentCommand->m_time <= pDoc->m_timeCurrent)
			{
				pDoc->YoHandleCommand(pDoc->m_currentCommand->m_buf);
				pDoc->m_currentCommand = pDoc->m_currentCommand->m_next;
			}

			if (pDoc->m_isMovement)
			{
				pDoc->YoMove();
				((CStageView *)pView)->YoRender(YO_RENDER_LIGHT);
				((CStageView *)pView)->YoRender(YO_RENDER_FULL);
			}

			if (pDoc->m_realTime == TRUE)
			{
				::GetSystemTime(&gmTimeCurrent);
				timeCurrent = gmTimeCurrent;
				spanSec = timeCurrent - timeStart;
				tms = gmTimeCurrent.wMilliseconds - gmTimeStart.wMilliseconds;
				pDoc->m_timeCurrent = spanSec.GetTotalSeconds() * 1000 + tms;
				timeFrame = (int)pDoc->m_timeCurrent * pDoc->m_framesPerSecond; 
			}
			else
			{
				timeFrame++;
				pDoc->m_timeCurrent = (double)timeFrame / (double)pDoc->m_framesPerSecond;
			}

			TRACE1("timeCurrent = %.3lf\n", pDoc->m_timeCurrent);
			//pMainFrame->PostMessage(WM_COMMAND, IDC_MODE_PAN, (LPARAM)0);

			if (pDoc->m_realTime == TRUE)
			{
				min = (int)(pDoc->m_timeCurrent / 60.0);
				sec = (int)pDoc->m_timeCurrent - (min * 60);
				frm = (int)((pDoc->m_timeCurrent
					- (double)((int)pDoc->m_timeCurrent)) * 100.0);
			}
			else
			{
				min = (int)(timeFrame / (pDoc->m_framesPerSecond * 60));
				sec = (int)((timeFrame - (min * pDoc->m_framesPerSecond * 60)) / pDoc->m_framesPerSecond);
				frm = ((timeFrame - (min * pDoc->m_framesPerSecond * 60)
					- (sec * pDoc->m_framesPerSecond)) / pDoc->m_framesPerSecond);
			}

			sprintf(s, "%02d", min);
			pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_MINUTES);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
			//sprintf(s, "%02d", sec);
			//pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_SECONDS);
			//pCBox->SetWindowText(s);
			//pCBox->UpdateWindow();
			//sprintf(s, "%02d", frm);
			//pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_FRAMES);
			//pCBox->SetWindowText(s);
			//pCBox->UpdateWindow();
			//pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_TIME);
			//((CSliderCtrl *)pCBox)->SetRange(0, (int)pDoc->m_timeEnd);
			//((CSliderCtrl *)pCBox)->SetPos((int)pDoc->m_timeCurrent);

		}

		//if (pDoc->m_animationState == YO_PLAY)
		//{
		//	pDoc->YoPause();
		//}

		delete pDoc;
		TRACE0("Exiting YoThreadPlay...\n");
      
		AfxEndThread(0);
		
	}
	return 0;
}
***/

/***
UINT YoThreadPlay(LPVOID pParam)
{
	CStageDoc *pDoc = (CStageDoc*)pParam;

	if (pDoc == NULL || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return 1;     // illegal parameter
	}

	else
	{

		char s[4];
		int min = 0;
		int sec = 0;
		int frm = 0;
		CWnd *pCBox;
		SYSTEMTIME gmTimeStart;
		SYSTEMTIME gmTimeEnd;
		SYSTEMTIME gmTimePlay;
		GLint timeElapsed;
		CTime timePlay;
		CTime timeStart;
		CTime timeEnd;
		GLint tms;
		CTimeSpan spanSec;
		GLint tp;
		POSITION pos = pDoc->GetFirstViewPosition();
		CStageView *pView = (CStageView *)(pDoc->GetNextView(pos));
		CFrameWnd *pMainFrame = pView->GetTopLevelFrame();


		::GetSystemTime(&gmTimePlay);
		tp = pDoc->m_timeCurrent;
		timePlay = gmTimePlay;

		while (pDoc->m_timeCurrent <= pDoc->m_timeEnd
			&& pDoc->m_animationState == YO_PLAY)
		{
			::GetSystemTime(&gmTimeStart);
			timeStart = gmTimeStart;

			min = pDoc->m_timeCurrent / (60 * pDoc->m_framesPerSecond);
			sec = (pDoc->m_timeCurrent
				- (min * 60 * pDoc->m_framesPerSecond)) / pDoc->m_framesPerSecond;
			frm = pDoc->m_timeCurrent
				- (min * 60 * pDoc->m_framesPerSecond)
				- (sec * pDoc->m_framesPerSecond);

			sprintf(s, "%02d", min);
			pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_MINUTES);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
			sprintf(s, "%02d", sec);
			pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_SECONDS);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
			sprintf(s, "%02d", frm);
			pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_FRAMES);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
			pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_TIME);
			((CSliderCtrl *)pCBox)->SetRange(0, pDoc->m_timeEnd);
			((CSliderCtrl *)pCBox)->SetPos(pDoc->m_timeCurrent);

			if (pDoc->m_commandList != NULL)
			{
				
			}

			if (pDoc->m_isMovement == 0)
			{
				pView->YoRender(YO_RENDER_FULL);
			}

			if (pDoc->m_render3d == 0x0 && pDoc->m_realTime == TRUE)
			{
				timeElapsed = 0;
				while(timeElapsed < 1000 / pDoc->m_framesPerSecond)
				{
					::GetSystemTime(&gmTimeEnd);
					timeEnd = gmTimeEnd;
					spanSec = timeEnd - timeStart;
					tms = gmTimeEnd.wMilliseconds - gmTimeStart.wMilliseconds;
					timeElapsed = spanSec.GetTotalSeconds() * 1000 + tms;
				}

				spanSec = timeEnd - timePlay;
				tms = gmTimeEnd.wMilliseconds - gmTimePlay.wMilliseconds;
				timeElapsed = spanSec.GetTotalSeconds() * 1000 + tms;
				pDoc->m_timeCurrent = tp + (int)(((float)timeElapsed / 1000.0) * (float)pDoc->m_framesPerSecond + 0.5);
			}
			else
			{
				pDoc->m_timeCurrent++;
			}
		}

		delete pDoc;
		TRACE0("Exiting YoThreadPlay...\n");
      
		AfxEndThread(0);
		
	}
}
***/


/////////////////////////////////////////////////////////////////////////////
// CStageDoc

IMPLEMENT_DYNCREATE(CStageDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CStageDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CStageDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageDoc construction/destruction

CStageDoc::CStageDoc()
{
	int i;
	TRACE0("CStageDoc::CStageDoc()\n");

	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here
	sprintf(m_fileName, "");
	sprintf(m_scriptName, "");
	m_deviceList = NULL;
	m_lightList = NULL;
	m_textureList = NULL;
	m_commandList = NULL;
	m_currentCommand = NULL;
	m_eyeList = NULL;
	m_camera = NULL;
	m_currentDevice = NULL;
	m_currentPart = NULL;
	m_currentTag = NULL;
	m_currentPolygonIndex = -1;
	m_closestVertexIndex = -1;
	m_units = YO_UNITS_MILLIMETERS;
	m_unitScaleFactor = 1.0f;
	m_grid[0] = (float)YO_DEFAULT_GRID_VISIBLE;
	m_grid[1] = (float)YO_DEFAULT_GRID_SPACING;
	m_grid[2] = (float)YO_DEFAULT_GRID_LENGTH;
	m_grid[3] = (float)YO_DEFAULT_GRID_WIDTH;
	m_grid[4] = (float)YO_DEFAULT_GRID_RED;
	m_grid[5] = (float)YO_DEFAULT_GRID_GREEN;
	m_grid[6] = (float)YO_DEFAULT_GRID_BLUE;

	m_lighting[0] = TRUE;
	m_lighting[1] = FALSE;
	m_lighting[2] = 50;
	m_lighting[3] = 50;
	m_lighting[4] = 50;
	m_lighting[5] = 255;
	m_sunAltitude = YO_DEFAULT_SUN_ALTITUDE;
	m_sunAzimuth = YO_DEFAULT_SUN_AZIMUTH;
	m_sunIntensity = YO_DEFAULT_SUN_INTENSITY;
	//m_threadRender = NULL;
	//m_threadPlay = NULL;
	m_timeModified = TRUE;
	m_timeCurrent = 0.0f;
	m_timeEnd = 0.0f;
	m_timePause = 0.0f;
	m_timeSleepTotal = 0.0f;
	m_scriptFastForward = FALSE;
	m_framesPerSecond = YO_DEFAULT_RENDER_FRAMES_PER_SECOND;
	m_render3d = 0; //YO_RENDER3D_MOTION_BLUR;
	m_motionBlurIterations = YO_DEFAULT_RENDER_MOTION_BLUR_ITERATIONS;
	m_accumCount = 0;
	m_quickMode = YO_WIREFRAME;
	//m_renderMode = YO_TEXTURE;
	m_renderMode = YO_RENDER3D;
	m_mode = YO_MODE_WORKCELL;
	m_realTime = TRUE;
	m_antiAlias = YO_DEFAULT_RENDER_ANTI_ALIAS;
	m_smoothShading = TRUE;
	m_outputBitmap = FALSE;
	m_animationState = YO_PAUSE;
	m_shadowSensitivity = 50;
	m_splineResolution = 16.0;
	m_alphaBlending[0] = GL_SRC_ALPHA;
	m_alphaBlending[1] = GL_ONE_MINUS_SRC_ALPHA;
	m_alphaFunction = GL_ALWAYS;
	m_alphaFunctionRef = 0.0f;
	m_fog[0] = FALSE;
	m_fog[1] = 0;
	m_worldCoordinateFrame = FALSE;
	m_boundingBox = YO_DEFAULT_RENDER_BOUNDING_BOX;
	//m_autoSocketServer = FALSE;
	m_isMovement = 0;
	m_deviceBeingAttached = FALSE;
	m_tempAttachedFromPart = NULL;
	m_numberOfPaths = 0;
	m_snapToViewPart = YO_SNAP_POLYGON_CENTER;
	m_snapToViewTag = YO_SNAP_POLYGON_CENTER;

	for (i = 0; i < 8; i++)
	{
		m_fogParameters[i] = 0.0f;
	}

	m_eyeList = new CStageEye(this);
	m_eyeList->m_motion = NULL;
	m_eyeList->m_score = NULL;
	m_eyeList->m_currentScore = NULL;
	m_eyeList->m_moving = FALSE;

	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		m_eyeViewHash[i] = NULL;
	}

	m_undo = new CStageUndo(this);
	m_undo->m_undoMode = YO_UNDO_OFF;

	m_port = YO_DEFAULT_NETWORK_PORT;
	m_socket = NULL;
	m_acceptSocket = NULL;
	m_resumeMove = FALSE;

	//::InitializeCriticalSection(&m_criticalSection);

	i = 0xffff;
	int j = 0x10000;
	int k = 0xffffff;
	TRACE3("%d %d %d\n", i, j, k);

}

CStageDoc::~CStageDoc()
{
	TRACE0("CStageDoc::~CStageDoc()\n");
	YoFreeWorkcell();
	delete m_eyeList;
	delete m_undo;
	if (m_acceptSocket)
	{
		delete m_acceptSocket;
	}
	if (m_socket)
	{
		delete m_socket;
	}
}

BOOL CStageDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}

	int i;
	char *s;

	s = m_fileName;
	if (strcmp(m_fileName, "") != 0 && m_mode != YO_MODE_PLAY_SIM)
	{
		for (i = strlen(m_fileName); i >= 0 && *(s + i) != '\\'; i--);
		if (i < 0)
		{
			YoWriteWorkcell("autoBackup.stg");
		}
		else
		{
			sprintf(s + i + 1, "autoBackup.stg");
		}
	}

	YoFreeWorkcell();
	sprintf(m_fileName, "");
	YoMessage("");

	SetTitle("Untitled");

	if (pMainFrame->SetTimer(1, 25, NULL) == 0)
	{
		TRACE0("SetTimer failed\n");
	}

	pView->m_fieldOfView = 30.0;
	pView->m_clipFront = 100.0;
	pView->m_clipRear = 100000.0;
	pView->m_eye[0] = 10000.0;
	pView->m_eye[1] = 6000.0;
	pView->m_eye[2] = 5000.0;
	pView->m_eye[3] = 0.0;
	pView->m_eye[4] = 0.0;
	pView->m_eye[5] = 0.0;
	pView->m_eye[6] = 0.0;
	pView->m_eye[7] = 0.0;
	pView->m_eye[8] = 1.0;

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
	pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
	pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

	//pView->YoRender(YO_RENDER_LIGHT);
	//pView->YoRender(YO_RENDER_FULL);

	return TRUE;
}


BOOL CStageDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	CWnd *pCBox;
	FILE *fp;
	char s[256];
	char *t;
	int i;
	
	t = m_fileName;
	if (strcmp(m_fileName, "") != 0 && m_mode != YO_MODE_PLAY_SIM)
	{
		for (i = strlen(m_fileName); i >= 0 && *(t + i) != '\\'; i--);
		if (i < 0)
		{
			YoWriteWorkcell("autoBackup.stg");
		}
		else
		{
			sprintf(t + i + 1, "autoBackup.stg");
		}
	}

	//if (!COleServerDoc::OnOpenDocument(lpszPathName))
	//	return FALSE;
	sprintf(s, "%s", (LPCTSTR)lpszPathName);

	if ((fp = fopen(s, "r")) == NULL)
	{
		sprintf(s, "File open failed.  Unable to find file:\n   %s", m_fileName);
		AfxMessageBox(s);
		return FALSE;
	}
	else
	{
		YoFreeWorkcell();
		if (YoReadWorkcell(fp) == FALSE)
		{
			sprintf(s, "Error: File open failed while reading file.\nIncorrect file format or corrupt data encountered.");
			AfxMessageBox(s);
			//YoFreeWorkcell();
			fclose(fp);
			pMainFrame->SendMessage(WM_COMMAND, ID_FILE_NEW, (LPARAM)0);
			return FALSE;
		}
		fclose(fp);
		sprintf(m_fileName, "%s", (LPCTSTR)lpszPathName);
	}

	if (m_mode == YO_MODE_PLAY_SIM)
	{
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_MINUTES);
		pCBox->SetWindowText("00");
		pCBox->UpdateWindow();
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_SECONDS);
		pCBox->SetWindowText("00");
		pCBox->UpdateWindow();
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_FRAMES);
		pCBox->SetWindowText("00");
		pCBox->UpdateWindow();
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_PLAY);
		((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmPlay);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_PAUSE);
		((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmPauseHL);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_REWIND);
		((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmRewind);
	}
	
	pMainFrame->RedrawWindow();
	// TODO: Add your specialized creation code here
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CStageDoc server implementation

COleServerItem* CStageDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CStageSrvrItem* pItem = new CStageSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

/////////////////////////////////////////////////////////////////////////////
// CStageDoc serialization

void CStageDoc::Serialize(CArchive& ar)
{
	//const CFile* fp = ar.GetFile();
	//CFile cfile;
	//char buf[32];
	//LPCTSTR s = buf;
	//sprintf(buf, "WORKCELL\n");
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//if (!YoWriteWorkcell(ar))
		//{
			//AfxMessageBox("Error writing workcell");
		//}
		
	}
	else
	{
		//if (!YoReadWorkcell(ar))
		//{
		//	AfxMessageBox("Error reading workcell");
		//} 
	}
}

/////////////////////////////////////////////////////////////////////////////
// CStageDoc diagnostics

#ifdef _DEBUG
void CStageDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CStageDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStageDoc commands

BOOL CStageDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	//AfxMessageBox(lpszPathName);
	// TODO: Add your specialized code here and/or call the base class
	//return COleServerDoc::OnSaveDocument(lpszPathName);

	sprintf(m_fileName, "%s", (LPCTSTR)lpszPathName);
	YoWriteWorkcell(lpszPathName);
	return TRUE;
}


BOOL CStageDoc::YoFreeWorkcell()

{
	CStageDevice *currentDevice;
	CStageDevice *ptrDevice;
	CStagePart *currentPart;
	CStagePart *ptrPart;
	CStageCommand *ptrCommand;
	int i;

	TRACE0("YoFreeWorkCell()\n");

	if (m_undo != NULL && m_undo->m_undoMode != YO_UNDO_OFF
		&& m_undo->m_undoMode != YO_UNDO_FILE_REVERT)
	{
		m_undo->m_undoMode = YO_UNDO_OFF;
		m_undo->m_undoDeviceDelete = NULL;
		m_undo->m_undoPartDelete = NULL;
		m_undo->m_undoTagDelete = NULL;
		YoMessage("");
	}

	m_deviceStack = NULL;

	for (currentDevice = m_deviceList; currentDevice != NULL;)
	{
		m_partStack = NULL;

		for (currentPart = currentDevice->m_ptrPart; currentPart != NULL;)
		{
			ptrPart = currentPart;
			if (currentPart->m_down != NULL)
			{
				if (currentPart->m_right != NULL)
				{
					YoPushPart(currentPart->m_right);
				}
				currentPart = currentPart->m_down;
			}
			else if (currentPart->m_right != NULL)
			{
				currentPart = currentPart->m_right;
			}
			else if (m_partStack != NULL)
			{
				currentPart = YoPopPart();
			}
			else 
			{
				currentPart = NULL; 
			}

			delete(ptrPart);
		}

		ptrDevice = currentDevice;
		if (currentDevice->m_down != NULL)
		{
			if (currentDevice->m_right != NULL)
			{
				YoPushDevice(currentDevice->m_right);
			}
			currentDevice = currentDevice->m_down;
		}
		else if (currentDevice->m_right != NULL)
		{
			currentDevice = currentDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			currentDevice = YoPopDevice();
		}
		else 
		{
			currentDevice = NULL;
		}

		if (ptrDevice->m_type == YO_LIGHT)
		{
			delete((CStageLight *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_CAMERA)
		{
			delete((CStageCamera *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_ROBOT6)
		{
			delete((CStageRobot6 *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_ROTARY_TABLE)
		{
			delete((CStageRotaryTable *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_GRIPPER)
		{
			delete((CStageGripper *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_CAMERA)
		{
			delete((CStageCamera *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_BAR_CODE_READER)
		{
			delete((CStageBarCodeReader *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_SCALE)
		{
			delete((CStageScale *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_TRAIN)
		{
			delete((CStageTrain *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_CONVEYOR)
		{
			delete((CStageConveyor *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_CONVEYOR_PALLET)
		{
			delete((CStageConveyorPallet *)ptrDevice);
		}
		else if (ptrDevice->m_type == YO_BARRETT_HAND)
		{
			delete((CStageBarrettHand *)ptrDevice);
		}
		else
		{
			delete(ptrDevice);
		}
	}

	YoEyeViewHashInit();
	YoDeviceHashInit();
	YoPathHashInit();
	m_deviceList = NULL;
	m_lightList = NULL;

	for (m_currentCommand = m_commandList; m_currentCommand != NULL;)
	{
		ptrCommand = m_currentCommand;
		m_currentCommand = m_currentCommand->m_next;
		delete ptrCommand;
	}
	m_commandList = NULL;
	m_currentCommand = NULL;
	m_mode = YO_MODE_WORKCELL;

	/***
	for (currentTexture = m_textureList; currentTexture != NULL;)
	{
		// free image memory and delete texture nodes
		ptrTexture = currentTexture;
		LocalFree(ptrTexture->m_pRGBImage);
		currentTexture = currentTexture->m_next;
		delete(ptrTexture);
	}
	YoTextureHashInit();
	m_textureList = NULL;
	***/

	YoPickInit();
	  
	YoFreeEyeList();

	::glDisable(GL_LIGHT0);
	::glDisable(GL_LIGHT1);
	::glDisable(GL_LIGHT2);
	::glDisable(GL_LIGHT3);
	::glDisable(GL_LIGHT4);
	::glDisable(GL_LIGHT5);
	::glDisable(GL_LIGHT6);
	::glDisable(GL_LIGHT7);
	m_numberLightsOn = 0;

	//yo_ObjectMenu();
	m_currentDevice = NULL;
	m_currentPart = NULL;
	m_currentTag = NULL;

	//sprintf(m_fileName, "");
	//sprintf(m_scriptName, "");
	m_deviceList = NULL;
	m_lightList = NULL;
	m_textureList = NULL;
	m_commandList = NULL;
	m_currentCommand = NULL;
	//m_eyeList = NULL;
	m_camera = NULL;
	m_currentDevice = NULL;
	m_currentPart = NULL;
	m_currentTag = NULL;
	m_currentPolygonIndex = -1;
	m_closestVertexIndex = -1;
	//m_units = YO_UNITS_MILLIMETERS;
	m_unitScaleFactor = 1.0f;
	m_grid[0] = (float)YO_DEFAULT_GRID_VISIBLE;
	m_grid[1] = (float)YO_DEFAULT_GRID_SPACING;
	m_grid[2] = (float)YO_DEFAULT_GRID_LENGTH;
	m_grid[3] = (float)YO_DEFAULT_GRID_WIDTH;
	m_grid[4] = (float)YO_DEFAULT_GRID_RED;
	m_grid[5] = (float)YO_DEFAULT_GRID_GREEN;
	m_grid[6] = (float)YO_DEFAULT_GRID_BLUE;
	//m_render3d = 0;
	//m_motionBlurIterations = 1;
	//m_quickMode = YO_WIREFRAME;
	//m_renderMode = YO_TEXTURE;
	m_mode = YO_MODE_WORKCELL;
	m_lighting[0] = TRUE;
	m_lighting[1] = FALSE;
	m_lighting[2] = 50;
	m_lighting[3] = 50;
	m_lighting[4] = 50;
	m_lighting[5] = 255;
	m_sunAltitude = YO_DEFAULT_SUN_ALTITUDE;
	m_sunAzimuth = YO_DEFAULT_SUN_AZIMUTH;
	m_sunIntensity = YO_DEFAULT_SUN_INTENSITY;
	//m_threadRender = NULL;
	//m_threadPlay = NULL;
	m_timeModified = TRUE;
	m_timeCurrent = 0.0f;
	m_timeEnd = 0.0f;
	m_timePause = 0.0f;
	m_timeSleepTotal = 0.0f;
	m_scriptFastForward = FALSE;
	m_accumCount = 0;
	//m_framesPerSecond = 30;
	//m_realTime = TRUE;
	//m_antiAlias = FALSE;
	//m_smoothShading = TRUE;
	//m_outputBitmap = FALSE;
	//m_undo->m_undoMode = YO_UNDO_OFF;
	m_animationState = YO_PAUSE;
	//m_shadowSensitivity = 50;
	//m_splineResolution = 16.0;
	m_alphaBlending[0] = GL_SRC_ALPHA;
	m_alphaBlending[1] = GL_ONE_MINUS_SRC_ALPHA;
	m_alphaFunction = GL_ALWAYS;
	m_alphaFunctionRef = 0.0f;
	m_fog[0] = FALSE;
	m_fog[1] = 0;
	//m_worldCoordinateFrame = FALSE;
	//m_boundingBox = FALSE;
	//m_autoSocketServer = FALSE;
	m_isMovement = 0;
	m_deviceBeingAttached = FALSE;
	m_tempAttachedFromPart = NULL;
	m_numberOfPaths = 0;
	m_displayListID = 3;

	for (i = 0; i < 8; i++)
	{
		m_fogParameters[i] = 0.0f;
	}

	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		m_eyeViewHash[i] = NULL;
	}

	//m_socket = NULL;
	//m_acceptSocket = NULL;
	m_resumeMove = FALSE;

	//YoMessage("");

	return TRUE;

}

BOOL CStageDoc::YoReadWorkcell(FILE *fp)
//BOOL CStageDoc::YoReadWorkcell(CArchive& ar)
{
	//CStatusBarCtrl& GetStatusBarCtrl( ) const;
	//CStatusBarCtrl& sbar;
	//CFrameWnd *pMainFrame = GetTopLevelFrame(); 

	//sbar = ((CMainFrame *)pMainFrame)->m_wndStatusBar->GetStatusBarCtrl();
	//sbar->SetText("Reading in Workcell", 255, SBT_NOBORDERS);

	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	int i;
	char s[256];
	char command[32];
	int ch = 0;
	BOOL done = FALSE;
	CWnd *pCBox;
	int nErrorCode;
	
	//fp = fopen((char *)lpszPathName, "r");

	//pView->YoRender(YO_RENDER_NO_LIGHT);
	// yo_init_open();

	//while(ar.ReadString(s, 128))
	//{
	while(!done)
	{
		// Read in single line from file
		memset(s, 0, 256);
		for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}

		else if (strcmp(command, "NULL") == 0)
		{
			fclose(fp);
			YoLinkTrackSegs();
			if (m_currentDevice != NULL && m_mode != YO_MODE_PLAY_SIM)
			{
				m_currentPart = m_currentDevice->m_ptrPart;
				//sprintf(s, "Device: %s   Part: %s",
				//	m_currentDevice->m_name, m_currentPart->m_partName);
				//YoMessage(s);
				if (pMainFrame->m_wndDlgEyeVisible && pMainFrame->m_wndDlgEye != NULL)
				{
					pMainFrame->YoUpdateEyeDlg();
				}
			}
			else
			{
				//YoMessage("Simulation Mode");
				if (m_acceptSocket)
				{
					m_acceptSocket->OnClose(nErrorCode);
					m_acceptSocket = NULL;
				}
				if (m_socket)
				{
					m_socket->OnClose(nErrorCode);
					m_socket = NULL;
					pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_CONNECT);
					pCBox->ShowWindow(SW_HIDE);
					pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_LISTEN);
					pCBox->ShowWindow(SW_HIDE);
					//pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_MODE_SOCKET);
					//((CButton *)pCBox)->SetBitmap((HBITMAP)pMainFrame->m_bmCircleRed);
				}
			}
			done = TRUE;
			return TRUE;
		}

		else if (strcmp(command, "SIMULATION") == 0)
		{
			m_mode = YO_MODE_PLAY_SIM;
		}
		
		else if (strcmp(command, "DEVICE") == 0)
		{
			CStageDevice *ptrDevice;
			ptrDevice = new CStageDevice(this);
			ptrDevice->m_type = YO_DEVICE;
			ptrDevice->YoInitDevice(ptrDevice);
			if (ptrDevice->YoReadDevice(fp, ptrDevice) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrDevice;
		}
		else if (strcmp(command, "LIGHT") == 0)
		{
			CStageLight *ptrLight;
			ptrLight = new CStageLight(this);
			ptrLight->m_type = YO_LIGHT;
			ptrLight->YoInitDevice((CStageDevice *)ptrLight);
			if (ptrLight->YoReadLight(fp, ptrLight) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrLight;
		}
		else if (strcmp(command, "ROBOT6") == 0)
		{
			CStageRobot6 *ptrRobot6;
			ptrRobot6 = new CStageRobot6(this);
			ptrRobot6->m_type = YO_ROBOT6;
			ptrRobot6->YoInitDevice((CStageDevice *)ptrRobot6);
			if (ptrRobot6->YoReadRobot6(fp, ptrRobot6) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrRobot6;
		}
		else if (strcmp(command, "ROTARY_TABLE") == 0)
		{
			CStageRotaryTable *ptrRotaryTable;
			ptrRotaryTable = new CStageRotaryTable(this);
			ptrRotaryTable->m_type = YO_ROTARY_TABLE;
			ptrRotaryTable->YoInitDevice((CStageDevice *)ptrRotaryTable);
			if (ptrRotaryTable->YoReadRotaryTable(fp, ptrRotaryTable) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrRotaryTable;
		}
		else if (strcmp(command, "CAMERA") == 0)
		{
			CStageCamera *ptrCamera;
			ptrCamera = new CStageCamera(this);
			ptrCamera->m_type = YO_CAMERA;
			ptrCamera->YoInitDevice((CStageDevice *)ptrCamera);
			if (ptrCamera->YoReadCamera(fp, ptrCamera) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrCamera;
		}
		else if (strcmp(command, "GRIPPER") == 0)
		{
			CStageGripper *ptrGripper;
			ptrGripper = new CStageGripper(this);
			ptrGripper->m_type = YO_GRIPPER;
			ptrGripper->YoInitDevice((CStageDevice *)ptrGripper);
			if (ptrGripper->YoReadGripper(fp, ptrGripper) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrGripper;
		}
		else if (strcmp(command, "BARRETT_HAND") == 0)
		{
			CStageBarrettHand *ptrBarrettHand;
			ptrBarrettHand = new CStageBarrettHand(this);
			ptrBarrettHand->m_type = YO_BARRETT_HAND;
			ptrBarrettHand->YoInitDevice((CStageDevice *)ptrBarrettHand);
			if (ptrBarrettHand->YoReadBarrettHand(fp, ptrBarrettHand) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrBarrettHand;
		}
		else if (strcmp(command, "BAR_CODE_READER") == 0)
		{
			CStageBarCodeReader *ptrBarCodeReader;
			ptrBarCodeReader = new CStageBarCodeReader(this);
			ptrBarCodeReader->m_type = YO_BAR_CODE_READER;
			ptrBarCodeReader->YoInitDevice((CStageDevice *)ptrBarCodeReader);
			if (ptrBarCodeReader->YoReadBarCodeReader(fp, ptrBarCodeReader) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrBarCodeReader;
		}
		else if (strcmp(command, "SCALE") == 0)
		{
			CStageScale *ptrScale;
			ptrScale = new CStageScale(this);
			ptrScale->m_type = YO_SCALE;
			ptrScale->YoInitDevice((CStageDevice *)ptrScale);
			if (ptrScale->YoReadScale(fp, ptrScale) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrScale;
		}
		else if (strcmp(command, "TRACK") == 0)
		{
			CStageDevice *ptrDevice;
			ptrDevice = new CStageDevice(this);
			ptrDevice->m_type = YO_TRACK;
			ptrDevice->YoInitDevice(ptrDevice);
			if (ptrDevice->YoReadDevice(fp, ptrDevice) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrDevice;
		}
		else if (strcmp(command, "TRAIN") == 0)
		{
			CStageTrain *ptrTrain;
			ptrTrain = new CStageTrain(this);
			ptrTrain->m_type = YO_TRAIN;
			ptrTrain->YoInitDevice((CStageDevice *)ptrTrain);
			if (ptrTrain->YoReadTrain(fp, ptrTrain) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrTrain;
		}
		else if (strcmp(command, "CONVEYOR") == 0)
		{
			CStageConveyor *ptrConveyor;
			ptrConveyor = new CStageConveyor(this);
			ptrConveyor->m_type = YO_CONVEYOR;
			ptrConveyor->YoInitDevice((CStageDevice *)ptrConveyor);
			if (ptrConveyor->YoReadConveyor(fp, ptrConveyor) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrConveyor;
		}
		else if (strcmp(command, "CONVEYOR_PALLET") == 0)
		{
			CStageConveyorPallet *ptrConveyorPallet;
			ptrConveyorPallet = new CStageConveyorPallet(this);
			ptrConveyorPallet->m_type = YO_CONVEYOR_PALLET;
			ptrConveyorPallet->YoInitDevice((CStageDevice *)ptrConveyorPallet);
			if (ptrConveyorPallet->YoReadConveyorPallet(fp, ptrConveyorPallet) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrConveyorPallet;
		}
		else if (strcmp(command, "CAMERA") == 0)
		{
			CStageCamera *ptrCamera;
			ptrCamera = new CStageCamera(this);
			ptrCamera->m_type = YO_CAMERA;
			ptrCamera->YoInitDevice((CStageDevice *)ptrCamera);
			if (ptrCamera->YoReadCamera(fp, ptrCamera) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrCamera;
		}
		else if (strcmp(command, "PART") == 0)
		{
			CStagePart *ptrPart;
			ptrPart = new CStagePart(this);
			ptrPart->YoInitPart(ptrPart);
			ptrPart->m_displayListID = YoGetNewDisplayListID(ptrPart, NULL);
			//ptrPart->m_wireframeDisplayListID = YoGetNewDisplayListID((CStagePart *)NULL);
			if (ptrPart->YoReadPart(fp, ptrPart) == FALSE)
			{
				return FALSE;
			}	
		}

		else if (strcmp(command, "ALPHA_BLENDING") == 0)
		{
			sscanf(s, "%*s %d %d", &m_alphaBlending[0],
				&m_alphaBlending[1]);
			glBlendFunc(m_alphaBlending[0], m_alphaBlending[1]);
		}
		else if (strcmp(command, "ALPHA_FUNCTION") == 0)
		{
			sscanf(s, "%*s %d %f",
				&m_alphaFunction, &m_alphaFunctionRef);
			::glAlphaFunc(m_alphaFunction, m_alphaFunctionRef);
		}
    
		else if (strcmp(command, "GRID") == 0)
		{
			//sscanf(s, "%*s %d %d %d %d %d %d %d",
			sscanf(s, "%*s %f %f %f %f %f %f %f",
				&m_grid[0], &m_grid[1], &m_grid[2], &m_grid[3],
				&m_grid[4], &m_grid[5], &m_grid[6]);
		}
		else if (strcmp(command, "LIGHTING_MODEL") == 0)
		{
			sscanf(s, "%*s %d %d %d %d %d %d %d",
				&m_lighting[0], &m_lighting[1], &m_lighting[2],
				&m_lighting[3], &m_lighting[4], &m_lighting[5]);
			// light model is always local, ignore m_lighting[0]
			//::glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, m_lighting[0]);
			::glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, m_lighting[1]);
			GLfloat lma[4];
			lma[0] = (GLfloat)m_lighting[2] / 255.0f;
			lma[1] = (GLfloat)m_lighting[3] / 255.0f;
			lma[2] = (GLfloat)m_lighting[4] / 255.0f;
			lma[3] = (GLfloat)m_lighting[5] / 255.0f;
			::glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lma);
		}
		else if (strcmp(command, "SUN_PARAMETERS") == 0)
		{
			sscanf(s, "%*s %f %f %f",
				&m_sunAltitude, &m_sunAzimuth, &m_sunIntensity);
		}
		else if (strcmp(command, "WORLD_COORDINATE_FRAME") == 0)
		{
			sscanf(s, "%*s %d", &m_worldCoordinateFrame);
		}
		else if (strcmp(command, "UNITS") == 0)
		{
			sscanf(s, "%*s %s", &command);
			if (strcmp(command, "inches") == 0)
			{
				m_units = YO_UNITS_INCHES;
			}
			else if (strcmp(command, "feet") == 0)
			{
				m_units = YO_UNITS_FEET;
			}
			else if (strcmp(command, "meters") == 0)
			{
				m_units = YO_UNITS_METERS;
			}
			else
			{
				m_units = YO_UNITS_MILLIMETERS;
			}
			YoUnitScaleFactor();
		}
		else if (strcmp(command, "BOUNDING_BOX") == 0)
		{
			sscanf(s, "%*s %d", &m_boundingBox);
		}
		else if (strcmp(command, "AUTO_SOCKET_SERVER") == 0)
		{
			//sscanf(s, "%*s %d", &m_autoSocketServer);
			//if (m_mode != YO_MODE_PLAY_SIM
			//	&& m_autoSocketServer
			//	&& m_socket == NULL)
			//{
			//	pMainFrame->SendMessage(WM_COMMAND, IDC_SOCKET, (LPARAM)0);
				//pMainFrame->SendMessage(WM_COMMAND, IDC_IMMEDIATE_MODE, (LPARAM)0);
			//}
		}
		else if (strcmp(command, "FOG") == 0)
		{
			sscanf(s, "%*s %d %d %f %f %f %f %f %f %f %f",
				&m_fog[0], &m_fog[1],
				&m_fogParameters[0], &m_fogParameters[1],
				&m_fogParameters[2], &m_fogParameters[3],
				&m_fogParameters[4], &m_fogParameters[5],
				&m_fogParameters[6], &m_fogParameters[7]);
			if (m_fog[0])
			{
				glEnable(GL_FOG);
				glFogfv(m_fog[1], m_fogParameters);
			}
			else
			{
				glDisable(GL_FOG);
			}
  
		}
		else if (strcmp(command, "SPLINE_RESOLUTION") == 0)
		{
			sscanf(s, "%*s %f", &m_splineResolution);
		}
		else if (strcmp(command, "EYE") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
				&pView->m_eye[0], &pView->m_eye[1], &pView->m_eye[2],
				&pView->m_eye[3], &pView->m_eye[4], &pView->m_eye[5],
				&pView->m_eye[6], &pView->m_eye[7], &pView->m_eye[8],
				&pView->m_clipFront, &pView->m_clipRear,
				&pView->m_fieldOfView, &pView->m_aspectRatio);


			for (i = 0; i < 9; i++)
			{
				m_eyeList->m_eye[0][i] = pView->m_eye[i];
				m_eyeList->m_eye[1][i] = pView->m_eye[i];
			}
			m_eyeList->m_clipFront[0] = pView->m_clipFront;
			m_eyeList->m_clipFront[1] = pView->m_clipFront;
			m_eyeList->m_clipRear[0] = pView->m_clipRear;
			m_eyeList->m_clipRear[1] = pView->m_clipRear;
			m_eyeList->m_fieldOfView[0] = pView->m_fieldOfView;
			m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
			m_eyeList->m_timeOfMove = 0.0f;
			m_eyeList->m_timeStart = 0.0f;
			m_eyeList->m_moving = FALSE;

			::glMatrixMode(GL_PROJECTION);
			::glLoadIdentity();
			::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
				pView->m_clipFront, pView->m_clipRear);
			
			::glMatrixMode(GL_MODELVIEW);
			::glLoadIdentity();
			::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
				pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
				pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);
		}

		else if (strcmp(command, "ANIMATION") == 0)
		// eliminate in future versions (Feb 2001)
		{
			sscanf(s, "%*s %d %d",
				&m_timeEnd, &m_framesPerSecond);
		}

		else if (strcmp(command, "FRAMES_PER_SECOND") == 0)
		{
			//sscanf(s, "%*s %d", &m_framesPerSecond);
			sscanf(s, "%*s %*d");
		}

		else if (strcmp(command, "REAL_TIME") == 0)
		{
			//sscanf(s, "%*s %d",	&m_realTime);
			sscanf(s, "%*s %*d");
		}

		else if (strcmp(command, "ANTI_ALIAS") == 0)
		{
			//sscanf(s, "%*s %d", &m_antiAlias);
			sscanf(s, "%*s %*d");
		}

		else if (strcmp(command, "SMOOTH_SHADING") == 0)
		{
			//sscanf(s, "%*s %d", &m_smoothShading);
			sscanf(s, "%*s %*d");
		}

		else if (strcmp(command, "OUTPUT_BITMAP") == 0)
		{
			//sscanf(s, "%*s %d", &m_outputBitmap);
			sscanf(s, "%*s %*d");
		}

		else if (strcmp(command, "EYE_MOTION") == 0)
		{
			CStageEyeMotion *ptrEyeMotion;
			ptrEyeMotion = new CStageEyeMotion(this);
			ptrEyeMotion->YoReadEyeMotion(fp);
		}

		else if (strcmp(command, "EYE_EFFECT") == 0)
		{
			//YoReadEye(fp, EYE_EFFECT);
		}
		else if (strcmp(command, "EYE_VIEW") == 0)
		{
			CStageEyeView *ptrEyeView;
			ptrEyeView = new CStageEyeView(this);
			ptrEyeView->YoReadEyeView(fp);
		}
		else if (strcmp(command, "COMMAND_LIST") == 0)
		{
			m_commandList = new CStageCommand(this);
			m_currentCommand = m_commandList;
			m_commandList->YoReadCommands(fp);
		}
		else
		{
			sprintf(s, "Error reading file:\n   %s\nIncorrect file format or corrupt data encountered",
				m_fileName);
			AfxMessageBox(s);
			fclose(fp);
			YoFreeWorkcell();
			return FALSE;
		}
	} // end while (ch != EOF)

	//m_currentDevice = m_deviceList;
	//m_currentPart = m_currentDevice->m_ptrPart;

	//pView->YoRender(YO_RENDER_NO_LIGHT);
	//pView->YoRender(YO_RENDER_LIGHT);
	//pView->YoRender(YO_RENDER_FULL);

	return TRUE;
}


void CStageDoc::YoEStop(void)
// ceases movement for all devices, and eye motion.  Sets m_isMovement = 0
{
	CStageDevice *ptrDevice;
	char buf[256];
	int i;

	if (m_isMovement == 0)
	{
		return;
	}

	if (m_eyeList->m_moving == TRUE)
	{
		m_eyeList->m_moving = FALSE;
	}

	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		for (ptrDevice = m_deviceHash[i];
			ptrDevice != NULL;
			ptrDevice = ptrDevice->m_nextHash)
		{
			switch (ptrDevice->m_type)
			{
				case YO_ROBOT6:
					sprintf(buf, "BRAKE");
					((CStageRobot6 *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_ROTARY_TABLE:
					((CStageRotaryTable *)ptrDevice)->YoEStop();
					break;

				case YO_BARRETT_HAND:
					((CStageBarrettHand *)ptrDevice)->YoEStop();
					break;

				case YO_BAR_CODE_READER:
					sprintf(buf, "TRIGGEROFF");
					((CStageBarCodeReader *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_TRAIN:
					((CStageTrain *)ptrDevice)->YoEStop();
					break;

				case YO_CONVEYOR:
					((CStageConveyor *)ptrDevice)->YoEStop();
					break;

				case YO_LIGHT:
					sprintf(buf, "STOP");
					((CStageLight *)ptrDevice)->YoHandleCommand(buf);
					break;

				default:
					break;	
			}
		}
	}

	m_isMovement = FALSE;
	m_resumeMove = FALSE;

	return;
}


BOOL CStageDoc::YoWriteWorkcell(LPCTSTR lpszPathName)
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	FILE *fp;
	CStageEyeMotion *ptrEyeMotion = m_eyeList->m_motion;
	CStageEyeView *ptrEyeView;
	int i;

	//pView->m_cfile = ar.GetFile();

	//if ((pView->m_cfile = ar.GetFile()) == NULL)
	//{
	//	return FALSE;
	//}
	// yo_init_open();

	fp = fopen((char *)lpszPathName, "w");

	if (fp == NULL)
	{
		return FALSE;
	}

	if (m_mode == YO_MODE_RECORD_SIM || m_mode == YO_MODE_PLAY_SIM)
	{
		fprintf(fp, "SIMULATION\n");
	}

	fprintf(fp, "ALPHA_BLENDING %d %d\n",
		m_alphaBlending[0], m_alphaBlending[1]);

	fprintf(fp, "ALPHA_FUNCTION %d %.3f\n",
		m_alphaFunction, m_alphaFunctionRef);

	fprintf(fp, "GRID %.0f %.3f %.3f %.3f %.0f %.0f %.0f\n", m_grid[0], m_grid[1],
		m_grid[2], m_grid[3], m_grid[4], m_grid[5], m_grid[6]);

	fprintf(fp, "LIGHTING_MODEL %d %d %d %d %d %d\n", m_lighting[0], m_lighting[1],
		m_lighting[2], m_lighting[3], m_lighting[4], m_lighting[5]);

	fprintf(fp, "SUN_PARAMETERS %.3f %.3f %f\n",
		m_sunAltitude, m_sunAzimuth, m_sunIntensity);

	fprintf(fp, "WORLD_COORDINATE_FRAME %d\n", m_worldCoordinateFrame);

	fprintf(fp, "UNITS ");
	if (m_units == YO_UNITS_INCHES)
	{
		fprintf(fp, "inches\n");
	}
	else if (m_units == YO_UNITS_FEET)
	{
		fprintf(fp, "feet\n");
	}
	else if (m_units == YO_UNITS_METERS)
	{
		fprintf(fp, "meters\n");
	}
	else
	{
		fprintf(fp, "millimeters\n");
	}

	fprintf(fp, "BOUNDING_BOX %d\n", m_boundingBox);
	//fprintf(fp, "AUTO_SOCKET_SERVER %d\n", m_autoSocketServer);

	fprintf(fp, "FOG %d %d %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
		m_fog[0], m_fog[1],
		m_fogParameters[0], m_fogParameters[1],
		m_fogParameters[2], m_fogParameters[3],
		m_fogParameters[4], m_fogParameters[5],
		m_fogParameters[6], m_fogParameters[7]);

	fprintf(fp, "SPLINE_RESOLUTION %.2f\n", m_splineResolution);

	fprintf(fp, "EYE %.3f %.3f %.3f %.3f %.3f %.3f %.2f %.2f %.2f %.3f %.1f %.2f %f\n",
		pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		pView->m_eye[6], pView->m_eye[7], pView->m_eye[8],
		pView->m_clipFront, pView->m_clipRear,
		pView->m_fieldOfView, pView->m_aspectRatio);

	//fprintf(fp, "ANIMATION %d %d\n",
	//	m_timeEnd, m_framesPerSecond);

	//fprintf(fp, "FRAMES_PER_SECOND %d\n", m_framesPerSecond);

	//fprintf(fp, "REAL_TIME %d\n", m_realTime);

	//fprintf(fp, "ANTI_ALIAS %d\n", m_antiAlias);

	//fprintf(fp, "SMOOTH_SHADING %d\n", m_smoothShading);

	//fprintf(fp, "OUTPUT_BITMAP %d\n", m_outputBitmap);

	fprintf(fp, "#\n");

	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		for (ptrEyeView = m_eyeViewHash[i]; ptrEyeView != NULL; ptrEyeView = ptrEyeView->m_nextHash)
		{
			fprintf(fp, "EYE_VIEW\n");
			fprintf(fp, "EYE_VIEW_NAME %s\n", ptrEyeView->m_name);
			fprintf(fp, "EYE_VIEW_EYE %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
				ptrEyeView->m_eye[0], ptrEyeView->m_eye[1], ptrEyeView->m_eye[2],
				ptrEyeView->m_eye[3], ptrEyeView->m_eye[4], ptrEyeView->m_eye[5],
				ptrEyeView->m_eye[6], ptrEyeView->m_eye[7], ptrEyeView->m_eye[8],
				ptrEyeView->m_eye[9], ptrEyeView->m_eye[10], ptrEyeView->m_eye[11]);
			fprintf(fp, "EYE_VIEW_NULL\n");
		}
	}

	while (ptrEyeMotion != NULL)
	{
		fprintf(fp, "EYE_MOTION\n");
		fprintf(fp, "EYE_MOTION_TIME %d\n", ptrEyeMotion->m_time);
		fprintf(fp, "EYE_MOTION_TYPE %d\n", ptrEyeMotion->m_type);
		fprintf(fp, "EYE_MOTION_EYE %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.2lf %.2lf %.2lf %.3lf %.1lf %.2lf\n",
			ptrEyeMotion->m_eye[0], ptrEyeMotion->m_eye[1], ptrEyeMotion->m_eye[2],
			ptrEyeMotion->m_eye[3], ptrEyeMotion->m_eye[4], ptrEyeMotion->m_eye[5],
			ptrEyeMotion->m_eye[6], ptrEyeMotion->m_eye[7], ptrEyeMotion->m_eye[8],
			ptrEyeMotion->m_clipFront, ptrEyeMotion->m_clipRear, ptrEyeMotion->m_fieldOfView);
		fprintf(fp, "EYE_MOTION_NULL\n");
		ptrEyeMotion = ptrEyeMotion->m_next;

	} // end while (ptrEyeMotion != NULL)

	fprintf(fp, "#\n");

	pView->m_fp = fp;
	pView->YoRenderDevice(YO_RENDER_SAVE_WORKCELL);

	if (m_mode == YO_MODE_RECORD_SIM)
	{
		return TRUE;
	}
	if (m_mode == YO_MODE_PLAY_SIM
		&& m_commandList != NULL)
	{
		m_commandList->YoWriteCommands(pView->m_fp);
	}
	fprintf(fp, "NULL\n");
	fclose(fp);
	return TRUE;
}


BOOL CStageDoc::YoWriteViewBitmap(char *filename)
// Write the current opengl (CStageView) window to a bitmap (bmp) file
// Note: the entire window must be visible on the screen and no other windows
// should cover the opengl window
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	HWND hWnd;
	RECT rectWnd;
	HPALETTE hPal = NULL;  // handle to palette
	HANDLE hDIB = NULL;   // handle to DIB

	hWnd = pView->GetSafeHwnd();
	//hWnd = pView->m_hWnd;

	// check for a valid window handle
	if (!hWnd)
	{
		return NULL;
	}

	// get the window rectangle
	GetWindowRect(hWnd, &rectWnd);
	LPRECT lpRect = &rectWnd;

	// get the device-dependent bitmap in lpRect by calling
	// CopyScreenToBitmap and passing it the rectangle to grab

	HDC hScrDC;						// screen DC
	HDC hMemDC;						// memory DC
	HBITMAP hBitmap;				// handle to device-dependent bitmap
	HBITMAP hOldBitmap;
	int nX, nY, nX2, nY2;			// coordinates of rectangle to grab
	int nWidth, nHeight;			// DIB width and height
	int xScrn, yScrn;				// screen resolution

	// check for an empty rectangle
	if (IsRectEmpty(lpRect))
	{
		return NULL;
	}

	// create a DC for the screen and create a memory DC compatible to screen DC
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	hMemDC = CreateCompatibleDC(hScrDC);

	/* get points of rectangle to grab */
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	// get screen resolution
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);

	// make sure bitmap rectangle is visible
	if (nX < 0)
	{
		nX = 0;
	}
	if (nY < 0)
	{
		nY = 0;
	}
	if (nX2 > xScrn)
	{
		nX2 = xScrn;
	}
	if (nY2 > yScrn)
	{
		nY2 = yScrn;
	}
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;

	// create a bitmap compatible with the screen DC
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth - 4, nHeight - 4);
	//hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);

	// select new bitmap into memory DC
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	// bitblt screen DC to memory DC
	// need to eliminate border around CView window
	BitBlt(hMemDC, 0, 0, nWidth - 4, nHeight - 4, hScrDC, nX + 2, nY + 2, SRCCOPY);
	// BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);

	//  select old bitmap back into memory DC and get handle to
	//  bitmap of the screen
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);

	DeleteDC(hScrDC);
	DeleteDC(hMemDC);

    BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 

    // Retrieve the bitmap's color format, width, and height. 
    if (!GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bmp))
	{
		TRACE0("ERROR: YoWriteViewBitmap()  GetObject\n");
	}

    // Convert the color format to a count of bits. 
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
	if (cClrBits == 1)
	{
		cClrBits = 1;
	}
	else if (cClrBits <= 4)
	{
		cClrBits = 4;
	}
	else if (cClrBits <= 8)
	{
		cClrBits = 8;
	}
	else if (cClrBits <= 16)
	{
		cClrBits = 16;
	}
	else if (cClrBits <= 24)
	{
		cClrBits = 24;
	}
	else
	{
		cClrBits = 32;
	}

	// Allocate memory for the BITMAPINFO structure. (This structure contains a
	// BITMAPINFOHEADER structure and an array of RGBQUAD data structures.) 

	if (cClrBits != 24)
	{
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER) + 
			sizeof(RGBQUAD) * (1<<cClrBits)); 
	}
	else 
	{
		// There is no RGBQUAD array for the 24-bit-per-pixel format. 
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER)); 
	}

	// Initialize the fields in the BITMAPINFO structure. 
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	pbmi->bmiHeader.biWidth = bmp.bmWidth; 
	pbmi->bmiHeader.biHeight = bmp.bmHeight; 
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
	if (cClrBits < 24)
	{
		pbmi->bmiHeader.biClrUsed = (1<<cClrBits);
	}

	// If the bitmap is not compressed, set the BI_RGB flag. 
	pbmi->bmiHeader.biCompression = BI_RGB; 

	// Compute the number of bytes in the array of color indices
	// and store the result in biSizeImage. 
	pbmi->bmiHeader.biSizeImage = (pbmi->bmiHeader.biWidth + 7) / 8 
		* pbmi->bmiHeader.biHeight * cClrBits;

	// Set biClrImportant to 0, indicating that all of the device colors are important. 
	pbmi->bmiHeader.biClrImportant = 0; 

	// The following example code defines a function that initializes the remaining structures,
	// retrieves the array of palette indices, opens the file, copies the data, and closes the file. 

	LPTSTR pszFile = filename;
    HANDLE hf;                 // file handle 
    BITMAPFILEHEADER hdr;       // bitmap file-header 
    PBITMAPINFOHEADER pbih;     // bitmap info-header 
    LPBYTE lpBits;              // memory pointer 
    DWORD dwTotal;              // total count of bytes 
    DWORD cb;                   // incremental count of bytes 
    BYTE *hp;                   // byte pointer 
    DWORD dwTmp; 

    pbih = (PBITMAPINFOHEADER) pbmi; 
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

    if (!lpBits) 
	{
		TRACE0("ERROR: YoWriteViewBitmap()  lpBits\n");
	}

	HDC hDC;
	hDC = GetDC(NULL);

	// Retrieve the color table (RGBQUAD array) and the bits 
	// (array of palette indices) from the DIB. 
	if (!GetDIBits(hDC, hBitmap, 0, (WORD) pbih->biHeight, lpBits, pbmi, 
		DIB_RGB_COLORS)) 
	{
		TRACE0("ERROR: YoWriteViewBitmap()  GetDIBits\n");
	}

	// Create the .BMP file. 
	hf = CreateFile(pszFile, 
		GENERIC_READ | GENERIC_WRITE, 
		(DWORD) 0, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		(HANDLE) NULL); 

	if (hf == INVALID_HANDLE_VALUE) 
	{
		TRACE0("ERROR: YoWriteViewBitmap()  CreateFile\n");
	}

	hdr.bfType = 0x4d42;			// 0x42 = "B" 0x4d = "M" 
	// Compute the size of the entire file. 
	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + pbih->biSizeImage); 
	hdr.bfReserved1 = 0; 
	hdr.bfReserved2 = 0; 

	// Compute the offset to the array of color indices. 
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed * sizeof (RGBQUAD); 

	// Copy the BITMAPFILEHEADER into the .BMP file. 
	if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
		(LPDWORD) &dwTmp,  NULL)) 
	{
		TRACE0("ERROR: YoWriteViewBitmap()  WriteFile\n");
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
	if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
		+ pbih->biClrUsed * sizeof (RGBQUAD), (LPDWORD) &dwTmp, ( NULL))) 
	{
		TRACE0("ERROR: YoWriteViewBitmap()  WriteFile\n");
	}

	// Copy the array of color indices into the .BMP file. 
	dwTotal = cb = pbih->biSizeImage; 
	hp = lpBits; 
	if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) 
	{
		TRACE0("ERROR: YoWriteViewBitmap()  WriteFile\n");
	}

	// Close the .BMP file. 
	if (!CloseHandle(hf)) 
	{
		TRACE0("ERROR: YoWriteViewBitmap()  CloseHandle\n");
	}

	// must release DC or ogl errors result
	ReleaseDC(hWnd, hDC);

	LocalFree(pbmi);
	GlobalFree((HGLOBAL)lpBits);
	DeleteObject(hBitmap);

	return TRUE;
}


CStageDevice::CStageDevice()
{
}


BOOL CStageDevice::YoInitDevice(CStageDevice *ptrDevice)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	int i;

	sprintf(ptrDevice->m_name, "");
	sprintf(ptrDevice->m_parent, "NONE");
	ptrDevice->m_min[0] = 0.0;
	ptrDevice->m_min[1] = 0.0;
	ptrDevice->m_min[2] = 0.0;
	ptrDevice->m_max[0] = 0.0;
	ptrDevice->m_max[1] = 0.0;
	ptrDevice->m_max[2] = 0.0;
	ptrDevice->m_scale[0] = 1.0;
	ptrDevice->m_scale[1] = 1.0;
	ptrDevice->m_scale[2] = 1.0;
	ptrDevice->m_visible = TRUE;
	ptrDevice->m_mass = 0.0;
	sprintf(ptrDevice->m_barCode, "000000000000");
	ptrDevice->m_ptrPart = NULL;
	ptrDevice->m_nextHash = NULL;
	//ptrDevice->m_stackBit = 0;
	//ptrDevice->m_nextStack = NULL;
	ptrDevice->m_right = NULL;
	ptrDevice->m_down = NULL;
	ptrDevice->m_left = NULL;
	ptrDevice->m_up = NULL;
	ptrDevice->m_attachedFromPart = NULL;

	if (ptrDevice->m_type == YO_LIGHT)
	{
		((CStageLight *)ptrDevice)->m_target = 0;
		((CStageLight *)ptrDevice)->m_enabled = FALSE;
		((CStageLight *)ptrDevice)->m_changing = FALSE;
		((CStageLight *)ptrDevice)->m_pointSource = TRUE;
		((CStageLight *)ptrDevice)->m_intensity = 1.0f;
		((CStageLight *)ptrDevice)->m_intensityStart = 1.0f;
		((CStageLight *)ptrDevice)->m_intensityFinal = 1.0f;
		((CStageLight *)ptrDevice)->m_spotCutoff = 180.0f;
		((CStageLight *)ptrDevice)->m_attenuation[0] = 0.0f;
		((CStageLight *)ptrDevice)->m_attenuation[1] = 0.0f;
		((CStageLight *)ptrDevice)->m_attenuation[2] = 0.0f;
		((CStageLight *)ptrDevice)->m_shadowMap = NULL;
		((CStageLight *)ptrDevice)->m_ptrLight = NULL;
		/***
		((CStageLight *)ptrDevice)->m_ambient[0] = 0.0f;
		((CStageLight *)ptrDevice)->m_ambient[1] = 0.0f;
		((CStageLight *)ptrDevice)->m_ambient[2] = 0.0f;
		((CStageLight *)ptrDevice)->m_ambient[3] = 1.0f;
		((CStageLight *)ptrDevice)->m_diffuse[0] = 1.0f;
		((CStageLight *)ptrDevice)->m_diffuse[1] = 1.0f;
		((CStageLight *)ptrDevice)->m_diffuse[2] = 1.0f;
		((CStageLight *)ptrDevice)->m_diffuse[3] = 1.0f;
		((CStageLight *)ptrDevice)->m_specular[0] = 0.5f;
		((CStageLight *)ptrDevice)->m_specular[1] = 0.5f;
		((CStageLight *)ptrDevice)->m_specular[2] = 0.5f;
		((CStageLight *)ptrDevice)->m_specular[3] = 1.0f;
		((CStageLight *)ptrDevice)->m_position[0] = 0.0f;
		((CStageLight *)ptrDevice)->m_position[1] = 0.0f;
		((CStageLight *)ptrDevice)->m_position[2] = -0.1f;
		((CStageLight *)ptrDevice)->m_position[3] = 0.0f;
		((CStageLight *)ptrDevice)->m_parameterName = 0;
		((CStageLight *)ptrDevice)->m_spotExponent = 1.0f;
		***/
	}
	else if (ptrDevice->m_type == YO_ROBOT6)
	{
		for (i = 1; i <= 6; i++)
		{
			((CStageRobot6 *)ptrDevice)->m_j[i] = 0.0;
			((CStageRobot6 *)ptrDevice)->m_jMaxAccelMaxSpeed[i][0] = 286.0;
			((CStageRobot6 *)ptrDevice)->m_jMaxAccelMaxSpeed[i][1] = 200.0;
			((CStageRobot6 *)ptrDevice)->m_jMinAccelTime[i] = 0.1;
			((CStageRobot6 *)ptrDevice)->m_jMinMax[i][0] = -180.0;
			((CStageRobot6 *)ptrDevice)->m_jMinMax[i][1] = 180.0;
			((CStageRobot6 *)ptrDevice)->m_home[i] = 0.0;
			((CStageRobot6 *)ptrDevice)->m_jFinal[i] = 0.0;
		}
		for (i = 0; i < 6; i++)
		{
			((CStageRobot6 *)ptrDevice)->m_tcpOffset[i] = 0.0;
			((CStageRobot6 *)ptrDevice)->m_cartesianSpace[i] = 0.0;
		}
		((CStageRobot6 *)ptrDevice)->m_speed = 50;
		((CStageRobot6 *)ptrDevice)->m_accelTime = 0.1;
		((CStageRobot6 *)ptrDevice)->m_accelDistance = 0.0;
		((CStageRobot6 *)ptrDevice)->m_totalDistance = 0.0;
		((CStageRobot6 *)ptrDevice)->m_minAccelTime = 0.1;
		((CStageRobot6 *)ptrDevice)->m_jointInterpolation = TRUE;
		((CStageRobot6 *)ptrDevice)->m_timeOfMove = 0.0;
		((CStageRobot6 *)ptrDevice)->m_moving = FALSE;
		((CStageRobot6 *)ptrDevice)->m_lefty = TRUE;
		((CStageRobot6 *)ptrDevice)->m_elbowUp = TRUE;
		((CStageRobot6 *)ptrDevice)->m_wristFlipped = FALSE;
	}
	else if (ptrDevice->m_type == YO_ROTARY_TABLE)
	{
		((CStageRotaryTable *)ptrDevice)->m_acceleration = 100.0f;
		((CStageRotaryTable *)ptrDevice)->m_currentPosition = 0;
		((CStageRotaryTable *)ptrDevice)->m_directionPositive = TRUE;
		((CStageRotaryTable *)ptrDevice)->m_distance = 0;
		((CStageRotaryTable *)ptrDevice)->m_endPosition = 0;
		((CStageRotaryTable *)ptrDevice)->m_encoderResolution = 4000;
		((CStageRotaryTable *)ptrDevice)->m_positionAbsolute = TRUE;
		((CStageRotaryTable *)ptrDevice)->m_ptrRotateInfo = NULL;
		((CStageRotaryTable *)ptrDevice)->m_rotating = 0;
		((CStageRotaryTable *)ptrDevice)->m_simRequestDone = TRUE;
		((CStageRotaryTable *)ptrDevice)->m_stoppingTable = FALSE;
		((CStageRotaryTable *)ptrDevice)->m_velocity = 1.0f;
	}
	else if (ptrDevice->m_type == YO_GRIPPER)
	{
		((CStageGripper *)ptrDevice)->m_gripping = FALSE;
		((CStageGripper *)ptrDevice)->m_typeTranslating = TRUE;
			// else gripper is of rotating type
			// with displacement in degrees
		((CStageGripper *)ptrDevice)->m_displacementOpen = 0.0f;
		((CStageGripper *)ptrDevice)->m_displacementClose = 0.0f;
	}
	else if (ptrDevice->m_type == YO_BARRETT_HAND)
	{
		((CStageBarrettHand *)ptrDevice)->m_gripping = FALSE;
		((CStageBarrettHand *)ptrDevice)->m_spread = 0.0;
		((CStageBarrettHand *)ptrDevice)->m_spreading = FALSE;

		for (i = 0; i < 3; i++)
		{
			((CStageBarrettHand *)ptrDevice)->m_fingerFixed[i] = 0.0;
			((CStageBarrettHand *)ptrDevice)->m_fingerLeft[i] = 0.0;
			((CStageBarrettHand *)ptrDevice)->m_fingerRight[i] = 0.0;
		}
		((CStageBarrettHand *)ptrDevice)->m_velocity = 500.0;
		((CStageBarrettHand *)ptrDevice)->m_moving = FALSE;

	}
	else if (ptrDevice->m_type == YO_BAR_CODE_READER)
	{
		((CStageBarCodeReader *)ptrDevice)->m_scanning = FALSE;
		((CStageBarCodeReader *)ptrDevice)->m_scanDistance = YO_SCAN_DISTANCE;
		sprintf(((CStageBarCodeReader *)ptrDevice)->m_barCode, "000000000000");
	}
	else if (ptrDevice->m_type == YO_SCALE)
	{
		((CStageScale *)ptrDevice)->m_weighing = FALSE;
		((CStageScale *)ptrDevice)->m_units = YO_UNITS_KILOGRAMS;
		((CStageScale *)ptrDevice)->m_mass = 0.0f;
	}
	else if (ptrDevice->m_type == YO_TRAIN)
	{
		((CStageTrain *)ptrDevice)->m_ptrTrackSeg = NULL;
		//((CStageTrain *)ptrDevice)->m_attachTrackSeg = 1;
		//((CStageTrain *)ptrDevice)->m_attachRelativePosition = 0.0f;
		((CStageTrain *)ptrDevice)->m_moving = FALSE;
		((CStageTrain *)ptrDevice)->m_ptrTrackSegEnd = NULL;
		((CStageTrain *)ptrDevice)->m_relativePositionEnd = 0.0f;
		//((CStageTrain *)ptrDevice)->m_endPosition[0] = 0.0f;
		//((CStageTrain *)ptrDevice)->m_endPosition[1] = 0.0f;
		//((CStageTrain *)ptrDevice)->m_currentPosition[0] = 0.0f;
		//((CStageTrain *)ptrDevice)->m_currentPosition[1] = 0.0f;
		((CStageTrain *)ptrDevice)->m_relativePosition = 0.0f;
		((CStageTrain *)ptrDevice)->m_velocity = 100.0f;
		((CStageTrain *)ptrDevice)->m_acceleration = 500.0f;
		((CStageTrain *)ptrDevice)->m_initialVelocity = 0.0f;
		((CStageTrain *)ptrDevice)->m_curVelocity = 0.0f;
		((CStageTrain *)ptrDevice)->m_finalVelocity = 100.0f;
		((CStageTrain *)ptrDevice)->m_reverseFinalVelocity = 0.0f;
		((CStageTrain *)ptrDevice)->m_directionPositive = TRUE;
		//((CStageTrain *)ptrDevice)->m_heading = 0.0;
		((CStageTrain *)ptrDevice)->m_trackOrientation = YO_TRACK_FROM_TO;
		((CStageTrain *)ptrDevice)->m_stoppingTrain = FALSE;
		((CStageTrain *)ptrDevice)->m_simRequestDone = FALSE;
	}
	else if (ptrDevice->m_type == YO_CONVEYOR)
	{
		((CStageConveyor *)ptrDevice)->m_offset[0] = 0.0f;
		((CStageConveyor *)ptrDevice)->m_offset[1] = 0.0f;
		((CStageConveyor *)ptrDevice)->m_offset[2] = 0.0f;
		((CStageConveyor *)ptrDevice)->m_moving = 0;
		// ((CStageConveyor *)ptrDevice)->m_ptrPallet = NULL;
		((CStageConveyor *)ptrDevice)->m_ptrSegment = NULL;
		// ((CStageConveyor *)ptrDevice)->m_ptrSensor = NULL;
		// ((CStageConveyor *)ptrDevice)->m_ptrStopGate = NULL;
		// ((CStageConveyor *)ptrDevice)->m_ptrTransverseLift = NULL;
	}
	else if (ptrDevice->m_type == YO_CONVEYOR_PALLET)
	{
		((CStageConveyorPallet *)ptrDevice)->m_startPosition[0] = 0.0f;
		((CStageConveyorPallet *)ptrDevice)->m_startPosition[1] = 0.0f;
		((CStageConveyorPallet *)ptrDevice)->m_startPosition[2] = 0.0f;
		((CStageConveyorPallet *)ptrDevice)->m_endPosition[0] = 0.0f;
		((CStageConveyorPallet *)ptrDevice)->m_endPosition[1] = 0.0f;
		((CStageConveyorPallet *)ptrDevice)->m_endPosition[2] = 0.0f;
		((CStageConveyorPallet *)ptrDevice)->m_moving = FALSE;
		((CStageConveyorPallet *)ptrDevice)->m_position[0] = 0.0f;
		((CStageConveyorPallet *)ptrDevice)->m_position[1] = 0.0f;
		((CStageConveyorPallet *)ptrDevice)->m_position[2] = 0.0f;
		((CStageConveyorPallet *)ptrDevice)->m_distance = 0.0f;
		((CStageConveyorPallet *)ptrDevice)->m_ptrNextPallet = NULL;
		((CStageConveyorPallet *)ptrDevice)->m_ptrPrevPallet = NULL;
		((CStageConveyorPallet *)ptrDevice)->m_ptrSegment = NULL;
		((CStageConveyorPallet *)ptrDevice)->m_relativePosition = 0.0f;
	}
	else if (ptrDevice->m_type == YO_CAMERA)
	{
		((CStageCamera *)ptrDevice)->m_enabled = FALSE;
		((CStageCamera *)ptrDevice)->m_fieldOfView = pView->m_fieldOfView;
		((CStageCamera *)ptrDevice)->m_clipFront = pView->m_clipFront;
		((CStageCamera *)ptrDevice)->m_clipRear = pView->m_clipRear;
		((CStageCamera *)ptrDevice)->m_fStop = 16.0;
		((CStageCamera *)ptrDevice)->m_ptrCamera = NULL;
	}

	return TRUE;
}


BOOL CStageDevice::YoReadDevice(FILE *fp, CStageDevice *ptrDevice)

{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	CStageDevice		*ptrParent;

	while (!done)
	{
		// Read in single line from file
		//ar.ReadString(s, 128);
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "DEVICE_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrDevice, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "DEVICE_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrDevice->m_name);
		}
		else if (strcmp(command, "DEVICE_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrDevice->m_parent, &partAttachName);
			if (strcmp(ptrDevice->m_parent, "NONE") != 0)
			{
				ptrParent = m_pDoc->YoDeviceHashLookup(ptrDevice->m_parent);
				ptrPart = m_pDoc->YoPartLookup(ptrParent, partAttachName);
			}
		}
		else if (strcmp(command, "DEVICE_SCALE") == 0)
		{
			sscanf(s, "%*s %f %f %f", &ptrDevice->m_scale[0],
				&ptrDevice->m_scale[1], &ptrDevice->m_scale[2]);
		}
		else if (strcmp(command, "DEVICE_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrDevice->m_visible);
		}
		else if (strcmp(command, "DEVICE_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrDevice->m_mass);
		}
		else if (strcmp(command, "DEVICE_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrDevice->m_barCode);
		}
		else
		{
			return FALSE;
		}

	} // end while (!done)
	return TRUE;
}


BOOL CStageDevice::YoHandleCommand(char ibuf[4096], char obuf[256])
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	CTimeSpan spanSec;

	if (m_pDoc->m_scriptFastForward == TRUE)
	{
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0) + m_pDoc->m_timeSleepTotal;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else if (pMainFrame->m_wndDlgScript != NULL && pMainFrame->m_wndDlgScriptVisible == TRUE)
	{
		//::GetSystemTime(&m_pDoc->m_gmTime);
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0)
		//	+ pMainFrame->m_wndDlgScript->m_timeSleepFastForward
		//	- pMainFrame->m_wndDlgScript->m_timeFastForward;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else
	{
		::GetSystemTime(&m_pDoc->m_gmTime);
	}


	return TRUE;
}


CStageLight::~CStageLight()
{
	YoFreeLight();
}


BOOL CStageLight::YoReadLight(FILE *fp, CStageLight *ptrLight)

{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	CStageDevice		*ptrParent;
  
	while (!done)
	{
		// Read in single line from file
		//ar.ReadString(s, 128);
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "LIGHT_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrLight, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "LIGHT_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrLight->m_name);
		}
		else if (strcmp(command, "LIGHT_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrLight->m_parent, &partAttachName);
			if (strcmp(ptrLight->m_parent, "NONE") != 0)
			{
				ptrParent = m_pDoc->YoDeviceHashLookup(ptrLight->m_parent);
				ptrPart = m_pDoc->YoPartLookup(ptrParent, partAttachName);
			}
		}
		else if (strcmp(command, "LIGHT_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrLight->m_visible);
		}
		else if (strcmp(command, "LIGHT_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrLight->m_mass);
		}
		else if (strcmp(command, "LIGHT_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrLight->m_barCode);
		}
		else if (strcmp(command, "LIGHT_SCALE") == 0)
		{
			sscanf(s, "%*s %f %f %f", &ptrLight->m_scale[0],
				&ptrLight->m_scale[1], &ptrLight->m_scale[2]);
		}
		else if (strcmp(command, "LIGHT_ENABLED") == 0)
		{
			sscanf(s, "%*s %d", &ptrLight->m_enabled);
			if (ptrLight->m_enabled)
			{
				ptrLight->YoGetLight();
			}
		}
		else if (strcmp(command, "LIGHT_POINT_SOURCE") == 0)
		{
			sscanf(s, "%*s %d", &ptrLight->m_pointSource);
		}
		else if (strcmp(command, "LIGHT_INTENSITY") == 0)
		{
			sscanf(s, "%*s %f", &ptrLight->m_intensity);
		}
		/****
		else if (strcmp(command, "LIGHT_AMBIENT") == 0)
		{
			sscanf(s, "%*s %f %f %f %f",
				&ptrLight->m_ambient[0], &ptrLight->m_ambient[1],
				&ptrLight->m_ambient[2], &ptrLight->m_ambient[3]);
		}
		else if (strcmp(command, "LIGHT_DIFFUSE") == 0)
		{
			sscanf(s, "%*s %f %f %f %f",
				&ptrLight->m_diffuse[0], &ptrLight->m_diffuse[1],
				&ptrLight->m_diffuse[2], &ptrLight->m_diffuse[3]);
		}
		else if (strcmp(command, "LIGHT_SPECULAR") == 0)
		{
			sscanf(s, "%*s %f %f %f %f",
				&ptrLight->m_specular[0], &ptrLight->m_specular[1],
				&ptrLight->m_specular[2], &ptrLight->m_specular[3]);
		}
		else if (strcmp(command, "LIGHT_POSITION") == 0)
		{
			sscanf(s, "%*s %f %f %f %f",
				&ptrLight->m_position[0], &ptrLight->m_position[1],
				&ptrLight->m_position[2], &ptrLight->m_position[3]);
		}
		else if (strcmp(command, "LIGHT_PARAMETER_NAME") == 0)
		{
			sscanf(s, "%*s %i", &ptrLight->m_parameterName);
		}
		else if (strcmp(command, "LIGHT_SPOT_EXPONENT") == 0)
		{
			sscanf(s, "%*s %f", &ptrLight->m_spotExponent);
		}
		****/
		else if (strcmp(command, "LIGHT_SPOT_CUTOFF") == 0)
		{
			sscanf(s, "%*s %f", &ptrLight->m_spotCutoff);
		}
		else if (strcmp(command, "LIGHT_ATTENUATION") == 0)
		{
			sscanf(s, "%*s %f %f %f", &ptrLight->m_attenuation[0],
				&ptrLight->m_attenuation[1], &ptrLight->m_attenuation[2]);
		}
		else
		{
			return FALSE;
		}
		
	} // end while (done == FALSE)
	return TRUE;
}

void CStageLight::YoCalculateLightIntensity()
{
	double				timeElapsed;
	CTime				timeStart = CTime::GetCurrentTime();
	CTime				timeCurrent = CTime::GetCurrentTime();
	int					tms;
	CTimeSpan			spanSec;
	GLdouble			a;
	char				buf[256];

	if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
	{
		timeElapsed = m_pDoc->m_timeCurrent - m_timeStart;	
	}
	else
	{
		timeCurrent = m_pDoc->m_gmTime;
		timeStart = m_gmTimeStart;
		spanSec = timeCurrent - timeStart;
		tms = m_pDoc->m_gmTime.wMilliseconds - m_gmTimeStart.wMilliseconds;
		timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
	}

	if (timeElapsed >= m_timeOfMove)
	{
		timeElapsed = m_timeOfMove;
		m_pDoc->m_isMovement--;
		m_changing = FALSE;
		m_intensity = m_intensityFinal;

		if (m_pDoc->m_acceptSocket != NULL)
		{
			memset(buf, 0, 256);
			sprintf(buf, "> %s INTENSITY %.2f %.3lf", m_name, m_intensity * 100.0, timeElapsed);
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
		return;
	}

	a = (sin(-PI / 2.0 + (PI * timeElapsed / m_timeOfMove)) + 1.0) / 2.0;
	m_intensity = (GLfloat)(m_intensityStart + a * (m_intensityFinal - m_intensityStart));

	return;
}

BOOL CStageLight::YoGetLight()
{
	// Called when a light is attempted to be enabled.
	// If successful the light is placed on the light list and TRUE is returned
	// If unsuccessful the light remains disabled and FALSE is returned

	// sun is by default GL_LIGHT0

	if (!::glIsEnabled(GL_LIGHT1))
	{
		m_target = GL_LIGHT1;
	}
	else if (!::glIsEnabled(GL_LIGHT2))
	{
		m_target = GL_LIGHT2;
	}
	else if (!::glIsEnabled(GL_LIGHT3))
	{
		m_target = GL_LIGHT3;
	}
	else if (!::glIsEnabled(GL_LIGHT4))
	{
		m_target = GL_LIGHT4;
	}
	else if (!::glIsEnabled(GL_LIGHT5))
	{
		m_target = GL_LIGHT5;
	}
	else if (!::glIsEnabled(GL_LIGHT6))
	{
		m_target = GL_LIGHT6;
	}
	else if (!::glIsEnabled(GL_LIGHT7))
	{
		m_target = GL_LIGHT7;
	}
	else
	{
		m_enabled = FALSE;
		return FALSE;
	}

	m_enabled = TRUE;
	m_pDoc->m_numberLightsOn++;

	// insert at head of light list
	m_ptrLight = m_pDoc->m_lightList;
	m_pDoc->m_lightList = this;

	return TRUE;
}


void CStageLight::YoFreeLight()
{
	// Called when a light is disabled or deleted.
	// The light is also removed from the light list

	CStageLight *curLight;

	if (m_enabled)
	{
		::glDisable(m_target);
		m_enabled = FALSE;
		m_pDoc->m_numberLightsOn--;

		// remove from light list
		for (curLight = m_pDoc->m_lightList;
			curLight != this
			&& curLight->m_ptrLight != NULL
			&& curLight->m_ptrLight != this;
			curLight = curLight->m_ptrLight);
		if (curLight == this)
		{
			m_pDoc->m_lightList = curLight->m_ptrLight;
		}
		else
		{
			curLight->m_ptrLight = this->m_ptrLight;
		}
		this->m_ptrLight = NULL;
	}

	return;
}


BOOL CStageLight::YoHandleCommand(char *buf)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	char command[16];
	char t[256];
	int i;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	CTimeSpan spanSec;

	if (m_pDoc->m_scriptFastForward == TRUE)
	{
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0) + m_pDoc->m_timeSleepTotal;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else if (pMainFrame->m_wndDlgScript != NULL && pMainFrame->m_wndDlgScriptVisible == TRUE)
	{
		//::GetSystemTime(&m_pDoc->m_gmTime);
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0)
		//	+ pMainFrame->m_wndDlgScript->m_timeSleepFastForward
		//	- pMainFrame->m_wndDlgScript->m_timeFastForward;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else
	{
		::GetSystemTime(&m_pDoc->m_gmTime);
	}

	if (toupper(buf[0]) == 'S' && toupper(buf[1]) == 'T')
	{
		sprintf(command, "STOP");
		sprintf(buf, "");
		if (m_changing == TRUE)
		{
			m_changing = FALSE;
			m_pDoc->m_isMovement--;
		}
	}
	else if (toupper(buf[0]) == 'E' && toupper(buf[1]) == 'N')
	{
		if (YoGetLight() == TRUE)
		{
			sprintf(command, "ENABLE");
			sprintf(buf, "");

			if (m_pDoc->m_isMovement == FALSE
				&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
				&& m_pDoc->m_scriptFastForward == FALSE)
			{
				pView->YoRender(YO_RENDER_LIGHT);
				pView->YoRender(YO_RENDER_FULL);
			}

		}
		else
		{
			sprintf(buf, "X ENABLE FAILED");
		}
	}
	else if (toupper(buf[0]) == 'D' && toupper(buf[1]) == 'I')
	{
		YoFreeLight();
		sprintf(command, "DISABLE");
		sprintf(buf, "");

		if (m_pDoc->m_isMovement == FALSE
			&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
			&& m_pDoc->m_scriptFastForward == FALSE)
		{
			pView->YoRender(YO_RENDER_LIGHT);
			pView->YoRender(YO_RENDER_FULL);
		}
	}
	else if (toupper(buf[0]) == 'I' && toupper(buf[1]) == 'N')
	{
		if (m_enabled == FALSE)
		{
			YoGetLight();
		}

		if (m_enabled == TRUE)
		{
			sprintf(command, "INTENSITY");
			i = sscanf(buf, "%*s %f %lf", &m_intensityFinal, &m_timeOfMove);
			if (i == 0)
			{
				sprintf(buf, "%.2f", m_intensity * 100.0);
			}
			else if (i == 1)
			{
				m_intensityFinal /= 100.0;
				m_intensity = m_intensityFinal;
				m_intensity = YO_MAX(0.0f, m_intensity);
				m_intensity = YO_MIN(1.0f, m_intensity);
				sprintf(buf, "%.2f", m_intensity * 100.0);

				if (m_pDoc->m_isMovement == FALSE
					&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
					&& m_pDoc->m_scriptFastForward == FALSE)
				{
					pView->YoRender(YO_RENDER_LIGHT);
					pView->YoRender(YO_RENDER_FULL);
				}
			}
			else if (i == 2)
			{
				m_intensityStart = m_intensity;
				m_intensityFinal /= 100.0;
				m_intensityFinal = YO_MAX(0.0f, m_intensityFinal);
				m_intensityFinal = YO_MIN(1.0f, m_intensityFinal);
				m_timeOfMove = YO_MAX(0.01, m_timeOfMove);
				sprintf(buf, "%.2f %.3lf", m_intensityFinal * 100.0, m_timeOfMove);

				if (m_changing == FALSE)
				{
					m_changing = TRUE;
					m_pDoc->m_isMovement++;
				}

				if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
					&& m_pDoc->m_currentCommand != NULL)
				{
					m_timeStart = m_pDoc->m_currentCommand->m_time;
				}
				else
				{
					m_gmTimeStart = m_pDoc->m_gmTime;
				}
				sprintf(t, "< %s %s %s", m_name, command, buf);
				sprintf(buf, "%s", t);
				return TRUE;
			}
		}
		else
		{
			sprintf(buf, "X");
		}
	}
	else
	{
		sprintf(buf, "X");
	}
	
	if (buf[0] == 'X')
	{
		return FALSE;
	}
	else
	{
		sprintf(t, "| %s %s %s", m_name, command, buf);
		sprintf(buf, "%s", t);
	}

	return TRUE;
}


BOOL CStageCamera::YoReadCamera(FILE *fp, CStageCamera *ptrCamera)

{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	
	sprintf(partAttachName, "");
  
	while (!done)
	{
		// Read in single line from file
		//ar.ReadString(s, 128);
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "CAMERA_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrCamera, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "CAMERA_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrCamera->m_name);
		}
		else if (strcmp(command, "CAMERA_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrCamera->m_parent, &partAttachName);
			ptrPart = m_pDoc->YoPartLookup(ptrCamera, partAttachName);
		}
		else if (strcmp(command, "CAMERA_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrCamera->m_visible);
		}
		else if (strcmp(command, "CAMERA_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrCamera->m_mass);
		}
		else if (strcmp(command, "CAMERA_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrCamera->m_barCode);
		}
		else if (strcmp(command, "CAMERA_FIELD_OF_VIEW") == 0)
		{
			sscanf(s, "%*s %lf", &ptrCamera->m_fieldOfView);
		}
		else if (strcmp(command, "CAMERA_F_STOP") == 0)
		{
			sscanf(s, "%*s %lf", &ptrCamera->m_fStop);
		}
		else if (strcmp(command, "CAMERA_CLIPPING_PLANES") == 0)
		{
			sscanf(s, "%*s %lf %lf",
				&ptrCamera->m_clipFront, &ptrCamera->m_clipRear);
		}
		else
		{
			return FALSE;
		}
		
	} // end while (!done)
	return TRUE;
}


BOOL CStageCamera::YoPositionCamera()
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	double m[16];
	double n[16];
	CStageDevice *currentDevice;
	CStagePart *currentPart;
	CPoint pt;

	currentDevice = m_pDoc->m_currentDevice;
	currentPart = m_pDoc->m_currentPart;

	m_pDoc->m_currentDevice = this;
	m_pDoc->m_currentPart = m_ptrPart;
	m_pDoc->YoModelMatrixOfCurrentPart(m);

	::glMatrixMode(GL_MODELVIEW);	
	::glLoadIdentity();
	::glMultMatrixd(m);
	::glTranslated(0.0, 0.0, 250.0);
	::glGetDoublev(GL_MODELVIEW_MATRIX, m);
	::glTranslated(0.0, 0.0, 1000.0);
	::glGetDoublev(GL_MODELVIEW_MATRIX, n);

	::glLoadIdentity();
	::gluLookAt(m[12], m[13], m[14],
		n[12], n[13], n[14],
		n[4], n[5], n[6]);

	m_pDoc->m_currentDevice = currentDevice;
	m_pDoc->m_currentPart = currentPart;

	return TRUE;
}


BOOL CStageCamera::YoHandleCommand(char *buf)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	char command[32];
	double val;
	int i;

	i = sscanf(buf, "%s %lf", command, &val);

	if (i == 0)
	{
		if (m_enabled)
		{
			sprintf(buf, "| %s ENABLED %.1lf %.1lf %.1lf",
				m_name, m_fieldOfView, m_clipFront, m_clipRear);
		}
		else
		{
			sprintf(buf, "| %s DISABLED %.1lf %.1lf %.1lf",
				m_name, m_fieldOfView, m_clipFront, m_clipRear);
		}
	}

	else if (toupper(buf[0]) == 'E' && toupper(buf[1]) == 'N')
	{
		// disable any other camera that might be currently enabled
		if (m_pDoc->m_camera != NULL && m_pDoc->m_camera != this)
		{
			m_pDoc->m_camera->m_enabled = FALSE;
		}

		// enable this camera
		m_enabled = TRUE;
		m_pDoc->m_camera = this;

		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(m_fieldOfView, pView->m_aspectRatio, m_clipFront, m_clipRear);

		sprintf(buf, "| %s ENABLED %.1lf %.1lf %.1lf",
			m_name, m_fieldOfView, m_clipFront, m_clipRear);
	}

	else if (toupper(buf[0]) == 'D')
	{
		m_enabled = FALSE;
		m_pDoc->m_camera = NULL;

		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
			pView->m_clipFront, pView->m_clipRear);
		
		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
			pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
			pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

		sprintf(buf, "| %s DISABLED", m_name);
	}

	else if (toupper(buf[0]) == 'F')
	{
		if (i == 2)
		{
			m_fieldOfView = val;
			m_fieldOfView = YO_MAX(m_fieldOfView, 0.0);
			m_fieldOfView = YO_MIN(m_fieldOfView, 180.0);

			if (m_enabled)
			{
				::glMatrixMode(GL_PROJECTION);
				::glLoadIdentity();
				::gluPerspective(m_fieldOfView, pView->m_aspectRatio, m_clipFront, m_clipRear);
			}
		}

		sprintf(buf, "| %s FIELDOFVIEW %.1lf", m_name, m_fieldOfView);
	}

	else if (toupper(buf[0]) == 'C' && toupper(buf[4]) == 'F')
	{
		if (i == 2)
		{
			m_clipFront = val;
			m_clipFront = YO_MAX(m_clipFront, 0.1);
			m_clipFront = YO_MIN(m_clipFront, m_clipRear);

			if (m_enabled)
			{
				::glMatrixMode(GL_PROJECTION);
				::glLoadIdentity();
				::gluPerspective(m_fieldOfView, pView->m_aspectRatio, m_clipFront, m_clipRear);
			}
		}

		sprintf(buf, "| %s CLIPFRONT %.1lf", m_name, m_clipFront);
	}

	else if (toupper(buf[0]) == 'C' && toupper(buf[4]) == 'R')
	{
		if (i == 2)
		{
			m_clipRear = val;
			m_clipRear = YO_MAX(m_clipFront, m_clipRear);

			if (m_enabled)
			{
				::glMatrixMode(GL_PROJECTION);
				::glLoadIdentity();
				::gluPerspective(m_fieldOfView, pView->m_aspectRatio, m_clipFront, m_clipRear);
			}
		}

		sprintf(buf, "| %s CLIPREAR %.1lf", m_name, m_clipRear);
	}

	else
	{
		sprintf(buf, "X");
	}

	if (buf[0] != 'X' && m_pDoc->m_isMovement == 0)
	{
		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);
	}

	return TRUE;
}

BOOL CStagePart::YoReadPart(FILE *fp, CStagePart *ptrPart)

{
	class CStageDevice	*ptrDevice;
	class CStageDevice  *ptrParent;
	char				s[256];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;


	sprintf(ptrPart->m_deviceName, "%s", m_pDoc->m_currentDevice->m_name);
	m_pDoc->m_currentPart = ptrPart;

	while (!done)
	{
		// Read in single line from file
		//ar.ReadString(s, 128);
		memset(s, 0, 256);
		for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "PART_NULL") == 0)
		{
			ptrDevice = m_pDoc->YoDeviceHashLookup(ptrPart->m_deviceName);
			m_pDoc->YoInsertPart(ptrDevice, ptrPart);

			YoComputeNormals();

			// insert pallet into conveyor object if parent is of type conveyor
			if (ptrDevice->m_type == YO_CONVEYOR_PALLET
				&& ptrPart == ptrDevice->m_ptrPart)
			{
				if (strcmp(ptrDevice->m_parent, "NONE") != 0)
				{
					ptrParent = m_pDoc->YoDeviceHashLookup(ptrDevice->m_parent);
					if (ptrParent != NULL && ptrParent->m_type == YO_CONVEYOR)
					{
						((CStageConveyor *)ptrParent)->YoInsertPallet((CStageConveyorPallet *)ptrDevice);
					}
				}
			}

			done = TRUE;

		}
		/****
		else if (strcmp(command, "PART_TYPE") == 0)
		{
			sscanf(s, "*s %d", &ptrPart->m_displayType);
		}
		****/
		else if (strcmp(command, "PART_DEVICE_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrPart->m_deviceName);
		}
		else if (strcmp(command, "PART_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrPart->m_partName);
		}
		else if (strcmp(command, "PART_PARENT") == 0)
		{
			sscanf(s, "%*s %s", &ptrPart->m_partParent); 
		}
		else if (strcmp(command, "PART_TRANSLATE") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf", &ptrPart->m_translate[0],
				&ptrPart->m_translate[1], &ptrPart->m_translate[2]);
		}
		else if (strcmp(command, "PART_ROTATE") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf", &ptrPart->m_rotate[0],
				&ptrPart->m_rotate[1], &ptrPart->m_rotate[2]);
		}
		else if (strcmp(command, "PART_TXYZ") == 0)
		{
			sscanf(s, "%*s %d", &ptrPart->m_txyz);
		}
		else if (strcmp(command, "PART_SMOOTH_SHADE_ANGLE") == 0)
		{
			sscanf(s, "%*s %f", &ptrPart->m_smoothShadeAngle);
		}
		else if (strcmp(command, "RENDER_MODE") == 0)
		{
			sscanf(s, "%*s %d", &ptrPart->m_renderMode);
		}
		else if (strcmp(command, "MATERIAL_AMBIENT") == 0)
		{
			sscanf(s, "%*s %f %f %f %f",
				&ptrPart->m_ambient[0], &ptrPart->m_ambient[1],
				&ptrPart->m_ambient[2], &ptrPart->m_ambient[3]);
		}
		else if (strcmp(command, "MATERIAL_DIFFUSE") == 0)
		{
			sscanf(s, "%*s %f %f %f %f",
				&ptrPart->m_diffuse[0], &ptrPart->m_diffuse[1],
				&ptrPart->m_diffuse[2], &ptrPart->m_diffuse[3]);
		}
		else if (strcmp(command, "MATERIAL_SPECULAR") == 0)
		{
			sscanf(s, "%*s %f %f %f %f",
				&ptrPart->m_specular[0], &ptrPart->m_specular[1],
				&ptrPart->m_specular[2], &ptrPart->m_specular[3]);
		}
		else if (strcmp(command, "MATERIAL_EMISSION") == 0)
		{
			sscanf(s, "%*s %f %f %f %f",
				&ptrPart->m_emission[0], &ptrPart->m_emission[1],
				&ptrPart->m_emission[2], &ptrPart->m_emission[3]);
		}
		else if (strcmp(command, "MATERIAL_WIREFRAME") == 0)
		{
			sscanf(s, "%*s %f %f %f %f",
				&ptrPart->m_wireframe[0], &ptrPart->m_wireframe[1],
				&ptrPart->m_wireframe[2], &ptrPart->m_wireframe[3]);
		}
		else if (strcmp(command, "MATERIAL_SHININESS") == 0)
		{
			sscanf(s, "%*s %f", &ptrPart->m_shininess);
		}
/***
		else if (strcmp(command, "TEXTURE_SCALE") == 0)
		{
			sscanf(s, "%*s %f", &ptrPart->m_textureScale);
		}
		else if (strcmp(command, "TEXTURE_ALPHA") == 0)
		{
			sscanf(s, "%*s %f", &ptrPart->m_textureAlpha);
		}
		else if (strcmp(command, "TEXTURE_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrPart->m_textureName);
			if ((ptrPart->m_texture
				= m_pDoc->YoTextureHashLookup(ptrPart->m_textureName)) == NULL)
			{
				ptrPart->m_texture = new CStageTexture(m_pDoc);
				ptrPart->m_texture->YoReadImage(ptrPart);
			}
		}
		else if (strcmp(command, "TEXTURE_WRAP") == 0)
		{
			sscanf(s, "%*s %f", &ptrPart->m_textureWrap);
		}
		else if (strcmp(command, "TEXTURE_TEV") == 0)
		{
			sscanf(s, "%*s %d", &ptrPart->m_textureTEV);
		}
		else if (strcmp(command, "TEXTURE_SPARAMETER") == 0)
		{
			sscanf(s, "%*s %f %f %f %f %d",
				&ptrPart->m_sParameter[0],
				&ptrPart->m_sParameter[1],
				&ptrPart->m_sParameter[2],
				&ptrPart->m_sParameter[3],
				&ptrPart->m_sMode);
		}
		else if (strcmp(command, "TEXTURE_TPARAMETER") == 0)
		{
			sscanf(s, "%*s %f %f %f %f %d",
				&ptrPart->m_tParameter[0],
				&ptrPart->m_tParameter[1],
				&ptrPart->m_tParameter[2],
				&ptrPart->m_tParameter[3],
				&ptrPart->m_tMode);
		}
		***/
		else if (strcmp(command, "EFFECT") == 0)
		{
			CStageEffect *ptrEffect;
			ptrEffect = new CStageEffect(m_pDoc);
			if (ptrEffect->YoReadEffect(fp, ptrPart) == FALSE)
			{
				return FALSE;
			}
		}
		else if (strcmp(command, "MOTION") == 0)
		{
			CStageMotion *ptrMotion;
			ptrMotion = new CStageMotion(m_pDoc);
			if (ptrMotion->YoReadMotion(fp, ptrPart) == FALSE)
			{
				return FALSE;
			}
		}
		else if (strcmp(command, "PATH") == 0)
		{
			CStagePath *ptrPath;
			ptrPath = new CStagePath(m_pDoc);
			ptrPath->YoInitPath(ptrPart);
			sscanf(s, "%*s %s", &ptrPart->m_path->m_name);
			m_pDoc->YoPathHashInstall(ptrPath);
			if (ptrPath->YoReadPath(fp, ptrPart) == FALSE)
			{
				return FALSE;
			}
		}
		else if (strcmp(command, "PART_FILE") == 0)
		{
			sscanf(s, "%*s %s", &ptrPart->m_partFile);
			// display list for filled surface
			//::glNewList(ptrPart->m_displayListID, GL_COMPILE);
			if (YoReadPartFile(ptrPart->m_partFile) == FALSE)
			{
				return FALSE;
			}
			// display list for wireframe
			//::glNewList(ptrPart->m_wireframeDisplayListID, GL_COMPILE);
			//YoReadPartFile(ptrPart->m_partFile, YO_WIREFRAME);
			//YoMakeDisplayList(m_displayListID, m_pDoc->m_renderMode);
			//YoMakeDisplayList(m_wireframeDisplayListID, m_pDoc->m_quickMode);
		}
		else if (strcmp(command, "PART_DATA") == 0)
		{
			if (YoReadPartData(fp) == FALSE)
			{
				return FALSE;
			}
		}

		else if (strcmp(command, "TRACK") == 0)
		{
			CStageTrackSeg *ptrTrackSeg;
			char trackType[16];
			double theta;
			double x;
			double y;

			ptrTrackSeg = new CStageTrackSeg();
			sscanf(s, "%*s %s", trackType);
			ptrTrackSeg->m_ptrFrom = NULL;
			ptrTrackSeg->m_ptrTo = NULL;
			ptrTrackSeg->m_ptrSwitch = NULL;

			if (strcmp(trackType, "LINE") == 0)
			{
				ptrPart->m_ptrTrackSeg = ptrTrackSeg;
				ptrTrackSeg->m_ptrPart = ptrPart;
				ptrTrackSeg->m_type = YO_TRACK_LINE;
				sscanf(s, "%*s %*s %lf %lf %lf %lf",
					&ptrTrackSeg->m_from[0], &ptrTrackSeg->m_from[1],
					&ptrTrackSeg->m_to[0], &ptrTrackSeg->m_to[1]);
				ptrTrackSeg->m_distance
					= sqrt((ptrTrackSeg->m_to[0] - ptrTrackSeg->m_from[0])
					* (ptrTrackSeg->m_to[0] - ptrTrackSeg->m_from[0])
					+ (ptrTrackSeg->m_to[1] - ptrTrackSeg->m_from[1])
					* (ptrTrackSeg->m_to[1] - ptrTrackSeg->m_from[1]));
			}
			else if (strcmp(trackType, "CIRCLE") == 0)
			{
				ptrPart->m_ptrTrackSeg = ptrTrackSeg;
				ptrTrackSeg->m_ptrPart = ptrPart;
				ptrTrackSeg->m_type = YO_TRACK_CIRCLE;
				sscanf(s, "%*s %*s %lf %lf %lf %lf %lf",
					&ptrTrackSeg->m_from[0], &ptrTrackSeg->m_from[1],
					&ptrTrackSeg->m_heading, &ptrTrackSeg->m_radius,
					&ptrTrackSeg->m_angle);
				if (ptrTrackSeg->m_angle >= 0.0)
				{
		  			theta = YO_DEGREES_TO_RADIANS * (ptrTrackSeg->m_heading - 90.0);
				}
				else
				{
		  			theta = YO_DEGREES_TO_RADIANS * (ptrTrackSeg->m_heading + 90.0);
				}
				x = ptrTrackSeg->m_radius * cos(theta);
				y = ptrTrackSeg->m_radius * sin(theta);
				x = ptrTrackSeg->m_from[0] - x;
				y = ptrTrackSeg->m_from[1] - y;
				theta += YO_DEGREES_TO_RADIANS * ptrTrackSeg->m_angle;
				ptrTrackSeg->m_to[0] = ptrTrackSeg->m_radius * cos(theta);
				ptrTrackSeg->m_to[1] = ptrTrackSeg->m_radius * sin(theta);
				ptrTrackSeg->m_to[0] += x;
				ptrTrackSeg->m_to[1] += y;
				ptrTrackSeg->m_distance
					= fabs(ptrTrackSeg->m_angle * YO_DEGREES_TO_RADIANS * ptrTrackSeg->m_radius);
			}
			else if (strcmp(trackType, "SWITCH") == 0)
			{
				ptrPart->m_ptrTrackSeg = ptrTrackSeg;
				ptrTrackSeg->m_ptrPart = ptrPart;
				ptrTrackSeg->m_type = YO_TRACK_SWITCH;
				sscanf(s, "%*s %*s %lf %lf %lf %lf %lf %lf %d",
					&ptrTrackSeg->m_from[0], &ptrTrackSeg->m_from[1],
					&ptrTrackSeg->m_to[0], &ptrTrackSeg->m_to[1],
					&ptrTrackSeg->m_switch[0], &ptrTrackSeg->m_switch[1],
					&ptrTrackSeg->m_switchStatus);
				ptrTrackSeg->m_distance
					= sqrt((ptrTrackSeg->m_to[0] - ptrTrackSeg->m_from[0])
					* (ptrTrackSeg->m_to[0] - ptrTrackSeg->m_from[0])
					+ (ptrTrackSeg->m_to[1] - ptrTrackSeg->m_from[1])
					* (ptrTrackSeg->m_to[1] - ptrTrackSeg->m_from[1]));
				ptrTrackSeg->m_switchDistance
					= sqrt((ptrTrackSeg->m_switch[0] - ptrTrackSeg->m_from[0])
					* (ptrTrackSeg->m_switch[0] - ptrTrackSeg->m_from[0])
					+ (ptrTrackSeg->m_switch[1] - ptrTrackSeg->m_from[1])
					* (ptrTrackSeg->m_switch[1] - ptrTrackSeg->m_from[1]));
			}
			else if (strcmp(trackType, "CROSS") == 0)
			{
				ptrPart->m_ptrTrackSeg = ptrTrackSeg;
				ptrTrackSeg->m_ptrPart = ptrPart;
				ptrTrackSeg->m_type = YO_TRACK_CROSS;
				sscanf(s, "%*s %*s %lf %lf %lf %lf",
					&ptrTrackSeg->m_from[0], &ptrTrackSeg->m_from[1],
					&ptrTrackSeg->m_to[0], &ptrTrackSeg->m_to[1]);
				ptrTrackSeg->m_distance
					= sqrt((ptrTrackSeg->m_to[0] - ptrTrackSeg->m_from[0])
					* (ptrTrackSeg->m_to[0] - ptrTrackSeg->m_from[0])
					+ (ptrTrackSeg->m_to[1] - ptrTrackSeg->m_from[1])
					* (ptrTrackSeg->m_to[1] - ptrTrackSeg->m_from[1]));
			}
			else
			{
				return FALSE;
			}
		}
		else if (strcmp(command, "CONVEYOR_SEGMENT") == 0)
		{
			CStageConveyorSegment *ptrSegment;
			ptrSegment = new CStageConveyorSegment();
			ptrSegment->m_ptrPart = ptrPart;
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf %lf %lf",
				&ptrSegment->m_from[0], &ptrSegment->m_from[1],
				&ptrSegment->m_from[2], &ptrSegment->m_to[0],
				&ptrSegment->m_to[1], &ptrSegment->m_to[2],
				&ptrSegment->m_maxVelocity, &ptrSegment->m_acceleration);
			((CStageConveyor *)m_pDoc->m_currentDevice)->YoInsertSegment(ptrSegment);
		}
		else if (strcmp(command, "CONVEYOR_SENSOR") == 0)
		{
			CStageConveyorSensor *ptrSensor;
			ptrSensor = new CStageConveyorSensor();
			ptrSensor->m_ptrPart = ptrPart;
			sscanf(s, "%*s %lf %lf %lf",
				&ptrSensor->m_position[0], &ptrSensor->m_position[1],
				&ptrSensor->m_position[2]);
			((CStageConveyor *)m_pDoc->m_currentDevice)->YoInsertSensor(ptrSensor);
		}
		else if (strcmp(command, "CONVEYOR_STOP_GATE") == 0)
		{
			CStageConveyorStopGate *ptrStopGate;
			ptrStopGate = new CStageConveyorStopGate();
			ptrStopGate->m_ptrPart = ptrPart;
			sscanf(s, "%*s %lf %lf %lf %d",
				&ptrStopGate->m_position[0], &ptrStopGate->m_position[1],
				&ptrStopGate->m_position[2], &ptrStopGate->m_forward);
			((CStageConveyor *)m_pDoc->m_currentDevice)->YoInsertStopGate(ptrStopGate);
		}
		else if (strcmp(command, "CONVEYOR_TRANSVERSE_LIFT") == 0)
		{
			CStageConveyorTransverseLift *ptrTransverseLift;
			ptrTransverseLift = new CStageConveyorTransverseLift();
			ptrTransverseLift->m_ptrPart = ptrPart;
			sscanf(s, "%*s %lf %lf %lf %d %d %d",
				&ptrTransverseLift->m_position[0], &ptrTransverseLift->m_position[1],
				&ptrTransverseLift->m_position[2],
				&ptrTransverseLift->m_up, &ptrTransverseLift->m_forwardBlocking, &ptrTransverseLift->m_reverseBlocking);
			((CStageConveyor *)m_pDoc->m_currentDevice)->YoInsertTransverseLift(ptrTransverseLift);
		}
		else
		{
			return FALSE;
		}

	} // end while (!done)
	return TRUE;
}


BOOL CStagePart::YoReadDXFFile(char *partFile)
// reads DXF file
// ignores all commands except 3DFACE
{
	char		s[2048];
	char		command[32];
	int			i;
	int			j;
	int			k;
	int			ch = 0;
	FILE		*fp;
	BOOL		done = FALSE;
	BOOL face3D = FALSE;
	int nextCommand = 0;
	GLdouble vertex[4][3];
	int index[4];
	CStageVertexList *ptrVertexList = NULL;
	CStageVertexList *prevVertexList = NULL;
	CStagePolygonList *ptrPolygonList = NULL;
	CStagePolygonList *prevPolygonList = NULL;
	CStageVertices *ptrVertices = NULL;
	CStageVertices *prevVertices = NULL;
	CStageNormals *ptrNormals = NULL;
	CStageNormals *prevNormals = NULL;
	CStageTextureCoords *ptrTextureCoords = NULL;
	CStageTextureCoords *prevTextureCoords = NULL;
#define YO_TEN 10
#define YO_ELEVEN 11
#define YO_TWELVE 12
#define YO_THIRTEEN 13
#define YO_TWENTY 20
#define YO_TWENTYONE 21
#define YO_TWENTYTWO 22
#define YO_TWENTYTHREE 23
#define YO_THIRTY 30
#define YO_THIRTYONE 31
#define YO_THIRTYTWO 32
#define YO_THIRTYTHREE 33
#define YO_TEN_VERTEX 110
#define YO_ELEVEN_VERTEX 111
#define YO_TWELVE_VERTEX 112
#define YO_THIRTEEN_VERTEX 113
#define YO_TWENTY_VERTEX 120
#define YO_TWENTYONE_VERTEX 121
#define YO_TWENTYTWO_VERTEX 122
#define YO_TWENTYTHREE_VERTEX 123
#define YO_THIRTY_VERTEX 130
#define YO_THIRTYONE_VERTEX 131
#define YO_THIRTYTWO_VERTEX 132
#define YO_THIRTYTHREE_VERTEX 133
#define YO_END_3DFACE 1000

	// open DXF file
	if ((fp = fopen(partFile, "r")) == NULL)
	{
		return FALSE;
    }

	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 2048);
		for (i = 0; (i < 2047) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		k = sscanf(s, "%s", command);
		if (k != 1 || strcmp(command, "EOF") == 0)
		{
			fclose(fp);
			if (face3D == TRUE)
			{
				YoComputeNormals();
			}
			return face3D;
		}

		if (strcmp(command, "3DFACE") == 0)
		{
			nextCommand = YO_TEN;
		}
		else if (nextCommand == YO_TEN && strcmp(command, "10") == 0)
		{
			nextCommand = YO_TEN_VERTEX;
		}
		else if (nextCommand == YO_TEN_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[0][0]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_TWENTY;
		}
		else if (nextCommand == YO_TWENTY && strcmp(command, "20") == 0)
		{
			nextCommand = YO_TWENTY_VERTEX;
		}
		else if (nextCommand == YO_TWENTY_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[0][1]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_THIRTY;
		}
		else if (nextCommand == YO_THIRTY && strcmp(command, "30") == 0)
		{
			nextCommand = YO_THIRTY_VERTEX;
		}
		else if (nextCommand == YO_THIRTY_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[0][2]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_ELEVEN;
		}

		else if (nextCommand == YO_ELEVEN && strcmp(command, "11") == 0)
		{
			nextCommand = YO_ELEVEN_VERTEX;
		}
		else if (nextCommand == YO_ELEVEN_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[1][0]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_TWENTYONE;
		}
		else if (nextCommand == YO_TWENTYONE && strcmp(command, "21") == 0)
		{
			nextCommand = YO_TWENTYONE_VERTEX;
		}
		else if (nextCommand == YO_TWENTYONE_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[1][1]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_THIRTYONE;
		}
		else if (nextCommand == YO_THIRTYONE && strcmp(command, "31") == 0)
		{
			nextCommand = YO_THIRTYONE_VERTEX;
		}
		else if (nextCommand == YO_THIRTYONE_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[1][2]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_TWELVE;
		}

		else if (nextCommand == YO_TWELVE && strcmp(command, "12") == 0)
		{
			nextCommand = YO_TWELVE_VERTEX;
		}
		else if (nextCommand == YO_TWELVE_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[2][0]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_TWENTYTWO;
		}
		else if (nextCommand == YO_TWENTYTWO && strcmp(command, "22") == 0)
		{
			nextCommand = YO_TWENTYTWO_VERTEX;
		}
		else if (nextCommand == YO_TWENTYTWO_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[2][1]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_THIRTYTWO;
		}
		else if (nextCommand == YO_THIRTYTWO && strcmp(command, "32") == 0)
		{
			nextCommand = YO_THIRTYTWO_VERTEX;
		}
		else if (nextCommand == YO_THIRTYTWO_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[2][2]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_THIRTEEN;
		}

		else if ((nextCommand == YO_THIRTEEN && strcmp(command, "0") == 0)
			|| (nextCommand == YO_END_3DFACE && strcmp(command, "0") == 0))
			// place vertices in vertex list then assign vertices to a polygon
		{
			for (j = 0; j < 4; j++)
			{
				if (YoGetVertexIndex(vertex[j], &index[j]) == FALSE)
				{
					if (m_numberVertices % 20 == 0)
					{
						ptrVertexList = new CStageVertexList();
						if (prevVertexList == NULL)
						{
							m_vertexList = ptrVertexList;
						}
						else
						{
							prevVertexList->m_next = ptrVertexList;
						}
						prevVertexList = ptrVertexList;
					}
					ptrVertexList->m_vertex[m_numberVertices % 20][0] = vertex[j][0];
					ptrVertexList->m_vertex[m_numberVertices % 20][1] = vertex[j][1];
					ptrVertexList->m_vertex[m_numberVertices % 20][2] = vertex[j][2];
					index[j] = m_numberVertices;
					m_pDoc->YoPartBoundingBox(ptrVertexList->m_vertex[m_numberVertices % 20]);
					m_numberVertices++;
				}
				if (j == 2 && nextCommand == YO_THIRTEEN)
				// polygon with 3 vertices.
				{
					j = 3;
					break;
				}
			}

			if (m_numberPolygons % 10 == 0)
			{
				ptrPolygonList = new CStagePolygonList();
				if (prevPolygonList == NULL)
				{
					m_polygonList = ptrPolygonList;
				}
				else
				{
					prevPolygonList->m_next = ptrPolygonList;
				}
				prevPolygonList = ptrPolygonList;
			}
			ptrPolygonList->m_normals[m_numberPolygons % 10] = NULL;
			ptrPolygonList->m_texture[m_numberPolygons % 10] = NULL;
			ptrPolygonList->m_origTexture[m_numberPolygons % 10] = NULL;
			ptrPolygonList->m_textureModified[m_numberPolygons % 10] = FALSE;
			ptrPolygonList->m_numberSides[m_numberPolygons % 10] = j;
			ptrPolygonList->m_textureStartVertex[m_numberPolygons % 10] = 0;
			ptrPolygonList->m_origTextureStartVertex[m_numberPolygons % 10] = 0;

			prevVertices = NULL;
			prevNormals = NULL;
			// get vertex indices
			for (j = 0; j < ptrPolygonList->m_numberSides[m_numberPolygons % 10]; j++)
			{
				if (j % 4 == 0)
				{
					ptrVertices = new CStageVertices();
					if (prevVertices == NULL)
					{
						ptrPolygonList->m_vertices[m_numberPolygons % 10] = ptrVertices;
					}
					else
					{
						prevVertices->m_next = ptrVertices;
					}
					prevVertices = ptrVertices;

					ptrNormals = new CStageNormals();
					if (prevNormals == NULL)
					{
						ptrPolygonList->m_normals[m_numberPolygons % 10] = ptrNormals;
					}
					else
					{
						prevNormals->m_next = ptrNormals;
					}
					prevNormals = ptrNormals;
				}

				ptrVertices->m_vertex[j % 4] = index[j];
				if (m_vertexList != NULL)
				{
					m_vertexList->YoInsertPolygon(ptrVertices->m_vertex[j % 4], m_numberPolygons);
				}
			}
			m_numberPolygons++;
			face3D = TRUE;
			nextCommand = 0;
		}

		else if (nextCommand == YO_THIRTEEN && strcmp(command, "13") == 0)
		{
			nextCommand = YO_THIRTEEN_VERTEX;
		}
		else if (nextCommand == YO_THIRTEEN_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[3][0]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_TWENTYTHREE;
		}
		else if (nextCommand == YO_TWENTYTHREE && strcmp(command, "23") == 0)
		{
			nextCommand = YO_TWENTYTHREE_VERTEX;
		}
		else if (nextCommand == YO_TWENTYTHREE_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[3][1]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_THIRTYTHREE;
		}
		else if (nextCommand == YO_THIRTYTHREE && strcmp(command, "33") == 0)
		{
			nextCommand = YO_THIRTYTHREE_VERTEX;
		}
		else if (nextCommand == YO_THIRTYTHREE_VERTEX)
		{
			k = sscanf(s, "%lf", &vertex[3][2]);
			if (k != 1)
			{
				fclose(fp);
				if (face3D == TRUE)
				{
					YoComputeNormals();
				}
				return face3D;
			}
			nextCommand = YO_END_3DFACE;
		}


	}
	return face3D;
}


BOOL CStagePart::YoGetVertexIndex(GLdouble vertex[3], int *index)
// searches part's list of vertices for vertex passed in.  If found the index
// is modified and TRUE is returned, else index remains unchanged and FALSE is returned
{
	CStageVertexList *ptrVertexList = NULL;
	int i;

	ptrVertexList = m_vertexList;

	for (i = 0; i < m_numberVertices; i++)
	{
		if (fabs(vertex[0] - ptrVertexList->m_vertex[i % 20][0]) <= 0.01
			&& fabs(vertex[1] - ptrVertexList->m_vertex[i % 20][1]) <= 0.01
			&& fabs(vertex[2] - ptrVertexList->m_vertex[i % 20][2]) <= 0.01)
		{
			*index = i;
			return TRUE;
		}

		if (i % 20 == 19)
		{
			ptrVertexList = ptrVertexList->m_next;
		}
	}

	return FALSE;
}


BOOL CStagePart::YoReadPartFile(char *partFile)

{

	char		s[256];
	char		command[32];
	GLdouble	a[3];
	int			i;
	int			j;
	int			k;
	int			numSides;
	int			ch = 0;
	FILE		*fp;
	BOOL		done = FALSE;
	long		sKnotCount;
	long		tKnotCount;
	long		sOrder;
	long		tOrder;
	GLdouble	sKnots[YO_MAX_KNOTS];
	GLdouble	tKnots[YO_MAX_KNOTS];
	GLdouble	ctrPoint[YO_MAX_ORDER * YO_MAX_ORDER][3];
	BOOL		nurbsDone;
	CStageVertexList *ptrVertexList = NULL;
	CStageVertexList *prevVertexList = NULL;
	CStagePolygonList *ptrPolygonList = NULL;
	CStagePolygonList *prevPolygonList = NULL;
	CStageVertices *ptrVertices = NULL;
	CStageVertices *prevVertices = NULL;
	CStageNormals *ptrNormals = NULL;
	CStageNormals *prevNormals = NULL;
	CStageTextureCoords *ptrTextureCoords = NULL;
	CStageTextureCoords *prevTextureCoords = NULL;

	// first check the file as printed
	if ((fp = fopen(partFile, "r")) == NULL)
	{
		// ask user to find file
		//AfxMessageBox("Can't find part file");
		return FALSE;
    }

	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 256);
		for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		k = sscanf(s, "%s", command);
		if (k != 1)
		{
			fclose(fp);
			if (YoReadDXFFile(partFile) == TRUE)
			{
				return TRUE;
			}
			return FALSE;
		}

		if (strcmp(command, "NULL") == 0)
		{
			fclose(fp);
			YoComputeNormals();
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "VERTEX") == 0)
		{
			if (m_numberVertices % 20 == 0)
			{
				ptrVertexList = new CStageVertexList();
				if (prevVertexList == NULL)
				{
					m_vertexList = ptrVertexList;
				}
				else
				{
					prevVertexList->m_next = ptrVertexList;
				}
				prevVertexList = ptrVertexList;
			}

			k = sscanf(s, "%*s %lf %lf %lf",
				&ptrVertexList->m_vertex[m_numberVertices % 20][0],
				&ptrVertexList->m_vertex[m_numberVertices % 20][1],
				&ptrVertexList->m_vertex[m_numberVertices % 20][2]);
			if (k != 3)
			{
				fclose(fp);
				return FALSE;
			}
			m_pDoc->YoPartBoundingBox(ptrVertexList->m_vertex[m_numberVertices % 20]);
			m_numberVertices++;
		}

		else if (strcmp(command, "POLYGON") == 0)
		{
			if (m_numberPolygons % 10 == 0)
			{
				ptrPolygonList = new CStagePolygonList();
				if (prevPolygonList == NULL)
				{
					m_polygonList = ptrPolygonList;
				}
				else
				{
					prevPolygonList->m_next = ptrPolygonList;
				}
				prevPolygonList = ptrPolygonList;
			}
			ptrPolygonList->m_normals[m_numberPolygons % 10] = NULL;
			ptrPolygonList->m_texture[m_numberPolygons % 10] = NULL;
			ptrPolygonList->m_origTexture[m_numberPolygons % 10] = NULL;
			ptrPolygonList->m_textureModified[m_numberPolygons % 10] = FALSE;
			ptrPolygonList->m_textureStartVertex[m_numberPolygons % 10] = 0;
			ptrPolygonList->m_origTextureStartVertex[m_numberPolygons % 10] = 0;

			k = sscanf(s, "%*s %d", &ptrPolygonList->m_numberSides[m_numberPolygons % 10]);
			if (k != 1)
			{
				fclose(fp);
				return FALSE;
			}
			prevVertices = NULL;
			prevNormals = NULL;
			// read vertex indices
			for (j = 0; j < ptrPolygonList->m_numberSides[m_numberPolygons % 10]; j++)
			{
				memset(s, 0, 256);
				for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
					&& (ch != '\n'); i++)
				{
					s[i] = (char)ch;
				}
				if (s[i] != EOF)
				{
					s[i] = '\0';
				}

				if (j % 4 == 0)
				{
					ptrVertices = new CStageVertices();
					if (prevVertices == NULL)
					{
						ptrPolygonList->m_vertices[m_numberPolygons % 10] = ptrVertices;
					}
					else
					{
						prevVertices->m_next = ptrVertices;
					}
					prevVertices = ptrVertices;

					ptrNormals = new CStageNormals();
					if (prevNormals == NULL)
					{
						ptrPolygonList->m_normals[m_numberPolygons % 10] = ptrNormals;
					}
					else
					{
						prevNormals->m_next = ptrNormals;
					}
					prevNormals = ptrNormals;
				}

				k = sscanf(s, "%d", &ptrVertices->m_vertex[j % 4]);
				if (k != 1 || ptrVertices->m_vertex[j % 4] < 0
					|| ptrVertices->m_vertex[j % 4] >= m_numberVertices)
				{
					fclose(fp);
					return FALSE;
				}
				else if (m_vertexList != NULL)
				{
					m_vertexList->YoInsertPolygon(ptrVertices->m_vertex[j % 4], m_numberPolygons);
				}
			}
			m_numberPolygons++;
		}

		else if (strcmp(command, "TEXTURE") == 0)
		{
			ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]
				= new CStageTexture();
			k = sscanf(s, "%*s %d",
				&ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_textureMode);
			if (k != 1)
			{
				fclose(fp);
				return FALSE;
			}

			ptrPolygonList->m_textureStartVertex[(m_numberPolygons - 1) % 10] = 0;
			// ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->YoInitFromDIB();
			prevTextureCoords = NULL;
			for (j = 0; j < ptrPolygonList->m_numberSides[(m_numberPolygons - 1) % 10]; j++)
			{
				memset(s, 0, 256);
				for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
					&& (ch != '\n'); i++)
				{
					s[i] = (char)ch;
				}
				if (s[i] != EOF)
				{
					s[i] = '\0';
				}

				if (j % 4 == 0)
				{
					ptrTextureCoords = new CStageTextureCoords();
					if (prevTextureCoords == NULL)
					{
						ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_textureCoords = ptrTextureCoords;
					}
					else
					{
						prevTextureCoords->m_next = ptrTextureCoords;
					}
					prevTextureCoords = ptrTextureCoords;
				}

				k = sscanf(s, "%lf %lf", &ptrTextureCoords->m_textureCoords[j % 4][0],
					&ptrTextureCoords->m_textureCoords[j % 4][1]);
				if (k != 2)
				{
					fclose(fp);
					return FALSE;
				}
			}
		}

		else if (strcmp(command, "TEXTURE_FILE") == 0)
		{
			k = sscanf(s, "%*s %s",
				&ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_DIBFileName);
			if (k != 1)
			{
				fclose(fp);
				return FALSE;
			}
		}

		else if (strcmp(command, "TEXTURE_WIDTH_HEIGHT") == 0)
		{
			ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_RGBImage
				= new CGLImage();
			k = sscanf(s, "%*s %d %d",
				&ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_RGBImage->m_iWidth,
				&ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_RGBImage->m_iHeight);
			if (k != 2)
			{
				fclose(fp);
				return FALSE;
			}
			ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_RGBImage->CreateFromStageFile(fp);
		}

		// Quad strips not yet implemented
		else if (strcmp(command, "QSTRIP") == 0)
		{
			// read # of sides
			memset(s, 0, 256);
			for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
				&& (ch != '\n'); i++)
			{
				s[i] = (char)ch;
			}
			if (s[i] != EOF)
			{
				s[i] = '\0';
			}
			k = sscanf(s, "%d", &numSides);
			if (k != 1)
			{
				fclose(fp);
				return FALSE;
			}
			glBegin(GL_QUAD_STRIP);
			for (j = 0; j < numSides; j++)
			{
				// read vertex
				memset(s, 0, 256);
				for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
					&& (ch != '\n'); i++)
				{
					s[i] = (char)ch;
				}
				if (s[i] != EOF)
				{
					s[i] = '\0';
				}
				k = sscanf(s, "%lf %lf %lf", &a[0], &a[1], &a[2]);
				if (k != 3)
				{
					fclose(fp);
					return FALSE;
				}
				glVertex3dv(a);
				m_pDoc->YoPartBoundingBox(a);
			}
			glEnd();
		}

		//nurbs not yet implemented
		else if (strcmp(command, "NURBS") == 0)
		{
			nurbsDone = FALSE;
			while (!nurbsDone)
			{
				memset(s, 0, 256);
				for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
					&& (ch != '\n'); i++)
				{
					s[i] = (char)ch;
				}
				if (s[i] != EOF)
				{
					s[i] = '\0';
				}
				k = sscanf(s, "%s", command);
				if (k != 1)
				{
					fclose(fp);
					return FALSE;
				}
				if (strcmp(command, "S_KNOT_COUNT") == 0)
				{
					k = sscanf(s, "%*s %ld", &sKnotCount);
					if (k != 1)
					{
						fclose(fp);
						return FALSE;
					}
					for (i = 0; i < (int)sKnotCount; i++)
					{
						k = fscanf(fp, "%lf", &sKnots[i]);
						if (k != 1)
						{
							fclose(fp);
							return FALSE;
						}
					}
				}
				else if (strcmp(command, "T_KNOT_COUNT") == 0)
				{
					k = sscanf(s, "%*s %ld", &tKnotCount);
					if (k != 1)
					{
						fclose(fp);
						return FALSE;
					}
					for (i = 0; i < (int)tKnotCount; i++)
					{
						k = fscanf(fp, "%lf", &tKnots[i]);
						if (k != 1)
						{
							fclose(fp);
							return FALSE;
						}
					}
				}
	
				else if (strcmp(command, "S_ORDER") == 0)
				{
					k = sscanf(s, "%*s %ld", &sOrder);
					if (k != 1)
					{
						fclose(fp);
						return FALSE;
					}
				}
				else if (strcmp(command, "T_ORDER") == 0)
				{
					k = sscanf(s, "%*s %ld", &tOrder);
					if (k != 1)
					{
						fclose(fp);
						return FALSE;
					}
				}
				else if (strcmp(command, "CONTROL_POINTS") == 0)
				{
					for (i = 0; i < sOrder * tOrder; i++)
					{
						k = fscanf(fp, "%lf", &ctrPoint[i][0]);
						if (k != 1)
						{
							fclose(fp);
							return FALSE;
						}
						k= fscanf(fp, "%lf", &ctrPoint[i][1]);
						if (k != 1)
						{
							fclose(fp);
							return FALSE;
						}
						k = fscanf(fp, "%lf", &ctrPoint[i][2]);
						if (k != 1)
						{
							fclose(fp);
							return FALSE;
						}
						a[0] = ctrPoint[i][0];
						a[1] = ctrPoint[i][1];
						a[2] = ctrPoint[i][2];
						m_pDoc->YoPartBoundingBox(a);
					}
				}
				else if (strcmp(command, "NURBS_DONE") == 0)
				{
					GLUnurbsObj *nurbsObject;
					nurbsDone = TRUE;
					//gluNewNurbsRenderer(nurbsObject);
					/* OGLXXX replace obj with your GLUnurbsObj* */
					gluBeginSurface(nurbsObject);
					/***
					nurbssurface (
						sKnotCount, sKnots,
						tKnotCount, tKnots,
						3 * sizeof(GLdouble),
						3 * sOrder * sizeof(GLdouble),
						&ctrPoint[0][0],
						sOrder, tOrder,
						N_V3D
					);
					**/
					/* OGLXXX replace obj with your GLUnurbsObj* */
					gluEndSurface(nurbsObject);
				}
				else
				{
					return FALSE;
				}	
			} // end while (!nurbsDone)
		}

		else
		{
			fclose(fp);
			if (YoReadDXFFile(partFile) == TRUE)
			{
				return TRUE;
			}
			return FALSE;
		}

	} // end while (!done)
	return TRUE;
}


BOOL CStagePart::YoReadPartData(FILE *fp)

{

	char		s[256];
	char		command[32];
	int			i;
	int			j;
	int			k;
	int			ch = 0;
	BOOL		done = FALSE;
	CStageVertexList *ptrVertexList = NULL;
	CStageVertexList *prevVertexList = NULL;
	CStagePolygonList *ptrPolygonList = NULL;
	CStagePolygonList *prevPolygonList = NULL;
	CStageVertices *ptrVertices = NULL;
	CStageVertices *prevVertices = NULL;
	CStageNormals *ptrNormals = NULL;
	CStageNormals *prevNormals = NULL;
	CStageTextureCoords *ptrTextureCoords = NULL;
	CStageTextureCoords *prevTextureCoords = NULL;


	while (!done)
	{
		// Read in single line from file
		//ar.ReadString(s, 128);

		// Read in single line from file
		memset(s, 0, 256);
		for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		k = sscanf(s, "%s", command);
		if (k != 1)
		{
			return FALSE;
		}

		if (strcmp(command, "PART_DATA_NULL") == 0)
		{
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "VERTEX") == 0)
		{
			if (m_numberVertices % 20 == 0)
			{
				ptrVertexList = new CStageVertexList();
				if (prevVertexList == NULL)
				{
					m_vertexList = ptrVertexList;
				}
				else
				{
					prevVertexList->m_next = ptrVertexList;
				}
				prevVertexList = ptrVertexList;
			}

			k = sscanf(s, "%*s %lf %lf %lf",
				&ptrVertexList->m_vertex[m_numberVertices % 20][0],
				&ptrVertexList->m_vertex[m_numberVertices % 20][1],
				&ptrVertexList->m_vertex[m_numberVertices % 20][2]);
			if (k != 3)
			{
				return FALSE;
			}
			m_pDoc->YoPartBoundingBox(ptrVertexList->m_vertex[m_numberVertices % 20]);
			m_numberVertices++;
		}

		else if (strcmp(command, "POLYGON") == 0)
		{
			if (m_numberPolygons % 10 == 0)
			{
				ptrPolygonList = new CStagePolygonList();
				if (prevPolygonList == NULL)
				{
					m_polygonList = ptrPolygonList;
				}
				else
				{
					prevPolygonList->m_next = ptrPolygonList;
				}
				prevPolygonList = ptrPolygonList;
			}
			ptrPolygonList->m_normals[m_numberPolygons % 10] = NULL;
			ptrPolygonList->m_texture[m_numberPolygons % 10] = NULL;
			ptrPolygonList->m_origTexture[m_numberPolygons % 10] = NULL;
			ptrPolygonList->m_textureModified[m_numberPolygons % 10] = NULL;
			ptrPolygonList->m_textureStartVertex[m_numberPolygons % 10] = 0;
			ptrPolygonList->m_origTextureStartVertex[m_numberPolygons % 10] = 0;

			k = sscanf(s, "%*s %d", &ptrPolygonList->m_numberSides[m_numberPolygons % 10]);
			if (k != 1)
			{
				return FALSE;
			}
			prevVertices = NULL;
			prevNormals = NULL;
			// read vertex indices
			for (j = 0; j < ptrPolygonList->m_numberSides[m_numberPolygons % 10]; j++)
			{
				//ar.ReadString(s, 128);
				// Read in single line from file
				memset(s, 0, 256);
				for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
					&& (ch != '\n'); i++)
				{
					s[i] = (char)ch;
				}
				if (s[i] != EOF)
				{
					s[i] = '\0';
				}
				if (j % 4 == 0)
				{
					ptrVertices = new CStageVertices();
					if (prevVertices == NULL)
					{
						ptrPolygonList->m_vertices[m_numberPolygons % 10] = ptrVertices;
					}
					else
					{
						prevVertices->m_next = ptrVertices;
					}
					prevVertices = ptrVertices;

					ptrNormals = new CStageNormals();
					if (prevNormals == NULL)
					{
						ptrPolygonList->m_normals[m_numberPolygons % 10] = ptrNormals;
					}
					else
					{
						prevNormals->m_next = ptrNormals;
					}
					prevNormals = ptrNormals;
				}

				k = sscanf(s, "%d", &ptrVertices->m_vertex[j % 4]);
				if (k != 1 || ptrVertices->m_vertex[j % 4] < 0
					|| ptrVertices->m_vertex[j % 4] >= m_numberVertices)
				{
					return FALSE;
				}
				else if (m_vertexList != NULL)
				{
					m_vertexList->YoInsertPolygon(ptrVertices->m_vertex[j % 4], m_numberPolygons);
				}
			}
			m_numberPolygons++;
		}

		else if (strcmp(command, "TEXTURE") == 0)
		{
			ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]
				= new CStageTexture();
			k = sscanf(s, "%*s %d",
				&ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_textureMode);
				//&ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_DIBFileName);
			if (k != 1)
			{
				return FALSE;
			}

			ptrPolygonList->m_textureStartVertex[(m_numberPolygons - 1) % 10] = 0;
			// ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->YoInitFromDIB();
			prevTextureCoords = NULL;
			for (j = 0; j < ptrPolygonList->m_numberSides[(m_numberPolygons - 1) % 10]; j++)
			{
				//ar.ReadString(s, 128);

				// Read in single line from file
				memset(s, 0, 256);
				for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
					&& (ch != '\n'); i++)
				{
					s[i] = (char)ch;
				}
				if (s[i] != EOF)
				{
					s[i] = '\0';
				}
				if (j % 4 == 0)
				{
					ptrTextureCoords = new CStageTextureCoords();
					if (prevTextureCoords == NULL)
					{
						ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_textureCoords = ptrTextureCoords;
					}
					else
					{
						prevTextureCoords->m_next = ptrTextureCoords;
					}
					prevTextureCoords = ptrTextureCoords;
				}

				k = sscanf(s, "%lf %lf", &ptrTextureCoords->m_textureCoords[j % 4][0],
					&ptrTextureCoords->m_textureCoords[j % 4][1]);
				if (k != 2)
				{
					return FALSE;
				}
			}
		}

		else if (strcmp(command, "TEXTURE_FILE") == 0)
		{
			k = sscanf(s, "%*s %s",
				&ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_DIBFileName);
			if (k != 1)
			{
				return FALSE;
			}
		}

		else if (strcmp(command, "TEXTURE_WIDTH_HEIGHT") == 0)
		{
			ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_RGBImage
				= new CGLImage();
			k = sscanf(s, "%*s %d %d",
				&ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_RGBImage->m_iWidth,
				&ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_RGBImage->m_iHeight);
			if (k != 2)
			{
				return FALSE;
			}
			ptrPolygonList->m_texture[(m_numberPolygons - 1) % 10]->m_RGBImage->CreateFromStageFile(fp);
		}

		else
		{
			return FALSE;
		}
	
} // end while (!done)
	return TRUE;
}

BOOL CStagePart::YoWritePartFile(FILE *fp)

{

	int			i;
	int			j;
	int			k;
	CStageVertexList *ptrVertexList = NULL;
	CStagePolygonList *ptrPolygonList = NULL;
	CStageVertices *ptrVertices = NULL;
	CStageTextureCoords *ptrTextureCoords = NULL;

	typedef struct _CGLRGBTRIPLE { 
    BYTE rgbRed;
    BYTE rgbGreen;
  	BYTE rgbBlue;
	} CGLRGBTRIPLE;
	CGLRGBTRIPLE *pRGB;

	fprintf(fp, "PART_DATA\n");

	ptrVertexList = m_vertexList;
	for (i = 0; i < m_numberVertices; i++)
	{
		fprintf(fp, "VERTEX %lf %lf %lf\n",
			ptrVertexList->m_vertex[i % 20][0],
			ptrVertexList->m_vertex[i % 20][1],
			ptrVertexList->m_vertex[i % 20][2]);

		if (i % 20 == 19)
		{
			ptrVertexList = ptrVertexList->m_next;
		}
	}

	ptrPolygonList = m_polygonList;
	for (i = 0; i < m_numberPolygons; i++)
	{
		fprintf(fp, "POLYGON %d\n", ptrPolygonList->m_numberSides[i % 10]);

		ptrVertices = ptrPolygonList->m_vertices[i % 10];
		for (j = 0; j < ptrPolygonList->m_numberSides[i % 10]; j++)
		{
			fprintf(fp, "%d\n", ptrVertices->m_vertex[j % 4]);
			if (j % 4 == 3)
			{
				ptrVertices = ptrVertices->m_next;
			}
		}

		if (ptrPolygonList->m_texture[i % 10] != NULL)
		{
			fprintf(fp, "TEXTURE %d\n",
				ptrPolygonList->m_texture[i % 10]->m_textureMode);
			ptrTextureCoords = ptrPolygonList->m_texture[i % 10]->m_textureCoords;
			for (j = 0; j < ptrPolygonList->m_numberSides[i % 10]; j++)
			{
				fprintf(fp, "%lf %lf\n",
					ptrTextureCoords->m_textureCoords[j % 4][0],
					ptrTextureCoords->m_textureCoords[j % 4][1]);
				if (j % 4 == 3)
				{
					ptrTextureCoords = ptrTextureCoords->m_next;
				}
			}
			k = ptrPolygonList->m_texture[i % 10]->m_RGBImage->m_iWidth
				* ptrPolygonList->m_texture[i % 10]->m_RGBImage->m_iHeight;
			fprintf(fp, "TEXTURE_WIDTH_HEIGHT %d %d\n",
				ptrPolygonList->m_texture[i % 10]->m_RGBImage->m_iWidth,
				ptrPolygonList->m_texture[i % 10]->m_RGBImage->m_iHeight);
			pRGB = (CGLRGBTRIPLE*) ptrPolygonList->m_texture[i % 10]->m_RGBImage->m_pBits;
			for (j = 0 ; j < k; j++)
			{
				fprintf(fp, "%02x%02x%02x ", pRGB->rgbRed, pRGB->rgbGreen, pRGB->rgbBlue);
				pRGB++;

				if (j % 8 == 7 && j < k - 1)
				{
					fprintf(fp, "\n");
				}
			}
			fprintf(fp, "\n");
		}
		if (i % 10 == 9)
		{
			ptrPolygonList = ptrPolygonList->m_next;
		}
	}

	fprintf(fp, "PART_DATA_NULL\n");
	return TRUE;

}

BOOL CStagePart::YoComputeNormals(void)
// assigns normal to the vertex of each polygon in m_polygonList
// for smooth shading purposes based on value of m_smoothShadeAngle.
{
	int i;
	int j;
	int k;
	int index;
	int numPolygons;
	GLdouble a[3];
	GLdouble b[3];
	GLdouble c[3];
	GLdouble u[3];
	GLdouble v[3];
	GLdouble normal[3];
	CStagePolygonList *ptrPolygonList;
	CStagePolygonList *nPolygonList;
	CStagePolygon *ptrPolygon;
	CStageVertices *ptrVertices;
	CStageNormals *ptrNormals;
	CStageVertexList *ptrVertexList;

	// calculate normals for flat shading
	ptrPolygonList = m_polygonList;
	for (j = 0; j < m_numberPolygons; j++)
	{
		ptrVertices = ptrPolygonList->m_vertices[j % 10];
		for (i = 0; i < 3; i++)
		{
			index = ptrVertices->m_vertex[i];
			// lookup vertex
			for (ptrVertexList = m_vertexList; index >= 20; ptrVertexList = ptrVertexList->m_next)
			{
				index -= 20;
			}

			// first three points define normal
			if (i == 0)
			{
				a[0] = ptrVertexList->m_vertex[index][0];
				a[1] = ptrVertexList->m_vertex[index][1];
				a[2] = ptrVertexList->m_vertex[index][2];
				u[0] = a[0];
				u[1] = a[1];
				u[2] = a[2];
			}
			else if (i == 1)
			{
				b[0] = ptrVertexList->m_vertex[index][0];
				b[1] = ptrVertexList->m_vertex[index][1];
				b[2] = ptrVertexList->m_vertex[index][2];
				u[0] -= b[0];
				u[1] -= b[1];
				u[2] -= b[2];
				v[0] = b[0];
				v[1] = b[1];
				v[2] = b[2];
			}
			else if (i == 2)
			{
				c[0] = ptrVertexList->m_vertex[index][0];
				c[1] = ptrVertexList->m_vertex[index][1];
				c[2] = ptrVertexList->m_vertex[index][2];
				v[0] = c[0] - v[0];
				v[1] = c[1] - v[1];
				v[2] = c[2] - v[2];
				m_pDoc->YoCrossProduct(ptrPolygonList->m_normalFlatShaded[j % 10], v, u);
				m_pDoc->YoNormalize(ptrPolygonList->m_normalFlatShaded[j % 10]);
				//m_pDoc->YoCrossProduct(normal, v, u);
				//m_pDoc->YoNormalize(normal);
			}
		}

		if (j % 10 == 9)
		{
			ptrPolygonList = ptrPolygonList->m_next;
		}

	}

	// calculate normals for smooth shading
	m_smoothShadeAngle = YO_MIN(m_smoothShadeAngle, 125.0f);
	m_smoothShadeAngle = YO_MAX(m_smoothShadeAngle, 0.0f);
	ptrPolygonList = m_polygonList;
	for (j = 0; j < m_numberPolygons; j++)
	{
		ptrVertices = ptrPolygonList->m_vertices[j % 10];
		ptrNormals = ptrPolygonList->m_normals[j % 10];

		for (i = 0; i < ptrPolygonList->m_numberSides[j % 10]; i++)
		{
			index = ptrVertices->m_vertex[i % 4];
			// lookup vertex
			for (ptrVertexList = m_vertexList; index >= 20; ptrVertexList = ptrVertexList->m_next)
			{
				index -= 20;
			}

			numPolygons = 1;
			normal[0] = ptrPolygonList->m_normalFlatShaded[j % 10][0];
			normal[1] = ptrPolygonList->m_normalFlatShaded[j % 10][1];
			normal[2] = ptrPolygonList->m_normalFlatShaded[j % 10][2];
			for (ptrPolygon = ptrVertexList->m_polygon[index]; ptrPolygon != NULL; ptrPolygon = ptrPolygon->m_next)
			{
				if (ptrPolygon->m_polygon != j)
				{
					k = ptrPolygon->m_polygon;
					// lookup polygon
					for (nPolygonList = m_polygonList; k >= 10; nPolygonList = nPolygonList->m_next)
					{
						k -= 10;
					}
					// vectors are normalized
					if (acos(ptrPolygonList->m_normalFlatShaded[j % 10][0] * nPolygonList->m_normalFlatShaded[k % 10][0]
						+ ptrPolygonList->m_normalFlatShaded[j % 10][1] * nPolygonList->m_normalFlatShaded[k % 10][1]
						+ ptrPolygonList->m_normalFlatShaded[j % 10][2] * nPolygonList->m_normalFlatShaded[k % 10][2])
						* YO_RADIANS_TO_DEGREES <= m_smoothShadeAngle)
					{
						normal[0] = normal[0] * numPolygons + nPolygonList->m_normalFlatShaded[k % 10][0];
						normal[1] = normal[1] * numPolygons + nPolygonList->m_normalFlatShaded[k % 10][1];
						normal[2] = normal[2] * numPolygons + nPolygonList->m_normalFlatShaded[k % 10][2];
						m_pDoc->YoNormalize(normal);
						numPolygons++;
					}
				}
			}
			ptrNormals->m_normal[i % 4][0] = normal[0];
			ptrNormals->m_normal[i % 4][1] = normal[1];
			ptrNormals->m_normal[i % 4][2] = normal[2];

			if (i % 4 == 3)
			{
				ptrVertices = ptrVertices->m_next;
				ptrNormals = ptrNormals->m_next;
			}
		}

		if (j % 10 == 9)
		{
			ptrPolygonList = ptrPolygonList->m_next;
		}
	}
	return TRUE;
}



CStagePart::~CStagePart()
{
	CStagePolygonList *currentPolygonList;
	CStagePolygonList *ptrPolygonList;
	CStagePolygon *currentPolygon;
	CStagePolygon *ptrPolygon;
	CStageVertexList *currentVertexList;
	CStageVertexList *ptrVertexList;
	CStageVertices *currentVertices;
	CStageVertices *ptrVertices;
	CStageNormals *currentNormals;
	CStageNormals *ptrNormals;
	//CStageTexture *currentTexture;
	//CStageTexture *ptrTexture;
	CStageTextureCoords *currentTextureCoords;
	CStageTextureCoords *ptrTextureCoords;
	CStageMotion *currentMotion;
	CStageMotion *ptrMotion;
	CStageEffect *currentEffect;
	CStageEffect *ptrEffect;
	CStageScore *currentScore;
	CStageScore *ptrScore;
	CStagePath *currentPath;
	CStagePath *ptrPath;
	CStageTag *currentTag;
	CStageTag *ptrTag;
	CStagePart *prevPart = NULL;
	CStagePart *currentPart;
	int i;

	currentEffect = m_effect;
	while (currentEffect != NULL)
	{
		ptrEffect = currentEffect;
		currentEffect = currentEffect->m_next;
		delete(ptrEffect);
	}

	currentMotion = m_motion;
	while (currentMotion != NULL)
	{
		ptrMotion = currentMotion;
		currentMotion = currentMotion->m_next;
		delete(ptrMotion);
	}

	currentScore = m_score;
	while (currentScore != NULL)
	{
		ptrScore = currentScore;
		currentScore = currentScore->m_next;
		delete(ptrScore);
	}

	currentPath = m_path;
	while (currentPath != NULL)
	{
		currentTag = currentPath->m_ptrTag;
		while (currentTag != NULL)
		{
			ptrTag = currentTag;
			currentTag = currentTag->m_nextTag;
			delete (ptrTag);
		}
		ptrPath = currentPath;
		currentPath = currentPath->m_nextPath;
		delete (ptrPath);
	}

	if (m_ptrTrackSeg != NULL)
	{
		delete (m_ptrTrackSeg);
		m_ptrTrackSeg = NULL;
	}

	// remove part from m_pDoc->m_pickPart table and relink list
	if (m_displayListID != -1)
	// m_displayListID set to -1 during undo part update
	{
		for (currentPart = m_pDoc->m_pickPart[m_displayListID % YO_HASH_SIZE];
			currentPart != this;)
		{
			prevPart = currentPart;
			currentPart = currentPart->m_pick;
		}
		
		if (prevPart == NULL)
		{
			m_pDoc->m_pickPart[m_displayListID % YO_HASH_SIZE] = m_pick;
		}
		else
		{
			prevPart->m_pick = m_pick;
		}
	}


	for (currentVertexList = m_vertexList; currentVertexList != NULL;)
	{
		for (i = 0; i < 20; i++)
		{
			for (currentPolygon = currentVertexList->m_polygon[i]; currentPolygon != NULL;)
			{
				ptrPolygon = currentPolygon;
				currentPolygon = currentPolygon->m_next;
				delete(ptrPolygon);	
			}
		}

		ptrVertexList = currentVertexList;
		currentVertexList = currentVertexList->m_next;
		delete(ptrVertexList);
	}

	currentPolygonList = m_polygonList;
	for (i = 0; i < m_numberPolygons; i++)
	{
		for (currentVertices = currentPolygonList->m_vertices[i % 10]; currentVertices != NULL;)
		{
			ptrVertices = currentVertices;
			currentVertices = currentVertices->m_next;
			delete(ptrVertices);
		}

		for (currentNormals = currentPolygonList->m_normals[i % 10]; currentNormals != NULL;)
		{
			ptrNormals = currentNormals;
			currentNormals = currentNormals->m_next;
			delete(ptrNormals);
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
		if (i % 10 == 9 && i != m_numberPolygons - 1)
		{
			ptrPolygonList = currentPolygonList;
			currentPolygonList = currentPolygonList->m_next;
			delete(ptrPolygonList);
		}
	}

	delete(currentPolygonList);

	return;
}

BOOL CStagePart::YoInitPart(CStagePart *ptrPart)
{
	//ptrPart->m_displayType = GL_POLYGON;
	ptrPart->m_displayListID = 0;
	ptrPart->m_wireframeDisplayListID = 0;
	ptrPart->m_vertexList = NULL;
	ptrPart->m_numberPolygons = 0;
	ptrPart->m_numberVertices = 0;
	ptrPart->m_polygonList = NULL;
	sprintf(ptrPart->m_partParent, "NONE");
	ptrPart->m_originVisible = FALSE;
	ptrPart->m_altOriginDisplayed = FALSE;
	ptrPart->m_altOrigin[0] = 1.0;
	ptrPart->m_altOrigin[1] = 0.0;
	ptrPart->m_altOrigin[2] = 0.0;
	ptrPart->m_altOrigin[3] = 0.0;
	ptrPart->m_altOrigin[4] = 0.0;
	ptrPart->m_altOrigin[5] = 1.0;
	ptrPart->m_altOrigin[6] = 0.0;
	ptrPart->m_altOrigin[7] = 0.0;
	ptrPart->m_altOrigin[8] = 0.0;
	ptrPart->m_altOrigin[9] = 0.0;
	ptrPart->m_altOrigin[10] = 1.0;
	ptrPart->m_altOrigin[11] = 0.0;
	ptrPart->m_altOrigin[12] = 0.0;
	ptrPart->m_altOrigin[13] = 0.0;
	ptrPart->m_altOrigin[14] = 0.0;
	ptrPart->m_altOrigin[15] = 1.0;
	ptrPart->m_translate[0] = 0.0;
	ptrPart->m_translate[1] = 0.0;
	ptrPart->m_translate[2] = 0.0;
	ptrPart->m_rotate[0] = 0.0;
	ptrPart->m_rotate[1] = 0.0;
	ptrPart->m_rotate[2] = 0.0;
	ptrPart->m_txyz = YO_TXYZ_TXYZ;
	ptrPart->m_min[0] = FLT_MAX;
	ptrPart->m_min[1] = FLT_MAX;
	ptrPart->m_min[2] = FLT_MAX;
	ptrPart->m_max[0] = -FLT_MAX;
	ptrPart->m_max[1] = -FLT_MAX;
	ptrPart->m_max[2] = -FLT_MAX;
	ptrPart->m_smoothShadeAngle = 32.0;
	ptrPart->m_down = NULL;
	ptrPart->m_right = NULL;
	ptrPart->m_up = NULL;
	ptrPart->m_left = NULL; 
	ptrPart->m_attachedDevice = NULL;
	ptrPart->m_pick = NULL;
	ptrPart->m_motionEffectModified = TRUE;
	m_pDoc->m_motionEffectModified = TRUE;
	ptrPart->m_effect = NULL;
	ptrPart->m_motion = NULL;
	ptrPart->m_score = NULL;
	ptrPart->m_currentScore = NULL;
	ptrPart->m_path = NULL;
	ptrPart->m_ptrTrackSeg = NULL;
	
	ptrPart->m_renderMode = YO_RENDER_MODE_POLYGON_FILLED;
	ptrPart->m_ambient[0] = 0.5f;
	ptrPart->m_ambient[1] = 0.5f;
	ptrPart->m_ambient[2] = 0.1f;
	ptrPart->m_ambient[3] = 1.0f;
	ptrPart->m_diffuse[0] = 0.5f;
	ptrPart->m_diffuse[1] = 0.5f;
	ptrPart->m_diffuse[2] = 0.1f;
	ptrPart->m_diffuse[3] = 1.0f;
	ptrPart->m_specular[0] = 0.5f;
	ptrPart->m_specular[1] = 0.5f;
	ptrPart->m_specular[2] = 0.1f;
	ptrPart->m_specular[3] = 1.0f;
	ptrPart->m_emission[0] = 0.1f;
	ptrPart->m_emission[1] = 0.1f;
	ptrPart->m_emission[2] = 0.0f;
	ptrPart->m_emission[3] = 1.0f;
	ptrPart->m_wireframe[0] = 0.5f;
	ptrPart->m_wireframe[1] = 0.5f;
	ptrPart->m_wireframe[2] = 0.1f;
	ptrPart->m_wireframe[3] = 1.0f;
	ptrPart->m_shininess = 64.0f;
	/***
	ptrPart->m_texture = NULL;
	ptrPart->m_textureScale = 1.0f;
	ptrPart->m_textureAlpha = YO_TRANSPARANT_OPAQUE;
	ptrPart->m_textureWrap = GL_REPEAT;
	ptrPart->m_textureTEV = GL_DECAL;
	ptrPart->m_sParameter[0] = 1.0f;
	ptrPart->m_sParameter[1] = 0.0f;
	ptrPart->m_sParameter[2] = 0.0f;
	ptrPart->m_sParameter[3] = 0.0f;
	ptrPart->m_sMode = GL_OBJECT_LINEAR;
	ptrPart->m_tParameter[0] = 0.0f;
	ptrPart->m_tParameter[1] = 1.0f;
	ptrPart->m_tParameter[2] = 0.0f;
	ptrPart->m_tParameter[3] = 0.0f;
	ptrPart->m_tMode = GL_OBJECT_LINEAR;
	***/

	return TRUE;
}

BOOL CStagePart::YoMakeDisplayList(GLint renderMode)
// routine currently not used
{
	GLdouble	a[3];
	GLdouble	b[3];
	GLdouble	c[3];
	GLdouble	normal[3];
	GLdouble	u[3];
	GLdouble	v[3];
	int			i;
	int			j;
	int			index;
	CStagePolygonList *ptrPolygonList;
	CStageVertices *ptrVertices;
	CStageTexture *ptrTexture = NULL;
	CStageTextureCoords *ptrTextureCoords = NULL;
	CStageVertexList *ptrVertexList;
	GLint displayListID;

	if (renderMode == YO_RENDER_FULL)
	{
		displayListID = m_displayListID;
	}
	else
	{
		displayListID = m_wireframeDisplayListID;
	}

	if (::glIsList(displayListID))
	{
		::glDeleteLists(displayListID, 1);
	}
	::glNewList(displayListID, GL_COMPILE);

	ptrPolygonList = this->m_polygonList;
	for (j = 0; j < this->m_numberPolygons; j++)
	{
		ptrVertices = ptrPolygonList->m_vertices[j % 10];
		ptrTexture = ptrPolygonList->m_texture[j % 10];
		if (ptrTexture != NULL)
		{
			ptrTextureCoords = ptrTexture->m_textureCoords;
		}
		else
		{
			ptrTextureCoords = NULL;
		}

		for (i = 0; i < ptrPolygonList->m_numberSides[j % 10]; i++)
		{
			index = ptrVertices->m_vertex[i % 4];
			// lookup vertex
			for (ptrVertexList = this->m_vertexList; index >= 20; ptrVertexList = ptrVertexList->m_next)
			{
				index -= 20;
			}

			/***
			if (m_renderMode == YO_WIREFRAME
				|| (renderMode == YO_RENDER_FULL
				&& pDoc->m_renderMode == YO_WIREFRAME)
				|| (renderMode == YO_RENDER_QUICK
				&& pDoc->m_quickMode == YO_WIREFRAME))
			{
				if (i == 0)
				{
					glBegin(GL_LINE_LOOP);
				}
				::glVertex3dv(ptrVertexList->m_vertex[index]);
			}
			else
			***/
			{
				// first three points define normal
				if (i == 0)
				{
					if (ptrTexture != NULL
						&& m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
						&& ((renderMode == YO_RENDER_FULL
						&& m_pDoc->m_renderMode >= YO_TEXTURE)
						|| (renderMode == YO_RENDER_QUICK
						&& m_pDoc->m_quickMode >= YO_TEXTURE)))
					{
						//if (ptrTexture->m_RGBImage == NULL)
						//{
						//	ptrTexture->YoInitFromDIB();
						//}
						//ptrTexture->YoSelectImage();
						if (ptrTexture->m_RGBImage != NULL)
						{
							ptrTexture->YoSelectImage();
						}
						
					}

					a[0] = ptrVertexList->m_vertex[index][0];
					a[1] = ptrVertexList->m_vertex[index][1];
					a[2] = ptrVertexList->m_vertex[index][2];
					u[0] = a[0];
					u[1] = a[1];
					u[2] = a[2];
				}
				else if (i == 1)
				{
					b[0] = ptrVertexList->m_vertex[index][0];
					b[1] = ptrVertexList->m_vertex[index][1];
					b[2] = ptrVertexList->m_vertex[index][2];
					u[0] -= b[0];
					u[1] -= b[1];
					u[2] -= b[2];
					v[0] = b[0];
					v[1] = b[1];
					v[2] = b[2];
				}
				else if (i == 2)
				{
					c[0] = ptrVertexList->m_vertex[index][0];
					c[1] = ptrVertexList->m_vertex[index][1];
					c[2] = ptrVertexList->m_vertex[index][2];
					v[0] = c[0] - v[0];
					v[1] = c[1] - v[1];
					v[2] = c[2] - v[2];
					m_pDoc->YoCrossProduct(normal, v, u);
					m_pDoc->YoNormalize(normal);

					if (m_renderMode == YO_RENDER_MODE_WIREFRAME
						|| m_renderMode == YO_RENDER_MODE_POLYGON_LINE
						|| m_renderMode == YO_RENDER_MODE_TEXTURE_POLYGON_LINE
						|| (renderMode == YO_RENDER_FULL
						&& m_pDoc->m_renderMode == YO_WIREFRAME)
						|| (renderMode == YO_RENDER_QUICK
						&& m_pDoc->m_quickMode == YO_WIREFRAME))
					{
						::glBegin(GL_LINE_LOOP);
					}
					else if (m_renderMode == YO_RENDER_MODE_POLYGON_POINT
						|| m_renderMode == YO_RENDER_MODE_TEXTURE_POLYGON_POINT)
					{
						::glBegin(GL_POINTS);
					}
					else
					{
						::glBegin(GL_POLYGON);
					}

					if ((renderMode == YO_RENDER_FULL
						&& m_pDoc->m_renderMode != YO_WIREFRAME)
						|| renderMode == YO_RENDER_QUICK
						&& m_pDoc->m_quickMode != YO_WIREFRAME)
					{
						::glNormal3dv(normal);
					}

					if (ptrTextureCoords != NULL
						&& m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
						&& ((renderMode == YO_RENDER_FULL
						&& m_pDoc->m_renderMode >= YO_TEXTURE)
						|| (renderMode == YO_RENDER_QUICK
						&& m_pDoc->m_quickMode >= YO_TEXTURE)))
					{
						::glTexCoord2d(ptrTextureCoords->m_textureCoords[0][0],
							ptrTextureCoords->m_textureCoords[0][1]);
					}
					glVertex3dv(a);
					if (ptrTextureCoords != NULL
						&& m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
						&& ((renderMode == YO_RENDER_FULL
						&& m_pDoc->m_renderMode >= YO_TEXTURE)
						|| (renderMode == YO_RENDER_QUICK
						&& m_pDoc->m_quickMode >= YO_TEXTURE)))
					{
						::glTexCoord2d(ptrTextureCoords->m_textureCoords[1][0],
							ptrTextureCoords->m_textureCoords[1][1]);
					}
					glVertex3dv(b);
					if (ptrTextureCoords != NULL
						&& m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
						&& ((renderMode == YO_RENDER_FULL
						&& m_pDoc->m_renderMode >= YO_TEXTURE)
						|| (renderMode == YO_RENDER_QUICK
						&& m_pDoc->m_quickMode >= YO_TEXTURE)))
					{
						::glTexCoord2d(ptrTextureCoords->m_textureCoords[2][0],
							ptrTextureCoords->m_textureCoords[2][1]);
					}
					glVertex3dv(c);
				}
				else
				{
					if (ptrTextureCoords != NULL
						&& m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
						&& ((renderMode == YO_RENDER_FULL
						&& m_pDoc->m_renderMode >= YO_TEXTURE)
						|| (renderMode == YO_RENDER_QUICK
						&& m_pDoc->m_quickMode >= YO_TEXTURE)))
					{
						::glTexCoord2d(ptrTextureCoords->m_textureCoords[i % 4][0],
							ptrTextureCoords->m_textureCoords[i % 4][1]);
					}
					::glVertex3dv(ptrVertexList->m_vertex[index]);
				}
			}

			if (i % 4 == 3)
			{
				ptrVertices = ptrVertices->m_next;
				if (ptrTextureCoords != NULL
					&& m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
					&& ((renderMode == YO_RENDER_FULL
					&& m_pDoc->m_renderMode >= YO_TEXTURE)
					|| (renderMode == YO_RENDER_QUICK
					&& m_pDoc->m_quickMode >= YO_TEXTURE)))
				{
					ptrTextureCoords = ptrTextureCoords->m_next;
				}
			}
		}
		::glEnd();
		if (ptrTexture != NULL
			&& m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
			&& ((renderMode == YO_RENDER_FULL
			&& m_pDoc->m_renderMode >= YO_TEXTURE)
			|| (renderMode == YO_RENDER_QUICK
			&& m_pDoc->m_quickMode >= YO_TEXTURE)))
		{
			::glDisable(GL_TEXTURE_2D);
		}

		if (j % 10 == 9)
		{
			ptrPolygonList = ptrPolygonList->m_next;
		}

	}
	::glEndList();

	return TRUE;
}


BOOL CStagePart::YoPositionTexture(GLint polygonIndex, GLint startVertexIndex)
// place texture so that the bottom of the texture is aligned to a base vector
// that goes from a start vertex index passed in to the next vertex listed in the polygon
{
	int i;
	int j;
	int index;
	int prevVertexIndex;
	int nextVertexIndex;
	CStagePolygonList *ptrPolygonList;
	CStageVertices *ptrVertices;
	CStageVertexList *ptrVertexList;
	CStageTexture *ptrTexture;
	CStageTextureCoords *ptrTextureCoords;
	GLdouble startVertex[3];
	GLdouble prevVertex[3];
	GLdouble nextVertex[3];
	GLdouble a[3];
	GLdouble b[3];
	GLdouble c[3];
	GLdouble lengthA;
	GLdouble min[2];
	GLdouble max[2];

	j = polygonIndex;
	for (ptrPolygonList = m_polygonList; j >= 10; ptrPolygonList = ptrPolygonList->m_next)
	{
		j -= 10;
	}

	// find start, previous, and next vertices
	if (startVertexIndex == 0)
	{
		prevVertexIndex = ptrPolygonList->m_numberSides[j % 10] - 1;
		nextVertexIndex = 1;
	}
	else if (startVertexIndex == ptrPolygonList->m_numberSides[j % 10] - 1)
	{
		prevVertexIndex = ptrPolygonList->m_numberSides[j % 10] - 2;
		nextVertexIndex = 0;
	}
	else
	{
		prevVertexIndex = startVertexIndex - 1;
		nextVertexIndex = startVertexIndex + 1;
	}

	index = startVertexIndex;
	for (ptrVertices = ptrPolygonList->m_vertices[j % 10]; index >= 4; ptrVertices = ptrVertices->m_next)
	{
		index -= 4;
	}
	index = ptrVertices->m_vertex[index];
	// lookup vertex
	for (ptrVertexList = m_vertexList; index >= 20; ptrVertexList = ptrVertexList->m_next)
	{
		index -= 20;
	}
	startVertex[0] = ptrVertexList->m_vertex[index][0];
	startVertex[1] = ptrVertexList->m_vertex[index][1];
	startVertex[2] = ptrVertexList->m_vertex[index][2];

	index = prevVertexIndex;
	for (ptrVertices = ptrPolygonList->m_vertices[j % 10]; index >= 4; ptrVertices = ptrVertices->m_next)
	{
		index -= 4;
	}
	index = ptrVertices->m_vertex[index];
	// lookup vertex
	for (ptrVertexList = m_vertexList; index >= 20; ptrVertexList = ptrVertexList->m_next)
	{
		index -= 20;
	}
	prevVertex[0] = ptrVertexList->m_vertex[index][0];
	prevVertex[1] = ptrVertexList->m_vertex[index][1];
	prevVertex[2] = ptrVertexList->m_vertex[index][2];

	index = nextVertexIndex;
	for (ptrVertices = ptrPolygonList->m_vertices[j % 10]; index >= 4; ptrVertices = ptrVertices->m_next)
	{
		index -= 4;
	}
	index = ptrVertices->m_vertex[index];
	// lookup vertex
	for (ptrVertexList = m_vertexList; index >= 20; ptrVertexList = ptrVertexList->m_next)
	{
		index -= 20;
	}
	nextVertex[0] = ptrVertexList->m_vertex[index][0];
	nextVertex[1] = ptrVertexList->m_vertex[index][1];
	nextVertex[2] = ptrVertexList->m_vertex[index][2];

	// find base vector (x axis) for texture map
	a[0] = nextVertex[0] - startVertex[0];
	a[1] = nextVertex[1] - startVertex[1];
	a[2] = nextVertex[2] - startVertex[2];
	lengthA = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	m_pDoc->YoNormalize(a);

	// find vector (y axis) perpendicular to base vector
	b[0] = prevVertex[0] - startVertex[0];
	b[1] = prevVertex[1] - startVertex[1];
	b[2] = prevVertex[2] - startVertex[2];
	m_pDoc->YoNormalize(b);
	m_pDoc->YoCrossProduct(c, a, b);
	m_pDoc->YoNormalize(c);
	m_pDoc->YoCrossProduct(b, c, a);
	m_pDoc->YoNormalize(b);

	// find texture coords
	ptrVertices = ptrPolygonList->m_vertices[j % 10];
	ptrTexture = ptrPolygonList->m_texture[j % 10];
	ptrTextureCoords = ptrTexture->m_textureCoords;
	min[0] = 0.0;
	max[0] = 1.0;
	min[1] = 0.0;
	max[0] = 0.0;
	for (i = 0; i < ptrPolygonList->m_numberSides[j % 10]; i++)
	{
		index = ptrVertices->m_vertex[i % 4];
		// lookup vertex
		for (ptrVertexList = m_vertexList; index >= 20; ptrVertexList = ptrVertexList->m_next)
		{
			index -= 20;
		}

		if (i == startVertexIndex)
		{
			ptrTextureCoords->m_textureCoords[i % 4][0] = 0.0;
			ptrTextureCoords->m_textureCoords[i % 4][1] = 0.0;
		}
		else if (i == nextVertexIndex)
		{
			ptrTextureCoords->m_textureCoords[i % 4][0] = 1.0;
			ptrTextureCoords->m_textureCoords[i % 4][1] = 0.0;
		}
		else
		{
			c[0] = ptrVertexList->m_vertex[index][0] - startVertex[0];
			c[1] = ptrVertexList->m_vertex[index][1] - startVertex[1];
			c[2] = ptrVertexList->m_vertex[index][2] - startVertex[2];
			ptrTextureCoords->m_textureCoords[i % 4][0] = YO_DOT_PRODUCT(c, a) / lengthA;
			ptrTextureCoords->m_textureCoords[i % 4][1] = YO_DOT_PRODUCT(c, b) / lengthA;
		}
		min[0] = YO_MIN(min[0], ptrTextureCoords->m_textureCoords[i % 4][0]);
		min[1] = YO_MIN(min[1], ptrTextureCoords->m_textureCoords[i % 4][1]);
		max[0] = YO_MAX(max[0], ptrTextureCoords->m_textureCoords[i % 4][0]);
		max[1] = YO_MAX(max[1], ptrTextureCoords->m_textureCoords[i % 4][1]);

		if (i % 4 == 3)
		{
			ptrVertices = ptrVertices->m_next;
			ptrTextureCoords = ptrTextureCoords->m_next;
		}
	}

	// set texture coords to range from 0.0 to 1.0
	ptrVertices = ptrPolygonList->m_vertices[j % 10];
	ptrTexture = ptrPolygonList->m_texture[j % 10];
	ptrTextureCoords = ptrTexture->m_textureCoords;
	for (i = 0; i < ptrPolygonList->m_numberSides[j % 10]; i++)
	{
		index = ptrVertices->m_vertex[i % 4];
		// lookup vertex
		for (ptrVertexList = m_vertexList; index >= 20; ptrVertexList = ptrVertexList->m_next)
		{
			index -= 20;
		}

		if (max[0] - min[0] != 0.0)
		{
			ptrTextureCoords->m_textureCoords[i % 4][0]
				= (ptrTextureCoords->m_textureCoords[i % 4][0] - min[0])
				/ (max[0] - min[0]);
		}
		if (max[1] - min[1] != 0.0)
		{
			ptrTextureCoords->m_textureCoords[i % 4][1]
				= (ptrTextureCoords->m_textureCoords[i % 4][1] - min[1])
				/ (max[1] - min[1]);
		}

		if (i % 4 == 3)
		{
			ptrVertices = ptrVertices->m_next;
			ptrTextureCoords = ptrTextureCoords->m_next;
		}
	}

	return TRUE;
}


BOOL CStageVertexList::YoInsertPolygon(GLint vertex, GLint polygon)
// insert polygon into linked list of polygons which contain given vertex
{
	GLint index;
	CStageVertexList *ptrVertexList;
	CStagePolygon *ptrPolygon;

	index = vertex;
	// lookup vertex
	for (ptrVertexList = this; index >= 20; ptrVertexList = ptrVertexList->m_next)
	{
		index -= 20;
	}

	ptrPolygon = new CStagePolygon();
	ptrPolygon->m_polygon = polygon;
	ptrPolygon->m_next = ptrVertexList->m_polygon[index];
	ptrVertexList->m_polygon[index] = ptrPolygon;

	return TRUE;
}


BOOL CStageEyeMotion::YoReadEyeMotion(FILE *fp)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	char s[128];
	int ch = 0;
	char command[32];
	int i;
	int done = FALSE;

	this->m_time = 1;
	this->m_type = YO_MOTION_HOLD;
	this->m_clipFront = pView->m_clipFront;
	this->m_clipRear = pView->m_clipRear;
	this->m_fieldOfView = pView->m_fieldOfView;
	for (i = 0; i < 9; i++)
	{
		m_eye[i] = pView->m_eye[i];
	}
	this->m_next = NULL;

	while (!done)
	{
		//ar.ReadString(s, 128);
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "EYE_MOTION_NULL") == 0)
		{
			if (this->m_time < 0)
			{
				this->m_time = 1;
			}
			m_pDoc->YoInsertEyeMotion(this);
			done = TRUE;
		}

		else if (strcmp(command, "EYE_MOTION_TIME") == 0)
		{
			sscanf(s, "%*s %d", &this->m_time);
		}

		else if (strcmp(command, "EYE_MOTION_TYPE") == 0)
		{
			sscanf(s, "%*s %d", &this->m_type);
		}

		else if (strcmp(command, "EYE_MOTION_EYE") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
				&this->m_eye[0], &this->m_eye[1], &this->m_eye[2],
				&this->m_eye[3], &this->m_eye[4], &this->m_eye[5],
				&this->m_eye[6], &this->m_eye[7], &this->m_eye[8],
				&this->m_clipFront, &this->m_clipRear,
				&this->m_fieldOfView);
		}

	} // end while (!done)
	return TRUE;
}


BOOL CStageEffect::YoReadEffect(FILE *fp, class CStagePart *ptrPart)

{
	BOOL			done = FALSE;
	class CStageEffect	*ptrEffect;

	ptrEffect = new	CStageEffect(m_pDoc);

	//ptrEffect->m_index = effectIndex++;
	ptrEffect->m_begin = 1;
	ptrEffect->m_end = 1;
	ptrEffect->m_priority = 1;
	ptrEffect->m_next = NULL;

	/********
	while (!done)
	{
		fscanf(fp, "%s", s);

		if (strcmp(s, "EFFECT_NULL") == 0)
		{
			if (ptrEffect->m_begin >= ptrEffect->m_end)
			{
				ptrEffect->m_end = ptrEffect->m_begin + 1;
			}
			if (ptrEffect->m_priority < 1)
			{
				ptrEffect->m_priority = 1;
			}
			//if (ptrEffect->m_priority > 10)
			//{
			//	ptrEffect->m_priority = 10;
			//}
			m_pDoc->YoInsertEffect(ptrEffect, ptrPart);
			done = TRUE;
		}

		else if (strcmp(s, "TIME_BEGIN") == 0)
		{
			fscanf(fp, "%d", &ptrEffect->m_begin);
		}

		else if (strcmp(s, "TIME_END") == 0)
		{
			fscanf(fp, "%d", &ptrEffect->m_end);
		}

		else if (strcmp(s, "PRIORITY") == 0)
		{
			fscanf(fp, "%d", &ptrEffect->m_priority);
		}

		else if (strcmp(s, "EFFECT_NAME") == 0)
		{
			fscanf(fp, "%s", &ptrEffect->m_name);
		}

		else if (strcmp(s, "PROPS") == 0)
		{
			for (i = 0; i < YO_MAX_EFFECT_PROPS; i++)
			{
				fscanf(fp, "%f", &ptrEffect->m_props[i]);
			}
			if (strcmp(ptrEffect->m_name, "EffectSparkle") == 0)
			{
				if (ptrEffect->m_props[0] < 0.0
					|| ptrEffect->m_props[0] > 1.0)
				{
					ptrEffect->m_props[0] = 0.5;
				}
				if (ptrEffect->m_props[1] < 1.0
					|| ptrEffect->m_props[1] > 60.0)
				{
					ptrEffect->m_props[1] = (float)m_pDoc->m_framesPerSecond;
				}
				if (ptrEffect->m_props[2] < 1.0
					|| ptrEffect->m_props[2] > 60.0)
				{
					ptrEffect->m_props[2] = (float)m_pDoc->m_framesPerSecond;
					ptrEffect->m_props[2]
						= YO_MAX(ptrEffect->m_props[1], ptrEffect->m_props[2]);
				}
			}
		}
		else
		{
			return FALSE;
		}
		} // end while (!done)
	*************/
	return TRUE;
}


BOOL CStageMotion::YoReadMotion(FILE *fp, class CStagePart *ptrPart)

{
	BOOL done = FALSE;
	char s[128];
	int i;
	char command[32];
	int ch = 0;
	class CStageMotion *ptrMotion;

	ptrMotion = new CStageMotion(m_pDoc);

	ptrMotion->m_time = 1;
	ptrMotion->m_type = YO_MOTION_HOLD;
	ptrMotion->m_next = NULL;

	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}

		if (strcmp(command, "MOTION_NULL") == 0)
		{
			if (ptrMotion->m_time < 0)
			{
				ptrMotion->m_time = 1;
			}
			m_pDoc->YoInsertPartMotion(ptrMotion, ptrPart);
			done = TRUE;
		}

		else if (strcmp(command, "MOTION_TIME") == 0)
		{
			sscanf(s, "%*s %d", &ptrMotion->m_time);
		}

		else if (strcmp(command, "MOTION_TYPE") == 0)
		{
			sscanf(s, "%*s %d", &ptrMotion->m_type);
		}

		else if (strcmp(command, "MOTION_TRANSLATE") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf", &ptrMotion->m_translate[0],
				&ptrMotion->m_translate[1], &ptrMotion->m_translate[2]);
		}

		else if (strcmp(command, "MOTION_ROTATE") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf", &ptrMotion->m_rotate[0],
				&ptrMotion->m_rotate[1], &ptrMotion->m_rotate[2]);
		}
		else
		{
			return FALSE;
		}
	} // end while (!done)

	return TRUE;
}

BOOL CStageMotion::YoWriteMotion(FILE *fp, CStagePart *ptrPart)

{
	CStageMotion *ptrMotion = ptrPart->m_motion;

	while (ptrMotion != NULL)
	{
		fprintf(fp, "MOTION\n");
		fprintf(fp, "MOTION_TIME %d\n", ptrMotion->m_time);
		fprintf(fp, "MOTION_TYPE %d\n", ptrMotion->m_type);
		fprintf(fp, "MOTION_TRANSLATE %lf %lf %lf\n",
			ptrMotion->m_translate[0], ptrMotion->m_translate[1], ptrMotion->m_translate[2]);
		fprintf(fp, "MOTION_ROTATE %lf %lf %lf\n",
			ptrMotion->m_rotate[0], ptrMotion->m_rotate[1], ptrMotion->m_rotate[2]);
		fprintf(fp, "MOTION_NULL\n");

		ptrMotion = ptrMotion->m_next;

	}
	return TRUE;
}


/***
BOOL CStageTexture::YoReadImage(CStagePart *ptrPart)
{
	sprintf(m_fileName, "%s", ptrPart->m_textureName);
	
	if((m_pRGBImage = auxDIBImageLoadA((const char*) m_fileName)) == NULL)
	{
		return FALSE;
	}

	ptrPart->m_texture->m_next = m_pDoc->m_textureList;
	m_pDoc->m_textureList = ptrPart->m_texture;
	return TRUE;
}
***/

CStagePath::~CStagePath()
{
	int i;
	CStagePath *ptrPath;
	CStagePath *prevPath = NULL;

	// relink paths of current part
	for (ptrPath = m_ptrPart->m_path; ptrPath != this;)
	{
		prevPath = ptrPath;
		ptrPath = ptrPath->m_nextPath;
	}
	if (prevPath == NULL)
	{
		m_ptrPart->m_path = this->m_nextPath;
	}
	else
	{
		prevPath->m_nextPath = this->m_nextPath;
	}


	// remove the name from the path hash table
	i = (int)m_pDoc->YoHash(m_name, YO_HASH_VALUE, YO_HASH_SIZE);
	prevPath = NULL;

	for (ptrPath = m_pDoc->m_pathHash[i];
		ptrPath != NULL && strcmp(m_name, ptrPath->m_name) != 0;
		ptrPath = ptrPath->m_nextHash)
	{
		prevPath = ptrPath;
	}
	if (prevPath == NULL)
	{
		m_pDoc->m_pathHash[i] = ptrPath->m_nextHash;
	}
	else
	{
		prevPath->m_nextHash = ptrPath->m_nextHash;
	}
	ptrPath->m_nextHash = NULL;

	m_pDoc->m_numberOfPaths--;

	/***
	// remove the name from the path hash table
	i = (int)m_pDoc->YoHash(m_name, YO_HASH_VALUE, YO_HASH_SIZE);
	for (ptrPath = m_pDoc->m_pathHash[i];
		(strcmp(m_name, ptrPath->m_name) != 0)
		|| (ptrPath->m_nextHash != NULL
		&& (strcmp(m_name, ptrPath->m_nextHash->m_name) != 0));
		ptrPath = ptrPath->m_nextHash);
	if (ptrPath == m_pDoc->m_pathHash[i]
		&& strcmp(m_name, ptrPath->m_name) == 0)
	{
		m_pDoc->m_pathHash[i] = ptrPath->m_nextHash;
		ptrPath->m_nextHash = NULL;
	}
	else
	{
		ptrPath->m_nextHash = ptrPath->m_nextHash->m_nextHash;
		ptrPath->m_nextHash->m_nextHash = NULL;
	}
	***/


}


BOOL CStagePath::YoReadPath(FILE *fp, CStagePart *ptrPart)
{
	CStageTag *ptrTag;
	char				s[128];
	char				command[32];
	BOOL				done = FALSE;
	BOOL				tdone = FALSE;
	int					ch = 0;
	int					i;

	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "PATH_NULL") == 0)
		{
			//m_nextPath = ptrPart->m_path;
			//ptrPart->m_path = this;
			done = TRUE;
		}
		else if (strcmp(command, "PATH_COLOR") == 0)
		{
			sscanf(s, "%*s %f %f %f %f",
				&m_color[0], &m_color[1],
				&m_color[2], &m_color[3]);
		}
		else if (strcmp(command, "PATH_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &m_visible);
		}
		else if (strcmp(command, "TAG") == 0)
		{
			ptrTag = new CStageTag(m_pDoc);
			ptrTag->m_ptrPath = this;
			sscanf(s, "%*s %d %lf %lf %lf %lf %lf %lf",
				&ptrTag->m_tag, &ptrTag->m_translate[0],
				&ptrTag->m_translate[1], &ptrTag->m_translate[2],
				&ptrTag->m_rotate[0], &ptrTag->m_rotate[1], &ptrTag->m_rotate[2]);
			YoInsertTag(ptrTag);
		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;
}


BOOL CStagePath::YoWritePath(FILE *fp)
{
	CStageTag *currentTag;

	fprintf(fp, "PATH %s\n", m_name);
	fprintf(fp, "PATH_VISIBLE %d\n", m_visible);
	fprintf(fp, "PATH_COLOR %lf %lf %lf %lf\n",
		m_color[0], m_color[1], m_color[2], m_color[3]);

	for (currentTag = m_ptrTag; currentTag != NULL; currentTag = currentTag->m_nextTag)
	{
		fprintf(fp, "TAG %d %lf %lf %lf %lf %lf %lf\n",
			currentTag->m_tag,
			currentTag->m_translate[0], currentTag->m_translate[1], currentTag->m_translate[2],
			currentTag->m_rotate[0], currentTag->m_rotate[1], currentTag->m_rotate[2]);
	}
	
	fprintf(fp, "PATH_NULL\n");

	return TRUE;
}


BOOL CStagePath::YoInitPath(CStagePart *ptrPart)
{
	int i;

	sprintf(m_name, "");
	for (i = 0; i < 4; i++)
	{
		m_color[i] = ptrPart->m_wireframe[i];
	}
	m_nextHash = NULL;
	m_nextPath = ptrPart->m_path;
	ptrPart->m_path = this;
	m_ptrTag = NULL;
	m_visible = TRUE;
	m_ptrPart = ptrPart;
	m_pDoc->m_numberOfPaths++;

	

	return TRUE;
}


BOOL CStagePath::YoInsertTag(CStageTag *ptrTag)
{
	CStageTag *currentTag;
	CStageTag *prevTag = NULL;

	ptrTag->m_displayListID = m_pDoc->YoGetNewDisplayListID(NULL, ptrTag);

	if (m_ptrTag == NULL)
	// reading from file, insert a beginning of list
	{
		m_ptrTag = ptrTag;
	}

	else if (ptrTag->m_tag == UINT_MAX)
	// insert new tag at end of list
	{
		for (currentTag = m_ptrTag; currentTag != NULL;)
		{
			prevTag = currentTag;
			currentTag = currentTag->m_nextTag;
		}

		ptrTag->m_tag = prevTag->m_tag + 1;
		prevTag->m_nextTag = ptrTag;
		ptrTag->m_prevTag = prevTag;
	}

	else
	{
		for (currentTag = m_ptrTag;
			currentTag != NULL && currentTag->m_tag < ptrTag->m_tag;)
		{
			prevTag = currentTag;
			currentTag = currentTag->m_nextTag;
		}

		if (currentTag == NULL && prevTag == NULL)
		{
			m_ptrTag = ptrTag;
			return TRUE;
		}
		else if (prevTag == NULL)
		{
			m_ptrTag = ptrTag;
		}
		else
		{
			prevTag->m_nextTag = ptrTag;
			ptrTag->m_prevTag = prevTag;
		}

		if (currentTag != NULL)
		{
			currentTag->m_prevTag = ptrTag;
			ptrTag->m_nextTag = currentTag;
		}
	}
	m_pDoc->m_currentTag = ptrTag;
	return TRUE;
}


BOOL CStagePath::YoDeleteTag(CStageTag *ptrTag)
{
	CStageTag *currentTag;
	CStageTag *prevTag = NULL;

	for (currentTag = m_ptrTag;
		currentTag != NULL && currentTag != ptrTag;)
		{
			prevTag = currentTag;
			currentTag = currentTag->m_nextTag;
		}

	if (currentTag == NULL)
	{
		return FALSE;
	}

	if (prevTag == NULL && currentTag->m_nextTag == NULL)
	{
		// last tag, therefore delete path as well
		delete ptrTag;
		delete this;
		return TRUE;
	}

	if (currentTag->m_nextTag != NULL && prevTag != NULL)
	{
		currentTag->m_nextTag->m_prevTag = prevTag;
		prevTag->m_nextTag = currentTag->m_nextTag;
	}
	else if (currentTag->m_nextTag != NULL && prevTag == NULL)
	{
		currentTag->m_nextTag->m_prevTag = NULL;
		m_ptrTag = currentTag->m_nextTag;
	}
	else if (currentTag->m_nextTag == NULL && prevTag != NULL)
	{
		prevTag->m_nextTag = NULL;
	}
	
	delete ptrTag;

	return TRUE;
}


CStageTag::~CStageTag()
{
	CStageTag *prevTag = NULL;
	CStageTag *currentTag;

	// remove tag from m_pDoc->m_pickTag table and relink list
	for (currentTag = m_pDoc->m_pickTag[m_displayListID % YO_HASH_SIZE];
		currentTag != this;)
	{
		prevTag = currentTag;
		currentTag = currentTag->m_pick;
	}
	
	if (prevTag == NULL)
	{
		m_pDoc->m_pickTag[m_displayListID % YO_HASH_SIZE] = m_pick;
	}
	else
	{
		prevTag->m_pick = m_pick;
	}
}


unsigned CStageDoc::YoHash(char *s, unsigned hashValue, unsigned hashSize)

// given a name, s, form a positive integer hash value

{
	unsigned h;

	for (h = 0; *s != '\0'; s++)
	{
		h = *s + hashValue * h;
	}
	return h % hashSize;
}

class CStageDevice* CStageDoc::YoDeviceHashLookup(char *s)

// takes an device name, hashes, finds the device node with that name,
// and returns a pointer to the device node

{
	int i;
	class CStageDevice *hptr;    
   
	i = (int)YoHash(s, YO_HASH_VALUE, YO_HASH_SIZE);
	hptr = m_deviceHash[i]; 
	while (hptr != NULL)
	{
		if (strcmp(s, hptr->m_name) == 0) 
		{
			return hptr;
		}
		hptr = hptr->m_nextHash;
	}
	return NULL;
}


BOOL CStageDoc::YoDeviceHashInstall(CStageDevice *ptrDevice)

// set up pointer in hash table, m_deviceHash, to device node, ptrDevice,
// with the hash value ptrDevice->m_name.  The device node has already been created
// in YoReadDevice.

{
	int i;

	if (YoDeviceHashLookup(ptrDevice->m_name) != NULL)
	{
		// device has already been installed in hash table
		return TRUE;
	}
   
	i = (int)YoHash(ptrDevice->m_name, YO_HASH_VALUE, YO_HASH_SIZE);
	ptrDevice->m_nextHash = m_deviceHash[i];
	m_deviceHash[i] = ptrDevice;

	return TRUE;
}


BOOL CStageDoc::YoDeviceHashInit(void)

// hash table is traversed and each pointer is reset to NULL

{
	int i;

	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		m_deviceHash[i] = NULL;
	}
	return TRUE;
}


class CStagePath* CStageDoc::YoPathHashLookup(char *s)

// takes an path name, hashes, finds the path node with that name,
// and returns a pointer to the path node

{
	int i;
	class CStagePath *hptr;    
   
	i = (int)YoHash(s, YO_HASH_VALUE, YO_HASH_SIZE);
	hptr = m_pathHash[i]; 
	while (hptr != NULL)
	{
		if (strcmp(s, hptr->m_name) == 0) 
		{
			return hptr;
		}
		hptr = hptr->m_nextHash;
	}
	return NULL;
}


BOOL CStageDoc::YoPathHashInstall(CStagePath *ptrPath)

// set up pointer in hash table, m_pathHash, to path node, ptrPath,
// with the hash value ptrPath->m_name.  The path node has already been created
// in YoReadPath.

{
	int i;

	if (YoPathHashLookup(ptrPath->m_name) != NULL)
	{
		// path has already been installed in hash table
		return TRUE;
	}
   
	i = (int)YoHash(ptrPath->m_name, YO_HASH_VALUE, YO_HASH_SIZE);
	ptrPath->m_nextHash = m_pathHash[i];
	m_pathHash[i] = ptrPath;

	return TRUE;
}


BOOL CStageDoc::YoPathHashInit(void)

// hash table is traversed and each pointer is reset to NULL

{
	int i;

	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		m_pathHash[i] = NULL;
	}
	return TRUE;
}


class CStageEyeView* CStageDoc::YoEyeViewHashLookup(char *s)

// takes an path name, hashes, finds the eye view with that name,
// and returns a pointer to the eye view node

{
	int i;
	class CStageEyeView *hptr;    
   
	i = (int)YoHash(s, YO_HASH_VALUE, YO_HASH_SIZE);
	hptr = m_eyeViewHash[i]; 
	while (hptr != NULL)
	{
		if (strcmp(s, hptr->m_name) == 0) 
		{
			return hptr;
		}
		hptr = hptr->m_nextHash;
	}
	return NULL;
}


BOOL CStageDoc::YoEyeViewHashInstall(CStageEyeView *ptrEyeView)

// set up pointer in hash table, m_eyeViewHash, to eye view node, ptrEyeView,
// with the hash value ptrEyeView->m_name.  The eye view node has already been created
// in YoReadWorkcell.

{
	int i;

	if (YoEyeViewHashLookup(ptrEyeView->m_name) != NULL)
	{
		// path has already been installed in hash table
		return TRUE;
	}
   
	i = (int)YoHash(ptrEyeView->m_name, YO_HASH_VALUE, YO_HASH_SIZE);
	ptrEyeView->m_nextHash = m_eyeViewHash[i];
	m_eyeViewHash[i] = ptrEyeView;

	return TRUE;
}


BOOL CStageDoc::YoEyeViewHashInit(void)

// hash table is traversed and all entries are deleted, then the
// table is reset to NULL.  Note: differs from other hash tables

{
	CStageEyeView *ptrEyeView;
	int i;

	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		while (m_eyeViewHash[i] != NULL)
		{
			ptrEyeView = m_eyeViewHash[i];
			delete ptrEyeView;
		}
	}
	return TRUE;
}


BOOL CStageDoc::YoIsChild(CStageDevice *ptrDevice, CStageDevice *ptrChild)
	// if ptrChild is a child, grandchild, great-grandchild, etc of ptrDevice
	// return TRUE.
{
	CStageDevice *currentDevice = ptrChild;
	BOOL up = TRUE;

	if (ptrDevice == NULL || ptrChild == NULL)
	{
		return FALSE;
	}

	while (TRUE)
	{
		if (currentDevice == ptrDevice && up == TRUE)
		{
			return TRUE;
		}
		else if (currentDevice == ptrDevice && up == FALSE)
		{
			return FALSE;
		}
		else if (currentDevice->m_up != NULL)
		{
			currentDevice = currentDevice->m_up;
			up = TRUE;
		}
		else if (currentDevice->m_left != NULL)
		{
			currentDevice = currentDevice->m_left;
			up = FALSE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}


BOOL CStageDoc::YoIsChild(CStagePart *ptrPart, CStagePart *ptrChild)
	// if ptrChild is a child, grandchild, great-grandchild, etc of ptrPart
	// return TRUE.
{
	CStagePart *currentPart = ptrChild;
	BOOL up = TRUE;

	if (ptrPart == NULL || ptrChild == NULL
		|| strcmp(ptrPart->m_deviceName, ptrChild->m_deviceName) != 0)
	{
		return FALSE;
	}

	while (TRUE)
	{
		if (currentPart == ptrPart && up == TRUE)
		{
			return TRUE;
		}
		else if (currentPart == ptrPart && up == FALSE)
		{
			return FALSE;
		}
		else if (currentPart->m_up != NULL)
		{
			currentPart = currentPart->m_up;
			up = TRUE;
		}
		else if (currentPart->m_left != NULL)
		{
			currentPart = currentPart->m_left;
			up = FALSE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}


class CStagePart* CStageDoc::YoPartLookup(CStageDevice *ptrDevice, char *s)
{

	m_partStack = NULL;
	CStagePart *ptrPart = ptrDevice->m_ptrPart;

	while (ptrPart != NULL)
	{
		if (strcmp(ptrPart->m_partName, s) == 0)
		{
			while (YoPopPart() != NULL);
			return ptrPart;
		}
		if (ptrPart->m_down != NULL)
		{
			if (ptrPart->m_right != NULL)
			{
				YoPushPart(ptrPart->m_right);
			}
			ptrPart = ptrPart->m_down;
		}
		else if (ptrPart->m_right != NULL)
		{
			ptrPart = ptrPart->m_right;
		}
		else if (m_partStack != NULL)
		{
			ptrPart = YoPopPart();
		}
		else 
		{
			ptrPart = NULL; 
		}
	}
	return NULL;

}

BOOL CStageDoc::YoPickInit(void)

{
	int i;

	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		m_pickPart[i] = NULL;
		m_pickTag[i] = NULL;
	}
	return TRUE;
}


/***
class CStageTexture* CStageDoc::YoTextureHashLookup(char *s)

// takes a texture name, hashes, finds the texture node with that name,
// and returns a pointer to the texture node

{
	int i;
	class CStageTexture *hptr;    
   
	i = (int)YoHash(s, YO_HASH_VALUE, YO_HASH_SIZE);
	hptr = m_textureHash[i]; 
	while (hptr != NULL)
	{
		if (strcmp(s, hptr->m_fileName) == 0) 
		{
			return hptr;
		}
		hptr = hptr->m_nextHash;
	}
	return NULL;
}


BOOL CStageDoc::YoTextureHashInstall(CStageTexture *ptrTexture)

// set up pointer in hash table, m_textureHash, to texture node, ptrTexture,
// with the hash value ptrTexture->m_fileName.  The texture node has already been created
// in YoReadTexture.

{
	int i;

	if (YoTextureHashLookup(ptrTexture->m_fileName) != NULL)
	{
		// texture has already been installed in hash table
		return TRUE;
	}
   
	i = (int)YoHash(ptrTexture->m_fileName, YO_HASH_VALUE, YO_HASH_SIZE);
	ptrTexture->m_nextHash = m_textureHash[i];
	m_textureHash[i] = ptrTexture;

	return TRUE;
}


BOOL CStageDoc::YoTextureHashInit(void)

// hash table is traversed and each pointer is reset to NULL
// TO DO:

{
	int i;

	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		m_textureHash[i] = NULL;
	}
	return TRUE;
}
***/


BOOL CStageDoc::YoInsertDevice(CStageDevice *ptrDevice, CStagePart *ptrPart)
// Device is inserted into main stage device data structure
// and installed in device hash table after it is created, cloned,
// or read in from file
{
	CStageDevice *currentDevice = m_deviceList;
	// CStageDevice *ptrParent;
	GLint stackDepth;
	GLint i;

	::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &stackDepth);
	m_deviceStack = NULL;

	YoDeviceHashInstall(ptrDevice);

	//if (ptrDevice->m_type == YO_LIGHT)
	//{
	//	((CStageLight *)ptrDevice)->m_ptrLight = m_lightList;
	//	m_lightList = (CStageLight *)ptrDevice;
	//}

	// insert pallet into conveyor object if parent is of type conveyor
	//if (ptrDevice->m_type == YO_CONVEYOR_PALLET
	//	&& strcmp(((CStageConveyorPallet *)ptrDevice)->m_parent, "NONE") != 0)
	//{
	//	ptrParent = YoDeviceHashLookup(((CStageConveyorPallet *)ptrDevice)->m_parent);
	//	if (ptrParent != NULL && ptrParent->m_type == YO_CONVEYOR)
	//	{
	//		((CStageConveyor *)ptrParent)->YoInsertPallet((CStageConveyorPallet *)ptrDevice);
	//	}
	//}

	if (currentDevice == NULL)
	{
		m_deviceList = ptrDevice;
		return TRUE;
	}

	while (TRUE)
	{
		if ((strcmp(ptrDevice->m_parent, currentDevice->m_name) == 0)
			&& (currentDevice->m_down == NULL))
		{
			currentDevice->m_down = ptrDevice;
			ptrDevice->m_up = currentDevice;
			
			if (ptrPart == NULL || ptrPart == ptrDevice->m_ptrPart)
			{
				ptrDevice->m_attachedFromPart = NULL;
			}
			else
			{
				ptrDevice->m_attachedFromPart = ptrPart;
				if (ptrPart->m_attachedDevice == NULL)
				{
					ptrPart->m_attachedDevice = ptrDevice;
				}
			}
			::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &i);
			while(i > stackDepth)
			{
				::glPopMatrix();
				i--;
			}
			YoFreeDevice();
			return TRUE;
		}

		if ((strcmp(ptrDevice->m_parent, currentDevice->m_parent) == 0)
			&& (currentDevice->m_right == NULL))
		{
			currentDevice->m_right = ptrDevice;
			ptrDevice->m_left = currentDevice;

			if (ptrPart == NULL || ptrPart == ptrDevice->m_ptrPart)
			{
				ptrDevice->m_attachedFromPart = NULL;
			}
			else
			{
				ptrDevice->m_attachedFromPart = ptrPart;
				if (ptrPart->m_attachedDevice == NULL)
				{
					ptrPart->m_attachedDevice = ptrDevice;
				}
			}

			//if (ptrPart != NULL)
			//{
			//	ptrDevice->m_attachedFromPart = ptrPart;
			//	if (ptrPart->m_attachedDevice == NULL)
			//	{
			//		ptrPart->m_attachedDevice = ptrDevice;
			//	}
			//}
			::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &i);
			while(i > stackDepth)
			{
				::glPopMatrix();
				i--;
			}
			YoFreeDevice();
			return TRUE;
		}

		if (currentDevice->m_down != NULL)
		{
			if (currentDevice->m_right != NULL)
			{
				YoPushDevice(currentDevice->m_right);
			}
			currentDevice = currentDevice->m_down;
		}
		else if (currentDevice->m_right != NULL)
		{
			currentDevice = currentDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			currentDevice = YoPopDevice();
		}
		else
		{
			return TRUE;
		}
  }
	return TRUE;
}


BOOL CStageDoc::YoAttachDevice(CStagePart *ptrPart)
// the current device is attached TO ptrPart
// Note: ptrPart != NULL
// Device must already exist in device hash table

{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	GLdouble m[16];
	GLdouble mp[16];
	GLdouble mpInv[16];
	CStagePart *currentPart;
	CStageDevice *currentDevice;
	CStageDevice *ptrDevice;
	CStageDevice *ptrParent;
	int i;
	int stackDepth;

	//if (ptrPart == NULL)
	//{
	//	return FALSE;
	//}


	::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &stackDepth);

	currentPart = m_currentPart;
	currentDevice = m_currentDevice;
	//m_currentPart = m_currentDevice->m_ptrPart;
	//YoModelMatrixOfCurrentPart(m);

	ptrParent = YoDeviceHashLookup(ptrPart->m_deviceName);

	if (currentDevice->m_type == YO_TRAIN
		&& ptrParent->m_type == YO_TRACK)
	{
		// always attach train to base part
		// TO DO: CHANGE THIS ROUTINE (09 Oct 2000)
		//ptrPart = ptrParent->m_ptrPart;
		//((CStageTrain *)m_currentDevice)->m_ptrTrackSeg 
		//	= ptrParent->m_ptrPart->m_ptrTrackSeg;
		//((CStageTrain *)m_currentDevice)->m_relativePosition = 0.0f;
		//((CStageTrain *)m_currentDevice)->YoCalculateTrainPosition();

		((CStageTrain *)m_currentDevice)->m_ptrTrackSeg = ptrPart->m_ptrTrackSeg;
		((CStageTrain *)m_currentDevice)->m_relativePosition = 0.0f;
		((CStageTrain *)m_currentDevice)->YoCalculateTrainPosition();
	
	}
	else
	{
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();
		pView->YoTxyz(m_currentDevice->m_ptrPart,
			m_currentDevice->m_ptrPart->m_translate,
			m_currentDevice->m_ptrPart->m_rotate);
		//::glMultMatrixd(m);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
		::glPopMatrix();
	}

	//m_currentDevice = currentDevice;
	//m_currentPart = currentPart;
	//YoTranslateRotateValues(m,
	//	m_currentDevice->m_ptrPart->m_translate,
	//	m_currentDevice->m_ptrPart->m_rotate);
	//for (i = 0; i < 3; i++)
	//{
	//	m_currentDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
	//}
	//:glPopMatrix();

	m_currentDevice = ptrParent;

	if (m_currentDevice->m_ptrPart == ptrPart)
	{
		currentDevice->m_attachedFromPart = NULL;
	}
	else
	{
		currentDevice->m_attachedFromPart = ptrPart;
	}

	sprintf(currentDevice->m_parent, "%s", m_currentDevice->m_name);

	if (currentDevice->m_type == YO_TRAIN
		&& ptrParent->m_type == YO_TRACK)
	{
		m_currentDevice = currentDevice;
		m_currentPart = currentPart;
	}
	else
	{
		m_currentPart = ptrPart;
		YoModelMatrixOfCurrentPart(mp);
		YoMatrixInverse(mp, mpInv);

		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadMatrixd(mpInv);
		::glMultMatrixd(m);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
		m_currentDevice = currentDevice;
		m_currentPart = currentPart;
		m_currentDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
		YoTranslateRotateValues(m,
			m_currentDevice->m_ptrPart->m_translate,
			m_currentDevice->m_ptrPart->m_rotate);
		for (i = 0; i < 3; i++)
		{
			m_currentDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
		}
		::glPopMatrix();

	}

	if (currentDevice->m_type == YO_CONVEYOR_PALLET
		&& ptrParent != NULL && ptrParent->m_type == YO_CONVEYOR)
	{
		((CStageConveyor *)ptrParent)->YoInsertPallet((CStageConveyorPallet *)currentDevice);
	}

//	YoInsertDevice(m_currentDevice, ptrPart);

	ptrDevice = m_deviceList;
	m_deviceStack = NULL;

	if (ptrDevice == NULL)
	{
		m_deviceList = m_currentDevice;
		return TRUE;
	}

	while (TRUE)
	{
		if ((strcmp(m_currentDevice->m_parent, ptrDevice->m_name) == 0)
			&& (ptrDevice->m_down == NULL))
		{
			ptrDevice->m_down = m_currentDevice;
			m_currentDevice->m_up = ptrDevice;

			if (ptrPart != NULL && ptrPart != ptrDevice->m_ptrPart)
			{
				m_currentDevice->m_attachedFromPart = ptrPart;
				if (ptrPart->m_attachedDevice == NULL)
				{
					ptrPart->m_attachedDevice = m_currentDevice;
				}
			}

			::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &i);
			while(i > stackDepth)
			{
				::glPopMatrix();
				i--;
			}

			YoFreeDevice();
			return TRUE;
		}

		if ((strcmp(m_currentDevice->m_parent, ptrDevice->m_parent) == 0)
			&& (ptrDevice->m_right == NULL))
		{
			ptrDevice->m_right = m_currentDevice;
			m_currentDevice->m_left = ptrDevice;

			if (ptrPart != NULL && ptrPart != ptrDevice->m_ptrPart)
			{
				m_currentDevice->m_attachedFromPart = ptrPart;
				if (ptrPart->m_attachedDevice == NULL)
				{
					ptrPart->m_attachedDevice = m_currentDevice;
				}
			}

			::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &i);
			while(i > stackDepth)
			{
				::glPopMatrix();
				i--;
			}

			YoFreeDevice();
			return TRUE;
		}

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			ptrDevice = YoPopDevice();
		}
		else
		{
			return TRUE;
		}
	}
	return TRUE;
}

/***

BOOL CStageDoc::YoAttachDevice(CStagePart *ptrPart)
{

	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDevice	*ptrDevice = m_deviceList;
	BOOL			done = FALSE;
	GLdouble		mat[16];
	GLdouble		invMat[16];
	int i;

	m_deviceStack = NULL;

	if (m_currentDevice == NULL)
	{
		return TRUE;
	}

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glLoadIdentity();

	while (!done)
	{
		::glPushMatrix();
		pView->YoTxyz(ptrDevice->m_ptrPart, ptrDevice->m_ptrPart->m_translate, ptrDevice->m_ptrPart->m_rotate);
		
		if (strcmp(m_currentDevice->m_parent, ptrDevice->m_name) == 0)
		{
			::glGetDoublev(GL_MODELVIEW_MATRIX, mat);
			YoMatrixInverse(mat, invMat);
			::glPushMatrix();
			::glLoadIdentity();
			::glMultMatrixd(invMat);
			pView->YoTxyz(m_currentDevice->m_ptrPart, m_currentDevice->m_ptrPart->m_translate, m_currentDevice->m_ptrPart->m_rotate);
			::glGetDoublev(GL_MODELVIEW_MATRIX, mat);
			::glPopMatrix();

			YoTranslateRotateValues(mat, m_currentDevice->m_ptrPart->m_translate, m_currentDevice->m_ptrPart->m_rotate);
			for (i = 0; i < 3; i++)
			{
				m_currentDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}
		}

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			else
			{
				YoPushDevice(NULL);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
			glPopMatrix();
		}
		else if (!YoAllStackDevicesNull())
		{
			glPopMatrix();
			glPopMatrix();
			while ((ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
		}
		else
		{
			glPopMatrix();
			while (m_deviceStack != NULL
				&& (ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
			done = TRUE;
		}
	} // end while (!done)

	::glPopMatrix();

	ptrDevice = m_deviceList;
	m_deviceStack = NULL;

	if (ptrDevice == NULL)
	{
		m_deviceList = m_currentDevice;
		return TRUE;
	}

	while (TRUE)
	{
		if ((strcmp(m_currentDevice->m_parent, ptrDevice->m_name) == 0)
			&& (ptrDevice->m_down == NULL))
		{
			ptrDevice->m_down = m_currentDevice;
			m_currentDevice->m_up = ptrDevice;

			if (ptrPart != NULL)
			{
				m_currentDevice->m_attachedFromPart = ptrPart;
				if (ptrPart->m_attachedDevice == NULL)
				{
					ptrPart->m_attachedDevice = m_currentDevice;
				}
			}

			YoFreeDevice();
			return TRUE;
		}

		if ((strcmp(m_currentDevice->m_parent, ptrDevice->m_parent) == 0)
			&& (ptrDevice->m_right == NULL))
		{
			ptrDevice->m_right = m_currentDevice;
			m_currentDevice->m_left = ptrDevice;

			if (ptrPart != NULL)
			{
				m_currentDevice->m_attachedFromPart = ptrPart;
				if (ptrPart->m_attachedDevice == NULL)
				{
					ptrPart->m_attachedDevice = m_currentDevice;
				}
			}

			YoFreeDevice();
			return TRUE;
		}

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			ptrDevice = YoPopDevice();
		}
		else
		{
			return TRUE;
		}
  }


	CStageDevice *ptrDevice = m_deviceList;
	GLdouble m[16];
	GLdouble trans[3];
	GLdouble rot[3];
	int i;

	m_deviceStack = NULL;

	if (ptrDevice == NULL)
	{
		m_deviceList = m_currentDevice;
		strcpy(m_currentDevice->m_parent, "NONE");
		return TRUE;
	}

	while (TRUE)
	{
		if (strcmp(m_currentDevice->m_parent, ptrDevice->m_name) == 0)
		{
			::glMatrixMode(GL_MODELVIEW);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			YoTranslateRotateValues(m, trans, rot);
			for (i = 0; i < 4; i++)
			{
				m_currentDevice->m_ptrPart->m_translate[i] -= ptrDevice->m_ptrPart->m_translate[i];
				m_currentDevice->m_ptrPart->m_rotate[i] -= ptrDevice->m_ptrPart->m_rotate[i];
			}
		}

		if (strcmp(m_currentDevice->m_parent, ptrDevice->m_name) == 0
			&& ptrDevice->m_down == NULL)
		{
			ptrDevice->m_down = m_currentDevice;
			m_currentDevice->m_up = ptrDevice;
			YoFreeDevice();
			return TRUE;
		}

		if (strcmp(m_currentDevice->m_parent, ptrDevice->m_parent) == 0
			&& ptrDevice->m_right == NULL)
		{
			ptrDevice->m_right = m_currentDevice;
			m_currentDevice->m_left = ptrDevice;
			YoFreeDevice();
			return TRUE;
		}

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			ptrDevice = YoPopDevice();
		}
		else
		{
			return TRUE;
		}
  }

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glLoadIdentity();

	while (!done)
	{
		::glPushMatrix();
		pView->YoTxyz(ptrDevice->m_ptrPart, ptrDevice->m_ptrPart->m_translate, ptrDevice->m_ptrPart->m_rotate);
		if (ptrDevice == m_currentDevice)
		{
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			m_currentDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
			YoTranslateRotateValues(m, m_currentDevice->m_ptrPart->m_translate, m_currentDevice->m_ptrPart->m_rotate);
		}

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			else
			{
				YoPushDevice(NULL);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
			glPopMatrix();
		}
		else if (!YoAllStackDevicesNull())
		{
			glPopMatrix();
			glPopMatrix();
			while ((ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
		}
		else
		{
			glPopMatrix();
			while (m_deviceStack != NULL
				&& (ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
			done = TRUE;
		}
	} // end while (!done)

	::glPopMatrix();

	return TRUE;
}
***/

BOOL CStageDoc::YoImportDevice(char *fileName, char *deviceName)
{
	char s[256];
	FILE *fp;
	char command[32];
	int done = FALSE;
	int ch = 0;
	int i;

	if ((fp = fopen(fileName, "r")) == NULL)
	{
		sprintf(s, "%s", (LPCSTR)GetPathName());
		for (i = strlen(s); i >= 0; i--)
		{
			if (s[i] == 'w' && s[i + 1] == 'o' && s[i + 2] == 'r'
				&& s[i + 3] == 'k' && s[i + 4] == 'c' && s[i + 5] == 'e'
				&& s[i + 6] == 'l' && s[i + 7] == 'l' && s[i + 8] == 's')
			{
				break;
			}
		}

		if (i > 0)
		{
			sprintf(&s[i], "devices\\%s", fileName); 
			if ((fp = fopen(s, "r")) == NULL)
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}

	if (YoDeviceHashLookup(deviceName) != NULL)
	{
		YoGetUniqueDeviceName(deviceName);
	}

	while(!done)
	{
		// Read in single line from file
		memset(s, 0, 256);
		for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}

		if (strcmp(command, "NULL") == 0)
		{
			fclose(fp);
			YoLinkTrackSegs();
			m_currentPart = m_currentDevice->m_ptrPart;
			done = TRUE;
		}
		
		else if (strcmp(command, "DEVICE") == 0)
		{
			CStageDevice *ptrDevice;
			ptrDevice = new CStageDevice(this);
			ptrDevice->m_type = YO_DEVICE;
			ptrDevice->YoInitDevice(ptrDevice);
			sprintf(ptrDevice->m_name, "%s", deviceName);
			if (ptrDevice->YoReadDevice(fp, ptrDevice) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrDevice;
		}
		else if (strcmp(command, "LIGHT") == 0)
		{
			CStageLight *ptrLight;
			ptrLight = new CStageLight(this);
			ptrLight->m_type = YO_LIGHT;
			ptrLight->YoInitDevice((CStageDevice *)ptrLight);
			sprintf(ptrLight->m_name, "%s", deviceName);
			if (ptrLight->YoReadLight(fp, ptrLight) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrLight;
		}
		else if (strcmp(command, "ROBOT6") == 0)
		{
			CStageRobot6 *ptrRobot6;
			ptrRobot6 = new CStageRobot6(this);
			ptrRobot6->m_type = YO_ROBOT6;
			ptrRobot6->YoInitDevice((CStageDevice *)ptrRobot6);
			sprintf(ptrRobot6->m_name, "%s", deviceName);
			if (ptrRobot6->YoReadRobot6(fp, ptrRobot6) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrRobot6;
		}
		else if (strcmp(command, "ROTARY_TABLE") == 0)
		{
			CStageRotaryTable *ptrRotaryTable;
			ptrRotaryTable = new CStageRotaryTable(this);
			ptrRotaryTable->m_type = YO_ROTARY_TABLE;
			ptrRotaryTable->YoInitDevice((CStageDevice *)ptrRotaryTable);
			sprintf(ptrRotaryTable->m_name, "%s", deviceName);
			if (ptrRotaryTable->YoReadRotaryTable(fp, ptrRotaryTable) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrRotaryTable;
		}
		else if (strcmp(command, "GRIPPER") == 0)
		{
			CStageGripper *ptrGripper;
			ptrGripper = new CStageGripper(this);
			ptrGripper->m_type = YO_GRIPPER;
			ptrGripper->YoInitDevice((CStageDevice *)ptrGripper);
			sprintf(ptrGripper->m_name, "%s", deviceName);
			if (ptrGripper->YoReadGripper(fp, ptrGripper) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrGripper;
		}
		else if (strcmp(command, "BARRETT_HAND") == 0)
		{
			CStageBarrettHand *ptrBarrettHand;
			ptrBarrettHand = new CStageBarrettHand(this);
			ptrBarrettHand->m_type = YO_BARRETT_HAND;
			ptrBarrettHand->YoInitDevice((CStageDevice *)ptrBarrettHand);
			sprintf(ptrBarrettHand->m_name, "%s", deviceName);
			if (ptrBarrettHand->YoReadBarrettHand(fp, ptrBarrettHand) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrBarrettHand;
		}
		else if (strcmp(command, "BAR_CODE_READER") == 0)
		{
			CStageBarCodeReader *ptrBarCodeReader;
			ptrBarCodeReader = new CStageBarCodeReader(this);
			ptrBarCodeReader->m_type = YO_BAR_CODE_READER;
			ptrBarCodeReader->YoInitDevice((CStageDevice *)ptrBarCodeReader);
			sprintf(ptrBarCodeReader->m_name, "%s", deviceName);
			if (ptrBarCodeReader->YoReadBarCodeReader(fp, ptrBarCodeReader) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrBarCodeReader;
		}
		else if (strcmp(command, "SCALE") == 0)
		{
			CStageScale *ptrScale;
			ptrScale = new CStageScale(this);
			ptrScale->m_type = YO_SCALE;
			ptrScale->YoInitDevice((CStageDevice *)ptrScale);
			sprintf(ptrScale->m_name, "%s", deviceName);
			if (ptrScale->YoReadScale(fp, ptrScale) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrScale;
		}
		else if (strcmp(command, "TRACK") == 0)
		{
			CStageDevice *ptrDevice;
			ptrDevice = new CStageDevice(this);
			ptrDevice->m_type = YO_TRACK;
			ptrDevice->YoInitDevice(ptrDevice);
			sprintf(ptrDevice->m_name, "%s", deviceName);
			if (ptrDevice->YoReadDevice(fp, ptrDevice) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrDevice;
		}
		else if (strcmp(command, "TRAIN") == 0)
		{
			CStageTrain *ptrTrain;
			ptrTrain = new CStageTrain(this);
			ptrTrain->m_type = YO_TRAIN;
			ptrTrain->YoInitDevice((CStageDevice *)ptrTrain);
			sprintf(ptrTrain->m_name, "%s", deviceName);
			if (ptrTrain->YoReadTrain(fp, ptrTrain) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrTrain;
		}
		else if (strcmp(command, "CONVEYOR") == 0)
		{
			CStageConveyor *ptrConveyor;
			ptrConveyor = new CStageConveyor(this);
			ptrConveyor->m_type = YO_CONVEYOR;
			ptrConveyor->YoInitDevice((CStageDevice *)ptrConveyor);
			sprintf(ptrConveyor->m_name, "%s", deviceName);
			if (ptrConveyor->YoReadConveyor(fp, ptrConveyor) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrConveyor;
		}
		else if (strcmp(command, "CONVEYOR_PALLET") == 0)
		{
			CStageConveyorPallet *ptrConveyorPallet;
			ptrConveyorPallet = new CStageConveyorPallet(this);
			ptrConveyorPallet->m_type = YO_CONVEYOR_PALLET;
			ptrConveyorPallet->YoInitDevice((CStageDevice *)ptrConveyorPallet);
			sprintf(ptrConveyorPallet->m_name, "%s", deviceName);
			if (ptrConveyorPallet->YoReadConveyorPallet(fp, ptrConveyorPallet) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrConveyorPallet;
		}
		else if (strcmp(command, "CAMERA") == 0)
		{
			CStageCamera *ptrCamera;
			ptrCamera = new CStageCamera(this);
			ptrCamera->m_type = YO_CAMERA;
			ptrCamera->YoInitDevice((CStageDevice *)ptrCamera);
			sprintf(ptrCamera->m_name, "%s", deviceName);
			if (ptrCamera->YoReadCamera(fp, ptrCamera) == FALSE)
			{
				return FALSE;
			}
			m_currentDevice = ptrCamera;
		}
		else if (strcmp(command, "PART") == 0)
		{
			CStagePart *ptrPart;
			ptrPart = new CStagePart(this);
			ptrPart->YoInitPart(ptrPart);
			ptrPart->m_displayListID = YoGetNewDisplayListID(ptrPart, NULL);
			if (ptrPart->YoReadPart(fp, ptrPart) == FALSE)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CStageDoc::YoCloneDevice(char *deviceName)
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	BOOL			done = FALSE;
	int				i;
	int				j;
	CStageDevice	*ptrDevice;
	CStagePart		*ptrPart;
	CStagePart		*curPart = m_currentDevice->m_ptrPart;
	CStageStack		*partStack = NULL;
	CStageVertexList *curPartVertexList = NULL;
	CStageVertexList *ptrVertexList = NULL;
	CStageVertexList *prevVertexList = NULL;
	CStagePolygonList *curPartPolygonList = NULL;
	CStagePolygonList *ptrPolygonList = NULL;
	CStagePolygonList *prevPolygonList = NULL;
	CStagePolygon *curPolygon = NULL;
	CStagePolygon *prevPolygon = NULL;
	CStagePolygon *ptrPolygon = NULL;
	CStageVertices *curPartVertices = NULL;
	CStageVertices *ptrVertices = NULL;
	CStageVertices *prevVertices = NULL;
	CStageNormals *curPartNormals = NULL;
	CStageNormals *ptrNormals = NULL;
	CStageNormals *prevNormals = NULL;
	CStageTextureCoords *curPartTextureCoords = NULL;
	CStageTextureCoords *ptrTextureCoords = NULL;
	CStageTextureCoords *prevTextureCoords = NULL;
	GLdouble m[16];

	if (m_currentDevice->m_type == YO_LIGHT)
	{
		ptrDevice = new CStageLight(this);
	}
	else if (m_currentDevice->m_type == YO_ROBOT6)
	{
		ptrDevice = new CStageRobot6(this);
	}
	else if (m_currentDevice->m_type == YO_ROTARY_TABLE)
	{
		ptrDevice = new CStageRotaryTable(this);
	}
	else if (m_currentDevice->m_type == YO_CAMERA)
	{
		ptrDevice = new CStageCamera(this);
	}
	else if (m_currentDevice->m_type == YO_GRIPPER)
	{
		ptrDevice = new CStageGripper(this);
	}
	else if (m_currentDevice->m_type == YO_BARRETT_HAND)
	{
		ptrDevice = new CStageBarrettHand(this);
	}
	else if (m_currentDevice->m_type == YO_BAR_CODE_READER)
	{
		ptrDevice = new CStageBarCodeReader(this);
	}
	else if (m_currentDevice->m_type == YO_SCALE)
	{
		ptrDevice = new CStageScale(this);
	}
	else if (m_currentDevice->m_type == YO_TRAIN)
	{
		ptrDevice = new CStageTrain(this);
	}
	else if (m_currentDevice->m_type == YO_CONVEYOR)
	{
		ptrDevice = new CStageConveyor(this);
	}
	else if (m_currentDevice->m_type == YO_CONVEYOR_PALLET)
	{
		ptrDevice = new CStageConveyorPallet(this);
	}
	else
	{
		ptrDevice = new CStageDevice(this);
	}
	ptrDevice->m_type = m_currentDevice->m_type;
	ptrDevice->YoInitDevice(ptrDevice);

	sprintf(ptrDevice->m_name, "%s", deviceName);
	YoDeviceHashInstall(ptrDevice);
	//sprintf(ptrDevice->m_parent, "%s", m_currentDevice->m_parent);
	sprintf(ptrDevice->m_parent, "NONE");
	ptrDevice->m_visible = m_currentDevice->m_visible;
	ptrDevice->m_mass = m_currentDevice->m_mass;
	sprintf(ptrDevice->m_barCode, "%s", m_currentDevice->m_barCode);
	for (i = 0; i < 3; i++)
	{
		ptrDevice->m_min[i] = m_currentDevice->m_min[i];
		ptrDevice->m_max[i] = m_currentDevice->m_max[i];
		ptrDevice->m_scale[i] = m_currentDevice->m_scale[i];
	}

	if (ptrDevice->m_type == YO_LIGHT)
	{
		//((CStageLight *)ptrDevice)->m_enabled = ((CStageLight *)m_currentDevice)->m_enabled;
		((CStageLight *)ptrDevice)->m_pointSource = ((CStageLight *)m_currentDevice)->m_pointSource;

		// if (((CStageLight *)ptrDevice)->m_enabled)
		{
			((CStageLight *)ptrDevice)->YoGetLight();
		}
		((CStageLight *)ptrDevice)->m_intensity = ((CStageLight *)m_currentDevice)->m_intensity;
		/***
		for (i = 0; i < 4; i++)
		{
			((CStageLight *)ptrDevice)->m_ambient[i] = ((CStageLight *)m_currentDevice)->m_ambient[i];
			((CStageLight *)ptrDevice)->m_diffuse[i] = ((CStageLight *)m_currentDevice)->m_diffuse[i];
			((CStageLight *)ptrDevice)->m_specular[i] = ((CStageLight *)m_currentDevice)->m_specular[i];
			((CStageLight *)ptrDevice)->m_position[i] = ((CStageLight *)m_currentDevice)->m_position[i];
		}
		((CStageLight *)ptrDevice)->m_spotExponent = ((CStageLight *)m_currentDevice)->m_spotExponent;
		***/
		((CStageLight *)ptrDevice)->m_spotCutoff = ((CStageLight *)m_currentDevice)->m_spotCutoff;
		for (i = 0; i < 3; i++)
		{
			((CStageLight *)ptrDevice)->m_attenuation[i] = ((CStageLight *)m_currentDevice)->m_attenuation[i];
		}
	}
	else if (ptrDevice->m_type == YO_ROBOT6)
	{
		for (i = 1; i <= 6; i++)
		{
			((CStageRobot6 *)ptrDevice)->m_j[i] = ((CStageRobot6 *)m_currentDevice)->m_j[i];
			((CStageRobot6 *)ptrDevice)->m_jMaxAccelMaxSpeed[i][0] = ((CStageRobot6 *)m_currentDevice)->m_jMaxAccelMaxSpeed[i][0];
			((CStageRobot6 *)ptrDevice)->m_jMaxAccelMaxSpeed[i][1] = ((CStageRobot6 *)m_currentDevice)->m_jMaxAccelMaxSpeed[i][1];
			((CStageRobot6 *)ptrDevice)->m_jMinAccelTime[i] = ((CStageRobot6 *)m_currentDevice)->m_jMinAccelTime[i];
			((CStageRobot6 *)ptrDevice)->m_jMinMax[i][0] = ((CStageRobot6 *)m_currentDevice)->m_jMinMax[i][0];
			((CStageRobot6 *)ptrDevice)->m_jMinMax[i][1] = ((CStageRobot6 *)m_currentDevice)->m_jMinMax[i][1];
			((CStageRobot6 *)ptrDevice)->m_home[i] = ((CStageRobot6 *)m_currentDevice)->m_home[i];
			((CStageRobot6 *)ptrDevice)->m_jFinal[i] = ((CStageRobot6 *)m_currentDevice)->m_jFinal[i];
		}
		for (i = 0; i < 6; i++)
		{
			((CStageRobot6 *)ptrDevice)->m_tcpOffset[i] = ((CStageRobot6 *)m_currentDevice)->m_tcpOffset[i];
			((CStageRobot6 *)ptrDevice)->m_cartesianSpace[i] = ((CStageRobot6 *)m_currentDevice)->m_cartesianSpace[i];
		}
		((CStageRobot6 *)ptrDevice)->m_speed = ((CStageRobot6 *)m_currentDevice)->m_speed;
		((CStageRobot6 *)ptrDevice)->m_accelTime = ((CStageRobot6 *)m_currentDevice)->m_accelTime;
		((CStageRobot6 *)ptrDevice)->m_accelDistance = ((CStageRobot6 *)m_currentDevice)->m_accelDistance;
		((CStageRobot6 *)ptrDevice)->m_totalDistance = ((CStageRobot6 *)m_currentDevice)->m_totalDistance;
		((CStageRobot6 *)ptrDevice)->m_minAccelTime = ((CStageRobot6 *)m_currentDevice)->m_minAccelTime;
		((CStageRobot6 *)ptrDevice)->m_jointInterpolation = ((CStageRobot6 *)m_currentDevice)->m_jointInterpolation;
		((CStageRobot6 *)ptrDevice)->m_timeOfMove = 0.0;
		((CStageRobot6 *)ptrDevice)->m_moving = FALSE;
		((CStageRobot6 *)ptrDevice)->m_lefty = ((CStageRobot6 *)m_currentDevice)->m_lefty;
		((CStageRobot6 *)ptrDevice)->m_elbowUp = ((CStageRobot6 *)m_currentDevice)->m_elbowUp;
		((CStageRobot6 *)ptrDevice)->m_wristFlipped = ((CStageRobot6 *)m_currentDevice)->m_wristFlipped;
	}
	else if (ptrDevice->m_type == YO_ROTARY_TABLE)
	{
		((CStageRotaryTable *)ptrDevice)->m_acceleration = ((CStageRotaryTable *)m_currentDevice)->m_acceleration;
		((CStageRotaryTable *)ptrDevice)->m_currentPosition = ((CStageRotaryTable *)m_currentDevice)->m_currentPosition;
		((CStageRotaryTable *)ptrDevice)->m_directionPositive = ((CStageRotaryTable *)m_currentDevice)->m_directionPositive;
		((CStageRotaryTable *)ptrDevice)->m_distance = ((CStageRotaryTable *)m_currentDevice)->m_distance;
		((CStageRotaryTable *)ptrDevice)->m_endPosition = ((CStageRotaryTable *)m_currentDevice)->m_endPosition;
		((CStageRotaryTable *)ptrDevice)->m_encoderResolution = ((CStageRotaryTable *)m_currentDevice)->m_encoderResolution;
		((CStageRotaryTable *)ptrDevice)->m_positionAbsolute = ((CStageRotaryTable *)m_currentDevice)->m_positionAbsolute;
		((CStageRotaryTable *)ptrDevice)->m_ptrRotateInfo = NULL;
		((CStageRotaryTable *)ptrDevice)->m_rotating = 0;
		((CStageRotaryTable *)ptrDevice)->m_simRequestDone = TRUE;
		((CStageRotaryTable *)ptrDevice)->m_stoppingTable = FALSE;
		((CStageRotaryTable *)ptrDevice)->m_velocity = ((CStageRotaryTable *)m_currentDevice)->m_velocity;
	}
	else if (ptrDevice->m_type == YO_CAMERA)
	{
		((CStageCamera *)ptrDevice)->m_enabled = FALSE;
		((CStageCamera *)ptrDevice)->m_clipFront = ((CStageCamera *)m_currentDevice)->m_clipFront;
		((CStageCamera *)ptrDevice)->m_clipRear = ((CStageCamera *)m_currentDevice)->m_clipRear;
		((CStageCamera *)ptrDevice)->m_fieldOfView = ((CStageCamera *)m_currentDevice)->m_fieldOfView;
		((CStageCamera *)ptrDevice)->m_fStop = ((CStageCamera *)m_currentDevice)->m_fStop;
	}
	else if (ptrDevice->m_type == YO_GRIPPER)
	{
		((CStageGripper *)ptrDevice)->m_gripping = ((CStageGripper *)m_currentDevice)->m_gripping;
		((CStageGripper *)ptrDevice)->m_typeTranslating = ((CStageGripper *)m_currentDevice)->m_typeTranslating;
		((CStageGripper *)ptrDevice)->m_displacementOpen = ((CStageGripper *)m_currentDevice)->m_displacementOpen;
		((CStageGripper *)ptrDevice)->m_displacementClose = ((CStageGripper *)m_currentDevice)->m_displacementClose;
	}
	else if (ptrDevice->m_type == YO_BARRETT_HAND)
	{
		((CStageBarrettHand *)ptrDevice)->m_gripping = ((CStageBarrettHand *)m_currentDevice)->m_gripping;
		((CStageBarrettHand *)ptrDevice)->m_spreading = FALSE;
		((CStageBarrettHand *)ptrDevice)->m_spread = ((CStageBarrettHand *)m_currentDevice)->m_spread;

		for (i = 0; i < 3; i++)
		{
			((CStageBarrettHand *)ptrDevice)->m_fingerFixed[i] = ((CStageBarrettHand *)m_currentDevice)->m_fingerFixed[i];
			((CStageBarrettHand *)ptrDevice)->m_fingerLeft[i] = ((CStageBarrettHand *)m_currentDevice)->m_fingerLeft[i];
			((CStageBarrettHand *)ptrDevice)->m_fingerRight[i] = ((CStageBarrettHand *)m_currentDevice)->m_fingerRight[i];
		}
		((CStageBarrettHand *)ptrDevice)->m_velocity = ((CStageBarrettHand *)m_currentDevice)->m_velocity;
		((CStageBarrettHand *)ptrDevice)->m_moving = FALSE;

	}
	else if (ptrDevice->m_type == YO_BAR_CODE_READER)
	{
		((CStageBarCodeReader *)ptrDevice)->m_scanning = FALSE;
		((CStageBarCodeReader *)ptrDevice)->m_scanDistance = YO_SCAN_DISTANCE;
		sprintf(((CStageBarCodeReader *)ptrDevice)->m_barCode, "000000000000");
	}
	else if (ptrDevice->m_type == YO_SCALE)
	{
		((CStageScale *)ptrDevice)->m_weighing = FALSE;
		((CStageScale *)ptrDevice)->m_units = ((CStageScale *)m_currentDevice)->m_units;
		((CStageScale *)ptrDevice)->m_mass = 0.0f;
	}
	else if (ptrDevice->m_type == YO_TRAIN)
	{
		((CStageTrain *)ptrDevice)->m_ptrTrackSeg = ((CStageTrain *)m_currentDevice)->m_ptrTrackSeg;
		//((CStageTrain *)ptrDevice)->m_attachTrackSeg = 1;
		//((CStageTrain *)ptrDevice)->m_attachRelativePosition = 0.0f;
		((CStageTrain *)ptrDevice)->m_moving = FALSE;
		((CStageTrain *)ptrDevice)->m_ptrTrackSegEnd = NULL;
		((CStageTrain *)ptrDevice)->m_relativePositionEnd = 0.0f;
		//((CStageTrain *)ptrDevice)->m_endPosition[0] = 0.0f;
		//((CStageTrain *)ptrDevice)->m_endPosition[1] = 0.0f;
		//((CStageTrain *)ptrDevice)->m_currentPosition[0] = ((CStageTrain *)m_currentDevice)->m_currentPosition[0];
		//((CStageTrain *)ptrDevice)->m_currentPosition[1] = ((CStageTrain *)m_currentDevice)->m_currentPosition[1];
		((CStageTrain *)ptrDevice)->m_relativePosition = ((CStageTrain *)m_currentDevice)->m_relativePosition;
		((CStageTrain *)ptrDevice)->m_velocity = ((CStageTrain *)m_currentDevice)->m_velocity;
		((CStageTrain *)ptrDevice)->m_acceleration = ((CStageTrain *)m_currentDevice)->m_acceleration;
		//((CStageTrain *)ptrDevice)->m_heading = ((CStageTrain *)m_currentDevice)->m_heading;
		((CStageTrain *)ptrDevice)->m_trackOrientation = ((CStageTrain *)m_currentDevice)->m_trackOrientation;
		((CStageTrain *)ptrDevice)->m_stoppingTrain = FALSE;
		((CStageTrain *)ptrDevice)->m_simRequestDone = FALSE;
	}
	else if (ptrDevice->m_type == YO_CONVEYOR)
	{
		((CStageConveyor *)m_currentDevice)->YoClone((CStageConveyor *)ptrDevice);
	}


	YoInsertDevice(ptrDevice, NULL);

	partStack = NULL;

	if (curPart == NULL)
	{
		return;
	}

	while (done == FALSE)
	{

		ptrPart = new CStagePart(this);
		ptrPart->YoInitPart(ptrPart);

		if (ptrDevice->m_type == YO_CONVEYOR)
		{
			((CStageConveyor *)ptrDevice)->YoClone(curPart, ptrPart);
		}
		//sprintf(ptrPart->m_partFile, "%s", curPart->m_partFile);
		ptrPart->m_displayListID = YoGetNewDisplayListID(ptrPart, NULL);
		ptrPart->m_numberPolygons = curPart->m_numberPolygons;
		ptrPart->m_numberVertices = curPart->m_numberVertices;
		//ptrPart->m_wireframeDisplayListID = YoGetNewDisplayListID((CStagePart *)NULL);

/****
		::glNewList(ptrPart->m_displayListID, GL_COMPILE);
		::glCallList(curPart->m_displayListID);
		::glEndList();
		// display list for wireframe
		::glNewList(ptrPart->m_wireframeDisplayListID, GL_COMPILE);
		::glCallList(curPart->m_wireframeDisplayListID);
		::glEndList();
****/

		//::glNewList(ptrPart->m_displayListID, GL_COMPILE);
		//ptrPart->YoReadPartFile(ptrPart->m_partFile, 0);
		// display list for wireframe
		//::glNewList(ptrPart->m_wireframeDisplayListID, GL_COMPILE);
		//ptrPart->YoReadPartFile(ptrPart->m_partFile, YO_WIREFRAME);


		prevVertexList = NULL;
		for (curPartVertexList = curPart->m_vertexList; curPartVertexList != NULL;
			curPartVertexList = curPartVertexList->m_next)
		{
			ptrVertexList = new CStageVertexList();
			if (prevVertexList == NULL)
			{
				ptrPart->m_vertexList = ptrVertexList;
			}
			else
			{
				prevVertexList->m_next = ptrVertexList;
			}
			prevVertexList = ptrVertexList;

			for (i = 0; i < 20; i++)
			{
				ptrVertexList->m_vertex[i][0] = curPartVertexList->m_vertex[i][0];
				ptrVertexList->m_vertex[i][1] = curPartVertexList->m_vertex[i][1];
				ptrVertexList->m_vertex[i][2] = curPartVertexList->m_vertex[i][2];

				prevPolygon = NULL;
				for (curPolygon = curPartVertexList->m_polygon[i]; curPolygon != NULL;
					curPolygon = curPolygon->m_next)
				{
					ptrPolygon = new CStagePolygon();
					ptrPolygon->m_polygon = curPolygon->m_polygon;
					if (prevPolygon == NULL)
					{
						ptrVertexList->m_polygon[i] = ptrPolygon;	
					}
					else
					{
						prevPolygon->m_next = ptrPolygon;
					}
					prevPolygon = ptrPolygon;
				}
			}
		}

		prevPolygonList = NULL;
		for (i = 0; i < curPart->m_numberPolygons; i++)
		{
			if (i % 10 == 0)
			{
				ptrPolygonList = new CStagePolygonList();
				if (prevPolygonList == NULL)
				{
					ptrPart->m_polygonList = ptrPolygonList;
					curPartPolygonList = curPart->m_polygonList;
				}
				else
				{
					prevPolygonList->m_next = ptrPolygonList;
					curPartPolygonList = curPartPolygonList->m_next;
				}
				prevPolygonList = ptrPolygonList;
			}

			ptrPolygonList->m_numberSides[i % 10]
				= curPartPolygonList->m_numberSides[i % 10];
			ptrPolygonList->m_normalFlatShaded[i % 10][0]
				= curPartPolygonList->m_normalFlatShaded[i % 10][0];
			ptrPolygonList->m_normalFlatShaded[i % 10][1]
				= curPartPolygonList->m_normalFlatShaded[i % 10][1];
			ptrPolygonList->m_normalFlatShaded[i % 10][2]
				= curPartPolygonList->m_normalFlatShaded[i % 10][2];
			ptrPolygonList->m_texture[i % 10] = NULL;
			ptrPolygonList->m_origTexture[i % 10] = NULL;
			ptrPolygonList->m_textureModified[i % 10] = NULL;
			ptrPolygonList->m_textureStartVertex[i % 10] = 0;
			ptrPolygonList->m_origTextureStartVertex[i % 10] = 0;

			prevVertices = NULL;
			prevNormals = NULL;
			for (j = 0; j < ptrPolygonList->m_numberSides[i % 10]; j++)
			{
				if (j % 4 == 0)
				{
					ptrVertices = new CStageVertices();
					if (prevVertices == NULL)
					{
						ptrPolygonList->m_vertices[i % 10] = ptrVertices;
						curPartVertices = curPartPolygonList->m_vertices[i % 10];
					}
					else
					{
						prevVertices->m_next = ptrVertices;
						curPartVertices = curPartVertices->m_next;
					}
					prevVertices = ptrVertices;

					ptrNormals = new CStageNormals();
					if (prevNormals == NULL)
					{
						ptrPolygonList->m_normals[i % 10] = ptrNormals;
						curPartNormals = curPartPolygonList->m_normals[i % 10];
					}
					else
					{
						prevNormals->m_next = ptrNormals;
						curPartNormals = curPartNormals->m_next;
					}
					prevNormals = ptrNormals;
				}

				ptrVertices->m_vertex[j % 4] = curPartVertices->m_vertex[j % 4];
				ptrNormals->m_normal[j % 4][0] = curPartNormals->m_normal[j % 4][0];
				ptrNormals->m_normal[j % 4][1] = curPartNormals->m_normal[j % 4][1];
				ptrNormals->m_normal[j % 4][2] = curPartNormals->m_normal[j % 4][2];
			}

			if (curPartPolygonList->m_texture[i % 10] != NULL)
			{
				ptrPolygonList->m_texture[i % 10] = new CStageTexture();
				ptrPolygonList->m_texture[i % 10]->m_textureMode
					= curPartPolygonList->m_texture[i % 10]->m_textureMode;
				sprintf(ptrPolygonList->m_texture[i % 10]->m_DIBFileName,
					"%s", curPartPolygonList->m_texture[i % 10]->m_DIBFileName);
				ptrPolygonList->m_texture[i % 10]->m_RGBImage = new CGLImage();
				ptrPolygonList->m_texture[i % 10]->m_RGBImage->
					SpecialCreate(curPartPolygonList->m_texture[i % 10]->m_RGBImage->m_iWidth,
					curPartPolygonList->m_texture[i % 10]->m_RGBImage->m_iHeight,
					curPartPolygonList->m_texture[i % 10]->m_RGBImage->m_pBits);

				ptrPolygonList->m_textureStartVertex[i % 10] = 0;
				prevTextureCoords = NULL;
				for (j = 0; j < ptrPolygonList->m_numberSides[i % 10]; j++)
				{
					if (j % 4 == 0)
					{
						ptrTextureCoords = new CStageTextureCoords();
						if (prevTextureCoords == NULL)
						{
							ptrPolygonList->m_texture[i % 10]->m_textureCoords = ptrTextureCoords;
							curPartTextureCoords = curPartPolygonList->m_texture[i % 10]->m_textureCoords;
						}
						else
						{
							prevTextureCoords->m_next = ptrTextureCoords;
							curPartTextureCoords = curPartTextureCoords->m_next;
						}
						prevTextureCoords = ptrTextureCoords;
					}

					ptrTextureCoords->m_textureCoords[j % 4][0]
						= curPartTextureCoords->m_textureCoords[j % 4][0];
					ptrTextureCoords->m_textureCoords[j % 4][1]
						= curPartTextureCoords->m_textureCoords[j % 4][1];
				}
			}
		}

		//ptrPart->m_displayType = curPart->m_displayType;
		sprintf(ptrPart->m_deviceName, "%s", deviceName);
		sprintf(ptrPart->m_partName, "%s", curPart->m_partName);
		sprintf(ptrPart->m_partParent, "%s", curPart->m_partParent);
		ptrPart->m_txyz = curPart->m_txyz;

		YoInsertPart(ptrDevice, ptrPart);

		for (i = 0; i < 3; i++)
		{
			ptrPart->m_translate[i] = curPart->m_translate[i];
			ptrPart->m_rotate[i] = curPart->m_rotate[i];
			ptrPart->m_min[i] = curPart->m_min[i];
			ptrPart->m_max[i] = curPart->m_max[i];
		}
		if (ptrPart == ptrDevice->m_ptrPart)
		{
			YoModelMatrixOfCurrentPart(m);
			ptrDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
			YoTranslateRotateValues(m,
				ptrDevice->m_ptrPart->m_translate,
				ptrDevice->m_ptrPart->m_rotate);
			for (i = 0; i < 3; i++)
			{
				ptrDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}

			ptrPart->m_translate[0]
				+= ((fabs(ptrPart->m_max[0] - ptrPart->m_min[0])
				+ fabs(ptrPart->m_max[1] - ptrPart->m_min[1])
				+ fabs(ptrPart->m_max[2] - ptrPart->m_min[2]))
				/ 3.0);
			ptrPart->m_translate[1]
				+= ((fabs(ptrPart->m_max[0] - ptrPart->m_min[0])
				+ fabs(ptrPart->m_max[1] - ptrPart->m_min[1])
				+ fabs(ptrPart->m_max[2] - ptrPart->m_min[2]))
				/ 3.0);
		}

		ptrPart->m_renderMode = curPart->m_renderMode;
		for (i = 0; i < 4; i++)
		{
			ptrPart->m_ambient[i] = curPart->m_ambient[i];
			ptrPart->m_diffuse[i] = curPart->m_diffuse[i];
			ptrPart->m_specular[i] = curPart->m_specular[i];
			ptrPart->m_emission[i] = curPart->m_emission[i];
			ptrPart->m_wireframe[i] = curPart->m_wireframe[i];
		}
		ptrPart->m_shininess = curPart->m_shininess;
		/***
		ptrPart->m_textureScale = curPart->m_textureScale;
		ptrPart->m_textureAlpha = curPart->m_textureAlpha;
		sprintf(ptrPart->m_textureName, "%s", curPart->m_textureName);
		ptrPart->m_texture = curPart->m_texture;
		ptrPart->m_textureWrap = curPart->m_textureWrap;
		ptrPart->m_textureTEV = curPart->m_textureTEV;
		for (i = 0; i < 4; i++)
		{
			ptrPart->m_sParameter[i] = curPart->m_sParameter[i];
			ptrPart->m_tParameter[i] = curPart->m_tParameter[i];
		}
		ptrPart->m_sMode = curPart->m_sMode;
		ptrPart->m_sMode = curPart->m_sMode;
		***/
		ptrPart->m_motion = NULL;
		ptrPart->m_effect = NULL;
		ptrPart->m_score = NULL;

		if (curPart->m_down != NULL)
		{
			if (curPart->m_right != NULL)
			{
				YoPushPart(&partStack, curPart->m_right);
			}
			curPart = curPart->m_down;
		}
		else if (curPart->m_right != NULL)
		{
			curPart = curPart->m_right;
		}
		else if (partStack != NULL)
		{
			curPart = YoPopPart(&partStack);
		}
		else 
		{
			done = TRUE;
		}

	}  //end while (!done)


	m_currentDevice = ptrDevice;
	m_currentPart = m_currentDevice->m_ptrPart;

	//sprintf(s, "Device: %s   Part: %s",
	//	m_currentDevice->m_name, m_currentPart->m_partName);
	//YoMessage(s);

	pView->YoRender(YO_RENDER_LIGHT);
	pView->YoRender(YO_RENDER_FULL);
	//yo_update_part();
	return;

}


void CStageDoc::YoGetUniqueDeviceName(char *deviceName)
{
	size_t k;
	int i;
	int count = 1;
	char s[64];
	char *t;

	k = strlen(deviceName);
	for (k = strlen(deviceName) - 1; deviceName[k] >= '0' && deviceName[k] <= '9'; k--);
	if (k != strlen(deviceName) - 1)
	{
		t = &deviceName[k + 1];
		sscanf(t, "%d", &count);
		deviceName[k + 1] = '\0';
	}
	sprintf(s, "%s", deviceName);



	for (i = count;;i++)
	{
		sprintf(deviceName, "%s%d", s, i);
		TRACE1("%s\n", deviceName);
		if (YoDeviceHashLookup(deviceName) == NULL)
		{
			return;
		}
	}
}


void CStageDoc::YoGetUniquePathName(char *pathName)
{
	size_t k;
	char t;

	for (t = 'a'; t < 'z'; t++)
	{
		sprintf(pathName, "%c", t);
		if (YoPathHashLookup(pathName) == NULL)
		{
			return;
		}
	}

	k = strlen(pathName);
	pathName[k] = 'x';
	pathName[k + 1] = '\0';

	return;
}


void CStageDoc::YoMessage(char *s)
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CWnd *pCBox;

	TRACE1("YoMessage(%s)\n", s);

	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_MESSAGE);
	pCBox->SetWindowText(s);
	//pCBox->UpdateWindow();

	return;
}



BOOL CStageDoc::YoModelMatrixOfCurrentPart(GLdouble m[16])
// finds model matrix of the current part in world coordinates
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CStageDevice	*ptrDevice = m_deviceList;
	CStagePart *ptrPart;
	BOOL			done = FALSE;
	BOOL	pDone = FALSE;
	GLdouble currentModelView[16];
	GLint stackDepth;
	GLint i;
	GLint j = 1;
	

	if (m_currentDevice == NULL)
	{
		return FALSE;
	}

	::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &stackDepth);
	// 99.08.18 BUG in this function perhaps
	CStageStack *ptrDeviceStack;
	ptrDeviceStack = m_deviceStack;
	m_deviceStack = NULL;

	::glMatrixMode(GL_MODELVIEW);
	::glGetDoublev(GL_MODELVIEW_MATRIX, currentModelView);
	::glLoadIdentity();

	while (!done)
	{
		::glPushMatrix();
		if (ptrDevice->m_attachedFromPart != NULL)
		{
			::glMultMatrixd(ptrDevice->m_mAttach);
		}
		pView->YoTxyz(ptrDevice->m_ptrPart,
			ptrDevice->m_ptrPart->m_translate, ptrDevice->m_ptrPart->m_rotate);
		if (ptrDevice == m_currentDevice)
		{
			if (m_currentPart == NULL)
			{
				return FALSE;
			}
			ptrPart = ptrDevice->m_ptrPart;
			while (!pDone)
			{
				if (ptrPart != ptrDevice->m_ptrPart)
				{
					::glPushMatrix();
					pView->YoTxyz(ptrPart, ptrPart->m_translate, ptrPart->m_rotate);
					if (ptrDevice->m_type == YO_ROBOT6)
					{
						((CStageRobot6 *)ptrDevice)->YoRotateJoint(ptrPart);
					}				
					else if (ptrDevice->m_type == YO_ROTARY_TABLE)
					{
						((CStageRotaryTable *)ptrDevice)->YoRotateTable(ptrPart);
					}
					else if (ptrDevice->m_type == YO_BARRETT_HAND)
					{
						((CStageBarrettHand *)ptrDevice)->YoPositionFinger(ptrPart);
					}
					else if (ptrDevice->m_type == YO_GRIPPER)
					{
						((CStageGripper *)ptrDevice)->YoPositionFinger(ptrPart);

						//if (ptrDevice->m_ptrPart != NULL 
						//	&& ptrDevice->m_ptrPart->m_down != NULL
						//	&& m_currentPart != ptrDevice->m_ptrPart)
						//{
						//	for (ptrGripperPart = ptrDevice->m_ptrPart->m_down;
						//		ptrGripperPart != NULL && ptrGripperPart != m_currentPart;
						//		ptrGripperPart = ptrGripperPart->m_right);
						//	if (ptrGripperPart != NULL)
						//	{
						//		::glPushMatrix();
						//		if (((CStageGripper *)ptrDevice)->m_typeTranslating == TRUE)
						//		{
						//			// translate fingers along x axis
						//			if (((CStageGripper *)ptrDevice)->m_gripping == TRUE)
						//			{
						//				::glTranslated(-((CStageGripper *)ptrDevice)->m_displacementClose, 0.0f, 0.0f);
						//			}
						//			else
						//			{
						//				::glTranslated(((CStageGripper *)ptrDevice)->m_displacementOpen, 0.0f, 0.0f);
						//			}
						//		}
						//		else
						//		{
						//			// rotate fingers around y axis
						//			if (((CStageGripper *)ptrDevice)->m_gripping == TRUE)
						//			{
						//				::glRotated(-((CStageGripper *)ptrDevice)->m_displacementClose, 0.0, 1.0, 0.0);
						//			}
						//			else
						//			{
						//				::glRotated(((CStageGripper *)ptrDevice)->m_displacementOpen, 0.0, 1.0, 0.0);
						//			}
						//		}
						//		::glPopMatrix();
						//	}
						//}
					}
				}
				if (ptrPart == m_currentPart)
				{
					::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					YoFreePart();
					//YoFreeDevice();

					::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &i);
					while(i > stackDepth)
					{
						::glPopMatrix();
						//YoFreeDevice(); //*
						i--;
					}
					YoFreeDevice();
					::glLoadIdentity();
					::glLoadMatrixd(currentModelView);
					m_deviceStack = ptrDeviceStack; //*

					return TRUE;
				}

				if (ptrPart->m_down != NULL)
				{
					if (ptrPart->m_right != NULL)
					{
						YoPushPart(ptrPart->m_right);
					}
					else
					{
						YoPushPart(NULL);
					}
					ptrPart = ptrPart->m_down;
				}
				else if (ptrPart->m_right != NULL)
				{
					ptrPart = ptrPart->m_right;
					glPopMatrix();
				}
				else if (!YoAllStackPartsNull())
				{
					glPopMatrix();
					glPopMatrix();
					while ((ptrPart = YoPopPart()) == NULL)
					{
						glPopMatrix();
					}
				}
				else
				{
					while (m_partStack != NULL
						&& (ptrPart = YoPopPart()) == NULL)
					{
						glPopMatrix();
					}
					pDone = TRUE;
					return FALSE;
				}
			}
		}

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			else
			{
				YoPushDevice(NULL);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
			glPopMatrix();
		}
		else if (!YoAllStackDevicesNull())
		{
			glPopMatrix();
			glPopMatrix();
			while ((ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
		}
		else
		{
			glPopMatrix();
			while (m_deviceStack != NULL
				&& (ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
			done = TRUE;
		}
	} // end while (!done)

	return FALSE;
}


BOOL CStageDoc::YoModelMatrixOfCurrentTag()
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CStageDevice	*ptrDevice = m_deviceList;
	CStagePart *ptrPart;
	BOOL	done = FALSE;
	BOOL	pDone = FALSE;
	GLdouble currentModelView[16];
	GLint stackDepth;
	GLint i;
	
	::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &stackDepth);
	m_deviceStack = NULL;

	if (m_currentDevice == NULL || m_currentTag == NULL)
	{
		return FALSE;
	}

	::glMatrixMode(GL_MODELVIEW);
	::glGetDoublev(GL_MODELVIEW_MATRIX, currentModelView);
	::glLoadIdentity();

	while (!done)
	{
		::glPushMatrix();
		if (ptrDevice->m_attachedFromPart != NULL)
		{
			::glMultMatrixd(ptrDevice->m_mAttach);
		}
		pView->YoTxyz(ptrDevice->m_ptrPart, ptrDevice->m_ptrPart->m_translate, ptrDevice->m_ptrPart->m_rotate);
		ptrPart = ptrDevice->m_ptrPart;
		pDone = FALSE;
		while (!pDone)
		{
			if (ptrPart != ptrDevice->m_ptrPart)
			{
				::glPushMatrix();
				pView->YoTxyz(ptrPart, ptrPart->m_translate, ptrPart->m_rotate);
				if (ptrDevice->m_type == YO_ROBOT6)
				{
					((CStageRobot6 *)ptrDevice)->YoRotateJoint(ptrPart);
				}
				else if (ptrDevice->m_type == YO_ROTARY_TABLE)
				{
					((CStageRotaryTable *)ptrDevice)->YoRotateTable(ptrPart);
				}
				else if (ptrDevice->m_type == YO_BARRETT_HAND)
				{
					((CStageBarrettHand *)ptrDevice)->YoPositionFinger(ptrPart);
				}
				else if (ptrDevice->m_type == YO_GRIPPER)
				{
					((CStageGripper *)ptrDevice)->YoPositionFinger(ptrPart);

					//if (ptrDevice->m_ptrPart != NULL 
					//	&& ptrDevice->m_ptrPart->m_down != NULL
					//	&& m_currentPart != ptrDevice->m_ptrPart)
					//{
					//	for (ptrGripperPart = ptrDevice->m_ptrPart->m_down;
					//		ptrGripperPart != NULL && ptrGripperPart != m_currentPart;
					//		ptrGripperPart = ptrGripperPart->m_right);
					//	if (ptrGripperPart != NULL)
					//	{
					//		::glPushMatrix();
					//		if (((CStageGripper *)ptrDevice)->m_typeTranslating == TRUE)
					//		{
					//			// translate fingers along x axis
					//			if (((CStageGripper *)ptrDevice)->m_gripping == TRUE)
					//			{
					//				::glTranslated(-((CStageGripper *)ptrDevice)->m_displacementClose, 0.0f, 0.0f);
					//			}
					//			else
					//			{
					//				::glTranslated(((CStageGripper *)ptrDevice)->m_displacementOpen, 0.0f, 0.0f);
					//			}
					//		}
					//		else
					//		{
					//			// rotate fingers around y axis
					//			if (((CStageGripper *)ptrDevice)->m_gripping == TRUE)
					//			{
					//				::glRotated(-((CStageGripper *)ptrDevice)->m_displacementClose, 0.0, 1.0, 0.0);
					//			}
					//			else
					//			{
					//				::glRotated(((CStageGripper *)ptrDevice)->m_displacementOpen, 0.0, 1.0, 0.0);
					//			}
					//		}
					//		::glPopMatrix();
					//	}
					//}
				}
			}
			if (ptrPart == m_currentTag->m_ptrPath->m_ptrPart)
			{
				::glTranslated(m_currentTag->m_translate[0],
					m_currentTag->m_translate[1], m_currentTag->m_translate[2]);
				::glRotated(m_currentTag->m_rotate[0], 1.0, 0.0, 0.0);
				::glRotated(m_currentTag->m_rotate[1], 0.0, 1.0, 0.0);
				::glRotated(m_currentTag->m_rotate[2], 0.0, 0.0, 1.0);
				::glGetDoublev(GL_MODELVIEW_MATRIX, m_mTag);
				YoFreePart();
				YoFreeDevice();

				::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &i);
				while(i > stackDepth)
				{
					::glPopMatrix();
					i--;
				}
				::glLoadIdentity();
				::glLoadMatrixd(currentModelView);

				return TRUE;
			}

			if (ptrPart->m_down != NULL)
			{
				if (ptrPart->m_right != NULL)
				{
					YoPushPart(ptrPart->m_right);
				}
				else
				{
					YoPushPart(NULL);
				}
				ptrPart = ptrPart->m_down;
			}
			else if (ptrPart->m_right != NULL)
			{
				ptrPart = ptrPart->m_right;
				glPopMatrix();
			}
			else if (!YoAllStackPartsNull())
			{
				glPopMatrix();
				glPopMatrix();
				while ((ptrPart = YoPopPart()) == NULL)
				{
					glPopMatrix();
				}
			}
			else
			{
				while (m_partStack != NULL
					&& (ptrPart = YoPopPart()) == NULL)
				{
					glPopMatrix();
				}
				pDone = TRUE;
			}
		}

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			else
			{
				YoPushDevice(NULL);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
			glPopMatrix();
		}
		else if (!YoAllStackDevicesNull())
		{
			glPopMatrix();
			glPopMatrix();
			while ((ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
		}
		else
		{
			glPopMatrix();
			while (m_deviceStack != NULL
				&& (ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
			done = TRUE;
		}
	} // end while (!done)

	return FALSE;
}


void CStageDoc::YoDetachDevice(void)

// detaches member variable m_currentDevice from a doubly linked list 
// and relinks the remaining devices.  m_currentDevice stands alone
// upon completion of this procedure.

// TO DO: April 97: check transformations and rotations, in particular
// yo_cur_object->down

{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDevice *ptrDevice;
	CStagePart *currentpart;
	BOOL done = FALSE;
	GLdouble m[16];
	int i;

	if (m_currentDevice->m_type == YO_CONVEYOR_PALLET
		&& ((CStageConveyorPallet *)m_currentDevice)->m_ptrSegment != NULL
		&& (ptrDevice = YoDeviceHashLookup(m_currentDevice->m_parent)) != NULL
		&& ptrDevice->m_type == YO_CONVEYOR
		&& (strcmp(m_currentDevice->m_parent, ptrDevice->m_name) == 0))
	{
		((CStageConveyor *)ptrDevice)->YoRemovePallet((CStageConveyorPallet *)m_currentDevice);
	}
	else if (m_currentDevice->m_type == YO_TRAIN)
	{
		((CStageTrain *)m_currentDevice)->m_ptrTrackSeg = NULL;
	}

	currentpart = m_currentPart;
	m_currentPart = m_currentDevice->m_ptrPart;
	YoModelMatrixOfCurrentPart(m);
	m_currentPart->m_txyz = YO_TXYZ_TXYZ;
	YoTranslateRotateValues(m, m_currentPart->m_translate, m_currentPart->m_rotate);
	for (i = 0; i < 3; i++)
	{
		m_currentPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
	}
	m_currentPart = currentpart;


	if (m_currentDevice == m_deviceList && m_currentDevice->m_right == NULL)
	{
		m_deviceList = NULL;
	}
	else if (m_currentDevice == m_deviceList && m_currentDevice->m_right != NULL)
	{
		m_currentDevice->m_right->m_left = NULL;
		m_deviceList = m_currentDevice->m_right;
		m_currentDevice->m_right = NULL;
	}
	else if (m_currentDevice->m_up == NULL)
	{
		if (m_currentDevice->m_attachedFromPart != NULL)
		{
			//for (ptrDevice = m_currentDevice->m_attachedFromPart->m_attachedDevice;
			//	ptrDevice != NULL
			//	&& ptrDevice->m_attachedFromPart != m_currentDevice->m_attachedFromPart;
			//	ptrDevice = ptrDevice->m_right);

			for (ptrDevice = m_currentDevice->m_attachedFromPart->m_attachedDevice;
				ptrDevice != NULL;
				ptrDevice = ptrDevice->m_right)
			{
				if (ptrDevice->m_attachedFromPart == m_currentDevice->m_attachedFromPart
					&& ptrDevice != m_currentDevice)
				{
					break;
				}
			}

			if (ptrDevice != NULL)
			{
				ptrDevice->m_attachedFromPart->m_attachedDevice = ptrDevice;
			}
			else
			{
				m_currentDevice->m_attachedFromPart->m_attachedDevice = NULL;
			}
			m_currentDevice->m_attachedFromPart = NULL;
		}

		m_currentDevice->m_left->m_right = m_currentDevice->m_right;
		if (m_currentDevice->m_right != NULL)
		{
			m_currentDevice->m_right->m_left = m_currentDevice->m_left;
		}
		m_currentDevice->m_left = NULL;
		m_currentDevice->m_right = NULL;
	}
	else if (m_currentDevice->m_left == NULL)
	{
		if (m_currentDevice->m_attachedFromPart != NULL)
		{
			for (ptrDevice = m_currentDevice->m_right; ptrDevice != NULL
				&& ptrDevice->m_attachedFromPart != m_currentDevice->m_attachedFromPart;
				ptrDevice = ptrDevice->m_right);
			if (ptrDevice != NULL)
			{
				ptrDevice->m_attachedFromPart->m_attachedDevice = ptrDevice;
			}
			else
			{
				m_currentDevice->m_attachedFromPart->m_attachedDevice = NULL;
			}
			m_currentDevice->m_attachedFromPart = NULL;
		}

		m_currentDevice->m_up->m_down = m_currentDevice->m_right;
		if (m_currentDevice->m_right != NULL)
		{
			m_currentDevice->m_right->m_left = NULL;
			m_currentDevice->m_right->m_up = m_currentDevice->m_up;
		}
		m_currentDevice->m_up = NULL;
		m_currentDevice->m_right = NULL;
	}
	sprintf(m_currentDevice->m_parent, "NONE");
	return;




	/****
	if (ptrDevice->m_type == YO_LIGHT)
	{
		for(ptrLight = m_lightList;
			ptrLight != (CStageLight *)ptrDevice
			|| (ptrLight->m_ptrLight != NULL
			&& ptrLight->m_ptrLight != (CStageLight *)ptrDevice);
			ptrLight = ptrLight->m_ptrLight);
		if (ptrLight == (CStageLight *)ptrDevice)
		{
			m_lightList = ptrLight->m_ptrLight;
		}
		else
		{
			ptrLight->m_ptrLight = ((CStageLight *)ptrDevice)->m_ptrLight;
		}
		((CStageLight *)ptrDevice)->m_ptrLight = NULL;
	}
	m_deviceStack = NULL;

	if (m_currentDevice == NULL)
	{
		return;
	}

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glLoadIdentity();

	while (!done)
	{
		::glPushMatrix();
		pView->YoTxyz(ptrDevice->m_ptrPart, ptrDevice->m_ptrPart->m_translate, ptrDevice->m_ptrPart->m_rotate);
		if (ptrDevice == m_currentDevice)
		{
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			m_currentDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
			YoTranslateRotateValues(m, m_currentDevice->m_ptrPart->m_translate, m_currentDevice->m_ptrPart->m_rotate);
			for (i = 0; i < 3; i++)
			{
				m_currentDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}
		}

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			else
			{
				YoPushDevice(NULL);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
			glPopMatrix();
		}
		else if (!YoAllStackDevicesNull())
		{
			glPopMatrix();
			glPopMatrix();
			while ((ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
		}
		else
		{
			glPopMatrix();
			while (m_deviceStack != NULL
				&& (ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
			done = TRUE;
		}
	} // end while (!done)

	::glPopMatrix();

	while (ptrDevice->m_left != NULL || ptrDevice->m_up != NULL)
	{
		if (ptrDevice->m_left != NULL)
		{
			ptrDevice = ptrDevice->m_left;
		}
		else                                                    // ptr->up != NULL 
		{
			m_currentDevice->m_ptrPart->m_translate[0] += ptrDevice->m_up->m_ptrPart->m_translate[0];
			m_currentDevice->m_ptrPart->m_translate[1] += ptrDevice->m_up->m_ptrPart->m_translate[1];
			m_currentDevice->m_ptrPart->m_translate[2] += ptrDevice->m_up->m_ptrPart->m_translate[2];

			m_currentDevice->m_ptrPart->m_rotate[0] += ptrDevice->m_up->m_ptrPart->m_rotate[0];
			m_currentDevice->m_ptrPart->m_rotate[1] += ptrDevice->m_up->m_ptrPart->m_rotate[1];
			m_currentDevice->m_ptrPart->m_rotate[2] += ptrDevice->m_up->m_ptrPart->m_rotate[2];
			ptrDevice = ptrDevice->m_up;
		}
	}
  //  yo_cur_object->next->trans[0] = cur_matrix[3][0];
  //  cur_object->next->trans[1] = cur_matrix[3][1];
  //  cur_object->next->trans[2] = cur_matrix[3][2];
  ***/


}

void CStageDoc::YoDeletePart()
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStagePart *ptrPart;
	CStagePart *currentPart;
	CStageDevice *ptrDevice;
	int i;

	if (m_currentPart->m_up == NULL)
	{
		m_currentPart->m_left->m_right = m_currentPart->m_right;
		if (m_currentPart->m_right != NULL)
		{
			m_currentPart->m_right->m_left = m_currentPart->m_left;
		}
		m_currentPart->m_left = NULL;
		m_currentPart->m_right = NULL;
	}
	else if (m_currentPart->m_left == NULL)
	{
		m_currentPart->m_up->m_down = m_currentPart->m_right;
		if (m_currentPart->m_right != NULL)
		{
			m_currentPart->m_right->m_left = NULL;
			m_currentPart->m_right->m_up = m_currentPart->m_up;
		}
		m_currentPart->m_up = NULL;
		m_currentPart->m_right = NULL;
	}

	// delete all parts in the tree starting with the current part
	m_partStack = NULL;

	for (currentPart = m_currentPart; currentPart != NULL;)
	{
		ptrPart = currentPart;
		if (currentPart->m_down != NULL)
		{
			if (currentPart->m_right != NULL)
			{
				YoPushPart(currentPart->m_right);
			}
			currentPart = currentPart->m_down;
		}
		else if (currentPart->m_right != NULL)
		{
			currentPart = currentPart->m_right;
		}
		else if (m_partStack != NULL)
		{
			currentPart = YoPopPart();
		}
		else 
		{
			currentPart = NULL; 
		}

		for (ptrDevice = ptrPart->m_attachedDevice; ptrDevice != NULL;
			ptrDevice = ptrDevice->m_right)
		{
			if (ptrDevice->m_attachedFromPart == ptrPart)
			{
				ptrDevice->m_attachedFromPart = NULL;
			}
		}
		if (m_currentTag != NULL
			&& m_currentTag->m_ptrPath->m_ptrPart == ptrPart)
		{
			m_currentTag = NULL;
		}
		delete(ptrPart);
	}

	m_currentPart = m_currentDevice->m_ptrPart;

	if (m_currentTag == NULL)
	{
		for (i = 0; i < YO_HASH_SIZE; i++)
		{
			if (m_pathHash[i] != NULL)
			{
				m_currentTag = m_pathHash[i]->m_ptrTag;
				break;
			}
		}
	}

	pView->YoRender(YO_RENDER_FULL);
	return;
}


void CStageDoc::YoDeleteDevice()
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	//CStageLight *ptrLight;
	CStageDevice *currentDevice;
	CStageDevice *ptrDevice;
	CStageDevice *prevDevice = NULL;
	CStageDevice *ptrParent = NULL;
	CStageDevice *ptrChild = NULL;
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
	//GLdouble m[16];
	//GLdouble n[16];
	char s[256];

	// last device in workcell
	//if (m_deviceList == NULL)
	//{
	//	m_deviceList = m_currentDevice;
	//	YoFreeWorkcell();
	//	return;
	//}

	// see if device to be deleted has a parent
	if (strcmp(m_currentDevice->m_parent, "NONE") != 0)
	{
		ptrParent = YoDeviceHashLookup(m_currentDevice->m_parent);
	}

	if (m_currentDevice->m_type == YO_CONVEYOR_PALLET
		&& ((CStageConveyorPallet *)m_currentDevice)->m_ptrSegment != NULL
		&& (ptrDevice = YoDeviceHashLookup(m_currentDevice->m_parent)) != NULL
		&& ptrDevice->m_type == YO_CONVEYOR
		&& (strcmp(m_currentDevice->m_parent, ptrDevice->m_name) == 0))
	{
		((CStageConveyor *)ptrDevice)->YoRemovePallet((CStageConveyorPallet *)m_currentDevice);
	}

	// if device to be deleted has children find new transformations
	// of children
	if (m_currentDevice->m_down != NULL)
	{
		currentDevice = m_currentDevice;
		for (ptrChild = m_currentDevice->m_down; ptrChild != NULL; ptrChild = ptrChild->m_right)
		{
			m_currentDevice = ptrChild;
			YoDetachDevice();
			if (ptrParent == NULL)
			{
				// reattach device at world coords (rightmost position)
				for (ptrDevice = m_deviceList;
					ptrDevice->m_right != NULL;
					ptrDevice = ptrDevice->m_right);
				ptrDevice->m_right = m_currentDevice;
				m_currentDevice->m_left = ptrDevice;
			}
			else
			{
				if (currentDevice->m_attachedFromPart == NULL)
				{
					m_currentDevice->m_attachedFromPart = ptrParent->m_ptrPart;
				}
				else
				{
					m_currentDevice->m_attachedFromPart = currentDevice->m_attachedFromPart;
				}
				sprintf(m_currentDevice->m_parent, "%s", currentDevice->m_parent);
				YoAttachDevice(m_currentDevice->m_attachedFromPart);
			}
		}
		m_currentDevice = currentDevice;
	}

	/****
	// if device to be deleted has children find new transformations
	// of children
	if (m_currentDevice->m_down != NULL)
	{
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();
		((CStageView *)pView)->YoTxyz(m_currentDevice->m_ptrPart,
			m_currentDevice->m_ptrPart->m_translate,
			m_currentDevice->m_ptrPart->m_rotate);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);
	}

	for (ptrDevice = m_currentDevice->m_down; ptrDevice != NULL;
		ptrDevice = ptrDevice->m_right)
	{
		::glLoadMatrixd(m);
		((CStageView *)pView)->YoTxyz(ptrDevice->m_ptrPart,
			ptrDevice->m_ptrPart->m_translate,
			ptrDevice->m_ptrPart->m_rotate);
		::glGetDoublev(GL_MODELVIEW_MATRIX, n);
		ptrDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
		YoTranslateRotateValues(n,
			ptrDevice->m_ptrPart->m_translate,
			ptrDevice->m_ptrPart->m_rotate);
		for (i = 0; i < 3; i++)
		{
			ptrDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
		}
		if (ptrParent != NULL)
		{
			sprintf(ptrDevice->m_parent, "%s", m_currentDevice->m_parent);
			if (m_currentDevice->m_attachedFromPart != NULL)
			{
				ptrDevice->m_attachedFromPart = m_currentDevice->m_attachedFromPart;
			}
			else
			{
				ptrDevice->m_attachedFromPart = NULL;
			}
		}
		else
		{
			sprintf(ptrDevice->m_parent, "NONE");
			ptrDevice->m_attachedFromPart = NULL;
		}
	}

	if (m_currentDevice->m_down != NULL)
	{
		::glPopMatrix();
	}
	***/

	// remove the  name from the device hash table
	i = (int)YoHash(m_currentDevice->m_name, YO_HASH_VALUE, YO_HASH_SIZE);
	
	for (ptrDevice = m_deviceHash[i];
		ptrDevice != NULL && strcmp(m_currentDevice->m_name, ptrDevice->m_name) != 0;
		ptrDevice = ptrDevice->m_nextHash)
	{
		prevDevice = ptrDevice;
	}
	if (prevDevice == NULL)
	{
		m_deviceHash[i] = ptrDevice->m_nextHash;
	}
	else
	{
		prevDevice->m_nextHash = ptrDevice->m_nextHash;
	}
	ptrDevice->m_nextHash = NULL;

	// delete parts associated with device
	m_partStack = NULL;

	for (currentPart = m_currentDevice->m_ptrPart; currentPart != NULL;)
	{
		ptrPart = currentPart;
		if (currentPart->m_down != NULL)
		{
			if (currentPart->m_right != NULL)
			{
				YoPushPart(currentPart->m_right);
			}
			currentPart = currentPart->m_down;
		}
		else if (currentPart->m_right != NULL)
		{
			currentPart = currentPart->m_right;
		}
		else if (m_partStack != NULL)
		{
			currentPart = YoPopPart();
		}
		else 
		{
			currentPart = NULL; 
		}

		/***
		currentEffect = ptrPart->m_effect;
		while (currentEffect != NULL)
		{
			ptrEffect = currentEffect;
			currentEffect = currentEffect->m_next;
			delete(ptrEffect);
		}

		currentMotion = ptrPart->m_motion;
		while (currentMotion != NULL)
		{
			ptrMotion = currentMotion;
			currentMotion = currentMotion->m_next;
			delete(ptrMotion);
		}

		currentScore = ptrPart->m_score;
		while (currentScore != NULL)
		{
			ptrScore = currentScore;
			currentScore = currentScore->m_next;
			delete(ptrScore);
		}
		***/

		//glDeleteLists(ptrPart->m_displayListID, 1);
		//glDeleteLists(ptrPart->m_wireframeDisplayListID, 1);
		delete(ptrPart);
	}

	// reconstruct device list without device to be deleted
	if (m_currentDevice->m_down == NULL)
	{
		if (m_currentDevice->m_left != NULL)
		{
			m_currentDevice->m_left->m_right = m_currentDevice->m_right;
		}
		if (m_currentDevice->m_right != NULL)
		{
			m_currentDevice->m_right->m_left = m_currentDevice->m_left;
		}
		if (m_currentDevice->m_up != NULL)
		{
			if (m_currentDevice->m_right != NULL)
			{
				m_currentDevice->m_up->m_down = m_currentDevice->m_right;
				m_currentDevice->m_right->m_up = m_currentDevice->m_up;
			}
			else
			{
				m_currentDevice->m_up->m_down = NULL;
			}
		}
	}
	else
	{
		for (ptrDevice = m_currentDevice->m_down;
			ptrDevice->m_right != NULL;
			ptrDevice = ptrDevice->m_right);

		if (m_currentDevice->m_left != NULL)
		{
			m_currentDevice->m_left->m_right = m_currentDevice->m_down;
			m_currentDevice->m_down->m_left = m_currentDevice->m_left;
		}
		if (m_currentDevice->m_right != NULL)
		{
			m_currentDevice->m_right->m_left = ptrDevice;
			ptrDevice->m_right = m_currentDevice->m_right;
		}
		if (m_currentDevice->m_up != NULL)
		{
			m_currentDevice->m_down->m_up = m_currentDevice->m_up;
			m_currentDevice->m_up->m_down = m_currentDevice->m_down;
		}
		else
		{
			m_currentDevice->m_down->m_up = NULL;
		}
	}

	if (m_currentDevice == m_deviceList)
	{
		if (m_currentDevice->m_down != NULL)
		{
			m_deviceList = m_currentDevice->m_down;
		}
		else if (m_currentDevice->m_right != NULL)
		{
			m_deviceList = m_currentDevice->m_right;
		}
		else
		{
			m_deviceList = NULL;
		}
	}


	if (ptrParent != NULL && m_currentDevice->m_attachedFromPart != NULL)
	{
		for (ptrDevice = ptrParent->m_down;
			ptrDevice != NULL;
			ptrDevice = ptrDevice->m_right)
		{
			if (ptrDevice->m_attachedFromPart == m_currentDevice->m_attachedFromPart
				&& ptrDevice != m_currentDevice)
			{
				break;
			}
		}

		if (ptrDevice != NULL)
		{
			ptrDevice->m_attachedFromPart->m_attachedDevice = ptrDevice;
		}
		else
		{
			m_currentDevice->m_attachedFromPart->m_attachedDevice = NULL;
		}
	}



/***
	if (m_deviceList == NULL)
	{
		if (m_currentDevice->m_right != NULL)
		{
			m_deviceList = m_currentDevice->m_right;
			m_currentDevice->m_right->m_left = NULL;
			if (m_currentDevice->m_down != NULL)
			{
				for (ptrDevice = m_deviceList;
					ptrDevice->m_right != NULL;
					ptrDevice = ptrDevice->m_right);
				m_currentDevice->m_down->m_left = ptrDevice;
				ptrDevice->m_right = m_currentDevice->m_down;
				m_currentDevice->m_down->m_up = NULL;
				sprintf(m_currentDevice->m_down->m_parent, "NONE");
				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				::glLoadIdentity();
				((CStageView *)pView)->YoTxyz(m_currentDevice->m_ptrPart,
					m_currentDevice->m_ptrPart->m_translate,
					m_currentDevice->m_ptrPart->m_rotate);
				((CStageView *)pView)->YoTxyz(m_currentDevice->m_down->m_ptrPart,
					m_currentDevice->m_down->m_ptrPart->m_translate,
					m_currentDevice->m_down->m_ptrPart->m_rotate);		
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				m_currentDevice->m_down->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
				YoTranslateRotateValues(m,
					m_currentDevice->m_down->m_ptrPart->m_translate,
					m_currentDevice->m_down->m_ptrPart->m_rotate);
				for (i = 0; i < 3; i++)
				{
					m_currentDevice->m_down->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
				}
				::glPopMatrix();
			}
		}
		else if (m_currentDevice->m_down != NULL)
		{
			m_deviceList = m_currentDevice->m_down;
			m_currentDevice->m_down->m_up = NULL;
			sprintf(m_currentDevice->m_down->m_parent, "NONE");
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadIdentity();
			((CStageView *)pView)->YoTxyz(m_currentDevice->m_ptrPart,
				m_currentDevice->m_ptrPart->m_translate,
				m_currentDevice->m_ptrPart->m_rotate);
			((CStageView *)pView)->YoTxyz(m_currentDevice->m_down->m_ptrPart,
				m_currentDevice->m_down->m_ptrPart->m_translate,
				m_currentDevice->m_down->m_ptrPart->m_rotate);		
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			m_currentDevice->m_down->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
			YoTranslateRotateValues(m,
				m_currentDevice->m_down->m_ptrPart->m_translate,
				m_currentDevice->m_down->m_ptrPart->m_rotate);
			for (i = 0; i < 3; i++)
			{
				m_currentDevice->m_down->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}
			::glPopMatrix();
		}
	}
	else
	{
		for (ptrDevice = m_deviceList;
			ptrDevice->m_right != NULL;
			ptrDevice = ptrDevice->m_right);
		if (m_currentDevice->m_right != NULL)
		{
			m_currentDevice->m_right->m_left = ptrDevice;
			ptrDevice->m_right = m_currentDevice->m_right; 
			if (m_currentDevice->m_down != NULL)
			{
				for (ptrDevice = ptrDevice;
					ptrDevice->m_right != NULL;
					ptrDevice = ptrDevice->m_right);
				m_currentDevice->m_down->m_left = ptrDevice;
				ptrDevice->m_right = m_currentDevice->m_down;
				m_currentDevice->m_down->m_up = NULL;
				sprintf(m_currentDevice->m_down->m_parent, "NONE");
				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				::glLoadIdentity();
				((CStageView *)pView)->YoTxyz(m_currentDevice->m_ptrPart,
					m_currentDevice->m_ptrPart->m_translate,
					m_currentDevice->m_ptrPart->m_rotate);
				((CStageView *)pView)->YoTxyz(m_currentDevice->m_down->m_ptrPart,
					m_currentDevice->m_down->m_ptrPart->m_translate,
					m_currentDevice->m_down->m_ptrPart->m_rotate);		
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				m_currentDevice->m_down->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
				YoTranslateRotateValues(m,
					m_currentDevice->m_down->m_ptrPart->m_translate,
					m_currentDevice->m_down->m_ptrPart->m_rotate);
				for (i = 0; i < 3; i++)
				{
					m_currentDevice->m_down->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
				}
				::glPopMatrix();
			}
		}
		else if (m_currentDevice->m_down != NULL)
		{
			ptrDevice->m_right = m_currentDevice->m_down;
			m_currentDevice->m_down->m_left = ptrDevice;
			m_currentDevice->m_down->m_up = NULL;
			sprintf(m_currentDevice->m_down->m_parent, "NONE");
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadIdentity();
			((CStageView *)pView)->YoTxyz(m_currentDevice->m_ptrPart,
				m_currentDevice->m_ptrPart->m_translate,
				m_currentDevice->m_ptrPart->m_rotate);
			((CStageView *)pView)->YoTxyz(m_currentDevice->m_down->m_ptrPart,
				m_currentDevice->m_down->m_ptrPart->m_translate,
				m_currentDevice->m_down->m_ptrPart->m_rotate);		
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			m_currentDevice->m_down->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
			YoTranslateRotateValues(m,
				m_currentDevice->m_down->m_ptrPart->m_translate,
				m_currentDevice->m_down->m_ptrPart->m_rotate);
			for (i = 0; i < 3; i++)
			{
				m_currentDevice->m_down->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}
			::glPopMatrix();
		}
	}

	// if device to be deleted is a light, then remove it from light list
	if (m_currentDevice->m_type == YO_LIGHT)
	{
		::glDisable(((CStageLight *)m_currentDevice)->m_target);
		for (ptrLight = m_lightList;
			ptrLight != (CStageLight *)m_currentDevice
			&& ptrLight->m_ptrLight != NULL
			&& ptrLight->m_ptrLight != (CStageLight *)m_currentDevice;
			ptrLight = ptrLight->m_ptrLight);
		if (ptrLight == (CStageLight *)m_currentDevice)
		{
			m_lightList = ptrLight->m_ptrLight;
		}
		else
		{
			ptrLight->m_ptrLight = ((CStageLight *)m_currentDevice)->m_ptrLight;
		}
	}
	***/

	delete (m_currentDevice);
	m_currentDevice = m_deviceList;
	if (m_currentDevice != NULL)
	{
		m_currentPart = m_currentDevice->m_ptrPart;
		if (m_currentPart->m_path != NULL)
		{
			m_currentTag = m_currentPart->m_path->m_ptrTag;
		}
		else
		{
			// try to find any path
			m_currentTag = NULL;
			for (i = 0; i < YO_HASH_SIZE; i++)
			{
				if (m_pathHash[i] != NULL)
				{
					m_currentTag = m_pathHash[i]->m_ptrTag;
					break;
				}
			}
		}
		sprintf(s, "Device: %s   Part: %s",
			m_currentDevice->m_name, m_currentPart->m_partName);
	}
	else
	{
		m_currentPart = NULL;
		m_currentTag = NULL;
		sprintf(s, "");
	}

	//YoMessage(s);
	//((CStageView *)pView)->YoRender(YO_RENDER_LIGHT);
	//((CStageView *)pView)->YoRender(YO_RENDER_FULL);
	return;
}


void CStageDoc::YoDeleteTag()
// delete m_currentTag then set m_currentTag to another tag in the path  
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageTag *dTag;

	if (m_currentTag == NULL)
	{
		return;
	}

	if (m_currentTag->m_nextTag == NULL && m_currentTag->m_prevTag == NULL)
	{
		YoDeletePath(m_currentTag);
		return;
	}

	dTag = m_currentTag;
	if (m_currentTag->m_nextTag != NULL)
	{
		m_currentTag = m_currentTag->m_nextTag;
	}
	else if(m_currentTag->m_prevTag != NULL)
	{
		m_currentTag = m_currentTag->m_prevTag;
	}

	dTag->m_ptrPath->YoDeleteTag(dTag);

	pView->YoRender(YO_RENDER_FULL);
	return;

}


void CStageDoc::YoDeletePath(CStageTag *ptrTag)
// delete a path given any tag on the path 
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageTag *dTag;
	CStagePart *ptrPart;
	int i;

	if (ptrTag == NULL)
	{
		return;
	}

	ptrPart = ptrTag->m_ptrPath->m_ptrPart;
	ptrTag = ptrTag->m_ptrPath->m_ptrTag;

	while (ptrTag != NULL)
	{
		dTag = ptrTag;
		ptrTag = ptrTag->m_nextTag;
		dTag->m_ptrPath->YoDeleteTag(dTag);
	}

	// try to find another path associated with ptrPart
	if (ptrPart->m_path != NULL)
	{
		m_currentTag = ptrPart->m_path->m_ptrTag;
		pView->YoRender(YO_RENDER_FULL);
		return;
	}
	// try to find any path
	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		if (m_pathHash[i] != NULL)
		{
			m_currentTag = m_pathHash[i]->m_ptrTag;
			pView->YoRender(YO_RENDER_FULL);
			return;
		}
	}

	m_currentTag = NULL;
	pView->YoRender(YO_RENDER_FULL);
	return;
}


BOOL CStageDoc::YoInsertPart(CStageDevice *ptrDevice, CStagePart *ptrPart)

{
	CStagePart  *currentPart = ptrDevice->m_ptrPart;
	GLint stackDepth;
	GLint i;
	
	::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &stackDepth);
	m_partStack = NULL;

	if (currentPart == NULL)
	{
		ptrDevice->m_ptrPart = ptrPart;
		return TRUE;
	}

	while (TRUE)
	{
		if ((strcmp(ptrPart->m_partParent, currentPart->m_partName) == 0)
			&& (currentPart->m_down == NULL))
		{
			currentPart->m_down = ptrPart;
			ptrPart->m_up = currentPart;
			::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &i);
			while(i > stackDepth)
			{
				::glPopMatrix();
				i--;
			}
			YoFreePart();
			return TRUE;
		}

		if ((strcmp(ptrPart->m_partParent, currentPart->m_partParent) == 0)
			&& (currentPart->m_right == NULL))
		{
			currentPart->m_right = ptrPart;
			ptrPart->m_left = currentPart;
			::glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &i);
			while(i > stackDepth)
			{
				::glPopMatrix();
				i--;
			}
			YoFreePart();
			return TRUE;
		}

		if (currentPart->m_down != NULL)
		{
			if (currentPart->m_right != NULL)
			{
				YoPushPart(currentPart->m_right);
			}
			currentPart = currentPart->m_down;
		}
		else if (currentPart->m_right != NULL)
		{
			currentPart = currentPart->m_right;
		}
		else if (m_partStack != NULL)
		{
			currentPart = YoPopPart();
		}
		else
		{
			return TRUE;
		}
	}
	return TRUE;
}


BOOL CStageDoc::YoInsertEffect(CStageEffect *ptrEffect, CStagePart *ptrPart)

// insert an effect node, ptrEffect, into the effect list for the specified part

{
	CStageEffect *currentEffect = ptrPart->m_effect;
	CStageEffect *previousEffect = NULL;
	CStageMotion *currentMotion = ptrPart->m_motion;

	// auto insert node at time = 0 if no motion nodes exist
	if (currentMotion == NULL)
	{         
		currentMotion = new CStageMotion(this);
		currentMotion->m_type = YO_MOTION_HOLD;
		currentMotion->m_translate[0] = m_currentPart->m_translate[0];
		currentMotion->m_translate[1] = m_currentPart->m_translate[1];
		currentMotion->m_translate[2] = m_currentPart->m_translate[2];
		currentMotion->m_rotate[0] = m_currentPart->m_rotate[0];
		currentMotion->m_rotate[1] = m_currentPart->m_rotate[1];
		currentMotion->m_rotate[2] = m_currentPart->m_rotate[2];
		currentMotion->m_next = NULL;
		ptrPart->m_motion = currentMotion;
	}

	while (currentEffect != NULL
		&& (ptrEffect->m_priority > currentEffect->m_priority
		|| ptrEffect->m_begin >= currentEffect->m_begin))
	{
		previousEffect = currentEffect;
		currentEffect = currentEffect->m_next;
	}

	if (previousEffect == NULL)
	{
		ptrPart->m_effect = ptrEffect;
	}
	else
	{
		previousEffect->m_next = ptrEffect;
	}
	ptrEffect->m_next = currentEffect;

	// YoUpdateMotionEffectBrowser();
	m_currentPart->m_motionEffectModified = TRUE;
	m_motionEffectModified = TRUE;
	return TRUE;
}


BOOL CStageDoc::YoInsertPartMotion(CStageMotion *ptrMotion, CStagePart *ptrPart)

// insert a motion node, ptrMotion,
// into the motion list for the specified part

{

	/***
	CStageMotion *currentMotion = ptrPart->m_motion;
	CStageMotion *previousMotion = NULL;

	// auto insert node at time = 0 if no motion nodes exist
	if (currentMotion == NULL && m_timeCurrent != 0)
	{
		currentMotion = new CStageMotion(this);
		currentMotion->m_time = 0;
		currentMotion->m_type = YO_MOTION_HOLD;
		currentMotion->m_translate[0] = m_currentPart->m_translate[0];
		currentMotion->m_translate[1] = m_currentPart->m_translate[1];
		currentMotion->m_translate[2] = m_currentPart->m_translate[2];
		currentMotion->m_rotate[0] = m_currentPart->m_rotate[0];
		currentMotion->m_rotate[1] = m_currentPart->m_rotate[1];
		currentMotion->m_rotate[2] = m_currentPart->m_rotate[2];
		currentMotion->m_next = NULL;
		ptrPart->m_motion = currentMotion;
	}

	while (currentMotion != NULL
		&& ptrMotion->m_time > currentMotion->m_time)
	{
		previousMotion = currentMotion;
		currentMotion = currentMotion->m_next;
	}

	if (previousMotion == NULL)
	{
		ptrPart->m_motion = ptrMotion;
	}
	else
	{
		previousMotion->m_next = ptrMotion;
	}

	if (currentMotion != NULL
		&& currentMotion->m_time == ptrMotion->m_time)
	{
		ptrMotion->m_next = currentMotion->m_next;
		delete(currentMotion);
	}
	else 
	{
		ptrMotion->m_next = currentMotion;
	}

	// YoUpdateMotionEffectBrowser();
	m_currentPart->m_motionEffectModified = TRUE;
	m_motionEffectModified = TRUE;
	***/
	return TRUE;
}


void CStageDoc::YoInsertEyeMotion(CStageEyeMotion *ptrMotion)

{
	/***
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageEyeMotion *curMotion = m_eyeList->m_motion;
	CStageEyeMotion *prevMotion = NULL;
	GLint i;

	// auto insert node at time = 0 if no eye motion nodes exist	
	if (curMotion == NULL && m_timeCurrent != 0)
	{
		curMotion = new CStageEyeMotion(this);
		curMotion->m_time = 0;
		curMotion->m_type = YO_MOTION_HOLD;
		for (i = 0; i < 9; i++)
		{
			curMotion->m_eye[i] = ((CStageView *)pView)->m_eye[i];
		}
		curMotion->m_clipFront = ((CStageView *)pView)->m_clipFront;
		curMotion->m_clipRear = ((CStageView *)pView)->m_clipRear;
		curMotion->m_fieldOfView = ((CStageView *)pView)->m_fieldOfView;
		
		curMotion->m_next = NULL;
		m_eyeList->m_motion = curMotion;
	}

	while (curMotion != NULL && ptrMotion->m_time > curMotion->m_time)
	{
		prevMotion = curMotion;
		curMotion = curMotion->m_next;
	}

	if (prevMotion == NULL)
	{
		m_eyeList->m_motion = ptrMotion;
	}
	else
	{
		prevMotion->m_next = ptrMotion;
	}

	if (curMotion != NULL && curMotion->m_time == ptrMotion->m_time)
	{
		ptrMotion->m_next = curMotion->m_next;
		delete(curMotion);
	}
	else
	{
		ptrMotion->m_next = curMotion;
	}

	m_motionEffectModified = YO_MOTION_EFFECT_MODIFIED_ALL;
	***/
	return;
}

void CStageDoc::YoLinkTrackSegs()
{
	CStageDevice *ptrDevice;
	CStagePart *ptrPart;
	CStagePart *curPart;
	GLdouble tolerance = 2.0f;

	for (ptrDevice = m_deviceList; ptrDevice != NULL;)
	{
		if (ptrDevice->m_type == YO_TRACK)
		{
			for (ptrPart = ptrDevice->m_ptrPart; ptrPart != NULL;)
			{
				for (curPart = ptrDevice->m_ptrPart; curPart != NULL;)
				{
					// try to find a track segment (tptr) that has the same
					// endpoints as track
	    			if (ptrPart->m_ptrTrackSeg != curPart->m_ptrTrackSeg
						&& ((fabs(curPart->m_ptrTrackSeg->m_to[0] - ptrPart->m_ptrTrackSeg->m_from[0]) < tolerance
						&& fabs(curPart->m_ptrTrackSeg->m_to[1] - ptrPart->m_ptrTrackSeg->m_from[1]) < tolerance)
						|| (fabs(curPart->m_ptrTrackSeg->m_from[0] - ptrPart->m_ptrTrackSeg->m_from[0]) < tolerance
						&& fabs(curPart->m_ptrTrackSeg->m_from[1] - ptrPart->m_ptrTrackSeg->m_from[1]) < tolerance)
						|| (curPart->m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
						&& fabs(curPart->m_ptrTrackSeg->m_switch[0] - ptrPart->m_ptrTrackSeg->m_from[0]) < tolerance
						&& fabs(curPart->m_ptrTrackSeg->m_switch[1] - ptrPart->m_ptrTrackSeg->m_from[1]) < tolerance)))
					{
						ptrPart->m_ptrTrackSeg->m_ptrFrom = curPart->m_ptrTrackSeg;
					}
					else if (ptrPart->m_ptrTrackSeg != curPart->m_ptrTrackSeg
						&& ((fabs(curPart->m_ptrTrackSeg->m_to[0] - ptrPart->m_ptrTrackSeg->m_to[0]) < tolerance
						&& fabs(curPart->m_ptrTrackSeg->m_to[1] - ptrPart->m_ptrTrackSeg->m_to[1]) < tolerance)
						|| (fabs(curPart->m_ptrTrackSeg->m_from[0] - ptrPart->m_ptrTrackSeg->m_to[0]) < tolerance
						&& fabs(curPart->m_ptrTrackSeg->m_from[1] - ptrPart->m_ptrTrackSeg->m_to[1]) < tolerance)
						|| (curPart->m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
						&& fabs(curPart->m_ptrTrackSeg->m_switch[0] - ptrPart->m_ptrTrackSeg->m_to[0]) < tolerance
						&& fabs(curPart->m_ptrTrackSeg->m_switch[1] - ptrPart->m_ptrTrackSeg->m_to[1]) < tolerance)))
					{
						ptrPart->m_ptrTrackSeg->m_ptrTo = curPart->m_ptrTrackSeg;
					}
					else if (ptrPart->m_ptrTrackSeg != curPart->m_ptrTrackSeg && ptrPart->m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
						&& ((fabs(curPart->m_ptrTrackSeg->m_to[0] - ptrPart->m_ptrTrackSeg->m_switch[0]) < tolerance
						&& fabs(curPart->m_ptrTrackSeg->m_to[1] - ptrPart->m_ptrTrackSeg->m_switch[1]) < tolerance)
						|| (fabs(curPart->m_ptrTrackSeg->m_from[0] - ptrPart->m_ptrTrackSeg->m_switch[0]) < tolerance
						&& fabs(curPart->m_ptrTrackSeg->m_from[1] - ptrPart->m_ptrTrackSeg->m_switch[1]) < tolerance)
						|| (curPart->m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
						&& fabs(curPart->m_ptrTrackSeg->m_switch[0] - ptrPart->m_ptrTrackSeg->m_switch[0]) < tolerance
						&& fabs(curPart->m_ptrTrackSeg->m_switch[1] - ptrPart->m_ptrTrackSeg->m_switch[1]) < tolerance)))
					{
						ptrPart->m_ptrTrackSeg->m_ptrSwitch = curPart->m_ptrTrackSeg;
					}

					// first track segment is the parent of all remaining track segments
					if (curPart == ptrDevice->m_ptrPart)
					{
						curPart = curPart->m_down;
					}
					else
					{
						curPart = curPart->m_right;
					}
				}
				// first track segment is the parent of all remaining track segments
				if (ptrPart == ptrDevice->m_ptrPart)
				{
					ptrPart = ptrPart->m_down;
				}
				else
				{
					ptrPart = ptrPart->m_right;
				}
			}
		}

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			ptrDevice = YoPopDevice();
		}
		else 
		{
			ptrDevice = NULL;
		}
	}

	return;
}

void CStageDoc::YoPushDevice(CStageDevice *ptrDevice)

{
	CStageStack  *ptrStack;

	ptrStack = new CStageStack(); 
	ptrStack->m_ptr = ptrDevice;

	if (m_deviceStack != NULL)
	{
		ptrStack->m_next = m_deviceStack;
	}
	else
	{
		ptrStack->m_next = NULL;
	}

	m_deviceStack = ptrStack;
	return;
	
}


CStageDevice* CStageDoc::YoPopDevice(void)

{
	CStageDevice  *ptrDevice;
	CStageStack *ptrStack;
 
	ptrStack = m_deviceStack;
	if (ptrStack == NULL)
	{
		return NULL;
	}
	ptrDevice = (CStageDevice *)m_deviceStack->m_ptr;
	m_deviceStack = m_deviceStack->m_next;
	delete ptrStack;
	return ptrDevice;
}


void CStageDoc::YoFreeDevice(void)
{
	CStageStack *ptrStack;
	while (m_deviceStack != NULL)
	{
		ptrStack = m_deviceStack;
		m_deviceStack = m_deviceStack->m_next;
		delete ptrStack;
	}
}


BOOL CStageDoc::YoAllStackDevicesNull(void)

{
	CStageStack *ptrStack = m_deviceStack;

	while (ptrStack != NULL)
	{
		if (ptrStack->m_ptr != NULL)
		{
			return FALSE;
		}
		ptrStack = ptrStack->m_next;
	}
	return TRUE;
}

void CStageDoc::YoPushPart(CStagePart *ptrPart)

{
	CStageStack  *ptrStack;

	ptrStack = new CStageStack(); 
	ptrStack->m_ptr = ptrPart;

	if (m_partStack != NULL)
	{
		ptrStack->m_next = m_partStack;
	}
	else
	{
		ptrStack->m_next = NULL;
	}

	m_partStack = ptrStack;
	return;
}


void CStageDoc::YoPushPart(CStageStack **partStack, CStagePart *ptrPart)

{

	CStageStack  *ptrStack;

	ptrStack = new CStageStack(); 
	ptrStack->m_ptr = ptrPart;

	if (partStack != NULL)
	{
		ptrStack->m_next = *partStack;
	}
	else
	{
		ptrStack->m_next = NULL;
	}

	*partStack = ptrStack;
	return;
}


CStagePart* CStageDoc::YoPopPart(void)

{
	CStagePart  *ptrPart;
	CStageStack *ptrStack;
 
	ptrStack = m_partStack;
	if (ptrStack == NULL)
	{
		return NULL;
	}
	ptrPart = (CStagePart *)m_partStack->m_ptr;
	m_partStack = m_partStack->m_next;
	delete ptrStack;
	return ptrPart;
}


CStagePart* CStageDoc::YoPopPart(CStageStack **partStack)

{
	CStagePart  *ptrPart;
	CStageStack *ptrStack;
 
	ptrStack = *partStack;
	if (ptrStack == NULL)
	{
		return NULL;
	}
	ptrPart = (CStagePart *)(*partStack)->m_ptr;
	*partStack = (*partStack)->m_next;
	delete ptrStack;
	return ptrPart;
}

void CStageDoc::YoFreePart(void)
{
	CStageStack *ptrStack;
	while (m_partStack != NULL)
	{
		ptrStack = m_partStack;
		m_partStack = m_partStack->m_next;
		delete ptrStack;
	}
}


BOOL CStageDoc::YoAllStackPartsNull(void)

{
	CStageStack *ptrStack = m_partStack;

	while (ptrStack != NULL)
	{
		if (ptrStack->m_ptr != NULL)
		{
			return FALSE;
		}
		ptrStack = ptrStack->m_next;
	}
	return TRUE;
}


void CStageDoc::YoCrossProduct(GLdouble *n, GLdouble *u, GLdouble *v)

// computes the cross product, n, of 1X3 vectors u and v

{

	n[0] = u[1] * v[2] - u[2] * v[1];
	n[1] = u[2] * v[0] - u[0] * v[2];
	n[2] = u[0] * v[1] - u[1] * v[0];

	return;
}


void CStageDoc::YoNormalize(GLdouble *v)

{
	GLdouble  d;

	d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d > 0.0)
	{
		v[0] /= d;
		v[1] /= d;
		v[2] /= d;
	}
	return;
}


BOOL CStageDoc::YoRayTriangleIntersect(double orig[3], double dir[3],
	double vert0[3], double vert1[3], double vert2[3],
	double *t, double *u, double *v)
{
// www.acm.org/jgt/papers/MollerTrumbore97/code.html
// Determines whether a ray intersects a triangle.
// The algorithm translates the origin of the ray and then changes the base
// to yield a vector (t u v)T, where t is the distance to the plane in which the triangle lies
// and (u,v) represents the coordinates inside the triangle. 

#define EPSILON 0.000001
#define CROSS(dest, v1, v2) \
	dest[0] = v1[1] * v2[2] - v1[2] * v2[1]; \
	dest[1] = v1[2] * v2[0] - v1[0] * v2[2]; \
	dest[2] = v1[0] * v2[1] - v1[1] * v2[0];
#define DOT(v1, v2) (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2])
#define SUB(dest, v1, v2) \
	dest[0] = v1[0] - v2[0]; \
	dest[1] = v1[1] - v2[1]; \
	dest[2] = v1[2] - v2[2]; 
#define TEST_CULL

	double edge1[3];
	double edge2[3];
	double tvec[3];
	double pvec[3];
	double qvec[3];
	double det;
	double inv_det;

	// find vectors for two edges sharing vert0
	SUB(edge1, vert1, vert0);
	SUB(edge2, vert2, vert0);

	// begin calculating determinant - also used to calculate U parameter
	CROSS(pvec, dir, edge2);

	// if determinant is near zero, ray lies in plane of triangle
	det = DOT(edge1, pvec);

#ifdef TEST_CULL           // define TEST_CULL if culling is desired

	if (det < EPSILON)
	{
		return FALSE;
	}

	// calculate distance from vert0 to ray origin
	SUB(tvec, orig, vert0);

	// calculate U parameter and test bounds
	*u = DOT(tvec, pvec);
	if (*u < 0.0 || *u > det)
	{
		return FALSE;
	}

	// prepare to test V parameter
	CROSS(qvec, tvec, edge1);

	// calculate V parameter and test bounds
	*v = DOT(dir, qvec);
	if (*v < 0.0 || *u + *v > det)
	{
		return FALSE;
	}

	// calculate t, scale parameters, ray intersects triangle
	*t = DOT(edge2, qvec);
	inv_det = 1.0 / det;
	*t *= inv_det;
	*u *= inv_det;
	*v *= inv_det;

#else                    // the non-culling branch

	if (det > -EPSILON && det < EPSILON)
	{
		return FALSE;
	}
	inv_det = 1.0 / det;

	// calculate distance from vert0 to ray origin
	SUB(tvec, orig, vert0);

	// calculate U parameter and test bounds
	*u = DOT(tvec, pvec) * inv_det;
	if (*u < 0.0 || *u > 1.0)
	{
		return FALSE;
	}

	// prepare to test V parameter
	CROSS(qvec, tvec, edge1);

	// calculate V parameter and test bounds
	*v = DOT(dir, qvec) * inv_det;
	if (*v < 0.0 || *u + *v > 1.0)
	{
		return FALSE;
	}

	// calculate t, ray intersects triangle
	*t = DOT(edge2, qvec) * inv_det;

#endif

	return TRUE;

}



BOOL CStageDoc::YoCoplanerTriangleTriangle(double N[3], double V0[3], double V1[3], double V2[3],
	double U0[3], double U1[3], double U2[3])
{

// This edge to edge test is based on Franlin Antonio's gem:
// "Faster Line Segment Intersection", in Graphics Gems III, pp. 199-202.
#define EDGE_EDGE_TEST(V0, U0, U1)									\
	Bx = U0[i0] - U1[i0];											\
	By = U0[i1] - U1[i1];											\
	Cx = V0[i0] - U0[i0];											\
	Cy = V0[i1] - U0[i1];											\
	f = Ay * Bx - Ax * By;											\
	d = By * Cx - Bx * Cy;											\
	if ((f > 0 && d >= 0 && d <= f) || (f < 0 && d <= 0 && d >= f))	\
	{																\
		e = Ax * Cy - Ay * Cx;										\
		if(f > 0)													\
		{															\
			if(e >= 0 && e <= f) return 1;							\
		}															\
		else														\
		{															\
			if(e <= 0 && e >= f) return 1;							\
		}															\
	}                                

#define EDGE_AGAINST_TRI_EDGES(V0, V1, U0, U1, U2)					\
{																	\
	double Ax, Ay, Bx, By, Cx, Cy, e, d, f;							\
	Ax = V1[i0] - V0[i0];											\
	Ay = V1[i1] - V0[i1];											\
	/* test edge U0,U1 against V0,V1 */								\
	EDGE_EDGE_TEST(V0, U0, U1);										\
	/* test edge U1,U2 against V0,V1 */								\
	EDGE_EDGE_TEST(V0, U1, U2);										\
	/* test edge U2,U1 against V0,V1 */								\
	EDGE_EDGE_TEST(V0, U2, U0);										\
}

#define POINT_IN_TRI(V0, U0, U1, U2)					\
{														\
	double a, b, c, d0, d1, d2;							\
	/* is T1 completly inside T2? */					\
	/* check if V0 is inside tri(U0, U1, U2) */			\
	a = U1[i1] - U0[i1];								\
	b = -(U1[i0] - U0[i0]);								\
	c = -a * U0[i0] - b * U0[i1];						\
	d0 = a * V0[i0] + b * V0[i1] + c;					\
														\
	a = U2[i1] - U1[i1];								\
	b = -(U2[i0] - U1[i0]);								\
	c = -a * U1[i0] - b * U1[i1];						\
	d1 = a * V0[i0] + b * V0[i1] + c;					\
														\
	a = U0[i1] - U2[i1];								\
	b = -(U0[i0] - U2[i0]);								\
	c = -a * U2[i0] - b * U2[i1];						\
	d2 = a * V0[i0] + b * V0[i1] + c;					\
	if (d0 * d1 > 0.0)									\
	{													\
		if (d0 * d2 > 0.0) return 1;					\
	}													\
}

	double A[3];
	short i0, i1;

	// first project onto an axis-aligned plane, that maximizes the area
	// of the triangles, compute indices: i0,i1.
	A[0] = fabs(N[0]);
	A[1] = fabs(N[1]);
	A[2] = fabs(N[2]);
	if (A[0] > A[1])
	{
		if (A[0] > A[2])  
		{
			i0 = 1;		// A[0] is greatest
			i1 = 2;
		}
		else
		{
			i0 = 0;		// A[2] is greatest
			i1 = 1;
		}
	}
	else				// A[0] <= A[1]
	{
		if (A[2] > A[1])
		{
			i0 = 0;		// A[2] is greatest
			i1 = 1;                                           
		}
		else
		{
			i0 = 0;		// A[1] is greatest
			i1 = 2;
		}
    }               
                
	// test all edges of triangle 1 against the edges of triangle 2
	EDGE_AGAINST_TRI_EDGES(V0, V1, U0, U1, U2);
	EDGE_AGAINST_TRI_EDGES(V1, V2, U0, U1, U2);
	EDGE_AGAINST_TRI_EDGES(V2, V0, U0, U1, U2);
                
	// finally, test if tri1 is totally contained in tri2 or vice versa
	POINT_IN_TRI(V0, U0, U1, U2);
	POINT_IN_TRI(U0, V0, V1, V2);

	return 0;
}


BOOL CStageDoc::YoTriangleTriangleIntersect(double V0[3], double V1[3], double V2[3],
	double U0[3], double U1[3], double U2[3])
{


// Triangle/triangle intersection test routine,
// by Tomas Moller, 1997.
// See article "A Fast Triangle-Triangle Intersection Test",
// Journal of Graphics Tools, 2(2), 1997
//
// int tri_tri_intersect(double V0[3],double V1[3],double V2[3],
//                         double U0[3],double U1[3],double U2[3])
//
// parameters: vertices of triangle 1: V0,V1,V2
//             vertices of triangle 2: U0,U1,U2
// result    : returns 1 if the triangles intersect, otherwise 0
//

// www.acm.org/jgt/papers/Moller97/tritri.html


// if USE_EPSILON_TEST is true then we do a check: 
// if |dv|<EPSILON then dv=0.0;
// else no check is done (which is less robust)

#define USE_EPSILON_TEST TRUE  
#define EPSILON 0.000001

#define CROSS(dest, v1, v2)							\
	dest[0] = v1[1] * v2[2] - v1[2] * v2[1];		\
	dest[1] = v1[2] * v2[0] - v1[0] * v2[2];		\
	dest[2] = v1[0] * v2[1] - v1[1] * v2[0];

#define DOT(v1,v2) (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2])

#define SUB(dest, v1, v2)							\
	dest[0] = v1[0] - v2[0];						\
	dest[1] = v1[1] - v2[1];						\
	dest[2] = v1[2] - v2[2]; 

// sort so that a <= b
#define SORT(a, b)									\
	if (a > b)										\
	{												\
		double c;									\
		c = a;										\
		a = b;										\
		b = c;										\
	}

#define ISECT(VV0, VV1, VV2, D0, D1, D2, isect0, isect1)			\
	isect0 = VV0 + (VV1 - VV0) * D0 / (D0 - D1);					\
	isect1 = VV0 + (VV2 - VV0) * D0 / (D0 - D2);

#define COMPUTE_INTERVALS(VV0, VV1, VV2, D0, D1, D2, D0D1, D0D2, isect0, isect1)	\
	if (D0D1 > 0.0f)																\
	{																				\
		/* here we know that D0D2 <= 0.0 */											\
		/* that is D0, D1 are on the same side, D2 on the other or on the plane */	\
		ISECT(VV2, VV0, VV1, D2, D0, D1, isect0, isect1);							\
	}																				\
	else if (D0D2 > 0.0f)															\
	{																				\
		/* here we know that d0d1 <= 0.0 */											\
		ISECT(VV1, VV0, VV2, D1, D0, D2, isect0, isect1);							\
	}																				\
	else if (D1 * D2 > 0.0f || D0 != 0.0f)											\
	{																				\
		/* here we know that d0d1 <= 0.0 or that D0 != 0.0 */						\
		ISECT(VV0, VV1, VV2, D0, D1, D2, isect0, isect1);							\
	}																				\
	else if (D1 != 0.0f)															\
	{																				\
		ISECT(VV1, VV0, VV2, D1, D0, D2, isect0, isect1);							\
	}																				\
	else if (D2 != 0.0f)															\
	{																				\
		ISECT(VV2, VV0, VV1, D2, D0, D1, isect0, isect1);							\
	}																				\
	else																			\
	{																				\
		/* triangles are coplanar */												\
		return YoCoplanerTriangleTriangle(N1, V0, V1, V2, U0, U1, U2);				\
	}

	double E1[3], E2[3];
	double N1[3], N2[3], d1, d2;
	double du0, du1, du2, dv0, dv1, dv2;
	double D[3];
	double isect1[2], isect2[2];
	double du0du1, du0du2, dv0dv1, dv0dv2;
	short index;
	double vp0, vp1, vp2;
	double up0, up1, up2;
	double b, c, max;

	// compute plane equation of triangle(V0, V1, V2)
	SUB(E1, V1, V0);
	SUB(E2, V2, V0);
	CROSS(N1, E1, E2);
	d1 = -DOT(N1, V0);
	// plane equation 1: N1.X+d1=0

	// put U0, U1, U2 into plane equation 1 to compute signed distances to the plane
	du0 = DOT(N1, U0) + d1;
	du1 = DOT(N1, U1) + d1;
	du2 = DOT(N1, U2) + d1;

	// coplanarity robustness check
#if USE_EPSILON_TEST==TRUE
	if (fabs(du0) < EPSILON) du0 = 0.0;
	if (fabs(du1) < EPSILON) du1 = 0.0;
	if (fabs(du2) < EPSILON) du2 = 0.0;
#endif
	du0du1 = du0 * du1;
	du0du2 = du0 * du2;

	if (du0du1 > 0.0f && du0du2 > 0.0f)	// same sign on all of them + not equal 0 ?
	{
		return 0;						// no intersection occurs
	}

	// compute plane of triangle (U0, U1, U2)
	SUB(E1, U1, U0);
	SUB(E2, U2, U0);
	CROSS(N2, E1, E2);
	d2 = -DOT(N2, U0);
	// plane equation 2: N2.X+d2=0

	// put V0, V1, V2 into plane equation 2
	dv0 = DOT(N2, V0) + d2;
	dv1 = DOT(N2, V1) + d2;
	dv2 = DOT(N2 ,V2) + d2;

#if USE_EPSILON_TEST==TRUE
	if(fabs(dv0) < EPSILON) dv0 = 0.0;
	if(fabs(dv1) < EPSILON) dv1 = 0.0;
	if(fabs(dv2) < EPSILON) dv2 = 0.0;
#endif

	dv0dv1 = dv0 * dv1;
	dv0dv2 = dv0 * dv2;
        
	if(dv0dv1 > 0.0f && dv0dv2 > 0.0f)	// same sign on all of them + not equal 0 ?
	{
		return 0;						// no intersection occurs
	}

	// compute direction of intersection line
	CROSS(D, N1, N2);

	// compute and index to the largest component of D
	max = fabs(D[0]);
	index = 0;
	b = fabs(D[1]);
	c = fabs(D[2]);
	if (b > max) max = b, index = 1;
	if (c > max) max = c, index = 2;

	// this is the simplified projection onto L
	vp0 = V0[index];
	vp1 = V1[index];
	vp2 = V2[index];

	up0 = U0[index];
	up1 = U1[index];
	up2 = U2[index];

	// compute interval for triangle 1
	COMPUTE_INTERVALS(vp0, vp1, vp2, dv0, dv1, dv2, dv0dv1, dv0dv2, isect1[0], isect1[1]);

	// compute interval for triangle 2
	COMPUTE_INTERVALS(up0, up1, up2, du0, du1, du2, du0du1, du0du2, isect2[0], isect2[1]);

	SORT(isect1[0], isect1[1]);
	SORT(isect2[0], isect2[1]);

	if (isect1[1] < isect2[0] || isect2[1] < isect1[0]) return 0;
	return 1;
}


void CStageDoc::YoPartBoundingBox(GLdouble *a)

// finds the bounding box of the current part
// member variable: m_currentPart

{
	GLint    i;

	for (i = 0; i < 3; i++)
	{
		m_currentPart->m_min[i] = YO_MIN(m_currentPart->m_min[i], a[i]);
		m_currentPart->m_max[i] = YO_MAX(m_currentPart->m_max[i], a[i]);
	}
	return;
}


void CStageDoc::YoValidateRotate(GLdouble *r)
{
	GLdouble f;
	long i;

	if (*r >= 360.0)
	{
		i = (long)(*r);
		f = *r - (GLdouble)i;
		i = i % 360;
		*r = (GLdouble)i + f;
	}
	else if (*r <= -360.0)
	{
		i = (long)(*r);
		f = *r + (GLdouble)i;
		i = -i % 360;
		*r = -(GLdouble)i - f;
	}
	return;
}


void CStageDoc::YoUnitScaleFactor()
{
	if (m_units == YO_UNITS_MILLIMETERS)
	{
		m_unitScaleFactor = 1.0f;
	}
	else if (m_units == YO_UNITS_INCHES)
	{
		m_unitScaleFactor = 1.0f / 25.4f;
	}
	else if (m_units == YO_UNITS_FEET)
	{
		m_unitScaleFactor = 1.0f / (12.0f * 25.4f);
	}
	else if (m_units == YO_UNITS_METERS)
	{
		m_unitScaleFactor = 0.001f;
	}

	return;
}


GLint CStageDoc::YoGetNewDisplayListID(CStagePart *ptrPart, CStageTag *ptrTag)
// assign a unique integer value to either a part or tag for use in identifying
// the given part or tag when picked.  One of ptrPart and ptrTag must be a valid
// pointer and the other must be NULL.
{
	// static GLint displayListID = 3;
	GLint last = 16000000;
	//GLint last = displayListID + 16000000;

	if (ptrPart == NULL && ptrTag == NULL)
	{
		return 0;
	}

	while (++m_displayListID <= last)
	{
			if (ptrPart != NULL)
			{
				ptrPart->m_pick = m_pickPart[m_displayListID % YO_HASH_SIZE];
				m_pickPart[m_displayListID % YO_HASH_SIZE] = ptrPart;
				// reserve next displayListID for part's alternate origin
				m_displayListID++;
				return m_displayListID - 1;
			}
			else if (ptrTag != NULL)
			{
				ptrTag->m_pick = m_pickTag[m_displayListID % YO_HASH_SIZE];
				m_pickTag[m_displayListID % YO_HASH_SIZE] = ptrTag;
				return m_displayListID;
			}

	}
	return 0;
}


void CStageDoc::YoMakeDisplayLists(GLint mode)
{
	CStageDevice *currentDevice;
	CStageDevice *ptrDevice;
	CStagePart *currentPart;
	CStagePart *ptrPart;

	m_deviceStack = NULL;

	for (currentDevice = m_deviceList; currentDevice != NULL;)
	{
		m_partStack = NULL;

		for (currentPart = currentDevice->m_ptrPart; currentPart != NULL;)
		{
			ptrPart = currentPart;
			if (currentPart->m_down != NULL)
			{
				if (currentPart->m_right != NULL)
				{
					YoPushPart(currentPart->m_right);
				}
				currentPart = currentPart->m_down;
			}
			else if (currentPart->m_right != NULL)
			{
				currentPart = currentPart->m_right;
			}
			else if (m_partStack != NULL)
			{
				currentPart = YoPopPart();
			}
			else 
			{
				currentPart = NULL; 
			}

			ptrPart->YoMakeDisplayList(mode);
		}

		ptrDevice = currentDevice;
		if (currentDevice->m_down != NULL)
		{
			if (currentDevice->m_right != NULL)
			{
				YoPushDevice(currentDevice->m_right);
			}
			currentDevice = currentDevice->m_down;
		}
		else if (currentDevice->m_right != NULL)
		{
			currentDevice = currentDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			currentDevice = YoPopDevice();
		}
		else 
		{
			currentDevice = NULL;
		}
	}
}


BOOL CStageDoc::YoPointOnCurrentPart(CPoint point)
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CStagePart *ptrPart;
	CStageDevice  *ptrDevice;

	if (m_currentDevice == NULL || m_currentPart == NULL)
	{
		return FALSE;
	}

	ptrPart = m_currentPart;
	ptrDevice = m_currentDevice;

	pView->YoRender(YO_RENDER_PICK_PART);
	YoMakeCurrentDevicePartTag(point);

	if (ptrPart == m_currentPart)
	{
		m_currentPart = ptrPart;
		m_currentDevice = ptrDevice;
		return TRUE;
	}
	else
	{
		m_currentPart = ptrPart;
		m_currentDevice = ptrDevice;
		return FALSE;
	}

}





BOOL CStageDoc::YoGetClosestPolygon(CPoint point)
// Finds the closest polygon of the current part and sets m_currentPolygonIndex and
// m_closestVertexIndex accordingly.
// m_mSnapTo matrix is aligned with either a part, vertex, edge, polygon, etc.
// to be used as a point for analysis, or a desired snapTo position.
// returns TRUE if polygon is found, false if not found.
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	GLdouble modelView[16];
	GLdouble proj[16];
	GLint viewport[4];
	GLdouble objx;
	GLdouble objy;
	GLdouble objz;
	GLdouble a[3];
	GLdouble b[3];
	GLdouble c[3];
	GLdouble e[3];
	GLdouble f[3];
	GLdouble v[3];
	GLdouble p[3];
	GLdouble minDistance = FLT_MAX;
	GLdouble d;
	GLfloat z[1];
	GLdouble d1;
	GLdouble d2;
	GLdouble minNormalDeviation = FLT_MAX;
	GLdouble m[16];
	int i;
	int j;
	int index;
	int prevVertexIndex;
	int nextVertexIndex;
	GLdouble prevVertex[3];
	GLdouble nextVertex[3];
	GLdouble closestVertex[3];
	CStageVertices *currentVertices;
	CStageVertices *ptrVerticesOfClosestPolygon;
	int numberSidesOfClosestPolygon;
	CStageVertexList *currentVertexList;
	CStagePolygonList *currentPolygonList;
	m_currentPolygonIndex = -1;
	GLfloat pt[3];
	GLint rBits;
	GLint gBits;
	GLint bBits;
	GLint red;
	GLint green;
	GLint blue;
	GLint powRed;
	GLint powGreen;
	GLint powBlue;
	//*numberSides = 0; 
	//ptrVertices = NULL;
	//ptrTexture = NULL;


	::glReadPixels(point.x, pView->m_windowSize[1] - point.y - 1, 1, 1,
		GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid *)z);

	::glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	::glGetDoublev(GL_PROJECTION_MATRIX, proj);
	::glGetIntegerv(GL_VIEWPORT, viewport);
			
	::gluUnProject((GLdouble) point.x,
		(GLdouble)(pView->m_windowSize[1] - point.y - 1),
		(GLdouble)z[0],
		m_modelViewOfCurrentPart,
		//modelView,
		proj,
		viewport,
		&objx,
		&objy,
		&objz);

	p[0] = objx;
	p[1] = objy;
	p[2] = objz;

	// find the same point in part coordinates
	//YoModelMatrixOfCurrentPart(modelView);
	//p[0] = p[0] - modelView[12];
	//p[1] = p[1] - modelView[13];
	//p[2] = p[2] - modelView[14];
	TRACE3("p(%lf, %lf, %lf\n", p[0], p[1], p[2]);

	YoModelMatrixOfCurrentPart(modelView);
	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glMultMatrixd(modelView);
	pView->YoRenderPartPolygons(m_currentPart, YO_RENDER_POLYGON);
	::glPopMatrix();

	::glGetIntegerv(GL_RED_BITS, &rBits);
	::glGetIntegerv(GL_GREEN_BITS, &gBits);
	::glGetIntegerv(GL_BLUE_BITS, &bBits);
	m_currentPolygonIndex = 0;

	for (i = 0; i < 3; i++)
		pt[i] = 0x00;

	::glReadPixels(point.x, pView->m_windowSize[1] - point.y - 1, 1, 1,
		GL_RGB, GL_FLOAT, (GLvoid *)pt);
  
	TRACE2("(x, y) = (%d, %d)\n", point.x, pView->m_windowSize[1] - point.y - 1);
	for (i = 0; i < 3; i++)
		TRACE2("%d: %f\n", i, pt[i]);
	powRed = (GLint)(pow(2.0, (double)rBits) - 1.0);
	pt[0] = pt[0] * powRed;
	powGreen = (GLint)(pow(2.0, (double)gBits) - 1.0);
	pt[1] = pt[1] * powGreen;
	powBlue = (GLint)(pow(2.0, (double)bBits) - 1.0);
	pt[2] = pt[2] * powBlue;

	if (pt[0] - floor(pt[0]) > 0.5)
	{
		red = (GLint)pt[0] + 1;
	}
	else
	{
		red = (GLint)pt[0];
	}
	if (pt[1] - floor(pt[1]) > 0.5)
	{
		green = (GLint)pt[1] + 1;
	}
	else
	{
		green = (GLint)pt[1];
	}
	if (pt[2] - floor(pt[2]) > 0.5)
	{
		blue = (GLint)pt[2] + 1;
	}
	else
	{
		blue = (GLint)pt[2];
	}

	for (i = 0; i < rBits; i++)
	{
		m_currentPolygonIndex += ((GLint)pow(2.0, (double)i) * ((red>>i) & 0x1));   
	}
	for (i = 0; i < gBits; i++)
	{
		m_currentPolygonIndex += ((GLint)pow(2.0, (double)(i + rBits)) * ((green>>i) & 0x1));   
	}
	for (i = 0; i < bBits; i++)
	{
		m_currentPolygonIndex += ((GLint)pow(2.0, (double)(i + rBits + gBits)) * ((blue>>i) & 0x1));   
	}

	if (m_currentPolygonIndex > m_currentPart->m_numberPolygons - 1
		|| m_currentPolygonIndex < 0)
	{
		m_currentPolygonIndex = 0;
	}

	index = m_currentPolygonIndex;
	for (currentPolygonList = m_currentPart->m_polygonList; index >= 10; currentPolygonList = currentPolygonList->m_next)
	{
		index -= 10;
	}

	ptrVerticesOfClosestPolygon = currentPolygonList->m_vertices[m_currentPolygonIndex % 10];
	numberSidesOfClosestPolygon = currentPolygonList->m_numberSides[m_currentPolygonIndex % 10];
	if (pMainFrame->m_analysisActive == TRUE)
	{
		if (pMainFrame->m_analysis->m_selected == 0)
		{
			pMainFrame->m_analysis->m_ptrPolygonVertices[0]
				= ptrVerticesOfClosestPolygon;
		}
		else if (pMainFrame->m_analysis->m_selected == 1)
		{
			pMainFrame->m_analysis->m_ptrPolygonVertices[1]
				= ptrVerticesOfClosestPolygon;
		}
	}

	if (m_currentPolygonIndex < 0)
	{
		m_closestVertexIndex = -1;
		return FALSE;
	}
	else
	{
		if ((pMainFrame->m_analysisActive == TRUE
			&& (pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_EDGE
			|| pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_EDGE_CENTER))
			|| (pMainFrame->m_viewPartActive == TRUE
			&& (pMainFrame->m_viewPart->m_snapTo == TRUE
			|| pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE)
			&& (pMainFrame->m_viewPart->m_snapToMode == YO_SNAP_EDGE
			|| pMainFrame->m_viewPart->m_snapToMode == YO_SNAP_EDGE_CENTER))
			|| (pMainFrame->m_trackDlgActive == TRUE
			&& pMainFrame->m_trackDialog->m_snapTo == TRUE
			&& (pMainFrame->m_trackDialog->m_snapToMode == YO_SNAP_EDGE
			|| pMainFrame->m_trackDialog->m_snapToMode == YO_SNAP_EDGE_CENTER))
			|| (pMainFrame->m_viewTagActive == TRUE
			&& (pMainFrame->m_viewTag->m_tagSnapMode == YO_SNAP_EDGE
			|| pMainFrame->m_viewTag->m_tagSnapMode == YO_SNAP_EDGE_CENTER)))
		{
			// find edge or edge center
			// first find index of closest vertex
			for (currentVertices = ptrVerticesOfClosestPolygon; currentVertices != NULL;)
			{
				for (j = 0; j < numberSidesOfClosestPolygon; j++)
				{
					index = currentVertices->m_vertex[j % 4];
					// lookup vertex
					for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
					{
						index -= 20;
					}
					d = sqrt((p[0] - currentVertexList->m_vertex[index][0]) * (p[0] - currentVertexList->m_vertex[index][0])
						+ (p[1] - currentVertexList->m_vertex[index][1]) * (p[1] - currentVertexList->m_vertex[index][1])
						+ (p[2] - currentVertexList->m_vertex[index][2]) * (p[2] - currentVertexList->m_vertex[index][2]));
					if (d < minDistance)
					{
						minDistance = d;
						m_closestVertexIndex = j;
						closestVertex[0] = currentVertexList->m_vertex[index][0];
						closestVertex[1] = currentVertexList->m_vertex[index][1];
						closestVertex[2] = currentVertexList->m_vertex[index][2];
					}
					if (j % 4 == 3)
					{
						currentVertices = currentVertices->m_next;
					}

				}
				currentVertices = NULL;
			}

			if (m_closestVertexIndex == 0)
			{
				prevVertexIndex = numberSidesOfClosestPolygon - 1;
				nextVertexIndex = 1;
			}
			else if (m_closestVertexIndex == numberSidesOfClosestPolygon - 1)
			{
				prevVertexIndex = numberSidesOfClosestPolygon - 2;
				nextVertexIndex = 0;
			}
			else
			{
				prevVertexIndex = m_closestVertexIndex - 1;
				nextVertexIndex = m_closestVertexIndex + 1;
			}

			index = prevVertexIndex;
			for (currentVertices = ptrVerticesOfClosestPolygon; index >= 4; currentVertices = currentVertices->m_next)
			{
				index -= 4;
			}
			index = currentVertices->m_vertex[index];
			// lookup vertex
			for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
			{
				index -= 20;
			}
			prevVertex[0] = currentVertexList->m_vertex[index][0];
			prevVertex[1] = currentVertexList->m_vertex[index][1];
			prevVertex[2] = currentVertexList->m_vertex[index][2];

			index = nextVertexIndex;
			for (currentVertices = ptrVerticesOfClosestPolygon; index >= 4; currentVertices = currentVertices->m_next)
			{
				index -= 4;
			}
			index = currentVertices->m_vertex[index];
			// lookup vertex
			for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
			{
				index -= 20;
			}
			nextVertex[0] = currentVertexList->m_vertex[index][0];
			nextVertex[1] = currentVertexList->m_vertex[index][1];
			nextVertex[2] = currentVertexList->m_vertex[index][2];

			c[0] = p[0] - closestVertex[0];
			c[1] = p[1] - closestVertex[1];
			c[2] = p[2] - closestVertex[2];

			a[0] = nextVertex[0] - closestVertex[0];
			a[1] = nextVertex[1] - closestVertex[1];
			a[2] = nextVertex[2] - closestVertex[2];
			YoNormalize(a);
			d2 = YO_DOT_PRODUCT(c, a);

			b[0] = prevVertex[0] - closestVertex[0];
			b[1] = prevVertex[1] - closestVertex[1];
			b[2] = prevVertex[2] - closestVertex[2];
			YoNormalize(b);
			d1 = YO_DOT_PRODUCT(c, b);

			YoCrossProduct(c, a, b);
			YoNormalize(c);

			if ((pMainFrame->m_analysisActive == TRUE
				&& pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_EDGE)
				|| (pMainFrame->m_viewPartActive == TRUE
				&& (pMainFrame->m_viewPart->m_snapTo == TRUE
				|| pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE)
				&& pMainFrame->m_viewPart->m_snapToMode == YO_SNAP_EDGE)
				|| (pMainFrame->m_trackDlgActive == TRUE
				&& pMainFrame->m_trackDialog->m_snapTo == TRUE
				&& pMainFrame->m_trackDialog->m_snapToMode == YO_SNAP_EDGE)
				|| (pMainFrame->m_viewTagActive == TRUE
				&& pMainFrame->m_viewTag->m_tagSnapMode == YO_SNAP_EDGE))
			{
				if (d2 >= d1)
				// pick point is closer to line with endpoints of closest vertex and next vertex
				{
					v[0] = closestVertex[0] + (a[0] * d2);
					v[1] = closestVertex[1] + (a[1] * d2);
					v[2] = closestVertex[2] + (a[2] * d2);
				}
				else
				// pick point is closer to line with endpoints of closest vertex and previous vertex
				{
					v[0] = closestVertex[0] + (b[0] * d1);
					v[1] = closestVertex[1] + (b[1] * d1);
					v[2] = closestVertex[2] + (b[2] * d1);
				}
			}
			else if ((pMainFrame->m_analysisActive == TRUE
				&& pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_EDGE_CENTER)
				|| (pMainFrame->m_viewPartActive == TRUE
				&& (pMainFrame->m_viewPart->m_snapTo == TRUE
				|| pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE)
				&& pMainFrame->m_viewPart->m_snapToMode == YO_SNAP_EDGE_CENTER)
				|| (pMainFrame->m_trackDlgActive == TRUE
				&& pMainFrame->m_trackDialog->m_snapTo == TRUE
				&& pMainFrame->m_trackDialog->m_snapToMode == YO_SNAP_EDGE_CENTER)
				|| (pMainFrame->m_viewTagActive == TRUE
				&& pMainFrame->m_viewTag->m_tagSnapMode == YO_SNAP_EDGE_CENTER))
			{
				if (d2 >= d1)
				// pick point is closer to line with endpoints of closest vertex and next vertex
				{
					v[0] = (closestVertex[0] + nextVertex[0]) * 0.5;
					v[1] = (closestVertex[1] + nextVertex[1]) * 0.5;
					v[2] = (closestVertex[2] + nextVertex[2]) * 0.5;
				}
				else
				// pick point is closer to line with endpoints of closest vertex and previous vertex
				{
					v[0] = (closestVertex[0] + prevVertex[0]) * 0.5;
					v[1] = (closestVertex[1] + prevVertex[1]) * 0.5;
					v[2] = (closestVertex[2] + prevVertex[2]) * 0.5;
				}
			}

			if ((pMainFrame->m_viewPartActive == TRUE
			&& (pMainFrame->m_viewPart->m_snapTo == TRUE
			|| pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE))
			||(pMainFrame->m_trackDlgActive == TRUE
			&& pMainFrame->m_trackDialog->m_snapTo == TRUE)
			|| pMainFrame->m_viewTagActive == TRUE)
			{
				m_mSnapTo[12] = v[0];
				m_mSnapTo[13] = v[1];
				m_mSnapTo[14] = v[2];
				m_mSnapTo[15] = 1.0f;

				if (d1 > d2)
				{
					a[0] = closestVertex[0] - prevVertex[0];
					a[1] = closestVertex[1] - prevVertex[1];
					a[2] = closestVertex[2] - prevVertex[2];
					YoNormalize(a);
				}

				YoCrossProduct(b, c, a);
				YoNormalize(b);

				for (i = 0; i < 3; i++)
				{
					m_mSnapTo[i] = a[i];
					m_mSnapTo[i + 4] = b[i];
					m_mSnapTo[i + 8] = c[i];
				}
				m_mSnapTo[3] = 0.0f;
				m_mSnapTo[7] = 0.0f;
				m_mSnapTo[11] = 0.0f;

				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				YoModelMatrixOfCurrentPart(m);
				::glLoadMatrixd(m);
				::glMultMatrixd(m_mSnapTo);
				::glGetDoublev(GL_MODELVIEW_MATRIX, m_mSnapTo);
				::glPopMatrix();
			}
		}
		else if ((pMainFrame->m_analysisActive == TRUE
			&& pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_POLYGON)
			|| (pMainFrame->m_viewPartActive == TRUE
			&& (pMainFrame->m_viewPart->m_snapTo == TRUE
			|| pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE)
			&& pMainFrame->m_viewPart->m_snapToMode == YO_SNAP_POLYGON)
			|| (pMainFrame->m_trackDlgActive == TRUE
			&& pMainFrame->m_trackDialog->m_snapTo == TRUE
			&& pMainFrame->m_trackDialog->m_snapToMode == YO_SNAP_POLYGON)
			|| (pMainFrame->m_viewTagActive == TRUE
			&& pMainFrame->m_viewTag->m_tagSnapMode == YO_SNAP_POLYGON))
		{
			for (currentVertices = ptrVerticesOfClosestPolygon; currentVertices != NULL;)
			{
				index = currentVertices->m_vertex[0];
				// lookup vertex
				for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
				{
					index -= 20;
				}
				closestVertex[0] = currentVertexList->m_vertex[index][0];
				closestVertex[1] = currentVertexList->m_vertex[index][1];
				closestVertex[2] = currentVertexList->m_vertex[index][2];
				currentVertices = NULL;
			}


			prevVertexIndex = numberSidesOfClosestPolygon - 1;
			nextVertexIndex = 1;

			index = prevVertexIndex;
			for (currentVertices = ptrVerticesOfClosestPolygon; index >= 4; currentVertices = currentVertices->m_next)
			{
				index -= 4;
			}
			index = currentVertices->m_vertex[index];
			// lookup vertex
			for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
			{
				index -= 20;
			}
			prevVertex[0] = currentVertexList->m_vertex[index][0];
			prevVertex[1] = currentVertexList->m_vertex[index][1];
			prevVertex[2] = currentVertexList->m_vertex[index][2];

			index = nextVertexIndex;
			for (currentVertices = ptrVerticesOfClosestPolygon; index >= 4; currentVertices = currentVertices->m_next)
			{
				index -= 4;
			}
			index = currentVertices->m_vertex[index];
			// lookup vertex
			for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
			{
				index -= 20;
			}
			nextVertex[0] = currentVertexList->m_vertex[index][0];
			nextVertex[1] = currentVertexList->m_vertex[index][1];
			nextVertex[2] = currentVertexList->m_vertex[index][2];

			a[0] = nextVertex[0] - closestVertex[0];
			a[1] = nextVertex[1] - closestVertex[1];
			a[2] = nextVertex[2] - closestVertex[2];
			YoNormalize(a);

			b[0] = prevVertex[0] - closestVertex[0];
			b[1] = prevVertex[1] - closestVertex[1];
			b[2] = prevVertex[2] - closestVertex[2];
			YoNormalize(b);

			YoCrossProduct(c, a, b);
			YoNormalize(c);
			YoCrossProduct(b, c, a);
			YoNormalize(b);

			e[0] = closestVertex[0] - p[0];
			e[1] = closestVertex[1] - p[1];
			e[2] = closestVertex[2] - p[2];
			d1 = YO_DOT_PRODUCT(e, c);
			f[0] = c[0] * d1;
			f[1] = c[1] * d1;
			f[2] = c[2] * d1;

			if ((pMainFrame->m_viewPartActive == TRUE
			&& (pMainFrame->m_viewPart->m_snapTo == TRUE
			|| pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE))
			|| (pMainFrame->m_trackDlgActive == TRUE
			&& pMainFrame->m_trackDialog->m_snapTo == TRUE)
			|| pMainFrame->m_viewTagActive == TRUE)
			{
				m_mSnapTo[12] = p[0] + f[0];
				m_mSnapTo[13] = p[1] + f[1];
				m_mSnapTo[14] = p[2] + f[2];
				m_mSnapTo[15] = 1.0f;

				for (i = 0; i < 3; i++)
				{
					m_mSnapTo[i] = a[i];
					m_mSnapTo[i + 4] = b[i];
					m_mSnapTo[i + 8] = c[i];
				}
				m_mSnapTo[3] = 0.0f;
				m_mSnapTo[7] = 0.0f;
				m_mSnapTo[11] = 0.0f;

				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				YoModelMatrixOfCurrentPart(m);
				::glLoadMatrixd(m);
				::glMultMatrixd(m_mSnapTo);
				::glGetDoublev(GL_MODELVIEW_MATRIX, m_mSnapTo);
				::glPopMatrix();
			}
			else
			{
				v[0] = p[0] + f[0];
				v[1] = p[1] + f[1];
				v[2] = p[2] + f[2];
			}
		}

		else if ((pMainFrame->m_analysisActive == TRUE
			&& pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_POLYGON_CENTER)
			|| (pMainFrame->m_viewPartActive == TRUE
			&& (pMainFrame->m_viewPart->m_snapTo == TRUE
			|| pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE)
			&& pMainFrame->m_viewPart->m_snapToMode == YO_SNAP_POLYGON_CENTER)
			|| (pMainFrame->m_trackDlgActive == TRUE
			&& pMainFrame->m_trackDialog->m_snapTo == TRUE
			&& pMainFrame->m_trackDialog->m_snapToMode == YO_SNAP_POLYGON_CENTER)
			|| (pMainFrame->m_viewTagActive == TRUE
			&& pMainFrame->m_viewTag->m_tagSnapMode == YO_SNAP_POLYGON_CENTER))
		{
			// find polygon center
			v[0] = 0.0;
			v[1] = 0.0;
			v[2] = 0.0;

			for (currentVertices = ptrVerticesOfClosestPolygon; currentVertices != NULL;)
			{
				for (j = 0; j < numberSidesOfClosestPolygon; j++)
				{
					index = currentVertices->m_vertex[j % 4];
					// lookup vertex
					for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
					{
						index -= 20;
					}
					v[0] += currentVertexList->m_vertex[index][0];
					v[1] += currentVertexList->m_vertex[index][1];
					v[2] += currentVertexList->m_vertex[index][2];

					if (j == 0)
					// make closest vertex the first vertex listed in the polygon
					{
						m_closestVertexIndex = j;
						closestVertex[0] = currentVertexList->m_vertex[index][0];
						closestVertex[1] = currentVertexList->m_vertex[index][1];
						closestVertex[2] = currentVertexList->m_vertex[index][2];
					}
					if (j % 4 == 3)
					{
						currentVertices = currentVertices->m_next;
					}

				}
				currentVertices = NULL;
			}

			v[0] /= numberSidesOfClosestPolygon;
			v[1] /= numberSidesOfClosestPolygon;
			v[2] /= numberSidesOfClosestPolygon;

			if ((pMainFrame->m_viewPartActive == TRUE
			&& (pMainFrame->m_viewPart->m_snapTo == TRUE
			|| pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE))
			|| (pMainFrame->m_trackDlgActive == TRUE
			&& pMainFrame->m_trackDialog->m_snapTo == TRUE)
			|| pMainFrame->m_viewTagActive == TRUE)
			{
				if (m_closestVertexIndex == 0)
				{
					prevVertexIndex = numberSidesOfClosestPolygon - 1;
					nextVertexIndex = 1;
				}
				else if (m_closestVertexIndex == numberSidesOfClosestPolygon - 1)
				{
					prevVertexIndex = numberSidesOfClosestPolygon - 2;
					nextVertexIndex = 0;
				}
				else
				{
					prevVertexIndex = m_closestVertexIndex - 1;
					nextVertexIndex = m_closestVertexIndex + 1;
				}

				index = prevVertexIndex;
				for (currentVertices = ptrVerticesOfClosestPolygon; index >= 4; currentVertices = currentVertices->m_next)
				{
					index -= 4;
				}
				index = currentVertices->m_vertex[index];
				// lookup vertex
				for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
				{
					index -= 20;
				}
				prevVertex[0] = currentVertexList->m_vertex[index][0];
				prevVertex[1] = currentVertexList->m_vertex[index][1];
				prevVertex[2] = currentVertexList->m_vertex[index][2];

				index = nextVertexIndex;
				for (currentVertices = ptrVerticesOfClosestPolygon; index >= 4; currentVertices = currentVertices->m_next)
				{
					index -= 4;
				}
				index = currentVertices->m_vertex[index];
				// lookup vertex
				for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
				{
					index -= 20;
				}
				nextVertex[0] = currentVertexList->m_vertex[index][0];
				nextVertex[1] = currentVertexList->m_vertex[index][1];
				nextVertex[2] = currentVertexList->m_vertex[index][2];

				a[0] = nextVertex[0] - closestVertex[0];
				a[1] = nextVertex[1] - closestVertex[1];
				a[2] = nextVertex[2] - closestVertex[2];
				YoNormalize(a);

				b[0] = prevVertex[0] - closestVertex[0];
				b[1] = prevVertex[1] - closestVertex[1];
				b[2] = prevVertex[2] - closestVertex[2];
				YoNormalize(b);

				YoCrossProduct(c, a, b);
				YoNormalize(c);
				YoCrossProduct(b, c, a);
				YoNormalize(b);

				m_mSnapTo[12] = v[0];
				m_mSnapTo[13] = v[1];
				m_mSnapTo[14] = v[2];
				m_mSnapTo[15] = 1.0f;

				for (i = 0; i < 3; i++)
				{
					m_mSnapTo[i] = a[i];
					m_mSnapTo[i + 4] = b[i];
					m_mSnapTo[i + 8] = c[i];
				}
				m_mSnapTo[3] = 0.0f;
				m_mSnapTo[7] = 0.0f;
				m_mSnapTo[11] = 0.0f;

				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				YoModelMatrixOfCurrentPart(m);
				::glLoadMatrixd(m);
				::glMultMatrixd(m_mSnapTo);
				::glGetDoublev(GL_MODELVIEW_MATRIX, m_mSnapTo);
				::glPopMatrix();
			}
		}
		else if ((pMainFrame->m_analysisActive == TRUE
			&& pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_VERTEX)
			|| (pMainFrame->m_viewPartActive == TRUE
			&& (pMainFrame->m_viewPart->m_snapTo == TRUE
			|| pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE)
			&& pMainFrame->m_viewPart->m_snapToMode == YO_SNAP_VERTEX)
			|| (pMainFrame->m_trackDlgActive == TRUE
			&& pMainFrame->m_trackDialog->m_snapTo == TRUE
			&& pMainFrame->m_trackDialog->m_snapToMode == YO_SNAP_VERTEX)
			|| (pMainFrame->m_viewTagActive == TRUE
			&& pMainFrame->m_viewTag->m_tagSnapMode == YO_SNAP_VERTEX))
		{
			for (currentVertices = ptrVerticesOfClosestPolygon; currentVertices != NULL;)
			{
				for (j = 0; j < numberSidesOfClosestPolygon; j++)
				{
					index = currentVertices->m_vertex[j % 4];
					// lookup vertex
					for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
					{
						index -= 20;
					}
					d = sqrt((p[0] - currentVertexList->m_vertex[index][0]) * (p[0] - currentVertexList->m_vertex[index][0])
						+ (p[1] - currentVertexList->m_vertex[index][1]) * (p[1] - currentVertexList->m_vertex[index][1])
						+ (p[2] - currentVertexList->m_vertex[index][2]) * (p[2] - currentVertexList->m_vertex[index][2]));
					if (d < minDistance)
					{
						minDistance = d;
						m_closestVertexIndex = j;
						v[0] = currentVertexList->m_vertex[index][0];
						v[1] = currentVertexList->m_vertex[index][1];
						v[2] = currentVertexList->m_vertex[index][2];
					}
					if (j % 4 == 3)
					{
						currentVertices = currentVertices->m_next;
					}

				}
				currentVertices = NULL;
			}

			if ((pMainFrame->m_viewPartActive == TRUE
			&& (pMainFrame->m_viewPart->m_snapTo == TRUE
			|| pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE))
			|| (pMainFrame->m_trackDlgActive == TRUE
			&& pMainFrame->m_trackDialog->m_snapTo == TRUE)
			|| pMainFrame->m_viewTagActive == TRUE)
			{
				if (m_closestVertexIndex == 0)
				{
					prevVertexIndex = numberSidesOfClosestPolygon - 1;
					nextVertexIndex = 1;
				}
				else if (m_closestVertexIndex == numberSidesOfClosestPolygon - 1)
				{
					prevVertexIndex = numberSidesOfClosestPolygon - 2;
					nextVertexIndex = 0;
				}
				else
				{
					prevVertexIndex = m_closestVertexIndex - 1;
					nextVertexIndex = m_closestVertexIndex + 1;
				}

				index = prevVertexIndex;
				for (currentVertices = ptrVerticesOfClosestPolygon; index >= 4; currentVertices = currentVertices->m_next)
				{
					index -= 4;
				}
				index = currentVertices->m_vertex[index];
				// lookup vertex
				for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
				{
					index -= 20;
				}
				prevVertex[0] = currentVertexList->m_vertex[index][0];
				prevVertex[1] = currentVertexList->m_vertex[index][1];
				prevVertex[2] = currentVertexList->m_vertex[index][2];

				index = nextVertexIndex;
				for (currentVertices = ptrVerticesOfClosestPolygon; index >= 4; currentVertices = currentVertices->m_next)
				{
					index -= 4;
				}
				index = currentVertices->m_vertex[index];
				// lookup vertex
				for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
				{
					index -= 20;
				}
				nextVertex[0] = currentVertexList->m_vertex[index][0];
				nextVertex[1] = currentVertexList->m_vertex[index][1];
				nextVertex[2] = currentVertexList->m_vertex[index][2];

				a[0] = nextVertex[0] - v[0];
				a[1] = nextVertex[1] - v[1];
				a[2] = nextVertex[2] - v[2];
				YoNormalize(a);

				b[0] = prevVertex[0] - v[0];
				b[1] = prevVertex[1] - v[1];
				b[2] = prevVertex[2] - v[2];
				YoNormalize(b);

				YoCrossProduct(c, a, b);
				YoNormalize(c);
				YoCrossProduct(b, c, a);
				YoNormalize(b);

				m_mSnapTo[12] = v[0];
				m_mSnapTo[13] = v[1];
				m_mSnapTo[14] = v[2];
				m_mSnapTo[15] = 1.0f;

				for (i = 0; i < 3; i++)
				{
					m_mSnapTo[i] = a[i];
					m_mSnapTo[i + 4] = b[i];
					m_mSnapTo[i + 8] = c[i];
				}
				m_mSnapTo[3] = 0.0f;
				m_mSnapTo[7] = 0.0f;
				m_mSnapTo[11] = 0.0f;

				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				YoModelMatrixOfCurrentPart(m);
				::glLoadMatrixd(m);
				::glMultMatrixd(m_mSnapTo);
				::glGetDoublev(GL_MODELVIEW_MATRIX, m_mSnapTo);
				::glPopMatrix();
			}
		}
		else
		// find the closest vertex to position a potential texture map
		{
			for (currentVertices = ptrVerticesOfClosestPolygon; currentVertices != NULL;)
			{
				for (j = 0; j < numberSidesOfClosestPolygon; j++)
				{
					index = currentVertices->m_vertex[j % 4];
					// lookup vertex
					for (currentVertexList = m_currentPart->m_vertexList; index >= 20; currentVertexList = currentVertexList->m_next)
					{
						index -= 20;
					}
					d = sqrt((p[0] - currentVertexList->m_vertex[index][0]) * (p[0] - currentVertexList->m_vertex[index][0])
						+ (p[1] - currentVertexList->m_vertex[index][1]) * (p[1] - currentVertexList->m_vertex[index][1])
						+ (p[2] - currentVertexList->m_vertex[index][2]) * (p[2] - currentVertexList->m_vertex[index][2]));
					if (d < minDistance)
					{
						minDistance = d;
						m_closestVertexIndex = j;
					}
					if (j % 4 == 3)
					{
						currentVertices = currentVertices->m_next;
					}

				}
				currentVertices = NULL;
			}
		}
	}

	/// find analysis pick point in world coordinates
	if (pMainFrame->m_analysisActive == TRUE)
	{
		if (pMainFrame->m_analysis->m_selected == 0
			|| pMainFrame->m_analysis->m_selected == 2)
		{
			//d = sqrt((m_eye[3] - m_eye[0]) * (m_eye[3] - m_eye[0])
			//	+ (m_eye[4] - m_eye[1]) * (m_eye[4] - m_eye[1])
			//	+ (m_eye[5] - m_eye[2]) * (m_eye[5] - m_eye[2]))
			//	* m_fieldOfView * .001;
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			YoModelMatrixOfCurrentPart(m);
			::glLoadMatrixd(m);
			::glTranslated(v[0], v[1], v[2]);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			// m_analysisPointInWorldCoords also used for snap to
			pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][0] = m[12];
			pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1] = m[13];
			pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2] = m[14];
			pMainFrame->m_analysis->m_ptrDevice[0] = m_currentDevice;
			pMainFrame->m_analysis->m_ptrTag[0] = NULL;
			::glPopMatrix();
		}
		if (pMainFrame->m_analysis->m_selected == 1)
		{
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			YoModelMatrixOfCurrentPart(m);
			::glLoadMatrixd(m);
			::glTranslated(v[0], v[1], v[2]);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0] = m[12];
			pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1] = m[13];
			pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][2] = m[14];
			pMainFrame->m_analysis->m_ptrDevice[1] = m_currentDevice;
			pMainFrame->m_analysis->m_ptrTag[1] = NULL;
			::glPopMatrix();
		}
	}

	return TRUE;
}



UINT CStageDoc::YoMakeCurrentDevicePartTag(CPoint point)
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return 0;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return 0;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return 0;
	}
	GLfloat p[3];
	GLint rBits;
	GLint gBits;
	GLint bBits;
	GLint red;
	GLint green;
	GLint blue;
	GLint powRed;
	GLint powGreen;
	GLint powBlue;
	GLint displayListID;
	glGetIntegerv(GL_RED_BITS, &rBits);
	glGetIntegerv(GL_GREEN_BITS, &gBits);
	glGetIntegerv(GL_BLUE_BITS, &bBits);
	displayListID = 0;
	CStageDevice *ptrDevice;
	CStagePart *ptrPart;
	CStagePart *ptrPickPart;
	CStageTag *ptrPickTag;
	int i;


	TRACE3("rgb bits =  %d %d %d\n", rBits, gBits, bBits);
	for (i = 0; i < 3; i++)
		p[i] = 0x00;

	::glReadPixels(point.x, pView->m_windowSize[1] - point.y - 1, 1, 1,
		GL_RGB, GL_FLOAT, (GLvoid *)p);
  
	TRACE2("(x, y) = (%d, %d)\n", point.x, pView->m_windowSize[1] - point.y - 1);
	for (i = 0; i < 3; i++)
		TRACE2("%d: %f\n", i, p[i]);
	powRed = (GLint)(pow(2.0, (double)rBits) - 1.0);
	p[0] = p[0] * powRed;
	powGreen = (GLint)(pow(2.0, (double)gBits) - 1.0);
	p[1] = p[1] * powGreen;
	powBlue = (GLint)(pow(2.0, (double)bBits) - 1.0);
	p[2] = p[2] * powBlue;

	if (p[0] - floor(p[0]) > 0.5)
	{
		red = (GLint)p[0] + 1;
	}
	else
	{
		red = (GLint)p[0];
	}
	if (p[1] - floor(p[1]) > 0.5)
	{
		green = (GLint)p[1] + 1;
	}
	else
	{
		green = (GLint)p[1];
	}
	if (p[2] - floor(p[2]) > 0.5)
	{
		blue = (GLint)p[2] + 1;
	}
	else
	{
		blue = (GLint)p[2];
	}

	for (i = 0; i < rBits; i++)
	{
		displayListID += ((GLint)pow(2.0, (double)i) * ((red>>i) & 0x1));   
	}
	for (i = 0; i < gBits; i++)
	{
		displayListID += ((GLint)pow(2.0, (double)(i + rBits)) * ((green>>i) & 0x1));   
	}
	for (i = 0; i < bBits; i++)
	{
		displayListID += ((GLint)pow(2.0, (double)(i + rBits + gBits)) * ((blue>>i) & 0x1));   
	}

	if (displayListID == 0)
	{
		return 0;
	}

	for (ptrPickPart = m_pickPart[displayListID % YO_HASH_SIZE];
		ptrPickPart != NULL && ptrPickPart->m_displayListID != displayListID;
		ptrPickPart = ptrPickPart->m_pick);

	if (ptrPickPart != NULL)
	{
		m_currentPart = ptrPickPart;
		m_currentDevice = YoDeviceHashLookup(m_currentPart->m_deviceName);
		return YO_DEVICE_PART;
	}

	for (ptrPickTag = m_pickTag[displayListID % YO_HASH_SIZE];
		ptrPickTag != NULL && ptrPickTag->m_displayListID != displayListID;
		ptrPickTag = ptrPickTag->m_pick);

	if (ptrPickTag != NULL)
	{
		m_currentTag = ptrPickTag;
		YoModelMatrixOfCurrentTag();
		return YO_TAG;
	}

	// check to see if coordinate system of a part has been picked
	// m_mTag is altered but m_currentPart, m_currentDevice, and m_currentTag are not
	for (ptrPickPart = m_pickPart[(displayListID - 1) % YO_HASH_SIZE];
		ptrPickPart != NULL && ptrPickPart->m_displayListID != displayListID - 1;
		ptrPickPart = ptrPickPart->m_pick);

	if (ptrPickPart != NULL)
	{
		ptrPart = m_currentPart;
		ptrDevice = m_currentDevice;
		m_currentPart = ptrPickPart;
		m_currentDevice = YoDeviceHashLookup(m_currentPart->m_deviceName);
		YoModelMatrixOfCurrentPart(m_mTag);
		if (m_currentPart->m_altOriginDisplayed == TRUE)
		{
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadMatrixd(m_mTag);
			::glMultMatrixd(m_currentPart->m_altOrigin);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m_mTag);
			::glPopMatrix();
		}
		m_currentPart = ptrPart;
		m_currentDevice = ptrDevice;
		return YO_TAG;
	}

	/***
	// update device transformation dialog
	for (i = 0; i < 3; i++)
	{
		YoValidateRotate(&m_currentDevice->m_ptrPart->m_rotate[i]);
		pMainFrame->m_wndDlgDeviceTransformation->m_translateOrig[i]
			= m_currentDevice->m_ptrPart->m_translate[i];
		pMainFrame->m_wndDlgDeviceTransformation->m_rotateOrig[i]
			= m_currentDevice->m_ptrPart->m_rotate[i];
	}

	sprintf(s, "%.1lf", pMainFrame->m_wndDlgDeviceTransformation->m_translateOrig[pMainFrame->m_wndDlgDeviceTransformation->m_xyz]);
	pCBox = (CComboBox*)pMainFrame->m_wndDlgDeviceTransformation->GetDlgItem(IDC_TRANSLATE);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	sprintf(s, "%.1lf", pMainFrame->m_wndDlgDeviceTransformation->m_rotateOrig[pMainFrame->m_wndDlgDeviceTransformation->m_xyz]);
	pCBox = (CComboBox*)pMainFrame->m_wndDlgDeviceTransformation->GetDlgItem(IDC_ROTATE);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	pCBox = (CComboBox*)pMainFrame->m_wndDlgDeviceTransformation->GetDlgItem(IDC_SLIDER_ROTATE);
	((CSliderCtrl *)pCBox)->SetRange((int)pMainFrame->m_wndDlgDeviceTransformation->m_rotateOrig[pMainFrame->m_wndDlgDeviceTransformation->m_xyz] - 180,
		(int)pMainFrame->m_wndDlgDeviceTransformation->m_rotateOrig[pMainFrame->m_wndDlgDeviceTransformation->m_xyz] + 180, TRUE);
	((CSliderCtrl *)pCBox)->SetPos((int)pMainFrame->m_wndDlgDeviceTransformation->m_rotateOrig[pMainFrame->m_wndDlgDeviceTransformation->m_xyz]);
	***/

	return 0;

}

void CStageDoc::YoUpdateScore(void)
{

// object list is traversed and the score is updated in yo_part_update_score */
// for each part with motion_effect_modified = TRUE */
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	BOOL done = FALSE;
	BOOL pdone;
	CStageDevice *ptrDevice = m_deviceList; 
	CStagePart *ptrPart;
	//Camera_effect_node	*ceptr = camera->effect;

	m_motionEffectModified = FALSE;

	YoFreeEyeScore();
	YoHandleEyeMotion();
	/***
	while (ceptr != NULL)
	{
		yo_handle_camera_effect(ceptr);
		ceptr = ceptr->next;
	}
	*****/
	m_eyeList->m_currentScore = m_eyeList->m_score;

	m_deviceStack = NULL;

	if (ptrDevice == NULL)
	{
		return;
	}

	//yo_print_message("composing motion and effects ...", obj_message);

	while (!done)
	{
		glPushMatrix();
		glScaled(ptrDevice->m_scale[0],
			ptrDevice->m_scale[1], ptrDevice->m_scale[2]);
		ptrPart = ptrDevice->m_ptrPart;
		m_partStack = NULL;
		pdone = FALSE;

		while (!pdone)
		{
			if (ptrPart != ptrDevice->m_ptrPart)
			{
				glPushMatrix();
			}
	
			((CStageView *)pView)->YoTxyz(ptrPart,
				ptrPart->m_translate, ptrPart->m_rotate);

			if (ptrPart->m_motionEffectModified == TRUE
				|| m_motionEffectModified == YO_MOTION_EFFECT_MODIFIED_ALL)
			{
				YoUpdatePartScore(ptrPart);
				ptrPart->m_motionEffectModified = FALSE;
			}

			if (ptrPart->m_down != NULL)
			{
				if (ptrPart->m_right != NULL)
				{
					YoPushPart(ptrPart->m_right);
				}
				else
				{
					YoPushPart(NULL);
				}
				ptrPart = ptrPart->m_down;
			}
			else if (ptrPart->m_right != NULL)
			{
				ptrPart = ptrPart->m_right;
				glPopMatrix();
			}
			else if (YoAllStackPartsNull() == FALSE)
			{
				glPopMatrix();
				while ((ptrPart = YoPopPart()) == NULL)
				{
					glPopMatrix();
				}
			}
			else
			{
				while (m_partStack != NULL
					&& (ptrPart = YoPopPart()) == NULL)
				{
					glPopMatrix();
				}
				pdone = TRUE;
			}
		}  // end while (!pdone)

		glScaled(1.0 / ptrDevice->m_scale[0],
			1.0 / ptrDevice->m_scale[1], 1.0 / ptrDevice->m_scale[2]);

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			else
			{
				YoPushDevice(NULL);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
			glPopMatrix();
		}
		else if (YoAllStackDevicesNull() == FALSE)
		{
			glPopMatrix();
			glPopMatrix();
			while ((ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
		}
		else
		{
			glPopMatrix();
			while (m_deviceStack != NULL
				&& (ptrDevice = YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
			done = TRUE;
		}
	} // end while (!done)

	return;
}

void CStageDoc::YoUpdatePartScore(CStagePart *ptrPart)

// for ptrPart, the score is first reinitialized to empty, then updated
// based on information given in motion and effect nodes */

{
	CStageEffect   *ptrEffect = ptrPart->m_effect;

	YoFreeScore(ptrPart);
	YoHandleMotion(ptrPart);

	/****
	while (ptrEffect != NULL)
	{
		YoHandleEffect(ptrPart, ptrEffect);
		ptrEffect = ptrEffect->m_next;
	}
	****/

	ptrPart->m_currentScore = ptrPart->m_score;
	
	return;
}


void CStageDoc::YoFreeScore(CStagePart *ptrPart)

// frees all nodes in the score list for a particular part
// and sets ptrPart->m_score to NULL

{
	CStageScore			*curScore = ptrPart->m_score;
	CStageScore			*ptrScore;

	while (curScore != NULL)
	{
		ptrScore = curScore;
		curScore = curScore->m_next;
		delete(ptrScore);
	}

	ptrPart->m_score = NULL;
	ptrPart->m_currentScore = NULL;
	return;

}


void CStageDoc::YoFreeEyeList()
{
	CStageEyeMotion  *curEyeMotion = m_eyeList->m_motion;
	CStageEyeMotion  *ptrEyeMotion = NULL;
	//CStageEyeEffect  *curEyeEffect = m_eyeList->m_effect;
	//CStageEyeEffect  *ptrEyeEffect = NULL;
	CStageEyeScore  *curEyeScore = m_eyeList->m_score;
	CStageEyeScore  *ptrEyeScore = NULL;

	while (curEyeMotion != NULL)
	{
		ptrEyeMotion = curEyeMotion; 
		curEyeMotion = curEyeMotion->m_next;
		delete(ptrEyeMotion);
	}
	m_eyeList->m_motion = NULL;

	/***
	while (curEyeEffect != NULL)
	{
		ptrEyeEffect = curEyeEffect; 
		curEyeEffect = curEyeEffect->m_next;
		delete(ptrEyeEffect);
	}
	m_eyeList->m_effect = NULL;
	***/

	while (curEyeScore != NULL)
	{
		ptrEyeScore = curEyeScore; 
		curEyeScore = curEyeScore->m_next;
		delete(ptrEyeScore);
	}
	m_eyeList->m_score = NULL;
	m_eyeList->m_currentScore = NULL;
	
}


void CStageDoc::YoFreeEyeScore()

// frees all nodes in the eye score list
// and sets m_eyeList->m_score and m_eyeList->m_currentScore to NULL

{
	CStageEyeScore	*curEyeScore = m_eyeList->m_score;
	CStageEyeScore	*ptrEyeScore;

	while (curEyeScore != NULL)
	{
		ptrEyeScore = curEyeScore;
		curEyeScore = curEyeScore->m_next;
		delete(ptrEyeScore);
	}

	m_eyeList->m_score = NULL;
	m_eyeList->m_currentScore = NULL;
	return;

}

void CStageDoc::YoRestoreCurrentScore(void)

// restores m_currentScore for all parts and the eye 

{
	BOOL			done = FALSE;
	BOOL			pdone;
	CStageDevice	*ptrDevice = m_deviceList;
	CStagePart		*ptrPart;

	m_deviceStack = NULL;
	m_timeModified = FALSE;
	m_eyeList->m_currentScore = m_eyeList->m_score;

	if (ptrDevice == NULL)
	{
		return;
	}

	while (!done)
	{
		ptrPart = ptrDevice->m_ptrPart;
		m_partStack = NULL;
		pdone = FALSE;

		while (!pdone)
		{
			ptrPart->m_currentScore = ptrPart->m_score;
			if (ptrPart->m_down != NULL)
			{
				if (ptrPart->m_right != NULL)
				{
					YoPushPart(ptrPart->m_right);
				}
				ptrPart = ptrPart->m_down;
			}
			else if (ptrPart->m_right != NULL)
			{
				ptrPart = ptrPart->m_right;
			}
			else if (m_partStack != NULL)
			{
				ptrPart = YoPopPart();
			}
			else
			{
				pdone = TRUE;
			}
		} // end while (!pdone)

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			ptrDevice = YoPopDevice();
		}
		else
		{
			done = TRUE;
		}
	}  // end while (!done)
	
	return;
}

void CStageDoc::YoHandleMotion(CStagePart *ptrPart)

// creates motion in the score

{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}	
	CStageMotion *curMotion = ptrPart->m_motion;
	CStageMotion *ptrMotion = NULL;
	CStageScore *ptrScore;
	CStageScore *prevScore = NULL;
	CStageScore *curScore = ptrPart->m_score;
	GLint i;
	GLint j;
	GLdouble d[3];
	GLdouble r[3];
	GLdouble tr[3];
	GLdouble ro[3];
	GLdouble a;
	GLint t;

	while (curMotion != NULL)
	{
		if (curMotion->m_type == YO_MOTION_CONTROL)
		{
			curMotion->m_type = YO_MOTION_ANCHOR;
		}
		ptrMotion = curMotion;

		if (curMotion->m_type == YO_MOTION_HOLD
			|| curMotion->m_next == NULL)
		{
			ptrScore = new CStageScore(this);
			ptrScore->m_time = curMotion->m_time;
			ptrScore->m_next = NULL;
			::glPushMatrix();
			::glLoadIdentity();
			((CStageView *)pView)->YoTxyz(ptrPart, curMotion->m_translate, curMotion->m_rotate);
			::glGetDoublev(GL_MODELVIEW_MATRIX, ptrScore->m_modelView);
			::glPopMatrix();
			
			for (i = 0; i < 4; i++)
			{
				ptrScore->m_ambient[i] = ptrPart->m_ambient[i];
   				ptrScore->m_diffuse[i] = ptrPart->m_diffuse[i];
				ptrScore->m_specular[i] = ptrPart->m_specular[i];
				ptrScore->m_emission[i] = ptrPart->m_emission[i];
				ptrScore->m_wireframe[i] = ptrPart->m_wireframe[i];
			}
			ptrScore->m_shininess = ptrPart->m_shininess;
			
			/***
			if (ptrPart->m_texture != NULL)
			{
				ptrScore->m_textureAlpha = ptrPart->m_textureAlpha;
				for (i = 0; i < 4; i++)
				{
					ptrScore->m_sParameter[i] = ptrPart->m_sParameter[i];
					ptrScore->m_tParameter[i] = ptrPart->m_tParameter[i];
				}
			}
			else 
			{
				// -FLT_MAX is a sentinel which states that texturing
				// is not being used.
				ptrScore->m_textureAlpha = -INT_MAX;
				for (i = 0; i < 4; i++)
				{
					ptrScore->m_sParameter[i] = -FLT_MAX;
					ptrScore->m_tParameter[i] = -FLT_MAX;
				}
			}
			***/

			curMotion = curMotion->m_next;
			if (prevScore == NULL)
			{
				ptrPart->m_score = ptrScore;
			}
			else
			{
				prevScore->m_next = ptrScore;
			}
			ptrScore->m_next = curScore;
			prevScore = ptrScore;
		}
		else
		{
			curMotion = curMotion->m_next;
			while (curMotion->m_next != NULL
				&& curMotion->m_type == YO_MOTION_CONTROL)
			{
				curMotion = curMotion->m_next;
			}
			for (i = 0; i < 3; i++)
			{
				d[i] = curMotion->m_translate[i] - ptrMotion->m_translate[i];
				r[i] = curMotion->m_rotate[i] - ptrMotion->m_rotate[i];
			}
			t = curMotion->m_time - ptrMotion->m_time;
			for (i = ptrMotion->m_time; i < curMotion->m_time; i++)
			{
				ptrScore = new CStageScore(this);
				ptrScore->m_time = i;
				ptrScore->m_next = NULL;
				::glPushMatrix();
				::glLoadIdentity();
				a = (sin(-PI / 2.0 + (PI * (i - ptrMotion->m_time) / t)) + 1.0) / 2.0;
				tr[0] = ptrMotion->m_translate[0] + a * d[0];
				tr[1] = ptrMotion->m_translate[1] + a * d[1];
				tr[2] = ptrMotion->m_translate[2] + a * d[2];
				ro[0] = ptrMotion->m_rotate[0] + a * r[0];
				ro[1] = ptrMotion->m_rotate[1] + a * r[1];
				ro[2] = ptrMotion->m_rotate[2] + a * r[2];
				//      tr[0] = mprev->trans[0] + (i - mprev->time) * d[0] / t;
				//      tr[1] = mprev->trans[1] + (i - mprev->time) * d[1] / t;
				//      tr[2] = mprev->trans[2] + (i - mprev->time) * d[2] / t;
				//      ro[0] = mprev->rot[0] + (i - mprev->time) * r[0] / t;
				//     	ro[1] = mprev->rot[1] + (i - mprev->time) * r[1] / t;
				//      ro[2] = mprev->rot[2] + (i - mprev->time) * r[2] / t;
				((CStageView *)pView)->YoTxyz(ptrPart, tr, ro);
				::glGetDoublev(GL_MODELVIEW_MATRIX, ptrScore->m_modelView);
				::glPopMatrix();
				//yo_make_score_layers(pptr, sptr);
				
				for (j = 0; j < 4; j++)
				{
					ptrScore->m_ambient[j] = ptrPart->m_ambient[j];
   					ptrScore->m_diffuse[j] = ptrPart->m_diffuse[j];
					ptrScore->m_specular[j] = ptrPart->m_specular[j];
					ptrScore->m_emission[j] = ptrPart->m_emission[j];
					ptrScore->m_wireframe[j] = ptrPart->m_wireframe[j];
				}
				ptrScore->m_shininess = ptrPart->m_shininess;
				
				/***
				if (ptrPart->m_texture != NULL)
				{
					ptrScore->m_textureAlpha = ptrPart->m_textureAlpha;
					for (i = 0; i < 4; i++)
					{
						ptrScore->m_sParameter[i] = ptrPart->m_sParameter[i];
						ptrScore->m_tParameter[i] = ptrPart->m_tParameter[i];
					}
				}
				else 
				{
					// -FLT_MAX is a sentinel which states that texturing
					// is not being used.
					ptrScore->m_textureAlpha = -INT_MAX;
					for (i = 0; i < 4; i++)
					{
						ptrScore->m_sParameter[i] = -FLT_MAX;
						ptrScore->m_tParameter[i] = -FLT_MAX;
					}
				}
				***/

				if (prevScore == NULL)
				{
					ptrPart->m_score = ptrScore;
				}
				else
				{
					prevScore->m_next = ptrScore;
				}
				ptrScore->m_next = curScore;
				prevScore = ptrScore;
			}
		}

	} // end while(curMotion != NULL)
	return;
}

BOOL CStageDoc::YoHandleCommand(char *ibuf)
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	//char command[64];
	char command[4096];
	char deviceName[64];
	CStageDevice *ptrDevice;
	char pathName[64];
	char fileName[256];
	BOOL visible;
	CStagePath *ptrPath;
	CStageDevice *currentDevice;
	CStagePart *currentPart;
	CStageEyeView *ptrEyeView;
	char attachToPartName[64];
	char attachToDeviceName[64];
	char barCode[32];
	CStagePart *ptrAttachToPart;
	CStageDevice *ptrToDevice;
	CStageTag *currentTag;
	int tag = -INT_MAX;
	GLdouble appro = -FLT_MAX;
	CStageTag *ptrTag;
	GLdouble m[16];
	char buf[256];
	char c[13][32];
	int i;
	UINT j;
	char *t;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	CTimeSpan spanSec;
	CStageCommand *ptrCommand;

	sprintf(deviceName, "");

	i = sscanf(ibuf, "%s %s", command, deviceName);
	//command[63] = '\0';
	//deviceName[63] = '\0';

	// DO NOT insert returns from this point to the end of procedure!
	memset(buf, 0, 256);

	//::GetSystemTime(&m_gmTime);

	if ((ptrDevice = YoDeviceHashLookup(command)) != NULL)
	{
		// strip off the device name from ibuf

		for (t = ibuf; *t == ' '; t++);  // strip off leading white space if any
		for (; *t != ' ' && *t != '\0' && *t != '\n'; t++);  // remove device name
		for (; *t == ' ' && *t != '\0' && *t != '\n'; t++); // remove white space after device name

		if (*t == '\0' || *t == '\n')
		{
			sprintf(buf, "X");
		}
		else
		{
			i = 0;
			while (*t != '\0' && *t != '\n')
			{
				buf[i] = *t;
				i++;
				t++;
			}
			buf[i] = '\0';

			switch (ptrDevice->m_type)
			{
				case YO_ROBOT6:
					((CStageRobot6 *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_ROTARY_TABLE:
					((CStageRotaryTable *)ptrDevice)->YoHandleSim(buf);
					break;

				case YO_CAMERA:
					((CStageCamera *)ptrDevice)->YoHandleCommand(buf);
					break;
				
				case YO_GRIPPER:
					((CStageGripper *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_BARRETT_HAND:
					((CStageBarrettHand *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_BAR_CODE_READER:
					((CStageBarCodeReader *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_SCALE:
					((CStageScale *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_TRAIN:
					((CStageTrain *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_CONVEYOR:
					((CStageConveyor *)ptrDevice)->YoHandleSim(buf);
					break;

				case YO_LIGHT:
					((CStageLight *)ptrDevice)->YoHandleCommand(buf);
					break;

				default:
					ptrDevice->YoHandleCommand(ibuf, buf);
					break;
			}
			if (strcmp(buf, "X") == 0)
			{
				sprintf(buf, "X %s", ibuf);
			}
			else
			{
				m_currentDevice = ptrDevice;
				m_currentPart = m_currentDevice->m_ptrPart;
			}
		}
	}

	else if (strcmp(command, "-view") == 0)
	{
		if ((ptrEyeView = YoEyeViewHashLookup(deviceName)) != NULL)
		// move eye to an existing view
		{
			if (m_camera != NULL)
			{
				m_camera->m_enabled = FALSE;
				m_camera = NULL;
			}

			m_eyeList->m_timeOfMove = 0.0;
			sscanf(ibuf, "%*s %*s %lf", &m_eyeList->m_timeOfMove);

			for (i = 0; i < 9; i++)
			{
				m_eyeList->m_eye[1][i] = ptrEyeView->m_eye[i];
				m_eyeList->m_eye[0][i] = pView->m_eye[i];
			}

			m_eyeList->m_fieldOfView[0] = pView->m_fieldOfView;
			m_eyeList->m_clipFront[0] = pView->m_clipFront;
			m_eyeList->m_clipRear[0] = pView->m_clipRear;
			m_eyeList->m_fieldOfView[1] = ptrEyeView->m_eye[9];
			m_eyeList->m_clipFront[1] = ptrEyeView->m_eye[10];
			m_eyeList->m_clipRear[1] = ptrEyeView->m_eye[11];

			if (m_eyeList->m_timeOfMove < 0.0)
			{
				m_eyeList->m_timeOfMove = 0.0;
			}

			if (m_eyeList->m_fieldOfView[1] <= 0.0
				&& m_eyeList->m_fieldOfView[1] >= 180.0)
			{
				m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
			}
			if (m_eyeList->m_clipFront[1] < 0.0
				|| m_eyeList->m_clipFront[1] >= m_eyeList->m_clipRear[1])
			{
				m_eyeList->m_clipFront[1] = pView->m_clipFront;
			}
			if (m_eyeList->m_clipFront[1] >= m_eyeList->m_clipRear[1])
			{
				m_eyeList->m_clipRear[1] = pView->m_clipRear;
			}

			if (m_eyeList->m_moving == FALSE)
			{
				m_eyeList->m_moving = TRUE;
				m_isMovement++;
			}

			if (m_mode == YO_MODE_PLAY_SIM //&& m_realTime == FALSE
				&& m_currentCommand != NULL)
			{
				m_eyeList->m_timeStart = m_currentCommand->m_time;
			}
			else
			{
				m_eyeList->m_gmTimeStart = m_gmTime;
				//::GetSystemTime(&m_eyeList->m_gmTimeStart);
			}

			sprintf(buf, "< -view %s %.3lf", deviceName, m_eyeList->m_timeOfMove);
		}
		else if (strcmp(deviceName, "") != 0)
		// create a new view at the current eye coordinates
		{
			ptrEyeView = new CStageEyeView(this);

			sprintf(ptrEyeView->m_name, "%s", deviceName);
			for (i = 0; i < 9; i++)
			{
				ptrEyeView->m_eye[i] = pView->m_eye[i];
			}
			ptrEyeView->m_eye[9] = pView->m_fieldOfView;
			ptrEyeView->m_eye[10] = pView->m_clipFront;
			ptrEyeView->m_eye[11] = pView->m_clipRear;

			YoEyeViewHashInstall(ptrEyeView);
			sprintf(buf, "| -view %s added to view list", deviceName);
		}
	}

	else if (strcmp(command, "-position") == 0
		&& (ptrDevice = YoDeviceHashLookup(deviceName)) != NULL)
	{
		i = sscanf(ibuf, "%*s %*s %s %s %s %s %s %s",
			&c[0], &c[1], &c[2], &c[3], &c[4], &c[5]);
		if (i == 0)
		{
			// return the current position of the device
			sprintf(buf, "| -position %s %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf",
				deviceName,
				ptrDevice->m_ptrPart->m_translate[0],
				ptrDevice->m_ptrPart->m_translate[1],
				ptrDevice->m_ptrPart->m_translate[2],
				ptrDevice->m_ptrPart->m_rotate[0],
				ptrDevice->m_ptrPart->m_rotate[1],
				ptrDevice->m_ptrPart->m_rotate[2]);

			if (m_isMovement == FALSE
				&& m_mode != YO_MODE_PLAY_SIM
				&& m_scriptFastForward == FALSE)
			{
				pView->YoRender(YO_RENDER_LIGHT);
				pView->YoRender(YO_RENDER_FULL);
			}
		}
		else if (i == 3)
		{
			// translate (* means use the current value)
			for (i = 0; i < 3; i++)
			{
				if (c[i][0] != '*')
				{
					sscanf(c[i], "%lf", &ptrDevice->m_ptrPart->m_translate[i]);
				}
			}
			sprintf(buf, "| -position %s %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf",
				deviceName,
				ptrDevice->m_ptrPart->m_translate[0],
				ptrDevice->m_ptrPart->m_translate[1],
				ptrDevice->m_ptrPart->m_translate[2],
				ptrDevice->m_ptrPart->m_rotate[0],
				ptrDevice->m_ptrPart->m_rotate[1],
				ptrDevice->m_ptrPart->m_rotate[2]);

			if (m_isMovement == FALSE
				&& m_mode != YO_MODE_PLAY_SIM
				&& m_scriptFastForward == FALSE)
			{
				pView->YoRender(YO_RENDER_LIGHT);
				pView->YoRender(YO_RENDER_FULL);
			}
		}
		else if (i == 6)
		{
			// translate and rotate values (* means use the current value)
			for (i = 0; i < 3; i++)
			{
				if (c[i][0] != '*')
				{
					sscanf(c[i], "%lf", &ptrDevice->m_ptrPart->m_translate[i]);
				}
				if (c[i + 3][0] != '*')
				{
					sscanf(c[i + 3], "%lf", &ptrDevice->m_ptrPart->m_rotate[i]);
				}
			}
			sprintf(buf, "| -position %s %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf",
				deviceName,
				ptrDevice->m_ptrPart->m_translate[0],
				ptrDevice->m_ptrPart->m_translate[1],
				ptrDevice->m_ptrPart->m_translate[2],
				ptrDevice->m_ptrPart->m_rotate[0],
				ptrDevice->m_ptrPart->m_rotate[1],
				ptrDevice->m_ptrPart->m_rotate[2]);

			if (m_isMovement == FALSE
				&& m_mode != YO_MODE_PLAY_SIM
				&& m_scriptFastForward == FALSE)
			{
				pView->YoRender(YO_RENDER_LIGHT);
				pView->YoRender(YO_RENDER_FULL);
			}
		}
		else if (i == 1)
		{
			// snap device to a tag
			sscanf(c[0], "%s", pathName);

			// separate path from tag
			j = strlen(pathName);
			for (t = &pathName[j - 1]; isdigit(*t) && j > 0;)
			{
				j--;
				t--; 
			}
			if (j == 0) // invalid name
			{
				sprintf(pathName, "");
			}
			else if (j != strlen(pathName))
			{
				sscanf(&pathName[j], "%d", &tag);
				pathName[j] = '\0';
			}

			if ((ptrPath = YoPathHashLookup(pathName)) != NULL)
			{
				if (tag < 0)
				{
					tag = 1;
				}

				for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL
					&& ptrTag->m_tag != (UINT)tag; ptrTag = ptrTag->m_nextTag);
				if (ptrTag != NULL)
				{
					m_currentDevice = ptrDevice;
					m_currentPart = ptrDevice->m_ptrPart;
					m_currentTag = ptrTag;

					YoDetachDevice();
					// reattach device at world coords (rightmost position)
					for (currentDevice = m_deviceList;
						currentDevice->m_right != NULL;
						currentDevice = currentDevice->m_right);
					currentDevice->m_right = m_currentDevice;
					m_currentDevice->m_left = currentDevice;

					YoModelMatrixOfCurrentTag();
					m_currentDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
					YoTranslateRotateValues(m_mTag,
						m_currentDevice->m_ptrPart->m_translate,
						m_currentDevice->m_ptrPart->m_rotate);

					for (i = 0; i < 3; i++)
					{
						m_currentDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
					}

					sprintf(buf, "| -position %s %s%d", deviceName, pathName, tag);

					if (m_isMovement == FALSE
						&& m_mode != YO_MODE_PLAY_SIM
						&& m_scriptFastForward == FALSE)
					{
						pView->YoRender(YO_RENDER_LIGHT);
						pView->YoRender(YO_RENDER_FULL);
					}				
				}
				else
				{
					sprintf(buf, "X %s", ibuf);
				}
			}
			else
			{
				sprintf(buf, "X %s", ibuf);
			}
		}
		else
		{
			// send error
			sprintf(buf, "X");
		}
	}

	else if (strcmp(command, "-import") == 0)
	{
		// if translate and rotate values are given scan them into pathName, c[1], c[2],
		// c[3], c[4], c[5] else scan in the pathName and tag c[1]
		sprintf(c[5], "#!9_9Ag*");
		sscanf(ibuf, "%*s %*s %s %s %d %s %s %s %s %s %s",
			fileName, barCode, &visible, pathName, &c[1], &c[2], &c[3], &c[4], &c[5]);

		if (YoImportDevice(fileName, deviceName) == TRUE)
		{
			m_currentDevice->m_visible = visible;
			sprintf(m_currentDevice->m_barCode, "%s", barCode);

			if (strcmp(c[5], "#!9_9Ag*") != 0)
			//if (pathName[0] == '-' || pathName[0] == '.' || (pathName[0] >= '0' && pathName[0] <= '9'))
			// set translate / rotate values
			{
				sscanf(pathName, "%lf", &m[0]);
				for (i = 1; i < 6; i++)
				{
					sscanf(c[i], "%lf", &m[i]);
				}
				for (i = 0; i < 3; i++)
				{
					m_currentDevice->m_ptrPart->m_translate[i] = m[i];
					m_currentDevice->m_ptrPart->m_rotate[i + 3] = m[i + 3];
				}
			}
			else
			// snap device to path / tag
			{
				sscanf(c[1], "%d", &tag);
				if ((ptrPath = YoPathHashLookup(pathName)) != NULL)
				{
					for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL
						&& ptrTag->m_tag != (UINT)tag; ptrTag = ptrTag->m_nextTag);
					if (ptrTag != NULL)
					{
						currentTag = m_currentTag;
						m_currentTag = ptrTag;
						YoModelMatrixOfCurrentTag();
						YoTranslateRotateValues(m_mTag,
							m_currentDevice->m_ptrPart->m_translate,
							m_currentDevice->m_ptrPart->m_rotate);
						m_currentTag = currentTag;
					}
				}
			}
			if (m_isMovement == FALSE
				&& m_mode != YO_MODE_PLAY_SIM
				&& m_scriptFastForward == FALSE)
			{
				pView->YoRender(YO_RENDER_LIGHT);
				pView->YoRender(YO_RENDER_FULL);
			}

			sprintf(buf, "| %s", m_currentDevice->m_name);
		}
		else //if (m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			//m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}

	else if (strcmp(command, "-export") == 0)
	{
		ptrDevice = YoDeviceHashLookup(deviceName);
		if (ptrDevice != NULL)
		{
			sprintf(buf, "| -export %s", deviceName);

			m_currentDevice = ptrDevice;
			YoDeleteDevice();

			if (m_isMovement == FALSE
				&& m_mode != YO_MODE_PLAY_SIM
				&& m_scriptFastForward == FALSE)
			{
				pView->YoRender(YO_RENDER_LIGHT);
				pView->YoRender(YO_RENDER_FULL);
			}
		}
		else
		{
			sprintf(buf, "X %s", ibuf);
		}
	}

	else if (strcmp(command, "-snapToTag") == 0)
	{
		i = sscanf(ibuf, "%*s %*s %s", pathName);

		ptrDevice = YoDeviceHashLookup(deviceName);
		if (ptrDevice != NULL && i == 1)
		{
			// separate path from tag
			j = strlen(pathName);
			for (t = &pathName[j - 1]; isdigit(*t) && j > 0;)
			{
				j--;
				t--; 
			}
			if (j == 0) // invalid name
			{
				sprintf(pathName, "");
			}
			else if (j != strlen(pathName))
			{
				sscanf(&pathName[j], "%d", &tag);
				pathName[j] = '\0';
			}

			if ((ptrPath = YoPathHashLookup(pathName)) != NULL)
			{
				if (tag < 0)
				{
					tag = 1;
				}

				for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL
					&& ptrTag->m_tag != (UINT)tag; ptrTag = ptrTag->m_nextTag);
				if (ptrTag != NULL)
				{
					m_currentDevice = ptrDevice;
					m_currentPart = ptrDevice->m_ptrPart;
					m_currentTag = ptrTag;

					YoDetachDevice();
					// reattach device at world coords (rightmost position)
					for (currentDevice = m_deviceList;
						currentDevice->m_right != NULL;
						currentDevice = currentDevice->m_right);
					currentDevice->m_right = m_currentDevice;
					m_currentDevice->m_left = currentDevice;

					YoModelMatrixOfCurrentTag();
					m_currentDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
					YoTranslateRotateValues(m_mTag,
						m_currentDevice->m_ptrPart->m_translate,
						m_currentDevice->m_ptrPart->m_rotate);

					for (i = 0; i < 3; i++)
					{
						m_currentDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
					}

					sprintf(buf, "| -snapToTag %s %s%d", deviceName, pathName, tag);

					if (m_isMovement == FALSE
						&& m_mode != YO_MODE_PLAY_SIM
						&& m_scriptFastForward == FALSE)
					{
						pView->YoRender(YO_RENDER_LIGHT);
						pView->YoRender(YO_RENDER_FULL);
					}			
				}
				else
				{
					sprintf(buf, "X %s", ibuf);
				}
			}
			else
			{
				sprintf(buf, "X %s", ibuf);
			}
		}
		else
		{
			sprintf(buf, "X %s", ibuf);
		}
	}

	else if (strcmp(command, "-attach") == 0)
	{
		if ((ptrDevice = YoDeviceHashLookup(deviceName)) != NULL)
		{
			i = sscanf(ibuf, "%*s %*s %s %s", attachToDeviceName, attachToPartName);
			
			if ((ptrToDevice = YoDeviceHashLookup(attachToDeviceName)) != NULL)
			{
				if (i == 1 || (ptrAttachToPart = YoPartLookup(ptrToDevice, attachToPartName)) == NULL)
				{
					ptrAttachToPart = ptrToDevice->m_ptrPart;
					sprintf(attachToPartName, "%s", ptrAttachToPart->m_partName);
				}

				if (ptrDevice == ptrToDevice
					|| YoIsChild(ptrDevice, ptrToDevice))
				{
					if (i == 1)
					{
						sprintf(buf, "X %s cannot be attached to itself", ptrDevice->m_name);
					}
					else
					{
						sprintf(buf, "X %s cannot be attached to child %s",
							ptrDevice->m_name, ptrToDevice->m_name);
					}
				}
				else
				{

					currentDevice = m_currentDevice;
					currentPart = m_currentPart;
					m_currentDevice = ptrDevice;
					m_currentPart = ptrDevice->m_ptrPart;
					
					YoDetachDevice();

					sprintf(m_currentDevice->m_parent, "%s", 
						ptrToDevice->m_name);
					YoAttachDevice(ptrAttachToPart);
					m_currentDevice = currentDevice;
					m_currentPart = currentPart;

					sprintf(buf, "| -attach %s %s %s", deviceName, attachToDeviceName, attachToPartName);
				}
			}
			else
			{
				sprintf(buf, "X %s", ibuf);
			}			
		}
		else
		{
			sprintf(buf, "X %s", ibuf);
		}

		if (m_isMovement == FALSE
			&& m_mode != YO_MODE_PLAY_SIM
			&& m_scriptFastForward == FALSE)
		{
			pView->YoRender(YO_RENDER_LIGHT);
			pView->YoRender(YO_RENDER_FULL);
		}
	}

	else if (strcmp(command, "-detach") == 0)
	{
		ptrDevice = YoDeviceHashLookup(deviceName);

		if (ptrDevice != NULL
			&& strcmp(ptrDevice->m_parent, "NONE") != 0)
		{
			ptrToDevice = ptrDevice;
			currentDevice = m_currentDevice;
			currentPart = m_currentPart;
			m_currentDevice = ptrToDevice;
			m_currentPart = ptrToDevice->m_ptrPart; 

			YoDetachDevice();

			// reattach device at world coords (rightmost position)
			for (ptrToDevice = m_deviceList;
				ptrToDevice->m_right != NULL;
				ptrToDevice = ptrToDevice->m_right);

			ptrToDevice->m_right = m_currentDevice;
			m_currentDevice->m_left = ptrToDevice;
			ptrToDevice = ptrToDevice->m_right;

			m_currentDevice = currentDevice;
			m_currentPart = currentPart;
		}

		if (ptrDevice != NULL)
		{
			sprintf(buf, "| -detach %s", deviceName);
		}
		else
		{
			sprintf(buf, "X %s", ibuf);
		}
	}

	else if (strcmp(command, "-eye") == 0)
	{
		if (m_camera != NULL)
		{
			m_camera->m_enabled = FALSE;
			m_camera = NULL;
		}

		i = sscanf(ibuf, "%*s %s %s %s %s %s %s %s %s %s %s %s %s %s",
			&c[0], &c[1], &c[2], &c[3], &c[4], &c[5], &c[6],
			&c[7], &c[8], &c[9], &c[10], &c[11], &c[12]);

		if (i == 13)
		{
			for (i = 0; i < 9; i++)
			{
				if (c[i][0] == '*')
				{
					m_eyeList->m_eye[1][i] = pView->m_eye[i];
				}
				else
				{
					m_eyeList->m_eye[1][i] = pView->m_eye[i];
					sscanf(c[i], "%lf", &m_eyeList->m_eye[1][i]);
				}
				m_eyeList->m_eye[0][i] = pView->m_eye[i];
			}

			m_eyeList->m_eye[1][6] = 0.0;
			m_eyeList->m_eye[1][7] = 0.0;
			m_eyeList->m_eye[1][8] = 1.0;

			if (c[9][0] == '*')
			{
				m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
			}
			else
			{
				m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
				sscanf(c[9], "%lf", &m_eyeList->m_fieldOfView[1]);
			}

			if (c[10][0] == '*')
			{
				m_eyeList->m_clipFront[1] = pView->m_clipFront;
			}
			else
			{
				m_eyeList->m_clipFront[1] = pView->m_clipFront;
				sscanf(c[10], "%lf", &m_eyeList->m_clipFront[1]);
			}

			if (c[11][0] == '*')
			{
				m_eyeList->m_clipRear[1] = pView->m_clipRear;
			}
			else
			{
				m_eyeList->m_clipRear[1] = pView->m_clipRear;
				sscanf(c[11], "%lf", &m_eyeList->m_clipRear);
			}
			if (c[12][0] == '*')
			{
				m_eyeList->m_timeOfMove = 0.0;
			}
			else
			{
				m_eyeList->m_timeOfMove = 0.0;
				sscanf(c[12], "%lf", &m_eyeList->m_timeOfMove);
			}

			m_eyeList->m_fieldOfView[0] = pView->m_fieldOfView;
			m_eyeList->m_clipFront[0] = pView->m_clipFront;
			m_eyeList->m_clipRear[0] = pView->m_clipRear;

			if (m_eyeList->m_timeOfMove < 0.0)
			{
				m_eyeList->m_timeOfMove = 0.0;
			}

			if (m_eyeList->m_fieldOfView[1] <= 0.0
				|| m_eyeList->m_fieldOfView[1] >= 180.0)
			{
				m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
			}
			if (m_eyeList->m_clipFront[1] < 0.0
				|| m_eyeList->m_clipFront[1] >= m_eyeList->m_clipRear[1])
			{
				m_eyeList->m_clipFront[1] = pView->m_clipFront;
			}
			if (m_eyeList->m_clipFront[1] >= m_eyeList->m_clipRear[1])
			{
				m_eyeList->m_clipRear[1] = pView->m_clipRear;
			}

			if (m_eyeList->m_moving == FALSE)
			{
				m_eyeList->m_moving = TRUE;
				m_isMovement++;
			}

		if (m_mode == YO_MODE_PLAY_SIM //&& m_realTime == FALSE
			&& m_currentCommand != NULL)
		{
			m_eyeList->m_timeStart = m_currentCommand->m_time;
		}
		else
		{
			m_eyeList->m_gmTimeStart = m_gmTime;
			//::GetSystemTime(&m_eyeList->m_gmTimeStart);
		}

			sprintf(buf, "< -eye %.3lf", m_eyeList->m_timeOfMove);
		}
		else
		{
			sprintf(buf, "X %s", ibuf);
		}
	}

	else
	{
		sprintf(buf, "X %s", ibuf);
	}

	if (m_mode == YO_MODE_RECORD_SIM && buf[0] != 'X')
	{
		ptrCommand = new CStageCommand(this);
		::GetSystemTime(&ptrCommand->m_gmTime);
		sprintf(ptrCommand->m_buf, "%s", ibuf);
		ptrCommand->YoInsertCommand();
	}

	if (m_acceptSocket != NULL)
	{
		m_acceptSocket->Send(buf, strlen(buf) + 1);
	}
	else if (pMainFrame->m_wndDlgScriptVisible)
		//&& (pMainFrame->m_wndDlgScript->m_animationState == YO_PLAY)
	{
		YoMessage(buf);
	}

	if (buf[0] == 'X')
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


void CStageDoc::YoHandleEyeMotion()

// takes eye motion information and creates motion in the eye score

{
	CStageEyeMotion		*curMotion = m_eyeList->m_motion;
	CStageEyeMotion		*ptrMotion = NULL;
	CStageEyeScore		*ptrScore;
	CStageEyeScore		*prevScore = NULL;
	CStageEyeScore		*curScore = m_eyeList->m_score;
	GLint				i;
	GLint				j;
	GLdouble			d[3];
	GLdouble			r[3];
	GLdouble			f;
	GLdouble			w[3];
	GLdouble			cf;
	GLdouble			cr;
	GLint				t;
	GLdouble			a;

	while (curMotion != NULL)
	{
		if (curMotion->m_type == YO_MOTION_CONTROL)
		{
			curMotion->m_type = YO_MOTION_ANCHOR;
		}
		ptrMotion = curMotion;

		if (curMotion->m_type == YO_MOTION_HOLD || curMotion->m_next == NULL)
		{
			ptrScore = new CStageEyeScore(this);
			ptrScore->m_time = curMotion->m_time;
			ptrScore->m_next = NULL;
			ptrScore->m_clipFront = curMotion->m_clipFront;
			ptrScore->m_clipRear = curMotion->m_clipRear;
			ptrScore->m_fieldOfView = curMotion->m_fieldOfView;
			for (i = 0; i < 9; i++)
			{
				ptrScore->m_eye[i] = curMotion->m_eye[i];
			}
			curMotion = curMotion->m_next;
			if (prevScore == NULL)
			{
				m_eyeList->m_score = ptrScore;
			}
			else
			{
				prevScore->m_next = ptrScore;
			}
			ptrScore->m_next = curScore;
			prevScore = ptrScore;
		}
		else
		{
			curMotion = curMotion->m_next;
			while (curMotion->m_next != NULL
				&& curMotion->m_type == YO_MOTION_CONTROL)
			{
				curMotion = curMotion->m_next;
			}
			for (i = 0; i < 3; i++)
			{
				d[i] = curMotion->m_eye[i] - ptrMotion->m_eye[i];
				r[i] = curMotion->m_eye[i + 3] - ptrMotion->m_eye[i + 3];
				w[i] = curMotion->m_eye[i + 6] - ptrMotion->m_eye[i + 6];
			}
			f = curMotion->m_fieldOfView - ptrMotion->m_fieldOfView;
			cf = curMotion->m_clipFront - ptrMotion->m_clipFront;
			cr = curMotion->m_clipRear - ptrMotion->m_clipRear;
			//w = cmcur->twist - cmprev->twist;
			t = curMotion->m_time - ptrMotion->m_time;
			for (i = ptrMotion->m_time; i < curMotion->m_time; i++)
			{
				ptrScore = new CStageEyeScore(this);
				ptrScore->m_time = i;
				ptrScore->m_next = NULL;
				a = (sin(-PI / 2.0 + (PI * (i - ptrMotion->m_time) / t)) + 1.0) / 2.0;
				for (j = 0; j < 3; j++)
				{
					ptrScore->m_eye[j] = ptrMotion->m_eye[j] + a * d[j];
					ptrScore->m_eye[j + 3] = ptrMotion->m_eye[j + 3] + a * r[j];
					ptrScore->m_eye[j + 6] = ptrMotion->m_eye[j + 6] + a * w[j];
					//        csptr->from[j] = cmprev->from[j] + (i - cmprev->time) * d[j] / t;
					//        csptr->to[j] = cmprev->to[j] + (i - cmprev->time) * r[j] / t;
				}
				ptrScore->m_fieldOfView = ptrMotion->m_fieldOfView + a * f;
				ptrScore->m_clipFront = ptrMotion->m_clipFront + a * cf;
				ptrScore->m_clipRear = ptrMotion->m_clipRear + a * cr;
				//      csptr->fov = cmprev->fov + (i - cmprev->time) * f / t;
				//csptr->twist = cmprev->twist + a * w;
				//      csptr->twist = cmprev->twist + (i - cmprev->time) * w / t;
				if (prevScore == NULL)
				{
					m_eyeList->m_score = ptrScore;
				}
				else
				{
					prevScore->m_next = ptrScore;
				}
				ptrScore->m_next = curScore;
				prevScore = ptrScore;
			}
		}
	} // end while (curMotion != NULL)
}



void CStageDoc::YoPause()

{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	BOOL done = FALSE;
	CStageDevice *ptrDevice = m_deviceList;
	m_deviceStack = NULL;
	CWnd *pCBox;
	int min;
	int sec;
	int frm;
	char s[4];
	char t[256];

	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_PLAY);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmPlay);
	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_PAUSE);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmPauseHL);
	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_REWIND);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmRewind);
	m_animationState = YO_PAUSE;

	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_MINUTES);
	((CEdit *)pCBox)->SetReadOnly(FALSE);
	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_SECONDS);
	((CEdit *)pCBox)->SetReadOnly(FALSE);
	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_FRAMES);
	((CEdit *)pCBox)->SetReadOnly(FALSE);

	if (m_timeCurrent >= m_timeEnd)
	{
		m_timeCurrent = m_timeEnd;
		min = (int)(m_timeCurrent / 60.0);
		sec = (int)m_timeCurrent - (min * 60);
		if (m_realTime == TRUE)
		{
			//frm = (int)((m_timeCurrent
			//	- (double)((int)m_timeCurrent)) * 100.0);
			frm = (int)((m_timeCurrent
				- (double)((int)m_timeCurrent)) * 100.0 + 0.5);
		}
		else
		{
			frm = (int)(((m_timeCurrent
				- (double)((int)m_timeCurrent))
				* (double)m_framesPerSecond) + 0.5);
			//min = (int)(timeFrame / (m_framesPerSecond * 60));
			//sec = (int)((timeFrame - (min * m_framesPerSecond * 60)) / m_framesPerSecond);
			//frm = ((timeFrame - (min * m_framesPerSecond * 60)
			//	- (sec * m_framesPerSecond)) / m_framesPerSecond);
		}
		
		sprintf(s, "%02d", min);
		pCBox = (CComboBox*)((pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_MINUTES);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%02d", sec);
		pCBox = (CComboBox*)((pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_SECONDS);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%02d", frm);
		pCBox = (CComboBox*)((pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_FRAMES);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		pCBox = (CComboBox*)((pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_TIME);
		((CSliderCtrl *)pCBox)->SetRange(0, (int)m_timeEnd);
		((CSliderCtrl *)pCBox)->SetPos((int)m_timeCurrent);

		sprintf(t, "End of simulation");
		YoMessage(t);
	}
	else
	{
		sprintf(t, "Pause...");
		YoMessage(t);
	}

	//if (m_realTime == TRUE)
	//{
	//	::GetSystemTime(&m_gmTimePause);
	//}

	//m_resumeMove = FALSE;

	/***
	if (m_eyeList->m_currentScore != NULL)
	{
		for (i = 0; i < 9; i++)
		{
			pView->m_eye[i] = m_eyeList->m_currentScore->m_eye[i];
		}
		pView->m_clipFront = m_eyeList->m_currentScore->m_clipFront;
		pView->m_clipRear = m_eyeList->m_currentScore->m_clipRear;
		pView->m_fieldOfView = m_eyeList->m_currentScore->m_fieldOfView;

		
		//fprintf(fp, "%d", (int)from[0]);
		//fl_set_input(obj_fromx, s);
		//fprintf(fp, "%d", (int)from[1]);
		//fl_set_input(obj_fromy, s);
		//fprintf(fp, "%d", (int)from[2]);
		//fl_set_input(obj_fromz, s);
		//fprintf(fp, "%d", (int)to[0]);
		//fl_set_input(obj_tox, s);
		//fprintf(fp, "%d", (int)to[1]);
		//fl_set_input(obj_toy, s);
		//fprintf(fp, "%d", (int)to[2]);
		//fl_set_input(obj_toz, s);
		//fl_set_slider_value(obj_zoom, -camera->cur_score->fov);
		
	}

	if (ptrDevice == NULL)
	{
		return;
	}


	// put currentScore transformations into part transformations
	while (!done)
	{
		ptrPart = ptrDevice->m_ptrPart;
		m_partStack = NULL;
		pdone = FALSE;

		while (!pdone)
		{
			if (ptrPart->m_currentScore != NULL)
			{ 
				YoExtractTranslateRotate(ptrPart->m_currentScore->m_modelView,
					ptrPart->m_translate, ptrPart->m_rotate);
				ptrPart->m_rotate[0] *= YO_RADIANS_TO_DEGREES;
				ptrPart->m_rotate[1] *= YO_RADIANS_TO_DEGREES;
				ptrPart->m_rotate[2] *= YO_RADIANS_TO_DEGREES;
			} 
			if (ptrPart->m_down != NULL)
			{
				if (ptrPart->m_right != NULL)
				{
					YoPushPart(ptrPart->m_right);
				}
				ptrPart = ptrPart->m_down;
			}
			else if (ptrPart->m_right != NULL)
			{
				ptrPart = ptrPart->m_right;
			}
			else if (m_partStack != NULL)
			{
				ptrPart = YoPopPart();
			}
			else
			{
				pdone = TRUE;
			}
		} // end while (!pdone)

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			ptrDevice = YoPopDevice();
		}
		else
		{
			done = TRUE;
		}
	}  // end while (!done)
	***/
}

void CStageDoc::YoExtractTranslateRotate(GLdouble *n, GLdouble *t, GLdouble *r)
//void CStageDoc::YoExtractTranslateRotate(GLdouble n[4][4], GLdouble t[3], GLdouble r[3])

// obtains x, y, z, translations and
// x, y, z rotations (in radians) from given a modelview matrix n

{
	t[0] = n[12];
	t[1] = n[13];
	t[2] = n[14];

	r[1] = atan2(n[8], sqrt(n[0] * n[0] + n[4] * n[4]));
	if (r[1] == PI / 2.0)
	{
		r[2] = 0.0;
		r[0] = -atan2(n[1], n[5]);
	}
	else if (r[1] == -PI / 2.0)
	{
		r[2] = 0.0;
		r[0] = atan2(n[1], n[5]);
	}
	else
	{
		r[2] = -atan2(n[4] / cos(r[1]), n[0] / cos(r[1]));
		r[0] = -atan2(n[9] / cos(r[1]), n[10] / cos(r[1]));
	}
	
/***
	t[0] = n[3][0];
	t[1] = n[3][1];
	t[2] = n[3][2];

	r[1] = atan2(n[2][0], sqrt(n[0][0] * n[0][0] + n[1][0] * n[1][0]));
	if (r[1] == PI / 2.0)
	{
		r[2] = 0.0;
		r[0] = -atan2(n[0][1], n[1][1]);
	}
	else if (r[1] == -PI / 2.0)
	{
		r[2] = 0.0;
		r[0] = atan2(n[0][1], n[1][1]);
	}
	else
	{
		r[2] = -atan2(n[1][0] / cos(r[1]), n[0][0] / cos(r[1]));
		r[0] = -atan2(n[2][1] / cos(r[1]), n[2][2] / cos(r[1]));
	}
***/
	
	return;
}


void CStageDoc::YoHaltAllMotion()
{
	/***
	CStageConveyorSegment *curSegment;
	CStageConveyorTransverseLift *curTransverseLift;
	CStageConveyorPallet *curPallet;


	if (m_isMovement == 0)
	{
		return;
	}

	m_eyeList->m_moving == TRUE)
	{
		m_eyeList->m_moving = FALSE;
		m_isMovement--;
	}

	for (currentDevice = m_deviceList; currentDevice != NULL;)
	{
		if (currentDevice->m_type == YO_ROBOT6
			&& ((CStageRobot6 *)currentDevice)->m_moving == TRUE)
		{
			((CStageRobot6 *)currentDevice)->m_moving = FALSE;
			m_isMovement--;
		}
		else if (currentDevice->m_type == YO_ROTARY_TABLE
			&& ((CStageRotaryTable *)currentDevice)->m_rotating)
		{
			for (curRotateInfo = ((CStageRotaryTable *)currentDevice)->m_ptrRotateInfo;
				curRotateInfo != NULL;)
			{
				ptrRotateInfo = curRotateInfo;
				curRotateInfo = curRotateInfo->m_next;
				delete ptrRotateInfo;
				((CStageRotaryTable *)currentDevice)->m_rotating--;
				m_isMovement--;
			}
			((CStageRotaryTable *)currentDevice)->m_ptrRotateInfo = NULL;
		}
		else if (currentDevice->m_type == YO_TRAIN
			&& ((CStageTrain *)currentDevice)->m_moving == TRUE)
		{
			((CStageTrain *)currentDevice)->m_moving = FALSE;
			m_isMovement--;
		}
		else if (currentDevice->m_type == YO_CONVEYOR
			&& ((CStageConveyor *)currentDevice)->m_moving)
		{


			for (curSegment = ((CStageConveyor *)currentDevice)->m_ptrSegment; curSegment != NULL;)
			{
				for (curTransverseLift = curSegment->m_ptrTransverseLift; curTransverseLift != NULL;)
				{
					curTransverseLift->m_inMotion = FALSE;
					curTransverseLift = curTransverseLift->m_ptrNextTransverseLift;
				}
				// since a conveyor pallet is a separate device, don't delete it
				// just remove it from the list for this conveyor
				for (curPallet = curSegment->m_ptrPallet; curPallet != NULL;)
				{
					curPallet->m_moving = FALSE;
					curPallet = curPallet->m_ptrNextPallet;
				}

				curSegment =
				curSegment = curSegment->m_ptrNextSegment;
				delete prevSegment;
			}
		}
		else if (currentDevice->m_type == YO_BARRETT_HAND
			&& ((CStageBarrettHand *)currentDevice)->m_moving)
		{
			((CStageBarrettHand *)currentDevice)->YoCalculateBHPosition();
		}

		m_partStack = NULL;

		for (currentPart = currentDevice->m_ptrPart; currentPart != NULL;)
		{
			if (currentPart->m_down != NULL)
			{
				if (currentPart->m_right != NULL)
				{
					YoPushPart(currentPart->m_right);
				}
				currentPart = currentPart->m_down;
			}
			else if (currentPart->m_right != NULL)
			{
				currentPart = currentPart->m_right;
			}
			else if (m_partStack != NULL)
			{
				currentPart = YoPopPart();
			}
			else 
			{
				currentPart = NULL; 
			}
		}

		if (currentDevice->m_down != NULL)
		{
			if (currentDevice->m_right != NULL)
			{
				YoPushDevice(currentDevice->m_right);
			}
			currentDevice = currentDevice->m_down;
		}
		else if (currentDevice->m_right != NULL)
		{
			currentDevice = currentDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			currentDevice = YoPopDevice();
		}
		else 
		{
			currentDevice = NULL;
		}
	}
***/
	return;
}


void CStageDoc::YoRewind()
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	BOOL done = FALSE;
	CStageDevice *ptrDevice = m_deviceList;
	m_deviceStack = NULL;
	char s[256];
	FILE *fp;
	CWnd *pCBox;


	//if (m_motionEffectModified == TRUE
	//	|| m_motionEffectModified == YO_MOTION_EFFECT_MODIFIED_ALL)
	//{
	//	YoUpdateScore();
	//}
	//else 
	//{
	//	YoRestoreCurrentScore();
	//}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_PLAY);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmPlay);
	pCBox->UpdateWindow();
	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_PAUSE);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmPause);
	pCBox->UpdateWindow();
	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_REWIND);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmRewindHL);
	pCBox->UpdateWindow();


	m_animationState = YO_PAUSE;
	m_resumeMove = FALSE;

	if ((fp = fopen(m_fileName, "r")) == NULL)
	{
		fclose(fp);
		sprintf(s, "Cannot Rewind.  Unable to find file:\n%s", m_fileName);
		AfxMessageBox(s);
	}
	else
	{
		//fclose(fp);
		YoFreeWorkcell();

		if (YoReadWorkcell(fp) == FALSE)
		{
			sprintf(s, "Error: Rewind failed while reading file.\nIncorrect file format or corrupt data encountered.");
			AfxMessageBox(s);

			YoFreeWorkcell();
			return;
		}
		fclose(fp);

		((CStageView *)pView)->YoRender(YO_RENDER_LIGHT);
		((CStageView *)pView)->YoRender(YO_RENDER_FULL);

		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_MINUTES);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->SetWindowText("00");
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_SECONDS);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->SetWindowText("00");
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_FRAMES);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->SetWindowText("00");
		//pCBox->UpdateWindow();
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_TIME);
		((CSliderCtrl *)pCBox)->SetRange(0, (int)m_timeEnd);
		((CSliderCtrl *)pCBox)->SetPos(0);
	}

	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_PLAY);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmPlay);
	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_PAUSE);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmPauseHL);
	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarTop.GetDlgItem(IDC_REWIND);
	((CStatic *)pCBox)->SetBitmap(pMainFrame->m_bmRewind);

	return;


	//m_timeCurrent = 0.0;
	//m_currentCommand = m_commandList;
	//m_isMovement = 0;
	//YoHaltAllMotion();

	/***
	if (m_eyeList->m_score != NULL)
	{
		for (i = 0; i < 9; i++)
		{
			pView->m_eye[i] = m_eyeList->m_score->m_eye[i];
		}
		pView->m_clipFront = m_eyeList->m_score->m_clipFront;
		pView->m_clipRear = m_eyeList->m_score->m_clipRear;
		pView->m_fieldOfView = m_eyeList->m_score->m_fieldOfView;
	}

	if (ptrDevice == NULL)
	{
		done = TRUE;
	}

	// put currentScore transformations into part transformations
	while (!done)
	{
		ptrPart = ptrDevice->m_ptrPart;
		m_partStack = NULL;
		pdone = FALSE;

		while (!pdone)
		{
			if (ptrPart->m_score != NULL)
			{ 
				YoExtractTranslateRotate(ptrPart->m_score->m_modelView,
					ptrPart->m_translate, ptrPart->m_rotate);
				ptrPart->m_rotate[0] *= YO_RADIANS_TO_DEGREES;
				ptrPart->m_rotate[1] *= YO_RADIANS_TO_DEGREES;
				ptrPart->m_rotate[2] *= YO_RADIANS_TO_DEGREES;
			} 
			if (ptrPart->m_down != NULL)
			{
				if (ptrPart->m_right != NULL)
				{
					YoPushPart(ptrPart->m_right);
				}
				ptrPart = ptrPart->m_down;
			}
			else if (ptrPart->m_right != NULL)
			{
				ptrPart = ptrPart->m_right;
			}
			else if (m_partStack != NULL)
			{
				ptrPart = YoPopPart();
			}
			else
			{
				pdone = TRUE;
			}
		} // end while (!pdone)

		if (ptrDevice->m_down != NULL)
		{
			if (ptrDevice->m_right != NULL)
			{
				YoPushDevice(ptrDevice->m_right);
			}
			ptrDevice = ptrDevice->m_down;
		}
		else if (ptrDevice->m_right != NULL)
		{
			ptrDevice = ptrDevice->m_right;
		}
		else if (m_deviceStack != NULL)
		{
			ptrDevice = YoPopDevice();
		}
		else
		{
			done = TRUE;
		}
	}  // end while (!done)

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
		pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
		pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

	pView->YoRender(YO_RENDER_LIGHT);
	***/
	return;
}


void CStageDoc::YoMove()
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageDevice *currentDevice;
	CStagePart *currentPart;
	CWnd *pCBox;
	char s[32];
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	CTimeSpan spanSec;

	if (m_isMovement > 0)
	{
		if (m_mode != YO_MODE_PLAY_SIM)
		{
			if (m_scriptFastForward == TRUE)
			{
				//timeCurrent = m_gmTime;
				//timeStart = m_gmTimeStart;
				//spanSec = timeCurrent - timeStart;
				//tms = m_gmTime.wMilliseconds - m_gmTimeStart.wMilliseconds;
				//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0) + m_timeSleepTotal;
				//YoChangeTime(&m_gmTime, timeElapsed);
				// m_gmTime.wSecond = (int)timeElapsed;
				// m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
			}
			else if (pMainFrame->m_wndDlgScript != NULL && pMainFrame->m_wndDlgScriptVisible == TRUE)
			{
				//::GetSystemTime(&m_gmTime);
				//timeCurrent = m_gmTime;
				//timeStart = m_gmTimeStart;
				//spanSec = timeCurrent - timeStart;
				//tms = m_gmTime.wMilliseconds - m_gmTimeStart.wMilliseconds;
				//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0)
				//	+ pMainFrame->m_wndDlgScript->m_timeSleepFastForward
				//	- pMainFrame->m_wndDlgScript->m_timeFastForward;
				//YoChangeTime(&m_gmTime, timeElapsed);
				// m_gmTime.wSecond = (int)timeElapsed;
				// m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
			}
			else
			{
				::GetSystemTime(&m_gmTime);
			}

		}
		// else m_gmTime is set in YoPlay()

		if (m_eyeList->m_moving == TRUE)
		{
			m_eyeList->YoCalculateEyePosition();

			::glMatrixMode(GL_PROJECTION);
			::glLoadIdentity();
			::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
				pView->m_clipFront, pView->m_clipRear);
			
			::glMatrixMode(GL_MODELVIEW);
			::glLoadIdentity();
			::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
				pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
				pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);
				pView->YoUpdateEyeDlg();
		}

		for (currentDevice = m_deviceList; currentDevice != NULL;)
		{
			if (currentDevice->m_type == YO_ROBOT6
				&& ((CStageRobot6 *)currentDevice)->m_moving == TRUE)
			{
				((CStageRobot6 *)currentDevice)->YoCalculateJointAngles();
			}
			else if (currentDevice->m_type == YO_ROTARY_TABLE
				&& ((CStageRotaryTable *)currentDevice)->m_rotating)
			{
				((CStageRotaryTable *)currentDevice)->YoCalculateRTPosition();
			}
			else if (currentDevice->m_type == YO_TRAIN
				&& ((CStageTrain *)currentDevice)->m_moving == TRUE)
			{
				((CStageTrain *)currentDevice)->YoAnimateTrain();
			}
			else if (currentDevice->m_type == YO_CONVEYOR
				&& ((CStageConveyor *)currentDevice)->m_moving)
			{
				((CStageConveyor *)currentDevice)->YoCalculatePositionOfPallets();
			}
			else if (currentDevice->m_type == YO_BARRETT_HAND
				&& ((CStageBarrettHand *)currentDevice)->m_moving)
			{
				((CStageBarrettHand *)currentDevice)->YoCalculateBHPosition();
			}
			else if (currentDevice->m_type == YO_LIGHT
				&& ((CStageLight *)currentDevice)->m_changing)
			{
				((CStageLight *)currentDevice)->YoCalculateLightIntensity();
			}

			m_partStack = NULL;

			for (currentPart = currentDevice->m_ptrPart; currentPart != NULL;)
			{
				if (currentPart->m_down != NULL)
				{
					if (currentPart->m_right != NULL)
					{
						YoPushPart(currentPart->m_right);
					}
					currentPart = currentPart->m_down;
				}
				else if (currentPart->m_right != NULL)
				{
					currentPart = currentPart->m_right;
				}
				else if (m_partStack != NULL)
				{
					currentPart = YoPopPart();
				}
				else 
				{
					currentPart = NULL; 
				}
			}

			if (currentDevice->m_down != NULL)
			{
				if (currentDevice->m_right != NULL)
				{
					YoPushDevice(currentDevice->m_right);
				}
				currentDevice = currentDevice->m_down;
			}
			else if (currentDevice->m_right != NULL)
			{
				currentDevice = currentDevice->m_right;
			}
			else if (m_deviceStack != NULL)
			{
				currentDevice = YoPopDevice();
			}
			else 
			{
				currentDevice = NULL;
			}
		}

		if (pMainFrame->m_robot6DlgActive == TRUE)
		{
			sprintf(s, "%.1lf", ((CStageRobot6 *)m_currentDevice)->m_j[1]);
			pCBox = (CComboBox*)pMainFrame->m_robot6Dialog->GetDlgItem(IDC_JOINT1);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
			
			sprintf(s, "%.1lf", ((CStageRobot6 *)m_currentDevice)->m_j[2]);
			pCBox = (CComboBox*)(CComboBox*)pMainFrame->m_robot6Dialog->GetDlgItem(IDC_JOINT2);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%.1lf", ((CStageRobot6 *)m_currentDevice)->m_j[3] + 180.0);
			pCBox = (CComboBox*)(CComboBox*)pMainFrame->m_robot6Dialog->GetDlgItem(IDC_JOINT3);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
			
			sprintf(s, "%.1lf", ((CStageRobot6 *)m_currentDevice)->m_j[4]);
			pCBox = (CComboBox*)(CComboBox*)pMainFrame->m_robot6Dialog->GetDlgItem(IDC_JOINT4);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
			
			sprintf(s, "%.1lf", ((CStageRobot6 *)m_currentDevice)->m_j[5]);
			pCBox = (CComboBox*)(CComboBox*)pMainFrame->m_robot6Dialog->GetDlgItem(IDC_JOINT5);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
			
			sprintf(s, "%.1lf", ((CStageRobot6 *)m_currentDevice)->m_j[6]);
			pCBox = (CComboBox*)(CComboBox*)pMainFrame->m_robot6Dialog->GetDlgItem(IDC_JOINT6);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
		}
		else if (pMainFrame->m_rotaryTableDlgActive == TRUE)
		{
			sprintf(s, "%ld", ((CStageRotaryTable *)m_currentDevice)->m_currentPosition);
			pCBox = (CComboBox*)pMainFrame->m_rotaryTableDialog->GetDlgItem(IDC_ROTARY_TABLE_CURRENT_POSITION);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
		}
		else if (pMainFrame->m_trainDlgActive == TRUE)
		{
			sprintf(s, "%.1lf", m_currentDevice->m_ptrPart->m_translate[0] * m_unitScaleFactor);
			pCBox = (CComboBox*)pMainFrame->m_trainDialog->GetDlgItem(IDC_TRAIN_POSITION_X);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			pCBox = (CComboBox*)pMainFrame->m_viewPart->GetDlgItem(IDC_TRANSLATE_X);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%.1lf", m_currentDevice->m_ptrPart->m_translate[1] * m_unitScaleFactor);
			pCBox = (CComboBox*)pMainFrame->m_trainDialog->GetDlgItem(IDC_TRAIN_POSITION_Y);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			pCBox = (CComboBox*)pMainFrame->m_viewPart->GetDlgItem(IDC_TRANSLATE_Y);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%s", ((CStageTrain *)m_currentDevice)->m_ptrTrackSeg->m_ptrPart->m_partName);
			pCBox = (CComboBox*)pMainFrame->m_trainDialog->GetDlgItem(IDC_TRAIN_TRACK);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%.3lf", ((CStageTrain *)m_currentDevice)->m_relativePosition);
			pCBox = (CComboBox*)pMainFrame->m_trainDialog->GetDlgItem(IDC_TRAIN_RELATIVE_POSITION);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%.1lf", m_currentDevice->m_ptrPart->m_rotate[2]);
			pCBox = (CComboBox*)pMainFrame->m_viewPart->GetDlgItem(IDC_ROTATE_Z);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
		}

		if (m_mode == YO_MODE_PLAY_SIM
			|| m_scriptFastForward == TRUE)
			//|| (pMainFrame->m_wndDlgScript != NULL
			//&& pMainFrame->m_wndDlgScript->m_animationState == YO_PLAY))
		{
			return;
		}
		else
		{
			pView->YoRender(YO_RENDER_LIGHT);
			pView->YoRender(YO_RENDER_FULL);
			return;
		}
	}

	return;
		


		/***
		if (m_mode == YO_MODE_PLAY_SIM)
		{
			return;
		}
		if (pMainFrame->m_wndDlgScript != NULL && pMainFrame->m_wndDlgScript->m_animationState == YO_PLAY)
		{
			return;
		}

		//if (m_acceptSocket != NULL
		//	&& ::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, NULL, NULL, PM_NOREMOVE))
		//{
		//	TRACE0("Return YoMove: m_resumeMove = TRUE\n");
		//	m_resumeMove = TRUE;
		//	return;
		//}
		if (::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, NULL, NULL, PM_NOREMOVE))
		{
			TRACE0("Return YoMove: m_resumeMove = TRUE\n");
			m_resumeMove = TRUE;
			return;
		}
		else if (pMainFrame->m_viewPartActive
			&& pMainFrame->m_conveyorDlgActive
			&& ::PeekMessage(&msg, ((CWnd*)(pMainFrame->m_viewPart))->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_NOREMOVE))
		{
			((CStageConveyor *)m_currentDevice)->YoEStop();
			return;
		}
		else if (pMainFrame->m_viewPartActive
			&& pMainFrame->m_robot6DlgActive
			&& ::PeekMessage(&msg, ((CWnd*)(pMainFrame->m_viewPart))->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_NOREMOVE))
		{
			sprintf(s, "BRAKE");
			((CStageRobot6 *)m_currentDevice)->YoHandleCommand(s);
			return;
		}
		else if (pMainFrame->m_viewPartActive
			&& pMainFrame->m_rotaryTableDlgActive
			&& ::PeekMessage(&msg, ((CWnd*)(pMainFrame->m_viewPart))->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_NOREMOVE))
		{
			((CStageRotaryTable *)m_currentDevice)->YoEStop();
			return;
		}
		else if (pMainFrame->m_viewPartActive
			&& pMainFrame->m_barCodeReaderDlgActive
			&& ::PeekMessage(&msg, ((CWnd*)(pMainFrame->m_viewPart))->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_NOREMOVE))
		{
			sprintf(s, "TRIGGEROFF");
			((CStageBarCodeReader *)m_currentDevice)->YoHandleCommand(s);
			return;
		}
		else if (pMainFrame->m_viewPartActive
			&& pMainFrame->m_barCodeReaderDlgActive
			&& ::PeekMessage(&msg, ((CWnd*)(pMainFrame->m_barCodeReaderDialog))->m_hWnd, NULL, NULL, PM_NOREMOVE))
		{
			m_resumeMove = TRUE;
			return;
		}
		else if (pMainFrame->m_viewPartActive
			&& pMainFrame->m_barrettHandDlgActive
			&& ::PeekMessage(&msg, ((CWnd*)(pMainFrame->m_viewPart))->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_NOREMOVE))
		{
			((CStageBarrettHand *)m_currentDevice)->YoEStop();
			return;
		}
		else if (pMainFrame->m_viewPartActive
			&& pMainFrame->m_barrettHandDlgActive
			&& ::PeekMessage(&msg, ((CWnd*)(pMainFrame->m_barrettHandDialog))->m_hWnd, NULL, NULL, PM_NOREMOVE))
		{
			m_resumeMove = TRUE;
			return;
		}
		else if (pMainFrame->m_viewPartActive
			&& pMainFrame->m_trainDlgActive 
			&& ::PeekMessage(&msg, ((CWnd *)pMainFrame->m_viewPart)->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_NOREMOVE))
		{
			sprintf(s, "STOP");
			((CStageTrain *)m_currentDevice)->YoHandleCommand(s);
			return;
		}
		else if (pMainFrame->m_viewPartActive
			&& pMainFrame->m_trainDlgActive
			&& ::PeekMessage(&msg, ((CWnd*)(pMainFrame->m_trainDialog))->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_NOREMOVE))
		{
			m_resumeMove = TRUE;
			return;
		}
		else if (pMainFrame->m_viewPartActive
			&& ::PeekMessage(&msg, ((CWnd*)(pMainFrame->m_viewPart))->m_hWnd, NULL, NULL, PM_NOREMOVE))
		{
			m_resumeMove = TRUE;
			return;
		}
		***/
		/***
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_MODE_WALK);

		if (m_acceptSocket != NULL && m_eyeList->m_moving == FALSE)
		{
			pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_MODE_WALK);
			pCBoxPan = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_MODE_PAN);

			if (::PeekMessage(&msg, ((CWnd *)pView)->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_NOREMOVE))
			{
				while (i = ::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, NULL, NULL, PM_REMOVE))
				{
					if (((CWnd *)pView)->m_hWnd == msg.hwnd)
					{
						wParam = msg.wParam;
						lParam = msg.lParam;
					}
					TRACE2("PeekMessage = %d hwnd = %ld\n", i, msg.hwnd);
				}
				pView->PostMessage(WM_LBUTTONDOWN, wParam, lParam);
				TRACE0("YoMove Returned...  pView\n");
				return;
			}

			if (::PeekMessage(&msg, ((CWnd *)pView)->m_hWnd, WM_LBUTTONUP, WM_LBUTTONUP, PM_NOREMOVE))
			{
				while (i = ::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, NULL, NULL, PM_REMOVE))
				{
					if (((CWnd *)pView)->m_hWnd == msg.hwnd)
					{
						wParam = msg.wParam;
						lParam = msg.lParam;
					}
					TRACE2("PeekMessage = %d hwnd = %ld\n", i, msg.hwnd);
				}
				pView->PostMessage(WM_LBUTTONUP, wParam, lParam);
				TRACE0("YoMove Returned...  pView\n");
				return;
			}

			if (::PeekMessage(&msg, ((CWnd *)pView)->m_hWnd, WM_RBUTTONDOWN, WM_RBUTTONDOWN, PM_NOREMOVE))
			{
				while (i = ::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, NULL, NULL, PM_REMOVE))
				{
					if (((CWnd *)pView)->m_hWnd == msg.hwnd)
					{
						wParam = msg.wParam;
						lParam = msg.lParam;
					}
					TRACE2("PeekMessage = %d hwnd = %ld\n", i, msg.hwnd);
				}
				pView->PostMessage(WM_RBUTTONDOWN, wParam, lParam);
				TRACE0("YoMove Returned...  pView\n");
				return;
			}

			if (::PeekMessage(&msg, ((CWnd *)pView)->m_hWnd, WM_RBUTTONUP, WM_RBUTTONUP, PM_NOREMOVE))
			{
				while (i = ::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, NULL, NULL, PM_REMOVE))
				{
					if (((CWnd *)pView)->m_hWnd == msg.hwnd)
					{
						wParam = msg.wParam;
						lParam = msg.lParam;
					}
					TRACE2("PeekMessage = %d hwnd = %ld\n", i, msg.hwnd);
				}
				pView->PostMessage(WM_RBUTTONUP, wParam, lParam);
				TRACE0("YoMove Returned...  pView\n");
				return;
			}

			if (::PeekMessage(&msg, pCBox->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONUP, PM_NOREMOVE))
			{
				while (::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, NULL, NULL, PM_REMOVE));

				pMainFrame->PostMessage(WM_COMMAND, IDC_MODE_WALK, (LPARAM)0);
				TRACE0("YoMove Returned...  Mainframe Walk\n");
				return;
			}

			if (::PeekMessage(&msg, pCBoxPan->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONUP, PM_NOREMOVE))
			{
				while (::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, NULL, NULL, PM_REMOVE));

				pMainFrame->PostMessage(WM_COMMAND, IDC_MODE_PAN, (LPARAM)0);
				TRACE0("YoMove Returned...  Mainframe Pan\n");
				return;
			}

		}
		***/

		/****
		if (m_acceptSocket != NULL)
		{
			int i;
			memset(m_acceptSocket->m_buf, 0, 256);
			if ((i = m_acceptSocket->Receive(m_acceptSocket->m_buf,
				sizeof(m_acceptSocket->m_buf), MSG_PEEK)) > 0)
			{
				TRACE1("Return YoMove: m_buf = %s\n", m_acceptSocket->m_buf);
				return;
			}
		}

		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);

		//if (m_acceptSocket != NULL
		//	&& (i = m_acceptSocket->Receive(m_acceptSocket->m_buf,
		//		sizeof(m_acceptSocket->m_buf), MSG_PEEK))
		//	&& strcmp(m_acceptSocket->m_buf, "****") != 0)
		//	
		//{
		//	TRACE1("Return YoMove: m_buf = %s\n", m_acceptSocket->m_buf);
		//	return;
		//}
		//TRACE2("YoMove: ->Recieve: %d %s\n", i, m_acceptSocket->m_buf);

	}

	if (m_acceptSocket != NULL)
	{
		while (::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, NULL, NULL, PM_REMOVE));
	}

	return;
	***/
}


void CStageDoc::YoPlay()
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	char s[4];
	char t[256];
	int min;// = 0;
	int sec;// = 0;
	int frm;// = 0;
	CWnd *pCBox;
	static SYSTEMTIME gmTimeStart;
	static SYSTEMTIME gmTimeCurrent;
	static CTime timePlay;
	static CTime timeStart;
	static CTime timeCurrent;
	static double timePause;
	GLint tms;
	CTimeSpan spanSec;
	int timeFrame;
	static int k = 0;
	static double avgTimeRender;
	static double m_timePrev;

	//TRACE0("YoPlay()\n");
	//if (m_resumeMove == FALSE)
	//{
		//m_realTime = TRUE;
		if (m_timeCurrent == 0.0)
		{
			m_currentCommand = m_commandList;
		}

		m_animationState = YO_PAUSE;
		timePause = m_timeCurrent;
		timeFrame = (int)(timePause * (double)m_framesPerSecond + 0.5);

		//timeFrame = (int)d;

		//for (;
		//	m_currentCommand != NULL && m_currentCommand->m_time <= timePause;
		//	m_currentCommand = m_currentCommand->m_next)
		//{
		//	m_timeCurrent = m_currentCommand->m_time;
		//	YoHandleCommand(m_currentCommand->m_buf);
		//}

		if (m_realTime == TRUE)
		{
			::GetSystemTime(&gmTimeStart);
			//m_gmTime = gmTimeStart;
			timeStart = gmTimeStart;
			//gmTimeStart.wSecond -= (WORD)tp;
			//gmTimeStart.wMilliseconds -= (WORD)((tp - (double)(int)tp) * 1000.0);
			//timeStart = gmTimeStart;
		}
		//m_timeCurrent = tp;
		m_animationState = YO_PLAY;
		//TRACE3("min = %d   sec = %d   msec = %d\n",
		//	gmTimeStart.wMinute, gmTimeStart.wSecond, gmTimeStart.wMilliseconds);

		if (m_outputBitmap == TRUE)
		{
			::SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, FALSE, 0, SPIF_SENDWININICHANGE);
		}
	//}

	//m_resumeMove = FALSE;

	//while (m_timeCurrent <= m_timeEnd
	//	&& m_animationState == YO_PLAY)
	if (m_timeCurrent <= m_timeEnd)
	{
		while (m_currentCommand != NULL
			&& m_currentCommand->m_time <= m_timeCurrent)
		{
			TRACE2("%.3lf: %s\n", m_currentCommand->m_time, m_currentCommand->m_buf);
			YoHandleCommand(m_currentCommand->m_buf);
			m_currentCommand = m_currentCommand->m_next;
		}

		if (m_realTime == FALSE
			&& m_render3d & YO_RENDER3D_MOTION_BLUR
			&& m_renderMode == YO_RENDER3D
			&& m_isMovement
			&& m_accumCount % m_motionBlurIterations != 0)
		{
			m_timeCurrent += ((double)m_accumCount / (double)m_motionBlurIterations) / (double)m_framesPerSecond;
		}

		if (m_isMovement)
		{
			YoMove();
		}
		//if (::PeekMessage(&msg, ((CWnd *)pMainFrame)->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONUP, PM_NOREMOVE))
		//if (::PeekMessage(&msg, pMainFrame->m_wndDlgBarTop.m_hWnd, WM_LBUTTONUP, WM_LBUTTONUP, PM_NOREMOVE))
		//if (::PeekMessage(&msg, ((CWnd *)pMainFrame)->m_hWnd, NULL, NULL, PM_NOREMOVE))
		//{
		//	m_resumeMove = TRUE;
		//	if (m_outputBitmap == TRUE)
		//	{
		//		::SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, TRUE, 0, SPIF_SENDWININICHANGE);
		//	}
		//	TRACE0("YoPlay()::PeekMessage return\n");
		//	return;
		//}

		pView->YoRender(YO_RENDER_LIGHT);
		pView->YoRender(YO_RENDER_FULL);

		if (m_realTime == FALSE
			&& m_render3d & YO_RENDER3D_MOTION_BLUR
			&& m_renderMode == YO_RENDER3D
			&& m_isMovement)
		{
			if (m_accumCount % m_motionBlurIterations == 0)
			{
				m_accumCount = 0;
				::glClearAccum(0.0f, 0.0f, 0.0f, 0.0f);
				::glClear(GL_ACCUM_BUFFER_BIT);
			}

			::glAccum(GL_ACCUM, 1.0f / m_motionBlurIterations);
			m_accumCount++;

			if (m_accumCount == m_motionBlurIterations)
			{
				::glAccum(GL_RETURN, 1.0f);
				if (::SwapBuffers(pView->m_pDC->GetSafeHdc()) == FALSE)
				{
					AfxMessageBox("ERROR in CStageDoc::YoPlay().  SwapBuffers failed.");
				}
				if (m_outputBitmap == TRUE)
				{
					sprintf(t, "%s_%06d.bmp", m_fileName, timeFrame);
					YoWriteViewBitmap(t);
				}
			}
		}
		else if (m_outputBitmap == TRUE)
		{
			//Sleep(1000);
			sprintf(t, "%s_%06d.bmp", m_fileName, timeFrame);
			YoWriteViewBitmap(t);
		}

		if (m_realTime == TRUE)
		{
			k++;
			m_timePrev = m_timeCurrent;
			::GetSystemTime(&gmTimeCurrent);
			m_gmTime = gmTimeCurrent;
			timeCurrent = gmTimeCurrent;
			spanSec = timeCurrent - timeStart;
			tms = gmTimeCurrent.wMilliseconds - gmTimeStart.wMilliseconds;
			m_timeCurrent = timePause + (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);

			avgTimeRender = m_timeCurrent / (double)k;
			//if (k > 3)
			//{
			//	m_timeCurrent = m_timePrev + avgTimeRender;
			//}
			timeFrame = (int)m_timeCurrent * m_framesPerSecond;
		}
		else
		{
			if (m_realTime == FALSE
				&& m_render3d & YO_RENDER3D_MOTION_BLUR
				&& m_renderMode == YO_RENDER3D
				&& m_isMovement
				&& m_accumCount % m_motionBlurIterations != 0)
			{
				// leave timeFrame as is
			}
			else
			{
				timeFrame++;
			}
			m_timeCurrent = (double)timeFrame / (double)m_framesPerSecond;		
		}

		//TRACE2("timeCurrent = %.3lf    timePause = %.3lf\n", m_timeCurrent, timePause);

		min = (int)(m_timeCurrent / 60.0);
		sec = (int)m_timeCurrent - (min * 60);
		if (m_realTime == TRUE)
		{
			//frm = (int)((m_timeCurrent
			//	- (double)((int)m_timeCurrent)) * 100.0);
			frm = (int)((m_timeCurrent
				- (double)((int)m_timeCurrent)) * 100.0 + 0.5);
		}
		else
		{
			frm = (int)(((m_timeCurrent
				- (double)((int)m_timeCurrent))
				* (double)m_framesPerSecond) + 0.5);
			//min = (int)(timeFrame / (m_framesPerSecond * 60));
			//sec = (int)((timeFrame - (min * m_framesPerSecond * 60)) / m_framesPerSecond);
			//frm = ((timeFrame - (min * m_framesPerSecond * 60)
			//	- (sec * m_framesPerSecond)) / m_framesPerSecond);
		}

		if (m_realTime == FALSE
			&& m_renderMode == YO_RENDER3D
			&& (m_render3d & YO_RENDER3D_MOTION_BLUR
			|| m_antiAlias == TRUE
			|| m_outputBitmap == TRUE))
		{
			if ((m_render3d & YO_RENDER3D_MOTION_BLUR) && m_isMovement)
			{
				sprintf(t, "Rendering frame: %06d (motion blur iteration = %02d)", timeFrame, m_accumCount);
				YoMessage(t);
			}
			else
			{
				sprintf(t, "Rendering frame: %06d", timeFrame);
				YoMessage(t);
			}
		}
			
		sprintf(s, "%02d", min);
		pCBox = (CComboBox*)((pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_MINUTES);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%02d", sec);
		pCBox = (CComboBox*)((pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_SECONDS);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%02d", frm);
		pCBox = (CComboBox*)((pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_FRAMES);
		((CEdit *)pCBox)->SetReadOnly(TRUE);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		pCBox = (CComboBox*)((pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_TIME);
		((CSliderCtrl *)pCBox)->SetRange(0, (int)m_timeEnd);
		((CSliderCtrl *)pCBox)->SetPos((int)m_timeCurrent);
	}
	else
	{
		YoPause();
	}

	return;


	/***
	//if (m_socket == NULL)
	//{
	//	YoSocketInit();
	//}
	//else
	//{
	//	YoPause();
	//	return;
	//}

	//if (m_threadPlay == NULL)
	//{
	CStageThreadPlay *tp;
		tp = new CStageThreadPlay;
		tp->m_hframeWND = pMainFrame->m_hWnd;
		tp->m_hviewWND = pView->m_hWnd;
		//m_threadPlay = new CStageDoc;
		//m_threadPlay->m_timeEnd = m_timeEnd;
	//}
	AfxBeginThread(YoThreadPlay, tp);
	
	return;
	***/
}

/***
void CStageDoc::YoPlay()
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	MSG msg;
	char s[4];
	int min = 0;
	int sec = 0;
	int frm = 0;
	CWnd *pCBox;
	SYSTEMTIME gmTimeStart;
	SYSTEMTIME gmTimeEnd;
	SYSTEMTIME gmTimePlay;
	GLint timeElapsed;
	CTime timePlay;
	CTime timeStart;
	CTime timeEnd;
	GLint tms;
	CTimeSpan spanSec;
	GLint tp;

	//((CMainFrame *)pMainFrame)->OnUpdateTime();

	if (pView == NULL || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;     // illegal parameter
	}
	
	::GetSystemTime(&gmTimePlay);
	tp = m_timeCurrent;
	timePlay = gmTimePlay;

	while (m_timeCurrent <= m_timeEnd
		&& m_animationState == YO_PLAY)
	{
		::GetSystemTime(&gmTimeStart);
		timeStart = gmTimeStart;

		min = m_timeCurrent / (60 * m_framesPerSecond);
		sec = (m_timeCurrent
			- (min * 60 * m_framesPerSecond)) / m_framesPerSecond;
		frm = m_timeCurrent
			- (min * 60 * m_framesPerSecond)
			- (sec * m_framesPerSecond);

		sprintf(s, "%02d", min);
		pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_MINUTES);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%02d", sec);
		pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_SECONDS);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%02d", frm);
		pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_FRAMES);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_TIME);
		((CSliderCtrl *)pCBox)->SetRange(0, m_timeEnd);
		((CSliderCtrl *)pCBox)->SetPos(m_timeCurrent);

		if (m_eyeList->m_score != NULL
			&& m_eyeList->m_currentScore->m_time <= m_timeCurrent)

		{
			while (m_eyeList->m_currentScore->m_next != NULL
				&& m_eyeList->m_currentScore->m_time < m_timeCurrent
				&& m_eyeList->m_currentScore->m_next->m_time <= m_timeCurrent)
			{
				m_eyeList->m_currentScore = m_eyeList->m_currentScore->m_next;
			}

			::glMatrixMode(GL_PROJECTION);
			::glLoadIdentity();
			::gluPerspective(m_eyeList->m_currentScore->m_fieldOfView,
				pView->m_aspectRatio,
				m_eyeList->m_currentScore->m_clipFront,
				m_eyeList->m_currentScore->m_clipRear);
			::glMatrixMode(GL_MODELVIEW);
			::glLoadIdentity();
			::gluLookAt(m_eyeList->m_currentScore->m_eye[0],
				m_eyeList->m_currentScore->m_eye[1],
				m_eyeList->m_currentScore->m_eye[2],
				m_eyeList->m_currentScore->m_eye[3],
				m_eyeList->m_currentScore->m_eye[4],
				m_eyeList->m_currentScore->m_eye[5],
				m_eyeList->m_currentScore->m_eye[6],
				m_eyeList->m_currentScore->m_eye[7],
				m_eyeList->m_currentScore->m_eye[8]);
            
		}
		pView->YoRender(YO_RENDER_FULL);
		//if (::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, WM_LBUTTONUP, WM_LBUTTONUP, PM_NOREMOVE))
		if (::PeekMessage(&msg, NULL, WM_LBUTTONUP, WM_LBUTTONUP, PM_NOREMOVE))
		{
			YoPause();
		}

		if (m_render3d == 0x0 && m_realTime == TRUE)
		{
			timeElapsed = 0;
			while(timeElapsed < 1000 / m_framesPerSecond)
			{
				::GetSystemTime(&gmTimeEnd);
				//ts = gmTimeEnd.wSecond - gmTimeStart.wSecond;
				//if (ts < 0)
				//{
				//	ts += 60;
				//}
				//ts *= 1000;
				timeEnd = gmTimeEnd;
				spanSec = timeEnd - timeStart;
				//timeElapsed = ((ts.GetTotalSeconds() - 1) * 1000)
				//	+ (gmTimeEnd.wMilliseconds) - (gmTimePlay.wMilliseconds - 1000);
				tms = gmTimeEnd.wMilliseconds - gmTimeStart.wMilliseconds;
				timeElapsed = spanSec.GetTotalSeconds() * 1000 + tms;
				//timeElapsed = ((ts.GetTotalSeconds() - 1) * 1000)
				//	+ (gmTimeEnd.wMilliseconds) - (gmTimeStart.wMilliseconds - 1000);
			}

			//::GetSystemTime(&gmTimeEnd);
			//timeEnd = gmTimeEnd;
			spanSec = timeEnd - timePlay;
			//ts = (gmTimeEnd.wSecond + (60 * min)) - gmTimePlay.wSecond;
			//if (ts < 0)
			//{
			//	ts += 60;
			//}
			//ts *= 1000;
			tms = gmTimeEnd.wMilliseconds - gmTimePlay.wMilliseconds;
			//timeElapsed = ts + tms;
			//TRACE1("timeCurrent = %d\n", m_timeCurrent);
			//TRACE1("sec = %d\n", ts.GetTotalSeconds());
			timeElapsed = spanSec.GetTotalSeconds() * 1000 + tms;
			m_timeCurrent = tp + (int)(((float)timeElapsed / 1000.0) * (float)m_framesPerSecond + 0.5);
			//	+ (gmTimeEnd.wMilliseconds) - (gmTimePlay.wMilliseconds - 1000);

			//m_timeCurrent = tp + (GLint)((float)timeElapsed / (float)m_framesPerSecond + 0.5);
			//m_timeCurrent = tp + (((ts.GetTotalSeconds() - 1) * m_framesPerSecond)
			//	+ (GLint)((float)(gmTimeEnd.wMilliseconds - (gmTimePlay.wMilliseconds - 1000))
			//	/ (float)m_framesPerSecond + 0.5));
		}
		else
		{
			m_timeCurrent++;
		}
	}
      
	//pDoc->YoPause();
	return;
}
***/


void CStageDoc::YoTranslateRotateValues(GLdouble n[16], GLdouble t[3], GLdouble r[3])

// obtains x, y, z, translations and
// x, y, z rotations (in radians) from given a matrix

{
	t[0] = n[12];
	t[1] = n[13];
	t[2] = n[14];

	r[1] = atan2(n[8], sqrt(n[0] * n[0] + n[4] * n[4]));
	if (r[1] == PI / 2.0)
	{
		r[2] = 0.0;
		r[0] = -atan2(n[1], n[5]);
	}
	else if (r[1] == -PI / 2.0)
	{
		r[2] = 0.0;
		r[0] = atan2(n[1], n[5]);
	}
	else
	{
		r[2] = -atan2(n[4] / cos(r[1]), n[0] / cos(r[1]));
		r[0] = -atan2(n[9] / cos(r[1]), n[10] / cos(r[1]));
	}

	return;

}


void CStageDoc::YoMatrixInverse(GLdouble mat[16], GLdouble invMat[16])
{
	GLdouble wtemp[4][8];
	GLdouble m0;
	GLdouble m1;
	GLdouble m2;
	GLdouble m3;
	GLdouble s;
	GLdouble *r0;
	GLdouble *r1;
	GLdouble *r2;
	GLdouble *r3;
	GLdouble *rtemp;

	r0 = wtemp[0];
	r1 = wtemp[1];
	r2 = wtemp[2];
	r3 = wtemp[3];
	r0[0] = mat[0];		// build up [A][I]
	r0[1] = mat[1];
	r0[2] = mat[2];
	r0[3] = mat[3];
	r0[4] = 1.0;
	r0[5] = 0.0;
	r0[6] = 0.0;
	r0[7] = 0.0;
	r1[0] = mat[4];
	r1[1] = mat[5];
	r1[2] = mat[6];
	r1[3] = mat[7];
	r1[4] = 0.0;
	r1[5] = 1.0;
	r1[6] = 0.0;
	r1[7] = 0.0;
	r2[0] = mat[8];
	r2[1] = mat[9];
	r2[2] = mat[10];
	r2[3] = mat[11];
	r2[4] = 0.0;
	r2[5] = 0.0;
	r2[6] = 1.0;
	r2[7] = 0.0;
	r3[0] = mat[12];
	r3[1] = mat[13];
	r3[2] = mat[14];
	r3[3] = mat[15];
	r3[4] = 0.0;
	r3[5] = 0.0;
	r3[6] = 0.0;
	r3[7] = 1.0;

	// swap rows if needed
	if (r0[0] == 0.0)
	{
		if (r1[0] == 0.0)
		{
			if (r2[0] == 0.0)
			{
				if (r3[0] == 0.0)
				{
					//AfxMessageBox("ERROR: Singular Matrix");
					//return;
					r3[0] = 0.00012735;
				}
				rtemp = r0;
				r0 = r3;
				r3 = rtemp;
			}
			else
			{
				rtemp = r0;
				r0 = r2;
				r2 = rtemp;
			}
		}
		else
		{
			rtemp = r0;
			r0 = r1;
			r1 = rtemp;
		}
	}

	m1 = r1[0] / r0[0];		// eliminate first variable
	m2 = r2[0] / r0[0];
	m3 = r3[0] / r0[0];
	s = r0[1];
	r1[1] = r1[1] - m1 * s;
	r2[1] = r2[1] - m2 * s;
	r3[1] = r3[1] - m3 * s;
	s = r0[2];
	r1[2] = r1[2] - m1 * s;
	r2[2] = r2[2] - m2 * s;
	r3[2] = r3[2] - m3 * s;
	s = r0[3];
	r1[3] = r1[3] - m1 * s;
	r2[3] = r2[3] - m2 * s;
	r3[3] = r3[3] - m3 * s;
	s = r0[4];
	if (s != 0.0)
	{
		r1[4] = r1[4] - m1 * s;
		r2[4] = r2[4] - m2 * s;
		r3[4] = r3[4] - m3 * s;
	}
	s = r0[5];
	if (s != 0.0)
	{
		r1[5] = r1[5] - m1 * s;
		r2[5] = r2[5] - m2 * s;
		r3[5] = r3[5] - m3 * s;
	}
	s = r0[6];
	if (s != 0.0)
	{
		r1[6] = r1[6] - m1 * s;
		r2[6] = r2[6] - m2 * s;
		r3[6] = r3[6] - m3 * s;
	}
	s = r0[7];
	if (s != 0.0)
	{
		r1[7] = r1[7] - m1 * s;
		r2[7] = r2[7] - m2 * s;
		r3[7] = r3[7] - m3 * s;
	}

	// swap rows if needed
	if (r1[1] == 0.0)
	{		
		if (r2[1] == 0.0)
		{
			if (r3[1] == 0.0)
			{
				//AfxMessageBox("ERROR: Singular Matrix");
				//return;
				r3[1] = -0.00011926;
			}
			rtemp = r1;
			r1 = r3;
			r3 = rtemp;
		}
		else
		{
			rtemp = r1;
			r1 = r2;
			r2 = rtemp;
		}
	}
	m2 = r2[1] / r1[1];		// eliminate second variable
	m3 = r3[1] / r1[1];
	r2[2] = r2[2] - m2 * r1[2];
	r3[2] = r3[2] - m3 * r1[2];
	r3[3] = r3[3] - m3 * r1[3];
	r2[3] = r2[3] - m2 * r1[3];
	s = r1[4];
	if (s != 0.0)
	{
		r2[4] = r2[4] - m2 * s;
		r3[4] = r3[4] - m3 * s;
	}
	s = r1[5];
	if (s != 0.0)
	{
		r2[5] = r2[5] - m2 * s;
		r3[5] = r3[5] - m3 * s;
	}
	s = r1[6];
	if (s != 0.0)
	{
		r2[6] = r2[6] - m2 * s;
		r3[6] = r3[6] - m3 * s;
	}
	s = r1[7];
	if (s != 0.0)
	{
		r2[7] = r2[7] - m2 * s;
		r3[7] = r3[7] - m3 * s;
	}

	// swap last 2 rows if needed
	if (r2[2] == 0.0)
	{		
		if (r3[2] == 0.0)
		{
			//AfxMessageBox("ERROR: Singular Matrix");
			//return;
			r3[2] = 0.00007925;
		}
		rtemp = r2;
		r2 = r3;
		r3 = rtemp;
	}

	// eliminate third variable
	m3 = r3[2] / r2[2];		
	r3[3] = r3[3] - m3 * r2[3];
	r3[4] = r3[4] - m3 * r2[4];
	r3[5] = r3[5] - m3 * r2[5];
	r3[6] = r3[6] - m3 * r2[6];
	r3[7] = r3[7] - m3 * r2[7];

	if (r3[3] == 0.0)
	{
		//AfxMessageBox("ERROR: Singular Matrix");
		//return;
		r3[3] = -0.00013002;
	}

	s = 1.0 / r3[3];		// now back substitute row 3
	r3[4] = r3[4] * s;
	r3[5] = r3[5] * s;
	r3[6] = r3[6] * s;
	r3[7] = r3[7] * s;

	m2 = r2[3];			// now back substitute row 2
	s = 1.0 / r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2);
	r2[5] = s * (r2[5] - r3[5] * m2);
	r2[6] = s * (r2[6] - r3[6] * m2);
	r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3];
	r1[4] = (r1[4] - r3[4] * m1);
	r1[5] = (r1[5] - r3[5] * m1);
	r1[6] = (r1[6] - r3[6] * m1);
	r1[7] = (r1[7] - r3[7] * m1);
	m0 = r0[3];
	r0[4] = (r0[4] - r3[4] * m0);
	r0[5] = (r0[5] - r3[5] * m0);
	r0[6] = (r0[6] - r3[6] * m0);
	r0[7] = (r0[7] - r3[7] * m0);

	m1 = r1[2];			// now back substitute row 1
	s = 1.0 / r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1);
	r1[5] = s * (r1[5] - r2[5] * m1);
	r1[6] = s * (r1[6] - r2[6] * m1);
	r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2];
	r0[4] = (r0[4] - r2[4] * m0);
	r0[5] = (r0[5] - r2[5] * m0);
	r0[6] = (r0[6] - r2[6] * m0);
	r0[7] = (r0[7] - r2[7] * m0);

	m0 = r0[1];			// now back substitute row 0
	s = 1.0 / r0[0];
	r0[4] = s * (r0[4] - r1[4] * m0);
	r0[5] = s * (r0[5] - r1[5] * m0);
	r0[6] = s * (r0[6] - r1[6] * m0);
	r0[7] = s * (r0[7] - r1[7] * m0);

	invMat[0] = r0[4];		// copy results back
	invMat[1] = r0[5];
	invMat[2] = r0[6];
	invMat[3] = r0[7];
	invMat[4] = r1[4];
	invMat[5] = r1[5];
	invMat[6] = r1[6];
	invMat[7] = r1[7];
	invMat[8] = r2[4];
	invMat[9] = r2[5];
	invMat[10] = r2[6];
	invMat[11] = r2[7];
	invMat[12] = r3[4];
	invMat[13] = r3[5];
	invMat[14] = r3[6];
	invMat[15] = r3[7];
	return;

}


CStageTexture::CStageTexture():
	m_RGBImage(NULL), m_textureCoords(NULL)
{
		sprintf(m_DIBFileName, "NONE");
}


BOOL CStageTexture::YoInitFromDIB()
{

// Given a path to a dib or bmp, create an OpenGL Mipmap for it.
// texFunc can be either GL_MODULATE or GL_DECAL (the default)

	//CString *s = (CString *)&m_DIBFileName;

	if (m_RGBImage != NULL)
	{
		//LocalFree(m_RGBImage);
		delete m_RGBImage;
	}
	else
	{
		m_RGBImage = new CGLImage();
	}
	
	//m_RGBImage = auxDIBImageLoadA((const char*)dibfile);
	//m_RGBImage = auxDIBImageLoadA(m_DIBFileName);

	m_RGBImage->Load(m_DIBFileName);

	if (m_RGBImage == NULL)
	{
		return FALSE;
	}

	//sprintf(m_DIBFileName, "%s", dibfile);
    m_textureMode = GL_MODULATE == m_textureMode ? GL_MODULATE : GL_DECAL;

	return TRUE;
}




BOOL CStageTexture::YoSelectImage()
{

// Once you have an image, you need to select it so that the
// texture gets applied. Once applied you can get rid of the image.

	if (m_RGBImage == NULL)
	{
		return FALSE;
	}

	::glEnable(GL_TEXTURE_2D);
	::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	::glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, m_textureMode);
    // Generate a series of texture maps of decreasing size
    ::gluBuild2DMipmaps( GL_TEXTURE_2D, 3,
		m_RGBImage->m_iWidth, m_RGBImage->m_iHeight,
		GL_RGB, GL_UNSIGNED_BYTE,
		m_RGBImage->m_pBits );

	return TRUE;
}


CStageTexture::~CStageTexture()
{
	if (m_RGBImage != NULL)
	{
		delete m_RGBImage;
	}
}

BOOL CStageDoc::YoSocketInit()
{
	m_socket = new CStageSocket(this);
	if (!m_socket->Create(m_port))
	{
		AfxMessageBox("Unable to create socket at specified port");
		delete m_socket;
		m_socket = NULL;
		return FALSE;
	}

	m_socket->AsyncSelect(FD_READ | FD_ACCEPT | FD_CLOSE);
	if (!m_socket->Listen(5))
	{
		AfxMessageBox("Socket listen failed");
		delete m_socket;
		m_socket = NULL;
		return FALSE;
	}

	return TRUE;
}


void CStageSocket::OnAccept(int nErrorCode)

// function called when listening server receives a request to
// connect from a client

{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CWnd *pCBox;
	char s[64];
	CStageCommand *ptrCommand;

	if (m_pDoc->m_socket == NULL)
	{
		return;
	}

	m_pDoc->m_acceptSocket = new CStageSocket(m_pDoc);

	if (!m_pDoc->m_socket->Accept(*(m_pDoc->m_acceptSocket)))
	{
		AfxMessageBox("Could not initiate socket accept");
		//pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarLeft).GetDlgItem(IDC_MODE_SOCKET);
		//((CButton *)pCBox)->SetBitmap((HBITMAP)pMainFrame->m_bmCircleRed);
		//pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_IMMEDIATE_MODE);
		//((CButton *)pCBox)->SetBitmap((HBITMAP)pMainFrame->m_bmCircleRed);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_CONNECT);
		pCBox->ShowWindow(SW_HIDE);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_LISTEN);
		pCBox->ShowWindow(SW_HIDE);
		delete m_pDoc->m_acceptSocket;
		return;
	}

	// send socket connect message to MainFrame 

	//pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarLeft).GetDlgItem(IDC_MODE_SOCKET);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)pMainFrame->m_bmCircleGreen);
	//pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_IMMEDIATE_MODE);
	//((CButton *)pCBox)->SetBitmap((HBITMAP)pMainFrame->m_bmCircleGreen);
	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_LISTEN);
	pCBox->ShowWindow(SW_HIDE);
	pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_CONNECT);
	pCBox->ShowWindow(SW_SHOW);

	sprintf(s, "Connection established at port %d.", m_pDoc->m_port);
	m_pDoc->YoMessage(s);

	if (m_pDoc->m_animationState != YO_PAUSE)
	{
		m_pDoc->YoPause();
	}

	if (pView->m_mode == YO_MODE_DEVICE_TRANSLATE)
	{
		pView->m_mode = YO_MODE_WALK;
		pMainFrame->SendMessage(WM_COMMAND, IDC_WALK, (LPARAM)0);
	}

	// send part name & id to client
	/***
	sprintf(m_buf, "");
	for (i = 0; i < YO_HASH_SIZE; i++)
	{
		for (ptrPart = m_pDoc->m_pick[i]; ptrPick != NULL;
			ptrPick = ptrPick->m_pick)
		{
			s = m_buf + strlen(m_buf)
			sprintf(s, 

	if (ptrPick != NULL)
	{
		m_currentPart = ptrPick;
		m_currentDevice = YoDeviceHashLookup(ptrPick->m_deviceName);
	}	}
			sprintf(buf, "-999999\n");
		m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		return;
	***/

	// Clear command list
	for (m_pDoc->m_currentCommand = m_pDoc->m_commandList; m_pDoc->m_currentCommand != NULL;)
	{
		ptrCommand = m_pDoc->m_currentCommand;
		m_pDoc->m_currentCommand = m_pDoc->m_currentCommand->m_next;
		delete ptrCommand;
	}
	m_pDoc->m_commandList = NULL;
	m_pDoc->m_currentCommand = NULL;

	return;
}


void CStageSocket::OnClose(int nErrorCode)
{
	//CTime timeStart;
	//CTime timeEnd;
	//CTimeSpan spanSec;


	if (this)
	{
		// send socket disconnect message to MainFrame
		POSITION pos = m_pDoc->GetFirstViewPosition();
		if (pos == NULL)
		{
			return;
		}
		CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
		if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
		{
			return;
		}
		CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
		if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
		{
			return;
		}
		CWnd *pCBox;

		if (this == m_pDoc->m_acceptSocket)
		{
			pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_CONNECT);
			pCBox->ShowWindow(SW_HIDE);
			pCBox = (CComboBox*)pMainFrame->m_wndDlgBarLeft.GetDlgItem(IDC_SOCKET_LISTEN);
			pCBox->ShowWindow(SW_SHOW);

			if (m_pDoc->m_camera != NULL)
			{
				m_pDoc->m_camera->m_enabled = FALSE;
				m_pDoc->m_camera = NULL;
			}

			//pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarLeft).GetDlgItem(IDC_MODE_SOCKET);
			//((CButton *)pCBox)->SetBitmap((HBITMAP)pMainFrame->m_bmCircleYellow);
			//pCBox = (CComboBox*)(((CMainFrame *)pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_IMMEDIATE_MODE);
			//((CButton *)pCBox)->SetBitmap((HBITMAP)pMainFrame->m_bmCircleYellow);
			//m_pDoc->YoMessage("");

			// compute time of simulation
			if (m_pDoc->m_mode == YO_MODE_RECORD_SIM
				&& m_pDoc->m_commandList != NULL
				&& pView->m_fp != NULL)
			{
				pMainFrame->OnModeRecordSim();
				//::GetSystemTime(&gmTimeEnd);
				//timeEnd = gmTimeEnd;
				//timeStart = m_pDoc->m_commandList->m_gmTime;
				//spanSec = timeEnd - timeStart;
				//tms = gmTimeEnd.wMilliseconds - m_pDoc->m_commandList->m_gmTime.wMilliseconds;
				//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
				//m_pDoc->m_timeEnd = (GLint)(m_pDoc->m_framesPerSecond * timeElapsed);
			}
		}

		delete this;
	}
	return;
}


void CStageSocket::OnReceive(int nErrorCode)
// function called when socket has pending data to be read
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	char command[64];
	char deviceName[64];
	CStageDevice *ptrDevice;
	CStageDevice *ptrTempDevice;
	char pathName[64];
	char trackName[64];
	double relativePosition;
	char fileName[256];
	BOOL visible;
	CStagePath *ptrPath;
	CStageDevice *currentDevice;
	CStagePart *currentPart;
	CStageEyeView *ptrEyeView;
	char attachToPartName[64];
	char attachToDeviceName[64];
	char s[64];
	char barCode[32];
	CStagePart *ptrAttachToPart;
	CStageDevice *ptrToDevice;
	CStageDevice *ptrParent;
	GLdouble speed;
	GLdouble x;
	GLdouble y;
	GLdouble z;
	CStageTag *currentTag;
	int tag = -INT_MAX;
	GLdouble appro = -FLT_MAX;
	CStageTag *ptrTag;
	GLdouble m[16];
	GLdouble mInv[16];
	int lefty;
	int elbowUp;
	int flipped;
	char buf[256];
	char c[13][32];
	int i;
	long distance;

	if (m_pDoc->m_acceptSocket == NULL)
	{
		return;
	}

	memset(m_buf, 0, 4096);

	if (!m_pDoc->m_acceptSocket->Receive(m_buf, sizeof(m_buf)))
	{
		TRACE0("OnReceive: ERROR\n");
		return;
	}

	if (pMainFrame->m_wndDlgScript != NULL
		&& pMainFrame->m_wndDlgScript->m_animationState == YO_PLAY)
	{
		return;
	}

	TRACE1("OnReceive: %s\n", m_buf);

	::GetSystemTime(&m_pDoc->m_gmTime);

	m_pDoc->YoHandleCommand(m_buf);

	memset(m_buf, 0, 4096);
	if ((i = Receive(m_buf, sizeof(m_buf), MSG_PEEK)) > 0)
	{
		return;
	}
	else if (m_pDoc->m_isMovement)
	{
		m_pDoc->YoMove();
	}
	/***
	sscanf(m_buf, "%s %s", command, deviceName);

	// DO NOT insert returns from this point to the end of procedure!
	memset(buf, 0, 256);

	if ((ptrDevice = m_pDoc->YoDeviceHashLookup(command)) != NULL)
	{
		// strip off the device name from m_buf

		for (t = m_buf; *t == ' '; t++);  // strip off leading while space if any
		for (; *t != ' ' && *t != '\0' && *t != '\n'; t++);  // remove device name
		for (; *t == ' ' && *t != '\0' && *t != '\n'; t++); // remove white space after device name

		if (*t == '\0' || *t == '\n')
		{
			sprintf(buf, "X");
		}
		else
		{
			i = 0;
			while (*t != '\0' && *t != '\n')
			{
				buf[i] = *t;
				i++;
				t++;
			}
			buf[i] = '\0';

			switch (ptrDevice->m_type)
			{
				case YO_ROBOT6:
					((CStageRobot6 *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_ROTARY_TABLE:
					((CStageRotaryTable *)ptrDevice)->YoHandleSim(buf);
					break;

				case YO_GRIPPER:
					((CStageGripper *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_BARRETT_HAND:
					((CStageBarrettHand *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_BAR_CODE_READER:
					((CStageBarCodeReader *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_SCALE:
					((CStageScale *)ptrDevice)->YoHandleCommand(buf);
					break;

				case YO_TRAIN:
					((CStageTrain *)ptrDevice)->YoHandleCommand(m_buf, buf);
					break;

				case YO_CONVEYOR:
					((CStageConveyor *)ptrDevice)->YoHandleSim(buf);
					break;

				default:
					ptrDevice->YoHandleCommand(m_buf, buf);
					break;
			}
			if (strcmp(buf, "X") == 0)
			{
				sprintf(buf, "X %s", m_buf);
			}
		}
	}

	else if (strcmp(command, "-view") == 0
		&& (ptrEyeView = m_pDoc->YoEyeViewHashLookup(deviceName)) != NULL)
	{
		m_pDoc->m_eyeList->m_timeOfMove = 0.0;
		sscanf(m_buf, "%*s %*s %lf", &m_pDoc->m_eyeList->m_timeOfMove);

		for (i = 0; i < 9; i++)
		{
			m_pDoc->m_eyeList->m_eye[1][i] = ptrEyeView->m_eye[i];
			m_pDoc->m_eyeList->m_eye[0][i] = pView->m_eye[i];
		}

		m_pDoc->m_eyeList->m_fieldOfView[0] = pView->m_fieldOfView;
		m_pDoc->m_eyeList->m_clipFront[0] = pView->m_clipFront;
		m_pDoc->m_eyeList->m_clipRear[0] = pView->m_clipRear;
		m_pDoc->m_eyeList->m_fieldOfView[1] = ptrEyeView->m_eye[9];
		m_pDoc->m_eyeList->m_clipFront[1] = ptrEyeView->m_eye[10];
		m_pDoc->m_eyeList->m_clipRear[1] = ptrEyeView->m_eye[11];

		if (m_pDoc->m_eyeList->m_timeOfMove < 0.0)
		{
			m_pDoc->m_eyeList->m_timeOfMove = 0.0;
		}

		if (m_pDoc->m_eyeList->m_fieldOfView[1] <= 0.0
			&& m_pDoc->m_eyeList->m_fieldOfView[1] >= 180.0)
		{
			m_pDoc->m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
		}
		if (m_pDoc->m_eyeList->m_clipFront[1] < 0.0
			|| m_pDoc->m_eyeList->m_clipFront[1] >= m_pDoc->m_eyeList->m_clipRear[1])
		{
			m_pDoc->m_eyeList->m_clipFront[1] = pView->m_clipFront;
		}
		if (m_pDoc->m_eyeList->m_clipFront[1] >= m_pDoc->m_eyeList->m_clipRear[1])
		{
			m_pDoc->m_eyeList->m_clipRear[1] = pView->m_clipRear;
		}

		if (m_pDoc->m_eyeList->m_moving == FALSE)
		{
			m_pDoc->m_eyeList->m_moving = TRUE;
			m_pDoc->m_isMovement++;
		}

		::GetSystemTime(&m_pDoc->m_eyeList->m_gmTimeStart);

		sprintf(buf, "< -view %s %.3lf", deviceName, m_pDoc->m_eyeList->m_timeOfMove);
	}

	else if (strcmp(command, "-import") == 0)
	{
		sprintf(c[5], "#!9_9Ag*");
		sscanf(m_buf, "%*s %*s %s %s %d %s %s %s %s %s %s",
			fileName, barCode, &visible, pathName, &c[1], &c[2], &c[3], &c[4], &c[5]);

		if (m_pDoc->YoImportDevice(fileName, deviceName) == TRUE)
		{
			m_pDoc->m_currentDevice->m_visible = visible;
			sprintf(m_pDoc->m_currentDevice->m_barCode, "%s", barCode);

			if (strcmp(c[5], "#!9_9Ag*") != 0)
			//if (pathName[0] == '-' || pathName[0] == '.' || (pathName[0] >= '0' && pathName[0] <= '9'))
			// set translate / rotate values
			{
				sscanf(pathName, "%lf", &m[0]);
				for (i = 1; i < 6; i++)
				{
					sscanf(c[i], "%lf", &m[i]);
				}
				for (i = 0; i < 3; i++)
				{
					m_pDoc->m_currentDevice->m_ptrPart->m_translate[i] = m[i];
					m_pDoc->m_currentDevice->m_ptrPart->m_rotate[i + 3] = m[i + 3];
				}
			}
			else
			// snap device to path / tag
			{
				sscanf(c[1], "%d", &tag);
				if ((ptrPath = m_pDoc->YoPathHashLookup(pathName)) != NULL)
				{
					for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL
						&& ptrTag->m_tag != (UINT)tag; ptrTag = ptrTag->m_nextTag);
					if (ptrTag != NULL)
					{
						currentTag = m_pDoc->m_currentTag;
						m_pDoc->m_currentTag = ptrTag;
						m_pDoc->YoModelMatrixOfCurrentTag();
						m_pDoc->YoTranslateRotateValues(m_pDoc->m_mTag,
							m_pDoc->m_currentDevice->m_ptrPart->m_translate,
							m_pDoc->m_currentDevice->m_ptrPart->m_rotate);
						m_pDoc->m_currentTag = currentTag;
					}
				}
			}
			if (m_pDoc->m_currentDevice->m_visible && m_pDoc->m_isMovement == FALSE)
			{
				pView->YoRender(YO_RENDER_LIGHT);
				pView->YoRender(YO_RENDER_FULL);
			}

			//if (m_pDoc->m_acceptSocket != NULL)
			//{
				sprintf(buf, "| %s", m_pDoc->m_currentDevice->m_name);
			//	m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			//}
		}
		else //if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			//m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}

	else if (strcmp(command, "-export") == 0)
	{
		ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName);
		if (ptrDevice != NULL)
		{
			sprintf(buf, "| -export %s", deviceName);

			m_pDoc->m_currentDevice = ptrDevice;
			m_pDoc->YoDeleteDevice();

			if (m_pDoc->m_isMovement == FALSE)
			{
				pView->YoRender(YO_RENDER_LIGHT);
				pView->YoRender(YO_RENDER_FULL);
			}
		}
		else
		{
			sprintf(buf, "X %s", m_buf);
		}
	}

	else if (strcmp(command, "-snapToTag") == 0)
	{
		i = sscanf(m_buf, "%*s %*s %s", pathName);

		ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName);
		if (ptrDevice != NULL && i == 1)
		{
			// separate path from tag
			j = strlen(pathName);
			for (t = &pathName[j - 1]; isdigit(*t) && j > 0;)
			{
				j--;
				t--; 
			}
			if (j == 0) // invalid name
			{
				sprintf(pathName, "");
			}
			else if (j != strlen(pathName))
			{
				sscanf(&pathName[j], "%d", &tag);
				pathName[j] = '\0';
			}

			if ((ptrPath = m_pDoc->YoPathHashLookup(pathName)) != NULL)
			{
				if (tag < 0)
				{
					tag = 1;
				}

				for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL
					&& ptrTag->m_tag != (UINT)tag; ptrTag = ptrTag->m_nextTag);
				if (ptrTag != NULL)
				{
					m_pDoc->m_currentDevice = ptrDevice;
					m_pDoc->m_currentPart = ptrDevice->m_ptrPart;
					m_pDoc->m_currentTag = ptrTag;

					m_pDoc->YoDetachDevice();
					// reattach device at world coords (rightmost position)
					for (currentDevice = m_pDoc->m_deviceList;
						currentDevice->m_right != NULL;
						currentDevice = currentDevice->m_right);
					currentDevice->m_right = m_pDoc->m_currentDevice;
					m_pDoc->m_currentDevice->m_left = currentDevice;

					m_pDoc->YoModelMatrixOfCurrentTag();
					m_pDoc->m_currentDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
					m_pDoc->YoTranslateRotateValues(m_pDoc->m_mTag,
						m_pDoc->m_currentDevice->m_ptrPart->m_translate,
						m_pDoc->m_currentDevice->m_ptrPart->m_rotate);

					for (i = 0; i < 3; i++)
					{
						m_pDoc->m_currentDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
					}

					sprintf(buf, "| -snapToTag %s %s%d", deviceName, pathName, tag);

					if (m_pDoc->m_currentDevice->m_visible && m_pDoc->m_isMovement == FALSE)
					{
						pView->YoRender(YO_RENDER_LIGHT);
						pView->YoRender(YO_RENDER_FULL);
					}				
				}
				else
				{
					sprintf(buf, "X %s", m_buf);
				}
			}
			else
			{
				sprintf(buf, "X %s", m_buf);
			}
		}
		else
		{
			sprintf(buf, "X %s", m_buf);
		}
	}

	else if (strcmp(command, "-attach") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			i = sscanf(m_buf, "%*s %*s %s %s", attachToDeviceName, attachToPartName);
			
			if ((ptrToDevice = m_pDoc->YoDeviceHashLookup(attachToDeviceName)) != NULL)
			{
				if (i == 1 || (ptrAttachToPart = m_pDoc->YoPartLookup(ptrToDevice, attachToPartName)) == NULL)
				{
					ptrAttachToPart = ptrToDevice->m_ptrPart;
					sprintf(attachToPartName, "%s", ptrAttachToPart->m_partName);
				}

				currentDevice = m_pDoc->m_currentDevice;
				currentPart = m_pDoc->m_currentPart;
				m_pDoc->m_currentDevice = ptrDevice;
				m_pDoc->m_currentPart = ptrDevice->m_ptrPart;
				
				m_pDoc->YoDetachDevice();

				sprintf(m_pDoc->m_currentDevice->m_parent, "%s", 
					ptrToDevice->m_name);
				m_pDoc->YoAttachDevice(ptrAttachToPart);
				m_pDoc->m_currentDevice = currentDevice;
				m_pDoc->m_currentPart = currentPart;

				sprintf(buf, "| -attach %s %s %s", deviceName, attachToDeviceName, attachToPartName);
			}
			else
			{
				sprintf(buf, "X %s", m_buf);
			}			
		}
		else
		{
			sprintf(buf, "X %s", m_buf);
		}

		if (m_pDoc->m_isMovement == FALSE)
		{
			pView->YoRender(YO_RENDER_LIGHT);
			pView->YoRender(YO_RENDER_FULL);
		}
	}

	else if (strcmp(command, "-detach") == 0)
	{
		ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName);

		if (ptrDevice != NULL
			&& strcmp(ptrDevice->m_parent, "NONE") != 0)
		{
			ptrToDevice = ptrDevice;
			currentDevice = m_pDoc->m_currentDevice;
			currentPart = m_pDoc->m_currentPart;
			m_pDoc->m_currentDevice = ptrToDevice;
			m_pDoc->m_currentPart = ptrToDevice->m_ptrPart; 

			m_pDoc->YoDetachDevice();

			// reattach device at world coords (rightmost position)
			for (ptrToDevice = m_pDoc->m_deviceList;
				ptrToDevice->m_right != NULL;
				ptrToDevice = ptrToDevice->m_right);

			ptrToDevice->m_right = m_pDoc->m_currentDevice;
			m_pDoc->m_currentDevice->m_left = ptrToDevice;
			ptrToDevice = ptrToDevice->m_right;

			m_pDoc->m_currentDevice = currentDevice;
			m_pDoc->m_currentPart = currentPart;
		}

		if (ptrDevice != NULL)
		{
			sprintf(buf, "| -detach %s", deviceName);
		}
		else
		{
			sprintf(buf, "X %s", m_buf);
		}
	}

	else if (strcmp(command, "-eye") == 0)
	{
		i = sscanf(m_buf, "%*s %s %s %s %s %s %s %s %s %s %s %s %s %s",
			&c[0], &c[1], &c[2], &c[3], &c[4], &c[5], &c[6],
			&c[7], &c[8], &c[9], &c[10], &c[11], &c[12]);

		if (i == 13)
		{
			for (i = 0; i < 9; i++)
			{
				if (c[i][0] == '*')
				{
					m_pDoc->m_eyeList->m_eye[1][i] = pView->m_eye[i];
				}
				else
				{
					m_pDoc->m_eyeList->m_eye[1][i] = pView->m_eye[i];
					sscanf(c[i], "%lf", &m_pDoc->m_eyeList->m_eye[1][i]);
				}
				m_pDoc->m_eyeList->m_eye[0][i] = pView->m_eye[i];
			}

			m_pDoc->m_eyeList->m_eye[1][6] = 0.0;
			m_pDoc->m_eyeList->m_eye[1][7] = 0.0;
			m_pDoc->m_eyeList->m_eye[1][8] = 1.0;

			if (c[9][0] == '*')
			{
				m_pDoc->m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
			}
			else
			{
				m_pDoc->m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
				sscanf(c[9], "%lf", &m_pDoc->m_eyeList->m_fieldOfView[1]);
			}

			if (c[10][0] == '*')
			{
				m_pDoc->m_eyeList->m_clipFront[1] = pView->m_clipFront;
			}
			else
			{
				m_pDoc->m_eyeList->m_clipFront[1] = pView->m_clipFront;
				sscanf(c[10], "%lf", &m_pDoc->m_eyeList->m_clipFront[1]);
			}

			if (c[11][0] == '*')
			{
				m_pDoc->m_eyeList->m_clipRear[1] = pView->m_clipRear;
			}
			else
			{
				m_pDoc->m_eyeList->m_clipRear[1] = pView->m_clipRear;
				sscanf(c[11], "%lf", &m_pDoc->m_eyeList->m_clipRear);
			}
			if (c[12][0] == '*')
			{
				m_pDoc->m_eyeList->m_timeOfMove = 0.0;
			}
			else
			{
				m_pDoc->m_eyeList->m_timeOfMove = 0.0;
				sscanf(c[12], "%lf", &m_pDoc->m_eyeList->m_timeOfMove);
			}

			m_pDoc->m_eyeList->m_fieldOfView[0] = pView->m_fieldOfView;
			m_pDoc->m_eyeList->m_clipFront[0] = pView->m_clipFront;
			m_pDoc->m_eyeList->m_clipRear[0] = pView->m_clipRear;

			if (m_pDoc->m_eyeList->m_timeOfMove < 0.0)
			{
				m_pDoc->m_eyeList->m_timeOfMove = 0.0;
			}

			if (m_pDoc->m_eyeList->m_fieldOfView[1] <= 0.0
				|| m_pDoc->m_eyeList->m_fieldOfView[1] >= 180.0)
			{
				m_pDoc->m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
			}
			if (m_pDoc->m_eyeList->m_clipFront[1] < 0.0
				|| m_pDoc->m_eyeList->m_clipFront[1] >= m_pDoc->m_eyeList->m_clipRear[1])
			{
				m_pDoc->m_eyeList->m_clipFront[1] = pView->m_clipFront;
			}
			if (m_pDoc->m_eyeList->m_clipFront[1] >= m_pDoc->m_eyeList->m_clipRear[1])
			{
				m_pDoc->m_eyeList->m_clipRear[1] = pView->m_clipRear;
			}

			if (m_pDoc->m_eyeList->m_moving == FALSE)
			{
				m_pDoc->m_eyeList->m_moving = TRUE;
				m_pDoc->m_isMovement++;
			}

			::GetSystemTime(&m_pDoc->m_eyeList->m_gmTimeStart);

			sprintf(buf, "< -eye %.3lf", m_pDoc->m_eyeList->m_timeOfMove);
		}
		else
		{
			sprintf(buf, "X %s", m_buf);
		}
	}

	else
	{
		sprintf(buf, "X %s", m_buf);
	}

	if (buf[0] != 'X')
	{
		ptrCommand = new CStageCommand(m_pDoc);
		::GetSystemTime(&ptrCommand->m_gmTime);
		sprintf(ptrCommand->m_buf, "%s", m_buf);
		ptrCommand->YoInsertCommand();
	}

	if (m_pDoc->m_acceptSocket != NULL)
	{
		m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
	}


	memset(m_buf, 0, 256);
	if ((i = Receive(m_buf, sizeof(m_buf), MSG_PEEK)) > 0)
	{
		return;
	}
	else if (m_pDoc->m_isMovement)
	{
		//sprintf(m_buf, "****"); // needed to tell YoMove() not to return
		m_pDoc->YoMove();
	}
	***/

	return;


	// old mc commands begin here ////////////////////////////////////////////////////

	if (strcmp(command, "mcEye") == 0)
	{
		sscanf(m_buf, "%*s %s %s %s %s %s %s %s %s %s %s %s %s %s",
			&c[0], &c[1], &c[2], &c[3], &c[4], &c[5], &c[6],
			&c[7], &c[8], &c[9], &c[10], &c[11], &c[12]);

		for (i = 0; i < 9; i++)
		{
			if (c[i][0] == '*')
			{
				m_pDoc->m_eyeList->m_eye[1][i] = pView->m_eye[i];
			}
			else
			{
				sscanf(c[i], "%lf", &m_pDoc->m_eyeList->m_eye[1][i]);
			}
			m_pDoc->m_eyeList->m_eye[0][i] = pView->m_eye[i];
		}

		if (c[9][0] == '*')
		{
			m_pDoc->m_eyeList->m_timeOfMove = 0.0;
		}
		else
		{
			sscanf(c[9], "%lf", &m_pDoc->m_eyeList->m_timeOfMove);
		}

		if (c[10][0] == '*')
		{
			m_pDoc->m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
		}
		else
		{
			sscanf(c[10], "%lf", &m_pDoc->m_eyeList->m_fieldOfView[1]);
		}

		if (c[11][0] == '*')
		{
			m_pDoc->m_eyeList->m_clipFront[1] = pView->m_clipFront;
		}
		else
		{
			sscanf(c[11], "%lf", &m_pDoc->m_eyeList->m_clipFront[1]);
		}

		if (c[12][0] == '*')
		{
			m_pDoc->m_eyeList->m_clipRear[1] = pView->m_clipRear;
		}
		else
		{
			sscanf(c[12], "%lf", &m_pDoc->m_eyeList->m_clipRear);
		}

		m_pDoc->m_eyeList->m_fieldOfView[0] = pView->m_fieldOfView;
		m_pDoc->m_eyeList->m_clipFront[0] = pView->m_clipFront;
		m_pDoc->m_eyeList->m_clipRear[0] = pView->m_clipRear;

		if (m_pDoc->m_eyeList->m_timeOfMove < 0.0)
		{
			m_pDoc->m_eyeList->m_timeOfMove = 0.0;
		}

		if (m_pDoc->m_eyeList->m_fieldOfView[1] <= 0.0
			&& m_pDoc->m_eyeList->m_fieldOfView[1] >= 180.0)
		{
			m_pDoc->m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
		}
		if (m_pDoc->m_eyeList->m_clipFront[1] < 0.0
			|| m_pDoc->m_eyeList->m_clipFront[1] >= m_pDoc->m_eyeList->m_clipRear[1])
		{
			m_pDoc->m_eyeList->m_clipFront[1] = pView->m_clipFront;
		}
		if (m_pDoc->m_eyeList->m_clipFront[1] >= m_pDoc->m_eyeList->m_clipRear[1])
		{
			m_pDoc->m_eyeList->m_clipRear[1] = pView->m_clipRear;
		}

		if (m_pDoc->m_eyeList->m_moving == FALSE)
		{
			m_pDoc->m_eyeList->m_moving = TRUE;
			m_pDoc->m_isMovement++;
		}


		if (m_pDoc->m_mode == YO_MODE_PLAY_SIM// && m_pDoc->m_realTime == FALSE
			&& m_pDoc->m_currentCommand != NULL)
		{
			m_pDoc->m_eyeList->m_timeStart = m_pDoc->m_currentCommand->m_time;
		}
		else
		{
			m_pDoc->m_eyeList->m_gmTimeStart = m_pDoc->m_gmTime;
		}

		if (m_pDoc->m_acceptSocket != NULL)
		{
			sprintf(buf, "< %.3lf", m_pDoc->m_eyeList->m_timeOfMove);
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}

	else if (strcmp(command, "mcView") == 0
		&& (ptrEyeView = m_pDoc->YoEyeViewHashLookup(deviceName)) != NULL)
	{
		sscanf(m_buf, "%*s %*s %lf", &m_pDoc->m_eyeList->m_timeOfMove);

		for (i = 0; i < 9; i++)
		{
			m_pDoc->m_eyeList->m_eye[1][i] = ptrEyeView->m_eye[i];
			m_pDoc->m_eyeList->m_eye[0][i] = pView->m_eye[i];
		}

		m_pDoc->m_eyeList->m_fieldOfView[0] = pView->m_fieldOfView;
		m_pDoc->m_eyeList->m_clipFront[0] = pView->m_clipFront;
		m_pDoc->m_eyeList->m_clipRear[0] = pView->m_clipRear;
		m_pDoc->m_eyeList->m_fieldOfView[1] = ptrEyeView->m_eye[9];
		m_pDoc->m_eyeList->m_clipFront[1] = ptrEyeView->m_eye[10];
		m_pDoc->m_eyeList->m_clipRear[1] = ptrEyeView->m_eye[11];

		if (m_pDoc->m_eyeList->m_timeOfMove < 0.0)
		{
			m_pDoc->m_eyeList->m_timeOfMove = 0.0;
		}

		if (m_pDoc->m_eyeList->m_fieldOfView[1] <= 0.0
			&& m_pDoc->m_eyeList->m_fieldOfView[1] >= 180.0)
		{
			m_pDoc->m_eyeList->m_fieldOfView[1] = pView->m_fieldOfView;
		}
		if (m_pDoc->m_eyeList->m_clipFront[1] < 0.0
			|| m_pDoc->m_eyeList->m_clipFront[1] >= m_pDoc->m_eyeList->m_clipRear[1])
		{
			m_pDoc->m_eyeList->m_clipFront[1] = pView->m_clipFront;
		}
		if (m_pDoc->m_eyeList->m_clipFront[1] >= m_pDoc->m_eyeList->m_clipRear[1])
		{
			m_pDoc->m_eyeList->m_clipRear[1] = pView->m_clipRear;
		}

		if (m_pDoc->m_eyeList->m_moving == FALSE)
		{
			m_pDoc->m_eyeList->m_moving = TRUE;
			m_pDoc->m_isMovement++;
		}

		if (m_pDoc->m_mode == YO_MODE_PLAY_SIM// && m_pDoc->m_realTime == FALSE
			&& m_pDoc->m_currentCommand != NULL)
		{
			m_pDoc->m_eyeList->m_timeStart = m_pDoc->m_currentCommand->m_time;
		}
		else
		{
			m_pDoc->m_eyeList->m_gmTimeStart = m_pDoc->m_gmTime;
		}

		if (m_pDoc->m_acceptSocket != NULL)
		{
			sprintf(buf, "< %.3lf", m_pDoc->m_eyeList->m_timeOfMove);
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}

	else if (strcmp(command, "mcMoveTo") == 0
		|| strcmp(command, "mcMoveAppro") == 0)
	{
		ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName);

		if (ptrDevice != NULL && ptrDevice->m_type == YO_ROBOT6)
		{
			sscanf(m_buf, "%*s %*s %s %d %lf", pathName, &tag, &appro);
			if ((ptrPath = m_pDoc->YoPathHashLookup(pathName)) != NULL)
			{
				if (tag < 0)
				{
					tag = 1;
				}
				if (appro < 0.0)
				{
					appro = 0.0;
				}
				for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL
					&& ptrTag->m_tag != (UINT)tag; ptrTag = ptrTag->m_nextTag);
				if (ptrTag != NULL)
				{
					currentDevice = m_pDoc->m_currentDevice;
					currentPart = m_pDoc->m_currentPart;
					currentTag = m_pDoc->m_currentTag;
					m_pDoc->m_currentDevice = ptrDevice;
					m_pDoc->m_currentPart = ptrDevice->m_ptrPart;
					m_pDoc->m_currentTag = ptrTag;

					m_pDoc->YoModelMatrixOfCurrentPart(m);
					m_pDoc->YoMatrixInverse(m, mInv);
					m_pDoc->YoModelMatrixOfCurrentTag();
					::glMatrixMode(GL_MODELVIEW);
					::glPushMatrix();
				
					::glLoadMatrixd(m_pDoc->m_mTag);
					::glTranslated(0.0, 0.0,
						-((CStageRobot6 *)m_pDoc->m_currentDevice)->m_tcpOffset[2] - appro);
					::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					::glLoadMatrixd(mInv);
					::glMultMatrixd(m);
					// m is matrix of tag relative to robot6 base
					::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					::glPopMatrix();

					m_pDoc->m_currentDevice = currentDevice;
					m_pDoc->m_currentPart = currentPart;
					m_pDoc->m_currentTag = currentTag;

					if (((CStageRobot6 *)ptrDevice)->m_moving == FALSE
						&& ((CStageRobot6 *)ptrDevice)->YoMoveTo(m) == TRUE)
					{
						//sprintf(m_buf, "****");
						//((CStageRobot6 *)ptrDevice)->YoMoveTo(m);
						if (m_pDoc->m_acceptSocket != NULL)
						{
							sprintf(buf, "< %.3lf", ((CStageRobot6 *)ptrDevice)->m_timeOfMove);
							m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
						}
					}
					else
					{
						// robot is already moving or move is invalid
						if (m_pDoc->m_acceptSocket != NULL)
						{
							// send error
							sprintf(buf, "X");
							m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
						}
					}
					
				}
			}
		}
		else if (ptrDevice != NULL && ptrDevice->m_type == YO_TRAIN)
		{
			currentPart = NULL;
			sscanf(m_buf, "%*s %*s %s %lf", trackName, &relativePosition);
			ptrParent = m_pDoc->YoDeviceHashLookup(ptrDevice->m_parent);
			if (ptrParent != NULL)
			{
				currentPart = m_pDoc->YoPartLookup(ptrParent, trackName);
			}
			if (currentPart != NULL && currentPart->m_ptrTrackSeg != NULL)
			{
				((CStageTrain *)ptrDevice)->m_ptrTrackSegEnd = currentPart->m_ptrTrackSeg;
				relativePosition = YO_MAX(relativePosition, 0.0f);
				relativePosition = YO_MIN(relativePosition, 1.0f);
				((CStageTrain *)ptrDevice)->m_relativePositionEnd = relativePosition;

				if (((CStageTrain *)ptrDevice)->m_moving == FALSE)
				{
					((CStageTrain *)ptrDevice)->m_moving = TRUE;
					m_pDoc->m_isMovement++;

					if (m_pDoc->m_mode == YO_MODE_PLAY_SIM// && m_pDoc->m_realTime == FALSE
						&& m_pDoc->m_currentCommand != NULL)
					{
						((CStageTrain *)ptrDevice)->m_timeStart = m_pDoc->m_currentCommand->m_time;
					}
					else
					{
						((CStageTrain *)ptrDevice)->m_gmTimeStart = m_pDoc->m_gmTime;
					}
				}
				
				if (m_pDoc->m_acceptSocket != NULL)
				{
					sprintf(buf, "<");
					m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
				}
			}
			else
			{
				// train not attached to track or invalid track #
				sprintf(buf, "X");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}

	else if (strcmp(command, "mcImportDevice") == 0)
	{
		sprintf(c[5], "#!9_9Ag*");
		sscanf(m_buf, "%*s %*s %s %s %d %s %s %s %s %s %s",
			fileName, barCode, &visible, pathName, &c[1], &c[2], &c[3], &c[4], &c[5]);

		if (m_pDoc->YoImportDevice(fileName, deviceName) == TRUE)
		{
			m_pDoc->m_currentDevice->m_visible = visible;
			sprintf(m_pDoc->m_currentDevice->m_barCode, "%s", barCode);

			if (strcmp(c[5], "#!9_9Ag*") != 0)
			//if (pathName[0] == '-' || pathName[0] == '.' || (pathName[0] >= '0' && pathName[0] <= '9'))
			// set translate / rotate values
			{
				sscanf(pathName, "%lf", &m[0]);
				for (i = 1; i < 6; i++)
				{
					sscanf(c[i], "%lf", &m[i]);
				}
				for (i = 0; i < 3; i++)
				{
					m_pDoc->m_currentDevice->m_ptrPart->m_translate[i] = m[i];
					m_pDoc->m_currentDevice->m_ptrPart->m_rotate[i + 3] = m[i + 3];
				}
			}
			else
			// snap device to path / tag
			{
				sscanf(c[1], "%d", &tag);
				if ((ptrPath = m_pDoc->YoPathHashLookup(pathName)) != NULL)
				{
					for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL
						&& ptrTag->m_tag != (UINT)tag; ptrTag = ptrTag->m_nextTag);
					if (ptrTag != NULL)
					{
						currentTag = m_pDoc->m_currentTag;
						m_pDoc->m_currentTag = ptrTag;
						m_pDoc->YoModelMatrixOfCurrentTag();
						m_pDoc->YoTranslateRotateValues(m_pDoc->m_mTag,
							m_pDoc->m_currentDevice->m_ptrPart->m_translate,
							m_pDoc->m_currentDevice->m_ptrPart->m_rotate);
						m_pDoc->m_currentTag = currentTag;
					}
				}
			}

			//for (i = 0; i < 3; i++)
			//{
			//	m_pDoc->m_currentDevice->m_ptrPart->m_translate[i] = m[i];
			//	m_pDoc->m_currentDevice->m_ptrPart->m_rotate[i + 3] = m[i + 3];
			//}
			if (m_pDoc->m_currentDevice->m_visible && m_pDoc->m_isMovement == FALSE)
			{
				pView->YoRender(YO_RENDER_LIGHT);
				pView->YoRender(YO_RENDER_FULL);
			}

			if (m_pDoc->m_acceptSocket != NULL)
			{
				sprintf(buf, "| %s", m_pDoc->m_currentDevice->m_name);
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}

	else if (strcmp(command, "mcExportDevice") == 0)
	{
		ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName);
		if (ptrDevice != NULL)
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				sprintf(buf, "| %s", m_pDoc->m_currentDevice->m_name);
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}

			m_pDoc->m_currentDevice = ptrDevice;
			//m_pDoc->YoDetachDevice();
			m_pDoc->YoDeleteDevice();

			if (m_pDoc->m_isMovement == FALSE)
			{
				pView->YoRender(YO_RENDER_LIGHT);
				pView->YoRender(YO_RENDER_FULL);
			}
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}

	else if (strcmp(command, "mcConfigureRobot") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL
			&& ptrDevice->m_type == YO_ROBOT6)
		{
			sscanf(m_buf, "%*s %*s %d %d %d", &lefty, &elbowUp, &flipped);
			if (lefty == 0)
			{
				((CStageRobot6 *)ptrDevice)->m_lefty = FALSE;
			}
			else
			{
				((CStageRobot6 *)ptrDevice)->m_lefty = TRUE;
			}
			if (elbowUp == 0)
			{
				((CStageRobot6 *)ptrDevice)->m_elbowUp = FALSE;
			}
			else
			{
				((CStageRobot6 *)ptrDevice)->m_elbowUp = TRUE;
			}
			if (flipped == 0)
			{
				((CStageRobot6 *)ptrDevice)->m_wristFlipped = FALSE;
			}
			else
			{
				((CStageRobot6 *)ptrDevice)->m_wristFlipped = TRUE;
			}

			if (m_pDoc->m_acceptSocket != NULL)
			{
				sprintf(buf, "| %d %d %d",
					((CStageRobot6 *)ptrDevice)->m_lefty,
					((CStageRobot6 *)ptrDevice)->m_elbowUp,
					((CStageRobot6 *)ptrDevice)->m_wristFlipped);
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}

		}
		else
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				// send error
				sprintf(buf, "X");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
	}
	else if (strcmp(command, "mcSetSpeed") == 0)
	{
		ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName);
		if (ptrDevice != NULL && ptrDevice->m_type == YO_ROBOT6)
		{
			sscanf(m_buf, "%*s %*s %lf", &speed);
			((CStageRobot6 *)ptrDevice)->m_speed = (int)(speed * 100.0);
			((CStageRobot6 *)ptrDevice)->m_speed
				= YO_MIN(100, ((CStageRobot6 *)ptrDevice)->m_speed);
			((CStageRobot6 *)ptrDevice)->m_speed
				= YO_MAX(1, ((CStageRobot6 *)ptrDevice)->m_speed);

			if (m_pDoc->m_acceptSocket != NULL)
			{
				sprintf(buf, "| %.3lf", ((CStageRobot6 *)ptrDevice)->m_speed / 100.0);
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
		else if (ptrDevice != NULL && ptrDevice->m_type == YO_TRAIN)
		{
			sscanf(m_buf, "%*s %*s %lf", &((CStageTrain *)ptrDevice)->m_velocity);

			if (m_pDoc->m_acceptSocket != NULL)
			{
				sprintf(buf, "| %.3lf", ((CStageTrain *)ptrDevice)->m_velocity);
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
		else
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				// send error
				sprintf(buf, "X");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
	}


	else if (strcmp(command, "mcAttach") == 0
		|| strcmp(command, "mcCloseGrip") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			if (strcmp(command, "mcCloseGrip") == 0)
			{
				((CStageGripper *)ptrDevice)->m_gripping = TRUE;
			}
			sscanf(m_buf, "%*s %*s %s %s", attachToDeviceName, attachToPartName);
			
			if ((ptrToDevice = m_pDoc->YoDeviceHashLookup(attachToDeviceName)) != NULL)
			{
				if (strcmp(command, "mcCloseGrip") == 0)
				{
					ptrTempDevice = ptrDevice;
					ptrDevice = ptrToDevice;
					ptrToDevice = ptrTempDevice;
					ptrAttachToPart = ptrToDevice->m_ptrPart;
				}
				else if ((ptrAttachToPart = m_pDoc->YoPartLookup(ptrToDevice, attachToPartName)) == NULL)
				{
					ptrAttachToPart = ptrToDevice->m_ptrPart;
				}

				currentDevice = m_pDoc->m_currentDevice;
				currentPart = m_pDoc->m_currentPart;
				m_pDoc->m_currentDevice = ptrDevice;
				m_pDoc->m_currentPart = ptrDevice->m_ptrPart;
				
				//if (strcmp(m_pDoc->m_currentDevice->m_parent, "NONE") != 0)
				//{
					m_pDoc->YoDetachDevice();
				//}
				sprintf(m_pDoc->m_currentDevice->m_parent, "%s", 
					ptrToDevice->m_name);
				m_pDoc->YoAttachDevice(ptrAttachToPart);
				m_pDoc->m_currentDevice = currentDevice;
				m_pDoc->m_currentPart = currentPart;
			}

			if (m_pDoc->m_acceptSocket != NULL)
			{
				sprintf(buf, "|");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
		else
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				// send error
				sprintf(buf, "X");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}

		if (!m_pDoc->m_isMovement && strcmp(command, "mcCloseGrip") == 0)
		{
			pView->YoRender(YO_RENDER_FULL);
		}

	}

	else if (strcmp(command, "mcDetach") == 0
		|| strcmp(command, "mcOpenGrip") == 0)
	{
		ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName);

		if (ptrDevice != NULL)
		{
			if (strcmp(command, "mcOpenGrip") == 0)
			{
				ptrToDevice = ptrDevice->m_down;
				((CStageGripper *)ptrDevice)->m_gripping = FALSE;
			}
			else
			{
				ptrToDevice = ptrDevice;
			}
		}

		if (ptrToDevice != NULL
			&& strcmp(ptrToDevice->m_parent, "NONE") != 0)
		{
			currentDevice = m_pDoc->m_currentDevice;
			currentPart = m_pDoc->m_currentPart;
			m_pDoc->m_currentDevice = ptrToDevice;
			m_pDoc->m_currentPart = ptrToDevice->m_ptrPart; 

			//if (strcmp(m_pDoc->m_currentDevice->m_parent, "NONE") == 0)
			//{
			//	return;
			//}

			if (m_pDoc->m_currentDevice->m_type == YO_TRAIN)
			{
				((CStageTrain *)m_pDoc->m_currentDevice)->m_ptrTrackSeg = NULL;
			}

			m_pDoc->YoDetachDevice();

			// reattach device at world coords (rightmost position)
			for (ptrToDevice = m_pDoc->m_deviceList;
				ptrToDevice->m_right != NULL;
				ptrToDevice = ptrToDevice->m_right);
			ptrToDevice->m_right = m_pDoc->m_currentDevice;
			m_pDoc->m_currentDevice->m_left = ptrToDevice;
			ptrToDevice = ptrToDevice->m_right;

			//pMainFrame->SendMessage(WM_COMMAND, ID_DEVICE_DETACH, (LPARAM)0);
			m_pDoc->m_currentDevice = currentDevice;
			m_pDoc->m_currentPart = currentPart;
		}

		if (ptrDevice != NULL)
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				sprintf(buf, "|");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
		else
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				// send error
				sprintf(buf, "X");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}

		if (!m_pDoc->m_isMovement && strcmp(command, "mcOpenGrip") == 0)
		{
			pView->YoRender(YO_RENDER_FULL);
		}

	}

	else if (strcmp(command, "mcSetRTableAccel") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sscanf(m_buf, "%*s %*s %lf", &x);
			sprintf(s, "A %.3lf", x);
			((CStageRotaryTable *)ptrDevice)->YoHandleSim(s);
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}
	else if (strcmp(command, "mcSetRTableSpeed") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sscanf(m_buf, "%*s %*s %lf", &x);
			sprintf(s, "V %.3lf", x);
			((CStageRotaryTable *)ptrDevice)->YoHandleSim(s);
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}
	else if (strcmp(command, "mcSetRTableNextPosition") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sscanf(m_buf, "%*s %*s %ld", &distance);
			sprintf(s, "D %ld", distance);
			((CStageRotaryTable *)ptrDevice)->YoHandleSim(s);
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}
	else if (strcmp(command, "mcRTableGo") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sprintf(s, "G");
			((CStageRotaryTable *)ptrDevice)->YoHandleSim(s);
				
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}
	else if (strcmp(command, "mcRTableHome") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sscanf(m_buf, "%*s %*s %lf", &x);
			sprintf(s, "GH %.3lf", x);
			((CStageRotaryTable *)ptrDevice)->YoHandleSim(s);
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}
	else if (strcmp(command, "mcRTableDPA") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sprintf(s, "1DPA");
			((CStageRotaryTable *)ptrDevice)->YoHandleSim(s);
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}

	else if (strcmp(command, "mcConveyorGo") == 0)
	// mcConveyor devicename segmentname %speed
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sscanf(m_buf, "%*s %*s %s %lf", &trackName, &x);
			sprintf(s, "GO %s %.3lf", trackName, x);
			((CStageConveyor *)ptrDevice)->YoHandleSim(s);
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}

	else if (strcmp(command, "mcConveyorStopGate") == 0)
	// mcConveyor deviceName stopGateName up
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sscanf(m_buf, "%*s %*s %s %d", &trackName, &i);
			sprintf(s, "SG %s %d", trackName, i);
			((CStageConveyor *)ptrDevice)->YoHandleSim(s);
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}

	else if (strcmp(command, "mcConveyorTransverseLift") == 0)
	// mcConveyor devicename liftName up
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sscanf(m_buf, "%*s %*s %s %d", &trackName, &i);
			sprintf(s, "TL %s %d", trackName, i);
			((CStageConveyor *)ptrDevice)->YoHandleSim(s);
		}
		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}
	}


	else if (strcmp(command, "mcTriggerBarCodeOn") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			if (((CStageBarCodeReader *)ptrDevice)->m_scanning == FALSE)
			{
				((CStageBarCodeReader *)ptrDevice)->m_scanning = TRUE;
				m_pDoc->m_isMovement++;
			}			

			((CStageBarCodeReader *)ptrDevice)->m_scanDistance = YO_SCAN_DISTANCE;
			sscanf(m_buf, "%*s %*s %s", attachToDeviceName);
			
			if ((ptrToDevice = m_pDoc->YoDeviceHashLookup(attachToDeviceName)) != NULL)
			{
				currentDevice = m_pDoc->m_currentDevice;
				currentPart = m_pDoc->m_currentPart;

				m_pDoc->m_currentDevice = ptrDevice;
				m_pDoc->m_currentPart = ptrDevice->m_ptrPart;
				m_pDoc->YoModelMatrixOfCurrentPart(m);

				m_pDoc->m_currentDevice = ptrToDevice;
				m_pDoc->m_currentPart = ptrToDevice->m_ptrPart;
				m_pDoc->YoModelMatrixOfCurrentPart(mInv);

				x = m[12] - mInv[12];
				y = m[13] - mInv[13];
				z = m[14] - mInv[14];

				((CStageBarCodeReader *)ptrDevice)->m_scanDistance
					= sqrt(x * x + y * y + z * z);

				m_pDoc->m_currentDevice = currentDevice;
				m_pDoc->m_currentPart = currentPart;
			}	
		}
		if (ptrDevice != NULL)
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				sprintf(buf, "|");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
		else
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				// send error
				sprintf(buf, "X");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
	}

	else if (strcmp(command, "mcGetBarCodeScan") == 0
		|| strcmp(command, "mcTriggerBarCodeOff") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			if (((CStageBarCodeReader *)ptrDevice)->m_scanning == TRUE)
			{
				((CStageBarCodeReader *)ptrDevice)->m_scanning = FALSE;
				m_pDoc->m_isMovement--;
			}
			((CStageBarCodeReader *)ptrDevice)->m_scanDistance = YO_SCAN_DISTANCE;
			sscanf(m_buf, "%*s %*s %s", attachToDeviceName);
			
			if ((ptrToDevice = m_pDoc->YoDeviceHashLookup(attachToDeviceName)) != NULL)
			{
				if (m_pDoc->m_acceptSocket != NULL
					&& strcmp(command, "mcGetBarCodeScan") == 0)
				{
					sprintf(buf, "| %s", ptrToDevice->m_barCode);
					m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
				}
			}
			else if (m_pDoc->m_acceptSocket != NULL)
			{
				sprintf(buf, "|");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}

		else if (m_pDoc->m_acceptSocket != NULL)
		{
			// send error
			sprintf(buf, "X");
			m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		}

		if (!m_pDoc->m_isMovement)
		{
			pView->YoRender(YO_RENDER_FULL);
		}
	}

	else if (strcmp(command, "mcGetWeight") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sscanf(m_buf, "%*s %*s %s", attachToDeviceName);
			if ((ptrToDevice = m_pDoc->YoDeviceHashLookup(attachToDeviceName)) != NULL)
			{
				sscanf(m_buf, "%*s %*s %s", attachToDeviceName);
				if (m_pDoc->m_acceptSocket != NULL)
				{
					if (((CStageScale *)ptrDevice)->m_units == YO_UNITS_POUNDS)
					{
						sprintf(buf, "| %.3lf", ptrToDevice->m_mass * 2.2);
					}
					else
					{
						sprintf(buf, "| %.3lf", ptrToDevice->m_mass);
					}
					m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
				}
			}
			else
			{
				if (m_pDoc->m_acceptSocket != NULL)
				{
					sprintf(buf, "| 0.000");
					m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
				}
			}
		}
		else
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				// send error
				sprintf(buf, "X");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}

		}
	}
	else if (strcmp(command, "mcSetScaleMode") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			sscanf(m_buf, "%*s %*s %s", s);
			if (toupper(s[0]) == 'L' || toupper(s[0]) == 'P')
			{
				((CStageScale *)ptrDevice)->m_units = YO_UNITS_POUNDS;
			}
			else
			{
				((CStageScale *)ptrDevice)->m_units = YO_UNITS_KILOGRAMS;
			}
			if (m_pDoc->m_acceptSocket != NULL)
			{
				if (((CStageScale *)ptrDevice)->m_units == YO_UNITS_POUNDS)
				{
					sprintf(buf, "| LB");
				}
				else
				{
					sprintf(buf, "| KG");
				}
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
		else
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				// send error
				sprintf(buf, "X");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
	}
	else if (strcmp(command, "mcIsMovement") == 0)
	{
		if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) != NULL)
		{
			if ((ptrDevice->m_type == YO_ROBOT6 && ((CStageRobot6 *)ptrDevice)->m_moving)
				|| (ptrDevice->m_type == YO_ROTARY_TABLE && ((CStageRotaryTable *)ptrDevice)->m_rotating)
				|| (ptrDevice->m_type == YO_TRAIN && ((CStageTrain *)ptrDevice)->m_moving))
			{
				if (m_pDoc->m_acceptSocket != NULL)
				{
					sprintf(buf, "| YES");
					m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
				}
			}
			else
			{
				if (m_pDoc->m_acceptSocket != NULL)
				{
					sprintf(buf, "| NO");
					m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
				}
			}
		}
		else
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				// send error
				sprintf(buf, "X");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}

	}
	else if (strcmp(command, "mcSetMaterial") == 0)
	{
		currentPart = NULL;
		ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName);
		if (ptrDevice != NULL)
		{
			sscanf(m_buf, "%*s %*s %s", s);
			currentPart = m_pDoc->YoPartLookup(ptrDevice, s);
		}

		if (ptrDevice != NULL && currentPart != NULL)
		{
			sscanf(m_buf, "%*s %*s %*s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
				&currentPart->m_ambient[0], &currentPart->m_ambient[1],
				&currentPart->m_ambient[2], &currentPart->m_ambient[3],
				&currentPart->m_diffuse[0], &currentPart->m_diffuse[1],
				&currentPart->m_diffuse[2], &currentPart->m_diffuse[3],
				&currentPart->m_specular[0], &currentPart->m_specular[1],
				&currentPart->m_specular[2], &currentPart->m_specular[3],
				&currentPart->m_emission[0], &currentPart->m_emission[1],
				&currentPart->m_emission[2], &currentPart->m_emission[3],
				&currentPart->m_wireframe[0], &currentPart->m_wireframe[1],
				&currentPart->m_wireframe[2], &currentPart->m_wireframe[3],
				&currentPart->m_shininess);

			for (i = 0; i < 4; i++)
			{
				currentPart->m_ambient[i] /= 255.0;
				currentPart->m_diffuse[i] /= 255.0;
				currentPart->m_specular[i] /= 255.0;
				currentPart->m_emission[i] /= 255.0;
				currentPart->m_wireframe[i] /= 255.0;
			}
			//currentPart->m_shininess /= 128.0;

			for (i = 0; i < 4; i++)
			{
				currentPart->m_ambient[i] = YO_MAX(currentPart->m_ambient[i], 0.0f);
				currentPart->m_diffuse[i] = YO_MAX(currentPart->m_diffuse[i], 0.0f);
				currentPart->m_specular[i] = YO_MAX(currentPart->m_specular[i], 0.0f);
				currentPart->m_emission[i] = YO_MAX(currentPart->m_emission[i], 0.0f);
				currentPart->m_wireframe[i] = YO_MAX(currentPart->m_wireframe[i], 0.0f);
			
				currentPart->m_ambient[i] = YO_MIN(currentPart->m_ambient[i], 1.0f);
				currentPart->m_diffuse[i] = YO_MIN(currentPart->m_diffuse[i], 1.0f);
				currentPart->m_specular[i] = YO_MIN(currentPart->m_specular[i], 1.0f);
				currentPart->m_emission[i] = YO_MIN(currentPart->m_emission[i], 1.0f);
				currentPart->m_wireframe[i] = YO_MIN(currentPart->m_wireframe[i], 1.0f);
			}
			currentPart->m_shininess = YO_MAX(currentPart->m_shininess, 0.0f);
			currentPart->m_shininess = YO_MIN(currentPart->m_shininess, 128.0f);

			if (!m_pDoc->m_isMovement)
			{
				pView->YoRender(YO_RENDER_FULL);
			}

			if (m_pDoc->m_acceptSocket != NULL)
			{
				sprintf(buf, "|");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}
		else
		{
			if (m_pDoc->m_acceptSocket != NULL)
			{
				// send error
				sprintf(buf, "X");
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}

	}


	if (m_pDoc->m_acceptSocket != NULL)
	{
		m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
	}

	if (m_pDoc->m_isMovement)
	{
		sprintf(m_buf, "****"); // needed to tell YoMove() not to return
		m_pDoc->YoMove();
	}

	return;
}


void CStageEye::YoCalculateEyePosition(void)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	int i;
	GLdouble d[3];
	GLdouble r[3];
	GLdouble f;
	GLdouble w[3];
	GLdouble cf;
	GLdouble cr;
	GLdouble a;
	double timeElapsed;
	//SYSTEMTIME gmTime;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	int tms;
	CTimeSpan spanSec;

	for (i = 0; i < 3; i++)
	{
		d[i] = m_eye[1][i] - m_eye[0][i];
		r[i] = m_eye[1][i + 3] - m_eye[0][i + 3];
		w[i] = m_eye[1][i + 6] - m_eye[0][i + 6];
	}
	f = m_fieldOfView[1] - m_fieldOfView[0];
	cf = m_clipFront[1] - m_clipFront[0];
	cr = m_clipRear[1] - m_clipRear[0];

	if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
	{
		timeElapsed = m_pDoc->m_timeCurrent - m_timeStart;	
		//TRACE1("Eye: timeElapsed = %.3lf\n", timeElapsed);
	}
	else
	{
		timeCurrent = m_pDoc->m_gmTime;
		timeStart = m_gmTimeStart;
		spanSec = timeCurrent - timeStart;
		tms = m_pDoc->m_gmTime.wMilliseconds - m_gmTimeStart.wMilliseconds;
		timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
		TRACE1("Eye: timeElapsed = %.3lf   ", timeElapsed);
		TRACE2("m_gmTimeStart = %d %d   ", m_gmTimeStart.wSecond, m_gmTimeStart.wMilliseconds);
		TRACE2("m_gmTime = %d %d\n", m_pDoc->m_gmTime.wSecond, m_pDoc->m_gmTime.wMilliseconds);
	}

	if (timeElapsed >= m_timeOfMove)
	{
		timeElapsed = m_timeOfMove;
		m_pDoc->m_isMovement--;
		m_moving = FALSE;

		//if (m_pDoc->m_acceptSocket != NULL)
		//{
		//	while (::PeekMessage(&msg, ((CWnd *)pView)->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONUP, PM_REMOVE));
		//	while (::PeekMessage(&msg, ((CWnd *)pView)->m_hWnd, WM_RBUTTONDOWN, WM_RBUTTONUP, PM_REMOVE));
		//	while (::PeekMessage(&msg, ((CWnd*)pMainFrame)->m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONUP, PM_REMOVE));
		//}

		for (i = 0; i < 9; i++)
		{
			pView->m_eye[i] = m_eye[1][i];
		}
		pView->m_fieldOfView = m_fieldOfView[1];
		pView->m_clipFront = m_clipFront[1];
		pView->m_clipRear = m_clipRear[1];
		return;
	}

	a = (sin(-PI / 2.0 + (PI * timeElapsed / m_timeOfMove)) + 1.0) / 2.0;
	for (i = 0; i < 3; i++)
	{
		pView->m_eye[i] = m_eye[0][i] + a * d[i];
		pView->m_eye[i + 3] = m_eye[0][i + 3] + a * r[i];
		pView->m_eye[i + 6] = m_eye[0][i + 6] + a * w[i];
	}
	pView->m_fieldOfView = m_fieldOfView[0] + a * f;
	pView->m_clipFront = m_clipFront[0] + a * cf;
	pView->m_clipRear = m_clipRear[0] + a * cr;

	return;
}


CStageEyeView::~CStageEyeView()
{
	int i;
	CStageEyeView *ptrEyeView;
	CStageEyeView *prevEyeView = NULL;

	// remove the name from the eye view hash table
	i = (int)m_pDoc->YoHash(m_name, YO_HASH_VALUE, YO_HASH_SIZE);
	
	for (ptrEyeView = m_pDoc->m_eyeViewHash[i];
		ptrEyeView != NULL && strcmp(m_name, ptrEyeView->m_name) != 0;
		ptrEyeView = ptrEyeView->m_nextHash)
	{
		prevEyeView = ptrEyeView;
	}
	if (prevEyeView == NULL)
	{
		m_pDoc->m_eyeViewHash[i] = ptrEyeView->m_nextHash;
	}
	else
	{
		prevEyeView->m_nextHash = ptrEyeView->m_nextHash;
	}
	ptrEyeView->m_nextHash = NULL;

	return;
}

BOOL CStageEyeView::YoReadEyeView(FILE *fp)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	char s[128];
	int ch = 0;
	char command[32];
	int i;
	int done = FALSE;

	this->m_nextHash = NULL;

	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "EYE_VIEW_NULL") == 0)
		{
			m_pDoc->YoEyeViewHashInstall(this);
			done = TRUE;
		}

		else if (strcmp(command, "EYE_VIEW_NAME") == 0)
		{
			sscanf(s, "%*s %s", &this->m_name);
		}

		else if (strcmp(command, "EYE_VIEW_EYE") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
				&this->m_eye[0], &this->m_eye[1], &this->m_eye[2],
				&this->m_eye[3], &this->m_eye[4], &this->m_eye[5],
				&this->m_eye[6], &this->m_eye[7], &this->m_eye[8],
				&this->m_eye[9], &this->m_eye[10], &this->m_eye[11]);
		}
	} // end while (!done)

	return TRUE;
}


void CStageRobot6::YoTagOnTcf(void)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	GLdouble mTcf[16];
	GLdouble mTag[16];
	GLdouble mTagInv[16];
	CStagePart *ptrPart;
	CStageDevice *ptrDevice;
	int j;

	ptrPart = m_pDoc->m_currentPart;
	ptrDevice = m_pDoc->m_currentDevice;

	m_pDoc->m_currentPart = m_ptrPart;
	for (j = 0; j <= 6 && m_pDoc->m_currentPart != NULL
		&& m_pDoc->m_currentPart->m_down != NULL; j++)
	{
		m_pDoc->m_currentPart = m_pDoc->m_currentPart->m_down;
	}
	m_pDoc->YoModelMatrixOfCurrentPart(mTcf);

	m_pDoc->m_currentPart = m_pDoc->m_currentTag->m_ptrPath->m_ptrPart;
	m_pDoc->m_currentDevice = m_pDoc->YoDeviceHashLookup(m_pDoc->m_currentPart->m_deviceName);
	m_pDoc->YoModelMatrixOfCurrentPart(mTag);

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glLoadMatrixd(mTcf);
	//::glTranslated(0.0, 0.0, 110.0);
	::glTranslated(0.0, 0.0, ((CStageRobot6 *)ptrDevice)->m_tcpOffset[2]);
	::glGetDoublev(GL_MODELVIEW_MATRIX, mTcf);

	m_pDoc->YoMatrixInverse(mTag, mTagInv);
	::glLoadMatrixd(mTagInv);
	::glMultMatrixd(mTcf);
	::glGetDoublev(GL_MODELVIEW_MATRIX, mTcf);

	/***

						pDoc->m_currentPart = ptrTag->m_ptrPath->m_ptrPart;
						pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(pDoc->m_currentPart->m_deviceName);
						pDoc->YoModelMatrixOfCurrentPart(m);
						pDoc->YoMatrixInverse(m, mInv);
						::glMatrixMode(GL_MODELVIEW);
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

						**/
	m_pDoc->YoTranslateRotateValues(mTcf, m_pDoc->m_currentTag->m_translate,
		m_pDoc->m_currentTag->m_rotate);
	for (j = 0; j < 3; j++)
	{
		m_pDoc->m_currentTag->m_rotate[j] *= YO_RADIANS_TO_DEGREES;
	}
	::glPopMatrix();

	m_pDoc->m_currentPart = ptrPart;
	m_pDoc->m_currentDevice = ptrDevice;

	if (m_pDoc->m_isMovement == FALSE
		&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
		&& m_pDoc->m_scriptFastForward == FALSE)
	{
		pView->YoRender(YO_RENDER_FULL);
	}





}


BOOL CStageRobot6::YoHandleCommand(char *buf)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	char command[32];
	char s[256];
	char *t;
	char teachPointName[64];
	int tag = -INT_MAX;
	double zOffset = -FLT_MAX;
	double zRotation = -FLT_MAX;
	int i;
	UINT j;
	CStagePath *ptrPath;
	CStageTag *ptrTag;
	double m[16];
	double mInv[16];
	double mTag[16];
	double mTagInv[16];
	double mRobot[16];
	int righty;
	int below;
	int flip;
	double timeElapsed;
	double timeOfMove = 0.0;
	//SYSTEMTIME gmTime;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	int tms;
	CTimeSpan spanSec;

	if (m_pDoc->m_scriptFastForward == TRUE)
	{
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0) + m_pDoc->m_timeSleepTotal;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else if (pMainFrame->m_wndDlgScript != NULL && pMainFrame->m_wndDlgScriptVisible == TRUE)
	{
		//::GetSystemTime(&m_pDoc->m_gmTime);
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0)
		//	+ pMainFrame->m_wndDlgScript->m_timeSleepFastForward
		//	- pMainFrame->m_wndDlgScript->m_timeFastForward;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else
	{
		::GetSystemTime(&m_pDoc->m_gmTime);
	}

	sscanf(buf, "%s", command);

	for (t = command; *t != '\0'; t++)
	{
		*t = toupper(*t);
	}

	if (strcmp(command, "MOVE") == 0 || strcmp(command, "MOVES") == 0
		|| strcmp(command, "APPRO") == 0 || strcmp(command, "APPRORS") == 0
		|| strcmp(command, "APPROS") == 0  || strcmp(command, "GETTEACHPOINTPOS") == 0)
	{
		i = sscanf(buf, "%*s %s %lf %lf %lf", teachPointName, &zOffset, &zRotation, &timeOfMove);

		if (i == 3 && strcmp(command, "APPROS") == 0)
		{
			timeOfMove = zRotation;
			zRotation = 0.0;
		}
		else if (i == 2 && strcmp(command, "MOVES") == 0)
		{
			timeOfMove = zOffset;
			zOffset = 0.0;
			zRotation = 0.0;
		}
		
		// separate path from tag
		j = strlen(teachPointName);
		for (t = &teachPointName[j - 1]; isdigit(*t) && j > 0;)
		{
			j--;
			t--; 
		}
		if (j == 0) // invalid name
		{
			sprintf(buf, "X");
			return TRUE;
		}
		if (j != strlen(teachPointName))
		{
			sscanf(&teachPointName[j], "%d", &tag);
			teachPointName[j] = '\0';
		}

		if ((ptrPath = m_pDoc->YoPathHashLookup(teachPointName)) != NULL)
		{
			if (tag < 0)
			{
				tag = 1;
			}
			if (zOffset < 0.0f)
			{
				zOffset = 0.0f;
			}
			if (zRotation < 0.0f)
			{
				zRotation = 0.0f;
			}

			for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL
				&& ptrTag->m_tag != (UINT)tag; ptrTag = ptrTag->m_nextTag);
			if (ptrTag != NULL)
			{
				//currentDevice = m_pDoc->m_currentDevice;
				//currentPart = m_pDoc->m_currentPart;
				//currentTag = m_pDoc->m_currentTag;
				m_pDoc->m_currentDevice = this;
				m_pDoc->m_currentPart = this->m_ptrPart;
				m_pDoc->m_currentTag = ptrTag;

				m_pDoc->YoModelMatrixOfCurrentPart(m);
				m_pDoc->YoMatrixInverse(m, mInv);
				m_pDoc->YoModelMatrixOfCurrentTag();
				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
			
				::glLoadMatrixd(m_pDoc->m_mTag);
				::glTranslated(0.0, 0.0, -m_tcpOffset[2] - zOffset);
				::glRotated(-m_tcpOffset[5] - zRotation, 0.0, 0.0, 1.0);
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				::glLoadMatrixd(mInv);
				::glMultMatrixd(m);
				// m is matrix of tag relative to robot6 base
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				::glPopMatrix();

				if (strcmp(command, "GETTEACHPOINTPOS") == 0)
				{
					sprintf(buf, "| %s GETTEACHPOINTPOS %s%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
						m_name, teachPointName, tag,
						m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10],
						m[11], m[12], m[13], m[14], m[15]);
					return TRUE;
				}

				//m_pDoc->m_currentDevice = currentDevice;
				//m_pDoc->m_currentPart = currentPart;
				//m_pDoc->m_currentTag = currentTag;

				if (m_moving == FALSE && YoMoveTo(m) == TRUE)
				{
					if (strcmp(command, "MOVES") == 0 || strcmp(command, "APPROS") == 0
						|| strcmp(command, "APPRORS") == 0)
					{
						m_jointInterpolation = FALSE;
						if (timeOfMove > 0.0 && timeOfMove < 60.0)
						{
							m_totalDistance *= (timeOfMove / m_timeOfMove);
							m_accelDistance *= (timeOfMove / m_timeOfMove);
							m_accelTime *= (timeOfMove / m_timeOfMove);
							m_timeOfMove = timeOfMove;
						}
					}
					else
					{
						m_jointInterpolation = TRUE;
					}
					sprintf(buf, "< %s %s %s%d %.3lf", m_name, command, teachPointName, tag, m_timeOfMove);
				}
				else
				{
					if (m_moving == FALSE && pMainFrame->m_viewPartActive == TRUE)
					{
						sprintf(s, "%s cannot reach %s%d in current configuration",
							m_pDoc->m_currentDevice->m_name, m_pDoc->m_currentTag->m_ptrPath->m_name,
							m_pDoc->m_currentTag->m_tag);
						m_pDoc->YoMessage(s);
					}
					// robot is already moving or move is invalid
					sprintf(buf, "X");
				}
				
			}
			else
			{
				sprintf(buf, "X");
			}
		}
		else
		{
			sprintf(buf, "X");
		}
	}

	else if (strcmp(command, "BRAKE") == 0)
	{
		if (m_moving == TRUE)
		{
			m_moving = FALSE;
			m_pDoc->m_isMovement--;
		}
		sprintf(buf, "| %s BRAKE", m_name);
	}

	else if (strcmp(command, "CONFIG") == 0 && m_moving == FALSE)
	{
		i = sscanf(buf, "%*s %d %d %d", &righty, &below, &flip);
		if (i == 3)
		{
			if (righty == TRUE)
			{
				m_lefty = FALSE;
			}
			else
			{
				m_lefty = TRUE;
			}
			if (below == TRUE)
			{
				m_elbowUp = FALSE;
			}
			else
			{
				m_elbowUp = TRUE;
			}
			if (flip == TRUE)
			{
				m_wristFlipped = TRUE;
			}
			else
			{
				m_wristFlipped = FALSE;
			}

			sprintf(buf, "| %s CONFIG %d %d %d", m_name, righty, below, flip);
		}
		else
		{
			sprintf(buf, "X");
		}
	}

	else if (strcmp(command, "SPEED") == 0  && m_moving == FALSE)
	{

		i = sscanf(buf, "%*s %d", &m_speed);
		if (i == 1)
		{
			m_speed	= YO_MIN(100, m_speed);
			m_speed	= YO_MAX(1, m_speed);

			sprintf(buf, "| %s SPEED %d", m_name, m_speed);
		}
		else
		{
			sprintf(buf, "X");
		}
	}

	else if (strcmp(command, "MOVEJOINTS") == 0 && m_moving == FALSE)
	{
		m_jointInterpolation = TRUE;
		i = sscanf(buf, "%*s %lf %lf %lf %lf %lf %lf",
			&m_jFinal[1], &m_jFinal[2], &m_jFinal[3],
			&m_jFinal[4], &m_jFinal[5], &m_jFinal[6]);

		if (i == 6)
		{
			m_jFinal[3] -= 180.0f;

			for (i = 1; i <= 6; i++)
			{
				m_jStart[i] = m_j[i];
			}

			if (YoCalculateTimeOfRotation() && m_timeOfMove > 0.0)
			{
				m_moving = TRUE;
				m_pDoc->m_isMovement++;
				sprintf(buf, "< %s MOVEJOINTS %.3lf", m_name, m_timeOfMove);
			}
			else
			{
				sprintf(buf, "X");
			}
		}
		else
		{
			sprintf(buf, "X");
		}
	}

	else if (strcmp(command, "TEACHPOINT") == 0)
	// Note: Staubli teachpoints are given in the form
	// tx ty tz rz ry rx, which differs from the stage form
	{
		i = sscanf(buf, "%*s %s %lf %lf %lf %lf %lf %lf", teachPointName,
			&m[0], &m[1], &m[2], &m[3], &m[4], &m[5]);

		if (i >= 2 && i <= 6)
		{
			sprintf(buf, "X");
			return TRUE;
		}
		
		// separate path from tag
		j = strlen(teachPointName);
		for (t = &teachPointName[j - 1]; isdigit(*t) && j > 0;)
		{
			j--;
			t--; 
		}
		if (j == 0) // invalid name
		{
			sprintf(buf, "X");
			return TRUE;
		}
		if (j != strlen(teachPointName))
		{
			sscanf(&teachPointName[j], "%d", &tag);
			teachPointName[j] = '\0';
		}

		if ((ptrPath = m_pDoc->YoPathHashLookup(teachPointName)) != NULL)
		{
			if (tag < 0)
			{
				tag = 1;
			}

			for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL
				&& ptrTag->m_tag != (UINT)tag; ptrTag = ptrTag->m_nextTag);

			if (ptrTag == NULL)
			{
				ptrTag = new CStageTag(m_pDoc);
				ptrTag->m_tag = tag;
				ptrTag->m_ptrPath = ptrPath;
				ptrPath->YoInsertTag(ptrTag);
			}
		}
		else 
		{
			ptrPath = new CStagePath(m_pDoc);
			ptrPath->YoInitPath(m_ptrPart);

			sprintf(ptrPath->m_name, "%s", teachPointName);
			m_pDoc->YoPathHashInstall(ptrPath);

			ptrTag = new CStageTag(m_pDoc);
			ptrTag->m_tag = 1;
			ptrTag->m_ptrPath = ptrPath;
			ptrPath->YoInsertTag(ptrTag);
		}

		m_pDoc->m_currentTag = ptrTag;

		if (i == 1)  // sscanf returns 1 so snap tag to TCF
		{
			m_pDoc->m_currentDevice = this;
			m_pDoc->m_currentPart = m_ptrPart;
			YoTagOnTcf();
		}
		else
		{
			m_pDoc->m_currentDevice = this;
			m_pDoc->m_currentPart = m_ptrPart;
			m_pDoc->YoModelMatrixOfCurrentPart(mRobot);

			m_pDoc->m_currentPart = m_pDoc->m_currentTag->m_ptrPath->m_ptrPart;
			m_pDoc->m_currentDevice = m_pDoc->YoDeviceHashLookup(m_pDoc->m_currentPart->m_deviceName);
			m_pDoc->YoModelMatrixOfCurrentPart(mTag);

			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadMatrixd(mRobot);
			::glTranslated(m[0], m[1], m[2]);
			::glRotated(m[3], 0.0, 0.0, 1.0);
			::glRotated(m[4], 0.0, 1.0, 0.0);
			::glRotated(m[5], 1.0, 0.0, 0.0);

			::glGetDoublev(GL_MODELVIEW_MATRIX, mRobot);

			m_pDoc->YoMatrixInverse(mTag, mTagInv);
			::glLoadMatrixd(mTagInv);
			::glMultMatrixd(mRobot);
			::glGetDoublev(GL_MODELVIEW_MATRIX, mRobot);


			m_pDoc->YoTranslateRotateValues(mRobot, m_pDoc->m_currentTag->m_translate,
				m_pDoc->m_currentTag->m_rotate);
			for (j = 0; j < 3; j++)
			{
				m_pDoc->m_currentTag->m_rotate[j] *= YO_RADIANS_TO_DEGREES;
			}
			::glPopMatrix();
		}

		if (m_pDoc->m_isMovement == FALSE
			&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
			&& m_pDoc->m_scriptFastForward == FALSE)
		{
			((CStageView *)pView)->YoRender(YO_RENDER_FULL);
		}

		sprintf(buf, "| %s TEACHPOINT %s%d", m_name, teachPointName, ptrTag->m_tag);
	}

	else if (strcmp(command, "TIMELEFT") == 0)
	{
		if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
		{
			timeElapsed = m_pDoc->m_timeCurrent - m_timeStart;	
		}
		else
		{
			timeCurrent = m_pDoc->m_gmTime;
			timeStart = m_gmTimeStart;
			spanSec = timeCurrent - timeStart;
			tms = m_pDoc->m_gmTime.wMilliseconds - m_gmTimeStart.wMilliseconds;
			timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
		}

		if (timeElapsed >= m_timeOfMove || m_moving == FALSE)
		{
			sprintf(buf, "| %s TIMELEFT 0.000", m_name);
		}
		else
		{
			sprintf(buf, "| %s TIMELEFT %.3lf", m_name, m_timeOfMove - timeElapsed);
		}
	}

	else if (strcmp(command, "GETSPEED") == 0)
	{
		sprintf(buf, "| %s GETSPEED %d", m_name, m_speed);
	}

	else if (strcmp(command, "GETCONFIG") == 0)
	{
		if (m_lefty == TRUE)
		{
			righty = FALSE;
		}
		else
		{
			righty = TRUE;
		}
		if (m_elbowUp == TRUE)
		{
			below = FALSE;
		}
		else
		{
			below = TRUE;
		}
		if (m_wristFlipped == TRUE)
		{
			flip = TRUE;
		}
		else
		{
			flip = FALSE;
		}
		sprintf(buf, "| %s GETCONFIG %d %d %d", m_name, righty, below, flip);
	}

	else if (strcmp(command, "GETJOINTS") == 0)
	{
		sprintf(buf, "| %s GETJOINTS %lf %lf %lf %lf %lf %lf",
			m_name, m_j[1], m_j[2], m_j[3] - 180.0, m_j[4], m_j[5], m_j[6]);
	}

	else if (strcmp(command, "ABOVE") == 0 && m_moving == FALSE)
	{
		m_elbowUp = TRUE;
		sprintf(buf, "| %s ABOVE", m_name);
	}

	else if (strcmp(command, "BELOW") == 0 && m_moving == FALSE)
	{
		m_elbowUp = FALSE;
		sprintf(buf, "| %s BELOW", m_name);
	}

	else if (strcmp(command, "LEFTY") == 0 && m_moving == FALSE)
	{
		m_lefty = TRUE;
		sprintf(buf, "| %s LEFTY", m_name);
	}

	else if (strcmp(command, "RIGHTY") == 0 && m_moving == FALSE)
	{
		m_lefty = FALSE;
		sprintf(buf, "| %s RIGHTY", m_name);
	}

	else if (strcmp(command, "FLIP") == 0 && m_moving == FALSE)
	{
		m_wristFlipped = TRUE;
		sprintf(buf, "| %s FLIP", m_name);
	}

	else if (strcmp(command, "NOFLIP") == 0 && m_moving == FALSE)
	{
		m_wristFlipped = FALSE;
		sprintf(buf, "| %s NOFLIP", m_name);
	}


	else
	{
		sprintf(buf, "X");
	}


	return TRUE;
}

BOOL CStageRobot6::YoRotateJoint(CStagePart *ptrPart)
// transforms current modelView matrix to reflect robot joint rotation of ptrPart
// make certain that glMatrixMode has been set to GL_MODELVIEW before calling this routine
{
	int i;
	CStagePart *curPart;

	// rotate around z axis
	curPart = m_ptrPart;
	for (i = 0; i <= 6 && curPart != NULL && curPart != ptrPart; i++)
	{
		curPart = curPart->m_down;
	}
	if (curPart != NULL && i != 0)
	{
		::glRotated(m_j[i], 0.0, 0.0, 1.0);
		return TRUE;
	}

	return FALSE;
}


BOOL CStageRobot6::YoReadRobot6(FILE *fp, CStageRobot6 *ptrRobot6)

{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	CStageDevice		*ptrParent;
  
	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "ROBOT6_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrRobot6, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "ROBOT6_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrRobot6->m_name);
		}
 		else if (strcmp(command, "ROBOT6_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrRobot6->m_parent, &partAttachName);
			if (strcmp(ptrRobot6->m_parent, "NONE") != 0)
			{
				ptrParent = m_pDoc->YoDeviceHashLookup(ptrRobot6->m_parent);
				ptrPart = m_pDoc->YoPartLookup(ptrParent, partAttachName);
			}
		}
		else if (strcmp(command, "ROBOT6_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrRobot6->m_visible);
		}
		else if (strcmp(command, "ROBOT6_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrRobot6->m_mass);
		}
		else if (strcmp(command, "ROBOT6_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrRobot6->m_barCode);
		}
		else if (strcmp(command, "ROBOT6_MIN_ACCEL_TIME") == 0)
		{
			sscanf(s, "%*s %lf", &ptrRobot6->m_minAccelTime);
		}
		else if (strcmp(command, "ROBOT6_HOME") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf",
				&ptrRobot6->m_home[1], &ptrRobot6->m_home[2], &ptrRobot6->m_home[3],
				&ptrRobot6->m_home[4], &ptrRobot6->m_home[5], &ptrRobot6->m_home[6]);
		}
		else if (strcmp(command, "ROBOT6_JOINT_VALUES") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf",
				&ptrRobot6->m_j[1], &ptrRobot6->m_j[2], &ptrRobot6->m_j[3],
				&ptrRobot6->m_j[4], &ptrRobot6->m_j[5], &ptrRobot6->m_j[6]);
		}
		else if (strcmp(command, "ROBOT6_MAX_ACCEL") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf",
				&ptrRobot6->m_jMaxAccelMaxSpeed[1][0], &ptrRobot6->m_jMaxAccelMaxSpeed[2][0],
				&ptrRobot6->m_jMaxAccelMaxSpeed[3][0], &ptrRobot6->m_jMaxAccelMaxSpeed[4][0],
				&ptrRobot6->m_jMaxAccelMaxSpeed[5][0], &ptrRobot6->m_jMaxAccelMaxSpeed[6][0]);
		}
		else if (strcmp(command, "ROBOT6_MAX_SPEED") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf",
				&ptrRobot6->m_jMaxAccelMaxSpeed[1][1], &ptrRobot6->m_jMaxAccelMaxSpeed[2][1],
				&ptrRobot6->m_jMaxAccelMaxSpeed[3][1], &ptrRobot6->m_jMaxAccelMaxSpeed[4][1],
				&ptrRobot6->m_jMaxAccelMaxSpeed[5][1], &ptrRobot6->m_jMaxAccelMaxSpeed[6][1]);
		}
		else if (strcmp(command, "ROBOT6_MIN_ACCEL_TIME") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf",
				&ptrRobot6->m_jMinAccelTime[1], &ptrRobot6->m_jMinAccelTime[2],
				&ptrRobot6->m_jMinAccelTime[3], &ptrRobot6->m_jMinAccelTime[4],
				&ptrRobot6->m_jMinAccelTime[5], &ptrRobot6->m_jMinAccelTime[6]);
		}
		else if (strcmp(command, "ROBOT6_MIN_JOINT_VALUES") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf",
				&ptrRobot6->m_jMinMax[1][0], &ptrRobot6->m_jMinMax[2][0],
				&ptrRobot6->m_jMinMax[3][0], &ptrRobot6->m_jMinMax[4][0],
				&ptrRobot6->m_jMinMax[5][0], &ptrRobot6->m_jMinMax[6][0]);
		}
		else if (strcmp(command, "ROBOT6_MAX_JOINT_VALUES") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf",
				&ptrRobot6->m_jMinMax[1][1], &ptrRobot6->m_jMinMax[2][1],
				&ptrRobot6->m_jMinMax[3][1], &ptrRobot6->m_jMinMax[4][1],
				&ptrRobot6->m_jMinMax[5][1], &ptrRobot6->m_jMinMax[6][1]);
		}
		else if (strcmp(command, "ROBOT6_JOINT_INTERPOLATION") == 0)
		{
			sscanf(s, "%*s %d", &ptrRobot6->m_jointInterpolation);
		}
		else if (strcmp(command, "ROBOT6_MAX_SCREW_SPEED") == 0)
		{
			sscanf(s, "%*s %lf", &ptrRobot6->m_maxScrewSpeed);
		}
		else if (strcmp(command, "ROBOT6_MAX_SCREW_ACCEL") == 0)
		{
			sscanf(s, "%*s %lf", &ptrRobot6->m_maxScrewAccel);
		}
		else if (strcmp(command, "ROBOT6_MAX_TOOL_SPEED") == 0)
		{
			sscanf(s, "%*s %lf", &ptrRobot6->m_maxToolSpeed);
		}
		else if (strcmp(command, "ROBOT6_MAX_TOOL_ACCEL") == 0)
		{
			sscanf(s, "%*s %lf", &ptrRobot6->m_maxToolAccel);
		}
		else if (strcmp(command, "ROBOT6_SPEED") == 0)
		{
			sscanf(s, "%*s %d", &ptrRobot6->m_speed);
		}
		else if (strcmp(command, "ROBOT6_TCP_OFFSET") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf %lf %lf %lf",
				&ptrRobot6->m_tcpOffset[0], &ptrRobot6->m_tcpOffset[1], &ptrRobot6->m_tcpOffset[2],
				&ptrRobot6->m_tcpOffset[3], &ptrRobot6->m_tcpOffset[4], &ptrRobot6->m_tcpOffset[5]);
		}
		else
		{
			return FALSE;
		}		

	} // end while (done == FALSE)
	return TRUE;
}


BOOL CStageRobot6::YoInverseKinematics(GLdouble m[16], GLdouble j[7][4])
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CStagePart *ptrPart;
	GLdouble px;
	GLdouble py;
	GLdouble pz;
	GLdouble theta[7][4];
	GLdouble theta23[4];
	GLdouble mc4s5[4];
	GLdouble s4s5[4];
	GLdouble s5[4];
	GLdouble c5[4];
	GLdouble s6[4];
	GLdouble c6[4];
	GLdouble K;
	int i;
	GLdouble z = 0.01;
	GLdouble a2;
	GLdouble d3;
	GLdouble a3;
	GLdouble d4;
	BOOL validMove = FALSE;

	px = m[12];
	py = m[13];
	pz = m[14];

	// use DH parameters alpha(Rx), a(Tx), and d(Tz)
	// kinematics for staubli Rx series
	ptrPart = this->m_ptrPart;
	for (i = 1; i <= 6; i++)
	{
		ptrPart = ptrPart->m_down;
		/***
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();
		::glRotated(ptrPart->m_rotate[0], 1.0, 0.0, 0.0);
		::glTranslated(ptrPart->m_translate[0], ptrPart->m_translate[1],
			ptrPart->m_translate[2]);
		::glGetDoublev(GL_MODELVIEW_MATRIX, t[i]);
		::glPopMatrix();
		***/
		if (i == 3)
		{
			a2 = ptrPart->m_translate[0];
			d3 = ptrPart->m_translate[2];
		}
		else if (i == 4)
		{
			a3 = ptrPart->m_translate[0];
			d4 = ptrPart->m_translate[2];// - 110.0;
		}
	}

	/***
	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glLoadIdentity();
	::glMultMatrixd(t[1]);
	::glMultMatrixd(t[2]);
	::glMultMatrixd(t[3]);
	::glGetDoublev(GL_MODELVIEW_MATRIX, t03);
	::glMultMatrixd(t[4]);
	::glGetDoublev(GL_MODELVIEW_MATRIX, t04);
	::glPopMatrix;

	m_pDoc->YoMatrixInverse(t03, t03Inv);
	m_pDoc->YoMatrixInverse(t04, t04Inv);
	***/


	// calculate joint 1
	theta[1][0] = atan2(py, px) - atan2(d3, sqrt(px * px + py * py - d3 * d3));
	theta[1][1] = atan2(py, px) - atan2(d3, -sqrt(px * px + py * py - d3 * d3));

	for (i = 0; i < 2; i++)
	{
		if (theta[1][i] > m_jMinMax[1][1] * YO_DEGREES_TO_RADIANS)
		{
			theta[1][i] = (-2.0 * YO_PI) + theta[1][i];
		}
		else if (theta[1][i] < m_jMinMax[1][0] * YO_DEGREES_TO_RADIANS)
		{
			theta[1][i] = (2.0 * YO_PI) + theta[1][i];
		}
	}

	// calculate joint 3
	K = (px * px + py * py + pz * pz
		- a2 * a2 - a3 * a3
		- d3 * d3 - d4 * d4)
		/ (2.0 * a2);
	theta[3][0] = atan2(a3, d4)
		- atan2(K, sqrt(a3 * a3 + d4 * d4 - K * K));
	theta[3][1] = atan2(a3, d4)
		- atan2(K, -(sqrt(a3 * a3 + d4 * d4 - K * K)));

	for (i = 0; i < 2; i++)
	{
		if (theta[3][i] > m_jMinMax[3][1] * YO_DEGREES_TO_RADIANS)
		{
			theta[3][i] = (-2.0 * YO_PI) + theta[3][i];
		}
		else if (theta[3][i] < m_jMinMax[3][0] * YO_DEGREES_TO_RADIANS)
		{
			theta[3][i] = (2.0 * YO_PI) + theta[3][i];
		}
	}

	// calculate joint 2
	theta23[0] = atan2((-a3 - a2 * cos(theta[3][0])) * pz
		- (cos(theta[1][0]) * px + sin(theta[1][0]) * py)
		* (d4 - a2 * sin(theta[3][0])),
		(a2 * sin(theta[3][0]) - d4) * pz
		+ (a3 + a2 * cos(theta[3][0]))
		* (cos(theta[1][0]) * px + sin(theta[1][0]) * py));
	theta23[1] = atan2((-a3 - a2 * cos(theta[3][0])) * pz
		- (cos(theta[1][1]) * px + sin(theta[1][1]) * py)
		* (d4 - a2 * sin(theta[3][0])),
		(a2 * sin(theta[3][0]) - d4) * pz
		+ (a3 + a2 * cos(theta[3][0]))
		* (cos(theta[1][1]) * px + sin(theta[1][1]) * py));
	theta23[2] = atan2((-a3 - a2 * cos(theta[3][1])) * pz
		- (cos(theta[1][0]) * px + sin(theta[1][0]) * py)
		* (d4 - a2 * sin(theta[3][1])),
		(a2 * sin(theta[3][1]) - d4) * pz
		+ (a3 + a2 * cos(theta[3][1]))
		* (cos(theta[1][0]) * px + sin(theta[1][0]) * py));
	theta23[3] = atan2((-a3 - a2 * cos(theta[3][1])) * pz
		- (cos(theta[1][1]) * px + sin(theta[1][1]) * py)
		* (d4 - a2 * sin(theta[3][1])),
		(a2 * sin(theta[3][1]) - d4) * pz
		+ (a3 + a2 * cos(theta[3][1]))
		* (cos(theta[1][1]) * px + sin(theta[1][1]) * py));

	theta[2][0] = theta23[0] - theta[3][0];
	theta[2][1] = theta23[1] - theta[3][0];
	theta[2][2] = theta23[2] - theta[3][1];
	theta[2][3] = theta23[3] - theta[3][1];

	for (i = 0; i < 4; i++)
	{
		if (theta[2][i] > m_jMinMax[2][1] * YO_DEGREES_TO_RADIANS)
		{
			theta[2][i] = (-2.0 * YO_PI) + theta[2][i];
		}
		else if (theta[2][i] < m_jMinMax[2][0] * YO_DEGREES_TO_RADIANS)
		{
			theta[2][i] = (2.0 * YO_PI) + theta[2][i];
		}
	}

	// calculate joint 4

	mc4s5[0] = m[8] * cos(theta[1][0]) * cos(theta23[0])
		+ m[9] * sin(theta[1][0]) * cos(theta23[0])
		- m[10] * sin(theta23[0]);
	s4s5[0] = -m[8] * sin(theta[1][0]) + m[9] * cos(theta[1][0]);
	mc4s5[1] = m[8] * cos(theta[1][0]) * cos(theta23[2])
		+ m[9] * sin(theta[1][0]) * cos(theta23[2])
		- m[10] * sin(theta23[2]);
	s4s5[1] = -m[8] * sin(theta[1][0]) + m[9] * cos(theta[1][0]);
	mc4s5[2] = m[8] * cos(theta[1][1]) * cos(theta23[1])
		+ m[9] * sin(theta[1][1]) * cos(theta23[1])
		- m[10] * sin(theta23[1]);
	s4s5[2] = -m[8] * sin(theta[1][1]) + m[9] * cos(theta[1][1]);	
	mc4s5[3] = m[8] * cos(theta[1][1]) * cos(theta23[3])
		+ m[9] * sin(theta[1][1]) * cos(theta23[3])
		- m[10] * sin(theta23[3]);
	s4s5[3] = -m[8] * sin(theta[1][1]) + m[9] * cos(theta[1][1]);

	/***
	mc4s5[0] = m[8] * cos(theta[1][0]) * cos(theta23[0])
		+ m[9] * sin(theta[1][0]) * cos(theta23[0])
		- m[10] * sin(theta23[0]);
	s4s5[0] = -m[8] * sin(theta[1][0]) + m[9] * cos(theta[1][0]);
	mc4s5[1] = m[8] * cos(theta[1][0]) * cos(theta23[1])
		+ m[9] * sin(theta[1][0]) * cos(theta23[1])
		- m[10] * sin(theta23[1]);
	s4s5[1] = -m[8] * sin(theta[1][0]) + m[9] * cos(theta[1][0]);
	mc4s5[2] = m[8] * cos(theta[1][1]) * cos(theta23[2])
		+ m[9] * sin(theta[1][1]) * cos(theta23[2])
		- m[10] * sin(theta23[2]);
	s4s5[2] = -m[8] * sin(theta[1][1]) + m[9] * cos(theta[1][1]);	
	mc4s5[3] = m[8] * cos(theta[1][1]) * cos(theta23[3])
		+ m[9] * sin(theta[1][1]) * cos(theta23[3])
		- m[10] * sin(theta23[3]);
	s4s5[3] = -m[8] * sin(theta[1][1]) + m[9] * cos(theta[1][1]);
***/

	for (i = 0; i < 4; i++)
	{
		if (-mc4s5[i] < z && -mc4s5[i] > -z && s4s5[i] < z && s4s5[i] > -z)
		{
			theta[4][i] = m_j[4] * YO_DEGREES_TO_RADIANS;
			TRACE0("theta4 (singular)\n");
		}
		else
		{
			theta[4][i] = atan2(s4s5[i], -mc4s5[i]);
		}
	}

	for (i = 0; i < 4; i++)
	{
		if (theta[4][i] > m_jMinMax[4][1] * YO_DEGREES_TO_RADIANS)
		{
			theta[4][i] = (-2.0 * YO_PI) + theta[4][i];
		}
		else if (theta[4][i] < m_jMinMax[4][0] * YO_DEGREES_TO_RADIANS)
		{
			theta[4][i] = (2.0 * YO_PI) + theta[4][i];
		}
	}

	// calculate joint 5

	s5[0] = -(m[8] * (cos(theta[1][0]) * cos(theta23[0]) * cos(theta[4][0])
		+ sin(theta[1][0]) * sin(theta[4][0]))
		+ m[9] * (sin(theta[1][0]) * cos(theta23[0]) * cos(theta[4][0])
		- cos(theta[1][0]) * sin(theta[4][0]))
		- m[10] * (sin(theta23[0]) * cos(theta[4][0])));
	c5[0] = m[8] * (-cos(theta[1][0]) * sin(theta23[0]))
		+ m[9] * (-sin(theta[1][0]) * sin(theta23[0]))
		+ m[10] * (-cos(theta23[0]));
	s5[1] = -(m[8] * (cos(theta[1][0]) * cos(theta23[2]) * cos(theta[4][1])
		+ sin(theta[1][0]) * sin(theta[4][1]))
		+ m[9] * (sin(theta[1][0]) * cos(theta23[2]) * cos(theta[4][1])
		- cos(theta[1][0]) * sin(theta[4][1]))
		- m[10] * (sin(theta23[2]) * cos(theta[4][1])));
	c5[1] = m[8] * (-cos(theta[1][0]) * sin(theta23[2]))
		+ m[9] * (-sin(theta[1][0]) * sin(theta23[2]))
		+ m[10] * (-cos(theta23[2]));
	s5[2] = -(m[8] * (cos(theta[1][1]) * cos(theta23[1]) * cos(theta[4][2])
		+ sin(theta[1][1]) * sin(theta[4][2]))
		+ m[9] * (sin(theta[1][1]) * cos(theta23[1]) * cos(theta[4][2])
		- cos(theta[1][1]) * sin(theta[4][2]))
		- m[10] * (sin(theta23[1]) * cos(theta[4][2])));
	c5[2] = m[8] * (-cos(theta[1][1]) * sin(theta23[1]))
		+ m[9] * (-sin(theta[1][1]) * sin(theta23[1]))
		+ m[10] * (-cos(theta23[1]));
	s5[3] = -(m[8] * (cos(theta[1][1]) * cos(theta23[3]) * cos(theta[4][3])
		+ sin(theta[1][1]) * sin(theta[4][3]))
		+ m[9] * (sin(theta[1][1]) * cos(theta23[3]) * cos(theta[4][3])
		- cos(theta[1][1]) * sin(theta[4][3]))
		- m[10] * (sin(theta23[3]) * cos(theta[4][3])));
	c5[3] = m[8] * (-cos(theta[1][1]) * sin(theta23[3]))
		+ m[9] * (-sin(theta[1][1]) * sin(theta23[3]))
		+ m[10] * (-cos(theta23[3]));

/***
	// changed minus sign on sin 1 & 2 ?? Works but why ??
	s5[0] = -(m[8] * (cos(theta[1][0]) * cos(theta23[0]) * cos(theta[4][0])
		+ sin(theta[1][0]) * sin(theta[4][0]))
		+ m[9] * (sin(theta[1][0]) * cos(theta23[0]) * cos(theta[4][0])
		- cos(theta[1][0]) * sin(theta[4][0]))
		- m[10] * (sin(theta23[0]) * cos(theta[4][0])));
	c5[0] = m[8] * (-cos(theta[1][0]) * sin(theta23[0]))
		+ m[9] * (-sin(theta[1][0]) * sin(theta23[0]))
		+ m[10] * (-cos(theta23[0]));
	s5[1] = (m[8] * (cos(theta[1][0]) * cos(theta23[2]) * cos(theta[4][1])
		+ sin(theta[1][0]) * sin(theta[4][1]))
		+ m[9] * (sin(theta[1][0]) * cos(theta23[2]) * cos(theta[4][1])
		- cos(theta[1][0]) * sin(theta[4][1]))
		- m[10] * (sin(theta23[2]) * cos(theta[4][1])));
	c5[1] = m[8] * (-cos(theta[1][0]) * sin(theta23[2]))
		+ m[9] * (-sin(theta[1][0]) * sin(theta23[2]))
		+ m[10] * (-cos(theta23[2]));
	s5[2] = (m[8] * (cos(theta[1][1]) * cos(theta23[1]) * cos(theta[4][2])
		+ sin(theta[1][1]) * sin(theta[4][2]))
		+ m[9] * (sin(theta[1][1]) * cos(theta23[1]) * cos(theta[4][2])
		- cos(theta[1][1]) * sin(theta[4][2]))
		- m[10] * (sin(theta23[1]) * cos(theta[4][2])));
	c5[2] = m[8] * (-cos(theta[1][1]) * sin(theta23[1]))
		+ m[9] * (-sin(theta[1][1]) * sin(theta23[1]))
		+ m[10] * (-cos(theta23[1]));
	s5[3] = -(m[8] * (cos(theta[1][1]) * cos(theta23[3]) * cos(theta[4][3])
		+ sin(theta[1][1]) * sin(theta[4][3]))
		+ m[9] * (sin(theta[1][1]) * cos(theta23[3]) * cos(theta[4][3])
		- cos(theta[1][1]) * sin(theta[4][3]))
		- m[10] * (sin(theta23[3]) * cos(theta[4][3])));
	c5[3] = m[8] * (-cos(theta[1][1]) * sin(theta23[3]))
		+ m[9] * (-sin(theta[1][1]) * sin(theta23[3]))
		+ m[10] * (-cos(theta23[3]));
***/

	for (i = 0; i < 4; i++)
	{
		theta[5][i] = atan2(s5[i], c5[i]);
	}

	for (i = 0; i < 4; i++)
	{
		if (theta[5][i] > m_jMinMax[5][1] * YO_DEGREES_TO_RADIANS)
		{
			theta[5][i] = (-2.0 * YO_PI) + theta[5][i];
		}
		else if (theta[5][i] < m_jMinMax[5][0] * YO_DEGREES_TO_RADIANS)
		{
			theta[5][i] = (2.0 * YO_PI) + theta[5][i];
		}
	}

	/**
	ptrPart = this->m_ptrPart->m_down;
	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glLoadIdentity();
	::glRotated(theta[1][0] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glRotated(ptrPart->m_rotate[0], 1.0, 0.0, 0.0);
	::glRotated(theta[2][0] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glTranslated(a2, 0.0, d3);
	::glRotated(theta[3][0] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glRotated(ptrPart->m_rotate[0], 1.0, 0.0, 0.0);
	::glTranslated(a3, 0.0, d4);
	::glRotated(theta[4][0] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	::glGetDoublev(GL_MODELVIEW_MATRIX, t04);
	m_pDoc->YoMatrixInverse(t04, t04Inv);
	theta[5][0] = atan2(-(m[8] * t04Inv[0] + m[9] * t04Inv[5] + m[10] * t04Inv[9]),
		(m[8] * t04Inv[2] + m[9] * t04Inv[6] + m[10] * t04Inv[10]));

	ptrPart = this->m_ptrPart->m_down;
	::glLoadIdentity();
	::glRotated(theta[1][1] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glRotated(ptrPart->m_rotate[0], 1.0, 0.0, 0.0);
	::glRotated(theta[2][1] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glTranslated(a2, 0.0, d3);
	::glRotated(theta[3][0] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glRotated(ptrPart->m_rotate[0], 1.0, 0.0, 0.0);
	::glTranslated(a3, 0.0, d4);
	::glRotated(theta[4][1] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	::glGetDoublev(GL_MODELVIEW_MATRIX, t04);
	m_pDoc->YoMatrixInverse(t04, t04Inv);
	theta[5][1] = atan2(-(m[8] * t04Inv[0] + m[9] * t04Inv[5] + m[10] * t04Inv[9]),
		(m[8] * t04Inv[2] + m[9] * t04Inv[6] + m[10] * t04Inv[10]));

	ptrPart = this->m_ptrPart->m_down;
	::glLoadIdentity();
	::glRotated(theta[1][0] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glRotated(ptrPart->m_rotate[0], 1.0, 0.0, 0.0);
	::glRotated(theta[2][2] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glTranslated(a2, 0.0, d3);
	::glRotated(theta[3][1] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glRotated(ptrPart->m_rotate[0], 1.0, 0.0, 0.0);
	::glTranslated(a3, 0.0, d4);
	::glRotated(theta[4][2] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	::glGetDoublev(GL_MODELVIEW_MATRIX, t04);
	m_pDoc->YoMatrixInverse(t04, t04Inv);
	theta[5][2] = atan2(-(m[8] * t04Inv[0] + m[9] * t04Inv[5] + m[10] * t04Inv[9]),
		(m[8] * t04Inv[2] + m[9] * t04Inv[6] + m[10] * t04Inv[10]));

	ptrPart = this->m_ptrPart->m_down;
	::glLoadIdentity();
	::glRotated(theta[1][1] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glRotated(ptrPart->m_rotate[0], 1.0, 0.0, 0.0);
	::glRotated(theta[2][3] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glTranslated(a2, 0.0, d3);
	::glRotated(theta[3][1] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	ptrPart = ptrPart->m_down;
	::glRotated(ptrPart->m_rotate[0], 1.0, 0.0, 0.0);
	::glTranslated(a3, 0.0, d4);
	::glRotated(theta[4][3] * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
	::glGetDoublev(GL_MODELVIEW_MATRIX, t04);
	m_pDoc->YoMatrixInverse(t04, t04Inv);
	theta[5][3] = atan2(-(m[8] * t04Inv[0] + m[9] * t04Inv[5] + m[10] * t04Inv[9]),
		(m[8] * t04Inv[2] + m[9] * t04Inv[6] + m[10] * t04Inv[10]));
	::glPopMatrix();
	**/

	// compute joint 6
	// changed minus sign on sin 1 & 2 ?? Works but why ??
/***
	s6[0] = -m[0] * (cos(theta[1][0]) * cos(theta23[0]) * sin(theta[4][0])
		- sin(theta[1][0]) * cos(theta[4][0]))
		- m[1] * (sin(theta[1][0]) * cos(theta23[0]) * sin(theta[4][0])
		+ cos(theta[1][0]) * cos(theta[4][0]))
		+ m[2] * (sin(theta23[0]) * sin(theta[4][0]));
	c6[0] = m[0] * ((cos(theta[1][0]) * cos(theta23[0]) * cos(theta[4][0])
		+ sin(theta[1][0]) * sin(theta[4][0])) * cos(theta[5][0])
		- cos(theta[1][0]) * sin(theta23[0]) * sin(theta[5][0]))
		+ m[1] * ((sin(theta[1][0]) * cos(theta23[0]) * cos(theta[4][0])
		- cos(theta[1][0]) * sin(theta[4][0])) * cos(theta[5][0])
		- sin(theta[1][0]) * sin(theta23[0]) * sin(theta[5][0]))
		- m[2] * (sin(theta23[0]) * cos(theta[4][0]) * cos(theta[5][0])
		+ cos(theta23[0]) * sin(theta[5][0]));
	s6[1] = m[0] * (cos(theta[1][0]) * cos(theta23[2]) * sin(theta[4][1])
		- sin(theta[1][0]) * cos(theta[4][1]))
		- m[1] * (sin(theta[1][0]) * cos(theta23[2]) * sin(theta[4][1])
		+ cos(theta[1][0]) * cos(theta[4][1]))
		+ m[2] * (sin(theta23[2]) * sin(theta[4][1]));
	c6[1] = m[0] * ((cos(theta[1][0]) * cos(theta23[2]) * cos(theta[4][1])
		+ sin(theta[1][0]) * sin(theta[4][1])) * cos(theta[5][1])
		- cos(theta[1][0]) * sin(theta23[2]) * sin(theta[5][1]))
		+ m[1] * ((sin(theta[1][0]) * cos(theta23[2]) * cos(theta[4][1])
		- cos(theta[1][0]) * sin(theta[4][1])) * cos(theta[5][1])
		- sin(theta[1][0]) * sin(theta23[2]) * sin(theta[5][1]))
		- m[2] * (sin(theta23[2]) * cos(theta[4][1]) * cos(theta[5][1])
		+ cos(theta23[2]) * sin(theta[5][1]));
	s6[2] = m[0] * (cos(theta[1][1]) * cos(theta23[1]) * sin(theta[4][2])
		- sin(theta[1][1]) * cos(theta[4][2]))
		- m[1] * (sin(theta[1][1]) * cos(theta23[1]) * sin(theta[4][2])
		+ cos(theta[1][1]) * cos(theta[4][2]))
		+ m[2] * (sin(theta23[1]) * sin(theta[4][2]));
	c6[2] = m[0] * ((cos(theta[1][1]) * cos(theta23[1]) * cos(theta[4][2])
		+ sin(theta[1][1]) * sin(theta[4][2])) * cos(theta[5][2])
		- cos(theta[1][1]) * sin(theta23[1]) * sin(theta[5][2]))
		+ m[1] * ((sin(theta[1][1]) * cos(theta23[1]) * cos(theta[4][2])
		- cos(theta[1][1]) * sin(theta[4][2])) * cos(theta[5][2])
		- sin(theta[1][1]) * sin(theta23[1]) * sin(theta[5][2]))
		- m[2] * (sin(theta23[1]) * cos(theta[4][2]) * cos(theta[5][2])
		+ cos(theta23[1]) * sin(theta[5][2]));	
	s6[3] = -m[0] * (cos(theta[1][1]) * cos(theta23[3]) * sin(theta[4][3])
		- sin(theta[1][1]) * cos(theta[4][3]))
		- m[1] * (sin(theta[1][1]) * cos(theta23[3]) * sin(theta[4][3])
		+ cos(theta[1][1]) * cos(theta[4][3]))
		+ m[2] * (sin(theta23[3]) * sin(theta[4][3]));
	c6[3] = m[0] * ((cos(theta[1][1]) * cos(theta23[3]) * cos(theta[4][3])
		+ sin(theta[1][1]) * sin(theta[4][3])) * cos(theta[5][3])
		- cos(theta[1][1]) * sin(theta23[3]) * sin(theta[5][3]))
		+ m[1] * ((sin(theta[1][1]) * cos(theta23[3]) * cos(theta[4][3])
		- cos(theta[1][1]) * sin(theta[4][3])) * cos(theta[5][3])
		- sin(theta[1][1]) * sin(theta23[3]) * sin(theta[5][3]))
		- m[2] * (sin(theta23[3]) * cos(theta[4][3]) * cos(theta[5][3])
		+ cos(theta23[3]) * sin(theta[5][3]));	
***/

	s6[0] = -m[0] * (cos(theta[1][0]) * cos(theta23[0]) * sin(theta[4][0])
		- sin(theta[1][0]) * cos(theta[4][0]))
		- m[1] * (sin(theta[1][0]) * cos(theta23[0]) * sin(theta[4][0])
		+ cos(theta[1][0]) * cos(theta[4][0]))
		+ m[2] * (sin(theta23[0]) * sin(theta[4][0]));
	c6[0] = m[0] * ((cos(theta[1][0]) * cos(theta23[0]) * cos(theta[4][0])
		+ sin(theta[1][0]) * sin(theta[4][0])) * cos(theta[5][0])
		- cos(theta[1][0]) * sin(theta23[0]) * sin(theta[5][0]))
		+ m[1] * ((sin(theta[1][0]) * cos(theta23[0]) * cos(theta[4][0])
		- cos(theta[1][0]) * sin(theta[4][0])) * cos(theta[5][0])
		- sin(theta[1][0]) * sin(theta23[0]) * sin(theta[5][0]))
		- m[2] * (sin(theta23[0]) * cos(theta[4][0]) * cos(theta[5][0])
		+ cos(theta23[0]) * sin(theta[5][0]));
	s6[1] = -m[0] * (cos(theta[1][0]) * cos(theta23[2]) * sin(theta[4][1])
		- sin(theta[1][0]) * cos(theta[4][1]))
		- m[1] * (sin(theta[1][0]) * cos(theta23[2]) * sin(theta[4][1])
		+ cos(theta[1][0]) * cos(theta[4][1]))
		+ m[2] * (sin(theta23[2]) * sin(theta[4][1]));
	c6[1] = m[0] * ((cos(theta[1][0]) * cos(theta23[2]) * cos(theta[4][1])
		+ sin(theta[1][0]) * sin(theta[4][1])) * cos(theta[5][1])
		- cos(theta[1][0]) * sin(theta23[2]) * sin(theta[5][1]))
		+ m[1] * ((sin(theta[1][0]) * cos(theta23[2]) * cos(theta[4][1])
		- cos(theta[1][0]) * sin(theta[4][1])) * cos(theta[5][1])
		- sin(theta[1][0]) * sin(theta23[2]) * sin(theta[5][1]))
		- m[2] * (sin(theta23[2]) * cos(theta[4][1]) * cos(theta[5][1])
		+ cos(theta23[2]) * sin(theta[5][1]));
	s6[2] = -m[0] * (cos(theta[1][1]) * cos(theta23[1]) * sin(theta[4][2])
		- sin(theta[1][1]) * cos(theta[4][2]))
		- m[1] * (sin(theta[1][1]) * cos(theta23[1]) * sin(theta[4][2])
		+ cos(theta[1][1]) * cos(theta[4][2]))
		+ m[2] * (sin(theta23[1]) * sin(theta[4][2]));
	c6[2] = m[0] * ((cos(theta[1][1]) * cos(theta23[1]) * cos(theta[4][2])
		+ sin(theta[1][1]) * sin(theta[4][2])) * cos(theta[5][2])
		- cos(theta[1][1]) * sin(theta23[1]) * sin(theta[5][2]))
		+ m[1] * ((sin(theta[1][1]) * cos(theta23[1]) * cos(theta[4][2])
		- cos(theta[1][1]) * sin(theta[4][2])) * cos(theta[5][2])
		- sin(theta[1][1]) * sin(theta23[1]) * sin(theta[5][2]))
		- m[2] * (sin(theta23[1]) * cos(theta[4][2]) * cos(theta[5][2])
		+ cos(theta23[1]) * sin(theta[5][2]));	
	s6[3] = -m[0] * (cos(theta[1][1]) * cos(theta23[3]) * sin(theta[4][3])
		- sin(theta[1][1]) * cos(theta[4][3]))
		- m[1] * (sin(theta[1][1]) * cos(theta23[3]) * sin(theta[4][3])
		+ cos(theta[1][1]) * cos(theta[4][3]))
		+ m[2] * (sin(theta23[3]) * sin(theta[4][3]));
	c6[3] = m[0] * ((cos(theta[1][1]) * cos(theta23[3]) * cos(theta[4][3])
		+ sin(theta[1][1]) * sin(theta[4][3])) * cos(theta[5][3])
		- cos(theta[1][1]) * sin(theta23[3]) * sin(theta[5][3]))
		+ m[1] * ((sin(theta[1][1]) * cos(theta23[3]) * cos(theta[4][3])
		- cos(theta[1][1]) * sin(theta[4][3])) * cos(theta[5][3])
		- sin(theta[1][1]) * sin(theta23[3]) * sin(theta[5][3]))
		- m[2] * (sin(theta23[3]) * cos(theta[4][3]) * cos(theta[5][3])
		+ cos(theta23[3]) * sin(theta[5][3]));	

	for (i = 0; i < 4; i++)
	{
		theta[6][i] = atan2(s6[i], c6[i]);
	}

	for (i = 0; i < 4; i++)
	{
		if (theta[6][i] > m_jMinMax[6][1] * YO_DEGREES_TO_RADIANS)
		{
			theta[6][i] = (-2.0 * YO_PI) + theta[6][i];
		}
		else if (theta[6][i] < m_jMinMax[6][0] * YO_DEGREES_TO_RADIANS)
		{
			theta[6][i] = (2.0 * YO_PI) + theta[6][i];
		}
	}


	theta[1][2] = theta[1][0];
	theta[1][3] = theta[1][1];
	theta[3][2] = theta[3][1];
	theta[3][3] = theta[3][1];
	theta[3][1] = theta[3][0];

	/***
	for (i = 0; i < 4; i++)
	{
		m_j[1] = theta[1][i] * YO_RADIANS_TO_DEGREES;
		m_j[2] = theta[2][i] * YO_RADIANS_TO_DEGREES;
		m_j[3] = theta[3][i] * YO_RADIANS_TO_DEGREES;
		m_j[4] = theta[4][i] * YO_RADIANS_TO_DEGREES;
		m_j[5] = theta[5][i] * YO_RADIANS_TO_DEGREES;
		m_j[6] = theta[6][i] * YO_RADIANS_TO_DEGREES;
		pView->YoRender(YO_RENDER_FULL);
		Sleep(3000);
	}
	***/

	/***
	if (m_wristFlipped == TRUE)
	{
		for (i = 0; i < 4; i++)
		{
			theta[4][i] += (180.0 * YO_DEGREES_TO_RADIANS);
			theta[5][i] = -theta[5][i];
			theta[6][i] += (180.0 * YO_DEGREES_TO_RADIANS); 
		}
	}
	***/

	//for (i = 1; i <= 6; i++)
	//{
	//	m_jStart[i] = m_j[i];
	//}

/***
	for (i = 0; i < 4; i++)
	{
		m_jFinal[1] = theta[1][i] * YO_RADIANS_TO_DEGREES;
		m_jFinal[2] = theta[2][i] * YO_RADIANS_TO_DEGREES;
		m_jFinal[3] = theta[3][i] * YO_RADIANS_TO_DEGREES;
		m_jFinal[4] = theta[4][i] * YO_RADIANS_TO_DEGREES;
		m_jFinal[5] = theta[5][i] * YO_RADIANS_TO_DEGREES;
		m_jFinal[6] = theta[6][i] * YO_RADIANS_TO_DEGREES;
		if ((i == 1 || i == 2) && m_jFinal[4] < 0.0)
		{
			m_jFinal[4] += 180.0;
		}
		else if ((i == 1 || i == 2) && m_jFinal[4] > 0.0)
		{
			m_jFinal[4] -= 180.0;
		}
		YoCalculateTimeOfRotation();
		m_moving = TRUE;
		m_pDoc->m_isMovement++;
		m_pDoc->YoMove();
		TRACE1("i = %d\n", i);
		Sleep(3000);
		int j;
		for (j = 1; j <= 6; j++)
		{
			m_jStart[j] = m_jFinal[j];
		}

	}
	***/
	for (i = 0; i < 4; i++)
	{
		j[1][i] = theta[1][i] * YO_RADIANS_TO_DEGREES;
		j[2][i] = theta[2][i] * YO_RADIANS_TO_DEGREES;
		j[3][i] = theta[3][i] * YO_RADIANS_TO_DEGREES;
		j[4][i] = theta[4][i] * YO_RADIANS_TO_DEGREES;
		j[5][i] = theta[5][i] * YO_RADIANS_TO_DEGREES;
		j[6][i] = theta[6][i] * YO_RADIANS_TO_DEGREES;
	}



	return TRUE;
}


BOOL CStageRobot6::YoMoveTo(GLdouble m[16])
// move a robot ptrDevice to a given tag m, relative to the base
// of the robot
{
	GLdouble j[7][4];
	int i;
	BOOL validMove;
	double mBase[16];
	double mTcf[16];
	double mBaseInv[16];
	CStageDevice *ptrDevice;
	CStagePart *ptrPart;

	if (m_moving == TRUE)
	{
		return FALSE;
	}

	YoInverseKinematics(m, j);

	for (i = 0; i < 16; i++)
	{
		m_mFinal[i] = m[i];
	}

	// calculate matrix of start position
	ptrPart = m_pDoc->m_currentPart;
	ptrDevice = m_pDoc->m_currentDevice;

	m_pDoc->m_currentDevice = this;
	m_pDoc->m_currentPart = m_ptrPart;
	m_pDoc->YoModelMatrixOfCurrentPart(mBase);
	for (i = 0; i <= 6 && m_pDoc->m_currentPart != NULL
		&& m_pDoc->m_currentPart->m_down != NULL; i++)
	{
		m_pDoc->m_currentPart = m_pDoc->m_currentPart->m_down;
	}
	m_pDoc->YoModelMatrixOfCurrentPart(mTcf);

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glLoadMatrixd(mTcf);
	//::glTranslated(0.0, 0.0, -m_tcpOffset[2]);
	::glGetDoublev(GL_MODELVIEW_MATRIX, mTcf);

	m_pDoc->YoMatrixInverse(mBase, mBaseInv);
	::glLoadMatrixd(mBaseInv);
	::glMultMatrixd(mTcf);
	::glGetDoublev(GL_MODELVIEW_MATRIX, m_mStart);

	::glPopMatrix();

	m_pDoc->m_currentDevice = ptrDevice;
	m_pDoc->m_currentPart = ptrPart;


	for (i = 1; i <= 6; i++)
	{
		m_jStart[i] = m_j[i];
	}

	for (i = 0; i < 4; i++)
	{
		m_jFinal[1] = j[1][i];
		m_jFinal[2] = j[2][i];
		m_jFinal[3] = j[3][i];
		m_jFinal[4] = j[4][i];
		m_jFinal[5] = j[5][i];
		m_jFinal[6] = j[6][i];

		if ((i == 1 || i == 2) && m_jFinal[4] < 0.0)
		{
			m_jFinal[4] += 180.0;
		}
		else if ((i == 1 || i == 2) && m_jFinal[4] > 0.0)
		{
			m_jFinal[4] -= 180.0;
		}

		if (m_wristFlipped == TRUE)
		{
			if (m_jFinal[4] <= 0.0)
			{
				m_jFinal[4] += 180.0;
			}
			else if (m_jFinal[4] > 0.0)
			{
				m_jFinal[4] -= 180.0;
			}
			m_jFinal[5] = -m_jFinal[5];
			if (m_jFinal[6] <= 0.0)
			{
				m_jFinal[6] += 180.0;
			}
			else if (m_jFinal[6] > 0.0)
			{
				m_jFinal[6] -= 180.0;
			}

		}

		if (m_lefty == TRUE && m_jFinal[2] >= -90.0
			&& m_elbowUp == TRUE && m_jFinal[3] >= -90.0)
		{
			if ((validMove = YoCalculateTimeOfRotation()) == TRUE
				&& m_timeOfMove > 0.0)
			{
				m_moving = TRUE;
				m_pDoc->m_isMovement++;
				return TRUE;
			}
		}
		else if (m_lefty == FALSE && m_jFinal[2] <= -90.0
			&& m_elbowUp == TRUE && m_jFinal[3] <= -90.0)
		{
			if ((validMove = YoCalculateTimeOfRotation()) == TRUE
				&& m_timeOfMove > 0.0)
			{
				m_moving = TRUE;
				m_pDoc->m_isMovement++;
				return TRUE;
			}
		}
		else if (m_lefty == TRUE && m_jFinal[2] >= -90.0
			&& m_elbowUp == FALSE && m_jFinal[3] <= -90.0)
		{
			if ((validMove = YoCalculateTimeOfRotation()) == TRUE
				&& m_timeOfMove > 0.0)
			{
				m_moving = TRUE;
				m_pDoc->m_isMovement++;
				return TRUE;
			}
		}
		else if (m_lefty == FALSE && m_jFinal[2] <= -90.0
			&& m_elbowUp == FALSE && m_jFinal[3] >= -90.0)
		{
			if ((validMove = YoCalculateTimeOfRotation()) == TRUE
				&& m_timeOfMove > 0.0)
			{
				m_moving = TRUE;
				m_pDoc->m_isMovement++;
				return TRUE;
			}
		}
	}

	if (validMove == FALSE)
	{
		TRACE0("Robot: INVALID MOVE\n");
		return FALSE;
	}

	return TRUE;
}


BOOL CStageRobot6::YoCalculateTimeOfRotation()
{
	int i;
	double tAccel[7];
	double dAccel[7];
	double dist;
	double velocity;
	double acceleration;
	double time[7];
	int longestJointMove;

	m_timeOfMove = 0.0;

	// check to make sure that joints are within min/max limits
	for (i = 1; i <= 6; i++)
	{
		if (m_jFinal[i] < m_jMinMax[i][0] || m_jFinal[i] > m_jMinMax[i][1])
		{
			TRACE2("Joint %d limit exceeded %.2lf \n", i, m_jFinal[i]);
			return FALSE;
		}
	}

	for (i = 1; i <= 6; i++)
	{
		dist = fabs(m_jFinal[i] - m_j[i]);
		if (dist > 0.0)
		{
			velocity = m_jMaxAccelMaxSpeed[i][1] * (GLdouble)m_speed * .01;
			tAccel[i] =  velocity / m_jMaxAccelMaxSpeed[i][0];
			tAccel[i] = YO_MAX(tAccel[i], m_jMinAccelTime[i]);
			tAccel[i] = YO_MAX(tAccel[i], m_minAccelTime);

			acceleration = velocity / tAccel[i];
			dAccel[i] = acceleration * tAccel[i] * tAccel[i] * 0.5;

			if (dAccel[i] * 2.0 >= dist)
			{
				// joint does not reach full velocity
				time[i] = 2.0 * sqrt(dist / acceleration);
				tAccel[i] = time[i] / 2.0;
				dAccel[i] = dist * 0.5;
			}
			else
			{
				time[i] = ((dist - (dAccel[i] * 2.0)) / velocity)
					+ (tAccel[i] * 2.0);
			}
		}
		else
		{
			time[i] = 0.0;
		}
		if (time[i] > m_timeOfMove)
		{
			m_timeOfMove = time[i];
			longestJointMove = i;
			m_accelTime = tAccel[i];
			m_accelDistance = dAccel[i];
			m_totalDistance = dist;
		}
	}

	if (m_timeOfMove > 0.0)
	{
		if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
			&& m_pDoc->m_currentCommand != NULL)
		{
			m_timeStart = m_pDoc->m_currentCommand->m_time;
		}
		else
		{
			m_gmTimeStart = m_pDoc->m_gmTime;
		}
	}

	return TRUE;
}




BOOL CStageRobot6::YoStraightLineMotion(double timeElapsed)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	double r;
	double acceleration;
	double velocity;
	GLdouble j[7][4];
	int i;
	int k;
	char s[256];
	GLdouble m[16];
	BOOL validMove;

	acceleration = (2.0 * m_accelDistance) / (m_accelTime * m_accelTime);
	velocity = acceleration * m_accelTime;

	if (timeElapsed <= m_accelTime)
	{
		r = (0.5 * acceleration * timeElapsed * timeElapsed) / m_totalDistance;
	}
	else if (timeElapsed >= m_timeOfMove - m_accelTime)
	{
		r = 1.0 - ((0.5 * acceleration * (m_timeOfMove - timeElapsed) * (m_timeOfMove - timeElapsed)) / m_totalDistance);
	}
	else
	{
		r = (m_accelDistance + (velocity * (timeElapsed - m_accelTime))) / m_totalDistance;
	}

	//TRACE1("r = %lf\n", r);
	for (i = 0; i < 16; i++)
	{
		m[i] = m_mStart[i] + ((m_mFinal[i] - m_mStart[i]) * r);
	}

	
	//m_pDoc->YoTranslateRotateValues(m_mStart, tS, rS);
	//m_pDoc->YoTranslateRotateValues(m_mFinal, tF, rF);

	//for (i = 0; i < 3; i++)
	//{
	//	tM[i] = tS[i] + ((tF[i] - tS[i]) * r);
	//	rM[i] = rS[i] + ((rF[i] - rS[i]) * r);
	//}

	//::glMatrixMode(GL_MODELVIEW);
	//::glPushMatrix();
	//::glLoadIdentity();
	//::glTranslated(tM[0], tM[1], tM[2]);
//	::glRotated(rM[0], 1.0, 0.0, 0.0);
	//::glRotated(rM[1], 0.0, 1.0, 0.0);
	//::glRotated(rM[2], 0.0, 0.0, 1.0);
	//::glGetDoublev(GL_MODELVIEW_MATRIX, m);
	//::glPopMatrix();

	YoInverseKinematics(m, j);

	for (i = 0; i < 4; i++)
	{
		//m_j[1] = j[1][i];
		//m_j[2] = j[2][i];
		//m_j[3] = j[3][i];
		//m_j[4] = j[4][i];
		//m_j[5] = j[5][i];
		//m_j[6] = j[6][i];

		if ((i == 1 || i == 2) && j[4][i] < 0.0)
		{
			j[4][i] += 180.0;
		}
		else if ((i == 1 || i == 2) && j[4][i] > 0.0)
		{
			j[4][i] -= 180.0;
		}

		if (m_wristFlipped == TRUE)
		{
			if (j[4][i] <= 0.0)
			{
				j[4][i] += 180.0;
			}
			else if (j[4][i] > 0.0)
			{
				j[4][i] -= 180.0;
			}
			j[5][i] = -j[5][i];
			if (j[6][i] <= 0.0)
			{
				j[6][i] += 180.0;
			}
			else if (j[6][i] > 0.0)
			{
				j[6][i] -= 180.0;
			}

		}

		if ((m_lefty == TRUE && j[2][i] >= -90.0
			&& m_elbowUp == TRUE && j[3][i] >= -90.0)
			|| (m_lefty == FALSE && j[2][i] <= -90.0
			&& m_elbowUp == TRUE && j[3][i] <= -90.0)
			|| (m_lefty == TRUE && j[2][i] >= -90.0
			&& m_elbowUp == FALSE && j[3][i] <= -90.0)
			|| (m_lefty == FALSE && j[2][i] <= -90.0
			&& m_elbowUp == FALSE && j[3][i] >= -90.0))
		{
			validMove = TRUE;
			for (k = 1; k <= 6; k++)
			{
				// check to make sure that joints are within min/max limits
				if (j[k][i] < m_jMinMax[k][0] || j[k][i] > m_jMinMax[k][1])
				{
					validMove = FALSE;
					break;
				}
			}
			if (validMove == TRUE)
			{
				m_j[1] = j[1][i];
				m_j[2] = j[2][i];
				m_j[3] = j[3][i];
				m_j[4] = j[4][i];
				m_j[5] = j[5][i];
				m_j[6] = j[6][i];
				return TRUE;
			}
		}
	}

	if (pMainFrame->m_viewPartActive == TRUE)
	{
		sprintf(s, "%s cannot reach %s%d using linear interpolation",
			m_pDoc->m_currentDevice->m_name, m_pDoc->m_currentTag->m_ptrPath->m_name,
			m_pDoc->m_currentTag->m_tag);
		m_pDoc->YoMessage(s);
	}

	m_moving = FALSE;
	m_pDoc->m_isMovement--;
	return FALSE;
}



BOOL CStageRobot6::YoCalculateJointAngles(void)
{
	double dAccel;
	double dist;
	double velocity;
	double acceleration;
	double timeElapsed;
	//SYSTEMTIME gmTime;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	int tms;
	CTimeSpan spanSec;
	int i;
	char buf[128];

	if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
	{
		timeElapsed = m_pDoc->m_timeCurrent - m_timeStart;	
	}
	else
	{
		timeCurrent = m_pDoc->m_gmTime;
		timeStart = m_gmTimeStart;
		spanSec = timeCurrent - timeStart;
		tms = m_pDoc->m_gmTime.wMilliseconds - m_gmTimeStart.wMilliseconds;
		timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
		TRACE1("Robot: timeElapsed = %.3lf   ", timeElapsed);
		TRACE2("m_gmTimeStart = %d %d   ", m_gmTimeStart.wSecond, m_gmTimeStart.wMilliseconds);
		TRACE2("m_gmTime = %d %d\n", m_pDoc->m_gmTime.wSecond, m_pDoc->m_gmTime.wMilliseconds);

	}

	if (timeElapsed >= m_timeOfMove)
	{
		timeElapsed = m_timeOfMove;
		m_moving = FALSE;
		m_pDoc->m_isMovement--;
	}
	else if (timeElapsed == 0.0)
	{
		return FALSE;
	}

	if (m_jointInterpolation == FALSE && m_moving == TRUE)
	{
		YoStraightLineMotion(timeElapsed);
	}
	else
	{
		for (i = 1; i <= 6; i++)
		{
			dist = m_jFinal[i] - m_jStart[i];
			if (fabs(dist) > 0.0)
			{
				dAccel = m_accelDistance * (fabs(dist) / m_totalDistance);
				acceleration = (2.0 * dAccel) / (m_accelTime * m_accelTime);
				velocity = acceleration * m_accelTime;

				/**
				//dAccel = fabs(dist) * (m_accelTime / m_timeOfMove);
				if (m_accelTime * 2.0 <= m_timeOfMove)
				{
					// will accelerate and reach constant velocity
					velocity = (fabs(dist) - (dAccel * 2.0))
						/ (m_timeOfMove - (m_accelTime * 2.0));
					acceleration = velocity / m_accelTime;
				}
				else
				{
					acceleration = (2.0 * dAccel) / (m_accelTime * m_accelTime);
				}
				**/

				if (timeElapsed <= m_accelTime)
				{
					//accelerating
					if (dist > 0)
					{
						m_j[i] = m_jStart[i] + (0.5 * acceleration * timeElapsed * timeElapsed);
					}
					else if (dist < 0)
					{
						m_j[i] = m_jStart[i] - (0.5 * acceleration * timeElapsed * timeElapsed);
					}
				}
				else if (timeElapsed >= m_timeOfMove - m_accelTime)
				{
					// deaccelerating
					if (dist > 0)
					{
						m_j[i] = m_jFinal[i] - (0.5 * acceleration
							* (m_timeOfMove - timeElapsed) * (m_timeOfMove - timeElapsed));
					}
					else if (dist < 0)
					{
						m_j[i] = m_jFinal[i] + (0.5 * acceleration
							* (m_timeOfMove - timeElapsed) * (m_timeOfMove - timeElapsed));
					}
				}
				else
				{
					// constant velocity
					if (dist > 0)
					{
						m_j[i] = (m_jStart[i] + dAccel) + (velocity * (timeElapsed - m_accelTime));
					}
					else if (dist < 0)
					{
						m_j[i] = (m_jStart[i] - dAccel) - (velocity * (timeElapsed - m_accelTime));
					}
				}
			}
		}
	}

	if (m_moving == FALSE && m_pDoc->m_acceptSocket != NULL)
	{
		// move has ended
		memset(buf, 0, 128);
		sprintf(buf, "> %s ENDMOVE", m_name);
		m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
	}

	return TRUE;
}


/***
BOOL CStageRobot6::YoCalculateJointAngles(void)
{
	double tAccel;
	double dAccel;
	long dist;
	double timeElapsed;
	SYSTEMTIME gmTime;
	CTime timeStart;
	CTime timeCurrent;
	int tms;
	CTimeSpan spanSec;
	long dpa;


	// calculate time of rotation
	timeCurrent = m_pDoc->m_gmTime;
	timeStart = m_ptrRotateInfo->m_gmTimeStart;
	spanSec = timeCurrent - timeStart;
	tms = m_pDoc->m_gmTime.wMilliseconds - m_ptrRotateInfo->m_gmTimeStart.wMilliseconds;
	timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);

	tAccel = (double)m_ptrRotateInfo->m_velocity / (double)m_ptrRotateInfo->m_acceleration;
	dAccel = ((double)m_encoderResolution * (double)m_ptrRotateInfo->m_acceleration * tAccel * tAccel * 0.5);
	dist = m_ptrRotateInfo->m_endPosition - m_ptrRotateInfo->m_startPosition;

	//TRACE3("tAccel = %.3lf  dAccel = %.3lf  timeElapsed = %.3lf  ", tAccel, dAccel, timeElapsed);
	//TRACE3("timeStart = %d  Cur = %d  tms = %d", m_ptrRotateInfo->m_gmTimeStart.wSecond, gmTime.wSecond,
	//	tms);

	if (dAccel * 2.0 >= (double)abs(dist))
	{
		// table does not reach full velocity
		if (timeElapsed <= m_ptrRotateInfo->m_timeOfRotation / 2.0)
		{
			// accelerating
			TRACE0(" + ");
			if (dist > 0)
			{
				dpa = m_ptrRotateInfo->m_startPosition + (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
			}
			else if (dist < 0)
			{
				dpa = m_ptrRotateInfo->m_startPosition - (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
			}
		}
		else
		{
			// deaccelerating
			TRACE0(" - ");
			if (dist > 0)
			{
				dpa = m_ptrRotateInfo->m_endPosition - (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* (m_ptrRotateInfo->m_timeOfRotation - timeElapsed) * (m_ptrRotateInfo->m_timeOfRotation - timeElapsed)
					* (double)m_encoderResolution);
			}
			else if (dist < 0)
			{
				dpa = m_ptrRotateInfo->m_endPosition + (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* (m_ptrRotateInfo->m_timeOfRotation - timeElapsed) * (m_ptrRotateInfo->m_timeOfRotation - timeElapsed)
					* (double)m_encoderResolution);
			}
		}
	}
	else
	{
		if (timeElapsed <= tAccel)
		{
			//accelerating
			TRACE0(" ++ ");
			if (dist > 0)
			{
				dpa = m_ptrRotateInfo->m_startPosition + (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
			}
			else if (dist < 0)
			{
				dpa = m_ptrRotateInfo->m_startPosition - (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
			}
		}
		else if (timeElapsed >= m_ptrRotateInfo->m_timeOfRotation - tAccel)
		{
			// deaccelerating
			TRACE0(" -- ");
			if (dist > 0)
			{
				dpa = m_ptrRotateInfo->m_endPosition - (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* (m_ptrRotateInfo->m_timeOfRotation - timeElapsed) * (m_ptrRotateInfo->m_timeOfRotation - timeElapsed)
					* (double)m_encoderResolution);
			}
			else if (dist < 0)
			{
				dpa = m_ptrRotateInfo->m_endPosition + (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* (m_ptrRotateInfo->m_timeOfRotation - timeElapsed) * (m_ptrRotateInfo->m_timeOfRotation - timeElapsed)
					* (double)m_encoderResolution);
			}
		}
		else
		{
			// constant velocity
			TRACE0(" ** ");
			if (dist > 0)
			{
				dpa = (m_ptrRotateInfo->m_startPosition + (long)dAccel) + (long)((double)m_ptrRotateInfo->m_velocity
					* (timeElapsed - tAccel) * (double)m_encoderResolution);
			}
			else if (dist < 0)
			{
				dpa = (m_ptrRotateInfo->m_startPosition - (long)dAccel) - (long)((double)m_ptrRotateInfo->m_velocity
					* (timeElapsed - tAccel) * (double)m_encoderResolution);
			}
		}
	}

	TRACE1("dpa = %ld\n", dpa);

	return TRUE;
}
***/


BOOL CStageRotaryTable::YoReadRotaryTable(FILE *fp, CStageRotaryTable *ptrRotaryTable)
{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	CStageDevice		*ptrParent;
  
	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "ROTARY_TABLE_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrRotaryTable, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "ROTARY_TABLE_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrRotaryTable->m_name);
		}
 		else if (strcmp(command, "ROTARY_TABLE_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrRotaryTable->m_parent, &partAttachName);
			if (strcmp(ptrRotaryTable->m_parent, "NONE") != 0)
			{
				ptrParent = m_pDoc->YoDeviceHashLookup(ptrRotaryTable->m_parent);
				ptrPart = m_pDoc->YoPartLookup(ptrParent, partAttachName);
			}
		}
		else if (strcmp(command, "ROTARY_TABLE_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrRotaryTable->m_visible);
		}
		else if (strcmp(command, "ROTARY_TABLE_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrRotaryTable->m_mass);
		}
		else if (strcmp(command, "ROTARY_TABLE_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrRotaryTable->m_barCode);
		}
		else if (strcmp(command, "ROTARY_TABLE_ACCEL") == 0)
		{
			sscanf(s, "%*s %f", &ptrRotaryTable->m_acceleration);
		}
		else if (strcmp(command, "ROTARY_TABLE_VELOCITY") == 0)
		{
			sscanf(s, "%*s %f", &ptrRotaryTable->m_velocity);
		}
		else if (strcmp(command, "ROTARY_TABLE_POSITION") == 0)
		{
			sscanf(s, "%*s %ld", &ptrRotaryTable->m_currentPosition);
			ptrRotaryTable->m_endPosition = ptrRotaryTable->m_currentPosition;
		}
		else if (strcmp(command, "ROTARY_TABLE_DIRECTION_POSITIVE") == 0)
		{
			sscanf(s, "%*s %d", &ptrRotaryTable->m_directionPositive);
		}
		else
		{
			return FALSE;
		}

	} // end while (done == FALSE)
	return TRUE;
}


BOOL CStageRotaryTable::YoHandleSim(char *buf)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	static SYSTEMTIME gmTimeStart;
	static UINT timeTotal;
	double timeOfRotation;
	char *s;
	int i = 0;
	CStageRotateInfo *curRI;
	//CWnd *pCBox;
	float acceleration;
	float velocity;
	long distance;
	BOOL modeP;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	CTimeSpan spanSec;

	if (m_pDoc->m_scriptFastForward == TRUE)
	{
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0) + m_pDoc->m_timeSleepTotal;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else if (pMainFrame->m_wndDlgScript != NULL && pMainFrame->m_wndDlgScriptVisible == TRUE)
	{
		//::GetSystemTime(&m_pDoc->m_gmTime);
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0)
		//	+ pMainFrame->m_wndDlgScript->m_timeSleepFastForward
		//	- pMainFrame->m_wndDlgScript->m_timeFastForward;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else
	{
		::GetSystemTime(&m_pDoc->m_gmTime);
	}

	if (buf[0] == 'G' && buf[1] == '\0')
	{
		timeOfRotation = YoCalculateTimeOfRotation();
		if (timeOfRotation > 0.0)
		{
			sprintf(buf, "< %s G %.3lf", m_name, timeOfRotation);
		}
		else
		{
			sprintf(buf, "X");
		}
	}
	else if (buf[0] == 'S' && buf[1] == '\0')
	{
		YoStopTable();
		sprintf(buf, "| %s S", m_name);
	}
	else if ((buf[1] == 'L' && buf[2] == 'F') || (buf[1] == 'C' && buf[2] == 'R'))
	{
		m_simRequestDone = TRUE;
	}
	else if (buf[0] == 'D' && buf[1] == 'o' && buf[2] == 'n' && buf[3] == 'e')
	{
		m_simRequestDone = FALSE;
	}
	else if (buf[0] == 'G' && buf[1] == 'H')
	{
		s = &buf[2];
		velocity = m_velocity;
		distance = m_distance;
		modeP = m_positionAbsolute;
		sscanf(s, "%f", &m_velocity);
		m_distance = m_endPosition + (360000 - (m_endPosition % 360000));
		m_positionAbsolute = TRUE;

		timeOfRotation = YoCalculateTimeToHome();
		if (timeOfRotation > 0.0)
		{
			sprintf(buf, "< %s GH %.3lf", m_name, timeOfRotation);
		}
		else
		{
			sprintf(buf, "X");
		}

		for (curRI = m_ptrRotateInfo; curRI != NULL; curRI = curRI->m_next)
		{
			i++;
		}
		TRACE1("i = %d\n", i);

		m_velocity = velocity;
		m_distance = distance;
		m_positionAbsolute = modeP;
	}
	else if (buf[1] == 'D' && buf[2] == 'P' && buf[3] == 'A')
	{
		if (m_ptrRotateInfo != NULL)
		{
			sprintf(buf, "| %s 1DPA %ld", m_name, YoCalculateRTPosition());
		}
		else
		{
			sprintf(buf, "| %s 1DPA %ld", m_name, m_endPosition);
		}
	}
	else if (buf[0] == '1' && buf[1] == 'V')
	{
		sprintf(buf, "| %s 1V %.2f", m_name, m_velocity);
	}
	else if (buf[0] == '1' && buf[1] == 'A')
	{
		sprintf(buf, "| %s 1A %.2f", m_name, m_acceleration);
	}
	else if (buf[0] == '1' && buf[1] == 'D')
	{
		sprintf(buf, "| %s 1D %ld", m_name, m_distance);
	}
	else if (buf[0] == 'V')
	{
		s = &buf[1];
		sscanf(s, "%f", &velocity);
		if (velocity >= 0.01 && velocity <= 200.0)
		{
			m_velocity = velocity;
		}
		sprintf(buf, "| %s V %.2f", m_name, m_velocity);
	}
	else if (buf[0] == 'A')
	{
		s = &buf[1];
		sscanf(s, "%f", &acceleration);
		if (acceleration >= 0.01 && acceleration <= 999.99)
		{
			m_acceleration = acceleration;
		}
		sprintf(buf, "| %s A %.2f", m_name, m_acceleration);
	}
	else if (buf[0] == 'D')
	{
		s = &buf[1];
		sscanf(s, "%ld", &m_distance);
		sprintf(buf, "| %s D %ld", m_name, m_distance);
	}
	else if (buf[0] == 'M' && buf[1] == 'P' && buf[2] == 'I')
	{
		m_positionAbsolute = FALSE;
		sprintf(buf, "| %s MPI", m_name);
	}
	else if (buf[0] == 'M' && buf[1] == 'P' && buf[2] == 'A')
	{
		m_positionAbsolute = TRUE;
		sprintf(buf, "| %s MPA", m_name);
	}
	else if (buf[0] == 'H' && (buf[1] != '+' || buf[1] != '-'))
	{
		if (m_directionPositive == TRUE)
		{
			m_directionPositive = FALSE;
			sprintf(buf, "| %s H-", m_name);
		}
		else
		{
			m_directionPositive = TRUE;
			sprintf(buf, "| %s H+", m_name);
		}
	}
	else if (buf[0] == 'H' && buf[1] != '+')
	{
		m_directionPositive = TRUE;
		sprintf(buf, "| %s H+", m_name);
	}
	else if (buf[0] == 'H' && buf[1] != '-')
	{
		m_directionPositive = FALSE;
		sprintf(buf, "| %s H-", m_name);
	}
	else
	{
		sprintf(buf, "X");
	}

	//::GetSystemTime(&gmTime);

	if (buf[0] == '<'
		&& m_ptrRotateInfo != NULL)
	{
		//if (m_timer > 0)
		//{
		//	KillTimer(1);
		//	timeCurrent = gmTime;
		//	timeStart = gmTimeStart;
		//	spanSec = timeCurrent - timeStart;
		//	tms = gmTime.wMilliseconds - gmTimeStart.wMilliseconds;
		//	timeElapsed = spanSec.GetTotalSeconds() * 1000 + tms;
		//	timeTotal += (UINT)timeOfRotation * 1000.0;
		//	SetTimer(1, timeTotal - timeElapsed, NULL);
		//}
		//else
		/***
		if (m_ptrRotateInfo != NULL && m_ptrRotateInfo->m_next == NULL)
		{
			m_ptrRotateInfo->m_gmTimeStart = gmTime;
			//pCBox = (CComboBox*)GetDlgItem(IDC_ROTATING);
			//pCBox->ShowWindow(SW_SHOW);
			//pCBox = (CComboBox*)GetDlgItem(IDC_STATUS);
			//pCBox->ShowWindow(SW_SHOW);
			timeTotal = (UINT)(timeOfRotation * 1000.0);
			SetTimer(1, timeTotal, NULL);
		}
		else if (i == 3)  // Go Home and no go commands stacked
		{
			m_ptrRotateInfo->m_gmTimeStart = gmTime;
			//pCBox = (CComboBox*)GetDlgItem(IDC_ROTATING);
			//pCBox->ShowWindow(SW_SHOW);
			//pCBox = (CComboBox*)GetDlgItem(IDC_STATUS);
			//pCBox->ShowWindow(SW_SHOW);
			timeTotal = (UINT)(m_ptrRotateInfo->m_timeOfRotation * 1000.0);
			SetTimer(1, timeTotal, NULL);
		}
		***/

		if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
			&& m_pDoc->m_currentCommand != NULL)
		{
			m_ptrRotateInfo->m_timeStart = m_pDoc->m_currentCommand->m_time;
		}
		else
		{
			m_ptrRotateInfo->m_gmTimeStart = m_pDoc->m_gmTime;
		}
		//if (m_pDoc->m_acceptSocket != NULL)
		//{
		//	m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		//}
		//if (m_pDoc->m_isMovement == 1)
		//{
		//	m_pDoc->YoMove();
		//}

	}
	else if (buf[0] == 'X')
	{
		//if (m_pDoc->m_acceptSocket != NULL)
		//{
		//	m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
		//}
		return FALSE;
	}
	//else if (m_pDoc->m_acceptSocket != NULL)
	//{
	//	sprintf(t, "| %s", buf);
	//	m_pDoc->m_acceptSocket->Send(t, strlen(t) + 1);
	//}

	return TRUE;
}


CStageRotaryTable::~CStageRotaryTable()
{
	CStageRotateInfo *curRotateInfo;
	CStageRotateInfo *prevRotateInfo = NULL;

	for (curRotateInfo = m_ptrRotateInfo; curRotateInfo != NULL;)
	{
		prevRotateInfo = curRotateInfo;
		curRotateInfo = curRotateInfo->m_next;
		delete prevRotateInfo;
	}
}

void CStageRotaryTable::YoGetRTSettings(void)
{

}


double CStageRotaryTable::YoCalculateTimeOfRotation(void)
{
	double tAccel;
	double dAccel;
	long dist;
	CStageRotateInfo *rotateInfo;
	CStageRotateInfo *curRI;

	// calculate time of rotation
	if (m_acceleration == 0.0)
	{
		return 0.0;
	}

	if (m_positionAbsolute == TRUE
		&& m_currentPosition == m_distance)
	{
		// already where you want to be
		return 0.0;
	}

	rotateInfo = new CStageRotateInfo();
	m_rotating++;
	m_pDoc->m_isMovement++;
	rotateInfo->m_acceleration = m_acceleration;
	rotateInfo->m_velocity = m_velocity;
	//rotateInfo->m_endPosition = m_distance;
	rotateInfo->m_directionPositive = m_directionPositive;

	if (m_ptrRotateInfo != NULL)
	{
		for (curRI = m_ptrRotateInfo; curRI != NULL && curRI->m_next != NULL; curRI = curRI->m_next);
		rotateInfo->m_startPosition = curRI->m_endPosition;
		curRI->m_next = rotateInfo;
	}
	else
	{
		rotateInfo->m_startPosition = m_endPosition;
		m_ptrRotateInfo = rotateInfo;
	}


	tAccel = (double)m_velocity / (double)m_acceleration;
	dAccel = ((double)m_encoderResolution * (double)m_acceleration * tAccel * tAccel * 0.5);
	if (m_positionAbsolute == TRUE)
	{
		dist = abs(m_distance - rotateInfo->m_startPosition);
		rotateInfo->m_endPosition = m_distance;
	}
	else
	{
		dist = abs(m_distance);
		if (m_directionPositive == TRUE)
		{
			rotateInfo->m_endPosition = rotateInfo->m_startPosition + dist;
		}
		else
		{
			rotateInfo->m_endPosition = rotateInfo->m_startPosition - dist;
		}
	}
	if (dAccel * 2.0 >= (double)dist)
	{
		// table does not reach full velocity
		rotateInfo->m_timeOfRotation = 2.0 * sqrt((2.0 * ((double)dist * 0.5 / (double)m_encoderResolution))
			/ (double)m_acceleration);
	}
	else
	{
		rotateInfo->m_timeOfRotation = ((((double)dist - (dAccel * 2.0)) / (double)m_encoderResolution)
			/ (double)m_velocity) + (tAccel * 2.0);
	}

	return rotateInfo->m_timeOfRotation;

}


double CStageRotaryTable::YoCalculateTimeToHome(void)
{
	double tAccel;
	double dAccel;
	long dist;
	long rotate3startPos = 1000;
	long initialStartPos;
	CStageRotateInfo *rotate1;
	CStageRotateInfo *rotate2;
	CStageRotateInfo *rotate3;
	CStageRotateInfo *curRI;


	// calculate time of rotation
	if (m_acceleration == 0.0)
	{
		return 0;
	}

	if (m_ptrRotateInfo != NULL)
	{
		for (curRI = m_ptrRotateInfo; curRI != NULL && curRI->m_next != NULL; curRI = curRI->m_next);
		initialStartPos = curRI->m_endPosition;
	}
	else
	{
		initialStartPos = m_endPosition;
	}

	if (initialStartPos % 360000 == 0)
	{
		// already at home
		return 0.0;
	}

	rotate1 = new CStageRotateInfo();
	m_rotating++;
	m_pDoc->m_isMovement++;
	rotate1->m_acceleration = m_acceleration;
	rotate1->m_startPosition = initialStartPos;
	if (m_ptrRotateInfo != NULL)
	{
		curRI->m_next = rotate1;
	}
	else
	{
		m_ptrRotateInfo = rotate1;
	}

	if (rotate1->m_startPosition % 360000 > 1000 || rotate1->m_startPosition % 360000 < 0)
	{
		m_distance = rotate1->m_startPosition + (360000 - (rotate1->m_startPosition % 360000));
		rotate1->m_velocity = m_velocity;
		//rotate1->m_endPosition = m_distance;
		//rotate1->m_directionPositive = m_directionPositive;

		tAccel = (double)m_velocity / (double)m_acceleration;
		dAccel = ((double)m_encoderResolution * (double)m_acceleration * tAccel * tAccel * 0.5);
		dist = abs(m_distance - rotate1->m_startPosition);
		//rotate1->m_endPosition = m_distance;

		if (dAccel >= (double)dist)
		{
			// table does not reach full velocity
			rotate1->m_timeOfRotation = 2.0 * sqrt((2.0 * ((double)dist / (double)m_encoderResolution))
				/ (double)m_acceleration);
			rotate1->m_endPosition = rotate1->m_startPosition + (dist * 2);
		}
		else
		{
			rotate1->m_timeOfRotation = ((((double)dist - dAccel) / (double)m_encoderResolution)
				/ (double)m_velocity) + (tAccel * 2.0);
			rotate1->m_endPosition = rotate1->m_startPosition + dist + (long)(dAccel + 0.5);
		}


		rotate2 = new CStageRotateInfo();
		m_rotating++;
		m_pDoc->m_isMovement++;
		rotate2->m_acceleration = m_acceleration;
		rotate2->m_velocity = m_velocity;
		//rotate1->m_endPosition = m_distance;
		//rotate1->m_directionPositive = m_directionPositive;

		rotate2->m_startPosition = rotate1->m_endPosition;
		rotate2->m_endPosition = m_distance + rotate3startPos;
		rotate1->m_next = rotate2;

		tAccel = (double)m_velocity / (double)m_acceleration;
		dAccel = ((double)m_encoderResolution * (double)m_acceleration * tAccel * tAccel * 0.5);
		dist = abs(m_distance + rotate3startPos - rotate2->m_startPosition);

		if (dAccel * 2.0 >= (double)dist)
		{
			// table does not reach full velocity
			rotate2->m_timeOfRotation = 2.0 * sqrt((2.0 * ((double)dist * 0.5 / (double)m_encoderResolution))
				/ (double)m_acceleration);
		}
		else
		{
			rotate2->m_timeOfRotation = ((((double)dist - (dAccel * 2.0)) / (double)m_encoderResolution)
				/ (double)m_velocity) + (tAccel * 2.0);
		}

		rotate3 = new CStageRotateInfo();
		m_rotating++;
		m_pDoc->m_isMovement++;
		rotate3->m_acceleration = m_acceleration;
		rotate3->m_velocity = 0.1f;

		rotate3->m_startPosition = rotate2->m_endPosition;
		rotate3->m_endPosition = m_distance;
		rotate2->m_next = rotate3;
		rotate3->m_endOfHome = TRUE;

		tAccel = (double)rotate3->m_velocity / (double)m_acceleration;
		dAccel = ((double)m_encoderResolution * (double)m_acceleration * tAccel * tAccel * 0.5);
		dist = rotate3startPos;
		if (dAccel * 2.0 >= (double)dist)
		{
			// table does not reach full velocity
			rotate3->m_timeOfRotation = 2.0 * sqrt((2.0 * ((double)dist * 0.5 / (double)m_encoderResolution))
				/ (double)m_acceleration);
		}
		else
		{
			rotate3->m_timeOfRotation = ((((double)dist - (dAccel * 2.0)) / (double)m_encoderResolution)
				/ (double)rotate3->m_velocity) + (tAccel * 2.0);
		}
		
		return rotate1->m_timeOfRotation + rotate2->m_timeOfRotation + rotate3->m_timeOfRotation;
	}

	else
	// special case when table is between 0 and 1 degree
	{
		m_distance = rotate1->m_startPosition - (rotate1->m_startPosition % 360000);
		rotate1->m_velocity = 0.1f;
		rotate1->m_endPosition = m_distance;
		rotate1->m_endOfHome = TRUE;

		tAccel = (double)rotate1->m_velocity / (double)m_acceleration;
		dAccel = ((double)m_encoderResolution * (double)m_acceleration * tAccel * tAccel * 0.5);
		dist = abs(m_distance - rotate1->m_startPosition);
		if (dAccel * 2.0 >= (double)dist)
		{
			// table does not reach full velocity
			rotate1->m_timeOfRotation = 2.0 * sqrt((2.0 * ((double)dist * 0.5 / (double)m_encoderResolution))
				/ (double)m_acceleration);
		}
		else
		{
			rotate1->m_timeOfRotation = ((((double)dist - (dAccel * 2.0)) / (double)m_encoderResolution)
				/ (double)rotate1->m_velocity) + (tAccel * 2.0);
		}
		
		return rotate1->m_timeOfRotation;

	}
}


BOOL CStageRotaryTable::YoRotateTable(CStagePart *ptrPart)
// transforms current modelView matrix to reflect table top rotation of ptrPart
// make certain that glMatrixMode has been set to GL_MODELVIEW before calling this routine
{
	int i;
	CStagePart *curPart;

	// rotate table top around z axis
	curPart = m_ptrPart;
	for (i = 0; i <= 1 && curPart != NULL && curPart != ptrPart; i++)
	{
		curPart = curPart->m_down;
	}
	if (curPart != NULL && i != 0)
	{
		::glRotated((GLdouble)((m_currentPosition / 1000) % 360), 0.0, 0.0, 1.0);
		return TRUE;
	}

	return FALSE;
}


long CStageRotaryTable::YoCalculateRTPosition(void)
{
	double tAccel;
	double dAccel;
	long dist;
	double timeElapsed;
	char buf[64];
	//SYSTEMTIME gmTime;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	int tms;
	CTimeSpan spanSec;
	CStageRotateInfo *ptrRI;
	CStageRotateInfo *curRI;


	// calculate time of rotation
	if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
	{
		timeElapsed = m_pDoc->m_timeCurrent - m_ptrRotateInfo->m_timeStart;	
	}
	else
	{
		timeCurrent = m_pDoc->m_gmTime;
		timeStart = m_ptrRotateInfo->m_gmTimeStart;
		spanSec = timeCurrent - timeStart;
		tms = m_pDoc->m_gmTime.wMilliseconds - m_ptrRotateInfo->m_gmTimeStart.wMilliseconds;
		timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
	}

	tAccel = (double)m_ptrRotateInfo->m_velocity / (double)m_ptrRotateInfo->m_acceleration;
	dAccel = ((double)m_encoderResolution * (double)m_ptrRotateInfo->m_acceleration * tAccel * tAccel * 0.5);
	dist = m_ptrRotateInfo->m_endPosition - m_ptrRotateInfo->m_startPosition;

	//TRACE3("tAccel = %.3lf  dAccel = %.3lf  timeElapsed = %.3lf  ", tAccel, dAccel, timeElapsed);
	//TRACE3("timeStart = %d  Cur = %d  tms = %d", m_ptrRotateInfo->m_gmTimeStart.wSecond, gmTime.wSecond,
	//	tms);

	if (dAccel * 2.0 >= (double)abs(dist))
	{
		// table does not reach full velocity
		if (timeElapsed <= m_ptrRotateInfo->m_timeOfRotation / 2.0)
		{
			// accelerating
			TRACE0(" + ");
			if (dist > 0)
			{
				m_currentPosition = m_ptrRotateInfo->m_startPosition + (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
			}
			else if (dist < 0)
			{
				m_currentPosition = m_ptrRotateInfo->m_startPosition - (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
			}
		}
		else
		{
			// deaccelerating
			TRACE0(" - ");
			if (dist > 0)
			{
				m_currentPosition = m_ptrRotateInfo->m_endPosition - (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* (m_ptrRotateInfo->m_timeOfRotation - timeElapsed) * (m_ptrRotateInfo->m_timeOfRotation - timeElapsed)
					* (double)m_encoderResolution);
			}
			else if (dist < 0)
			{
				m_currentPosition = m_ptrRotateInfo->m_endPosition + (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* (m_ptrRotateInfo->m_timeOfRotation - timeElapsed) * (m_ptrRotateInfo->m_timeOfRotation - timeElapsed)
					* (double)m_encoderResolution);
			}
		}
	}
	else
	{
		if (timeElapsed <= tAccel)
		{
			//accelerating
			TRACE0(" ++ ");
			if (dist > 0)
			{
				m_currentPosition = m_ptrRotateInfo->m_startPosition + (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
			}
			else if (dist < 0)
			{
				m_currentPosition = m_ptrRotateInfo->m_startPosition - (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
			}
		}
		else if (timeElapsed >= m_ptrRotateInfo->m_timeOfRotation - tAccel)
		{
			// deaccelerating
			TRACE0(" -- ");
			if (dist > 0)
			{
				m_currentPosition = m_ptrRotateInfo->m_endPosition - (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* (m_ptrRotateInfo->m_timeOfRotation - timeElapsed) * (m_ptrRotateInfo->m_timeOfRotation - timeElapsed)
					* (double)m_encoderResolution);
			}
			else if (dist < 0)
			{
				m_currentPosition = m_ptrRotateInfo->m_endPosition + (long)(0.5 * (double)m_ptrRotateInfo->m_acceleration
					* (m_ptrRotateInfo->m_timeOfRotation - timeElapsed) * (m_ptrRotateInfo->m_timeOfRotation - timeElapsed)
					* (double)m_encoderResolution);
			}
		}
		else
		{
			// constant velocity
			TRACE0(" ** ");
			if (dist > 0)
			{
				m_currentPosition = (m_ptrRotateInfo->m_startPosition + (long)dAccel) + (long)((double)m_ptrRotateInfo->m_velocity
					* (timeElapsed - tAccel) * (double)m_encoderResolution);
			}
			else if (dist < 0)
			{
				m_currentPosition = (m_ptrRotateInfo->m_startPosition - (long)dAccel) - (long)((double)m_ptrRotateInfo->m_velocity
					* (timeElapsed - tAccel) * (double)m_encoderResolution);
			}
		}
	}

	TRACE1("m_currentPosition = %ld\n", m_currentPosition);

	if (timeElapsed >= m_ptrRotateInfo->m_timeOfRotation)
	{
		if (m_stoppingTable == FALSE)
		{
			if (m_ptrRotateInfo != NULL && m_ptrRotateInfo->m_next == NULL)
			{
				//pCBox = (CComboBox*)GetDlgItem(IDC_ROTATING);
				//pCBox->ShowWindow(SW_HIDE);
				//pCBox = (CComboBox*)GetDlgItem(IDC_STATUS);
				//pCBox->ShowWindow(SW_HIDE);
				//TRACE0("WM_TIMER\n");
				//KillTimer(1);
				if (m_ptrRotateInfo->m_endOfHome == TRUE)
				{
					m_endPosition = 0;
				}
				else
				{
					m_endPosition = m_ptrRotateInfo->m_endPosition;
				}
				m_rotating--;
				m_pDoc->m_isMovement--;
				delete m_ptrRotateInfo;
				m_ptrRotateInfo = NULL;
				if (m_pDoc->m_acceptSocket != NULL)
				{
					memset(buf,0, 64);
					sprintf(buf, "> %s ENDROTATION", m_name);
					m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
				}
			}
			else if (m_ptrRotateInfo != NULL && m_ptrRotateInfo->m_next != NULL)
			{
				m_endPosition = m_ptrRotateInfo->m_endPosition;
				//KillTimer(1);
				if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
					&& m_pDoc->m_currentCommand != NULL)
				{
					m_ptrRotateInfo->m_next->m_timeStart = m_pDoc->m_currentCommand->m_time;
				}
				else
				{
					m_ptrRotateInfo->m_next->m_gmTimeStart = m_pDoc->m_gmTime;
				}
				//timeTotal = (UINT)(m_ptrRotateInfo->m_next->m_timeOfRotation * 1000.0);
				//i = SetTimer(1, timeTotal, NULL);
				//TRACE2("WM_TIMER: set timer = %d   ret = %d\n", timeTotal, i);
				ptrRI = m_ptrRotateInfo;
				m_ptrRotateInfo = ptrRI->m_next;
				m_rotating--;
				m_pDoc->m_isMovement--;
				delete ptrRI;
			}
		}
		else // m_stoppingTable == TRUE
		{
			if (m_ptrRotateInfo != NULL)
			{
				//pCBox = (CComboBox*)GetDlgItem(IDC_ROTATING);
				//pCBox->ShowWindow(SW_HIDE);
				//pCBox = (CComboBox*)GetDlgItem(IDC_STATUS);
				///pCBox->ShowWindow(SW_HIDE);
				//KillTimer(1);
				m_endPosition = m_ptrRotateInfo->m_endPosition;

				for (curRI = m_ptrRotateInfo; curRI != NULL;)
				{
					ptrRI = curRI;
					curRI = curRI->m_next;
					m_rotating--;
					m_pDoc->m_isMovement--;
					delete ptrRI;
				}
				m_ptrRotateInfo = NULL;
				m_stoppingTable = FALSE;
				//if (m_pDoc->m_acceptSocket != NULL)
				//{
				//	sprintf(buf, "> %s ENDROTATION", m_name);
				//	m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
				//}
			}


		}
		m_currentPosition = m_endPosition;

		//if (m_simRequestDone == TRUE)
		//{
			// need to simulate a CR or LF
		//	HandleSim("Done");
		//}
	}



	return m_currentPosition;
}


BOOL CStageRotaryTable::YoHandleCommand(char *ibuf, char *obuf)
{
	return TRUE;
}

void CStageRotaryTable::YoEStop(void)
{
	CStageRotateInfo *ptrRI;
	CStageRotateInfo *curRI;

	if (m_ptrRotateInfo != NULL)
	{

		for (curRI = m_ptrRotateInfo; curRI != NULL;)
		{
			ptrRI = curRI;
			curRI = curRI->m_next;
			delete ptrRI;
		}

		m_endPosition = m_currentPosition;

		m_rotating = 0;
		m_pDoc->m_isMovement--;
		m_ptrRotateInfo = NULL;
		m_stoppingTable = FALSE;
		m_simRequestDone = TRUE;
	}
	return;
}


void CStageRotaryTable::YoStopTable(void)
{
	double tAccel;
	double dAccel;
	long dist;
	double timeElapsed;
	double timeToStop;
	//SYSTEMTIME gmTime;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	int tms;
	CTimeSpan spanSec;


	// calculate time of rotation
	if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
	{
		timeElapsed = m_pDoc->m_timeCurrent - m_ptrRotateInfo->m_timeStart;	
	}
	else
	{
		timeCurrent = m_pDoc->m_gmTime;
		timeStart = m_ptrRotateInfo->m_gmTimeStart;
		spanSec = timeCurrent - timeStart;
		tms = m_pDoc->m_gmTime.wMilliseconds - m_ptrRotateInfo->m_gmTimeStart.wMilliseconds;
		timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
	}

	tAccel = (double)m_ptrRotateInfo->m_velocity / (double)m_ptrRotateInfo->m_acceleration;
	dAccel = ((double)m_encoderResolution * (double)m_ptrRotateInfo->m_acceleration * tAccel * tAccel * 0.5);
	dist = m_ptrRotateInfo->m_endPosition - m_ptrRotateInfo->m_startPosition;

	//TRACE3("tAccel = %.3lf  dAccel = %.3lf  timeElapsed = %.3lf  ", tAccel, dAccel, timeElapsed);
	//TRACE3("timeStart = %d  Cur = %d  tms = %d", m_ptrRotateInfo->m_gmTimeStart.wSecond, gmTime.wSecond,
	//	tms);

	if (dAccel * 2.0 >= (double)abs(dist))
	{
		// table does not reached full velocity
		if (timeElapsed <= m_ptrRotateInfo->m_timeOfRotation / 2.0)
		{
			// accelerating
			TRACE0(" + ");
			if (dist > 0)
			{
				m_ptrRotateInfo->m_endPosition
					= m_ptrRotateInfo->m_startPosition + (long)((double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
				m_ptrRotateInfo->m_timeOfRotation = timeElapsed * 2.0;
				timeToStop = timeElapsed;
			}
			else if (dist < 0)
			{
				m_ptrRotateInfo->m_endPosition
					= m_ptrRotateInfo->m_startPosition - (long)((double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
				m_ptrRotateInfo->m_timeOfRotation = timeElapsed * 2.0;
				timeToStop = timeElapsed;
			}
		}
		else
		{
			// deaccelerating
			return;
		}
	}
	else
	{
		if (timeElapsed <= tAccel)
		{
			//accelerating
			TRACE0(" ++ ");
			if (dist > 0)
			{
				m_ptrRotateInfo->m_endPosition
					= m_ptrRotateInfo->m_startPosition + (long)((double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
				m_ptrRotateInfo->m_timeOfRotation = timeElapsed * 2.0;
				timeToStop = timeElapsed;
			}
			else if (dist < 0)
			{
				m_ptrRotateInfo->m_endPosition
					= m_ptrRotateInfo->m_startPosition - (long)((double)m_ptrRotateInfo->m_acceleration
					* timeElapsed * timeElapsed * (double)m_encoderResolution);
				m_ptrRotateInfo->m_timeOfRotation = timeElapsed * 2.0;
				timeToStop = timeElapsed;
			}
		}
		else if (timeElapsed >= m_ptrRotateInfo->m_timeOfRotation - tAccel)
		{
			// deaccelerating
			return;
		}
		else
		{
			// constant velocity
			TRACE0(" ** ");
			if (dist > 0)
			{
				m_ptrRotateInfo->m_endPosition
					= (m_ptrRotateInfo->m_startPosition + (long)(dAccel * 2.0)) + (long)((double)m_ptrRotateInfo->m_velocity
					* (timeElapsed - tAccel) * (double)m_encoderResolution);
				m_ptrRotateInfo->m_timeOfRotation = timeElapsed + tAccel;
				timeToStop = tAccel;

			}
			else if (dist < 0)
			{
				m_ptrRotateInfo->m_endPosition
					= (m_ptrRotateInfo->m_startPosition - (long)(dAccel * 2.0)) - (long)((double)m_ptrRotateInfo->m_velocity
					* (timeElapsed - tAccel) * (double)m_encoderResolution);
				m_ptrRotateInfo->m_timeOfRotation = timeElapsed + tAccel;
				timeToStop = tAccel;
			}
		}
	}

	TRACE2("STOP in %.3lf at pos = %ld\n", timeToStop, m_ptrRotateInfo->m_endPosition);
	m_stoppingTable = TRUE;
	//KillTimer(1);
	//SetTimer(1, (UINT)(timeToStop * 1000.0), NULL);

	return;

}


void CStageGripper::YoOpenGripper(void)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDevice *currentDevice;
	CStageDevice *ptrDevice;
	CStageDevice *ptrToDevice;
	CStagePart *currentPart;
	CStagePart *ptrPart;
	CStagePart *ptrToPart;
	double maxDistance;
	double m[16];
	RECT vrect;
	CPoint pt;
	BOOL visible;
	BOOL visibleGrip;

	if (m_gripping == TRUE && m_down != NULL
		&& (ptrDevice = YoFindDeviceToGrip()) != NULL)
	{
		currentDevice = m_pDoc->m_currentDevice;
		currentPart = m_pDoc->m_currentPart;

		m_pDoc->m_currentDevice = this;
		m_pDoc->m_currentPart = m_ptrPart;
		m_pDoc->YoModelMatrixOfCurrentPart(m);

		// move camera out just past faceplate of hand
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();
		::glMultMatrixd(m);
		::glTranslated(0.0, 0.0, 120.0);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);

		visibleGrip = ptrDevice->m_visible;
		ptrDevice->m_visible = FALSE;
		visible = m_visible;
		m_visible = FALSE;

		maxDistance = YO_MAX(ptrDevice->m_ptrPart->m_max[0] - ptrDevice->m_ptrPart->m_min[0],
			ptrDevice->m_ptrPart->m_max[1] - ptrDevice->m_ptrPart->m_min[1]);
		maxDistance = YO_MAX(maxDistance,
			ptrDevice->m_ptrPart->m_max[2] - ptrDevice->m_ptrPart->m_min[2]);

		ptrPart = ptrDevice->m_ptrPart;

		// if device that is being released is above another device (z axis)
		// attach it to the other device
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::glFrustum(-40.0, 40.0, -40.0, 40.0, 1.0, maxDistance + 25.0);
		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		//if (m[12] == n[12] && m[13] == n[13])
		//{
		//	::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, 0.999, -0.01);
		//}
		//else
		//{
		//	::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, -0.01, .999);
		//}
		::gluLookAt(m[12], m[13], m[14], m[12], m[13], m[14] - 100.0, 0.01, 0.999, -0.01);

		pView->YoRender(YO_RENDER_PICK_PART);
		//::SwapBuffers(pView->m_pDC->GetSafeHdc());
		//Sleep(8000);

		m_visible = visible;
		ptrDevice->m_visible = visibleGrip;

		pView->GetWindowRect(&vrect);
		pt.x = (long)((vrect.right - vrect.left) / 2.0);
		pt.y = (long)((vrect.bottom - vrect.top) / 2.0);

		if (m_pDoc->YoMakeCurrentDevicePartTag(pt) == YO_DEVICE_PART
			&& (m_pDoc->YoIsChild(this, m_pDoc->m_currentDevice)) == FALSE)
		{
			ptrToDevice = m_pDoc->m_currentDevice;
			ptrToPart = m_pDoc->m_currentPart;

			m_pDoc->m_currentDevice = ptrDevice;
			m_pDoc->m_currentPart = ptrPart;
			m_pDoc->YoDetachDevice();
			m_pDoc->YoAttachDevice(ptrToPart);
		}
		else
		{
			m_pDoc->m_currentDevice = ptrDevice;
			m_pDoc->m_currentPart = ptrPart;
			m_pDoc->YoDetachDevice();
			// reattach device at world coords (rightmost position)
			for (ptrDevice = m_pDoc->m_deviceList;
				ptrDevice->m_right != NULL;
				ptrDevice = ptrDevice->m_right);
			ptrDevice->m_right = m_pDoc->m_currentDevice;
			m_pDoc->m_currentDevice->m_left = ptrDevice;
		}

		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
			pView->m_clipFront, pView->m_clipRear);
		::glMatrixMode(GL_MODELVIEW);
		::glPopMatrix();

		m_pDoc->m_currentDevice = currentDevice;
		m_pDoc->m_currentPart = currentPart;
	}

	m_gripping = FALSE;

	if (m_pDoc->m_isMovement == FALSE
		&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
		&& m_pDoc->m_scriptFastForward == FALSE)
	{
		pView->YoRender(YO_RENDER_FULL);
	}

	return;
}

void CStageGripper::YoCloseGripper(void)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}

	//if (pMainFrame->m_gripperDlgActive)
	//{
	//	m_pDoc->m_deviceBeingAttached = TRUE;
	//	SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)pMainFrame->m_hCursorLink);
	//}

	YoFindDeviceToGrip();

	m_gripping = TRUE;
	if (m_pDoc->m_isMovement == FALSE
		&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
		&& m_pDoc->m_scriptFastForward == FALSE)
	{
		pView->YoRender(YO_RENDER_FULL);
	}

	return;
}


BOOL CStageGripper::YoHandleCommand(char *buf)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CStageDevice *ptrDevice;
	char t[64];
	int i;

	if (toupper(buf[0]) == 'C' && toupper(buf[1]) == 'L')
	{
		i = sscanf(buf, "%*s %s", &t);
		if (i == 1 && (ptrDevice = m_pDoc->YoDeviceHashLookup(t)) != NULL)
		{
			YoCloseGripper(t);
			sprintf(buf, "| %s CLOSE %s", m_name, ptrDevice->m_name);
		}
		else
		{
			if ((ptrDevice = YoFindDeviceToGrip()) != NULL)
			{
				sprintf(buf, "| %s CLOSE %s", m_name, ptrDevice->m_name);
			}
			else
			{
				sprintf(buf, "| %s CLOSE", m_name);
			}
			m_gripping = TRUE;
			if (m_pDoc->m_isMovement == FALSE
				&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
				&& m_pDoc->m_scriptFastForward == FALSE)
			{
				pView->YoRender(YO_RENDER_FULL);
			}
		}
	}

	else if (toupper(buf[0]) == 'O' && toupper(buf[1]) == 'P')
	{
		if (m_down != NULL && strcmp(m_down->m_parent, "NONE") != 0)
		{
			sprintf(buf, "| %s OPEN %s", m_name, m_down->m_name);
			YoOpenGripper();
		}
		else
		{
			m_gripping = FALSE;
			sprintf(buf, "| %s OPEN", m_name);
			if (m_pDoc->m_isMovement == FALSE
				&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
				&& m_pDoc->m_scriptFastForward == FALSE)
			{
				pView->YoRender(YO_RENDER_FULL);
			}
		}
	}

	else if (toupper(buf[0]) == 'G' && toupper(buf[1]) == 'E')
	{
		if (m_gripping == TRUE)
		{
			sprintf(buf, "| %s GETCONFIG CLOSE", m_name);
		}
		else
		{
			sprintf(buf, "| %s GETCONFIG OPEN", m_name);
		}
	}

	else
	{
		sprintf(buf, "X");
	}


	return TRUE;
}

CStageDevice *CStageGripper::YoFindDeviceToGrip()
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return NULL;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return NULL;
	}
	double m[16];
	double n[16];
	RECT vrect;
	CStageDevice *currentDevice;
	CStagePart *currentPart;
	CStageDevice *ptrDevice;
	CPoint pt;
	BOOL visible;

	currentDevice = m_pDoc->m_currentDevice;
	currentPart = m_pDoc->m_currentPart;

	m_pDoc->m_currentDevice = this;
	m_pDoc->m_currentPart = m_ptrPart;
	m_pDoc->YoModelMatrixOfCurrentPart(m);

	visible = m_visible;
	m_visible = FALSE;

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	
	::glLoadIdentity();
	::glMultMatrixd(m);
	::glTranslated(0.0, 0.0, 1000.0);
	::glGetDoublev(GL_MODELVIEW_MATRIX, n);

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::glFrustum(-40.0, 40.0, -40.0, 40.0, m_ptrPart->m_max[2] - 1.0, m_ptrPart->m_max[2] + 50.0);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	if (m[12] == n[12] && m[13] == n[13])
	{
		::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, 0.999, -0.01);
	}
	else
	{
		::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, -0.01, .999);
	}

	pView->YoRender(YO_RENDER_PICK_PART);
	//::SwapBuffers(pView->m_pDC->GetSafeHdc());
	//Sleep(8000);

	pView->GetWindowRect(&vrect);
	pt.x = (long)((vrect.right - vrect.left) / 2.0);
	pt.y = (long)((vrect.bottom - vrect.top) / 2.0);

	if (m_pDoc->YoMakeCurrentDevicePartTag(pt) == YO_DEVICE_PART)
	{
		ptrDevice = m_pDoc->m_currentDevice;
		m_pDoc->YoDetachDevice();
		m_pDoc->YoAttachDevice(this->m_ptrPart);
	}
	else
	{
		ptrDevice = NULL;
	}

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	::glMatrixMode(GL_MODELVIEW);
	::glPopMatrix();

	m_visible = visible;

	m_pDoc->m_currentDevice = currentDevice;
	m_pDoc->m_currentPart = currentPart;

	return ptrDevice;
}

BOOL CStageGripper::YoPositionFinger(CStagePart *ptrPart)
// transforms current modelView matrix to reflect finger position of ptrPart
// make certain that glMatrixMode has been set to GL_MODELVIEW before calling this routine
{
	CStagePart *curPart;

	if (m_ptrPart != NULL 
		&& m_ptrPart->m_down != NULL
		&& ptrPart != m_ptrPart)
	{
		for (curPart = m_ptrPart->m_down;
			curPart != NULL && curPart != ptrPart;
			curPart = curPart->m_right);
		if (curPart != NULL)
		{
			//::glPushMatrix();
			if (m_typeTranslating == TRUE)
			{
				// translate fingers along x axis
				if (m_gripping == TRUE)
				{
					::glTranslated(-m_displacementClose, 0.0f, 0.0f);
				}
				else
				{
					::glTranslated(m_displacementOpen, 0.0f, 0.0f);
				}
			}
			else
			{
				// rotate fingers around y axis
				if (m_gripping == TRUE)
				{
					::glRotated(-m_displacementClose, 0.0, 1.0, 0.0);
				}
				else
				{
					::glRotated(m_displacementOpen, 0.0, 1.0, 0.0);
				}

			}
			//::glPopMatrix();
			return TRUE;
		}
	}
	return FALSE;
}



void CStageGripper::YoCloseGripper(char deviceName[64])
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageDevice *currentDevice;
	CStagePart *currentPart;
	CStageDevice *ptrDevice;

	if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) == NULL)
	{
		return;
	}

	currentDevice = m_pDoc->m_currentDevice;
	currentPart = m_pDoc->m_currentPart;
	m_pDoc->m_currentDevice = ptrDevice;
	m_pDoc->m_currentPart = ptrDevice->m_ptrPart;

	m_pDoc->YoDetachDevice();

	m_pDoc->YoAttachDevice(this->m_ptrPart);

	m_pDoc->m_currentDevice = currentDevice;
	m_pDoc->m_currentPart = currentPart;

	m_gripping = TRUE;

	if (m_pDoc->m_isMovement == FALSE
		&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
		&& m_pDoc->m_scriptFastForward == FALSE)
	{
		pView->YoRender(YO_RENDER_FULL);
	}

	return;
}


BOOL CStageGripper::YoReadGripper(FILE *fp, CStageGripper *ptrGripper)
{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	CStageDevice		*ptrParent;
  
	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "GRIPPER_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrGripper, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "GRIPPER_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrGripper->m_name);
		}
 		else if (strcmp(command, "GRIPPER_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrGripper->m_parent, &partAttachName);
			if (strcmp(ptrGripper->m_parent, "NONE") != 0)
			{
				ptrParent = m_pDoc->YoDeviceHashLookup(ptrGripper->m_parent);
				ptrPart = m_pDoc->YoPartLookup(ptrParent, partAttachName);
			}
		}
		else if (strcmp(command, "GRIPPER_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrGripper->m_visible);
		}
		else if (strcmp(command, "GRIPPER_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrGripper->m_mass);
		}
		else if (strcmp(command, "GRIPPER_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrGripper->m_barCode);
		}
		else if (strcmp(command, "GRIPPER_TYPE_TRANSLATING") == 0)
		{
			sscanf(s, "%*s %d", &ptrGripper->m_typeTranslating);
		}
		else if (strcmp(command, "GRIPPER_GRIPPING") == 0)
		{
			sscanf(s, "%*s %d", &ptrGripper->m_gripping);
		}
		else if (strcmp(command, "GRIPPER_DISPLACEMENT_OPEN") == 0)
		{
			sscanf(s, "%*s %lf", &ptrGripper->m_displacementOpen);
		}
		else if (strcmp(command, "GRIPPER_DISPLACEMENT_CLOSE") == 0)
		{
			sscanf(s, "%*s %lf", &ptrGripper->m_displacementClose);
		}
		else
		{
			return FALSE;
		}

	} // end while (done == FALSE)
	return TRUE;
}


BOOL CStageBarCodeReader::YoReadBarCodeReader(FILE *fp, CStageBarCodeReader *ptrBarCodeReader)
{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	CStageDevice		*ptrParent;
  
	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "BAR_CODE_READER_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrBarCodeReader, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "BAR_CODE_READER_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrBarCodeReader->m_name);
		}
 		else if (strcmp(command, "BAR_CODE_READER_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrBarCodeReader->m_parent, &partAttachName);
			if (strcmp(ptrBarCodeReader->m_parent, "NONE") != 0)
			{
				ptrParent = m_pDoc->YoDeviceHashLookup(ptrBarCodeReader->m_parent);
				ptrPart = m_pDoc->YoPartLookup(ptrParent, partAttachName);
			}
		}
		else if (strcmp(command, "BAR_CODE_READER_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrBarCodeReader->m_visible);
		}
		else if (strcmp(command, "BAR_CODE_READER_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrBarCodeReader->m_mass);
		}
		else if (strcmp(command, "BAR_CODE_READER_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrBarCodeReader->m_barCode);
		}
		else
		{
			return FALSE;
		}

	} // end while (done == FALSE)
	return TRUE;
}


BOOL CStageScale::YoReadScale(FILE *fp, CStageScale *ptrScale)
{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	CStageDevice		*ptrParent;
  
	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "SCALE_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrScale, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "SCALE_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrScale->m_name);
		}
 		else if (strcmp(command, "SCALE_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrScale->m_parent, &partAttachName);
			if (strcmp(ptrScale->m_parent, "NONE") != 0)
			{
				ptrParent = m_pDoc->YoDeviceHashLookup(ptrScale->m_parent);
				ptrPart = m_pDoc->YoPartLookup(ptrParent, partAttachName);
			}
		}
		else if (strcmp(command, "SCALE_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrScale->m_visible);
		}
		else if (strcmp(command, "SCALE_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrScale->m_mass);
		}
		else if (strcmp(command, "SCALE_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrScale->m_barCode);
		}
		else if (strcmp(command, "SCALE_UNITS") == 0)
		{
			sscanf(s, "%*s %d", &ptrScale->m_units);
		}
		else
		{
			return FALSE;
		}

	} // end while (done == FALSE)
	return TRUE;
}

BOOL CStageScale::YoHandleCommand(char *buf)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	CStageDevice *ptrDevice;
	char s[128];
	char t[64];
	int i;
	CWnd *pCBox;

	i = sscanf(buf, "%*s %s", &t);
	sprintf(s, "0.000");

	if (toupper(buf[0]) == 'L' || toupper(buf[0]) == 'P')
	{
		m_units = YO_UNITS_POUNDS;
	}
	else if (toupper(buf[0]) == 'K') 
	{
		m_units = YO_UNITS_KILOGRAMS;
	}


	if (toupper(buf[0]) == 'L' || toupper(buf[0]) == 'P' || toupper(buf[0]) == 'K')
	{
		if (i == 1)
		{
			ptrDevice = m_pDoc->YoDeviceHashLookup(t);
		}
		else
		{
			ptrDevice = YoGetMass();
		}

		if (ptrDevice != NULL && ptrDevice->m_mass > 0.0)
		{
			if (m_units == YO_UNITS_POUNDS)
			{
				sprintf(buf, "| %s LB %.3lf %s", m_name, ptrDevice->m_mass * 2.2, ptrDevice->m_name);
				sprintf(s, "%.3lf", ptrDevice->m_mass * 2.2);
			}
			else
			{
				sprintf(buf, "| %s KG %.3lf %s", m_name, ptrDevice->m_mass, ptrDevice->m_name);
				sprintf(s, "%.3lf", ptrDevice->m_mass);
			}
		}
		else
		{
			if (m_units == YO_UNITS_POUNDS)
			{
				sprintf(buf, "| %s LB", m_name);
			}
			else
			{
				sprintf(buf, "| %s KG", m_name);
			}
		}
	}

	else if (toupper(buf[0]) == 'Z')
	{
		sprintf(buf, "| %s Z", m_name);
	}
	else
	{
		sprintf(buf, "X");
	}

	if (pMainFrame->m_scaleDlgActive)
	{
		pCBox = (CComboBox*)pMainFrame->m_scaleDialog->GetDlgItem(IDC_SCALE_MASS);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
	}

	return TRUE;
}


CStageDevice *CStageScale::YoGetMass()
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return NULL;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return NULL;
	}
	double m[16];
	double n[16];
	RECT vrect;
	CStageDevice *currentDevice;
	CStagePart *currentPart;
	CStageDevice *ptrDevice;
	CPoint pt;
	int i;
	int j;
	BOOL visible;

	currentDevice = m_pDoc->m_currentDevice;
	currentPart = m_pDoc->m_currentPart;

	m_pDoc->m_currentDevice = this;
	m_pDoc->m_currentPart = m_ptrPart;
	m_pDoc->YoModelMatrixOfCurrentPart(m);

	visible = m_visible;
	m_visible = FALSE;

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	
	::glLoadIdentity();
	::glMultMatrixd(m);
	::glTranslated(0.0, 0.0, 1000.0);
	::glGetDoublev(GL_MODELVIEW_MATRIX, n);

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::glFrustum(m_ptrPart->m_min[0], m_ptrPart->m_max[0],
		m_ptrPart->m_min[1], m_ptrPart->m_max[2], m_ptrPart->m_max[2] - 15.0, m_ptrPart->m_max[2] + 15.0);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	//::glMatrixMode(GL_MODELVIEW);
	//::glPushMatrix();
	
	//::glLoadIdentity();
	//::glMultMatrixd(m);
	//::glTranslated(m_ptrPart->m_min[0], 0.0, m_ptrPart->m_max[2]);
	//::glGetDoublev(GL_MODELVIEW_MATRIX, m);
	//::glTranslated(1000.0, 0.0, 0.0);
	//::glGetDoublev(GL_MODELVIEW_MATRIX, n);

	//::glMatrixMode(GL_PROJECTION);
	//::glLoadIdentity();
	//::glFrustum(m_ptrPart->m_min[1], m_ptrPart->m_max[1], 1.0, 10.0,
	//	10.0, (m_ptrPart->m_max[0] - m_ptrPart->m_min[0]));
	//::glMatrixMode(GL_MODELVIEW);
	//::glLoadIdentity();
	if (m[12] == n[12] && m[13] == n[13])
	{
		::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, 0.999, -0.01);
	}
	else
	{
		::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, -0.01, .999);
	}

	pView->YoRender(YO_RENDER_PICK_PART);
	//::SwapBuffers(pView->m_pDC->GetSafeHdc());
	//Sleep(5000);

	pView->GetWindowRect(&vrect);
	//pt.x = (long)((vrect.right - vrect.left) / 2.0);
	//pt.x = 0;
	//pt.y = (long)((vrect.bottom - vrect.top) / 2.0);
	ptrDevice = NULL;

	for (i = 1; i < 8; i++)
	{
		pt.x = (long)((vrect.right - vrect.left) / 8.0) * (long)i;
		for (j = 1; j < 8; j++)
		{
			pt.y = (long)((vrect.bottom - vrect.top) / 8.0) * (long)j;
			if (m_pDoc->YoMakeCurrentDevicePartTag(pt) == YO_DEVICE_PART)
			{
				ptrDevice = m_pDoc->m_currentDevice;
				m_pDoc->YoDetachDevice();
				m_pDoc->YoAttachDevice(this->m_ptrPart);
				i = 8;
				j = 8;
			}
		}
	}

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	::glMatrixMode(GL_MODELVIEW);
	::glPopMatrix();

	m_visible = visible;

	m_pDoc->m_currentDevice = currentDevice;
	m_pDoc->m_currentPart = currentPart;

	return ptrDevice;

}


BOOL CStageBarCodeReader::YoHandleCommand(char *buf)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	char attachToDeviceName[64];
	CStageDevice *ptrToDevice;
	CWnd *pCBox;
	char s[256];
//	CStageDevice *currentDevice;
//	CStagePart *currentPart;
//	double m[16];
//	double mInv[16];
//	double x;
//	double y;
//	double z;
	int i;

	if ((toupper(buf[7]) == 'O' && toupper(buf[8]) == 'F')
		|| (toupper(buf[0]) == 'G' && toupper(buf[1]) == 'E'))
		// TRIGGER OFF or GETSCAN
	{
		i = sscanf(buf, "%*s %s", attachToDeviceName);
		
		if (i == 1 && toupper(buf[0]) == 'G' && m_scanning == TRUE)
		{
			if ((ptrToDevice = m_pDoc->YoDeviceHashLookup(attachToDeviceName)) != NULL)
			{
				sprintf(buf, "| %s GETSCAN %s %s", m_name, ptrToDevice->m_barCode, ptrToDevice->m_name);
				m_scanning = FALSE;
				m_pDoc->m_isMovement--;
				m_scanDistance = YO_SCAN_DISTANCE;
			}
			else
			{
				sprintf(buf, "X");
			}
		}
		else if (toupper(buf[0]) == 'G' && m_scanning == TRUE)
		{
			if ((ptrToDevice = YoGetScan()) != NULL)
			{
				sprintf(buf, "| %s GETSCAN %s %s", m_name, ptrToDevice->m_barCode, ptrToDevice->m_name);
				m_scanning = FALSE;
				m_pDoc->m_isMovement--;
				m_scanDistance = YO_SCAN_DISTANCE;

				if (pMainFrame->m_barCodeReaderDlgActive)
				{
					sprintf(s, "%s", ptrToDevice->m_barCode);
					pCBox = (CComboBox*)pMainFrame->m_barCodeReaderDialog->GetDlgItem(IDC_BCR_CODE);
					pCBox->SetWindowText(s);
					pCBox->UpdateWindow();

					pCBox = (CComboBox*)pMainFrame->m_barCodeReaderDialog->GetDlgItem(IDC_BCR_TRIGGER);
					((CButton *)pCBox)->SetCheck(0);
				}
			}
			else
			{
				sprintf(buf, "X");

				if (pMainFrame->m_barCodeReaderDlgActive)
				{
					sprintf(s, "");
					pCBox = (CComboBox*)pMainFrame->m_barCodeReaderDialog->GetDlgItem(IDC_BCR_CODE);
					pCBox->SetWindowText(s);
					pCBox->UpdateWindow();
				}
			}
		}
		else if (toupper(buf[7]) == 'O')
		{
			sprintf(buf, "| %s TRIGGEROFF", m_name);
			if (m_scanning == TRUE)
			{
				m_scanning = FALSE;
				m_pDoc->m_isMovement--;
			}
			m_scanDistance = YO_SCAN_DISTANCE;

			if (pMainFrame->m_barCodeReaderDlgActive)
			{
				pCBox = (CComboBox*)pMainFrame->m_barCodeReaderDialog->GetDlgItem(IDC_BCR_TRIGGER);
				((CButton *)pCBox)->SetCheck(0);
			}
		}

		else
		{
			sprintf(buf, "X");
		}

		if (m_pDoc->m_isMovement == FALSE
			&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
			&& m_pDoc->m_scriptFastForward == FALSE)
		{
			pView->YoRender(YO_RENDER_FULL);
		}
	}
	
	else if (toupper(buf[0]) == 'T' && toupper(buf[1]) == 'R')
	// TRIGGER
	{
		if (m_scanning == FALSE)
		{
			m_scanning = TRUE;
			m_pDoc->m_isMovement++;
		}			

		m_scanDistance = YO_SCAN_DISTANCE;
		sprintf(buf, "| %s TRIGGER", m_name);
		/***
		sscanf(buf, "%*s %s", attachToDeviceName);
		
		if ((ptrToDevice = m_pDoc->YoDeviceHashLookup(attachToDeviceName)) != NULL)
		{
			currentDevice = m_pDoc->m_currentDevice;
			currentPart = m_pDoc->m_currentPart;

			m_pDoc->m_currentDevice = this;
			m_pDoc->m_currentPart = m_ptrPart;
			m_pDoc->YoModelMatrixOfCurrentPart(m);

			m_pDoc->m_currentDevice = ptrToDevice;
			m_pDoc->m_currentPart = ptrToDevice->m_ptrPart;
			m_pDoc->YoModelMatrixOfCurrentPart(mInv);

			x = m[12] - mInv[12];
			y = m[13] - mInv[13];
			z = m[14] - mInv[14];

			m_scanDistance = sqrt(x * x + y * y + z * z);

			m_pDoc->m_currentDevice = currentDevice;
			m_pDoc->m_currentPart = currentPart;
			sprintf(buf, "| TRIGGER %s", ptrToDevice->m_name);
		}	
		else
		{
				sprintf(buf, "| TRIGGER");
		}
		***/
	}

	else
	{
			sprintf(buf, "X");
	}




	return TRUE;
}


CStageDevice *CStageBarCodeReader::YoGetScan()
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return NULL;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return NULL;
	}
	double m[16];
	double n[16];
	RECT vrect;
	CStageDevice *currentDevice;
	CStagePart *currentPart;
	CStageDevice *ptrDevice;
	CPoint pt;
	BOOL visible;

	currentDevice = m_pDoc->m_currentDevice;
	currentPart = m_pDoc->m_currentPart;

	m_pDoc->m_currentDevice = this;
	m_pDoc->m_currentPart = m_ptrPart;
	while(m_pDoc->m_currentPart->m_down != NULL)
	{
		m_pDoc->m_currentPart = m_pDoc->m_currentPart->m_down;
	}
	m_pDoc->YoModelMatrixOfCurrentPart(m);

	visible = m_visible;
	m_visible = FALSE;

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	
	::glLoadIdentity();
	::glMultMatrixd(m);
	::glTranslated(0.0, 0.0, 1000.0);
	::glGetDoublev(GL_MODELVIEW_MATRIX, n);

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::glFrustum(-25.0, 25.0, -25.0, 25.0, 100.0, YO_SCAN_DISTANCE + 100.0);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	if (m[12] == n[12] && m[13] == n[13])
	{
		::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, 0.999, -0.01);
	}
	else
	{
		::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, -0.01, .999);
	}

	pView->YoRender(YO_RENDER_PICK_PART);
	//::SwapBuffers(pView->m_pDC->GetSafeHdc());
	//Sleep(8000);

	pView->GetWindowRect(&vrect);
	pt.x = (long)((vrect.right - vrect.left) / 2.0);
	pt.y = (long)((vrect.bottom - vrect.top) / 2.0);

	if (m_pDoc->YoMakeCurrentDevicePartTag(pt) == YO_DEVICE_PART
		&& strcmp(m_pDoc->m_currentDevice->m_barCode, "000000000000") != 0)
	{
		ptrDevice = m_pDoc->m_currentDevice;
	}
	else
	{
		ptrDevice = NULL;
	}

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	::glMatrixMode(GL_MODELVIEW);
	::glPopMatrix();

	m_visible = visible;

	m_pDoc->m_currentDevice = currentDevice;
	m_pDoc->m_currentPart = currentPart;

	return ptrDevice;
}


void CStageBarCodeReader::YoRenderScan()
{
	GLdouble vStart[3];
	GLdouble vEnd[3];
	BOOL reenableLighting = FALSE;
	GLfloat colorRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLdouble scanRange = m_scanDistance / 8.0;
	GLdouble span = scanRange / 4.0;
	static GLushort pattern[] = {0xf30c, 0x0c33};
	int i;

	srand((unsigned)time(NULL));

	if (::glIsEnabled(GL_LIGHTING))
	{
		reenableLighting = TRUE;
		::glDisable(GL_LIGHTING);
	}
	::glColor4fv(colorRed);

	::glEnable(GL_LINE_STIPPLE);

	/***
	for (i = 0; i < 9; i++)
	{			
		vStart[0] = 0.0;
		vStart[1] = 0.0;
		vStart[2] = 0.0;
		vEnd[0] = (GLdouble)(rand() % ((int)(scanRange * 100.0))) / 100.0f
			- (scanRange / 2.0);
		vEnd[1] = 0.0;
		vEnd[2] = m_scanDistance;
		::glBegin(GL_LINES);
			::glVertex3dv(vStart);
			::glVertex3dv(vEnd);
		::glEnd();
	}
	***/
	for (i = 0; i < 9; i++)
	{
		::glLineStipple(1, pattern[i % 2]);
		vStart[0] = 0.0;
		vStart[1] = 0.0;
		vStart[2] = 0.0;
		vEnd[0]
			= ((GLdouble)(rand() % ((int)((scanRange + span / 2.0)  * 100.0f) - (int)((scanRange - span / 2.0) * 100.0f))) / 100.0f
			+ (scanRange - span / 2.0));
		scanRange -= span;
		vEnd[1] = 0.0;
		vEnd[2] = m_scanDistance;
		::glBegin(GL_LINES);
			::glVertex3dv(vStart);
			::glVertex3dv(vEnd);
		::glEnd();
	}

	for (i = 0; i < 2; i++)
	{
		if (pattern[i] & 0x0003)
		{
			pattern[i] = (pattern[i]>>2) | 0xc000;
		}
		else
		{
			pattern[i] = pattern[i]>>2;
		}
	}

	::glLineStipple(1, 0xffff);
	::glDisable(GL_LINE_STIPPLE);

	if (reenableLighting == TRUE)
	{
		::glEnable(GL_LIGHTING);
	}

	return;
}


BOOL CStageTrain::YoReadTrain(FILE *fp, CStageTrain *ptrTrain)
{
	char				s[128];
	char				command[32];
	char				t[64];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	CStageDevice		*ptrParent;
  
	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "TRAIN_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrTrain, ptrPart);
			//if (ptrParent->m_type == YO_TRACK)
			//{
			//	YoCalculateTrainPosition();
			//}
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "TRAIN_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrTrain->m_name);
		}
 		else if (strcmp(command, "TRAIN_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrTrain->m_parent, &partAttachName);
			if (strcmp(ptrTrain->m_parent, "NONE") != 0)
			{
				ptrParent = m_pDoc->YoDeviceHashLookup(ptrTrain->m_parent);
				ptrPart = m_pDoc->YoPartLookup(ptrTrain, partAttachName);
			}
		}
		else if (strcmp(command, "TRAIN_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrTrain->m_visible);
		}
		else if (strcmp(command, "TRAIN_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrTrain->m_mass);
		}
		else if (strcmp(command, "TRAIN_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrTrain->m_barCode);
		}
		else if (strcmp(command, "TRAIN_ACCELERATION") == 0)
		{
			sscanf(s, "%*s %lf", &ptrTrain->m_acceleration);
		}
		else if (strcmp(command, "TRAIN_VELOCITY") == 0)
		{
			sscanf(s, "%*s %lf", &ptrTrain->m_velocity);
		}
		else if (strcmp(command, "TRAIN_ATTACH_TRACK_SEG") == 0)
		{
			sscanf(s, "%*s %s", t);
			ptrPart = m_pDoc->YoPartLookup(ptrParent, t);
			if (ptrPart != NULL)
			{
				ptrTrain->m_ptrTrackSeg = ptrPart->m_ptrTrackSeg;
			}
			ptrPart = NULL;
		}
		else if (strcmp(command, "TRAIN_ATTACH_RELATIVE_POSITION") == 0)
		{
			sscanf(s, "%*s %lf", &ptrTrain->m_relativePosition);
		}
		else if (strcmp(command, "TRAIN_DIRECTION_POSITIVE") == 0)
		{
			sscanf(s, "%*s %d", &ptrTrain->m_directionPositive);
		}
		else
		{
			return FALSE;
		}

	} // end while (done == FALSE)

	return TRUE;
}


BOOL CStageTrain::YoHandleCommand(char *buf)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	char command[16];
	char t[256];
	double deltaT;
	CWnd *pCBox;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	CTimeSpan spanSec;

	if (m_pDoc->m_scriptFastForward == TRUE)
	{
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0) + m_pDoc->m_timeSleepTotal;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else if (pMainFrame->m_wndDlgScript != NULL && pMainFrame->m_wndDlgScriptVisible == TRUE)
	{
		//::GetSystemTime(&m_pDoc->m_gmTime);
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0)
		//	+ pMainFrame->m_wndDlgScript->m_timeSleepFastForward
		//	- pMainFrame->m_wndDlgScript->m_timeFastForward;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else
	{
		::GetSystemTime(&m_pDoc->m_gmTime);
	}

	if (toupper(buf[0]) == 'S' && toupper(buf[1]) == 'T')
	{
		sprintf(command, "STOP");
		sprintf(buf, "");
		m_initialVelocity = m_curVelocity;
		m_finalVelocity = 0.0f;
		m_totalDistance = 0.0f;
		//if (m_moving)
		//{
		//	m_pDoc->m_isMovement--;
		//}
		//m_moving = FALSE;

		if (pMainFrame->m_trainDlgActive)
		{
			pCBox = (CComboBox*)pMainFrame->m_trainDialog->GetDlgItem(IDC_TRAIN_GO);
			((CButton *)pCBox)->SetCheck(0);
		}
	}
	else if (toupper(buf[0]) == 'G' && toupper(buf[1]) == 'O')
	{
		sprintf(command, "GO");
		sprintf(buf, "");
		//::GetSystemTime(&m_gmTimeStart);
		if (m_moving == FALSE)
		{
			m_pDoc->m_isMovement++;
		}
		m_initialVelocity = m_curVelocity;
		m_finalVelocity = m_velocity;
		m_totalDistance = 0.0f;
		m_moving = TRUE;
	}
	else if (toupper(buf[0]) == 'V')
	{
		sprintf(command, "VELOCITY");
		sscanf(buf, "%*s %lf", &m_velocity);
		sprintf(buf, "%.3lf", m_velocity);
		m_initialVelocity = m_curVelocity;
		m_finalVelocity = m_velocity;
		m_totalDistance = 0.0f;
	}
	else if (toupper(buf[0]) == 'A')
	{
		sprintf(command, "ACCELERATION");
		sscanf(buf, "%*s %lf", &m_acceleration);
		sprintf(buf, "%.3lf", m_acceleration);
		m_initialVelocity = m_curVelocity;
		m_finalVelocity = m_velocity;
		m_totalDistance = 0.0f;
	}
	else
	{
		sprintf(buf, "X");
	}
	
	if (buf[0] == 'X')
	{
		return FALSE;
	}
	else
	{
		if (m_moving)
		{
			if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
				&& m_pDoc->m_currentCommand != NULL)
			{
				m_timeStart = m_pDoc->m_currentCommand->m_time;
			}
			else
			{
				m_gmTimeStart = m_pDoc->m_gmTime;
			}

			if ((m_curVelocity > 0.0f && m_velocity < 0.0f)
				|| (m_curVelocity < 0.0f && m_velocity > 0.0f))
			{
				m_changingDirection = TRUE;
				deltaT = fabs(m_curVelocity) / m_acceleration;
				m_reverseFinalVelocity = m_velocity;
				m_initialVelocity = m_curVelocity;
				m_finalVelocity = 0.0f;
				sprintf(buf, "%.3lf", deltaT);
			}
			else
			{
				deltaT = fabs(m_curVelocity - m_velocity) / m_acceleration;
				m_initialVelocity = m_curVelocity;
				sprintf(buf, "%.3lf", deltaT);
			}
		}

		sprintf(t, "| %s %s %s", m_name, command, buf);
		sprintf(buf, "%s", t);
	}

	return TRUE;
}


void CStageTrain::YoCalculateTrainPosition()
{
	// function which calculates the current train position and
	// heading for a given train

	double	x;
	double	y;
	double	d;
	double	theta;

	if (m_ptrTrackSeg == NULL)
	{
		return;
	}

	if (m_ptrTrackSeg->m_type == YO_TRACK_CIRCLE)
	{
		if (m_ptrTrackSeg->m_angle >= 0.0)
		{
			theta = YO_DEGREES_TO_RADIANS * (m_ptrTrackSeg->m_heading - 90.0);
		}
		else
		{
			theta = YO_DEGREES_TO_RADIANS * (m_ptrTrackSeg->m_heading + 90.0);
		}

		x = m_ptrTrackSeg->m_radius * cos(theta);
		y = m_ptrTrackSeg->m_radius * sin(theta);
		x = m_ptrTrackSeg->m_from[0] - x;
		y = m_ptrTrackSeg->m_from[1] - y;
		m_ptrPart->m_rotate[2] = m_ptrTrackSeg->m_heading
			+ (m_ptrTrackSeg->m_angle * m_relativePosition);
		theta += YO_DEGREES_TO_RADIANS * m_ptrTrackSeg->m_angle * m_relativePosition;
		m_ptrPart->m_translate[0] = m_ptrTrackSeg->m_radius * cos(theta);
		m_ptrPart->m_translate[1] = m_ptrTrackSeg->m_radius * sin(theta);
		m_ptrPart->m_translate[0] += x;
		m_ptrPart->m_translate[1] += y;
	}
	else
	{
		if (m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
			&& m_ptrTrackSeg->m_switchStatus == YO_SWITCH_OPENED)
		{
			m_ptrPart->m_translate[0] = m_ptrTrackSeg->m_from[0] + (m_relativePosition *
				(m_ptrTrackSeg->m_switch[0] - m_ptrTrackSeg->m_from[0]));
			m_ptrPart->m_translate[1] = m_ptrTrackSeg->m_from[1] + (m_relativePosition *
				(m_ptrTrackSeg->m_switch[1] - m_ptrTrackSeg->m_from[1]));
		}
		else
		{
			m_ptrPart->m_translate[0] = m_ptrTrackSeg->m_from[0] + (m_relativePosition *
				(m_ptrTrackSeg->m_to[0] - m_ptrTrackSeg->m_from[0]));
			m_ptrPart->m_translate[1] = m_ptrTrackSeg->m_from[1] + (m_relativePosition *
				(m_ptrTrackSeg->m_to[1] - m_ptrTrackSeg->m_from[1]));
		}
		//x = m_ptrPart->m_translate[0] - m_ptrTrackSeg->m_from[0];
		//y = m_ptrPart->m_translate[1] - m_ptrTrackSeg->m_from[1];
		x = m_ptrTrackSeg->m_to[0] - m_ptrTrackSeg->m_from[0];
		y = m_ptrTrackSeg->m_to[1] - m_ptrTrackSeg->m_from[1];
		d = sqrt(x * x + y * y);
		if (y >= 0.0)
		{
			m_ptrPart->m_rotate[2] = acos(x / d) * YO_RADIANS_TO_DEGREES;
		}
		else
		{
			m_ptrPart->m_rotate[2] = -acos(x / d) * YO_RADIANS_TO_DEGREES;
		}
	}

	if (m_ptrPart->m_rotate[2] > 180.0)
	{
		m_ptrPart->m_rotate[2] -= 360.0;
	}
	else if (m_ptrPart->m_rotate[2] <= -180.0)
	{
		m_ptrPart->m_rotate[2] += 360.0;
	}

	// change heading by 180 degrees on to-from tracks
	if (m_trackOrientation == YO_TRACK_TO_FROM)
	{
		if (m_ptrPart->m_rotate[2] >= 0.0 && m_ptrPart->m_rotate[2] < 180.0)
		{
			m_ptrPart->m_rotate[2] = -(180.0 - m_ptrPart->m_rotate[2]);
		}
		else if (m_ptrPart->m_rotate[2] < 0.0 && m_ptrPart->m_rotate[2] >= -180.0)
		{
			m_ptrPart->m_rotate[2] = 180.0 + m_ptrPart->m_rotate[2];
		}
		else if (m_ptrPart->m_rotate[2] >= 180.0)
		{
			m_ptrPart->m_rotate[2] -= 180.0;
		}
		else if (m_ptrPart->m_rotate[2] < -180.0)
		{
			m_ptrPart->m_rotate[2] += 180.0;
		}
	}

	// change heading by 180 degrees if direction is not positive
	if (m_directionPositive == FALSE)
	//if (m_curVelocity < 0.0f)
	{
		if (m_ptrPart->m_rotate[2] >= 0.0 && m_ptrPart->m_rotate[2] < 180.0)
		{
			m_ptrPart->m_rotate[2] = -(180.0 - m_ptrPart->m_rotate[2]);
		}
		else if (m_ptrPart->m_rotate[2] < 0.0 && m_ptrPart->m_rotate[2] >= -180.0)
		{
			m_ptrPart->m_rotate[2] = 180.0 + m_ptrPart->m_rotate[2];
		}
		else if (m_ptrPart->m_rotate[2] >= 180.0)
		{
			m_ptrPart->m_rotate[2] -= 180.0;
		}
		else if (m_ptrPart->m_rotate[2] < -180.0)
		{
			m_ptrPart->m_rotate[2] += 180.0;
		}
	}

	return;
}


void CStageTrain::YoAnimateTrain()

// Routine which moves the train that is attached to a track.
// Note: assumption is made that switch is properly set

{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	double timeElapsed;
	//SYSTEMTIME gmTime;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	int tms;
	double dist;
	double	d;
	double	dTotal;
	double dAccel;
	double tAccel;
	double dEnd;
	CTimeSpan spanSec;
	CWnd *pCBox;
	char buf[256];

	if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
	{
		timeElapsed = m_pDoc->m_timeCurrent - m_timeStart;	
	}
	else
	{
		timeCurrent = m_pDoc->m_gmTime;
		timeStart = m_gmTimeStart;
		spanSec = timeCurrent - timeStart;
		tms = m_pDoc->m_gmTime.wMilliseconds - m_gmTimeStart.wMilliseconds;
		timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
	}

	//tAccel = m_velocity / m_acceleration;
	//dAccel = ((double)m_encoderResolution * (double)m_ptrRotateInfo->m_acceleration * tAccel * tAccel * 0.5);
	//dist = m_ptrRotateInfo->m_endPosition - m_ptrRotateInfo->m_startPosition;

	//m_gmTimeStart = m_pDoc->m_gmTime;

	d = 0.0;
	//dTotal = fabs(m_velocity / (1000.0 / timeElapsed));

	//dTotal = fabs(m_velocity * timeElapsed);


	tAccel = fabs((m_finalVelocity - m_initialVelocity) / m_acceleration);
	if (m_finalVelocity > m_initialVelocity)
	{
		dAccel = fabs(m_initialVelocity * tAccel + 0.5 * m_acceleration * tAccel * tAccel);
	}
	else if (m_finalVelocity < m_initialVelocity)
	{
		dAccel = fabs(m_initialVelocity * tAccel - 0.5 * m_acceleration * tAccel * tAccel);
	}
	else
	{
		dAccel = 0.0f;
	}

	if (timeElapsed > tAccel)
	{
		dist = dAccel + fabs(m_finalVelocity * (timeElapsed - tAccel));
		m_curVelocity = m_finalVelocity;
	}
	else
	{
		if (m_finalVelocity >= m_initialVelocity)
		{
			dist = fabs(m_initialVelocity * timeElapsed
				+ 0.5 * m_acceleration * timeElapsed * timeElapsed);
			m_curVelocity = m_initialVelocity + m_acceleration * timeElapsed;
		}
		else
		{
			dist = fabs(m_initialVelocity * timeElapsed
				- 0.5 * m_acceleration * timeElapsed * timeElapsed);
			m_curVelocity = m_initialVelocity - m_acceleration * timeElapsed;
		}
	}

	dTotal = dist - m_totalDistance;
	m_totalDistance = dist;

	//while (d < dTotal && m_velocity != 0.0)
	while (fabs(d) < fabs(dTotal) && m_moving)
	{
		if ((m_trackOrientation == YO_TRACK_FROM_TO
			&& m_curVelocity > 0.0)
			|| (m_trackOrientation == YO_TRACK_TO_FROM
			&& m_curVelocity < 0.0))
		{
			if (m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
				&& m_ptrTrackSeg->m_switchStatus == YO_SWITCH_OPENED)
			{
				d += (1.0 - m_relativePosition)
					* m_ptrTrackSeg->m_switchDistance;
				if (m_ptrTrackSegEnd == m_ptrTrackSeg)
				{
					dEnd = fabs((m_relativePosition - m_relativePositionEnd)
						* m_ptrTrackSeg->m_switchDistance);
				}
			}
			else
			{
				d += (1.0 - m_relativePosition)
					* m_ptrTrackSeg->m_distance;
				if (m_ptrTrackSegEnd == m_ptrTrackSeg)
				{
					dEnd = fabs((m_relativePosition - m_relativePositionEnd)
						* m_ptrTrackSeg->m_distance);
				}
			}
		}
		else
		{
			if (m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
				&& m_ptrTrackSeg->m_switchStatus == YO_SWITCH_OPENED)
			{
				d += (0.0 + m_relativePosition)
					* m_ptrTrackSeg->m_switchDistance;
				if (m_ptrTrackSegEnd == m_ptrTrackSeg)
				{
					dEnd = fabs((m_relativePosition - m_relativePositionEnd)
						* m_ptrTrackSeg->m_switchDistance);
				}
			}
			else
			{
				d += (0.0 + m_relativePosition)
					* m_ptrTrackSeg->m_distance;
				if (m_ptrTrackSegEnd == m_ptrTrackSeg)
				{
					dEnd = fabs((m_relativePosition - m_relativePositionEnd)
						* m_ptrTrackSeg->m_distance);
				}
			}
		}

		TRACE3("%ld: d = %.3lf   dTotal = %.3lf\n", m_ptrTrackSeg, d, dTotal);

		if (m_ptrTrackSegEnd == m_ptrTrackSeg && dEnd <= dTotal)
		// train has reached end position so halt
		{
			m_moving = FALSE;
			m_pDoc->m_isMovement--;
			m_relativePosition = m_relativePositionEnd;
			if (pMainFrame->m_trainDlgActive == TRUE)
			{
				pCBox = (CComboBox*)pMainFrame->m_trainDialog->GetDlgItem(IDC_TRAIN_GO);
				((CButton *)pCBox)->SetCheck(0);
			}
			else if (m_pDoc->m_acceptSocket != NULL)
			{
				memset(buf, 0, 256);
				sprintf(buf, "> %s HALT", m_name);
				m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
			}
		}

		// go to the next track segment
		else if (d < dTotal)
		{
			if ((m_trackOrientation == YO_TRACK_FROM_TO
				&& m_curVelocity > 0.0)
				|| (m_trackOrientation == YO_TRACK_TO_FROM
				&& m_curVelocity < 0.0))
			{
				if (m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
					&& m_ptrTrackSeg->m_switchStatus == YO_SWITCH_OPENED
					&& m_ptrTrackSeg->m_ptrSwitch != NULL
					&& fabs(m_ptrTrackSeg->m_ptrSwitch->m_from[0] - m_ptrTrackSeg->m_switch[0]) < YO_TRACK_TOLERANCE
					&& fabs(m_ptrTrackSeg->m_ptrSwitch->m_from[1] - m_ptrTrackSeg->m_switch[1]) < YO_TRACK_TOLERANCE)
				{
					// turn off any sensors that might have been triggered
					//CheckSensors(train, FALSE);
					m_ptrTrackSeg = m_ptrTrackSeg->m_ptrSwitch;
					dTotal -= d;
					d = 0.0;
					m_relativePosition = 0.0;
				}
				else if (m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
					&& m_ptrTrackSeg->m_switchStatus == YO_SWITCH_OPENED
					&& m_ptrTrackSeg->m_ptrSwitch != NULL
					&& ((m_ptrTrackSeg->m_ptrSwitch->m_type == YO_TRACK_SWITCH
					&& fabs(m_ptrTrackSeg->m_ptrSwitch->m_switch[0] - m_ptrTrackSeg->m_switch[0]) < YO_TRACK_TOLERANCE
					&& fabs(m_ptrTrackSeg->m_ptrSwitch->m_switch[1] - m_ptrTrackSeg->m_switch[1]) < YO_TRACK_TOLERANCE)
					|| (fabs(m_ptrTrackSeg->m_ptrSwitch->m_to[0] - m_ptrTrackSeg->m_switch[0]) < YO_TRACK_TOLERANCE
					&& fabs(m_ptrTrackSeg->m_ptrSwitch->m_to[1] - m_ptrTrackSeg->m_switch[1]) < YO_TRACK_TOLERANCE)))
				{
					// turn off any sensors that might have been triggered
					//CheckSensors(train, FALSE);
					m_ptrTrackSeg = m_ptrTrackSeg->m_ptrSwitch;
					dTotal -= d;
					d = 0.0;
					if (m_trackOrientation == YO_TRACK_FROM_TO)
					{
						m_trackOrientation = YO_TRACK_TO_FROM;
					}
					else
					{
						m_trackOrientation = YO_TRACK_FROM_TO;
					}
					m_relativePosition = 1.0;	
				}
				else if (m_ptrTrackSeg->m_ptrTo != NULL
					&& fabs(m_ptrTrackSeg->m_ptrTo->m_from[0] - m_ptrTrackSeg->m_to[0]) < YO_TRACK_TOLERANCE
					&& fabs(m_ptrTrackSeg->m_ptrTo->m_from[1] - m_ptrTrackSeg->m_to[1]) < YO_TRACK_TOLERANCE)
				{
					// turn off any sensors that might have been triggered
					//CheckSensors(train, FALSE);
					m_ptrTrackSeg = m_ptrTrackSeg->m_ptrTo;
					dTotal -= d;
					d = 0.0;
					m_relativePosition = 0.0;
				}
				else if (m_ptrTrackSeg->m_ptrTo != NULL
					&& ((m_ptrTrackSeg->m_ptrTo->m_type == YO_TRACK_SWITCH
					&& fabs(m_ptrTrackSeg->m_ptrTo->m_switch[0] - m_ptrTrackSeg->m_to[0]) < YO_TRACK_TOLERANCE
					&& fabs(m_ptrTrackSeg->m_ptrTo->m_switch[1] - m_ptrTrackSeg->m_to[1]) < YO_TRACK_TOLERANCE)
					|| (fabs(m_ptrTrackSeg->m_ptrTo->m_to[0] - m_ptrTrackSeg->m_to[0]) < YO_TRACK_TOLERANCE
					&& fabs(m_ptrTrackSeg->m_ptrTo->m_to[1] - m_ptrTrackSeg->m_to[1]) < YO_TRACK_TOLERANCE)))
				{
					// turn off any sensors that might have been triggered
					//CheckSensors(train, FALSE);
					m_ptrTrackSeg = m_ptrTrackSeg->m_ptrTo;
					dTotal -= d;
					d = 0.0;
					if (m_trackOrientation == YO_TRACK_FROM_TO)
					{
						m_trackOrientation = YO_TRACK_TO_FROM;
					}
					else
					{
						m_trackOrientation = YO_TRACK_FROM_TO;
					}
					m_relativePosition = 1.0;
				}
				else // dead end
				{
					//m_curVelocity = 0.0;
					m_moving = FALSE;
					m_pDoc->m_isMovement--;
					m_relativePosition = 1.0;
					if (pMainFrame->m_trainDlgActive == TRUE)
					{
						pCBox = (CComboBox*)pMainFrame->m_trainDialog->GetDlgItem(IDC_TRAIN_GO);
						((CButton *)pCBox)->SetCheck(0);
					}
				}
			}
			else if ((m_trackOrientation == YO_TRACK_FROM_TO
				&& m_curVelocity < 0.0)
				|| (m_trackOrientation == YO_TRACK_TO_FROM
				&& m_curVelocity > 0.0))
			{
				if (m_ptrTrackSeg->m_ptrFrom != NULL
					&& fabs(m_ptrTrackSeg->m_ptrFrom->m_from[0] - m_ptrTrackSeg->m_from[0]) < YO_TRACK_TOLERANCE
					&& fabs(m_ptrTrackSeg->m_ptrFrom->m_from[1] - m_ptrTrackSeg->m_from[1]) < YO_TRACK_TOLERANCE)
				{
					// turn off any sensors that might have been triggered
					//CheckSensors(train, FALSE);
					m_ptrTrackSeg = m_ptrTrackSeg->m_ptrFrom;
					dTotal -= d;
					d = 0.0;
					if (m_trackOrientation == YO_TRACK_FROM_TO)
					{
						m_trackOrientation = YO_TRACK_TO_FROM;
					}
					else
					{
						m_trackOrientation = YO_TRACK_FROM_TO;
					}
					m_relativePosition = 0.0;
				}
				else if (m_ptrTrackSeg->m_ptrFrom != NULL
					&& ((m_ptrTrackSeg->m_ptrFrom->m_type == YO_TRACK_SWITCH
					&& fabs(m_ptrTrackSeg->m_ptrFrom->m_switch[0] - m_ptrTrackSeg->m_from[0]) < YO_TRACK_TOLERANCE
					&& fabs(m_ptrTrackSeg->m_ptrFrom->m_switch[1] - m_ptrTrackSeg->m_from[1]) < YO_TRACK_TOLERANCE)
					|| (fabs(m_ptrTrackSeg->m_ptrFrom->m_to[0] - m_ptrTrackSeg->m_from[0]) < YO_TRACK_TOLERANCE
					&& fabs(m_ptrTrackSeg->m_ptrFrom->m_to[1] - m_ptrTrackSeg->m_from[1]) < YO_TRACK_TOLERANCE)))
				{
					// turn off any sensors that might have been triggered
					//CheckSensors(train, FALSE);
					m_ptrTrackSeg = m_ptrTrackSeg->m_ptrFrom;
					dTotal -= d;
					d = 0.0;
					m_relativePosition = 1.0;
				}
				else // dead end
				{
					//m_curVelocity = 0.0;
					m_moving = FALSE;
					m_pDoc->m_isMovement--;
					m_relativePosition = 0.0;
					if (pMainFrame->m_trainDlgActive == TRUE)
					{
						pCBox = (CComboBox*)pMainFrame->m_trainDialog->GetDlgItem(IDC_TRAIN_GO);
						((CButton *)pCBox)->SetCheck(0);
					}
				}
			}

		TRACE3("d < dTotal %ld: d = %.3lf   dTotal = %.3lf\n", m_ptrTrackSeg, d, dTotal);
		}
		else 
		{
			if ((m_trackOrientation == YO_TRACK_FROM_TO
				&& m_curVelocity > 0.0)
				|| (m_trackOrientation == YO_TRACK_TO_FROM
				&& m_curVelocity < 0.0))
			{
				if (m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
					&& m_ptrTrackSeg->m_switchStatus == YO_SWITCH_OPENED)
				{
					m_relativePosition += dTotal
						/ m_ptrTrackSeg->m_switchDistance;
				}
				else
				{
					m_relativePosition += dTotal
						/ m_ptrTrackSeg->m_distance;
				}
			}
			else if ((m_trackOrientation == YO_TRACK_FROM_TO
				&& m_curVelocity < 0.0)
				|| (m_trackOrientation == YO_TRACK_TO_FROM
				&& m_curVelocity > 0.0))

			{
				if (m_ptrTrackSeg->m_type == YO_TRACK_SWITCH
					&& m_ptrTrackSeg->m_switchStatus == YO_SWITCH_OPENED)
				{
					m_relativePosition -= dTotal
						/ m_ptrTrackSeg->m_switchDistance;
				}
				else
				{
					m_relativePosition -= dTotal
						/ m_ptrTrackSeg->m_distance;
				}
			}
		}
	} // end while (fabs(d) < fabs(dTotal) && m_moving)
	
	YoCalculateTrainPosition();

	if (m_moving == TRUE && m_curVelocity == 0.0f
		&& m_finalVelocity == 0.0f && m_initialVelocity != 0.0f)
	{
		if (m_changingDirection == TRUE && m_reverseFinalVelocity != 0.0f)
		{
			if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
			{
				m_timeStart = m_pDoc->m_timeCurrent;
			}
			else
			{
				m_gmTimeStart = m_pDoc->m_gmTime;
			}

			m_initialVelocity = 0.0f;
			m_finalVelocity = m_reverseFinalVelocity;
			m_totalDistance = 0.0f;
			m_reverseFinalVelocity = 0.0f;
			m_changingDirection = FALSE;
			if (m_relativePositionEnd == 1.0)
			{
				m_relativePositionEnd = 0.0;
			}
			else
			{
				m_relativePositionEnd = 1.0;
			}
		}
		else
		{
			m_pDoc->m_isMovement--;
			m_moving = FALSE;
		}
		
	}

	return;
}


BOOL CStageTrain::YoEStop()
{
	if (m_moving == TRUE)
	{
		m_moving = FALSE;
		m_pDoc->m_isMovement--;
	}
	m_curVelocity = 0.0f;
	m_initialVelocity = 0.0f;

	return TRUE;
}


CStageConveyor::~CStageConveyor()
{
	CStageConveyorSegment *prevSegment = NULL;
	CStageConveyorSegment *curSegment;
	CStageConveyorSensor *prevSensor = NULL;
	CStageConveyorSensor *curSensor;
	CStageConveyorStopGate *prevStopGate = NULL;
	CStageConveyorStopGate *curStopGate;
	CStageConveyorTransverseLift *prevTransverseLift = NULL;
	CStageConveyorTransverseLift *curTransverseLift;
	CStageConveyorPallet *prevPallet = NULL;
	CStageConveyorPallet *curPallet;

	for (curSegment = m_ptrSegment; curSegment != NULL;)
	{
		for (curSensor = curSegment->m_ptrSensor; curSensor != NULL;)
		{
			prevSensor = curSensor;
			curSensor = curSensor->m_ptrNextSensor;
			delete prevSensor;
		}
		for (curStopGate = curSegment->m_ptrStopGate; curStopGate != NULL;)
		{
			prevStopGate = curStopGate;
			curStopGate = curStopGate->m_ptrNextStopGate;
			delete prevStopGate;
		}
		for (curTransverseLift = curSegment->m_ptrTransverseLift; curTransverseLift != NULL;)
		{
			prevTransverseLift = curTransverseLift;
			curTransverseLift = curTransverseLift->m_ptrNextTransverseLift;
			delete prevTransverseLift;
		}
		// since a conveyor pallet is a separate device, don't delete it
		// just remove it from the list for this conveyor
		for (curPallet = curSegment->m_ptrPallet; curPallet != NULL;)
		{
			prevPallet = curPallet;
			curPallet = curPallet->m_ptrNextPallet;

			prevPallet->m_moving = FALSE;
			prevPallet->m_distance = 0.0f;
			prevPallet->m_ptrNextPallet = NULL;
			prevPallet->m_ptrPrevPallet = NULL;
			prevPallet->m_ptrSegment = NULL;
			prevPallet->m_position[0] = 0.0f;
			prevPallet->m_position[1] = 0.0f;
			prevPallet->m_position[2] = 0.0f;
			prevPallet->m_endPosition[0] = 0.0f;
			prevPallet->m_endPosition[1] = 0.0f;
			prevPallet->m_endPosition[2] = 0.0f;
			prevPallet->m_startPosition[0] = 0.0f;
			prevPallet->m_startPosition[1] = 0.0f;
			prevPallet->m_startPosition[2] = 0.0f;
			prevPallet->m_relativePosition = 0.0f;
			// delete prevPallet;
		}

		prevSegment = curSegment;
		curSegment = curSegment->m_ptrNextSegment;
		delete prevSegment;
	}

}


BOOL CStageConveyor::YoReadConveyor(FILE *fp, CStageConveyor *ptrConveyor)

{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	
	sprintf(partAttachName, "");
  
	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "CONVEYOR_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrConveyor, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "CONVEYOR_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrConveyor->m_name);
		}
		else if (strcmp(command, "CONVEYOR_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrConveyor->m_parent, &partAttachName);
			ptrPart = m_pDoc->YoPartLookup(ptrConveyor, partAttachName);
		}
		else if (strcmp(command, "CONVEYOR_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrConveyor->m_visible);
		}
		else if (strcmp(command, "CONVEYOR_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrConveyor->m_mass);
		}
		else if (strcmp(command, "CONVEYOR_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrConveyor->m_barCode);
		}
		else if (strcmp(command, "CONVEYOR_OFFSET") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf", &ptrConveyor->m_offset[0],
				&ptrConveyor->m_offset[1], &ptrConveyor->m_offset[2]);
		}
		else
		{
			return FALSE;
		}

	} // end while (!done)
	return TRUE;
}

BOOL CStageConveyor::YoWriteConveyor(FILE *fp, CStagePart *ptrPart)
// Writes conveyor segment, sensor, stop gate, or transverse lift information
// to the end of a part portion of a workcell file if ptrPart is found
// Called from CStageView::YoRenderPart
{
	CStageConveyorSegment *ptrSegment;
	CStageConveyorSensor *ptrSensor;
	CStageConveyorStopGate *ptrStopGate;
	CStageConveyorTransverseLift *ptrTransverseLift;

	for (ptrSegment = m_ptrSegment; ptrSegment != NULL; ptrSegment = ptrSegment->m_ptrNextSegment)
	{
		if (ptrSegment->m_ptrPart == ptrPart)
		{
			fprintf(fp, "CONVEYOR_SEGMENT %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf\n",
				ptrSegment->m_from[0], ptrSegment->m_from[1],
				ptrSegment->m_from[2], ptrSegment->m_to[0],
				ptrSegment->m_to[1], ptrSegment->m_to[2],
				ptrSegment->m_maxVelocity, ptrSegment->m_acceleration);
			return TRUE;
		}

		for (ptrSensor = ptrSegment->m_ptrSensor; ptrSensor != NULL; ptrSensor = ptrSensor->m_ptrNextSensor)
		{
			if (ptrSensor->m_ptrPart == ptrPart)
			{
				fprintf(fp, "CONVEYOR_SENSOR %.3lf %.3lf %.3lf\n",
					ptrSensor->m_position[0], ptrSensor->m_position[1],
					ptrSensor->m_position[2]);
				return TRUE;
			}
		}

		for (ptrStopGate = ptrSegment->m_ptrStopGate; ptrStopGate != NULL; ptrStopGate = ptrStopGate->m_ptrNextStopGate)
		{
			if (ptrStopGate->m_ptrPart == ptrPart)
			{
				fprintf(fp, "CONVEYOR_STOP_GATE %.3lf %.3lf %.3lf %d\n",
					ptrStopGate->m_position[0], ptrStopGate->m_position[1],
					ptrStopGate->m_position[2], ptrStopGate->m_forward);
				return TRUE;
			}
		}

		for (ptrTransverseLift = ptrSegment->m_ptrTransverseLift; ptrTransverseLift != NULL;
			ptrTransverseLift = ptrTransverseLift->m_ptrNextTransverseLift)
		{
			if (ptrTransverseLift->m_ptrPart == ptrPart)
			{
				fprintf(fp, "CONVEYOR_TRANSVERSE_LIFT %.3lf %.3lf %.3lf %d %d %d\n",
					ptrTransverseLift->m_position[0], ptrTransverseLift->m_position[1],
					ptrTransverseLift->m_position[2], ptrTransverseLift->m_up,
					ptrTransverseLift->m_forwardBlocking, ptrTransverseLift->m_reverseBlocking);
				return TRUE;
			}
		}
	}

	return FALSE;
}


BOOL CStageConveyor::YoHandleSim(char *buf)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	double minTime;
	double speed;  // positive and negative values for speed set the direction
	double stoppingTime;
	double a = FLT_MAX;
	double b = FLT_MAX;
	double prevTranslate[3];
	double prevRotate[3];
	double prevPosition[3];
	CStageDevice *prevPtrParent;
	CStagePart *prevPtrAttachedFromPart;
	CStagePart *ptrPart;
	CStageDevice *ptrDevice;
	CStageDevice *curDevice;
	CStageConveyorSegment *ptrSegment;
	CStageConveyorSegment *prevPtrSegment;
	CStageConveyorSegment *curSegment;
	CStageConveyorSensor *ptrSensor;
	CStageConveyorSensor *curSensor;
	CStageConveyorStopGate *ptrStopGate;
	CStageConveyorTransverseLift *ptrTransverseLift;
	CStageConveyorPallet *ptrPallet;
	CStageConveyorPallet *curPallet;
	BOOL stop;
	BOOL liftUp;
	char command[16];
	char s[256];
	char t[256];
	char u[64];
	int i = 0;
	BOOL done = FALSE;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	CTimeSpan spanSec;

	if (m_pDoc->m_scriptFastForward == TRUE)
	{
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0) + m_pDoc->m_timeSleepTotal;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else if (pMainFrame->m_wndDlgScript != NULL && pMainFrame->m_wndDlgScriptVisible == TRUE)
	{
		//::GetSystemTime(&m_pDoc->m_gmTime);
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0)
		//	+ pMainFrame->m_wndDlgScript->m_timeSleepFastForward
		//	- pMainFrame->m_wndDlgScript->m_timeFastForward;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else
	{
		::GetSystemTime(&m_pDoc->m_gmTime);
	}

	if ((toupper(buf[0]) == 'G' && toupper(buf[1]) == 'O')
		|| (toupper(buf[0]) == 'S' && toupper(buf[1]) == 'T'))
	{
		i = sscanf(buf, "%*s %s %lf", &t, &speed);

		if (toupper(buf[0]) == 'S')
		{
			sprintf(command, "STOP");
		}
		else
		{
			sprintf(command, "GO");
		}

		if (toupper(buf[0]) == 'S' && i == 0)
		{
			speed = 0.0f;
			sprintf(t, "%s", m_ptrSegment->m_ptrPart->m_partName);
		}
		else if (toupper(buf[0]) == 'S' && i == 1)
		{
			speed = 0.0f;
		}
		else if (toupper(buf[0]) == 'G' && i != 2)
		{
			sprintf(buf, "X");
			done = TRUE;
		}

		while (!done)
		{
			speed = YO_MIN(100.0f, speed);
			speed = YO_MAX(-100.0f, speed);

			ptrPart = m_pDoc->YoPartLookup(this, t);
			if (ptrPart != NULL
				//&& (ptrSegment = YoFindSegment(ptrPart)) != NULL
				&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) == YO_CONVEYOR_SEGMENT
				&& YoIllegalMove(ptrSegment, speed) == FALSE)
			{
				YoCalculatePositionOfPallets(ptrSegment);

				if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
					&& m_pDoc->m_currentCommand != NULL)
				{
					ptrSegment->m_timeStart = m_pDoc->m_currentCommand->m_time;
				}
				else
				{
					ptrSegment->m_gmTimeStart = m_pDoc->m_gmTime;
				}

				ptrSegment->m_speed = fabs(speed / 100.0f);

				if ((ptrSegment->m_directionForward == TRUE
					&& ptrSegment->m_curVelocity > 0.0f
					&& speed < 0.0f)
					|| (ptrSegment->m_directionForward == FALSE
					&& ptrSegment->m_curVelocity > 0.0f
					&& speed > 0.0f))
				{
					ptrSegment->m_changingDirection = TRUE;
					stoppingTime = ptrSegment->m_curVelocity / ptrSegment->m_acceleration;
					ptrSegment->m_reverseFinalVelocity = ptrSegment->m_maxVelocity * ptrSegment->m_speed;
					ptrSegment->m_initialVelocity = ptrSegment->m_curVelocity;
					ptrSegment->m_finalVelocity = 0.0f;
					YoSetStartPositionOfPallets(ptrSegment);
					sprintf(buf, "%.3lf", stoppingTime);
				}
				else if (ptrSegment->m_moving == TRUE)
				{
					ptrSegment->m_initialVelocity = ptrSegment->m_curVelocity;
					ptrSegment->m_finalVelocity = ptrSegment->m_maxVelocity * ptrSegment->m_speed;
					YoSetStartPositionOfPallets(ptrSegment);
					minTime = YoCalculateEndPositionOfPallets(ptrSegment);
					sprintf(buf, "%.3lf", minTime);
				}
				else
				{
					ptrSegment->m_initialVelocity = 0.0f;
					ptrSegment->m_finalVelocity = ptrSegment->m_maxVelocity * ptrSegment->m_speed;
					if (speed == 0.0f)
					{
						sprintf(buf, "0.000");
					}
					else // conveyor segment is not moving
					{
						if (speed > 0.0f)
						{
							ptrSegment->m_directionForward = TRUE;
						}
						else if (speed < 0.0f)
						{
							ptrSegment->m_directionForward = FALSE;
						}
						if (m_moving == 0)
						{
							m_pDoc->m_isMovement++;
						}
						m_moving++;
						ptrSegment->m_moving = TRUE;
						YoSetStartPositionOfPallets(ptrSegment);
						minTime = YoCalculateEndPositionOfPallets(ptrSegment);
						sprintf(buf, "%.3lf", minTime);
					}
				}

				if (toupper(command[0]) == 'S' && i == 0 && ptrSegment->m_ptrNextSegment != NULL)
				{
					sprintf(t, "%s", ptrSegment->m_ptrNextSegment->m_ptrPart->m_partName);
				}
				else
				{
					done = TRUE;
				}
			}
			else
			{
				done = TRUE;
				sprintf(buf, "X");
			}
		}
		if (toupper(command[0]) == 'S')
		{
			sprintf(buf, "");
		}
	}

	else if (toupper(buf[0]) == 'S' && toupper(buf[1]) == 'G')
	{
		i = sscanf(buf, "%*s %s %d", &t, &stop);
		sprintf(command, "SG");

		if (i == 2)
		{
			ptrPart = m_pDoc->YoPartLookup(this, t);
			if (ptrPart != NULL
				//&& (ptrStopGate = YoFindStopGate(ptrPart)) != NULL
				&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) == YO_CONVEYOR_STOP_GATE
				&& ((ptrStopGate->m_forward == TRUE
				&& ptrStopGate->m_ptrSegment->m_directionForward == TRUE)
				|| (ptrStopGate->m_forward == FALSE
				&& ptrStopGate->m_ptrSegment->m_directionForward == FALSE)
				|| ptrStopGate->m_ptrSegment->m_curVelocity == 0.0f
				|| stop == 0))
				//&& YoTransverseLiftsInMotion(ptrStopGate->m_ptrSegment) == FALSE)
			{
				if (ptrStopGate->m_stop != stop)
				{
					ptrStopGate->m_stop = stop;

					if (ptrStopGate->m_ptrSegment->m_moving == TRUE)
					{
						YoCalculatePositionOfPallets(ptrStopGate->m_ptrSegment);
						ptrStopGate->m_ptrSegment->m_initialVelocity = ptrStopGate->m_ptrSegment->m_curVelocity;

						if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
							&& m_pDoc->m_currentCommand != NULL)
						{
							ptrStopGate->m_ptrSegment->m_timeStart = m_pDoc->m_currentCommand->m_time;
						}
						else
						{
							ptrStopGate->m_ptrSegment->m_gmTimeStart = m_pDoc->m_gmTime;
						}

						YoSetStartPositionOfPallets(ptrStopGate->m_ptrSegment);
						minTime = YoCalculateEndPositionOfPallets(ptrStopGate->m_ptrSegment);
						//sprintf(buf, "< %.3lf", minTime);
					}
					else if (m_pDoc->m_isMovement == 0
						&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
						&& m_pDoc->m_scriptFastForward == FALSE)
					{
						pView->YoRender(YO_RENDER_FULL);
					}
				}
				sprintf(buf, "%s %d", t, ptrStopGate->m_stop);
				if (pMainFrame->m_viewPartActive == TRUE)
				{
					m_pDoc->YoMessage("");
				}			
				sprintf(buf, "X");
			}
			else
			{
				if (pMainFrame->m_viewPartActive == TRUE)
				{
					sprintf(s, "Unable to raise stop gate. Turn off conveyor segment %s before proceeding",
						ptrStopGate->m_ptrSegment->m_ptrPart->m_partName);
					m_pDoc->YoMessage(s);
				}			
				sprintf(buf, "X");
			}
		}
		else if (i == 1)
		{
			ptrPart = m_pDoc->YoPartLookup(this, t);
			if (ptrPart != NULL
				&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) == YO_CONVEYOR_STOP_GATE)
			{
				sprintf(buf, "%s %d", t, ptrStopGate->m_stop);
			}
			else
			{
				sprintf(buf, "X");
			}
		}
		else
		{
			sprintf(buf, "X");
		}
	}

	else if (toupper(buf[0]) == 'T' && toupper(buf[1]) == 'L')
	{
		i = sscanf(buf, "%*s %s %d", &t, &liftUp);
		sprintf(command, "TL");

		if (i == 2)
		{

			ptrPart = m_pDoc->YoPartLookup(this, t);
			if (ptrPart != NULL
				//&& (ptrTransverseLift = YoFindTransverseLift(ptrPart)) != NULL
				&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) == YO_CONVEYOR_TRANSVERSE_LIFT
				&& YoSafeLift(ptrTransverseLift, liftUp) == TRUE
				&& ptrTransverseLift->m_inMotion == FALSE)
			{
				if (ptrTransverseLift->m_up != liftUp)
				{
					ptrTransverseLift->m_up = liftUp;
					ptrTransverseLift->m_ptrMirrorTransverseLift->m_up = ptrTransverseLift->m_up;
					ptrTransverseLift->m_inMotion = TRUE;
					ptrTransverseLift->m_ptrMirrorTransverseLift->m_inMotion = TRUE;
					if (m_moving == 0)
					{
						m_pDoc->m_isMovement++;
					}
					m_moving++;

					if (ptrTransverseLift->m_ptrSegment->m_moving == TRUE)
					{
						//YoCalculatePositionOfPallets(ptrTransverseLift->m_ptrSegment);
						ptrTransverseLift->m_ptrSegment->m_initialVelocity = ptrTransverseLift->m_ptrSegment->m_curVelocity;
					}
					if (ptrTransverseLift->m_ptrTransverseSegment->m_moving == TRUE)
					{
						//YoCalculatePositionOfPallets(ptrTransverseLift->m_ptrTransverseSegment);
						ptrTransverseLift->m_ptrTransverseSegment->m_initialVelocity = ptrTransverseLift->m_ptrTransverseSegment->m_curVelocity;
					}


					if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
						&& m_pDoc->m_currentCommand != NULL)
					{
						ptrTransverseLift->m_timeStart = m_pDoc->m_currentCommand->m_time;
					}
					else
					{
						ptrTransverseLift->m_gmTimeStart = m_pDoc->m_gmTime;
					}

					if (ptrTransverseLift->m_ptrSegment->m_moving == TRUE)
					{
						if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
							&& m_pDoc->m_currentCommand != NULL)
						{
							ptrTransverseLift->m_ptrSegment->m_timeStart = ptrTransverseLift->m_timeStart;
						}
						else
						{
							ptrTransverseLift->m_ptrSegment->m_gmTimeStart = ptrTransverseLift->m_gmTimeStart;
						}

						YoSetStartPositionOfPallets(ptrTransverseLift->m_ptrSegment);
						YoCalculateEndPositionOfPallets(ptrTransverseLift->m_ptrSegment);
					}
					if (ptrTransverseLift->m_ptrTransverseSegment->m_moving == TRUE)
					{
						if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
							&& m_pDoc->m_currentCommand != NULL)
						{
							ptrTransverseLift->m_ptrTransverseSegment->m_timeStart = ptrTransverseLift->m_timeStart;
						}
						else
						{
							ptrTransverseLift->m_ptrTransverseSegment->m_gmTimeStart = ptrTransverseLift->m_gmTimeStart;
						}

						YoSetStartPositionOfPallets(ptrTransverseLift->m_ptrTransverseSegment);
						YoCalculateEndPositionOfPallets(ptrTransverseLift->m_ptrTransverseSegment);
					}

					if (ptrTransverseLift->m_up == FALSE)
					{
						ptrPallet = NULL;
						for (curPallet = ptrTransverseLift->m_ptrTransverseSegment->m_ptrPallet;
							curPallet != NULL; curPallet = curPallet->m_ptrNextPallet)
						{
							if (curPallet->m_relativePosition + 0.0001 >= ptrTransverseLift->m_ptrMirrorTransverseLift->m_relativePosition
								&& curPallet->m_relativePosition - 0.0001 <= ptrTransverseLift->m_ptrMirrorTransverseLift->m_relativePosition
								&& curPallet->m_ptrPart != NULL)
							{
								ptrPallet = curPallet;
								break;
							}
						}
						if (ptrPallet != NULL)
						{
							ptrPallet->m_position[2] -= YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
							YoTransferPallet(ptrPallet, ptrTransverseLift->m_ptrSegment);
						}
					}
					
					//sprintf(buf, "< %.3lf", YO_CONVEYOR_TRANSVERSE_LIFT_TIME);
				}
				sprintf(buf, "%s %d", t, ptrTransverseLift->m_up);
			}
			else
			{
				sprintf(buf, "X");
			}
		}
		else if (i == 1)
		{
			ptrPart = m_pDoc->YoPartLookup(this, t);
			if (ptrPart != NULL
				&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) == YO_CONVEYOR_TRANSVERSE_LIFT)
			{
				sprintf(buf, "%s %d", t, ptrTransverseLift->m_up);
			}
			else
			{
				sprintf(buf, "X");
			}
		}
		else
		{
			sprintf(buf, "X");
		}
	}

	else if (toupper(buf[0]) == 'S' && toupper(buf[1]) == 'E')
	{
		sscanf(buf, "%*s %s", &t);
		ptrPart = m_pDoc->YoPartLookup(this, t);
		if (ptrPart != NULL
			//&& (ptrSensor = YoFindSensor(ptrPart)) != NULL)
			&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) == YO_CONVEYOR_SENSOR)
		{
			sprintf(command, "SEN");
			if (ptrSensor->m_ptrPallet == NULL)
			{
				sprintf(buf, "%s 0", t);
			}
			else
			{
				sprintf(buf, "%s 1 %s", t, ptrSensor->m_ptrPallet->m_name);
			}
		}
		else
		{
			sprintf(buf, "X");
		}
	}

	else if (toupper(buf[0]) == 'P' && toupper(buf[1]) == 'O' && toupper(buf[2]) == 'S')
	{
		i = sscanf(buf, "%*s %s %s %lf", &t, &u, &a);
		ptrDevice = m_pDoc->YoDeviceHashLookup(t);

		sprintf(command, "POS");

		if (ptrDevice != NULL && ptrDevice->m_type == YO_CONVEYOR_PALLET && i == 1)
		{
			if (((CStageConveyorPallet *)ptrDevice)->m_ptrSegment != NULL)
			{
				for (curSensor = ((CStageConveyorPallet *)ptrDevice)->m_ptrSegment->m_ptrSensor;
					curSensor != NULL && curSensor->m_ptrPallet != (CStageConveyorPallet *)ptrDevice;
					curSensor = curSensor->m_ptrNextSensor);

				if (curSensor == NULL)
				{
				sprintf(buf, "%s %s %.6lf", ptrDevice->m_name,
					((CStageConveyorPallet *)ptrDevice)->m_ptrSegment->m_ptrPart->m_partName,
					((CStageConveyorPallet *)ptrDevice)->m_relativePosition);
				}
				else
				{
				sprintf(buf, "%s %s %.6lf %s", ptrDevice->m_name,
					((CStageConveyorPallet *)ptrDevice)->m_ptrSegment->m_ptrPart->m_partName,
					((CStageConveyorPallet *)ptrDevice)->m_relativePosition,
					curSensor->m_ptrPart->m_partName);
				}
			}
			else
			{
				sprintf(buf, "X");
			}
		}
		else if (ptrDevice != NULL && ptrDevice->m_type == YO_CONVEYOR_PALLET && (i == 2 || i == 3))
		{
			ptrPart = m_pDoc->YoPartLookup(this, u);
			if (ptrPart != NULL
				//&& ((ptrSegment = YoFindSegment(ptrPart)) != NULL
				//|| (ptrStopGate = YoFindStopGate(ptrPart)) != NULL
				//|| (ptrTransverseLift = YoFindTransverseLift(ptrPart)) != NULL
				//|| (ptrSensor = YoFindSensor(ptrPart)) != NULL)
				&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) != 0
				&& m_moving == FALSE)
			{
				if (i == 3)
				{
					a = YO_MIN(1.0, a);
					a = YO_MAX(0.0, a);
				}
				else if (ptrSensor != NULL)
				{
					a = ptrSensor->m_relativePosition;
					ptrSegment = ptrSensor->m_ptrSegment;
				}
				else if (ptrStopGate != NULL)
				{
					a = ptrStopGate->m_relativePosition;
					ptrSegment = ptrStopGate->m_ptrSegment;
				}
				else if (ptrTransverseLift != NULL)
				{
					a = ptrTransverseLift->m_relativePosition;
					ptrSegment = ptrTransverseLift->m_ptrSegment;
				}
				else if (i == 2 && ptrSegment != NULL)
				{
					if (((CStageConveyorPallet *)ptrDevice)->m_relativePosition > 1.0
						|| ((CStageConveyorPallet *)ptrDevice)->m_relativePosition < 0.0)
					{
						a = 0.0;
					}
					else
					{
						a = ((CStageConveyorPallet *)ptrDevice)->m_relativePosition;
					}
				}

				m_pDoc->m_currentDevice = ptrDevice;
				m_pDoc->m_currentPart = ptrDevice->m_ptrPart;

				prevPtrParent = m_pDoc->YoDeviceHashLookup(m_pDoc->m_currentDevice->m_parent);
				prevPtrAttachedFromPart = m_pDoc->m_currentDevice->m_attachedFromPart;
				if (prevPtrParent != NULL && prevPtrAttachedFromPart == NULL)
				{
					prevPtrAttachedFromPart = prevPtrParent->m_ptrPart;
				}

				if (strcmp(ptrDevice->m_parent, m_name) != 0)
				{
					m_pDoc->YoDetachDevice();

					for (i = 0; i < 3; i++)

					{
						prevTranslate[i] = m_pDoc->m_currentDevice->m_ptrPart->m_translate[i];
						prevRotate[i] = m_pDoc->m_currentDevice->m_ptrPart->m_rotate[i];
					}

					m_pDoc->YoAttachDevice(m_ptrPart);
				}
				else
				{
					for (i = 0; i < 3; i++)
					{
						prevPosition[i] = ((CStageConveyorPallet *)ptrDevice)->m_position[i];
						prevPtrSegment = ((CStageConveyorPallet *)ptrDevice)->m_ptrSegment;
					}
				}

				YoRemovePallet((CStageConveyorPallet *)ptrDevice);

				for (i = 0; i < 3; i++)
				{
					((CStageConveyorPallet *)ptrDevice)->m_position[i]
						= ptrSegment->m_from[i] + ((ptrSegment->m_to[i] - ptrSegment->m_from[i]) * a);
				}

				i = YoCheckForPalletCollision(&ptrSegment, &((CStageConveyorPallet *)ptrDevice)->m_position[0],
					&((CStageConveyorPallet *)ptrDevice)->m_position[1],
					&((CStageConveyorPallet *)ptrDevice)->m_position[2]);

				YoInsertPallet((CStageConveyorPallet *)ptrDevice, ptrSegment);

				if (i == 1)
				{
					sprintf(buf, "%s %s %.6lf", ptrDevice->m_name,
						((CStageConveyorPallet *)ptrDevice)->m_ptrSegment->m_ptrPart->m_partName,
						((CStageConveyorPallet *)ptrDevice)->m_relativePosition);
				}
				else // collision occured
				{
					if (prevPtrParent != this)
					{
						m_pDoc->YoDetachDevice();
						for (i = 0; i < 3; i++)
						{
							m_pDoc->m_currentDevice->m_ptrPart->m_translate[i] = prevTranslate[i];
							m_pDoc->m_currentDevice->m_ptrPart->m_rotate[i] = prevRotate[i];
						}
						if (prevPtrParent != NULL)
						{
							sprintf(m_pDoc->m_currentDevice->m_parent, "%s", prevPtrParent->m_name);
							m_pDoc->YoAttachDevice(prevPtrAttachedFromPart);
						}
						else
						{
							// reattach device at world coords (rightmost position)
							for (curDevice = m_pDoc->m_deviceList;
								curDevice->m_right != NULL;
								curDevice = curDevice->m_right);
							curDevice->m_right = m_pDoc->m_currentDevice;
							m_pDoc->m_currentDevice->m_left = curDevice;
						}
					}
					else
					{
						YoRemovePallet((CStageConveyorPallet *)ptrDevice);
						for (i = 0; i < 3; i++)
						{
							((CStageConveyorPallet *)ptrDevice)->m_position[i] = prevPosition[i];
						}
						YoInsertPallet((CStageConveyorPallet *)ptrDevice, prevPtrSegment);
					}
					sprintf(buf, "X Pallet Collision");
				}


				if (m_pDoc->m_isMovement == 0
					&& m_pDoc->m_mode != YO_MODE_PLAY_SIM
					&& m_pDoc->m_scriptFastForward == FALSE)
				{
					pView->YoRender(YO_RENDER_LIGHT);
					pView->YoRender(YO_RENDER_FULL);
				}
			}
			else
			{
				sprintf(buf, "X");
			}
		}
		else if (i == 1)
		{
			ptrPart = m_pDoc->YoPartLookup(this, t);
			if (ptrPart != NULL
				//&& (ptrSensor = YoFindSensor(ptrPart)) != NULL)
				&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) == YO_CONVEYOR_SENSOR)
			{
				sprintf(buf, "%s %s %.6lf", ptrSensor->m_ptrPart->m_partName,
					ptrSensor->m_ptrSegment->m_ptrPart->m_partName, ptrSensor->m_relativePosition);
			}
			else if (ptrPart != NULL
				//&& (ptrStopGate = YoFindStopGate(ptrPart)) != NULL)
				&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) == YO_CONVEYOR_STOP_GATE)
			{
				sprintf(buf, "%s %s %.6lf", ptrStopGate->m_ptrPart->m_partName,
					ptrStopGate->m_ptrSegment->m_ptrPart->m_partName, ptrStopGate->m_relativePosition);
			}
			else if (ptrPart != NULL
				//&& (ptrTransverseLift = YoFindTransverseLift(ptrPart)) != NULL)
				&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) == YO_CONVEYOR_TRANSVERSE_LIFT)
			{
				sprintf(buf, "%s %s %.6lf", ptrTransverseLift->m_ptrPart->m_partName,
					ptrTransverseLift->m_ptrSegment->m_ptrPart->m_partName,
					ptrTransverseLift->m_relativePosition);	
			}
			else
			{
				sprintf(buf, "X");
			}
		}
		else
		{
			sprintf(buf, "X");
		}
	}

	else if ((toupper(buf[0]) == 'V' && toupper(buf[1]) == 'M')
		|| (toupper(buf[0]) == 'A' && toupper(buf[1]) == 'C'))
	{
		i = sscanf(buf, "%*s %lf %s", &a, &t);

		if (toupper(buf[0]) == 'V')
		{
			sprintf(command, "VMAX");
		}
		else
		{
			sprintf(command, "ACCEL");
		}

		if (i == 2)
		{
			ptrPart = m_pDoc->YoPartLookup(this, t);
			if (ptrPart != NULL
				&& YoFind(ptrPart, &ptrSegment, &ptrSensor, &ptrStopGate, &ptrTransverseLift) == YO_CONVEYOR_SEGMENT)
			{
				if (toupper(buf[0]) == 'V')
				{
					a = YO_MAX(a, 0.01);
					ptrSegment->m_maxVelocity = YO_MIN(a, 1000.0);
					sprintf(buf, "%.3lf %s", ptrSegment->m_maxVelocity, ptrSegment->m_ptrPart->m_partName);
				}
				else
				{
					a = YO_MAX(a, 0.01);
					ptrSegment->m_acceleration = YO_MIN(a, 10000.0);
					sprintf(buf, "%.3lf %s", ptrSegment->m_acceleration, ptrSegment->m_ptrPart->m_partName);
				}
			}
			else
			{
				sprintf(buf, "X");
			}
		}
		else if (i == 1)
		{
			for (curSegment = m_ptrSegment; curSegment != NULL; curSegment = curSegment->m_ptrNextSegment)
			{
				if (toupper(buf[0]) == 'V')
				{
					a = YO_MAX(a, 0.01);
					curSegment->m_maxVelocity = YO_MIN(a, 1000.0);
					if (curSegment->m_ptrNextSegment == NULL)
					{
						sprintf(buf, "%.3lf", curSegment->m_maxVelocity);
					}
				}
				else
				{
					a = YO_MAX(a, 0.01);
					curSegment->m_acceleration = YO_MIN(a, 10000.0);
					if (curSegment->m_ptrNextSegment == NULL)
					{
						sprintf(buf, "%.3lf", curSegment->m_acceleration);
					}
				}
			}
		}
		else
		{
			sprintf(buf, "X");
		}
	}

	if (buf[0] == 'X')
	{
		return FALSE;
	}
	else
	{
		sprintf(t, "| %s %s %s", m_name, command, buf);
		sprintf(buf, "%s", t);
	}

	return TRUE;
}


BOOL CStageConveyor::YoRemovePallet(CStageConveyorPallet *ptrPallet)
// removes a pallet from the conveyor data structure
// but does not delete the pallet device itself
{
	CStageConveyorSegment *curSegment;
	CStageConveyorPallet *curPallet;
	CStageConveyorSensor *curSensor;

	// test to make sure that pallet is attached to this conveyor
	for (curSegment = m_ptrSegment; curSegment != NULL; curSegment = curSegment->m_ptrNextSegment)
	{
		for (curPallet = curSegment->m_ptrPallet; curPallet != NULL && curPallet != ptrPallet;
			curPallet = curPallet->m_ptrNextPallet);

		if (curPallet != NULL)  // pallet found
		{
			if (ptrPallet->m_ptrNextPallet != NULL)
			{
				ptrPallet->m_ptrNextPallet->m_ptrPrevPallet = ptrPallet->m_ptrPrevPallet;
			}
			else  // last pallet in the list
			{
				curSegment->m_ptrLastPallet = ptrPallet->m_ptrPrevPallet;
			}

			if (ptrPallet->m_ptrPrevPallet != NULL)
			{
				ptrPallet->m_ptrPrevPallet->m_ptrNextPallet = ptrPallet->m_ptrNextPallet;
			}
			else  // first pallet in the list
			{
				curSegment->m_ptrPallet = ptrPallet->m_ptrNextPallet;
			}

			ptrPallet->m_moving = FALSE;
			ptrPallet->m_ptrNextPallet = NULL;
			ptrPallet->m_ptrPrevPallet = NULL;
			ptrPallet->m_ptrSegment = NULL;

			// check to see if a sensor is pointing to this pallet
			for (curSensor = curSegment->m_ptrSensor;
				curSensor != NULL && curSensor->m_ptrPallet != ptrPallet;
				curSensor = curSensor->m_ptrNextSensor);

			if (curSensor != NULL)
			{
				curSensor->m_ptrPallet = NULL;
			}

			//delete ptrPallet;

			return TRUE;
		}
	}
	return FALSE; // pallet not found
}

BOOL CStageConveyor::YoTransferPallet(CStageConveyorPallet *ptrPallet, CStageConveyorSegment *ptrSegment)
// removes a pallet from the current segment and inserts it in the
// segment ptrSegment.  Called during transverse lift operations.
// Note: the new position of pallet on ptrSegment must be set before calling this routine
{

	if (YoRemovePallet(ptrPallet))
	{
		if (YoInsertPallet(ptrPallet, ptrSegment))
		{
			return TRUE;
		}
	}

	return FALSE; // pallet not found
}


BOOL CStageConveyor::YoInsertPallet(CStageConveyorPallet *ptrPallet)
// inserts a pallet into the conveyor data structure when the attached to
// conveyor segment is not known (i.e. when reading a pallet in from file)
{
	CStageDevice *ptrParent;
	CStageConveyorSegment *ptrSegment;

	// make certain parent is this conveyor
	if (strcmp(ptrPallet->m_parent, "NONE") != 0)
	{
		ptrParent = m_pDoc->YoDeviceHashLookup(ptrPallet->m_parent);
		if (ptrParent == NULL || ptrParent->m_type != YO_CONVEYOR)
		{
			return FALSE;
		}
		if (this != (CStageConveyor *)ptrParent)
		{
			return FALSE;
		}
	}

	ptrPallet->m_position[0] = ptrPallet->m_ptrPart->m_translate[0] - m_offset[0];
	ptrPallet->m_position[1] = ptrPallet->m_ptrPart->m_translate[1] - m_offset[1];
	ptrPallet->m_position[2] = ptrPallet->m_ptrPart->m_translate[2] - m_offset[2];
	ptrSegment = YoFindSegment(&ptrPallet->m_position[0],
		&ptrPallet->m_position[1], &ptrPallet->m_position[2]);
	if (ptrSegment != NULL)
	{
		YoCheckForPalletCollision(&ptrSegment, &ptrPallet->m_position[0],
			&ptrPallet->m_position[1], &ptrPallet->m_position[2]);
		YoInsertPallet(ptrPallet, ptrSegment);
		//YoUpdatePalletGraphicsPosition(ptrPallet);
		return TRUE;
	}

	return FALSE;
}

BOOL CStageConveyor::YoInsertPallet(CStageConveyorPallet *ptrPallet, CStageConveyorSegment *ptrSegment)
// inserts a pallet into a known conveyor segment
// Note: x,y,z position of pallet must be a point on ptrSegment
{
	CStageConveyorSegment *curSegment;
	CStageConveyorPallet *curPallet;
	double x;
	double y;
	double z;

	for (curSegment = m_ptrSegment; curSegment != NULL && ptrSegment != curSegment;
		curSegment = curSegment->m_ptrNextSegment);
	if (curSegment == NULL)
	{
		return FALSE;
	}

	ptrPallet->m_startPosition[0] = ptrPallet->m_position[0];
	ptrPallet->m_startPosition[1] = ptrPallet->m_position[1];
	ptrPallet->m_startPosition[2] = ptrPallet->m_position[2];

	// compute relative position of pallet
	x = ptrPallet->m_position[0] - ptrSegment->m_from[0];
	y = ptrPallet->m_position[1] - ptrSegment->m_from[1];
	z = ptrPallet->m_position[2] - ptrSegment->m_from[2];
	ptrPallet->m_relativePosition = sqrt(x * x + y * y + z * z) / ptrSegment->m_distance;
	ptrPallet->m_ptrSegment = ptrSegment;

	YoUpdatePalletGraphicsPosition(ptrPallet);

	if (ptrSegment->m_ptrPallet == NULL)  // no pallets in this segment
	{
		ptrSegment->m_ptrPallet = ptrPallet;
		ptrSegment->m_ptrLastPallet = ptrPallet;
	}
	else
	{
		for (curPallet = ptrSegment->m_ptrPallet;
			curPallet != NULL && curPallet->m_relativePosition < ptrPallet->m_relativePosition;
			curPallet = curPallet->m_ptrNextPallet);

		if (curPallet == NULL) // insert at end of list
		{
			ptrSegment->m_ptrLastPallet->m_ptrNextPallet = ptrPallet;
			ptrPallet->m_ptrPrevPallet = ptrSegment->m_ptrLastPallet;
			ptrSegment->m_ptrLastPallet = ptrPallet;
		}
		else if (curPallet == ptrSegment->m_ptrPallet) // insert at beginning of list
		{
			curPallet->m_ptrPrevPallet = ptrPallet;
			ptrPallet->m_ptrNextPallet = curPallet;
			ptrSegment->m_ptrPallet = ptrPallet;
		}
		else // insert in middle of list
		{
			ptrPallet->m_ptrNextPallet = curPallet;
			ptrPallet->m_ptrPrevPallet = curPallet->m_ptrPrevPallet;
			ptrPallet->m_ptrPrevPallet->m_ptrNextPallet = ptrPallet;
			curPallet->m_ptrPrevPallet = ptrPallet;
		}
	}

	YoCheckSensors();

	return TRUE;
}


BOOL CStageConveyor::YoCheckForPalletCollision(CStageConveyorSegment **ptrSegment, double *px, double *py, double *pz)

{
	double x;
	double y;
	double z;
	double relPalletWidth = YO_CONVEYOR_PALLET_WIDTH / (*ptrSegment)->m_distance;
	double relPalletPosition;
	CStageConveyorPallet *collisionPallet = NULL;
	CStageConveyorPallet *curPallet;
	CStageConveyorTransverseLift *curTransverseLift;


	// compute relative position of pallet
	x = *px - (*ptrSegment)->m_from[0];
	y = *py - (*ptrSegment)->m_from[1];
	z = *pz - (*ptrSegment)->m_from[2];
	relPalletPosition = sqrt(x * x + y * y + z * z) / (*ptrSegment)->m_distance;

	// first check if pallet is over a transverse lift
	for (curTransverseLift = (*ptrSegment)->m_ptrTransverseLift; curTransverseLift != NULL;
		curTransverseLift = curTransverseLift->m_ptrNextTransverseLift)
	{
		if (relPalletPosition + relPalletWidth > curTransverseLift->m_relativePosition
			&& relPalletPosition - relPalletWidth < curTransverseLift->m_relativePosition
			&& curTransverseLift->m_up == TRUE)
		{
			if (curTransverseLift->m_ptrTransverseSegment != NULL)
			{
				*px = curTransverseLift->m_position[0];
				*py = curTransverseLift->m_position[1];
				*pz = curTransverseLift->m_position[2] + YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
				*ptrSegment = curTransverseLift->m_ptrTransverseSegment;
				x = *px - (*ptrSegment)->m_from[0];
				y = *py - (*ptrSegment)->m_from[1];
				z = *pz - (*ptrSegment)->m_from[2];
				relPalletPosition = sqrt(x * x + y * y + z * z) / (*ptrSegment)->m_distance;
				relPalletWidth = YO_CONVEYOR_PALLET_WIDTH / (*ptrSegment)->m_distance;
			}
			break;
		}
		else if (relPalletPosition + relPalletWidth > curTransverseLift->m_relativePosition
			&& relPalletPosition - relPalletWidth < curTransverseLift->m_relativePosition
			&& curTransverseLift->m_up == FALSE)
		{
			if (curTransverseLift->m_ptrTransverseSegment == NULL)
			{
				if (curTransverseLift->m_relativePosition == 0.0)
				{
					relPalletPosition = YO_CONVEYOR_PALLET_WIDTH / (*ptrSegment)->m_distance;
				}
				else
				{
					relPalletPosition = 1.0f - (YO_CONVEYOR_PALLET_WIDTH / (*ptrSegment)->m_distance);
				}
				*px = (*ptrSegment)->m_from[0] + (((*ptrSegment)->m_to[0] - (*ptrSegment)->m_from[0]) * relPalletPosition);
				*py = (*ptrSegment)->m_from[1] + (((*ptrSegment)->m_to[1] - (*ptrSegment)->m_from[1]) * relPalletPosition);
				*pz = (*ptrSegment)->m_from[2] + (((*ptrSegment)->m_to[2] - (*ptrSegment)->m_from[2]) * relPalletPosition);
			}
			break;
		}
	}


	for (curPallet = (*ptrSegment)->m_ptrPallet; curPallet != NULL && collisionPallet == NULL;
		curPallet = curPallet->m_ptrNextPallet)
	{
		if (relPalletPosition + relPalletWidth > curPallet->m_relativePosition
			&& relPalletPosition - relPalletWidth < curPallet->m_relativePosition)
		{
			collisionPallet = curPallet;
		}
	}

	if (collisionPallet != NULL)
	{
		if (relPalletPosition <= collisionPallet->m_relativePosition)
		{
			// search towards beginning of segment
			relPalletPosition = collisionPallet->m_relativePosition;
			for (curPallet = collisionPallet; curPallet != NULL && relPalletPosition >= 0.0f;
				curPallet = curPallet->m_ptrPrevPallet)
			{
				if (relPalletPosition + relPalletWidth > curPallet->m_relativePosition
					&& relPalletPosition - relPalletWidth < curPallet->m_relativePosition)
				{
					relPalletPosition = curPallet->m_relativePosition - relPalletWidth;
					if (YoCheckTransverseLift(*ptrSegment, &relPalletPosition))
					{
						relPalletPosition -= relPalletWidth;
					}
				}
				else if (YoCheckTransverseLift(*ptrSegment, &relPalletPosition))
				{
					relPalletPosition -= relPalletWidth;
				}
				else
				{
					break;
				}
			}
			if (relPalletPosition < 0.0f)
			{
				// search towards end of segment
				relPalletPosition = collisionPallet->m_relativePosition;
				for (curPallet = collisionPallet; curPallet != NULL && relPalletPosition <= 1.0f;
					curPallet = curPallet->m_ptrNextPallet)
				{
					if (relPalletPosition + relPalletWidth > curPallet->m_relativePosition
						&& relPalletPosition - relPalletWidth < curPallet->m_relativePosition)
					{
						relPalletPosition = curPallet->m_relativePosition + relPalletWidth;
						if (YoCheckTransverseLift(*ptrSegment, &relPalletPosition))
						{
							relPalletPosition += relPalletWidth;
						}
					}
					else if (YoCheckTransverseLift(*ptrSegment, &relPalletPosition))
					{
						relPalletPosition += relPalletWidth;
					}
					else
					{
						break;
					}
				}
				if (relPalletPosition > 1.0f)
				{
					return FALSE;
				}
				else // empty position found
				{
					*px = (*ptrSegment)->m_from[0] + (((*ptrSegment)->m_to[0] - (*ptrSegment)->m_from[0]) * relPalletPosition);
					*py = (*ptrSegment)->m_from[1] + (((*ptrSegment)->m_to[1] - (*ptrSegment)->m_from[1]) * relPalletPosition);
					*pz = (*ptrSegment)->m_from[2] + (((*ptrSegment)->m_to[2] - (*ptrSegment)->m_from[2]) * relPalletPosition);
				}

			}
			else  // empty position found
			{
				*px = (*ptrSegment)->m_from[0] + (((*ptrSegment)->m_to[0] - (*ptrSegment)->m_from[0]) * relPalletPosition);
				*py = (*ptrSegment)->m_from[1] + (((*ptrSegment)->m_to[1] - (*ptrSegment)->m_from[1]) * relPalletPosition);
				*pz = (*ptrSegment)->m_from[2] + (((*ptrSegment)->m_to[2] - (*ptrSegment)->m_from[2]) * relPalletPosition);
			}
		}

		else // ptrPallet->m_relativePosition > collisionPallet->m_relativePosition
		{
			// search towards end of segment
			relPalletPosition = collisionPallet->m_relativePosition;
			for (curPallet = collisionPallet; curPallet != NULL && relPalletPosition <= 1.0f;
				curPallet = curPallet->m_ptrNextPallet)
			{
				if (relPalletPosition + relPalletWidth > curPallet->m_relativePosition
					&& relPalletPosition - relPalletWidth < curPallet->m_relativePosition)
				{
					relPalletPosition = curPallet->m_relativePosition + relPalletWidth;
					if (YoCheckTransverseLift(*ptrSegment, &relPalletPosition))
					{
						relPalletPosition += relPalletWidth;
					}
				}
				else if (YoCheckTransverseLift(*ptrSegment, &relPalletPosition))
				{
					relPalletPosition += relPalletWidth;
				}
				else
				{
					break;
				}
			}
			if (relPalletPosition > 1.0f)
			{
				// search towards beginning of segment
				relPalletPosition = collisionPallet->m_relativePosition;
				for (curPallet = collisionPallet; curPallet != NULL && relPalletPosition >= 0.0f;
					curPallet = curPallet->m_ptrPrevPallet)
				{
					if (relPalletPosition + relPalletWidth > curPallet->m_relativePosition
						&& relPalletPosition - relPalletWidth < curPallet->m_relativePosition)
					{
						relPalletPosition = curPallet->m_relativePosition - relPalletWidth;
						if (YoCheckTransverseLift(*ptrSegment, &relPalletPosition))
						{
							relPalletPosition -= relPalletWidth;
						}
					}
					else if (YoCheckTransverseLift(*ptrSegment, &relPalletPosition))
					{
						relPalletPosition -= relPalletWidth;
					}
					else
					{
						break;
					}
				}
				if (relPalletPosition < 0.0f)
				{
					return FALSE;
				}
				else // empty position found
				{
					*px = (*ptrSegment)->m_from[0] + (((*ptrSegment)->m_to[0] - (*ptrSegment)->m_from[0]) * relPalletPosition);
					*py = (*ptrSegment)->m_from[1] + (((*ptrSegment)->m_to[1] - (*ptrSegment)->m_from[1]) * relPalletPosition);
					*pz = (*ptrSegment)->m_from[2] + (((*ptrSegment)->m_to[2] - (*ptrSegment)->m_from[2]) * relPalletPosition);
				}

			}
			else  // empty position found
			{
				*px = (*ptrSegment)->m_from[0] + (((*ptrSegment)->m_to[0] - (*ptrSegment)->m_from[0]) * relPalletPosition);
				*py = (*ptrSegment)->m_from[1] + (((*ptrSegment)->m_to[1] - (*ptrSegment)->m_from[1]) * relPalletPosition);
				*pz = (*ptrSegment)->m_from[2] + (((*ptrSegment)->m_to[2] - (*ptrSegment)->m_from[2]) * relPalletPosition);
			}
		}
	}
	return TRUE;
}


BOOL CStageConveyor::YoCheckTransverseLift(CStageConveyorSegment *ptrSegment, double *relPalletPosition)
// when checking for pallet collisions it is necessary to see if pallet is over a transverse lift
// in an undesirable position.  If so modify the pallet position and return TRUE
{
	CStageConveyorTransverseLift *curTransverseLift;
	double relPalletWidth = YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance;
	BOOL retVal = FALSE;

	for (curTransverseLift = ptrSegment->m_ptrTransverseLift; curTransverseLift != NULL;
		curTransverseLift = curTransverseLift->m_ptrNextTransverseLift)
	{
		if (*relPalletPosition + relPalletWidth > curTransverseLift->m_relativePosition
			&& *relPalletPosition - relPalletWidth < curTransverseLift->m_relativePosition)
		{
			if (curTransverseLift->m_ptrTransverseSegment != NULL && curTransverseLift->m_up == TRUE)
			{
				*relPalletPosition = curTransverseLift->m_relativePosition;
				retVal = TRUE;
			}
			else if (curTransverseLift->m_ptrTransverseSegment == NULL && curTransverseLift->m_up == FALSE)
			{
				*relPalletPosition = curTransverseLift->m_relativePosition;
				retVal = TRUE;
			}
		}
	}
	return retVal;

}


BOOL CStageConveyor::YoInsertSegment(CStageConveyorSegment *ptrSegment)
{
	CStageConveyorSegment *prevSegment;
	CStageConveyorSegment *curSegment;
	double x;
	double y;
	double z;

	// compute distance of the segment
	x = ptrSegment->m_to[0] - ptrSegment->m_from[0];
	y = ptrSegment->m_to[1] - ptrSegment->m_from[1];
	z = ptrSegment->m_to[2] - ptrSegment->m_from[2];
	ptrSegment->m_distance = sqrt(x * x + y * y + z * z);

	if (m_ptrSegment == NULL)  // no segments in list, insert at beginning of list
	{
		m_ptrSegment = ptrSegment;
		return TRUE;
	}

	for (curSegment = m_ptrSegment; curSegment != NULL;
		curSegment = curSegment->m_ptrNextSegment)
	{
		prevSegment = curSegment;
	}

	// insert ptrSegment at end of list
	ptrSegment->m_ptrPrevSegment = prevSegment;
	prevSegment->m_ptrNextSegment = ptrSegment;

	return TRUE;
}


BOOL CStageConveyor::YoInsertSensor(CStageConveyorSensor *ptrSensor)
{
	CStageConveyorSegment *ptrSegment;
	CStageConveyorSensor *curSensor;
	double x;
	double y;
	double z;

	ptrSegment = YoFindSegment(&ptrSensor->m_position[0],
		&ptrSensor->m_position[1], &ptrSensor->m_position[2]);
	if (ptrSegment == NULL)
	{
		return FALSE;
	}

	ptrSensor->m_ptrSegment = ptrSegment;

	// compute relative position of sensor
	x = ptrSensor->m_position[0] - ptrSegment->m_from[0];
	y = ptrSensor->m_position[1] - ptrSegment->m_from[1];
	z = ptrSensor->m_position[2] - ptrSegment->m_from[2];
	ptrSensor->m_relativePosition = sqrt(x * x + y * y + z * z) / ptrSegment->m_distance; 

	if (ptrSegment->m_ptrSensor == NULL)  // no sensors in this segment
	{
		ptrSegment->m_ptrSensor = ptrSensor;
		ptrSegment->m_ptrLastSensor = ptrSensor;
		return TRUE;
	}

	for (curSensor = ptrSegment->m_ptrSensor;
		curSensor != NULL && curSensor->m_relativePosition < ptrSensor->m_relativePosition;
		curSensor = curSensor->m_ptrNextSensor);

	if (curSensor == NULL) // insert at end of list
	{
		ptrSegment->m_ptrLastSensor->m_ptrNextSensor = ptrSensor;
		ptrSensor->m_ptrPrevSensor = ptrSegment->m_ptrLastSensor;
		ptrSegment->m_ptrLastSensor = ptrSensor;
	}
	else if (curSensor == ptrSegment->m_ptrSensor) // insert at beginning of list
	{
		curSensor->m_ptrPrevSensor = ptrSensor;
		ptrSensor->m_ptrNextSensor = curSensor;
		ptrSegment->m_ptrSensor = ptrSensor;
	}
	else // insert in middle of list
	{
		ptrSensor->m_ptrNextSensor = curSensor;
		ptrSensor->m_ptrPrevSensor = curSensor->m_ptrPrevSensor;
		ptrSensor->m_ptrPrevSensor->m_ptrNextSensor = ptrSensor;
		curSensor->m_ptrPrevSensor = ptrSensor;
	}

	return TRUE;
}


BOOL CStageConveyor::YoSetStopGates()
{
	CStageConveyorSegment *curSegment;
	CStageConveyorStopGate *curStopGate;

	for (curSegment = m_ptrSegment; curSegment != NULL; curSegment = curSegment->m_ptrNextSegment)
	{
		for (curStopGate = curSegment->m_ptrStopGate; curStopGate != NULL; curStopGate = curStopGate->m_ptrNextStopGate)
		{
			if (curStopGate->m_ptrPart->m_down != NULL)
			{
				if (curStopGate->m_stop == TRUE)
				{
					curStopGate->m_ptrPart->m_down->m_translate[2] = 0.0f;
				}
				else
				{
					curStopGate->m_ptrPart->m_down->m_translate[2] = -20.0f;
				}
			}
		}
	}

	return TRUE;
}


BOOL CStageConveyor::YoInsertStopGate(CStageConveyorStopGate *ptrStopGate)
{
	CStageConveyorSegment *ptrSegment;
	CStageConveyorStopGate *curStopGate;
	double x;
	double y;
	double z;

	ptrSegment = YoFindSegment(&ptrStopGate->m_position[0],
		&ptrStopGate->m_position[1], &ptrStopGate->m_position[2]);
	if (ptrSegment == NULL)
	{
		return FALSE;
	}

	ptrStopGate->m_ptrSegment = ptrSegment;

	// compute relative position of stop gate
	x = ptrStopGate->m_position[0] - ptrSegment->m_from[0];
	y = ptrStopGate->m_position[1] - ptrSegment->m_from[1];
	z = ptrStopGate->m_position[2] - ptrSegment->m_from[2];
	ptrStopGate->m_relativePosition = sqrt(x * x + y * y + z * z) / ptrSegment->m_distance; 

	if (ptrSegment->m_ptrStopGate == NULL)  // no stop gates in this segment
	{
		ptrSegment->m_ptrStopGate = ptrStopGate;
		ptrSegment->m_ptrLastStopGate = ptrStopGate;
		return TRUE;
	}

	for (curStopGate = ptrSegment->m_ptrStopGate;
		curStopGate != NULL && curStopGate->m_relativePosition < ptrStopGate->m_relativePosition;
		curStopGate = curStopGate->m_ptrNextStopGate);

	if (curStopGate == NULL) // insert at end of list
	{
		ptrSegment->m_ptrLastStopGate->m_ptrNextStopGate = ptrStopGate;
		ptrStopGate->m_ptrPrevStopGate = ptrSegment->m_ptrLastStopGate;
		ptrSegment->m_ptrLastStopGate = ptrStopGate;
	}
	else if (curStopGate == ptrSegment->m_ptrStopGate) // insert at beginning of list
	{
		curStopGate->m_ptrPrevStopGate = ptrStopGate;
		ptrStopGate->m_ptrNextStopGate = curStopGate;
		ptrSegment->m_ptrStopGate = ptrStopGate;
	}
	else // insert in middle of list
	{
		ptrStopGate->m_ptrNextStopGate = curStopGate;
		ptrStopGate->m_ptrPrevStopGate = curStopGate->m_ptrPrevStopGate;
		ptrStopGate->m_ptrPrevStopGate->m_ptrNextStopGate = ptrStopGate;
		curStopGate->m_ptrPrevStopGate = ptrStopGate;
	}

	return TRUE;
}

BOOL CStageConveyor::YoInsertTransverseLift(CStageConveyorTransverseLift *ptrTransverseLift)
{
	CStageConveyorSegment *ptrSegment;
	CStageConveyorSegment *ptrTransverseSegment;
	CStageConveyorTransverseLift *curTransverseLift;
	CStageConveyorTransverseLift *newTransverseLift;
	double x;
	double y;
	double z;

	ptrSegment = YoFindSegment(&ptrTransverseLift->m_position[0],
		&ptrTransverseLift->m_position[1], &ptrTransverseLift->m_position[2]);
	ptrTransverseLift->m_position[2] += YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
	ptrTransverseSegment = YoFindSegment(&ptrTransverseLift->m_position[0],
		&ptrTransverseLift->m_position[1], &ptrTransverseLift->m_position[2]);
	ptrTransverseLift->m_position[2] -= YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
	if (ptrSegment == NULL || ptrTransverseSegment == NULL)
	{
		return FALSE;
	}

	ptrTransverseLift->m_ptrSegment = ptrSegment;
	ptrTransverseLift->m_ptrTransverseSegment = ptrTransverseSegment;

	// compute relative position of transverse lift on the primary segment
	x = ptrTransverseLift->m_position[0] - ptrSegment->m_from[0];
	y = ptrTransverseLift->m_position[1] - ptrSegment->m_from[1];
	z = ptrTransverseLift->m_position[2] - ptrSegment->m_from[2];
	ptrTransverseLift->m_relativePosition = sqrt(x * x + y * y + z * z) / ptrSegment->m_distance; 

	if (ptrSegment->m_ptrTransverseLift == NULL)  // no transverse lifts in this segment
	{
		ptrSegment->m_ptrTransverseLift = ptrTransverseLift;
		ptrSegment->m_ptrLastTransverseLift = ptrTransverseLift;
	}
	else
	{
		for (curTransverseLift = ptrSegment->m_ptrTransverseLift;
			curTransverseLift != NULL && curTransverseLift->m_relativePosition < ptrTransverseLift->m_relativePosition;
			curTransverseLift = curTransverseLift->m_ptrNextTransverseLift);

		if (curTransverseLift == NULL) // insert at end of list
		{
			ptrSegment->m_ptrLastTransverseLift->m_ptrNextTransverseLift = ptrTransverseLift;
			ptrTransverseLift->m_ptrPrevTransverseLift = ptrSegment->m_ptrLastTransverseLift;
			ptrSegment->m_ptrLastTransverseLift = ptrTransverseLift;
		}
		else if (curTransverseLift == ptrSegment->m_ptrTransverseLift) // insert at beginning of list
		{
			curTransverseLift->m_ptrPrevTransverseLift = ptrTransverseLift;
			ptrTransverseLift->m_ptrNextTransverseLift = curTransverseLift;
			ptrSegment->m_ptrTransverseLift = ptrTransverseLift;
		}
		else // insert in middle of list
		{
			ptrTransverseLift->m_ptrNextTransverseLift = curTransverseLift;
			ptrTransverseLift->m_ptrPrevTransverseLift = curTransverseLift->m_ptrPrevTransverseLift;
			ptrTransverseLift->m_ptrPrevTransverseLift->m_ptrNextTransverseLift = ptrTransverseLift;
			curTransverseLift->m_ptrPrevTransverseLift = ptrTransverseLift;
		}
	}


	// put a new transverse lift object on the transverse segment
	newTransverseLift = new CStageConveyorTransverseLift();
	newTransverseLift->m_forwardBlocking = ptrTransverseLift->m_forwardBlocking;
	newTransverseLift->m_reverseBlocking = ptrTransverseLift->m_reverseBlocking;
	newTransverseLift->m_up = ptrTransverseLift->m_up;
	newTransverseLift->m_position[0] = ptrTransverseLift->m_position[0];
	newTransverseLift->m_position[1] = ptrTransverseLift->m_position[1];
	newTransverseLift->m_position[2] = ptrTransverseLift->m_position[2] + YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
	newTransverseLift->m_ptrPart = NULL;
	newTransverseLift->m_ptrTransverseSegment = NULL;

	// compute relative position of transverse lift on the transverse segment
	// by design can only be 0.0 or 1.0
	if (newTransverseLift->m_position[0] == ptrTransverseSegment->m_to[0]
		&& newTransverseLift->m_position[1] == ptrTransverseSegment->m_to[1])
	{
		newTransverseLift->m_relativePosition = 1.0f;
	}
	else
	{
		newTransverseLift->m_relativePosition = 0.0f;
	}

	if (ptrTransverseSegment->m_ptrTransverseLift == NULL)  // no transverse lifts in this segment
	{
		ptrTransverseSegment->m_ptrTransverseLift = newTransverseLift;
		ptrTransverseSegment->m_ptrLastTransverseLift = newTransverseLift;
	}
	else
	{
		for (curTransverseLift = ptrTransverseSegment->m_ptrTransverseLift;
			curTransverseLift != NULL && curTransverseLift->m_relativePosition < newTransverseLift->m_relativePosition;
			curTransverseLift = curTransverseLift->m_ptrNextTransverseLift);

		if (curTransverseLift == NULL) // insert at end of list
		{
			ptrTransverseSegment->m_ptrLastTransverseLift->m_ptrNextTransverseLift = newTransverseLift;
			newTransverseLift->m_ptrPrevTransverseLift = ptrTransverseSegment->m_ptrLastTransverseLift;
			ptrTransverseSegment->m_ptrLastTransverseLift = newTransverseLift;
		}
		else if (curTransverseLift == ptrTransverseSegment->m_ptrTransverseLift) // insert at beginning of list
		{
			curTransverseLift->m_ptrPrevTransverseLift = newTransverseLift;
			newTransverseLift->m_ptrNextTransverseLift = curTransverseLift;
			ptrSegment->m_ptrTransverseLift = newTransverseLift;
		}
		else // insert in middle of list
		{
			newTransverseLift->m_ptrNextTransverseLift = curTransverseLift;
			newTransverseLift->m_ptrPrevTransverseLift = curTransverseLift->m_ptrPrevTransverseLift;
			newTransverseLift->m_ptrPrevTransverseLift->m_ptrNextTransverseLift = newTransverseLift;
			curTransverseLift->m_ptrPrevTransverseLift = newTransverseLift;
		}
	}

	ptrTransverseLift->m_ptrMirrorTransverseLift = newTransverseLift;
	return TRUE;
}


BOOL CStageConveyor::YoClone(CStageConveyor *ptrConveyorClone)
{
	CStageConveyorSegment *curSegment;
	CStageConveyorSegment *ptrSegment;
	CStageConveyorSensor *curSensor;
	CStageConveyorSensor *ptrSensor;
	CStageConveyorStopGate *curStopGate;
	CStageConveyorStopGate *ptrStopGate;
	CStageConveyorTransverseLift *curTransverseLift;
	CStageConveyorTransverseLift *ptrTransverseLift;

	ptrConveyorClone->m_offset[0] = m_offset[0];
	ptrConveyorClone->m_offset[1] = m_offset[1];
	ptrConveyorClone->m_offset[2] = m_offset[2];

	for (curSegment = m_ptrSegment; curSegment != NULL; curSegment = curSegment->m_ptrNextSegment)
	{
		ptrSegment = new CStageConveyorSegment();
		ptrSegment->m_acceleration = curSegment->m_acceleration;
		ptrSegment->m_from[0] = curSegment->m_from[0];
		ptrSegment->m_from[1] = curSegment->m_from[1];
		ptrSegment->m_from[2] = curSegment->m_from[2];
		ptrSegment->m_to[0] = curSegment->m_to[0];
		ptrSegment->m_to[1] = curSegment->m_to[1];
		ptrSegment->m_to[2] = curSegment->m_to[2];
		ptrSegment->m_speed = curSegment->m_speed;
		ptrSegment->m_maxVelocity = curSegment->m_maxVelocity;
		ptrSegment->m_ptrPart = curSegment->m_ptrPart;
		ptrConveyorClone->YoInsertSegment(ptrSegment);

		for (curSensor = curSegment->m_ptrSensor; curSensor != NULL;
			curSensor = curSensor->m_ptrNextSensor)
		{
			ptrSensor = new CStageConveyorSensor();
			ptrSensor->m_position[0] = curSensor->m_position[0];
			ptrSensor->m_position[1] = curSensor->m_position[1];
			ptrSensor->m_position[2] = curSensor->m_position[2];
			ptrSensor->m_ptrPart = curSensor->m_ptrPart;
			ptrConveyorClone->YoInsertSensor(ptrSensor);
		}
		for (curStopGate = curSegment->m_ptrStopGate; curStopGate != NULL;
			curStopGate = curStopGate->m_ptrNextStopGate)
		{
			ptrStopGate = new CStageConveyorStopGate();
			ptrStopGate->m_forward = curStopGate->m_forward;
			ptrStopGate->m_position[0] = curStopGate->m_position[0];
			ptrStopGate->m_position[1] = curStopGate->m_position[1];
			ptrStopGate->m_position[2] = curStopGate->m_position[2];
			ptrStopGate->m_ptrPart = curStopGate->m_ptrPart;
			ptrConveyorClone->YoInsertStopGate(ptrStopGate);
		}
		for (curTransverseLift = curSegment->m_ptrTransverseLift; curTransverseLift != NULL;
			curTransverseLift = curTransverseLift->m_ptrNextTransverseLift)
		{
			if (curTransverseLift->m_ptrPart != NULL)
			{
				ptrTransverseLift = new CStageConveyorTransverseLift();
				ptrTransverseLift->m_forwardBlocking = curTransverseLift->m_forwardBlocking;
				ptrTransverseLift->m_reverseBlocking = curTransverseLift->m_reverseBlocking;
				ptrTransverseLift->m_position[0] = curTransverseLift->m_position[0];
				ptrTransverseLift->m_position[1] = curTransverseLift->m_position[1];
				ptrTransverseLift->m_position[2] = curTransverseLift->m_position[2];
				ptrTransverseLift->m_ptrPart = curTransverseLift->m_ptrPart;
				ptrConveyorClone->YoInsertTransverseLift(ptrTransverseLift);
			}
		}
	}

	return TRUE;
}


BOOL CStageConveyor::YoClone(CStagePart *ptrPart, CStagePart *ptrPartClone)
// called after conveyor device has been cloned
// switches part pointers to point at the cloned part instead of the original
{
	CStageConveyorSegment *curSegment;
	CStageConveyorSensor *curSensor;
	CStageConveyorStopGate *curStopGate;
	CStageConveyorTransverseLift *curTransverseLift;

	for (curSegment = m_ptrSegment; curSegment != NULL; curSegment = curSegment->m_ptrNextSegment)
	{
		if (curSegment->m_ptrPart == ptrPart)
		{
			curSegment->m_ptrPart = ptrPartClone;
			return TRUE;
		}

		for (curSensor = curSegment->m_ptrSensor; curSensor != NULL;
			curSensor = curSensor->m_ptrNextSensor)
		{
			if (curSensor->m_ptrPart == ptrPart)
			{
				curSensor->m_ptrPart = ptrPartClone;
				return TRUE;
			}
		}
		for (curStopGate = curSegment->m_ptrStopGate; curStopGate != NULL;
			curStopGate = curStopGate->m_ptrNextStopGate)
		{
			if (curStopGate->m_ptrPart == ptrPart)
			{
				curStopGate->m_ptrPart = ptrPartClone;
				return TRUE;
			}

		}
		for (curTransverseLift = curSegment->m_ptrTransverseLift; curTransverseLift != NULL;
			curTransverseLift = curTransverseLift->m_ptrNextTransverseLift)
		{
			if (curTransverseLift->m_ptrPart == ptrPart)
			{
				curTransverseLift->m_ptrPart = ptrPartClone;
				return TRUE;
			}

		}
	}

	return FALSE;
}

BOOL CStageConveyor::YoCalculateEndPositionOfPallets()
{
	CStageConveyorSegment *curSegment;

	for (curSegment = m_ptrSegment; curSegment != NULL; curSegment = curSegment->m_ptrNextSegment)
	{
		YoCalculateEndPositionOfPallets(curSegment);
	}

	return TRUE;
}

BOOL CStageConveyor::YoEStop()
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	CStageConveyorSegment *ptrSegment;
	CStageConveyorTransverseLift *ptrTransverseLift;
	CStageConveyorPallet *ptrPallet;
	double z;
	CWnd *pCBox;

	if (pMainFrame->m_conveyorDlgActive)
	{
		pCBox = (CComboBox*)pMainFrame->m_conveyorDialog->GetDlgItem(IDC_CONVEYOR_FORWARD);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)pMainFrame->m_conveyorDialog->GetDlgItem(IDC_CONVEYOR_REVERSE);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)pMainFrame->m_conveyorDialog->GetDlgItem(IDC_CONVEYOR_PAUSE);
		((CButton *)pCBox)->SetCheck(1);

		pCBox = (CComboBox*)pMainFrame->m_conveyorDialog->GetDlgItem(IDC_CONVEYOR_MAX_SPEED);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox*)pMainFrame->m_conveyorDialog->GetDlgItem(IDC_CONVEYOR_REL_SPEED);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
		pCBox = (CComboBox*)pMainFrame->m_conveyorDialog->GetDlgItem(IDC_CONVEYOR_ACCEL);
		((CEdit *)pCBox)->SetReadOnly(FALSE);
		pCBox->UpdateWindow();
	}

	for (ptrSegment = m_ptrSegment; ptrSegment != NULL; ptrSegment = ptrSegment->m_ptrNextSegment)
	{
		ptrSegment->m_moving = FALSE;
		ptrSegment->m_changingDirection = FALSE;
		ptrSegment->m_curVelocity = 0.0f;
		ptrSegment->m_finalVelocity = 0.0f;
		ptrSegment->m_initialVelocity = 0.0f;

		for (ptrTransverseLift = ptrSegment->m_ptrTransverseLift; ptrTransverseLift != NULL;
			ptrTransverseLift = ptrTransverseLift->m_ptrNextTransverseLift)
		{
			if (ptrTransverseLift->m_ptrPart != NULL)
			{
				ptrTransverseLift->m_inMotion = FALSE;
				if (ptrTransverseLift->m_up)
				{
					z = YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
				}
				else
				{
					z = 0.0f;
				}
				ptrTransverseLift->m_ptrPart->m_translate[2]
					= m_offset[2] - 6.35 + ptrTransverseLift->m_position[2] + z;
			}
		}
		for (ptrPallet = ptrSegment->m_ptrPallet; ptrPallet != NULL;
			ptrPallet = ptrPallet->m_ptrNextPallet)
		{
			ptrPallet->m_moving = FALSE;
			YoUpdatePalletGraphicsPosition(ptrPallet);
		}
	}

	if (m_moving)
	{
		m_moving = 0;
		m_pDoc->m_isMovement--;
	}

	return TRUE;
}

double CStageConveyor::YoCalculateEndPositionOfPallets(CStageConveyorSegment *ptrSegment)
{
	CStageConveyorPallet *curPallet;
	CStageConveyorStopGate *curStopGate;
	CStageConveyorTransverseLift *curTransverseLift;
	double endRelPosition;
	double relDistance;
	double minRelDistance;
	double minDistance;
	double minTime;
	double taccel;
	double daccel;
	double endPosition[3];
	double x;
	double y;
	double z;

	if (ptrSegment->m_ptrPallet == NULL)
	{
		return 0.0f;
	}

	if (ptrSegment->m_directionForward == TRUE)  // conveyor moving forward
	{
		endRelPosition = 1.0f;
		endPosition[0] = ptrSegment->m_to[0];
		endPosition[1] = ptrSegment->m_to[1];
		endPosition[2] = ptrSegment->m_to[2];
		
		for (curPallet = ptrSegment->m_ptrLastPallet; curPallet != NULL; curPallet = curPallet->m_ptrPrevPallet)
		{
			minRelDistance = endRelPosition - curPallet->m_relativePosition;

			relDistance = minRelDistance;
			for (curStopGate = ptrSegment->m_ptrLastStopGate; curStopGate != NULL && relDistance > 0.0f;
				curStopGate = curStopGate->m_ptrPrevStopGate)
			{
				if (curStopGate->m_forward == TRUE && curStopGate->m_stop == TRUE)
				{
					relDistance = curStopGate->m_relativePosition - curPallet->m_relativePosition;
					if (relDistance >= 0.0f && relDistance < minRelDistance)
					{
						minRelDistance = relDistance;
						endPosition[0] = curStopGate->m_position[0];
						endPosition[1] = curStopGate->m_position[1];
						endPosition[2] = curStopGate->m_position[2];
						endRelPosition = curStopGate->m_relativePosition;
					}
				}
			}

			relDistance = minRelDistance;
			for (curTransverseLift = ptrSegment->m_ptrLastTransverseLift; curTransverseLift != NULL && relDistance > 0.0f;
				curTransverseLift = curTransverseLift->m_ptrPrevTransverseLift)
			{
				if (curTransverseLift->m_ptrPart != NULL
					&& curTransverseLift->m_relativePosition != curPallet->m_relativePosition
					&& (curTransverseLift->m_up == TRUE || curTransverseLift->m_reverseBlocking == TRUE
					|| curTransverseLift->m_inMotion == TRUE))
				{
					relDistance = (curTransverseLift->m_relativePosition - (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance))
						- curPallet->m_relativePosition;
					if (relDistance >= 0.0f && relDistance < minRelDistance)
					{
						minRelDistance = relDistance;
						endPosition[0] = ptrSegment->m_from[0] + (ptrSegment->m_to[0] - ptrSegment->m_from[0])
							* (curTransverseLift->m_relativePosition - (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance));
						endPosition[1] = ptrSegment->m_from[1] + (ptrSegment->m_to[1] - ptrSegment->m_from[1])
							* (curTransverseLift->m_relativePosition - (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance));
						endPosition[2] = ptrSegment->m_from[2] + (ptrSegment->m_to[2] - ptrSegment->m_from[2])
							* (curTransverseLift->m_relativePosition - (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance));
						endRelPosition = curTransverseLift->m_relativePosition
							- (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance);
					}
				}
				else if ((curTransverseLift->m_ptrPart == NULL
					&& curTransverseLift->m_relativePosition != curPallet->m_relativePosition)
					|| (curTransverseLift->m_ptrPart != NULL
					&& curTransverseLift->m_forwardBlocking == TRUE))
				{
					relDistance = curTransverseLift->m_relativePosition - curPallet->m_relativePosition;
					if (relDistance >= 0.0f && relDistance < minRelDistance)
					{
						minRelDistance = relDistance;
						endPosition[0] = curTransverseLift->m_position[0];
						endPosition[1] = curTransverseLift->m_position[1];
						endPosition[2] = curTransverseLift->m_position[2];
						endRelPosition = curTransverseLift->m_relativePosition;
					}
				}
			}

			curPallet->m_endPosition[0] = endPosition[0];
			curPallet->m_endPosition[1] = endPosition[1];
			curPallet->m_endPosition[2] = endPosition[2];

			x = curPallet->m_endPosition[0] - curPallet->m_startPosition[0];
			y = curPallet->m_endPosition[1] - curPallet->m_startPosition[1];
			z = curPallet->m_endPosition[2] - curPallet->m_startPosition[2];
			curPallet->m_distance = sqrt(x * x + y * y + z * z);

			endRelPosition -= (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance);
			endPosition[0] = ptrSegment->m_from[0] + (ptrSegment->m_to[0] - ptrSegment->m_from[0]) * endRelPosition;
			endPosition[1] = ptrSegment->m_from[1] + (ptrSegment->m_to[1] - ptrSegment->m_from[1]) * endRelPosition;
			endPosition[2] = ptrSegment->m_from[2] + (ptrSegment->m_to[2] - ptrSegment->m_from[2]) * endRelPosition;
		}
	}
	else   // conveyor moving in reverse
	{
		endRelPosition = 0.0f;
		endPosition[0] = ptrSegment->m_from[0];
		endPosition[1] = ptrSegment->m_from[1];
		endPosition[2] = ptrSegment->m_from[2];

		for (curPallet = ptrSegment->m_ptrPallet; curPallet != NULL; curPallet = curPallet->m_ptrNextPallet)
		{
			minRelDistance = endRelPosition - curPallet->m_relativePosition;

			relDistance = minRelDistance;
			for (curStopGate = ptrSegment->m_ptrStopGate; curStopGate != NULL && relDistance < 0.0f;
				curStopGate = curStopGate->m_ptrNextStopGate)
			{
				if (curStopGate->m_forward == FALSE && curStopGate->m_stop == TRUE)
				{
					relDistance = curStopGate->m_relativePosition - curPallet->m_relativePosition;
					if (relDistance <= 0.0f && relDistance > minRelDistance)
					{
						minRelDistance = relDistance;
						endPosition[0] = curStopGate->m_position[0];
						endPosition[1] = curStopGate->m_position[1];
						endPosition[2] = curStopGate->m_position[2];
						endRelPosition = curStopGate->m_relativePosition;
					}
				}
			}

			relDistance = minRelDistance;
			for (curTransverseLift = ptrSegment->m_ptrTransverseLift; curTransverseLift != NULL && relDistance < 0.0f;
				curTransverseLift = curTransverseLift->m_ptrNextTransverseLift)
			{
				if (curTransverseLift->m_ptrPart != NULL
					&& curTransverseLift->m_relativePosition != curPallet->m_relativePosition
					&& (curTransverseLift->m_up == TRUE || curTransverseLift->m_forwardBlocking == TRUE
					|| curTransverseLift->m_inMotion == TRUE))
				{
					relDistance = (curTransverseLift->m_relativePosition + (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance))
						- curPallet->m_relativePosition;
					if (relDistance <= 0.0f && relDistance > minRelDistance)
					{
						minRelDistance = relDistance;
						endPosition[0] = ptrSegment->m_from[0] + (ptrSegment->m_to[0] - ptrSegment->m_from[0])
							* (curTransverseLift->m_relativePosition + (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance));
						endPosition[1] = ptrSegment->m_from[1] + (ptrSegment->m_to[1] - ptrSegment->m_from[1])
							* (curTransverseLift->m_relativePosition + (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance));
						endPosition[2] = ptrSegment->m_from[2] + (ptrSegment->m_to[2] - ptrSegment->m_from[2])
							* (curTransverseLift->m_relativePosition + (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance));
						endRelPosition = curTransverseLift->m_relativePosition
							+ (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance);
					}
				}
				else if ((curTransverseLift->m_ptrPart == NULL
					&& curTransverseLift->m_relativePosition != curPallet->m_relativePosition)
					|| (curTransverseLift->m_ptrPart != NULL
					&& curTransverseLift->m_reverseBlocking == TRUE))
				{
					relDistance = curTransverseLift->m_relativePosition - curPallet->m_relativePosition;
					if (relDistance <= 0.0f && relDistance > minRelDistance)
					{
						minRelDistance = relDistance;
						endPosition[0] = curTransverseLift->m_position[0];
						endPosition[1] = curTransverseLift->m_position[1];
						endPosition[2] = curTransverseLift->m_position[2];
						endRelPosition = curTransverseLift->m_relativePosition;
					}
				}
			}

			curPallet->m_endPosition[0] = endPosition[0];
			curPallet->m_endPosition[1] = endPosition[1];
			curPallet->m_endPosition[2] = endPosition[2];

			x = curPallet->m_endPosition[0] - curPallet->m_startPosition[0];
			y = curPallet->m_endPosition[1] - curPallet->m_startPosition[1];
			z = curPallet->m_endPosition[2] - curPallet->m_startPosition[2];
			curPallet->m_distance = sqrt(x * x + y * y + z * z);

			endRelPosition += (YO_CONVEYOR_PALLET_WIDTH / ptrSegment->m_distance);
			endPosition[0] = ptrSegment->m_from[0] + (ptrSegment->m_to[0] - ptrSegment->m_from[0]) * endRelPosition;
			endPosition[1] = ptrSegment->m_from[1] + (ptrSegment->m_to[1] - ptrSegment->m_from[1]) * endRelPosition;
			endPosition[2] = ptrSegment->m_from[2] + (ptrSegment->m_to[2] - ptrSegment->m_from[2]) * endRelPosition;

		}
	}

	minDistance = fabs(ptrSegment->m_distance * minRelDistance);
	taccel = fabs((ptrSegment->m_finalVelocity - ptrSegment->m_initialVelocity)
		/ ptrSegment->m_acceleration);
	daccel = ptrSegment->m_initialVelocity * taccel
		+ 0.5f * ptrSegment->m_acceleration * taccel * taccel;
	if (minDistance < daccel)
	{
		minTime = (sqrt(ptrSegment->m_initialVelocity * ptrSegment->m_initialVelocity
			+ 2.0f * ptrSegment->m_acceleration * minDistance)
			- ptrSegment->m_initialVelocity) / ptrSegment->m_acceleration;
	}
	else if (ptrSegment->m_finalVelocity == 0.0f)
	{
		minTime = taccel;
	}
	else
	{
		minTime = taccel + ((minDistance - daccel) / ptrSegment->m_finalVelocity);
	}
	
	TRACE1("minDistance = %.3lf\n", minDistance);
	return minTime;
}


BOOL CStageConveyor::YoCalculatePositionOfPallets()
{
	CStageConveyorSegment *curSegment;

	for (curSegment = m_ptrSegment; curSegment != NULL; curSegment = curSegment->m_ptrNextSegment)
	{
		YoCalculatePositionOfPallets(curSegment);
	}

	YoCheckSensors();

	return TRUE;
}



BOOL CStageConveyor::YoCalculatePositionOfPallets(CStageConveyorSegment *ptrSegment)
{
	CStageConveyorPallet *curPallet;
	CStageConveyorPallet *ptrPallet;
	CStageConveyorTransverseLift *curTransverseLift;
	BOOL allPalletsAtEndPosition = TRUE;
	//SYSTEMTIME gmTime;
	CTime timeCurrent = CTime::GetCurrentTime();
	CTime timeStart = CTime::GetCurrentTime();
	CTimeSpan spanSec;
	int tms;
	double time;
	double timeElapsed = -1.0f;
	double distance;
	double dAccel;
	double tAccel;
	double x;
	double y;
	double z;


	if (m_moving == 0)
	{
		return TRUE;
	}

	// see if transverse lift is currently in motion
	for (curTransverseLift = ptrSegment->m_ptrTransverseLift; curTransverseLift != NULL;
		curTransverseLift = curTransverseLift->m_ptrNextTransverseLift)
	{
		if (curTransverseLift->m_ptrPart != NULL && curTransverseLift->m_inMotion == TRUE)
		{
			if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
			{
				if (timeElapsed < 0.0)
				{
					time = m_pDoc->m_timeCurrent;
				}
				timeElapsed = time - curTransverseLift->m_timeStart;
			}
			else
			{
				if (timeElapsed < 0.0)
				{
					timeCurrent = m_pDoc->m_gmTime;
				}
				timeStart = curTransverseLift->m_gmTimeStart;
				spanSec = timeCurrent - timeStart;
				tms = m_pDoc->m_gmTime.wMilliseconds - curTransverseLift->m_gmTimeStart.wMilliseconds;
				timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
			}

			// see if a pallet is over this transverse lift
			ptrPallet = NULL;
			for (curPallet = ptrSegment->m_ptrPallet; curPallet != NULL; curPallet = curPallet->m_ptrNextPallet)
			{
				if (curPallet->m_relativePosition + 0.0001 >= curTransverseLift->m_relativePosition
					&& curPallet->m_relativePosition - 0.0001 <= curTransverseLift->m_relativePosition
					&& curPallet->m_ptrPart != NULL)
				{
					ptrPallet = curPallet;
					break;
				}
			}

			if (timeElapsed < YO_CONVEYOR_TRANSVERSE_LIFT_TIME)
			{
				if (curTransverseLift->m_up == TRUE)
				{
					z = (timeElapsed  / YO_CONVEYOR_TRANSVERSE_LIFT_TIME) * YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
				}
				else
				{
					z = YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT
						- (timeElapsed  / YO_CONVEYOR_TRANSVERSE_LIFT_TIME) * YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
				}
				if (ptrPallet != NULL && ptrPallet->m_ptrPart != NULL)
				{
					ptrPallet->m_ptrPart->m_translate[2] = m_offset[2] + curTransverseLift->m_position[2] + z;
				}
			}
			else
			{
				curTransverseLift->m_inMotion = FALSE;
				curTransverseLift->m_ptrMirrorTransverseLift->m_inMotion = curTransverseLift->m_inMotion;

				m_moving--;
				if (m_moving == 0)
				{
					m_pDoc->m_isMovement--;
				}

				if (curTransverseLift->m_up == TRUE)
				{
					z = YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
					if (ptrPallet != NULL && ptrPallet->m_ptrPart != NULL)
					{
						ptrPallet->m_ptrPart->m_translate[2] = m_offset[2] + curTransverseLift->m_position[2] + z;
						ptrPallet->m_position[2] += YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT;
						YoTransferPallet(ptrPallet, curTransverseLift->m_ptrTransverseSegment);
						if (curTransverseLift->m_ptrTransverseSegment->m_moving == TRUE)
						{
							curTransverseLift->m_ptrTransverseSegment->m_initialVelocity = curTransverseLift->m_ptrTransverseSegment->m_curVelocity;
							if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
							{
								//curTransverseLift->m_ptrTransverseSegment->m_timeStart = time;
								curTransverseLift->m_ptrTransverseSegment->m_timeStart += YO_CONVEYOR_TRANSVERSE_LIFT_TIME;
							}
							else
							{
								//curTransverseLift->m_ptrTransverseSegment->m_gmTimeStart = m_pDoc->m_gmTime;
								m_pDoc->YoChangeTime(&curTransverseLift->m_ptrTransverseSegment->m_gmTimeStart, YO_CONVEYOR_TRANSVERSE_LIFT_TIME);

							}
							YoSetStartPositionOfPallets(curTransverseLift->m_ptrTransverseSegment);
							YoCalculateEndPositionOfPallets(curTransverseLift->m_ptrTransverseSegment);
						}
					}
				}
				else
				{
					z = 0.0f;
					if (ptrPallet != NULL && ptrPallet->m_ptrPart != NULL)
					{
						ptrPallet->m_ptrPart->m_translate[2] = m_offset[2] + curTransverseLift->m_position[2];

					}
					if (curTransverseLift->m_ptrSegment->m_moving == TRUE
						&& curTransverseLift->m_ptrSegment->m_ptrPallet != NULL)
					{
						curTransverseLift->m_ptrSegment->m_initialVelocity = curTransverseLift->m_ptrSegment->m_curVelocity;
						if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
						{
							//curTransverseLift->m_ptrSegment->m_timeStart = time;
							curTransverseLift->m_ptrSegment->m_timeStart += YO_CONVEYOR_TRANSVERSE_LIFT_TIME;
						}
						else
						{
							//curTransverseLift->m_ptrSegment->m_gmTimeStart = m_pDoc->m_gmTime;
							m_pDoc->YoChangeTime(&curTransverseLift->m_ptrSegment->m_gmTimeStart, YO_CONVEYOR_TRANSVERSE_LIFT_TIME);
						}
						YoSetStartPositionOfPallets(curTransverseLift->m_ptrSegment);
						YoCalculateEndPositionOfPallets(curTransverseLift->m_ptrSegment);
					}
				}

			}
			curTransverseLift->m_ptrPart->m_translate[2] = m_offset[2] - 6.35 + curTransverseLift->m_position[2] + z;
			TRACE3("LIFT  up = %d  inMotion = %d  timeElapsed = %.3lf\n", curTransverseLift->m_up, curTransverseLift->m_inMotion, timeElapsed);  
		}
	}

	if (ptrSegment->m_moving == FALSE)
	{
		return TRUE;
	}

	/***
	for (curPallet = ptrSegment->m_ptrPallet; curPallet != NULL && allPalletsAtEndPosition == TRUE;
		curPallet = curPallet->m_ptrNextPallet)
	{
		if (curPallet->m_position[0] != curPallet->m_endPosition[0]
			|| curPallet->m_position[1] != curPallet->m_endPosition[1]
			|| curPallet->m_position[2] != curPallet->m_endPosition[2])
		{
			allPalletsAtEndPosition = FALSE;
		}
	}
	
	if (allPalletsAtEndPosition == TRUE)
	{
		return TRUE;
	}
	***/


	// calculate the total distance the pallets have moved
	if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
	{
		if (timeElapsed < 0.0)
		{
			time = m_pDoc->m_timeCurrent;
		}
		timeElapsed = time - ptrSegment->m_timeStart;
	}
	else
	{
		if (timeElapsed < 0.0)
		{
			timeCurrent = m_pDoc->m_gmTime;
		}
		timeStart = ptrSegment->m_gmTimeStart;
		spanSec = timeCurrent - timeStart;
		tms = m_pDoc->m_gmTime.wMilliseconds - ptrSegment->m_gmTimeStart.wMilliseconds;
		timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
		TRACE2("Conveyor(%s): timeElapsed = %.3lf   ", ptrSegment->m_ptrPart->m_partName, timeElapsed);
		TRACE2("m_gmTimeStart = %d %d   ", ptrSegment->m_gmTimeStart.wSecond, ptrSegment->m_gmTimeStart.wMilliseconds);
		TRACE2("m_gmTime = %d %d\n", m_pDoc->m_gmTime.wSecond, m_pDoc->m_gmTime.wMilliseconds);

	}

	//if (ptrSegment->m_finalVelocity == 0.0
	//	&& timeElapsed > ptrSegment->m_stoppingTime)
	//{
	//	timeElapsed = ptrSegment->m_stoppingTime;
	//}

	tAccel = fabs((ptrSegment->m_finalVelocity - ptrSegment->m_initialVelocity)
		/ ptrSegment->m_acceleration);
	if (ptrSegment->m_finalVelocity > ptrSegment->m_initialVelocity)
	{
		dAccel = fabs(ptrSegment->m_initialVelocity * tAccel
			+ 0.5 * ptrSegment->m_acceleration * tAccel * tAccel);
	}
	else if (ptrSegment->m_finalVelocity < ptrSegment->m_initialVelocity)
	{
		dAccel = fabs(ptrSegment->m_initialVelocity * tAccel
			- 0.5 * ptrSegment->m_acceleration * tAccel * tAccel);
	}
	else
	{
		dAccel = 0.0f;
	}

	if (timeElapsed > tAccel)
	{
		distance = dAccel + fabs(ptrSegment->m_finalVelocity * (timeElapsed - tAccel));
		ptrSegment->m_curVelocity = ptrSegment->m_finalVelocity;
	}
	else
	{
		if (ptrSegment->m_finalVelocity >= ptrSegment->m_initialVelocity)
		{
			distance = fabs(ptrSegment->m_initialVelocity * timeElapsed
				+ 0.5 * ptrSegment->m_acceleration * timeElapsed * timeElapsed);
			ptrSegment->m_curVelocity = ptrSegment->m_initialVelocity + ptrSegment->m_acceleration * timeElapsed;
		}
		else
		{
			distance = fabs(ptrSegment->m_initialVelocity * timeElapsed
				- 0.5 * ptrSegment->m_acceleration * timeElapsed * timeElapsed);
			ptrSegment->m_curVelocity = ptrSegment->m_initialVelocity - ptrSegment->m_acceleration * timeElapsed;
		}
	}

	// update position of pallets for this conveyor segment
	for (curPallet = ptrSegment->m_ptrPallet; curPallet != NULL; curPallet = curPallet->m_ptrNextPallet)
	{
		if (curPallet->m_moving == TRUE)
		{
			if (distance >= curPallet->m_distance)
			{
				curPallet->m_position[0] = curPallet->m_endPosition[0];
				curPallet->m_position[1] = curPallet->m_endPosition[1];
				curPallet->m_position[2] = curPallet->m_endPosition[2];
				curPallet->m_moving = FALSE;
			}
			else
			{
				curPallet->m_position[0] = curPallet->m_startPosition[0]
					+ (curPallet->m_endPosition[0] - curPallet->m_startPosition[0]) * (distance / curPallet->m_distance);
				curPallet->m_position[1] = curPallet->m_startPosition[1]
					+ (curPallet->m_endPosition[1] - curPallet->m_startPosition[1]) * (distance / curPallet->m_distance);
				curPallet->m_position[2] = curPallet->m_startPosition[2]
					+ (curPallet->m_endPosition[2] - curPallet->m_startPosition[2]) * (distance / curPallet->m_distance);
			}
			x = curPallet->m_position[0] - ptrSegment->m_from[0];
			y = curPallet->m_position[1] - ptrSegment->m_from[1];
			z = curPallet->m_position[2] - ptrSegment->m_from[2];
			curPallet->m_relativePosition = sqrt(x * x + y * y + z * z) / ptrSegment->m_distance;

			YoUpdatePalletGraphicsPosition(curPallet);

			if (ptrSegment->m_moving == FALSE)
			{
				curPallet->m_moving = FALSE;
			}
		}
		//TRACE2("curPallet->m_position[0] = %.3lf  curVelocity = %.3lf\n", curPallet->m_position[0], ptrSegment->m_curVelocity);
	}

	if (ptrSegment->m_moving == TRUE && ptrSegment->m_curVelocity == 0.0f
		&& ptrSegment->m_finalVelocity == 0.0f && ptrSegment->m_initialVelocity > 0.0f)
	{
		if (ptrSegment->m_changingDirection == TRUE && ptrSegment->m_reverseFinalVelocity > 0.0f)
		{
			if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
			{
				ptrSegment->m_timeStart = time;
			}
			else
			{
				ptrSegment->m_gmTimeStart = m_pDoc->m_gmTime;
			}
			if (ptrSegment->m_directionForward == TRUE)
			{
				ptrSegment->m_directionForward = FALSE;
			}
			else
			{
				ptrSegment->m_directionForward = TRUE;
			}
			ptrSegment->m_initialVelocity = 0.0f;
			ptrSegment->m_finalVelocity = ptrSegment->m_reverseFinalVelocity;
			ptrSegment->m_reverseFinalVelocity = 0.0f;
			ptrSegment->m_changingDirection = FALSE;
			YoSetStartPositionOfPallets(ptrSegment);
			YoCalculateEndPositionOfPallets(ptrSegment);
		}
		else
		{
			ptrSegment->m_moving = FALSE;
			m_moving--;
			if (m_moving == 0)
			{
				m_pDoc->m_isMovement--;
			}
		}
		
	}

	return TRUE;
}


BOOL CStageConveyor::YoSetStartPositionOfPallets()
{
	CStageConveyorSegment *curSegment;

	for (curSegment = m_ptrSegment; curSegment != NULL; curSegment = curSegment->m_ptrNextSegment)
	{
		if (curSegment->m_ptrPallet != NULL)
		{
			YoSetStartPositionOfPallets(curSegment);
		}
	}
	return TRUE;
}


BOOL CStageConveyor::YoSetStartPositionOfPallets(CStageConveyorSegment *ptrSegment)
// sets the start position of each pallet to be the same as the
// current position.  Called when the conveyor segment changes state.
{
	CStageConveyorPallet *curPallet;

	if (ptrSegment->m_ptrPallet == NULL)
	{
		return TRUE;
	}

	for (curPallet = ptrSegment->m_ptrPallet; curPallet != NULL; curPallet = curPallet->m_ptrNextPallet)
	{
		curPallet->m_startPosition[0] = curPallet->m_position[0];
		curPallet->m_startPosition[1] = curPallet->m_position[1];
		curPallet->m_startPosition[2] = curPallet->m_position[2];
		if (ptrSegment->m_moving == TRUE)
		{
			curPallet->m_moving = TRUE;
		}
	}


	return TRUE;
}

BOOL CStageConveyor::YoUpdatePalletGraphicsPosition(CStageConveyorPallet *ptrPallet)
// updates pallet translate variable based on ptrPallet->m_position
// and conveyor offset
{
	GLdouble m[16];

	if (ptrPallet == NULL || ptrPallet->m_ptrSegment == NULL)
	{
		return FALSE;
	}

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glLoadIdentity();
	::glTranslated(m_offset[0], m_offset[1], m_offset[2]);
	::glTranslated(ptrPallet->m_position[0], ptrPallet->m_position[1], ptrPallet->m_position[2]);
	::glGetDoublev(GL_MODELVIEW_MATRIX, m);
	ptrPallet->m_ptrPart->m_translate[0] = m[12];
	ptrPallet->m_ptrPart->m_translate[1] = m[13];
	ptrPallet->m_ptrPart->m_translate[2] = m[14];
	ptrPallet->m_ptrPart->m_rotate[0] = 0.0f;
	ptrPallet->m_ptrPart->m_rotate[1] = 0.0f;
	ptrPallet->m_ptrPart->m_rotate[2] = 0.0f;
	::glPopMatrix();

	return TRUE;
}


void CStageConveyor::YoCheckSensors()
{
	CStageConveyorSensor *curSensor;
	CStageConveyorPallet *curPallet;
	CStageConveyorSegment *curSegment;
	double halfRelVelocity;
	char buf[128];

	for (curSegment = m_ptrSegment; curSegment != NULL; curSegment = curSegment->m_ptrNextSegment)
	{
		halfRelVelocity = 0.5 * curSegment->m_curVelocity / curSegment->m_distance;
		for (curSensor = curSegment->m_ptrSensor; curSensor != NULL; curSensor = curSensor->m_ptrNextSensor)
		{
			if (curSensor->m_ptrPallet != NULL
				&& curSensor->m_relativePosition + .0001 + halfRelVelocity >= curSensor->m_ptrPallet->m_relativePosition
				&& curSensor->m_relativePosition - .0001 - halfRelVelocity <= curSensor->m_ptrPallet->m_relativePosition)
			{
				// pallet still over sensor
			}
			else
			{
				curSensor->m_ptrPallet = NULL;
				for (curPallet = curSegment->m_ptrPallet;
					curPallet != NULL && curSensor->m_ptrPallet == NULL;
					curPallet = curPallet->m_ptrNextPallet)
				{
					if (curSensor->m_relativePosition + .0001 + halfRelVelocity >= curPallet->m_relativePosition
						&& curSensor->m_relativePosition - .0001 - halfRelVelocity <= curPallet->m_relativePosition)
					{
						// pallet has moved over sensor
						curSensor->m_ptrPallet = curPallet;
						
						if (m_moving && m_pDoc->m_acceptSocket != NULL)
						{
							memset(buf, 0, 128);
							sprintf(buf, "! %s SEN %s %s 1",
								m_name, curSensor->m_ptrPart->m_partName, curSensor->m_ptrPallet->m_name); 
							m_pDoc->m_acceptSocket->Send(buf, strlen(buf) + 1);
						}
					}
				}
			}
		}
	}
	return;
}


BOOL CStageConveyorPallet::YoReadConveyorPallet(FILE *fp, CStageConveyorPallet *ptrPallet)

{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	
	sprintf(partAttachName, "");
  
	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "CONVEYOR_PALLET_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrPallet, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "CONVEYOR_PALLET_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrPallet->m_name);
		}
		else if (strcmp(command, "CONVEYOR_PALLET_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrPallet->m_parent, &partAttachName);
			ptrPart = m_pDoc->YoPartLookup(ptrPallet, partAttachName);
		}
		else if (strcmp(command, "CONVEYOR_PALLET_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrPallet->m_visible);
		}
		else if (strcmp(command, "CONVEYOR_PALLET_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrPallet->m_mass);
		}
		else if (strcmp(command, "CONVEYOR_PALLET_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrPallet->m_barCode);
		}
		else if (strcmp(command, "CONVEYOR_PALLET_POSITION") == 0)
		{
			sscanf(s, "%*s %lf %lf %lf", &ptrPallet->m_position[0],
				&ptrPallet->m_position[1], &ptrPallet->m_position[2]);
		}
		else
		{
			return FALSE;
		}
	
	} // end while (!done)
	return TRUE;
}

CStageConveyorSegment *CStageConveyor::YoFindSegment(CStagePart *ptrPart)
// find ptrSegment which is either ptrPart or a parent of ptrPart
{ 
	CStageConveyorSegment *curSegment;
	CStagePart *curPart;

	for (curPart = ptrPart; curPart != NULL;)
	{
		for (curSegment = m_ptrSegment; curSegment != NULL;
			curSegment = curSegment->m_ptrNextSegment)
		{
			if (curSegment->m_ptrPart == curPart)
			{
				return curSegment;
			}
		}
		if (strcmp(curPart->m_partParent, "NONE") == 0)
		{
			curPart = NULL;
		}
		else
		{
			curPart = m_pDoc->YoPartLookup(this, curPart->m_partParent);
		}
	}
	return NULL;
}


CStageConveyorSegment *CStageConveyor::YoFindSegment(double *px, double *py, double *pz)
// try to find a conveyor segment which is closest to the point px, py, pz
// and then set the point so that it lies on the chosen conveyor segment
{ 
	CStageConveyorSegment *curSegment;
	CStageConveyorSegment *ptrSegmentBis = NULL;
	CStageConveyorSegment *ptrSegmentEnd = NULL;
	BOOL fromClosestBis = TRUE;
	BOOL fromClosestEnd = TRUE;
	double a;
	double b;
	double c;
	double d;
	double angleA;
	double edge;
	double dEnd = FLT_MAX;
	double dBis = FLT_MAX;
	double x;
	double y;
	double z;
	double d0;
	double d1;


	// find appropriate conveyor segment
	for (curSegment = m_ptrSegment; curSegment != NULL; curSegment = curSegment->m_ptrNextSegment)
	{
		x = *px - curSegment->m_from[0];
		y = *py - curSegment->m_from[1];
		z = *pz - curSegment->m_from[2];
		d0 = sqrt(x * x + y * y + z * z);
		x = *px - curSegment->m_to[0];
		y = *py - curSegment->m_to[1];
		z = *pz - curSegment->m_to[2];
		d1 = sqrt(x * x + y * y + z * z);

		// first do a quick check to see if point already lies on curSegment
		if (d0 <= 0.1)
		{
			*px = curSegment->m_from[0];
			*py = curSegment->m_from[1];
			*pz = curSegment->m_from[2];
			return curSegment;
		}
		else if (d1 <= 0.1)
		{
			*px = curSegment->m_to[0];
			*py = curSegment->m_to[1];
			*pz = curSegment->m_to[2];
			return curSegment;
		}
		else if (d0 + d1 + 0.1 >= curSegment->m_distance
			&& d0 + d1 - 0.1 <= curSegment->m_distance)
		{
			return curSegment;
		}

		// find distance from point to conveyor segment
		// line segment b is from the closest vertex to pick point
		if (d0 <= d1)
		{
			a = d1;
			b = d0;
		}
		else
		{
			a = d0;
			b = d1;
		}
		c = curSegment->m_distance;

		angleA = acos (((b * b) + (c * c) - (a * a)) / (2.0 * b * c));

		if (angleA > 90.0 * YO_DEGREES_TO_RADIANS)
		// point does not bisect conveyor segment
		{
			if (b < dEnd)
			{
				dEnd = b;
				ptrSegmentEnd = curSegment;
				if (d0 <= d1)
				{
					fromClosestEnd = TRUE;
				}
				else
				{
					fromClosestEnd = FALSE;
				}
			}
		}
		else  // point besects conveyor segment
		{
			d = b * sin(angleA);
			if (d < dBis)
			{
				dBis = d;
				edge = b * cos(angleA);
				ptrSegmentBis = curSegment;
				if (d0 <= d1)
				{
					fromClosestBis = TRUE;
				}
				else
				{
					fromClosestBis = FALSE;
				}		
			}
		}
	}

	if (ptrSegmentBis != NULL && dBis <= dEnd)
	{
		if (fromClosestBis == TRUE)
		{
			*px = ptrSegmentBis->m_from[0] + (ptrSegmentBis->m_to[0] - ptrSegmentBis->m_from[0])
				* (edge / ptrSegmentBis->m_distance);
			*py = ptrSegmentBis->m_from[1] + (ptrSegmentBis->m_to[1] - ptrSegmentBis->m_from[1])
				* (edge / ptrSegmentBis->m_distance);
			*pz = ptrSegmentBis->m_from[2] + (ptrSegmentBis->m_to[2] - ptrSegmentBis->m_from[2])
				* (edge / ptrSegmentBis->m_distance);
		}
		else
		{
			*px = ptrSegmentBis->m_to[0] + (ptrSegmentBis->m_from[0] - ptrSegmentBis->m_to[0])
				* (edge / ptrSegmentBis->m_distance);
			*py = ptrSegmentBis->m_to[1] + (ptrSegmentBis->m_from[1] - ptrSegmentBis->m_to[1])
				* (edge / ptrSegmentBis->m_distance);
			*pz = ptrSegmentBis->m_to[2] + (ptrSegmentBis->m_from[2] - ptrSegmentBis->m_to[2])
				* (edge / ptrSegmentBis->m_distance);
		}
		return ptrSegmentBis;
	}
	else if (ptrSegmentEnd != NULL && dEnd <= dBis)
	{
		if (fromClosestEnd == TRUE)
		{
			*px = ptrSegmentEnd->m_from[0];
			*py = ptrSegmentEnd->m_from[1];
			*pz = ptrSegmentEnd->m_from[2];
		}
		else
		{
			*px = ptrSegmentEnd->m_to[0];
			*py = ptrSegmentEnd->m_to[1];
			*pz = ptrSegmentEnd->m_to[2];
		}
		return ptrSegmentEnd;
	}

	return NULL;
}


CStageConveyorStopGate *CStageConveyor::YoFindStopGate(CStagePart *ptrPart)
// find ptrStopGate which is either ptrPart or a parent of ptrPart
{ 
	CStageConveyorSegment *curSegment;
	CStageConveyorStopGate *curStopGate;
	CStagePart *curPart;

	for (curPart = ptrPart; curPart != NULL;)
	{
		for (curSegment = m_ptrSegment; curSegment != NULL;
			curSegment = curSegment->m_ptrNextSegment)
		{
			for (curStopGate = curSegment->m_ptrStopGate; curStopGate != NULL;
				curStopGate = curStopGate->m_ptrNextStopGate)
			{
				if (curStopGate->m_ptrPart == curPart)
				{
					return curStopGate;
				}
			}
		}
		if (strcmp(curPart->m_partParent, "NONE") == 0)
		{
			curPart = NULL;
		}
		else
		{
			curPart = m_pDoc->YoPartLookup(this, curPart->m_partParent);
		}
	}
	return NULL;
}

int CStageConveyor::YoFind(CStagePart *ptrPart, CStageConveyorSegment **ptrSegment,
	CStageConveyorSensor **ptrSensor, CStageConveyorStopGate **ptrStopGate,
	CStageConveyorTransverseLift **ptrTransverseLift)
// given a part find the corresponding segment, sensor, stop gate, or transverse lift
// return the type or 0 if nothing found
{
	CStagePart *curPart;
	CStageConveyorSegment *curSegment;
	CStageConveyorSensor *curSensor;
	CStageConveyorStopGate *curStopGate;
	CStageConveyorTransverseLift *curTransverseLift;

	*ptrSegment = NULL;
	*ptrSensor = NULL;
	*ptrStopGate = NULL;
	*ptrTransverseLift = NULL;

	for (curPart = ptrPart; curPart != NULL;)
	{
		for (curSegment = m_ptrSegment; curSegment != NULL;
			curSegment = curSegment->m_ptrNextSegment)
		{
			for (curSensor = curSegment->m_ptrSensor; curSensor != NULL;
				curSensor = curSensor->m_ptrNextSensor)
			{
				if (curSensor->m_ptrPart == curPart)
				{
					*ptrSensor = curSensor;
					return YO_CONVEYOR_SENSOR;
				}
			}
			for (curStopGate = curSegment->m_ptrStopGate; curStopGate != NULL;
				curStopGate = curStopGate->m_ptrNextStopGate)
			{
				if (curStopGate->m_ptrPart == curPart)
				{
					*ptrStopGate = curStopGate;
					return YO_CONVEYOR_STOP_GATE;
				}
			}
			for (curTransverseLift = curSegment->m_ptrTransverseLift; curTransverseLift != NULL;
				curTransverseLift = curTransverseLift->m_ptrNextTransverseLift)
			{
				if (curTransverseLift->m_ptrPart == curPart)
				{
					*ptrTransverseLift = curTransverseLift;
					return YO_CONVEYOR_TRANSVERSE_LIFT;
				}
			}
			if (curSegment->m_ptrPart == curPart)
			{
				*ptrSegment = curSegment;
				return YO_CONVEYOR_SEGMENT;
			}

		}
		if (strcmp(curPart->m_partParent, "NONE") == 0)
		{
			curPart = NULL;
		}
		else
		{
			curPart = m_pDoc->YoPartLookup(this, curPart->m_partParent);
		}
	}
	return 0;
}


CStageConveyorSensor *CStageConveyor::YoFindSensor(CStagePart *ptrPart)
// find ptrSensor which is either ptrPart or a parent of ptrPart
{ 
	CStageConveyorSegment *curSegment;
	CStageConveyorSensor *curSensor;
	CStagePart *curPart;

	for (curPart = ptrPart; curPart != NULL;)
	{
		for (curSegment = m_ptrSegment; curSegment != NULL;
			curSegment = curSegment->m_ptrNextSegment)
		{
			for (curSensor = curSegment->m_ptrSensor; curSensor != NULL;
				curSensor = curSensor->m_ptrNextSensor)
			{
				if (curSensor->m_ptrPart == curPart)
				{
					return curSensor;
				}
			}
		}
		if (strcmp(curPart->m_partParent, "NONE") == 0)
		{
			curPart = NULL;
		}
		else
		{
			curPart = m_pDoc->YoPartLookup(this, curPart->m_partParent);
		}
	}
	return NULL;
}


CStageConveyorTransverseLift *CStageConveyor::YoFindTransverseLift(CStagePart *ptrPart)
// find ptrTransverseLift which is either ptrPart or a parent of ptrPart
{ 
	CStageConveyorSegment *curSegment;
	CStageConveyorTransverseLift *curTransverseLift;
	CStagePart *curPart;

	for (curPart = ptrPart; curPart != NULL;)
	{
		for (curSegment = m_ptrSegment; curSegment != NULL;
			curSegment = curSegment->m_ptrNextSegment)
		{
			for (curTransverseLift = curSegment->m_ptrTransverseLift; curTransverseLift != NULL;
				curTransverseLift = curTransverseLift->m_ptrNextTransverseLift)
			{
				if (curTransverseLift->m_ptrPart == curPart)
				{
					return curTransverseLift;
				}
			}
		}
		if (strcmp(curPart->m_partParent, "NONE") == 0)
		{
			curPart = NULL;
		}
		else
		{
			curPart = m_pDoc->YoPartLookup(this, curPart->m_partParent);
		}
	}
	return NULL;
}


BOOL CStageConveyor::YoSafeLift(CStageConveyorTransverseLift *ptrTransverseLift, BOOL liftUp)
// Make certain that pallets are completely off or on transverse lift
// and that the transverse segment is not moving toward the lift during a lower command
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	CStageConveyorPallet *curPallet;
	double relPalletWidth;
	char s[256];

	relPalletWidth = YO_CONVEYOR_PALLET_WIDTH / ptrTransverseLift->m_ptrSegment->m_distance;
	for (curPallet = ptrTransverseLift->m_ptrSegment->m_ptrPallet;
		curPallet != NULL; curPallet = curPallet->m_ptrNextPallet)
	{
		if (curPallet->m_relativePosition + relPalletWidth > ptrTransverseLift->m_relativePosition
			&& curPallet->m_relativePosition - relPalletWidth < ptrTransverseLift->m_relativePosition
			&& fabs(curPallet->m_relativePosition - ptrTransverseLift->m_relativePosition) > 0.0001)
		{
			if (pMainFrame->m_viewPartActive == TRUE)
			{
				sprintf(s, "Unable to move transverse lift due to pallet straddling edge of lift");
				m_pDoc->YoMessage(s);
			}
			return FALSE;
		}
	}

	relPalletWidth = YO_CONVEYOR_PALLET_WIDTH / ptrTransverseLift->m_ptrTransverseSegment->m_distance;
	for (curPallet = ptrTransverseLift->m_ptrTransverseSegment->m_ptrPallet;
		curPallet != NULL; curPallet = curPallet->m_ptrNextPallet)
	{
		if (curPallet->m_relativePosition + relPalletWidth > ptrTransverseLift->m_ptrMirrorTransverseLift->m_relativePosition
			&& curPallet->m_relativePosition - relPalletWidth < ptrTransverseLift->m_ptrMirrorTransverseLift->m_relativePosition
			&& fabs(curPallet->m_relativePosition - ptrTransverseLift->m_ptrMirrorTransverseLift->m_relativePosition) > 0.0001)
		{
			if (pMainFrame->m_viewPartActive == TRUE)
			{
				sprintf(s, "Unable to move transverse lift due to pallet straddling edge of lift");
				m_pDoc->YoMessage(s);
			}
			return FALSE;
		}
	}

	if ((ptrTransverseLift->m_ptrMirrorTransverseLift->m_relativePosition == 0.0
		&& ptrTransverseLift->m_ptrTransverseSegment->m_directionForward == FALSE
		&& ptrTransverseLift->m_ptrTransverseSegment->m_curVelocity != 0.0f
		&& liftUp == FALSE)
		|| (ptrTransverseLift->m_ptrMirrorTransverseLift->m_relativePosition == 1.0
		&& ptrTransverseLift->m_ptrTransverseSegment->m_directionForward == TRUE
		&& ptrTransverseLift->m_ptrTransverseSegment->m_curVelocity != 0.0f
		&& liftUp == FALSE))
	{
			if (pMainFrame->m_viewPartActive == TRUE)
			{
				sprintf(s, "Unable to lower transverse lift.  Turn off segment %s before proceeding",
					ptrTransverseLift->m_ptrTransverseSegment->m_ptrPart->m_partName);
				m_pDoc->YoMessage(s);
			}
			return FALSE;
	}

	if (pMainFrame->m_viewPartActive == TRUE)
	{
		m_pDoc->YoMessage("");
	}
	return TRUE;

}


BOOL CStageConveyor::YoIllegalMove(CStageConveyorSegment *ptrSegment, double speed)
// If conveyor segment is the transverse segment of a transverse lift
// make certain the lift is up if the move is toward the transverse lift
// Check stop gates to make certain that all stop gates in the opposite
// direction of the move are down
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	CStageConveyorTransverseLift *curTransverseLift;
	CStageConveyorStopGate *curStopGate;
	char s[256];

	for (curTransverseLift = ptrSegment->m_ptrTransverseLift;
		curTransverseLift != NULL;
		curTransverseLift = curTransverseLift->m_ptrNextTransverseLift)
	{
		if (curTransverseLift->m_ptrPart == NULL
			&& curTransverseLift->m_up == FALSE
			&& ((curTransverseLift->m_relativePosition == 0.0f
			&& speed < 0.0f)
			|| (curTransverseLift->m_relativePosition == 1.0f
			&& speed > 0.0f)))
		{
			if (pMainFrame->m_viewPartActive == TRUE)
			{
				sprintf(s, "Unable to engage segment %s. Raise tranverse lift before proceeding",
					ptrSegment->m_ptrPart->m_partName);
				m_pDoc->YoMessage(s);
			}
			return TRUE;
		}
		//if (curTransverseLift->m_inMotion == TRUE)
		//{
		//	return TRUE;
		//}
	}

	for (curStopGate = ptrSegment->m_ptrStopGate;
		curStopGate != NULL;
		curStopGate = curStopGate->m_ptrNextStopGate)
	{
		if ((speed > 0.0f
			&& curStopGate->m_forward == FALSE
			&& curStopGate->m_stop == TRUE)
			|| (speed < 0.0f
			&& curStopGate->m_forward == TRUE
			&& curStopGate->m_stop == TRUE))
		{
			if (pMainFrame->m_viewPartActive == TRUE)
			{
				sprintf(s, "Unable to engage segment %s. Lower stop gates before proceeding",
					ptrSegment->m_ptrPart->m_partName);
				m_pDoc->YoMessage(s);
			}
			return TRUE;
		}
	}

	if (pMainFrame->m_viewPartActive == TRUE)
	{
		m_pDoc->YoMessage("");
	}
	return FALSE;
}


BOOL CStageConveyor::YoTransverseLiftsInMotion(CStageConveyorSegment *ptrSegment)
{
	CStageConveyorTransverseLift *curTransverseLift;

	for (curTransverseLift = ptrSegment->m_ptrTransverseLift; curTransverseLift != NULL;
		curTransverseLift = curTransverseLift->m_ptrNextTransverseLift)
	{
		if (curTransverseLift->m_inMotion == TRUE)
		{
			return TRUE;
		}
	}

	return FALSE;

}


BOOL CStageBarrettHand::YoHandleCommand(char *buf)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return FALSE;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return FALSE;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	CStageDevice *ptrDevice;
	char t[64];
	int i;
	double f[3];
	double l[3];
	double r[3];
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	CTimeSpan spanSec;

	if (m_moving == TRUE)
	{
		sprintf(buf, "X");
		return FALSE;
	}

	if (m_pDoc->m_scriptFastForward == TRUE)
	{
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0) + m_pDoc->m_timeSleepTotal;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else if (pMainFrame->m_wndDlgScript != NULL && pMainFrame->m_wndDlgScriptVisible == TRUE)
	{
		//::GetSystemTime(&m_pDoc->m_gmTime);
		//timeCurrent = m_pDoc->m_gmTime;
		//timeStart = m_pDoc->m_gmTimeStart;
		//spanSec = timeCurrent - timeStart;
		//tms = m_pDoc->m_gmTime.wMilliseconds - m_pDoc->m_gmTimeStart.wMilliseconds;
		//timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0)
		//	+ pMainFrame->m_wndDlgScript->m_timeSleepFastForward
		//	- pMainFrame->m_wndDlgScript->m_timeFastForward;
		//m_pDoc->YoChangeTime(&m_pDoc->m_gmTime, timeElapsed);
		//m_pDoc->m_gmTime.wSecond = (int)timeElapsed;
		//m_pDoc->m_gmTime.wMilliseconds = (int)((timeElapsed - (double)(int)timeElapsed) * 1000.0);
	}
	else
	{
		::GetSystemTime(&m_pDoc->m_gmTime);
	}

	if (toupper(buf[0]) == 'C' && toupper(buf[1]) == 'L')
	{
		i = sscanf(buf, "%*s %lf %lf %lf %lf %lf %lf %s", &r[1], &r[2], &l[1], &l[2], &f[1], &f[2], &t);

		if (i == 6 || i == 7)
		{
			f[1] = YO_MIN(f[1], 140.0);
			f[1] = YO_MAX(f[1], 0.0);
			f[2] = YO_MIN(f[2], 45.0);
			f[2] = YO_MAX(f[2], 0.0);
			l[1] = YO_MIN(l[1], 140.0);
			l[1] = YO_MAX(l[1], 0.0);
			l[2] = YO_MIN(l[2], 45.0);
			l[2] = YO_MAX(l[2], 0.0);
			r[1] = YO_MIN(r[1], 140.0);
			r[1] = YO_MAX(r[1], 0.0);
			r[2] = YO_MIN(r[2], 45.0);
			r[2] = YO_MAX(r[2], 0.0);

			m_fingerFixedStart[1] = m_fingerFixed[1];
			m_fingerFixedEnd[1] = f[1];
			m_fingerFixedStart[2] = m_fingerFixed[2];
			m_fingerFixedEnd[2] = f[2];
			m_fingerLeftStart[1] = m_fingerLeft[1];
			m_fingerLeftEnd[1] = l[1];
			m_fingerLeftStart[2] = m_fingerLeft[2];
			m_fingerLeftEnd[2] = l[2];
			m_fingerRightStart[1] = m_fingerRight[1];
			m_fingerRightEnd[1] = r[1];
			m_fingerRightStart[2] = m_fingerRight[2];
			m_fingerRightEnd[2] = r[2];
		}

		if (i == 7 && (ptrDevice = m_pDoc->YoDeviceHashLookup(t)) != NULL)
		{
			YoCloseHand(t);
			sprintf(buf, "| %s CLOSE %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %s",
				m_name, r[1], r[2], l[1], l[2], f[1], f[2], ptrDevice->m_name);
			m_gripping = TRUE;
			if (m_moving == FALSE)
			{
				m_pDoc->m_isMovement++;
			}
			m_moving = TRUE;

			if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
				&& m_pDoc->m_currentCommand != NULL)
			{
				m_timeStart = m_pDoc->m_currentCommand->m_time;
			}
			else
			{
				m_gmTimeStart = m_pDoc->m_gmTime;
			}
		}
		else if (i == 6)
		{
			if ((ptrDevice = YoFindDeviceToGrab()) != NULL)
			{
				sprintf(buf, "| %s CLOSE %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %s",
					m_name, r[1], r[2], l[1], l[2], f[1], f[2], ptrDevice->m_name);
			}
			else
			{
				sprintf(buf, "| %s CLOSE %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf",
					m_name, r[1], r[2], l[1], l[2], f[1], f[2]);
			}
			m_gripping = TRUE;
			if (m_moving == FALSE)
			{
				m_pDoc->m_isMovement++;
			}
			m_moving = TRUE;

			if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
				&& m_pDoc->m_currentCommand != NULL)
			{
				m_timeStart = m_pDoc->m_currentCommand->m_time;
			}
			else
			{
				m_gmTimeStart = m_pDoc->m_gmTime;
			}
		}
		else
		{
			sprintf(buf, "X");
		}
	}

	else if (toupper(buf[0]) == 'O' && toupper(buf[1]) == 'P')
	{
		m_fingerFixedStart[1] = m_fingerFixed[1];
		m_fingerFixedEnd[1] = 0.0;
		m_fingerFixedStart[2] = m_fingerFixed[2];
		m_fingerFixedEnd[2] = 0.0;
		m_fingerLeftStart[1] = m_fingerLeft[1];
		m_fingerLeftEnd[1] = 0.0;
		m_fingerLeftStart[2] = m_fingerLeft[2];
		m_fingerLeftEnd[2] = 0.0;
		m_fingerRightStart[1] = m_fingerRight[1];
		m_fingerRightEnd[1] = 0.0;
		m_fingerRightStart[2] = m_fingerRight[2];
		m_fingerRightEnd[2] = 0.0;

		if (m_down != NULL && strcmp(m_down->m_parent, "NONE") != 0)
		{
			sprintf(buf, "| %s OPEN %s", m_name, m_down->m_name);
			YoOpenHand();
			m_gripping = FALSE;
			if (m_moving == FALSE)
			{
				m_pDoc->m_isMovement++;
			}
			m_moving = TRUE;

			if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
				&& m_pDoc->m_currentCommand != NULL)
			{
				m_timeStart = m_pDoc->m_currentCommand->m_time;
			}
			else
			{
				m_gmTimeStart = m_pDoc->m_gmTime;
			}
		}
		else
		{
			m_gripping = FALSE;
			if (m_moving == FALSE)
			{
				m_pDoc->m_isMovement++;
			}
			m_moving = TRUE;

			if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
				&& m_pDoc->m_currentCommand != NULL)
			{
				m_timeStart = m_pDoc->m_currentCommand->m_time;
			}
			else
			{
				m_gmTimeStart = m_pDoc->m_gmTime;
			}
			sprintf(buf, "| %s OPEN", m_name);
		}
	}

	else if (toupper(buf[0]) == 'S' && toupper(buf[1]) == 'P')
	{
		i = sscanf(buf, "%*s %lf", &f[0]);

		if (i == 1)
		{
			f[0] = YO_MIN(f[0], 180.0);
			f[0] = YO_MAX(f[0], 0.0);

			m_fingerFixedStart[0] = m_spread;
			m_fingerFixedEnd[0] = f[0];
			m_spreading = TRUE;
			if (m_moving == FALSE)
			{
				m_pDoc->m_isMovement++;
			}
			m_moving = TRUE;

			if (m_pDoc->m_mode == YO_MODE_PLAY_SIM //&& m_pDoc->m_realTime == FALSE
				&& m_pDoc->m_currentCommand != NULL)
			{
				m_timeStart = m_pDoc->m_currentCommand->m_time;
			}
			else
			{
				m_gmTimeStart = m_pDoc->m_gmTime;
			}
			sprintf(buf, "| %s SPREAD %.2lf", m_name, f[0]);
		}

		else
		{
			sprintf(buf, "X");
		}
	}

	else if (toupper(buf[0]) == 'V' && toupper(buf[1]) == 'E')
	{
		i = sscanf(buf, "%*s %lf", &f[0]);

		if (i == 1)
		{
			f[0] = YO_MIN(f[0], 255.0);
			f[0] = YO_MAX(f[0], 0.1);

			m_velocity = f[0] * 3.0;
			sprintf(buf, "| %s VEL %.1lf", m_name, f[0]);
		}

		else
		{
			sprintf(buf, "X");
		}
	}

	else
	{
		sprintf(buf, "X");
	}

	return TRUE;
}


BOOL CStageBarrettHand::YoEStop()
{
	if (m_moving == TRUE)
	{
		if (m_spreading == TRUE)
		{
			m_spreading = FALSE;
		}
		m_moving = FALSE;
		m_pDoc->m_isMovement--;
	}

	return TRUE;
}


BOOL CStageBarrettHand::YoReadBarrettHand(FILE *fp, CStageBarrettHand *ptrBarrettHand)
{
	char				s[128];
	char				command[32];
	int					done = FALSE;
	int					ch = 0;
	int					i;
	char				partAttachName[64];
	CStagePart			*ptrPart = NULL;
	
	sprintf(partAttachName, "");
  
	while (!done)
	{
		// Read in single line from file
		memset(s, 0, 128);
		for (i = 0; (i < 127) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "BARRETT_HAND_NULL") == 0)
		{
			m_pDoc->YoInsertDevice(ptrBarrettHand, ptrPart);
			done = TRUE;
			return TRUE;
		}
		else if (strcmp(command, "BARRETT_HAND_NAME") == 0)
		{
			sscanf(s, "%*s %s", &ptrBarrettHand->m_name);
		}
		else if (strcmp(command, "BARRETT_HAND_PARENT") == 0)
		{
			sscanf(s, "%*s %s %s", &ptrBarrettHand->m_parent, &partAttachName);
			ptrPart = m_pDoc->YoPartLookup(ptrBarrettHand, partAttachName);
		}
		else if (strcmp(command, "BARRETT_HAND_VISIBLE") == 0)
		{
			sscanf(s, "%*s %d", &ptrBarrettHand->m_visible);
		}
		else if (strcmp(command, "BARRETT_HAND_MASS") == 0)
		{
			sscanf(s, "%*s %lf", &ptrBarrettHand->m_mass);
		}
		else if (strcmp(command, "BARRETT_HAND_BAR_CODE") == 0)
		{
			sscanf(s, "%*s %s", &ptrBarrettHand->m_barCode);
		}
		else if (strcmp(command, "BARRETT_HAND_GRIPPING") == 0)
		{
			sscanf(s, "%*s %d", &ptrBarrettHand->m_gripping);
		}
		else if (strcmp(command, "BARRETT_HAND_VELOCITY") == 0)
		{
			sscanf(s, "%*s %lf", &ptrBarrettHand->m_velocity);
		}
		else if (strcmp(command, "BARRETT_HAND_SPREAD") == 0)
		{
			sscanf(s, "%*s %lf", &ptrBarrettHand->m_spread);
		}
		else if (strcmp(command, "BARRETT_HAND_FINGER_FIXED") == 0)
		{
			sscanf(s, "%*s %lf %lf",
				&ptrBarrettHand->m_fingerFixed[1], &ptrBarrettHand->m_fingerFixed[2]);
		}
		else if (strcmp(command, "BARRETT_HAND_FINGER_LEFT") == 0)
		{
			sscanf(s, "%*s %lf %lf",
				&ptrBarrettHand->m_fingerLeft[1], &ptrBarrettHand->m_fingerLeft[2]);
		}
		else if (strcmp(command, "BARRETT_HAND_FINGER_RIGHT") == 0)
		{
			sscanf(s, "%*s %lf %lf",
				&ptrBarrettHand->m_fingerRight[1], &ptrBarrettHand->m_fingerRight[2]);
		}
		else
		{
			return FALSE;
		}
		
	} // end while (!done)
	return TRUE;
}


BOOL CStageBarrettHand::YoCalculateBHPosition()
{

	double timeElapsed;
	//SYSTEMTIME gmTime;
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	int tms;
	CTimeSpan spanSec;
	double timeFingerFixed[3];
	double timeFingerLeft[3];
	double timeFingerRight[3];

	// calculate time of rotation
	if (m_pDoc->m_mode == YO_MODE_PLAY_SIM)// && m_pDoc->m_realTime == FALSE)
	{
		timeElapsed = m_pDoc->m_timeCurrent - m_timeStart;	
	}
	else
	{
		timeCurrent = m_pDoc->m_gmTime;
		timeStart = m_gmTimeStart;
		spanSec = timeCurrent - timeStart;
		tms = m_pDoc->m_gmTime.wMilliseconds - m_gmTimeStart.wMilliseconds;
		timeElapsed = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
		TRACE1("BH timeElapsed = %.3lf\n", timeElapsed);
	}

	if (m_spreading == TRUE)
	{
		timeFingerFixed[0] = fabs((m_fingerFixedEnd[0] - m_fingerFixedStart[0]) / m_velocity);
		if (timeFingerFixed[0] <= timeElapsed)
		{
			m_spread = m_fingerFixedEnd[0];
		}
		else if (m_fingerFixedStart[0] <= m_fingerFixedEnd[0])
		{
			m_spread = m_fingerFixedStart[0] + (m_velocity * timeElapsed);
		}
		else
		{
			m_spread = m_fingerFixedStart[0] - (m_velocity * timeElapsed);
		}

		if (m_spread == m_fingerFixedEnd[0])
		{
			m_moving = FALSE;
			m_spreading = FALSE;
			m_pDoc->m_isMovement--;
		}
		return TRUE;
	}



	if (m_gripping == TRUE)
	{
		timeFingerFixed[1] = (m_fingerFixedEnd[1] - m_fingerFixedStart[1]) / m_velocity;
		if (timeFingerFixed[1] <= timeElapsed)
		{
			m_fingerFixed[1] = m_fingerFixedEnd[1];
			timeFingerFixed[2] = (m_fingerFixedEnd[2] - m_fingerFixedStart[2]) / m_velocity;
			if (timeFingerFixed[2] + timeFingerFixed[1] <= timeElapsed)
			{
				m_fingerFixed[2] = m_fingerFixedEnd[2];
			}
			else
			{
				m_fingerFixed[2] = m_fingerFixedStart[2] + (m_velocity * (timeElapsed - timeFingerFixed[1]));
			}
		}
		else
		{
			m_fingerFixed[1] = m_fingerFixedStart[1] + (m_velocity * timeElapsed);
		}

		timeFingerLeft[1] = (m_fingerLeftEnd[1] - m_fingerLeftStart[1]) / m_velocity;
		if (timeFingerLeft[1] <= timeElapsed)
		{
			m_fingerLeft[1] = m_fingerLeftEnd[1];
			timeFingerLeft[2] = (m_fingerLeftEnd[2] - m_fingerLeftStart[2]) / m_velocity;
			if (timeFingerLeft[2] + timeFingerLeft[1] <= timeElapsed)
			{
				m_fingerLeft[2] = m_fingerLeftEnd[2];
			}
			else
			{
				m_fingerLeft[2] = m_fingerLeftStart[2] + (m_velocity * (timeElapsed - timeFingerLeft[1]));
			}
		}
		else
		{
			m_fingerLeft[1] = m_fingerLeftStart[1] + (m_velocity * timeElapsed);
		}

		timeFingerRight[1] = (m_fingerRightEnd[1] - m_fingerRightStart[1]) / m_velocity;
		if (timeFingerRight[1] <= timeElapsed)
		{
			m_fingerRight[1] = m_fingerRightEnd[1];
			timeFingerRight[2] = (m_fingerRightEnd[2] - m_fingerRightStart[2]) / m_velocity;
			if (timeFingerRight[2] + timeFingerRight[1] <= timeElapsed)
			{
				m_fingerRight[2] = m_fingerRightEnd[2];
			}
			else
			{
				m_fingerRight[2] = m_fingerRightStart[2] + (m_velocity * (timeElapsed - timeFingerRight[1]));
			}
		}
		else
		{
			m_fingerRight[1] = m_fingerRightStart[1] + (m_velocity * timeElapsed);
		}
	}

	else // m_gripping == FALSE
	{
		timeFingerFixed[1] = fabs((m_fingerFixedEnd[1] - m_fingerFixedStart[1]) / m_velocity);
		if (timeFingerFixed[1] <= timeElapsed)
		{
			m_fingerFixed[1] = m_fingerFixedEnd[1];
		}
		else
		{
			m_fingerFixed[1] = m_fingerFixedStart[1] - (m_velocity * timeElapsed);
		}
		timeFingerFixed[2] = fabs((m_fingerFixedEnd[2] - m_fingerFixedStart[2]) / m_velocity);
		if (timeFingerFixed[2] <= timeElapsed)
		{
			m_fingerFixed[2] = m_fingerFixedEnd[2];
		}
		else
		{
			m_fingerFixed[2] = m_fingerFixedStart[2] - (m_velocity * timeElapsed);
		}

		timeFingerLeft[1] = fabs((m_fingerLeftEnd[1] - m_fingerLeftStart[1]) / m_velocity);
		if (timeFingerLeft[1] <= timeElapsed)
		{
			m_fingerLeft[1] = m_fingerLeftEnd[1];
		}
		else
		{
			m_fingerLeft[1] = m_fingerLeftStart[1] - (m_velocity * timeElapsed);
		}
		timeFingerLeft[2] = fabs((m_fingerLeftEnd[2] - m_fingerLeftStart[2]) / m_velocity);
		if (timeFingerLeft[2] <= timeElapsed)
		{
			m_fingerLeft[2] = m_fingerLeftEnd[2];
		}
		else
		{
			m_fingerLeft[2] = m_fingerLeftStart[2] - (m_velocity * timeElapsed);
		}

		timeFingerRight[1] = fabs((m_fingerRightEnd[1] - m_fingerRightStart[1]) / m_velocity);
		if (timeFingerRight[1] <= timeElapsed)
		{
			m_fingerRight[1] = m_fingerRightEnd[1];
		}
		else
		{
			m_fingerRight[1] = m_fingerRightStart[1] - (m_velocity * timeElapsed);
		}
		timeFingerRight[2] = fabs((m_fingerRightEnd[2] - m_fingerRightStart[2]) / m_velocity);
		if (timeFingerRight[2] <= timeElapsed)
		{
			m_fingerRight[2] = m_fingerRightEnd[2];
		}
		else
		{
			m_fingerRight[2] = m_fingerRightStart[2] - (m_velocity * timeElapsed);
		}
	}

	if (m_fingerFixed[1] == m_fingerFixedEnd[1] && m_fingerFixed[2] == m_fingerFixedEnd[2]
		&& m_fingerLeft[1] == m_fingerLeftEnd[1] && m_fingerLeft[2] == m_fingerLeftEnd[2]
		&& m_fingerRight[1] == m_fingerRightEnd[1] && m_fingerRight[2] == m_fingerRightEnd[2])
	{
		m_moving = FALSE;
		m_pDoc->m_isMovement--;
	}

	return TRUE;
}


void CStageBarrettHand::YoCloseHand(char deviceName[64])
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageDevice *currentDevice;
	CStagePart *currentPart;
	CStageDevice *ptrDevice;

	if ((ptrDevice = m_pDoc->YoDeviceHashLookup(deviceName)) == NULL)
	{
		return;
	}

	currentDevice = m_pDoc->m_currentDevice;
	currentPart = m_pDoc->m_currentPart;
	m_pDoc->m_currentDevice = ptrDevice;
	m_pDoc->m_currentPart = ptrDevice->m_ptrPart;

	m_pDoc->YoDetachDevice();

	m_pDoc->YoAttachDevice(this->m_ptrPart);

	m_pDoc->m_currentDevice = currentDevice;
	m_pDoc->m_currentPart = currentPart;

	return;
}


CStageDevice *CStageBarrettHand::YoFindDeviceToGrab()
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return NULL;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return NULL;
	}
	double m[16];
	double n[16];
	RECT vrect;
	CStageDevice *currentDevice;
	CStagePart *currentPart;
	CStageDevice *ptrDevice;
	CPoint pt;
	BOOL visible;

	currentDevice = m_pDoc->m_currentDevice;
	currentPart = m_pDoc->m_currentPart;

	m_pDoc->m_currentDevice = this;
	m_pDoc->m_currentPart = m_ptrPart;
	m_pDoc->YoModelMatrixOfCurrentPart(m);

	visible = m_visible;
	m_visible = FALSE;

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	
	::glLoadIdentity();
	::glMultMatrixd(m);
	::glTranslated(0.0, 0.0, 1000.0);
	::glGetDoublev(GL_MODELVIEW_MATRIX, n);

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::glFrustum(-40.0, 40.0, -25.0, 25.0, m_ptrPart->m_max[2] - 1.0, m_ptrPart->m_max[2] + 50.0);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	if (m[12] == n[12] && m[13] == n[13])
	{
		::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, 0.999, -0.01);
	}
	else
	{
		::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, -0.01, .999);
	}

	pView->YoRender(YO_RENDER_PICK_PART);
	//::SwapBuffers(pView->m_pDC->GetSafeHdc());
	//Sleep(8000);

	pView->GetWindowRect(&vrect);
	pt.x = (long)((vrect.right - vrect.left) / 2.0);
	pt.y = (long)((vrect.bottom - vrect.top) / 2.0);

	if (m_pDoc->YoMakeCurrentDevicePartTag(pt) == YO_DEVICE_PART)
	{
		ptrDevice = m_pDoc->m_currentDevice;
		m_pDoc->YoDetachDevice();
		m_pDoc->YoAttachDevice(this->m_ptrPart);
	}
	else
	{
		ptrDevice = NULL;
	}

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
		pView->m_clipFront, pView->m_clipRear);
	::glMatrixMode(GL_MODELVIEW);
	::glPopMatrix();

	m_visible = visible;

	m_pDoc->m_currentDevice = currentDevice;
	m_pDoc->m_currentPart = currentPart;

	return ptrDevice;
}


BOOL CStageBarrettHand::YoPositionFinger(CStagePart *ptrPart)
// transforms current modelView matrix to reflect finger rotation of ptrPart
// make certain that glMatrixMode has been set to GL_MODELVIEW before calling this routine
{

	if (strcmp(ptrPart->m_partName, "F3") == 0)
	{
		::glRotated(m_fingerFixed[1], 0.0, 0.0, 1.0);
	}
	else if (strcmp(ptrPart->m_partName, "J32") == 0)
	{
		::glRotated(m_fingerFixed[2], 0.0, 0.0, 1.0);
	}
	else if (strcmp(ptrPart->m_partName, "J21") == 0)
	{
		::glRotated(m_spread, 0.0, 0.0, 1.0);
	}
	else if (strcmp(ptrPart->m_partName, "F2") == 0)
	{
		::glRotated(m_fingerLeft[1], 0.0, 0.0, 1.0);
	}
	else if (strcmp(ptrPart->m_partName, "J22") == 0)
	{
		::glRotated(m_fingerLeft[2], 0.0, 0.0, 1.0);
	}
	else if (strcmp(ptrPart->m_partName, "J11") == 0)
	{
		::glRotated(-m_spread, 0.0, 0.0, 1.0);
	}
	else if (strcmp(ptrPart->m_partName, "F1") == 0)
	{
		::glRotated(m_fingerRight[1], 0.0, 0.0, 1.0);
	}
	else if (strcmp(ptrPart->m_partName, "J12") == 0)
	{
		::glRotated(m_fingerRight[2], 0.0, 0.0, 1.0);
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}


void CStageBarrettHand::YoOpenHand(void)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CStageDevice *currentDevice;
	CStageDevice *ptrDevice;
	CStageDevice *ptrToDevice;
	CStagePart *currentPart;
	CStagePart *ptrPart;
	CStagePart *ptrToPart;
	double maxDistance;
	double m[16];
	RECT vrect;
	CPoint pt;
	BOOL visible;
	BOOL visibleGrip;

	if (m_gripping == TRUE && m_down != NULL
		&& (ptrDevice = YoFindDeviceToGrab()) != NULL)
	{
		currentDevice = m_pDoc->m_currentDevice;
		currentPart = m_pDoc->m_currentPart;

		m_pDoc->m_currentDevice = this;
		m_pDoc->m_currentPart = m_ptrPart;
		m_pDoc->YoModelMatrixOfCurrentPart(m);

		// move camera out just past faceplate of hand
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();
		::glMultMatrixd(m);
		::glTranslated(0.0, 0.0, 120.0);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m);

		visibleGrip = ptrDevice->m_visible;
		ptrDevice->m_visible = FALSE;
		visible = m_visible;
		m_visible = FALSE;

		maxDistance = YO_MAX(ptrDevice->m_ptrPart->m_max[0] - ptrDevice->m_ptrPart->m_min[0],
			ptrDevice->m_ptrPart->m_max[1] - ptrDevice->m_ptrPart->m_min[1]);
		maxDistance = YO_MAX(maxDistance,
			ptrDevice->m_ptrPart->m_max[2] - ptrDevice->m_ptrPart->m_min[2]);

		ptrPart = ptrDevice->m_ptrPart;

		// if device that is being released is above another device (z axis)
		// attach it to the other device
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::glFrustum(-40.0, 40.0, -25.0, 25.0, 1.0, maxDistance + 25.0);
		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		//if (m[12] == n[12] && m[13] == n[13])
		//{
		//	::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, 0.999, -0.01);
		//}
		//else
		//{
		//	::gluLookAt(m[12], m[13], m[14], n[12], n[13], n[14], 0.01, -0.01, .999);
		//}
		::gluLookAt(m[12], m[13], m[14], m[12], m[13], m[14] - 100.0, 0.01, 0.999, -0.01);

		pView->YoRender(YO_RENDER_PICK_PART);
		//::SwapBuffers(pView->m_pDC->GetSafeHdc());
		//Sleep(8000);

		m_visible = visible;
		ptrDevice->m_visible = visibleGrip;

		pView->GetWindowRect(&vrect);
		pt.x = (long)((vrect.right - vrect.left) / 2.0);
		pt.y = (long)((vrect.bottom - vrect.top) / 2.0);

		if (m_pDoc->YoMakeCurrentDevicePartTag(pt) == YO_DEVICE_PART
			&& (m_pDoc->YoIsChild(this, m_pDoc->m_currentDevice)) == FALSE)
		{
			ptrToDevice = m_pDoc->m_currentDevice;
			ptrToPart = m_pDoc->m_currentPart;

			m_pDoc->m_currentDevice = ptrDevice;
			m_pDoc->m_currentPart = ptrPart;
			m_pDoc->YoDetachDevice();
			m_pDoc->YoAttachDevice(ptrToPart);
		}
		else
		{
			m_pDoc->m_currentDevice = ptrDevice;
			m_pDoc->m_currentPart = ptrPart;
			m_pDoc->YoDetachDevice();
			// reattach device at world coords (rightmost position)
			for (ptrDevice = m_pDoc->m_deviceList;
				ptrDevice->m_right != NULL;
				ptrDevice = ptrDevice->m_right);
			ptrDevice->m_right = m_pDoc->m_currentDevice;
			m_pDoc->m_currentDevice->m_left = ptrDevice;
		}

		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(pView->m_fieldOfView, pView->m_aspectRatio,
			pView->m_clipFront, pView->m_clipRear);
		::glMatrixMode(GL_MODELVIEW);
		::glPopMatrix();

		m_pDoc->m_currentDevice = currentDevice;
		m_pDoc->m_currentPart = currentPart;
	}

	return;
}


void CStageCommand::YoInsertCommand()
{

	if (m_pDoc->m_commandList == NULL)
	{
		m_pDoc->m_commandList = this;
		m_pDoc->m_currentCommand = this;
	}
	else
	{
		m_pDoc->m_currentCommand->m_next = this;
		m_pDoc->m_currentCommand = this;
	}

	return;
}


void CStageCommand::YoReadCommands(FILE *fp)
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CWnd *pCBox;
	int i;
	char s[256];
	char command[32];
	int ch = 0;
	CStageCommand *ptrCommand;


	while(TRUE)
	{
		// Read in single line from file
		memset(s, 0, 256);
		for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
			&& (ch != '\n'); i++)
		{
			s[i] = (char)ch;
		}
		if (s[i] != EOF)
		{
			s[i] = '\0';
		}

		sscanf(s, "%s", command);

		if (s[0] == '#') 
		{
			// line is a comment--ignore
		}
		else if (strcmp(command, "COMMAND_LIST_NULL") == 0)
		{
			m_pDoc->m_currentCommand = m_pDoc->m_commandList;
			return;
		}
		else
		{
			if (strcmp(command, "SIMULATION_BEGIN") != 0)
			{
				ptrCommand = new CStageCommand(m_pDoc);
				sprintf(ptrCommand->m_buf, "%s", s);
			}
			else
			{
				sprintf(m_buf, "SIMULATION_BEGIN");
			}

			// Read in the next line from file
			memset(s, 0, 256);
			for (i = 0; (i < 255) && ((ch = fgetc(fp)) != EOF)
				&& (ch != '\n'); i++)
			{
				s[i] = (char)ch;
			}
			if (s[i] != EOF)
			{
				s[i] = '\0';
			}

			if (strcmp(command, "SIMULATION_BEGIN") != 0)
			{
				sscanf(s, "%lf", &ptrCommand->m_time);
				ptrCommand->YoInsertCommand();
				if (strcmp(command, "SIMULATION_END") == 0)
				{
					m_pDoc->m_timeEnd = ptrCommand->m_time;
					pCBox = (CComboBox*)((pMainFrame)->m_wndDlgBarTop).GetDlgItem(IDC_TIME);
					((CSliderCtrl *)pCBox)->SetRange(0, (int)m_pDoc->m_timeEnd);
					//((CSliderCtrl *)pCBox)->SetPos(0);

				}
			}
			else
			{
				m_time = 0.0f;
				//YoInsertCommand();
			}
		}
	}

	return;
}


void CStageCommand::YoWriteCommands(FILE *fp)
{
	CTime timeStart = CTime::GetCurrentTime();
	CTime timeCurrent = CTime::GetCurrentTime();
	int tms;
	CTimeSpan spanSec;
	CStageCommand *curCommand;
	char s[256];

	if (fp == NULL)
	{
		return;
	}

	fprintf(fp, "COMMAND_LIST\n");

	for (curCommand = m_pDoc->m_commandList; curCommand != NULL; curCommand = curCommand->m_next)
	{
		if (curCommand == m_pDoc->m_commandList)
		{
			fprintf(fp, "SIMULATION_BEGIN\n");
			fprintf(fp, "0.0\n");
			if (m_pDoc->m_mode == YO_MODE_RECORD_SIM)
			{
				timeStart = curCommand->m_gmTime;
			}
		}

		else
		{
			if (m_pDoc->m_mode == YO_MODE_RECORD_SIM)
			{
				timeCurrent = curCommand->m_gmTime;
				spanSec = timeCurrent - timeStart;
				tms = curCommand->m_gmTime.wMilliseconds - m_pDoc->m_commandList->m_gmTime.wMilliseconds;
				curCommand->m_time = (double)(spanSec.GetTotalSeconds()) + ((double)tms / 1000.0);
			}
			sscanf(curCommand->m_buf, "%s", s);
			if (strcmp(s, "-sleep") == 0)
			{
				// ignore sleep messages in sim file
			}
			else
			{
				fprintf(fp, "%s\n", curCommand->m_buf);
				fprintf(fp, "%lf\n", curCommand->m_time);
			}
		}
	}

	fprintf(fp, "COMMAND_LIST_NULL\n");

	return;
}


void CStageUndo::YoUndo(void)
// performs undo task based on m_undoMode, then turns off undo mode
{
	POSITION pos = m_pDoc->GetFirstViewPosition();
	if (pos == NULL)
	{
		return;
	}
	CStageView *pView = (CStageView *)m_pDoc->GetNextView(pos);
	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return;
	}
	CMainFrame *pMainFrame = (CMainFrame *)pView->GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	char s[512];


	if (m_pDoc->m_deviceBeingAttached == TRUE)
	{
		m_pDoc->m_deviceBeingAttached = FALSE;
		SetClassLong(pView->m_hWnd, GCL_HCURSOR, (long)pMainFrame->m_hCursorArrow);
		sprintf(s, "Device attach aborted.");
		m_pDoc->YoMessage(s);
		return;
	}

	if (m_undoMode == YO_UNDO_DEVICE_DELETE
		&& m_pDoc->m_undo->m_undoDeviceDelete != NULL)
	{
		m_pDoc->m_currentDevice = m_pDoc->m_undo->m_undoDeviceDelete;
		m_pDoc->YoDeleteDevice();
		m_pDoc->m_undo->m_undoDeviceDelete = NULL;
	}
	else if (m_undoMode == YO_UNDO_PART_DELETE
		&& m_pDoc->m_undo->m_undoPartDelete != NULL)
	{
		m_pDoc->m_currentPart = m_pDoc->m_undo->m_undoPartDelete;
		m_pDoc->YoDeletePart();
		m_pDoc->m_undo->m_undoPartDelete = NULL;
	}
	else if (m_undoMode == YO_UNDO_PART_UPDATE
		&& m_pDoc->m_undo->m_undoPartDelete != NULL)
	{
		m_pDoc->m_undo->m_undoPartDelete->m_displayListID = -1;
		delete m_pDoc->m_undo->m_undoPartDelete;
		m_pDoc->m_undo->m_undoPartDelete = NULL;
	}
	else if (m_undoMode == YO_UNDO_PATH_DELETE
		&& m_pDoc->m_undo->m_undoTagDelete != NULL)
	{
		m_pDoc->YoDeletePath(m_pDoc->m_undo->m_undoTagDelete);
		m_pDoc->m_undo->m_undoTagDelete = NULL;
	}
	else if (m_undoMode == YO_UNDO_TAG_DELETE
		&& m_pDoc->m_undo->m_undoTagDelete != NULL)
	{
		m_pDoc->m_currentTag = m_pDoc->m_undo->m_undoTagDelete;
		m_pDoc->YoDeleteTag();
		m_pDoc->m_undo->m_undoTagDelete = NULL;
	}
	else if (m_undoMode == YO_UNDO_FILE_REVERT)
	{
		sprintf(s, "%s.UNDO", m_pDoc->m_fileName);
		::DeleteFile((LPCTSTR)s);
	}

	m_pDoc->m_undo->m_undoMode = YO_UNDO_OFF;
	m_pDoc->YoMessage("");

	return;
}

void CStageDoc::YoChangeTime(SYSTEMTIME *gmTime, double sec)
{
	CTime timeCurrent = CTime::GetCurrentTime();
	CTimeSpan spanSec;
	int ms;
	int gmTimems;

	if (sec == 0.0)
	{
		return;
	}

	ms = (int)((sec - (double)(int)sec) * 1000.0);
	timeCurrent = *gmTime;

	gmTimems = gmTime->wMilliseconds + ms;

	if (gmTimems >= 1000)
	{
		gmTime->wMilliseconds = gmTimems - 1000;
		spanSec = (int)sec + 1;
	}
	else if (gmTimems < 0)
	{
		gmTime->wMilliseconds = gmTimems + 1000;
		spanSec = (int)sec - 1;
	}
	else
	{
		gmTime->wMilliseconds = gmTimems;
		spanSec = (int)sec;
	}

	timeCurrent += spanSec;

	gmTime->wYear = timeCurrent.GetYear();
	gmTime->wMonth = timeCurrent.GetMonth();
	gmTime->wDay = timeCurrent.GetDay();
	gmTime->wDayOfWeek = timeCurrent.GetDayOfWeek();
	gmTime->wHour = timeCurrent.GetHour();
	gmTime->wMinute = timeCurrent.GetMinute();
	gmTime->wSecond = timeCurrent.GetSecond();

	TRACE3("YoChangeTime(%d, %d, %d, ", gmTime->wYear, gmTime->wMonth, gmTime->wDay);
	TRACE2("%d, %d, ", gmTime->wHour, gmTime->wMinute);
	TRACE3("%d, %d)   sec = %.3lf\n", gmTime->wSecond, gmTime->wMilliseconds, sec);


	return;
}


