// stageView.h : interface of the CStageView class
//
/////////////////////////////////////////////////////////////////////////////

class CStageView : public CView
{
//protected: // create from serialization only
public:
	CStageView();
	DECLARE_DYNCREATE(CStageView)

// Attributes
public:
	CStageDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStageView)
	afx_msg void OnCancelEditSrvr();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// stage declarations

#define YO_MODE_WALK 1
#define YO_MODE_PAN 3
#define YO_MODE_DEVICE_TRANSLATE 4
#define YO_MENU_HIDE 0
#define YO_MENU_EYE 1
#define YO_MENU_SCRIPT 2
#define YO_MOUSE_LEFT 1
#define YO_MOUSE_RIGHT 3
#define PI 3.14159265359
//#define YO_THRESH_WIDTH 680
//#define YO_THRESH_WIDTH 420
#define YO_THRESH_WIDTH 482

public:
	virtual BOOL YoSetupPixelFormat(void);
	virtual BOOL YoRenderStockScene(void);
	//virtual BOOL YoRenderSetup(int);
	virtual BOOL YoRender(int);
	virtual BOOL YoRenderDevice(int);
	virtual BOOL YoRenderPart(CStageDevice *, int);
	virtual void YoRenderTrackSeg(CStagePart *, int);
	void YoWriteDevice(CStageDevice *, int);
	BOOL YoDrawBoundingBox(CStagePart *);
	BOOL YoRenderPartPolygons(CStagePart *, int);
	BOOL YoRenderPartCoords(CStagePart *, int);
	BOOL YoRenderTags(CStagePart *, int);
	BOOL YoRenderOrigin(CStagePart *, int);
	virtual BOOL YoRenderGrid(void);
	virtual BOOL YoRenderAnalysis(void);
	void YoTxyz(CStagePart *, GLdouble *, GLdouble *);
	BOOL YoCreateShadowMaps(void);
	BOOL YoHandleShadows(GLdouble, GLdouble, GLdouble,
		GLdouble[9], GLint *);
	BOOL YoAccumulate(void);
	void YoAntiAlias(void);
	void YoUpdateEyeDlg(void);

	UINT m_mode;

//private:
	BOOL YoInitOpenGL();
	void YoWalk(CPoint);
	void YoPanInOut(CPoint);
	void YoPanLeftRightUpDown(CPoint);
	void YoTranslateDevice(CPoint);
	void YoMotionBlurModelView(GLint, CStageScore *);

	HGLRC m_hRC;
	CClientDC* m_pDC;
	long x0;               // beginning mouse x coordinate
	long y0;               // beginning mouse y coordinate
	CPoint p0;
	UINT m_mouse;
	double m_walkSpeed;
	double m_panInOutSpeed;
	double m_panLeftRightUpDownSpeed;

public:
	GLdouble m_fieldOfView;
	GLdouble m_aspectRatio;
	GLint m_viewportSize[2];
	GLint m_windowSize[2];
	GLdouble m_clipFront;
	GLdouble m_clipRear;
	GLdouble m_eye[9];
	GLfloat m_rasterPos[3];
	GLdouble m_viewInv[16];
	GLdouble m_mBase[16];
	FILE *m_fp;
	// vars used to compute device translate
	GLdouble	m_windowSizeInWorldCoords[6];
	GLdouble	m_originalTranslate[3];
	GLdouble	m_originalEye[6];
};

#ifndef _DEBUG  // debug version in stageView.cpp
inline CStageDoc* CStageView::GetDocument()
   { return (CStageDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
