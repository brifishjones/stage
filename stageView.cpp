// stageView.cpp : implementation of the CStageView class
//

#include "stdafx.h"
#include "stage.h"

#include "stageDoc.h"
#include "stageView.h"
#include "stageEyeDialog.h"
#include "stageViewPart.h"
#include "stageAnalysisDlg.h"
#include "stageViewTag.h"
#include "stageTrackDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/***
UINT YoThreadRender(LPVOID pParam)
{
	CStageView *pView = (CStageView*)pParam;

	if (pView == NULL || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
	{
		return 1;     // illegal parameter
	}

	pView->YoRender(YO_RENDER_FULL);

	return 0;
}
***/



/////////////////////////////////////////////////////////////////////////////
// CStageView

IMPLEMENT_DYNCREATE(CStageView, CView)

BEGIN_MESSAGE_MAP(CStageView, CView)
	//{{AFX_MSG_MAP(CStageView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStageView construction/destruction

CStageView::CStageView()
{
	// TODO: add construction code here
	TRACE0("CStageView::CStageView()\n");
	int i;

	m_hRC = NULL;
	m_pDC = NULL;
	m_fp = NULL;

	x0 = 0;               // beginning mouse x coordinate
	y0 = 0;               // beginning mouse y coordinate
	m_mouse = 0;
	m_walkSpeed = 0.0;
	m_panInOutSpeed = 0.0;
	m_panLeftRightUpDownSpeed = 0.0;

	m_fieldOfView = 0.0;
	m_aspectRatio = 0.0;
	m_clipFront = 0.0;
	m_clipRear = 0.0;

	for (i = 0; i < 2; i++)
	{
		m_viewportSize[i] = 0;
		m_windowSize[i] = 0;
	}

	for (i = 0; i < 3; i++)
	{
		m_rasterPos[i] = 0.0;
		m_originalTranslate[i] = 0.0;
	}

	for (i = 0; i < 6; i++)
	{
		m_windowSizeInWorldCoords[i] = 0.0;
		m_originalEye[i] = 0.0;
	}

	for (i = 0; i < 9; i++)
	{
		m_eye[i] = 0.0;
	}

	for (i = 0; i < 16; i++)
	{
		m_viewInv[i] = 0.0;
		m_mBase[i] = 0.0;
	}

}

CStageView::~CStageView()
{
	TRACE0("CStageView::~CStageView()\n");
}

BOOL CStageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// An OpenGL window must be created with the following
	// flags and must not include CS_PARENTDC for
	// the class style.

	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStageView drawing

void CStageView::OnDraw(CDC* pDC)
{
	TRACE0("CStageView::OnDraw()\n");
	CStageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	YoRender(YO_RENDER_LIGHT);
	YoRender(YO_RENDER_FULL);
}

/////////////////////////////////////////////////////////////////////////////
// CStageView printing

BOOL CStageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CStageView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CStageView diagnostics

#ifdef _DEBUG
void CStageView::AssertValid() const
{
	CView::AssertValid();
}

void CStageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStageDoc* CStageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStageDoc)));
	return (CStageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStageView message handlers

int CStageView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	YoInitOpenGL();

	if (CView::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	
	return 0;
}

void CStageView::OnDestroy() 
{	
	//HGLRC	hrc;

	m_hRC = ::wglGetCurrentContext();

    ::wglMakeCurrent(NULL, NULL);

    if (m_hRC)
	{
        ::wglDeleteContext(m_hRC);
	}

    //if (hrc)
	//{
    //    ::wglDeleteContext(hrc);
	//}

    if (m_pDC)
	{
        delete m_pDC;
	}

	CView::OnDestroy();	
}

void CStageView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if ( 0 >= cx || 0 >= cy )
	{
		return;
	}

/****
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	RECT rect;
	RECT vrect;
	BOOL tooSmall = FALSE;

	pMainFrame->GetWindowRect(&rect);
	GetWindowRect(&vrect);

	if (cx < 320)
	{
		m_windowSize[0] = 320;
		m_viewportSize[0] = 320;
		rect.right += (320 - (vrect.right - vrect.left) + 4);
		tooSmall = TRUE;
	}
	else
	{
		m_windowSize[0] = cx;
		m_viewportSize[0] = cx;
	}

	if (cy < 240)
	{
		m_windowSize[1] = 240;
		m_viewportSize[1] = 240;
		rect.bottom += (240 - (vrect.bottom - vrect.top) + 4);
		tooSmall = TRUE;
	}
	else
	{
		m_windowSize[1] = cy;
		m_viewportSize[1] = cy;
	}

	if (tooSmall)
	{
		pMainFrame->MoveWindow(&rect, TRUE);
	}
	/****

	//For Testing only
	/***
	m_viewportSize[0] = 320;
	m_viewportSize[1] = 240;

	if (m_viewportSize[0] <= cx && m_viewportSize[1] <= cy)
	{
		//::glViewport((cx - m_viewportSize[0]) / 2,
		//	(cy - m_viewportSize[1]) / 2,
		::glViewport(0, 0,
			m_viewportSize[0], m_viewportSize[1]);
		m_aspectRatio = (GLdouble)m_viewportSize[0] / (GLdouble)m_viewportSize[1]; 
	}
	else
	{
		::glViewport(0, 0, cx, cy);
		m_aspectRatio = (GLdouble)cx / (GLdouble)cy;
	}
	***/

	m_windowSize[0] = cx;
	m_viewportSize[0] = cx;
	m_windowSize[1] = cy;
	m_viewportSize[1] = cy;

	::glViewport(0, 0, cx, cy);
	m_aspectRatio = (GLdouble)cx / (GLdouble)cy;

	// select the projection matrix and clear it
    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();

	
	// select the viewing volume
	::gluPerspective(m_fieldOfView, m_aspectRatio,
		m_clipFront, m_clipRear);
	
	// switch back to the modelview matrix
    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();

	// now perform any viewing transformations
	::gluLookAt(m_eye[0], m_eye[1], m_eye[2],
		m_eye[3], m_eye[4], m_eye[5],
		m_eye[6], m_eye[7], m_eye[8]);

}

void CStageView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonDown(nFlags, point);

	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageDevice *ptrDevice;
	CStagePart *ptrPart;
	char s[128];
	GLdouble m[16];
	GLdouble		modelView[16];
	GLdouble		proj[16];
	GLint			viewport[4];
	GLdouble	winx;
	GLdouble	winy;
	GLdouble	winz;
	GLdouble	xLeft;
	GLdouble	yLeft;
	GLdouble	zLeft;
	GLdouble	xRight;
	GLdouble	yRight;
	GLdouble	zRight;
	GLdouble	xTop;
	GLdouble	yTop;
	GLdouble	zTop;
	GLdouble	xBottom;
	GLdouble	yBottom;
	GLdouble	zBottom;
	double        x;
	double        y;
	double        z;
	double        r;
	double        phi;
	int i;
	
	TRACE3("CStageView::OnLButtonDown() -- eye from(%.2lf, %.2lf, %.2lf\n",
		m_eye[0], m_eye[1], m_eye[2]);

	if (pDoc->m_mode != YO_MODE_WORKCELL
		|| (pDoc->m_currentDevice != NULL
		&& pDoc->m_currentDevice->m_type == YO_CAMERA
		&& ((CStageCamera *)pDoc->m_currentDevice)->m_enabled == TRUE))
	{
		return;
	}

	SetCapture();
	m_mouse = YO_MOUSE_LEFT;
	x0 = point.x;
	y0 = -point.y;
	p0 = point;

	if (pDoc->m_deviceBeingAttached == FALSE)
	{
		pDoc->m_undo->YoUndo();
	}

	if (m_mode == YO_MODE_WALK || m_mode == YO_MODE_PAN)
	{
		for (i = 0; i < 9; i++)
		{
			pDoc->m_undo->m_undoEye[i] = m_eye[i];
		}
	}

	if (m_mode == YO_MODE_DEVICE_TRANSLATE)
	//if (h = GetKeyState(VK_CONTROL)&0x1000)
	// signifies device translate
	// high order bit = 1 means key down
	{
		sprintf(s, "Translating %s...", pDoc->m_currentDevice->m_name);
		pDoc->YoMessage(s);
		pDoc->m_undo->m_undoPartTranslate[0] = pDoc->m_currentDevice->m_ptrPart->m_translate[0];
		pDoc->m_undo->m_undoPartTranslate[1] = pDoc->m_currentDevice->m_ptrPart->m_translate[1];
		pDoc->m_undo->m_undoPartTranslate[2] = pDoc->m_currentDevice->m_ptrPart->m_translate[2];

		if (pDoc->m_currentDevice->m_ptrPart->m_txyz != YO_TXYZ_TXYZ)
		{
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadIdentity();
			YoTxyz(pDoc->m_currentDevice->m_ptrPart,
				pDoc->m_currentDevice->m_ptrPart->m_translate,
				pDoc->m_currentDevice->m_ptrPart->m_rotate);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			pDoc->YoTranslateRotateValues(m,
				pDoc->m_currentDevice->m_ptrPart->m_translate,
				pDoc->m_currentDevice->m_ptrPart->m_rotate);
			pDoc->m_currentDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
			::glPopMatrix();
		}
		if (strcmp(pDoc->m_currentDevice->m_parent, "NONE") != 0)
		{
			sprintf(s, "%s", pDoc->m_currentDevice->m_parent);
			ptrPart = pDoc->m_currentDevice->m_attachedFromPart;

			//pMainFrame->SendMessage(WM_COMMAND, ID_DEVICE_DETACH, (LPARAM)0);
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

			// need parent for reattachment after device move
			sprintf(pDoc->m_currentDevice->m_parent, "%s", s);
			pDoc->m_tempAttachedFromPart = ptrPart;
		}


		::glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
		::glGetDoublev(GL_PROJECTION_MATRIX, proj);
		::glGetIntegerv(GL_VIEWPORT, viewport);

		gluProject(pDoc->m_currentDevice->m_ptrPart->m_translate[0],
			pDoc->m_currentDevice->m_ptrPart->m_translate[1],
			pDoc->m_currentDevice->m_ptrPart->m_translate[2],
			modelView,
			proj,
			viewport,
			&winx,
			&winy,
			&winz);
						
		::gluUnProject(0.0,
			winy,
			winz,
			modelView,
			proj,
			viewport,
			&xLeft,
			&yLeft,
			&zLeft);
		::gluUnProject((GLdouble)m_windowSize[0] - 1.0,
			winy,
			winz,
			modelView,
			proj,
			viewport,
			&xRight,
			&yRight,
			&zRight);
		::gluUnProject(winx,
			0.0,
			winz,
			modelView,
			proj,
			viewport,
			&xBottom,
			&yBottom,
			&zBottom);
		::gluUnProject(winx,
			(GLdouble)m_windowSize[1] - 1.0,
			winz,
			modelView,
			proj,
			viewport,
			&xTop,
			&yTop,
			&zTop);

		x = m_eye[0] - m_eye[3];
		y = m_eye[1] - m_eye[4];
		z = fabs(m_eye[2] - m_eye[5]);

		r = sqrt(x * x + y * y);

		if (r != 0.0)
		{
			phi = atan2(z, r);
		}
		else if (z > 0.0)
		{
			phi = PI / 2.0;
		}
		else
		{
			phi = 0.0;
		}

		m_originalTranslate[0] = pDoc->m_currentDevice->m_ptrPart->m_translate[0];
		m_originalTranslate[1] = pDoc->m_currentDevice->m_ptrPart->m_translate[1];
		m_windowSizeInWorldCoords[0] = (xRight - xLeft);
		m_windowSizeInWorldCoords[1] = (yRight - yLeft);
		m_windowSizeInWorldCoords[2] = (xTop - xBottom);
		m_windowSizeInWorldCoords[3] = (yTop - yBottom);

		m_mode = YO_MODE_DEVICE_TRANSLATE;
	}
	else if (m_mode == YO_MODE_PAN)
	{
		::glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
		::glGetDoublev(GL_PROJECTION_MATRIX, proj);
		::glGetIntegerv(GL_VIEWPORT, viewport);

		gluProject(m_eye[3],
			m_eye[4],
			m_eye[5],
			modelView,
			proj,
			viewport,
			&winx,
			&winy,
			&winz);
						
		::gluUnProject(0.0,
			winy,
			winz,
			modelView,
			proj,
			viewport,
			&xLeft,
			&yLeft,
			&zLeft);
		::gluUnProject((GLdouble)m_windowSize[0] - 1.0,
			winy,
			winz,
			modelView,
			proj,
			viewport,
			&xRight,
			&yRight,
			&zRight);
		::gluUnProject(winx,
			0.0,
			winz,
			modelView,
			proj,
			viewport,
			&xBottom,
			&yBottom,
			&zBottom);
		::gluUnProject(winx,
			(GLdouble)m_windowSize[1] - 1.0,
			winz,
			modelView,
			proj,
			viewport,
			&xTop,
			&yTop,
			&zTop);
		for (i = 0; i < 6; i++)
		{
			m_originalEye[i] = m_eye[i];
		}
		m_windowSizeInWorldCoords[0] = (xRight - xLeft);
		m_windowSizeInWorldCoords[1] = (yRight - yLeft);
		m_windowSizeInWorldCoords[2] = (zRight - zLeft);
		m_windowSizeInWorldCoords[3] = (xTop - xBottom);
		m_windowSizeInWorldCoords[4] = (yTop - yBottom);
		m_windowSizeInWorldCoords[5] = (zTop - zBottom);
	}

	return;
}

void CStageView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnRButtonDown(nFlags, point);

	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	int i;

	if (pDoc->m_mode != YO_MODE_WORKCELL
		|| (pDoc->m_currentDevice != NULL
		&& pDoc->m_currentDevice->m_type == YO_CAMERA
		&& ((CStageCamera *)pDoc->m_currentDevice)->m_enabled == TRUE))
	{
		return;
	}

	if (pDoc->m_deviceBeingAttached == FALSE)
	{
		pDoc->m_undo->YoUndo();
	}
	
	for (i = 0; i < 6; i++)
	{
		pDoc->m_undo->m_undoEye[i] = m_eye[i];
	}

	SetCapture();
	m_mouse = YO_MOUSE_RIGHT;
	x0 = point.x;
	y0 = point.y;
	p0 = point;
	return;
}

void CStageView::OnLButtonUp(UINT nFlags, CPoint point) 
{	
	CView::OnLButtonUp(nFlags, point);

	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	GLdouble m[16];
	GLdouble mInv[16];
	GLdouble		modelView[16];
	GLdouble		proj[16];
	GLint			viewport[4];
	GLdouble objx;
	GLdouble objy;
	GLdouble objz;
	double        x;
	double        y;
	double        z;
	double        r;
	double theta;
	double        phi;
	char s[256];
	GLfloat p[1];
	int i;
	int index;
	CWnd *pCBox;
	//CStageVertices ptrVertices = NULL;
	//CStageTexture ptrTexture = NULL;
	//int *numberSides;
	CStagePolygonList *currentPolygonList;
	CStagePart *ptrPart;
	CStagePart *currentPart;
	CStageDevice *ptrDevice;
	CStageDevice *currentDevice;
	CStageTag *ptrTag;
	CDialog *ptrDlg;
	int snapToMode;

	TRACE0("CStageView::OnLButtonUp()\n");
	
	if (pDoc->m_mode != YO_MODE_WORKCELL
		|| (pDoc->m_currentDevice != NULL
		&& pDoc->m_currentDevice->m_type == YO_CAMERA
		&& ((CStageCamera *)pDoc->m_currentDevice)->m_enabled == TRUE))
	{
		return;
	}

	if(GetCapture( ) != this )
	{
		return;
	}

	ReleaseCapture( );

	if (pDoc->m_acceptSocket != NULL)
	{
		if (point.x == p0.x && point.y == p0.y && pDoc->m_deviceList != NULL)
		{
			YoRender(YO_RENDER_PICK_PART_AND_TAG);
			//if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART
			//	&& pDoc->m_boundingBox == TRUE)
			{
				i = pDoc->YoMakeCurrentDevicePartTag(point);
				if (i == YO_DEVICE_PART)
				{
					sprintf(s, "Device: %s   Part: %s",
						pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
					pDoc->YoMessage(s);
				}
				else if (i == YO_TAG)
				{
					sprintf(s, "Path: %s   Tag: %d",
						pDoc->m_currentTag->m_ptrPath->m_name, pDoc->m_currentTag->m_tag);
					pDoc->YoMessage(s);
				}
			}
		}

		YoRender(YO_RENDER_LIGHT);
		YoRender(YO_RENDER_FULL);
		return;
	}

	if (point.x == p0.x && point.y == p0.y)
	{
		//if (pMainFrame->m_viewPartActive == TRUE
		//	&& pDoc->m_currentDevice->m_type != YO_LIGHT)
		//{
		//	return;
		//}

		if (pDoc->m_deviceList != NULL && pDoc->m_deviceBeingAttached == TRUE
			&& pMainFrame->m_gripperDlgActive == TRUE)
		{
			currentDevice = pDoc->m_currentDevice;
			currentPart = pDoc->m_currentPart;
			YoRender(YO_RENDER_PICK_PART);
			if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART
				&& currentDevice != pDoc->m_currentDevice)
			{
				pDoc->YoDetachDevice();

				sprintf(pDoc->m_currentDevice->m_parent, "%s", 
					currentDevice->m_name);
				pDoc->YoAttachDevice(currentDevice->m_ptrPart);
			}
			pDoc->m_currentDevice = currentDevice;
			pDoc->m_currentPart = currentPart;
			pDoc->m_deviceBeingAttached = FALSE;
			((CStageGripper *)pDoc->m_currentDevice)->m_gripping = TRUE;
			SetClassLong(m_hWnd, GCL_HCURSOR, (long)pMainFrame->m_hCursorArrow);
			YoRender(YO_RENDER_FULL);
			return;
		}
		else if (pDoc->m_deviceList != NULL && pDoc->m_deviceBeingAttached == TRUE
			&& pMainFrame->m_gripperDlgActive == FALSE)
		{
			currentDevice = pDoc->m_currentDevice;
			currentPart = pDoc->m_currentPart;
			YoRender(YO_RENDER_PICK_PART);
			if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART)
			{
				if (currentDevice == pDoc->m_currentDevice
					|| pDoc->YoIsChild(currentDevice, pDoc->m_currentDevice))
				{
					pDoc->m_currentDevice = currentDevice;
					pDoc->m_currentPart = currentPart;
					sprintf(s, "ERROR: Device %s cannot be attached to itself or its children",
						pDoc->m_currentDevice->m_name);
					pDoc->YoMessage(s);
				}
				else
				{
					ptrPart = pDoc->m_currentPart;
					ptrDevice = pDoc->m_currentDevice;
					//if (pDoc->m_currentPart == pDoc->m_currentDevice->m_ptrPart)
					//{
					//	ptrPart = NULL;
					//}
					pDoc->m_currentDevice = currentDevice;
					pDoc->m_currentPart = currentPart;
					//if (strcmp(pDoc->m_currentDevice->m_parent, "NONE") != 0)
					//{
						pDoc->YoDetachDevice();
						//if (pDoc->m_deviceList == NULL)
						//{
						//	pDoc->m_deviceList = pDoc->m_currentDevice;
						//	return;
						//}

						// reattach device at world coords (rightmost position)
						//for (currentDevice = pDoc->m_deviceList;
						//	currentDevice->m_right != NULL;
						//	currentDevice = currentDevice->m_right);
						//currentDevice->m_right = pDoc->m_currentDevice;
						//pDoc->m_currentDevice->m_left = currentDevice;

					//}
					sprintf(pDoc->m_currentDevice->m_parent, "%s", 
						ptrDevice->m_name);
					pDoc->YoAttachDevice(ptrPart);
					sprintf(s, "Device %s attached to %s",
						pDoc->m_currentDevice->m_name, pDoc->m_currentDevice->m_parent);
					pDoc->YoMessage(s);

				}
			}
			pDoc->m_deviceBeingAttached = FALSE;
			SetClassLong(m_hWnd, GCL_HCURSOR, (long)pMainFrame->m_hCursorArrow);
			YoRender(YO_RENDER_FULL);
			return;
		}

		if (pMainFrame->m_analysisActive == TRUE)
		{
			if (pMainFrame->m_analysis->m_selected <= 2)
			{
				if (pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_COORDINATE
					&& pDoc->m_currentTag != NULL)
				{
					ptrTag = pDoc->m_currentTag;
					YoRender(YO_RENDER_PICK_PART_AND_TAG);

					if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_TAG)
					{
						//YoRender(YO_RENDER_PICK_PART_AND_TAG);
						if (pMainFrame->m_analysis->m_selected == 0
							|| pMainFrame->m_analysis->m_selected == 2)
						{
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][0] = pDoc->m_mTag[12];
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1] = pDoc->m_mTag[13];
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2] = pDoc->m_mTag[14];
							pMainFrame->m_analysis->m_ptrTag[0] = pDoc->m_currentTag;
							pMainFrame->m_analysis->m_ptrDevice[0] = NULL;
						}
						else if (pMainFrame->m_analysis->m_selected == 1)
						{
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0] = pDoc->m_mTag[12];
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1] = pDoc->m_mTag[13];
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][2] = pDoc->m_mTag[14];
							pMainFrame->m_analysis->m_ptrTag[1] = pDoc->m_currentTag;
							pMainFrame->m_analysis->m_ptrDevice[1] = NULL;
						}
						if (pMainFrame->m_analysis->m_selected == 0
							|| pMainFrame->m_analysis->m_selected == 1)
						{
							pMainFrame->m_analysis->m_selected++;
							pMainFrame->m_analysis->YoUpdateSelected();
						}
						else if (pMainFrame->m_analysis->m_selected == 2)
						{
							pMainFrame->m_analysis->m_selected--;
							pMainFrame->m_analysis->YoUpdateSelected();
						}
					}
					pDoc->m_currentTag = ptrTag;
					YoRender(YO_RENDER_FULL);
				}
				else if ((pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_PART
					|| pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_DEVICE)
					&& pDoc->m_currentDevice != NULL)
				{
					ptrPart = pDoc->m_currentPart;
					ptrDevice = pDoc->m_currentDevice;
					YoRender(YO_RENDER_PICK_PART);

					if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART)
					{
						if (pMainFrame->m_analysis->m_mode == YO_ANALYSIS_MODE_DEVICE)
						{
							pDoc->m_currentPart = pDoc->m_currentDevice->m_ptrPart;
						}
						pDoc->YoModelMatrixOfCurrentPart(m);
						if (pMainFrame->m_analysis->m_selected == 0
							|| pMainFrame->m_analysis->m_selected == 2)
						{
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][0] = m[12];
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1] = m[13];
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2] = m[14];
							pMainFrame->m_analysis->m_ptrDevice[0] = pDoc->m_currentDevice;
							pMainFrame->m_analysis->m_ptrTag[0] = NULL;
						}
						else if (pMainFrame->m_analysis->m_selected == 1)
						{
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0] = m[12];
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1] = m[13];
							pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][2] = m[14];
							pMainFrame->m_analysis->m_ptrDevice[1] = pDoc->m_currentDevice;
							pMainFrame->m_analysis->m_ptrTag[1] = NULL;
						}
						if (pMainFrame->m_analysis->m_selected == 0
							|| pMainFrame->m_analysis->m_selected == 1)
						{
							pMainFrame->m_analysis->m_selected++;
							pMainFrame->m_analysis->YoUpdateSelected();
						}
						else if (pMainFrame->m_analysis->m_selected == 2)
						{
							pMainFrame->m_analysis->m_selected--;
							pMainFrame->m_analysis->YoUpdateSelected();
						}
					}
					pDoc->m_currentPart = ptrPart;
					pDoc->m_currentDevice = ptrDevice;
					YoRender(YO_RENDER_FULL);
				}
				else
				{
					ptrPart = pDoc->m_currentPart;
					ptrDevice = pDoc->m_currentDevice;
					YoRender(YO_RENDER_PICK_PART);

					if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART
						&& pDoc->m_currentDevice->m_type != YO_TRACK)
					{
						YoRender(YO_RENDER_PICK_PART);
						if (pDoc->YoGetClosestPolygon(point) == TRUE)
						{
							if (pMainFrame->m_analysis->m_selected == 0
								|| pMainFrame->m_analysis->m_selected == 1)
							{
								pMainFrame->m_analysis->m_selected++;
								pMainFrame->m_analysis->YoUpdateSelected();
							}
							else if (pMainFrame->m_analysis->m_selected == 2)
							{
								pMainFrame->m_analysis->m_selected--;
								pMainFrame->m_analysis->YoUpdateSelected();
							}
						}
					}

					pDoc->m_currentPart = ptrPart;
					pDoc->m_currentDevice = ptrDevice;
					YoRender(YO_RENDER_FULL);
				}

			}
			return;
		}

		else if ((pMainFrame->m_viewPartActive == TRUE
			&& pMainFrame->m_viewPart->m_snapTo == TRUE)
			|| (pMainFrame->m_trackDlgActive == TRUE
			&& pMainFrame->m_trackDialog->m_snapTo == TRUE))
		{
			if (pMainFrame->m_viewPartActive == TRUE)
			{
				ptrDlg = pMainFrame->m_viewPart;
				snapToMode = pMainFrame->m_viewPart->m_snapToMode;
			}
			else
			{
				ptrDlg = pMainFrame->m_trackDialog;
				snapToMode = pMainFrame->m_trackDialog->m_snapToMode;
			}
			if (snapToMode == YO_SNAP_COORDINATE)
			{
				ptrTag = pDoc->m_currentTag;
				ptrPart = pDoc->m_currentPart;
				ptrDevice = pDoc->m_currentDevice;
				YoRender(YO_RENDER_PICK_PART_AND_TAG);

				if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_TAG)
				{
					if (ptrDevice->m_ptrPart == ptrPart
						&& (strcmp(ptrDevice->m_parent, "NONE") == 0))
					{
						// base part without a parent
						::glMatrixMode(GL_MODELVIEW);
						::glPushMatrix();
						::glLoadMatrixd(pDoc->m_mTag);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}
					else if (ptrDevice->m_ptrPart == ptrPart
						&& ptrDevice->m_attachedFromPart != NULL)
					{
						// base part attached to part of parent device
						pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(ptrDevice->m_parent);
						pDoc->m_currentPart = ptrDevice->m_attachedFromPart;
						pDoc->YoModelMatrixOfCurrentPart(m);
						pDoc->YoMatrixInverse(m, mInv);
						::glMatrixMode(GL_MODELVIEW);
						::glPushMatrix();
						::glLoadMatrixd(mInv);
						::glMultMatrixd(pDoc->m_mTag);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}
					else if (ptrDevice->m_ptrPart == ptrPart
						&& ptrDevice->m_attachedFromPart == NULL)
					{
						// base part attached to base part of parent device
						pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(ptrDevice->m_parent);
						pDoc->m_currentPart = pDoc->m_currentDevice->m_ptrPart;
						pDoc->YoModelMatrixOfCurrentPart(m);
						pDoc->YoMatrixInverse(m, mInv);
						::glMatrixMode(GL_MODELVIEW);
						::glPushMatrix();
						::glLoadMatrixd(mInv);
						::glMultMatrixd(pDoc->m_mTag);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}
					else
					{
						// part is not base part
						for (pDoc->m_currentPart = ptrPart;
							pDoc->m_currentPart->m_left != NULL;
							pDoc->m_currentPart = pDoc->m_currentPart->m_left);
						pDoc->m_currentPart = pDoc->m_currentPart->m_up;
						pDoc->m_currentDevice = ptrDevice;
						pDoc->YoModelMatrixOfCurrentPart(m);
						pDoc->YoMatrixInverse(m, mInv);
						::glMatrixMode(GL_MODELVIEW);
						::glPushMatrix();
						::glLoadMatrixd(mInv);
						::glMultMatrixd(pDoc->m_mTag);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}

					if (ptrPart->m_altOriginDisplayed == TRUE)
					{
						pDoc->YoMatrixInverse(ptrPart->m_altOrigin, mInv);
						::glMultMatrixd(mInv);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}

					ptrPart->m_txyz = YO_TXYZ_TXYZ;
					pDoc->YoTranslateRotateValues(m,
						ptrPart->m_translate,
						ptrPart->m_rotate);
					for (i = 0; i < 3; i++)
					{
						ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
					}
					::glPopMatrix();
				}
			}
			else if (snapToMode == YO_SNAP_PART)
			{
				ptrTag = pDoc->m_currentTag;
				ptrPart = pDoc->m_currentPart;
				ptrDevice = pDoc->m_currentDevice;	
				YoRender(YO_RENDER_PICK_PART);
				if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART)
				{
					pDoc->YoModelMatrixOfCurrentPart(pDoc->m_mSnapTo);
					if (ptrDevice->m_ptrPart == ptrPart
						&& (strcmp(ptrDevice->m_parent, "NONE") == 0))
					{
						// base part without a parent
						::glMatrixMode(GL_MODELVIEW);
						::glPushMatrix();
						::glLoadMatrixd(pDoc->m_mSnapTo);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}
					else if (ptrDevice->m_ptrPart == ptrPart
						&& ptrDevice->m_attachedFromPart != NULL)
					{
						// base part attached to part of parent device
						pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(ptrDevice->m_parent);
						pDoc->m_currentPart = ptrDevice->m_attachedFromPart;
						pDoc->YoModelMatrixOfCurrentPart(m);
						pDoc->YoMatrixInverse(m, mInv);
						::glMatrixMode(GL_MODELVIEW);
						::glPushMatrix();
						::glLoadMatrixd(mInv);
						::glMultMatrixd(pDoc->m_mSnapTo);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}
					else if (ptrDevice->m_ptrPart == ptrPart
						&& ptrDevice->m_attachedFromPart == NULL)
					{
						// base part attached to base part of parent device
						pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(ptrDevice->m_parent);
						pDoc->m_currentPart = pDoc->m_currentDevice->m_ptrPart;
						pDoc->YoModelMatrixOfCurrentPart(m);
						pDoc->YoMatrixInverse(m, mInv);
						::glMatrixMode(GL_MODELVIEW);
						::glPushMatrix();
						::glLoadMatrixd(mInv);
						::glMultMatrixd(pDoc->m_mSnapTo);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}
					else
					{
						// part is not base part
						for (pDoc->m_currentPart = ptrPart;
							pDoc->m_currentPart->m_left != NULL;
							pDoc->m_currentPart = pDoc->m_currentPart->m_left);
						pDoc->m_currentPart = pDoc->m_currentPart->m_up;
						pDoc->m_currentDevice = ptrDevice;
						pDoc->YoModelMatrixOfCurrentPart(m);
						pDoc->YoMatrixInverse(m, mInv);
						::glMatrixMode(GL_MODELVIEW);
						::glPushMatrix();
						::glLoadMatrixd(mInv);
						::glMultMatrixd(pDoc->m_mSnapTo);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}

					if (ptrPart->m_altOriginDisplayed == TRUE)
					{
						pDoc->YoMatrixInverse(ptrPart->m_altOrigin, mInv);
						::glMultMatrixd(mInv);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}
					
					ptrPart->m_txyz = YO_TXYZ_TXYZ;
					pDoc->YoTranslateRotateValues(m,
						ptrPart->m_translate,
						ptrPart->m_rotate);
					for (i = 0; i < 3; i++)
					{
						ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
					}
					::glPopMatrix();
				}
			}
			else
			{
				ptrTag = pDoc->m_currentTag;
				ptrPart = pDoc->m_currentPart;
				ptrDevice = pDoc->m_currentDevice;
				YoRender(YO_RENDER_PICK_PART);
				if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART
					&& pDoc->m_currentDevice->m_type != YO_TRACK)
				{
					YoRender(YO_RENDER_PICK_PART);
					if (pDoc->YoGetClosestPolygon(point) == TRUE)
					{
						if (ptrDevice->m_ptrPart == ptrPart
							&& (strcmp(ptrDevice->m_parent, "NONE") == 0))
						{
							// base part without a parent
							::glMatrixMode(GL_MODELVIEW);
							::glPushMatrix();
							::glLoadMatrixd(pDoc->m_mSnapTo);
							::glGetDoublev(GL_MODELVIEW_MATRIX, m);
						}
						else if (ptrDevice->m_ptrPart == ptrPart
							&& ptrDevice->m_attachedFromPart != NULL)
						{
							// base part attached to part of parent device
							pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(ptrDevice->m_parent);
							pDoc->m_currentPart = ptrDevice->m_attachedFromPart;
							pDoc->YoModelMatrixOfCurrentPart(m);
							pDoc->YoMatrixInverse(m, mInv);
							::glMatrixMode(GL_MODELVIEW);
							::glPushMatrix();
							::glLoadMatrixd(mInv);
							::glMultMatrixd(pDoc->m_mSnapTo);
							::glGetDoublev(GL_MODELVIEW_MATRIX, m);
						}
						else if (ptrDevice->m_ptrPart == ptrPart
							&& ptrDevice->m_attachedFromPart == NULL)
						{
							// base part attached to base part of parent device
							pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(ptrDevice->m_parent);
							pDoc->m_currentPart = pDoc->m_currentDevice->m_ptrPart;
							pDoc->YoModelMatrixOfCurrentPart(m);
							pDoc->YoMatrixInverse(m, mInv);
							::glMatrixMode(GL_MODELVIEW);
							::glPushMatrix();
							::glLoadMatrixd(mInv);
							::glMultMatrixd(pDoc->m_mSnapTo);
							::glGetDoublev(GL_MODELVIEW_MATRIX, m);
						}
						else
						{
							// part is not base part
							for (pDoc->m_currentPart = ptrPart;
								pDoc->m_currentPart->m_left != NULL;
								pDoc->m_currentPart = pDoc->m_currentPart->m_left);
							pDoc->m_currentPart = pDoc->m_currentPart->m_up;
							pDoc->m_currentDevice = ptrDevice;
							pDoc->YoModelMatrixOfCurrentPart(m);
							pDoc->YoMatrixInverse(m, mInv);
							::glMatrixMode(GL_MODELVIEW);
							::glPushMatrix();
							::glLoadMatrixd(mInv);
							::glMultMatrixd(pDoc->m_mSnapTo);
							::glGetDoublev(GL_MODELVIEW_MATRIX, m);
						}
					}

					if (ptrPart->m_altOriginDisplayed == TRUE)
					{
						pDoc->YoMatrixInverse(ptrPart->m_altOrigin, mInv);
						::glMultMatrixd(mInv);
						::glGetDoublev(GL_MODELVIEW_MATRIX, m);
					}


					ptrPart->m_txyz = YO_TXYZ_TXYZ;
					pDoc->YoTranslateRotateValues(m,
						ptrPart->m_translate,
						ptrPart->m_rotate);
					for (i = 0; i < 3; i++)
					{
						ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
					}
					::glPopMatrix();
				}
			}

			pDoc->m_currentTag = ptrTag;
			pDoc->m_currentPart = ptrPart;
			pDoc->m_currentDevice = ptrDevice;

			if (pMainFrame->m_viewPartActive == TRUE)
			{
				pMainFrame->m_viewPart->YoUpdateTranslateRotate();
				pMainFrame->m_viewPart->m_snapTo = FALSE;
			}
			else
			{
				pMainFrame->m_trackDialog->YoUpdateTranslateRotate();
				pMainFrame->m_trackDialog->m_snapTo = FALSE;
			}

			SetClassLong(m_hWnd, GCL_HCURSOR, (long)pMainFrame->m_hCursorArrow);
			YoRender(YO_RENDER_LIGHT);
			YoRender(YO_RENDER_FULL);

			return;
		}

		else if (pMainFrame->m_viewTagActive == TRUE)
		{
			if (pMainFrame->m_viewTag->m_tagSnapMode == YO_SNAP_COORDINATE)
			{
				ptrTag = pDoc->m_currentTag;
				ptrPart = pDoc->m_currentPart;
				ptrDevice = pDoc->m_currentDevice;
				YoRender(YO_RENDER_PICK_PART_AND_TAG);

				if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_TAG)
				{
					if (ptrTag != pDoc->m_currentTag)
					{
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
						::glPopMatrix();
					}
					pDoc->m_currentTag = ptrTag;
					pDoc->m_currentPart = ptrPart;
					pDoc->m_currentDevice = ptrDevice;
					pMainFrame->m_viewTag->YoUpdateDialog();
					YoRender(YO_RENDER_FULL);
				}
			}
			else if (pMainFrame->m_viewTag->m_tagSnapMode == YO_SNAP_PART)
			{
				ptrTag = pDoc->m_currentTag;
				ptrPart = pDoc->m_currentPart;
				ptrDevice = pDoc->m_currentDevice;
				
				pDoc->m_currentPart = ptrTag->m_ptrPath->m_ptrPart;
				pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(pDoc->m_currentPart->m_deviceName);
				pDoc->YoModelMatrixOfCurrentPart(m);
				pDoc->YoMatrixInverse(m, mInv);

				YoRender(YO_RENDER_PICK_PART);

				if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART)
				{
					pDoc->YoModelMatrixOfCurrentPart(m);
					::glMatrixMode(GL_MODELVIEW);
					::glPushMatrix();
					::glLoadMatrixd(mInv);
					::glMultMatrixd(m);
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
				pDoc->m_currentTag = ptrTag;
				pDoc->m_currentPart = ptrPart;
				pDoc->m_currentDevice = ptrDevice;
				pMainFrame->m_viewTag->YoUpdateDialog();
				YoRender(YO_RENDER_FULL);
			}
			else
			{
				ptrTag = pDoc->m_currentTag;
				ptrPart = pDoc->m_currentPart;
				ptrDevice = pDoc->m_currentDevice;

				pDoc->m_currentPart = ptrTag->m_ptrPath->m_ptrPart;
				pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(pDoc->m_currentPart->m_deviceName);
				pDoc->YoModelMatrixOfCurrentPart(m);
				pDoc->YoMatrixInverse(m, mInv);
				
				YoRender(YO_RENDER_PICK_PART);

				if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART
					&& pDoc->m_currentDevice->m_type != YO_TRACK)
				{
					YoRender(YO_RENDER_PICK_PART);
					if (pDoc->YoGetClosestPolygon(point) == TRUE)
					{
						::glMatrixMode(GL_MODELVIEW);
						::glPushMatrix();
						::glLoadMatrixd(mInv);
						::glMultMatrixd(pDoc->m_mSnapTo);
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
				}
				pDoc->m_currentTag = ptrTag;
				pDoc->m_currentPart = ptrPart;
				pDoc->m_currentDevice = ptrDevice;
				pMainFrame->m_viewTag->YoUpdateDialog();
				YoRender(YO_RENDER_FULL);
			}
			pCBox = ((CComboBox*)pMainFrame->m_viewTag)->GetDlgItem(IDC_TAG_ROTATE_Z);
			pCBox->SetFocus();
			::SetActiveWindow(pMainFrame->m_viewTag->m_hWnd);
			return;
		}

		else if (pMainFrame->m_viewPartActive == TRUE
			&& pMainFrame->m_viewPart->m_selectingAltOrigin == TRUE)
		{
			ptrDlg = pMainFrame->m_viewPart;
			snapToMode = pMainFrame->m_viewPart->m_snapToMode;
			ptrTag = pDoc->m_currentTag;
			ptrPart = pDoc->m_currentPart;
			ptrDevice = pDoc->m_currentDevice;
			pDoc->YoModelMatrixOfCurrentPart(m);
			pDoc->YoMatrixInverse(m, mInv);

			if (snapToMode == YO_SNAP_COORDINATE)
			{
				YoRender(YO_RENDER_PICK_PART_AND_TAG);

				if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_TAG)
				{
					::glMatrixMode(GL_MODELVIEW);
					::glPushMatrix();
					::glLoadMatrixd(mInv);
					::glMultMatrixd(pDoc->m_mTag);
					::glGetDoublev(GL_MODELVIEW_MATRIX, ptrPart->m_altOrigin);
					::glPopMatrix();
				}
			}
			else if (snapToMode == YO_SNAP_PART)
			{
				YoRender(YO_RENDER_PICK_PART);

				if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART)
				{
					pDoc->YoModelMatrixOfCurrentPart(pDoc->m_mSnapTo);
					::glMatrixMode(GL_MODELVIEW);
					::glPushMatrix();
					::glLoadMatrixd(mInv);
					::glMultMatrixd(pDoc->m_mSnapTo);
					::glGetDoublev(GL_MODELVIEW_MATRIX, ptrPart->m_altOrigin);
					::glPopMatrix();
				}
			}
			else
			{
				YoRender(YO_RENDER_PICK_PART);

				if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART)
				{
					YoRender(YO_RENDER_PICK_PART);
					if (pDoc->YoGetClosestPolygon(point) == TRUE)
					{
						// rotations of the alternative origin are the same as the
						// rotations of the part's original origin
						pDoc->m_mSnapTo[0] = m[0];
						pDoc->m_mSnapTo[1] = m[1];
						pDoc->m_mSnapTo[2] = m[2];
						pDoc->m_mSnapTo[3] = m[3];
						pDoc->m_mSnapTo[4] = m[4];
						pDoc->m_mSnapTo[5] = m[5];
						pDoc->m_mSnapTo[6] = m[6];
						pDoc->m_mSnapTo[7] = m[7];
						pDoc->m_mSnapTo[8] = m[8];
						pDoc->m_mSnapTo[9] = m[9];
						pDoc->m_mSnapTo[10] = m[10];
						pDoc->m_mSnapTo[11] = m[11];

						::glMatrixMode(GL_MODELVIEW);
						::glPushMatrix();
						::glLoadMatrixd(mInv);
						::glMultMatrixd(pDoc->m_mSnapTo);
						::glGetDoublev(GL_MODELVIEW_MATRIX, ptrPart->m_altOrigin);
						::glPopMatrix();

						/**
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

						ptrPart->m_altOrigin[12] = pDoc->m_mSnapTo[12] - m[12];
						ptrPart->m_altOrigin[13] = pDoc->m_mSnapTo[13] - m[13];
						ptrPart->m_altOrigin[14] = pDoc->m_mSnapTo[14] - m[14];
						ptrPart->m_altOrigin[15] = 1.0;
						**/
					}
				}
			}

			pDoc->m_currentTag = ptrTag;
			pDoc->m_currentPart = ptrPart;
			pDoc->m_currentDevice = ptrDevice;

			pMainFrame->m_viewPart->m_selectingAltOrigin = FALSE;
			pMainFrame->m_viewPart->m_originAltDisplayed = TRUE;
			pDoc->m_currentPart->m_altOriginDisplayed = TRUE;
			pMainFrame->m_viewPart->UpdateData(FALSE);
			pMainFrame->m_viewPart->YoUpdateTranslateRotate();
			::SetActiveWindow(pMainFrame->m_viewPart->m_hWnd);

			SetClassLong(m_hWnd, GCL_HCURSOR, (long)pMainFrame->m_hCursorArrow);
			YoRender(YO_RENDER_LIGHT);
			YoRender(YO_RENDER_FULL);

			return;
		}

		else if (pMainFrame->m_viewPartActive == TRUE
			&& pMainFrame->m_viewPart->m_inheritingMaterial == TRUE)
		{
			// inherit material from part designated by point
			ptrPart = pDoc->m_currentPart;
			ptrDevice = pDoc->m_currentDevice;
			YoRender(YO_RENDER_PICK_PART);

			if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART
				&& ptrPart != pDoc->m_currentPart)
			{
				for (i = 0; i < 4; i++)
				{
					ptrPart->m_ambient[i] = pDoc->m_currentPart->m_ambient[i];
					ptrPart->m_diffuse[i] = pDoc->m_currentPart->m_diffuse[i];
					ptrPart->m_specular[i] = pDoc->m_currentPart->m_specular[i];
					ptrPart->m_emission[i] = pDoc->m_currentPart->m_emission[i];
					ptrPart->m_wireframe[i] = pDoc->m_currentPart->m_wireframe[i];

					pMainFrame->m_viewPart->m_ambient[i] = (UINT)(ptrPart->m_ambient[i] * 255.0);
					pMainFrame->m_viewPart->m_diffuse[i] = (UINT)(ptrPart->m_diffuse[i] * 255.0);
					pMainFrame->m_viewPart->m_specular[i] = (UINT)(ptrPart->m_specular[i] * 255.0);
					pMainFrame->m_viewPart->m_emission[i] = (UINT)(ptrPart->m_emission[i] * 255.0);
					pMainFrame->m_viewPart->m_wireframe[i] = (UINT)(ptrPart->m_wireframe[i] * 255.0);
				}

				if (pMainFrame->m_viewPart->m_partMaterial.GetCurSel() == 0)  // ambient
				{
					pMainFrame->m_viewPart->m_partRed = pMainFrame->m_viewPart->m_ambient[0];
					pMainFrame->m_viewPart->m_partGreen = pMainFrame->m_viewPart->m_ambient[1];
					pMainFrame->m_viewPart->m_partBlue = pMainFrame->m_viewPart->m_ambient[2];
					pMainFrame->m_viewPart->m_partAlpha = pMainFrame->m_viewPart->m_ambient[3];
				}
				else if (pMainFrame->m_viewPart->m_partMaterial.GetCurSel() == 1)  // diffuse
				{
					pMainFrame->m_viewPart->m_partRed = pMainFrame->m_viewPart->m_diffuse[0];
					pMainFrame->m_viewPart->m_partGreen = pMainFrame->m_viewPart->m_diffuse[1];
					pMainFrame->m_viewPart->m_partBlue = pMainFrame->m_viewPart->m_diffuse[2];
					pMainFrame->m_viewPart->m_partAlpha = pMainFrame->m_viewPart->m_diffuse[3];
				}
				else if (pMainFrame->m_viewPart->m_partMaterial.GetCurSel() == 2)  // emission
				{
					pMainFrame->m_viewPart->m_partRed = pMainFrame->m_viewPart->m_emission[0];
					pMainFrame->m_viewPart->m_partGreen = pMainFrame->m_viewPart->m_emission[1];
					pMainFrame->m_viewPart->m_partBlue = pMainFrame->m_viewPart->m_emission[2];
					pMainFrame->m_viewPart->m_partAlpha = pMainFrame->m_viewPart->m_emission[3];
				}
				else if (pMainFrame->m_viewPart->m_partMaterial.GetCurSel() == 3)  // specular
				{
					pMainFrame->m_viewPart->m_partRed = pMainFrame->m_viewPart->m_specular[0];
					pMainFrame->m_viewPart->m_partGreen = pMainFrame->m_viewPart->m_specular[1];
					pMainFrame->m_viewPart->m_partBlue = pMainFrame->m_viewPart->m_specular[2];
					pMainFrame->m_viewPart->m_partAlpha = pMainFrame->m_viewPart->m_specular[3];
				}
				else if (pMainFrame->m_viewPart->m_partMaterial.GetCurSel() == 4)  // wireframe
				{
					pMainFrame->m_viewPart->m_partRed = pMainFrame->m_viewPart->m_wireframe[0];
					pMainFrame->m_viewPart->m_partGreen = pMainFrame->m_viewPart->m_wireframe[1];
					pMainFrame->m_viewPart->m_partBlue = pMainFrame->m_viewPart->m_wireframe[2];
					pMainFrame->m_viewPart->m_partAlpha = pMainFrame->m_viewPart->m_wireframe[3];
				}

				ptrPart->m_shininess = pDoc->m_currentPart->m_shininess;
				pMainFrame->m_viewPart->m_partShininess = (UINT)ptrPart->m_shininess;
				pMainFrame->m_viewPart->UpdateData(FALSE);

				pMainFrame->m_viewPart->m_partSliderRed.SetPos(pMainFrame->m_viewPart->m_partRed);
				pMainFrame->m_viewPart->m_partSliderGreen.SetPos(pMainFrame->m_viewPart->m_partGreen);
				pMainFrame->m_viewPart->m_partSliderBlue.SetPos(pMainFrame->m_viewPart->m_partBlue);
				pMainFrame->m_viewPart->m_partSliderAlpha.SetPos(pMainFrame->m_viewPart->m_partAlpha);
				pMainFrame->m_viewPart->m_partSliderShininess.SetPos(pMainFrame->m_viewPart->m_partShininess);

				sprintf(s, "%s:%s successfully inherited material of %s:%s", ptrDevice->m_name, ptrPart->m_partName,
					pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
				pDoc->YoMessage(s);

				pDoc->m_currentPart = ptrPart;
				pDoc->m_currentDevice = ptrDevice;
				YoRender(YO_RENDER_FULL);
			}
			else
			{
				sprintf(s, "Material remains the same");
				pDoc->YoMessage(s);
				pDoc->m_currentPart = ptrPart;
				pDoc->m_currentDevice = ptrDevice;	
			}

			SetClassLong(m_hWnd, GCL_HCURSOR, (long)pMainFrame->m_hCursorArrow);
			pMainFrame->m_viewPart->m_inheritingMaterial = FALSE;
			return;
		}

		else if (pMainFrame->m_viewPartActive == TRUE
			&& pDoc->m_currentDevice->m_type == YO_ROBOT6)
		{	
			ptrTag = pDoc->m_currentTag;
			ptrPart = pDoc->m_currentPart;
			ptrDevice = pDoc->m_currentDevice;
			YoRender(YO_RENDER_PICK_PART_AND_TAG);

			if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_TAG)
			{
				if (((CStageRobot6 *)pDoc->m_currentDevice)->m_jointInterpolation == FALSE)
				{
					sprintf(s, "MOVES %s%d", pDoc->m_currentTag->m_ptrPath->m_name, pDoc->m_currentTag->m_tag);
				}
				else
				{
					sprintf(s, "MOVE %s%d", pDoc->m_currentTag->m_ptrPath->m_name, pDoc->m_currentTag->m_tag);
				}
				((CStageRobot6 *)pDoc->m_currentDevice)->YoHandleCommand(s);
				if (pDoc->m_isMovement)
				{
					pDoc->YoMove();
				}
				else
				{
					pDoc->m_currentTag = ptrTag;
				}
			}
			pDoc->m_currentPart = ptrPart;
			pDoc->m_currentDevice = ptrDevice;
			
			
			/***
			ptrTag = pDoc->m_currentTag;
			ptrPart = pDoc->m_currentPart;
			//ptrDevice = pDoc->m_currentDevice;
			YoRender(YO_RENDER_PICK_PART_AND_TAG);

			if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_TAG)
			{
				// select a tag and move to it
				pDoc->m_currentPart = pDoc->m_currentDevice->m_ptrPart;
				//pDoc->m_currentDevice = pDoc->YoDeviceHashLookup(pDoc->m_currentPart->m_deviceName);
				pDoc->YoModelMatrixOfCurrentPart(m);
				pDoc->YoMatrixInverse(m, mInv);
				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				::glLoadMatrixd(pDoc->m_mTag);
				//::glTranslated(0.0, 0.0, -110.0);
				::glTranslated(0.0, 0.0, -((CStageRobot6 *)pDoc->m_currentDevice)->m_tcpOffset[2]);
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				::glLoadMatrixd(mInv);
				//::glMultMatrixd(pDoc->m_mTag);
				::glMultMatrixd(m);
				//::glMultMatrixd(mInv);
				// m is matrix of tag relative to robot6 base
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				::glPopMatrix();
				::GetSystemTime(&pDoc->m_gmTime);
				if (((CStageRobot6 *)pDoc->m_currentDevice)->YoMoveTo(m) == TRUE)
				{
					pDoc->YoMove();
				}
				
			}
			pDoc->m_currentTag = ptrTag;
			pDoc->m_currentPart = ptrPart;
			//pDoc->m_currentDevice = ptrDevice;
			//pMainFrame->m_viewTag->YoUpdateDialog();
			//YoRender(YO_RENDER_FULL);
			***/
			

			return;
		}


		else if (pMainFrame->m_viewPartActive == TRUE
			&& pDoc->m_currentDevice->m_type == YO_LIGHT
			&& pDoc->YoPointOnCurrentPart(point) == FALSE)
		{
			// focus light on selected x, y, z point
			::glReadPixels(point.x, m_windowSize[1] - point.y - 1, 1, 1,
				GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid *)p);

			::glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
			::glGetDoublev(GL_PROJECTION_MATRIX, proj);
			::glGetIntegerv(GL_VIEWPORT, viewport);
						
			::gluUnProject((GLdouble) point.x,
				(GLdouble)(m_windowSize[1] - point.y - 1),
				(GLdouble)p[0],
				modelView,
				proj,
				viewport,
				&objx,
				&objy,
				&objz);

			if (pDoc->m_currentDevice->m_ptrPart->m_txyz != YO_TXYZ_TXYZ)
			{
				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				::glLoadIdentity();
				YoTxyz(pDoc->m_currentDevice->m_ptrPart,
					pDoc->m_currentDevice->m_ptrPart->m_translate,
					pDoc->m_currentDevice->m_ptrPart->m_rotate);
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				pDoc->YoTranslateRotateValues(m,
					pDoc->m_currentDevice->m_ptrPart->m_translate,
					pDoc->m_currentDevice->m_ptrPart->m_rotate);
				pDoc->m_currentDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
				::glPopMatrix();
			}
			if (strcmp(pDoc->m_currentDevice->m_parent, "NONE") != 0)
			{
				sprintf(s, "%s", pDoc->m_currentDevice->m_parent);
				if (pDoc->m_currentDevice->m_attachedFromPart == NULL)
				{
					ptrDevice = pDoc->YoDeviceHashLookup(pDoc->m_currentDevice->m_parent);
					ptrPart = ptrDevice->m_ptrPart;
				}
				else
				{
					ptrPart = pDoc->m_currentDevice->m_attachedFromPart;
				}
				pDoc->YoDetachDevice();
				//pMainFrame->SendMessage(WM_COMMAND, ID_DEVICE_DETACH, (LPARAM)0);	
				sprintf(pDoc->m_currentDevice->m_parent, "%s", s);
			}


			x = pDoc->m_currentDevice->m_ptrPart->m_translate[0] - objx;
			y = pDoc->m_currentDevice->m_ptrPart->m_translate[1] - objy;
			z = pDoc->m_currentDevice->m_ptrPart->m_translate[2] - objz;

			
			r = sqrt(x * x + y * y);

			if ((x > 0.0 && y >= 0.0) || x < 0.0)
			{
				theta = atan2(y, x);
			}
			else if (x > 0.0 && y < 0.0)
			{
				theta = 2.0 * PI + atan2(y, x);
			}
			else if (y > 0.0)
			{
				theta = PI / 2.0;
			}
			else if (y < 0.0)
			{
				theta = -PI / 2.0;
			}
			else
			{
				theta = 0.0;
			}

			if (r != 0.0)
			{
				phi = atan2(z, r);
			}
			else if (z > 0.0)
			{
				phi = PI / 2.0;
			}
			else if (z < 0.0)
			{
				phi = -PI / 2.0;
			}
			else
			{
				phi = 0.0;
			}

			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadIdentity();
			::glTranslated(pDoc->m_currentDevice->m_ptrPart->m_translate[0],
				pDoc->m_currentDevice->m_ptrPart->m_translate[1],
				pDoc->m_currentDevice->m_ptrPart->m_translate[2]);
			::glRotated(theta * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
			::glRotated((phi - PI / 2.0) * YO_RADIANS_TO_DEGREES, 0.0, -1.0, 0.0);
			//::glRotated(phi * YO_RADIANS_TO_DEGREES, 1.0, 0.0, 0.0);
			::glRotated(-theta * YO_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m);
			pDoc->m_currentDevice->m_ptrPart->m_txyz = YO_TXYZ_TXYZ;
			pDoc->YoTranslateRotateValues(m,
				pDoc->m_currentDevice->m_ptrPart->m_translate,
				pDoc->m_currentDevice->m_ptrPart->m_rotate);
			::glPopMatrix();

			for (i = 0; i < 3; i++)
			{
				pDoc->m_currentDevice->m_ptrPart->m_rotate[i] *= YO_RADIANS_TO_DEGREES;
			}

			if (strcmp(pDoc->m_currentDevice->m_parent, "NONE") != 0)
			{
				pDoc->YoAttachDevice(ptrPart);
			}

			sprintf(s, "%.1lf", pDoc->m_currentPart->m_translate[0]
				* pDoc->m_unitScaleFactor);
			pCBox = ((CComboBox*)pMainFrame->m_viewPart)->GetDlgItem(IDC_TRANSLATE_X);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%.1lf", pDoc->m_currentPart->m_translate[1]
				* pDoc->m_unitScaleFactor);
			pCBox = ((CComboBox*)pMainFrame->m_viewPart)->GetDlgItem(IDC_TRANSLATE_Y);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%.1lf", pDoc->m_currentPart->m_translate[2]
				* pDoc->m_unitScaleFactor);
			pCBox = ((CComboBox*)pMainFrame->m_viewPart)->GetDlgItem(IDC_TRANSLATE_Z);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%.1lf", pDoc->m_currentPart->m_rotate[0]);
			pCBox = ((CComboBox*)pMainFrame->m_viewPart)->GetDlgItem(IDC_ROTATE_X);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%.1lf", pDoc->m_currentPart->m_rotate[1]);
			pCBox = ((CComboBox*)pMainFrame->m_viewPart)->GetDlgItem(IDC_ROTATE_Y);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%.1lf", pDoc->m_currentPart->m_rotate[2]);
			pCBox = ((CComboBox*)pMainFrame->m_viewPart)->GetDlgItem(IDC_ROTATE_Z);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
			
			YoRender(YO_RENDER_LIGHT);
			YoRender(YO_RENDER_FULL);
			return;
		}
		else if (pMainFrame->m_viewPartActive == TRUE
			&& pDoc->YoPointOnCurrentPart(point) == TRUE)
		{
			// find selected polygon and modify texture
			YoRender(YO_RENDER_PICK_PART);
			if (pDoc->m_currentDevice->m_type != YO_TRACK
				&& pDoc->YoGetClosestPolygon(point) == TRUE)
			{
				index = pDoc->m_currentPolygonIndex;
				for (currentPolygonList = pDoc->m_currentPart->m_polygonList; index >= 10; currentPolygonList = currentPolygonList->m_next)
				{
					index -= 10;
				}

				if (currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10] != NULL
					&& currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]->m_textureMode == GL_MODULATE)
				{
					pMainFrame->m_viewPart->m_textureBlending = TRUE;
				}
				else
				{
					pMainFrame->m_viewPart->m_textureBlending = FALSE;
				}

				pMainFrame->m_viewPart->UpdateData(FALSE);

				TRACE3("numberSides = %d    ptrVertices = %d   ptrTexture = %d\n",
					currentPolygonList->m_numberSides[pDoc->m_currentPolygonIndex % 10],
					currentPolygonList->m_vertices[pDoc->m_currentPolygonIndex % 10],
					currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]);
			}
		}
		else if (pMainFrame->m_viewPartActive == TRUE
			&& pDoc->YoPointOnCurrentPart(point) == FALSE)
		{
			pDoc->m_currentPolygonIndex = -1;
			return;
		}
		else if (pMainFrame->m_viewTagActive == TRUE)
		{

			return;
		}
	}

	if (m_mode == YO_MODE_DEVICE_TRANSLATE)
	{
		if (strcmp(pDoc->m_currentDevice->m_parent, "NONE") != 0)
		{
			sprintf(s, "%s", pDoc->m_currentDevice->m_parent);
			ptrPart = pDoc->m_tempAttachedFromPart;
			pDoc->YoDetachDevice();
			sprintf(pDoc->m_currentDevice->m_parent, "%s", s);
			if (ptrPart == NULL)
			{
				ptrDevice = pDoc->YoDeviceHashLookup(pDoc->m_currentDevice->m_parent);
				ptrPart = ptrDevice->m_ptrPart;
			}
			pDoc->YoAttachDevice(ptrPart);
		}

		if (pMainFrame->m_viewPartActive == TRUE)
		{
			sprintf(s, "%.1lf", pDoc->m_currentPart->m_translate[0]
				* pDoc->m_unitScaleFactor);
			pCBox = ((CComboBox*)pMainFrame->m_viewPart)->GetDlgItem(IDC_TRANSLATE_X);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();

			sprintf(s, "%.1lf", pDoc->m_currentPart->m_translate[1]
				* pDoc->m_unitScaleFactor);
			pCBox = ((CComboBox*)pMainFrame->m_viewPart)->GetDlgItem(IDC_TRANSLATE_Y);
			pCBox->SetWindowText(s);
			pCBox->UpdateWindow();
		}

		pDoc->m_undo->m_undoMode = YO_UNDO_PART_POSITION;
		pDoc->YoMessage("");

		//m_mode = YO_MODE_WALK;
		YoRender(YO_RENDER_LIGHT);
		YoRender(YO_RENDER_FULL);
		pMainFrame->SendMessage(WM_COMMAND, IDC_WALK, (LPARAM)0);

		return;
	}

	if (point.x == p0.x && point.y == p0.y && pDoc->m_deviceList != NULL)
	{
		YoRender(YO_RENDER_PICK_PART_AND_TAG);
		//if (pDoc->YoMakeCurrentDevicePartTag(point) == YO_DEVICE_PART
		//	&& pDoc->m_boundingBox == TRUE)
		{
			i = pDoc->YoMakeCurrentDevicePartTag(point);
			if (i == YO_DEVICE_PART)
			{
				sprintf(s, "Device: %s   Part: %s",
					pDoc->m_currentDevice->m_name, pDoc->m_currentPart->m_partName);
				pDoc->YoMessage(s);
			}
			else if (i == YO_TAG)
			{
				sprintf(s, "Path: %s   Tag: %d",
					pDoc->m_currentTag->m_ptrPath->m_name, pDoc->m_currentTag->m_tag);
				pDoc->YoMessage(s);
			}
			YoRender(YO_RENDER_FULL);
		}
	}
	else
	{
		YoRender(YO_RENDER_LIGHT);
		YoRender(YO_RENDER_FULL);
	}

	if ((point.x != p0.x || point.y != p0.y)
		&& m_mode == YO_MODE_WALK || m_mode == YO_MODE_PAN)
	{
		pDoc->m_undo->m_undoMode = YO_UNDO_EYE_POSITION;
	}

	return;
}

void CStageView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	if (pDoc->m_mode != YO_MODE_WORKCELL
		|| (pDoc->m_currentDevice != NULL
		&& pDoc->m_currentDevice->m_type == YO_CAMERA
		&& ((CStageCamera *)pDoc->m_currentDevice)->m_enabled == TRUE))
	{
		return;
	}

	CView::OnMouseMove(nFlags, point);

	if(GetCapture( ) != this )
	{
		return;
	}

	if (m_mode == YO_MODE_DEVICE_TRANSLATE)
	{
		YoTranslateDevice(point);
		return;
	}

	if (m_mode == YO_MODE_WALK && m_mouse == YO_MOUSE_LEFT)
	{
		YoWalk(point);
	}
	else if (m_mouse == YO_MOUSE_RIGHT)
	{
		YoPanInOut(point);
	}
	else if (m_mode == YO_MODE_PAN && m_mouse == YO_MOUSE_LEFT)
	{
		YoPanLeftRightUpDown(point);
	}

	YoUpdateEyeDlg();

	return;
}

void CStageView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CView::OnRButtonUp(nFlags, point);

	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	GLfloat p[1];
	GLdouble modelView[16];
	GLdouble proj[16];
	GLint viewport[4];
	GLdouble *objx;
	GLdouble *objy;
	GLdouble *objz;

	if (pDoc->m_mode != YO_MODE_WORKCELL
		|| (pDoc->m_currentDevice != NULL
		&& pDoc->m_currentDevice->m_type == YO_CAMERA
		&& ((CStageCamera *)pDoc->m_currentDevice)->m_enabled == TRUE))
	{
		return;
	}

	if(GetCapture( ) != this )
	{
		return;
	}

	ReleaseCapture( );

	if (pDoc->m_deviceBeingAttached == TRUE)
	{
		pDoc->m_undo->YoUndo();
		return;
	}

	if (point.x == p0.x && point.y == p0.y)
	{
		objx = new GLdouble[1];
		objy = new GLdouble[1];
		objz = new GLdouble[1];

		YoRender(YO_RENDER_PICK_PART);

		::glReadPixels(point.x, m_windowSize[1] - point.y - 1, 1, 1,
			GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid *)p);
		//winz = (GLdouble)(m_clipFront + ((m_clipRear - m_clipFront) * p[0]));
		TRACE1("depth buffer = %f\n", p[0]);

		if (p[0] == 1.0)
		{
			return;
		}

		::glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
		::glGetDoublev(GL_PROJECTION_MATRIX, proj);
		::glGetIntegerv(GL_VIEWPORT, viewport);
					
		::gluUnProject((GLdouble) point.x,
			(GLdouble)(m_windowSize[1] - point.y - 1),
			(GLdouble)p[0],
			modelView,
			proj,
			viewport,
			objx,
			objy,
			objz);
		TRACE3("obj (%lf, %lf, %lf)\n", *objx, *objy, *objz);
		::glMatrixMode(GL_MODELVIEW);
		/****
		for (i = 1; i < 10; i++)
		{
			tmpto[0] = m_eye[3] + ((objx[0] - m_eye[3]) * ((double)i / (double)10));
			tmpto[1] = m_eye[4] + ((objy[0] - m_eye[4]) * ((double)i / (double)10));
			tmpto[2] = m_eye[5] + ((objz[0] - m_eye[5]) * ((double)i / (double)10));
			::glLoadIdentity();
			::gluLookAt(m_eye[0], m_eye[1], m_eye[2],
				tmpto[0], tmpto[1], tmpto[2],
				m_eye[6], m_eye[7], m_eye[8]);
			YoRender(YO_RENDER_QUICK);
		}
		****/
		m_eye[3] = *objx;
		m_eye[4] = *objy;
		m_eye[5] = *objz;
		::glLoadIdentity();
		::gluLookAt(m_eye[0], m_eye[1], m_eye[2],
			m_eye[3], m_eye[4], m_eye[5],
			m_eye[6], m_eye[7], m_eye[8]);

		delete objx;
		delete objy;
		delete objz;
	}

	pDoc->m_undo->m_undoMode = YO_UNDO_EYE_POSITION;

	YoUpdateEyeDlg();

	//if (pDoc->m_acceptSocket != NULL)
	//{
	//	return;
	//}

	YoRender(YO_RENDER_LIGHT);
	YoRender(YO_RENDER_FULL);



	return;
}

void CStageView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
// Note: function keys will trigger this routine during debugging
// In particular F5 is the same as 't'
{	
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
	//HWND htop = ::GetTopWindow(NULL);
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}

	switch (tolower(nChar))
	{
		case '1':
			if (pDoc->m_mode == YO_MODE_WORKCELL)
			{
				m_mode = YO_MODE_WALK;
				pMainFrame->SendMessage(WM_COMMAND, IDC_WALK, (LPARAM)0);
			}
			break;

		case '2':
			if (pDoc->m_mode == YO_MODE_WORKCELL)
			{
				m_mode = YO_MODE_PAN;
				pMainFrame->SendMessage(WM_COMMAND, IDC_PAN, (LPARAM)0);
			}
			break;

		case '3':
			if (pDoc->m_mode == YO_MODE_WORKCELL
				&& pDoc->m_currentPart != NULL
				&& pDoc->m_currentDevice != NULL
				&& pMainFrame->m_viewPartActive == FALSE
				&& pMainFrame->m_analysisActive == FALSE
				&& pMainFrame->m_viewTagActive == FALSE
				&& pDoc->m_acceptSocket == NULL
				&& pDoc->m_animationState == YO_PAUSE
				&& (pDoc->m_undo->m_undoMode != YO_UNDO_DEVICE_DELETE
				|| pDoc->m_deviceList != pDoc->m_currentDevice
				|| pDoc->m_currentDevice->m_down != NULL
				|| pDoc->m_currentDevice->m_right != NULL))				
			{
				m_mode = YO_MODE_DEVICE_TRANSLATE;
				pMainFrame->SendMessage(WM_COMMAND, IDC_DEVICE_TRANSLATE, (LPARAM)0);
			}
			break;

		case '4':
			if (pDoc->m_mode == YO_MODE_WORKCELL)
			{
				pMainFrame->SendMessage(WM_COMMAND, IDC_EYE, (LPARAM)0);
			}
			break;

		case '5':
			if (pDoc->m_mode == YO_MODE_WORKCELL)
			{
				pMainFrame->SendMessage(WM_COMMAND, IDC_SCRIPT, (LPARAM)0);
			}
			break;

		break;


	}
}

BOOL CStageView::YoInitOpenGL()
{

	GLint i;

	m_pDC = new CClientDC(this);

	if (!m_pDC)
	{
		MessageBox("Unable to get a DC");
		return FALSE;
	}

	if (!YoSetupPixelFormat())
	{
		return FALSE;
	}

	if ((m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc())) == 0)
	{
		AfxMessageBox("wglCreateContext failed");
		return FALSE;
	}

	if ((::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC)) == FALSE)
	{
		AfxMessageBox("wglMakeCurrent failed");
		return FALSE;
	}

	// specify black as clear color and opaque
	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// specify back of depth buffer as clear depth
	::glClearDepth(1.0f);
	// enable depth testing
	::glEnable(GL_DEPTH_TEST);
	::glEnable(GL_NORMALIZE);
	// enable anti-aliasing
	//::glEnable(GL_POINT_SMOOTH);
	//::glEnable(GL_POLYGON_SMOOTH);
	//::glEnable(GL_LINE_SMOOTH);
	//::glEnable(GL_BLEND);
	//::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//::glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	//::glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	//::glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);

	::glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	::glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, YO_DEFAULT_LIGHTING_TWO_SIDED);
	GLfloat lma[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	::glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lma);
	::glPolygonMode(GL_BACK, GL_POINT);

	::glGetIntegerv(GL_RED_BITS, &i);
	TRACE1("RGBA bits = (%d, ", i);
	::glGetIntegerv(GL_GREEN_BITS, &i);
	TRACE1("%d, ", i);
	::glGetIntegerv(GL_BLUE_BITS, &i);
	TRACE1("%d, ", i);
	::glGetIntegerv(GL_ALPHA_BITS, &i);
	TRACE1("%d)\n", i);
	::glGetIntegerv(GL_DEPTH_BITS, &i);
	TRACE1("Depth buffer bits = %d\n", i);
	::glGetIntegerv(GL_ACCUM_RED_BITS, &i);
	TRACE1("Accumulation buffer bits = (%d, ", i);
	::glGetIntegerv(GL_ACCUM_GREEN_BITS, &i);
	TRACE1("%d, ", i);
	::glGetIntegerv(GL_ACCUM_BLUE_BITS, &i);
	TRACE1("%d, ", i);
	::glGetIntegerv(GL_ACCUM_ALPHA_BITS, &i);
	TRACE1("%d)\n", i);

//There are eight new OpenGL functions in Windows NT 4.0: wglCreateLayerContext, wglDescribeLayerPlane, wglSetLayerPaletteEntries, wglGetLayerPaletteEntries, wglRealizeLayerPalette, wglSwapLayerBuffers, wglCopyContext, and GetEnhMetaFilePixelFormat. Most of these functions deal with layer planes. Video boards often break up the color contents of a given pixel into layers (for example, a red plane, a green plane, and a blue plane). In Windows NT 4.0, these new OpenGL functions let you read and write the video layers directly. 

	TRACE1("_WIN32_WINNT = %x\n", _WIN32_WINNT);
	SYSTEM_INFO siSysInfo;
	::GetSystemInfo(&siSysInfo);
	TRACE0("GetSystemInfo:\n");
	TRACE1("OEM ID: %u\n", siSysInfo.dwOemId);
	TRACE1("Number of processors: %u\n", siSysInfo.dwNumberOfProcessors);
	TRACE1("Page size: %u\n", siSysInfo.dwPageSize);
	TRACE1("Processor type: %u\n", siSysInfo.dwProcessorType);
	TRACE1("Minimum application address: %lx\n", siSysInfo.lpMinimumApplicationAddress);
	TRACE1("Maximum application address: %lx\n", siSysInfo.lpMaximumApplicationAddress);
	TRACE1("Active processor mask: %u\n", siSysInfo.dwActiveProcessorMask);

	//HW_PROFILE_INFO   HwProfInfo;
	//if (!GetCurrentHwProfile(&HwProfInfo))
	//{
	//	TRACE1("::GetCurrentHwProfile failed with error %lx\n", GetLastError());
	//}
	//else
	//{
	//	TRACE1("DockInfo = %d\n", HwProfInfo.dwDockInfo);
	//	TRACE1("Profile Guid = %s\n", HwProfInfo.szHwProfileGuid);
	//	TRACE1("Friendly Name = %s\n", HwProfInfo.szHwProfileName);
	//}

	m_fieldOfView = 30.0;
	m_clipFront = 100.0;
	m_clipRear = 100000.0;
	m_eye[0] = 10000.0;
	m_eye[1] = 6000.0;
	m_eye[2] = 5000.0;
	m_eye[3] = 0.0;
	m_eye[4] = 0.0;
	m_eye[5] = 0.0;
	m_eye[6] = 0.0;
	m_eye[7] = 0.0;
	m_eye[8] = 1.0;
	m_walkSpeed = 0.01;
	m_panInOutSpeed = 0.005;
	m_panLeftRightUpDownSpeed = 0.01;
	m_mode = YO_MODE_WALK;

	return TRUE;
}

BOOL CStageView::YoSetupPixelFormat()
{

    const PIXELFORMATDESCRIPTOR pfd =
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,								// version number
        PFD_DRAW_TO_WINDOW |            // support window
          PFD_SUPPORT_OPENGL |          // support OpenGL
          PFD_DOUBLEBUFFER, // |            // double buffered
		  //PFD_GENERIC_ACCELERATED,
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        //3, 16, 3, 8, 3, 0,               // color bits ignored
		0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
		//8,                              // 8-bit alpha buffer
        0,                              // shift bit ignored
        //0,                              // no accumulation buffer
		32,                              // 32-bit accumulation buffer
        8, 8, 8, 8,                     // accum bits ignored
        32,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };

    int pixelformat;

	// First-chance exception in stage.exe (GDI32.DLL): 0xC0000005: Access Violation
	// occurs (sometimes!) when calling ::ChoosePixelFormat

    if ((pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
    {
        AfxMessageBox("ChoosePixelFormat failed.  Unable to run program");
        return FALSE;
    }

    if (::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
        AfxMessageBox("SetPixelFormat failed.  Unable to run program");
        return FALSE;
    }

    return TRUE;
}


/****
BOOL CStageView::YoRenderSetup(int option)
{
	if (option == YO_RENDER_FULL)
	{
		// create a worker thread for rendering
		CStageDoc* pDoc = GetDocument();
		pDoc->m_threadRender = AfxBeginThread(YoThreadRender, this);
		pDoc->m_threadRender = NULL;
	}
	else
	{
		YoRender(option);
	}
	return TRUE;
}
****/


BOOL CStageView::YoRender(int option)

// main drawing routine which renders a frame into the current buffer

{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	GLdouble view[16];
	GLfloat lightIntensity[4];
	GLfloat lightPosition[4];
	int i;

	if (option == YO_RENDER_QUICK && pDoc->m_quickMode != YO_WIREFRAME)
	{
		YoRender(YO_RENDER_LIGHT);
	}

	if (pDoc->m_camera != NULL)
	{
		pDoc->m_camera->YoPositionCamera();
	}
	else
	{
		if (m_eye[0] == m_eye[3] && m_eye[1] == m_eye[4])
		// will result in singular matrix when YoMatrixInverse is called
		// so jitter fromy eye position slightly
		{
			m_eye[1] += 0.0001;
			::glMatrixMode(GL_MODELVIEW);
			::glLoadIdentity();
			::gluLookAt(m_eye[0], m_eye[1], m_eye[2],
				m_eye[3], m_eye[4], m_eye[5],
				m_eye[6], m_eye[7], m_eye[8]);
		}
		else if (m_eye[8] == 0.0f)
		{
			m_eye[8] = 1.0f;
			::glMatrixMode(GL_MODELVIEW);
			::glLoadIdentity();
			::gluLookAt(m_eye[0], m_eye[1], m_eye[2],
				m_eye[3], m_eye[4], m_eye[5],
				m_eye[6], m_eye[7], m_eye[8]);
		}
	}

	::glMatrixMode(GL_MODELVIEW);
	::glGetDoublev(GL_MODELVIEW_MATRIX, view);

	pDoc->YoMatrixInverse(view, m_viewInv);


	/***
//if (fl_get_button(obj_form5_play) == 1
//  && ((fl_get_button(obj_form5_motion_blur) == 1)
//  || fl_get_button(obj_form1_anti_alias) == 1 
//  || fl_get_button(obj_form1_shadows) == 1))
	if (pDoc->m_animationState == YO_PLAY
		&& pDoc->m_motionEffectModified == FALSE
		//&& pDoc->m_timeModified == FALSE
		&& pDoc->m_render3d)
	{
		YoAccumulate();
	}
	***/

	//else  // normal drawing mode 
	{
		//if (pDoc->m_animationState == YO_PLAY)
		//{
		//	pMainFrame->SendMessage(EN_KILLFOCUS, IDC_PLAY, (LPARAM)0);
		//}

		::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		::glClearDepth(1.0f);
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(pDoc->m_grid[0] && option != YO_RENDER_PICK_PART
			&& option != YO_RENDER_PICK_PART_AND_TAG)
		{
			YoRenderGrid();
		}

		if (option == YO_RENDER_NO_LIGHT)
		{
			YoRenderDevice(0);
		}
		else if (option == YO_RENDER_QUICK)
		{
			YoRenderDevice(YO_RENDER_QUICK);
		}
		else if (option == YO_RENDER_PICK_PART || option == YO_RENDER_PICK_PART_AND_TAG)
		{
			YoRenderDevice(option);
		}
		else if (option == YO_RENDER_LIGHT)
		{
			// set up sun
			for (i = 0; i < 3; i++)
			{
				lightIntensity[i] = (GLfloat)(pDoc->m_sunIntensity);
			}
			lightIntensity[3] = 1.0;
	
			::glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
			::glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
			::glLightfv(GL_LIGHT0, GL_SPECULAR, lightIntensity);

			if (pDoc->m_sunAltitude == 90.0)
			{
				lightPosition[0] = 0.0f;
				lightPosition[1] = 0.0f;
				lightPosition[2] = 1.0f;
			}
			else if (pDoc->m_sunAltitude == -90.0)
			{
				lightPosition[0] = 0.0f;
				lightPosition[1] = 0.0f;
				lightPosition[2] = -1.0f;
			}
			else
			{
				lightPosition[0] = (GLfloat)cos((double)pDoc->m_sunAzimuth * YO_DEGREES_TO_RADIANS);
				lightPosition[1] = (GLfloat)sin((double)pDoc->m_sunAzimuth * YO_DEGREES_TO_RADIANS);
				lightPosition[2] = (GLfloat)sin((double)pDoc->m_sunAltitude * YO_DEGREES_TO_RADIANS);
			}

			lightPosition[3] = 0.0f;  // directional light source

			::glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

			::glEnable(GL_LIGHT0);

			if (pDoc->m_numberLightsOn > 0)
			{
				YoRenderDevice(YO_RENDER_LIGHT);
			}
		}
		else
		{
			YoRenderDevice(0);
		}
		
		if (option != YO_RENDER_PICK_PART && option != YO_RENDER_PICK_PART_AND_TAG
			&& pMainFrame->m_analysisActive == TRUE)
		{
			YoRenderAnalysis();
		}
	}

/***********
	//if (fl_get_button(obj_form1_add_noise) == 1)
	if (yo_render2d & YO_RENDER2D_NOISE)
	{
		// winset not supported -- See Window Manager
		// winset(window_0)
		// getsize not supported -- See Window Manager
		// getsize(&x_winsize, &y_winsize)

		for (i = 0; i < y_winsize; i++)
		{
			// OGLXXX lrectread: see man page for glReadPixels
			glReadPixels(0, i, x_winsize, 1, GL_RGBA, GL_BYTE, imgbuf);

			for (j = 0; j < x_winsize; j++)
			{
				//imgbuf[j] = (random()&0x001F1F1F)|(imgbuf[j]&0xFFE0E0E0);
				imgbuf[j] = (random()&0x000F0F0F)|(imgbuf[j]&0xFFF0F0F0);
			}
			// OGLXXX lrectwrite: see man page for glDrawPixels
			glRasterPos2i(0, i);
			glDrawPixels(x_winsize, 1, GL_RGBA, GL_BYTE, imgbuf);
		}
	}

	//if (fl_get_choice(obj_form5_screen) == 4      // 3:2 35mm film
	//  || fl_get_choice(obj_form5_screen) == 5)    // 16:9 HDTV
	if (yo_screen == YO_SCREEN_VHS_640X480_35MM 
		|| yo_screen == YO_SCREEN_VHS_640X480_HDTV
	{
		//getsize not supported -- See Window Manager
		//getsize(&x_winsize, &y_winsize)

		glBlendFunc(GL_ONE, GL_ZERO);
		//if (fl_get_choice(obj_form5_screen) == 4)
		if (yo_screen == YO_SCREEN_VHS_640X480_35MM)
		{
			for (i = 0; i < 27; i++)
			{
				gl
				2i(0, i);
				glDrawPixels(x_winsize, 1, GL_RGBA, GL_BYTE, ptr_black); 
			}
			for (i = 454; i < 480; i++)
			{
				glRasterPos2i(0, i);
				glDrawPixels(x_winsize, 1, GL_RGBA, GL_BYTE, ptr_black); 
			}
		}
		else if (yo_screen == YO_SCREEN_VHS_640X480_HDTV)
		{
			for (i = 0; i < 60; i++)
			{
				glRasterPos2i(0, i);
				glDrawPixels(x_winsize, 1, GL_RGBA, GL_BYTE, ptr_black); 
			}
			for (i = 420; i < 480; i++)
			{
				glRasterPos2i(0, i);
				glDrawPixels(x_winsize, 1, GL_RGBA, GL_BYTE, ptr_black); 
			}
		}

		// if (fl_get_choice(obj_form0_blend) == 2)
		if (yo_blend == YO_BLEND_GL_SRC_ALPHA_GL_ONE_MINUS_SRC_ALPHA)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		//else if (fl_get_choice(obj_form0_blend) == 3)
		else if (yo_blend == YO_BLEND_GL_ONE_GL_ONE_MINUS_SRC_ALPHA)
		{
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		}
		//  else if (fl_get_choice(obj_form0_blend) == 4)
		else if (yo_blend == YO_BLEND_GL_SRC_ALPHA_GL_DST_ALPHA)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
		}
	}
********/

	//glXSwapBuffers(*display, window);
	if (option != YO_RENDER_PICK_PART && option != YO_RENDER_PICK_PART_AND_TAG
		&& option != YO_RENDER_LIGHT)
	{
		if (pDoc->m_mode == YO_MODE_PLAY_SIM
			&& pDoc->m_renderMode == YO_RENDER3D
			//&& pDoc->m_outputBitmap == TRUE
			&& pDoc->m_antiAlias == TRUE
			&& pDoc->m_animationState == YO_PLAY)
		{
			YoAntiAlias();
		}

		if (pDoc->m_mode == YO_MODE_PLAY_SIM
			&& pDoc->m_animationState == YO_PLAY
			&& pDoc->m_realTime == FALSE
			&& pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR
			&& pDoc->m_renderMode == YO_RENDER3D
			&& pDoc->m_isMovement)
		{
			// SwapBuffers will be called in CMainFrame::OnTimer()
		}
		else if (::SwapBuffers(m_pDC->GetSafeHdc()) == FALSE)
		{
			AfxMessageBox("ERROR in CStageView::YoRender().  SwapBuffers failed.");
			return FALSE;
		}
	}

/*********
	//if (fl_get_button(obj_form5_play) == 1
	//  && fl_get_button(obj_form5_movie_out) == 1)
	if (pDoc->animationState == YO_PLAY && yo_movie_out)
	{
		if ((yo_screen | YO_SCREEN_320X240 | YO_SCREEN_VHS_640X480
			| YO_SCREEN_VHS_640X480_35MM | YO_SCREEN_VHS_640X480_HDTV)
			&& yo_time_cur % (yo_frames_per_second
			/ (60 / yo_frames_per_update)) == 0)
		{
			if ((ptr = popen("echo $HOME", "r")) != NULL)
			{
				fscanf(ptr, "%s", t);   // get path to user home dir
				pclose(ptr);
			}
			strcat(t, "/stage/stagelib/movies/");
			fprintf(m_fp, "%s%s.%04d.rgb", t, yo_filename(workcell_name),
			yo_time_cur / (yo_frames_per_second / (60 / yo_frames_per_update)));
			yo_SaveWindow(s);
		}
	}
**********/
	return TRUE;
}

void CStageView::YoWriteDevice(CStageDevice *currentDevice, int option)
{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CStageDevice *ptrParent;

	if (currentDevice->m_type == YO_DEVICE
		|| currentDevice->m_type == YO_TRACK)
	{
		if (currentDevice->m_type == YO_TRACK)
		{
			fprintf(m_fp, "TRACK\n");
		}
		else
		{
			fprintf(m_fp, "DEVICE\n");
		}
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "DEVICE_NAME %s\n", currentDevice->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "DEVICE_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "DEVICE_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "DEVICE_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "DEVICE_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "DEVICE_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "DEVICE_SCALE %f %f %f\n", currentDevice->m_scale[0],
			currentDevice->m_scale[1], currentDevice->m_scale[2]);
		fprintf(m_fp, "DEVICE_NULL\n");
	}

	else if (currentDevice->m_type == YO_LIGHT)
	{
		fprintf(m_fp, "LIGHT\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "LIGHT_NAME %s\n", currentDevice->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "LIGHT_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "LIGHT_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "LIGHT_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "LIGHT_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "LIGHT_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "LIGHT_SCALE %f %f %f\n", currentDevice->m_scale[0],
			currentDevice->m_scale[1], currentDevice->m_scale[2]);
		if (((CStageLight *)currentDevice)->m_enabled)
		{
			fprintf(m_fp, "LIGHT_ENABLED 1\n");
		}
		else
		{
			fprintf(m_fp, "LIGHT_ENABLED 0\n");
		}
		if (((CStageLight *)currentDevice)->m_pointSource)
		{
			fprintf(m_fp, "LIGHT_POINT_SOURCE 1\n");
		}
		else
		{
			fprintf(m_fp, "LIGHT_POINT_SOURCE 0\n");
		}
		fprintf(m_fp, "LIGHT_INTENSITY %f\n",
			((CStageLight *)currentDevice)->m_intensity);
		/***
		fprintf(m_fp, "LIGHT_AMBIENT %f %f %f %f\n",
			((CStageLight *)currentDevice)->m_ambient[0],
			((CStageLight *)currentDevice)->m_ambient[1],
			((CStageLight *)currentDevice)->m_ambient[2],
			((CStageLight *)currentDevice)->m_ambient[3]);
		fprintf(m_fp, "LIGHT_DIFFUSE %f %f %f %f\n",
			((CStageLight *)currentDevice)->m_diffuse[0],
			((CStageLight *)currentDevice)->m_diffuse[1],
			((CStageLight *)currentDevice)->m_diffuse[2],
			((CStageLight *)currentDevice)->m_diffuse[3]);
		fprintf(m_fp, "LIGHT_SPECULAR %f %f %f %f\n",
			((CStageLight *)currentDevice)->m_specular[0],
			((CStageLight *)currentDevice)->m_specular[1],
			((CStageLight *)currentDevice)->m_specular[2],
			((CStageLight *)currentDevice)->m_specular[3]);
		fprintf(m_fp, "LIGHT_POSITION %f %f %f %f\n",
			((CStageLight *)currentDevice)->m_position[0],
			((CStageLight *)currentDevice)->m_position[1],
			((CStageLight *)currentDevice)->m_position[2],
			((CStageLight *)currentDevice)->m_position[3]);
		//fprintf(m_fp, "LIGHT_PARAMETER_NAME %i\n",
			//((CStageLight *)currentDevice)->m_parameterName);
		fprintf(m_fp, "LIGHT_SPOT_EXPONENT %f\n",
			((CStageLight *)currentDevice)->m_spotExponent);
		***/
		fprintf(m_fp, "LIGHT_SPOT_CUTOFF %f\n",
			((CStageLight *)currentDevice)->m_spotCutoff);
		fprintf(m_fp, "LIGHT_ATTENUATION %f %f %f\n",
			((CStageLight *)currentDevice)->m_attenuation[0],
			((CStageLight *)currentDevice)->m_attenuation[1],
			((CStageLight *)currentDevice)->m_attenuation[2]);
		fprintf(m_fp, "LIGHT_NULL\n");
	}

	else if (currentDevice->m_type == YO_ROBOT6)
	{
		fprintf(m_fp, "ROBOT6\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "ROBOT6_NAME %s\n",
				((CStageRobot6 *)currentDevice)->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "ROBOT6_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "ROBOT6_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "ROBOT6_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "ROBOT6_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "ROBOT6_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "ROBOT6_MIN_ACCEL_TIME %.3lf\n",
			((CStageRobot6 *)currentDevice)->m_minAccelTime);
		fprintf(m_fp, "ROBOT6_HOME %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_home[1],
			((CStageRobot6 *)currentDevice)->m_home[2],
			((CStageRobot6 *)currentDevice)->m_home[3],
			((CStageRobot6 *)currentDevice)->m_home[4],
			((CStageRobot6 *)currentDevice)->m_home[5],
			((CStageRobot6 *)currentDevice)->m_home[6]);
		fprintf(m_fp, "ROBOT6_JOINT_VALUES %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_j[1],
			((CStageRobot6 *)currentDevice)->m_j[2],
			((CStageRobot6 *)currentDevice)->m_j[3],
			((CStageRobot6 *)currentDevice)->m_j[4],
			((CStageRobot6 *)currentDevice)->m_j[5],
			((CStageRobot6 *)currentDevice)->m_j[6]);
		fprintf(m_fp, "ROBOT6_MAX_ACCEL %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[1][0],
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[2][0],
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[3][0],
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[4][0],
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[5][0],
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[6][0]);
		fprintf(m_fp, "ROBOT6_MAX_SPEED %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[1][1],
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[2][1],
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[3][1],
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[4][1],
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[5][1],
			((CStageRobot6 *)currentDevice)->m_jMaxAccelMaxSpeed[6][1]);
		fprintf(m_fp, "ROBOT6_MIN_ACCEL_TIME %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_jMinAccelTime[1],
			((CStageRobot6 *)currentDevice)->m_jMinAccelTime[2],
			((CStageRobot6 *)currentDevice)->m_jMinAccelTime[3],
			((CStageRobot6 *)currentDevice)->m_jMinAccelTime[4],
			((CStageRobot6 *)currentDevice)->m_jMinAccelTime[5],
			((CStageRobot6 *)currentDevice)->m_jMinAccelTime[6]);
		fprintf(m_fp, "ROBOT6_MIN_JOINT_VALUES %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_jMinMax[1][0],
			((CStageRobot6 *)currentDevice)->m_jMinMax[2][0],
			((CStageRobot6 *)currentDevice)->m_jMinMax[3][0],
			((CStageRobot6 *)currentDevice)->m_jMinMax[4][0],
			((CStageRobot6 *)currentDevice)->m_jMinMax[5][0],
			((CStageRobot6 *)currentDevice)->m_jMinMax[6][0]);
		fprintf(m_fp, "ROBOT6_MAX_JOINT_VALUES %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_jMinMax[1][1],
			((CStageRobot6 *)currentDevice)->m_jMinMax[2][1],
			((CStageRobot6 *)currentDevice)->m_jMinMax[3][1],
			((CStageRobot6 *)currentDevice)->m_jMinMax[4][1],
			((CStageRobot6 *)currentDevice)->m_jMinMax[5][1],
			((CStageRobot6 *)currentDevice)->m_jMinMax[6][1]);

		fprintf(m_fp, "ROBOT6_JOINT_INTERPOLATION %d\n",
			((CStageRobot6 *)currentDevice)->m_jointInterpolation);
		fprintf(m_fp, "ROBOT6_MAX_SCREW_SPEED %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_maxScrewSpeed);
		fprintf(m_fp, "ROBOT6_MAX_SCREW_ACCEL %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_maxScrewAccel);
		fprintf(m_fp, "ROBOT6_MAX_TOOL_SPEED %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_maxToolSpeed);
		fprintf(m_fp, "ROBOT6_MAX_TOOL_ACCEL %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_maxToolAccel);
		fprintf(m_fp, "ROBOT6_SPEED %d\n", 
			((CStageRobot6 *)currentDevice)->m_speed);
		fprintf(m_fp, "ROBOT6_TCP_OFFSET %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
			((CStageRobot6 *)currentDevice)->m_tcpOffset[0],
			((CStageRobot6 *)currentDevice)->m_tcpOffset[1],
			((CStageRobot6 *)currentDevice)->m_tcpOffset[2],
			((CStageRobot6 *)currentDevice)->m_tcpOffset[3],
			((CStageRobot6 *)currentDevice)->m_tcpOffset[4],
			((CStageRobot6 *)currentDevice)->m_tcpOffset[5]);
		fprintf(m_fp, "ROBOT6_NULL\n");
	}
	else if (currentDevice->m_type == YO_ROTARY_TABLE)
	{
		fprintf(m_fp, "ROTARY_TABLE\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "ROTARY_TABLE_NAME %s\n",
				((CStageRotaryTable *)currentDevice)->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "ROTARY_TABLE_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "ROTARY_TABLE_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "ROTARY_TABLE_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "ROTARY_TABLE_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "ROTARY_TABLE_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "ROTARY_TABLE_ACCEL %f\n",
			((CStageRotaryTable *)currentDevice)->m_acceleration);
		fprintf(m_fp, "ROTARY_TABLE_VELOCITY %f\n",
			((CStageRotaryTable *)currentDevice)->m_velocity);
		fprintf(m_fp, "ROTARY_TABLE_POSITION %ld\n",
			((CStageRotaryTable *)currentDevice)->m_currentPosition);
		fprintf(m_fp, "ROTARY_TABLE_DIRECTION_POSITIVE %d\n",
			((CStageRotaryTable *)currentDevice)->m_directionPositive);
		fprintf(m_fp, "ROTARY_TABLE_NULL\n");
	}

	else if (currentDevice->m_type == YO_BARRETT_HAND)
	{
		fprintf(m_fp, "BARRETT_HAND\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "BARRETT_HAND_NAME %s\n",
				((CStageBarrettHand *)currentDevice)->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "BARRETT_HAND_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "BARRETT_HAND_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "BARRETT_HAND_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "BARRETT_HAND_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "BARRETT_HAND_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "BARRETT_HAND_GRIPPING %d\n",
			((CStageBarrettHand *)currentDevice)->m_gripping);
		fprintf(m_fp, "BARRETT_HAND_VELOCITY %.3lf\n",
			((CStageBarrettHand *)currentDevice)->m_velocity);
		fprintf(m_fp, "BARRETT_HAND_SPREAD %.3lf\n",
			((CStageBarrettHand *)currentDevice)->m_spread);
		fprintf(m_fp, "BARRETT_HAND_FINGER_FIXED %.3lf %.3lf\n",
			((CStageBarrettHand *)currentDevice)->m_fingerFixed[1],
			((CStageBarrettHand *)currentDevice)->m_fingerFixed[2]);
		fprintf(m_fp, "BARRETT_HAND_FINGER_LEFT %.3lf %.3lf\n",
			((CStageBarrettHand *)currentDevice)->m_fingerLeft[1],
			((CStageBarrettHand *)currentDevice)->m_fingerLeft[2]);
		fprintf(m_fp, "BARRETT_HAND_FINGER_RIGHT %.3lf %.3lf\n",
			((CStageBarrettHand *)currentDevice)->m_fingerRight[1],
			((CStageBarrettHand *)currentDevice)->m_fingerRight[2]);
		fprintf(m_fp, "BARRETT_HAND_NULL\n");
	}

	else if (currentDevice->m_type == YO_CAMERA)
	{
		fprintf(m_fp, "CAMERA\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "CAMERA_NAME %s\n",
				((CStageCamera *)currentDevice)->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "CAMERA_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "CAMERA_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "CAMERA_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "CAMERA_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "CAMERA_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "CAMERA_FIELD_OF_VIEW %.3f\n", ((CStageCamera *)currentDevice)->m_fieldOfView);
		fprintf(m_fp, "CAMERA_F_STOP %.1f\n", ((CStageCamera *)currentDevice)->m_fStop);
		fprintf(m_fp, "CAMERA_CLIPPING_PLANES %.3f %.3f\n",
			((CStageCamera *)currentDevice)->m_clipFront, ((CStageCamera *)currentDevice)->m_clipRear);
		fprintf(m_fp, "CAMERA_NULL\n");
	}

	else if (currentDevice->m_type == YO_GRIPPER)
	{
		fprintf(m_fp, "GRIPPER\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "GRIPPER_NAME %s\n",
				((CStageGripper *)currentDevice)->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "GRIPPER_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "GRIPPER_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "GRIPPER_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "GRIPPER_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "GRIPPER_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "GRIPPER_TYPE_TRANSLATING %d\n",
			((CStageGripper *)currentDevice)->m_typeTranslating);
		fprintf(m_fp, "GRIPPER_GRIPPING %d\n",
			((CStageGripper *)currentDevice)->m_gripping);
		fprintf(m_fp, "GRIPPER_DISPLACEMENT_OPEN %.3lf\n",
			((CStageGripper *)currentDevice)->m_displacementOpen);
		fprintf(m_fp, "GRIPPER_DISPLACEMENT_CLOSE %.3lf\n",
			((CStageGripper *)currentDevice)->m_displacementClose);
		fprintf(m_fp, "GRIPPER_NULL\n");
	}

	else if (currentDevice->m_type == YO_BAR_CODE_READER)
	{
		fprintf(m_fp, "BAR_CODE_READER\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "BAR_CODE_READER_NAME %s\n",
				((CStageBarCodeReader *)currentDevice)->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "BAR_CODE_READER_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "BAR_CODE_READER_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "BAR_CODE_READER_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "BAR_CODE_READER_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "BAR_CODE_READER_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "BAR_CODE_READER_NULL\n");
	}

	else if (currentDevice->m_type == YO_SCALE)
	{
		fprintf(m_fp, "SCALE\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "SCALE_NAME %s\n",
				((CStageScale *)currentDevice)->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "SCALE_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "SCALE_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "SCALE_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "SCALE_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "SCALE_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "SCALE_UNITS %d\n",
			((CStageScale *)currentDevice)->m_units);
		fprintf(m_fp, "SCALE_NULL\n");
	}
	else if (currentDevice->m_type == YO_TRAIN)
	{
		fprintf(m_fp, "TRAIN\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "TRAIN_NAME %s\n",
				((CStageTrain *)currentDevice)->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "TRAIN_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "TRAIN_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "TRAIN_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "TRAIN_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "TRAIN_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "TRAIN_ACCELERATION %.3lf\n", ((CStageTrain *)currentDevice)->m_acceleration);
		fprintf(m_fp, "TRAIN_VELOCITY %.3lf\n", ((CStageTrain *)currentDevice)->m_velocity);
		ptrParent = pDoc->YoDeviceHashLookup(currentDevice->m_parent);
		if (ptrParent != NULL && ptrParent->m_type == YO_TRACK)
		{
			fprintf(m_fp, "TRAIN_ATTACH_RELATIVE_POSITION %.3lf\n", ((CStageTrain *)currentDevice)->m_relativePosition);
			fprintf(m_fp, "TRAIN_ATTACH_TRACK_SEG %s\n", ((CStageTrain *)currentDevice)->m_ptrTrackSeg->m_ptrPart->m_partName);
			//fprintf(m_fp, "TRAIN_ATTACH_TRACK_SEG %d\n", ((CStageTrain *)currentDevice)->m_attachTrackSeg);
		}
		fprintf(m_fp, "TRAIN_NULL\n");
	}
	else if (currentDevice->m_type == YO_CONVEYOR)
	{
		fprintf(m_fp, "CONVEYOR\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "CONVEYOR_NAME %s\n",
				((CStageConveyor *)currentDevice)->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "CONVEYOR_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "CONVEYOR_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "CONVEYOR_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "CONVEYOR_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "CONVEYOR_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "CONVEYOR_OFFSET %.3lf %.3lf %.3lf\n",
			((CStageConveyor *)currentDevice)->m_offset[0],
			((CStageConveyor *)currentDevice)->m_offset[1],
			((CStageConveyor *)currentDevice)->m_offset[2]);
		fprintf(m_fp, "CONVEYOR_NULL\n");
	}

	else if (currentDevice->m_type == YO_CONVEYOR_PALLET)
	{
		fprintf(m_fp, "CONVEYOR_PALLET\n");
		if (option == YO_RENDER_SAVE_WORKCELL)
		{
			fprintf(m_fp, "CONVEYOR_PALLET_NAME %s\n",
				((CStageConveyorPallet *)currentDevice)->m_name);
			if (currentDevice->m_attachedFromPart != NULL)
			{
				fprintf(m_fp, "CONVEYOR_PALLET_PARENT %s %s\n",
					currentDevice->m_parent,
					currentDevice->m_attachedFromPart->m_partName);
			}
			else
			{
				fprintf(m_fp, "CONVEYOR_PALLET_PARENT %s NONE\n",
					currentDevice->m_parent);
			}
			fprintf(m_fp, "CONVEYOR_PALLET_VISIBLE %d\n", currentDevice->m_visible);
		}
		fprintf(m_fp, "CONVEYOR_PALLET_MASS %.3lf\n", currentDevice->m_mass);
		fprintf(m_fp, "CONVEYOR_PALLET_BAR_CODE %s\n", currentDevice->m_barCode);
		fprintf(m_fp, "CONVEYOR_PALLET_POSITION %.3lf %.3lf %.3lf\n",
			((CStageConveyorPallet *)currentDevice)->m_position[0],
			((CStageConveyorPallet *)currentDevice)->m_position[1],
			((CStageConveyorPallet *)currentDevice)->m_position[2]);
		fprintf(m_fp, "CONVEYOR_PALLET_NULL\n");
	}

	fprintf(m_fp, "#\n");
}


BOOL CStageView::YoRenderDevice(int option)
{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	BOOL done = FALSE;
	CStageDevice *currentDevice = pDoc->m_deviceList;
	GLfloat lightIntensity[4];
	GLfloat lightPosition[4];
	int i;

	pDoc->m_deviceStack = NULL;

	if (currentDevice == NULL)
	{
		return TRUE;
	}

	if (option == YO_RENDER_LIGHT_VIEWPOINT)
	{
		pDoc->m_numberLightsOn = 0;
	}

	while (!done)
	{
		/***
		if (::PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE)
			&& (option == YO_RENDER_FULL))
		{
			option = YO_RENDER_QUICK;
		}
		***/

		//if (option == YO_OPTION_OBJECT_ATTACH)
			// fl_addto_browser(obj_attach_browser, cur->name);
		//if (option == YO_OPTION_OBJECT_ENTER)
			// fl_addto_browser(obj_enter_browser, cur->name);
		if (option == YO_RENDER_SAVE_WORKCELL
			|| (option == YO_RENDER_SAVE_DEVICE
			&& currentDevice == pDoc->m_currentDevice))
		{
			YoWriteDevice(currentDevice, option);
			//const CString& workcellName = pDoc->GetPathName( );
			//m_fp = fopen(workcellName, "a");
		}

		glPushMatrix();
		glScaled(currentDevice->m_scale[0],
			currentDevice->m_scale[1], currentDevice->m_scale[2]);



		if (option == YO_RENDER_LIGHT
			|| option == YO_RENDER_LIGHT_VIEWPOINT)
		{
			//if (pDoc->m_animationState == YO_PLAY
			//	&& currentDevice->m_ptrPart->m_score != NULL
			//	&& currentDevice->m_ptrPart->m_currentScore->m_time <= pDoc->m_timeCurrent)
			//{
			//	while(currentDevice->m_ptrPart->m_currentScore->m_next != NULL
			//		&& currentDevice->m_ptrPart->m_currentScore->m_time < pDoc->m_timeCurrent
			//		&& currentDevice->m_ptrPart->m_currentScore->m_next->m_time <= pDoc->m_timeCurrent)
			//	{
			//		currentDevice->m_ptrPart->m_currentScore
			//			= currentDevice->m_ptrPart->m_currentScore->m_next;
			//	}
			//	if (pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR
			//		&& pDoc->m_timeMotionBlur > 0
			//		&& currentDevice->m_ptrPart->m_currentScore->m_next != NULL
			//		&& currentDevice->m_ptrPart->m_currentScore->m_next->m_time
			//		- currentDevice->m_ptrPart->m_currentScore->m_time == 1)
			//	{
			//		YoMotionBlurModelView(YO_RENDER_MOTION_BLUR_SET,
			//			currentDevice->m_ptrPart->m_currentScore);
			//	}
			//	::glMultMatrixd(currentDevice->m_ptrPart->m_currentScore->m_modelView);
			//}
			//else
			{
				YoTxyz(currentDevice->m_ptrPart,
					currentDevice->m_ptrPart->m_translate,
					currentDevice->m_ptrPart->m_rotate);
			}

			if (currentDevice->m_type == YO_LIGHT
				&& ((CStageLight *)currentDevice)->m_enabled)
			{
				if (option == YO_RENDER_LIGHT
					&& ((CStageLight *)currentDevice)->m_target)
				{
					GLfloat li[4] = {0.0f, 0.0f, 0.0f, 1.0f};
					for (i = 0; i < 3; i++)
					{
						lightIntensity[i] = ((CStageLight *)currentDevice)->m_intensity;
						li[i] = lightIntensity[i] / 1.2f;
						lightPosition[i] = 0.0f;
					}

					lightIntensity[3] = 1.0f;
					::glLightfv(((CStageLight *)currentDevice)->m_target,
						GL_AMBIENT, lightIntensity);
					::glLightfv(((CStageLight *)currentDevice)->m_target,
						GL_DIFFUSE, lightIntensity);
					::glLightfv(((CStageLight *)currentDevice)->m_target,
						GL_SPECULAR, lightIntensity);

					if (((CStageLight *)currentDevice)->m_pointSource == TRUE)
					{
						lightPosition[2] = 1.0f;
						lightPosition[3] = 1.0f;
					}
					else
					{
						lightPosition[2] = 1.0f;
						lightPosition[3] = 0.0f;
					}
					::glLightfv(((CStageLight *)currentDevice)->m_target,
						GL_POSITION, lightPosition);
					if (((CStageLight *)currentDevice)->m_pointSource == TRUE)
					{
						::glLightf(((CStageLight *)currentDevice)->m_target,
							GL_CONSTANT_ATTENUATION, ((CStageLight *)currentDevice)->m_attenuation[0]);
						::glLightf(((CStageLight *)currentDevice)->m_target,
							GL_LINEAR_ATTENUATION, ((CStageLight *)currentDevice)->m_attenuation[1]);
						::glLightf(((CStageLight *)currentDevice)->m_target,
							GL_QUADRATIC_ATTENUATION, ((CStageLight *)currentDevice)->m_attenuation[2]);
						::glLightf(((CStageLight *)currentDevice)->m_target,
							GL_SPOT_CUTOFF, ((CStageLight *)currentDevice)->m_spotCutoff);
						//::glLightf(((CStageLight *)currentDevice)->m_target,
						//	GL_SPOT_EXPONENT, ((CStageLight *)currentDevice)->m_spotExponent);
					}
					else
					{
						::glLightf(((CStageLight *)currentDevice)->m_target,
							GL_CONSTANT_ATTENUATION, 1.0f);
						::glLightf(((CStageLight *)currentDevice)->m_target,
							GL_LINEAR_ATTENUATION, 0.0f);
						::glLightf(((CStageLight *)currentDevice)->m_target,
							GL_QUADRATIC_ATTENUATION, 0.0f);
						::glLightf(((CStageLight *)currentDevice)->m_target,
							GL_SPOT_CUTOFF, 180.0f);
						//::glLightf(((CStageLight *)currentDevice)->m_target,
						//	GL_SPOT_EXPONENT, ((CStageLight *)currentDevice)->m_spotExponent);
					}
					GLfloat spotDirection[3] = {0.0f, 0.0f, -1.0f};
					::glLightfv(((CStageLight *)currentDevice)->m_target,
						GL_SPOT_DIRECTION, spotDirection);

					::glEnable(((CStageLight *)currentDevice)->m_target);
				}
				else if (option == YO_RENDER_LIGHT_VIEWPOINT)
				{
					::glMatrixMode(GL_MODELVIEW);
					::glPushMatrix();
					::glLoadIdentity();
					YoTxyz(currentDevice->m_ptrPart, currentDevice->m_ptrPart->m_translate,
						currentDevice->m_ptrPart->m_rotate);
					::glGetDoublev(GL_MODELVIEW_MATRIX,
						((CStageLight *)currentDevice)->m_modelView);
					::glPopMatrix();
					pDoc->m_numberLightsOn++;
				}
			}
		}

		if (option == YO_RENDER_LIGHT
			&& currentDevice->m_type == YO_LIGHT
			&& (!((CStageLight *)currentDevice)->m_enabled))
			
		{
			::glDisable(((CStageLight *)currentDevice)->m_target);
		}
		//else if (currentDevice->m_type != YO_LIGHT
		else if ((option != YO_RENDER_LIGHT)
			//&& currentDevice->m_visible)
			|| option == YO_RENDER_SAVE_WORKCELL
			|| option == YO_RENDER_SAVE_DEVICE)
		{
			YoRenderPart(currentDevice, option);
		}

		//if ((option == YO_RENDER_LIGHT
		//	|| option == YO_RENDER_LIGHT_VIEWPOINT)
		//	&& pDoc->m_animationState == YO_PLAY
		//	&& currentDevice->m_ptrPart->m_score != NULL
		//	&& currentDevice->m_ptrPart->m_currentScore->m_time <= pDoc->m_timeCurrent
		//	&& pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR
		//	&& pDoc->m_timeMotionBlur > 0
		//	&& currentDevice->m_ptrPart->m_currentScore->m_next != NULL
		//	&& currentDevice->m_ptrPart->m_currentScore->m_next->m_time
		//	- currentDevice->m_ptrPart->m_currentScore->m_time == 1)
		//{
		//	YoMotionBlurModelView(YO_RENDER_MOTION_BLUR_RESTORE,   
		//		currentDevice->m_ptrPart->m_currentScore);
		//}
    
		glScaled(1.0 / currentDevice->m_scale[0],
			1.0 / currentDevice->m_scale[1],
			1.0 / currentDevice->m_scale[2]); 

		if (currentDevice->m_down != NULL)
		{
			if (currentDevice->m_right != NULL)
			{
				pDoc->YoPushDevice(currentDevice->m_right);
			}
			else
			{
				pDoc->YoPushDevice(NULL);
			}
			currentDevice = currentDevice->m_down;
		}
		else if (currentDevice->m_right != NULL)
		{
			currentDevice = currentDevice->m_right;
			glPopMatrix();
		}
		else if (!pDoc->YoAllStackDevicesNull())
		{
			glPopMatrix();
			glPopMatrix();
			while ((currentDevice = pDoc->YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
		}
		else
		{
			glPopMatrix();
			while (pDoc->m_deviceStack != NULL
				&& (currentDevice = pDoc->YoPopDevice()) == NULL)
			{
				glPopMatrix();
			}
			done = TRUE;
		}
	} // end while (!done)

	if (option == YO_RENDER_SAVE_WORKCELL)
	{
		//const CString& workcellName = pDoc->GetPathName( );
		//m_fp = fopen(workcellName, "a");
		//fprintf(m_fp, "NULL\n");
		//fprintf(m_fp, "#\n");
		//fclose(m_fp);
	}
	return TRUE;
}


BOOL CStageView::YoRenderPart(CStageDevice *currentDevice, int option)
{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	GLint done = FALSE;
	CStagePart*	currentPart = currentDevice->m_ptrPart;
	CStageDevice *ptrDevice;
	CStagePath *currentPath;
	GLdouble mBaseInv[16];
	GLdouble mMV[16];
	GLdouble currentScale = 1.0;
	pDoc->m_partStack = NULL;

	if (currentPart == NULL)
	{
		return TRUE;
	}

	if ((option == YO_RENDER_QUICK && pDoc->m_quickMode == YO_WIREFRAME)
		|| option == YO_RENDER_SAVE_WORKCELL
		|| option == YO_RENDER_SAVE_DEVICE
		|| option == YO_RENDER_PICK_PART
		|| option == YO_RENDER_PICK_PART_AND_TAG
		|| option == YO_RENDER_FLAT)
	{
		::glDisable(GL_LIGHTING);
	}
	else
	{
		::glEnable(GL_LIGHTING);
	}	

	if (option == YO_RENDER_SAVE_WORKCELL)
	{
		//const CString& workcellName = pDoc->GetPathName( );
		//m_fp = fopen(workcellName, "a");
	}

	while (!done)
	{
		if (option == YO_RENDER_SAVE_WORKCELL
			|| (option == YO_RENDER_SAVE_DEVICE
			&& currentDevice == pDoc->m_currentDevice))
		{
			fprintf(m_fp, "PART\n");
			//fprintf(m_fp, "PART_DEVICE_NAME %s\n", currentPart->m_deviceName);
			fprintf(m_fp, "PART_NAME %s\n", currentPart->m_partName);
			if (currentPart != currentDevice->m_ptrPart
				|| option == YO_RENDER_SAVE_WORKCELL)
			{
				fprintf(m_fp, "PART_PARENT %s\n", currentPart->m_partParent);
				fprintf(m_fp, "PART_TRANSLATE %lf %lf %lf\n",
					currentPart->m_translate[0],
					currentPart->m_translate[1],
					currentPart->m_translate[2]);
				fprintf(m_fp, "PART_ROTATE %lf %lf %lf\n",
					currentPart->m_rotate[0],
					currentPart->m_rotate[1],
					currentPart->m_rotate[2]);
				fprintf(m_fp, "PART_TXYZ %d\n", currentPart->m_txyz);
				fprintf(m_fp, "PART_SMOOTH_SHADE_ANGLE %f\n", currentPart->m_smoothShadeAngle);
			}
			//fprintf(m_fp, "PART_FILE %s\n", currentPart->m_partFile);
			if (option == YO_RENDER_SAVE_WORKCELL)
			{
				if (currentPart->m_motion != NULL)
				{
					currentPart->m_motion->YoWriteMotion(m_fp, currentPart);
				}
				for (currentPath = currentPart->m_path; currentPath != NULL; currentPath = currentPath->m_nextPath)
				{
					currentPath->YoWritePath(m_fp);
				}
				//YoWriteEffect(m_fp, currentPart);
			}
		}

    if (currentPart != currentDevice->m_ptrPart)
    {
		// base part already pushed for scaling in routine YoRender 
		glPushMatrix();
		//TRACE0("Part PUSH\n");
    }
	else
	{
		/***
		// m is used for devices attached to parts other
		// than the base part  i.e. for robot motion
		::glGetDoublev(GL_MODELVIEW_MATRIX, m_mBase);
		::glPushMatrix();
		::glLoadMatrixd(m_viewInv);
		::glMultMatrixd(m_mBase);
		::glGetDoublev(GL_MODELVIEW_MATRIX, m_mBase);
		::glPopMatrix();

		//::glMatrixMode(GL_MODELVIEW);
		//ptrDevice = pDoc->m_currentDevice;
		//ptrPart = pDoc->m_currentPart;
		//pDoc->m_currentDevice = currentDevice;
		//pDoc->m_currentPart = currentPart;
		//::glPushMatrix();
		//pDoc->YoModelMatrixOfCurrentPart(m);
		//::glPopMatrix();
		//pDoc->m_currentDevice = ptrDevice;
		//pDoc->m_currentPart = ptrPart;
		**/

	}

	if (currentDevice->m_attachedFromPart != NULL
		&& currentPart == currentDevice->m_ptrPart)
	{
		//AfxMessageBox("m_mAttach");
		::glMultMatrixd(currentDevice->m_mAttach);
	}

    //if (pDoc->m_animationState == YO_PLAY
	//	&& currentPart->m_score != NULL
	//	&& currentPart->m_currentScore->m_time <= pDoc->m_timeCurrent
	//	&& option != YO_RENDER_PICK_PART
	//	&& option != YO_RENDER_PICK_PART_AND_TAG)
	//{
	//	while(currentPart->m_currentScore->m_next != NULL
	//		&& currentPart->m_currentScore->m_time < pDoc->m_timeCurrent
	//		&& currentPart->m_currentScore->m_next->m_time <= pDoc->m_timeCurrent)
	//	{
	//		currentPart->m_currentScore = currentPart->m_currentScore->m_next;
	//	}
	//	if (pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR
	//		&& pDoc->m_timeMotionBlur > 0
	//		&& currentPart->m_currentScore->m_next != NULL
	//		&& currentPart->m_currentScore->m_next->m_time
	//		- currentPart->m_currentScore->m_time == 1)
	//	{
	//		YoMotionBlurModelView(YO_RENDER_MOTION_BLUR_SET,
	//			currentPart->m_currentScore);
	    
	//	}
	//	glMultMatrixd(currentPart->m_currentScore->m_modelView);
	//}
	//else
	{
		YoTxyz(currentPart, currentPart->m_translate, currentPart->m_rotate);
		if (currentPart == currentDevice->m_ptrPart)
		{
			::glGetDoublev(GL_MODELVIEW_MATRIX, m_mBase);
			::glPushMatrix();
			::glLoadMatrixd(m_viewInv);
			::glMultMatrixd(m_mBase);
			::glGetDoublev(GL_MODELVIEW_MATRIX, m_mBase);
			::glPopMatrix();
		}
		
		if (currentDevice->m_type == YO_ROBOT6)
		{
			((CStageRobot6 *)currentDevice)->YoRotateJoint(currentPart);
		}
		else if (currentDevice->m_type == YO_ROTARY_TABLE)
		{
			((CStageRotaryTable *)currentDevice)->YoRotateTable(currentPart);
		}
		else if (currentDevice->m_type == YO_BARRETT_HAND)
		{
			((CStageBarrettHand *)currentDevice)->YoPositionFinger(currentPart);
		}
		else if (currentDevice->m_type == YO_CONVEYOR && currentPart == currentDevice->m_ptrPart)
		{
			((CStageConveyor *)currentDevice)->YoSetStopGates();
		}
		else if (currentDevice->m_type == YO_GRIPPER)
		{
			((CStageGripper *)currentDevice)->YoPositionFinger(currentPart);

			//if (currentDevice->m_ptrPart != NULL 
			//	&& currentDevice->m_ptrPart->m_down != NULL
			//	&& currentPart != currentDevice->m_ptrPart)
			//{
			//	for (ptrPart = currentDevice->m_ptrPart->m_down;
			//		ptrPart != NULL && ptrPart != currentPart;
			//		ptrPart = ptrPart->m_right);
			//	if (ptrPart != NULL)
			//	{
			//	//	::glPushMatrix();
			//		if (((CStageGripper *)currentDevice)->m_typeTranslating == TRUE)
			//		{
			//			// translate fingers along x axis
			//			if (((CStageGripper *)currentDevice)->m_gripping == TRUE)
			//			{
			//				::glTranslated(-((CStageGripper *)currentDevice)->m_displacementClose, 0.0f, 0.0f);
			//			}
			//			else
			//			{
			//				::glTranslated(((CStageGripper *)currentDevice)->m_displacementOpen, 0.0f, 0.0f);
			//			}
			//		}
			//		else
			//		{
			//			// rotate fingers around y axis
			//			if (((CStageGripper *)currentDevice)->m_gripping == TRUE)
			//			{
			//				::glRotated(-((CStageGripper *)currentDevice)->m_displacementClose, 0.0, 1.0, 0.0);
			//			}
			//			else
			//			{
			//				::glRotated(((CStageGripper *)currentDevice)->m_displacementOpen, 0.0, 1.0, 0.0);
			//			}
			//		}
			//	//	::glPopMatrix();
			//	}
			//}
		}

		if (currentPart->m_attachedDevice != NULL)
		{
			//AfxMessageBox("m_attachedDevice != NULL");
			for (ptrDevice = currentPart->m_attachedDevice;
				ptrDevice != NULL; ptrDevice = ptrDevice->m_right)
			{
				if (ptrDevice->m_attachedFromPart != NULL
					&& ptrDevice->m_attachedFromPart == currentPart)
				{
					::glGetDoublev(GL_MODELVIEW_MATRIX, mMV);
					::glPushMatrix();
					::glLoadMatrixd(m_viewInv);
					::glMultMatrixd(mMV);
					::glGetDoublev(GL_MODELVIEW_MATRIX, mMV);

					pDoc->YoMatrixInverse(m_mBase, mBaseInv);
					::glLoadMatrixd(mBaseInv);
					::glMultMatrixd(mMV);
					::glGetDoublev(GL_MODELVIEW_MATRIX,
						ptrDevice->m_mAttach);
					::glPopMatrix();

					
					//pDoc->YoModelMatrixOfCurrentPart(mMV);
					//pDoc->YoMatrixInverse(m, mInv);
					//::glPushMatrix();
					//::glLoadMatrixd(mInv);
					//::glMultMatrixd(mMV);
					//::glGetDoublev(GL_MODELVIEW_MATRIX,
					//	currentPart->m_attachedDevice->m_mAttach);
					//::glPopMatrix();
				}
			}	
		}
    }

	if (currentDevice == pDoc->m_currentDevice
		&& currentPart == pDoc->m_currentPart
		&& currentDevice->m_visible
		&& pDoc->m_boundingBox
		&& option != YO_RENDER_PICK_PART
		&& option != YO_RENDER_PICK_PART_AND_TAG
		&& option != YO_RENDER_FLAT
		&& pDoc->m_undo->m_undoMode != YO_UNDO_PART_DELETE
		&& pDoc->m_undo->m_undoPartDelete != currentPart
		&& pDoc->YoIsChild(pDoc->m_undo->m_undoPartDelete, currentPart) == FALSE)
	{
		YoDrawBoundingBox(currentPart);
	}

	if (option == YO_RENDER_SAVE_WORKCELL
		|| (option == YO_RENDER_SAVE_DEVICE
		&& currentDevice == pDoc->m_currentDevice))
	{
		fprintf(m_fp, "RENDER_MODE %d\n", currentPart->m_renderMode);
		fprintf(m_fp, "MATERIAL_AMBIENT %lf %lf %lf %lf\n",
			currentPart->m_ambient[0], currentPart->m_ambient[1],
			currentPart->m_ambient[2], currentPart->m_ambient[3]);
		fprintf(m_fp, "MATERIAL_DIFFUSE %lf %lf %lf %lf\n",
			currentPart->m_diffuse[0], currentPart->m_diffuse[1],
			currentPart->m_diffuse[2], currentPart->m_diffuse[3]);
		fprintf(m_fp, "MATERIAL_SPECULAR %lf %lf %lf %lf\n",
			currentPart->m_specular[0], currentPart->m_specular[1],
			currentPart->m_specular[2], currentPart->m_specular[3]);
		fprintf(m_fp, "MATERIAL_EMISSION %lf %lf %lf %lf\n",
			currentPart->m_emission[0], currentPart->m_emission[1],
			currentPart->m_emission[2], currentPart->m_emission[3]);
		fprintf(m_fp, "MATERIAL_WIREFRAME %lf %lf %lf %lf\n",
			currentPart->m_wireframe[0], currentPart->m_wireframe[1],
			currentPart->m_wireframe[2], currentPart->m_wireframe[3]);
		fprintf(m_fp, "MATERIAL_SHININESS %lf\n", currentPart->m_shininess);

		if (currentDevice->m_type == YO_CONVEYOR)
		{
			((CStageConveyor *)currentDevice)->YoWriteConveyor(m_fp, currentPart);
		}

		if (currentDevice->m_type != YO_TRACK)
		{
			currentPart->YoWritePartFile(m_fp);
		}

		/***
		if (currentPart->m_texture != NULL)
		{
			fprintf(m_fp, "TEXTURE_SCALE %f\n", currentPart->m_textureScale);
			fprintf(m_fp, "TEXTURE_ALPHA %f\n", currentPart->m_textureAlpha);
			fprintf(m_fp, "TEXTURE_NAME %f\n", currentPart->m_textureName);
			fprintf(m_fp, "TEXTURE_WRAP %f\n", currentPart->m_textureWrap);
			fprintf(m_fp, "TEXTURE_TEV %f\n", currentPart->m_textureTEV);
			fprintf(m_fp, "TEXTURE_SPARAMETER %f %f %f %f %d\n",
				currentPart->m_sParameter[0],
				currentPart->m_sParameter[1],
				currentPart->m_sParameter[2],
				currentPart->m_sParameter[3],
				currentPart->m_sMode);
			fprintf(m_fp, "TEXTURE_TPARAMETER %f %f %f %f %d\n",
				currentPart->m_tParameter[0],
				currentPart->m_tParameter[1],
				currentPart->m_tParameter[2],
				currentPart->m_tParameter[3],
				currentPart->m_tMode);
		}
		***/
	}

	//if (pDoc->m_animationState == YO_PLAY
	//	&& currentPart->m_score != NULL
	//	&& currentPart->m_currentScore->m_time <= pDoc->m_timeCurrent)
	//{
	//	if (option == YO_RENDER_QUICK || option == YO_RENDER_FLAT)
	//	{
	//		glColor4fv(currentPart->m_currentScore->m_wireframe);
	//	}
	//	else
	//	{
	//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,
	//			currentPart->m_currentScore->m_ambient);
	//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
	//			currentPart->m_currentScore->m_diffuse);
	//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,
	//			currentPart->m_currentScore->m_specular);
	//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,
	//			currentPart->m_currentScore->m_emission);
	//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,
	//			currentPart->m_currentScore->m_shininess);
	//	}
    //}
	//else
	if (currentDevice->m_visible)
    {
		if ((option == YO_RENDER_QUICK && pDoc->m_quickMode == YO_WIREFRAME)
			|| option == YO_RENDER_FLAT)
		{
			glColor4fv(currentPart->m_wireframe);
		}
		else if (option == YO_RENDER_PICK_PART
			|| option == YO_RENDER_PICK_PART_AND_TAG)
		{
			GLfloat p[3];
			GLint r;
			GLint g;
			GLint b;
			GLint power;

			glGetIntegerv(GL_RED_BITS, &r);
			glGetIntegerv(GL_GREEN_BITS, &g);
			glGetIntegerv(GL_BLUE_BITS, &b);

			power = (GLint)(pow(2.0, (double)r) - 1.0);
			p[0] = (GLfloat)(power & currentPart->m_displayListID)
				/ (GLfloat)power; 
			power = (GLint)(pow(2.0, (double)g) - 1.0);
			p[1] = (GLfloat)(power & ((currentPart->m_displayListID)>>r))
				/ (GLfloat)power;
			power = (GLint)(pow(2.0, (double)b) - 1.0);
			p[2] = (GLfloat)(power & ((currentPart->m_displayListID)>>(r + g)))
				/ (GLfloat)power;

			//p[0] = (0xff & currentPart->m_displayListID) / 255.0f;
			//p[1] = (0xff & ((currentPart->m_displayListID)>>8)) / 255.0f;
			//p[2] = (0xff & ((currentPart->m_displayListID)>>16)) / 255.0f;
			
			::glColor3fv(p);
		}
		else
		{
			::glMaterialfv(GL_FRONT, GL_AMBIENT, currentPart->m_ambient);
			::glMaterialfv(GL_FRONT, GL_SPECULAR, currentPart->m_specular);
			::glMaterialfv(GL_FRONT, GL_DIFFUSE, currentPart->m_diffuse);
			::glMaterialfv(GL_FRONT, GL_EMISSION, currentPart->m_emission);
			::glMaterialf(GL_FRONT, GL_SHININESS, currentPart->m_shininess);

			//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, currentPart->m_ambient);
			//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, currentPart->m_specular);
			//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, currentPart->m_diffuse);
			//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, currentPart->m_emission);
			//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, currentPart->m_shininess);
		}
	}

	/***
	if (currentPart->m_texture != NULL
		&& pDoc->m_renderMode >= YO_TEXTURE
		&& option != YO_RENDER_PICK_PART
		&& option != YO_RENDER_PICK_PART_AND_TAG
		&& option != YO_RENDER_QUICK
		&& option != YO_RENDER_FLAT)
	{ 
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, currentPart->m_textureTEV);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
			currentPart->m_textureWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
			currentPart->m_textureWrap);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		//	currentPart->m_texture->m_pRGBImage->sizeX,
		//	currentPart->m_texture->m_pRGBImage->sizeY,
		//	GL_UNSIGNED_BYTE, currentPart->m_texture->m_pRGBImage->data); 
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, GL_RGBA,
			currentPart->m_texture->m_pRGBImage->sizeX,
			currentPart->m_texture->m_pRGBImage->sizeY,
			GL_UNSIGNED_BYTE, currentPart->m_texture->m_pRGBImage->data); 

		if (pDoc->m_animationState == YO_PLAY 
			&& currentPart->m_score != NULL
			&& currentPart->m_currentScore->m_time <= pDoc->m_timeCurrent)
		{
			if (currentPart->m_sMode == GL_SPHERE_MAP)
			{
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGenfv(GL_S, GL_OBJECT_PLANE,
					currentPart->m_currentScore->m_sParameter);
			}
			else   // (currentPart->m_sMode == GL_OBJECT_LINEAR)
			{
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
				glTexGenfv(GL_S, GL_OBJECT_PLANE,
					currentPart->m_currentScore->m_sParameter);
			}

			if (currentPart->m_tMode == GL_SPHERE_MAP)
			{
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGenfv(GL_T, GL_OBJECT_PLANE,
					currentPart->m_currentScore->m_tParameter);
			}
			else   // (currentPart->m_tMode == GL_OBJECT_LINEAR)
			{
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
				glTexGenfv(GL_T, GL_OBJECT_PLANE,
					currentPart->m_currentScore->m_tParameter);
			}
		}

		else
		{
			if (currentPart->m_sMode == GL_SPHERE_MAP)
			{
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGenfv(GL_S, GL_OBJECT_PLANE,
					currentPart->m_sParameter);
			}
			else   // (currentPart->m_sMode == GL_OBJECT_LINEAR)
			{
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
				glTexGenfv(GL_S, GL_OBJECT_PLANE,
					currentPart->m_sParameter);
			}

			if (currentPart->m_tMode == GL_SPHERE_MAP)
			{
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGenfv(GL_T, GL_OBJECT_PLANE,
					currentPart->m_tParameter);
			}
			else   // (currentPart->m_tMode == GL_OBJECT_LINEAR)
			{
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
				glTexGenfv(GL_T, GL_OBJECT_PLANE,
					currentPart->m_tParameter);
			}
		}

		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		m[0] = currentPart->m_textureScale;
		m[5] = currentPart->m_textureScale;
		m[10] = currentPart->m_textureScale;
		glMultMatrixf(m);
		glMatrixMode(GL_MODELVIEW);
	}
	****/

	/****
	if (option == YO_RENDER_QUICK)
	{
		//::glCallList(currentPart->m_wireframeDisplayListID);
	}
	else
	{
		::glCallList(currentPart->m_displayListID);
	}
	***/

	// update model matrix of part
	::glGetDoublev(GL_MODELVIEW_MATRIX, currentPart->m_modelMatrix);
	::glPushMatrix();
	::glLoadMatrixd(m_viewInv);
	::glMultMatrixd(currentPart->m_modelMatrix);
	::glGetDoublev(GL_MODELVIEW_MATRIX, currentPart->m_modelMatrix);
	::glPopMatrix();

	if (currentPart == pDoc->m_currentPart
		&& option == YO_RENDER_PICK_PART)
	{
		::glGetDoublev(GL_MODELVIEW_MATRIX, pDoc->m_modelViewOfCurrentPart);
	}


	if (pDoc->m_undo->m_undoMode == YO_UNDO_PART_DELETE
		&& (pDoc->m_undo->m_undoPartDelete == currentPart
		|| pDoc->YoIsChild(pDoc->m_undo->m_undoPartDelete, currentPart)))
	{
		// don't render the part or any paths attached to the part
	}
	else if (currentDevice->m_visible)
	{
		if (currentDevice->m_type != YO_TRACK)
		{
			YoRenderPartPolygons(currentPart, option);
		}
		else
		{
			YoRenderTrackSeg(currentPart, option);
		}

		if (currentPart->m_path != NULL
			&& option != YO_RENDER_PICK_PART)
		{
			YoRenderTags(currentPart, option);
		}

		if (currentPart->m_originVisible == TRUE
			&& option != YO_RENDER_PICK_PART)
		{
			YoRenderOrigin(currentPart, option);
		}

		if (option == YO_RENDER_FULL
			&& currentDevice->m_type == YO_BAR_CODE_READER
			&& ((CStageBarCodeReader *)currentDevice)->m_scanning
			&& currentPart->m_left == NULL
			&& currentPart->m_down == NULL)
		{
			((CStageBarCodeReader *)currentDevice)->YoRenderScan();
		}
	}

    if (option == YO_RENDER_SAVE_WORKCELL
		|| (option == YO_RENDER_SAVE_DEVICE
		&& currentDevice == pDoc->m_currentDevice))
	{
		if (currentDevice->m_type == YO_TRACK
			&& currentPart->m_ptrTrackSeg != NULL)
		{
			if (currentPart->m_ptrTrackSeg->m_type == YO_TRACK_LINE)
			{
				fprintf(m_fp, "TRACK LINE %.3lf %.3lf %.3lf %.3lf\n",
					currentPart->m_ptrTrackSeg->m_from[0], currentPart->m_ptrTrackSeg->m_from[1],
					currentPart->m_ptrTrackSeg->m_to[0], currentPart->m_ptrTrackSeg->m_to[1]);
			}
			else if (currentPart->m_ptrTrackSeg->m_type == YO_TRACK_CIRCLE)
			{
				fprintf(m_fp, "TRACK CIRCLE %.3lf %.3lf %.3lf %.3lf %.3lf\n",
					currentPart->m_ptrTrackSeg->m_from[0], currentPart->m_ptrTrackSeg->m_from[1],
					currentPart->m_ptrTrackSeg->m_heading,
					currentPart->m_ptrTrackSeg->m_radius,
					currentPart->m_ptrTrackSeg->m_angle);
			}
			else if (currentPart->m_ptrTrackSeg->m_type == YO_TRACK_SWITCH)
			{
				fprintf(m_fp, "TRACK SWITCH %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %d\n",
					currentPart->m_ptrTrackSeg->m_from[0], currentPart->m_ptrTrackSeg->m_from[1],
					currentPart->m_ptrTrackSeg->m_to[0], currentPart->m_ptrTrackSeg->m_to[1],
					currentPart->m_ptrTrackSeg->m_switch[0], currentPart->m_ptrTrackSeg->m_switch[1],
					currentPart->m_ptrTrackSeg->m_switchStatus);
			}
			else if (currentPart->m_ptrTrackSeg->m_type == YO_TRACK_CROSS)
			{
				fprintf(m_fp, "TRACK CROSS %.3lf %.3lf %.3lf %.3lf\n",
					currentPart->m_ptrTrackSeg->m_from[0], currentPart->m_ptrTrackSeg->m_from[1],
					currentPart->m_ptrTrackSeg->m_to[0], currentPart->m_ptrTrackSeg->m_to[1]);
			}
		}

		fprintf(m_fp, "PART_NULL\n");
		fprintf(m_fp, "#\n");
	}

    //if (pDoc->m_animationState == YO_PLAY
	//	&& currentPart->m_score != NULL
	//	&& currentPart->m_currentScore->m_time <= pDoc->m_timeCurrent
	//	&& pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR
	//	&& pDoc->m_timeMotionBlur > 0
	//	&& currentPart->m_currentScore->m_next != NULL
	//	&& currentPart->m_currentScore->m_next->m_time
	//	- currentPart->m_currentScore->m_time == 1)
	//{
	//	YoMotionBlurModelView(YO_RENDER_MOTION_BLUR_RESTORE,
	//		currentPart->m_currentScore);
	//}

    //glScalef(1.0 / cur_scale, 1.0 / cur_scale, 1.0 / cur_scale);

    if (currentPart->m_down != NULL)
	{
		if (currentPart->m_right != NULL)
		{
			pDoc->YoPushPart(currentPart->m_right);
		}
		else
		{
			pDoc->YoPushPart(NULL);
		}
		currentPart = currentPart->m_down;
	}
    else if (currentPart->m_right != NULL)
	{
		currentPart = currentPart->m_right;
		glPopMatrix();
		//TRACE0("Part POP\n");
	}
	else if (!pDoc->YoAllStackPartsNull())
	{
		glPopMatrix();
		//TRACE0("Part POP\n");
		glPopMatrix();
		//TRACE0("Part POP\n");
		while ((currentPart = pDoc->YoPopPart()) == NULL)
		{
			glPopMatrix();
			//TRACE0("Part POP\n");
		}
	}
	else
	{
		while (pDoc->m_partStack != NULL
			&& (currentPart = pDoc->YoPopPart()) == NULL)
		{
			glPopMatrix();
			//TRACE0("Part POP\n");
		}
		done = TRUE;
	}

	}    // end while (!done)

	if (option == YO_RENDER_SAVE_WORKCELL)
	{
		//fclose(m_fp);
	}

	return TRUE;
}


BOOL CStageView::YoRenderPartPolygons(CStagePart *currentPart, int option)
// given a part, each of the individual polygons are rendered according to
// the option specified.
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	int			i;
	int			j;
	int			index;
	CStagePolygonList *ptrPolygonList;
	CStageVertices *ptrVertices;
	CStageNormals *ptrNormals;
	CStageTexture *ptrTexture = NULL;
	CStageTextureCoords *ptrTextureCoords = NULL;
	CStageVertexList *ptrVertexList;
	GLfloat p[3];
	GLint r;
	GLint g;
	GLint bl;
	GLint power;
	GLint displayListID;


	if (option == YO_RENDER_POLYGON)
	{
		p[0] = 0.0;
		p[1] = 0.0;
		p[2] = 0.0;
		displayListID = 0;

		::glGetIntegerv(GL_RED_BITS, &r);
		::glGetIntegerv(GL_GREEN_BITS, &g);
		::glGetIntegerv(GL_BLUE_BITS, &bl);

		::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		::glClearDepth(1.0f);
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		::glColor3fv(p);
	}

	ptrPolygonList = currentPart->m_polygonList;
	for (j = 0; j < currentPart->m_numberPolygons; j++)
	{
		ptrVertices = ptrPolygonList->m_vertices[j % 10];
		ptrNormals = ptrPolygonList->m_normals[j % 10];
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
			for (ptrVertexList = currentPart->m_vertexList; index >= 20; ptrVertexList = ptrVertexList->m_next)
			{
				index -= 20;
			}

			if (i == 0)
			{
				if (ptrTexture != NULL
					&& currentPart->m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
					&& option != YO_RENDER_PICK_PART
					&& option != YO_RENDER_PICK_PART_AND_TAG
					&& option != YO_RENDER_POLYGON
					&& ((option == YO_RENDER_FULL
					&& pDoc->m_renderMode >= YO_TEXTURE)
					|| (option == YO_RENDER_QUICK
					&& pDoc->m_quickMode >= YO_TEXTURE)))
				{
					//if (ptrTexture->m_RGBImage == NULL)
					//{
					//	ptrTexture->YoInitFromDIB();
					//}
					if (ptrTexture->m_RGBImage != NULL)
					{
						ptrTexture->YoSelectImage();
					}					
				}

				if (currentPart->m_renderMode == YO_RENDER_MODE_WIREFRAME
					|| currentPart->m_renderMode == YO_RENDER_MODE_POLYGON_LINE
					|| currentPart->m_renderMode == YO_RENDER_MODE_TEXTURE_POLYGON_LINE
					|| (option == YO_RENDER_FULL
					&& pDoc->m_renderMode == YO_WIREFRAME)
					|| (option == YO_RENDER_QUICK
					&& pDoc->m_quickMode == YO_WIREFRAME))
				{
					::glBegin(GL_LINE_LOOP);
				}
				else if (currentPart->m_renderMode == YO_RENDER_MODE_POLYGON_POINT
					|| currentPart->m_renderMode == YO_RENDER_MODE_TEXTURE_POLYGON_POINT)
				{
					::glBegin(GL_POINTS);
				}
				else
				{
					::glBegin(GL_POLYGON);
				}				
				
				// first three points define normal
				//a[0] = ptrVertexList->m_vertex[index][0];
				//a[1] = ptrVertexList->m_vertex[index][1];
				//a[2] = ptrVertexList->m_vertex[index][2];
				//u[0] = a[0];
				//u[1] = a[1];
				//u[2] = a[2];
			}
			//else if (i == 1)
			//{
				//b[0] = ptrVertexList->m_vertex[index][0];
				//b[1] = ptrVertexList->m_vertex[index][1];
				//b[2] = ptrVertexList->m_vertex[index][2];
				//u[0] -= b[0];
				//u[1] -= b[1];
				//u[2] -= b[2];
				//v[0] = b[0];
				//v[1] = b[1];
				//v[2] = b[2];
			//}
			//else if (i == 2)
			//{
				//c[0] = ptrVertexList->m_vertex[index][0];
				//c[1] = ptrVertexList->m_vertex[index][1];
				//c[2] = ptrVertexList->m_vertex[index][2];
				//v[0] = c[0] - v[0];
				//v[1] = c[1] - v[1];
				//v[2] = c[2] - v[2];
				//pDoc->YoCrossProduct(normal, v, u);
				//pDoc->YoNormalize(normal);

				//if (currentPart->m_renderMode == YO_RENDER_MODE_WIREFRAME
				//	|| currentPart->m_renderMode == YO_RENDER_MODE_POLYGON_LINE
				//	|| currentPart->m_renderMode == YO_RENDER_MODE_TEXTURE_POLYGON_LINE
				//	|| (option == YO_RENDER_FULL
				//	&& pDoc->m_renderMode == YO_WIREFRAME)
				//	|| (option == YO_RENDER_QUICK
				//	&& pDoc->m_quickMode == YO_WIREFRAME))
				//{
				//	::glBegin(GL_LINE_LOOP);
				//}
				//else if (currentPart->m_renderMode == YO_RENDER_MODE_POLYGON_POINT
				//	|| currentPart->m_renderMode == YO_RENDER_MODE_TEXTURE_POLYGON_POINT)
				//{
				//	::glBegin(GL_POINTS);
				//}
				//else
				//{
				//	::glBegin(GL_POLYGON);
				//}

				//if ((option != YO_RENDER_PICK_PART
				//	&& option != YO_RENDER_PICK_PART_AND_TAG
				//	&& option != YO_RENDER_POLYGON)
				//	//&& (option == YO_RENDER_FULL
				//	//&& pDoc->m_renderMode != YO_WIREFRAME)
				//	|| option == YO_RENDER_QUICK
				//	&& pDoc->m_quickMode != YO_WIREFRAME)
				//{
				//	::glNormal3dv(normal);
				//}

				//if (ptrTextureCoords != NULL
				//	&& option != YO_RENDER_PICK_PART
				//	&& option != YO_RENDER_PICK_PART_AND_TAG
				//	&& option != YO_RENDER_POLYGON
				//	&& currentPart->m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
				//	&& ((option == YO_RENDER_FULL
				//	&& pDoc->m_renderMode >= YO_TEXTURE)
				//	|| (option == YO_RENDER_QUICK
				//	&& pDoc->m_quickMode >= YO_TEXTURE)))
				//{
				//	::glTexCoord2d(ptrTextureCoords->m_textureCoords[0][0],
				//		ptrTextureCoords->m_textureCoords[0][1]);
				//}
				//glVertex3dv(a);
				//if (ptrTextureCoords != NULL
				//	&& option != YO_RENDER_PICK_PART
				//	&& option != YO_RENDER_PICK_PART_AND_TAG
				//	&& option != YO_RENDER_POLYGON
				//	&& currentPart->m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
				//	&& ((option == YO_RENDER_FULL
				//	&& pDoc->m_renderMode >= YO_TEXTURE)
				//	|| (option == YO_RENDER_QUICK
				//	&& pDoc->m_quickMode >= YO_TEXTURE)))
				//{
				//	::glTexCoord2d(ptrTextureCoords->m_textureCoords[1][0],
				//		ptrTextureCoords->m_textureCoords[1][1]);
				//}
				//::glVertex3dv(b);
				//if (ptrTextureCoords != NULL
				//	&& option != YO_RENDER_PICK_PART
				//	&& option != YO_RENDER_PICK_PART_AND_TAG
				//	&& option != YO_RENDER_POLYGON
				//	&& currentPart->m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
				//	&& ((option == YO_RENDER_FULL
				//	&& pDoc->m_renderMode >= YO_TEXTURE)
				//	|| (option == YO_RENDER_QUICK
				//	&& pDoc->m_quickMode >= YO_TEXTURE)))
				//{
				//	::glTexCoord2d(ptrTextureCoords->m_textureCoords[2][0],
				//		ptrTextureCoords->m_textureCoords[2][1]);
				//}
				//::glVertex3dv(c);
			//}
			//else
			//{
				if ((option != YO_RENDER_PICK_PART
					&& option != YO_RENDER_PICK_PART_AND_TAG
					&& option != YO_RENDER_POLYGON)
					//&& (option == YO_RENDER_FULL
					//&& pDoc->m_renderMode != YO_WIREFRAME)
					|| option == YO_RENDER_QUICK
					&& pDoc->m_quickMode != YO_WIREFRAME)
				{
					if (pDoc->m_smoothShading == TRUE)
					{
						::glNormal3dv(ptrNormals->m_normal[i % 4]);
					}
					else if (i == 0)
					{
						::glNormal3dv(ptrPolygonList->m_normalFlatShaded[j % 10]);
					}
				}

				if (ptrTextureCoords != NULL
					&& option != YO_RENDER_PICK_PART
					&& option != YO_RENDER_PICK_PART_AND_TAG
					&& option != YO_RENDER_POLYGON
					&& currentPart->m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
					&& ((option == YO_RENDER_FULL
					&& pDoc->m_renderMode >= YO_TEXTURE)
					|| (option == YO_RENDER_QUICK
					&& pDoc->m_quickMode >= YO_TEXTURE)))
				{
					::glTexCoord2d(ptrTextureCoords->m_textureCoords[i % 4][0],
						ptrTextureCoords->m_textureCoords[i % 4][1]);
				}
				
				::glVertex3dv(ptrVertexList->m_vertex[index]);
			//}

			if (i % 4 == 3)
			{
				ptrVertices = ptrVertices->m_next;
				ptrNormals = ptrNormals->m_next;
				if (ptrTextureCoords != NULL
					&& option != YO_RENDER_PICK_PART
					&& option != YO_RENDER_PICK_PART_AND_TAG
					&& option != YO_RENDER_POLYGON
					&& currentPart->m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
					&& ((option == YO_RENDER_FULL
					&& pDoc->m_renderMode >= YO_TEXTURE)
					|| (option == YO_RENDER_QUICK
					&& pDoc->m_quickMode >= YO_TEXTURE)))
				{
					ptrTextureCoords = ptrTextureCoords->m_next;
				}
			}
		}
		::glEnd();

		if (ptrTexture != NULL
			&& option != YO_RENDER_PICK_PART
			&& option != YO_RENDER_PICK_PART_AND_TAG
			&& option != YO_RENDER_POLYGON
			&& currentPart->m_renderMode >= YO_RENDER_MODE_TEXTURE_POLYGON_FILLED
			&& ((option == YO_RENDER_FULL
			&& pDoc->m_renderMode >= YO_TEXTURE)
			|| (option == YO_RENDER_QUICK
			&& pDoc->m_quickMode >= YO_TEXTURE)))
		{
			::glDisable(GL_TEXTURE_2D);
		}

/***
		/// find analysis pick point in world coordinates
		if (pMainFrame->m_analysisActive == TRUE)
		{
			if (pMainFrame->m_analysis->m_select == 1
				&& pMainFrame->m_analysis->m_ptrPolygonVertices == ptrPolygonList->m_vertices[j % 10])
			{
				//d = sqrt((m_eye[3] - m_eye[0]) * (m_eye[3] - m_eye[0])
				//	+ (m_eye[4] - m_eye[1]) * (m_eye[4] - m_eye[1])
				//	+ (m_eye[5] - m_eye[2]) * (m_eye[5] - m_eye[2]))
				//	* m_fieldOfView * .001;
				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				::glTranslated(pMainFrame->m_analysis->m_analysisPoint[0][0],
					pMainFrame->m_analysis->m_analysisPoint[0][1],
					pMainFrame->m_analysis->m_analysisPoint[0][2]);
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][0] = m[12];
				pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1] = m[13];
				pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2] = m[14];
				::glPopMatrix();
			}
			if (pMainFrame->m_analysis->m_select == 2
				&& pMainFrame->m_analysis->m_ptrPolygonVertices == ptrPolygonList->m_vertices[j % 10])
			{
				::glMatrixMode(GL_MODELVIEW);
				::glPushMatrix();
				::glTranslated(pMainFrame->m_analysis->m_analysisPoint[1][0],
					pMainFrame->m_analysis->m_analysisPoint[1][1],
					pMainFrame->m_analysis->m_analysisPoint[1][2]);
				::glGetDoublev(GL_MODELVIEW_MATRIX, m);
				pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0] = m[12];
				pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1] = m[13];
				pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][2] = m[14];
				::glPopMatrix();
			}
		}
	***/

		if (j % 10 == 9)
		{
			ptrPolygonList = ptrPolygonList->m_next;
		}

		if (option == YO_RENDER_POLYGON)
		{
			displayListID++;
			power = (GLint)(pow(2.0, (double)r) - 1.0);
			p[0] = (GLfloat)(power & displayListID)
				/ (GLfloat)power; 
			power = (GLint)(pow(2.0, (double)g) - 1.0);
			p[1] = (GLfloat)(power & ((displayListID)>>r))
				/ (GLfloat)power;
			power = (GLint)(pow(2.0, (double)bl) - 1.0);
			p[2] = (GLfloat)(power & ((displayListID)>>(r + g)))
				/ (GLfloat)power;
			::glColor3fv(p);
		}

	}
	return TRUE;
}


void CStageView::YoRenderTrackSeg(CStagePart *ptrPart, int option)
{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	GLdouble vStart[3];
	GLdouble vEnd[3];
	GLdouble alpha;
	GLdouble theta;
	GLdouble x;
	GLdouble y;
	int i;
	int j;

	if (ptrPart->m_ptrTrackSeg == NULL)
	{
		return;
	}

	if (option == YO_RENDER_PICK_PART
		|| option == YO_RENDER_PICK_PART_AND_TAG)
	{
		GLfloat p[3];
		GLint r;
		GLint g;
		GLint b;
		GLint power;

		::glGetIntegerv(GL_RED_BITS, &r);
		::glGetIntegerv(GL_GREEN_BITS, &g);
		::glGetIntegerv(GL_BLUE_BITS, &b);

		power = (GLint)(pow(2.0, (double)r) - 1.0);
		p[0] = (GLfloat)(power & ptrPart->m_displayListID)
			/ (GLfloat)power; 
		power = (GLint)(pow(2.0, (double)g) - 1.0);
		p[1] = (GLfloat)(power & ((ptrPart->m_displayListID)>>r))
			/ (GLfloat)power;
		power = (GLint)(pow(2.0, (double)b) - 1.0);
		p[2] = (GLfloat)(power & ((ptrPart->m_displayListID)>>(r + g)))
			/ (GLfloat)power;
		
		::glColor3fv(p);
	}
	else
	{
		::glColor3f(ptrPart->m_wireframe[0], ptrPart->m_wireframe[1],
			ptrPart->m_wireframe[2]);
	}


	::glDisable(GL_LIGHTING);
	::glLineWidth(5.0f);

	vStart[2] = 0.0f;						// set z to 0
	vEnd[2] = 0.0f;

	vStart[0] = ptrPart->m_ptrTrackSeg->m_from[0];
	vStart[1] = ptrPart->m_ptrTrackSeg->m_from[1];

	if (ptrPart->m_ptrTrackSeg->m_type != YO_TRACK_CIRCLE)
	{
		vEnd[0] = ptrPart->m_ptrTrackSeg->m_to[0];
		vEnd[1] = ptrPart->m_ptrTrackSeg->m_to[1];
		glBegin(GL_LINES);
			glVertex3dv(vStart);
			glVertex3dv(vEnd);
		glEnd();

		if (ptrPart->m_ptrTrackSeg->m_type == YO_TRACK_SWITCH)
		{
			vEnd[0] = ptrPart->m_ptrTrackSeg->m_switch[0];
			vEnd[1] = ptrPart->m_ptrTrackSeg->m_switch[1];
			glBegin(GL_LINES);
				glVertex3dv(vStart);
				glVertex3dv(vEnd);
			glEnd();
		}
	}

	else
	{
		if (ptrPart->m_ptrTrackSeg->m_angle >= 0.0)
		{
		  	theta = YO_DEGREES_TO_RADIANS * (ptrPart->m_ptrTrackSeg->m_heading - 90.0);
		}
		else
		{
		  	theta = YO_DEGREES_TO_RADIANS * (ptrPart->m_ptrTrackSeg->m_heading + 90.0);
		}

		x = ptrPart->m_ptrTrackSeg->m_radius * cos(theta);
		y = ptrPart->m_ptrTrackSeg->m_radius * sin(theta);
		x = ptrPart->m_ptrTrackSeg->m_from[0] - x;
		y = ptrPart->m_ptrTrackSeg->m_from[1] - y;
		j = ((int)fabs(ptrPart->m_ptrTrackSeg->m_angle) + 5) / 5;

		for (i = 0; i < j; i++)
		{
			if (i > 0)
			{
				vStart[0] = vEnd[0];
				vStart[1] = vEnd[1];
			}
			if (i == j - 1)
			{
				vEnd[0] = ptrPart->m_ptrTrackSeg->m_to[0];
				vEnd[1] = ptrPart->m_ptrTrackSeg->m_to[1];
			}
			else
			{
				alpha = theta + YO_DEGREES_TO_RADIANS
					* ptrPart->m_ptrTrackSeg->m_angle * (((GLdouble)i + 1.0f) / (GLdouble)j);
				vEnd[0] = ptrPart->m_ptrTrackSeg->m_radius * cos(alpha);
				vEnd[1] = ptrPart->m_ptrTrackSeg->m_radius * sin(alpha);
				vEnd[0] += x;
				vEnd[1] += y;
			}
			glBegin(GL_LINES);
				glVertex3dv(vStart);
				glVertex3dv(vEnd);
			glEnd();

		}
	}

	::glLineWidth(1.0f);
	if (option == YO_RENDER_FULL)
	{
		::glEnable(GL_LIGHTING);
	}

	return;
}

BOOL CStageView::YoRenderPartCoords(CStagePart *ptrPart, int option)
{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	CStagePath *ptrPath;
	CStageTag *ptrTag;
	GLdouble d;
	GLdouble vStart[3] = {0.0f, 0.0f, 0.0f};
	GLdouble vEnd[3];
	GLfloat p[3];
	GLint r;
	GLint g;
	GLint b;
	GLint power;
	
	//::glDisable(GL_DEPTH_TEST);

	if (option == YO_RENDER_PICK_PART_AND_TAG)
	{
		::glDepthRange(0.0, 0.0);
		::glLineWidth(5.0f);
	}
	else
	{
		::glLineWidth(1.0f);
	}

	::glDisable(GL_LIGHTING);

	d = sqrt((m_eye[3] - m_eye[0]) * (m_eye[3] - m_eye[0])
		+ (m_eye[4] - m_eye[1]) * (m_eye[4] - m_eye[1])
		+ (m_eye[5] - m_eye[2]) * (m_eye[5] - m_eye[2]))
		* m_fieldOfView * .0008;

	for (ptrPath = ptrPart->m_path; ptrPath != NULL; ptrPath = ptrPath->m_nextPath)
	{
		if (option != YO_RENDER_PICK_PART_AND_TAG)
		{
			::glColor4fv(ptrPath->m_color);
		}

		for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL; ptrTag = ptrTag->m_nextTag)
		{
			if (option == YO_RENDER_PICK_PART_AND_TAG)
			{
				glGetIntegerv(GL_RED_BITS, &r);
				glGetIntegerv(GL_GREEN_BITS, &g);
				glGetIntegerv(GL_BLUE_BITS, &b);

				power = (GLint)(pow(2.0, (double)r) - 1.0);
				p[0] = (GLfloat)(power & ptrTag->m_displayListID)
					/ (GLfloat)power; 
				power = (GLint)(pow(2.0, (double)g) - 1.0);
				p[1] = (GLfloat)(power & ((ptrTag->m_displayListID)>>r))
					/ (GLfloat)power;
				power = (GLint)(pow(2.0, (double)b) - 1.0);
				p[2] = (GLfloat)(power & ((ptrTag->m_displayListID)>>(r + g)))
					/ (GLfloat)power;
				
				glColor3fv(p);
			}
			else if (ptrTag == pDoc->m_currentTag)
			{
				::glLineWidth(2.0f);
			}

			if ((pDoc->m_currentTag->m_ptrPath == ptrTag->m_ptrPath
				&& pDoc->m_undo->m_undoMode == YO_UNDO_PATH_DELETE
				&& ptrTag->m_ptrPath->m_visible == TRUE)
				|| (pDoc->m_undo->m_undoMode == YO_UNDO_TAG_DELETE
				&& pDoc->m_undo->m_undoTagDelete == ptrTag)
				|| ptrTag->m_ptrPath->m_visible == FALSE)
			{
				// don't render tag
			}
			else
			{
				::glPushMatrix();
				::glTranslated(ptrTag->m_translate[0],
					ptrTag->m_translate[1], ptrTag->m_translate[2]);
				::glRotated(ptrTag->m_rotate[0], 1.0, 0.0, 0.0);
				::glRotated(ptrTag->m_rotate[1], 0.0, 1.0, 0.0);
				::glRotated(ptrTag->m_rotate[2], 0.0, 0.0, 1.0);

				vEnd[0] = d;
				vEnd[1] = 0.0f;
				vEnd[2] = 0.0f;
				::glBegin(GL_LINES);
					::glVertex3dv(vStart);
					::glVertex3dv(vEnd);
				::glEnd();

				vEnd[0] = 0.0f;
				vEnd[1] = d;
				::glBegin(GL_LINES);
					::glVertex3dv(vStart);
					::glVertex3dv(vEnd);
				::glEnd();

				vEnd[1] = 0.0f;
				vEnd[2] = d * 1.5;
				::glBegin(GL_LINES);
					::glVertex3dv(vStart);
					::glVertex3dv(vEnd);
				::glEnd();

				if (option != YO_RENDER_PICK_PART_AND_TAG)
				{
					::glDepthRange(0.0, 0.0);
					::glLineStipple(1, 0x3333);
					::glEnable(GL_LINE_STIPPLE);

					vEnd[0] = d;
					vEnd[1] = 0.0f;
					vEnd[2] = 0.0f;
					::glBegin(GL_LINES);
						::glVertex3dv(vStart);
						::glVertex3dv(vEnd);
					::glEnd();

					vEnd[0] = 0.0f;
					vEnd[1] = d;
					::glBegin(GL_LINES);
						::glVertex3dv(vStart);
						::glVertex3dv(vEnd);
					::glEnd();

					vEnd[1] = 0.0f;
					vEnd[2] = d * 1.5;
					::glBegin(GL_LINES);
						::glVertex3dv(vStart);
						::glVertex3dv(vEnd);
					::glEnd();

					::glDepthRange(0.0, 1.0);
					::glLineStipple(3, 0xffff);
					::glDisable(GL_LINE_STIPPLE);
				}

				::glPopMatrix();
			}

			if (option != YO_RENDER_PICK_PART_AND_TAG
				&& ptrTag == pDoc->m_currentTag)
			{
				::glLineWidth(1.0f);
			}
		}
	}

	::glLineWidth(1.0f);

	if ((option == YO_RENDER_QUICK && pDoc->m_quickMode == YO_WIREFRAME)
		|| option == YO_RENDER_SAVE_WORKCELL
		|| option == YO_RENDER_SAVE_DEVICE
		|| option == YO_RENDER_PICK_PART
		|| option == YO_RENDER_PICK_PART_AND_TAG
		|| option == YO_RENDER_FLAT)
	{
		//::glDisable(GL_LIGHTING);
	}
	else
	{
		::glEnable(GL_LIGHTING);
	}

	::glDepthRange(0.0, 1.0);
	//::glEnable(GL_DEPTH_TEST);

	return TRUE;
}

BOOL CStageView::YoRenderTags(CStagePart *ptrPart, int option)
{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	CStagePath *ptrPath;
	CStageTag *ptrTag;
	GLdouble d;
	GLdouble vStart[3] = {0.0f, 0.0f, 0.0f};
	GLdouble vEnd[3];
	GLfloat p[3];
	GLint r;
	GLint g;
	GLint b;
	GLint power;
	
	//::glDisable(GL_DEPTH_TEST);

	if (option == YO_RENDER_PICK_PART_AND_TAG)
	{
		::glDepthRange(0.0, 0.0);
		::glLineWidth(5.0f);
	}
	else
	{
		::glLineWidth(1.0f);
	}

	::glDisable(GL_LIGHTING);

	d = sqrt((m_eye[3] - m_eye[0]) * (m_eye[3] - m_eye[0])
		+ (m_eye[4] - m_eye[1]) * (m_eye[4] - m_eye[1])
		+ (m_eye[5] - m_eye[2]) * (m_eye[5] - m_eye[2]))
		* m_fieldOfView * .0008;

	for (ptrPath = ptrPart->m_path; ptrPath != NULL; ptrPath = ptrPath->m_nextPath)
	{
		if (option != YO_RENDER_PICK_PART_AND_TAG)
		{
			::glColor4fv(ptrPath->m_color);
		}

		for (ptrTag = ptrPath->m_ptrTag; ptrTag != NULL; ptrTag = ptrTag->m_nextTag)
		{
			if (option == YO_RENDER_PICK_PART_AND_TAG)
			{
				glGetIntegerv(GL_RED_BITS, &r);
				glGetIntegerv(GL_GREEN_BITS, &g);
				glGetIntegerv(GL_BLUE_BITS, &b);

				power = (GLint)(pow(2.0, (double)r) - 1.0);
				p[0] = (GLfloat)(power & ptrTag->m_displayListID)
					/ (GLfloat)power; 
				power = (GLint)(pow(2.0, (double)g) - 1.0);
				p[1] = (GLfloat)(power & ((ptrTag->m_displayListID)>>r))
					/ (GLfloat)power;
				power = (GLint)(pow(2.0, (double)b) - 1.0);
				p[2] = (GLfloat)(power & ((ptrTag->m_displayListID)>>(r + g)))
					/ (GLfloat)power;
				
				glColor3fv(p);
			}
			else if (ptrTag == pDoc->m_currentTag)
			{
				::glLineWidth(2.0f);
			}

			if ((pDoc->m_currentTag->m_ptrPath == ptrTag->m_ptrPath
				&& pDoc->m_undo->m_undoMode == YO_UNDO_PATH_DELETE
				&& ptrTag->m_ptrPath->m_visible == TRUE)
				|| (pDoc->m_undo->m_undoMode == YO_UNDO_TAG_DELETE
				&& pDoc->m_undo->m_undoTagDelete == ptrTag)
				|| ptrTag->m_ptrPath->m_visible == FALSE)
			{
				// don't render tag
			}
			else
			{
				::glPushMatrix();
				::glTranslated(ptrTag->m_translate[0],
					ptrTag->m_translate[1], ptrTag->m_translate[2]);
				::glRotated(ptrTag->m_rotate[0], 1.0, 0.0, 0.0);
				::glRotated(ptrTag->m_rotate[1], 0.0, 1.0, 0.0);
				::glRotated(ptrTag->m_rotate[2], 0.0, 0.0, 1.0);

				vEnd[0] = d;
				vEnd[1] = 0.0f;
				vEnd[2] = 0.0f;
				::glBegin(GL_LINES);
					::glVertex3dv(vStart);
					::glVertex3dv(vEnd);
				::glEnd();

				vEnd[0] = 0.0f;
				vEnd[1] = d;
				::glBegin(GL_LINES);
					::glVertex3dv(vStart);
					::glVertex3dv(vEnd);
				::glEnd();

				vEnd[1] = 0.0f;
				vEnd[2] = d * 1.5;
				::glBegin(GL_LINES);
					::glVertex3dv(vStart);
					::glVertex3dv(vEnd);
				::glEnd();

				if (option != YO_RENDER_PICK_PART_AND_TAG)
				{
					::glDepthRange(0.0, 0.0);
					::glLineStipple(1, 0x3333);
					::glEnable(GL_LINE_STIPPLE);

					vEnd[0] = d;
					vEnd[1] = 0.0f;
					vEnd[2] = 0.0f;
					::glBegin(GL_LINES);
						::glVertex3dv(vStart);
						::glVertex3dv(vEnd);
					::glEnd();

					vEnd[0] = 0.0f;
					vEnd[1] = d;
					::glBegin(GL_LINES);
						::glVertex3dv(vStart);
						::glVertex3dv(vEnd);
					::glEnd();

					vEnd[1] = 0.0f;
					vEnd[2] = d * 1.5;
					::glBegin(GL_LINES);
						::glVertex3dv(vStart);
						::glVertex3dv(vEnd);
					::glEnd();

					::glDepthRange(0.0, 1.0);
					::glLineStipple(3, 0xffff);
					::glDisable(GL_LINE_STIPPLE);
				}

				::glPopMatrix();
			}

			if (option != YO_RENDER_PICK_PART_AND_TAG
				&& ptrTag == pDoc->m_currentTag)
			{
				::glLineWidth(1.0f);
			}
		}
	}

	::glLineWidth(1.0f);

	if ((option == YO_RENDER_QUICK && pDoc->m_quickMode == YO_WIREFRAME)
		|| option == YO_RENDER_SAVE_WORKCELL
		|| option == YO_RENDER_SAVE_DEVICE
		|| option == YO_RENDER_PICK_PART
		|| option == YO_RENDER_PICK_PART_AND_TAG
		|| option == YO_RENDER_FLAT)
	{
		//::glDisable(GL_LIGHTING);
	}
	else
	{
		::glEnable(GL_LIGHTING);
	}

	::glDepthRange(0.0, 1.0);
	//::glEnable(GL_DEPTH_TEST);

	return TRUE;
}


BOOL CStageView::YoRenderOrigin(CStagePart *ptrPart, int option)
// render cordinate system of the part's origin or alternate origin 
{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	GLdouble d;
	GLdouble vStart[3] = {0.0f, 0.0f, 0.0f};
	GLdouble vEnd[3];
	GLfloat p[3];
	GLint r;
	GLint g;
	GLint b;
	GLint power;
	
	if (ptrPart->m_originVisible == FALSE)
	{
		return TRUE;
	}

	if (option == YO_RENDER_PICK_PART_AND_TAG)
	{
		::glDepthRange(0.0, 0.0);
		::glLineWidth(5.0f);
	}
	else
	{
		::glLineWidth(1.0f);
	}

	::glDisable(GL_LIGHTING);

	d = sqrt((m_eye[3] - m_eye[0]) * (m_eye[3] - m_eye[0])
		+ (m_eye[4] - m_eye[1]) * (m_eye[4] - m_eye[1])
		+ (m_eye[5] - m_eye[2]) * (m_eye[5] - m_eye[2]))
		* m_fieldOfView * .0008;

	if (option != YO_RENDER_PICK_PART_AND_TAG)
	{
		::glColor4fv(ptrPart->m_wireframe);
	}

	if (option == YO_RENDER_PICK_PART_AND_TAG)
	{
		glGetIntegerv(GL_RED_BITS, &r);
		glGetIntegerv(GL_GREEN_BITS, &g);
		glGetIntegerv(GL_BLUE_BITS, &b);

		// display list ID of alternate origin is 1 greater than display ID of part
		power = (GLint)(pow(2.0, (double)r) - 1.0);
		p[0] = (GLfloat)(power & (ptrPart->m_displayListID + 1))
			/ (GLfloat)power; 
		power = (GLint)(pow(2.0, (double)g) - 1.0);
		p[1] = (GLfloat)(power & ((ptrPart->m_displayListID + 1)>>r))
			/ (GLfloat)power;
		power = (GLint)(pow(2.0, (double)b) - 1.0);
		p[2] = (GLfloat)(power & ((ptrPart->m_displayListID + 1)>>(r + g)))
			/ (GLfloat)power;
		
		glColor3fv(p);
	}
	else if (ptrPart == pDoc->m_currentPart)
	{
		::glLineWidth(2.0f);
	}

	::glPushMatrix();
	if (ptrPart->m_altOriginDisplayed == TRUE)
	{
		::glMultMatrixd(ptrPart->m_altOrigin);
	}

	vEnd[0] = d;
	vEnd[1] = 0.0f;
	vEnd[2] = 0.0f;
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vEnd[0] = 0.0f;
	vEnd[1] = d;
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vEnd[1] = 0.0f;
	vEnd[2] = d * 1.5;
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	if (option != YO_RENDER_PICK_PART_AND_TAG)
	{
		::glDepthRange(0.0, 0.0);
		::glLineStipple(1, 0x3333);
		::glEnable(GL_LINE_STIPPLE);

		vEnd[0] = d;
		vEnd[1] = 0.0f;
		vEnd[2] = 0.0f;
		::glBegin(GL_LINES);
			::glVertex3dv(vStart);
			::glVertex3dv(vEnd);
		::glEnd();

		vEnd[0] = 0.0f;
		vEnd[1] = d;
		::glBegin(GL_LINES);
			::glVertex3dv(vStart);
			::glVertex3dv(vEnd);
		::glEnd();

		vEnd[1] = 0.0f;
		vEnd[2] = d * 1.5;
		::glBegin(GL_LINES);
			::glVertex3dv(vStart);
			::glVertex3dv(vEnd);
		::glEnd();

		::glDepthRange(0.0, 1.0);
		::glLineStipple(3, 0xffff);
		::glDisable(GL_LINE_STIPPLE);
	}

	::glPopMatrix();
	::glLineWidth(1.0f);

	if ((option == YO_RENDER_QUICK && pDoc->m_quickMode == YO_WIREFRAME)
		|| option == YO_RENDER_SAVE_WORKCELL
		|| option == YO_RENDER_SAVE_DEVICE
		|| option == YO_RENDER_PICK_PART
		|| option == YO_RENDER_PICK_PART_AND_TAG
		|| option == YO_RENDER_FLAT)
	{
		//::glDisable(GL_LIGHTING);
	}
	else
	{
		::glEnable(GL_LIGHTING);
	}

	::glDepthRange(0.0, 1.0);
	return TRUE;
}

BOOL CStageView::YoRenderAnalysis()
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return FALSE;
	}
	GLdouble d;
	GLdouble vStart[3];
	GLdouble vEnd[3];

	if (pMainFrame->m_analysisActive == TRUE)
	{
		::glDisable(GL_DEPTH_TEST);
		::glLineWidth(2.0f);

		d = sqrt((m_eye[3] - m_eye[0]) * (m_eye[3] - m_eye[0])
			+ (m_eye[4] - m_eye[1]) * (m_eye[4] - m_eye[1])
			+ (m_eye[5] - m_eye[2]) * (m_eye[5] - m_eye[2]))
			* m_fieldOfView * .0006;
		if (pMainFrame->m_analysis->m_selected == 1
			|| pMainFrame->m_analysis->m_selected == 2)
		{
			::glDisable(GL_LIGHTING);
			::glColor3f(1.0f, 0.1f, 1.0f);

			vStart[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][0] - d;
			vStart[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1];
			vStart[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2];
			vEnd[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][0] + d;
			vEnd[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1];
			vEnd[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2];
			::glBegin(GL_LINES);
				::glVertex3dv(vStart);
				::glVertex3dv(vEnd);
			::glEnd();

			vStart[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][0];
			vStart[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1] - d;
			vEnd[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][0];
			vEnd[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1] + d;
			::glBegin(GL_LINES);
				::glVertex3dv(vStart);
				::glVertex3dv(vEnd);
			::glEnd();

			vStart[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1];
			vStart[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2] - d;
			vEnd[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1];
			vEnd[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2] + d;
			::glBegin(GL_LINES);
				::glVertex3dv(vStart);
				::glVertex3dv(vEnd);
			::glEnd();
	
		}
		if (pMainFrame->m_analysis->m_selected == 2)
		{
			vStart[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0] - d;
			vStart[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1];
			vStart[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][2];
			vEnd[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0] + d;
			vEnd[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1];
			vEnd[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][2];
			::glBegin(GL_LINES);
				::glVertex3dv(vStart);
				::glVertex3dv(vEnd);
			::glEnd();

			vStart[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0];
			vStart[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1] - d;
			vEnd[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0];
			vEnd[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1] + d;
			::glBegin(GL_LINES);
				::glVertex3dv(vStart);
				::glVertex3dv(vEnd);
			::glEnd();

			vStart[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1];
			vStart[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][2] - d;
			vEnd[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1];
			vEnd[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][2] + d;
			::glBegin(GL_LINES);
				::glVertex3dv(vStart);
				::glVertex3dv(vEnd);
			::glEnd();

			// draw line connecting points
			::glColor3f(1.0f, 1.0f, 0.0f);
			vStart[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][0];
			vStart[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1];
			vStart[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2];
			vEnd[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0];
			vEnd[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1];
			vEnd[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][2];
			::glBegin(GL_LINES);
				::glVertex3dv(vStart);
				::glVertex3dv(vEnd);
			::glEnd();

			// draw x, y, z components of distance
			::glColor3f(0.6f, 0.6f, 0.5f);
			::glLineStipple(3, 0x7777);
			::glEnable(GL_LINE_STIPPLE);
			vStart[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][0];
			vStart[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1];
			vStart[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2];
			vEnd[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0];
			vEnd[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1];
			vEnd[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2];
			::glBegin(GL_LINES);
				::glVertex3dv(vStart);
				::glVertex3dv(vEnd);
			::glEnd();
			vStart[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0];
			vStart[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][1];
			vStart[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2];
			vEnd[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0];
			vEnd[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1];
			vEnd[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2];
			::glBegin(GL_LINES);
				::glVertex3dv(vStart);
				::glVertex3dv(vEnd);
			::glEnd();  
			vStart[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0];
			vStart[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1];
			vStart[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[0][2];
			vEnd[0] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][0];
			vEnd[1] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][1];
			vEnd[2] = pMainFrame->m_analysis->m_analysisPointInWorldCoords[1][2];
			::glBegin(GL_LINES);
				::glVertex3dv(vStart);
				::glVertex3dv(vEnd);
			::glEnd(); 
			::glLineStipple(1, 0xffff);
			::glDisable(GL_LINE_STIPPLE);
		}

		::glLineWidth(1.0f);
		::glEnable(GL_DEPTH_TEST);

	}
	return TRUE;
}

BOOL CStageView::YoRenderGrid()

// draw a 2 dimensional wireframe grid in the current scene

{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	int i;
	GLfloat a;
	GLfloat vStart[3];
	GLfloat vEnd[3];

	::glDisable(GL_LIGHTING);
	glColor3f(pDoc->m_grid[4] / 255.0f, pDoc->m_grid[5] / 255.0f,
		pDoc->m_grid[6] / 255.0f);
	//TRACE3("grid color: (%d, %d, %d)\n", pDoc->m_grid[4],
	//	pDoc->m_grid[5], pDoc->m_grid[6]);
	/***
	GLboolean *params;
	::glGetBooleanv(GL_RGBA_MODE, params);
	TRACE1("GL_RGBA_MODE = %d\n", *params);
	***/

	vStart[2] = 0.0f;                        // set z to 0
	vEnd[2] = 0.0f;

	vStart[0] = -pDoc->m_grid[2] / 2.0f;     // draw x axis grid 
	vEnd[0] = pDoc->m_grid[2] / 2.0f;

	i = 0;
	for (a = -pDoc->m_grid[3] / 2.0f; a <= (pDoc->m_grid[3] + 0.1f) / 2.0f;
		a += pDoc->m_grid[1])
	{
		vStart[1] = vEnd[1] = a;

		glBegin(GL_LINES);
			glVertex3fv(vStart);
			glVertex3fv(vEnd);
		glEnd();
		i++;
	}

	vStart[1] = -pDoc->m_grid[3] / 2.0f;       // draw y axis grid
	vEnd[1] = pDoc->m_grid[3] / 2.0f;

	for (a = -pDoc->m_grid[2] / 2.0f; a <= (pDoc->m_grid[2] + 0.1f) / 2.0f;
		a += pDoc->m_grid[1])
	{
		vStart[0] = vEnd[0] = a;

		glBegin(GL_LINES);
			glVertex3fv(vStart);
			glVertex3fv(vEnd);
		glEnd();
	}

	return TRUE;
}


BOOL CStageView::YoCreateShadowMaps()

// creates shadow maps for all light sources 

{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	//GLfloat       near;
	//GLfloat       rear;
	//GLfloat       fov;
	CStageLight		*ptrLight = pDoc->m_lightList;
	GLdouble		m[16];
	GLdouble		fov;

	// set light sources as cameras
	YoRenderDevice(YO_RENDER_LIGHT_VIEWPOINT);

	if (pDoc->m_numberLightsOn == 0)
	{
		return TRUE;
	}

	/* OGLXXX
	 * getsize not supported -- See Window Manager
	 * getsize(&x_winsize, &y_winsize)                   TO DO
	 */
	/*DELETED*/;
	//fov = abs(10 * (int)fl_get_slider_value(obj_zoom));
	//sscanf(fl_get_input(obj_clipfront), "%f", &front);
	//sscanf(fl_get_input(obj_cliprear), "%f", &rear);
	/* OGLXXX SRC_ZBUFFER: use GL_DEPTH_COMPONENT in glReadPixels call */
	//glReadBuffer(XXX);

	while (ptrLight != NULL)
	{
		if (ptrLight->m_enabled)
		{
			// compute camera center position
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadMatrixd(ptrLight->m_modelView);
			glTranslated(0.0, 0.0, -100.0);
			glGetDoublev(GL_MODELVIEW_MATRIX, m);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if (ptrLight->m_pointSource == TRUE)
			{
				fov = YO_MIN(120.0, 2.0 * ptrLight->m_spotCutoff);
			}
			else
			{
				fov = YO_MIN(120.0, m_fieldOfView);
			}
			gluPerspective(fov, m_aspectRatio,
				m_clipFront, m_clipRear);
			//gluLookAt(lptr->mview[3][0], lptr->mview[3][1], lptr->mview[3][2],
			//	m[3][0], m[3][1], m[3][2], yo_upat[0], yo_upat[1], yo_upat[2]);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(ptrLight->m_modelView[12], ptrLight->m_modelView[13], ptrLight->m_modelView[14],
				m[12], m[13], m[14],
				m_eye[6], m_eye[7], m_eye[8]);

			// change ptrLight->m_modelView so that it contains
			// the camera position matrix
			glGetDoublev(GL_MODELVIEW_MATRIX, ptrLight->m_modelView);
			//glPopMatrix();

			::glMatrixMode(GL_MODELVIEW);

			::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			::glClearDepth(1.0f);
			::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			YoRenderDevice(YO_RENDER_FLAT);
			//::SwapBuffers(m_pDC->GetSafeHdc());
			//Sleep(500);
			glPopMatrix();

			ptrLight->m_shadowMap = new GLfloat[m_viewportSize[0] * m_viewportSize[1]];
			//::glReadPixels(0, 0, m_windowSize[0] - 1, m_windowSize[1] - 1,
			//	GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid *)ptrLight->m_shadowMap);
			//::glReadPixels((m_windowSize[0] - m_viewportSize[0]) / 2,
			//	(m_windowSize[1] - m_viewportSize[1]) / 2,
			::glReadPixels(0, 0,
				m_viewportSize[0],
				m_viewportSize[1],
				GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid *)ptrLight->m_shadowMap);


			// restore camera field of view
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(m_fieldOfView, m_aspectRatio,
				m_clipFront, m_clipRear);
			glMatrixMode(GL_MODELVIEW);
/****			
			yo_Message("db:  depth buffer values for lptr->shadow_map:\n");
			offset = 0;
			for (i = 0; i < y_winsize; i++)
			{
				for (j = 0; j < x_winsize; j++)
				{
					if (i%60 == 30 && j%80 == 40)
					{
						yo_Message("db:  --(%d,%d): %ld  (%x) %x\n",
						j, i, *(lptr->shadow_map + offset), *(lptr->shadow_map + offset),
						*(lptr->shadow_map + offset) & 0x00000001);
					}
					offset++;
				}
			}
****/
		}
		ptrLight = ptrLight->m_ptrLight;
	}
	return TRUE;
}



BOOL CStageView::YoHandleShadows(GLdouble fov, GLdouble front,
	GLdouble rear, GLdouble eye[9], GLint *shadowBuffer)
	
// pixels in shadows are darkened

{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	GLint			i;
	GLint			j;
	//GLdouble		x1;
	//GLdouble		y1;
	//GLdouble		z1;
	GLdouble		*worldCoord;
	GLdouble		*lightScreen;
	//GLint			xScreen;
	//GLint			yScreen;
	//GLfloat			*zScreen;
	CStageLight		*ptrLight = pDoc->m_lightList;
	GLfloat			*zbuf;
	//GLdouble        zmax = 1.0;
	//GLdouble        zmin = 0.0;
	//GLdouble        zspan = 1.0;
	//GLdouble        sf;
	//GLdouble        szbuf;
	GLint			offset;
	//GLint			shadow_offset;
	GLdouble		modelView[16];
	GLdouble		proj[16];
	GLint			viewport[4];
	//GLdouble		objx[1];
	//GLdouble		objy[1];
	//GLdouble		objz[1];
	MSG msg;

	//shadow_offset = fl_get_slider_value(obj_form1_shadow_offset);

	worldCoord = new GLdouble[m_viewportSize[0] * m_viewportSize[1] * 3];
	zbuf = new GLfloat[m_viewportSize[0] * m_viewportSize[1]];
	lightScreen = new GLdouble[m_viewportSize[0] * m_viewportSize[1] * 3];
  
	//::glReadPixels(0, 0, m_windowSize[0] - 1, m_windowSize[1] - 1,
	//	GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid *)zbuf);
	//::glReadPixels((m_windowSize[0] - m_viewportSize[0]) / 2,
	//	(m_windowSize[1] - m_viewportSize[1]) / 2,
	::glReadPixels(0, 0,
		m_viewportSize[0],
		m_viewportSize[1],
		GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid *)zbuf);
	
    ::glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	::glGetDoublev(GL_PROJECTION_MATRIX, proj);
	::glGetIntegerv(GL_VIEWPORT, viewport);


	for (j = 0; j < m_viewportSize[1]; j++)
	{
		for (i = 0; i < m_viewportSize[0]; i++)
		{
			::gluUnProject((GLdouble)i,
				(GLdouble)j,
				(GLdouble)(*(zbuf + (j * m_viewportSize[0] + i))),
				modelView,
				proj,
				viewport,
				(worldCoord + (((j * m_viewportSize[0]) + i) * 3)),
				(worldCoord + (((j * m_viewportSize[0]) + i) * 3 + 1)),
				(worldCoord + (((j * m_viewportSize[0]) + i) * 3 + 2)));
			if (i == 0 && j == 0)
			{
				m_rasterPos[0] = (GLfloat)(*(worldCoord + (((j * m_viewportSize[0]) + i) * 3)));
				m_rasterPos[1] = (GLfloat)(*(worldCoord + (((j * m_viewportSize[0]) + i) * 3 + 1)));
				m_rasterPos[2] = (GLfloat)(*(worldCoord + (((j * m_viewportSize[0]) + i) * 3 + 2)));
			}
		}

		if (::PeekMessage(&msg, NULL, WM_LBUTTONUP, WM_LBUTTONUP, PM_NOREMOVE))
		{
			delete zbuf;
			delete worldCoord;
			delete lightScreen;
			for (ptrLight = pDoc->m_lightList; ptrLight != NULL; ptrLight = ptrLight->m_ptrLight)
			{
				delete(ptrLight->m_shadowMap);
				ptrLight->m_shadowMap = NULL;
			}
			return FALSE;
		}

	}

	// convert world coordinates to screen coordinates by first multiplying 
	// world coordinates by the each light's modelview matrix, then turning the
	// transformed x,y,z into screen coordinates.
	while (ptrLight != NULL)
	{
		if (ptrLight->m_enabled)
		{
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
			::glLoadMatrixd(ptrLight->m_modelView);
			::glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
			::glPopMatrix();

			offset = 0;
			for (i = 0; i < m_viewportSize[1]; i++)
			{
				for (j = 0; j < m_viewportSize[0]; j++)
				{
					gluProject(*(worldCoord + offset),
						*(worldCoord + offset + 1),
						*(worldCoord + offset + 2),
						modelView,
						proj,
						viewport,
						lightScreen + offset,
						lightScreen + offset + 1,
						lightScreen + offset + 2);
						//&x1,
						//&y1,
						//&z1);
					offset += 3;
				}
				if (::PeekMessage(&msg, NULL, WM_LBUTTONUP, WM_LBUTTONUP, PM_NOREMOVE))
				{
					delete zbuf;
					delete worldCoord;
					delete lightScreen;
					for (ptrLight = pDoc->m_lightList; ptrLight != NULL; ptrLight = ptrLight->m_ptrLight)
					{
						delete(ptrLight->m_shadowMap);
						ptrLight->m_shadowMap = NULL;
					}
					return FALSE;
				}
			}

					/***
					// xLight, yLight, zLight map into the range -1.0 to 1.0
					wLight = (*(worldCoord + offset) * ptrLight->m_modelView[3])
						+ (*(worldCoord + offset + 1) * ptrLight->m_modelView[7])
						+ (*(worldCoord + offset + 2) * ptrLight->m_modelView[11])
						+ ptrLight->m_modelView[15];
					xLight = ((*(worldCoord + offset) * ptrLight->m_modelView[0])
						+ (*(worldCoord + offset + 1) * ptrLight->m_modelView[4])
						+ (*(worldCoord + offset + 2) * ptrLight->m_modelView[8])
						+ ptrLight->m_modelView[12]) / wLight;
					yLight = ((*(worldCoord + offset) * ptrLight->m_modelView[1])
						+ (*(worldCoord + offset + 1) * ptrLight->m_modelView[5])
						+ (*(worldCoord + offset + 2) * ptrLight->m_modelView[9])
						+ ptrLight->m_modelView[13]) / wLight;
					zLight = ((*(worldCoord + offset) * ptrLight->m_modelView[2])
						+ (*(worldCoord + offset + 1) * ptrLight->m_modelView[6])
						+ (*(worldCoord + offset + 2) * ptrLight->m_modelView[10])
						+ ptrLight->m_modelView[14]) / wLight;
					
					xScreen = (GLint)(((xLight + 1.0) / 2.0 * m_windowSize[0]) + 0.5); // 0.5 is for rounding
					yScreen = (GLint)(((yLight + 1.0) / 2.0 * m_windowSize[1]) + 0.5);
					zScreen = (GLfloat)(zLight + 1.0) / 2.0;
					***/

			offset = 0;
			for (i = 0; i < m_viewportSize[1]; i++)
			{
				for (j = 0; j < m_viewportSize[0]; j++)
				{
					//xScreen = (GLint)(x1 + 0.5);
					//yScreen = (GLint)(y1 + 0.5);
					//zScreen = (GLfloat)z1;
/***
					if ((xScreen >= 0 && xScreen < m_viewportSize[0] 
						&& yScreen >= 0 && yScreen < m_viewportSize[1])
						&& (ptrLight->m_shadowMap[yScreen * m_viewportSize[0] + xScreen]
						+ (GLfloat)pDoc->m_shadowSensitivity * .00001 
						< zScreen))
					{
						(*(shadowBuffer + (i * m_viewportSize[0]) + j)) /= 2;
					}
***/
					if (i > 0 && i < m_viewportSize[1] - 1
						&& j > 0 && j < m_viewportSize[0] - 1

						&& *(lightScreen + offset) >= 0.0
						&& *(lightScreen + offset) < (GLdouble)m_viewportSize[0]
						&& *(lightScreen + offset + 1) >= 0.0
						&& *(lightScreen + offset + 1) < (GLdouble)m_viewportSize[1]
						&& (ptrLight->m_shadowMap[(GLint)(*(lightScreen + offset + 1))
							* m_viewportSize[0] + (GLint)(*(lightScreen + offset))]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001
							< (GLfloat)(*(lightScreen + offset + 2)))

						&& *(lightScreen + offset - 3) >= 0.0
						&& *(lightScreen + offset - 3) < (GLdouble)m_viewportSize[0]
						&& *(lightScreen + offset - 3 + 1) >= 0.0
						&& *(lightScreen + offset - 3 + 1) < (GLdouble)m_viewportSize[1]
						&& (ptrLight->m_shadowMap[(GLint)(*(lightScreen + offset - 3 + 1))
							* m_viewportSize[0] + (GLint)(*(lightScreen + offset - 3))]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001
							< (GLfloat)(*(lightScreen + offset - 3 + 2)))

						&& *(lightScreen + offset + 3) >= 0.0
						&& *(lightScreen + offset + 3) < (GLdouble)m_viewportSize[0]
						&& *(lightScreen + offset + 3 + 1) >= 0.0
						&& *(lightScreen + offset + 3 + 1) < (GLdouble)m_viewportSize[1]
						&& (ptrLight->m_shadowMap[(GLint)(*(lightScreen + offset + 3 + 1))
							* m_viewportSize[0] + (GLint)(*(lightScreen + offset + 3))]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001
							< (GLfloat)(*(lightScreen + offset + 3 + 2)))

						&& *(lightScreen + offset - (m_viewportSize[0] * 3)) >= 0.0
						&& *(lightScreen + offset - (m_viewportSize[0] * 3)) < (GLdouble)m_viewportSize[0]
						&& *(lightScreen + offset - (m_viewportSize[0] * 3) + 1) >= 0.0
						&& *(lightScreen + offset - (m_viewportSize[0] * 3) + 1) < (GLdouble)m_viewportSize[1]
						&& (ptrLight->m_shadowMap[(GLint)(*(lightScreen + offset - (m_viewportSize[0] * 3) + 1))
							* m_viewportSize[0] + (GLint)(*(lightScreen + offset - (m_viewportSize[0] * 3)))]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001
							< (GLfloat)(*(lightScreen + offset - (m_viewportSize[0] * 3) + 2)))

						&& *(lightScreen + offset - (m_viewportSize[0] * 3) - 3) >= 0.0
						&& *(lightScreen + offset - (m_viewportSize[0] * 3) - 3) < (GLdouble)m_viewportSize[0]
						&& *(lightScreen + offset - (m_viewportSize[0] * 3) - 3 + 1) >= 0.0
						&& *(lightScreen + offset - (m_viewportSize[0] * 3) - 3 + 1) < (GLdouble)m_viewportSize[1]
						&& (ptrLight->m_shadowMap[(GLint)(*(lightScreen + offset - (m_viewportSize[0] * 3) - 3 + 1))
							* m_viewportSize[0] + (GLint)(*(lightScreen + offset - (m_viewportSize[0] * 3) - 3))]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001
							< (GLfloat)(*(lightScreen + offset - (m_viewportSize[0] * 3) - 3 + 2)))

						&& *(lightScreen + offset - (m_viewportSize[0] * 3) + 3) >= 0.0
						&& *(lightScreen + offset - (m_viewportSize[0] * 3) + 3) < (GLdouble)m_viewportSize[0]
						&& *(lightScreen + offset - (m_viewportSize[0] * 3) + 3 + 1) >= 0.0
						&& *(lightScreen + offset - (m_viewportSize[0] * 3) + 3 + 1) < (GLdouble)m_viewportSize[1]
						&& (ptrLight->m_shadowMap[(GLint)(*(lightScreen + offset - (m_viewportSize[0] * 3) + 3 + 1))
							* m_viewportSize[0] + (GLint)(*(lightScreen + offset - (m_viewportSize[0] * 3) + 3))]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001
							< (GLfloat)(*(lightScreen + offset - (m_viewportSize[0] * 3) + 3 + 2)))

						&& *(lightScreen + offset + (m_viewportSize[0] * 3)) >= 0.0
						&& *(lightScreen + offset + (m_viewportSize[0] * 3)) < (GLdouble)m_viewportSize[0]
						&& *(lightScreen + offset + (m_viewportSize[0] * 3) + 1) >= 0.0
						&& *(lightScreen + offset + (m_viewportSize[0] * 3) + 1) < (GLdouble)m_viewportSize[1]
						&& (ptrLight->m_shadowMap[(GLint)(*(lightScreen + offset + (m_viewportSize[0] * 3) + 1))
							* m_viewportSize[0] + (GLint)(*(lightScreen + offset + (m_viewportSize[0] * 3)))]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001
							< (GLfloat)(*(lightScreen + offset + (m_viewportSize[0] * 3) + 2)))

						&& *(lightScreen + offset + (m_viewportSize[0] * 3) - 3) >= 0.0
						&& *(lightScreen + offset + (m_viewportSize[0] * 3) - 3) < (GLdouble)m_viewportSize[0]
						&& *(lightScreen + offset + (m_viewportSize[0] * 3) - 3 + 1) >= 0.0
						&& *(lightScreen + offset + (m_viewportSize[0] * 3) - 3 + 1) < (GLdouble)m_viewportSize[1]
						&& (ptrLight->m_shadowMap[(GLint)(*(lightScreen + offset + (m_viewportSize[0] * 3) - 3 + 1))
							* m_viewportSize[0] + (GLint)(*(lightScreen + offset + (m_viewportSize[0] * 3) - 3))]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001
							< (GLfloat)(*(lightScreen + offset + (m_viewportSize[0] * 3) - 3 + 2)))

						&& *(lightScreen + offset + (m_viewportSize[0] * 3) + 3) >= 0.0
						&& *(lightScreen + offset + (m_viewportSize[0] * 3) + 3) < (GLdouble)m_viewportSize[0]
						&& *(lightScreen + offset + (m_viewportSize[0] * 3) + 3 + 1) >= 0.0
						&& *(lightScreen + offset + (m_viewportSize[0] * 3) + 3 + 1) < (GLdouble)m_viewportSize[1]
						&& (ptrLight->m_shadowMap[(GLint)(*(lightScreen + offset + (m_viewportSize[0] * 3) + 3 + 1))
							* m_viewportSize[0] + (GLint)(*(lightScreen + offset + (m_viewportSize[0] * 3) + 3))]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001
							< (GLfloat)(*(lightScreen + offset + (m_viewportSize[0] * 3) + 3 + 2))))
					{
						(*(shadowBuffer + (i * m_viewportSize[0]) + j)) /= 2;
					}

					/*****
					if (i == 0 && j == 0
						|| j == 119 && i == 119
						|| j == 120 && i == 119
						|| j == 121 && i == 119
						|| j == 119 && i == 120
						|| j == 120 && i == 120
						|| j == 121 && i == 120
						|| j == 119 && i == 121
						|| j == 120 && i == 121
						|| j == 121 && i == 121)
						//|| j == m_viewportSize[0] - 2 && i == m_viewportSize[1] - 2)
					{
						//TRACE2("ji(%d, %d)  ", j, i);
						TRACE3("ij(%d, %d)  zsmap = %f < ", j, i, ptrLight->m_shadowMap[yScreen * m_viewportSize[0] + xScreen]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001);
						TRACE3("zScreen = %f   xyScreen = (%d, %d)", zScreen, xScreen, yScreen);
						TRACE3("  worldCoords(%.2lf, %.2lf, %.2lf)\n",
							*(worldCoord + offset), *(worldCoord + offset + 1),
							*(worldCoord + offset + 2));
					}

					if (i%60 == 30 && j%80 == 40 && xScreen >= 0 && xScreen < m_viewportSize[0]
						&& yScreen >= 0 && yScreen < m_viewportSize[1]) 
					{
						//TRACE3("ij(%d, %d)  zsmap = %f < ", j, i, ptrLight->m_shadowMap[yScreen * m_windowSize[0] + xScreen] + (pDoc->m_timeCurrent * .00001));
						TRACE3("ij(%d, %d)  zsmap = %f < ", j, i, ptrLight->m_shadowMap[yScreen * m_viewportSize[0] + xScreen]
							+ (GLfloat)pDoc->m_shadowSensitivity * .00001);
						TRACE3("zScreen = %f   xyScreen = (%d, %d)", zScreen, xScreen, yScreen);
						TRACE3("  worldCoords(%.2lf, %.2lf, %.2lf)\n",
							*(worldCoord + offset), *(worldCoord + offset + 1),
							*(worldCoord + offset + 2));
					}
					****/

					offset += 3;
				}
				if (::PeekMessage(&msg, NULL, WM_LBUTTONUP, WM_LBUTTONUP, PM_NOREMOVE))
				{
					delete zbuf;
					delete worldCoord;
					delete lightScreen;
					for (ptrLight = pDoc->m_lightList; ptrLight != NULL; ptrLight = ptrLight->m_ptrLight)
					{
						delete(ptrLight->m_shadowMap);
						ptrLight->m_shadowMap = NULL;
					}
					return FALSE;
				}
			}

			delete(ptrLight->m_shadowMap);
			ptrLight->m_shadowMap = NULL;
		}
		ptrLight = ptrLight->m_ptrLight;
	}
	delete zbuf;
	delete worldCoord;
	delete lightScreen;
	return TRUE;
}


BOOL CStageView::YoAccumulate(void)

// routine which uses accumulation buffer to do:
//   1) motion blur
//   2) depth of field
//   3) antialiasing
// shadow routines are also called from YoAccumulate

{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	//GLint              nmb = 1;
	//GLint              naa = 1;
	//GLint              ndof;
	GLint				i;
	GLint				j;
	GLint				k;
	//GLint              shutter_speed;
	//GLint              fstop;
	//GLint              time_anti_alias;
	//GLint              time_dof;
	long               z = 0x7fffffff;
	//GLfloat            m[16];
	GLdouble			e[9];
	GLdouble			f;
	GLdouble			cf;
	GLdouble			cr;
	GLdouble			eye[9];
	GLdouble			fov;
	GLdouble			front;
	GLdouble			rear;
	//GLfloat            aadx;
	//GLfloat            aady;
	//GLfloat            aadz;
	//GLfloat            dofdx;
	//GLfloat            dofdy;
	//GLfloat            dofdz;
	//GLfloat            shadowScaleFactor;
	//GLfloat            col[7];
	GLfloat            accumValue;
	//unsigned long      alpha;
	//unsigned short     red;
	//unsigned short     green;
	//unsigned short     blue;
	GLint				*shadowBuffer = NULL;
	GLint				*shadowAntialias = NULL;
	GLfloat				*imageBuffer = NULL;
	MSG					msg;
	GLdouble		modelView[16];
	GLdouble		proj[16];
	GLint			viewport[4];
	GLfloat			zbuf;



	::glClearAccum(0.0f, 0.0f, 0.0f, 0.0f);
	::glClear(GL_ACCUM_BUFFER_BIT);

	//sscanf(fl_get_input(obj_form4_camera_fstop), "%d", &fstop);

	if (pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR)
	{
		// do initial calculations for camera inbetweens
		if (pDoc->m_eyeList->m_currentScore != NULL
			&& pDoc->m_eyeList->m_currentScore->m_next != NULL
			&& pDoc->m_eyeList->m_currentScore->m_next->m_time
			- pDoc->m_eyeList->m_currentScore->m_time == 1)
		{
			for (i = 0; i < 9; i++)
			{
				e[i] = (pDoc->m_eyeList->m_currentScore->m_next->m_eye[i]
					- pDoc->m_eyeList->m_currentScore->m_eye[i]);
			}
			f = pDoc->m_eyeList->m_currentScore->m_next->m_fieldOfView
				- pDoc->m_eyeList->m_currentScore->m_fieldOfView;
			cf = pDoc->m_eyeList->m_currentScore->m_next->m_clipFront
				- pDoc->m_eyeList->m_currentScore->m_clipFront;
			cr = pDoc->m_eyeList->m_currentScore->m_next->m_clipRear
				- pDoc->m_eyeList->m_currentScore->m_clipRear;
		}
	}

	for (pDoc->m_timeMotionBlur = 0;
		pDoc->m_timeMotionBlur < pDoc->m_motionBlurIterations;
		pDoc->m_timeMotionBlur++)
	{
		if (pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR)
		{
			// compute inbetweens for camera at pDoc->m_timeMotionBlur and set camera
			if (pDoc->m_eyeList->m_currentScore != NULL
				&& pDoc->m_eyeList->m_currentScore->m_next != NULL
				&& pDoc->m_eyeList->m_currentScore->m_next->m_time
				- pDoc->m_eyeList->m_currentScore->m_time == 1)
			{
				for (j = 0; j < 9; j++)
				{
					eye[j] = pDoc->m_eyeList->m_currentScore->m_eye[j]
						+ (e[j] * pDoc->m_timeMotionBlur / pDoc->m_motionBlurIterations);
				}
				fov = pDoc->m_eyeList->m_currentScore->m_fieldOfView
					+ (f * pDoc->m_timeMotionBlur / pDoc->m_motionBlurIterations);
				front = pDoc->m_eyeList->m_currentScore->m_clipFront
					+ (cf * pDoc->m_timeMotionBlur / pDoc->m_motionBlurIterations);
				rear = pDoc->m_eyeList->m_currentScore->m_clipRear
					+ (cr * pDoc->m_timeMotionBlur / pDoc->m_motionBlurIterations);
				::glMatrixMode(GL_PROJECTION);
				::glLoadIdentity();
				::gluPerspective(fov, m_aspectRatio, front, rear);
				::glMatrixMode(GL_MODELVIEW);
				::glLoadIdentity();
				::gluLookAt(eye[0], eye[1], eye[2],
					eye[3], eye[4], eye[5],
					eye[6], eye[7], eye[8]);
			}
		}

		accumValue = 1.0f / pDoc->m_motionBlurIterations;

		if (pDoc->m_render3d & YO_RENDER3D_SHADOWS)
		{
			YoCreateShadowMaps();

			// restore original eye position
			if (pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR
				&& pDoc->m_eyeList->m_currentScore != NULL
				&& pDoc->m_eyeList->m_currentScore->m_next != NULL
				&& pDoc->m_eyeList->m_currentScore->m_next->m_time
				- pDoc->m_eyeList->m_currentScore->m_time == 1)
			{
				::glMatrixMode(GL_PROJECTION);
				::glLoadIdentity();
				::gluPerspective(fov, m_aspectRatio, front, rear);
				::glMatrixMode(GL_MODELVIEW);
				::glLoadIdentity();
				::gluLookAt(eye[0], eye[1], eye[2],
					eye[3], eye[4], eye[5],
					eye[6], eye[7], eye[8]);
			}
			else if (pDoc->m_eyeList->m_currentScore != NULL
				&& pDoc->m_eyeList->m_currentScore->m_next != NULL
				&& pDoc->m_eyeList->m_currentScore->m_next->m_time
				- pDoc->m_eyeList->m_currentScore->m_time == 1)
			{
				::glMatrixMode(GL_PROJECTION);
				::glLoadIdentity();
				::gluPerspective(pDoc->m_eyeList->m_currentScore->m_fieldOfView,
					m_aspectRatio,
					pDoc->m_eyeList->m_currentScore->m_clipFront,
					pDoc->m_eyeList->m_currentScore->m_clipRear);
				::glMatrixMode(GL_MODELVIEW);
				::glLoadIdentity();
				::gluLookAt(pDoc->m_eyeList->m_currentScore->m_eye[0],
					pDoc->m_eyeList->m_currentScore->m_eye[1],
					pDoc->m_eyeList->m_currentScore->m_eye[2],
					pDoc->m_eyeList->m_currentScore->m_eye[3],
					pDoc->m_eyeList->m_currentScore->m_eye[4],
					pDoc->m_eyeList->m_currentScore->m_eye[5],
					pDoc->m_eyeList->m_currentScore->m_eye[6],
					pDoc->m_eyeList->m_currentScore->m_eye[7],
					pDoc->m_eyeList->m_currentScore->m_eye[8]);
			}
		}

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (pDoc->m_grid[0])
		{
			YoRenderGrid();
		}
		YoRenderDevice(YO_RENDER_LIGHT);
		YoRenderDevice(YO_RENDER_FULL);

		if ((pDoc->m_render3d & YO_RENDER3D_SHADOWS)
			&& pDoc->m_numberLightsOn > 0)
		{
			if (pDoc->m_timeMotionBlur == 0)
			{
				shadowBuffer = new GLint[m_viewportSize[0] * m_viewportSize[1]];
			}
			for (i = 0; i < m_viewportSize[0] * m_viewportSize[1] - 1; i++)
			{
				*(shadowBuffer + i) = 255;
			}

			if ((pDoc->m_render3d & YO_RENDER3D_MOTION_BLUR)
				&& pDoc->m_eyeList->m_currentScore != NULL
				&& pDoc->m_eyeList->m_currentScore->m_next != NULL
				&& pDoc->m_eyeList->m_currentScore->m_next->m_time
				- pDoc->m_eyeList->m_currentScore->m_time == 1)
			{
				if (!YoHandleShadows(fov, front, rear, eye, shadowBuffer))
				{
					delete imageBuffer;
					delete shadowBuffer;
					return FALSE;
				}
			}
			else if (pDoc->m_eyeList->m_currentScore != NULL
				&& pDoc->m_eyeList->m_currentScore->m_next != NULL
				&& pDoc->m_eyeList->m_currentScore->m_next->m_time
				- pDoc->m_eyeList->m_currentScore->m_time == 1)
			{
				if (!YoHandleShadows(pDoc->m_eyeList->m_currentScore->m_fieldOfView,
					pDoc->m_eyeList->m_currentScore->m_clipFront,
					pDoc->m_eyeList->m_currentScore->m_clipRear,
					pDoc->m_eyeList->m_currentScore->m_eye,
					shadowBuffer))
				{
					delete imageBuffer;
					delete shadowBuffer;
					return FALSE;
				}
			}
			else
			{
				if (!YoHandleShadows(m_fieldOfView,
					m_clipFront,
					m_clipRear,
					m_eye,
					shadowBuffer))
				{
					delete imageBuffer;
					delete shadowBuffer;
					return FALSE;
				}
			}

			// do shadow reduction
			if (pDoc->m_timeMotionBlur == 0)
			{
				imageBuffer = new GLfloat[m_viewportSize[0] * m_viewportSize[1] * 4];
			}
			//::glReadPixels(0, 0, m_windowSize[0] - 1, m_windowSize[1] - 1,
			//	GL_RGBA, GL_FLOAT, (GLvoid *)imageBuffer);
			//::glReadPixels((m_windowSize[0] - m_viewportSize[0]) / 2,
			//	(m_windowSize[1] - m_viewportSize[1]) / 2,
			::glReadPixels(0, 0,
				m_viewportSize[0],
				m_viewportSize[1],
				GL_RGBA, GL_FLOAT, (GLvoid *)imageBuffer);

			TRACE2("imageBuffer = %lf %lf ", *(imageBuffer), *(imageBuffer + 1));
			TRACE2("%lf %lf\n", *(imageBuffer + 2), *(imageBuffer + 3));

/*******
				// do shadow anti-aliasing using golden mean 1.618
				for (i = 2; i < m_windowSize[1] - 2; i++)
				{
					// initial condition: j = 3
					col[0] = GM1 * (GLfloat)(*(shadow_buf + ((i + 2) * x_winsize)))
						+ GM2 * (GLfloat)(*(shadow_buf + ((i + 1) * x_winsize)))
						+ GM3 * (GLfloat)(*(shadow_buf + (i * x_winsize)))
						+ GM2 * (GLfloat)(*(shadow_buf + ((i - 1) * x_winsize)))
						+ GM1 * (GLfloat)(*(shadow_buf + ((i - 2) * x_winsize)));
					col[1] = GM2 * (GLfloat)(*(shadow_buf + ((i + 2) * x_winsize + 1)))
						+ GM3 * (GLfloat)(*(shadow_buf + ((i + 1) * x_winsize) + 1))
						+ GM4 * (GLfloat)(*(shadow_buf + (i * x_winsize) + 1))
						+ GM3 * (GLfloat)(*(shadow_buf + ((i - 1) * x_winsize) + 1))
						+ GM2 * (GLfloat)(*(shadow_buf + ((i - 2) * x_winsize) + 1));
					col[2] = GM3 * (GLfloat)(*(shadow_buf + ((i + 2) * x_winsize) + 2))
						+ GM4 * (GLfloat)(*(shadow_buf + ((i + 1) * x_winsize) + 2))
						+ GM5 * (GLfloat)(*(shadow_buf + (i * x_winsize) + 2))
						+ GM4 * (GLfloat)(*(shadow_buf + ((i - 1) * x_winsize) + 2))
						+ GM3 * (GLfloat)(*(shadow_buf + ((i - 2) * x_winsize) + 2));
					col[3] = GM4 * (GLfloat)(*(shadow_buf + ((i + 2) * x_winsize) + 3))
						+ GM5 * (GLfloat)(*(shadow_buf + ((i + 1) * x_winsize) + 3))
						+ GM6 * (GLfloat)(*(shadow_buf + (i * x_winsize) + 3))
						+ GM5 * (GLfloat)(*(shadow_buf + ((i - 1) * x_winsize) + 3))
						+ GM4 * (GLfloat)(*(shadow_buf + ((i - 2) * x_winsize) + 3));
					col[4] = GM3 * (GLfloat)(*(shadow_buf + ((i + 2) * x_winsize) + 4))
						+ GM4 * (GLfloat)(*(shadow_buf + ((i + 1) * x_winsize) + 4))
						+ GM5 * (GLfloat)(*(shadow_buf + (i * x_winsize) + 4))
						+ GM4 * (GLfloat)(*(shadow_buf + ((i - 1) * x_winsize) + 4))
						+ GM3 * (GLfloat)(*(shadow_buf + ((i - 2) * x_winsize) + 4));
					col[5] = GM2 * (GLfloat)(*(shadow_buf + ((i + 2) * x_winsize) + 5))
						+ GM3 * (GLfloat)(*(shadow_buf + ((i + 1) * x_winsize) + 5))
						+ GM4 * (GLfloat)(*(shadow_buf + (i * x_winsize) + 5))
						+ GM3 * (GLfloat)(*(shadow_buf + ((i - 1) * x_winsize) + 5))
						+ GM2 * (GLfloat)(*(shadow_buf + ((i - 2) * x_winsize) + 5));
					col[6] = GM1 * (GLfloat)(*(shadow_buf + ((i + 2) * x_winsize) + 6))
						+ GM2 * (GLfloat)(*(shadow_buf + ((i + 1) * x_winsize) + 6))
						+ GM3 * (GLfloat)(*(shadow_buf + (i * x_winsize) + 6))
						+ GM2 * (GLfloat)(*(shadow_buf + ((i - 1) * x_winsize) + 6))
						+ GM1 * (GLfloat)(*(shadow_buf + ((i - 2) * x_winsize) + 6));

					for (j = 4; j < x_winsize - 4; j++)
					{
						shadow_sf = (col[0] + col[1] + col[2] + col[3]
						+ col[4] + col[5] + col[6]) / GMTotal;

						if (shadow_sf < 0.03 || shadow_sf > 0.97)
						{
							if (*(shadow_buf + (i * x_winsize + j - 1)) == 0)
							{
								// leave image alone
							}
							else // ((*(shadow_buf + (i * x_winsize + j - 1)) &0x0ff) == 1) 
							{
								alpha = *(imgbuf + (i * x_winsize + j - 1)) & 0xff000000;
									*(imgbuf + (i * x_winsize + j - 1))
									= ((*(imgbuf + (i * x_winsize + j - 1))>>1) & 0x007f7f7f)
									| alpha;
							}
						}
						else  // anti alias
						{
							alpha
							= (*(imgbuf + (i * x_winsize + j - 1))>>24) & 0x000000ff;
							red = (unsigned short)
							*(imgbuf + (i * x_winsize + j - 1))&0x00ff;
							green = (unsigned short)
							(*(imgbuf + (i * x_winsize + j - 1))>>8)&0x00ff;
							blue = (unsigned short)
							(*(imgbuf + (i * x_winsize + j - 1))>>16)&0x00ff;
							red = (unsigned short)((float)red - shadow_sf
							* ((float)red - (float)red /  2.0));
							green = (unsigned short)((float)green - shadow_sf
							* ((float)green - (float)green /  2.0));
							blue = (unsigned short)((float)blue - shadow_sf
							* ((float)blue - (float)blue /  2.0));
							*(imgbuf + (i * x_winsize + j - 1))
							= red | green<<8 | blue<<16 | alpha;
						}
						col[0] = col[1] / GM1; 
						col[1] = col[2] / GM1; 
						col[2] = col[3] / GM1; 
						col[3] = col[4] * GM1; 
						col[4] = col[5] * GM1; 
						col[5] = col[6] * GM1; 
						col[6] = GM1
						* (float)(*(shadow_buf + ((i + 2) * x_winsize) + j + 3))
						+ GM2 * (float)(*(shadow_buf + ((i + 1) * x_winsize) + j + 3))
						+ GM3 * (float)(*(shadow_buf + (i * x_winsize) + j + 3))
						+ GM2 * (float)(*(shadow_buf + ((i - 1) * x_winsize) + j + 3))
						+ GM1 * (float)(*(shadow_buf + ((i - 2) * x_winsize) + j + 3));
					}
				}
******/
			// do shadow anti-aliasing and remove lone dots
			shadowAntialias = new GLint[m_viewportSize[0] * 3];
			for (i = 0; i < m_viewportSize[1]; i++)
			{
				for (j = 0; j < m_viewportSize[0]; j++)
				{
					if (j < 2 || j >= m_viewportSize[0] - 2
						|| i < 2 || i >= m_viewportSize[1] - 2)
					{
						*(shadowAntialias + (((i % 3) * m_viewportSize[0]) + j))
							= *(shadowBuffer + (i * m_viewportSize[0] + j));
					}
					else
					{
						*(shadowAntialias + (((i % 3) * m_viewportSize[0]) + j))
							= (GLint)(((*(shadowBuffer + ((i - 2) * m_viewportSize[0] + (j - 2)))
							+ *(shadowBuffer + ((i - 2) * m_viewportSize[0] + (j - 1)))
							+ *(shadowBuffer + ((i - 2) * m_viewportSize[0] + (j)))
							+ *(shadowBuffer + ((i - 2) * m_viewportSize[0] + (j + 1)))
							+ *(shadowBuffer + ((i - 2) * m_viewportSize[0] + (j + 2)))
							+ *(shadowBuffer + ((i - 1) * m_viewportSize[0] + (j - 2)))
							+ *(shadowBuffer + ((i - 1) * m_viewportSize[0] + (j - 1)))
							+ *(shadowBuffer + ((i - 1) * m_viewportSize[0] + (j)))
							+ *(shadowBuffer + ((i - 1) * m_viewportSize[0] + (j + 1)))
							+ *(shadowBuffer + ((i - 1) * m_viewportSize[0] + (j + 2)))
							+ *(shadowBuffer + ((i) * m_viewportSize[0] + (j - 2)))
							+ *(shadowBuffer + ((i) * m_viewportSize[0] + (j - 1)))
							+ *(shadowBuffer + ((i) * m_viewportSize[0] + (j)))
							+ *(shadowBuffer + ((i) * m_viewportSize[0] + (j + 1)))
							+ *(shadowBuffer + ((i) * m_viewportSize[0] + (j + 2)))
							+ *(shadowBuffer + ((i + 1) * m_viewportSize[0] + (j - 2)))
							+ *(shadowBuffer + ((i + 1) * m_viewportSize[0] + (j - 1)))
							+ *(shadowBuffer + ((i + 1) * m_viewportSize[0] + (j)))
							+ *(shadowBuffer + ((i + 1) * m_viewportSize[0] + (j + 1)))
							+ *(shadowBuffer + ((i + 1) * m_viewportSize[0] + (j + 2)))
							+ *(shadowBuffer + ((i + 2) * m_viewportSize[0] + (j - 2)))
							+ *(shadowBuffer + ((i + 2) * m_viewportSize[0] + (j - 1)))
							+ *(shadowBuffer + ((i + 2) * m_viewportSize[0] + (j)))
							+ *(shadowBuffer + ((i + 2) * m_viewportSize[0] + (j + 1)))
							+ *(shadowBuffer + ((i + 2) * m_viewportSize[0] + (j + 2))))
							/ 25.0) + 0.5);

					}

				}
				if (i >= 2)
				{
					for (k = 0; k < m_viewportSize[0]; k++)
					{
						*(shadowBuffer + ((i - 2) * m_viewportSize[0] + k))
							= *(shadowAntialias + ((((i - 2) % 3) * m_viewportSize[0]) + k));
					}
				}

			}
			delete shadowAntialias;


			for (i = 0; i < m_viewportSize[0] * m_viewportSize[1] - 1; i++)
			{
				*(imageBuffer + (i * 4)) *= (GLfloat)(*(shadowBuffer + i)) / 255.0f;
				*(imageBuffer + (i * 4) + 1) *= (GLfloat)(*(shadowBuffer + i)) / 255.0f;
				*(imageBuffer + (i * 4) + 2) *= (GLfloat)(*(shadowBuffer + i)) / 255.0f;
			}

			::glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
			::glGetDoublev(GL_PROJECTION_MATRIX, proj);
			::glGetIntegerv(GL_VIEWPORT, viewport);
			double rp[4];

			//::glReadPixels((m_windowSize[0] - m_viewportSize[0]) / 2,
			//	(m_windowSize[1] - m_viewportSize[1]) / 2,
			::glReadPixels(0, 0,
				1,
				1,
				GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid *)&zbuf);

			::gluUnProject((GLdouble)0.1,
				(GLdouble)0.1,
				(GLdouble)zbuf,
				modelView,
				proj,
				viewport,
				&rp[0],
				&rp[1],
				&rp[2]);


			//::glGetDoublev(GL_CURRENT_RASTER_POSITION, rp);
			//::glRasterPos3d(-5.0, 15.0, -1.0);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClearDepth(1.0f);
			::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//::glRasterPos3f(m_rasterPos[0], m_rasterPos[1], m_rasterPos[2]);
			::glRasterPos3d(rp[0], rp[1], rp[2]);
			::glGetDoublev(GL_CURRENT_RASTER_POSITION, rp);
			//::glDrawPixels(m_windowSize[0] - 1, m_windowSize[1] - 1,
			//	GL_RGBA, GL_FLOAT, (GLvoid *)imageBuffer);
			::glDrawPixels(m_viewportSize[0], m_viewportSize[1],
				GL_RGBA, GL_FLOAT, (GLvoid *)imageBuffer);

		}

		::glAccum(GL_ACCUM, accumValue);

		if (::PeekMessage(&msg, NULL, WM_LBUTTONUP, WM_LBUTTONUP, PM_NOREMOVE))
		{
			delete imageBuffer;
			delete shadowBuffer;
			return FALSE;
		}
	}

	delete imageBuffer;
	delete shadowBuffer;
	pDoc->m_timeMotionBlur = 0;

	::glAccum(GL_RETURN, 1.0f);

	return TRUE;
}


void CStageView::YoAntiAlias(void)
{
	GLfloat *srcBuffer;
	GLfloat *destBuffer;
	GLfloat *sbuf;
	GLfloat *dbuf;
	int i;
	int j;
	int k;
	GLfloat pw = 84.0;
	GLfloat pw1 = 2.0; //1.0; //3.0;
	GLfloat pw2 = 1.0; //0.25; //1.0;
	GLfloat pw3 = 1.0;
	GLfloat pwa = -30.0;
	GLfloat pw1a = 15.0;
	GLfloat pwb = -40.0;
	GLfloat pw1b = 20.0;
	GLfloat pwc = -20.0;
	GLfloat pw1c = 10.0;
	GLfloat pwd = -10.0;
	GLfloat pw1d = 5.0;
	double rp[3];
	GLdouble modelView[16];
	GLdouble proj[16];
	GLint viewport[4];
	GLfloat zbuf;

	srcBuffer = new GLfloat[m_windowSize[0] * m_windowSize[1] * 3];
	destBuffer = new GLfloat[m_windowSize[0] * m_windowSize[1] * 3];

	::glReadPixels(0, 0, m_windowSize[0], m_windowSize[1],
		GL_RGB, GL_FLOAT, (GLvoid *)srcBuffer);

	sbuf = srcBuffer;
	dbuf = destBuffer;

	for (j = 0; j < m_windowSize[1]; j++)
	{
		for (i = 0; i < m_windowSize[0]; i++)
		{
			for (k = 0; k < 3; k++)
			{
				if (j < 1 || j >= m_windowSize[1] - 1
					|| i < 1 || i >= m_windowSize[0] - 1)
				{
					*dbuf = *sbuf;
				}
				else if (j < 2 || j >= m_windowSize[1] - 2
					|| i < 2 || i >= m_windowSize[0] - 2)
				{
						*dbuf = ((*sbuf * pw)
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ (pw + (pw1 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
				}

				else if (j < 4 || j >= m_windowSize[1] - 4
					|| i < 4 || i >= m_windowSize[0] - 4)
				{
						*dbuf = ((*sbuf * pw)
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ (pw + (pw1 * (GLfloat)4.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
				}

				else
				{
					/***
					if (*sbuf == *(sbuf - 3)
						&& *sbuf == *(sbuf + 3)
						&& *sbuf == *(sbuf - m_windowSize[0] * 3)
						&& *sbuf == *(sbuf - 3 - m_windowSize[0] * 3)
						&& *sbuf == *(sbuf + 3 - m_windowSize[0] * 3)
						&& *sbuf == *(sbuf + m_windowSize[0] * 3)
						&& *sbuf == *(sbuf - 3 + m_windowSize[0] * 3)
						&& *sbuf == *(sbuf + 3 + m_windowSize[0] * 3))
					// all surrounding pixels are the same
					{
						*dbuf = *sbuf;
					}
					***/

					if (*sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3))
					// isolated pixel
					{
						*dbuf = ((*sbuf * 20.0)
							+ (*(sbuf - 3) * 10.0)
							+ (*(sbuf + 3) * 10.0)
							+ (*(sbuf - m_windowSize[0] * 3) * 10.0)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * 10.0)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * 10.0)
							+ (*(sbuf + m_windowSize[0] * 3) * 10.0)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * 10.0)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * 10.0))
							/ 100.0;
					}
					else if (*sbuf != *(sbuf + 3) && *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf + 3) == *(sbuf + m_windowSize[0] * 3))
					// diagonal line NE corner
					{
						*dbuf = ((*sbuf * (pw + pwa))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1a))
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1a))

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwa) + (pw1 * (GLfloat)2.0 + (pw1 + pw1a) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if (*sbuf != *(sbuf - 3) && *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf - 3) == *(sbuf + m_windowSize[0] * 3))
					// diagonal line NW corner
					{
						*dbuf = ((*sbuf * (pw + pwa))
							+ (*(sbuf - 3) * (pw1 + pw1a))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1a))

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwa) + (pw1 * (GLfloat)2.0 + (pw1 + pw1a) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if (*sbuf != *(sbuf + 3) && *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf + 3) == *(sbuf - m_windowSize[0] * 3))
					// diagonal line SE corner
					{
						*dbuf = ((*sbuf * (pw + pwa))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1a))
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1a))
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwa) + (pw1 * (GLfloat)2.0 + (pw1 + pw1a) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if (*sbuf != *(sbuf - 3) && *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf - 3) == *(sbuf - m_windowSize[0] * 3))
					// diagonal line SW corner
					{
						*dbuf = ((*sbuf * (pw + pwa))
							+ (*(sbuf - 3) * (pw1 + pw1a))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1a))
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwa) + (pw1 * (GLfloat)2.0 + (pw1 + pw1a) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if ((*sbuf == *(sbuf + 3) && *sbuf != *(sbuf + 6)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3)
						&& *(sbuf + 6) == *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf + 6) == *(sbuf + 3 + m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf + m_windowSize[0] * 3) && *sbuf != *(sbuf + m_windowSize[0] * 6)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3)
						&& *(sbuf + m_windowSize[0] * 6) == *(sbuf + 3)
						&& *(sbuf + m_windowSize[0] * 6) == *(sbuf + 3 + m_windowSize[0] * 3)))
					// diagonal line NE corner shift 1
					{
						*dbuf = ((*sbuf * (pw + pwb))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1b))
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1b))

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwb) + (pw1 * (GLfloat)2.0 + (pw1 + pw1b) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if ((*sbuf == *(sbuf - 3) && *sbuf != *(sbuf - 6)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *(sbuf - 6) == *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf - 6) == *(sbuf - 3 + m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf + m_windowSize[0] * 3) && *sbuf != *(sbuf + m_windowSize[0] * 6)
						&& *sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *(sbuf + m_windowSize[0] * 6) == *(sbuf - 3)
						&& *(sbuf + m_windowSize[0] * 6) == *(sbuf - 3 + m_windowSize[0] * 3)))
					// diagonal line NW corner shift 1
					{
						*dbuf = ((*sbuf * (pw + pwb))
							+ (*(sbuf - 3) * (pw1 + pw1b))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1b))

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwb) + (pw1 * (GLfloat)2.0 + (pw1 + pw1b) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if ((*sbuf == *(sbuf + 3) && *sbuf != *(sbuf + 6)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *(sbuf + 6) == *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf + 6) == *(sbuf + 3 - m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf - m_windowSize[0] * 3) && *sbuf != *(sbuf - m_windowSize[0] * 6)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *(sbuf - m_windowSize[0] * 6) == *(sbuf + 3)
						&& *(sbuf - m_windowSize[0] * 6) == *(sbuf + 3 - m_windowSize[0] * 3)))
					// diagonal line SE corner shift 1
					{
						*dbuf = ((*sbuf * (pw + pwb))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1b))
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1b))
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwb) + (pw1 * (GLfloat)2.0 + (pw1 + pw1b) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if ((*sbuf == *(sbuf - 3) && *sbuf != *(sbuf - 6)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *(sbuf - 6) == *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf - 6) == *(sbuf - 3 - m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf - m_windowSize[0] * 3) && *sbuf != *(sbuf - m_windowSize[0] * 6)
						&& *sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *(sbuf - m_windowSize[0] * 6) == *(sbuf - 3)
						&& *(sbuf - m_windowSize[0] * 6) == *(sbuf - 3 - m_windowSize[0] * 3)))
					// diagonal line SW corner shift 1
					{
						*dbuf = ((*sbuf * (pw + pwb))
							+ (*(sbuf - 3) * (pw1 + pw1b))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1b))
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwb) + (pw1 * (GLfloat)2.0 + (pw1 + pw1b) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}

					else if ((*sbuf == *(sbuf + 3)
						&& *sbuf == *(sbuf + 6)
						&& *sbuf != *(sbuf + 9)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 6 + m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf + 3 + m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf + 6 + m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf + m_windowSize[0] * 3)
						&& *sbuf == *(sbuf + m_windowSize[0] * 6)
						&& *sbuf != *(sbuf + m_windowSize[0] * 9)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 6)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf + 3)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf + 3 + m_windowSize[0] * 3)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf + 3 + m_windowSize[0] * 6)))
					// diagonal line NE corner shift 2
					{
						*dbuf = ((*sbuf * (pw + pwc))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1c))
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1c))

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwc) + (pw1 * (GLfloat)2.0 + (pw1 + pw1c) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					
					}
					else if ((*sbuf == *(sbuf - 3)
						&& *sbuf == *(sbuf - 6)
						&& *sbuf != *(sbuf - 9)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 6 + m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf - 3 + m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf - 6 + m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf + m_windowSize[0] * 3)
						&& *sbuf == *(sbuf + m_windowSize[0] * 6)
						&& *sbuf != *(sbuf + m_windowSize[0] * 9)
						&& *sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 6)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf - 3)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf - 3 + m_windowSize[0] * 3)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf - 3 + m_windowSize[0] * 6)))
					// diagonal line NW corner shift 2
					{
						*dbuf = ((*sbuf * (pw + pwc))
							+ (*(sbuf - 3) * (pw1 + pw1c))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1c))

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwc) + (pw1 * (GLfloat)2.0 + (pw1 + pw1c) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if ((*sbuf == *(sbuf + 3)
						&& *sbuf == *(sbuf + 6)
						&& *sbuf != *(sbuf + 9)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 6 - m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf + 3 - m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf + 6 - m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf - m_windowSize[0] * 3)
						&& *sbuf == *(sbuf - m_windowSize[0] * 6)
						&& *sbuf != *(sbuf - m_windowSize[0] * 9)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 6)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf + 3)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf + 3 - m_windowSize[0] * 3)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf + 3 - m_windowSize[0] * 6)))
					// diagonal line SE corner shift 2
					{
						*dbuf = ((*sbuf * (pw + pwc))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1c))
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1c))
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwc) + (pw1 * (GLfloat)2.0 + (pw1 + pw1c) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if ((*sbuf == *(sbuf - 3)
						&& *sbuf == *(sbuf - 6)
						&& *sbuf != *(sbuf - 9)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 6 - m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf - 3 - m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf - 6 - m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf - m_windowSize[0] * 3)
						&& *sbuf == *(sbuf - m_windowSize[0] * 6)
						&& *sbuf != *(sbuf - m_windowSize[0] * 9)
						&& *sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 6)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf - 3)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf - 3 - m_windowSize[0] * 3)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf - 3 - m_windowSize[0] * 6)))
					// diagonal line SW corner shift 2
					{
						*dbuf = ((*sbuf * (pw + pwc))
							+ (*(sbuf - 3) * (pw1 + pw1c))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1c))
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwc) + (pw1 * (GLfloat)2.0 + (pw1 + pw1c) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}

					else if ((*sbuf == *(sbuf + 3)
						&& *sbuf == *(sbuf + 6)
						&& *sbuf == *(sbuf + 9)
						&& *sbuf != *(sbuf + 12)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 6 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 9 + m_windowSize[0] * 3)
						&& *(sbuf + 12) == *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf + 12) == *(sbuf + 3 + m_windowSize[0] * 3)
						&& *(sbuf + 12) == *(sbuf + 6 + m_windowSize[0] * 3)
						&& *(sbuf + 12) == *(sbuf + 9 + m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf + m_windowSize[0] * 3)
						&& *sbuf == *(sbuf + m_windowSize[0] * 6)
						&& *sbuf == *(sbuf + m_windowSize[0] * 9)
						&& *sbuf != *(sbuf + m_windowSize[0] * 12)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 6)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 9)
						&& *(sbuf + m_windowSize[0] * 12) == *(sbuf + 3)
						&& *(sbuf + m_windowSize[0] * 12) == *(sbuf + 3 + m_windowSize[0] * 3)
						&& *(sbuf + m_windowSize[0] * 12) == *(sbuf + 3 + m_windowSize[0] * 6)
						&& *(sbuf + m_windowSize[0] * 12) == *(sbuf + 3 + m_windowSize[0] * 9)))
					// diagonal line NE corner shift 3
					{
						*dbuf = ((*sbuf * (pw + pwd))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1d))
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1d))

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwd) + (pw1 * (GLfloat)2.0 + (pw1 + pw1d) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if ((*sbuf == *(sbuf - 3)
						&& *sbuf == *(sbuf - 6)
						&& *sbuf == *(sbuf - 9)
						&& *sbuf != *(sbuf - 12)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 6 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 9 + m_windowSize[0] * 3)
						&& *(sbuf - 12) == *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf - 12) == *(sbuf - 3 + m_windowSize[0] * 3)
						&& *(sbuf - 12) == *(sbuf - 6 + m_windowSize[0] * 3)
						&& *(sbuf - 12) == *(sbuf - 9 + m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf + m_windowSize[0] * 3)
						&& *sbuf == *(sbuf + m_windowSize[0] * 6)
						&& *sbuf == *(sbuf + m_windowSize[0] * 9)
						&& *sbuf != *(sbuf + m_windowSize[0] * 12)
						&& *sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 6)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 9)
						&& *(sbuf + m_windowSize[0] * 12) == *(sbuf - 3)
						&& *(sbuf + m_windowSize[0] * 12) == *(sbuf - 3 + m_windowSize[0] * 3)
						&& *(sbuf + m_windowSize[0] * 12) == *(sbuf - 3 + m_windowSize[0] * 6)
						&& *(sbuf + m_windowSize[0] * 12) == *(sbuf - 3 + m_windowSize[0] * 9)))
					// diagonal line NW corner shift 3
					{
						*dbuf = ((*sbuf * (pw + pwd))
							+ (*(sbuf - 3) * (pw1 + pw1d))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1d))

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwd) + (pw1 * (GLfloat)2.0 + (pw1 + pw1d) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}	
					else if ((*sbuf == *(sbuf + 3)
						&& *sbuf == *(sbuf + 6)
						&& *sbuf == *(sbuf + 9)
						&& *sbuf != *(sbuf + 12)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 6 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 9 - m_windowSize[0] * 3)
						&& *(sbuf + 12) == *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf + 12) == *(sbuf + 3 - m_windowSize[0] * 3)
						&& *(sbuf + 12) == *(sbuf + 6 - m_windowSize[0] * 3)
						&& *(sbuf + 12) == *(sbuf + 9 - m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf - m_windowSize[0] * 3)
						&& *sbuf == *(sbuf - m_windowSize[0] * 6)
						&& *sbuf == *(sbuf - m_windowSize[0] * 9)
						&& *sbuf != *(sbuf - m_windowSize[0] * 12)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 6)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 9)
						&& *(sbuf - m_windowSize[0] * 12) == *(sbuf + 3)
						&& *(sbuf - m_windowSize[0] * 12) == *(sbuf + 3 - m_windowSize[0] * 3)
						&& *(sbuf - m_windowSize[0] * 12) == *(sbuf + 3 - m_windowSize[0] * 6)
						&& *(sbuf - m_windowSize[0] * 12) == *(sbuf + 3 - m_windowSize[0] * 9)))
					// diagonal line SE corner shift 3
					{
						*dbuf = ((*sbuf * (pw + pwd))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1d))
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1d))
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwd) + (pw1 * (GLfloat)2.0 + (pw1 + pw1d) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					else if ((*sbuf == *(sbuf - 3)
						&& *sbuf == *(sbuf - 6)
						&& *sbuf == *(sbuf - 9)
						&& *sbuf != *(sbuf - 12)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 6 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 9 - m_windowSize[0] * 3)
						&& *(sbuf - 12) == *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf - 12) == *(sbuf - 3 - m_windowSize[0] * 3)
						&& *(sbuf - 12) == *(sbuf - 6 - m_windowSize[0] * 3)
						&& *(sbuf - 12) == *(sbuf - 9 - m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf - m_windowSize[0] * 3)
						&& *sbuf == *(sbuf - m_windowSize[0] * 6)
						&& *sbuf == *(sbuf - m_windowSize[0] * 9)
						&& *sbuf != *(sbuf - m_windowSize[0] * 12)
						&& *sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 6)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 9)
						&& *(sbuf - m_windowSize[0] * 12) == *(sbuf - 3)
						&& *(sbuf - m_windowSize[0] * 12) == *(sbuf - 3 - m_windowSize[0] * 3)
						&& *(sbuf - m_windowSize[0] * 12) == *(sbuf - 3 - m_windowSize[0] * 6)
						&& *(sbuf - m_windowSize[0] * 12) == *(sbuf - 3 - m_windowSize[0] * 9)))
					// diagonal line SW corner shift 3
					{
						*dbuf = ((*sbuf * (pw + pwd))
							+ (*(sbuf - 3) * (pw1 + pw1d))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1d))
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ ((pw + pwd) + (pw1 * (GLfloat)2.0 + (pw1 + pw1d) * (GLfloat)2.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));
					}
					/***
					else if (*sbuf != *(sbuf + 3) && *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf + 3) == *(sbuf + m_windowSize[0] * 3))
					// diagonal line NE corner
					{
						//*dbuf = ((*sbuf * 48.0)
						//	+ (*(sbuf - 3) * 2.0)
						//	+ (*(sbuf + 3) * 20.0)
						//	+ (*(sbuf - m_windowSize[0] * 3) * 2.0)
						//	+ (*(sbuf - 3 - m_windowSize[0] * 3) * 2.0)
						//	+ (*(sbuf + 3 - m_windowSize[0] * 3) * 2.0)
						//	+ (*(sbuf + m_windowSize[0] * 3) * 20.0)
						//	+ (*(sbuf - 3 + m_windowSize[0] * 3) * 2.0)
						//	+ (*(sbuf + 3 + m_windowSize[0] * 3) * 2.0))
						//	/ 100.0;
						*dbuf = ((*sbuf * (pw + pwa))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1a))
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1a))
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwa) + (pw1 * (GLfloat)6.0 + pw1a * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));
					}
					else if (*sbuf != *(sbuf - 3) && *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf - 3) == *(sbuf + m_windowSize[0] * 3))
					// diagonal line NW corner
					{
						*dbuf = ((*sbuf * 48.0)
							+ (*(sbuf - 3) * 20.0)
							+ (*(sbuf + 3) * 2.0)
							+ (*(sbuf - m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf + m_windowSize[0] * 3) * 20.0)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * 2.0))
							/ 100.0;
						*dbuf = ((*sbuf * (pw + pwa))
							+ (*(sbuf - 3) * (pw1 + pw1a))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1a))
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwa) + (pw1 * (GLfloat)6.0 + pw1a * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));

					}
					else if (*sbuf != *(sbuf + 3) && *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf + 3) == *(sbuf - m_windowSize[0] * 3))
					// diagonal line SE corner
					{
						*dbuf = ((*sbuf * 48.0)
							+ (*(sbuf - 3) * 2.0)
							+ (*(sbuf + 3) * 20.0)
							+ (*(sbuf - m_windowSize[0] * 3) * 20.0)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf + m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * 2.0))
							/ 100.0;
						*dbuf = ((*sbuf * (pw + pwa))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1a))
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1a))
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwa) + (pw1 * (GLfloat)6.0 + pw1a * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));

					}
					else if (*sbuf != *(sbuf - 3) && *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf - 3) == *(sbuf - m_windowSize[0] * 3))
					// diagonal line SW corner
					{
						*dbuf = ((*sbuf * 48.0)
							+ (*(sbuf - 3) * 20.0)
							+ (*(sbuf + 3) * 2.0)
							+ (*(sbuf - m_windowSize[0] * 3) * 20.0)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf + m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * 2.0)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * 2.0))
							/ 100.0;
						*dbuf = ((*sbuf * (pw + pwa))
							+ (*(sbuf - 3) * (pw1 + pw1a))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1a))
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwa) + (pw1 * (GLfloat)6.0 + pw1a * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));
					}

					else if ((*sbuf == *(sbuf + 3) && *sbuf != *(sbuf + 6)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3)
						&& *(sbuf + 6) == *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf + 6) == *(sbuf + 3 + m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf + m_windowSize[0] * 3) && *sbuf != *(sbuf + m_windowSize[0] * 6)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3)
						&& *(sbuf + m_windowSize[0] * 6) == *(sbuf + 3)
						&& *(sbuf + m_windowSize[0] * 6) == *(sbuf + 3 + m_windowSize[0] * 3)))
					// diagonal line NE corner shift 1
					{
						*dbuf = ((*sbuf * (pw + pwb))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1b))
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1b))
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwb) + (pw1 * (GLfloat)6.0 + pw1b * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));
					}
					else if ((*sbuf == *(sbuf - 3) && *sbuf != *(sbuf - 6)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *(sbuf - 6) == *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf - 6) == *(sbuf - 3 + m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf + m_windowSize[0] * 3) && *sbuf != *(sbuf + m_windowSize[0] * 6)
						&& *sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *(sbuf + m_windowSize[0] * 6) == *(sbuf - 3)
						&& *(sbuf + m_windowSize[0] * 6) == *(sbuf - 3 + m_windowSize[0] * 3)))
					// diagonal line NW corner shift 1
					{
						*dbuf = ((*sbuf * (pw + pwb))
							+ (*(sbuf - 3) * (pw1 + pw1b))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1b))
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwb) + (pw1 * (GLfloat)6.0 + pw1b * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));
					}
					else if ((*sbuf == *(sbuf + 3) && *sbuf != *(sbuf + 6)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *(sbuf + 6) == *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf + 6) == *(sbuf + 3 - m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf - m_windowSize[0] * 3) && *sbuf != *(sbuf - m_windowSize[0] * 6)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *(sbuf - m_windowSize[0] * 6) == *(sbuf + 3)
						&& *(sbuf - m_windowSize[0] * 6) == *(sbuf + 3 - m_windowSize[0] * 3)))
					// diagonal line SE corner shift 1
					{
						*dbuf = ((*sbuf * (pw + pwb))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1b))
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1b))
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwb) + (pw1 * (GLfloat)6.0 + pw1b * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));
					}
					else if ((*sbuf == *(sbuf - 3) && *sbuf != *(sbuf - 6)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *(sbuf - 6) == *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf - 6) == *(sbuf - 3 - m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf - m_windowSize[0] * 3) && *sbuf != *(sbuf - m_windowSize[0] * 6)
						&& *sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *(sbuf - m_windowSize[0] * 6) == *(sbuf - 3)
						&& *(sbuf - m_windowSize[0] * 6) == *(sbuf - 3 - m_windowSize[0] * 3)))
					// diagonal line SW corner shift 1
					{
						*dbuf = ((*sbuf * (pw + pwb))
							+ (*(sbuf - 3) * (pw1 + pw1b))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1b))
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwb) + (pw1 * (GLfloat)6.0 + pw1b * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));
					}

					else if ((*sbuf == *(sbuf + 3)
						&& *sbuf == *(sbuf + 6)
						&& *sbuf != *(sbuf + 9)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 6 + m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf + 3 + m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf + 6 + m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf + m_windowSize[0] * 3)
						&& *sbuf == *(sbuf + m_windowSize[0] * 6)
						&& *sbuf != *(sbuf + m_windowSize[0] * 9)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 + m_windowSize[0] * 6)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf + 3)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf + 3 + m_windowSize[0] * 3)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf + 3 + m_windowSize[0] * 6)))
					// diagonal line NE corner shift 2
					{
						*dbuf = ((*sbuf * (pw + pwc))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1c))
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1c))
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwc) + (pw1 * (GLfloat)6.0 + pw1c * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));
					}
					else if ((*sbuf == *(sbuf - 3)
						&& *sbuf == *(sbuf - 6)
						&& *sbuf != *(sbuf - 9)
						&& *sbuf != *(sbuf + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 6 + m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf + m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf - 3 + m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf - 6 + m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf + m_windowSize[0] * 3)
						&& *sbuf == *(sbuf + m_windowSize[0] * 6)
						&& *sbuf != *(sbuf + m_windowSize[0] * 9)
						&& *sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 + m_windowSize[0] * 6)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf - 3)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf - 3 + m_windowSize[0] * 3)
						&& *(sbuf + m_windowSize[0] * 9) == *(sbuf - 3 + m_windowSize[0] * 6)))
					// diagonal line NW corner shift 2
					{
						*dbuf = ((*sbuf * (pw + pwc))
							+ (*(sbuf - 3) * (pw1 + pw1c))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * (pw1 + pw1c))
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwc) + (pw1 * (GLfloat)6.0 + pw1c * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));
					}
					else if ((*sbuf == *(sbuf + 3)
						&& *sbuf == *(sbuf + 6)
						&& *sbuf != *(sbuf + 9)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 6 - m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf + 3 - m_windowSize[0] * 3)
						&& *(sbuf + 9) == *(sbuf + 6 - m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf - m_windowSize[0] * 3)
						&& *sbuf == *(sbuf - m_windowSize[0] * 6)
						&& *sbuf != *(sbuf - m_windowSize[0] * 9)
						&& *sbuf != *(sbuf + 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf + 3 - m_windowSize[0] * 6)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf + 3)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf + 3 - m_windowSize[0] * 3)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf + 3 - m_windowSize[0] * 6)))
					// diagonal line SE corner shift 2
					{
						*dbuf = ((*sbuf * (pw + pwc))
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * (pw1 + pw1c))
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1c))
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwc) + (pw1 * (GLfloat)6.0 + pw1c * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));
					}
					else if ((*sbuf == *(sbuf - 3)
						&& *sbuf == *(sbuf - 6)
						&& *sbuf != *(sbuf - 9)
						&& *sbuf != *(sbuf - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 6 - m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf - m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf - 3 - m_windowSize[0] * 3)
						&& *(sbuf - 9) == *(sbuf - 6 - m_windowSize[0] * 3))
						||
						(*sbuf == *(sbuf - m_windowSize[0] * 3)
						&& *sbuf == *(sbuf - m_windowSize[0] * 6)
						&& *sbuf != *(sbuf - m_windowSize[0] * 9)
						&& *sbuf != *(sbuf - 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 3)
						&& *sbuf != *(sbuf - 3 - m_windowSize[0] * 6)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf - 3)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf - 3 - m_windowSize[0] * 3)
						&& *(sbuf - m_windowSize[0] * 9) == *(sbuf - 3 - m_windowSize[0] * 6)))
					// diagonal line SW corner shift 2
					{
						*dbuf = ((*sbuf * (pw + pwc))
							+ (*(sbuf - 3) * (pw1 + pw1c))
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * (pw1 + pw1c))
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ ((pw + pwc) + (pw1 * (GLfloat)6.0 + pw1c * (GLfloat)2.0) + (pw2 * (GLfloat)16.0));
					}
					else
					{
						*dbuf = ((*sbuf * pw)
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf - 6 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 3 + m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + 6 + m_windowSize[0] * 6) * pw2))
							/ (pw + (pw1 * (GLfloat)8.0) + (pw2 * (GLfloat)16.0));
					}
					***/
					else
					{
						*dbuf = ((*sbuf * pw)
							+ (*(sbuf - 3) * pw1)
							+ (*(sbuf + 3) * pw1)
							+ (*(sbuf - m_windowSize[0] * 3) * pw1)
							+ (*(sbuf + m_windowSize[0] * 3) * pw1)

							+ (*(sbuf - 6) * pw2)
							+ (*(sbuf + 6) * pw2)
							+ (*(sbuf - m_windowSize[0] * 6) * pw2)
							+ (*(sbuf + m_windowSize[0] * 6) * pw2)

							+ (*(sbuf - 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 - m_windowSize[0] * 3) * pw3)
							+ (*(sbuf - 3 + m_windowSize[0] * 3) * pw3)
							+ (*(sbuf + 3 + m_windowSize[0] * 3) * pw3))

							/ (pw + (pw1 * (GLfloat)4.0) + (pw2 * (GLfloat)4.0) + (pw3 * (GLfloat)4.0));

					}
						
				}

			//if (j == 100 || j == 300)
			//{
			//	TRACE2("%f %f\n", *sbuf, *dbuf);
			//}
			sbuf++;
			dbuf++;
			}
		}
	}


		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(m_fieldOfView, m_aspectRatio, m_clipFront, m_clipRear);
		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		::gluLookAt(m_eye[0], m_eye[1], m_eye[2],
			m_eye[3], m_eye[4], m_eye[5],
			m_eye[6], m_eye[7], m_eye[8]);

		::glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
		::glGetDoublev(GL_PROJECTION_MATRIX, proj);
		::glGetIntegerv(GL_VIEWPORT, viewport);
		
		::glReadPixels(0, 0,
			1,
			1,
			GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid *)&zbuf);

		::gluUnProject((GLdouble)0.1,
			(GLdouble)0.1,
			(GLdouble)zbuf,
			modelView,
			proj,
			viewport,
			&rp[0],
			&rp[1],
			&rp[2]);

		//::glGetDoublev(GL_CURRENT_RASTER_POSITION, rp);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		::glRasterPos3d(rp[0], rp[1], rp[2]);
		//::glGetDoublev(GL_CURRENT_RASTER_POSITION, rp);

	::glDrawPixels(m_windowSize[0], m_windowSize[1],
		GL_RGB, GL_FLOAT, (GLvoid *)destBuffer);

	delete(srcBuffer);
	delete(destBuffer);

	return;
}


BOOL CStageView::YoRenderStockScene()
{
	// draw a red wire sphere inside a
	// light blue cube

	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	YoRenderGrid();
	::glPushMatrix();

	// rotate the wire sphere so it's vertically
	// oriented
	::glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
	::glColor3f( 1.0f, 0.0f, 0.0f );
	::auxWireSphere( .5 );
	::glColor3f( 0.5f, 0.5f, 1.0f );
	::auxWireCube( 1.0 );
	::glPopMatrix();

	::glFinish();
	if (::SwapBuffers(m_pDC->GetSafeHdc()) == FALSE)
	{
		MessageBox("SwapBuffers failed");
		return FALSE;
	}
    return TRUE;
}	

void CStageView::YoWalk(CPoint point)
{
	long x1;
	long y1;
	double x;
	double y;
	double z;
	double r;
	double rhat;
	double theta;
	double phi;

  /* when finished reset x0 and y0 to a number where abs(x1 - x0) and        */
  /* abs(y1 - y0) > THRESH_WALK to prevent jerky motion.                     */
  //if (option == OPT_WALK_DONE)
  //{
  //  x0 = -9999;                                        
  //  return;
  //}

  //sscanf(fl_get_input(obj_clipfront), "%f", &front);
  //sscanf(fl_get_input(obj_cliprear), "%f", &rear);

  //fov = abs(10 * (int)fl_get_slider_value(obj_zoom));

	x = m_eye[0] - m_eye[3];
	y = m_eye[1] - m_eye[4];
	z = m_eye[2] - m_eye[5];

	r = sqrt(x * x + y * y);

	if ((x > 0.0 && y >= 0.0) || x < 0.0)
	{
		theta = atan2(y, x);
	}
	else if (x > 0.0 && y < 0.0)
	{
		theta = 2.0 * PI + atan2(y, x);
	}
	else if (y > 0.0)
	{
		theta = PI / 2.0;
	}
	else if (y < 0.0)
	{
		theta = -PI / 2.0;
	}
	else
	{
		theta = 0.0;
	}

	rhat = sqrt(r * r + z * z);

	if (r != 0.0)
	{
		phi = atan2(z, r);
	}
	else if (z > 0.0)
	{
		phi = PI / 2.0;
	}
	else if (z < 0.0)
	{
		phi = -PI / 2.0;
	}
	else
	{
		phi = 0.0;
	}

	x1 = point.x;
	y1 = -point.y;                  // y in wgl is opposite of irisGL
  
	theta -= m_walkSpeed * (x1 - x0);
	phi -= m_walkSpeed * (y1 - y0);
	x0 = x1;
	y0 = y1;

	y = r * sin(theta);
	x = r * cos(theta);

	if (phi > PI / 2.0)
	{
    phi = PI / 2.0 - .0001;
	}
	if (phi < -PI / 2.0)
	{
		phi = 3.0 * PI / 2.0 + .0001;
	}
	r = rhat * cos(phi);
	z = rhat * sin(phi);

	x = r * cos(theta);
	y = r * sin(theta);

	m_eye[0] = x + m_eye[3];
	m_eye[1] = y + m_eye[4];
	m_eye[2] = z + m_eye[5];

    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();
	::gluPerspective(m_fieldOfView, m_aspectRatio,
		m_clipFront, m_clipRear);
	
    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
	::gluLookAt(m_eye[0], m_eye[1], m_eye[2],
		m_eye[3], m_eye[4], m_eye[5],
		m_eye[6], m_eye[7], m_eye[8]);

	YoRender(YO_RENDER_QUICK);
	return;
}

void CStageView::YoUpdateEyeDlg()
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	CWnd *pCBox;
	char s[32];

	if (pMainFrame->m_wndDlgEye != NULL
		&& pMainFrame->m_wndDlgEyeVisible == TRUE)
	{
		sprintf(s, "%.1lf", m_eye[0] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMX);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", m_eye[1] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMY);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", m_eye[2] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMZ);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();

		sprintf(s, "%.1lf", m_eye[3] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOX);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", m_eye[4] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOY);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", m_eye[5] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOZ);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
	}

	/***
	if ((m_mode == YO_MODE_PAN || m_mode == YO_MODE_WALK)
		&& pMainFrame->m_wndDlgEye != NULL)
	{
		sprintf(s, "%.1lf", m_eye[0] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMX);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", m_eye[1] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMY);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", m_eye[2] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_FROMZ);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
	}

	if (m_mode == YO_MODE_PAN && pMainFrame->m_wndDlgEye != NULL)
	{
		sprintf(s, "%.1lf", m_eye[3] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOX);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", m_eye[4] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOY);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
		sprintf(s, "%.1lf", m_eye[5] * pDoc->m_unitScaleFactor);
		pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOZ);
		pCBox->SetWindowText(s);
		pCBox->UpdateWindow();
	}
	***/
}


void CStageView::YoPanInOut(CPoint point)
{
	long x1;
	long y1;
	double d;

	x1 = point.x;
	y1 = point.y;

	if (x1 > x0)
	{
		d = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
	}
	else
	{
		d = -sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
	}

	m_eye[0] += (m_eye[3] - m_eye[0]) * d * m_panInOutSpeed;
	m_eye[1] += (m_eye[4] - m_eye[1]) * d * m_panInOutSpeed;
	m_eye[2] += (m_eye[5] - m_eye[2]) * d * m_panInOutSpeed;

	x0 = x1;
	y0 = y1;
	::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();
	::gluPerspective(m_fieldOfView, m_aspectRatio,
		m_clipFront, m_clipRear);
	
    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
	::gluLookAt(m_eye[0], m_eye[1], m_eye[2],
		m_eye[3], m_eye[4], m_eye[5],
		m_eye[6], m_eye[7], m_eye[8]);

	YoRender(YO_RENDER_QUICK);
	return;
}

void CStageView::YoPanLeftRightUpDown(CPoint point)
{
	long x1;
	long y1;

	x1 = point.x;
	y1 = -point.y;		// y in wgl is opposite of openGL 
	
	m_eye[3] = m_originalEye[3]
		+ (((GLdouble)(x0 - x1) / (GLdouble)m_windowSize[0])
		* m_windowSizeInWorldCoords[0])
		+ (((GLdouble)(y0 - y1) / (GLdouble)m_windowSize[1])
		* m_windowSizeInWorldCoords[3]);
	m_eye[4] = m_originalEye[4]
		+ (((GLdouble)(x0 - x1) / (GLdouble)m_windowSize[0])
		* m_windowSizeInWorldCoords[1])
		+ (((GLdouble)(y0 - y1) / (GLdouble)m_windowSize[1])
		* m_windowSizeInWorldCoords[4]);
	m_eye[5] = m_originalEye[5]
		+ (((GLdouble)(x0 - x1) / (GLdouble)m_windowSize[0])
		* m_windowSizeInWorldCoords[2])
		+ (((GLdouble)(y0 - y1) / (GLdouble)m_windowSize[1])
		* m_windowSizeInWorldCoords[5]);
	m_eye[0] = m_originalEye[0] + (m_eye[3] - m_originalEye[3]);
	m_eye[1] = m_originalEye[1] + (m_eye[4] - m_originalEye[4]);
	m_eye[2] = m_originalEye[2] + (m_eye[5] - m_originalEye[5]);

/****
	x = m_eye[0] - m_eye[3];
	y = m_eye[1] - m_eye[4];
	z = m_eye[2] - m_eye[5];

	r = sqrt(x * x + y * y);

	if ((x > 0.0 && y >= 0.0) || x < 0.0)
	{
		theta = atan2(y, x);
	}
	else if (x > 0.0 && y < 0.0)
	{
		theta = 2.0 * PI + atan2(y, x);
	}
	else if (y > 0.0)
	{
		theta = PI / 2.0;
	}
	else if (y < 0.0)
	{
		theta = -PI / 2.0;
	}
	else
	{
		theta = 0.0;
	}

	rhat = sqrt(r * r + z * z);

	if (r != 0.0)
	{
		phi = atan2(z, r);
	}
	else if (z > 0.0)
	{
		phi = PI / 2.0;
	}
	else if (z < 0.0)
	{
		phi = -PI / 2.0;
	}
	else
	{
		phi = 0.0;
	}

	x1 = point.x;
	y1 = -point.y;                  // y in wgl is opposite of irisGL
  
 
	x = sin(theta) * (x1 - x0);
	y = -cos(theta) * (x1 - x0);
	r = sin(phi) * (y1 - y0);
	z = -cos(phi) * (y1 - y0);
	x0 = x1;
	y0 = y1;

	x += r * cos(theta);
	y += r * sin(theta);


	m_eye[0] += x * m_panLeftRightUpDownSpeed;
	m_eye[1] += y * m_panLeftRightUpDownSpeed;
	m_eye[2] += z * m_panLeftRightUpDownSpeed;
	m_eye[3] += x * m_panLeftRightUpDownSpeed;
	m_eye[4] += y * m_panLeftRightUpDownSpeed;
	m_eye[5] += z * m_panLeftRightUpDownSpeed;
****/

	::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();
	::gluPerspective(m_fieldOfView, m_aspectRatio,
		m_clipFront, m_clipRear);
	
    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
	::gluLookAt(m_eye[0], m_eye[1], m_eye[2],
		m_eye[3], m_eye[4], m_eye[5],
		m_eye[6], m_eye[7], m_eye[8]);
	
	YoRender(YO_RENDER_QUICK);
	return;
}


void CStageView::YoTranslateDevice(CPoint point)
{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	long x1;
	long y1;

	x1 = point.x;
	y1 = -point.y;		// y in wgl is opposite of openGL  

	pDoc->m_currentDevice->m_ptrPart->m_translate[0]
		= m_originalTranslate[0]
		+ (((GLdouble)(x1 - x0) / (GLdouble)m_windowSize[0])
		* m_windowSizeInWorldCoords[0])
		+ (((GLdouble)(y1 - y0) / (GLdouble)m_windowSize[1])
		* m_windowSizeInWorldCoords[2]);
	pDoc->m_currentDevice->m_ptrPart->m_translate[1]
		= m_originalTranslate[1]
		+ (((GLdouble)(x1 - x0) / (GLdouble)m_windowSize[0])
		* m_windowSizeInWorldCoords[1])
		+ (((GLdouble)(y1 - y0) / (GLdouble)m_windowSize[1])
		* m_windowSizeInWorldCoords[3]);

	/*****

	x = m_eye[0] - m_eye[3];
	y = m_eye[1] - m_eye[4];
	z = m_eye[2] - m_eye[5];

	r = sqrt(x * x + y * y);

	if ((x > 0.0 && y >= 0.0) || x < 0.0)
	{
		theta = atan2(y, x);
	}
	else if (x > 0.0 && y < 0.0)
	{
		theta = 2.0 * PI + atan2(y, x);
	}
	else if (y > 0.0)
	{
		theta = PI / 2.0;
	}
	else if (y < 0.0)
	{
		theta = -PI / 2.0;
	}
	else
	{
		theta = 0.0;
	}

	rhat = sqrt(r * r + z * z);

	if (r != 0.0)
	{
		phi = atan2(z, r);
	}
	else if (z > 0.0)
	{
		phi = PI / 2.0;
	}
	else if (z < 0.0)
	{
		phi = -PI / 2.0;
	}
	else
	{
		phi = 0.0;
	}

	x1 = point.x;
	y1 = -point.y;                  // y in wgl is opposite of irisGL
  
 
	x = sin(theta) * (x1 - x0);
	y = -cos(theta) * (x1 - x0);
	r = sin(phi) * (y1 - y0);
	//z = -cos(phi) * (y1 - y0);
	x0 = x1;
	y0 = y1;

	x += r * cos(theta);
	y += r * sin(theta);

	pDoc->m_currentDevice->m_ptrPart->m_translate[0] += x;
	pDoc->m_currentDevice->m_ptrPart->m_translate[1] += y;
****/

	//if ((x1 - x0) % 5 == 0)
	{
		YoRender(YO_RENDER_QUICK);
	//::GetMessage(&msg, NULL, WM_MOUSEFIRST, WM_MOUSELAST);
	}
	return;
}

void CStageView::YoTxyz(CStagePart *ptrPart, GLdouble *translate, GLdouble *rotate)
// performs translations and rotations on the specified part

{
	if (ptrPart == NULL)
	{
		return;
	}

	switch (ptrPart->m_txyz)
	{
		case YO_TXYZ_TXYZ:
			glTranslated(translate[0], translate[1], translate[2]);
			glRotated(rotate[0], 1.0, 0.0, 0.0);
			glRotated(rotate[1], 0.0, 1.0, 0.0);
			glRotated(rotate[2], 0.0, 0.0, 1.0);
			break;

		case YO_TXYZ_TXZY:
			glTranslated(translate[0], translate[1], translate[2]);
			glRotated(rotate[0], 1.0, 0.0, 0.0);
			glRotated(rotate[1], 0.0, 0.0, 1.0);
			glRotated(rotate[2], 0.0, 1.0, 0.0);
			break;

		case YO_TXYZ_TYXZ:
			glTranslated(translate[0], translate[1], translate[2]);
			glRotated(rotate[0], 0.0, 1.0, 0.0);
			glRotated(rotate[1], 1.0, 0.0, 0.0);
			glRotated(rotate[2], 0.0, 0.0, 1.0);
			break;

		case YO_TXYZ_TYZX:
			glTranslated(translate[0], translate[1], translate[2]);
			glRotated(rotate[0], 0.0, 1.0, 0.0);
			glRotated(rotate[1], 0.0, 0.0, 1.0);
			glRotated(rotate[2], 1.0, 0.0, 0.0);
			break;

		case YO_TXYZ_TZXY:
			glTranslated(translate[0], translate[1], translate[2]);
			glRotated(rotate[0], 0.0, 0.0, 1.0);
			glRotated(rotate[1], 1.0, 0.0, 0.0);
			glRotated(rotate[2], 0.0, 1.0, 0.0);
			break;

		case YO_TXYZ_TZYX:
			glTranslated(translate[0], translate[1], translate[2]);
			glRotated(rotate[0], 0.0, 0.0, 1.0);
			glRotated(rotate[1], 0.0, 1.0, 0.0);
			glRotated(rotate[2], 1.0, 0.0, 0.0);
			break;

		case YO_TXYZ_XYZT:
			glRotated(rotate[0], 1.0, 0.0, 0.0);
			glRotated(rotate[1], 0.0, 1.0, 0.0);
			glRotated(rotate[2], 0.0, 0.0, 1.0);
			glTranslated(translate[0], translate[1], translate[2]);
			break;

		case YO_TXYZ_XZYT:
			glRotated(rotate[0], 1.0, 0.0, 0.0);
			glRotated(rotate[1], 0.0, 0.0, 1.0);
			glRotated(rotate[2], 0.0, 1.0, 0.0);
			glTranslated(translate[0], translate[1], translate[2]);
			break;
		
		case YO_TXYZ_YXZT:
			glRotated(rotate[0], 0.0, 1.0, 0.0);
			glRotated(rotate[1], 1.0, 0.0, 0.0);
			glRotated(rotate[2], 0.0, 0.0, 1.0);
			glTranslated(translate[0], translate[1], translate[2]);
			break;

		case YO_TXYZ_YZXT:
			glRotated(rotate[0], 0.0, 1.0, 0.0);
			glRotated(rotate[1], 0.0, 0.0, 1.0);
			glRotated(rotate[2], 1.0, 0.0, 0.0);
			glTranslated(translate[0], translate[1], translate[2]);
			break;

		case YO_TXYZ_ZXYT:
			glRotated(rotate[0], 0.0, 0.0, 1.0);
			glRotated(rotate[1], 1.0, 0.0, 0.0);
			glRotated(rotate[2], 0.0, 1.0, 0.0);
			glTranslated(translate[0], translate[1], translate[2]);
			break;

		case YO_TXYZ_ZYXT:
			glRotated(rotate[0], 0.0, 0.0, 1.0);
			glRotated(rotate[1], 0.0, 1.0, 0.0);
			glRotated(rotate[2], 1.0, 0.0, 0.0);
			glTranslated(translate[0], translate[1], translate[2]);
			break;
	}
	return;
}


void CStageView::YoMotionBlurModelView(GLint option, CStageScore *ptrScore)

// routine which either sets (inserts) or restores (deletes)
// a temporary part modelview matrix.
// assumes that ptrScore->m_next is valid (i.e. not NULL)
// m_time = ptrScore->m_time + 1

{
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	static GLdouble m[16];
	GLint i;

	if (option == YO_RENDER_MOTION_BLUR_SET)
	{
		for (i = 0; i < 16; i++) 
		{
			m[i] = ptrScore->m_modelView[i];
			ptrScore->m_modelView[i] = ptrScore->m_modelView[i]
				+ (((ptrScore->m_next->m_modelView[i]
				- ptrScore->m_modelView[i])
				/***
				* YO_MIN(1.0, (float)pDoc->m_framesPerSecond
				/ (float)pDoc->m_shutterSpeed)***/)
				* pDoc->m_timeMotionBlur / pDoc->m_motionBlurIterations);
		}
	}
	else if (option == YO_RENDER_MOTION_BLUR_RESTORE)
	{
		for (i = 0; i < 16; i++) 
		{
			ptrScore->m_modelView[i] = m[i];
		}
	}
}


void CStageView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
	if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		return;
	}
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return;
	}
	int index;
	UINT dpt;
	CStagePolygonList *currentPolygonList;

	TRACE0("CStageView::OnLButtonDblClk()\n");

	pDoc->m_undo->YoUndo();

	if (pDoc->m_mode != YO_MODE_WORKCELL
		|| pMainFrame->m_viewPartActive == TRUE
		|| pMainFrame->m_trackDlgActive == TRUE
		|| pMainFrame->m_analysisActive == TRUE
		|| pMainFrame->m_viewTagActive == TRUE
		|| (pDoc->m_currentDevice != NULL
		&& pDoc->m_currentDevice->m_type == YO_CAMERA
		&& ((CStageCamera *)pDoc->m_currentDevice)->m_enabled == TRUE))
	{
		return;
	}

	if (pDoc->m_acceptSocket != NULL)
	{
		return;
	}

	if (pDoc->m_deviceList != NULL)
	{
		YoRender(YO_RENDER_PICK_PART_AND_TAG);
		dpt = pDoc->YoMakeCurrentDevicePartTag(point);
		if (dpt == YO_DEVICE_PART
			&& pDoc->m_currentDevice->m_type != YO_TRACK)
		{
			// find selected polygon and modify texture
			YoRender(YO_RENDER_PICK_PART);
			if (pDoc->YoGetClosestPolygon(point) == TRUE)
			{
				index = pDoc->m_currentPolygonIndex;
				for (currentPolygonList = pDoc->m_currentPart->m_polygonList; index >= 10; currentPolygonList = currentPolygonList->m_next)
				{
					index -= 10;
				}

				TRACE3("numberSides = %d    ptrVertices = %d   ptrTexture = %d\n",
					currentPolygonList->m_numberSides[pDoc->m_currentPolygonIndex % 10],
					currentPolygonList->m_vertices[pDoc->m_currentPolygonIndex % 10],
					currentPolygonList->m_texture[pDoc->m_currentPolygonIndex % 10]);
			}
			pMainFrame->SendMessage(WM_COMMAND, ID_VIEW_CURRENT_PART, (LPARAM)0);

		}
		else if (dpt == YO_DEVICE_PART
			&& pDoc->m_currentDevice->m_type == YO_TRACK)
		{
			pMainFrame->SendMessage(WM_COMMAND, ID_VIEW_CURRENT_PART, (LPARAM)0);
		}

		else if (dpt == YO_TAG)
		{
			pMainFrame->SendMessage(WM_COMMAND, ID_VIEW_CURRENT_TAG, (LPARAM)0);
		}
	}

	
	return;

	CView::OnLButtonDblClk(nFlags, point);
}



BOOL CStageView::YoDrawBoundingBox(CStagePart *ptrPart)
{
	CStageDoc* pDoc = GetDocument();
	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
	{
		return FALSE;
	}
	GLdouble vStart[3];
	GLdouble vEnd[3];
	BOOL reenableLighting = FALSE;

	if (::glIsEnabled(GL_LIGHTING))
	{
		reenableLighting = TRUE;
		::glDisable(GL_LIGHTING);
	}
	::glColor4fv(ptrPart->m_wireframe);

	vStart[0] = ptrPart->m_min[0];
	vStart[1] = ptrPart->m_min[1];
	vStart[2] = ptrPart->m_min[2];
	vEnd[0] = ptrPart->m_max[0];
	vEnd[1] = ptrPart->m_min[1];
	vEnd[2] = ptrPart->m_min[2];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vEnd[0] = ptrPart->m_min[0];
	vEnd[2] = ptrPart->m_max[2];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vEnd[1] = ptrPart->m_max[1];
	vEnd[2] = ptrPart->m_min[2];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vStart[0] = ptrPart->m_max[0];
	vStart[1] = ptrPart->m_max[1];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vEnd[0] = ptrPart->m_max[0];
	vEnd[1] = ptrPart->m_min[1];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vEnd[1] = ptrPart->m_max[1];
	vEnd[2] = ptrPart->m_max[2];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vStart[1] = ptrPart->m_min[1];
	vStart[2] = ptrPart->m_max[2];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vEnd[1] = ptrPart->m_min[1];
	vEnd[2] = ptrPart->m_min[2];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vEnd[0] = ptrPart->m_min[0];
	vEnd[2] = ptrPart->m_max[2];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vStart[0] = ptrPart->m_min[0];
	vStart[1] = ptrPart->m_max[1];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vEnd[1] = ptrPart->m_max[1];
	vEnd[2] = ptrPart->m_min[2];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	vEnd[0] = ptrPart->m_max[0];
	vEnd[2] = ptrPart->m_max[2];
	::glBegin(GL_LINES);
		::glVertex3dv(vStart);
		::glVertex3dv(vEnd);
	::glEnd();

	if (reenableLighting == TRUE)
	{
		::glEnable(GL_LIGHTING);
	}

	return TRUE;
}

