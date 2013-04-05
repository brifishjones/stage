// SrvrItem.h : interface of the CStageSrvrItem class
//

class CStageSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CStageSrvrItem)

// Constructors
public:
	CStageSrvrItem(CStageDoc* pContainerDoc);

// Attributes
	CStageDoc* GetDocument() const
		{ return (CStageDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CStageSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////
